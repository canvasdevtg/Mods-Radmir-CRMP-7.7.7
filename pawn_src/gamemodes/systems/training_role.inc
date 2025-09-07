#if defined _training_role_included
    #endinput
#endif
#define _training_role_included

public: SDSY_OnPlayerAccept(playerid, event)
{
    switch(event)
    {
        case 0:
        {
            SetPlayerInterior(playerid, 0);
	        SetPlayerVirtualWorld(playerid, 0);
	        SetCameraBehindPlayer(playerid);
            CEF_HIDE(playerid, "TrainingRole");
            CEF_CREATE(playerid, 2, 4, "Overlay", "[1000, 2500]");
            IntfDialogCallRemote(playerid, -1, DIALOG_STYLE_MSGBOX,"{"#cW"}Подсказка","{"#cW"}Неподалеку от Вас находится {ff9980}квестовый персонаж\n{"#cW"}у которого Вы можете получить специальные\n{"#cW"}{ff9980}обучающие задания{FFFFFF}.\n\n{"#cW"}Квесты не только познакомят Вас с сервером но и\n{"#cW"}наделят игровыми ценностями, для старта.","Понял", "");
        }
        case 1:
        {
            /*SetPVarInt(playerid, "TrainingRole", 1);
            StartTrainingRole(playerid);
            CEF_HIDE(playerid, "TrainingRole");*/
        }
    }
    return 1;
}
