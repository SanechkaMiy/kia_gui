#ifndef KIA_ENUMS_H
#define KIA_ENUMS_H
enum  CHECK_STATUS
{
    CS_IS_OFF = 0,
    CS_IS_ON = 1
};

enum Kia_command
{
    SHTMI_1 = 0,
    SHTMI_2 = 1,
    MSHI_OR = 2,
    DTMI_ONE = 3,
    MLOCK_ONE = 76,
    SMTI = 4,
    VMTI = 5,
    SYNCHRO = 6,
    SKOR = 7,

    CYCLOGRAM_NO = 8,
    CYCLOGRAM_TO = 9,
    CYCLOGRAM_LOC = 10,
    CYCLOGRAM_OO = 39,

    CYCLOGRAM_STATE_ON = 11,
    CYCLOGRAM_STATE_OFF = 12,
    DO_RESTART = 62,

    COMMAND_FULL_EXP = 13,
    COMMAND_BIN_EXP = 40,

    POWER_ON = 14,
    POWER_OFF = 15,

    ON_1S = 16,
    OFF_1S = 17,

    COMMAND_NO = 18,
    COMMAND_TO = 19,
    COMMAND_LOC = 20,
    COMMAND_OTCLP = 21,
    COMMAND_BSHV = 77,
    COMMAND_RESTART = 78,
    COMMAND_OO = 79,

    CYCLOGRAM_OFFLINE_TEST = 22,
    CYCLOGRAM_STOP = 23,
    CYCLOGRAM_DEFINE_ADDRESS = 24,
    COMMAND_OS = 25,
    COMMAND_VSKOU = 26,
    SET_USED_BOKZ = 27,
    SET_USED_ADDRESS = 28,
    SET_TD = 29,
    SET_NUM_MPI = 30,

    SET_TYPE_FRAME_RECIEVE = 31,
    SET_TYPE_FRAME = 32,
    SET_BSHV = 33,

    CYCLOGRAM_OPERATION = 34,
    CYCLOGRAM_1S_MARK = 35,
    CYCLOGRAM_TEST_MKO = 36,
    CYCLOGRAM_TECH_RUN = 37,

    SET_CURRENT_LPI = 38,
    SET_USED_MPI_COMMAND_IN_CYCLOGRAM = 41,
    SET_CYCLOGRAM_SETTINGS_IF_DO_A_LOT = 42,
    SET_EXC_FREQ = 43,
    CYCLOGRAM_ZKR = 44,
    DO_FULL_FRAME = 45,
    DO_BIN_FRAME = 52,

    CYCL_FULL_FRAMES = 46,
    SET_FULL_FRAMES_SETTINGS = 47,
    SET_RELAY_PULSE = 48,
    SET_RELAY_PULSE_TIME = 49,
    SET_RELAY_POLAR = 50,
    SET_SEC_MARK_PERIOD = 51,
    SET_NUM_BI = 53,
    IMITATOR_ON = 54,
    IMITATOR_OFF = 55,
    CONROL_COMMAND_ON = 56,
    CONROL_COMMAND_OFF = 57,
    SET_USED_CHANNEL = 58,

    SET_UPN = 59,
    GET_CHPN = 60,
    //64 is free
    //65 is free,
    // is free 66,
    // is free 67,
    CYCLOGRAM_SYNCHRO = 68,
    CYCLOGRAM_TEST_ADRESS = 69,
    SET_AI_SKIP_OR_STOP = 70,
    DEBUGGING_COMMAND = 71,
    COMMAND_ZKR = 72,
    COMMAND_OTKR = 61,
    SET_IS_OFF_POWER_IN_TP = 73,
    SET_DO_CYCLOGRAM_IN_TP = 74,
    SET_COUNT_TO_DO_CYCLOGRAM_IN_TP = 75,

    SET_DO_CYCLOGRAM_IN_AI = 80,

    SET_DO_CYCLOGRAM_IN_DO = 81,
    SET_PAUSE_DO_CYCLOGRAM_IN_DO = 82,

    SET_DO_CYCLOGRAM_POWER_IN_DO = 63
};

enum KIA_GUI_COMMAND
{
    SET_KIA_GUI_SETTINGS = 0,
    SEND_MPI_COMMAND = 1,
    SEND_OTHER_MPI_COMMAND = 19,
    SEND_CYCLOGRAMS_AI = 2,
    SEND_CYCLOGRAMS_RI = 17,
    SEND_CYCLOGRAMS_DO = 18,
    SEND_CYCLOGRAMS_TP = 3,
    CONNECT_TO_CORE = 4,
    CONNECT_TO_DB = 5,
    SEND_DATA_TO_STATE_WINDOW = 6,
    SEND_DATA_TO_SETTINGS_WINDOW = 7,
    SET_INFO_TO_WINDOW_INFO = 8,
    SET_WINDOW_INFO_MPI = 9,
    SET_WINDOW_INFO_DEVICE_PROTOCOL = 10,
    SET_STATUS_1S_MARK = 11,
    SET_INFO_TO_ERROR_WINDOW = 12,
    SET_INFO_TO_AI_WINDOW = 13,
    SEND_COMMAND = 14,
    SEND_STATUS_INFO = 15,
    LOAD_PROFILE = 16,
    SEND_PN_COMMAND = 20,
    SEND_CYCLOGRAMS_POWER = 21,
    SEND_CYCLOGRAMS_POWER_DO = 22,
};

enum NUM_MPI_COMMAND_M60
{
    NMC_M60_SHTMI1 = 0,
    NMC_M60_SHTMI2 = 1,
    NMC_M60_MSHIOR = 2,
    NMC_M60_DTMI = 3,
    NMC_M60_DTMI_LOC = 4,
    NMC_M60_SMTI = 5,
    NMC_M60_VMTI = 6,
    NMC_M60_SYNCHRO = 7,
    NMC_M60_SKOR = 8,
    NMC_M60_COMMAND_NO = 9,
    NMC_M60_COMMAND_TO = 10,
    NMC_M60_COMMAND_FULL_EXP = 11,
    NMC_M60_COMMAND_LOC = 12,
    NMC_M60_COMMAND_OTCLP = 13,
    NMC_M60_COMMAND_OPENKR = 14,
    NMC_M60_COMMAND_ZKR = 15,
    NMC_M60_COMMAND_KVAOR = 16,
    NMC_M60_COMMAND_OS = 17,
    NMC_M60_COMMAND_VSKOU = 18,
    NMC_M60_INITIAL_STATE = 19,
    NMC_M60_BLOCK_OU = 20,
    NMC_M60_UNBLOCK_OU = 21,
};

enum NUM_MPI_COMMAND_Mf
{
    MF_SHTMI1 = 0,
    MF_SHTMI2 = 1,
    MF_MSHIOR = 2,
    MF_DTMI = 3,
    MF_MLOC = 4
};

enum TYPE_BOKZ
{
    TYPE_BOKZ_BOKZM60 = 0,
    TYPE_BOKZ_BOKZMF= 1,
};

enum TYPE_BI
{
    TYPE_BI_BKPIK= 0,
    TYPE_BI_BIU = 1
};

enum TYPE_KLED
{
    CHECK_CON_CORE = 0,
    CHECK_CON_DB = 1
};

enum KIA_STATUS
{
    KiaS_SUCCESS = 0x0000,
    KiaS_FAIL = 0x0001
};

enum KIA_CYCLOGRAM_STATUS
{
    KCS_SUCCES = 0x0000,
    KCS_CNT_FIND_OR = 0x0001
};
enum DO_IT
{
    EP_NOEXCHANGE = 0x0001,
    EP_NOPROTECTEDEXCHANGE = 0x0002,
    EP_NOFULLEXCHANGE = 0x0004,
    EP_NODATACONVERTION = 0x0008,
    EP_NOTEXTCONVERTION = 0x0010,
    EP_NOSQLCONVERTION = 0x0020,
    EP_NOOUTTOWINDOW = 0x0040,

    EP_NOSQLPROTOCOL = 0x2000,
    EP_NOCHARTPROTOCOL = 0x4000,
    EP_NOTEXTPROTOCOL = 0x8000,
    EP_DOALL = 0x0000,
};

enum KIA_NAME_CYCLOGRAMS
{
    KNCycl_AI = 0,
    KNCycl_REGULAR = 1,
    KNCycl_POWER = 2,
    KNCycl_AI_USED_CYCL = 3
};

enum SET_PARAM_CYCLOGRAM
{
    SPC_COUNT = 0,
    SPC_PERIOD = 1,
    SPC_DURATION = 2,
};

enum DO_SAVE_TO_PROTOCOL
{
    SP_DO_MKO = 0,
    SP_DO_DEV = 1,
    SP_DO_SYSTEM = 2,
    SP_DO_AI = 3,
    SP_DO_ERROR  = 4
};

enum TABLE_SETTINGS
{
    TS_USED_BOKZ = 0,
    TS_ADDRESS = 1,
    TS_MPI = 2,
    TS_LPI = 3,
    TS_TYPE_BI = 4,
    TS_NUM_CH = 5,
    TS_TD = 6
};

enum BIU_STATE_TABLE
{
    Biu_Num_bi = 0,
    Biu_ST_KS = 1,
    Biu_KRR = 2,
    Biu_BRTUZ = 3,
    Biu_KP = 4,
    Biu_BTVK = 5,
    Biu_DEV_V = 6,
    Biu_VIP_V = 7,
    Biu_dev_fid_1 = 8,
    Biu_dev_fid_2 = 9,
    Biu_im_fid_1 = 10,
    Biu_im_fid_2 = 11,
    Biu_td = 12,
    Biu_1C = 13
};

enum BINARY_PROTOCOL
{
    DO_BINARY_FALSE = 0,
    DO_BINARY_TRUE = 1
};

enum BI_STATUS_1S_MARK
{
    BIS1SM_BOTH_ON = 0,
    BIS1SM_REZERV_ON= 1,
    BIS1SM_MAIN_ON = 2,
    BIS1M_BOTH_OFF = 3
};

enum BI_TURN_MAIN_OR_REZ_CH
{
    BI_MAIN_REZ_ON = 0,
    BI_MAIN_ON = 1,
    BI_REZERV_ON = 2,
    BI_ALL_OFF = 3
};
enum TYPE_RELAY_COM
{
    TRC_PULSE = 0,
    TRC_TIME_PULSE = 1,
    TRC_POLAR = 2
};

enum TYPE_BI_SETTINGS
{
    TBS_SEC_MARK = 0,
    TBS_RELAY_COMMAND = 1
};

enum QUERY_PARM
{
    QP_X = 0,
    QP_Y = 1,
    QP_ARR_X = 2,
    QP_ARR_Y = 3,
    QP_TYPE_DEV = 4,
    QP_TYPE_ARR = 5,
    QP_X_DESC = 6,
    QP_Y_DESC = 7,
    QP_X_UM = 8,
    QP_Y_UM = 9,
    QP_NUM_BOKZ = 10,
    QP_NUM_BOKZ_FOR_ANGLES = 11,
    QP_NUM_WIDGET = 12,
    QP_TYPE_WIDGET = 13,
    QP_NUM_MAIN_TAB_WIDGET = 14,
};

enum TYPE_COMMAND
{
    IS_MPI_COMMAND = 0,
    IS_CYCLOGRAM = 1,
};

enum DEV_STATUS_POWERED
{
    IS_POWERED = 0,
    IS_NOT_POWERED = 1,
};

enum COMMAND_PARAM
{
    IS_PARAM = 0,
    IS_TABLE = 1,
};


enum TYPE_TABLE
{
    TT_MATRIX_PSK = 0,
    TT_Qo = 1,
    TT_Wo = 2
};

enum STATUS_PARAM
{
    IS_DEFAULT = 0,
    IS_CHANGED = 1,

};


enum PROFILE_DATA
{
    NAME_PROFILE = 0,
    NUM_PROFILE = 1,

};

enum STATUS_TABLE
{
    ST_BSHV = 0,
    ST_ST1= 1,
    ST_ST2= 2

};

enum TABLE_STATE_COL_VALUE
{
    IS_VISIBILYTY = 0,
    IS_COLOR = 1

};

enum TYPE_CONNECTION
{
    TYPE_RAW = 0,
    TYPE_DATA = 1
};

enum TYPE_DATA_FOCUS
{
    FOCUS = 0,
    CORD_X = 1,
    CORD_Y = 2
};


enum TABS_PARAM
{
    NUM_TAB = 0,
    NAME_TAB = 1
};

enum TYPE_MENU_ACTIONS
{
    STATE_WORK = 0,
    PCI = 1,
    RES = 2,
    COMMANDS = 3,
    GET_FRAMES = 4
};

enum COMMAND_SETTINGS
{
    CS_NUM_BOKZ = 0,
    CS_DIRECTION = 1,
    CS_FORMAT = 2,
    CS_SUB_ADDRESS = 3,
    CS_WORD_DATA = 4,
    CS_STRUCT_ID = 5,
    CS_STRUCT_ID_DESCK = 6,
    CS_DATA_TO_EXC = 7
};

enum TYPE_WINDOW_INFO
{
    WINDOW_MPI = 0,
    WINDOW_MPI_DEV = 1,
    WINDOW_DEV_PROTOCOL = 2,
    WINDOW_SYSTEM_INFO = 3,
    WINDOW_ERROR_INFO = 4,
    WINDOW_AI_PROTOCOL = 5,
    WINDOW_MPI_COMMAND = 6
};

enum TYPE_SETTINGS_FOR_TP
{
    USED_CYCLOGRAM = 0,
    COUNT_TO_DO_CYCLOGRAM = 1,
    OFF_POWER = 2
};

enum TYPE_SETTINGS_FOR_REGULAR_CYCLOGRAM
{
    USED_COMMAND = 0,
    PAUSE_COMMAND = 1,
};

enum TYPE_COMMAND_TO_SEND
{
    CYCL_FUNC = 0,
    CYCL_NAME = 1,
    CYCL_TYPE_TO_SEND = 2
};


enum TYPE_PN_TO_SEND
{
    TP_NAME = 0,
    TP_KEY = 1,
    TP_TYPE_VIEW = 2,
    TP_TYPE_COMMAND = 3,
};

enum FRAME_SETTINGS
{
    FS_TYPE_RECEIVE = 0,
    FS_TYPE_FRAME = 1
};

enum PIO_ARR_DESCR
{
    PAD_NAME = 0,
    PAD_VALUE = 1,
    PAD_LOW_INTERVAL = 2,
    PAD_HIGH_INTERVAL = 3
};
#endif // KIA_ENUMS_H
