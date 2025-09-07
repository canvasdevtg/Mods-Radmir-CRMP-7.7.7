#if defined _register_included
    #endinput
#endif
#define _register_included

new RegActor[MAX_PLAYERS][5];
new PlayerRegActor[MAX_PLAYERS];

forward CreateRegActor(playerid);
public CreateRegActor(playerid)
{
    PlayerRegActor[playerid] = CreateActor(78, 237.75, 2772.30, 13.39, 332.51);
    SetActorVirtualWorld(PlayerRegActor[playerid], 1 + playerid);
    ApplyActorAnimation(PlayerRegActor[playerid], "COP_AMBIENT", "COPLOOK_NOD", 4.10, false, false, false, true, 0);
    ApplyActorAnimation(PlayerRegActor[playerid], "COP_AMBIENT", "COPLOOK_NOD", 4.10, false, false, false, true, 0);

    RegActor[playerid][0] = CreateActor(63, 230.22, 2767.80, 12.98, 357.81);
    SetActorVirtualWorld(RegActor[playerid][0], 1 + playerid);
    ApplyActorAnimation(RegActor[playerid][0], "ON_LOOKERS", "wave_loop", 4.00, true, false, false, false, 0);
    ApplyActorAnimation(RegActor[playerid][0], "ON_LOOKERS", "wave_loop", 4.00, true, false, false, false, 0);

    RegActor[playerid][1] = CreateActor(59, 232.46, 2769.06, 12.98, 356.56);
    SetActorVirtualWorld(RegActor[playerid][1], 1 + playerid);
    ApplyActorAnimation(RegActor[playerid][1], "PLAYIDLES", "SHIFT", 4.10, true, false, false, false, 0);
    ApplyActorAnimation(RegActor[playerid][1], "PLAYIDLES", "SHIFT", 4.10, true, false, false, false, 0);

    RegActor[playerid][2] = CreateActor(44, 234.17, 2771.74, 13.39, 269.27);
    SetActorVirtualWorld(RegActor[playerid][2], 1 + playerid);
    ApplyActorAnimation(RegActor[playerid][2], "MISC", "SEAT_LR", 4.00, false, false, false, true, 0);
    ApplyActorAnimation(RegActor[playerid][2], "MISC", "SEAT_LR", 4.00, false, false, false, true, 0);

    RegActor[playerid][3] = CreateActor(21, 234.21, 2772.48, 13.39, 86.64);
    SetActorVirtualWorld(RegActor[playerid][3], 1 + playerid);
    ApplyActorAnimation(RegActor[playerid][3], "MISC", "SEAT_LR", 4.00, false, false, false, true, 0);
    ApplyActorAnimation(RegActor[playerid][3], "MISC", "SEAT_LR", 4.00, false, false, false, true, 0);

    RegActor[playerid][4] = CreateActor(8, 235.94, 2771.74, 13.39, 268.39);
    SetActorVirtualWorld(RegActor[playerid][4], 1 + playerid);
    ApplyActorAnimation(RegActor[playerid][4], "MISC", "SEAT_LR", 4.00, true, false, false, false, 0);
    ApplyActorAnimation(RegActor[playerid][4], "MISC", "SEAT_LR", 4.00, true, false, false, false, 0);

    return 1;
}

stock DestroyRegActor(playerid)
{
    for(new i = 0; i < 5; i++)
    {
        if(IsValidActor(RegActor[playerid][i]))
        {
            DestroyActor(RegActor[playerid][i]);
            RegActor[playerid][i] = INVALID_ACTOR_ID;
        }
    }

    if(IsValidActor(PlayerRegActor[playerid]))
    {
        DestroyActor(PlayerRegActor[playerid]);
        PlayerRegActor[playerid] = INVALID_ACTOR_ID;
    }

    return 1;
}

new Float:xCoords[] = {226.00, 229.00, 231.00};
new Float:yCoords[] = {2773.23, 2773.23, 2773.23};
new Float:zCoords[] = {13.40, 13.40, 13.40};
new Float:speeds[] = {1.20, 0.80, 0.40};

new ObjectTrain[MAX_PLAYERS] = {INVALID_OBJECT_ID, ...};
new ObjectCamera[MAX_PLAYERS] = {INVALID_OBJECT_ID, ...};
new currentStep[MAX_PLAYERS];
new currentStepCamera[MAX_PLAYERS];

public: MoveToNextPoint(playerid)
{
    if(currentStep[playerid] >= sizeof(xCoords)) return 1;

    MoveObject(ObjectTrain[playerid],
        xCoords[currentStep[playerid]],
        yCoords[currentStep[playerid]],
        zCoords[currentStep[playerid]],
        speeds[currentStep[playerid]],
        0.00, 0.00, -90.00
    );

    if(currentStep[playerid] == 0)
    {
        currentStep[playerid]++;
        SetTimerEx("MoveToNextPoint", 1000, false, "i", playerid);
        return 1;
    }

    new Float:dx = xCoords[currentStep[playerid]] - xCoords[currentStep[playerid] - 1];
    new Float:dy = yCoords[currentStep[playerid]] - yCoords[currentStep[playerid] - 1];
    new Float:dz = zCoords[currentStep[playerid]] - zCoords[currentStep[playerid] - 1];

    new Float:dist = floatsqroot(dx*dx + dy*dy + dz*dz);
    new time = floatround(dist / speeds[currentStep[playerid]] * 1000.0, floatround_round);

    currentStep[playerid]++;
    SetTimerEx("MoveToNextPoint", time, false, "i", playerid);
    return 1;
}

new Float:x_camera_Coords[] = {225.80, 228.80, 230.80};
new Float:y_camera_Coords[] = {2774.13, 2774.13, 2774.13};
new Float:z_camera_Coords[] = {13.90, 13.90, 13.90};
new Float:camera_speeds[] = {1.20, 0.80, 0.40};

public: MoveCameraToNextPoint(playerid)
{
    if(currentStepCamera[playerid] >= sizeof(x_camera_Coords))
    {
        DestroyObject(ObjectCamera[playerid]);

        SetTimerEx("CreateRegActor", 50, false, "i", playerid);

        InterpolateCameraPos(playerid, 230.80, 2774.13, 13.90, 238.80, 2774.13, 13.90, 3000);
        InterpolateCameraLookAt(playerid, 230.80, 2772.33, 13.90, 238.20, 2772.33, 13.90, 3000);
        return 1;
    } 

    MoveObject(ObjectCamera[playerid],
        x_camera_Coords[currentStepCamera[playerid]],
        y_camera_Coords[currentStepCamera[playerid]],
        z_camera_Coords[currentStepCamera[playerid]],
        camera_speeds[currentStepCamera[playerid]],
        0.00, 0.00, -90.00
    );

    if(currentStepCamera[playerid] == 0)
    {
        currentStepCamera[playerid]++;
        SetTimerEx("MoveCameraToNextPoint", 1000, false, "i", playerid);
        return 1;
    }

    new Float:dx = x_camera_Coords[currentStepCamera[playerid]] - x_camera_Coords[currentStepCamera[playerid] - 1];
    new Float:dy = y_camera_Coords[currentStepCamera[playerid]] - y_camera_Coords[currentStepCamera[playerid] - 1];
    new Float:dz = z_camera_Coords[currentStepCamera[playerid]] - z_camera_Coords[currentStepCamera[playerid] - 1];

    new Float:dist = floatsqroot(dx*dx + dy*dy + dz*dz);
    new time = floatround(dist / camera_speeds[currentStepCamera[playerid]] * 1000.0, floatround_round);

    currentStepCamera[playerid]++;
    SetTimerEx("MoveCameraToNextPoint", time, false, "i", playerid);
    return 1;
}

stock ShowPlayerReg(playerid)
{
	SetPVarInt(playerid, "Login_1", 1);
	g_player_account_state[playerid] = 2;

    SetSpawnInfo(playerid, 0, 0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
    TogglePlayerSpectating(playerid, true);
    SetPlayerPos(playerid, 231.00, 2773.23, 23.40);

	SetPlayerVirtualWorld(playerid, 1 + playerid);

    ObjectTrain[playerid] = CreateObject(10926, 226.00, 2773.23, 13.40, 0.00, 0.00, -90.00);
    ObjectCamera[playerid] = CreateObject(10887, 225.80, 2774.13, 13.90, 0.00, 0.00, -90.00);

    SetPlayerCameraPos(playerid, 225.22, 2771.04, 17.98);
	SetPlayerCameraLookAt(playerid, 225.22, 2766.54, 17.98, CAMERA_CUT);

    SetTimerEx("ShowUIWithDelay", 100, false, "i", playerid);

	CEF_CREATE(playerid, 1, 2, "window.playSound('train/stop.mp3')");
	CEF_CREATE(playerid, 1, 2, "hideInterface('Hud')");

    SetTimerEx("MoveObjectReg", 2500, false, "i", playerid);
    
    new fmt_str[268];
	format(fmt_str, sizeof fmt_str, "[\"register\", [78,135,137,212,160,230,15327,15353,15354,15355,15524,15525], %d, %d, %d, %d, %d]", SERVER, g_xbonus, SERVER_HUD_HELLOWEEN, SERVER_HUD_NEW_YEAR, SERVER_HUD_EASTER);
	CEF_CREATE(playerid, 2, 4, "Authorization", fmt_str);

	_player_skin[playerid] = 78;
	_player_skin_sex[playerid] = false;

    return 1;
}

public: ShowUIWithDelay(playerid)
{
    CEF_CREATE(playerid, 2, 4, "Overlay", "[1000, 2300]");
    return 1;
}
public: MoveObjectReg(playerid)
{
    currentStep[playerid] = 1;
    currentStepCamera[playerid] = 1;
    MoveToNextPoint(playerid);
    MoveCameraToNextPoint(playerid);
    AttachCameraToObject(playerid, ObjectCamera[playerid]);
    return 1;
}