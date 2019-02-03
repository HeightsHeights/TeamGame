
#pragma once

typedef enum {
    NC_MOVE_SCENE = 0,            //シーン移動を送る用
    NC_SEND_NAME = 1,             //名前を送る命令　送る時
    NC_SEND_ID = 2,               //IDを送る
    NC_SEND_CONTROLLER_PARAM = 3, //コントローラのパラメータを送る時
    NC_SEND_SIGNAL = 4,           //SIGNAL
    NC_SEND_CHARA_DATA = 5,       //CHARAの情報を送る時
    NC_SEND_OBJECT_DATA = 6,      //OBJECTの情報を送る時
    NC_SEND_TEAM_STATUS = 7,      //TEAM STATUS
    NC_SEND_EFFECT_DATA = 8,      //EFFECT
    NC_SEND_RESULT_DATA = 9,      //試合結果
    NC_FINISH = 10,               //終了
    NC_NUMBER = 11,
} NETWORK_COMMAND;