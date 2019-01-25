
#pragma once

typedef enum {
    NC_MOVE_SCENE = 0,            //シーン移動を送る用
    NC_SEND_NAME = 1,             //名前を送る命令　送る時
    NC_SEND_CONTROLLER_PARAM = 2, //コントローラのパラメータを送る時
    NC_SEND_CHARA_DATA = 3,       //ゲームオブジェクトの情報を送る時
    NC_FINISH = 4,                //終了
    NC_NUMBER = 5,
} NETWORK_COMMAND;