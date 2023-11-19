#ifndef CLIENT_H
#define CLIENT_H
#include <QObject>
#include <QTcpSocket>
#include <QTime>
#include <thread>
#include <QMessageBox>
#include <iostream>
#include "Kia_main_struct.h"
#include "Kia_enums.h"
class Client : public QObject
{
    Q_OBJECT
public:
    Client(const QString &strHost, int nPort, std::shared_ptr<Kia_settings> kia_settings);
public slots:
    void send_data_to_server(const qint16& num, QStringList data_for_server = QStringList());
signals:
    void sendToAction(QString num_mpi);
    void send_to_set_table(QStringList);
    void set_window_info_mpi(qint16, QString);
    void set_window_info_ai_window(qint16, QString);
    void set_window_info_system_window(qint16, QString);
    void set_window_info_error_window(qint16, QString);
    void set_window_info_mpi_dev(qint16, QString);
    void set_window_info_device_protocol(qint16, qint16, QString);
    void set_1s_mark_status(qint16);
    void send_to_table_state_window(qint16 type_bi, QStringList);
    void signal_for_mpi_dev(QString data);
    void send_to_table_settings_window(QStringList);
    void send_variables(QStringList);
    void send_axis_settings(QStringList);
    void set_kia_gui_settings();
    void check_connect(qint16, qint16);
    void send_status_info(QStringList);
    void load_profile();

    void set_read_command(qint16, qint16, qint16, QString);
private:
    QString m_server_ip;
    int32_t m_port;
    quint16 m_nNextBlockSize = 0;
    std::shared_ptr<Kia_settings> m_kia_settings;
    QTcpSocket* m_pTcpScoket;
    quint16 m_tag = 0;
    void connect_to_server();
private slots:
    void slot_read_server();
    void slot_connected();
    void slot_error(QAbstractSocket::SocketError err);
};

#endif // CLIENT_H
