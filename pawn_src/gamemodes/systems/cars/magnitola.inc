#if defined _magnitola_included
    #endinput
#endif
#define _magnitola_included

enum E_SAB_STRUCT
{
    E_NAME[64],
    bool:E_MUSIC_START,
    E_VOLUME
}
new g_subwoofer[MAX_VEHICLES][E_SAB_STRUCT];

public: MUSIC_OnClientSendData(playerid, types, name[], idx, volume)
{
	new vehicleid = GetPlayerVehicleID(playerid);

	if(vehicleid != -1)
	{
		if(GetPlayerOwnableCarLast(playerid) != vehicleid) return SendClientMessage(playerid, 0xFF6600FF, "¬ы должны находитьс€ в личном транспорте");

		new index = GetVehicleData(vehicleid, V_ACTION_ID);

		new Float: x, Float: y, Float: z;
		GetVehiclePos(vehicleid, x, y, z);

		new Float: x_1, Float: y_1, Float: z_1;
		GetPlayerPos(playerid, x, y, z);

		if(idx == -1 && volume > 9)
		{
			new query[148];
			format(query, sizeof query, "interface('MusicPlayer').srv_onReceiveData(0.%d0000, 2)", volume);
			CEF_CREATE(playerid, 1, 2, query);

			format(query, sizeof query, "interface('Music').srv_onReceiveData(%d,2)", volume);
			CEF_CREATE(playerid, 1, 2, query);

			SetOwnableCarData(index, OC_MUSIC_VOLUME, volume);
		}
		else if(idx == 0)
		{
			CEF_HIDE(playerid, "MusicPlayer");
			
			new query[148];
			format(query, sizeof query, "interface('Music').srv_onReceiveData([[],[],%d,false,0,%d],0)", gettime(), GetOwnableCarData(index, OC_MUSIC_VOLUME));
			CEF_CREATE(playerid, 1, 2, query);

			SetOwnableCarData(index, OC_MUSIC_STATUS, 0);
		}
		else if(idx != -1)
		{
			format(g_ownable_car[index][OC_MUSIC_NAME], 148, "%s", name);

			SetOwnableCarData(index, OC_MUSIC_STATUS, 1);

			SetOwnableCarData(index, OC_MUSIC_TIME, gettime());

			new query[256];
			format(query, sizeof query, "[\"https://music.radmir.online/audio/%s.mp3\",%d,230,[%f,%f,%f],500000.000000,0.%d0000,[%f,%f,%f]]", name, GetOwnableCarData(index, OC_MUSIC_TIME), x, y, z, GetOwnableCarData(index, OC_MUSIC_VOLUME), x_1, y_1, z_1);

			foreach(new i: Player)
			{
				if(!IsPlayerConnected(i)) continue;
				else if(!IsPlayerLogged(i)) continue;
		
				if(!IsPlayerInAnyVehicle(i)) continue;
				if(GetPlayerVehicleID(i) != vehicleid) continue;

				CEF_HIDE(i, "MusicPlayer");
				CEF_CREATE(i, 2, 4, "MusicPlayer", query);
			}

			format(query, sizeof query, "interface('Music').srv_onReceiveData([[[\"%s\", 230]],[],%d,false,0,%d],0)",name, GetOwnableCarData(index, OC_MUSIC_TIME), GetOwnableCarData(index, OC_MUSIC_VOLUME));
			CEF_CREATE(playerid, 1, 2, query);
		}
	}
	return 1;
}

stock Music_Start(playerid,type,name[],index,volume)
{
    #pragma unused index
    new vehicleid = GetPlayerVehicleID(playerid);

	new carindex = GetVehicleData(vehicleid, V_ACTION_ID);

    switch(type)
    {
        case 0:
        {
            format(STRING_GLOBAL, sizeof STRING_GLOBAL, "interface('Music').srv_onReceiveData([[[\"%s\",173]],[],0,0,0,%d],0)", name,g_subwoofer[vehicleid][E_VOLUME]);
            CEF_CREATE(playerid, 1, 2, STRING_GLOBAL);

            format(g_subwoofer[carindex][E_NAME],64, "%s",name);
            string_replace(name," ","%20",_,true);
            new Float:x,Float:y,Float:z;
            g_subwoofer[vehicleid][E_MUSIC_START] = true;

            SetOwnableCarData(carindex, OC_MUSIC_STATUS, 1);

            SetOwnableCarData(carindex, OC_MUSIC_TIME, gettime());

            GetVehiclePos(vehicleid,x,y,z);
            foreach(new i:Player)
            {
                format(STRING_GLOBAL, sizeof STRING_GLOBAL, "window.createSound3D(%d, 'https://music.radmir.online/audio/%s.mp3', %.2f, %.2f, %.2f, 0.50, 7.00, 35.00, true, false) || window.setSound3DPosition(10009, 0.000000) || window.attachSoundToVehicle(%d, %d, 0.00, 0.00, 0.00, 0.00)", vehicleid,name,x,y,z,vehicleid,vehicleid);
                CEF_CREATE(i, 1, 2, STRING_GLOBAL);
            }
        }
        case 1:
        {
            g_subwoofer[vehicleid][E_MUSIC_START] = false;

            CEF_CREATE(playerid, 1, 2, "interface('Music').srv_onReceiveData([[],[],0,0,0,50],0)");
            
            format(STRING_GLOBAL, sizeof STRING_GLOBAL, "window.destroySound(%d,35)", vehicleid);
            CEF_CREATE(playerid, 1, 2, STRING_GLOBAL);
            SetOwnableCarData(carindex, OC_MUSIC_STATUS, 0);
        }
        case 7:
        {
            g_subwoofer[vehicleid][E_VOLUME] = volume;
            format(STRING_GLOBAL, sizeof STRING_GLOBAL, "interface('Music').srv_onReceiveData(%d,2)", volume);
            CEF_CREATE(playerid, 1, 2, STRING_GLOBAL);

            format(STRING_GLOBAL, sizeof STRING_GLOBAL, "window.soundSlideAttribute(%d, 2, %.2f, 200)", vehicleid, float(volume)/100);
            CEF_CREATE(playerid, 1, 2, STRING_GLOBAL);
        }
    }
}
string_replace(inputvar[], const searchstring[], const replacestring[],
                bool:ignorecase=true, bool:replaceall=false)
{
    if (strfind(replacestring, searchstring, ignorecase) != -1)
        return -1;
    new pos = strfind(inputvar, searchstring, ignorecase);
    if (pos == -1)
        return 0;
    if (replaceall == true)
    {
        while (strfind(inputvar, searchstring, ignorecase) != -1)
        {
            pos = strfind(inputvar, searchstring, ignorecase);
            strdel(inputvar, pos, pos + strlen(searchstring));
            strins(inputvar, replacestring, pos, strlen(inputvar));
        }
    }
    else
    {
        strdel(inputvar, pos, pos + strlen(searchstring));
        strins(inputvar, replacestring, pos, strlen(inputvar));
    }
    return 1;
}