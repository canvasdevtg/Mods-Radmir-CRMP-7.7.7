#if defined _police_tablet_included
    #endinput
#endif
#define _police_tablet_included

#define PoliceTablet: PoliceTablet_

new const e_suspect[][35] =
{
	"Неподчинение",
	"Отказ предоставления паспорта",
	"Оскорбление МВД",
	"Вооруженное нападение на МВД",
	"Вооруженное нападение на человека",
	"Убийство гражданина",
	"Убийство сотрудника МВД",
	"Попытка угона гос. или частного ТС",
	"Угон ТС"
};
new tempplayersuspect[MAX_PLAYERS];

stock PoliceTablet:OnPlayerPage(playerid, page)
{
	switch(page)
	{
	    case 3://штрафы
	    {
			mysql_tquery(mysql,"SELECT * FROM tickets","ShowTabletFines","i",playerid);
	    }
	    case 5://ф.розыск
		{
		    mysql_tquery(mysql,"SELECT * FROM accounts WHERE suspect > 0","ShowTabletSuspect","i",playerid);
		}
		case 6://р.розыск
		{
            mysql_tquery(mysql,"SELECT * FROM accounts WHERE suspect > 0","ShowTabletNearSuspect","i",playerid);
		}
		case 7: //архив
		{
		    mysql_tquery(mysql,"SELECT * FROM police_tablet WHERE event=11","ShowTabletArchive","i",playerid);
		}
		case 8://Карта
		{

		}
		case 9://подмога
		{
		    mysql_tquery(mysql,"SELECT * FROM police_tablet WHERE event=9","ShowTabletHelp","i",playerid);
		}
	}

}
stock PoliceTablet:IssueFine(playerid, sum[], name[], reason[])
{
    if(strfind(name,"|") != -1 || strfind(name,"&") != -1 || strfind(name,"#") != -1 || strfind(name,"@") != -1 || strfind(name,"%") != -1) return 1;
    if(strfind(reason,"|") != -1 || strfind(reason,"&") != -1 || strfind(reason,"#") != -1 || strfind(reason,"@") != -1 || strfind(reason,"%") != -1) return 1;
   	new to_player = -1;
	foreach(new i : Player)
	{
		if(!IsPlayerLogged(i)) continue;
        if(!IsPlayerConnected(i)) continue;
		if(strfind(GetPlayerNameEx(i), name, true) != -1) to_player = i;
	}
	if(to_player != -1)
	{
	    if(!IsPlayerInRangeOfPlayer(playerid, to_player, 6.0)) return SendClientMessage(playerid, 0x999999FF, "Игрок находится слишком далеко");
		if(to_player == playerid) return SendClientMessage(playerid, 0x999999FF, "Вы не можете выдать штраф сам себе");
		
		SCMF(to_player, 0x3399FFFF, "%s[%d] выписал Вам штраф в размере %s руб. Причина: %s", GetPlayerNameEx(playerid), playerid, sum, reason);

		SCMF(playerid, 0x3399FFFF, "Вы выписали %s штраф в размере %s руб. Причина: %s", name, sum, reason);

        new query[190];

	    mysql_format(mysql, query, sizeof query, "INSERT INTO tickets (uid, amount, issuer, description, time) VALUES (%d, %d, 'МВД', '%s', %d)",
	    GetPlayerAccountID(to_player), strval(sum), reason, gettime());
	    mysql_query(mysql, query, false);
	}
	return 1;
}

stock PoliceTablet:OnPlayerRequest(playerid, event, toplayer,name[])
{
	mysql_string[0] = EOS;
	switch(event)
	{
		case 3:
		{
			format(mysql_string, sizeof mysql_string,"SELECT * FROM accounts_canvasdev WHERE name='%s'",name);
			mysql_tquery(mysql,mysql_string,"ShowTabletBaseAccounts","i",playerid);
		}
		case 1:
	    {
			format(mysql_string, sizeof mysql_string,"SELECT * FROM police_tablet WHERE name='%s' AND event=11",name);
			mysql_tquery(mysql,mysql_string,"ShowTabletArchiveAccounts","i",playerid);
	    }
	    case 5:
	    {
			format(mysql_string, sizeof mysql_string,"SELECT * FROM accounts_canvasdev WHERE name='%s'",name);
			mysql_tquery(mysql,mysql_string,"ShowTabletSuspectAccounts","is",playerid,name);
	    }
		case 7:
		{
			str_2[0] = EOS;

		    for(new i; i < sizeof(e_suspect); i++)
		    {
		        format(str_2,sizeof str_2,"%s%d. %s\n",str_2,i+1,e_suspect[i]);
		    }

		    tempplayersuspect[playerid] = GetPlayerIDBySqlID(toplayer);

            if(tempplayersuspect[playerid] == playerid) return SCM(playerid,-1,"Вы не можете выдать розыск самому себе");

		    IntfDialogCallRemote(playerid,DIALOG_SUSPECT,DIALOG_STYLE_LIST,"Причина выдачи розыска",str_2,"Готово","Назад");
		}
	}
	return true;
}
stock PoliceTablet:OnPlayerRespond(playerid, toplayer)
{
    new to_player = GetPlayerIDBySqlID(toplayer);
	if(!IsPlayerConnected(playerid)) return SCM(playerid,-1,"Игрок не онлайн");

	mysql_string[0] = EOS;
	format(mysql_string,sizeof mysql_string,"SELECT * FROM police_tablet WHERE event = 9 AND ownerid=%d",toplayer);
	mysql_tquery(mysql,mysql_string,"RequestHelp","ii",playerid,to_player);

	return true;
}
public: ShowTabletArchive(playerid)
{
    new rows = cache_num_rows();
	if(rows)
	{
	    str_2[0] = EOS;

		strcat(str_2, "interface('Police').setArchive('[");

	    new name[MAX_PLAYER_NAME],time,skin,suspect,reason[35],type,cuffname[MAX_PLAYER_NAME];

	    for(new i; i < rows; i++)
	    {
			time = cache_get_field_content_int(i, "time");
			skin = cache_get_field_content_int(i, "skin");
			suspect = cache_get_field_content_int(i, "suspect");
			type = cache_get_field_content_int(i, "type");
	        cache_get_field_content(i, "name", name);
	        cache_get_field_content(i, "cuffname", cuffname);
	        cache_get_field_content(i, "reason", reason);
	        format(str_2, sizeof str_2, "%s[\"%s\", %d, %d, %d, 1, \"%s\", %d, \"%s\"],",str_2, name, skin, suspect,time,reason,type, cuffname);
	    }
        strdel(str_2, strlen(str_2) - 1, strlen(str_2));
        strcat(str_2, "]')");

        CEF_CREATE(playerid, 1, 2, str_2);
	}
}
public: ShowTabletSuspect(playerid)
{
    new rows = cache_num_rows();
	if(rows)
	{
	    str_2[0] = EOS;
		strcat(str_2, "interface('Police').updateWantedList('[");
	    new name[MAX_PLAYER_NAME],skin,ownerid,suspect;
	    for(new i; i < rows; i++)
	    {
	        ownerid = cache_get_field_content_int(i, "id");
			skin = cache_get_field_content_int(i, "skin");
			suspect = cache_get_field_content_int(i, "suspect");
	        cache_get_field_content(i, "name", name);
	        format(str_2, sizeof str_2, "%s[\"%s\", %d, %d, %d],",str_2, name, ownerid, skin,suspect);
	    }
        strdel(str_2, strlen(str_2) - 1, strlen(str_2));
        strcat(str_2, "]')");

        CEF_CREATE(playerid, 1, 2, str_2);
	}
}
public: ShowTabletNearSuspect(playerid)
{
    new rows = cache_num_rows();
	if(rows)
	{
	    str_2[0] = EOS;
		strcat(str_2, "interface('Police').updateWantedNearList('[");

	    new name[MAX_PLAYER_NAME],skin,ownerid,suspect;
	    for(new i; i < rows; i++)
	    {
	        ownerid = cache_get_field_content_int(i, "id");
			skin = cache_get_field_content_int(i, "skin");
			suspect = cache_get_field_content_int(i, "suspect");
	        cache_get_field_content(i, "name", name);
	        format(str_2, sizeof str_2, "%s[\"%s\", %d, %d, %d],",str_2, name, ownerid, skin,suspect);
	    }
        strdel(str_2, strlen(str_2) - 1, strlen(str_2));
		strcat(str_2, "]')");

        CEF_CREATE(playerid, 1, 2, str_2);
	}
}
public: ShowTabletFines(playerid)
{
	new rows = cache_num_rows();
	if(rows)
	{
	    str_2[0] = EOS;
		strcat(str_2, "interface('Police').updateFinesList('[");

	    new amount,ownerid,name[MAX_PLAYER_NAME],rule[64],issuer[MAX_PLAYER_NAME],status,time;
	    for(new i; i < rows; i++)
	    {
	        ownerid = cache_get_field_content_int(i, "uid");
	        amount = cache_get_field_content_int(i, "amount");
	        status = cache_get_field_content_int(i, "status");
	        time = cache_get_field_content_int(i, "time");
	        cache_get_field_content(i, "name", name);
	        cache_get_field_content(i, "description", rule);
	        cache_get_field_content(i, "issuer", issuer);

	        format(str_2,sizeof str_2,"%s[%d, \"%s\",\"%s\", %d, %d, %d,\"%s\"],",
			str_2,ownerid,name,rule,status,amount,time,issuer);
	    }
	    strdel(str_2, strlen(str_2) - 1, strlen(str_2));
		strcat(str_2, "]')");
	    CEF_CREATE(playerid, 1, 2, str_2);
	}
}
public: ShowTabletHelp(playerid)
{
    new rows = cache_num_rows();
	if(rows)
	{
	    str_2[0] = EOS;
		strcat(str_2, "interface('Police').updateHelpsList('[");

	    new name[MAX_PLAYER_NAME],time,place[24],ownerid;
	    for(new i; i < rows; i++)
	    {
	        ownerid = cache_get_field_content_int(i, "ownerid");
			time = cache_get_field_content_int(i, "time");
	        cache_get_field_content(i, "name", name);
	        cache_get_field_content(i, "place", place);
	        format(str_2, sizeof str_2, "%s[\"%s\", \"%s\", %d, %d],",str_2,name, place,time, ownerid);
	    }
        strdel(str_2, strlen(str_2) - 1, strlen(str_2));
		strcat(str_2, "]')");

        CEF_CREATE(playerid, 1, 2, str_2);
	}
	else CEF_CREATE(playerid, 1, 2, "interface('Police').updateHelpsList('[]')");
}
public: ShowTabletBaseAccounts(playerid)
{
	new rows = cache_num_rows();
	if(rows)
	{
	    new id = cache_get_field_content_int(0, "id");
	    new age = cache_get_field_content_int(0, "level");
	    new sex = cache_get_field_content_int(0, "sex");
	    new skin = cache_get_field_content_int(0, "skin");
	    new suspect = cache_get_field_content_int(0, "suspect");
	    new crimes = cache_get_field_content_int(0, "crimes");
	    new name[MAX_PLAYER_NAME];
	    cache_get_field_content(0, "name",name,mysql,MAX_PLAYER_NAME);
	    new fines = GetCountTickets(id);
	   
	    str_2[0] = EOS;
	    format(str_2, sizeof str_2,"interface('Police').setDatabase('[1,\"%s\",2,%d,%d,%d,%d,%d,%d,%d]')",name,suspect,crimes,fines,sex,age,skin,id);
	    CEF_CREATE(playerid, 1, 2, str_2);

		mysql_string[0] = EOS;
  		format(mysql_string,sizeof mysql_string,"SELECT * FROM ownable_cars WHERE owner_id=%d",id);
  		mysql_tquery(mysql, mysql_string,"SetTabletDataProp","i",playerid);

	}
}
public: ShowTabletArchiveAccounts(playerid)
{
    new rows = cache_num_rows();
	if(rows)
	{
	    str_2[0] = EOS;
		strcat(str_2, "interface('Police').setArchive('[");

	    new name[MAX_PLAYER_NAME],time,skin,suspect,reason[35],type,cuffname[MAX_PLAYER_NAME];
	    
		for(new i; i < rows; i++)
	    {
			time = cache_get_field_content_int(i, "time");
			skin = cache_get_field_content_int(i, "skin");
			suspect = cache_get_field_content_int(i, "suspect");
			type = cache_get_field_content_int(i, "type");
	        cache_get_field_content(i, "name", name);
	        cache_get_field_content(i, "cuffname", cuffname);
	        cache_get_field_content(i, "reason", reason);
	        format(str_2, sizeof str_2, "%s[\"%s\", %d, %d, %d, 1, \"%s\", %d, \"%s\"],",str_2, name, skin, suspect,time,reason,type, cuffname);
	    }

        strdel(str_2, strlen(str_2) - 1, strlen(str_2));

		strcat(str_2, "]')");

        CEF_CREATE(playerid, 1, 2, str_2);
	}
}
public: ShowTabletSuspectAccounts(playerid,name[])
{
	new rows = cache_num_rows();
	if(rows)
	{
	    new id = cache_get_field_content_int(0, "id");
	    new age = cache_get_field_content_int(0, "level");
	    new sex = cache_get_field_content_int(0, "sex");
	    new skin = cache_get_field_content_int(0, "skin");
	    new suspect = cache_get_field_content_int(0, "suspect");
	    new crimes = cache_get_field_content_int(0, "crimes");
	    new fines = GetCountTickets(id);

	    str_2[0] = EOS;
	    format(str_2, sizeof str_2,"interface('Police').setModalPlayerData('[1,\"%s\",2,%d,%d,%d,%d,%d,%d,%d]')",name,suspect,crimes,fines,sex,age,skin,id);
	    CEF_CREATE(playerid, 1, 2, str_2);

		mysql_string[0] = EOS;
  		format(mysql_string,sizeof mysql_string,"SELECT * FROM ownable_cars WHERE owner_id=%d",id);
  		mysql_tquery(mysql, mysql_string,"SetTabletDataProp","i",playerid);

	}
}
public: SetTabletDataProp(playerid)
{
	new rows = cache_num_rows();
	if(rows)
	{
	    str_2[0] = EOS;
		strcat(str_2, "interface('Police').setModalProperties('[");
	    new modelid,number[15];
	    for(new i; i < rows; i++)
	    {
			modelid = cache_get_field_content_int(i, "model_id");
			
			cache_get_field_content(i, "number",number);
			
			format(str_2,sizeof str_2,"%s[0,\"%s\", \"%s\"],",str_2,CheckCarNameByID(modelid),number);
	    }
        strdel(str_2, strlen(str_2) - 1, strlen(str_2));
		
		strcat(str_2, "]')");
       
	    CEF_CREATE(playerid, 1, 2, str_2);
	}
}
public: RequestHelp(playerid, to_player)
{
	if(cache_num_rows())
	{
		new Float:x = cache_get_field_content_float(0, "x");
		new Float:y = cache_get_field_content_float(0, "y");
		new Float:z = cache_get_field_content_float(0, "z");
		SCM(playerid, -1, "Координаты отмечены на GPS");
		EnablePlayerGPS(playerid, 37, x, y, z, "");
	}
}
stock PoliceTablet:OnDialogResponse(playerid, dialogid, response, listitem)
{
    switch(dialogid)
 	{
		case DIALOG_SUSPECT:
		{
			if(response)
			{
			    new criminalid = tempplayersuspect[playerid];

                if(GetPlayerSuspect(criminalid) != 6)
				{
                    AddPlayerData(criminalid, P_SUSPECT, +, 1);
					SetPlayerSuspectInit(criminalid);
					UpdatePlayerDatabaseInt(criminalid, "suspect", GetPlayerData(criminalid, P_SUSPECT));

					STRING_GLOBAL[0] = EOS;

				    SCMF(criminalid, 0x3399FFFF, "%s объявил Вас в розыск. Причина: %s. Текущий уровень розыска %d", GetPlayerNameEx(playerid), e_suspect[listitem], GetPlayerSuspect(criminalid));
				    SCMF(playerid, 0x3399FFFF, "Вы объявили %s в розыск. Причина: %s. Текущий уровень розыска %d", GetPlayerNameEx(criminalid), e_suspect[listitem], GetPlayerSuspect(criminalid));

				    format(STRING_GLOBAL, sizeof STRING_GLOBAL, "%s %s[%d] объявил %s[%d] в розыск [%d/6], причина: %s", GetPlayerJobAndRankName(playerid),
				    GetPlayerNameEx(playerid), playerid, GetPlayerNameEx(criminalid), criminalid, GetPlayerSuspect(criminalid), e_suspect[listitem]);

				    SendMessageToPoliceTeam(STRING_GLOBAL, 0xFFC000FF);

                    AddPlayerCrimes(criminalid);
				    AddPlayerToArchive(criminalid, GetPlayerNameEx(criminalid), 0, e_suspect[listitem], gettime(), GetPlayerData(criminalid, P_SUSPECT),GetPlayerData(criminalid,P_SKIN));
				}
			}
	    }
	}
}
stock DeleteRequestHelp(id)
{
	static const query[] = "SELECT * FROM police_tablet WHERE event=9 AND ownerid=%d";
	new fmt[sizeof query + 8];
	format(fmt, sizeof fmt, query, id);
	mysql_pquery(mysql, fmt, "CB_DeleteRequestHelp","i",id);

}
public: CB_DeleteRequestHelp(id)
{
	if(cache_num_rows())
	{
		static const query[] = "DELETE FROM police_tablet WHERE event=9 AND ownerid=%d";
		
		new fmt[sizeof query + 4];
		format(fmt, sizeof fmt, query, id);
		mysql_pquery(mysql,fmt);	
	}
}

stock GetCountTickets(ownerid)
{
	static string[300];
	string[0] = EOS;

	new count,Cache:result;

	mysql_format(mysql,string,sizeof string,"SELECT * FROM tickets WHERE uid=%d AND status=0",ownerid);
	result = mysql_query(mysql,string,true);

	count = cache_num_rows();

	cache_delete(result);

	return count;
}
stock AddPlayerToArchive(playerid, name[], type, reason[], time, suspect,skin)
{
	static const query[] = "INSERT INTO police_tablet (event, ownerid, time, name, reason, type, suspect, skin) VALUES (11, %d, %d, '%s', '%s', %d, %d, %d)";
	
	new fmt[sizeof(query) + MAX_PLAYER_NAME + 35 + 20];
	format(fmt,sizeof fmt, query, GetPlayerAccountID(playerid), time, name, reason,type, suspect, skin);
	mysql_pquery(mysql, fmt);
}
CMD:ticket(playerid)
{
	if(!IsPlayerInPoliceTeam(playerid)) return SendClientMessage(playerid, 0x999999FF, "Вы не работник ДПС");
	CEF_CREATE(playerid, 1, 4, "Police");
	return 1;
}
CMD:police_tablet(playerid)
{
	if(!IsPlayerInPoliceTeam(playerid)) return SendClientMessage(playerid, 0x999999FF, "Вы не сотрудник ДПС");
	CEF_CREATE(playerid, 1, 4, "Police");
	return 1;
}
stock AddPlayerCrimes(criminalid)
{
	AddPlayerData(criminalid, P_SUSPECT, +, 1);
	UpdatePlayerDatabaseInt(criminalid, "suspect", GetPlayerData(criminalid, P_SUSPECT));
}

stock CheckCarNameByID(id)
{
    static model_name[55] = "Автомобиль";
    for(new i; i < sizeof g_vehicle_info; i++)
    {
        if(id == g_vehicle_info[i][VI_ID])
        {
            model_name[0] = EOS;
            model_name = "";
            strcat(model_name, g_vehicle_info[i][VI_NAME]);
            return model_name;
        }
    }
    return model_name;
}