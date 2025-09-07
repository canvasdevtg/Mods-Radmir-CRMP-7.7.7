#if defined _progress_bar_included
    #endinput
#endif
#define _progress_bar_included

new progress_bar_time[MAX_PLAYERS];

new const progress_bar_text[][] = {"Нажимайте Y<br>с небольшим интервалом","Кликайте по прогрессу<br>с небольшим интервалом"};

stock Progress_Bar_Menu(playerid, type, gain, penalty)
{
    if(GetPVarInt(playerid, "progress_bar_type") != 0) return 0;

    SetPVarInt(playerid, "progress_bar_type", type);
    SetPVarInt(playerid, "progress_bar_fill", 0);
    SetPVarInt(playerid, "ProgressGain", gain);
    SetPVarInt(playerid, "ProgressPenalty", penalty);

	TogglePlayerControllable(playerid, false);

    new str[115];
    format(str, sizeof str, "[[\"%s\", 0, 1000]]", progress_bar_text[GetPlayerClient(playerid)]);
    CEF_CREATE(playerid, 2, 4, "ProgressBar", str);
    return 1;
}

stock OnPlayerProgressBar(playerid)
{
    new type = GetPVarInt(playerid, "progress_bar_type");
    new time = progress_bar_time[playerid];
    new fill = GetPVarInt(playerid, "progress_bar_fill");
    new ProgressPenalty = GetPVarInt(playerid, "ProgressPenalty");
    new ProgressGain = GetPVarInt(playerid, "ProgressGain");

    if(type == 0) return 0;

    if(time != 0)
    {
        fill -= ProgressPenalty;
        if(fill < 0) fill = 0;
        SetPVarInt(playerid, "progress_bar_fill", fill);
    }
    else
    {
        fill += ProgressGain;
        if(fill > 100) fill = 100;
        SetPVarInt(playerid, "progress_bar_fill", fill);

        progress_bar_time[playerid] = 1;
        ProgressBarAnim(playerid, type);
    }

    new fmt_text[64];
	format(fmt_text, sizeof fmt_text, "interface('ProgressBar').setFill(0,%d)", fill);
	CEF_CREATE(playerid, 1, 2, fmt_text);

    if(fill >= 100){
        ProgressBarComplete(playerid, type);
        SetPVarInt(playerid, "progress_bar_type", 0);
    }
    return 1; 
}

stock ProgressBarAnim(playerid, type)
{
    switch(type){
        case 1: ApplyAnimationEx(playerid, "OTB", "betslp_loop", 4.1, 0, 0, 0, 1, 20_000, 0, USE_ANIM_TYPE_NONE - 1);
        case 6: ApplyAnimationEx(playerid, "OTB", "betslp_loop", 4.1, 0, 0, 0, 1, 20_000, 0, USE_ANIM_TYPE_NONE - 1);
        case 7: ApplyAnimationEx(playerid, "OTB", "betslp_loop", 4.1, 0, 0, 0, 1, 20_000, 0, USE_ANIM_TYPE_NONE - 1);
        case 9: ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0);
        default: return 0;
    }
    return 1;
}

stock ProgressBarComplete(playerid, type)
{
    CEF_HIDE(playerid, "ProgressBar");
    TogglePlayerControllable(playerid, true);

    switch(type){
        case 1:{
            new vehicleid = GetNearestVehicleID(playerid, 6.0);

			RepairVehicle(vehicleid);

			if(IsAOwnableCar(vehicleid)) SetVehicleData(vehicleid, V_HEALTH, 1000.0);

			SendClientMessage(playerid, COLOR_GREY, "Вы успешно починили транспорт");

			GiveIteam(playerid, 44, 0, 1, 0);

			OnBattlePass_Perfomance(playerid, 6, 1);

			ClearAnimations(playerid);

			SetVehicleParam(vehicleid, V_BONNET, VEHICLE_PARAM_OFF);
        }
        case 2:{
			DisablePlayerCheckpoint(playerid);
			ClearAnimations(playerid);
			ApplyAnimationEx(playerid, "CARRY", "liftup", 4.0, 0, 0, 0, 0, 0, 0, USE_ANIM_TYPE_NONE - 1);
			SetTimerEx("SetPlayerLoaderJobLoad", 1000, false, "i", playerid);
        }
        case 3:{
            for(new i; i < sizeof(diving_chest); i++)
	        {
                if(IsPlayerInRangeOfPoint(playerid, 3.0, diving_chest[i][E_POS][0], diving_chest[i][E_POS][1], diving_chest[i][E_POS][2]))
		        {
				    if(diving_chest[i][E_STATUS] == 1)
                    {
                        ItemDayving(playerid);
                        GiveRandCase(playerid);
                        DestroyDynamicObject(diving_chest[i][E_OBJECT]);
				        DestroyDynamic3DTextLabel(diving_chest[i][E_LABEL]);
				        DestroyDynamicArea(diving_chest[i][E_INTERACTION]);
	                    diving_chest[i][E_INTERACTION] = 0;
				        diving_chest[i][E_STATUS] = 0;
				        diving_chest[i][E_TIMER] = 120;
                    }
			    }
			}
        }
        case 4:{
            DisablePlayerCheckpoint(playerid);
			
			SetPlayerJobLoadItems(playerid, GetPlayerJobLoadItems(playerid) + 1);

            RemovePlayerAttachedObject(playerid, A_OBJECT_SLOT_HAND);
			ApplyAnimationEx(playerid, "CARRY", "putdwn", 4.0, 0, 0, 0, 0, 0, 0);

			SetPlayerLoaderJobLoadCP(playerid);
			
			SendClientMessage(playerid, COLOR_GREEN, "Вы успешно положили ящик");

			new fmt_str[70];
			format(fmt_str, sizeof fmt_str, "Вы положили: {FF9900}%d ящиков", GetPlayerJobLoadItems(playerid));
			SendClientMessage(playerid, 0x66CC00FF, fmt_str);
        }
        case 5:{
            ApplyAnimationEx(playerid, "CARRY", "putdwn", 4.0, 0, 0, 0, 0, 0, 0);

			RemovePlayerAttachedObject(playerid, 2);

			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

			SetPlayerCheckpoint(playerid, 488.3341, -2383.1311, 34.7456, 2.0);
			lesopilka_cp[playerid] = 1;
			Lesopilka[playerid] = 3;

			SendClientMessage(playerid, 0xabcdefFF, "Вы успешно начали работу на станке. Ожидайте, пока станок распилит бревно.");
        }
        case 6:{
            GiveIteam(playerid, 167, 0, 1, 0, "Замена компонента");

            new biz_id = GetPlayerInBiz(playerid);

			SetBusinessData(biz_id, B_WORK, 1);

			new query[297];
			mysql_format(mysql, query, sizeof query, "UPDATE business SET `work`=%d WHERE `id`=%d LIMIT 1", GetBusinessData(biz_id, B_WORK), GetBusinessData(biz_id, B_SQL_ID));
			mysql_query(mysql, query, false);

			if(GetBusinessData(biz_id, B_WORK) == 1)
		    {
				if(GetBusinessData(biz_id, B_WORK_2) == 1)
				{
					SetBusinessData(biz_id, B_VETR_WORK, 1);

			        mysql_format(mysql, query, sizeof query, "UPDATE business SET `vetr_work`=%d WHERE `id`=%d LIMIT 1", GetBusinessData(biz_id, B_VETR_WORK), GetBusinessData(biz_id, B_SQL_ID));
			        mysql_query(mysql, query, false);	
				}
			}

		    GameText(playerid, "~g~Успешно", 4000, 2);
		    SendClientMessage(playerid, 0xCECECEFF, "{B8CEF6}Вы успешно заменили {FFFFFF}компонент");
        }
        case 7:{
            GiveIteam(playerid, 166, 0, 1, 0, "Замена компонента");

            new biz_id = GetPlayerInBiz(playerid);

			SetBusinessData(biz_id, B_WORK_2, 1);

            new query[297];
			mysql_format(mysql, query, sizeof query, "UPDATE business SET `work_2`=%d WHERE `id`=%d LIMIT 1", GetBusinessData(biz_id, B_WORK_2), GetBusinessData(biz_id, B_SQL_ID));
			mysql_query(mysql, query, false);

			if(GetBusinessData(biz_id, B_WORK_2) == 1)
		    {
				if(GetBusinessData(biz_id, B_WORK) == 1)
				{
					SetBusinessData(biz_id, B_VETR_WORK, 1);

			        mysql_format(mysql, query, sizeof query, "UPDATE business SET `vetr_work`=%d WHERE `id`=%d LIMIT 1", GetBusinessData(biz_id, B_VETR_WORK), GetBusinessData(biz_id, B_SQL_ID));
			        mysql_query(mysql, query, false);	
				}
			}

		    GameText(playerid, "~g~Успешно", 4000, 2);
		    SendClientMessage(playerid, 0xCECECEFF, "{B8CEF6}Вы успешно заменили {FFFFFF}компонент");
        }
        case 8:{
            string_dialog[0] = EOS;

			format
			(
				string_dialog, sizeof string_dialog, "Компонент\t Последняя диагностика\n\
				{FFFFFF}Масляный фильтр: \t {ffba42}0 час 0 минуты назад\n\
				{FFFFFF}Воздушный фильтр: \t {ffba42}0 час 0 минуты назад"
			);
			IntfDialogCallRemote(playerid, DIALOG_BIZ_VETRIKI, DIALOG_STYLE_TABLIST_HEADERS, "Обслуживание", string_dialog, "Далее", "Отмена");
        }
        case 9:{
            ClearAnimations(playerid);

			new vehicleid = GetNearestVehicleID(playerid, 6.0);
            if(vehicleid == INVALID_VEHICLE_ID) 
            {
                return 1;
            }

            new Float:x, Float:y, Float:z;
			new Float:angle;

			GetVehiclePos(vehicleid, x, y, z);

			if(!IsPlayerInRangeOfPoint(playerid, 3.0, x, y, z)) 
                return SCM(playerid, 0xCECECEFF, "* Вы должны находиться рядом с транспортом.");

            GetVehicleZAngle(vehicleid, angle);

            SetVehiclePos(vehicleid, x, y, z + 1.5);
            SetVehicleZAngle(vehicleid, angle);
        }
        case 11:{
            new garden_id = GetPVarInt(playerid, "garden_id");
			new yamka_id = GetPVarInt(playerid, "yamka_id");

			G_STATUS_YAM[garden_id][yamka_id] = 1;

			UpdateDynamic3DTextLabelText(gardendyamkalab[garden_id][yamka_id], 0xFFFF00FF, "{FFA500}Свободная ямка\n{FFFFFF}Необходима известь");
        }
        case 12:{
            ClearAnimations(playerid);

			if(g_player_mine_status[playerid] == 4)
			{
				g_player_mine_cp[playerid] = 6;
				GameText(playerid, "~y~Готово!~n~Возьмите тележку и лопату у стойки", 3000, 2);
				CEF_CREATE(playerid, 1, 2, "window.destroySound(10311, 30)");
				SetPVarInt(playerid, "Ices_Axe_2", 0);
				new rack = g_player_mine_rack[playerid];

				SetPlayerCheckpoint(playerid, g_mine_rack[rack][0], g_mine_rack[rack][1], g_mine_rack[rack][2], 1.0);

				g_player_mine_status[playerid] = 5;

				new id = g_player_mine_ore[playerid];
				
				g_mine_ore[id][MO_STATUS] = 3;

				if(IsValidDynamicObject(g_mine_ore[id][MO_OBJECT])) 
					DestroyDynamicObject(g_mine_ore[id][MO_OBJECT]);
			
				g_mine_ore[id][MO_OBJECT] = INVALID_OBJECT_ID;

				g_mine_ore[id][MO_OBJECT] = CreateDynamicObject(17107, g_mine_ore_pos[id][MOP_DOWN][0], g_mine_ore_pos[id][MOP_DOWN][1], g_mine_ore_pos[id][MOP_DOWN][2], 0.0, 0.0, 0.0);

				UpdateDynamic3DTextLabelText(g_mine_ore[id][MO_LABEL], 0xFFFFFFFF, "{"MINE_COLOR"}Каменная пыль\nс залежами");
				
			}
        }
    }
    return 1;
}