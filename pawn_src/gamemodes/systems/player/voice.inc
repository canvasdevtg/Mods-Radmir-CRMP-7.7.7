static IteratorArray:g_player_zone[MAX_PLAYERS]<MAX_PLAYERS>;

#if !defined str_f
    #define str_f(%0,%1) string_format[0]=EOS,\
        format(string_format, sizeof string_format, %0, %1), string_format
#endif

public: Voice_OnPlayerConnect(playerid)
{
    Iter_Clear(g_player_zone[playerid]);
    Iter_Add(g_player_zone[playerid], playerid);
    return 1;
}

public: Voice_OnPlayerStreamOut(playerid, forplayerid)
{
    new BitStream:bs = BS_New();

    BS_WriteValue(bs, PR_UINT8, PACKET);
    BS_WriteValue(bs, PR_UINT16, 5);
	BS_WriteValue(bs, PR_UINT32, forplayerid);

    PR_SendPacket(bs, playerid);
    BS_Delete(bs);

    Iter_Remove(g_player_zone[playerid], forplayerid);

    return 1;
}

public: Voice_OnPlayerStreamIn(playerid, forplayerid)
{
    new BitStream:bs = BS_New();

    BS_WriteValue(bs, PR_UINT8, PACKET);
    BS_WriteValue(bs, PR_UINT16, 4);
	BS_WriteValue(bs, PR_UINT32, forplayerid);
    BS_WriteValue(bs, PR_FLOAT, 6.0);
    BS_WriteValue(bs, PR_BOOL, true);
    BS_WriteValue(bs, PR_UINT8, 2);
    BS_WriteValue(bs, PR_UINT32, forplayerid);

    PR_SendPacket(bs, playerid);
    BS_Delete(bs);

    Iter_Add(g_player_zone[playerid], forplayerid);

    return 1;
}

stock Float: GetDistanceBetweenPlayers(p1,p2)
{
    if(!IsPlayerConnected(p1) || !IsPlayerConnected(p2)) return -1.00;
	new Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2;
	GetPlayerPos(p1,x1,y1,z1), GetPlayerPos(p2,x2,y2,z2);
	return floatsqroot(floatpower(floatabs(floatsub(x2,x1)),2)+floatpower(floatabs(floatsub(y2,y1)),2)+floatpower(floatabs(floatsub(z2,z1)),2));
}

stock PlayerSetting_OnVoiceChange(playerid, volume)
{
    new BitStream:bs = BS_New();

    BS_WriteValue(bs, PR_UINT8, PACKET);
    BS_WriteValue(bs, PR_UINT16, 6);
	BS_WriteValue(bs, PR_UINT32, volume);

    PR_SendPacket(bs, playerid);
    BS_Delete(bs);

    return 1;
}

stock SendPacket_VoiceEnable(playerid, BitStream:bs)
{
    if(GetPlayerData(playerid, P_MUTE) > 0)
    {
        return false;
    }

    new BitStream: VoiceBitStreams = BS_New(), bits;

    BS_WriteValue
    (
        VoiceBitStreams,
        PR_UINT8, 215,
        PR_UINT16, 3,
        PR_UINT32, playerid
    );

    BS_SetReadOffset(bs, 24);
    BS_GetNumberOfBytesUsed(bs, bits);
    BS_WriteValue(VoiceBitStreams, PR_UINT32, bits - 3);
    
    for(new i, uint8; i < bits - 3; i++)
    {
        BS_ReadUint8(bs, uint8);
        BS_WriteValue(VoiceBitStreams, PR_UINT8, uint8);
    }

	foreach(new forplayerid : g_player_zone[playerid])
    {
        if(playerid == forplayerid) continue;

        if(GetDistanceBetweenPlayers(playerid, forplayerid) < 12)
        {
            PR_SendPacket(VoiceBitStreams, forplayerid);
        }
    }
    
    BS_Delete(VoiceBitStreams);
    return true;
}

public: OnVoiceChatStartRecord(playerid)
{
    foreach(new forplayerid : g_player_zone[playerid])
    {
        if(GetDistanceBetweenPlayers(playerid, forplayerid) < 12)
        {
            format(string_dialog, sizeof(string_dialog), "interface('Hud').addVoiceChatEntry([0,\"%s\",%i,0,\"\",%i])", GetPlayerNameEx(playerid), playerid, playerid);
            CEF_CREATE(forplayerid, 1, 2, string_dialog);
        }
    }
}

public: OnVoiceChatEndRecord(playerid)
{
    foreach(new forplayerid : g_player_zone[playerid])
    {
        if(GetDistanceBetweenPlayers(playerid, forplayerid) < 12)
        {
            format(string_dialog, sizeof(string_dialog), "interface('Hud').removeVoiceChatEntry([[%i,%i]])", playerid, playerid);
            CEF_CREATE(forplayerid, 1, 2, string_dialog);
        }
    }
}
