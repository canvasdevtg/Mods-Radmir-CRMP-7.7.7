#if defined _cef_data_included
    #endinput
#endif
#define _cef_data_included

#define PACKET 215

stock CEF_CREATE(playerid, type_intf, type, string[], string2[] = "") 
{
    new BitStream:intf = BS_New(); // Обновить интерфейс 2, Показать интерфейс 4, Обновить числовое значение 6

    BS_WriteValue(intf, PR_UINT8, PACKET);
    BS_WriteValue(intf, PR_UINT16, 2);
	BS_WriteValue(intf, PR_UINT32, type);

	BS_WriteValue(intf, PR_UINT8, type_intf);

	if(type_intf == 1){
		BS_WriteValue(intf, PR_UINT32, strlen(string), PR_STRING, string, strlen(string));
	}
	else if(type_intf == 2){
        BS_WriteValue(intf, PR_UINT32, strlen(string), PR_STRING, string, strlen(string));
		BS_WriteValue(intf, PR_UINT32, strlen(string2), PR_STRING, string2, strlen(string2));
	}

    PR_SendPacket(intf, playerid);
    BS_Delete(intf);
	return SUCCESS;
}

stock CEF_HIDE(playerid, string[])
{
	new BitStream:intf = BS_New();

    BS_WriteValue(intf, PR_UINT8, PACKET);
    BS_WriteValue(intf, PR_UINT16, 2);
	BS_WriteValue(intf, PR_UINT32, 5);
	BS_WriteValue(intf, PR_UINT8, 1);
	BS_WriteValue(intf, PR_UINT32, strlen(string), PR_STRING, string, strlen(string));
    PR_SendPacket(intf, playerid);
    BS_Delete(intf);
	return SUCCESS;
}

stock PACKET_215(playerid, type_packet, arg1=0, arg2=0, arg3[]="", arg4[]="", arg5=0, arg6=0, arg7=0, arg8=0)
{
    new BitStream:bs = BS_New();

    if(type_packet != 29) BS_WriteValue(bs, PR_UINT8, PACKET, PR_UINT16, type_packet, PR_UINT32, arg1);
    else BS_WriteValue(bs, PR_UINT8, PACKET, PR_UINT16, type_packet, PR_UINT32, playerid);
    
    if(type_packet == 29){
        BS_WriteValue(bs, PR_UINT32, arg1);
    }
    else if(type_packet == 32){
        BS_WriteValue(bs, PR_UINT32, 0, PR_UINT16, 256, PR_UINT32, arg2);
        BS_WriteValue(bs, PR_UINT32, strlen(arg3), PR_STRING, arg3, strlen(arg3));
	    BS_WriteValue(bs, PR_UINT32, strlen(arg4), PR_STRING, arg4, strlen(arg4));
    }
    else if(type_packet == 12){
        BS_WriteValue(bs, PR_UINT32, arg2, PR_UINT8, arg5, PR_UINT8, arg6, PR_UINT8, arg7, PR_UINT8, arg8);
    }
    else if(type_packet == 15){
        BS_WriteValue(bs, PR_UINT8, arg2, PR_UINT8, arg5);
    }
    else if(type_packet == 17){
        BS_WriteValue(bs, PR_UINT32, arg2, PR_UINT32, arg5);
    }

    if(type_packet != 29) PR_SendPacket(bs, playerid);
    else PR_SendPacketToPlayerStream(bs, playerid);

    BS_Delete(bs);
    return SUCCESS;
}