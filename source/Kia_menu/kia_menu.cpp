#include "kia_menu.h"

Kia_menu::Kia_menu()
{
    map_key_command[SHTMI_1] = QKeySequence(Qt::Key_F2);
    map_key_command[SHTMI_2] = QKeySequence(Qt::Key_F3);
    map_key_command[MSHI_OR] = QKeySequence(Qt::Key_F4);
    map_key_command[DTMI_ONE] = QKeySequence(Qt::Key_F5);
    map_key_command[MLOCK_ONE] = QKeySequence(Qt::Key_F6);

    map_key_cyclogram_tp[CYCLOGRAM_NO] = QKeySequence(Qt::CTRL + Qt::Key_N);
    map_key_cyclogram_tp[CYCLOGRAM_TO] = QKeySequence(Qt::CTRL + Qt::Key_T);
    map_key_cyclogram_tp[CYCLOGRAM_LOC] = QKeySequence(Qt::CTRL + Qt::Key_L);

    map_key_cyclogram_ai[CYCLOGRAM_STATE_ON] = QKeySequence();
    map_key_cyclogram_ai[CYCLOGRAM_TEST_ADRESS] = QKeySequence();
    map_key_cyclogram_ai[CYCLOGRAM_TEST_MKO] = QKeySequence();
    map_key_cyclogram_ai[CYCLOGRAM_1S_MARK] = QKeySequence();
    map_key_cyclogram_ai[CYCLOGRAM_OPERATION] = QKeySequence();
    map_key_cyclogram_ai[CYCLOGRAM_SYNCHRO] = QKeySequence();
    map_key_cyclogram_ai[CYCLOGRAM_STATE_OFF] = QKeySequence();

    map_key_cyclogram_ri[CYCLOGRAM_TECH_RUN] = QKeySequence();
    map_key_cyclogram_ri[CYCLOGRAM_ZKR] = QKeySequence();
    map_key_cyclogram_ri[CYCL_FULL_FRAMES] = QKeySequence();
}
