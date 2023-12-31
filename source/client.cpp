#include "client.h"

Client::Client(const QString& strHost, int nPort, std::shared_ptr<Kia_settings> kia_settings):
    m_server_ip(strHost)
  , m_port(nPort)
  , m_kia_settings(kia_settings)
{
    connect_to_server();
}

void Client::send_data_to_server(uint16_t num, QStringList data_for_server)
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_3);
    out << quint16(0) << data_for_server << m_kia_settings->m_type_bokz << m_kia_settings->m_type_bi << num;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    m_pTcpScoket->write(arrBlock);
    arrBlock.clear();
}

void Client::connect_to_server()
{
    m_pTcpScoket = new QTcpSocket(this);
    m_pTcpScoket->connectToHost(m_server_ip, m_port);
    connect(m_pTcpScoket, SIGNAL(connected()), SLOT(slot_connected()));
    connect(m_pTcpScoket, SIGNAL(readyRead()), SLOT(slot_read_server()));
    connect(m_pTcpScoket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slot_error(QAbstractSocket::SocketError)));
}

void Client::slot_connected()
{
    std::cout << "Received the connected() signal" << std::endl;
}

void Client::slot_error(QAbstractSocket::SocketError err)
{
    QString strError =
            "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                             "The host was not found." :
                             err == QAbstractSocket::RemoteHostClosedError ?
                                 "The remote host is closed." :
                                 err == QAbstractSocket::ConnectionRefusedError ?
                                     "The connection was refused." :
                                     QString(m_pTcpScoket->errorString()));
    std::cout << strError.toStdString() << std::endl;
    m_kia_settings->m_is_con_to_core = CS_IS_OFF;
    emit check_connect(CHECK_CON_CORE, m_kia_settings->m_is_con_to_core);
}

void Client::slot_read_server()
{

    QDataStream in(m_pTcpScoket);
    in.setVersion(QDataStream::Qt_5_3);
    for(;;)
    {
        if (!m_nNextBlockSize)
        {
            if (m_pTcpScoket->bytesAvailable() < sizeof (quint16))
            {
                break;
            }
            in >> m_nNextBlockSize;
        }
        if (m_pTcpScoket->bytesAvailable() < m_nNextBlockSize)
        {
            break;
        }
        QStringList data_from_server;
        qint16 num;
        qint16 type_bokz;
        qint16 type_bi;
        in >> data_from_server >> type_bokz >> type_bi >> num;
        //m_kia_settings->m_kia_gui_settings->m_mpi_command_name
        switch (num)
        {
        case SET_KIA_GUI_SETTINGS:
            m_kia_settings->m_type_bokz = type_bokz;
            m_kia_settings->m_type_bi = type_bi;
            m_kia_settings->m_kia_bi_settings->m_count_bi = data_from_server[0].toInt();
            break;
        case SEND_MPI_COMMAND:
            for (uint16_t num_comm = 0; num_comm < data_from_server.size(); num_comm++)
            {
                if (num_comm % 2 == 0)
                    m_kia_settings->m_kia_gui_settings->m_mpi_command_name.push_back(std::make_pair(data_from_server[num_comm], data_from_server[num_comm + 1].toInt()));
            }
            m_kia_settings->m_kia_bokz_settings->m_max_mpi_command = data_from_server.size() / 2;
            break;
        case SEND_CYCLOGRAMS_AI:
            for (uint16_t num_cycl = 0; num_cycl < data_from_server.size(); num_cycl++)
            {
                if (num_cycl % 2 == 0)
                    m_kia_settings->m_kia_gui_settings->m_cyclogram_ai_name.push_back(std::make_pair(data_from_server[num_cycl], data_from_server[num_cycl + 1].toInt()));
            }
            m_kia_settings->m_kia_bokz_settings->m_max_cyclograms_in_ai = data_from_server.size() / 2;
            std::cout << m_kia_settings->m_kia_bokz_settings->m_max_cyclograms_in_ai << std::endl;
            break;
        case SEND_CYCLOGRAMS_TP:
            for (uint16_t num_cycl = 0; num_cycl < data_from_server.size(); num_cycl++)
            {
                if (num_cycl % 2 == 0)
                    m_kia_settings->m_kia_gui_settings->m_cyclogram_tp_name.push_back(std::make_pair(data_from_server[num_cycl], data_from_server[num_cycl + 1].toInt()));
            }
            m_kia_settings->m_kia_bokz_settings->m_max_cyclograms_in_tp = data_from_server.size() / 2;
            break;
        case CONNECT_TO_CORE:
            m_kia_settings->m_kias_db->m_experiment_id = data_from_server[0];
            emit set_kia_gui_settings();
            m_kia_settings->m_is_con_to_core = CS_IS_ON;
            emit check_connect(CHECK_CON_CORE, m_kia_settings->m_is_con_to_core);
            break;
        case CONNECT_TO_DB:
            m_kia_settings->m_is_con_to_db = data_from_server[0].toInt();
            emit check_connect(CHECK_CON_DB, m_kia_settings->m_is_con_to_db);
            break;
        case SEND_DATA_TO_STATE_WINDOW:
            emit send_to_table_state_window(type_bi, data_from_server);
            break;
        case SEND_DATA_TO_SETTINGS_WINDOW:
            emit send_to_table_settings_window(data_from_server);
            break;
        case SET_INFO_TO_WINDOW_INFO:
            emit set_window_info_system_window(data_from_server[0].toInt(), data_from_server[1]);
            break;
        case SET_WINDOW_INFO_MPI:
            emit set_window_info_mpi(data_from_server[0].toInt(), data_from_server[1]);
            break;
        case SET_WINDOW_INFO_DEVICE_PROTOCOL:
            emit set_window_info_device_protocol(data_from_server[0].toInt(), data_from_server[1].toInt(), data_from_server[2]);
            break;
        case SET_STATUS_1S_MARK:
            emit set_1s_mark_status(data_from_server[0].toInt());
            break;
        case SET_INFO_TO_ERROR_WINDOW:
            emit set_window_info_error_window(data_from_server[0].toInt(), data_from_server[1]);
            break;
        case SET_INFO_TO_AI_WINDOW:
            emit set_window_info_ai_window(data_from_server[0].toInt(), data_from_server[1]);
            break;
        case SEND_COMMAND:
            emit set_read_command(data_from_server[0].toInt(), data_from_server[1].toInt(), data_from_server[2].toInt(), data_from_server[3]);
            break;
        case SEND_STATUS_INFO:
            emit send_status_info(data_from_server);
            break;
        case LOAD_PROFILE:
            emit load_profile();
            break;
        }
        m_nNextBlockSize = 0;
    }
}
