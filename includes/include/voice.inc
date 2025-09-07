// всем общий от ивана фейна

// OnIncomingPakcet
if(style == 3)
{
	new BitStream:BitVoice = BS_New();
	new bits;

	BS_WriteValue(BitVoice,
		PR_UINT8, 215,
		PR_UINT16, 3,
		PR_UINT32, playerid);

	BS_SetReadOffset(bs, 24);
	BS_GetNumberOfBytesUsed(bs, bits);
	
	BS_WriteValue(BitVoice, PR_UINT32, bits - 3);

	for(new i, x; i < bits - 3; i++)
	{
		BS_ReadUint8(bs, x);
		BS_WriteValue(BitVoice, PR_UINT8, x);
	}
	PR_SendPacketToPlayerStream(BitVoice, playerid);

	BS_Delete(BitVoice);
}

// OnPlayerTimer
if(IsPlayerLogged(playerid))
{
	foreach(new i : Player)
	{
		if(i == playerid) continue;

		AddPlayerToVoiceStream(playerid, i);
	}
}

AddPlayerToVoiceStream(playerid, targetID) // Записываем дистанцию игроков.
{    
	new Float: dist = GetDistanceBetweenPlayers(playerid, targetID);

	if(dist < 25.0)
	{
		new BitStream:bs = BS_New();

		BS_WriteValue(bs,
			PR_UINT8, 215,
			PR_UINT16, 4,
			PR_UINT32, targetID,
			PR_FLOAT, dist
		);

		PR_SendPacket(bs, playerid);
		BS_Delete(bs);
	}
}