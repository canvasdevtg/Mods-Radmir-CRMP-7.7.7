#if defined _dialog_included
    #endinput
#endif
#define _dialog_included

stock OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(GetPVarInt(playerid, "Login_1") != 1) 
    {
        Kick(playerid);
        return 1;
    }
	if(player_DialogID[playerid] != dialogid) return 1;
	player_DialogID[playerid] = -1;

    new list_id = listitem + 1;
	if(strcmp(inputtext, "#", true) == 0 || strcmp(inputtext, "|", true) == 0 || strcmp(inputtext, "%", true) == 0 || strcmp(inputtext, "@", true) == 0 || strcmp(inputtext, "&", true) == 0) SendClientMessage(playerid, 0xFF6600FF, "В сообщение присутствуют запрещеные символы");
	if(strfind(inputtext,"%") != -1) return 0;
	PoliceTablet:OnDialogResponse(playerid, dialogid, response, listitem);
	switch(dialogid)
	{
		case DIALOG_DECOR:
		{
			new model_id = g_decoration_id[playerid];
			new id = g_decoration_mysql_id[playerid];
			if(!response) return 1;
			switch(listitem)
			{
				case 0:
				{
					EditDynamicObject(playerid, DecorInfo[id][Decor_Object]);

					SetPVarInt(playerid, "EditDecor", 1);
					SetPVarInt(playerid, "EditDecorID", id);
					SetPVarInt(playerid, "EditDecorObject", model_id);

					if(g_player_use_editing[playerid] == true)
					{
						DeletePlayer3DTextLabel(playerid, g_object_text[playerid][id]);
						g_object_text[playerid][id] = PlayerText3D: -1;
					}
				}
				case 1:
				{
					GiveAcs(playerid, model_id, 23);

					new str[256];

					format(str, sizeof(str), "UPDATE decoration SET Status = 1 WHERE id = %d LIMIT 1", id + 1);
					mysql_query(mysql, str, false);

					DestroyDynamicObject(DecorInfo[id][Decor_Object]);
					DecorInfo[id][Decor_Status] = 1;

					DeletePlayer3DTextLabel(playerid, g_object_text[playerid][id]);
					g_object_text[playerid][id] = PlayerText3D: -1;
				}
			}
		}
		case DIALOG_VETR_TARIF:
		{
			new businessid = GetPVarInt(playerid, "ownablebiz_id");
			if(businessid != -1)
			{
				if(response)
				{
					new price = strval(inputtext);
					if(strlen(inputtext) && IsNumeric(inputtext))
					{
						if(15 <= price <= 35)
						{
							new query[64 + 1];
							SetBusinessData(businessid, B_PROD_PRICE, price);

							format(query, sizeof query, "UPDATE business SET prod_price=%d WHERE id=%d LIMIT 1", GetBusinessData(businessid, B_PROD_PRICE), GetBusinessData(businessid, B_SQL_ID));
							mysql_query(mysql, query, false);
							UpdateBusinessLabel(businessid);

							SendClientMessage(playerid, 0x66CC00FF, "Стоимость тарифа изменена");
							return ShowPlayerBusinessDialog(playerid, BIZ_OPERATION_PARAMS);
						}
						else SendClientMessage(playerid, 0xCECECEFF, "Укажите стоимость от 15 до 35 рублей");
					}
					else SendClientMessage(playerid, 0xCECECEFF, "Введите стоимость тарифа");
					ShowPlayerBusinessDialog(playerid, BIZ_OPERATION_PROD_PRICE);
				}
				else ShowPlayerBusinessDialog(playerid, BIZ_OPERATION_PARAMS);
			}
		}
		case DIALOG_VETRIAK_IMPROVEMENT:
		{
			if(!response) return ShowPlayerBusinessDialog(playerid, BIZ_OPERATION_PARAMS);

            SetPVarInt(playerid, "selected_improvement", listitem);

			switch(listitem + 1)
			{
				case 1:
				{
                    IntfDialogCallRemote
	                (
		                playerid, DIALOG_VETR_IMPROVEMENT, DIALOG_STYLE_MSGBOX,
		                "Покупка улучшения",
		                "{FAAC58}Резервные аккумуляторы\n"\
		                "\n"\
		                "{FFFFFF}В вашей ветровой станции появится дополнительное хранилище энергии, которое будет постепенно\n"\
						"{FFFFFF}заполняться относительно нагруженности станции. (До 5000 кВт)\n"\
		                "\n"\
						"{FFFFFF}При ветрянной погоде хранилище заполняется быстрее!\n"\
						"\n"\
						"{FFFFFF}В случае поломки ветряной станции, ваши клиенты будут потреблять электричество за счет хранилища,\n"\
						"{FFFFFF}позволяя вам не потерять клиентов при поломке.",
						"Купить", "Отмена"
	                );
				}
				case 2:
				{
                    IntfDialogCallRemote
	                (
		                playerid, DIALOG_VETR_IMPROVEMENT, DIALOG_STYLE_MSGBOX,
		                "Покупка улучшения",
		                "{FAAC58}Дополнительные аккумуляторы\n"\
		                "\n"\
		                "{FFFFFF}В вашей ветровой станции появится дополнительное хранилище энергии, которое будет постепенно\n"\
						"{FFFFFF}заполняться относительно нагруженности станции. (До 10000 кВт)",
						"Купить", "Отмена"
	                );
				}
			}
		}
		case DIALOG_VETR_IMPROVEMENT:
		{
			new businessid = GetPVarInt(playerid, "ownablebiz_id");

			listitem = GetPVarInt(playerid, "selected_improvement");

			if(businessid != -1)
			{
				if(response)
				{
					if(0 <= listitem && listitem < sizeof g_vetr_improvements)
					{
						new i_level = GetBusinessData(businessid, B_IMPROVEMENTS);
						new i_price = g_vetr_improvements[listitem][I_PRICE];

						if(i_level < listitem)
						{
								SendClientMessage(playerid, 0xCECECEFF, "Этот уровень улучшений пока недоступен");
						}
						else if(i_level > listitem)
						{
								SendClientMessage(playerid, 0xCECECEFF, "Вы уже купили этот уровень улучшений");
						}
						else if(!VerifyIntString(QueryPlayerBalance(playerid), i_price))
						{
							new fmt_str[64];

							format(fmt_str, sizeof fmt_str, "Для покупки %d уровня улучшений необходимо %d рублей", listitem + 1, i_price);
							SendClientMessage(playerid, 0xCECECEFF, fmt_str);
						}
						else
						{
							new fmt_str[128];

							format(fmt_str, sizeof fmt_str, "UPDATE accounts_canvasdev a, business b SET a.money=%s, b.improvements=%d WHERE a.id=%d AND b.id=%d", SetILPlayerInt(playerid, QueryPlayerBalance(playerid), -i_price), i_level + 1, GetPlayerAccountID(playerid), GetBusinessData(businessid, B_SQL_ID));
							mysql_query(mysql, fmt_str, false);

							if(!mysql_errno())
							{
								ModifyCashBalance(playerid, -i_price, "Покупка улучшений для Бизнеса", false, true);

								format(fmt_str, sizeof fmt_str, "Вы улучшили свой бизнес до {FFCD00}%s {3399FF}уровня", GetNumericName(listitem + 1));
								SendClientMessage(playerid, 0x3399FFFF, fmt_str);

								AddBusinessData(businessid, B_IMPROVEMENTS, +, 1);
								switch(listitem + 1)
								{
									case 1:
									{
									    SendClientMessage(playerid, 0x66CC00FF, "Теперь Ваш бизнес установлена дополнительное хранилище энергии.");
										SendClientMessage(playerid, 0x66CC00FF, "Это позволит потреблять энергию за счет хранилища в случае поломки ветрянной станции.");
									}
									case 2:
									{
										SendClientMessage(playerid, 0x66CC00FF, "Теперь Ваш бизнес установлена дополнительное хранилище энергии.");
										SendClientMessage(playerid, 0x66CC00FF, "Это позволит потреблять энергию за счет хранилища в случае поломки ветрянной станции.");
									}
								}
							}
							else SendClientMessage(playerid, 0xFF6600FF, "Ошибка сохранения, повторите попытку {FF0000}(equ-code 23)");
						}
					}
					ShowPlayerBusinessDialog(playerid, BIZ_OPERATION_PARAMS);
				}
			}
		}
		case DIALOG_SELL_KVARIAT:
		{
			if(!response) return 1;

			new slot = player_slot[playerid];
            new type = player_type[playerid];

	        for(new i; i < MAX_PLAYER_ITEMS; i++)
	        { 
		        if(GetPlayerItem(i, PI_OWNER_ID) != GetPlayerAccountID(playerid)) continue;
		        if(GetPlayerItem(i, PI_SLOTS) != slot) continue;
		        if(GetPlayerItem(i, PI_TYPE) != type) continue;

		        new item_id = GetPlayerItem(i, PI_ITEM);

		        SetPlayerData(playerid, P_DOSTIJ23, GetPlayerData(playerid, P_DOSTIJ23) + ItemsInfo[item_id][i_item_price]);
		        UpdatePlayerDatabaseInt(playerid, "dostij23", GetPlayerData(playerid, P_DOSTIJ23) + ItemsInfo[item_id][i_item_price]);

		        SCMF(playerid, 0xCECECEFF, "Вы продали предмет: '%s' в антиквариатной лавке за %d руб.", ItemsInfo[item_id][i_item_name], ItemsInfo[item_id][i_item_price]);
			
		        GiveIteam(playerid, item_id, 0, 1, 0);
		        ModifyCashBalance(playerid, ItemsInfo[item_id][i_item_price], "[ItemSell] Продажа в антиквариатной лавке");

				if(GetPlayerLevel(playerid) > 4)
                {
				    AddPlayerData(playerid, P_ACHIV_22, +, ItemsInfo[item_id][i_item_price]);
                    UpdatePlayerDatabaseInt(playerid, "achiv_22", GetPlayerData(playerid, P_ACHIV_22));
        
		            if(GetPlayerData(playerid, P_ACHIV_22) >= 500000 && GetPlayerData(playerid, P_ACHIV_22_COMPLETED) == 0)
		            {
			            GivePlayerMyPrizes(playerid, "Донат", 10, 0, 0, 120, 0);
                        SendClientMessage(playerid, COLOR_GREEN, "Поздравляем! Вы получили достижение: {FFFF00}\"Золотая лихорадка\"");
			            SendClientMessage(playerid, 0xead671FF, "Вам выдана награда за получение достижения. Используйте {ffffff}клавишу M > Награды, {ead671}чтобы забрать её.");
		    
			            SetPlayerData(playerid, P_ACHIV_22_COMPLETED, 1);		        
                        UpdatePlayerDatabaseInt(playerid, "achiv_22_completed", 1);

					    CEF_CREATE(playerid, 2, 4, "AchievementNotification", "[22, 2, \"Вы получили достижение!\"]");
		            }
				}
	        }
			return 1;
		}
		case DIALOG_GANG_MAFIA:
		{
			if(!response) return 1;

			switch(listitem + 1)
			{
				case 1:
				{
                    new fmt_text[512],query[50];
                    for(new i = 0; i < 18; i ++)
	                {
    	                format(query, sizeof query, "\"%06x\",", family_colors[i]);
		                strcat(fmt_text, query);
                    }
  	                new str_len;
	                str_len = strlen(fmt_text);
	                strdel(fmt_text, str_len - 1, str_len);
	                format(STRING_GLOBAL, sizeof STRING_GLOBAL, "[\"Выберите цвет банды\", [%s], 1]",  fmt_text);
	                SetPVarInt(playerid,"colortype",1);
					SetPVarInt(playerid,"MafiaType",1);
                    CEF_CREATE(playerid, 2, 4, "GangColor", STRING_GLOBAL);
                    CEF_HIDE(playerid, "GangCreate");
				}
				case 2:
				{
                    new fmt_text[512],query[50];
                    for(new i = 0; i < 18; i ++)
	                {
    	                format(query, sizeof query, "\"%06x\",", family_colors[i]);
		                strcat(fmt_text, query);
                    }
  	                new str_len;
	                str_len = strlen(fmt_text);
	                strdel(fmt_text, str_len - 1, str_len);
	                format(STRING_GLOBAL, sizeof STRING_GLOBAL, "[\"Выберите цвет банды\", [%s], 1]",  fmt_text);
	                SetPVarInt(playerid,"colortype",1);
					SetPVarInt(playerid,"MafiaType",2);
                    CEF_CREATE(playerid, 2, 4, "GangColor", STRING_GLOBAL);
                    CEF_HIDE(playerid, "GangCreate");
				}
				case 3:
				{
                    new fmt_text[512],query[50];
                    for(new i = 0; i < 18; i ++)
	                {
    	                format(query, sizeof query, "\"%06x\",", family_colors[i]);
		                strcat(fmt_text, query);
                    }
  	                new str_len;
	                str_len = strlen(fmt_text);
	                strdel(fmt_text, str_len - 1, str_len);
	                format(STRING_GLOBAL, sizeof STRING_GLOBAL, "[\"Выберите цвет банды\", [%s], 1]",  fmt_text);
	                SetPVarInt(playerid,"colortype",1);
					SetPVarInt(playerid,"MafiaType",3);
                    CEF_CREATE(playerid, 2, 4, "GangColor", STRING_GLOBAL);
                    CEF_HIDE(playerid, "GangCreate");
				}
			}
		}
		case DIALOG_TPLIST:
		{
			if(!response) return 1;

			switch(listitem + 1)
			{
				case 1:
				{
					IntfDialogCallRemote
	                (
		                playerid, DIALOG_TPLIST_1, DIALOG_STYLE_LIST,
		                "{9966FF}Города",
		                "[1] - Южный\n"\
						"[2] - Арзамас\n"\
						"[3] - Лыткарино\n"\
						"[4] - Нижегородск\n"\
						"[5] - Эдово",
		                "Выбрать", "Закрыть"
	                );
				}
				case 2:
				{
					IntfDialogCallRemote
	                (
		                playerid, DIALOG_TPLIST_2, DIALOG_STYLE_LIST,
		                "{9966FF}Казино",
		                "[1] - Casino Бендер\n"\
						"[2] - Casino Royal",
		                "Выбрать", "Закрыть"
	                );
				}
				case 3:
				{
					IntfDialogCallRemote
	                (
		                playerid, DIALOG_TPLIST_3, DIALOG_STYLE_LIST,
		                "{9966FF}Работы",
		                "[1] - Шахта\n"\
						"[2] - Ферма\n"\
						"[3] - Лесопилка\n"\
						"[4] - Электрик",
		                "Выбрать", "Закрыть"
	                );
				}
				case 4:
				{
					IntfDialogCallRemote
	                (
		                playerid, DIALOG_TPLIST_4, DIALOG_STYLE_LIST,
		                "{9966FF}Автосалоны",
		                "[1] - Низкий\n"\
						"[2] - Средний\n"\
						"[3] - Элитный",
		                "Выбрать", "Закрыть"
	                );
				}
				case 5:
				{
					IntfDialogCallRemote
	                (
		                playerid, DIALOG_TPLIST_5, DIALOG_STYLE_LIST,
		                "{9966FF}Остальное",
		                "[1] - Тц LEKA\n"\
						"[2] - Контейнеры\n"\
						"[3] - МГУ\n"\
						"[4] - Пасаж",
		                "Выбрать", "Закрыть"
	                );
				}
				case 6:
				{
					IntfDialogCallRemote
	                (
		                playerid, DIALOG_TPLIST_6, DIALOG_STYLE_LIST,
		                "{9966FF}Посёлки",
		                "[1] - Гарель\n"\
						"[2] - Корякино\n"\
						"[3] - Батырево\n"\
						"[4] - Бусаево\n"\
						"[5] - Лесное\n"\
						"[6] - Рублёвка\n"\
						"[7] - Мирное\n"\
						"[8] - Простоквасино\n"\
						"[9] - Армейское\n"\
						"[10] - Шахтерское\n"\
						"[11] - Барвиха",
		                "Выбрать", "Закрыть"
	                );
				}
			}
		}
		case DIALOG_TPLIST_1:
		{
			if(!response) return callcmd::tplist(playerid, "");

			switch(listitem + 1)
			{
				case 1:
				{
					SetPlayerPos(playerid, 2570.7505,-2048.2893,21.9640);
		            SetPlayerVirtualWorld(playerid, 0);
				}
				case 2:
				{
					SetPlayerPos(playerid, 842.4398,594.0474,15.8857);
		            SetPlayerVirtualWorld(playerid, 0);
				}
				case 3:
				{
					SetPlayerPos(playerid, -2666.0464,150.2831,12.4110);
		            SetPlayerVirtualWorld(playerid, 0);
				}
				case 4:
				{
					SetPlayerPos(playerid, -2539.7690,1867.1367,53.0226);
		            SetPlayerVirtualWorld(playerid, 0);
				}
				case 5:
				{
					SetPlayerPos(playerid, -2477.1113,2884.9019,64.7278);
		            SetPlayerVirtualWorld(playerid, 0);
				}
			}
		}
		case DIALOG_TPLIST_2:
		{
			if(!response) return callcmd::tplist(playerid, "");

			switch(listitem + 1)
			{
				case 1:
				{
					SetPlayerPos(playerid, -2204.0806,-299.3063,23.3879);
		            SetPlayerVirtualWorld(playerid, 0);
				}
				case 2:
				{
					SetPlayerPos(playerid, 1917.2189,-1938.4081,31.7932);
		            SetPlayerVirtualWorld(playerid, 0);
				}
			}
		}
		case DIALOG_TPLIST_3:
		{
			if(!response) return callcmd::tplist(playerid, "");

			switch(listitem + 1)
			{
				case 1:
				{
					SetPlayerPos(playerid, -497.6328,3337.8948,29.6522);
		            SetPlayerVirtualWorld(playerid, 0);
				}
				case 2:
				{
					SetPlayerPos(playerid, 1620.1111,654.8436,16.0372);
		            SetPlayerVirtualWorld(playerid, 0);
				}
				case 3:
				{
					SetPlayerPos(playerid, 430.4370,-2435.8274,34.7629);
		            SetPlayerVirtualWorld(playerid, 0);
				}
				case 4:
				{
					SetPlayerPos(playerid, 1805.3126,2497.9937,15.7108);
		            SetPlayerVirtualWorld(playerid, 0);
				}
			}
		}
		case DIALOG_TPLIST_4:
		{
			if(!response) return callcmd::tplist(playerid, "");

			switch(listitem + 1)
			{
				case 1:
				{
					SetPlayerPos(playerid, 3232.5356,-43.7308,5.0234);
		            SetPlayerVirtualWorld(playerid, 0);
				}
				case 2:
				{
					SetPlayerPos(playerid, 390.6593,794.1421,12.2102);
		            SetPlayerVirtualWorld(playerid, 0);
				}
				case 3:
				{
					SetPlayerPos(playerid, 1866.1742,2825.8401,12.0000);
		            SetPlayerVirtualWorld(playerid, 0);
				}
			}
		}
		case DIALOG_TPLIST_5:
		{
			if(!response) return callcmd::tplist(playerid, "");

			switch(listitem + 1)
			{
				case 1:
				{
					SetPlayerPos(playerid, 3234.7639,-37.0375,5.2666);
		            SetPlayerVirtualWorld(playerid, 0);
				}
				case 2:
				{
					SetPlayerPos(playerid, -1932.6188,2909.9631,5.9990);
		            SetPlayerVirtualWorld(playerid, 0);
				}
				case 3:
				{
					SetPlayerPos(playerid, -399.3446,780.6558,12.1673);
		            SetPlayerVirtualWorld(playerid, 0);
				}
				case 4:
				{
					SetPlayerPos(playerid, 132.9044,664.6984,11.9385);
		            SetPlayerVirtualWorld(playerid, 0);
				}
			}
		}
		case DIALOG_TPLIST_6:
		{
			if(!response) return callcmd::tplist(playerid, "");

			switch(listitem + 1)
			{
				case 1:
				{
					SetPlayerPos(playerid, 2761.3259,-227.6433,3.4632);
		            SetPlayerVirtualWorld(playerid, 0);
				}
				case 2:
				{
					SetPlayerPos(playerid, 828.8032,-1356.0903,40.1405);
		            SetPlayerVirtualWorld(playerid, 0);
				}
				case 3:
				{
					SetPlayerPos(playerid, 1761.8978,2567.4502,14.3506);
		            SetPlayerVirtualWorld(playerid, 0);
				}
				case 4:
				{
					SetPlayerPos(playerid, 243.1151,-970.8812,39.8704);
		            SetPlayerVirtualWorld(playerid, 0);
				}
				case 5:
				{
					SetPlayerPos(playerid, -2247.4683,-1819.6254,13.0557);
		            SetPlayerVirtualWorld(playerid, 0);
				}
				case 6:
				{
					SetPlayerPos(playerid, 1873.9680,-2732.7590,27.0289);
		            SetPlayerVirtualWorld(playerid, 0);
				}
				case 7:
				{
					SetPlayerPos(playerid, 410.2462,1220.8755,9.9005);
		            SetPlayerVirtualWorld(playerid, 0);
				}
				case 8:
				{
					SetPlayerPos(playerid, -888.1649,1954.6395,45.8526);
		            SetPlayerVirtualWorld(playerid, 0);
				}
				case 9:
				{
					SetPlayerPos(playerid, 518.1373,2715.5190,10.8280);
		            SetPlayerVirtualWorld(playerid, 0);
				}
				case 10:
				{
					SetPlayerPos(playerid, 3.4385,2847.6792,7.5001);
					SetPlayerVirtualWorld(playerid, 0);
				}
				case 11:
				{
					SetPlayerPos(playerid, 3603.6006,3983.4048,8.6765);
					SetPlayerVirtualWorld(playerid, 0);
				}
			}
		}
		case DIALOG_DONATE_BUY:
		{
			if(!response) return callcmd::donate(playerid, "");

			new	query[94],
				Cache: result;

			format(query, sizeof query, "SELECT * FROM donate_items WHERE id=%d LIMIT 1", GetPlayerListitemValue(playerid, listitem));
			result = mysql_query(mysql, query, true);

			new name[48];

			cache_get_field_content(0, "name", name);
			new item_id = cache_get_field_content_int(0, "item_id");
			new price = cache_get_field_content_int(0, "price");
			new type = cache_get_field_content_int(0, "type");

			cache_delete(result);

			if(QueryPlayerDonationBalance(playerid) < price) return GameText(playerid, "~r~Недостаточно~n~"SERVER_DONATE"", 3000, 2), callcmd::donate(playerid, "");

			if(type == 1)
			{
				if((GetPlayerOwnableCars(playerid) + 1) > GetPlayerCarSlots(playerid)) return SendClientMessage(playerid, 0x3399FFFF, "Все слоты для транспорта заняты.");

				ProcessPlayerCredit(playerid, -price);

				if(item_id == 15107)
				{
					GiveCar(playerid, item_id, 1, 1, 0, 0, -1765.9470, 2911.2585, 5.8822, 90.4859, gettime());
				}
				else
				{
					GiveCar(playerid, item_id, 1, 1, -1, -1, -1765.9470, 2911.2585, 5.8822, 90.4859, gettime());
				}

				SCMF(playerid, 0xFFFFFFFF, "{"SERVER_COLOR"}Вы успешно приобрели транспорт: {FFFFFF}%s[№%d] {"SERVER_COLOR"}за {FFFFFF}%d "SERVER_DONATE"", name, item_id, price);
			}
		}
		case DIALOG_BUY_LVL:
		{
			if(!response) return callcmd::donate(playerid, "");

			switch(listitem + 1)
			{
				case 1:
				{
					if(QueryPlayerDonationBalance(playerid) < 25) return IntfDialogCallRemote(playerid, -1, DIALOG_STYLE_MSGBOX, "{FF6600}Ошибка", "{FFFFFF}Недостаточно DCOINS для покупки", "Назад", "");

					ProcessPlayerCredit(playerid, -25);

					SetPlayerData(playerid, P_EXP, 0);
				    AddPlayerData(playerid, P_LEVEL, +, 1);
					UpdatePlayerDatabaseInt(playerid, "exp", GetPlayerData(playerid, P_EXP));
					UpdatePlayerDatabaseInt(playerid, "level", GetPlayerData(playerid, P_LEVEL));
				    SendClientMessage(playerid, 0xCECECEFF, "Поздравляем! Ваш уровень повышен");
				    SetPlayerLevelInit(playerid);

					SCM(playerid, 0xFFFFFFFF, "{"SERVER_COLOR"}Вы успешно приобрели: {FFFFFF}Игровой уровень +1 {"SERVER_COLOR"}за {FFFFFF}25 [DCOINS]");
				}
				case 2:
				{
					if(QueryPlayerDonationBalance(playerid) < 75) return IntfDialogCallRemote(playerid, -1, DIALOG_STYLE_MSGBOX, "{FF6600}Ошибка", "{FFFFFF}Недостаточно DCOINS для покупки", "Назад", "");

					ProcessPlayerCredit(playerid, -75);

					SetPlayerData(playerid, P_EXP, 0);
				    AddPlayerData(playerid, P_LEVEL, +, 5);
					UpdatePlayerDatabaseInt(playerid, "exp", GetPlayerData(playerid, P_EXP));
					UpdatePlayerDatabaseInt(playerid, "level", GetPlayerData(playerid, P_LEVEL));
				    SendClientMessage(playerid, 0xCECECEFF, "Поздравляем! Ваш уровень повышен");
				    SetPlayerLevelInit(playerid);

					SCM(playerid, 0xFFFFFFFF, "{"SERVER_COLOR"}Вы успешно приобрели: {FFFFFF}Игровой уровень +5 {"SERVER_COLOR"}за {FFFFFF}25 [DCOINS]");
				}
				case 3:
				{
					if(QueryPlayerDonationBalance(playerid) < 170) return IntfDialogCallRemote(playerid, -1, DIALOG_STYLE_MSGBOX, "{FF6600}Ошибка", "{FFFFFF}Недостаточно DCOINS для покупки", "Назад", "");
	
					ProcessPlayerCredit(playerid, -170);

					SetPlayerData(playerid, P_EXP, 0);
				    AddPlayerData(playerid, P_LEVEL, +, 10);
					UpdatePlayerDatabaseInt(playerid, "exp", GetPlayerData(playerid, P_EXP));
					UpdatePlayerDatabaseInt(playerid, "level", GetPlayerData(playerid, P_LEVEL));
				    SendClientMessage(playerid, 0xCECECEFF, "Поздравляем! Ваш уровень повышен");
				    SetPlayerLevelInit(playerid);

					SCM(playerid, 0xFFFFFFFF, "{"SERVER_COLOR"}Вы успешно приобрели: {FFFFFF}Игровой уровень +10 {"SERVER_COLOR"}за {FFFFFF}170 [DCOINS]");
				}
				case 4:
				{
					if(QueryPlayerDonationBalance(playerid) < 250) return IntfDialogCallRemote(playerid, -1, DIALOG_STYLE_MSGBOX, "{FF6600}Ошибка", "{FFFFFF}Недостаточно DCOINS для покупки", "Назад", "");
			
					ProcessPlayerCredit(playerid, -250);

					SetPlayerData(playerid, P_EXP, 0);
				    AddPlayerData(playerid, P_LEVEL, +, 20);
					UpdatePlayerDatabaseInt(playerid, "exp", GetPlayerData(playerid, P_EXP));
					UpdatePlayerDatabaseInt(playerid, "level", GetPlayerData(playerid, P_LEVEL));
				    SendClientMessage(playerid, 0xCECECEFF, "Поздравляем! Ваш уровень повышен");
				    SetPlayerLevelInit(playerid);

					SCM(playerid, 0xFFFFFFFF, "{"SERVER_COLOR"}Вы успешно приобрели: {FFFFFF}Игровой уровень +20 {"SERVER_COLOR"}за {FFFFFF}250 [DCOINS]");
				}
				case 5:
				{
					if(QueryPlayerDonationBalance(playerid) < 500) return IntfDialogCallRemote(playerid, -1, DIALOG_STYLE_MSGBOX, "{FF6600}Ошибка", "{FFFFFF}Недостаточно DCOINS для покупки", "Назад", "");
					
					ProcessPlayerCredit(playerid, -500);

					SetPlayerData(playerid, P_EXP, 0);
				    AddPlayerData(playerid, P_LEVEL, +, 50);
					UpdatePlayerDatabaseInt(playerid, "exp", GetPlayerData(playerid, P_EXP));
					UpdatePlayerDatabaseInt(playerid, "level", GetPlayerData(playerid, P_LEVEL));
				    SendClientMessage(playerid, 0xCECECEFF, "Поздравляем! Ваш уровень повышен");
				    SetPlayerLevelInit(playerid);

					SCM(playerid, 0xFFFFFFFF, "{"SERVER_COLOR"}Вы успешно приобрели: {FFFFFF}Игровой уровень +50 {"SERVER_COLOR"}за {FFFFFF}500 [DCOINS]");
				}
			}
		}
		case DIALOG_DONATE_CHENOSTI:
		{
			if(!response) return 1;

			switch(listitem + 1)
			{
				case 1:
				{
					SetPVarInt(playerid, "BuyItems", 1);
					CEF_CREATE(playerid, 2, 4, "ItemStore", "[\"Предметы\",[\"Предметы\"],\
					[[\"/inventoryItems/288\",\"Ценная бумага\",\"3500\",0],\
					[\"/inventoryItems/361\",\"Домкрат\",\"200\",1],\
					[\"/inventoryItems/369\",\"Болгарка\",\"250\",2],\
					[\"/inventoryItems/44\",\"Рем комплект\",\"150\",3]],0]");
				}
				case 2:
				{
					SetPVarInt(playerid, "BuyCase", 1);
					CEF_CREATE(playerid, 2, 4, "ItemStore", "[\"Покупка кейсов и ключей\",[\"Кейсы\"],\
					[[\"/cases/0\",\"Форсаж\",\"150\",0],\
					[\"/cases/1\",\"Темные дела\",\"150\",1],\
					[\"/cases/2\",\"Велесова ночь\",\"150\",2],\
					[\"/cases/3\",\"Оперской\",\"150\",3],\
					[\"/cases/4\",\"Новогодний\",\"150\",4],\
					[\"/cases/5\",\"Черное золото\",\"150\",5],\
					[\"/cases/6\",\"Охотничий\",\"150\",6],\
					[\"/cases/7\",\"Египетская Сила\",\"150\",7],\
					[\"/cases/8\",\"Велесова ночь 2\",\"150\",8],\
					[\"/cases/9\",\"Рождественский экспресс\",\"150\",9],\
					[\"/cases/10\",\"Путь воина\",\"150\",10],\
					[\"/cases/11\",\"Пиратский\",\"150\",11],\
					[\"/cases/12\",\"Проклятие\",\"150\",12],\
					[\"/cases/13\",\"Зимняя сказка\",\"150\",13],\
					[\"/inventoryItems/259\",\"Ключ от кейса\",\"250\",14]],0]");
				}
				case 3:
				{
					 IntfDialogCallRemote
		             (
			             playerid, DIALOG_BUY_LVL, DIALOG_STYLE_TABLIST_HEADERS,
			             "{FFFFFF}Игровой уровень",
			             "Уровень\t Стоимость\n\
			             +1\t{FFFFFF} 25 [DCOINS]\n\
						 +5\t{FFFFFF} 75 [DCOINS]\n\
						 +10\t{FFFFFF} 170 [DCOINS]\n\
						 +20\t{FFFFFF} 250 [DCOINS]\n\
						 +50\t{FFFFFF} 500 [DCOINS]",
			             "Выбрать", "Закрыть"
	                );
				}
				case 4:
				{
					 IntfDialogCallRemote
		             (
			             playerid, DIALOG_BUY_SKIN, DIALOG_STYLE_TABLIST_HEADERS,
			             "{FFFFFF}Одежда",
			             "Название\t Стоимость\n\
			             Школьник №35\t{FFFFFF} 500 [DCOINS]\n\
						 Школьник №36\t{FFFFFF} 500 [DCOINS]\n\
						 Модник №115\t{FFFFFF} 300 [DCOINS]\n\
						 Адидас Черный №47\t{FFFFFF} 750 [DCOINS]\n\
						 Адидас белый №182\t{FFFFFF} 600 [DCOINS]\n\
						 Morgenshtern №15320\t{FFFFFF} 350 [DCOINS]\n\
						 FRESH №15358\t{FFFFFF} 350 [DCOINS]\n\
						 Bulkin №15357\t{FFFFFF} 350 [DCOINS]\n\
						 Паша Пэл №15407\t{FFFFFF} 400 [DCOINS]\n\
						 Супер Сус №15414\t{FFFFFF} 400 [DCOINS]\n\
						 Ляшов №15419\t{FFFFFF} 350 [DCOINS]\n\
						 Стэн Лютер №15420\t{FFFFFF} 350 [DCOINS]\n\
						 Slava Marlow №15421\t{FFFFFF} 350 [DCOINS]\n\
						 GRAND №15422\t{FFFFFF} 350 [DCOINS]\n\
						 TheAronPLAY №15434\t{FFFFFF} 350 [DCOINS]\n\
						 DESPAIR №15436\t{FFFFFF} 350 [DCOINS]\n\
						 Монстрик №15480\t{FFFFFF} 450 [DCOINS]\n\
						 ALMAZOV №15483\t{FFFFFF} 350 [DCOINS]\n\
						 Coffi Channel №15487\t{FFFFFF} 350 [DCOINS]\n\
						 Данилыч №15488\t{FFFFFF} 350 [DCOINS]\n\
						 DEMARTINI №15489\t{FFFFFF} 350 [DCOINS]\n\
						 Teddy Guevara №15490\t{FFFFFF} 350 [DCOINS]\n\
						 MATRIX №15491\t{FFFFFF} 350 [DCOINS]\n\
						 Skipper №15494\t{FFFFFF} 350 [DCOINS]\n\
						 СПЕКТОР №15495\t{FFFFFF} 350 [DCOINS]\n\
						 Toni Nite №15497\t{FFFFFF} 350 [DCOINS]\n\
						 Хасбик №15498\t{FFFFFF} 350 [DCOINS]\n\
						 Max Deep №15499\t{FFFFFF} 350 [DCOINS]\n\
						 SodaEffect №15500\t{FFFFFF} 350 [DCOINS]\n\
						 Bosow №15501\t{FFFFFF} 400 [DCOINS]\n\
						 Гонщик №15502\t{FFFFFF} 350 [DCOINS]\n\
						 Женщина №15505\t{FFFFFF} 350 [DCOINS]\n\
						 Дед мороз Supreme №15506\t{FFFFFF} 350 [DCOINS]\n\
						 Бустер №15528\t{FFFFFF} 350 [DCOINS]\n\
						 Disszari №15529\t{FFFFFF} 350 [DCOINS]\n\
						 Марк Грозный №15533\t{FFFFFF} 350 [DCOINS]\n\
						 Шейх №15535\t{FFFFFF} 350 [DCOINS]\n\
						 TaGs Play Theme №15536\t{FFFFFF} 350 [DCOINS]\n\
						 Уэ?нздей А?ддамс №15538\t{FFFFFF} 350 [DCOINS]\n\
						 XXXTentacion №15539\t{FFFFFF} 500 [DCOINS]\n\
						 Боярский №15543\t{FFFFFF} 350 [DCOINS]\n\
						 Антоха Реальные пацаны №15544\t{FFFFFF} 350 [DCOINS]\n\
						 Космонавт №15546\t{FFFFFF} 350 [DCOINS]\n\
						 Колян Реальные пацаны №15547\t{FFFFFF} 350 [DCOINS]\n\
						 Масхалат №15549\t{FFFFFF} 350 [DCOINS]",
			             "Выбрать", "Закрыть"
	                );
				}
				case 5:
				{
					SetPVarInt(playerid, "BuyDonateAcs", 1);
					player_acs_page[playerid] = 0;
                    SendAcsPage(playerid, 0);
				}
				case 6:
				{
					SetPVarInt(playerid, "BuyDonateCarAcs", 1);
					player_car_acs_page[playerid] = 0;
                    SendCarAcsPage(playerid, 0);
				}
				case 7:
				{
                    page_cars[playerid] = 1;
					ShowDialogDonatePerfect(playerid, 1, page_cars[playerid]);
				}
				case 8:
				{
					SetPVarInt(playerid, "BuyHomeAcs", 1);
				    player_decoration_page[playerid] = 0;
                    SendDecorationPage(playerid, 0);
				}
			}
		}
		case DIALOG_CREATE_DONATE_FINISH:
		{
			if(!response) return callcmd::createcoinsitem(playerid);
			
			SCM(playerid, COLOR_GREY, "Вы успешно создали предмет в "SERVER_DONATE" меню");

			new query[248];
			format(query, sizeof query, "INSERT INTO donate_items (type, name, item_id, price, count, indx) VALUES (%d, '%s', %d, %d, %d, %d)", 
			g_donate_create[playerid][DC_TYPE], g_donate_create[playerid][DC_NAME], g_donate_create[playerid][DC_ITEM_ID], g_donate_create[playerid][DC_PRICE], g_donate_create[playerid][DC_COUNT], g_donate_create[playerid][DC_INDX]);
			mysql_tquery(mysql, query, "", "");
		}
		case DIALOG_CREATE_DONATE_1:
		{
			if(!response) return 1;

			switch(listitem)
			{
				case 0: callcmd::createcoinsitem(playerid);
				case 1: // транспорт id 1
				{
					g_donate_create[playerid][DC_TYPE] = 1;
					IntfDialogCallRemote(playerid, DIALOG_CREATE_DONATE_2, DIALOG_STYLE_INPUT, "{FFCD00}Транспорт", "{FFFFFF}Введите id транспорта который хотите добавить", "Далее", "Назад");
				}
				case 2: // одежда id 2
				{
					g_donate_create[playerid][DC_TYPE] = 2;
					IntfDialogCallRemote(playerid, DIALOG_CREATE_DONATE_2, DIALOG_STYLE_INPUT, "{FFCD00}Одежда", "{FFFFFF}Введите id одежды который хотите добавить", "Далее", "Назад");
				}
				case 3: // аксессуар id 3
				{
					g_donate_create[playerid][DC_TYPE] = 3;
					IntfDialogCallRemote(playerid, DIALOG_CREATE_DONATE_2, DIALOG_STYLE_INPUT, "{FFCD00}Аксессуар", "{FFFFFF}Введите id аксессуара который хотите добавить", "Далее", "Назад");
				}
				case 4: // аксессуар id 5
				{
					g_donate_create[playerid][DC_TYPE] = 5;
					IntfDialogCallRemote(playerid, DIALOG_CREATE_DONATE_2, DIALOG_STYLE_INPUT, "{FFCD00}Предмет", "{FFFFFF}Введите id предмета который хотите добавить", "Далее", "Назад");
				}
			}
		}

		case DIALOG_CREATE_DONATE_2:
		{
			if(!response) return callcmd::createcoinsitem(playerid);

			if(strlen(inputtext) < 1 || !IsNumeric(inputtext)) 
			{	
				if(g_donate_create[playerid][DC_TYPE] == 1) IntfDialogCallRemote(playerid, DIALOG_CREATE_DONATE_2, DIALOG_STYLE_INPUT, "{FFCD00}Транспорт", "{FFFFFF}Введите id транспорта который хотите добавить\n\n{FF6600}Укажите корректное значение", "Далее", "Назад");
				if(g_donate_create[playerid][DC_TYPE] == 2) IntfDialogCallRemote(playerid, DIALOG_CREATE_DONATE_2, DIALOG_STYLE_INPUT, "{FFCD00}Одежда", "{FFFFFF}Введите id одежды который хотите добавить\n\n{FF6600}Укажите корректное значение", "Далее", "Назад");
				if(g_donate_create[playerid][DC_TYPE] == 3) IntfDialogCallRemote(playerid, DIALOG_CREATE_DONATE_2, DIALOG_STYLE_INPUT, "{FFCD00}Аксессуар", "{FFFFFF}Введите id аксессуара который хотите добавить\n\n{FF6600}Укажите корректное значение", "Далее", "Назад");
				if(g_donate_create[playerid][DC_TYPE] == 5) IntfDialogCallRemote(playerid, DIALOG_CREATE_DONATE_2, DIALOG_STYLE_INPUT, "{FFCD00}Предмет", "{FFFFFF}Введите id предмета который хотите добавить\n\n{FF6600}Укажите корректное значение", "Далее", "Назад");
				return 1;
			}

			if(g_donate_create[playerid][DC_TYPE] == 1)
			{
				IntfDialogCallRemote(playerid, DIALOG_CREATE_DONATE_3, DIALOG_STYLE_INPUT, "{FFCD00}Транспорт", "{FFFFFF}Введите название транспорта который хотите добавить", "Далее", "Назад");
			}
			if(g_donate_create[playerid][DC_TYPE] == 2)
			{
				IntfDialogCallRemote(playerid, DIALOG_CREATE_DONATE_3, DIALOG_STYLE_INPUT, "{FFCD00}Одежда", "{FFFFFF}Введите название одежды который хотите добавить", "Далее", "Назад");
			}
			if(g_donate_create[playerid][DC_TYPE] == 3)
			{
				IntfDialogCallRemote(playerid, DIALOG_CREATE_DONATE_3, DIALOG_STYLE_INPUT, "{FFCD00}Аксессуар", "{FFFFFF}Введите название аксессуар который хотите добавить", "Далее", "Назад");
			}
			if(g_donate_create[playerid][DC_TYPE] == 5)
			{
				IntfDialogCallRemote(playerid, DIALOG_CREATE_DONATE_3, DIALOG_STYLE_INPUT, "{FFCD00}Предмет", "{FFFFFF}Введите название предмета который хотите добавить", "Далее", "Назад");
			}
			g_donate_create[playerid][DC_ITEM_ID] = strval(inputtext);
		}

		case DIALOG_CREATE_DONATE_5:
		{
			if(!response) return callcmd::createcoinsitem(playerid);

			if(strlen(inputtext) < 1 || !IsNumeric(inputtext)) 
			{	
				if(g_donate_create[playerid][DC_TYPE] == 1) IntfDialogCallRemote(playerid, DIALOG_CREATE_DONATE_5, DIALOG_STYLE_INPUT, "{FFCD00}Транспорт", "{FFFFFF}Введите стоимость транспорта который хотите добавить\n\n{FF6600}Укажите корректное значение", "Далее", "Назад");
				if(g_donate_create[playerid][DC_TYPE] == 2) IntfDialogCallRemote(playerid, DIALOG_CREATE_DONATE_5, DIALOG_STYLE_INPUT, "{FFCD00}Одежда", "{FFFFFF}Введите стоимость одежды который хотите добавить\n\n{FF6600}Укажите корректное значение", "Далее", "Назад");
				if(g_donate_create[playerid][DC_TYPE] == 3) IntfDialogCallRemote(playerid, DIALOG_CREATE_DONATE_5, DIALOG_STYLE_INPUT, "{FFCD00}Аксессуар", "{FFFFFF}Введите стоимость аксессуара который хотите добавить\n\n{FF6600}Укажите корректное значение", "Далее", "Назад");
				if(g_donate_create[playerid][DC_TYPE] == 5) IntfDialogCallRemote(playerid, DIALOG_CREATE_DONATE_5, DIALOG_STYLE_INPUT, "{FFCD00}Предмет", "{FFFFFF}Введите стоимость предмета который хотите добавить\n\n{FF6600}Укажите корректное значение", "Далее", "Назад");
				return 1;
			}

			g_donate_create[playerid][DC_PRICE] = strval(inputtext);

			if(g_donate_create[playerid][DC_TYPE] == 1)
			{
				CreateDonateItems(playerid);
			}
			if(g_donate_create[playerid][DC_TYPE] == 2)
			{
				CreateDonateItems(playerid);
			}
			if(g_donate_create[playerid][DC_TYPE] == 3)
			{
				IntfDialogCallRemote
				(
					playerid, DIALOG_CREATE_DONATE_4, DIALOG_STYLE_INPUT, 
					"{FFCD00}Аксессуар", 
					"{FFFFFF}Введите тип аксессуара который хотите добавить\n\n\
					Список типов аксессуаров:\n\
					Тип 0 - Очки\n\
					Тип 1 - Бандана\n\
					Тип 2 - Маска\n\
					Тип 3 - Берет\n\
					Тип 4 - шляпа (Шапка, Кепка)\n\
					Тип 5 - Сумка\n\
					Тип 6 - Ремень\n\
					Тип 7 - Украшение на руку\n\
					Тип 8 - Рюкзак\n\
					Тип 9 - Украшение на шею\n\
					Тип 10 - Плащ\n\
					Тип 11 - Бронижелет\n\
					Тип 12 - Посох\n\
					Тип 13 - Крылья\n\
					Тип 14 - Украшение на транспорт\n\
					Тип 15 - Украшение на транспорт\n\
					Тип 16 - Украшение на транспорт\n\
					Тип 17 - Украшение на транспорт\n\
					Тип 18 - Скейтборд\n\
					Тип 19 - украшение на левое плечо\n\
					Тип 20 - Украшение на транспорт\n\
					Тип 21 - Украшение на транспорт\n\
					Тип 22 - Аксессуар на спину", 
					"Далее", "Назад"
				);
			}
			if(g_donate_create[playerid][DC_TYPE] == 5)
			{
				IntfDialogCallRemote(playerid, DIALOG_CREATE_DONATE_4, DIALOG_STYLE_INPUT, "{FFCD00}Предмет", "{FFFFFF}Введите количество предмета который хотите добавить", "Далее", "Назад");
			}
		}

		case DIALOG_CREATE_DONATE_3:
		{
			if(!response) return callcmd::createcoinsitem(playerid);

			if(strlen(inputtext) > 48 || 5 > strlen(inputtext))
			{	
				if(g_donate_create[playerid][DC_TYPE] == 1) IntfDialogCallRemote(playerid, DIALOG_CREATE_DONATE_3, DIALOG_STYLE_INPUT, "{FFCD00}Транспорт", "{FFFFFF}Введите название транспорта который хотите добавить\n\n{FF6600}Укажите не меньше 5-ти и не больше 48-ми символов", "Далее", "Назад");
				if(g_donate_create[playerid][DC_TYPE] == 2) IntfDialogCallRemote(playerid, DIALOG_CREATE_DONATE_3, DIALOG_STYLE_INPUT, "{FFCD00}Одежда", "{FFFFFF}Введите название одежды который хотите добавить\n\n{FF6600}Укажите не меньше 5-ти и не больше 48-ми символов", "Далее", "Назад");
				if(g_donate_create[playerid][DC_TYPE] == 3) IntfDialogCallRemote(playerid, DIALOG_CREATE_DONATE_3, DIALOG_STYLE_INPUT, "{FFCD00}Аксессуар", "{FFFFFF}Введите название аксессуара который хотите добавить\n\n{FF6600}Укажите не меньше 5-ти и не больше 48-ми символов", "Далее", "Назад");
				if(g_donate_create[playerid][DC_TYPE] == 5) IntfDialogCallRemote(playerid, DIALOG_CREATE_DONATE_3, DIALOG_STYLE_INPUT, "{FFCD00}Предмет", "{FFFFFF}Введите название предмета который хотите добавить\n\n{FF6600}Укажите не меньше 5-ти и не больше 48-ми символов", "Далее", "Назад");
				return 1;
			}

			format(g_donate_create[playerid][DC_NAME], 48, "%s", inputtext);

			if(g_donate_create[playerid][DC_TYPE] == 1) IntfDialogCallRemote(playerid, DIALOG_CREATE_DONATE_5, DIALOG_STYLE_INPUT, "{FFCD00}Транспорт", "{FFFFFF}Введите стоимость транспорта который хотите добавить", "Далее", "Назад");
			if(g_donate_create[playerid][DC_TYPE] == 2) IntfDialogCallRemote(playerid, DIALOG_CREATE_DONATE_5, DIALOG_STYLE_INPUT, "{FFCD00}Одежда", "{FFFFFF}Введите стоимость одежды который хотите добавить", "Далее", "Назад");
			if(g_donate_create[playerid][DC_TYPE] == 3) IntfDialogCallRemote(playerid, DIALOG_CREATE_DONATE_5, DIALOG_STYLE_INPUT, "{FFCD00}Аксессуар", "{FFFFFF}Введите стоимость аксессуара который хотите добавить", "Далее", "Назад");
			if(g_donate_create[playerid][DC_TYPE] == 5) IntfDialogCallRemote(playerid, DIALOG_CREATE_DONATE_5, DIALOG_STYLE_INPUT, "{FFCD00}Предмет", "{FFFFFF}Введите стоимость предмета который хотите добавить", "Далее", "Назад");

		}

		case DIALOG_CREATE_DONATE_4:
		{
			if(!response) return callcmd::createcoinsitem(playerid);

			if(strlen(inputtext) < 1 || !IsNumeric(inputtext)) 
			{
				if(g_donate_create[playerid][DC_TYPE] == 3) 
					IntfDialogCallRemote
					(
						playerid, DIALOG_CREATE_DONATE_4, DIALOG_STYLE_INPUT, 
						"{FFCD00}Аксессуар", 
						"{FFFFFF}Введите тип аксессуара который хотите добавить\n\n\
						Список типов аксессуара:\n\
						Тип 0 - Очки\n\
						Тип 1 - Бандана\n\
						Тип 2 - Маска\n\
						Тип 3 - Берет\n\
						Тип 4 - шляпа (Шапка, Кепка)\n\
						Тип 5 - Сумка\n\
						Тип 6 - Ремень\n\
						Тип 7 - Украшение на руку\n\
						Тип 8 - Рюкзак\n\
						Тип 9 - Украшение на шею\n\
						Тип 10 - Плащ\n\
						Тип 11 - Бронижелет\n\
						Тип 12 - Посох\n\
						Тип 13 - Крылья\n\
						Тип 14 - Украшение на транспорт\n\
						Тип 15 - Украшение на транспорт\n\
						Тип 16 - Украшение на транспорт\n\
						Тип 17 - Украшение на транспорт\n\
						Тип 18 - Скейтборд\n\
						Тип 19 - украшение на левое плечо\n\
						Тип 20 - Украшение на транспорт\n\
						Тип 21 - Украшение на транспорт\n\
						Тип 22 - Аксессуар на спину\n\n\
						{FF6600}Укажите корректное значение", 
						"Далее", "Назад"
					);

				if(g_donate_create[playerid][DC_TYPE] == 5) IntfDialogCallRemote(playerid, DIALOG_CREATE_DONATE_4, DIALOG_STYLE_INPUT, "{FFCD00}Предмет", "{FFFFFF}Введите количество предмета который хотите добавить\n\n{FF6600}Укажите корректное значение", "Далее", "Назад");
				return 1;	
			}

			if(g_donate_create[playerid][DC_TYPE] == 3)
			{
				if(strval(inputtext) > 22)
				{
					IntfDialogCallRemote
					(
						playerid, DIALOG_CREATE_DONATE_4, DIALOG_STYLE_INPUT, 
						"{FFCD00}Аксессуар", 
						"{FFFFFF}Введите тип аксессуара который хотите добавить\n\n\
						Список типов аксессуаров:\n\
						Тип 0 - Очки\n\
						Тип 1 - Бандана\n\
						Тип 2 - Маска\n\
						Тип 3 - Берет\n\
						Тип 4 - шляпа (Шапка, Кепка)\n\
						Тип 5 - Сумка\n\
						Тип 6 - Ремень\n\
						Тип 7 - Украшение на руку\n\
						Тип 8 - Рюкзак\n\
						Тип 9 - Украшение на шею\n\
						Тип 10 - Плащ\n\
						Тип 11 - Бронижелет\n\
						Тип 12 - Посох\n\
						Тип 13 - Крылья\n\
						Тип 14 - Украшение на транспорт\n\
						Тип 15 - Украшение на транспорт\n\
						Тип 16 - Украшение на транспорт\n\
						Тип 17 - Украшение на транспорт\n\
						Тип 18 - Скейтборд\n\
						Тип 19 - украшение на левое плечо\n\
						Тип 20 - Украшение на транспорт\n\
						Тип 21 - Украшение на транспорт\n\
						Тип 22 - Аксессуар на спину\n\n\
						{FF6600}Данного типа не существует", 
						"Далее", "Назад"
					);
					return 1;
				}

				g_donate_create[playerid][DC_INDX] = strval(inputtext);
				CreateDonateItems(playerid);
			}
			if(g_donate_create[playerid][DC_TYPE] == 5)
			{
				if(strval(inputtext) > 2000000000)
				{
					IntfDialogCallRemote(playerid, DIALOG_CREATE_DONATE_4, DIALOG_STYLE_INPUT, "{FFCD00}Предмет", "{FFFFFF}Введите количество предмета который хотите добавить\n\n{FF6600}Нельзя указать количество больше 1.999.999.999 шт.", "Далее", "Назад");
					return 1;
				}
				g_donate_create[playerid][DC_COUNT] = strval(inputtext);
				CreateDonateItems(playerid);
			}

		}
		case DIALOG_CAR_LIST_NOTARY:
		{
			if(!response) return 1;

			if((GetPlayerOwnableCars(g_player_notary_offer_id[playerid]) + 1) > GetPlayerCarSlots(g_player_notary_offer_id[playerid]))
				return SendClientMessage(playerid, 0xeb622aFF, "У одной из сторон достигнут лимит ТС");

			new idx = GetPlayerListitemValue(playerid, listitem);

			new vehicleid = INVALID_VEHICLE_ID;

			for(new i = 0; i < MAX_VEHICLES; i++)
			{
				if(GetVehicleData(i, V_ACTION_TYPE) == VEHICLE_ACTION_TYPE_OWNABLE_CAR)
				{
					new iddx = GetVehicleData(i, V_ACTION_ID);
					if(GetOwnableCarData(iddx,OC_SQL_ID) == idx)
					{
						vehicleid = i;
					}
				}
			}

			if(vehicleid == INVALID_VEHICLE_ID)
				return SendClientMessage(playerid, 0xFF6600FF, "Данный транспорт не загружен на сервер");

			g_player_notary_item_id[playerid] = vehicleid;

			new model_id = GetVehicleData(vehicleid, V_MODELID);

			new fmt_text[248];
			format(fmt_text, sizeof fmt_text, "interface('Trade').updateData('{\"player1\": {\"item\": 2,\"itemName\": \"Транспорт %s \",\"itemPrice\": %d,\"itemSurcharge\": 0,\"state\": 0,\"commission\": 0}}')",GetVehicleInfo(model_id, VI_NAME), GetVehicleInfo(model_id, VI_PRICE));
			CEF_CREATE(playerid, 1, 2, fmt_text);

			format(fmt_text, sizeof fmt_text, "interface('Trade').updateData('{\"player2\": {\"item\": 2,\"itemName\": \"Транспорт %s \",\"itemPrice\": %d,\"itemSurcharge\": 0,\"state\": 0,\"commission\": 0}}')",GetVehicleInfo(model_id, VI_NAME), GetVehicleInfo(model_id, VI_PRICE));
			CEF_CREATE(g_player_notary_offer_id[playerid], 1, 2, fmt_text);

		}
		case DIALOG_IMPROVEMENTS_BUY:
		{
			if(!response) return 1;
			if(!VerifyIntString(QueryPlayerBalance(playerid), 50000)) return GameText(playerid, "~r~Недостаточно~n~средств", 3000, 2);
		    ModifyCashBalance(playerid, -50000,"покупка 1 улучшения огорода", true,true);
		    new garden = GetPVarInt(playerid,"garden_id");
	        new query[144];

		    gardenobj_1[garden] = CreateDynamicObject(16560, GetGardenData(garden, G_POS_X) + -2.67, GetGardenData(garden, G_POS_Y) + -0.009998, GetGardenData(garden, G_POS_Z) + 0.124374,0.00000, 0.00000, 0.0);
		    gardenobj_1_label[garden] = CreateDynamic3DTextLabel("{FFA500}Бочка для воды\n{FFFFFF}Заполнено: {FFA500}0/150 л.", -1, GetGardenData(garden, G_POS_X) + -2.67, GetGardenData(garden, G_POS_Y) + -0.009998, (GetGardenData(garden, G_POS_Z) + 0.124374) + 1.5, 2.0);
		    gardenobj_1_woter[garden] = 0;
		    SetGardenData(garden, G_IMPROVEMENTS, 1);

            SCM(playerid, -1, "{FF8000}Вы приобрели улучшение {ffffff}\"Бочка для воды\" {FF8000}за {ffffff}50.000 руб.");

	        format(query, sizeof query, "UPDATE gardens SET improvements=%d WHERE id=%d", GetGardenData(garden, G_IMPROVEMENTS), GetGardenData(garden, G_SQL_ID));
	        mysql_query(mysql, query, false);

	        format(query, sizeof query, "interface('Gardens').setBoughtUpgrades(%d)", GetGardenData(garden, G_IMPROVEMENTS));
	        CEF_CREATE(playerid, 1, 2, query);

		}
		case DIALOG_IMPROVEMENTS_BUY2:
		{
			if(!response) return 1;
			if(!VerifyIntString(QueryPlayerBalance(playerid), 150000)) return GameText(playerid, "~r~Недостаточно~n~средств", 3000, 2);
		    ModifyCashBalance(playerid, -150000,"покупка 2 улучшения огорода", true,true);
		    new garden = GetPVarInt(playerid,"garden_id");
	        new query[144];

		    gardenobj_2[garden] = CreateDynamicObject(16564, GetGardenData(garden, G_POS_X) + -0.034111, GetGardenData(garden, G_POS_Y) + -0.00752, GetGardenData(garden, G_POS_Z) + 0.017313,0.00000, 0.00000, 0.0);

		    SetGardenData(garden, G_IMPROVEMENTS, 2);

			SCM(playerid, -1, "{FF8000}Вы приобрели улучшение {ffffff}\"Ультрафиолетовая лампа\" {FF8000}за {ffffff}150.000 руб.");

	        format(query, sizeof query, "UPDATE gardens SET improvements=%d WHERE id=%d", GetGardenData(garden, G_IMPROVEMENTS), GetGardenData(garden, G_SQL_ID));
	        mysql_query(mysql, query, false);

	        format(query, sizeof query, "interface('Gardens').setBoughtUpgrades(%d)", GetGardenData(garden, G_IMPROVEMENTS));
	        CEF_CREATE(playerid, 1, 2, query);

		}
		case DIALOG_IMPROVEMENTS_BUY3:
		{
			if(!response) return 1;
			if(!VerifyIntString(QueryPlayerBalance(playerid), 200000)) return GameText(playerid, "~r~Недостаточно~n~средств", 3000, 2);
		    ModifyCashBalance(playerid, -200000,"покупка 3 улучшения огорода", true,true);

		    new garden = GetPVarInt(playerid,"garden_id");
	        new query[144];

		    DestroyObject(gardendver[garden]);
		    DestroyDynamicObject(gardenobj_1[garden]);
		    DestroyDynamic3DTextLabel(gardenobj_1_label[garden]);
		    DestroyObject(gardenobj[garden]);
		    DestroyDynamic3DTextLabel(gardendvlabel[garden]);
		    DestroyDynamicArea(array_gardens_data[garden]);
		    array_gardens_data[garden] = 0;

		    for(new i = 0; i < 10; i ++)
		    {
			   DestroyDynamic3DTextLabel(gardendyamkalab[garden][i]);
			   DestroyDynamicArea(array_gardens_yamka[garden][i]);
			   array_gardens_yamka[garden][i] = 0;
		    }
		    for(new i = 0; i < 14; i ++)
		    {
			   gardendyamkalab[garden][i] = CreateDynamic3DTextLabel("{FFA500}Свободная ямка\n{FFFFFF}Требуется обработка", -1, GetGardenData(garden, G_POS_X) + GardenGryadka_2[i][0], GetGardenData(garden, G_POS_Y) + GardenGryadka_2[i][1], GetGardenData(garden, G_POS_Z) + GardenGryadka_2[i][2] + 1, 2.0);
               array_gardens_yamka_2[garden][i] = CreateDynamicSphere(GetGardenData(garden, G_POS_X) + GardenGryadka_2[i][0], GetGardenData(garden, G_POS_Y) + GardenGryadka_2[i][1], GetGardenData(garden, G_POS_Z) + GardenGryadka_2[i][2] + 1, 1.0, -1, -1);
			}

		    gardenobj_1[garden] = CreateDynamicObject(16560, GetGardenData(garden, G_POS_X) + -3.39779, GetGardenData(garden, G_POS_Y) + 0.025699, GetGardenData(garden, G_POS_Z) + 0.025609,0.00000, 0.00000, 0.0);
		    gardenobj_1_label[garden] = CreateDynamic3DTextLabel("{FFA500}Бочка для воды\n{FFFFFF}Заполнено: {FFA500}0/150 л.", -1, GetGardenData(garden, G_POS_X) + -3.39779, GetGardenData(garden, G_POS_Y) + 0.025699, (GetGardenData(garden, G_POS_Z) + 0.025609) + 1.5, 2.0);
		    gardenobj_1_woter[garden] = 0;

		    gardendvlabel[garden] = CreateDynamic3DTextLabel("{FFA500}Двери теплицы", -1, GetGardenData(garden, G_POS_X) + 3.75328, GetGardenData(garden, G_POS_Y) + 0.393359, GetGardenData(garden, G_POS_Z) + 1, 2.0);
		    gardendver[garden] = CreateObject(10938, GetGardenData(garden, G_POS_X) + 3.75328, GetGardenData(garden, G_POS_Y) + 0.393359, GetGardenData(garden, G_POS_Z),   0.00000, 0.00000, 0.00000);
		    gardenobj[garden] = CreateObject(10933, GetGardenData(garden, G_POS_X), GetGardenData(garden, G_POS_Y), GetGardenData(garden, G_POS_Z),   0.00000, 0.00000, 0.0);
		    array_gardens_data_2[garden] = CreateDynamicSphere(GetGardenData(garden, G_POS_X) + 3.75328, GetGardenData(garden, G_POS_Y) + 0.393359, GetGardenData(garden, G_POS_Z) + 0.00000, 1.5, -1, -1);

		    SetGardenData(garden, G_IMPROVEMENTS, 3);

			SCM(playerid, -1, "{FF8000}Вы приобрели улучшение {ffffff}\"Средняя теплица\" {FF8000}за {ffffff}200.000 руб.");

	        format(query, sizeof query, "UPDATE gardens SET improvements=%d WHERE id=%d", GetGardenData(garden, G_IMPROVEMENTS), GetGardenData(garden, G_SQL_ID));
	        mysql_query(mysql, query, false);

	        format(query, sizeof query, "interface('Gardens').setBoughtUpgrades(%d)", GetGardenData(garden, G_IMPROVEMENTS));
	        CEF_CREATE(playerid, 1, 2, query);

		}
		case DIALOG_IMPROVEMENTS_BUY4:
		{
			if(!response) return 1;
			if(!VerifyIntString(QueryPlayerBalance(playerid), 300000)) return GameText(playerid, "~r~Недостаточно~n~средств", 3000, 2);

		    ModifyCashBalance(playerid, -300000,"покупка 4 улучшения огорода", true,true);

		    new garden = GetPVarInt(playerid,"garden_id");
	        new query[144];

		    DestroyDynamicObject(gardenobj_1[garden]);
		    DestroyDynamic3DTextLabel(gardenobj_1_label[garden]);

		    DestroyDynamicObject(gardenobj_2[garden]);
		    DestroyObject(gardendver[garden]);
		    DestroyObject(gardenobj[garden]);
		    DestroyDynamic3DTextLabel(gardendvlabel[garden]);
		    DestroyDynamicArea(array_gardens_data_2[garden]);
		    array_gardens_data_2[garden] = 0;

		    for(new i = 0; i < 14; i ++)
		    {
			    DestroyDynamic3DTextLabel(gardendyamkalab[garden][i]);
			    DestroyDynamicArea(array_gardens_yamka_2[garden][i]);
			    array_gardens_yamka_2[garden][i] = 0;
		    }
		    for(new i = 0; i < 20; i ++)
		    {
			    gardendyamkalab[garden][i] = CreateDynamic3DTextLabel("{FFA500}Свободная ямка\n{FFFFFF}Требуется обработка", -1, GetGardenData(garden, G_POS_X) + GardenGryadka_3[i][0], GetGardenData(garden, G_POS_Y) + GardenGryadka_3[i][1], GetGardenData(garden, G_POS_Z) + GardenGryadka_3[i][2] + 1, 2.0);
                array_gardens_yamka_3[garden][i] = CreateDynamicSphere(GetGardenData(garden, G_POS_X) + GardenGryadka_3[i][0], GetGardenData(garden, G_POS_Y) + GardenGryadka_3[i][1], GetGardenData(garden, G_POS_Z) + GardenGryadka_3[i][2] + 1, 1.0, -1, -1);
			}

		    gardenobj_1[garden] = CreateDynamicObject(16560, GetGardenData(garden, G_POS_X) + -5.07046, GetGardenData(garden, G_POS_Y) + 0.075143, GetGardenData(garden, G_POS_Z) + 0.036848,0.00000, 0.00000, 0.0);
		    gardenobj_1_label[garden] = CreateDynamic3DTextLabel("{FFA500}Бочка для воды\n{FFFFFF}Заполнено: {FFA500}0/150 л.", -1, GetGardenData(garden, G_POS_X) + -5.07046, GetGardenData(garden, G_POS_Y) + 0.075143, (GetGardenData(garden, G_POS_Z) + 0.036848) + 1.5, 2.0);
		    gardenobj_1_woter[garden] = 0;

		    gardenobj_2[garden] = CreateDynamicObject(16564, GetGardenData(garden, G_POS_X) + -0.434392, GetGardenData(garden, G_POS_Y) + -0.054589, GetGardenData(garden, G_POS_Z) + 0.461218,0.00000, 0.00000, 0.0);
		    gardendvlabel[garden] = CreateDynamic3DTextLabel("{FFA500}Двери теплицы", -1, GetGardenData(garden, G_POS_X) + 2.20977, GetGardenData(garden, G_POS_Y) + -2.19371, GetGardenData(garden, G_POS_Z) + 1, 2.0);
		    gardendver[garden] = CreateObject(16060, GetGardenData(garden, G_POS_X) + 2.20977, GetGardenData(garden, G_POS_Y) + -2.19371, GetGardenData(garden, G_POS_Z),   0.00000, 0.00000, 0.00000);
		    gardenobj[garden] = CreateObject(16042, GetGardenData(garden, G_POS_X), GetGardenData(garden, G_POS_Y), GetGardenData(garden, G_POS_Z),   0.00000, 0.00000, 0.0);
		    array_gardens_data_3[garden] = CreateDynamicSphere(GetGardenData(garden, G_POS_X) + 2.20977, GetGardenData(garden, G_POS_Y) + -2.19371, GetGardenData(garden, G_POS_Z) + 0.00000, 1.5, -1, -1);

		    SetGardenData(garden, G_IMPROVEMENTS, 4);

			SCM(playerid, -1, "{FF8000}Вы приобрели улучшение {ffffff}\"Большая теплица\" {FF8000}за {ffffff}300.000 руб.");

	        format(query, sizeof query, "UPDATE gardens SET improvements=%d WHERE id=%d", GetGardenData(garden, G_IMPROVEMENTS), GetGardenData(garden, G_SQL_ID));
	        mysql_query(mysql, query, false);

	        format(query, sizeof query, "interface('Gardens').setBoughtUpgrades(%d)", GetGardenData(garden, G_IMPROVEMENTS));
	        CEF_CREATE(playerid, 1, 2, query);

		}
		case DIALOG_BIZ_LIST_NOTARY:
		{
			if(!response) return 1;

			if((GetPlayerOwnableBiz(g_player_notary_offer_id[playerid]) + 1) > GetPlayerBizSlots(g_player_notary_offer_id[playerid])) 
				return SCM(playerid, 0xeb622aFF, "У одной из сторон достигнут лимит бизнесов");

			new idx = GetPlayerListitemValue(playerid, listitem) + 1;

			g_player_notary_item_id[playerid] = idx;

			new fmt_text[248];
			format(fmt_text, sizeof fmt_text, "interface('Trade').updateData('{\"player1\": {\"item\": 1,\"itemName\": \"Бизнес %s №%d\",\"itemPrice\": %d,\"itemSurcharge\": 0,\"state\": 0,\"commission\": 0}}')",GetBusinessData(idx, B_NAME), idx, GetBusinessData(idx, B_PRICE));
			CEF_CREATE(playerid, 1, 2, fmt_text);
			
			format(fmt_text, sizeof fmt_text, "interface('Trade').updateData('{\"player2\": {\"item\": 1,\"itemName\": \"Бизнес %s №%d\",\"itemPrice\": %d,\"itemSurcharge\": 0,\"state\": 0,\"commission\": 0}}')",GetBusinessData(idx, B_NAME), idx, GetBusinessData(idx, B_PRICE));
			CEF_CREATE(g_player_notary_offer_id[playerid], 1, 2, fmt_text);
		}
		case DIALOG_GARAGE_LIST_NOTARY:
		{
			if(!response) return 1;

			if(GetPlayerOwnableGarage(g_player_notary_offer_id[playerid]) + 1 > GetPlayerGarageSlots(g_player_notary_offer_id[playerid])) 
				return SCM(playerid, 0xeb622aFF, "У одной из сторон достигнут лимит гаражей");

			new idx = GetPlayerListitemValue(playerid, listitem) + 1;

			g_player_notary_item_id[playerid] = idx;

			new fmt_text[248];
			format(fmt_text, sizeof fmt_text, "interface('Trade').updateData('{\"player1\": {\"item\": 0,\"itemName\": \"Гараж №%d\",\"itemPrice\": %d,\"itemSurcharge\": 0,\"state\": 0,\"commission\": 0}}')", idx, GetGarageData(idx, G_PRICE));
			CEF_CREATE(playerid, 1, 2, fmt_text);
			
			format(fmt_text, sizeof fmt_text, "interface('Trade').updateData('{\"player2\": {\"item\": 0,\"itemName\": \"Гараж №%d\",\"itemPrice\": %d,\"itemSurcharge\": 0,\"state\": 0,\"commission\": 0}}')", idx, GetGarageData(idx, G_PRICE));
			CEF_CREATE(g_player_notary_offer_id[playerid], 1, 2, fmt_text);

		}
		case DIALOG_KIOSK_LIST_NOTARY:
		{
			if(!response) return 1;

			if((GetPlayerOwnableKiosk(g_player_notary_offer_id[playerid]) + 1) > GetPlayerKioskSlots(g_player_notary_offer_id[playerid])) 
				return SCM(playerid, 0xeb622aFF, "У одной из сторон достигнут лимит киосков");

			new idx = GetPlayerListitemValue(playerid, listitem) + 1;

			g_player_notary_item_id[playerid] = idx;

			new fmt_text[248];
			format(fmt_text, sizeof fmt_text, "interface('Trade').updateData('{\"player1\": {\"item\": 8,\"itemName\": \"Киоск: %s №%d\",\"itemPrice\": %d,\"itemSurcharge\": 0,\"state\": 0,\"commission\": 0}}')", GetKioskData(idx, K_NAME), idx, GetKioskData(idx, K_PRICE));
			CEF_CREATE(playerid, 1, 2, fmt_text);
			
			format(fmt_text, sizeof fmt_text, "interface('Trade').updateData('{\"player2\": {\"item\": 8,\"itemName\": \"Киоск: %s №%d\",\"itemPrice\": %d,\"itemSurcharge\": 0,\"state\": 0,\"commission\": 0}}')", GetKioskData(idx, K_NAME), idx, GetKioskData(idx, K_PRICE));
			CEF_CREATE(g_player_notary_offer_id[playerid], 1, 2, fmt_text);
		}
		case DIALOG_GARDEN_LIST_NOTARY:
		{
			if(!response) return 1;

			if(GetPlayerOwnableGarden(g_player_notary_offer_id[playerid]) + 1 > GetPlayerGardenSlots(g_player_notary_offer_id[playerid])) 
				return SCM(playerid, 0xeb622aFF, "У одной из сторон достигнут лимит огородов");

			new idx = GetPlayerListitemValue(playerid, listitem);

			g_player_notary_item_id[playerid] = idx;

			new fmt_text[248];
			format(fmt_text, sizeof fmt_text, "interface('Trade').updateData('{\"player1\": {\"item\": 7,\"itemName\": \"Огород: №%d\",\"itemPrice\": %d,\"itemSurcharge\": 0,\"state\": 0,\"commission\": 0}}')",idx, GetGardenData(idx, G_PRICE));
			CEF_CREATE(playerid, 1, 2, fmt_text);
			
			format(fmt_text, sizeof fmt_text, "interface('Trade').updateData('{\"player2\": {\"item\": 7,\"itemName\": \"Огород: №%d\",\"itemPrice\": %d,\"itemSurcharge\": 0,\"state\": 0,\"commission\": 0}}')",idx, GetGardenData(idx, G_PRICE));
			CEF_CREATE(g_player_notary_offer_id[playerid], 1, 2, fmt_text);
		}
		case DIALOG_HOME_LIST_NOTARY:
		{
			if(!response) return 1;

			if((GetPlayerOwnableHouse(g_player_notary_offer_id[playerid]) + 1) > GetPlayerHouseSlots(g_player_notary_offer_id[playerid])) 
				return SCM(playerid, 0xeb622aFF, "У одной из сторон достигнут лимит домов");

			new idx = GetPlayerListitemValue(playerid, listitem) + 1;

			g_player_notary_item_id[playerid] = idx;

			new fmt_text[248];
			format(fmt_text, sizeof fmt_text, "interface('Trade').updateData('{\"player1\": {\"item\": 3,\"itemName\": \"Дом №%d\",\"itemPrice\": %d,\"itemSurcharge\": 0,\"state\": 0,\"commission\": 0}}')", idx, GetHouseData(idx, H_PRICE));
			CEF_CREATE(playerid, 1, 2, fmt_text);
			
			format(fmt_text, sizeof fmt_text, "interface('Trade').updateData('{\"player2\": {\"item\": 3,\"itemName\": \"Дом №%d\",\"itemPrice\": %d,\"itemSurcharge\": 0,\"state\": 0,\"commission\": 0}}')", idx, GetHouseData(idx, H_PRICE));
			CEF_CREATE(g_player_notary_offer_id[playerid], 1, 2, fmt_text);
		}
		case DIALOG_BET_SVALKA:
		{
			if(!response) return 1;

			if(g_svalka_playerid_type[playerid] == 1) 
				if((GetPlayerOwnableCars(playerid) + 1) > GetPlayerCarSlots(playerid)) return SendClientMessage(playerid, 0x3399FFFF, "Все слоты для транспорта заняты.");

			if(g_svalka_playerid_type[playerid] == 2)
				if(GetInventorySlots(playerid) == -1) return SendClientMessage(playerid, 0x3399FFFF, "В вашем инвентаре нет свободного места.");

			OnPlayerOpenDumpInterface(playerid, g_svalka_playerid[playerid], g_svalka_playerid_type[playerid]);
		}
		case DIALOG_TK_JMENU:
		{
			if(!response) return 1;

			switch(listitem + 1)
			{
				case 1: 
				{
					string_dialog[0] = EOS;
					format
					(
						string_dialog, sizeof string_dialog, 
						"{ffffff}Наименование: {ffd31d}%s{ffffff}\n\
						Владелец: {fbdf6a}%s{ffffff}\n\
						Рейтинг: {fbdf6a}0{ffffff} ед.\n\n\
						- Критерии по рейтингу для вступления: {cefb6a}отсутствуют{ffffff}\n\
						- Критерии по рейтингу для увольнения: {f06868}отсутствуют{ffffff}\n\
						- Зарплата заместителей: {cefb6a}отсутствуют",
						GetBusinessData(GetPlayerData(playerid, P_TK_JOB), B_NAME), 
						GetBusinessData(GetPlayerData(playerid, P_TK_JOB), B_OWNER_NAME)
					);

					IntfDialogCallRemote(playerid, DIALOG_TK_JMENU_1, DIALOG_STYLE_MSGBOX, "{FFCD00}Информация о компании", string_dialog,"Назад", "");
				}
				case 2:
				{
					IntfDialogCallRemote
					(
						playerid, DIALOG_TK_JMENU_TUTORIAL, DIALOG_STYLE_LIST, 
						"{FFCD00}Руководство по работе", 
						"{fbdf6a}1.{ffffff} Что такое транспортная компания\n\
						{fbdf6a}2.{ffffff} Как работать в транспортной компании\n\
						{fbdf6a}3.{ffffff} Информация о навыке дальнобойщика\n\
						{fbdf6a}4.{ffffff} Понятия \'рейтинг\' и \'номинация\'\n\
						{fbdf6a}5.{ffffff} Возможные штрафы за нарушения\n",
						"Далее", "Назад"
					);
				}
				case 3:
				{
					string_dialog[0] = EOS;

					new fmt_text[135];

					string_dialog = "{ffffff}Имя\t{ffffff}Должность\t{ffffff}Состояние\t{ffffff}Рейтинг";
					foreach(new i: Player)
					{
						if(!IsPlayerConnected(i)) continue;
						else if(!IsPlayerLogged(i)) continue;
						else if(!HasJob(i, 15)) continue;
						else if(GetPlayerData(i, P_TK_JOB) != GetPlayerData(playerid, P_TK_JOB)) continue;
						else if(GetPlayerData(i, P_JOB_CAR) == INVALID_VEHICLE_ID) continue;

						format(fmt_text, sizeof fmt_text, "\n%s\tСотрудник\tСвободен\t{fbdf6a}%d{ffffff} ед.", GetPlayerNameEx(i), GetPlayerData(i, P_JOB_LOAD_ITEMS));

						strcat(string_dialog, fmt_text);
					}

					IntfDialogCallRemote(playerid, DIALOG_TK_JMENU_1, DIALOG_STYLE_TABLIST_HEADERS, "{FFCD00}Сотрудники на рабочем месте", string_dialog,"Назад", "");
				}
				case 4:
				{
					JobInvite(playerid, -1);
					SCM(playerid, COLOR_RED, "Вы уволились с работы: \"Дальнобойщик\"");
				}
			}
		}
		case DIALOG_JOB_ITEM:
		{
			if(response)
			{
				if(GetPlayerJobLoadItems(playerid) > 5299) return SCM(playerid, COLOR_GREY, "Ваш прицеп уже загружен на максимальное количество (5300 ед.)");
				IntfDialogCallRemote(playerid, DIALOG_JOB_ITEM_1, DIALOG_STYLE_INPUT, "{FFFFFF}Действие на заводе", "{FFFFFF}Введите количество товара, которое хотите погрузить:", "Далее", "Закрыть");
			}
			else
			{
				if(GetPlayerJobLoadItems(playerid) < 1) return SCM(playerid, COLOR_GREY, "Вы не можете разгрузить, так как ваш прицеп пуст!");
				IntfDialogCallRemote(playerid, DIALOG_JOB_ITEM_2, DIALOG_STYLE_INPUT, "{FFFFFF}Действие на заводе", "{FFFFFF}Введите количество товара, которое хотите разгрузить:", "Далее", "Закрыть");
			}
		}
		case DIALOG_JOB2_ITEM:
		{
			if(response)
			{
				if(GetPlayerJobLoadItems(playerid) > 5299) return SCM(playerid, COLOR_GREY, "Ваш прицеп уже загружен на максимальное количество (5300 ед.)");
				IntfDialogCallRemote(playerid, DIALOG_JOB_ITEM_3, DIALOG_STYLE_INPUT, "{FFFFFF}Действие на заводе", "{FFFFFF}Введите количество топлива, которое хотите погрузить:", "Далее", "Закрыть");
			}
			else
			{
				if(GetPlayerJobLoadItems(playerid) < 1) return SCM(playerid, COLOR_GREY, "Вы не можете разгрузить, так как ваш прицеп пуст!");
				IntfDialogCallRemote(playerid, DIALOG_JOB_ITEM_4, DIALOG_STYLE_INPUT, "{FFFFFF}Действие на заводе", "{FFFFFF}Введите количество топлива, которое хотите разгрузить:", "Далее", "Закрыть");
			}
		}

		case DIALOG_JOB_ITEM_1:
		{
			if(!response) return 1;
			new count = strval(inputtext);

			if(5300 < GetPlayerJobLoadItems(playerid) + count) return SCM(playerid, COLOR_GREY, "Вы не можете погрузить больше 5300 ед.");
			if(count < 1) return SCM(playerid, COLOR_GREY, "Некорректное количество.");

			g_player_order_time[playerid][0] = count / 180;
			g_player_order_count[playerid] = count;

			if(g_player_order_time[playerid][0] == 0) g_player_order_time[playerid][0] = 2; 

			TogglePlayerControllable(playerid,false);

			if(GetPlayerJobLoadItems(playerid) + count > 4080) SCM(playerid, 0xd8dd8fFF, "Вы превысили рекомендации по количеству груза, есть шанс того, что в ходе доставки транспорт не справится");
			SCMF(playerid, 0xFFFFFFFF, "Погрузка товара началась, примерное время: {b8d469}%d сек{FFFFFF}, не покидайте свой транспорт", g_player_order_time[playerid][0]);
		}

		case DIALOG_JOB_ITEM_2:
		{
			if(!response) return 1;
			new count = strval(inputtext);

			if(count > GetPlayerJobLoadItems(playerid)) return SCM(playerid, COLOR_GREY, "Вы не можете разгрузить больше, чем у вас имеется.");
			if(count < 1) return SCM(playerid, COLOR_GREY, "Некорректное количество.");

			new vehicleid = GetPlayerVehicleID(playerid);
			if(!IsTrailerAttachedToVehicle(vehicleid)) return SCM(playerid, COLOR_GREY, "Невозможно начать разгрузку, так как у вас отсутствует прицеп с товаром");

			g_player_order_time[playerid][1] = count / 180;
			g_player_order_count[playerid] = count;

			TogglePlayerControllable(playerid,false);

			SCMF(playerid, 0xFFFFFFFF, "Разгрузка товара началась, примерное время: {b8d469}%d сек{FFFFFF}, не покидайте свой транспорт", g_player_order_time[playerid][1]);
		}
		case DIALOG_JOB_ITEM_3:
		{
			if(!response) return 1;
			new count = strval(inputtext);

			if(5300 < GetPlayerJobLoadItems(playerid) + count) return SCM(playerid, COLOR_GREY, "Вы не можете погрузить больше 5300 ед.");
			if(count < 1) return SCM(playerid, COLOR_GREY, "Некорректное количество.");

			g_player_order_time_fuel[playerid][0] = count / 180;
			g_player_order_count[playerid] = count;

			if(g_player_order_time_fuel[playerid][0] == 0) g_player_order_time_fuel[playerid][0] = 2; 

			TogglePlayerControllable(playerid,false);

			if(GetPlayerJobLoadItems(playerid) + count > 4080) SCM(playerid, 0xd8dd8fFF, "Вы превысили рекомендации по количеству груза, есть шанс того, что в ходе доставки транспорт не справится");
			SCMF(playerid, 0xFFFFFFFF, "Погрузка топлива началась, примерное время: {b8d469}%d сек{FFFFFF}, не покидайте свой транспорт", g_player_order_time_fuel[playerid][0]);
		}

		case DIALOG_JOB_ITEM_4:
		{
			if(!response) return 1;
			new count = strval(inputtext);

			if(count > GetPlayerJobLoadItems(playerid)) return SCM(playerid, COLOR_GREY, "Вы не можете разгрузить больше, чем у вас имеется.");
			if(count < 1) return SCM(playerid, COLOR_GREY, "Некорректное количество.");

			new vehicleid = GetPlayerVehicleID(playerid);
			if(!IsTrailerAttachedToVehicle(vehicleid)) return SCM(playerid, COLOR_GREY, "Невозможно начать разгрузку, так как у вас отсутствует прицеп с товаром");

			g_player_order_time_fuel[playerid][1] = count / 180;
			g_player_order_count[playerid] = count;

			TogglePlayerControllable(playerid,false);

			SCMF(playerid, 0xFFFFFFFF, "Разгрузка топлива началась, примерное время: {b8d469}%d сек{FFFFFF}, не покидайте свой транспорт", g_player_order_time_fuel[playerid][1]);
		}
		case DIALOG_TK_JMENU_TUTORIAL:
		{
			if(!response) ShowPlayerJMenu(playerid);

			switch(listitem + 1)
			{
				case 1: 
				{
					IntfDialogCallRemote
					(
						playerid, DIALOG_TK_JMENU_TUTORIAL_EXIT, DIALOG_STYLE_MSGBOX, 
						"{FFCD00}Руководство по работе: транспортные компании", 
						"{ffffff}Транспортная компания - это организация, которая занимается поставками груза и топлива для бизнес-предприятий.\n\
						Таких компаний всего несколько, но все они между собой соревнуются, дабы занять лидерство на рынке поставок.\n\n\
						У каждой компании есть свой владелец. Он принимает сотрудников на работу, может их увольнять или повышать до заместителя.\n\
						Также владелец способен полностью управлять транспортом компании: покупка, настройка, улучшения и многое другое.\n",
						"Назад", ""
					);
				}
				case 2: 
				{
					IntfDialogCallRemote
					(
						playerid, DIALOG_TK_JMENU_TUTORIAL_EXIT, DIALOG_STYLE_MSGBOX, 
						"{FFCD00}Руководство по работе: начало работы", 
						"{ffffff}Для начала стоит знать, что работать в компании нужно с полной ответственностью и пониманием к другим игрокам. \n\
						На базе компании есть парковка, где должны располагаться фуры. С их помощью которых можно начать работу.\n\n\
						После того как Вы возьмёте транспорт компании, необходимо оставить залог. Если Вы заняли тягач, то Вам потребуется взять\n\
						нужный прицеп. Они доступны в меню гаража (меню можно открыть через сигнал грузовика). Прицепы появляются на специальной\n\
						парковке. Также рекомендуем обращать внимание на инструкции в чате, они часто помогают.\n\n\
						Есть два вида прицепов: для топлива и для твёрдого товара. Иногда все прицепы одного типа могут разобрать. Если в гараже нет\n\
						нужного Вам прицепа, то придётся подождать пока кто-то другой не закончит свою работу. Если на парковке компании есть\n\
						обычный грузовик (не тягач), то можно использовать его, он не требует прицепа (однако он не может перевозить топливо).\n\n\
						Чтобы правильно закончить работу, необходимо приехать на базу компании и вернуть рабочий транспорт и прицеп (если \n\
						Вы его брали). Важное примечание: если рабочий транспорт будет сломан, то придётся оплатить штраф.\n",
						"Назад", ""
					);
				}
				case 3: 
				{
					IntfDialogCallRemote
					(
						playerid, DIALOG_TK_JMENU_TUTORIAL_EXIT, DIALOG_STYLE_MSGBOX, 
						"{FFCD00}Руководство по работе: навык и опыт", 
						"{ffffff}Навык дальнобойщика показывает Вашу опытность на данной работе и влияет на рабочий процесс, зачастую упрощая его.\n\
						Навык может как увеличиваться так и уменьшаться. Всё зависит от Вашего стиля работы.\n\n\
						Пожалуй, единственный способ заставить прогрессировать навык, это быстро и качественно выполнять свою работу.\n\
						Но иногда случаются аварии, в ходе чего перевозимый Вами товар может повредиться. Если повреждения критичны,\n\
						то компания выпишет Вам денежный штраф (при получении штрафов навык снижается). Нанесение ущерба транспорту,\n\
						прицепам и небрежное отношение к работе также способствует убыванию навыка.\n\n\
						Хорошо развитый навык может неплохо скрасить рабочий процесс. Он позволяет получить преимущество перед менее\n\
						опытными сотрудниками. У опытного дальнобойщика будет уходить меньше времени на погрузку товара и он сможет\n\
						получать приятную надбавку к заработанной плате (исходя из прогнозируемой зарплаты и процента прокачки навыка).\n\n\
						У каждого дальнобойщика есть своё удостоверение, которое можно показать. Оно доступно по команде {fbdf6a}/tpass{ffffff}.\n",
						"Назад", ""
					);
				}
				case 4: 
				{
					IntfDialogCallRemote
					(
						playerid, DIALOG_TK_JMENU_TUTORIAL_EXIT, DIALOG_STYLE_MSGBOX, 
						"{FFCD00}Руководство по работе: система рейтинга", 
						"{ffffff}Система рейтинга помогает соревноваться дальнобойщикам и компаниям между собой. Очки могут как прибавляться,\n\
						так и убавляться. Например, за поставку груза без задержек и ущерба Вы сможете получить вознаграждение в виде очков\n\
						навыка и рейтинга. Важно полностью завершать заказы, а не оставлять их на половине. Иначе Вы не сможете получить \n\
						полное вознаграждение.\n\n\
						В системе рейтинга среди сотрудников компаний существуют номинации: \'{fbdf6a}Сотрудник Дня{ffffff}\', \'{fbdf6a}Сотрудник Недели{ffffff}\'\n\
						и \'{fbdf6a}Сотрудник Месяца{ffffff}\'. Победитель одной из таких номинаций определяется наибольшим количеством заработанных\n\
						очков рейтинга за указаный промежуток времени. Вознаграждения за победу в номинации бывают разные, чем больше срок\n\
						определения победителя, тем более ценная будет награда.",
						"Назад", ""
					);
				}
				case 5: 
				{
					IntfDialogCallRemote
					(
						playerid, DIALOG_TK_JMENU_TUTORIAL_EXIT, DIALOG_STYLE_MSGBOX, 
						"{FFCD00}Руководство по работе: штрафы", 
						"{ffffff}1. Уничтожение грузовика и прицепа (или цистерны).\n\
						Последствия: -{f06868}650 руб{ffffff}.\n\n\
						2. Уничтожение рабочего грузовика.\n\
						Последствия: -{f06868}400 руб{ffffff}.\n\n\
						3. Уничтожение прицепа для груза или цистерны с топливом.\n\
						Последствия: -{f06868}250 руб{ffffff}.\n\n\
						4. Потеря прицепа для груза или прицепа с цистерной.\n\
						Последствия: -{f06868}300 руб{ffffff}.\n\n\
						5. Долгое нахождение на паузе, при этом занимая рабочий транспорт.\n\
						Последствия: -{f06868}400 руб{ffffff}.\n\n\
						6. Ущерб доставляемому грузу.\n\
						Последствия: {f06868}денежный штраф{ffffff}, исходя из нанесённого ущерба.\n\n\
						7. Проезд на красный в рабочее время.\n\
						Последствия: {f06868}денежный штраф от государства{ffffff}.\n\n\
						За каждое нарушение предусмотрено снижение очков рейтинга и очков навыка.\n\
						Если у Вас не будет средств, чтобы оплатить штраф, то очки будут снижены в большом количестве.\n",
						"Назад", ""
					);
				}
			}
		}
		case DIALOG_TK_JMENU_TUTORIAL_EXIT:
		{
			if(!response) return 1;

			IntfDialogCallRemote
			(
				playerid, DIALOG_TK_JMENU_TUTORIAL, DIALOG_STYLE_LIST, 
				"{FFCD00}Руководство по работе", 
				"{fbdf6a}1.{ffffff} Что такое транспортная компания\n\
				{fbdf6a}2.{ffffff} Как работать в транспортной компании\n\
				{fbdf6a}3.{ffffff} Информация о навыке дальнобойщика\n\
				{fbdf6a}4.{ffffff} Понятия \'рейтинг\' и \'номинация\'\n\
				{fbdf6a}5.{ffffff} Возможные штрафы за нарушения\n",
				"Далее", "Назад"
			);
		}

		case DIALOG_TK_JMENU_1:
		{
			if(!response) return 1;

			ShowPlayerJMenu(playerid);
		}
		case DIALOG_TK_MENU_INVITE_1:
		{
			if(!response) return 1;
			
			if(GetPlayerData(playerid, P_LEVEL) < 4) return SCM(playerid, COLOR_GREY, "У вас недостаточный уровень для трудоустройства");
			
			IntfDialogCallRemote
			(
				playerid, DIALOG_TK_MENU_INVITE_2, DIALOG_STYLE_LIST, 
				"{FFFFFF}Список доступных вакансий", 
				"{FFFFFF}1. Внештатный сотрудник\t{E6CE7B}(требуется свой грузовик)\n\
				{FFFFFF}2. Обычный сотрудник\t{E6CE7B}(особых критерий нет)",
				"Выбор", "Закрыть"
			);
		}

		case DIALOG_TK_MENU_INVITE_2:
		{
			if(!response) return 1;

			switch(listitem + 1)
			{
				case 1: 
				{
					SCM(playerid, 0x66CC00FF, "Вы устроились на работу \"Дальнобойщик\"");
					SCM(playerid, 0xFFFFFFFF, "Рекомендуем Вам ознакомиться с {E6CE7B}руководством по работе{FFFFFF}, оно доступно через меню - {BEC58C}/jmenu");

					JobInvite(playerid, 15);

					SetPlayerData(playerid, P_TK_JOB, GetNearestBusiness(playerid, 64.0));	
					UpdatePlayerDatabaseInt(playerid, "tk_job", GetPlayerData(playerid, P_TK_JOB));

					SetPlayerData(playerid, P_TK_JOB_TYPE, 2);	
					UpdatePlayerDatabaseInt(playerid, "tk_job_type", GetPlayerData(playerid, P_TK_JOB_TYPE));
				}
				case 2:
				{
					SCM(playerid, 0x66CC00FF, "Вы устроились на работу \"Дальнобойщик\"");
					SCM(playerid, 0xFFFFFFFF, "Рекомендуем Вам ознакомиться с {E6CE7B}руководством по работе{FFFFFF}, оно доступно через меню - {BEC58C}/jmenu");

					JobInvite(playerid, 15);

					SetPlayerData(playerid, P_TK_JOB, GetNearestBusiness(playerid, 64.0));	
					UpdatePlayerDatabaseInt(playerid, "tk_job", GetPlayerData(playerid, P_TK_JOB));

					SetPlayerData(playerid, P_TK_JOB_TYPE, 1);	
					UpdatePlayerDatabaseInt(playerid, "tk_job_type", GetPlayerData(playerid, P_TK_JOB_TYPE));
				}
			}
		}

		case DIALOG_TK_MENU_H:
		{
			if(!response) return 1;

			if(GetPlayerData(playerid, P_JOB_CAR) != GetPlayerVehicleID(playerid)) return 1;

			switch(listitem + 1)
			{
				case 1: 
				{
					if(GetPlayerData(playerid, P_TK_JOB_TYPE) != 1) return SCM(playerid, COLOR_GREY, "Вы не можете посместить свой транспорт на парковку");

					SCM(playerid, 0xFFFFFFFF, "Вы поместили {E6CE7B}транспорт на парковку");
					SetVehicleToRespawn(GetPlayerData(playerid, P_JOB_CAR));

					SetPlayerData(playerid, P_JOB_CAR, INVALID_VEHICLE_ID);
				}
				case 2:
				{
					if(g_player_trailer_status[playerid] == 0) return SCM(playerid, COLOR_GREY, "Вы не брали прицеп, чтобы его поместить в гараж");
					SCM(playerid, 0xFFFFFFFF, "Вы поместили {E6CE7B}прицеп в гараж");
					DestroyVehicle(g_player_trailer[playerid]);
					g_player_trailer_status[playerid] = 0;
					g_player_trailer_type[playerid] = 0;
				}
				case 3:
				{
					if(g_player_trailer_status[playerid] != 0) return SCM(playerid, COLOR_GREY, "Сначала поместите прицеп в гараж который взяли ранее");

					new type;
					if(GetPlayerData(playerid, P_TK_JOB) == 129) type = 0;
					if(GetPlayerData(playerid, P_TK_JOB) == 130) type = 1;
					if(GetPlayerData(playerid, P_TK_JOB) == 131) type = 2;

					new random_ = random(4);
					g_player_trailer[playerid] = CreateVehicle(435, g_pos_truck_trailer[type][random_][0],g_pos_truck_trailer[type][random_][1],g_pos_truck_trailer[type][random_][2],g_pos_truck_trailer[type][random_][3], 1, 1, -1); //Дальнобойщики
					g_player_trailer_status[playerid] = 1;
					g_player_trailer_type[playerid] = 1;

					SCM(playerid, 0xFFFFFFFF, "Ваш прицеп располагается в {E6CE7B}складском комплексе{FFFFFF}, подъедьте к нему {E6CE7B}задней стороной {FFFFFF}и прицепитесь");
				}
				case 4:
				{
					if(g_player_trailer_status[playerid] != 0) return SCM(playerid, COLOR_GREY, "Сначала поместите прицеп в гараж который взяли ранее");

					new type;
					if(GetPlayerData(playerid, P_TK_JOB) == 129) type = 0;
					if(GetPlayerData(playerid, P_TK_JOB) == 130) type = 1;
					if(GetPlayerData(playerid, P_TK_JOB) == 131) type = 2;

					new random_ = random(4);
					g_player_trailer[playerid] = CreateVehicle(584, g_pos_truck_trailer[type][random_][0],g_pos_truck_trailer[type][random_][1],g_pos_truck_trailer[type][random_][2],g_pos_truck_trailer[type][random_][3], 1, 1, -1); //Дальнобойщики
					g_player_trailer_status[playerid] = 1;
					g_player_trailer_type[playerid] = 2;

					SCM(playerid, 0xFFFFFFFF, "Ваш прицеп располагается в {E6CE7B}складском комплексе{FFFFFF}, подъедьте к нему {E6CE7B}задней стороной {FFFFFF}и прицепитесь");
				}
				case 5:
				{
					IntfDialogCallRemote
					(
						playerid, DIALOG_TK_MENU_H, DIALOG_STYLE_MSGBOX, 
						"{FFCD00}Информация о парковке", 
						"{ffffff}На базе каждой транспортной компании есть парковка для грузовиков. Одновременно на парковке не может\n\
						располагаться более 5 фур. Это стандартные лимиты на парковочные места. Иногда транспорта\n\
						может и вовсе не быть.\n\n\
						Начинающие компании могут позволить себе немного транспорта, по мере развития автопарк становится больше.\n\
						Обищй лимит транспортных средств в компании - 20 единиц. На каждого сотрудника предусмотрен транспорт.\n\n\
						Как только сотрудник возьмёт себе транспорт и покинет парковку, при наличии транспорта в гараже,\n\
						спустя некоторое время на парковку будет вывезен очередной грузовик. Владелец компании может полностью \n\
						распоряжаться своими транспортными средствами, и при необходимости изменять свой автопарк.\n\n\
						Если сотрудник нанёс ущерб транспорту, или доставлемому товару - ему выдадут штраф на определённую сумму.\n\
						Полный список штрафов можно глянуть в руководстве (/jmenu > Руководство).\n\n",
						"", "Закрыть"
					);
				}
			}
		}
		case DIALOG_TINTING_INSTAL:
		{
			if(!response) return 1;

			if(!VerifyIntString(QueryPlayerBalance(playerid), g_player_tinting_price[playerid])) return GameText(playerid, "~r~Недостаточно~n~средств", 3000, 2);

			new vehicleid = GetPlayerVehicleID(playerid);
    		new toner_id = GetPlayerInBiz(playerid);

			ModifyCashBalance(playerid, -g_player_tinting_price[playerid], "Покупка тонировки");

			AddBusinessProfit(playerid, toner_id, (g_player_tinting_price[playerid] / 100) * 20, 1);

			OnBattlePass_Perfomance(playerid, 21, 1);

			CEF_HIDE(playerid, "TintingOrder");
			CEF_CREATE(playerid, 1, 2, "window.setCursorStatus(1, 0)");

			SetVehiclePos(vehicleid, GetBusinessData(toner_id, B_EXIT_POS_X), GetBusinessData(toner_id, B_EXIT_POS_Y), GetBusinessData(toner_id, B_EXIT_POS_Z));
			SetVehicleZAngle(vehicleid, GetBusinessData(toner_id, B_EXIT_ANGLE));
			SetPlayerInterior(playerid, 0);
			SetPlayerVirtualWorld(playerid, 0);
			LinkVehicleToInterior(vehicleid, 0);
			SetVehicleVirtualWorld(vehicleid, 0);

			SetPlayerInBiz(playerid, -1);
			TogglePlayerControllable(playerid, true);
			SetCameraBehindPlayer(playerid);

			SaveOwnableTinting(vehicleid);

			g_player_tinting_price[playerid] = 0;
		}
		case DIALOG_VINIL_INSTAL:
		{
			if(!response) return 1;

            new vinil_price = GetPVarInt(playerid, "vinil_price");
			new vinil_id = GetPVarInt(playerid, "vinil_id");
			new type = GetPVarInt(playerid, "vinil_type");

			new vehicleid = GetPlayerOwnableCarLast(playerid);
			new model = GetVehicleModel(vehicleid);
			new index = GetVehicleData(vehicleid, V_ACTION_ID);

			if(IsVinilBanned(type, model)) return GameText(playerid, "~r~Этот винил нельзя установить", 3000, 2);

			if(type < 29){if(!VerifyIntString(QueryPlayerBalance(playerid), vinil_price)) return GameText(playerid, "~r~Недостаточно~n~средств", 3000, 2);}
			else{if(!VerifyIntString(QueryPlayerBalance(playerid), 10000000)) return GameText(playerid, "~r~Недостаточно~n~средств", 3000, 2);}

			if(type < 29){ModifyCashBalance(playerid, -vinil_price, "Покупка винила в детелинге");}
			else{ModifyCashBalance(playerid, -10000000, "Покупка винила в детелинге");} 

		    SetOwnableCarData(index, OC_VINIL, vinil_id);

			if(type < 29){SetOwnableCarData(index, OC_VINILTYPE, 1);}
			else{SetOwnableCarData(index, OC_VINILTYPE, 0);}

			new query[148];
			format(query, sizeof query, "UPDATE ownable_cars SET vinil=%d, viniltype=%d WHERE id=%d", GetOwnableCarData(index, OC_VINIL), GetOwnableCarData(index, OC_VINILTYPE), GetOwnableCarData(index, OC_SQL_ID));
			mysql_query(mysql, query, false);

			new biz_id = GetPlayerInBiz(playerid);

			if(type < 29){AddBusinessProfit(playerid, biz_id, (vinil_price / 100) * 20, 1);}
			else{AddBusinessProfit(playerid, biz_id, 2000000, 1);}

			CEF_CREATE(playerid, 1, 2, "window.setCursorStatus(1, 0)");
		}
		case DIALOG_SHINOMONTAJ_INSTAL:
		{
			if(!response) return 1;

			new vehicleid = GetPlayerOwnableCarLast(playerid);

			if(vehicleid == INVALID_VEHICLE_ID) return 1;

			new index = GetVehicleData(vehicleid, V_ACTION_ID);

			new type = g_player_diski[playerid];
	
			if(!VerifyIntString(QueryPlayerBalance(playerid), g_tuning_diski_id[type][2])) return GameText(playerid, "~r~Недостаточно~n~средств", 3000, 2);

			ModifyCashBalance(playerid, -g_tuning_diski_id[type][2], "покупка дисков");

			SetOwnableCarData(index, OC_DISKI, g_tuning_diski_id[type][0]);

			new query[148];
			format(query, sizeof query, "UPDATE ownable_cars SET diski=%d WHERE id=%d", g_tuning_diski_id[type][0], GetOwnableCarData(index, OC_SQL_ID));
			mysql_query(mysql, query, false);

			new business_id = GetNearestBusiness(playerid, 15.0);

			if(business_id != -1)
			{
				AddBusinessProfit(playerid, business_id, g_tuning_diski_id[type][2], 1);
			}

			new Float:x = GetPVarFloat(playerid, "styling_x");
			new Float:y = GetPVarFloat(playerid, "styling_y");
			new Float:z = GetPVarFloat(playerid, "styling_z");
			new Float:a = GetPVarFloat(playerid, "styling_a");

			SetCameraBehindPlayer(playerid);

			TogglePlayerSpectating(playerid, 0);
	        SetPlayerPosEx(playerid, x, y, z, a);

			CEF_HIDE(playerid, "TuningStyling");
		}
		case DIALOG_SHINOMONTAJ:
		{
			if(!response) return 1;

			switch(listitem + 1)
			{
				case 1:
				{
                    page_cars[playerid] = 1;
				    type_page_cars[playerid] = 18;
				    ShowOwnableCars(playerid, DIALOG_DISKI_CAR, page_cars[playerid]);
				}
			}
		}
		//контейнеры
		case DIALOG_CONTAINER_BET:
		{
			if(!response) return 1;
			
			for(new i; i < MAX_CONTAINERS; i++)
			{
				if(IsPlayerInRangeOfPoint(playerid, 3.0, s_containers_pos_obj[i][4][0], s_containers_pos_obj[i][4][1], s_containers_pos_obj[i][4][2]))
				{
					if(s_containers[i][S_CT_STATUS] != 1) return 1;

					if(IsPlayerInRangeOfPoint(playerid, 4.0,-1965.4330,2931.9961,7.8827)){InterpolateCameraPos(playerid, -1971.4741,2924.9089,11.0000, -1971.4741,2924.9089,11.0000, 140000);InterpolateCameraLookAt(playerid, -1958.8909,2932.2317,7.6256, -1958.8909,2932.2317,7.6256, 140000);}
					if(IsPlayerInRangeOfPoint(playerid, 4.0,-1949.1790,2932.1426,7.8827)){InterpolateCameraPos(playerid, -1954.6362,2925.3267,11.0000, -1954.6362,2925.3267,11.0000, 140000);InterpolateCameraLookAt(playerid, -1942.3273,2932.2578,7.6256, -1942.3273,2932.2578,7.6256, 140000);}
					if(IsPlayerInRangeOfPoint(playerid, 4.0,-1931.8142,2932.0295,7.8827)){InterpolateCameraPos(playerid, -1937.0596,2925.6311,11.0000, -1937.0596,2925.6311,11.0000, 140000);InterpolateCameraLookAt(playerid, -1925.0729,2932.0801,7.6256, -1925.0729,2932.0801,7.6256, 140000);}
					if(IsPlayerInRangeOfPoint(playerid, 4.0,-1914.7488,2931.9314,7.8827)){InterpolateCameraPos(playerid, -1919.9353,2925.3799,11.0000, -1919.9353,2925.3799,11.0000, 140000);	InterpolateCameraLookAt(playerid, -1908.0543,2932.1396,7.8256, -1908.0543,2932.1396,7.8256, 140000);}
					if(IsPlayerInRangeOfPoint(playerid, 4.0,-1904.9335,2926.5046,7.8827)){InterpolateCameraPos(playerid, -1908.7003,2920.2185,11.0000, -1908.7003,2920.2185,11.0000, 140000);	InterpolateCameraLookAt(playerid, -1898.1759,2926.6406,8.0333, -1898.1759,2926.6406,8.0333, 140000);}
					if(IsPlayerInRangeOfPoint(playerid, 4.0,-1922.4528,2926.6348,7.8827)){InterpolateCameraPos(playerid, -1926.1553,2919.7920,11.0000, -1926.1553,2919.7920,11.0000, 140000);	InterpolateCameraLookAt(playerid, -1915.8451,2926.5098,8.0256, -1915.8451,2926.5098,8.0256, 140000);}
					if(IsPlayerInRangeOfPoint(playerid, 4.0,-1938.8236,2926.3770,7.8827)){InterpolateCameraPos(playerid, -1942.5883,2919.4651,11.0000, -1942.5883,2919.4651,11.0000, 140000);	InterpolateCameraLookAt(playerid, -1931.7786,2926.5559,8.0256, -1931.7786,2926.5559,8.0256, 140000);}

					new fsf[213];
					format(fsf, sizeof fsf, "[\"%s\", %d, %d, %d, %d]", s_containers_type_name[s_containers[i][S_CT_ITEM_TYPE]], s_containers[i][S_CT_TYPE], s_containers[i][S_CT_PRICE], s_containers[i][S_CT_PRICE] + s_containers[i][S_CT_PRICE] / 10, s_containers[i][S_CT_TIME]);
					CEF_CREATE(playerid, 2, 4, "ContainersBet", fsf);

					SCM(playerid, 0xa9acafFF, "Вы вошли в режим участника на аукцион контейнеров.");
					SCM(playerid, 0xa9acafFF, "Увеличивайте ставку чтобы лидировать в аукционе относительно текущей цены контейнера.");
					SCM(playerid, 0xa9acafFF, "Не покидайте, аукцион, если Ваша ставка лидирует, иначе дальнейшее участие будет невозможно.");

					containers_id[playerid] = i;
				}
			}
		}
		case DIALOG_PLAYER_ACS_CONTAINER:
		{
			if(!response) return 1;

			new i = containers_id[playerid];
			
			new item_id = containers_item_id[playerid];

			switch(listitem)
			{
				case 0..1:
				{
					new str_c[450],str_cs[70];
					new port = 50000 / 100 * 20;
					format(str_cs, sizeof str_cs,"{769A37}Аксессуар: №%d", s_containers_items[i][item_id][S_CT_I_ID]);
					format(str_c, sizeof str_c,
					"{ffffff}-Государственная стоимость: {FFA500}%s руб\n{ffffff}-Стоимость в порту: {FFA500}%s руб {B25520}(-20%)\n{FFFFFF}\n{ffffff}1.Оставить себе\n{ffffff}2.Продать в порту", formatInt(50000), formatInt(50000 - port));
					
					IntfDialogCallRemote
					(
						playerid, DIALOG_PLAYER_ACS_CONTAINER, DIALOG_STYLE_LIST, str_cs, str_c,
						"Выбор", "Отмена"
					);
				}
				case 2:
				{
					if(GetInventorySlots(playerid) == -1) return GameText(playerid, "В вашем инвентаре нет свободного места", 3000, 0);

					SCMF(playerid, 0x78C02AFF, "Вы забрали Аксессуар {FFFFFF}[№%d] {78C02A}себе в инвентарь.", s_containers_items[i][item_id][S_CT_I_ID]);

					GiveAcs(playerid, s_containers_items[i][item_id][S_CT_I_ID], s_containers_items[i][item_id][S_CT_I_IDNX]);

					s_containers_items[i][item_id][S_CT_I_STATUS] = 0;

					CEF_HIDE(playerid, "Containers");

					OpenItemContainers(playerid);
				}
				case 3:
				{
					new port = 50000 / 100 * 20;
					SCMF(playerid, 0x78C02AFF, "Аксессуар {FFFFFF}[№%d] {78C02A}был продан за {FFA500}%s руб.", s_containers_items[i][item_id][S_CT_I_ID], formatInt(50000 - port));

					ModifyCashBalance(playerid, 50000 - port, "Продажа предмета с контейнера");

					s_containers_items[i][item_id][S_CT_I_STATUS] = 0;

					CEF_HIDE(playerid, "Containers");

					OpenItemContainers(playerid);
				}
			}
		}
		case DIALOG_PLAYER_ITEM_CONTAINER:
		{
			if(!response) return 1;

			new i = containers_id[playerid];
			
			new item_id = containers_item_id[playerid];

			switch(listitem)
			{
				case 0..1:
				{
					new str_c[450],str_cs[70];
					new port = ItemsInfo[s_containers_items[i][item_id][S_CT_I_ID]][i_item_price] / 100 * 20;
					format(str_cs, sizeof str_cs,"{769A37}Предмет: №%d", s_containers_items[i][item_id][S_CT_I_ID]);
					format(str_c, sizeof str_c,
					"{ffffff}-Государственная стоимость: {FFA500}%s руб\n{ffffff}-Стоимость в порту: {FFA500}%s руб {B25520}(-20%)\n{FFFFFF}\n{ffffff}1.Оставить себе\n{ffffff}2.Продать в порту", formatInt(ItemsInfo[s_containers_items[i][item_id][S_CT_I_ID]][i_item_price]), formatInt(ItemsInfo[s_containers_items[i][item_id][S_CT_I_ID]][i_item_price] - port));
					
					IntfDialogCallRemote
					(
						playerid, DIALOG_PLAYER_ITEM_CONTAINER, DIALOG_STYLE_LIST, str_cs, str_c,
						"Выбор", "Отмена"
					);
				}
				case 2:
				{
					if(GetInventorySlots(playerid) == -1) return GameText(playerid, "В вашем инвентаре нет свободного места", 3000, 0);

					SCMF(playerid, 0x78C02AFF, "Вы забрали {FFFFFF}%s [№%d] {78C02A}себе в инвентарь.", ItemsInfo[s_containers_items[i][item_id][S_CT_I_ID]], s_containers_items[i][item_id][S_CT_I_ID]);

					GiveIteam(playerid, s_containers_items[i][item_id][S_CT_I_ID], 1, 1, 0);

					s_containers_items[i][item_id][S_CT_I_STATUS] = 0;

					CEF_HIDE(playerid, "Containers");

					OpenItemContainers(playerid);
				}
				case 3:
				{
					new port = ItemsInfo[s_containers_items[i][item_id][S_CT_I_ID]][i_item_price] / 100 * 20;
					SCMF(playerid, 0x78C02AFF, "Предмет {FFFFFF}%s [№%d] {78C02A}был продан за {FFA500}%s руб.", ItemsInfo[s_containers_items[i][item_id][S_CT_I_ID]], s_containers_items[i][item_id][S_CT_I_ID], formatInt(ItemsInfo[s_containers_items[i][item_id][S_CT_I_ID]][i_item_price] - port));

					ModifyCashBalance(playerid, ItemsInfo[s_containers_items[i][item_id][S_CT_I_ID]][i_item_price] - port, "Продажа предмета с контейнера");

					s_containers_items[i][item_id][S_CT_I_STATUS] = 0;

					CEF_HIDE(playerid, "Containers");

					OpenItemContainers(playerid);
				}
			}
		}
		case DIALOG_PLAYER_SKIN_CONTAINER:
		{
			if(!response) return 1;

			new i = containers_id[playerid];
			
			new item_id = containers_item_id[playerid];

			switch(listitem)
			{
				case 0..1:
				{
					new str_c[450],str_cs[70];
					new port = s_containers_skins[s_containers[i][S_CT_TYPE]][s_containers_items[i][item_id][S_CT_I_IDNX]][1] / 100 * 20;
					format(str_cs, sizeof str_cs,"{769A37}Одежда: №%d",s_containers_skins[s_containers[i][S_CT_TYPE]][s_containers_items[i][item_id][S_CT_I_IDNX]][0]);
					format(str_c, sizeof str_c,
					"{ffffff}-Государственная стоимость: {FFA500}%s руб\n{ffffff}-Стоимость в порту: {FFA500}%s руб {B25520}(-20%)\n{FFFFFF}\n{ffffff}1.Оставить себе\n{ffffff}2.Продать в порту", formatInt(s_containers_skins[s_containers[i][S_CT_TYPE]][s_containers_items[i][item_id][S_CT_I_IDNX]][1]), formatInt(s_containers_skins[s_containers[i][S_CT_TYPE]][s_containers_items[i][item_id][S_CT_I_IDNX]][1] - port));
					
					IntfDialogCallRemote
					(
						playerid, DIALOG_PLAYER_SKIN_CONTAINER, DIALOG_STYLE_LIST, str_cs, str_c,
						"Выбор", "Отмена"
					);
				}
				case 2:
				{
					if(GetInventorySlots(playerid) == -1) return GameText(playerid, "В вашем инвентаре нет свободного места", 3000, 0);

					SCMF(playerid, 0x78C02AFF, "Вы забрали одежду {FFFFFF}№%d {78C02A}себе в инвентарь.", s_containers_items[i][item_id][S_CT_I_ID]);

					GiveSkin(playerid, s_containers_items[i][item_id][S_CT_I_ID]);

					s_containers_items[i][item_id][S_CT_I_STATUS] = 0;

					CEF_HIDE(playerid, "Containers");

					OpenItemContainers(playerid);
				}
				case 3:
				{
					new port = s_containers_skins[s_containers[i][S_CT_TYPE]][s_containers_items[i][item_id][S_CT_I_IDNX]][1] / 100 * 20;
					SCMF(playerid, 0x78C02AFF, "Одежда {FFFFFF}№%d {78C02A}была продан за {FFA500}%s руб.", s_containers_items[i][item_id][S_CT_I_ID], formatInt(s_containers_skins[s_containers[i][S_CT_TYPE]][s_containers_items[i][item_id][S_CT_I_IDNX]][1] - port));

					ModifyCashBalance(playerid, s_containers_skins[s_containers[i][S_CT_TYPE]][s_containers_items[i][item_id][S_CT_I_IDNX]][1] - port, "Продажа скина с контейнера");

					s_containers_items[i][item_id][S_CT_I_STATUS] = 0;

					CEF_HIDE(playerid, "Containers");

					OpenItemContainers(playerid);
				}
			}
		}
		case DIALOG_PLAYER_CAR_CONTAINER:
		{
			if(!response) return 1;

			new i = containers_id[playerid];

			switch(listitem)
			{
				case 0..1:
				{
					new str_c[450];
					new proc[20];
					format(proc, sizeof proc, "20%");
					new port = GetVehicleInfo(s_containers_items[i][0][S_CT_I_ID] , VI_PRICE) / 100 * 20;
					format(str_c, sizeof str_c,
					"{ffffff}-Государственная стоимость: {FFA500}%s руб\n{ffffff}-Стоимость в порту: {FFA500}%s руб {B25520}(-%s)\n\n\n{ffffff}1.Оставить себе\n2.Продать в порту", formatInt(GetVehicleInfo(s_containers_items[i][0][S_CT_I_ID] , VI_PRICE)), formatInt(GetVehicleInfo(s_containers_items[i][0][S_CT_I_ID] , VI_PRICE) - port), proc);
					IntfDialogCallRemote
					(
						playerid, DIALOG_PLAYER_CAR_CONTAINER, DIALOG_STYLE_LIST, "{769A37}Действие с транспортом", str_c,
						"Выбор", "Отмена"
					);
				}
				case 2:
				{
					if((GetPlayerOwnableCars(playerid) + 1) > GetPlayerCarSlots(playerid))
					{
						new str_c[450];
						new proc[20];
						format(proc, sizeof proc, "20%");
						new port = GetVehicleInfo(s_containers_items[i][0][S_CT_I_ID] , VI_PRICE) / 100 * 20;
						format(str_c, sizeof str_c,
						"{ffffff}-Государственная стоимость: {FFA500}%s руб\n{ffffff}-Стоимость в порту: {FFA500}%s руб {B25520}(-%s)\n\n\n{ffffff}1.Оставить себе\n2.Продать в порту", formatInt(GetVehicleInfo(s_containers_items[i][0][S_CT_I_ID] , VI_PRICE)), formatInt(GetVehicleInfo(s_containers_items[i][0][S_CT_I_ID] , VI_PRICE) - port), proc);
						IntfDialogCallRemote
						(
							playerid, DIALOG_PLAYER_CAR_CONTAINER, DIALOG_STYLE_LIST, "{769A37}Действие с транспортом", str_c,
							"Выбор", "Отмена"
						);
						return 1;
					}
					GiveCar(playerid, s_containers_items[i][0][S_CT_I_ID], 1, 1, -1, -1, container_spawn_vehicle_buy[i][CS_POS_X], container_spawn_vehicle_buy[i][CS_POS_Y], container_spawn_vehicle_buy[i][CS_POS_Z], container_spawn_vehicle_buy[i][CS_POS_A], gettime());

					SCM(playerid, -1, "{bec129}Вы выгнали своё транспортное средство из контейнера.");

					DellContainers(i);
					containers_id[playerid] = -1;
				}
				case 3:
				{
					new port = GetVehicleInfo(s_containers_items[i][0][S_CT_I_ID] , VI_PRICE) / 100 * 20;
					new query[144];
					format(query, sizeof query, "Транспортное средство {FFFFFF}%s {ead671}было продано во владение порта за {FFA500}%d руб.", GetVehicleInfo(s_containers_items[i][0][S_CT_I_ID], VI_NAME), GetVehicleInfo(s_containers_items[i][0][S_CT_I_ID], VI_PRICE) - port);
					SendClientMessage(playerid, 0xead671FF, query);

					ModifyCashBalance(playerid, GetVehicleInfo(s_containers_items[i][0][S_CT_I_ID], VI_PRICE) - port, "Продажа авто в порту");
					
					DellContainers(i);
					containers_id[playerid] = -1;
				}
			}
		}
		case DIALOG_CARWASH_START:
		{
			if(!response) return 1;

			new i = g_carwash_player_id[playerid];

			new business = GetNearestBusiness(playerid, 18.0);

			if(business == -1) return 1;

			if(!IsPlayerInRangeOfPoint(playerid, 4.5, g_carwash_object_pos[i][0][G_CARWASH_X],g_carwash_object_pos[i][0][G_CARWASH_Y],g_carwash_object_pos[i][0][G_CARWASH_Z])) return 1;

			if(g_carwash_status[i] == 1) return SendClientMessage(playerid, 0xCECECEFF, "Данная автомойка уже моет");

			if(!IsPlayerInAnyVehicle(playerid)) return SendClientMessage(playerid, 0xCECECEFF, "Вы должны находиться в транспорте");

			if(!VerifyIntString(QueryPlayerBalance(playerid), GetBusinessData(business, B_PROD_PRICE))) return GameText(playerid, "~r~Недостаточно~n~средств", 3000, 2);

			ModifyCashBalance(playerid, -GetBusinessData(business, B_PROD_PRICE), "оплата на автомойке");

			AddBusinessProfit(playerid, business, (GetBusinessData(business, B_PROD_PRICE) / 100) * 30, 1);

			g_carwash_object[i][0] = CreateObject(g_carwash_object_pos[i][1][G_CARWASH_ID], g_carwash_object_pos[i][1][G_CARWASH_X],g_carwash_object_pos[i][1][G_CARWASH_Y],g_carwash_object_pos[i][1][G_CARWASH_Z], 0.0, 0.0, 0.0);
			g_carwash_object[i][1] = CreateObject(g_carwash_object_pos[i][2][G_CARWASH_ID], g_carwash_object_pos[i][2][G_CARWASH_X],g_carwash_object_pos[i][2][G_CARWASH_Y],g_carwash_object_pos[i][2][G_CARWASH_Z], 0.0, 0.0, 0.0);
			g_carwash_object[i][2] = CreateObject(g_carwash_object_pos[i][3][G_CARWASH_ID], g_carwash_object_pos[i][3][G_CARWASH_X],g_carwash_object_pos[i][3][G_CARWASH_Y],g_carwash_object_pos[i][3][G_CARWASH_Z], 0.0, 0.0, 0.0);
			g_carwash_object[i][3] = CreateObject(g_carwash_object_pos[i][4][G_CARWASH_ID], g_carwash_object_pos[i][4][G_CARWASH_X],g_carwash_object_pos[i][4][G_CARWASH_Y],g_carwash_object_pos[i][4][G_CARWASH_Z], 0.0, 0.0, 0.0);

			GameText(playerid, "Мойка автомобиля...", 60000, 3);

			SCM(playerid, 0x75A3D2FF, "Сейчас Ваш транспорт будет вымыт. Ожидайте...");

			g_carwash_status[i] = 1;

			SetTimerEx("StopCarWash", 60000, false, "i", playerid);
			return 1;
		}
		
		case DIALOG_CREATE_CODE:
		{
			if(!response) return 1;

			switch(listitem)
			{
				case 0: typecode = 1, IntfDialogCallRemote(playerid, DIALOG_NAME_CODE, DIALOG_STYLE_INPUT, "Промокод", "Введите название промокода", "Далее", "Закрыть");
				case 1: typecode = 2, IntfDialogCallRemote(playerid, DIALOG_NAME_CODE, DIALOG_STYLE_INPUT, "Бонус-код", "Введите название бонус-кода", "Далее", "Закрыть");
				case 2: typecode = 3, IntfDialogCallRemote(playerid, DIALOG_NAME_CODE, DIALOG_STYLE_INPUT, "Ютуберский промокод", "Введите название промокода", "Далее", "Закрыть");		
			}
		}
		case DIALOG_NAME_CODE:
		{
			if(!response) return 1;

			if(strlen(inputtext) < 4)
			{
				if(typecode == 1) IntfDialogCallRemote(playerid, DIALOG_NAME_CODE, DIALOG_STYLE_INPUT, "Промокод", "Введите название промокода\n\n{BE2D2D}Название должно состоять минимум из 4 символов", "Далее", "Закрыть");
				if(typecode == 2) IntfDialogCallRemote(playerid, DIALOG_NAME_CODE, DIALOG_STYLE_INPUT, "Бонус-код", "Введите название бонус-кода\n\n{BE2D2D}Название должно состоять минимум из 4 символов", "Далее", "Закрыть");
				if(typecode == 3) IntfDialogCallRemote(playerid, DIALOG_NAME_CODE, DIALOG_STYLE_INPUT, "Ютуберский промокод", "Введите название промокода\n\n{BE2D2D}Название должно состоять минимум из 4 символов", "Далее", "Закрыть");
				return 1;
			}

			format(code_name, sizeof(code_name), "%s", inputtext);

			if(typecode == 1) IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_1, DIALOG_STYLE_INPUT, "Промокод", "Введите кол-во активаций промокода", "Далее", "Закрыть");
			if(typecode == 2) IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_1, DIALOG_STYLE_INPUT, "Бонус-код", "Введите кол-во активаций бонус-кода", "Далее", "Закрыть");
			if(typecode == 3) IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_1, DIALOG_STYLE_INPUT, "Ютуберский промокод", "Введите кол-во активаций промокода", "Далее", "Закрыть");
		}
		case DIALOG_SETTINGS_CODE_1:
		{
			if(!response) return 1;

			new count = strval(inputtext);
			if(250 < count || 1 > count)
			{
				if(typecode == 1) IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_1, DIALOG_STYLE_INPUT, "Промокод", "Введите кол-во активаций промокода\n\n{BE2D2D}Введите корректное значение: от 1 до 250 активаций", "Далее", "Закрыть");
				if(typecode == 2) IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_1, DIALOG_STYLE_INPUT, "Бонус-код", "Введите кол-во активаций бонус-кода\n\n{BE2D2D}Введите корректное значение: от 1 до 250 активаций", "Далее", "Закрыть");
				if(typecode == 3) IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_1, DIALOG_STYLE_INPUT, "Ютуберский промокод", "Введите кол-во активаций промокода\n\n{BE2D2D}Введите корректное значение: от 1 до 250 активаций", "Далее", "Закрыть");
				return 1;
			}

			code_count_activation = count;

            if(typecode == 3) IntfDialogCallRemote(playerid, DIALOG_TIME_CODE, DIALOG_STYLE_INPUT, "Ютуберский промокод", "Введите кол-во времени для отыгровки промокода (в минутах)", "Далее", "Закрыть");
			if(typecode == 2) UpdateCodeDialog(playerid);
			if(typecode == 1) IntfDialogCallRemote(playerid, DIALOG_TIME_CODE, DIALOG_STYLE_INPUT, "Промокод", "Введите кол-во времени для отыгровки промокода (в минутах)", "Далее", "Закрыть");
		}
		case DIALOG_TIME_CODE:
		{
			if(!response) return 1;

			new count = strval(inputtext);

			if(250 < count || 1 > count)
			{
				IntfDialogCallRemote(playerid, DIALOG_TIME_CODE, DIALOG_STYLE_INPUT, "Промокод", "Введите кол-во времени для отыгровки промокода (в минутах)\n\n{BE2D2D}Введите корректное значение: от 1 до 250 минут", "Далее", "Закрыть");
				return 1;
			}
			code_count_time = count;

			UpdateCodeDialog(playerid);
		}
		case DIALOG_SETTINGS_CODE_2:
		{
			if(!response) return 1;

			if(IsPlayerAdminLevel(playerid) < 7) return 1;
 	    		else if(admin_logged[playerid] == false) return SendClientMessage(playerid, 0x999999FF, "Вы не авторизированы, для этого используйте /alogin");

			switch(listitem + 1)
			{
				case 1: 
				{
					new query[148];
					STRING_GLOBAL[0] = EOS;
					format(STRING_GLOBAL, sizeof STRING_GLOBAL, "");
					for(new i; i < MAX_PRIZES_CODE; i++)
					{
						if(code_additionally[i] != 0)
						{
							if(code_additionally_type[i] == 1) format(query, sizeof query, "\nПриз: Деньги: %s руб", formatInt(code_additionally_count[i]));
							if(code_additionally_type[i] == 2) format(query, sizeof query, "\nПриз: Донат: %s руб", formatInt(code_additionally_count[i]));
							if(code_additionally_type[i] == 3) format(query, sizeof query, "\nПриз: EXP: %d шт", code_additionally_count[i]);
							if(code_additionally_type[i] == 4) format(query, sizeof query, "\nПриз: %s[№%d]: %d шт", ItemsInfo[code_additionally_id[i]][i_item_name], code_additionally_id[i], code_additionally_count[i]);
							if(code_additionally_type[i] == 5) format(query, sizeof query, "\nПриз: Транспорт[№%d]", code_additionally_id[i], code_additionally_count[i]);
							if(code_additionally_type[i] == 6) format(query, sizeof query, "\nПриз: Слоты на бизнес: %d шт", code_additionally_count[i]);
							if(code_additionally_type[i] == 7) format(query, sizeof query, "\nПриз: Слоты на дом: %d шт", code_additionally_count[i]);
							if(code_additionally_type[i] == 8) format(query, sizeof query, "\nПриз: Слоты на гараж: %d шт", code_additionally_count[i]);
							if(code_additionally_type[i] == 9) format(query, sizeof query, "\nПриз: Слоты на авто: %d шт", code_additionally_count[i]);
							if(code_additionally_type[i] == 10) format(query, sizeof query, "\nПриз: Слоты на киоск: %d шт", code_additionally_count[i]);
							if(code_additionally_type[i] == 11) format(query, sizeof query, "\nПриз: Одежда[№%d]", code_additionally_id[i]);
							if(code_additionally_type[i] == 12) format(query, sizeof query, "\nПриз: Аксессуар[№%d]", code_additionally_id[i]);
							if(code_additionally_type[i] == 13 && code_additionally_id[i] == 1) format(query, sizeof query, "\nПриз: Купон на выход из Деморгана (%d мин)", code_additionally_count[i]);
							strcat(STRING_GLOBAL, query);
						}
					}

                    if(typecode == 3) DLGF(playerid, DIALOG_SETTINGS_CODE_FINAL, DIALOG_STYLE_MSGBOX, "Информация", "Название: %s\nТип: Ютуберский промокод\nКоличество активаций: %d\nПризы:%s\n\nВы действительно хотите создать?", "Создать", "Назад", code_name, code_count_activation, STRING_GLOBAL);
					if(typecode == 2) DLGF(playerid, DIALOG_SETTINGS_CODE_FINAL, DIALOG_STYLE_MSGBOX, "Информация", "Название: %s\nТип: бонус-код\nКоличество активаций: %d\nПризы:%s\n\nВы действительно хотите создать?", "Создать", "Назад", code_name, code_count_activation, STRING_GLOBAL);
					if(typecode == 1) DLGF(playerid, DIALOG_SETTINGS_CODE_FINAL, DIALOG_STYLE_MSGBOX, "Информация", "Название: %s\nТип: промокод\nВремя отыгровки: %d минут\nКоличество активаций: %d\nПризы:%s\n\nВы действительно хотите создать?", "Создать", "Назад", code_name, code_count_time, code_count_activation, STRING_GLOBAL);
				}
				case 2: 
				{
					if(IsPlayerAdminLevel(playerid) < 7) return 1;
 	    				else if(admin_logged[playerid] == false) return SendClientMessage(playerid, 0x999999FF, "Вы не авторизированы, для этого используйте /alogin");

					for(new i; i < MAX_PRIZES_CODE; i++)
					{
						if(code_additionally[i] != 0) continue;
						IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_3, DIALOG_STYLE_LIST, "Создать приз", "1. Деньги\n2. Донат\n3. EXP\n4. Предмет\n5. Транспорт\n6. Слот на бизнес\n7. Слот на дом\n8. Слот на гараж\n9. Слот на авто\n10. Слот на киоски\n11. Одежда\n12. Аксессуар\n13. Купоны","Далее", "Назад");
						return 1;
					}
					UpdateCodeDialog(playerid), SCM(playerid, COLOR_GREY, "Создано максимальное количество призов.");
				}
				case 3: 
				{
					for(new i; i < MAX_PRIZES_CODE; i++)
					{
						code_additionally[i] = 0;
						code_additionally_type[i] = 0;
						code_additionally_id[i] = 0;
						code_additionally_count[i] = 0;
					}
					UpdateCodeDialog(playerid), SCM(playerid, COLOR_GREY, "Вы удалили все призы.");
				}
				case 4..10:
				{
					new id[6];
					new count;

					for(new i; i < MAX_PRIZES_CODE; i++)
					{
						if(code_additionally[i] == 0) continue;
						id[count] = i;
						count++;
					}

					code_additionally[id[listitem - 3]] = 0;
					code_additionally_type[id[listitem - 3]] = 0;
					code_additionally_id[id[listitem - 3]] = 0;
					code_additionally_count[id[listitem - 3]] = 0;

					UpdateCodeDialog(playerid), SCM(playerid, COLOR_GREY, "Вы успешно удалили приз");
				}
			}
		}
		case DIALOG_SETTINGS_CODE_FINAL:
		{
			if(!response) return UpdateCodeDialog(playerid);

			if(IsPlayerAdminLevel(playerid) < 7) return 1;
 	    		else if(admin_logged[playerid] == false) return SendClientMessage(playerid, 0x999999FF, "Вы не авторизированы, для этого используйте /alogin");

            if(typecode == 3)
			{
                new query[548];
			    format(query, sizeof query, "INSERT INTO prizes_code (name, count_time, count_activation, type_code, type_prize_1, id_prize_1, count_prize_1, type_prize_2, id_prize_2, count_prize_2, type_prize_3, id_prize_3, count_prize_3, type_prize_4, id_prize_4, count_prize_4, type_prize_5, id_prize_5, count_prize_5, type_prize_6, id_prize_6, count_prize_6, yt_promo)\
			    VALUES ('%s', %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, 1)",
			    code_name, code_count_time * 60, code_count_activation, typecode,
			    code_additionally_type[0], code_additionally_id[0], code_additionally_count[0],
			    code_additionally_type[1], code_additionally_id[1], code_additionally_count[1],
			    code_additionally_type[2], code_additionally_id[2], code_additionally_count[2],
			    code_additionally_type[3], code_additionally_id[3], code_additionally_count[3],
			    code_additionally_type[4], code_additionally_id[4], code_additionally_count[4],
			    code_additionally_type[5], code_additionally_id[5], code_additionally_count[5]);
			    mysql_query(mysql, query);
			}
			else
			{
                new query[548];
			    format(query, sizeof query, "INSERT INTO prizes_code (name, count_time, count_activation, type_code, type_prize_1, id_prize_1, count_prize_1, type_prize_2, id_prize_2, count_prize_2, type_prize_3, id_prize_3, count_prize_3, type_prize_4, id_prize_4, count_prize_4, type_prize_5, id_prize_5, count_prize_5, type_prize_6, id_prize_6, count_prize_6, yt_promo)\
			    VALUES ('%s', %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, 0)",
			    code_name, code_count_time * 60, code_count_activation, typecode,
			    code_additionally_type[0], code_additionally_id[0], code_additionally_count[0],
			    code_additionally_type[1], code_additionally_id[1], code_additionally_count[1],
			    code_additionally_type[2], code_additionally_id[2], code_additionally_count[2],
			    code_additionally_type[3], code_additionally_id[3], code_additionally_count[3],
			    code_additionally_type[4], code_additionally_id[4], code_additionally_count[4],
			    code_additionally_type[5], code_additionally_id[5], code_additionally_count[5]);
			    mysql_query(mysql, query);
			}

			for(new i; i < MAX_PRIZES_CODE; i++)
			{
				code_additionally[i] = 0;
			}
			if(typecode == 3) SCMF(playerid, COLOR_ORANGE, "Вы успешно создали ютуберский промокод: {BE2D2D}%s", code_name);
			if(typecode == 2) SCMF(playerid, COLOR_ORANGE, "Вы успешно создали бонус-код: {BE2D2D}%s", code_name);
			if(typecode == 1) SCMF(playerid, COLOR_ORANGE, "Вы успешно создали промокод: {BE2D2D}%s", code_name);
			code_count_time = 0;
		}
		case DIALOG_SETTINGS_CODE_3:
		{
			if(!response) return UpdateCodeDialog(playerid);

			new prize_code;
			for(new i; i < MAX_PRIZES_CODE; i++)
			{
				if(code_additionally[i] != 0) continue;
				prize_code = i;
				break;
			}

			code_additionally_type[prize_code] = listitem + 1;

			switch(listitem + 1)
			{
				case 1: IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_4, DIALOG_STYLE_INPUT, "Деньги", "Введите кол-во денег", "Далее", "");
				case 2: IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_4, DIALOG_STYLE_INPUT, "Донат", "Введите кол-во доната", "Далее", "");
				case 3: IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_4, DIALOG_STYLE_INPUT, "EXP", "Введите кол-во EXP", "Далее", "");
				case 4: IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_4, DIALOG_STYLE_INPUT, "Предмет", "Введите id предмета", "Далее", "");
				case 5: IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_4, DIALOG_STYLE_INPUT, "Транспорт", "Введите id автомобиля", "Далее", "");
				case 6: IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_4, DIALOG_STYLE_INPUT, "Слот на бизнес", "Введите кол-во слотов на бизнес", "Далее", "");
				case 7: IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_4, DIALOG_STYLE_INPUT, "Слот на дом", "Введите кол-во слотов на дом", "Далее", "");
				case 8: IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_4, DIALOG_STYLE_INPUT, "Слот на гараж", "Введите кол-во слотов на гараж", "Далее", "");
				case 9: IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_4, DIALOG_STYLE_INPUT, "Слот на авто", "Введите кол-во слотов на авто", "Далее", "");
				case 10: IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_4, DIALOG_STYLE_INPUT, "Слот на киоски", "Введите кол-во слотов на киоски", "Далее", "");
				case 11: IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_4, DIALOG_STYLE_INPUT, "Одежда", "Введите id одежды", "Далее", "");
				case 12: IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_4, DIALOG_STYLE_INPUT, "Аксессуар", "Введите id (объект) аксессуара", "Далее", "");
				case 13: IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_4, DIALOG_STYLE_LIST, "Купоны", "Купон на выход из тюрьмы Деморган", "Далее", "");
			}
		}
		case DIALOG_SETTINGS_CODE_4:
		{
			if(!response) return 1;

			new prize_code;
			for(new i; i < MAX_PRIZES_CODE; i++)
			{
				if(code_additionally[i] != 0) continue;
				prize_code = i;
				break;
			}

			new count = strval(inputtext);
			if(code_additionally_type[prize_code] == 5) 
			{
				if(count < 1) return IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_4, DIALOG_STYLE_INPUT, "Транспорт", "Введите id автомобиля\n\n{BE2D2D}Вы указали неверный id авто. Доступные авто: 400-614, 699, 793-799, 907-909, 965, 999, 1326, 15065-15299, 15600-15675", "Далее", "");
				if(!(400 <= count <= 614) && (!(699 <= count <= 699) && (!(793 <= count <= 799) && (!(15065 <= count <= 15299) && (!(15600 <= count <= 15691) && (!(907 <= count <= 909) && (!(965 <= count <= 965) && (!(999 <= count <= 999) && (!(1326 <= count <= 1326))))))))))
				{
					return IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_4, DIALOG_STYLE_INPUT, "Транспорт", "Введите id автомобиля\n\n{BE2D2D}Вы указали неверный id авто. Доступные авто: 400-614, 699, 793-799, 907-909, 965, 999, 1326, 15065-15299, 15600-15691", "Далее", "");
				}
			}
			if(code_additionally_type[prize_code] != 5) 
			{
				switch(code_additionally_type[prize_code])
				{
					case 1: if(500000000 < count || 1 > count) return IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_4, DIALOG_STYLE_INPUT, "Деньги", "Введите кол-во денег\n\n{BE2D2D}Введите корректное значение: от 1 до 500.000.000", "Далее", "");
					case 2: if(100000 < count || 1 > count) return IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_4, DIALOG_STYLE_INPUT, "Донат", "Введите кол-во доната\n\n{BE2D2D}Введите корректное значение: от 1 до 100.000", "Далее", "");
					case 3: if(100 < count || 1 > count) return IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_4, DIALOG_STYLE_INPUT, "EXP", "Введите кол-во EXP\n\n{BE2D2D}Введите корректное значение: от 1 до 100", "Далее", "");
					case 4: if(500 < count || 1 > count) return IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_4, DIALOG_STYLE_INPUT, "Предмет", "Введите id предмета\n\n{BE2D2D}Введите корректное значение", "Далее", "");
					case 6: if(15 < count || 1 > count) return IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_4, DIALOG_STYLE_INPUT, "Слот на бизнес", "Введите кол-во слотов на бизнес\n\n{BE2D2D}Введите корректное значение: от 1 до 15", "Далее", "");
					case 7: if(15 < count || 1 > count) return IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_4, DIALOG_STYLE_INPUT, "Слот на дом", "Введите кол-во слотов на дом\n\n{BE2D2D}Введите корректное значение: от 1 до 15", "Далее", "");
					case 8: if(15 < count || 1 > count) return IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_4, DIALOG_STYLE_INPUT, "Слот на гараж", "Введите кол-во слотов на гараж\n\n{BE2D2D}Введите корректное значение: от 1 до 15", "Далее", "");
					case 9: if(15 < count || 1 > count) return IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_4, DIALOG_STYLE_INPUT, "Слот на авто", "Введите кол-во слотов на авто\n\n{BE2D2D}Введите корректное значение: от 1 до 15", "Далее", "");
					case 10: if(15 < count || 1 > count) return IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_4, DIALOG_STYLE_INPUT, "Слот на киоски", "Введите кол-во слотов на киоски\n\n{BE2D2D}Введите корректное значение: от 1 до 15", "Далее", "");
					case 11: if(50000 < count || 1 > count) return IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_4, DIALOG_STYLE_INPUT, "Одежда", "Введите id одежды\n\n{BE2D2D}Введите корректное значение", "Далее", "");
				}
			}
			if(code_additionally_type[prize_code] == 4)
			{
				code_additionally_id[prize_code] = count;
				IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_ITEM, DIALOG_STYLE_INPUT, "Предмет", "Введите кол-во предмета", "Далее", "");
			}
			else if(code_additionally_type[prize_code] == 12)
			{
				code_additionally_id[prize_code] = count;
				IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_ITEM, DIALOG_STYLE_INPUT, "Аксессуар", "Типы аксессуаров:\n\
				Тип 0 - Очки\n\
				Тип 1 - Бандана\n\
				Тип 2 - Маска\n\
				Тип 3 - Берет\n\
				Тип 4 - Шляпа\n\
				Тип 5 - Сумка\n\
				Тип 6 - Ремень\n\
				Тип 7 - Украшение на руку\n\
				Тип 8 - Рюкзак\n\
				Тип 9 - Украшение на шею\n\
				Тип 10 - Плащ\n\
				Тип 11 - Бронижелет\n\
				Тип 12 - Посох\n\
				Тип 13 - Крылья\n\
				Тип 14 - Украшение на транспорт\n\
				Тип 15 - Украшение на транспорт\n\
				Тип 16 - Украшение на транспорт\n\
				Тип 17 - Украшение на транспорт\n\
				Тип 18 - Скейтборд\n\
				Тип 19 - Украшение на левое плечо\n\n\
				Введите определенный тип аксессуара:", "Далее", "");
			}
			else if(code_additionally_type[prize_code] == 13)
			{
				new type = listitem + 1;

				code_additionally_id[prize_code] = type;

				IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_ITEM, DIALOG_STYLE_INPUT, "Купон", "Введите время действия купона (в минутах)", "Далее", "");
			}
			else 
			{
				if(code_additionally_type[prize_code] == 5 || code_additionally_type[prize_code] == 11) code_additionally_id[prize_code] = count;
				else code_additionally_count[prize_code] = count;
				code_additionally[prize_code] = 1;
				UpdateCodeDialog(playerid);
			}
		}
		case DIALOG_SETTINGS_CODE_ITEM:
		{
			if(!response) return 1;

			new prize_code;
			for(new i; i < MAX_PRIZES_CODE; i++)
			{
				if(code_additionally[i] != 0) continue;
				prize_code = i;
				break;
			}

			if(code_additionally_type[prize_code] == 4)
			{
				new count = strval(inputtext);
				if(50 < count || 1 > count) return IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_ITEM, DIALOG_STYLE_INPUT, "Предмет", "Введите кол-во предмета\n\n{BE2D2D}Введите корректное значение: от 1 до 50", "Далее", "");
			}
			else if(code_additionally_type[prize_code] == 13)
			{
				new count = strval(inputtext);
				if(500 < count || 5 > count) return IntfDialogCallRemote(playerid, DIALOG_SETTINGS_CODE_ITEM, DIALOG_STYLE_INPUT, "Купон", "Введите время действия купона (в минутах)\n\n{BE2D2D}Введите корректное значение (от 5 до 500 минут)", "Далее", "");
			}
			code_additionally_count[prize_code] = strval(inputtext);
			code_additionally[prize_code] = 1;
			UpdateCodeDialog(playerid);
		}
		case DIALOG_PROMO_ACTIVATE:
		{
			if(response)
			{
				if(!strlen(inputtext)) return callcmd::pcode(playerid, "");

				new query[256],
	            Cache: result,
	            rows,
	            count_activation,
	            count_time,
	            type_prize[6],
	            id_prize[6],
	            type_code,
	            count_prize[6];

	            string_dialog[0] = EOS;
				
	            mysql_format(mysql, query, sizeof query, "SELECT * FROM promocode_activations WHERE owner_id='%d' AND name='%s'", GetPlayerAccountID(playerid), inputtext);
	            result = mysql_query(mysql, query, true);

	            rows = cache_num_rows();

	            cache_delete(result);

	            if(rows) return IntfDialogCallRemote(playerid, -1, DIALOG_STYLE_MSGBOX,"Ошибка активации","Вы уже активировали данный промокод","", "Хорошо");

	            mysql_format(mysql, query, sizeof query, "SELECT * FROM prizes_code WHERE name='%s' AND count_activation > 0", inputtext);
	            result = mysql_query(mysql, query, true);

	            rows = cache_num_rows();

	            if(rows)
	            {
		            count_activation = cache_get_field_content_int(0, "count_activation");
		            count_time = cache_get_field_content_int(0, "count_time");
		            type_code = cache_get_field_content_int(0, "type_code");

		            type_prize[0] = cache_get_field_content_int(0, "type_prize_1");
		            id_prize[0] = cache_get_field_content_int(0, "id_prize_1");
		            count_prize[0] = cache_get_field_content_int(0, "count_prize_1");

		            type_prize[1] = cache_get_field_content_int(0, "type_prize_2");
		            id_prize[1] = cache_get_field_content_int(0, "id_prize_2");
		            count_prize[1] = cache_get_field_content_int(0, "count_prize_2");
					
		            type_prize[2] = cache_get_field_content_int(0, "type_prize_3");
		            id_prize[2] = cache_get_field_content_int(0, "id_prize_3");
		            count_prize[2] = cache_get_field_content_int(0, "count_prize_3");

		            type_prize[3] = cache_get_field_content_int(0, "type_prize_4");
		            id_prize[3] = cache_get_field_content_int(0, "id_prize_4");
		            count_prize[3] = cache_get_field_content_int(0, "count_prize_4");

		            type_prize[4] = cache_get_field_content_int(0, "type_prize_5");
		            id_prize[4] = cache_get_field_content_int(0, "id_prize_5");
		            count_prize[4] = cache_get_field_content_int(0, "count_prize_5");

		            type_prize[5] = cache_get_field_content_int(0, "type_prize_6");
		            id_prize[5] = cache_get_field_content_int(0, "id_prize_6");
		            count_prize[5] = cache_get_field_content_int(0, "count_prize_6");
	            }
	            cache_delete(result);

	            if(!rows) return IntfDialogCallRemote(playerid, -1, DIALOG_STYLE_MSGBOX,"Ошибка активации","Данный промокод не найден","", "Хорошо");

                if(type_code == 1) // Промокод
	            {
	                if(count_activation > 0)
	                {
		                mysql_format(mysql, query, sizeof query, "UPDATE prizes_code SET count_activation='%d' WHERE name='%s'", count_activation - 1, inputtext);
		                mysql_query(mysql, query, false);

		                CreatePlayerPromo(playerid, inputtext, count_time);

		                SCMF(playerid, 0x66CC33FF, "{ffff00}Вы активировали промокод \"%s\"", inputtext);
		                SCM(playerid, COLOR_GREY, "Примечание: бонусы выдаются во время зарплаты");

		                string_dialog[0] = EOS;

		                for(new i; i < MAX_PRIZES_CODE; i++)
		                {	
			                if(type_prize[i] == 1) format(query, sizeof query, "{FFFFFF}- %s рублей\n", formatInt(count_prize[i])),strcat(string_dialog, query);
			                if(type_prize[i] == 2) format(query, sizeof query, "{FFFFFF}- %s донат-монет\n", formatInt(count_prize[i])),strcat(string_dialog, query);
		                    if(type_prize[i] == 3) format(query, sizeof query, "{FFFFFF}- Игровой опыт в количестве %d шт.\n", count_prize[i]),strcat(string_dialog, query);
			                if(type_prize[i] == 4) format(query, sizeof query, "{FFFFFF}- %s в количестве %d шт.\n", ItemsInfo[id_prize[i]][i_item_name], count_prize[i]),strcat(string_dialog, query);
			                if(type_prize[i] == 5) format(query, sizeof query, "{FFFFFF}- %s [№%d]\n", GetVehicleInfo(id_prize[i], VI_NAME), id_prize[i]),strcat(string_dialog, query);
			                if(type_prize[i] == 6) format(query, sizeof query, "{FFFFFF}- Слот на бизнес в количестве %d шт.\n", count_prize[i]),strcat(string_dialog, query);
			                if(type_prize[i] == 7) format(query, sizeof query, "{FFFFFF}- Слот на дом в количестве %d шт.\n", count_prize[i]),strcat(string_dialog, query);
			                if(type_prize[i] == 8) format(query, sizeof query, "{FFFFFF}- Слот на гараж в количестве %d шт.\n", count_prize[i]),strcat(string_dialog, query);
			                if(type_prize[i] == 9) format(query, sizeof query, "{FFFFFF}- Слот на транспорт в количестве %d шт.\n", count_prize[i]),strcat(string_dialog, query);
			                if(type_prize[i] == 10) format(query, sizeof query, "{FFFFFF}- Слот на киоск в количестве %d шт.\n", count_prize[i]),strcat(string_dialog, query);
			                if(type_prize[i] == 11) format(query, sizeof query, "{FFFFFF}- Одежда[№%d]\n", id_prize[i]),strcat(string_dialog, query);
		                    if(type_prize[i] == 12) format(query, sizeof query, "{FFFFFF}- Аксессуар[№%d]\n", id_prize[i]),strcat(string_dialog, query);
			                if(type_prize[i] == 13 && id_prize[i] == 1) format(query, sizeof query, "{FFFFFF}- Купон на выход из Деморгана (%d мин)\n", count_prize[i]),strcat(string_dialog, query);
		                }

		                format
		                (
			                string_dialog, sizeof string_dialog, 
			                "{bebfba}Вы активировали промокод \'%s\'\n\
			                {FFFFFF}После {6cbbea}%02d {FFFFFF}минут игры на сервере (не AFK), Вы получите:\n\n\
			                %s\n\
			                Примечание: призы выдаются во время отыгранной зарплаты\n\n\
			                Успейте выполнить все условия для получения награды",
			                inputtext, floatround(count_time / 60), string_dialog
		                );
		                IntfDialogCallRemote(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, "{FFFFFF}Активация промокода", string_dialog,"", "Хорошо");
	                }
	                else 
	                {
	                    IntfDialogCallRemote(playerid, -1, DIALOG_STYLE_MSGBOX,"Ошибка активации","{bebfba}Достигнут лимит использований промокода","", "Хорошо");
	                }
	            }
				if(type_code == 3) // Промокод YT
	            {
	                if(count_activation > 0)
	                {
						if(GetPlayerData(playerid, P_YT_PROMO) != 1)
						{
                            mysql_format(mysql, query, sizeof query, "UPDATE prizes_code SET count_activation='%d' WHERE name='%s'", count_activation - 1, inputtext);
		                    mysql_query(mysql, query, false);

		                    CreatePlayerPromo(playerid, inputtext, count_time);

						    SetPlayerData(playerid, P_YT_PROMO, 1);
                            UpdatePlayerDatabaseInt(playerid, "yt_promo", 1);

		                    SCMF(playerid, 0x66CC33FF, "{ffff00}Вы активировали промокод \"%s\"", inputtext);
		                    SCM(playerid, COLOR_GREY, "Примечание: бонусы выдаются во время зарплаты");

		                    string_dialog[0] = EOS;

		                    for(new i; i < MAX_PRIZES_CODE; i++)
		                    {	
			                    if(type_prize[i] == 1) format(query, sizeof query, "{FFFFFF}- %s рублей\n", formatInt(count_prize[i])),strcat(string_dialog, query);
			                    if(type_prize[i] == 2) format(query, sizeof query, "{FFFFFF}- %s донат-монет\n", formatInt(count_prize[i])),strcat(string_dialog, query);
		                        if(type_prize[i] == 3) format(query, sizeof query, "{FFFFFF}- Игровой опыт в количестве %d шт.\n", count_prize[i]),strcat(string_dialog, query);
			                    if(type_prize[i] == 4) format(query, sizeof query, "{FFFFFF}- %s в количестве %d шт.\n", ItemsInfo[id_prize[i]][i_item_name], count_prize[i]),strcat(string_dialog, query);
			                    if(type_prize[i] == 5) format(query, sizeof query, "{FFFFFF}- %s [№%d]\n", GetVehicleInfo(id_prize[i], VI_NAME), id_prize[i]),strcat(string_dialog, query);
			                    if(type_prize[i] == 6) format(query, sizeof query, "{FFFFFF}- Слот на бизнес в количестве %d шт.\n", count_prize[i]),strcat(string_dialog, query);
			                    if(type_prize[i] == 7) format(query, sizeof query, "{FFFFFF}- Слот на дом в количестве %d шт.\n", count_prize[i]),strcat(string_dialog, query);
			                    if(type_prize[i] == 8) format(query, sizeof query, "{FFFFFF}- Слот на гараж в количестве %d шт.\n", count_prize[i]),strcat(string_dialog, query);
			                    if(type_prize[i] == 9) format(query, sizeof query, "{FFFFFF}- Слот на транспорт в количестве %d шт.\n", count_prize[i]),strcat(string_dialog, query);
			                    if(type_prize[i] == 10) format(query, sizeof query, "{FFFFFF}- Слот на киоск в количестве %d шт.\n", count_prize[i]),strcat(string_dialog, query);
			                    if(type_prize[i] == 11) format(query, sizeof query, "{FFFFFF}- Одежда[№%d]\n", id_prize[i]),strcat(string_dialog, query);
		                        if(type_prize[i] == 12) format(query, sizeof query, "{FFFFFF}- Аксессуар[№%d]\n", id_prize[i]),strcat(string_dialog, query);
			                    if(type_prize[i] == 13 && id_prize[i] == 1) format(query, sizeof query, "{FFFFFF}- Купон на выход из Деморгана (%d мин)\n", count_prize[i]),strcat(string_dialog, query);
		                    }

		                    format
		                    (
			                    string_dialog, sizeof string_dialog, 
			                    "{bebfba}Вы активировали промокод \'%s\'\n\
			                    {FFFFFF}После {6cbbea}%02d {FFFFFF}минут игры на сервере (не AFK), Вы получите:\n\n\
			                    %s\n\
			                    Примечание: призы выдаются во время отыгранной зарплаты\n\n\
			                    Успейте выполнить все условия для получения награды",
			                    inputtext, floatround(count_time / 60), string_dialog
		                    );
		                    IntfDialogCallRemote(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, "{FFFFFF}Активация промокода", string_dialog,"", "Хорошо");
						}
						else IntfDialogCallRemote(playerid, -1, DIALOG_STYLE_MSGBOX,"Ошибка активации","Вы уже активировали ютуберский промокод","", "Хорошо");
	                }
	                else 
	                {
	                    IntfDialogCallRemote(playerid, -1, DIALOG_STYLE_MSGBOX,"Ошибка активации","{bebfba}Достигнут лимит использований промокода","", "Хорошо");
	                }
	            }
			}
		}
        case DIALOG_BONUSCODE_ACTIVATE:
		{
			if(!response) return 1;
			if(!strlen(inputtext)) return IntfDialogCallRemote(playerid, DIALOG_BONUSCODE_ACTIVATE, DIALOG_STYLE_INPUT,"Активация бонус кода","Введите ваш бонус код в поле ниже","Далее", "Отмена");
			
			new query[256],
				Cache: result,
				rows,
				count_activation,
				type_code,
				type_prize[6],
				id_prize[6],
				count_prize[6];

			format(query, sizeof query, "SELECT * FROM promocode_activations WHERE owner_id='%d' AND name='%s'", GetPlayerAccountID(playerid), inputtext);
			result = mysql_query(mysql, query, true);

			rows = cache_num_rows();

			cache_delete(result);

			if(rows) return IntfDialogCallRemote(playerid, -1, DIALOG_STYLE_MSGBOX,"Ошибка активации","Вы уже активировали данный бонус код","", "Хорошо");

			format(query, sizeof query, "SELECT * FROM prizes_code WHERE name='%s' AND count_activation > 0 AND type_code=2", inputtext);
			result = mysql_query(mysql, query, true);

			rows = cache_num_rows();

			if(rows)
			{
				count_activation = cache_get_field_content_int(0, "count_activation");

				type_prize[0] = cache_get_field_content_int(0, "type_prize_1");
				id_prize[0] = cache_get_field_content_int(0, "id_prize_1");
				count_prize[0] = cache_get_field_content_int(0, "count_prize_1");

				type_prize[1] = cache_get_field_content_int(0, "type_prize_2");
				id_prize[1] = cache_get_field_content_int(0, "id_prize_2");
				count_prize[1] = cache_get_field_content_int(0, "count_prize_2");
				
				type_prize[2] = cache_get_field_content_int(0, "type_prize_3");
				id_prize[2] = cache_get_field_content_int(0, "id_prize_3");
				count_prize[2] = cache_get_field_content_int(0, "count_prize_3");

				type_prize[3] = cache_get_field_content_int(0, "type_prize_4");
				id_prize[3] = cache_get_field_content_int(0, "id_prize_4");
				count_prize[3] = cache_get_field_content_int(0, "count_prize_4");

				type_prize[4] = cache_get_field_content_int(0, "type_prize_5");
				id_prize[4] = cache_get_field_content_int(0, "id_prize_5");
				count_prize[4] = cache_get_field_content_int(0, "count_prize_5");

				type_prize[5] = cache_get_field_content_int(0, "type_prize_6");
				id_prize[5] = cache_get_field_content_int(0, "id_prize_6");
				count_prize[5] = cache_get_field_content_int(0, "count_prize_6");

				type_code = cache_get_field_content_int(0, "type_code");
			}

			cache_delete(result);

			if(type_code == 1) return IntfDialogCallRemote(playerid, -1, DIALOG_STYLE_MSGBOX,"Ошибка активации","Данный бонус код не найден","", "Хорошо");

			if(!rows) IntfDialogCallRemote(playerid, -1, DIALOG_STYLE_MSGBOX,"Ошибка активации","Данный бонус код не найден","", "Хорошо");

			mysql_format(mysql, query, sizeof query, "SELECT * FROM promocode_activations WHERE owner_id='%d' AND name='%s'", GetPlayerAccountID(playerid), inputtext);
			result = mysql_query(mysql, query, true);

			rows = cache_num_rows();

			if(count_activation > 0)
			{
				mysql_format(mysql, query, sizeof query, "UPDATE prizes_code SET count_activation='%d' WHERE name='%s'", count_activation - 1, inputtext);
				mysql_query(mysql, query, false);

				mysql_format(mysql, query, sizeof query, "INSERT INTO promocode_activations (owner_id, name, time, type, status) VALUES (%d, '%s', 0, 0, 2)", GetPlayerAccountID(playerid), inputtext);
				mysql_query(mysql, query, false);

				string_dialog[0] = EOS;

				for(new i; i < MAX_PRIZES_CODE; i++)
				{	
					if(type_prize[i] == 1) 
						SCMF(playerid, COLOR_ORANGE, "{3599f5}Вам начислен приз {FFFFFF}Деньги: %d руб {3599f5}за активацию бонус кода", count_prize[i]), 
						GivePlayerMyPrizes(playerid, "Деньги", 5, 0, 0, count_prize[i], 0),
						format(query, sizeof query, "{FFFFFF}- %s рублей\n", formatInt(count_prize[i])),
						strcat(string_dialog, query);

					if(type_prize[i] == 2) 
						SCMF(playerid, COLOR_ORANGE, "{3599f5}Вам начислен приз {FFFFFF}Донат: %d руб {3599f5}за активацию бонус кода", count_prize[i]), 
						GivePlayerMyPrizes(playerid, "Донат", 10, 0, 0, count_prize[i], 0),
						format(query, sizeof query, "{FFFFFF}- %s донат-монет\n", formatInt(count_prize[i])),
						strcat(string_dialog, query);

					if(type_prize[i] == 3) 
						SCMF(playerid, COLOR_ORANGE, "{3599f5}Вам начислен приз {FFFFFF}%d EXP {3599f5}за активацию бонус кода", count_prize[i]), 
						GivePlayerExp(playerid, count_prize[i]),
						format(query, sizeof query, "{FFFFFF}- Игровой опыт в количестве %d шт.\n", count_prize[i]),
						strcat(string_dialog, query);

					if(type_prize[i] == 4) 
						SCMF(playerid, COLOR_ORANGE, "{3599f5}Вам начислен приз {FFFFFF}%s в количестве %d шт. {3599f5}за активацию бонус кода",ItemsInfo[id_prize[i]][i_item_name], count_prize[i]), 
						format(query, sizeof query, "%s", ItemsInfo[id_prize[i]][i_item_name]),
						GivePlayerMyPrizes(playerid, query, 8, id_prize[i], 0, count_prize[i], 0),
						format(query, sizeof query, "{FFFFFF}- %s в количестве %d шт.\n", ItemsInfo[id_prize[i]][i_item_name], count_prize[i]),
						strcat(string_dialog, query);

					if(type_prize[i] == 5) 
						SCMF(playerid, COLOR_ORANGE, "{3599f5}Вам начислен приз {FFFFFF}%s {3599f5}за активацию бонус кода", GetVehicleInfo(id_prize[i], VI_NAME)), 
						format(query, sizeof query, "%s[№%d]", GetVehicleInfo(id_prize[i], VI_NAME), id_prize[i]),
						GivePlayerMyPrizes(playerid, query, 3, id_prize[i], 0, 1, -1),
						format(query, sizeof query, "{FFFFFF}- %s [№%d]\n", GetVehicleInfo(id_prize[i], VI_NAME), id_prize[i]),
						strcat(string_dialog, query);
			
					if(type_prize[i] == 6) 
						SCMF(playerid, COLOR_ORANGE, "{3599f5}Вам начислен приз {FFFFFF}Слот на бизнес в количестве %d шт. {3599f5}за активацию бонус кода", count_prize[i]), 
						AddPlayerData(playerid, P_BIZ_SLOTS, +, count_prize[i]),
						UpdatePlayerDatabaseInt(playerid, "biz_slots", GetPlayerData(playerid, P_BIZ_SLOTS)),
						format(query, sizeof query, "{FFFFFF}- Слот на бизнес в количестве %d шт.\n", count_prize[i]),
						strcat(string_dialog, query);

					if(type_prize[i] == 7) 
						SCMF(playerid, COLOR_ORANGE, "{3599f5}Вам начислен приз {FFFFFF}Слот на дом в количестве %d шт. {3599f5}за активацию бонус кода", count_prize[i]), 
						AddPlayerData(playerid, P_HOUSE_SLOTS, +, count_prize[i]),
						UpdatePlayerDatabaseInt(playerid, "house_slots", GetPlayerData(playerid, P_HOUSE_SLOTS)),
						format(query, sizeof query, "{FFFFFF}- Слот на дом в количестве %d шт.\n", count_prize[i]),
						strcat(string_dialog, query);
				
					if(type_prize[i] == 8) 
						SCMF(playerid, COLOR_ORANGE, "{3599f5}Вам начислен приз {FFFFFF}Слот на гараж в количестве %d шт. {3599f5}за активацию бонус кода", count_prize[i]), 
						AddPlayerData(playerid, P_GARAGE_SLOTS, +, count_prize[i]),
						UpdatePlayerDatabaseInt(playerid, "garage_slots", GetPlayerData(playerid, P_GARAGE_SLOTS)),
						format(query, sizeof query, "{FFFFFF}- Слот на гараж в количестве %d шт.\n", count_prize[i]),
						strcat(string_dialog, query);
				
					if(type_prize[i] == 9) 
						SCMF(playerid, COLOR_ORANGE, "{3599f5}Вам начислен приз {FFFFFF}Слот на транспорт в количестве %d шт. {3599f5}за активацию бонус кода", count_prize[i]), 
						AddPlayerData(playerid, P_CAR_SLOTS, +, count_prize[i]),
						UpdatePlayerDatabaseInt(playerid, "car_slots", GetPlayerData(playerid, P_CAR_SLOTS)),
						format(query, sizeof query, "{FFFFFF}- Слот на транспорт в количестве %d шт.\n", count_prize[i]),
						strcat(string_dialog, query);

					if(type_prize[i] == 10) 
						SCMF(playerid, COLOR_ORANGE, "{3599f5}Вам начислен приз {FFFFFF}Слот на киоск в количестве %d шт. {3599f5}за активацию бонус кода", count_prize[i]), 
						AddPlayerData(playerid, P_KIOSK_SLOTS, +, count_prize[i]),
						UpdatePlayerDatabaseInt(playerid, "kiosk_slots", GetPlayerData(playerid, P_KIOSK_SLOTS)),
						format(query, sizeof query, "{FFFFFF}- Слот на киоск в количестве %d шт.\n", count_prize[i]),
						strcat(string_dialog, query);
			
					if(type_prize[i] == 11)
						SCMF(playerid, COLOR_ORANGE, "{3599f5}Вам начислен приз {FFFFFF}Одежда[№%d] {3599f5}за активацию бонус кода", id_prize[i]), 
						format(query, sizeof query, "Одежда[№%d]", id_prize[i]),
						GivePlayerMyPrizes(playerid, query, 4, id_prize[i], 0, 1, 0),
						format(query, sizeof query, "{FFFFFF}- Одежда[№%d]\n", id_prize[i]),
						strcat(string_dialog, query);
				
					if(type_prize[i] == 12) 
						SCMF(playerid, COLOR_ORANGE, "{3599f5}Вам начислен приз {FFFFFF}Аксессуар[№%d] {3599f5}за активацию бонус кода", id_prize[i]), 
						format(query, sizeof query, "Аксессуар[№%d]", id_prize[i]),
						GivePlayerMyPrizes(playerid, query, 6, id_prize[i], 0, 1, count_prize[i]),
						format(query, sizeof query, "{FFFFFF}- Аксессуар[№%d]\n", id_prize[i]),
						strcat(string_dialog, query);

					if(type_prize[i] == 13 && id_prize[i] == 1) 
						SCMF(playerid, COLOR_ORANGE, "{3599f5}Вам начислен приз {FFFFFF}Купон на выход из Деморгана (%d мин) {3599f5}за активацию бонус кода", count_prize[i]), 
						format(query, sizeof query, "Купон для выхода из тюрьмы Деморган (%d мин)", count_prize[i]),
						GivePlayerMyPrizes(playerid, query, 16, count_prize[i], 0, 0, 0),
						format(query, sizeof query, "{FFFFFF}- Купон для выхода из Деморган (%d мин)\n", count_prize[i]),
						strcat(string_dialog, query);
				}

				format
				(
					string_dialog, sizeof string_dialog, 
					"{bebfba}Вы успешно активировали бонус код и получили:\n\n\
					%s",
					string_dialog
				);
				IntfDialogCallRemote(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, "{FFFFFF}Успешная активация", string_dialog,"", "Хорошо");
			}
			else IntfDialogCallRemote(playerid, -1, DIALOG_STYLE_MSGBOX,"Ошибка активации","{bebfba}Достигнут лимит использований бонус кода","", "Хорошо");

			return 1;
		}

		case DIALOG_OWNABLE_GARAGE_OPLATA:
		{
			if(!response) return 1;

			new idx = GetPlayerListitemValue(playerid, listitem) + 1;
			SetPVarInt(playerid, "ownablegarage_id", idx);
			ShowPlayerGaragePayForRent(playerid);
		}

		case DIALOG_SELL_GARAGE_LIST:
		{
			if(!response) return 1;
			new idx = GetPlayerListitemValue(playerid, listitem) + 1;
			SetPVarInt(playerid, "ownablegarage_id", idx);

			new garage_id = GetPVarInt(playerid, "ownablegarage_id");
			if(garage_id != -1)
			{
				IntfDialogCallRemote
				(
					playerid, DIALOG_GARAGE_SELL, DIALOG_STYLE_MSGBOX,
					"{FFD83D}Продажа гаража",
					"{"#cW"}Вы уверены что хотите продать свой гараж государству?\n\n"\
					"Вам будет возвращена его стоимость за вычитом 30%\n"\
					"Также будет возвращено 60% от стоимости купленных улучшений\n\n"\
					"Если Вы хотите продать бизнес другому игроку,\n"\
					"используйте команду: {FFD83D}/sellmygarage",
					"Да", "Нет"
				);
			}
			else SendClientMessage(playerid, 0xFF6600FF, "У Вас нет гаража");
			return 1;
		}

		case DIALOG_INFO_GARAGE_LIST:
		{
			if(!response) return 1;
			new idx = GetPlayerListitemValue(playerid, listitem) + 1;
			SetPVarInt(playerid, "ownablegarage_id", idx);

			new garage_id = GetPVarInt(playerid, "ownablegarage_id");

			if(garage_id != -1)
			{
				string_dialog[0] = EOS;

				format
				(
					string_dialog, sizeof string_dialog,
					"{ffffff}Номер гаража:<t><t><t>%d\n",
					garage_id
				);

				format
				(
					string_dialog, sizeof string_dialog,
					"{ffffff}Владелец:<t><t><t><t>{339999}%s\n"\
					"%s{ffffff}Город / поселок:\t\t\t%s\n"\
					"Район:\t\t\t\t\t%s\n"\
					"Уровень улучшений:<t><t><t>%d\n"\
					"Гараж оплачен на:<t><t><t>%d/30 дней\n"\
					"Гос. стоимость:<t><t><t>%s\n"\
					"Арендная плата:<t><t><t>%d руб в день\n"\
					"Статус:<t><t><t><t><t>%s\n\n"\
					"{669966}Для открытия панели управления Вашим гаражом\n"\
					"нажмите кнопку 'Изменить'",
					GetGarageData(garage_id, G_OWNER_NAME),
					string_dialog,
					GetCityName(GetGarageData(garage_id, G_CITY)),
					GetZoneName(GetGarageData(garage_id, G_ZONE)),
					GetGarageData(garage_id, G_IMPROVEMENTS),
					GetGarageData(garage_id, G_RENT_DATE) <= gettime() ? 0 :
					GetElapsedTime(GetGarageData(garage_id, G_RENT_DATE), gettime(), CONVERT_TIME_TO_DAYS),
					formatInt(GetGarageData(garage_id, G_PRICE)),
					GetGarageData(garage_id, G_IMPROVEMENTS) > 0 ? (GetGarageData(garage_id, G_RENT_PRICE) / 2) : (GetGarageData(garage_id, G_RENT_PRICE)),
					GetGarageData(garage_id, G_LOCK_STATUS) ? ("{CC3333}Гараж закрыт") : ("{66CC33}Гараж открыт")
				);
				IntfDialogCallRemote(playerid, DIALOG_GARAGE_INFO, DIALOG_STYLE_MSGBOX, "{FFD83D}Информация о гараже", string_dialog, "Изменить", "Отмена");
			}
			else SendClientMessage(playerid, 0xFF6600FF, "У Вас нет гаража");
			return 1;
		}

		case DIALOG_SELL_MY_GARAGE_LIST:
		{
			if(!response) return 1;
			new idx = GetPlayerListitemValue(playerid, listitem) + 1;
			SetPVarInt(playerid, "ownablegarage_id", idx);

			new garageid = GetPVarInt(playerid, "ownablegarage_id");

			new price = GetPVarInt(playerid, "Sellprice");
			new to_player = GetPVarInt(playerid, "to_player");

			new Float: g_pos_x = GetGarageData(garageid, G_POS_X);
			new Float: g_pos_y = GetGarageData(garageid, G_POS_Y);
			new Float: g_pos_z = GetGarageData(garageid, G_POS_Z);

			if(!(IsPlayerInRangeOfPoint(playerid, 7.0, g_pos_x, g_pos_y, g_pos_z) && IsPlayerInRangeOfPoint(to_player, 7.0, g_pos_x, g_pos_y, g_pos_z)))
				SendClientMessage(playerid, 0xFF6600FF, "Вы и покупатель должны находиться рядом с бизнесом который хотите продать");

			SendPlayerOffer(playerid, to_player, OFFER_TYPE_SELL_GARAGE, garageid, price);

			return 1;
		}
		case DIALOG_CREATE_FAMILY:
            {
                if(!response) return 1;

                if(GetPlayerData(playerid, P_FAMILY) != 0) return SendClientMessage(playerid, 0xCECECEFF, "Вы уже состоите в семье");
                if(VerifyIntString(QueryPlayerBalance(playerid), 50000000))
                {
                    new str_len = strlen(inputtext);
					if(6 <= str_len <= 36)
					{
	                    new query[512],
	                        Cache: result,
	                        rows;

	                    mysql_format(mysql, query, sizeof query, "SELECT * FROM family WHERE name='%s'", inputtext);
	                    result = mysql_query(mysql, query, true);
	                    rows = cache_num_rows();
	                    cache_delete(result);

	                    if(rows)
	                    {
	                        SendClientMessage(playerid, 0xCECECEFF, "Данное имя уже используется");
						    IntfDialogCallRemote
						    (
						        playerid, DIALOG_CREATE_FAMILY, DIALOG_STYLE_INPUT,
						        "Создание семьи",
						        "{999999}- Цена: 50.000.000 рублей<n>\
								{999999}- Только русские и английские символы<n>\
								{999999}- Используйте от 6 до 36 символов<n>\
								{FFFFFF}Введите название Вашей семьи",
						        "Создать", "Отмена"
						    );
	                        return 1;
	                    }
	                    ModifyCashBalance(playerid, -50000000, "Создание семьи",true,true);
	                    SendClientMessage(playerid, 0x66CC00FF, "Вы успешно создали семью! {"#cGold"}Используйте /fmenu для информации.");

	                    new time = gettime();
	                    mysql_format
	                    (
	                        mysql, query, sizeof query,
	                        "INSERT INTO family "\
	                            "(name,u_id,time) "\
	                            "VALUES "\
	                            "('%e',%d,%d)",
	                        inputtext,
	                        GetPlayerAccountID(playerid),
	                        time
	                    );
	                    result = mysql_query(mysql, query);

	                    new fam_id = cache_insert_id();

	                    SetPlayerData(playerid, P_FAMILY, fam_id);
	                    SetPlayerData(playerid, P_FAMILY_RANK, 10);

	                    format(query, sizeof query, "UPDATE accounts_canvasdev SET family=%d, family_rank=%d WHERE id=%d LIMIT 1", GetPlayerData(playerid, P_FAMILY), GetPlayerData(playerid, P_FAMILY_RANK), GetPlayerAccountID(playerid));
						mysql_query(mysql, query, false);

	                    SetFamilyData(fam_id, F_SQL_ID, fam_id);
	                    format(g_family[fam_id][F_NAME], 64, "%s", inputtext);
						new text_str[144];
						format(text_str, 144, "{FFB500}%s", inputtext);
						g_player[playerid][P_FAM_LABEL] = CreateDynamic3DTextLabel(text_str, -1, 0.0, 0.0, 0.6, 14.0, playerid, INVALID_VEHICLE_ID, 1);
						
						new
							hour, minute,second,
							day, month, year;

						gettime(hour, minute,second);
						getdate(year, month, day);

	                    SetFamilyData(fam_id, F_TIME_DAY, day);
	                    SetFamilyData(fam_id, F_TIME_MOUNTH, month);
	                    SetFamilyData(fam_id, F_TIME_YEAR, year);

	                    SetFamilyData(fam_id, F_TIME_HOUR, hour);
	                    SetFamilyData(fam_id, F_TIME_MINUTE, minute);
	                    SetFamilyData(fam_id, F_TIME_SECOND, second);

	                    format(query, sizeof query, "UPDATE family SET day=%d, mounth=%d,year=%d,hour=%d,minute=%d,second=%d WHERE id=%d LIMIT 1", day,month,year,hour,minute,second, g_family[fam_id][F_SQL_ID]);
						mysql_query(mysql, query, false);

	                    SetFamilyData(fam_id, F_HOUSE_ID, -1);
	                    SetFamilyData(fam_id, F_USER_ID, GetPlayerAccountID(playerid));
	                    format(g_family[fam_id][F_RANK1], 32, "Терпила");
	                    format(g_family[fam_id][F_RANK2], 32, "Шнырь");
	                    format(g_family[fam_id][F_RANK3], 32, "Босяк");
	                    format(g_family[fam_id][F_RANK4], 32, "Барыга");
	                    format(g_family[fam_id][F_RANK5], 32, "Вор");
	                    format(g_family[fam_id][F_RANK6], 32, "Блатной");
	                    format(g_family[fam_id][F_RANK7], 32, "Пахан");
	                    format(g_family[fam_id][F_RANK8], 32, "Командир");
	                    format(g_family[fam_id][F_RANK9], 32, "Заместитель");
	                    format(g_family[fam_id][F_RANK10], 32, "Создатель");
	                    mysql_format(mysql, query, sizeof query, "UPDATE family SET rank1='%e', rank2='%e' WHERE id=%d LIMIT 1",
						GetFamilyData(fam_id, F_RANK1),GetFamilyData(fam_id, F_RANK2), g_family[fam_id][F_SQL_ID]);
						mysql_query(mysql, query, false);

						mysql_format(mysql, query, sizeof query, "UPDATE family SET rank3='%e', rank4='%e' WHERE id=%d LIMIT 1",
						GetFamilyData(fam_id, F_RANK3),GetFamilyData(fam_id, F_RANK4), g_family[fam_id][F_SQL_ID]);
						mysql_query(mysql, query, false);

						mysql_format(mysql, query, sizeof query, "UPDATE family SET rank5='%e', rank6='%e' WHERE id=%d LIMIT 1",
						GetFamilyData(fam_id, F_RANK5),GetFamilyData(fam_id, F_RANK6), g_family[fam_id][F_SQL_ID]);
						mysql_query(mysql, query, false);

						mysql_format(mysql, query, sizeof query, "UPDATE family SET rank7='%e',rank8='%e' WHERE id=%d LIMIT 1",
						GetFamilyData(fam_id, F_RANK7),GetFamilyData(fam_id, F_RANK8), g_family[fam_id][F_SQL_ID]);
						mysql_query(mysql, query, false);

						mysql_format(mysql, query, sizeof query, "UPDATE family SET rank9='%e', rank10='%e' WHERE id=%d LIMIT 1",
						GetFamilyData(fam_id, F_RANK9),GetFamilyData(fam_id, F_RANK10), g_family[fam_id][F_SQL_ID]);
						mysql_query(mysql, query, false);
						g_family_loaded ++;
						cache_delete(result);
					}
					else
					{
					    SendClientMessage(playerid, 0xCECECEFF, "* Кол-во символов от 6 до 36!");
					    IntfDialogCallRemote
					    (
					        playerid, DIALOG_CREATE_FAMILY, DIALOG_STYLE_INPUT,
					        "Создание семьи",
					        "{999999}- Цена: 50.000.000 рублей<n>\
							{999999}- Только русские и английские символы<n>\
							{999999}- Используйте от 6 до 36 символов<n>\
							{FFFFFF}Введите название Вашей семьи",
					        "Создать", "Отмена"
					    );
					}
                }
                else SendClientMessage(playerid, 0xCECECEFF, "*У Вас недостаточно денег");
            }
			case DIALOG_COLOR_GANG_CR:
			{
			    if(!response) return 1;

			    new fam_id = GetPlayerData(playerid, P_FAMILY),
					fmt_text[556];

			    SetFamilyData(fam_id, F_COLOR, list_id);
                SetFamilyData(fam_id, F_GANG, 1);
                SetFamilyData(fam_id, F_FAMILY_CARS, 10);
				SetFamilyData(fam_id, F_HOUSE_ID,GetPlayerHouse(playerid));
                mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE family SET color='%d',gang=1,house_id=%d,family_cars=10 WHERE id='%d' LIMIT 1", list_id,GetPlayerHouse(playerid), fam_id);
				mysql_query(mysql, fmt_text, false);
				foreach(new i : Player)
				{
					if(!IsPlayerConnected(i)) continue;
					else if(!IsPlayerLogged(i)) continue;
					if(GetPlayerData(i, P_FAMILY) == GetPlayerData(playerid, P_FAMILY))
					{
						DestroyDynamic3DTextLabel(g_player[i][P_FAM_LABEL]);
						g_player[i][P_FAM_LABEL] = Text3D: -1;
						SetPlayerColorEx(i, family_colors[GetFamilyData(GetPlayerData(i, P_FAMILY), F_COLOR)]);
						new text_str[144];
						format(text_str, 144, "{%06x}%s", family_colors[GetFamilyData(GetPlayerData(i, P_FAMILY), F_COLOR)] >>> 8, g_family[GetPlayerFamily(i)][F_NAME]);
						g_player[i][P_FAM_LABEL] = CreateDynamic3DTextLabel(text_str, -1, 0.0, 0.0, 0.6, 14.0, i, INVALID_VEHICLE_ID, 1);
					}
				}
		        new houseid = GetFamilyData(fam_id, F_HOUSE_ID);
		        new type = GetHouseData(houseid, H_TYPE);
				DestroyPickup(gangsklads[fam_id]);
				if(IsValidDynamic3DTextLabel(GetFamilyData(fam_id, F_SKLAD))) DestroyDynamic3DTextLabel(GetFamilyData(fam_id, F_SKLAD));
		        gangsklads[fam_id] = CreatePickup(1239, 23, GetHouseTypeInfo(type, HT_SKLAD_POS_X), GetHouseTypeInfo(type, HT_SKLAD_POS_Y), GetHouseTypeInfo(type, HT_SKLAD_POS_Z), houseid + 2000, PICKUP_ACTION_TYPE_SKLAD);

				SetFamilyData(fam_id, F_SKLAD, CreateDynamic3DTextLabel("", 0xFFFF00FF, GetHouseTypeInfo(type, HT_SKLAD_POS_X), GetHouseTypeInfo(type, HT_SKLAD_POS_Y), GetHouseTypeInfo(type, HT_SKLAD_POS_Z) + 1, 6.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, houseid + 2000, -1, -1, 50.0));
				CallLocalFunction("UpdateGangSklad", "i", fam_id);

				format(fmt_text, sizeof fmt_text, "<%s> Ваша семья стала бандой! База находится в доме №%d", GetFamilyData(fam_id, F_NAME), GetFamilyData(fam_id, F_HOUSE_ID));
				SendClientMessage(playerid, 0xFF9C18FF, fmt_text);
			}
            case DIALOG_FAMILY_FFF:
            {
                callcmd::fmenu(playerid, "");
            }
            case DIALOG_FAMILY_MENU:
            {
                if(!response) return 1;

                switch(listitem)
                {
                    case 0:
                    {
						new fmt_text[78],fmt_texts[30],
							list[sizeof fmt_text * 10 + 50] = "{ffffff}Имя<t>{ffffff}Телефон<n>";
						new pl,afk;
						foreach(new i : Player)
						{
							if(!IsPlayerConnected(i)) continue;
							else if(!IsPlayerLogged(i)) continue;
							if(GetPlayerData(i, P_FAMILY) == GetPlayerData(playerid, P_FAMILY))
							{
							    new namerank[40];
							    new fam_id = GetPlayerData(playerid, P_FAMILY);
							    new rank = GetPlayerData(i, P_FAMILY_RANK);
							    pl = pl+1;
							    if(IsPlayerAFK(i))
							    {
							        afk = afk +1;
							    }
							    if(rank == 1) format(namerank, sizeof namerank, "%s",GetFamilyData(fam_id, F_RANK1));
							    if(rank == 2) format(namerank, sizeof namerank, "%s",GetFamilyData(fam_id, F_RANK2));
							    if(rank == 3) format(namerank, sizeof namerank, "%s",GetFamilyData(fam_id, F_RANK3));
							    if(rank == 4) format(namerank, sizeof namerank, "%s",GetFamilyData(fam_id, F_RANK4));
							    if(rank == 5) format(namerank, sizeof namerank, "%s",GetFamilyData(fam_id, F_RANK5));
							    if(rank == 6) format(namerank, sizeof namerank, "%s",GetFamilyData(fam_id, F_RANK6));
							    if(rank == 7) format(namerank, sizeof namerank, "%s",GetFamilyData(fam_id, F_RANK7));
							    if(rank == 8) format(namerank, sizeof namerank, "%s",GetFamilyData(fam_id, F_RANK8));
							    if(rank == 9) format(namerank, sizeof namerank, "%s",GetFamilyData(fam_id, F_RANK9));
							    if(rank == 10) format(namerank, sizeof namerank, "%s",GetFamilyData(fam_id, F_RANK10));
								format(fmt_text, sizeof fmt_text, "1. %s[%d] {e65050}[%s]{ffffff}<t>%d<n>", GetPlayerNameEx(i), i, namerank,GetPlayerPhone(i));
								strcat(list, fmt_text);
								format(fmt_texts, sizeof fmt_texts, "{FFCD00}В игре: %d (%d в AFK)",pl,afk);
							}
						}

						IntfDialogCallRemote(playerid, DIALOG_FAMILY_FFF, 5, fmt_texts, list, "Назад", "");
                    }
                    case 1:
                    {
						new query[144],
							text[1440],
							Cache: result,
							rows;
						mysql_format(mysql, query, sizeof query, "SELECT * FROM accounts_canvasdev WHERE family='%d'", GetPlayerData(playerid, P_FAMILY));
						result = mysql_query(mysql, query);
						rows = cache_num_rows();

						for(new i = 0; i < rows; i++)
						{
							new name[21];

							cache_get_field_content(i, "name", name);
							new user_id = cache_get_field_content_int(i, "id");
							format(query, sizeof query, "%d. %s<n>", i+1, name);
							strcat(text, query);
							SetPlayerListitemValue(playerid, i, user_id);
						}

						cache_delete(result);

						IntfDialogCallRemote(playerid, DIALOG_FAMILY_PL, DIALOG_STYLE_LIST, "{FFCD00}Состав семьи", text, "Выгнать", "Отмена");
                    }
                    case 2: ShowFamilyInfo(playerid);
                    case 3:
                    {
					 	if(IsPlayerInRangeOfPoint(playerid, 35.0, 300.5571,304.2417,1001.0000)) //300.5571,304.2417,1001.0000
						{
							IntfDialogCallRemote(playerid, DIALOG_FAMILY_BANK, DIALOG_STYLE_LIST, "{FFCD00}Бюджет семьи", "1. Пополнить<n>2. Снять<n>3. История", "Принять", "Отмена");
						}
						else SendClientMessage(playerid, 0xCECECEFF, "*Вы не в банке");
                    }
                }
            }
            case DIALOG_GANG_MENU:
            {
                if(!response) return 1;
                switch(listitem)
                {
                    case 0:
                    {
						new fmt_text[78], fmt_texts[30];
						string_dialog = "{ffffff}Имя<t>{ffffff}Телефон<n>";
						new pl,afk;
						foreach(new i : Player)
						{
							if(!IsPlayerConnected(i)) continue;
							else if(!IsPlayerLogged(i)) continue;
							if(GetPlayerData(i, P_FAMILY) == GetPlayerData(playerid, P_FAMILY))
							{
							    new namerank[40];
							    new fam_id = GetPlayerData(playerid, P_FAMILY);
							    new rank = GetPlayerData(i, P_FAMILY_RANK);
							    pl = pl+1;

							    if(IsPlayerAFK(i)) afk = afk +1;

							    if(rank == 1) format(namerank, sizeof namerank, "%s",GetFamilyData(fam_id, F_RANK1));
							    if(rank == 2) format(namerank, sizeof namerank, "%s",GetFamilyData(fam_id, F_RANK2));
							    if(rank == 3) format(namerank, sizeof namerank, "%s",GetFamilyData(fam_id, F_RANK3));
							    if(rank == 4) format(namerank, sizeof namerank, "%s",GetFamilyData(fam_id, F_RANK4));
							    if(rank == 5) format(namerank, sizeof namerank, "%s",GetFamilyData(fam_id, F_RANK5));
							    if(rank == 6) format(namerank, sizeof namerank, "%s",GetFamilyData(fam_id, F_RANK6));
							    if(rank == 7) format(namerank, sizeof namerank, "%s",GetFamilyData(fam_id, F_RANK7));
							    if(rank == 8) format(namerank, sizeof namerank, "%s",GetFamilyData(fam_id, F_RANK8));
							    if(rank == 9) format(namerank, sizeof namerank, "%s",GetFamilyData(fam_id, F_RANK9));
							    if(rank == 10) format(namerank, sizeof namerank, "%s",GetFamilyData(fam_id, F_RANK10));

							    if(IsPlayerAFK(i)) format(fmt_text, sizeof fmt_text, "%d. %s[%d](AFK) {e65050}[%s]{ffffff}<t>%d<n>", pl,GetPlayerNameEx(i), i, namerank,GetPlayerPhone(i));
								else format(fmt_text, sizeof fmt_text, "%d. %s[%d] {e65050}[%s]{ffffff}<t>%d<n>", pl,GetPlayerNameEx(i), i, namerank,GetPlayerPhone(i));

								strcat(string_dialog, fmt_text);
								format(fmt_texts, sizeof fmt_texts, "{FFCD00}В игре: %d (%d в AFK)",pl,afk);
							}
						}
						IntfDialogCallRemote(playerid, DIALOG_FAMILY_FFF, 5, fmt_texts, string_dialog, "Назад", "");
                    }
                    case 1:
                    {
						string_dialog[0] = EOS;
						new query[144], Cache: result, rows;
						mysql_format(mysql, query, sizeof query, "SELECT * FROM accounts_canvasdev WHERE family='%d'", GetPlayerData(playerid, P_FAMILY));
						result = mysql_query(mysql, query);
						rows = cache_num_rows();

						for(new i = 0; i < rows; i++)
						{
							new name[21];

							cache_get_field_content(i, "name", name);
							new user_id = cache_get_field_content_int(i, "id");
							format(query, sizeof query, "%d. %s<n>", i+1, name);
							strcat(string_dialog, query);
							SetPlayerListitemValue(playerid, i, user_id);
						}
						cache_delete(result);
						IntfDialogCallRemote(playerid, DIALOG_FAMILY_PL, DIALOG_STYLE_LIST, "{FFCD00}Состав семьи", string_dialog, "Выгнать", "Отмена");
                    }
                    case 2: ShowFamilyInfo(playerid);
                    case 3:
                    {
					    if(GetPlayerData(playerid, P_FAMILY_RANK) != 10) return SendClientMessage(playerid, 0xCECECEFF, "У Вас нет доступа");

						new query[50];
					    for(new i = 0; i < 18; i ++)
						{
					    	format(query, sizeof query, "\"%06x\",", family_colors[i]);
							strcat(STRING_GLOBAL, query);
					    }
					  	new str_len;
						str_len = strlen(STRING_GLOBAL);
						strdel(STRING_GLOBAL, str_len - 1, str_len);
						format(STRING_GLOBAL, sizeof STRING_GLOBAL, "[\"Выберите цвет банды\", [%s], 1]",  STRING_GLOBAL);
						SetPVarInt(playerid,"colortype",2);
					    CEF_CREATE(playerid, 2, 4, "GangColor", STRING_GLOBAL);
                    }
                    case 4:
                    {
						new query[148],
							Cache: result,
							biz_id,
							biz_name[64];

						mysql_format(mysql, query, sizeof query, "SELECT * FROM business WHERE gang='%d'", GetPlayerData(playerid, P_FAMILY));
						result = mysql_query(mysql, query, true);

						new rows = cache_num_rows();

						if(!rows)
							return SendClientMessage(playerid, 0x999999FF, "У Вашей банды нет во владенни бизнесов.");

                        vibor_biz_atm[playerid] = 1;

						string_dialog[0] = EOS;
						for(new i = 0; i < rows; i ++)
						{
							biz_id = cache_get_field_content_int(i, "id");
							cache_get_field_content(i, "name", biz_name);

							format(query, sizeof query, "{FFFFFF} %s [%d]\n", biz_name, biz_id);
							strcat(string_dialog, query);
							SetPlayerListitemValue(playerid, i, biz_id-1);
						}
						IntfDialogCallRemote
						(
							playerid, DIALOG_GANG_BIZ, DIALOG_STYLE_LIST,
							"{FFCD00}Бизнесы банды",
							string_dialog,
							"Выбрать", "Закрыть"
						);
						cache_delete(result);
                    }
                    case 5: ViewFamilyCar(playerid);
                    case 6: ShowInfoGangSklad(playerid);
                    case 7:
                    {
                        if(GetPlayerData(playerid, P_FAMILY_RANK) == 10)
                        {
							IntfDialogCallRemote
							(
								playerid, DIALOG_GANG_RANG, DIALOG_STYLE_LIST,
								"{FFCD00}Настройка рангов",
								"1. Настройка склада<n>2. Настройка названий рангов",
								"Выбрать", "Закрыть"
							);
						}
						else SendClientMessage(playerid, 0xCECECEFF, "*Данное меню вам не доступно");
                    }
	           	}
            }
			case DIALOG_GANG_SK_EDIT:
			{
			    if(!response) return 1;
                new fam_id = GetPlayerData(playerid, P_FAMILY);
                switch(listitem)
                {
                    case 0:
                    {
						string_dialog[0] = EOS;
						new fmt_text[144];
					    format(fmt_text, sizeof fmt_text, "1. %s<n>",GetFamilyData(fam_id, F_RANK1));
					    strcat(string_dialog, fmt_text);
					    format(fmt_text, sizeof fmt_text, "2. %s<n>",GetFamilyData(fam_id, F_RANK2));
					    strcat(string_dialog, fmt_text);
					    format(fmt_text, sizeof fmt_text, "3. %s<n>",GetFamilyData(fam_id, F_RANK3));
					    strcat(string_dialog, fmt_text);
					    format(fmt_text, sizeof fmt_text, "4. %s<n>",GetFamilyData(fam_id, F_RANK4));
					    strcat(string_dialog, fmt_text);
					    format(fmt_text, sizeof fmt_text, "5. %s<n>",GetFamilyData(fam_id, F_RANK5));
					    strcat(string_dialog, fmt_text);
					    format(fmt_text, sizeof fmt_text, "6. %s<n>",GetFamilyData(fam_id, F_RANK6));
					    strcat(string_dialog, fmt_text);
					    format(fmt_text, sizeof fmt_text, "7. %s<n>",GetFamilyData(fam_id, F_RANK7));
					    strcat(string_dialog, fmt_text);
					    format(fmt_text, sizeof fmt_text, "8. %s<n>",GetFamilyData(fam_id, F_RANK8));
					    strcat(string_dialog, fmt_text);
					    format(fmt_text, sizeof fmt_text, "9. %s<n>",GetFamilyData(fam_id, F_RANK9));
					    strcat(string_dialog, fmt_text);
					    format(fmt_text, sizeof fmt_text, "10. %s<n>",GetFamilyData(fam_id, F_RANK10));
						strcat(string_dialog, fmt_text);
						IntfDialogCallRemote
						(
							playerid, DIALOG_GANG_SK_EDIT_1, DIALOG_STYLE_LIST,
							"{FFCD00}Выберите ранг для изменения",
							string_dialog,
							"Выбрать", "Закрыть"
						);
                    }
                    case 1:
                    {
						string_dialog[0] = EOS;
						new fmt_text[144];
					    format(fmt_text, sizeof fmt_text, "1. %s<n>",GetFamilyData(fam_id, F_RANK1));
					    strcat(string_dialog, fmt_text);
					    format(fmt_text, sizeof fmt_text, "2. %s<n>",GetFamilyData(fam_id, F_RANK2));
					    strcat(string_dialog, fmt_text);
					    format(fmt_text, sizeof fmt_text, "3. %s<n>",GetFamilyData(fam_id, F_RANK3));
					    strcat(string_dialog, fmt_text);
					    format(fmt_text, sizeof fmt_text, "4. %s<n>",GetFamilyData(fam_id, F_RANK4));
					    strcat(string_dialog, fmt_text);
					    format(fmt_text, sizeof fmt_text, "5. %s<n>",GetFamilyData(fam_id, F_RANK5));
					    strcat(string_dialog, fmt_text);
					    format(fmt_text, sizeof fmt_text, "6. %s<n>",GetFamilyData(fam_id, F_RANK6));
					    strcat(string_dialog, fmt_text);
					    format(fmt_text, sizeof fmt_text, "7. %s<n>",GetFamilyData(fam_id, F_RANK7));
					    strcat(string_dialog, fmt_text);
					    format(fmt_text, sizeof fmt_text, "8. %s<n>",GetFamilyData(fam_id, F_RANK8));
					    strcat(string_dialog, fmt_text);
					    format(fmt_text, sizeof fmt_text, "9. %s<n>",GetFamilyData(fam_id, F_RANK9));
					    strcat(string_dialog, fmt_text);
					    format(fmt_text, sizeof fmt_text, "10. %s<n>",GetFamilyData(fam_id, F_RANK10));
						strcat(string_dialog, fmt_text);
						IntfDialogCallRemote
						(
							playerid, DIALOG_GANG_SK_EDIT_2, DIALOG_STYLE_LIST,
							"{FFCD00}Выберите ранг для изменения",
							string_dialog,
							"Выбрать", "Закрыть"
						);
                    }
               	}
			}
            case DIALOG_GANG_RANG:
            {
                if(!response) return 1;
                if(GetPlayerData(playerid, P_FAMILY_RANK) == 10)
                {
                    new fam_id = GetPlayerData(playerid, P_FAMILY);
                    switch(listitem)
	                {
	                    case 0:
	                    {
							IntfDialogCallRemote
							(
								playerid, DIALOG_GANG_SK_EDIT, DIALOG_STYLE_LIST,
								"{FFCD00}Выберите предмет который хотите настроить",
								"1. Деньги<n> 2. Оружие",
								"Выбрать", "Закрыть"
							);
	                    }
	                    case 1:
	                    {

							string_dialog[0] = EOS;
							new fmt_text[144];
						    format(fmt_text, sizeof fmt_text, "1. %s<n>",GetFamilyData(fam_id, F_RANK1));
						    strcat(string_dialog, fmt_text);
						    format(fmt_text, sizeof fmt_text, "2. %s<n>",GetFamilyData(fam_id, F_RANK2));
						    strcat(string_dialog, fmt_text);
						    format(fmt_text, sizeof fmt_text, "3. %s<n>",GetFamilyData(fam_id, F_RANK3));
						    strcat(string_dialog, fmt_text);
						    format(fmt_text, sizeof fmt_text, "4. %s<n>",GetFamilyData(fam_id, F_RANK4));
						    strcat(string_dialog, fmt_text);
						    format(fmt_text, sizeof fmt_text, "5. %s<n>",GetFamilyData(fam_id, F_RANK5));
						    strcat(string_dialog, fmt_text);
						    format(fmt_text, sizeof fmt_text, "6. %s<n>",GetFamilyData(fam_id, F_RANK6));
						    strcat(string_dialog, fmt_text);
						    format(fmt_text, sizeof fmt_text, "7. %s<n>",GetFamilyData(fam_id, F_RANK7));
						    strcat(string_dialog, fmt_text);
						    format(fmt_text, sizeof fmt_text, "8. %s<n>",GetFamilyData(fam_id, F_RANK8));
						    strcat(string_dialog, fmt_text);
						    format(fmt_text, sizeof fmt_text, "9. %s<n>",GetFamilyData(fam_id, F_RANK9));
						    strcat(string_dialog, fmt_text);
						    format(fmt_text, sizeof fmt_text, "10. %s<n>",GetFamilyData(fam_id, F_RANK10));
							strcat(string_dialog, fmt_text);
							IntfDialogCallRemote
							(
								playerid, DIALOG_GANG_RANG_EDIT, DIALOG_STYLE_LIST,
								"{FFCD00}Выберите ранг для изменения",
								string_dialog,
								"Выбрать", "Закрыть"
							);
	                    }
	               }
                }
				else SendClientMessage(playerid, 0xCECECEFF, "*Данное меню вам не доступно");
            }
            case DIALOG_GANG_SK_EDIT_1:
            {
			    if(response)
                {
                    SetPVarInt(playerid, "listitems",listitem);
					IntfDialogCallRemote(playerid, DIALOG_GANG_SK_EDIT_3, DIALOG_STYLE_INPUT, "{FFCD00}Настройка рангов", "{FFFFFF}Введите кол-во патрон который сможет брать данный ранг:", "Приять", "Назад");
                }
            }
            case DIALOG_GANG_SK_EDIT_2:
            {
			    if(response)
                {
                    SetPVarInt(playerid, "listitems",listitem);
                 	IntfDialogCallRemote(playerid, DIALOG_GANG_SK_EDIT_4, DIALOG_STYLE_INPUT, "{FFCD00}Настройка рангов", "{FFFFFF}Введите кол-во денег который сможет брать данный ранг:", "Приять", "Назад");
                }
            }
			case DIALOG_GANG_RANG_EDIT:
			{
			    if(response)
                {
                    SetPVarInt(playerid, "listitems",listitem);
	                IntfDialogCallRemote(playerid, DIALOG_GANG_RANG_EDIT_1, DIALOG_STYLE_INPUT, "{FFCD00}Настройка рангов", "{FFFFFF}Введите название ранга которое хотите поставить:", "Приять", "Назад");
                }
			}
			case DIALOG_GANG_SK_EDIT_3:
			{
			    if(!response) return 1;
			    new put_sum = strval(inputtext);
			    if(!(100 <= put_sum <= 50000000)) return SendClientMessage(playerid, 0xCECECEFF, "Кол-во денег от 100 до 50.000.000");
			    new fam_id = GetPlayerData(playerid, P_FAMILY);
			    listitem = GetPVarInt(playerid, "listitems");
			    F_RANK_MON[fam_id][listitem] = put_sum;
			    new query[144];
			 	format(query, sizeof query, "UPDATE family SET mon_rank%d=%d WHERE id=%d LIMIT 1",listitem+1,F_RANK_MON[fam_id][listitem], g_family[fam_id][F_SQL_ID]);
				mysql_query(mysql, query, false);
			    SendClientMessage(playerid, 0xCECECEFF, "Вы успешно изменили кол-во денег, которое может брать данный ранг!");
			}
			case DIALOG_GANG_SK_EDIT_4:
			{
			    if(!response) return 1;
			    new put_sum = strval(inputtext);
			    if(!(10 <= put_sum <= 500)) return SendClientMessage(playerid, 0xCECECEFF, "Кол-во патрон от 100 до 500");
			    new fam_id = GetPlayerData(playerid, P_FAMILY);
			    listitem = GetPVarInt(playerid, "listitems");
			    F_RANK_PAT[fam_id][listitem] = put_sum;
				new query[144];
			 	format(query, sizeof query, "UPDATE family SET pat_rank%d=%d WHERE id=%d LIMIT 1",listitem+1,F_RANK_PAT[fam_id][listitem], g_family[fam_id][F_SQL_ID]);
				mysql_query(mysql, query, false);
			    SendClientMessage(playerid, 0xCECECEFF, "Вы успешно изменили кол-во патрон, которое может брать данный ранг!");
			}
			case DIALOG_GANG_RANG_EDIT_1:
			{
			    if(response)
                {
                    if(!(5 <= strlen(inputtext) <= 30)) return SendClientMessage(playerid, 0xCECECEFF, "Кол-во символов от 5 до 30");
                    new fam_id = GetPlayerData(playerid, P_FAMILY);
					listitem = GetPVarInt(playerid, "listitems");
                    if(listitem == 0)format(GetFamilyData(fam_id, F_RANK1), 31, "%s", inputtext);
                    if(listitem == 1)format(GetFamilyData(fam_id, F_RANK2), 31, "%s", inputtext);
                    if(listitem == 2)format(GetFamilyData(fam_id, F_RANK3), 31, "%s", inputtext);
                    if(listitem == 3)format(GetFamilyData(fam_id, F_RANK4), 31, "%s", inputtext);
                    if(listitem == 4)format(GetFamilyData(fam_id, F_RANK5), 31, "%s", inputtext);
                    if(listitem == 5)format(GetFamilyData(fam_id, F_RANK6), 31, "%s", inputtext);
                    if(listitem == 6)format(GetFamilyData(fam_id, F_RANK7), 31, "%s", inputtext);
                    if(listitem == 7)format(GetFamilyData(fam_id, F_RANK8), 31, "%s", inputtext);
                    if(listitem == 8)format(GetFamilyData(fam_id, F_RANK9), 31, "%s", inputtext);
					if(listitem == 9)format(GetFamilyData(fam_id, F_RANK10), 31, "%s", inputtext);

                    new query[255];
                    format(query, sizeof query, "UPDATE family SET rank1='%s', rank2='%s' WHERE id=%d LIMIT 1",
					GetFamilyData(fam_id, F_RANK1),GetFamilyData(fam_id, F_RANK2), g_family[fam_id][F_SQL_ID]);
					mysql_query(mysql, query, false);

					format(query, sizeof query, "UPDATE family SET rank3='%s', rank4='%s' WHERE id=%d LIMIT 1",
					GetFamilyData(fam_id, F_RANK3),GetFamilyData(fam_id, F_RANK4), g_family[fam_id][F_SQL_ID]);
					mysql_query(mysql, query, false);

					format(query, sizeof query, "UPDATE family SET rank5='%s', rank6='%s' WHERE id=%d LIMIT 1",
					GetFamilyData(fam_id, F_RANK5),GetFamilyData(fam_id, F_RANK6), g_family[fam_id][F_SQL_ID]);
					mysql_query(mysql, query, false);

					format(query, sizeof query, "UPDATE family SET rank7='%s',rank8='%s' WHERE id=%d LIMIT 1",
					GetFamilyData(fam_id, F_RANK7),GetFamilyData(fam_id, F_RANK8), g_family[fam_id][F_SQL_ID]);
					mysql_query(mysql, query, false);

					format(query, sizeof query, "UPDATE family SET rank9='%s', rank10='%s' WHERE id=%d LIMIT 1",
					GetFamilyData(fam_id, F_RANK9),GetFamilyData(fam_id, F_RANK10), g_family[fam_id][F_SQL_ID]);
					mysql_query(mysql, query, false);
                    SendClientMessage(playerid, 0xCECECEFF, "Вы успешно изменили название ранга!");
                }
			}
			case DIALOG_FAMILY_PL:
			{
                if(!response) return 1;
                if(GetPlayerData(playerid, P_FAMILY_RANK) < 9) return SendClientMessage(playerid, 0xCECECEFF, "*Данное меню вам не доступно");
				new idx = GetPlayerListitemValue(playerid, listitem);

				SetPVarInt(playerid, "listitem_fam", listitem);
				SetPVarInt(playerid, "acc_id", idx);

				new query[144],
					Cache: result,
					rows;
				mysql_format(mysql, query, sizeof query, "SELECT * FROM accounts_canvasdev WHERE id='%d'", idx);
				result = mysql_query(mysql, query);
				rows = cache_num_rows();

				for(new i = 0; i < rows; i++)
				{
					new name[21];
					new namerank[20];
					new rank = cache_get_field_content_int(i, "family_rank");
					new fam_id = cache_get_field_content_int(i, "family");
				    if(rank == 1) format(namerank, sizeof namerank, "%s",GetFamilyData(fam_id, F_RANK1));
				    if(rank == 2) format(namerank, sizeof namerank, "%s",GetFamilyData(fam_id, F_RANK2));
				    if(rank == 3) format(namerank, sizeof namerank, "%s",GetFamilyData(fam_id, F_RANK3));
				    if(rank == 4) format(namerank, sizeof namerank, "%s",GetFamilyData(fam_id, F_RANK4));
				    if(rank == 5) format(namerank, sizeof namerank, "%s",GetFamilyData(fam_id, F_RANK5));
				    if(rank == 6) format(namerank, sizeof namerank, "%s",GetFamilyData(fam_id, F_RANK6));
				    if(rank == 7) format(namerank, sizeof namerank, "%s",GetFamilyData(fam_id, F_RANK7));
				    if(rank == 8) format(namerank, sizeof namerank, "%s",GetFamilyData(fam_id, F_RANK8));
				    if(rank == 9) format(namerank, sizeof namerank, "%s",GetFamilyData(fam_id, F_RANK9));
				    if(rank == 10) format(namerank, sizeof namerank, "%s",GetFamilyData(fam_id, F_RANK10));
					cache_get_field_content(i, "name", name);
					format(query, sizeof query, "{FFFFFF}Игрок: %s<n>Положение: %s",  name, namerank);
				}
				cache_delete(result);
				IntfDialogCallRemote(playerid, DIALOG_FAMILY_PLA, DIALOG_STYLE_MSGBOX, "{FFCD00}Состав семьи", query, "Выгнать", "Отмена");
			}
			case DIALOG_FAMILY_PLA:
			{
			    if(!response) return 1;
			    if(GetPlayerData(playerid, P_FAMILY_RANK) < 9) return SendClientMessage(playerid, 0xCECECEFF, "*Данное меню вам не доступно");
			    new id = GetPVarInt(playerid, "acc_id");
			    new fmt_str[144],Cache: result;

				mysql_format(mysql, fmt_str, sizeof fmt_str, "SELECT * FROM accounts_canvasdev WHERE id='%d'", id);
				result = mysql_query(mysql, fmt_str);

				new rows = cache_num_rows();

				for(new i = 0; i < rows; i++)
				{
				    new rank = cache_get_field_content_int(i, "family_rank");
				    if(GetPlayerData(playerid, P_FAMILY_RANK) == rank)
				    {
				        return SendClientMessage(playerid, 0xCECECEFF, "*Вы не можете выгнать данного человека!");
				    }
				    if(rank == 10)
				    {
				        return SendClientMessage(playerid, 0xCECECEFF, "*Вы не можете выгнать данного человека!");
				    }
				}
			 	format(fmt_str, sizeof fmt_str, "UPDATE accounts_canvasdev SET family=0,family_rank=0 WHERE id=%d LIMIT 1", id);
    			mysql_query(mysql, fmt_str, false);
    			cache_delete(result);
				foreach(new i: Player)
				{
					if(!IsPlayerConnected(i)) continue;
					if(!IsPlayerLogged(i)) continue;
					if(GetPlayerData(i, P_FAMILY) == 0) continue;
					if(GetPlayerData(i, P_FAMILY) != GetPlayerData(playerid, P_FAMILY)) continue;
					if(id == GetPlayerAccountID(i))
					{
					    SetPlayerData(i, P_FAMILY,0);
					    SetPlayerData(i, P_FAMILY_RANK,0);
						DestroyDynamic3DTextLabel(g_player[i][P_FAM_LABEL]);
						g_player[i][P_FAM_LABEL] = Text3D: -1;
						SetPlayerColorEx(i, GetPlayerTeamColor(i));
					}
				}
			}
            case DIALOG_FAMILY_BANK_PUT:
            {
                if(response)
                {
	                new put_sum = strval(inputtext);
	                if(put_sum > 0 && IsNumeric(inputtext))
	                {

	                    new fmt_str[155];

						if(VerifyIntString(QueryPlayerBalance(playerid), put_sum))
	                    {
	                        format(fmt_str, sizeof fmt_str, "UPDATE accounts_canvasdev a,family f SET a.money=%s,f.money=f.money + %d WHERE a.id=%d AND f.id=%d", SetILPlayerInt(playerid, QueryPlayerBalance(playerid), -put_sum), put_sum, GetPlayerAccountID(playerid), GetPlayerData(playerid, P_FAMILY) + 1);
	                        mysql_query(mysql, fmt_str, false);

	                        if(!mysql_errno())
	                        {
	                            AddFamilyData(GetPlayerData(playerid, P_FAMILY), F_MONEY, +, put_sum);
	                            ModifyCashBalance(playerid, -put_sum, "Пополнение банка семьи", false, true);

	                            new fmt_msg[144];

	                            format(fmt_msg, sizeof fmt_msg, "<%s> %s[%d] пополнил бюджет семьи на %d руб. Бюджет %d руб.", GetFamilyData(GetPlayerData(playerid, P_FAMILY), F_NAME), GetPlayerNameEx(playerid), playerid, put_sum,GetFamilyData(GetPlayerData(playerid, P_FAMILY), F_MONEY));

								foreach(new i: Player)
								{
									if(!IsPlayerConnected(i)) continue;
									if(!IsPlayerLogged(i)) continue;
									if(GetPlayerData(i, P_FAMILY) == 0) continue;
									if(GetPlayerData(i, P_FAMILY) != GetPlayerData(playerid, P_FAMILY)) continue;

									SendClientMessage(i, 0xFF4D18FF, fmt_msg);
								}
	                        }
	                        else SendClientMessage(playerid, 0xCECECEFF, "Ошибка сохранения, повторите попытку {FF0000}(equ-code 09)");
	                    }
	                    else SendClientMessage(playerid, 0xFFFFFFFF, "Недостаточно средств");
	                }
                }
                else IntfDialogCallRemote(playerid, DIALOG_FAMILY_BANK, DIALOG_STYLE_LIST, "{FFCD00}Бюджет семьи", "1. Пополнить<n>2. Снять<n>3. История", "Принять", "Отмена");

            }
            case DIALOG_FAMILY_BANK_PICK:
            {
                if(response)
                {
	                new put_sum = strval(inputtext);
	                if(put_sum > 0 && IsNumeric(inputtext))
	                {

	                    new fmt_str[155];

	                    if(GetPlayerData(playerid, P_FAMILY) >= put_sum)
	                    {
	                        format(fmt_str, sizeof fmt_str, "UPDATE accounts_canvasdev a,family f SET a.money=%s,f.money=f.money + %d WHERE a.id=%d AND f.id=%d", SetILPlayerInt(playerid, QueryPlayerBalance(playerid), put_sum), -put_sum, GetPlayerAccountID(playerid), GetPlayerData(playerid, P_FAMILY) + 1);
	                        mysql_query(mysql, fmt_str, false);

	                        if(!mysql_errno())
	                        {
	                            AddFamilyData(GetPlayerData(playerid, P_FAMILY), F_MONEY, -, put_sum);
	                            ModifyCashBalance(playerid, put_sum, "снятие с банка семьи", false, true);

	                            new fmt_msg[144];

	                            format(fmt_msg, sizeof fmt_msg, "<%s> %s[%d] снял с бюджета семьи на %d руб. Бюджет %d руб.", GetFamilyData(GetPlayerData(playerid, P_FAMILY), F_NAME), GetPlayerNameEx(playerid), playerid, put_sum,GetFamilyData(GetPlayerData(playerid, P_FAMILY), F_MONEY));

								foreach(new i: Player)
								{
									if(!IsPlayerConnected(i)) continue;
									if(!IsPlayerLogged(i)) continue;
									if(GetPlayerData(i, P_FAMILY) == 0) continue;
									if(GetPlayerData(i, P_ADVISOR_BLOCK_CHAT)) continue;

									if(GetPlayerData(i, P_FAMILY) != GetPlayerData(playerid, P_FAMILY)) continue;

									SendClientMessage(i, 0xFF4D18FF, fmt_msg);
								}
	                        }
	                        else SendClientMessage(playerid, 0xCECECEFF, "Ошибка сохранения, повторите попытку {FF0000}(equ-code 09)");
	                    }
	                    else SendClientMessage(playerid, 0xFFFFFFFF, "Недостаточно средств на счете семьи");
	                }
                }
                else IntfDialogCallRemote(playerid, DIALOG_FAMILY_BANK, DIALOG_STYLE_LIST, "{FFCD00}Бюджет семьи", "1. Пополнить<n>2. Снять<n>3. История", "Принять", "Отмена");
            }
            case DIALOG_FAMILY_BANK:
            {
                if(response)
                {
                    switch(listitem)
                    {
                        case 0:
                        {
                            IntfDialogCallRemote(playerid, DIALOG_FAMILY_BANK_PUT, DIALOG_STYLE_INPUT, "{FFCD00}Бюджет семьи", "{FFFFFF}Введите количество, которое хотите положить:", "Приять", "Назад");
                        }
                        case 1:
                        {
                            new fmt_texts[144];
                            format(fmt_texts, sizeof fmt_texts, "{FFFFFF}Доступно: {FFCD00}%d руб.<n><n>{FFFFFF}Введите количество, которое хотите снять:",GetFamilyData(GetPlayerData(playerid, P_FAMILY), F_MONEY));
                            IntfDialogCallRemote(playerid, DIALOG_FAMILY_BANK_PICK, DIALOG_STYLE_INPUT, "{FFCD00}Бюджет семьи", fmt_texts, "Приять", "Назад");
                        }
                        case 2:
                        {
                        }
                    }
                }
                else callcmd::fmenu(playerid, "");

            }
            case DIALOG_FAMILY_LEAVE:
            {
                new fmt_text[110];
                if(response)
                {
                    new fam_id = GetPlayerData(playerid, P_FAMILY);

                    format(fmt_text, sizeof fmt_text, "<%s> %s[%d]: покинул семью по собственному желанию",
                    GetFamilyData(fam_id, F_NAME), GetPlayerNameEx(playerid), playerid);

                    foreach(new i: Player)
                    {
                        if(!IsPlayerConnected(i)) continue;
                        if(!IsPlayerLogged(i)) continue;
                        if(GetPlayerData(i, P_FAMILY) == 0) continue;
                        if(GetPlayerData(i, P_ADVISOR_BLOCK_CHAT)) continue;

                        if(GetPlayerData(i, P_FAMILY) != GetPlayerData(playerid, P_FAMILY)) continue;

                        SendClientMessage(i, 0xCECECEFF, fmt_text);
                    }

                    format(fmt_text, sizeof fmt_text, "Вы покинули семью \"%s\"", GetFamilyData(fam_id, F_NAME));
                    SendClientMessage(playerid, 0xFFFF00FF, fmt_text);

                    FUnInvite(playerid, playerid);
                }
            }
            case DIALOG_FAMILY_RANG:
            {
                if(!response) return callcmd::fmenu(playerid, "");

                new fam_id = GetPlayerData(playerid, P_FAMILY),
                    desc[32] = "";

                switch(listitem)
                {
                    case 0: strcat(desc, g_family[fam_id][F_RANK1]);
                    case 1: strcat(desc, g_family[fam_id][F_RANK2]);
                    case 2: strcat(desc, g_family[fam_id][F_RANK3]);
                    case 3: strcat(desc, g_family[fam_id][F_RANK4]);
                    case 4: strcat(desc, g_family[fam_id][F_RANK5]);
                    case 5: strcat(desc, g_family[fam_id][F_RANK6]);
                    case 6: strcat(desc, g_family[fam_id][F_RANK7]);
                    case 7: strcat(desc, g_family[fam_id][F_RANK8]);
                    case 8: strcat(desc, g_family[fam_id][F_RANK9]);
                    case 9: strcat(desc, g_family[fam_id][F_RANK10]);
                }

                SetPVarInt(playerid, "userang", listitem+1);
                IntfDialogCallRemote
                (
                    playerid, DIALOG_FAMILY_RCHANGE, DIALOG_STYLE_INPUT,
                    desc,
                    "{FFFFFF}Введите название, которое Вы хотите {d8284c}установить:",
                    "Далее", "Отмена"
                );
            }
			case DIALOG_OWNABLE_HOME_FAMILY:
			{
				if(!response) return 1;

				new idx = GetPlayerListitemValue(playerid, listitem) + 1;
				SetPVarInt(playerid, "ownablehouse_id", idx);
				new houseids = GetPVarInt(playerid, "ownablehouse_id");

				if(g_family[GetPlayerFamily(playerid)][F_GANG] == 1)
				{
					new fmt_text[144];
					new fam_id = GetPlayerData(playerid, P_FAMILY);
					SetFamilyData(fam_id, F_HOUSE_ID, houseids);
					mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE family SET house_id=%d WHERE id='%d' LIMIT 1", houseids, fam_id);
					mysql_query(mysql, fmt_text, false);
					format(fmt_text, sizeof fmt_text, "<%s> База банды теперь находится в доме №%d", GetFamilyData(fam_id, F_NAME), GetFamilyData(fam_id, F_HOUSE_ID));

					foreach(new i: Player)
					{
						if(!IsPlayerConnected(i)) continue;
						if(!IsPlayerLogged(i)) continue;
						if(GetPlayerData(i, P_FAMILY) == 0) continue;
						if(GetPlayerData(i, P_ADVISOR_BLOCK_CHAT)) continue;

						if(GetPlayerData(i, P_FAMILY) != GetPlayerData(playerid, P_FAMILY)) continue;

						SendClientMessage(playerid, 0xFF9C18FF, fmt_text);
					}
					new houseid = GetFamilyData(fam_id, F_HOUSE_ID);
					new type = GetHouseData(houseid, H_TYPE);
					DestroyPickup(gangsklads[fam_id]);
					if(IsValidDynamic3DTextLabel(GetFamilyData(fam_id, F_SKLAD))) DestroyDynamic3DTextLabel(GetFamilyData(fam_id, F_SKLAD));
					gangsklads[fam_id] = CreatePickup(1239, 23, GetHouseTypeInfo(type, HT_SKLAD_POS_X), GetHouseTypeInfo(type, HT_SKLAD_POS_Y), GetHouseTypeInfo(type, HT_SKLAD_POS_Z), houseid + 2000, PICKUP_ACTION_TYPE_SKLAD);

					SetFamilyData(fam_id, F_SKLAD, CreateDynamic3DTextLabel("", 0xFFFF00FF, GetHouseTypeInfo(type, HT_SKLAD_POS_X), GetHouseTypeInfo(type, HT_SKLAD_POS_Y), GetHouseTypeInfo(type, HT_SKLAD_POS_Z) + 1, 6.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, houseid + 2000, -1, -1, 50.0));
					CallLocalFunction("UpdateGangSklad", "i", fam_id);
				}
			}
            case DIALOG_FAMILY_RCHANGE:
            {
                if(!response) return callcmd::fmenu(playerid, "");

                new fmt_text[556],
                    rang_id = GetPVarInt(playerid, "userang"),
                    fam_id = GetPlayerData(playerid, P_FAMILY);

                switch(rang_id)
                {
                    case 1:
                    {
                        format(g_family[fam_id][F_RANK1], 32, inputtext);
                        mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE family SET rank1='%s' WHERE id='%d' LIMIT 1", inputtext, fam_id + 1);
                        mysql_query(mysql, fmt_text, false);
                    }
                    case 2:
                    {
                        format(g_family[fam_id][F_RANK2], 32, inputtext);
                        mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE family SET rank2='%s' WHERE id='%d' LIMIT 1", inputtext, fam_id + 1);
                        mysql_query(mysql, fmt_text, false);
                    }
                    case 3:
                    {
                        format(g_family[fam_id][F_RANK3], 32, inputtext);
                        mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE family SET rank3='%s' WHERE id='%d' LIMIT 1", inputtext, fam_id + 1);
                        mysql_query(mysql, fmt_text, false);
                    }
                    case 4:
                    {
                        format(g_family[fam_id][F_RANK4], 32, inputtext);
                        mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE family SET rank4='%s' WHERE id='%d' LIMIT 1", inputtext, fam_id + 1);
                        mysql_query(mysql, fmt_text, false);
                    }
                    case 5:
                    {
                        format(g_family[fam_id][F_RANK5], 32, inputtext);
                        mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE family SET rank5='%s' WHERE id='%d' LIMIT 1", inputtext, fam_id + 1);
                        mysql_query(mysql, fmt_text, false);
                    }
                    case 6:
                    {
                        format(g_family[fam_id][F_RANK6], 32, inputtext);
                        mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE family SET rank6='%s' WHERE id='%d' LIMIT 1", inputtext, fam_id + 1);
                        mysql_query(mysql, fmt_text, false);
                    }
                    case 7:
                    {
                        format(g_family[fam_id][F_RANK7], 32, inputtext);
                        mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE family SET rank7='%s' WHERE id='%d' LIMIT 1", inputtext, fam_id + 1);
                        mysql_query(mysql, fmt_text, false);
                    }
                    case 8:
                    {
                        format(g_family[fam_id][F_RANK8], 32, inputtext);
                        mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE family SET rank8='%s' WHERE id='%d' LIMIT 1", inputtext, fam_id + 1);
                        mysql_query(mysql, fmt_text, false);
                    }
                    case 9:
                    {
                        format(g_family[fam_id][F_RANK9], 32, inputtext);
                        mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE family SET rank9='%s' WHERE id='%d' LIMIT 1", inputtext, fam_id + 1);
                        mysql_query(mysql, fmt_text, false);
                    }
                    case 10:
                    {
                        format(g_family[fam_id][F_RANK10], 32, inputtext);
                        mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE family SET rank10='%s' WHERE id='%d' LIMIT 1", inputtext, fam_id + 1);
                        mysql_query(mysql, fmt_text, false);
                    }
                }

                format(fmt_text, sizeof fmt_text, "Вы успешно изменили название ранга {d8284c}№%d {1E90FF}на {d8284c}\"%s\"", rang_id, inputtext);
                SendClientMessage(playerid, 0x1E90FFFF, fmt_text);
            }
            case DIALOG_FAMILY_CAR_ADD:
            {
            	if(response)
				{
					if(GetPlayerData(playerid, P_FAMILY) == 0) return SendClientMessage(playerid, 0xCECECEFF, "Вы не состоите в семье");
					if(GetPlayerData(playerid, P_FAMILY_RANK) != 10) return SendClientMessage(playerid, 0xCECECEFF, "У Вас нет доступа");
					if(!IsPlayerInAnyVehicle(playerid))
						return SendClientMessage(playerid, 0xCECECEFF, "Вы должны находиться в транспорте");

					new vehicleid = GetPlayerVehicleID(playerid);
					new query[144];


					new vehicleid1 = GetPlayerOwnableCarLast(playerid);

					if(vehicleid1 != GetPlayerVehicleID(playerid))
					return SendClientMessage(playerid, 0xFF6600FF, "Вы должны находиться в личном транспорте");

					new idx = GetVehicleData(vehicleid, V_ACTION_ID);
					SetOwnableCarData(idx, OC_FAM_CAR, GetPlayerData(playerid, P_FAMILY));
					SetOwnableCarData(idx, OC_FAM_CAR_RANK, 1);
					mysql_format(mysql, query, sizeof query, "UPDATE ownable_cars SET famcar=%d, famcarrank=%d WHERE id=%d", GetOwnableCarData(idx, OC_FAM_CAR),GetOwnableCarData(idx, OC_FAM_CAR_RANK), GetOwnableCarData(idx, OC_SQL_ID));
					mysql_query(mysql, query, false);
					new color = family_color_car[GetFamilyData(GetPlayerData(playerid, P_FAMILY), F_COLOR)][0];
					ChangeVehicleColor(vehicleid, color, color);
					SendClientMessage(playerid, 0xCECECEFF, "Вы успешно добавили свой транспорт себе в семью!");
				}
            }
            case DIALOG_FAMILY_CAR_REMOVE:
            {
            	if(response)
				{
					if(GetPlayerData(playerid, P_FAMILY) == 0) return SendClientMessage(playerid, 0xCECECEFF, "Вы не состоите в семье");
					if(GetPlayerData(playerid, P_FAMILY_RANK) != 10) return SendClientMessage(playerid, 0xCECECEFF, "У Вас нет доступа");
					if(!IsPlayerInAnyVehicle(playerid))
						return SendClientMessage(playerid, 0xCECECEFF, "Вы должны находиться в транспорте");

					new vehicleid = GetPlayerVehicleID(playerid);
					new query[144];


					new vehicleid1 = GetPlayerOwnableCarLast(playerid);

					if(vehicleid1 != GetPlayerVehicleID(playerid))
					return SendClientMessage(playerid, 0xFF6600FF, "Вы должны находиться в личном транспорте");
					new idx = GetVehicleData(vehicleid, V_ACTION_ID);
					SetOwnableCarData(idx, OC_FAM_CAR, 0);
					SetOwnableCarData(idx, OC_FAM_CAR_RANK, 0);
					mysql_format(mysql, query, sizeof query, "UPDATE ownable_cars SET famcar=%d, famcarrank=%d WHERE id=%d", GetOwnableCarData(idx, OC_FAM_CAR),GetOwnableCarData(idx, OC_FAM_CAR_RANK), GetOwnableCarData(idx, OC_SQL_ID));
					mysql_query(mysql, query, false);
					ChangeVehicleColor(vehicleid, GetOwnableCarData(idx, OC_COLOR_1), GetOwnableCarData(idx, OC_COLOR_2));
					SendClientMessage(playerid, 0xCECECEFF, "Вы успешно убрали свой транспорт со своей семьи!");
				}
			}
			case DIALOG_FAMILY_DELL:
			{
			    if(!response) return 1;
			    
				new fam_id = GetPlayerData(playerid, P_FAMILY),
					query[80];

				format(query, sizeof query, "UPDATE family SET u_id=-1,name='delete' WHERE id=%d LIMIT 1", g_family[fam_id][F_SQL_ID]);
				mysql_query(mysql, query, false);

				DestroyPickup(gangsklads[fam_id]);
				if(IsValidDynamic3DTextLabel(GetFamilyData(fam_id, F_SKLAD))) DestroyDynamic3DTextLabel(GetFamilyData(fam_id, F_SKLAD));

				foreach(new i : Player)
				{
					if(!IsPlayerConnected(i)) continue;
					else if(!IsPlayerLogged(i)) continue;
					if(GetPlayerData(i, P_FAMILY) == GetPlayerData(playerid, P_FAMILY))
					{
						DestroyDynamic3DTextLabel(g_player[i][P_FAM_LABEL]);
						SetPlayerColorEx(i, GetPlayerTeamColor(i));
						SCMF(i, 0x1E90FFFF, "Внимание! Владелец удалил семью %s, в которой вы состоите", GetFamilyData(fam_id, F_NAME));
						SetPlayerData(i, P_FAMILY,0);
						SetPlayerData(i, P_FAMILY_RANK,0);

				        format(query, sizeof query, "UPDATE accounts_canvasdev SET family=%d,family_rank=%d WHERE id=%d",GetPlayerData(i, P_FAMILY), GetPlayerData(i, P_FAMILY_RANK), GetPlayerAccountID(i));
				        mysql_query(mysql, query, false);
					}
				}
			}
			case DIALOG_OWNABLE_CAR_FAMILY:
			{
			    if(response)
				{
					new vehicleid = INVALID_VEHICLE_ID;
					new idx = GetPVarInt(playerid, "ownablecar_id");
	                for(new i = 0; i < MAX_VEHICLES; i++)
					{
					    if(GetVehicleData(i, V_ACTION_TYPE) == VEHICLE_ACTION_TYPE_FAMILY_CAR)
					    {
						    new iddx = GetVehicleData(i, V_ACTION_ID);
					        if(GetOwnableCarData(iddx,OC_SQL_ID) == idx)
					        {
					            vehicleid = i;
					        }
				        }

					}
					if(vehicleid != INVALID_VEHICLE_ID)
					{
						switch(listitem + 1)
						{
						    case 1:
						    {
								if(GetPlayerGPSInfo(playerid, G_ENABLED) == GPS_STATUS_OFF)
								{
									if(VerifyIntString(QueryPlayerBalance(playerid), 300))
									{
										ModifyCashBalance(playerid, -300, "Метка ТС на GPS", true, true);

										new Float: x, Float: y, Float: z;
										GetVehiclePos(vehicleid, x, y, z);

										EnablePlayerGPS(playerid, 55, x, y, z, "Местоположение Вашего транспорта отмечено на GPS");
										return 1;
									}
									else SendClientMessage(playerid, 0x999999FF, "Недостаточно денег");
								}
								else SendClientMessage(playerid, 0xCECECEFF, "На Вашем GPS уже отмечено место");
						    }
							case 2: // Открыть / закрыть
							{
								if(VerifyIntString(QueryPlayerBalance(playerid), 1000))
								{
									SetPVarInt(playerid, "go_list", 1);
									SetVehicleToRespawn(vehicleid);
									ModifyCashBalance(playerid, -1000, "респавн тс семьи", true, true);
								}
								else SendClientMessage(playerid, 0x999999FF, "Недостаточно денег");
							}
							case 3: // Выгрузить транспорт
							{
//							    new famid = GetPlayerData(playerid, P_FAMILY);
								if(UnloadFamilyOwnableCar(vehicleid))
									SendClientMessage(playerid, 0x66CC33FF, "Транспорт успешно выгружен!");
							}
							case 4: // Выгрузить транспорт
							{
								SetPVarInt(playerid, "veh_id", vehicleid);
								IntfDialogCallRemote
								(
									playerid, DIALOG_FAMILT_CAR_RANK, DIALOG_STYLE_INPUT,
									"Изменение доступа ранга траспорта банды",
									"{FFFFFF} Введите какой хотите поставить ранг у траспорта\n\
									Доступный ранг, который можно поставить от 1 до 9",
									"Поставить", "Назад"
								);
							}
						}
					}
				}
			}
			case DIALOG_FAM_CAR_LIST:
			{
				if(response)
				{
					new idx = GetPlayerListitemValue(playerid, listitem);

					SetPVarInt(playerid, "listitem_car", listitem);
					new Cache: result;
					new famid = GetPlayerData(playerid, P_FAMILY);
					SetPVarInt(playerid, "ownablecar_id", idx);
	//					new famid = GetPlayerData(playerid, P_FAMILY);


					new veh_id = INVALID_VEHICLE_ID;

					for(new i = 0; i < MAX_VEHICLES; i++)
					{
						if(GetVehicleData(i, V_ACTION_TYPE) == VEHICLE_ACTION_TYPE_FAMILY_CAR)
						{
							new iddx = GetVehicleData(i, V_ACTION_ID);
							if(GetOwnableCarData(iddx,OC_SQL_ID) == idx)
							{
								veh_id = i;
							}
						}

					}


					if(veh_id == INVALID_VEHICLE_ID)
					{
						//ShowOwnableCarLoadDialog(playerid, idx, true);
						if(LoadFamilyCar(famid,idx) != -1)
						{
							SendClientMessage(playerid, 0x66CC33FF, "Данный траспорт успешно загружен!");
							SendClientMessage(playerid, -1, "Чтобы открыть данный транспорт пропишите: /lock 4.");
						}
						else SendClientMessage(playerid, 0x999999FF, "Ошибка при загрузке транспорта семьи");
					}
					else
					{
						ShowOwnableCarFamilyLoadDialog(playerid, idx, true);
					}
					cache_delete(result);
				}
			}
			case DIALOG_FAMILT_CAR_RANK:
			{
			    if(response)
				{
				    new rang = strval(inputtext);
				    if(1 <= rang <= 9)
				    {
	        			new query[100];
	                    new vehicleid = GetPVarInt(playerid, "veh_id"), index = GetVehicleData(vehicleid, V_ACTION_ID);
	                    SetOwnableCarData(index, OC_RANG, rang);
	                    mysql_format(mysql, query, sizeof query, "UPDATE family_cars SET rang = '%d' WHERE id='%d'",rang, GetOwnableCarData(index, OC_SQL_ID));
	                    mysql_query(mysql, query, false);
	                    SendClientMessage(playerid, -1, "Вы успешно изменили ранг-доступ данному трансопрту");
	               	}
	               	else
	               	{
	               	    SendClientMessage(playerid, -1, "Допустимый ранг от 1 до 9!");
						IntfDialogCallRemote
						(
							playerid, DIALOG_FAMILT_CAR_RANK, DIALOG_STYLE_INPUT,
							"Изменение доступа ранга траспорта банды",
							"{FFFFFF} Введите какой хотите поставить ранг у траспорта\n\
							Доступный ранг, который можно поставить от 1 до 9",
							"Поставить", "Назад"
						);
	               	}
				}
			}
			case DIALOG_GANG_CAR_ADD:
		{
			if(response)
			{
				new vehicleid = GetPlayerOwnableCarLast(playerid);
				new fam_id = GetPlayerData(playerid,P_FAMILY);
				new query[1024],Cache: result;
				new index = GetVehicleData(vehicleid, V_ACTION_ID);
				new Float: x,Float: y,Float: z,Float: angle;
				GetVehiclePos(vehicleid, x, y, z); // узнаем координаты авто
				GetVehicleZAngle(vehicleid, angle);

				mysql_format(mysql, query, sizeof query, "DELETE FROM ownable_cars WHERE id=%d", GetOwnableCarData(index, OC_SQL_ID));
				mysql_query(mysql, query, false);
				format
				(
					query, sizeof query,
					"INSERT INTO family_cars \
					(owner_id,model_id,color_1,color_2,pos_x,pos_y,pos_z,angle,create_time,diski,gidra,mileage,iznos,gryaz,vinil,typenumber,number,region,obves,tonerinstall) \
					VALUES \
					('%d','%d','%d','%d','%f','%f','%f','%f','%d','%d','%d','%f','%d','%f','%d','%d','%s','%s','%s','%d')",
					fam_id,
					GetOwnableCarData(index, OC_MODEL_ID),
					GetOwnableCarData(index, OC_COLOR_1),
					GetOwnableCarData(index, OC_COLOR_2),
					x,
					y,
					z,
					angle,
					gettime(),
					GetOwnableCarData(index, OC_DISKI),
					GetOwnableCarData(index, OC_GIDRA),
					GetVehicleData(vehicleid, V_MILEAGE),
					GetVehicleData(vehicleid, V_IZNOS),
					GetVehicleData(vehicleid, V_GRYAZ),
					GetOwnableCarData(index, OC_VINIL),
					GetOwnableCarData(index, OC_NUMBERTYPE),
					GetOwnableCarData(index, OC_NUMBER),
					GetOwnableCarData(index, OC_REGION),
					GetOwnableCarData(index, OC_OBVES),
					GetOwnableCarData(index, OC_TONERINSTALL)
				);
				result = mysql_query(mysql, query, true);
				cache_delete(result);
				SendClientMessage(playerid, 0x66CC00FF, "Вы успешно отдали данный транспорт в использование свой банды.");
				SetOwnableCarData(index, OC_CREATE, 0);
				DestroyVehicleLabel(vehicleid);
				DestroyVehicle(vehicleid);
				SetVehicleData(vehicleid, V_LAST_LOAD_TIME, 0);

			}
		}
		case DIALOG_GANG_CAR_DELL:
		{
			if(response)
			{
				new vehicleid = GetFamilyOwnableCarLast(playerid,GetPlayerData(playerid, P_FAMILY));
				new query[1024],Cache: result;
				new index = GetVehicleData(vehicleid, V_ACTION_ID);
				new Float: x,Float: y,Float: z,Float: angle;
				GetVehiclePos(vehicleid, x, y, z); // узнаем координаты авто
				GetVehicleZAngle(vehicleid, angle);

				mysql_format(mysql, query, sizeof query, "DELETE FROM family_cars WHERE id=%d", GetOwnableCarData(index, OC_SQL_ID));
				mysql_query(mysql, query, false);
				format
				(
					query, sizeof query,
					"INSERT INTO ownable_cars \
					(owner_id,model_id,color_1,color_2,pos_x,pos_y,pos_z,angle,create_time,diski,gidra,vinil,typenumber,number,region,obves,tonerinstall) \
					VALUES \
					('%d','%d','%d','%d','%f','%f','%f','%f','%d','%d','%d','%d','%d','%s','%s','%s','%d')",
					GetPlayerAccountID(playerid),
					GetOwnableCarData(index, OC_MODEL_ID),
					GetOwnableCarData(index, OC_COLOR_1),
					GetOwnableCarData(index, OC_COLOR_2),
					x,
					y,
					z,
					angle,
					gettime(),
					GetOwnableCarData(index, OC_DISKI),
					GetOwnableCarData(index, OC_GIDRA),
					GetOwnableCarData(index, OC_VINIL),
					GetOwnableCarData(index, OC_NUMBERTYPE),
					GetOwnableCarData(index, OC_NUMBER),
					GetOwnableCarData(index, OC_REGION),
					GetOwnableCarData(index, OC_OBVES),
					GetOwnableCarData(index, OC_TONERINSTALL)
				);

				result = mysql_query(mysql, query, true);
				cache_delete(result);

				SendClientMessage(playerid, 0x66CC00FF, "Вы успешно забрали данный транспорт со своей банды.");

				SetOwnableCarData(index, OC_OWNER_ID, 0);
				DestroyVehicleLabel(vehicleid);

				DestroyVehicle(vehicleid);

				SetVehicleData(vehicleid, V_LAST_LOAD_TIME, 0);
			}
		}
		case DIALOG_STOP_TESTDRIVE:
		{
			if(!response) return 1;

            DestroyVehicle(g_temp_vehicle2[playerid]);
            g_temp_vehicle2[playerid] = INVALID_VEHICLE_ID;
			CEF_HIDE(playerid, "Interactions");
			SCM(playerid, 0x6699CCFF, "{ecf96a}Тест-драйв {FFFFFF}донат-пакета {ecf96a}был завершён.");
			GameText(playerid, "~g~Тест-Драйв Завершён", 3000, 2);
			TestDrive[playerid] = 0;
			KillTimer(testdrive_timer[playerid]);
			SetPlayerVirtualWorld(playerid, 0);
			SetVehicleVirtualWorld(g_temp_vehicle2[playerid], 0);
			CEF_HIDE(playerid, "InformationTimer");
			if(PosTestDrive[playerid] == 1)
            {
                SetPlayerPos(playerid, 1919.7533,-1978.5594,31.5505);
                SetPlayerFacingAngle(playerid, 142.9231);
                PosTestDrive[playerid] = 0;
            }
            if(PosTestDrive[playerid] == 2)
            {
                SetPlayerPos(playerid, 1867.2260,2803.1262,12.0000);
                SetPlayerFacingAngle(playerid, 125.4598);
                PosTestDrive[playerid] = 0;
	        }
            if(PosTestDrive[playerid] == 3)
            {
               SetPlayerPos(playerid, -1938.8820,2909.1531,5.9990);
               SetPlayerFacingAngle(playerid, 264.6414);
               PosTestDrive[playerid] = 0;
            }
            if(PosTestDrive[playerid] == 4)
            {
               SetPlayerPos(playerid, -1912.2034,1917.0387,175.2322);
               SetPlayerFacingAngle(playerid, 0.0000);
               PosTestDrive[playerid] = 0;
	        }
            if(PosTestDrive[playerid] == 5)
            {
               SetPlayerPos(playerid, -406.2524,746.5653,12.2882);
               SetPlayerFacingAngle(playerid, 75.3678);
               PosTestDrive[playerid] = 0;
            }
		}
		case DIALOG_BUY_DONATE_PACK_1:
		{
			if(!response) return 1;

			if(QueryPlayerDonationBalance(playerid) < 55000) return GameText(playerid, "~r~Недостаточно~n~средств", 3000, 2);

			GiveCar(playerid, 17404, 1, 1, -1, -1, -1765.9470, 2911.2585, 5.8822, 90.4859, gettime());

			ProcessPlayerCredit(playerid, -55000);
			SCM(playerid, 0x6699CCFF, "{FF8800}Вы успешно приобрели набор 'R8 Titan'");
			GameText(playerid, "~r~~h~Успешно", 3000, 2);
		}
		case DIALOG_TEST_DRIVE:
		{
			if(!response) return 1;

            SCM(playerid, COLOR_LightSeaGreen, "{ecf96a}Вы попали на тест-драйв {FFFFFF}донат-пакета. {ecf96a}У вас есть {FF0000}3 минуты.");
			format(STRING_GLOBAL, sizeof STRING_GLOBAL, "[\"До конца тест-драйва\",%d]", 179);
			CEF_CREATE(playerid, 2, 4, "InformationTimer", STRING_GLOBAL);
		    testdrive_timer[playerid] = SetTimer("TestDrivePack", 179000, false);
		    CEF_HIDE(playerid, "Interactions");
			CEF_CREATE(playerid, 2, 4, "Interactions", "[[-1, \"Завершить тест драйв\"]]");
		    CEF_HIDE(playerid, "DonateItem");
			GameText(playerid, "~g~Тест-Драйв начат", 3000, 2);
			TestDrive[playerid] = 1;
            if(IsPlayerInRangeOfPoint(playerid,6.0, 1920.7385,-1977.4579,31.5505))
	        {
                g_temp_vehicle2[playerid] = CreateVehicle(17401, 1926.6510, -1979.0786, 31.1686, 59.7267, 0, 0, -1);
	            PutPlayerInVehicle(playerid, g_temp_vehicle2[playerid], 0);
	            SetPlayerVirtualWorld(playerid, 259);
			    SetVehicleVirtualWorld(g_temp_vehicle2[playerid], 259);
			    PosTestDrive[playerid] = 1;
	        }
	        if(IsPlayerInRangeOfPoint(playerid,6.0, 1867.4656,2803.1958,12.0000))
	        {
                g_temp_vehicle2[playerid] = CreateVehicle(17401, 1870.7363, 2809.5242, 11.6234, 359.5703, 0, 0, -1);
	            PutPlayerInVehicle(playerid, g_temp_vehicle2[playerid], 0);
	            SetPlayerVirtualWorld(playerid, 259);
			    SetVehicleVirtualWorld(g_temp_vehicle2[playerid], 259);
			    PosTestDrive[playerid] = 2;
	        }
            if(IsPlayerInRangeOfPoint(playerid,6.0, -1938.8953,2909.2773,5.9990))
	        {
                g_temp_vehicle2[playerid] = CreateVehicle(17401, -1943.3036, 2911.9465, 5.6206, 91.0131, 0, 0, -1);
	            PutPlayerInVehicle(playerid, g_temp_vehicle2[playerid], 0);
	            SetPlayerVirtualWorld(playerid, 259);
			    SetVehicleVirtualWorld(g_temp_vehicle2[playerid], 259);
			    PosTestDrive[playerid] = 3;
			}
  	        if(IsPlayerInRangeOfPoint(playerid,6.0, -1912.2034,1917.0387,175.2322))
	        {
                g_temp_vehicle2[playerid] = CreateVehicle(17401, -1913.9109, 1912.3358, 174.7725, 179.5422, 0, 0, -1);
	            PutPlayerInVehicle(playerid, g_temp_vehicle2[playerid], 0);
	            SetPlayerVirtualWorld(playerid, 259);
			    SetVehicleVirtualWorld(g_temp_vehicle2[playerid], 259);
			    PosTestDrive[playerid] = 4;
	        }
	        if(IsPlayerInRangeOfPoint(playerid,6.0, -406.3729,746.4713,12.2904))
	        {
                g_temp_vehicle2[playerid] = CreateVehicle(17401, -412.8358, 763.3583, 12.0024, 270.0263, 0, 0, -1);
	            PutPlayerInVehicle(playerid, g_temp_vehicle2[playerid], 0);
	            SetPlayerVirtualWorld(playerid, 259);
			    SetVehicleVirtualWorld(g_temp_vehicle2[playerid], 259);
			    PosTestDrive[playerid] = 5;
	        }
		}
		case DIALOG_FREE_HEAL:
		{
			if(response)
			{
				if(!VerifyIntString(QueryPlayerBalance(playerid), 2000000)) return SendClientMessage(playerid, 0xFF6600FF, "Медицинская помощь стоит 2.000.000 рублей");
				{
					ModifyCashBalance(playerid, -2000000, "Медицинская помощь");
					SetPlayerData(playerid, P_HEALTH, 70.0);
					SetPlayerHealthEx(playerid, 70.0);
					GameText(playerid, "~b~+70 здоровья", 4000, 2);
					ApplyAnimation(playerid, "ped", "gum_eat", 4.0, 0, 0, 0, 0, 0, 0);
					return 1;
				}
			}
		}
			case DIALOG_KEYSN: if(response) GiveIteam(playerid, 284, 1, 1, 0);
			case DIALOG_KEYST: if(response) GiveIteam(playerid, 261, 1, 1, 0);

			
			case DIALOG_SELL_MYSTALL:
			{
			    new idx = GetPlayerListitemValue(playerid, listitem) + 1;
			    new businessid = idx;
			    
			    new Float: g_pos_x = GetKioskData(businessid, K_POS_X);
				new Float: g_pos_y = GetKioskData(businessid, K_POS_Y);
				new Float: g_pos_z = GetKioskData(businessid, K_POS_Z);

				if(!(IsPlayerInRangeOfPoint(playerid, 7.0, g_pos_x, g_pos_y, g_pos_z) && IsPlayerInRangeOfPoint(GetPVarInt(playerid, "to_player"), 7.0, g_pos_x, g_pos_y, g_pos_z)))
					return SendClientMessage(playerid, 0xFF6600FF, "Вы и покупатель должны находиться рядом с киоском который хотите продать");

			    SendPlayerOffer(playerid, GetPVarInt(playerid, "to_player"), OFFER_TYPE_SELL_KIOSK, businessid, GetPVarInt(playerid, "price"));
			}
			case DIALOG_SELL_ITEM_ACCEPT:
			{
				if(!response) return 1;

				new kiosk_id = GetNearestKiosk(playerid, 7.0);
				new item_id = GetPVarInt(playerid, "SellItem");
				new count = GetPVarInt(playerid, "SellItemCount");
				new price = GetPVarInt(playerid, "SellItemPrice");
				new index = GetPVarInt(playerid, "SellItemIndx");
				new query[512];

				mysql_format(mysql, query, sizeof query, "INSERT INTO kiosks_items (kiosk_id, item_id, owner_id, name, count, price, indx) VALUES (%d, %d, %d, '%s', %d, %d, %d)", GetKioskData(kiosk_id, K_SQL_ID), item_id, GetPlayerAccountID(playerid), GetPlayerNameEx(playerid), count, price, index);
				mysql_query(mysql, query, false);

				GiveIteam(playerid, item_id, 0, count, index, "Выставил предмет в киоск");

				SCM(playerid, 0xADCEEAFF, "Вы успешно выставили предмет на продажу");
			}
			case DIALOG_SELL_NUMBER_ACCEPT:
			{
				if(!response) return 1;
				new kiosk_id = GetNearestKiosk(playerid, 7.0);

				new slot = GetPVarInt(playerid, "SellItemSlot");
				new type = GetPVarInt(playerid, "SellItemType");

				new price = GetPVarInt(playerid, "SellItemPrice");
				new query[512], number[32], region[32], typenumber;

				for(new i; i < MAX_PLAYER_ITEMS; i++)
				{
					if(GetPlayerItem(i, PI_OWNER_ID) != GetPlayerAccountID(playerid)) continue;
					if(GetPlayerItem(i, PI_SLOTS) != slot) continue;
					if(GetPlayerItem(i, PI_TYPE) != type) continue;

					format(number, 32, "%s", GetPlayerItem(i, PI_NUMBER));
					format(region, 32, "%s", GetPlayerItem(i, PI_REGION));

					typenumber = GetPlayerItem(i, PI_TYPENUMBER);

					mysql_format(mysql, query, sizeof query, "INSERT INTO kiosks_items (kiosk_id, item_id, owner_id, name, count, price, number, region, typenumber, aks_id, typeacs, indx, skin_id, item_type) VALUES (%d, 0, %d, '%s', 1, %d, '%s', '%s', %d, 0, 0, 0, 0, 1)",
					GetKioskData(kiosk_id, K_SQL_ID), GetPlayerAccountID(playerid), GetPlayerNameEx(playerid), price, number, region, typenumber);
					mysql_query(mysql, query, false);

					mysql_format(mysql, query, sizeof query, "DELETE FROM items WHERE slots=%d AND type=%d AND owner_id=%d LIMIT 1", slot, type, GetPlayerAccountID(playerid));
					mysql_query(mysql, query, false);

					DeleteItems(i);

					SCM(playerid, 0xADCEEAFF, "Вы успешно выставили автомобильный номер на продажу");
					return 1;
				}
			}
			case DIALOG_SELL_ACS_ACCEPT:
			{
				if(!response) return 1;
				new kiosk_id = GetNearestKiosk(playerid, 7.0);
				new slot = GetPVarInt(playerid, "SellItemSlot");
				new type = GetPVarInt(playerid, "SellItemType");
				new price = GetPVarInt(playerid, "SellItemPrice");
				new query[512], indx, aks_id, typeacs, status;

				for(new i; i < MAX_PLAYER_ITEMS; i++)
				{
					if(GetPlayerItem(i, PI_OWNER_ID) != GetPlayerAccountID(playerid)) continue;
					if(GetPlayerItem(i, PI_SLOTS) != slot) continue;
					if(GetPlayerItem(i, PI_TYPE) != type) continue;

					typeacs = GetPlayerItem(i, PI_TYPEACS);
					aks_id = GetPlayerItem(i, PI_AKS_ID);
					indx = GetPlayerItem(i, PI_INDX);
					status = GetPlayerItem(i, PI_STATUS);

					if(status == 0)
					{
						mysql_format(mysql, query, sizeof query, "INSERT INTO kiosks_items (kiosk_id, item_id, owner_id, name, count, price, aks_id, typeacs, indx, skin_id, item_type) VALUES (%d, 0, %d, '%s', 1, %d, %d, %d, %d, 0, 2)",
						GetKioskData(kiosk_id, K_SQL_ID), GetPlayerAccountID(playerid), GetPlayerNameEx(playerid), price, aks_id, typeacs, indx);
						mysql_query(mysql, query, false);

						mysql_format(mysql, query, sizeof query, "DELETE FROM items WHERE slots=%d AND type=%d AND owner_id=%d LIMIT 1", slot, type, GetPlayerAccountID(playerid));
						mysql_query(mysql, query, false);

						SCM(playerid, 0xADCEEAFF, "Вы успешно выставили аксессуар на продажу");

						DeleteItems(i);
					}
					else if(status == 1)
					{
						SCM(playerid, 0xADCEEAFF, "Для того чтобы продать аксессуар, нужно его снять");
					}
					return 1;
				}
			}
			case DIALOG_SELL_SKIN_ACCEPT:
			{
				if(!response) return 1;
				new kiosk_id = GetNearestKiosk(playerid, 7.0);
				new slot = GetPVarInt(playerid, "SellItemSlot");
				new type = GetPVarInt(playerid, "SellItemType");
				new price = GetPVarInt(playerid, "SellItemPrice");
				new query[512], skin_id;

				for(new i; i < MAX_PLAYER_ITEMS; i++)
				{
					if(GetPlayerItem(i, PI_OWNER_ID) != GetPlayerAccountID(playerid)) continue;
					if(GetPlayerItem(i, PI_SLOTS) != slot) continue;
					if(GetPlayerItem(i, PI_TYPE) != type) continue;

					skin_id = GetPlayerItem(i, PI_SKIN_ID);

					if(GetPlayerSkin(playerid) == skin_id) SetPlayerSkin(playerid, 252);

					mysql_format(mysql, query, sizeof query, "INSERT INTO kiosks_items (kiosk_id, item_id, owner_id, name, count, price, skin_id, item_type) VALUES (%d, 0, %d, '%s', 1, %d, %d, 3)",
					GetKioskData(kiosk_id, K_SQL_ID), GetPlayerAccountID(playerid), GetPlayerNameEx(playerid), price, skin_id);
					mysql_query(mysql, query, false);

					mysql_format(mysql, query, sizeof query, "DELETE FROM items WHERE slots=%d AND type=%d AND owner_id=%d LIMIT 1", slot, type, GetPlayerAccountID(playerid));
					mysql_query(mysql, query, false);

					DeleteItems(i);

					SCM(playerid, 0xADCEEAFF, "Вы успешно выставили свою одежду на продажу");
					return 1;
				}
			}
			case DIALOG_STALL_BUY_ITEM_ACCEPT:
			{
				if(!response) return 1;

				new kiosk_id = GetNearestKiosk(playerid, 7.0);
				new item_id = GetPVarInt(playerid, "item_id");
				new index = GetPVarInt(playerid, "indx_items");
				new price = GetPVarInt(playerid, "price");
				new count = GetPVarInt(playerid, "count");
				new count1 = GetPVarInt(playerid, "count1"); // сколько есть в бд
				new owner_id = GetPVarInt(playerid, "owner_id");
				new id = GetPVarInt(playerid, "id");

				if(GetStallItemsId(id) == -1) return SCM(playerid, COLOR_BLUENEW, "Данный предемет был продан или снят с продажи.");

				if(!VerifyIntString(QueryPlayerBalance(playerid), price)) return SCM(playerid, 0xADCEEAFF, "У вас недостаточно средств.");

				ModifyCashBalance(playerid, -price, "Покупка предмета в киоске");

				format(g_kiosk[kiosk_id][K_BALANCE], 21, "%s", SetILPlayerInt(playerid, g_kiosk[kiosk_id][K_BALANCE], (price / 100) * GetKioskData(kiosk_id, K_NALOG)));

                new fmt_str_st[512];
				mysql_format(mysql, fmt_str_st, sizeof fmt_str_st, "UPDATE kiosk SET balance=%s WHERE id=%d", GetKioskData(kiosk_id, K_BALANCE),GetKioskData(kiosk_id, K_SQL_ID));
				mysql_query(mysql, fmt_str_st, false);

				GiveIteam(playerid, item_id, 1, count, index);

				CEF_HIDE(playerid, "Stall");

				if(count1 - count != 0)
				{
					new query[512];
					format(query, sizeof query, "UPDATE kiosks_items SET count=%d WHERE id=%d LIMIT 1", count1 - count, id);
					mysql_query(mysql, query, false);
				}
				else
				{
					new query[512];
					mysql_format(mysql, query, sizeof query, "DELETE FROM kiosks_items WHERE id=%d", id);
					mysql_query(mysql, query, false);
				}

				new to_player = GetPlayerIDBySqlID(owner_id);

				if(IsPlayerConnected(to_player) && IsPlayerLogged(to_player))
				{
					ModifyCashBalance(to_player, price - ((price / 100) * GetKioskData(kiosk_id, K_NALOG)), "продажа предмета в киоске");
					SCM(to_player, 0xADCEEAFF, "Ваш предмет в киоске приобрели.");
				}
				else
				{
					new fmt_str[512];

					format(fmt_str, sizeof fmt_str, "UPDATE accounts_canvasdev SET bank = bank + %d WHERE id=%d LIMIT 1", price - ((price / 100) * GetKioskData(kiosk_id, K_NALOG)), owner_id);
					mysql_query(mysql, fmt_str, false);
				}

			}
			case DIALOG_STALL_BUY_ITEM:
			{
				if(!response) return 1;

				new count = strval(inputtext);
				new item_id = GetPVarInt(playerid, "item_id");
				new price = GetPVarInt(playerid, "price");
				new have_count = GetPVarInt(playerid, "count");
				new id = GetPVarInt(playerid, "id");
				new str_c[268];

				if(GetStallItemsId(id) == -1) return SCM(playerid, COLOR_BLUENEW, "Данный предемет был продан или снят с продажи.");

				if(count < 1) return SCM(playerid, 0xADCEEAFF, "Нкорректное количество товара.");

				if(count > have_count) return SCM(playerid, 0xADCEEAFF, "В этом киоске нет этого товара в таком количестве.");

				if(count > 25) return SCM(playerid, COLOR_RED, "За раз можно купить до 25 вещей!"), DLGF(playerid, DIALOG_STALL_BUY_ITEM, DIALOG_STYLE_INPUT, "Покупка предмета", "{FFFFFF}Сколько вы желаете приобрести?\nНа продаже: {006400}%d {FFFFFF}ед.", "Далее", "Назад", count);

				new sellprice = price * count;

				SetPVarInt(playerid, "price", sellprice);
				SetPVarInt(playerid, "count", count);

				format(str_c, sizeof str_c, "{FFFFFF}Товар: {FECC00}'%s'\n{FFFFFF}Количество: {FECC00}%d\n{FFFFFF}Стоимость: {FECC00}%d руб.", ItemsInfo[item_id][i_item_name], count, sellprice);
				IntfDialogCallRemote(playerid, DIALOG_STALL_BUY_ITEM_ACCEPT, DIALOG_STYLE_MSGBOX, "Желаете приобрести?", str_c, "Да", "Нет");
			}
			case DIALOG_SET_NALOG:
			{
				if(!response) return 1;

				new kiosk_id = GetNearestKiosk(playerid, 7.0);
				new nalog = strval(inputtext);
				new query[512];

				if(nalog < 1) return SCM(playerid, 0xCECECEFF, "* Налог не должен быть меньше 1 процента.");
				if(nalog > 25) return SCM(playerid, 0xCECECEFF, "* Налог не должен превышать 25 процентов.");

				mysql_format(mysql, query, sizeof query, "UPDATE kiosk SET nalog=%d WHERE id=%d", nalog, GetKioskData(kiosk_id, K_SQL_ID));
				mysql_query(mysql, query, false);

				SetKioskData(kiosk_id, K_NALOG, nalog);

				SCMF(playerid, 0xADCEEAFF, "Вы успешно поставили налог в {FFFFFF}%d процентов", nalog);
			}
			case DIALOG_REMOVE_OWNED_ITEM:
			{
				if(!response) return 1;

				new item_id = GetPVarInt(playerid, "item_id");
				new count = GetPVarInt(playerid, "count");
				new query[512];

				GiveIteam(playerid, item_id, 1, count, 0);

				SCM(playerid, 0xADCEEAFF, "Вы сняли ваш предмет с продажи.");

				mysql_format(mysql, query, sizeof query, "DELETE FROM kiosks_items WHERE id=%d", GetPVarInt(playerid, "id"));
				mysql_query(mysql, query, false);

				CEF_HIDE(playerid, "Stall");
			}
			case DIALOG_REMOVE_STALL_ITEM:
			{
				if(!response) return DeletePVar(playerid, "RemoveItem");

				new kiosk_id = GetNearestKiosk(playerid, 7.0);
				new item_id = GetPVarInt(playerid, "RemoveItem");

				new query[264], 
					number[32], 
					region[32], 
					Cache:result;

				SCM(playerid, 0xADCEEAFF, "Вы сняли предмет с продажи");

				format(query, sizeof query, "SELECT * FROM kiosks_items WHERE kiosk_id=%d AND id=%d", kiosk_id, GetPVarInt(playerid, "ItemSQLid"));
				result = mysql_query(mysql, query, true);

				cache_get_field_content(0, "region", region);
				cache_get_field_content(0, "number", number);

				new owner_id = cache_get_field_content_int(0, "owner_id");
				new count = cache_get_field_content_int(0, "count");
				new typenumber = cache_get_field_content_int(0, "typenumber");
				new aks_id = cache_get_field_content_int(0, "aks_id");
				new typeacs = cache_get_field_content_int(0, "typeacs");
				new indx = cache_get_field_content_int(0, "indx");
				new skin_id = cache_get_field_content_int(0, "skin_id");
				new item_type = cache_get_field_content_int(0, "item_type");
				new player = GetPlayerIDBySqlID(owner_id);

				cache_delete(result);

				if(IsPlayerConnected(player) && IsPlayerLogged(player))
				{
					SCM(player, 0xABCDEFFF, "Пока вы находились вне игры, вам вернули товары из киоска, используйте {FFFFFF}/return_items {ABCDEF}чтобы забрать их.");

					if(item_type == 0) GiveIteam(player, item_id, 1, count, 0);

					if(item_type == 1)
					{
						CreateItemsCarNumber(GetPlayerAccountID(player), 1, -1, -1, number, region, typenumber, -1, -1, 0, 1);
					}
					if(item_type == 2)
					{
						CreateItemsAcs(GetPlayerAccountID(player), 1, -1, -1, aks_id, typeacs, 0, indx, -1, -1, 0, 2);
					}
					if(item_type == 3)
					{

						CreateItemsSkin(GetPlayerAccountID(player), 1, -1, -1, skin_id, 0, -1, -1, 0, 3);
					}
				}
				else
				{
					if(item_type == 1)
					{
						CreateItemsCarNumber(owner_id, 1, -1, -1, number, region, typenumber, -1, -1, 0, 1);
					}
					if(item_type == 2)
					{
						CreateItemsAcs(owner_id, 1, -1, -1, aks_id, typeacs, 0, indx, -1, -1, 0, 2);
					}
					if(item_type == 3)
					{
						CreateItemsSkin(owner_id, 1, -1, -1, skin_id, 0, -1, -1, 0, 3);
					}
				}
				format(query, sizeof query, "DELETE FROM kiosks_items WHERE id=%d", GetPVarInt(playerid, "ItemSQLid"));
				mysql_query(mysql, query, false);

				DeletePVar(playerid, "RemoveItem");
				DeletePVar(playerid, "ItemSQLid");
			}
			
			case DIALOG_BUY_STALL:
			{
				if(!response) return 1;
				
				new kiosk_id = GetPVarInt(playerid, "buy_stall");

				if((GetPlayerOwnableKiosk(playerid) + 1) > GetPlayerKioskSlots(playerid)) return SendClientMessage(playerid, 0x3399FFFF, "Вы уже имеете максимально количество бизнес компаний.");
				if(!VerifyIntString(QueryPlayerBalance(playerid), GetKioskData(kiosk_id, K_PRICE))) return SCM(playerid, -1, "*Недостаточно средств.");

				new query[512];

				//SetPlayerData(playerid, P_KIOSK, kiosk_id);
				//UpdatePlayerDatabaseInt(playerid, "kiosk", kiosk_id);

				SetKioskData(kiosk_id, K_OWNER_ID, GetPlayerAccountID(playerid));

				mysql_format(mysql, query, sizeof query, "UPDATE kiosk SET owner_id=%d WHERE id=%d", GetPlayerAccountID(playerid), GetKioskData(kiosk_id, K_SQL_ID));
				mysql_query(mysql, query, false);

				ModifyCashBalance(playerid, -GetKioskData(kiosk_id, K_PRICE));

				SCMF(playerid, 0x499E3DFF, "Поздравляем! {FFFFFF}Вы успешно приобрели киоск {499E3D}№%d {FFFFFF}за {499E3D}%d руб.", kiosk_id, GetKioskData(kiosk_id, K_PRICE));

				SCM(playerid, 0xADCEEAFF, "Если вы хотите изменить название киоска, воспользуйтесь командой {FFFFFF}/changestallname");
				SCM(playerid, 0xADCEEAFF, "Если вы захотите продать киоск, воспользуйтесь командой {FFFFFF}/sellstall");
				SCM(playerid, 0xADCEEAFF, "Для управления киоском подойдите к нему и нажмите клавишу {FFFFFF}ALT");
				SCM(playerid, 0xADCEEAFF, "Не забывайте регулярно проводить уборку в киоске, иначе он может ломаться и потеряет улучшения.");
			}

			case 0:
			{
				switch(listitem)
				{
				    
				}
				return 1;
			}
			case DIALOG_BUY_MARIH:
			{
				if(!response) return 1;
				
				new count = strval(inputtext);
				new price = count * 300;

				if(1 <= count <= 20 && IsNumeric(inputtext))
				{
                    if(!VerifyIntString(QueryPlayerBalance(playerid), price)) return SendClientMessage(playerid, 0xFF6600FF, "* У вас недостаточно средств");
                    
                    GiveIteam(playerid, 172, 1, count, 0);
                    ModifyCashBalance(playerid, -price, "Покупка семян конопли", true, true);
                    new fmt_text[32];
				    format(fmt_text, sizeof fmt_text, "%s", SetIntegerMultiply(playerid, "300", count));

				    SCMF(playerid, COLOR_WHITE, "Вы купили {42B02C}\"Семена марихуанны\" {FFFFFF}за {42B02C}%s {FFFFFF}руб", formatStr(fmt_text));
				}
			}
			case DIALOG_VARKA_DRUGS:
			{
			    if(response)
			    {
			        if(!VerifyIntString(QueryPlayerBalance(playerid), 100000)) return SendClientMessage(playerid, 0xFF6600FF, "* У вас недостаточно денег для варки");
			        if(GetPlayerLevel(playerid) < 2) return SendClientMessage(playerid, 0xFF6600FF, "* Варить наркотики можно со 2 лвла");
					{
						ModifyCashBalance(playerid, -100000, "Варка наркотиков", true, true);
						new drugs = RandomEx(5, 70);

						switch(drugs)
						{
							case 5..20: CEF_CREATE(playerid, 2, 4, "Drugs", "[0]");
							case 21..32: CEF_CREATE(playerid, 2, 4, "Drugs", "[1]");
							case 33..40: CEF_CREATE(playerid, 2, 4, "Drugs", "[2]");
							case 41..47: CEF_CREATE(playerid, 2, 4, "Drugs", "[3]");
							case 48..60: CEF_CREATE(playerid, 2, 4, "Drugs", "[4]");
							case 61..70: CEF_CREATE(playerid, 2, 4, "Drugs", "[5]");
							case 71..87: CEF_CREATE(playerid, 2, 4, "Drugs", "[0]");
							case 88..99: CEF_CREATE(playerid, 2, 4, "Drugs", "[1]");
							case 100..111: CEF_CREATE(playerid, 2, 4, "Drugs", "[2]");
							case 112..120: CEF_CREATE(playerid, 2, 4, "Drugs", "[3]");
							case 121..140: CEF_CREATE(playerid, 2, 4, "Drugs", "[4]");
							case 141..148: CEF_CREATE(playerid, 2, 4, "Drugs", "[5]");
						}
						GiveIteam(playerid, 25, 1, 10, 0);
                        GameText(playerid, "~r~~h~Сварите наркотики", 3000, 1);
			            return 1;
					}
				}
			}
			case DIALOG_STAGES_1:
			{
				if(response)
				{
		    		new vehicleid = GetPlayerVehicleID(playerid);
		    		if(IsValidDynamicObject(EditStage1Player[vehicleid])) DestroyDynamicObject(EditStage1Player[vehicleid]);
		    	    new index = GetVehicleData(vehicleid, V_ACTION_ID);
		    	    new fmt_text[144];
		    	    SetOwnableCarData(index, OC_STAGE1, 0);

					SetOwnableCarData(index, OC_ENGINE_ACCELERATION, GetOwnableCarData(index, OC_ENGINE_ACCELERATION) - 10.0);
					SetOwnableCarData(index, OC_MAX_VELOCITY, GetOwnableCarData(index, OC_MAX_VELOCITY) - 20.0);

					new Float:accel = GetOwnableCarData(index, OC_ENGINE_ACCELERATION);
                    new Float:maxvel = GetOwnableCarData(index, OC_MAX_VELOCITY);

                    mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE ownable_cars SET engineacceleration='%f', maxgearvelocity='%f' WHERE id=%d LIMIT 1", accel, maxvel, GetOwnableCarData(index, OC_SQL_ID));
                    mysql_query(mysql, fmt_text, false);

					UpdateVehicleHandling(playerid, vehicleid);

		    	    SetOwnableCarData(index, OC_STAGE, 0);
					mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE ownable_cars SET stage1=0, stage=0 WHERE id=%d LIMIT 1", GetOwnableCarData(index, OC_SQL_ID));
					mysql_query(mysql, fmt_text, false);

					SetOwnableCarData(index, OC_STAGE1_OBJ, 0);
					mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE ownable_cars SET stage1_obj=%d WHERE id=%d LIMIT 1", GetOwnableCarData(index, OC_STAGE1_OBJ), GetOwnableCarData(index, OC_SQL_ID));
					mysql_query(mysql, fmt_text, false);

					if(IsValidDynamicObject(Stage1[vehicleid])) DestroyDynamicObject(Stage1[vehicleid]);

					ModifyCashBalance(playerid, 150000);
				}
				else
				{
   					SetPlayerCameraPos(playerid,2342.3635,-2606.8323,1002.6982);
					SetPlayerCameraLookAt(playerid,2339.8787,-2611.8870,1002.2754);
				}
		    }
		    case DIALOG_STAGES_1_1:
			{
				if(response)
				{
		    		new vehicleid = GetPlayerVehicleID(playerid);
		    		if(IsValidDynamicObject(EditStage1_1Player[vehicleid])) DestroyDynamicObject(EditStage1_1Player[vehicleid]);
		    	    new index = GetVehicleData(vehicleid, V_ACTION_ID);
		    	    new fmt_text[144];
		    	    SetOwnableCarData(index, OC_STAGE1_1, 0);

					SetOwnableCarData(index, OC_ENGINE_ACCELERATION, GetOwnableCarData(index, OC_ENGINE_ACCELERATION) - 15.0);
					SetOwnableCarData(index, OC_MAX_VELOCITY, GetOwnableCarData(index, OC_MAX_VELOCITY) - 30.0);

					new Float:accel = GetOwnableCarData(index, OC_ENGINE_ACCELERATION);
                    new Float:maxvel = GetOwnableCarData(index, OC_MAX_VELOCITY);

                    mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE ownable_cars SET engineacceleration='%f', maxgearvelocity='%f' WHERE id=%d LIMIT 1", accel, maxvel, GetOwnableCarData(index, OC_SQL_ID));
                    mysql_query(mysql, fmt_text, false);

					UpdateVehicleHandling(playerid, vehicleid);

		    	    SetOwnableCarData(index, OC_STAGE, 1);
					mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE ownable_cars SET stage1_1=0, stage=1 WHERE id=%d LIMIT 1", GetOwnableCarData(index, OC_SQL_ID));
					mysql_query(mysql, fmt_text, false);

					SetOwnableCarData(index, OC_STAGE1_1_OBJ, 0);
					mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE ownable_cars SET stage1_1_obj=%d WHERE id=%d LIMIT 1", GetOwnableCarData(index, OC_STAGE1_1_OBJ), GetOwnableCarData(index, OC_SQL_ID));
					mysql_query(mysql, fmt_text, false);

	                if(IsValidDynamicObject(Stage1_1[vehicleid])) DestroyDynamicObject(Stage1_1[vehicleid]);

					ModifyCashBalance(playerid, 200000);
				}
				else
				{
   					SetPlayerCameraPos(playerid,2342.3635,-2606.8323,1002.6982);
					SetPlayerCameraLookAt(playerid,2339.8787,-2611.8870,1002.2754);
				}
		    }
		    case DIALOG_STAGES_2:
			{
				if(response)
				{
		    		new vehicleid = GetPlayerVehicleID(playerid);
		    		if(IsValidDynamicObject(EditStage2Player[vehicleid])) DestroyDynamicObject(EditStage2Player[vehicleid]);
		    	    new index = GetVehicleData(vehicleid, V_ACTION_ID);
		    	    new fmt_text[144];
		    	    SetOwnableCarData(index, OC_STAGE2, 0);

					SetOwnableCarData(index, OC_ENGINE_ACCELERATION, GetOwnableCarData(index, OC_ENGINE_ACCELERATION) - 25.0);
					SetOwnableCarData(index, OC_MAX_VELOCITY, GetOwnableCarData(index, OC_MAX_VELOCITY) - 40.0);

					new Float:accel = GetOwnableCarData(index, OC_ENGINE_ACCELERATION);
                    new Float:maxvel = GetOwnableCarData(index, OC_MAX_VELOCITY);

                    mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE ownable_cars SET engineacceleration='%f', maxgearvelocity='%f' WHERE id=%d LIMIT 1", accel, maxvel, GetOwnableCarData(index, OC_SQL_ID));
                    mysql_query(mysql, fmt_text, false);

					UpdateVehicleHandling(playerid, vehicleid);

		    	    SetOwnableCarData(index, OC_STAGE, 2);
					mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE ownable_cars SET stage2=0, stage=2 WHERE id=%d LIMIT 1", GetOwnableCarData(index, OC_SQL_ID));
					mysql_query(mysql, fmt_text, false);

					SetOwnableCarData(index, OC_STAGE2_OBJ, 0);
					mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE ownable_cars SET stage2_obj=%d WHERE id=%d LIMIT 1", GetOwnableCarData(index, OC_STAGE2_OBJ), GetOwnableCarData(index, OC_SQL_ID));
					mysql_query(mysql, fmt_text, false);

	                if(IsValidDynamicObject(Stage2[vehicleid])) DestroyDynamicObject(Stage2[vehicleid]);

					ModifyCashBalance(playerid, 1000000);
				}
				else
				{
   					SetPlayerCameraPos(playerid,2342.3635,-2606.8323,1002.6982);
					SetPlayerCameraLookAt(playerid,2339.8787,-2611.8870,1002.2754);
				}
		    }
		    case DIALOG_STAGES_3:
			{
				if(response)
				{
		    		new vehicleid = GetPlayerVehicleID(playerid);
		    		if(IsValidDynamicObject(EditStage3Player[vehicleid])) DestroyDynamicObject(EditStage3Player[vehicleid]);
		    	    new index = GetVehicleData(vehicleid, V_ACTION_ID);
		    	    new fmt_text[144];
		    	    SetOwnableCarData(index, OC_STAGE3, 0);
		    	    SetOwnableCarData(index, OC_STAGE, 3);

					SetOwnableCarData(index, OC_ENGINE_ACCELERATION, GetOwnableCarData(index, OC_ENGINE_ACCELERATION) - 25.0);
					SetOwnableCarData(index, OC_MAX_VELOCITY, GetOwnableCarData(index, OC_MAX_VELOCITY) - 50.0);

					new Float:accel = GetOwnableCarData(index, OC_ENGINE_ACCELERATION);
                    new Float:maxvel = GetOwnableCarData(index, OC_MAX_VELOCITY);

                    mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE ownable_cars SET engineacceleration='%f', maxgearvelocity='%f' WHERE id=%d LIMIT 1", accel, maxvel, GetOwnableCarData(index, OC_SQL_ID));
                    mysql_query(mysql, fmt_text, false);

					UpdateVehicleHandling(playerid, vehicleid);

					mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE ownable_cars SET stage3=0, stage=3 WHERE id=%d LIMIT 1", GetOwnableCarData(index, OC_SQL_ID));
					mysql_query(mysql, fmt_text, false);

					SetOwnableCarData(index, OC_STAGE3_OBJ, 0);
					mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE ownable_cars SET stage3_obj=%d WHERE id=%d LIMIT 1", GetOwnableCarData(index, OC_STAGE3_OBJ), GetOwnableCarData(index, OC_SQL_ID));
					mysql_query(mysql, fmt_text, false);

	                if(IsValidDynamicObject(Stage3[vehicleid])) DestroyDynamicObject(Stage3[vehicleid]);

					ModifyCashBalance(playerid, 2000000);
				}
				else
				{
   					SetPlayerCameraPos(playerid,2342.3635,-2606.8323,1002.6982);
					SetPlayerCameraLookAt(playerid,2339.8787,-2611.8870,1002.2754);
				}
		    }
			case DIALOG_STAGE_INSTAL_1:
			{
				if(response)
				{
                    new Float: x, Float: y, Float: z;
				    new vehicleid = GetPlayerVehicleID(playerid);
				    GetVehiclePos(vehicleid, x,y,z);

				    if(IsValidDynamicObject(EditStage1_1Player[vehicleid])) DestroyDynamicObject(EditStage1_1Player[vehicleid]);
				    SetPlayerCameraPos(playerid,2342.3635,-2606.8323,1002.6982);
				    SetPlayerCameraLookAt(playerid,2339.8787,-2611.8870,1002.2754);
				    EditStage1Player[vehicleid] = CreateDynamicObject(10443, x, y, z,   0.00000, 0.00000, 180.00000);
				    SetPVarInt(playerid, "stage_edit_1", 1);
				    SetPVarInt(playerid, "model_id", 10443);
				    EditDynamicObject(playerid, EditStage1Player[vehicleid]);
				}
				else
				{
                    if(!VerifyIntString(QueryPlayerBalance(playerid), 300000)) return GameText(playerid, "~r~Недостаточно средств!", 4000, 2);
	
		            new vehicleid = GetPlayerVehicleID(playerid);
		            new index = GetVehicleData(vehicleid, V_ACTION_ID);
		            new fmt_text[144];
		
		            SetOwnableCarData(index, OC_STAGE1, 1);
		            SetOwnableCarData(index, OC_ENGINE_ACCELERATION, GetOwnableCarData(index, OC_ENGINE_ACCELERATION) + 10.0);
		            SetOwnableCarData(index, OC_MAX_VELOCITY, GetOwnableCarData(index, OC_MAX_VELOCITY) + 20.0);

					new Float:accel = GetOwnableCarData(index, OC_ENGINE_ACCELERATION);
                    new Float:maxvel = GetOwnableCarData(index, OC_MAX_VELOCITY);

                    mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE ownable_cars SET engineacceleration='%f', maxgearvelocity='%f' WHERE id=%d LIMIT 1", accel, maxvel, GetOwnableCarData(index, OC_SQL_ID));
                    mysql_query(mysql, fmt_text, false);

		            UpdateVehicleHandling(playerid, vehicleid);
		            SetOwnableCarData(index, OC_STAGE, 1);
		            mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE ownable_cars SET stage1=1, stage=1 WHERE id=%d LIMIT 1", GetOwnableCarData(index, OC_SQL_ID));
		            mysql_query(mysql, fmt_text, false);

					SetOwnableCarData(index, OC_STAGE1_OBJ, 1);
					mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE ownable_cars SET stage1_obj=%d WHERE id=%d LIMIT 1", GetOwnableCarData(index, OC_STAGE1_OBJ), GetOwnableCarData(index, OC_SQL_ID));
					mysql_query(mysql, fmt_text, false);

	                ModifyCashBalance(playerid, -300000);
				}
			}
			case DIALOG_STAGE_INSTAL_2:
			{
				if(response)
				{
                    new Float: x, Float: y, Float: z;
				    new vehicleid = GetPlayerVehicleID(playerid);
				    new idx = GetVehicleData(vehicleid, V_ACTION_ID);
				    GetVehiclePos(vehicleid, x,y,z);

				    if(GetOwnableCarData(idx, OC_STAGE1) == 1)
				    {
					    if(IsValidDynamicObject(EditStage1_1Player[vehicleid])) DestroyDynamicObject(EditStage1_1Player[vehicleid]);
					    SetPlayerCameraPos(playerid,2337.7588,-2617.0513,1003.1210);
					    SetPlayerCameraLookAt(playerid,2339.8787,-2611.8870,1002.2754);
					    EditStage1_1Player[vehicleid] = CreateDynamicObject(10442, x, y, z,   0.00000, 0.00000, 180.00000);
					    SetPVarInt(playerid, "stage_edit_1_1", 1);
					    SetPVarInt(playerid, "model_id", 10442);
					    EditDynamicObject(playerid, EditStage1_1Player[vehicleid]);
				    }
				}
				else
				{
                    if(!VerifyIntString(QueryPlayerBalance(playerid), 400000)) return GameText(playerid, "~r~Недостаточно средств!", 4000, 2);
	
		            new vehicleid = GetPlayerVehicleID(playerid);
		            new index = GetVehicleData(vehicleid, V_ACTION_ID);
		            new fmt_text[144];
		            
					SetOwnableCarData(index, OC_STAGE1_1, 1);
		            SetOwnableCarData(index, OC_ENGINE_ACCELERATION, GetOwnableCarData(index, OC_ENGINE_ACCELERATION) + 15.0);
		            SetOwnableCarData(index, OC_MAX_VELOCITY, GetOwnableCarData(index, OC_MAX_VELOCITY) + 30.0);

					new Float:accel = GetOwnableCarData(index, OC_ENGINE_ACCELERATION);
                    new Float:maxvel = GetOwnableCarData(index, OC_MAX_VELOCITY);

                    mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE ownable_cars SET engineacceleration='%f', maxgearvelocity='%f' WHERE id=%d LIMIT 1", accel, maxvel, GetOwnableCarData(index, OC_SQL_ID));
                    mysql_query(mysql, fmt_text, false);

		            UpdateVehicleHandling(playerid, vehicleid);
		            SetOwnableCarData(index, OC_STAGE, 2);
		            mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE ownable_cars SET stage1_1=1, stage=2 WHERE id=%d LIMIT 1", GetOwnableCarData(index, OC_SQL_ID));
		            mysql_query(mysql, fmt_text, false);

					SetOwnableCarData(index, OC_STAGE1_1_OBJ, 1);
					mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE ownable_cars SET stage1_1_obj=%d WHERE id=%d LIMIT 1", GetOwnableCarData(index, OC_STAGE1_1_OBJ), GetOwnableCarData(index, OC_SQL_ID));
					mysql_query(mysql, fmt_text, false);

	                ModifyCashBalance(playerid, -400000);
				}
			}
			case DIALOG_STAGE_INSTAL_3:
			{
				if(response)
				{
                    new Float: x, Float: y, Float: z;
				    new vehicleid = GetPlayerVehicleID(playerid);
				    new idx = GetVehicleData(vehicleid, V_ACTION_ID);
				    GetVehiclePos(vehicleid, x,y,z);

				    if(GetOwnableCarData(idx, OC_STAGE1) == 1 && GetOwnableCarData(idx, OC_STAGE1_1) == 1)
				    {							
					    if(IsValidDynamicObject(EditStage2Player[vehicleid])) DestroyDynamicObject(EditStage2Player[vehicleid]);
					    SetPlayerCameraPos(playerid,2342.3635,-2606.8323,1002.6982);
					    SetPlayerCameraLookAt(playerid,2339.8787,-2611.8870,1002.2754);
					    EditStage2Player[vehicleid] = CreateDynamicObject(10445, x, y, z,   0.00000, 0.00000, 180.00000);
					    SetPVarInt(playerid, "stage_edit_2", 1);
					    SetPVarInt(playerid, "model_id", 10445);
					    EditDynamicObject(playerid, EditStage2Player[vehicleid]);
			        }
				}
				else
				{
                    if(!VerifyIntString(QueryPlayerBalance(playerid), 2000000)) return GameText(playerid, "~r~Недостаточно средств!", 4000, 2);
	            
		            new vehicleid = GetPlayerVehicleID(playerid);
		            new index = GetVehicleData(vehicleid, V_ACTION_ID);
		            new fmt_text[144];

		            SetOwnableCarData(index, OC_STAGE2, 1);
		            SetOwnableCarData(index, OC_ENGINE_ACCELERATION, GetOwnableCarData(index, OC_ENGINE_ACCELERATION) + 25.0);
		            SetOwnableCarData(index, OC_MAX_VELOCITY, GetOwnableCarData(index, OC_MAX_VELOCITY) + 40.0);

					new Float:accel = GetOwnableCarData(index, OC_ENGINE_ACCELERATION);
                    new Float:maxvel = GetOwnableCarData(index, OC_MAX_VELOCITY);

                    mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE ownable_cars SET engineacceleration='%f', maxgearvelocity='%f' WHERE id=%d LIMIT 1", accel, maxvel, GetOwnableCarData(index, OC_SQL_ID));
                    mysql_query(mysql, fmt_text, false);

		            UpdateVehicleHandling(playerid, vehicleid);
		            SetOwnableCarData(index, OC_STAGE, 3);
		            mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE ownable_cars SET stage2=1, stage=3 WHERE id=%d LIMIT 1", GetOwnableCarData(index, OC_SQL_ID));
		            mysql_query(mysql, fmt_text, false);

					SetOwnableCarData(index, OC_STAGE2_OBJ, 1);
					mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE ownable_cars SET stage2_obj=%d WHERE id=%d LIMIT 1", GetOwnableCarData(index, OC_STAGE2_OBJ), GetOwnableCarData(index, OC_SQL_ID));
					mysql_query(mysql, fmt_text, false);

	                ModifyCashBalance(playerid, -2000000);
				}
			}
			case DIALOG_STAGE_INSTAL_4:
			{
				if(response)
				{
                    new Float: x, Float: y, Float: z;
				    new vehicleid = GetPlayerVehicleID(playerid);
				    new idx = GetVehicleData(vehicleid, V_ACTION_ID);
				    GetVehiclePos(vehicleid, x,y,z);

				    if(GetOwnableCarData(idx, OC_STAGE1) == 1 && GetOwnableCarData(idx, OC_STAGE1_1) == 1 && GetOwnableCarData(idx, OC_STAGE2) == 1)
				    {							
					    if(IsValidDynamicObject(EditStage3Player[vehicleid])) DestroyDynamicObject(EditStage3Player[vehicleid]);
					    SetPlayerCameraPos(playerid,2342.3635,-2606.8323,1002.6982);
					    SetPlayerCameraLookAt(playerid,2339.8787,-2611.8870,1002.2754);
					    EditStage3Player[vehicleid] = CreateDynamicObject(10444, x, y, z,   0.00000, 0.00000, 180.00000);
					    SetPVarInt(playerid, "stage_edit_3", 1);
					    SetPVarInt(playerid, "model_id", 10444);
					    EditDynamicObject(playerid, EditStage3Player[vehicleid]);
				    }
				}
				else
				{
                    if(!VerifyIntString(QueryPlayerBalance(playerid), 4000000)) return GameText(playerid, "~r~Недостаточно~n~средств", 3000, 2);

	                new vehicleid = GetPlayerVehicleID(playerid);
	                new index = GetVehicleData(vehicleid, V_ACTION_ID);
	                new fmt_text[144];
 
	                SetOwnableCarData(index, OC_STAGE3, 1);
	                SetOwnableCarData(index, OC_ENGINE_ACCELERATION, GetOwnableCarData(index, OC_ENGINE_ACCELERATION) + 25.0);
	                SetOwnableCarData(index, OC_MAX_VELOCITY, GetOwnableCarData(index, OC_MAX_VELOCITY) + 50.0);

					new Float:accel = GetOwnableCarData(index, OC_ENGINE_ACCELERATION);
                    new Float:maxvel = GetOwnableCarData(index, OC_MAX_VELOCITY);

                    mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE ownable_cars SET engineacceleration='%f', maxgearvelocity='%f' WHERE id=%d LIMIT 1", accel, maxvel, GetOwnableCarData(index, OC_SQL_ID));
                    mysql_query(mysql, fmt_text, false);

	                UpdateVehicleHandling(playerid, vehicleid);
	                SetOwnableCarData(index, OC_STAGE, 4);
	                mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE ownable_cars SET stage3=1, stage=4 WHERE id=%d LIMIT 1", GetOwnableCarData(index, OC_SQL_ID));
	                mysql_query(mysql, fmt_text, false);

					SetOwnableCarData(index, OC_STAGE3_OBJ, 1);
					mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE ownable_cars SET stage3_obj=%d WHERE id=%d LIMIT 1", GetOwnableCarData(index, OC_STAGE3_OBJ), GetOwnableCarData(index, OC_SQL_ID));
					mysql_query(mysql, fmt_text, false);

	                ModifyCashBalance(playerid, -4000000);
				}
			}
   			case DIALOG_STAGE_1:
			{
				if(response)
				{
				    new Float: x, Float: y, Float: z;
				    new vehicleid = GetPlayerVehicleID(playerid);
				    new idx = GetVehicleData(vehicleid, V_ACTION_ID);
				    GetVehiclePos(vehicleid, x,y,z);
					switch(listitem + 1)
					{
						case 1,2,5,7:
						{
							string_dialog[0] = EOS;
							format(string_dialog, sizeof string_dialog,
							"{E4E4DF}Деталь \t{E4E4DF}Статус \t{E4E4DF}Стоимость \n\n\n{F6B243}Комплект STAGE 1 \n{E4E4DF}Радиатор \t%s \t{91D643}300.000 руб\n{E4E4DF}Выхлоп \t%s \t{91D643}400.000 руб\n\n\n{946A1F}Комплект STAGE 2 \n{5C5D5C}Турбина \t%s \t{55703F}2.000.000 руб\n\n\n{946A1F}Комплект STAGE 3 \n{5C5D5C}Нагнетатель \t%s \t{55703F}4.000.000 руб\n",
							GetOwnableCarData(idx, OC_STAGE1) ? ("{00CC00}Устонавлено")  : ("{AF9795}Не устонавлено"),
							GetOwnableCarData(idx, OC_STAGE1_1) ? ("{00CC00}Устонавлено")  : ("{AF9795}Не устонавлено"),
							GetOwnableCarData(idx, OC_STAGE2) ? ("{00CC00}Устонавлено")  : ("{AF9795}Не устонавлено"),
							GetOwnableCarData(idx, OC_STAGE3) ? ("{00CC00}Устонавлено")  : ("{AF9795}Не устонавлено")
							);

							IntfDialogCallRemote(playerid, DIALOG_STAGE_1, DIALOG_STYLE_LIST, "{F6CC3F}Элементы установки", string_dialog, "Выбор", "Отмена");
						}
					    case 3:
					    {
							if(stagestats[playerid] == 1)
							{
						        if(GetOwnableCarData(idx, OC_STAGE1) == 1)
						        {
									IntfDialogCallRemote
									(
									    playerid, DIALOG_STAGES_1, 0,
									    "{F6CC3F}Элементы установки",
									    "{E4E4DF}Вы действительно хотите снять компонент STAGE 1 'Радиатор'<n>\
										Вам будет возвращено: 150.000 рублей",
									    "Выбор", "Отмена"
									);
						        }
						        else
								{
									IntfDialogCallRemote
									(
									    playerid, DIALOG_STAGE_INSTAL_1, 0,
									    "Выбор установки",
									    "Вы хотите установить обьект под это улучшение?\n"\
										"\n"\
										"Если откажетесь, то стэйдж будет установлен без визуального обьекта.",
									    "Да", "Нет"
									);
								}
				            }

					    }
					    case 4:
					    {
					    	if(stagestats[playerid] == 1)
							{
						        if(GetOwnableCarData(idx, OC_STAGE1_1) == 1)
						        {
									IntfDialogCallRemote
									(
									    playerid, DIALOG_STAGES_1_1, 0,
									    "{F6CC3F}Элементы установки",
									    "{E4E4DF}Вы действительно хотите снять компонент STAGE 1 'Выхлоп'<n>\
										Вам будет возвращено: 200.000 рублей",
									    "Выбор", "Отмена"
									);
						        }
								else
								{
							        if(GetOwnableCarData(idx, OC_STAGE1) == 1)
							        {
								        IntfDialogCallRemote
									    (
									        playerid, DIALOG_STAGE_INSTAL_2, 0,
									        "Выбор установки",
									        "Вы хотите установить обьект под это улучшение?\n"\
										    "\n"\
										    "Если откажетесь, то стэйдж будет установлен без визуального обьекта.",
									        "Да", "Нет"
									    );
									}
								}
							}
					    }
					    case 6:
					    {
					    	if(stagestats[playerid] == 2)
							{
						    	if(GetOwnableCarData(idx, OC_STAGE2) == 1)
						        {
						        	IntfDialogCallRemote
									(
									    playerid, DIALOG_STAGES_2, 0,
									    "{F6CC3F}Элементы установки",
									    "{E4E4DF}Вы действительно хотите снять компонент STAGE 2 'Турбина'<n>\
										Вам будет возвращено: 1.000.000 рублей",
									    "Выбор", "Отмена"
									);
						        }
								else
						        {
							    	if(GetOwnableCarData(idx, OC_STAGE1) == 1 && GetOwnableCarData(idx, OC_STAGE1_1) == 1)
							        {
										IntfDialogCallRemote
									    (
									        playerid, DIALOG_STAGE_INSTAL_3, 0,
									        "Выбор установки",
									        "Вы хотите установить обьект под это улучшение?\n"\
										    "\n"\
										    "Если откажетесь, то стэйдж будет установлен без визуального обьекта.",
									        "Да", "Нет"
									    );
									}
					            }
					       	}
					    }
					    case 8:
					    {
					    	if(stagestats[playerid] == 3)
							{
						    	if(GetOwnableCarData(idx, OC_STAGE3) == 1)
						        {
						        	IntfDialogCallRemote
									(
									    playerid, DIALOG_STAGES_3, 0,
									    "{F6CC3F}Элементы установки",
									    "{E4E4DF}Вы действительно хотите снять компонент STAGE 3 'Нагнетатель'<n>\
										Вам будет возвращено: 2.000.000 рублей",
									    "Выбор", "Отмена"
									);
						        }
								else
						        {
							        if(GetOwnableCarData(idx, OC_STAGE1) == 1 && GetOwnableCarData(idx, OC_STAGE1_1) == 1 && GetOwnableCarData(idx, OC_STAGE2) == 1)
							        {
										IntfDialogCallRemote
									    (
									        playerid, DIALOG_STAGE_INSTAL_4, 0,
									        "Выбор установки",
									        "Вы хотите установить обьект под это улучшение?\n"\
										    "\n"\
										    "Если откажетесь, то стэйдж будет установлен без визуального обьекта.",
									        "Да", "Нет"
									    );
									}
					            }
					       	}
					    }
					}
				}
			}

			case DIALOG_OWNABLE_BIZ_OPLATA:
			{
				if(response)
				{
				    new idx = GetPlayerListitemValue(playerid, listitem) + 1;
				    SetPVarInt(playerid, "ownablebiz_id", idx);
				    ShowPlayerBusinessPayForRent(playerid);
				}
			}
			case DIALOG_OWNABLE_KIOSK_OPLATA:
			{
				if(response)
				{
				    new idx = GetPlayerListitemValue(playerid, listitem) + 1;
				    SetPVarInt(playerid, "ownablekiosk_id", idx);
				    ShowPlayerKioskPayForRent(playerid);
				}
			}
         case DIALOG_GARDEN_SELL:
			{
				new garden = GetPVarInt(playerid, "garden_id");
				if(garden != -1)
				{
					if(response)
					{
						SellGarden(playerid,garden);
					}
				}
			}
			case DIALOG_RULLET_SHOW:
			{
				if(!response) return 1;

				if(IsPlayerInRangeOfPoint(playerid, 2.5, 223.4474,-302.4741,1012.0385))
				{
					RouletteTable[playerid] = 1;
					InterpolateCameraPos(playerid, 226.078033, -302.750885, 1011.523315, 225.375091, -302.632354, 1013.522888, 1000);
					InterpolateCameraLookAt(playerid, 221.130889, -302.555145, 1010.825195, 221.801132, -302.647369, 1010.026245, 1000);
				}
				if(IsPlayerInRangeOfPoint(playerid, 2.5, 223.1531,-296.3004,1012.0284))
				{
					RouletteTable[playerid] = 2;
					InterpolateCameraPos(playerid, 226.246841, -296.717224, 1011.795837, 225.492965, -296.621063, 1013.492187, 1000);
					InterpolateCameraLookAt(playerid, 221.296600, -296.629730, 1011.097717, 221.715301, -296.595642, 1010.216735, 1000);
				}
				if(IsPlayerInRangeOfPoint(playerid, 2.5, 207.7382,-296.5287,1012.0684))
				{
					RouletteTable[playerid] = 3;
					InterpolateCameraPos(playerid, 205.489654, -296.730712, 1011.446472, 205.750213, -296.680328, 1013.723571, 1000);
					InterpolateCameraLookAt(playerid, 210.484100, -296.722320, 1011.210998, 209.323822, -296.732971, 1010.226928, 1000);
				}
				if(IsPlayerInRangeOfPoint(playerid, 2.5, 207.9463,-303.3881,1012.0385))
				{
					RouletteTable[playerid] = 4;
					InterpolateCameraPos(playerid, 204.530761, -303.071838, 1011.295043, 205.576446, -303.171691, 1013.490661, 1000);
					InterpolateCameraLookAt(playerid, 209.524154, -303.174743, 1011.059570, 209.493804, -303.188140, 1010.383544, 1000);
				}
				if(IsPlayerInRangeOfPoint(playerid, 2.5, 191.6914,-293.2050,1012.8684))
				{
					RouletteTable[playerid] = 5;
					InterpolateCameraPos(playerid, 191.356338, -296.251281, 1012.188903, 191.293655, -295.537445, 1014.428344, 1000);  //
					InterpolateCameraLookAt(playerid, 191.410964, -291.255920, 1011.980712, 191.314788, -291.671630, 1011.257385, 1000);
				}
				if(IsPlayerInRangeOfPoint(playerid, 2.5, 201.4565,-331.6115,1012.0385))
				{
					RouletteTable[playerid] = 6;
					InterpolateCameraPos(playerid, 204.557525, -331.987152, 1011.129333, 203.738037, -331.871582, 1013.848327, 1000);
					InterpolateCameraLookAt(playerid, 199.560974, -331.924133, 1011.303894, 200.052810, -331.764617, 1010.470825, 1000);
				}
				RulletShow(playerid);
				return 1;
			}
			case DIALOG_MINER_BUY_METALL:
			{
				if(!response) return 1;

				if(strval(inputtext) < 1) return SCM(playerid, COLOR_GREY, "Некорректное количество."), ShowPlayerBuyMetalDialog(playerid);
				if(strval(inputtext) > 1000) return SCM(playerid, COLOR_GREY, "Можно купить от 1 до 1000 кг металла за раз."), ShowPlayerBuyMetalDialog(playerid);
				if(!VerifyIntString(QueryPlayerBalance(playerid), strval(inputtext) * 10000)) return SCM(playerid, COLOR_GREY, "Недостаточно средств для покупки металла.");
		
				if(GetInventorySlots(playerid) == -1) return SCM(playerid, COLOR_GREY, "В вашем инвентаре нет свободного места"), ShowPlayerBuyMetalDialog(playerid);

				SCMF(playerid, 0x3584ccFF, "Вы купили %d кг за %s рублей", strval(inputtext), formatInt(strval(inputtext) * 10000));

				ModifyCashBalance(playerid, -(strval(inputtext) * 10000), "Покупка металла");
				GiveIteam(playerid, 27, 1, strval(inputtext), 0);
			}
			case DIALOG_MVDPICKUP:
			{
				if(response)
				{
					switch(listitem)
					{
						case 0:
						{
	 				 		SendClientMessage(playerid, 0xAA3333AA, "Бегите пока не поздно!");
						}
						case 1:
						{
							SendClientMessage(playerid, 0xAA3333AA, "Свяжитесь с сотрудником МВД!");
							return 1;
						}
					}
				}
			}
			
            case DIALOG_EXIT_METRO:
			{
			    if(response)
			    {
					if(GetPVarInt(playerid, "Metro_work") == 1)
					{
						metro_user -= 1;
						DisablePlayerRaceCheckpoint(playerid);
						DestroyVehicle(metro_train[playerid]);
						new fmt_str[130];

						format(fmt_str, sizeof fmt_str, "Рабочий день завершен. Вы заработали %d руб.", metro_zarplata[playerid]);
						SendClientMessage(playerid, 0x3399FFFF, fmt_str);
						ModifyCashBalance(playerid, metro_zarplata[playerid], "Работа метро", true, true);
						metro_train[playerid] = INVALID_VEHICLE_ID;
						metro_zarplata[playerid] = 0;
						CEF_CREATE(playerid, 1, 2, "closeInterface('Machinist')");
						SetPlayerPos(playerid, 93.8737,812.0742,-30.5367);
						SetCameraBehindPlayer(playerid);
						OffFirstPerson(playerid);
						DeletePVar(playerid, "Metro_work");
					}
				}
			}
			case DIALOG_INVITE_METRO:
			{
			    if(response)
			    {
					if(metro_user >= 5) return SendClientMessage(playerid, 0x7f7f7fFF, "На маршруте нет свободных мест");
					if(metro_status == 1) return SendClientMessage(playerid, 0x7f7f7fFF, "В депо метрополитена нет мест,подождите пока займут электропоезд");
					SetPVarInt(playerid, "Metro_work",1);
					SetPVarInt(playerid, "Metro_start",1);
					metro_user += 1;
					metro_status = 1;
					metro_train[playerid] = AddStaticVehicleEx(537,-394.6066,475.2843,12.0387,90.0,17,17, -1); //поезд метро
					SetPlayerCheckpoint(playerid, -392.5566,482.6591,12.0604, 2.0, CP_ACTION_TYPE_PUT_TRAIN);
					SetVehicleParam(metro_train[playerid], V_ENGINE, VEHICLE_PARAM_ON);
				}
			}
			case DIALOG_POBEG_MAFIA_RUSSIAN:
			{
			   	if(VerifyIntString(QueryPlayerBalance(playerid), 15000000))
			    {
				    SendClientMessage(playerid, 0xf4ba5bFF, "Вы сбежали из подвала, быстрее убегайте с территории мафии!");
				    SetPlayerPosEx(playerid, 1949.1350,-48.5137,6.4177,182.6890, 0, 0);
			    	SetPlayerData(playerid, P_TURMA, 0);
					UpdatePlayerDatabaseInt(playerid, "turma", 0);
					ModifyCashBalance(playerid, -15000000, "Побег", true, true);
				}
				else SendClientMessage(playerid, 0xf4ba5bFF, "У вас нету 15.000.000");
			}
			case DIALOG_POBEG_MAFIA_ITALIA:
			{
			    if(VerifyIntString(QueryPlayerBalance(playerid), 15000000))
			    {
				    SendClientMessage(playerid, 0xf4ba5bFF, "Вы сбежали из подвала, быстрее убегайте с территории мафии!");
				    SetPlayerPosEx(playerid, -3178.0903,829.0162,6.4273,274.5032, 0, 0);
			    	SetPlayerData(playerid, P_TURMA, 0);
					UpdatePlayerDatabaseInt(playerid, "turma", 0);
					ModifyCashBalance(playerid, -15000000, "Побег", true, true);
                }
				else SendClientMessage(playerid, 0xf4ba5bFF, "У вас нету 15.000.000");
			}
			case DIALOG_POBEG_MAFIA_JAPAN:
			{
			    if(VerifyIntString(QueryPlayerBalance(playerid), 15000000))
			    {
				    SendClientMessage(playerid, 0xf4ba5bFF, "Вы сбежали из подвала, быстрее убегайте с территории мафии!");
				    SetPlayerPosEx(playerid, 4004.6062,3857.9153,7.9312,70.8894, 0, 0);
			    	SetPlayerData(playerid, P_TURMA, 0);
					UpdatePlayerDatabaseInt(playerid, "turma", 0);
					ModifyCashBalance(playerid, -15000000, "Побег", true, true);
                }
				else SendClientMessage(playerid, 0xf4ba5bFF, "У вас нету 15.000.000");
			}
			
			case DIALOG_ADMIN_CREATE:
		    {
                if(!response) return true;
		        if(response)
		        {
		            if(!(1 <= strlen(inputtext) <= 15) || strfind(inputtext, " ") != -1)
					{
						SendClientMessage(playerid, 0xFF6600FF, "Длина пароля должна быть от 6 до 15 символов");
						SendClientMessage(playerid, 0xFF6600FF, "Также не допускается использование пробелов");
					}
					else
					{
						if(!strcmp(g_player[playerid][P_PASSWORD], inputtext, true)) return SCM(playerid, COLOR_GREY, "Пароль от аккаунта и пароль от админ-прав должен различаться");

						new query[100];
						mysql_format(mysql, query, sizeof query, "UPDATE accounts_canvasdev SET adminspasslogin='%e' WHERE id=%d LIMIT 1", inputtext, GetPlayerAccountID(playerid));
						mysql_query(mysql, query, false);

						if(!mysql_errno())
						{
							format(g_player[playerid][P_ADMIN_PASSWORD], 16, "%s", inputtext);
							format(query, sizeof query, "{99CC00}Ваш пароль: {FFFFFF}%s", GetPlayerData(playerid, P_ADMIN_PASSWORD));
							if(IsPlayerAdminLevel(playerid) != 0)
							{
								format
								(
					                STRING_GLOBAL, sizeof STRING_GLOBAL,
									"[A]{FFFFFF} %s[%d] {99CC00}регистрируется в системе как администратор %d уровня",
									GetPlayerNameEx(playerid), playerid, IsPlayerAdminLevel(playerid)

								);
							}
							if(GetPlayerYAdminEx(playerid) != 0)
							{
								format
								(
					                STRING_GLOBAL, sizeof STRING_GLOBAL,
									"[A]{FFFFFF} %s[%d] {99CC00}регистрируется в системе как ютубер %d уровня",
									GetPlayerNameEx(playerid), playerid, GetPlayerYAdminEx(playerid)

								);
							}

                            SendMessageToAdmins(STRING_GLOBAL, 0x99CC00FF);
							SendClientMessage(playerid, 0x99CC00FF, query);
							return 1;
						}
						else SendClientMessage(playerid, 0xFF6600FF, "Ошибка сохранения, повторите попытку {FF0000}(equ-code 05)");
					}
		        }
		    }
			case DIALOG_ADMIN_CREATE_2:
		    {
                if(!response) return true;

				if(!(1 <= strlen(inputtext) <= 15) || strfind(inputtext, " ") != -1)
				{
					SendClientMessage(playerid, 0xFF6600FF, "Длина пароля должна быть от 6 до 15 символов");
					SendClientMessage(playerid, 0xFF6600FF, "Также не допускается использование пробелов");
					IntfDialogCallRemote(playerid, DIALOG_ADMIN_CREATE_2, DIALOG_STYLE_PASSWORD,"{FFD83D}Регистрация Админ-Прав","{FFFFFF}Создайте свой личный пароль для авторизации как администратор","Далее", "Закрыть");
				}
				else
				{
					if(!strcmp(g_player[playerid][P_PASSWORD], inputtext, true)) 
					{
						IntfDialogCallRemote(playerid, DIALOG_ADMIN_CREATE_2, DIALOG_STYLE_PASSWORD,"{FFD83D}Регистрация Админ-Прав","{FFFFFF}Создайте свой личный пароль для авторизации как администратор","Далее", "Закрыть");
						return SCM(playerid, COLOR_GREY, "Пароль от аккаунта и пароль от админ-прав должен различаться");
					}
					new query[100];
					mysql_format(mysql, query, sizeof query, "UPDATE accounts_canvasdev SET adminspasslogin='%e' WHERE id=%d LIMIT 1", inputtext, GetPlayerAccountID(playerid));
					mysql_query(mysql, query, false);

					if(!mysql_errno())
					{
						format(g_player[playerid][P_ADMIN_PASSWORD], 16, "%s", inputtext);
						format(query, sizeof query, "{99CC00}Ваш пароль: {FFFFFF}%s", GetPlayerData(playerid, P_ADMIN_PASSWORD));
						if(IsPlayerAdminLevel(playerid) != 0)
						{
							format
							(
								STRING_GLOBAL, sizeof STRING_GLOBAL,
								"[A]{FFFFFF} %s[%d] {99CC00}регистрируется как администратор %d уровня",
								GetPlayerNameEx(playerid), playerid, IsPlayerAdminLevel(playerid)

							);
						}
						SendMessageToAdmins(STRING_GLOBAL, 0x99CC00FF);
						SendClientMessage(playerid, 0x99CC00FF, query);
						IntfDialogCallRemote(playerid, DIALOG_ADMIN_PASS_2, DIALOG_STYLE_PASSWORD,"{FFD83D}Авторизация Админ-Прав","Вы пытаетесь авторизоваться как администратор.\n\n{FFFFFF}Введите пароль:", "Далее", "Закрыть");
						return 1;
					}
					else SendClientMessage(playerid, 0xFF6600FF, "Ошибка сохранения, повторите попытку {FF0000}(equ-code 05)");
				}
		    }
			case DIALOG_ADMIN_PASS_2:
			{
                if(!response) return Kick(playerid);

				if(strlen(inputtext) && !strcmp(inputtext, g_player[playerid][P_ADMIN_PASSWORD], false))
				{
					STRING_GLOBAL[0] = EOS;
					format(STRING_GLOBAL, sizeof STRING_GLOBAL, "[A] Администратор %s[%d] авторизовался в системе безопасности (%d уровень админ-прав)", GetPlayerNameEx(playerid), playerid, IsPlayerAdminLevel(playerid));
					SendMessageToAdmins(STRING_GLOBAL, COLOR_GREY);
					admin_logged[playerid] = true;
				}
				else 
				{
					if(GetPVarInt(playerid, "Alogin") == 1) return admin_logged[playerid] = false, Kick(playerid);
					else if(GetPVarInt(playerid, "Alogin") == 0) return IntfDialogCallRemote(playerid, DIALOG_ADMIN_PASS_2, DIALOG_STYLE_PASSWORD,"{FFD83D}Авторизация Админ-Прав","Вы пытаетесь авторизоваться как администратор.\n\n{BE2D2D}У вас осталось последняя попытка\n{FFFFFF}Введите пароль:","Далее", "Закрыть"), SetPVarInt(playerid, "Alogin", 1);
				}
			}
			case DIALOG_ADMIN_PASS:
			{
                if(!response) return Kick(playerid);
				if(response)
				{
					if(strlen(inputtext) && !strcmp(inputtext, g_player[playerid][P_ADMIN_PASSWORD], false))
					{
						STRING_GLOBAL[0] = EOS;
						format(STRING_GLOBAL, sizeof STRING_GLOBAL, "[A] Администратор %s[%d] авторизовался в системе безопасности (%d уровень админ-прав)", GetPlayerNameEx(playerid), playerid, IsPlayerAdminLevel(playerid));
						SendMessageToAdmins(STRING_GLOBAL, COLOR_GREY);
						admin_logged[playerid] = true;
					}
					else 
					{
						if(GetPVarInt(playerid, "Alogin") == 1) return SendClientMessage(playerid, 0xFF6600FF, "Пароль не верный."), admin_logged[playerid] = false, Kick(playerid);
						else if(GetPVarInt(playerid, "Alogin") == 0) return IntfDialogCallRemote(playerid, DIALOG_ADMIN_PASS, DIALOG_STYLE_PASSWORD,"{FFD83D}Система безопасности","{BE2D2D}У вас осталось последняя попытка\n{FFFFFF}Введите пароль:","Далее", "Закрыть"), SetPVarInt(playerid, "Alogin", 1);
					}
				}
			}
			case DIALOG_MEROPRIATIE:
			{
			    if(response)
				{
					switch(listitem + 1)
					{
						case 1:
						{
							SendClientMessageToAll(COLOR_YELLOW, "[МП] Открыт телепорт на мероприятие 'Уедь от админа'");
							SendClientMessageToAll(COLOR_YELLOW, "[МП] Телепортироваться : /tp");
							SendClientMessageToAll(COLOR_YELLOW, "[МП] Сразу в строй у стены!");

							SendClientMessageToAll(COLOR_YELLOW, "[МП] Телепорт закроется через 1 минуту!");

							SetPlayerPos(playerid, -187.2291,390.1685,14.4367);

							mptp = SetTimer("CloseMpTeleport", 60000, true);

							number_mp_player = 15;
                            
							mp_status = 1;
							mpPos[0] = -187.2291;
							mpPos[1] = 390.1685;
							mpPos[2] = 14.4367;
							mpWorld[0] = GetPlayerInterior(playerid);
							mpWorld[1] = GetPlayerVirtualWorld(playerid);
							
							AddStaticVehicle(555,-205.3443,391.5666,14.2532,271.0813,0,1);
							AddStaticVehicle(555,-205.3443,388.5666,14.2532,271.0813,0,1);
							AddStaticVehicle(555,-205.3443,385.5666,14.2532,271.0813,0,1);
							AddStaticVehicle(555,-205.3443,382.5666,14.2532,271.0813,0,1);
							AddStaticVehicle(555,-205.3443,379.5666,14.2532,271.0813,0,1);
							AddStaticVehicle(555,-205.3443,376.5666,14.2532,271.0813,0,1);
							AddStaticVehicle(555,-205.3443,373.5666,14.2532,271.0813,0,1);
							AddStaticVehicle(555,-205.3443,370.5666,14.2532,271.0813,0,1);
							AddStaticVehicle(555,-205.3443,367.5666,14.2532,271.0813,0,1);
							AddStaticVehicle(555,-205.3443,364.5666,14.2532,271.0813,0,1);
							AddStaticVehicle(555,-205.3443,361.5666,14.2532,271.0813,0,1);
							AddStaticVehicle(555,-205.3443,358.5666,14.2532,271.0813,0,1);
							AddStaticVehicle(555,-205.3443,355.5666,14.2532,271.0813,0,1);
							AddStaticVehicle(555,-205.3443,352.5666,14.2532,271.0813,0,1);
							AddStaticVehicle(555,-205.3443,349.5666,14.2532,271.0813,0,1);
							AddStaticVehicle(444,-179.5972,390.1159,14.8067,90.5121,1,1);
						}
						case 2:
						{
							SendClientMessageToAll(COLOR_YELLOW, "[МП] Открыт телепорт на мероприятие 'Король Дигла'");
							SendClientMessageToAll(COLOR_YELLOW, "[МП] Телепортироваться : /tp");
							SendClientMessageToAll(COLOR_YELLOW, "[МП] Сразу в строй у стены!");

							SendClientMessageToAll(COLOR_YELLOW, "[МП] Телепорт закроется через 1 минуту!");

							SetPlayerPos(playerid, -179.6144,390.2608,14.4367);

							mptp = SetTimer("CloseMpTeleport", 60000, true);

							number_mp_player = 150;

							mp_status = 1;
							mpPos[0] = -187.2291;
							mpPos[1] = 390.1685;
							mpPos[2] = 14.4367;
							mpWorld[0] = GetPlayerInterior(playerid);
							mpWorld[1] = GetPlayerVirtualWorld(playerid);
							
							new gun, ammo, radius;



	                        new Float:pos[3];
	                        GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
                            new string[144];
                            new players;
	                        foreach(new i : Player)
	                        {
                            if(!IsPlayerInRangeOfPoint(i, 200, pos[0], pos[1], pos[2])) continue;
		                    GiveWeapon(i, 24, 999);
		                    format(string, sizeof string, "[MP]: Вы получили оружие %s [%d] и %d пт.", GetWeaponName(gun), gun, ammo);
		                    SendClientMessage(i, 0xCECECEFF, string);
		                    players++;
	                        }
	                        format(string, sizeof string, "Оружие выдано %i игрокам в радиусе %i метров", players, radius);
                            SendClientMessage(playerid, COLOR_WHITE, string);
						}
						case 3:
						{
							SendClientMessageToAll(COLOR_YELLOW, "[МП] Открыт телепорт на мероприятие 'CS:GO'");
							SendClientMessageToAll(COLOR_YELLOW, "[МП] Телепортироваться : /tp");
							SendClientMessageToAll(COLOR_YELLOW, "[МП] Сразу в строй у стены!");

							SendClientMessageToAll(COLOR_YELLOW, "[МП] Телепорт закроется через 1 минуту!");

							SetPlayerPos(playerid, -3048.8674,-4961.2710,5.8995);

							mptp = SetTimer("CloseMpTeleport", 60000, true);

							number_mp_player = 50;

							mp_status = 1;
							mpPos[0] = -3048.8674;
							mpPos[1] = -4961.2710;
							mpPos[2] = 5.8995;
							mpWorld[0] = GetPlayerInterior(playerid);
							mpWorld[1] = GetPlayerVirtualWorld(playerid);
						}
						case 4:
						{
							SendClientMessageToAll(COLOR_YELLOW, "[МП] Открыт телепорт на мероприятие 'Мокрая Вечеринка'");
							SendClientMessageToAll(COLOR_YELLOW, "[МП] Телепортироваться : /tp");
							SendClientMessageToAll(COLOR_YELLOW, "[МП] Сразу в строй у стены!");

							SendClientMessageToAll(COLOR_YELLOW, "[МП] Телепорт закроется через 1 минуту!");

							number_mp_player = 50;

							SetPlayerPos(playerid, 1931.6908,-1911.1093,56.5136);

							AddStaticVehicle(601,1918.5977,-1902.8547,56.2827,181.5945,0,1);

							mptp = SetTimer("CloseMpTeleport", 60000, true);

							mp_status = 1;
							mpPos[0] = 1931.6908;
							mpPos[1] = -1911.1093;
							mpPos[2] = 56.5136;
							mpWorld[0] = GetPlayerInterior(playerid);
							mpWorld[1] = GetPlayerVirtualWorld(playerid);
						}
						case 5:
						{
							SendClientMessageToAll(COLOR_YELLOW, "[МП] Открыт телепорт на мероприятие 'Восточная Дуэль'");
							SendClientMessageToAll(COLOR_YELLOW, "[МП] Телепортироваться : /tp");
							SendClientMessageToAll(COLOR_YELLOW, "[МП] Сразу в строй у стены!");

							SendClientMessageToAll(COLOR_YELLOW, "[МП] Телепорт закроется через 1 минуту!");

							number_mp_player = 20;

							SetPlayerPos(playerid, -179.6144,390.2608,14.4367);

							mptp = SetTimer("CloseMpTeleport", 60000, true);

							mp_status = 1;
							mpPos[0] = -179.6144;
							mpPos[1] = 390.2608;
							mpPos[2] = 14.4367;
							mpWorld[0] = GetPlayerInterior(playerid);
							mpWorld[1] = GetPlayerVirtualWorld(playerid);
						}
					}
				}
				else return GameText(playerid, "~b~ну ты и ленивый(~n~~y~мп провести сложно~n~~r~собака ты", 1500, 5);
			}
			case DIALOG_MEROPRIATIE1:
			{
			    if(response)
				{
					switch(listitem + 1)
					{
						case 1:
						{
							SendClientMessageToAll(COLOR_YELLOW, "[МП] TEST 'Уедь от админа'");
							SendClientMessageToAll(COLOR_YELLOW, "[МП] TEST : /TEST");
							SendClientMessageToAll(COLOR_YELLOW, "[МП] TEST TEST TESTй TEST TEST!");

							SendClientMessageToAll(COLOR_YELLOW, "[МП] TEST TEST TEST TEST TEST!");

							SetPlayerPos(playerid, -187.2291,390.1685,14.4367);

							mptp = SetTimer("CloseMpTeleport", 60000, true);

							number_mp_player = 15;

							mp_status = 1;
							mpPos[0] = -187.2291;
							mpPos[1] = 390.1685;
							mpPos[2] = 14.4367;
							mpWorld[0] = GetPlayerInterior(playerid);
							mpWorld[1] = GetPlayerVirtualWorld(playerid);
							AddStaticVehicle(555,-205.3443,391.5666,14.2532,271.0813,0,1);
							AddStaticVehicle(555,-205.3443,388.5666,14.2532,271.0813,0,1);
							AddStaticVehicle(555,-205.3443,385.5666,14.2532,271.0813,0,1);
							AddStaticVehicle(555,-205.3443,382.5666,14.2532,271.0813,0,1);
							AddStaticVehicle(555,-205.3443,379.5666,14.2532,271.0813,0,1);
							AddStaticVehicle(555,-205.3443,376.5666,14.2532,271.0813,0,1);
							AddStaticVehicle(555,-205.3443,373.5666,14.2532,271.0813,0,1);
							AddStaticVehicle(555,-205.3443,370.5666,14.2532,271.0813,0,1);
							AddStaticVehicle(555,-205.3443,367.5666,14.2532,271.0813,0,1);
							AddStaticVehicle(555,-205.3443,364.5666,14.2532,271.0813,0,1);
							AddStaticVehicle(555,-205.3443,361.5666,14.2532,271.0813,0,1);
							AddStaticVehicle(555,-205.3443,358.5666,14.2532,271.0813,0,1);
							AddStaticVehicle(555,-205.3443,355.5666,14.2532,271.0813,0,1);
							AddStaticVehicle(555,-205.3443,352.5666,14.2532,271.0813,0,1);
							AddStaticVehicle(555,-205.3443,349.5666,14.2532,271.0813,0,1);
							AddStaticVehicle(444,-179.5972,390.1159,14.8067,90.5121,1,1);
						}
						case 2:
						{
							SendClientMessageToAll(COLOR_YELLOW, "[TEST] TEST TEST TEST TEST 'TEST TEST'");
							SendClientMessageToAll(COLOR_YELLOW, "[TEST] TEST : /TEST");
							SendClientMessageToAll(COLOR_YELLOW, "[TEST] TEST TEST TEST TEST TEST!");

							SendClientMessageToAll(COLOR_YELLOW, "[TEST] TEST TEST TEST TEST TEST!");

							SetPlayerPos(playerid, -179.6144,390.2608,14.4367);

							mptp = SetTimer("CloseMpTeleport", 60000, true);

							number_mp_player = 150;

							mp_status = 1;
							mpPos[0] = -187.2291;
							mpPos[1] = 390.1685;
							mpPos[2] = 14.4367;
							mpWorld[0] = GetPlayerInterior(playerid);
							mpWorld[1] = GetPlayerVirtualWorld(playerid);
						}
						case 3:
						{
							SendClientMessageToAll(COLOR_YELLOW, "[МП] Открыт телепорт на мероприятие 'CS:GO'");
							SendClientMessageToAll(COLOR_YELLOW, "[МП] Телепортироваться : /tp");
							SendClientMessageToAll(COLOR_YELLOW, "[МП] Сразу в строй у стены!");

							SendClientMessageToAll(COLOR_YELLOW, "[МП] Телепорт закроется через 1 минуту!");

							SetPlayerPos(playerid, -3048.8674,-4961.2710,5.8995);

							mptp = SetTimer("CloseMpTeleport", 60000, true);

							number_mp_player = 50;

							mp_status = 1;
							mpPos[0] = -3048.8674;
							mpPos[1] = -4961.2710;
							mpPos[2] = 5.8995;
							mpWorld[0] = GetPlayerInterior(playerid);
							mpWorld[1] = GetPlayerVirtualWorld(playerid);
						}
						case 4:
						{
							SendClientMessageToAll(COLOR_YELLOW, "[МП] Открыт телепорт на мероприятие 'Мокрая Вечеринка'");
							SendClientMessageToAll(COLOR_YELLOW, "[МП] Телепортироваться : /tp");
							SendClientMessageToAll(COLOR_YELLOW, "[МП] Сразу в строй у стены!");

							SendClientMessageToAll(COLOR_YELLOW, "[МП] Телепорт закроется через 1 минуту!");

							number_mp_player = 50;

							SetPlayerPos(playerid, 1931.6908,-1911.1093,56.5136);

							AddStaticVehicle(601,1918.5977,-1902.8547,56.2827,181.5945,0,1);

							mptp = SetTimer("CloseMpTeleport", 60000, true);

							mp_status = 1;
							mpPos[0] = 1931.6908;
							mpPos[1] = -1911.1093;
							mpPos[2] = 56.5136;
							mpWorld[0] = GetPlayerInterior(playerid);
							mpWorld[1] = GetPlayerVirtualWorld(playerid);
						}
						case 5:
						{
							SendClientMessageToAll(COLOR_YELLOW, "[МП] Открыт телепорт на мероприятие 'Восточная Дуэль'");
							SendClientMessageToAll(COLOR_YELLOW, "[МП] Телепортироваться : /tp");
							SendClientMessageToAll(COLOR_YELLOW, "[МП] Сразу в строй у стены!");

							SendClientMessageToAll(COLOR_YELLOW, "[МП] Телепорт закроется через 1 минуту!");

							number_mp_player = 20;

							SetPlayerPos(playerid, -179.6144,390.2608,14.4367);

							mptp = SetTimer("CloseMpTeleport", 60000, true);

							mp_status = 1;
							mpPos[0] = -179.6144;
							mpPos[1] = 390.2608;
							mpPos[2] = 14.4367;
							mpWorld[0] = GetPlayerInterior(playerid);
							mpWorld[1] = GetPlayerVirtualWorld(playerid);
						}
					}
				}
				else return GameText(playerid, "~b~ну ты и ленивый(~n~~y~мп провести сложно~n~~r~собака ты", 1500, 5);
			}
			case R_F:
			{
			    if(response)
		        {
					new carprice = GetVehicleData(GetPlayerVehicleID(playerid), V_RENTP),string[80];
					new businessid = GetVehicleData(GetPlayerVehicleID(playerid), V_RENT);
					if(VerifyIntString(QueryPlayerBalance(playerid), carprice))
					{
						RemovePlayerFromVehicle(playerid);
						TogglePlayerControllable(playerid,1);
						SendClientMessage(playerid,COLOR_WHITE,"У вас недостаточно средств для аренды транспорта.");
						return 1;
					}
					if(GetPlayerData(playerid, P_RENT_CAR) != INVALID_VEHICLE_ID)
					{
						RemovePlayerFromVehicle(playerid);
						TogglePlayerControllable(playerid,1);
						SendClientMessage(playerid,COLOR_WHITE,"У вас уже есть арендованное авто. /unrent чтобы вернуть его.");
						return 1;
					}
					new take_prods = 50;

					if(GetBusinessData(businessid, B_PRODS) >= take_prods)
					{
						AddBusinessProfit(playerid, businessid, carprice, take_prods);
					}
					else
					{
						RemovePlayerFromVehicle(playerid);
						TogglePlayerControllable(playerid,1);
						SendClientMessage(playerid,COLOR_WHITE,"В бизнесе недостаточно продуктов. Аренда авто закрыта.");
						return 1;
					}

					format(string, sizeof(string), "{66CC00}Вы арендовали транспорт для временного использования");
					SendClientMessage(playerid,COLOR_WHITE,string);
					SendClientMessage(playerid, 0xFFFFFFFF, "Используйте {3CB371}/lock 2{FFFFFF} для открытия и закрытия дверей");
					SendClientMessage(playerid, 0xFFFFFFFF, "Чтобы разорвать договор аренды введите {3CB371}/unrent");
					TogglePlayerControllable(playerid,1);
					ModifyCashBalance(playerid, -carprice, "Аренда авто");
					GetVehicleData(GetPlayerVehicleID(playerid), V_OWRENT) = GetPlayerName(playerid, OwnedName, sizeof(OwnedName));
					SetVehicleNumberPlate(GetPlayerVehicleID(playerid),"RENTED");
					SetPlayerData(playerid, P_RENT_CAR, GetPlayerVehicleID(playerid));
		        }
          		else
		        {
		            RemovePlayerFromVehicle(playerid);
				    TogglePlayerControllable(playerid,1);
		        }
			}
			// -----------------------------------------------------------------
			case DIALOG_PNEWMA_DESTROY:
			{
				if(!response) return 1;
				
				new vehicleid = GetPlayerVehicleID(playerid);
				new index = GetVehicleData(vehicleid, V_ACTION_ID);

				ModifyCashBalance(playerid, 750000, "снятие пневмы", true, true);
				SetOwnableCarData(index, OC_PNEWMA, 0);

				SetOwnableCarData(index, OC_PNEWMA_1, 0.0);
				SetOwnableCarData(index, OC_PNEWMA_2, 0.0);

				SetPlayerVirtualWorld(playerid, 0);
				SetVehicleVirtualWorld(vehicleid, 0);
				SetVehiclePos(vehicleid, -413.4231,1010.6860,12.0819);
				SetVehicleZAngle(vehicleid, 2.8581);
				SetCameraBehindPlayer(playerid);

				TogglePlayerControllable(playerid, 1);

				SpeedometrShowForPlayer(playerid);

				SendClientMessage(playerid, -1, "Вы успешно сняли пневму со своего авто!");
				SaveOwnableCar(vehicleid);

				UpdateVehicleHandling(playerid, vehicleid);

				CEF_HIDE(playerid, "TuningPneuma");
			}
			case DIALOG_F_STYLE:
			{
				if(response)
				{
					switch(listitem + 1)
					{
						case 1:
						{
						if(GetPlayerData(playerid, P_STYLE_1) == 0)
						SendClientMessage(playerid, 0xFF0000AA, "У вас не изучен стиль боя 'Бокс'");

					    if(GetPlayerData(playerid, P_STYLE_1) == 1)
			            {
						SetPlayerFightingStyle(playerid, FIGHT_STYLE_BOXING);
						SendClientMessage(playerid, 0x33FF33AA, "Вы выбрали стиль боя 'Бокс'");
						}
						}
						case 2:
						{
						if(GetPlayerData(playerid, P_STYLE_2) == 0)
						SendClientMessage(playerid, 0xFF0000AA, "У вас не изучен стиль боя 'Кунгфу'");

					    if(GetPlayerData(playerid, P_STYLE_2) == 1)
			            {
						SetPlayerFightingStyle(playerid, FIGHT_STYLE_KUNGFU);
						SendClientMessage(playerid, 0x33FF33AA, "Вы выбрали стиль боя 'Кунгфу'");
						}
						}
						case 3:
						{
						if(GetPlayerData(playerid, P_STYLE_3) == 0)
						SendClientMessage(playerid, 0xFF0000AA, "У вас не изучен стиль боя 'СКолена'");

					    if(GetPlayerData(playerid, P_STYLE_3) == 1)
			            {
						SetPlayerFightingStyle(playerid, FIGHT_STYLE_KNEEHEAD);
						SendClientMessage(playerid, 0x33FF33AA, "Вы выбрали стиль боя 'СКолена'");
						}
						}
						case 4:
						{
						if(GetPlayerData(playerid, P_STYLE_4) == 0)
						SendClientMessage(playerid, 0xFF0000AA, "У вас не изучен стиль боя 'Проход в ноги'");

					    if(GetPlayerData(playerid, P_STYLE_4) == 1)
			            {
						SetPlayerFightingStyle(playerid, FIGHT_STYLE_GRABKICK);
						SendClientMessage(playerid, 0x33FF33AA, "Вы выбрали стиль боя 'Проход в ноги'");
						}
						}
						case 5:
						{
						if(GetPlayerData(playerid, P_STYLE_5) == 0)
						SendClientMessage(playerid, 0xFF0000AA, "У вас не изучен стиль боя 'Локтем'");

					    if(GetPlayerData(playerid, P_STYLE_5) == 1)
			            {
						SetPlayerFightingStyle(playerid, FIGHT_STYLE_ELBOW);
						SendClientMessage(playerid, 0x33FF33AA, "Вы выбрали стиль боя 'Локтем'");
						}
						}
						default:
							return 1;
					}
				}
			}
			case DIALOG_24_7:
			{
			    if(!response) return 1;
			    switch(listitem)
			    {
			        case 0:
			        {

					   	if(VerifyIntString(QueryPlayerBalance(playerid), 6000))
			            {
							GiveWeapon(playerid, 43, 15);
							SendClientMessage(playerid, 0x66CC00FF, "Вы купили фотоаппарат на 15 снимков");
				            ModifyCashBalance(playerid, -6000);
						}
						else SendClientMessage(playerid, 0xCECECEFF, "Набор фотографа стоит 6000 рублей");
			        }
			        case 1:
			        {

					   	if(VerifyIntString(QueryPlayerBalance(playerid), 6500))
			            {
							GiveWeapon(playerid, WEAPON_FLOWER, 1);
							SendClientMessage(playerid, 0x66CC00FF, "Вы купили букет цветов");
							SendClientMessage(playerid, 0x66CC00FF, "Используйте {FFCD00}/present {66CC00}чтобы подарить их кому нибудь");
				            ModifyCashBalance(playerid, -6500);
						}
						else SendClientMessage(playerid, 0xCECECEFF, "Букет стоит 6500 рублей");
			        }
			        case 2:
			        {

					   	if(VerifyIntString(QueryPlayerBalance(playerid), 18000))
			            {
							GiveWeapon(playerid, WEAPON_CANE, 1);
							SendClientMessage(playerid, 0x66CC00FF, "Вы купили трость");
				            ModifyCashBalance(playerid, -18000);
						}
						else SendClientMessage(playerid, 0xCECECEFF, "Трость стоит 18000 рублей");
			        }
					case 3:
			        {

					   	if(VerifyIntString(QueryPlayerBalance(playerid), 24000))
			            {
							GiveWeapon(playerid, WEAPON_PARACHUTE, 1);
							SendClientMessage(playerid, 0x66CC00FF, "Вы купили парашют");
				            ModifyCashBalance(playerid, -24000);
						}
						else SendClientMessage(playerid, 0xCECECEFF, "Парашют стоит 24000 рублей");
			        }
		        	case 4:
			        {
			        }
		        	case 5:
			        {
						if(!GetPlayerData(playerid, P_MASK))
						{
							if(VerifyIntString(QueryPlayerBalance(playerid), 7100))
							{
								SetPlayerData(playerid, P_MASK, 1);
								SendClientMessage(playerid, 0x66CC00FF, "Вы купили маску");
								SendClientMessage(playerid, 0x66CC00FF, "Используйте {FFCD00}/mask {66CC00}для скрытия Вашего расположения на карте (на 10 минут)");
								ModifyCashBalance(playerid, -7100);
							}
							else SendClientMessage(playerid, 0xCECECEFF, "Маска стоит 7100 рублей");
						}
						else SendClientMessage(playerid, 0x999999FF, "Вы уже приобрели маску");
			        }
		        	case 6:
			        {
						
			        }
		     	  }
			}
			case DIALOG_PLAYER_STATS: if(response) callcmd::menu(playerid);
			case DIALOG_TEMP_LEADER:
			{
			    if(!response) return 1;

				SetPlayerTeamEx(playerid, listitem + 1);
				SetPlayerData(playerid, P_JOB, 10);

				if(!GetPlayerSex(playerid))
					SetPlayerData(playerid, P_OSKIN, g_organization[listitem][O_SKINS][9]);
				else
					SetPlayerData(playerid, P_OSKIN, g_organization[listitem][O_WOMEN_SKIN]);

				SetPlayerColorEx(playerid, team_colors[listitem + 1]);

                ResetSkin(playerid);

				new fmt_msg[200];

				format(fmt_msg, sizeof fmt_msg, "Вы взяли временное лидерство организации \"%s\"", GetPlayerTeamName(playerid));
				SendClientMessage(playerid, 0xCECECEFF, fmt_msg);

				format(fmt_msg, sizeof fmt_msg, "[A] %s [%d] взял временное лидерство организации \"%s\"", GetPlayerNameEx(playerid), playerid, GetPlayerTeamName(playerid));
				SendMessageToAdmins(fmt_msg, COLOR_GREY);
			}
			case DIALOG_SECURITY_SETTING_PASS_1:
			{
				if(response)
				{
					if
					(
						strlen(inputtext)
						&& !strcmp(inputtext, GetPlayerData(playerid, P_PASSWORD), false)
					)
					{
						IntfDialogCallRemote
						(
							playerid, DIALOG_SECURITY_SETTING_PASS_2, DIALOG_STYLE_INPUT,
							"{FFD83D}Новый пароль",
							"{FFFFFF}Введите новый пароль в поле ниже:",
							"Изменить", "Отмена"
						);
						return 1;
					}
					else SendClientMessage(playerid, 0xFF6600FF, "Вы ввели неверный пароль");
				}
			}
			case DIALOG_SECURITY_SETTING_PASS_2:
			{
				if(response)
				{
					if(!(1 <= strlen(inputtext) <= 23) || strfind(inputtext, " ") != -1)
					{
						SendClientMessage(playerid, 0xFF6600FF, "Длина пароля должна быть от 6 до 15 символов");
						SendClientMessage(playerid, 0xFF6600FF, "Также не допускается использование пробелов");
					}
					else
					{
						if(strcmp(GetPlayerIpEx(playerid), GetPlayerData(playerid, P_REG_IP), false))
						{
							new lastip[64];
							new regip[64];
							strmid(lastip,GetPlayerIpEx(playerid),0,3);
							strmid(regip,GetPlayerData(playerid, P_REG_IP),0,3);

							if(strval(lastip) != strval(regip)) 
							{
								new fmt_text[148];
								format(fmt_text, sizeof fmt_text,"[A] Игрок %s[%d] неудачно попытался сменить пароль (Смена основного IP-адреса)",GetPlayerNameEx(playerid), playerid, GetPlayerIpEx(playerid), GetPlayerData(playerid, P_REG_IP));
								SendMessageToAdmins(fmt_text, 0xFF6600FF);

								printf("[AC] Игрок %s неудачно попытался сменить пароль (Смена IP-адреса) [%s (last) | %s (reg)]", GetPlayerNameEx(playerid), GetPlayerIpEx(playerid), GetPlayerData(playerid, P_REG_IP));
								return 1;
							}
						}

						new query[100];
						mysql_format(mysql, query, sizeof query, "UPDATE accounts_canvasdev SET players_password='%e' WHERE id=%d LIMIT 1", inputtext, GetPlayerAccountID(playerid));
						mysql_query(mysql, query, false);

						if(!mysql_errno())
						{
							format(g_player[playerid][P_PASSWORD], 85, "%s", inputtext);
							format(query, sizeof query, "Ваш новый пароль: {3399FF}%s", GetPlayerData(playerid, P_PASSWORD));
							SendClientMessage(playerid, 0xFFFF00FF, query);
							
							SendClientMessage(playerid, 0xFFFFFFFF, "Рекомендуем сделать скрин {00CC00}(клавиша F8) {FFFFFF}чтобы не забыть его");
							return 1;
						}
						else SendClientMessage(playerid, 0xFF6600FF, "Ошибка сохранения, повторите попытку {FF0000}(equ-code 05)");
					}
					IntfDialogCallRemote
					(
						playerid, DIALOG_SECURITY_SETTING_PASS_2, DIALOG_STYLE_INPUT,
						"{FFD83D}Новый пароль",
						"{FFFFFF}Введите новый пароль в поле ниже:",
						"Изменить", "Отмена"
					);
				}
			}
			case DIALOG_ADMIN_FLY:
			{
				if(!response) return 1;

				switch(listitem)
				{
					case 0:
					{
		   		   		new inter, world, Float:X, Float:Y, Float:Z, Float:FA;
		                GetPlayerPos(playerid, X, Y, Z);
		                GetPlayerFacingAngle(playerid, FA);
		                inter = GetPlayerInterior(playerid);
		                world = GetPlayerVirtualWorld(playerid);
		                SetPVarFloat(playerid, "SpecX", X);
		                SetPVarFloat(playerid, "SpecY", Y);
		                SetPVarFloat(playerid, "SpecZ", Z);
		                SetPVarFloat(playerid, "SpecFA", FA);
		                SetPVarInt(playerid, "SpecInt", inter);
		                SetPVarInt(playerid, "SpecWorld", world);

		                if(GetPlayerData(playerid, P_SKIN) > 0) SetPlayerSkin(playerid, GetPlayerData(playerid, P_SKIN));

                        DeletePVar(playerid, "FlyMode");
                        CancelEdit(playerid);
                        TogglePlayerSpectating(playerid, false);

                        DestroyPlayerObject(playerid, noclipdata[playerid][fly_object]);
                        noclipdata[playerid][camera_mode] = CAMERA_MODE_NONE;
                        SetPlayerSpawnInit(playerid);
                        SpawnPlayer(playerid);
                        SetPlayerPos(playerid, X, Y, Z);
                        SetPlayerFacingAngle(playerid, FA);
                        SetPlayerVirtualWorld(playerid, world);
                        SetPlayerInterior(playerid, inter);
					}
					case 1:
					{
						new inter = GetPVarInt(playerid, "SpecInt");
						DeletePVar(playerid, "SpecX");
						DeletePVar(playerid, "SpecY");
						DeletePVar(playerid, "SpecZ");
						DeletePVar(playerid, "SpecFA");
						DeletePVar(playerid, "SpecInt");
						DeletePVar(playerid, "SpecWorld");
						SetPlayerInterior(playerid, inter);
						SetPlayerScore(playerid, GetPlayerLevel(playerid));
						if(GetPlayerSuspect(playerid) > 0) SetPlayerWantedLevel(playerid, GetPlayerSuspect(playerid));
						if(GetPlayerData(playerid, P_SKIN) > 0) SetPlayerSkin(playerid, GetPlayerData(playerid, P_SKIN));
						DeletePVar(playerid, "FlyMode");
						CancelEdit(playerid);
						TogglePlayerSpectating(playerid, false);

						DestroyPlayerObject(playerid, noclipdata[playerid][fly_object]);
						noclipdata[playerid][camera_mode] = CAMERA_MODE_NONE;
						SetPlayerSpawnInit(playerid);
						SpawnPlayer(playerid);
					}
				}
			}
			case DIALOG_TAKE_ITEM_SKIN:
			{
				if(!response) return 1;

				for(new i; i < MAX_ITEMS; i++)
				{
					if(items_objs[i] != -1)
					{
						if(IsPlayerInRangeOfPoint(playerid, 2.0, itempos[i][0], itempos[i][1], itempos[i][2]))
						{
							if(inventory_kd_take[playerid] != 0) return SCM(playerid, 0xa9acafFF, "* Вы уже недавно подбирали предметы");

							if(GetInventorySlots(playerid) == -1) return GameText(playerid, "В вашем инвентаре нет свободного места", 3000, 0);

                            inventory_kd_take[playerid] = 5;

							DestroyObject(items_objs[i]);
							DestroyDynamic3DTextLabel(number_labels[i]);

							ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 2, 0, 0, 0, 0, 0);

							GiveSkin(playerid, item1[i]);

							SendClientMessage(playerid, 0xCECECEFF, "{"#cGold"}Вы подобрали предмет 'Одежда' в количестве 1.");

							items_objs[i] = -1;
							type_item[i] = 0;
							item1[i] = 0;

							STRING_GLOBAL[0] = EOS;
							format(STRING_GLOBAL,sizeof(STRING_GLOBAL), "Подобрал(а) предмет");
							SetPlayerChatBubble(playerid, STRING_GLOBAL, 0x3399FFFF, 10.0, 5000);
							DestroyDynamicArea(ItemDropSphere[i]);
							return 1;
						}
					}
				}
			}
			case DIALOG_TAKE_ITEM_GUN:
			{
				if(!response) return 1;

				for(new i; i < MAX_ITEMS; i++)
				{
					if(items_objs[i] != -1)
					{
						if(IsPlayerInRangeOfPoint(playerid, 2.0, itempos[i][0], itempos[i][1], itempos[i][2]))
						{
							if(inventory_kd_take[playerid] != 0) return SCM(playerid, 0xa9acafFF, "* Вы уже недавно подбирали предметы");

							if(GetInventorySlots(playerid) == -1) return GameText(playerid, "В вашем инвентаре нет свободного места", 3000, 0);

                            inventory_kd_take[playerid] = 5;

							DestroyObject(items_objs[i]);
							DestroyDynamic3DTextLabel(number_labels[i]);

							ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 2, 0, 0, 0, 0, 0);

							GiveWeapon(playerid, item1[i], item2[i]);

							SCMF(playerid, 0xCECECEFF, "{"#cGold"}Вы подобрали предмет 'Оружие' в количестве %d.", item2[i]);

							items_objs[i] = -1;
							type_item[i] = 0;
							item1[i] = 0;
							item2[i] = 0;

							STRING_GLOBAL[0] = EOS;
							format(STRING_GLOBAL,sizeof(STRING_GLOBAL), "Подобрал(а) предмет");
							SetPlayerChatBubble(playerid, STRING_GLOBAL, 0x3399FFFF, 10.0, 5000);
							DestroyDynamicArea(ItemDropSphere[i]);
							return 1;
						}
					}
				}
			}
			case DIALOG_TAKE_ITEM_ACS:
			{
			    if(!response) return 1;

				for(new i; i < MAX_ITEMS; i++)
				{
					if(items_objs[i] != -1)
					{
						if(IsPlayerInRangeOfPoint(playerid, 2.0, itempos[i][0], itempos[i][1], itempos[i][2]))
						{
							if(inventory_kd_take[playerid] != 0) return SCM(playerid, 0xa9acafFF, "* Вы уже недавно подбирали предметы");

							if(GetInventorySlots(playerid) == -1) return GameText(playerid, "В вашем инвентаре нет свободного места", 3000, 0);

                            inventory_kd_take[playerid] = 5;

							DestroyObject(items_objs[i]);
							DestroyDynamic3DTextLabel(number_labels[i]);

							ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 2, 0, 0, 0, 0, 0);

							CreateItemsAcs(GetPlayerAccountID(playerid), 0, 1, GetInventorySlots(playerid), item1[i], item3[i], 0, item2[i], -1, -1, 0, type_item[i]);

							STRING_GLOBAL[0] = EOS;
							format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "{"#cGold"}Вы подобрали предмет '%s' в количестве 1.", ItemsInfo[item3[i]]);
							SendClientMessage(playerid, 0xCECECEFF, STRING_GLOBAL);

							items_objs[i] = -1;
							type_item[i] = 0;
							item1[i] = 0;
							item2[i] = 0;
							item3[i] = 0;
							item4[i] = 0;

							format(STRING_GLOBAL,sizeof(STRING_GLOBAL), "Подобрал(а) предмет");
							SetPlayerChatBubble(playerid, STRING_GLOBAL, 0x3399FFFF, 10.0, 5000);
							DestroyDynamicArea(ItemDropSphere[i]);
							return 1;
						}
					}
				}
			}
			case DIALOG_TAKE_MONEY:
			{
				if(!response) return 1;

				for(new i; i < MAX_ITEMS; i++)
				{
					if(items_objs[i] != -1)
					{
						if(IsPlayerInRangeOfPoint(playerid, 2.0, itempos[i][0], itempos[i][1], itempos[i][2]))
						{
							if(inventory_kd_take[playerid] != 0) return SCM(playerid, 0xa9acafFF, "* Вы уже недавно подбирали предметы");

                            inventory_kd_take[playerid] = 5;

							DestroyObject(items_objs[i]);
							DestroyDynamic3DTextLabel(number_labels[i]);

							ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 2, 0, 0, 0, 0, 0);

							ModifyCashBalance(playerid, item2[i], "Подобрал деньги");

							STRING_GLOBAL[0] = EOS;
							format(STRING_GLOBAL, sizeof STRING_GLOBAL, "{"#cGold"}Вы подобрали предмет 'Деньги' в количестве %d.",item2[i]);
							SendClientMessage(playerid, 0xCECECEFF, STRING_GLOBAL);

							itempos[i][0]=0, itempos[i][1]=0, itempos[i][2]=-10;
							items_objs[i] = 0;
							type_item[i] = 0;
							item1[i] = 0;
							item2[i] = 0;

							format(STRING_GLOBAL,sizeof(STRING_GLOBAL), "Подобрал(а) предмет");
							SetPlayerChatBubble(playerid, STRING_GLOBAL, 0x3399FFFF, 10.0, 5000);
							DestroyDynamicArea(ItemDropSphere[i]);
							return 1;
						}
					}
				}
			}
			case DIALOG_TAKE_ITEM:
			{
			    if(!response) return 1;

				for(new i; i < MAX_ITEMS; i++)
				{
					if(items_objs[i] != -1)
					{
						if(IsPlayerInRangeOfPoint(playerid, 2.0, itempos[i][0], itempos[i][1], itempos[i][2]))
						{
							if(inventory_kd_take[playerid] != 0) return SCM(playerid, 0xa9acafFF, "* Вы уже недавно подбирали предметы");

							if(GetInventorySlots(playerid) == -1) return GameText(playerid, "В вашем инвентаре нет свободного места", 3000, 0);
							
							inventory_kd_take[playerid] = 5;

							DestroyObject(items_objs[i]);
							DestroyDynamic3DTextLabel(number_labels[i]);

							ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 2, 0, 0, 0, 0, 0);

							if(item1[i] == 279) GiveIteam(playerid, item1[i], 1, item2[i], -1, "Поднял предмет [Инвентарь]");
							else GiveIteam(playerid, item1[i], 1, item2[i], 0, "Поднял предмет [Инвентарь]");

							STRING_GLOBAL[0] = EOS;
							format(STRING_GLOBAL, sizeof STRING_GLOBAL, "{"#cGold"}Вы подобрали предмет '%s' в количестве %d.", ItemsInfo[item1[i]],item2[i]);
							SendClientMessage(playerid, 0xCECECEFF, STRING_GLOBAL);

							itempos[i][0]=0, itempos[i][1]=0, itempos[i][2]=-10;
							items_objs[i] = 0;
							type_item[i] = 0;
							item1[i] = 0;
							item2[i] = 0;

							format(STRING_GLOBAL,sizeof(STRING_GLOBAL), "Подобрал(а) предмет");
							SetPlayerChatBubble(playerid, STRING_GLOBAL, 0x3399FFFF, 10.0, 5000);
							DestroyDynamicArea(ItemDropSphere[i]);
							return 1;
						}
					}
				}
			}
			case DIALOG_TAKE_ITEM_NUMBER:
			{
			    if(!response) return 1;

				for(new i; i < MAX_ITEMS; i++)
				{
					if(items_objs[i] != -1)
					{
						if(IsPlayerInRangeOfPoint(playerid, 2.0, itempos[i][0], itempos[i][1], itempos[i][2]))
						{
							if(inventory_kd_take[playerid] != 0) return SCM(playerid, 0xa9acafFF, "* Вы уже недавно подбирали предметы");

							if(GetInventorySlots(playerid) == -1) return GameText(playerid, "В вашем инвентаре нет свободного места", 3000, 0);

                            inventory_kd_take[playerid] = 5;

							DestroyObject(items_objs[i]);
							DestroyDynamic3DTextLabel(number_labels[i]);

							ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 2, 0, 0, 0, 0, 0);

							SendClientMessage(playerid, 0xCECECEFF, "{"#cGold"}Вы подобрали предмет 'Автомобильный номер' в количестве 1.");

							CreateItemsCarNumber(GetPlayerAccountID(playerid), 0, 1, GetInventorySlots(playerid), number_item[i], region_item[i], item1[i], -1, -1, 0, 1);

							itempos[i][0]=0, itempos[i][1]=0, itempos[i][2]=-10;
							format(number_item[i], 10, "");
							format(region_item[i], 10, "");
							items_objs[i] = 0;
							type_item[i] = 0;
							item1[i] = 0;

							STRING_GLOBAL[0] = EOS;
							format(STRING_GLOBAL,sizeof(STRING_GLOBAL), "Подобрал(а) предмет");
							SetPlayerChatBubble(playerid, STRING_GLOBAL, 0x3399FFFF, 10.0, 5000);
							DestroyDynamicArea(ItemDropSphere[i]);
							return 1;
						}
					}
				}
			}
			case DIALOG_KIOSK_BUY:
			{
			    if(!response) return 1;
				new kiosk_id = GetNearestKiosk(playerid, 7.0);

				if(kiosk_id == -1) return SCM(playerid, 0xCECECEFF, "* Вы слишком далеко от киоска");
				if(GetKioskData(kiosk_id, K_OWNER_ID) != 0) return SCM(playerid, 0xCECECEFF, "* Этот киоск уже куплен");
				//if(GetPlayerData(playerid, P_KIOSK) != -1) return SCM(playerid, 0xCECECEFF, "* У вас уже есть киоск");

				IntfDialogCallRemote(playerid, DIALOG_BUY_STALL, DIALOG_STYLE_MSGBOX, "Покупка киоска", "Вы действительно хотите приобрести этот киоск?", "Да", "Нет");

				SetPVarInt(playerid, "buy_stall", kiosk_id);

				return 1;
			}
			case DIALOG_FIX_CAR:
			{
				if(response)
				{
					{
                        if(!VerifyIntString(QueryPlayerBalance(playerid), 5000000)) return SendClientMessage(playerid, 0xFF6600FF, "У Вас недостаточно средств");
                    
					    SendClientMessage(playerid, COLOR_ORANGE, "Вы купили рем. комплект!");
					    SendClientMessage(playerid, COLOR_ORANGE, "Использовать рем. комплект: {2f89f7}через инвентарь");

					    ModifyCashBalance(playerid, -5000000);

					    GiveIteam(playerid, 44, 1, 1, 0);
					}
				}
			}
			case DIALOG_REPORT_Z:
			{
				if(!response) return 1;

				new query[345];
				format(query, sizeof query, "INSERT INTO `report_mesage` (`owner_id`, `report_id`, `name`, `text`, `data`, `status`) VALUES (%d, %d, '%s', '%s', %d, 1)", GetPlayerAccountID(playerid), m_player_report_id[playerid], GetPlayerNameEx(playerid), inputtext, gettime());
				mysql_query(mysql, query, false);

				SCMF(playerid, COLOR_YELLOW, "Вы успешно ответили на запрос {FFFFFF}[№ %d]", m_player_report_id[playerid]);

				GetPVarInt(playerid, "owner_id_player");

				new to_player = GetPlayerIDBySqlID(GetPVarInt(playerid, "owner_id_player"));

				if(IsPlayerConnected(to_player) && IsPlayerLogged(to_player))
				{
					STRING_GLOBAL[0] = EOS;
					format(STRING_GLOBAL, sizeof STRING_GLOBAL, "[1, 0, \"%s\", %d]", GetPlayerNameEx(playerid), m_player_report_id[playerid]);
					CEF_CREATE(to_player, 2, 4, "Notification", STRING_GLOBAL);

					format(STRING_GLOBAL, sizeof STRING_GLOBAL, "Для %s[acc:%d]: %s", GetPlayerNameEx(to_player), GetPlayerAccountID(to_player), inputtext);
					SendLog(playerid, LOG_TYPE_ADMIN_ANSWER, STRING_GLOBAL);
				}
				m_player_report_id[playerid] = -1;

			}
			case DIALOG_REPORT_1:
			{
   				if(!response) return 1;

  			  	format(report_message[playerid], sizeof report_message, "%s", inputtext);

				if(strfind(report_message[playerid], "%~%k%~%~SWITCH_DEBUG_CAM_ON%~") != -1 || strfind(report_message[playerid],"|") != -1 || strfind(report_message[playerid],"}") != -1 || strfind(report_message[playerid],"{") != -1 || strfind(report_message[playerid],"&") != -1 || strfind(report_message[playerid],"#") != -1 || strfind(report_message[playerid],"@") != -1 || strfind(report_message[playerid],"%") != -1)
				{
				return SendClientMessage(playerid, 0xFF6600FF, "В сообщение присутствуют запрещеные символы");
				}
				if(strfind(report_message[playerid], "~k~~SWITCH_DEBUG_CAM_ON~") != -1 || strfind(report_message[playerid],"|") != -1 || strfind(report_message[playerid],"}") != -1 || strfind(report_message[playerid],"{") != -1 || strfind(report_message[playerid],"&") != -1 || strfind(report_message[playerid],"#") != -1 || strfind(report_message[playerid],"@") != -1 || strfind(report_message[playerid],"%") != -1)
				{
				return SendClientMessage(playerid, 0xFF6600FF, "В сообщение присутствуют запрещеные символы");
				}
			    if(strfind(report_message[playerid], "~k~~TAKE_SCREEN_SHOT~") != -1 || strfind(report_message[playerid],"|") != -1 || strfind(report_message[playerid],"}") != -1 || strfind(report_message[playerid],"{") != -1 || strfind(report_message[playerid],"&") != -1 || strfind(report_message[playerid],"#") != -1 || strfind(report_message[playerid],"@") != -1 || strfind(report_message[playerid],"%") != -1)
			    {
			    return SendClientMessage(playerid, 0xFF6600FF, "В сообщение присутствуют запрещеные символы");
			    }
				if(strfind(report_message[playerid], "%~%k%~%~SWITCH_DEBUG_CAM_ON%~") != -1 || strfind(report_message[playerid],"|") != -1 || strfind(report_message[playerid],"}") != -1 || strfind(report_message[playerid],"{") != -1 || strfind(report_message[playerid],"&") != -1 || strfind(report_message[playerid],"#") != -1 || strfind(report_message[playerid],"@") != -1 || strfind(report_message[playerid],"%") != -1)
				{
					return SendClientMessage(playerid, 0xFF6600FF, "В сообщение присутствуют запрещеные символы");
				}
				if(strfind(report_message[playerid],"%s") != -1)
				{
					return SendClientMessage(playerid, 0xFF6600FF, "В сообщение присутствуют запрещеные символы");
				}
				if(strfind(report_message[playerid],"%ss") != -1)
				{
					return SendClientMessage(playerid, 0xFF6600FF, "В сообщение присутствуют запрещеные символы");
				}

		    	IntfDialogCallRemote(playerid, DIALOG_REPORT_2, DIALOG_STYLE_LIST, "Выберите действие", "1. Жалоба на игрока\n2. Задать вопрос", "Далее", "Закрыть");
			}
			case DIALOG_GOTO_GPS:
        	{
        	    if(response)
        	    {
        	        TeleportPlayerGPS(playerid, GetPVarFloat(playerid, "goto_x"), GetPVarFloat(playerid, "goto_y"), GetPVarFloat(playerid, "goto_z"));

        	        DeletePVar(playerid, "goto_x");
                    DeletePVar(playerid, "goto_y");
                    DeletePVar(playerid, "goto_z");
				}
        	}
	    	case DIALOG_AFTERPOS:
			{
				if(response)
				{
					EnterPlayerToHouse(playerid, GetPlayerHouse(playerid, HOUSE_TYPE_HOME));
					if(GetPlayerData(playerid, P_JAIL))
					{
						new jail_pos = random(sizeof g_jail_positions);

						SetPlayerPosEx
						(
							playerid,
							g_jail_positions[jail_pos][0],
							g_jail_positions[jail_pos][1],
							g_jail_positions[jail_pos][2],
							g_jail_positions[jail_pos][3],
							5, 6
						);

						SetPlayerData(playerid, P_HEALTH, 100);
						SetPlayerHealthEx(playerid, 100);
						return 1;
					}
		    	}
			}
			
			case DIALOG_REPORT_2:
			{
			    if(!response) return 1;

				if(IsPlayerRMuted(playerid) > 0) return SendClientMessage(playerid, 0xFF6600FF, "У Вас заблокирован доступ к репорту. Время до разблокировки: /time");

				if(strlen(report_message[playerid]) < 3)
				{
				    SendClientMessage(playerid, 0xFF6600FF, "Слишком короткий запрос");
				    return 1;
				}
				if(strlen(report_message[playerid]) > 180)
				{
				    SendClientMessage(playerid, 0xFF6600FF, "Слишком длинный запрос");
				    return 1;
				}
				if(strfind(report_message[playerid],"|") != -1 || strfind(report_message[playerid],"}") != -1 || strfind(report_message[playerid],"{") != -1 || strfind(report_message[playerid],"&") != -1 || strfind(report_message[playerid],"#") != -1 || strfind(report_message[playerid],"@") != -1 || strfind(report_message[playerid],"%") != -1)
				{
					return SendClientMessage(playerid, 0xFF6600FF, "В сообщение присутствуют запрещеные символы");
				}
				if(strfind(report_message[playerid], "~k~~SWITCH_DEBUG_CAM_ON~") != -1 || strfind(report_message[playerid],"|") != -1 || strfind(report_message[playerid],"}") != -1 || strfind(report_message[playerid],"{") != -1 || strfind(report_message[playerid],"&") != -1 || strfind(report_message[playerid],"#") != -1 || strfind(report_message[playerid],"@") != -1 || strfind(report_message[playerid],"%") != -1)
				{
				return SendClientMessage(playerid, 0xFF6600FF, "В сообщение присутствуют запрещеные символы");
				}
			    if(strfind(report_message[playerid], "~k~~TAKE_SCREEN_SHOT~") != -1 || strfind(report_message[playerid],"|") != -1 || strfind(report_message[playerid],"}") != -1 || strfind(report_message[playerid],"{") != -1 || strfind(report_message[playerid],"&") != -1 || strfind(report_message[playerid],"#") != -1 || strfind(report_message[playerid],"@") != -1 || strfind(report_message[playerid],"%") != -1)
			    {
			    return SendClientMessage(playerid, 0xFF6600FF, "В сообщение присутствуют запрещеные символы");
			    }
				if(strfind(report_message[playerid], "%~%k%~%~SWITCH_DEBUG_CAM_ON%~") != -1 || strfind(report_message[playerid],"|") != -1 || strfind(report_message[playerid],"}") != -1 || strfind(report_message[playerid],"{") != -1 || strfind(report_message[playerid],"&") != -1 || strfind(report_message[playerid],"#") != -1 || strfind(report_message[playerid],"@") != -1 || strfind(report_message[playerid],"%") != -1)
				{
				return SendClientMessage(playerid, 0xFF6600FF, "В сообщение присутствуют запрещеные символы");
				}
				if(strfind(report_message[playerid], "%~%k%~%~SWITCH_DEBUG_CAM_ON%~") != -1 || strfind(report_message[playerid],"|") != -1 || strfind(report_message[playerid],"}") != -1 || strfind(report_message[playerid],"{") != -1 || strfind(report_message[playerid],"&") != -1 || strfind(report_message[playerid],"#") != -1 || strfind(report_message[playerid],"@") != -1 || strfind(report_message[playerid],"%") != -1)
				{
					return SendClientMessage(playerid, 0xFF6600FF, "В сообщение присутствуют запрещеные символы");
				}
				if(strfind(report_message[playerid],"%s") != -1)
				{
					return SendClientMessage(playerid, 0xFF6600FF, "В сообщение присутствуют запрещеные символы");
				}
				if(strfind(report_message[playerid],"%ss") != -1)
				{
					return SendClientMessage(playerid, 0xFF6600FF, "В сообщение присутствуют запрещеные символы");
				}

				new mes[228];

				switch(listitem + 1)
				{
				    case 1:
				    {
						format(mes,sizeof(mes),"{FF0000}Жалоба от %s [%d]:{E9DB00} %s", GetPlayerNameEx(playerid), playerid, report_message[playerid]);
						SendMessageToAdmins(mes, -1);

						format(mes,sizeof(mes),"Текст жалобы: %s", report_message[playerid]);

						SendClientMessage(playerid, -1, "Ваша жалоба была успешно отправлена. Ожидайте действий администратора");
						SendClientMessage(playerid, -1, mes);
						OnBattlePass_Perfomance(playerid, 13, 1);
				    }
				    case 2:
				    {
						format(mes,sizeof(mes),"{00FF17}Вопрос от %s [%d]:{E9DB00} %s", GetPlayerNameEx(playerid), playerid, report_message[playerid]);
						SendMessageToAdmins(mes, -1);

						format(mes,sizeof(mes),"Текст вопроса: %s", report_message[playerid]);

						SendClientMessage(playerid, -1, "Ваш вопрос был успешно отправлен. Ожидайте ответа");
						SendClientMessage(playerid, -1, mes);
						OnBattlePass_Perfomance(playerid, 13, 1);
				    }
			    }
			    SetPVarInt(playerid, "antifloodrep", gettime() + 15);
			}
			
			case DIALOG_CHANGE_NAME:
			{
				if(response)
				{
					if(!GetPVarInt(playerid, "change_name_status"))
					{
						new len = strlen(inputtext);
						if(4 <= len <= 20)
						{
							new bool: valid_name = true;
							for(new idx; idx < len; idx ++)
							{
								switch(inputtext[idx])
								{
									case 'a'..'z', 'A'..'Z', '[', ']', '_': continue;
									default:
										valid_name = false;
								}
							}

							if(!strcmp(GetPlayerNameEx(playerid), inputtext, true))
							{
								SendClientMessage(playerid, 0xFF6600FF, "Вы уже используете это имя");
							}
							else if(valid_name)
							{
								new query[128];
								new Cache: result, rows;

								mysql_format(mysql, query, sizeof query, "SELECT id FROM accounts_canvasdev WHERE name='%e' LIMIT 1", inputtext);
								result = mysql_query(mysql, query, true);

								rows = cache_num_rows();
								cache_delete(result);

								if(!rows)
								{
									SetPVarInt(playerid, "change_name_status", 1);
									SetPVarString(playerid, "change_name", inputtext);

									IntfDialogCallRemote
									(
										playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX,
										"{FFD83D}Заявка на изменение имени",
										"{FFFFFF}Ваша просьба об изменении ника отправлена администрации.\n"\
										"Вы получите сообщение, как только заявка будет обработана.\n\n"\
										"Если в течении нескольких минут Ваше имя не было изменено,\n"\
										"то, скорее всего, оно не соответствует RP правилам,\n"\
										"либо Вы уже используете RP имя.",
										"Ок", ""
									);

									format(query, sizeof query, "[Смена non rp имени] %s >> %s {FFCD00}| /okay %d для одобрения" , GetPlayerNameEx(playerid), inputtext, playerid);
									SendMessageToAdmins(query, 0x66CC99FF);

								}
								else SendClientMessage(playerid, 0xFF6600FF, "Введенное Вами имя уже используется");

							}
							else
							{
								SendClientMessage(playerid, 0xFF6600FF, "Имя уже используется или содержит недопустимые символы");
								SendClientMessage(playerid, 0xFFFFFFFF, "Используйте латинские буквы a-z A-Z, а также символы [ ] _");
							}
						}
						else SendClientMessage(playerid, 0xFF6600FF, "Недопустимый формат ввода");
					}
					else SendClientMessage(playerid, 0xCECECEFF, "Вы уже подавали заявку на изменение имени");
				}
			}
			// -----------------------------------------------------------------
			case DIALOG_HELP:
			{
				if(response)
				{
					if(0 <= listitem <= sizeof help_info - 1)
						ShowPlayerHelpSection(playerid, listitem);
				}
				else DeletePVar(playerid, "help_section");
			}
			case DIALOG_HELP_SECTION:
			{
				new sectionid = GetPVarInt(playerid, "help_section");

				if(!response && sectionid < sizeof help_info - 1)
				{
					ShowPlayerHelpSection(playerid, sectionid + 1);
				}
				else callcmd::help(playerid, "");
			}
			case DIALOG_ANIM_LIST:
			{
				if(response)
				{
					switch(listitem + 1)
					{
						case 1:
						{
							IntfDialogCallRemote
							(
								playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX,
								"Информация",
								"Для быстрого запуска нужной анимации можно использовать {FFFFFF}/anim(list) [номер категории] [номер анимации из списка]",
								"Закрыть", ""
							);
						}
						case 2:
						{
	    					IntfDialogCallRemote
							(
								playerid, DIALOG_ANIM_LIST_1, DIALOG_STYLE_LIST,
								"{9966FF}Анимации",
								"1. Махать рукой\n"\
								"2. Попрощаться\n"\
								"3. Приветствие 1\n"\
								"4. Приветствие 2\n"\
								"5. Приветствие 3\n"\
								"6. Приветствие 4\n"\
								"7. Отдать честь",
								"Выбрать", "Закрыть"
							);
						}
						case 3:
						{
							IntfDialogCallRemote
							(
								playerid, DIALOG_ANIM_LIST_2, DIALOG_STYLE_LIST,
								"{"#cGold"}Уникальные танцы",
								 "1. Аэробика\n"\
					            "2. Руки вверх\n"\
					            "3. Лучшие друзья\n"\
					            "4. Танец локтями\n"\
					            "5. Конго\n"\
					            "6. Робот\n"\
					            "7. Крисс-Кросс\n"\
					            "8. Классический\n"\
					            "9. Диско\n"\
					            "10. Хочу в пляс\n"\
					            "11. Казачок\n"\
					            "12. Фламенко\n"\
					            "13. Харлем-Шейк\n"\
					            "14. Флосс\n"\
					            "15. Грув\n"\
					            "16. Рокер\n"\
					            "17. Хип-Хоп\n"\
					            "18. Техно-Виккинг\n"\
					            "19. Торнадо\n"\
					            "20. Брейк-данс\n"\
					            "21. Флекс\n"\
					            "22. Техно-Зомби\n"\
								"23. Сияй",
							 	"Выбрать", "Закрыть"
					 		);
						}
						case 4:
						{
 							IntfDialogCallRemote
							(
								playerid, DIALOG_ANIM_LIST_3, DIALOG_STYLE_LIST,
								"{9966FF}Анимации",
								"1. Лечь на землю\n"\
								"2. Укрыться\n"\
								"3. Эффект электрошокера\n"\
								"4. Присесть\n"\
								"5. Расслаблено сесть\n"\
								"6. Спать на боку\n"\
								"7. Спать на спине\n"\
								"8. Облокотиться на бок\n"\
								"9. Лечь, оперевшись на ладонь\n"\
								"10. Сесть на стул\n"\
								"11. Сидеть уставшим за компьютером\n"\
								"12. Сидеть за столом\n"\
								"13. Сидеть и печатать\n"\
								"14. Сесть, закинув ногу на ногу\n"\
								"15. Сесть на стул (2)\n"\
								"16. Сесть на стул (3)\n"\
								"17. Лечь на землю (2)\n"\
								"18. Плохое самочувствие",
								"Выбрать", "Закрыть"
							);
						}
						case 5:
						{
 							IntfDialogCallRemote
							(
								playerid, DIALOG_ANIM_LIST_4, DIALOG_STYLE_LIST,
								"{9966FF}Анимации",
								"1. Походка пьяного\n"\
								"2. Кувыркаться",
								"Выбрать", "Закрыть"
							);
						}
						case 6:
						{
                        	IntfDialogCallRemote
							(
								playerid, DIALOG_ANIM_LIST_5, DIALOG_STYLE_LIST,
								"{9966FF}Анимации",
								"1. Вытянуть руку перед собой\n"\
								"2. Сложить руки вместе\n"\
								"3. Поза вратаря\n"\
								"4. Руки вверх!\n"\
								"5. Раздумье\n"\
								"6. Размахивать руками на месте\n"\
								"7. Смотреть наверх\n"\
								"8. Указать рукой наверх\n"\
								"9. Вытянуть правую руку",
								"Выбрать", "Закрыть"
							);
						}
						case 7:
						{
                        	IntfDialogCallRemote
							(
								playerid, DIALOG_ANIM_LIST_6, DIALOG_STYLE_LIST,
								"{9966FF}Анимации",
								"1. Подложить бомбу\n"\
								"2. Надеть маску\n"\
								"3. Предложить наркотики\n"\
								"4. Мужское курение\n"\
								"5. Женское курение\n"\
								"6. Выпить напиток\n"\
								"7. Позвать кого-то\n"\
								"8. Смотреть по сторонам\n"\
								"9. Толкнуть боком\n"\
								"10. Взять что-то и рассмотреть\n"\
								"11. Отказаться от чего-либо\n"\
								"12. Искуственное дыхание\n"\
								"13. Пощечины для лежачего\n"\
								"14. Подглядывать через что-то\n"\
								"15. Движения тореодора\n"\
								"16. Быть в страхе\n"\
								"17. Призывать к чему-либо\n"\
								"18. Сходить по-маленькому\n"\
								"19. Голосовать на остановке\n"\
								"20. Удар ногой\n"\
								"21. Стучаться в дверь\n"\
								"22. Устроить бунт\n"\
								"23. Отжимание\n"\
								"24. Просить милостыню",
								"Выбрать", "Закрыть"
							);
						}
						case 8:
						{
							IntfDialogCallRemote
							(
								playerid, DIALOG_ANIM_LIST_7, DIALOG_STYLE_LIST,
								"{9966FF}Анимации",
								"1. Шлепнуть кому-то по заднице\n"\
								"2. Поцелуй 1\n"\
								"3. Поцелуй 2\n"\
								"4. Поцелуй 3",
								"Выбрать", "Закрыть"
							);
						}
						case 9:
						{
							IntfDialogCallRemote
							(
								playerid, DIALOG_ANIM_LIST_8, DIALOG_STYLE_LIST,
								"{9966FF}Анимации",
								"1. Читать рэп\n"\
								"2. Восточное единоборство\n"\
								"3. Facepalm\n"\
								"4. Гангстерский жест\n"\
								"5. Смех",
								"Выбрать", "Закрыть"
							);
						}
						case 10:
						{
							IntfDialogCallRemote
							(
								playerid, DIALOG_ANIM_LIST_9, DIALOG_STYLE_LIST,
								"{9966FF}Анимации",
								"1. Съел что-то не то...\n"\
								"2. Перекусить",
								"Выбрать", "Закрыть"
							);
						}
						case 11:
						{
							IntfDialogCallRemote
							(
								playerid, DIALOG_ANIM_LIST_10, DIALOG_STYLE_LIST,
								"{9966FF}Эксклюзивные Анимации",
								"1. Эксклюзивный танец\n"\
								"2. Эксклюзивный танец\n"\
								"3. Эксклюзивный танец\n"\
								"4. Эксклюзивный танец\n"\
								"5. Эксклюзивный танец\n"\
								"6. Эксклюзивный танец\n"\
								"7. Эксклюзивный танец\n"\
								"8. Эксклюзивный танец\n"\
								"9. Эксклюзивный танец\n"\
								"10. Эксклюзивный танец\n"\
								"11. Эксклюзивный танец\n"\
								"12. Эксклюзивный танец",
								"Выбрать", "Закрыть"
							);
						}
					}
				}
			}
			case DIALOG_ANIM_LIST_1:
			{
				if(response)
				{
					switch(listitem + 1)
					{
					    case 1: ApplyAnimation(playerid, "ON_LOOKERS",		"wave_loop",			4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
					    case 2: ApplyAnimation(playerid, "ped",				"endchat_03",			4.0, true,  1, 1, 1, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
					    case 3: ApplyAnimation(playerid, "RIOT",			"RIOT_ANGRY",			4.0, false, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
					    case 4: ApplyAnimation(playerid, "GHANDS",			"gsign2",				4.0, false, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
					    case 5: ApplyAnimation(playerid, "GHANDS",			"gsign5",				4.0, false, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
					    case 6: ApplyAnimation(playerid, "GHANDS",			"gsign4",				4.0, false, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 7: ApplyAnimation(playerid, "FINALE",			"FIN_Cop1_Loop",	    4.10, false, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
					}
				}
			}
			case DIALOG_ANIM_LIST_2:
			{
				if(response)
				{
					switch(listitem + 1)
					{
						case 1: ApplyAnimation(playerid, "TATTOOS", "TAT_ArmL_In_O", 	4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 2: ApplyAnimation(playerid, "TATTOOS", "TAT_ArmL_In_P", 	4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 3: ApplyAnimation(playerid, "TATTOOS", "TAT_ArmL_In_T", 	4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 4: ApplyAnimation(playerid, "TATTOOS", "TAT_ArmL_Out_O", 	4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 5: ApplyAnimation(playerid, "TATTOOS", "TAT_ArmL_Pose_P", 	4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 6: ApplyAnimation(playerid, "TATTOOS", "TAT_ArmL_Pose_O", 	4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 7: ApplyAnimation(playerid, "TATTOOS", "TAT_ArmL_Pose_P", 	4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 8: ApplyAnimation(playerid, "TATTOOS", "TAT_ArmL_Pose_T", 	4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 9: ApplyAnimation(playerid, "TATTOOS", "TAT_ArmR_In_O", 	4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 10: ApplyAnimation(playerid, "TATTOOS", "none none none ", 4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 11: ApplyAnimation(playerid, "TATTOOS", "TAT_ArmR_In_T", 	4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 12: ApplyAnimation(playerid, "TATTOOS", "TAT_ArmR_Out_O", 	4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 13: ApplyAnimation(playerid, "TATTOOS", "TAT_ArmR_Out_P", 	4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 14: ApplyAnimation(playerid, "TATTOOS", "TAT_ArmR_Out_T", 	4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 15: ApplyAnimation(playerid, "TATTOOS", "TAT_ArmR_Pose_O", 4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 16: ApplyAnimation(playerid, "TATTOOS", "TAT_ArmR_Pose_P", 4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 17: ApplyAnimation(playerid, "TATTOOS", "TAT_ArmR_Pose_T", 4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 18: ApplyAnimation(playerid, "TATTOOS", "TAT_Back_In_O", 	4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 19: ApplyAnimation(playerid, "TATTOOS", "TAT_Back_Pose_T", 4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 20: ApplyAnimation(playerid, "TATTOOS", "TAT_ArmL_Out_P", 	4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 21: ApplyAnimation(playerid, "TATTOOS", "TAT_Sit_Loop_T", 	4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 22: ApplyAnimation(playerid, "TATTOOS", "TAT_Back_Sit_In_P", 4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 23: ApplyAnimation(playerid, "RYDER", "RYD_BECKON_01", 4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
					}
				}
			}
			case DIALOG_ANIM_LIST_3:
			{
				if(response)
				{
					switch(listitem + 1)
					{
						case 1: ApplyAnimation(playerid, "BEACH",			"bather",				4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 2: ApplyAnimation(playerid, "ped",				"cower", 				3.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 3: ApplyAnimation(playerid, "CRACK",			"crckdeth2",			4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 4: ApplyAnimation(playerid, "BEACH",			"ParkSit_M_loop",		4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 5: ApplyAnimation(playerid, "BLOWJOBZ",			"BJ_COUCH_LOOP_P",	4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 6: ApplyAnimation(playerid, "CRACK",			"crckidle2",			4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 7: ApplyAnimation(playerid, "CRACK",			"crckidle4",			4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 8: ApplyAnimation(playerid, "GANGS",			"leanIDLE",				4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 9: ApplyAnimation(playerid, "BEACH",			"ParkSit_W_loop",		4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 10: ApplyAnimation(playerid, "INT_HOUSE",		"LOU_Loop",				4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 11: ApplyAnimation(playerid, "INT_OFFICE",		"OFF_Sit_Bored_Loop",	4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 12: ApplyAnimation(playerid, "INT_OFFICE",		"OFF_Sit_Idle_Loop",	4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 13: ApplyAnimation(playerid, "INT_OFFICE",		"OFF_Sit_Type_Loop",	4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 14: ApplyAnimation(playerid, "JST_BUISNESS",		"girl_02",			4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 15: ApplyAnimation(playerid, "MISC",				"SEAT_LR",			4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 16: ApplyAnimation(playerid, "ped",				"SEAT_idle",		4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 17: ApplyAnimation(playerid, "SWAT",				"gnstwall_injurd",	4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 18: ApplyAnimation(playerid, "SWEET",			"Sweet_injuredloop",	4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
					}
				}
			}
			case DIALOG_ANIM_LIST_4:
			{
				if(response)
				{
					switch(listitem + 1)
					{
						case 1: ApplyAnimation(playerid, "PED",				"WALK_DRUNK",			4.0, true,  1, 1, 1, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 2: ApplyAnimation(playerid, "ped",				"Crouch_Roll_L",		4.0, true,  1, 1, 1, 1), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
					}
				}
			}
			case DIALOG_ANIM_LIST_5:
			{
				if(response)
				{
					switch(listitem + 1) // ApplyAnimation(playerid, );
					{
						case 1: ApplyAnimation(playerid, "SHOP",				"ROB_Loop_Threat",	4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 2: ApplyAnimation(playerid, "COP_AMBIENT",		"Coplook_loop",			4.0, true,  0, 1, 1, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 3: ApplyAnimation(playerid, "BSKTBALL",			"BBALL_def_loop",	4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 4: ApplyAnimation(playerid, "PED",				"HANDSUP",				4.0, 2, 1, 0, 1, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 5: ApplyAnimation(playerid, "GANGS",			"smkcig_prtl",			4.0, false, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 6: ApplyAnimation(playerid, "LOWRIDER",			"RAP_B_Loop",		4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 7: ApplyAnimation(playerid, "ON_LOOKERS",		"lkup_loop",			4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 8: ApplyAnimation(playerid, "ON_LOOKERS",		"Pointup_loop",			4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 9: ApplyAnimation(playerid, "PED",		        "Driveby_R",			4.0, true,  true, true, true, 1), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
					}
				}
			}
			case DIALOG_ANIM_LIST_6:
			{
				if(response)
				{
					switch(listitem + 1)
					{
						case 1: ApplyAnimation(playerid, "BOMBER",			"BOM_Plant",			4.0, false, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 2: ApplyAnimation(playerid, "SHOP",				"ROB_Shifty",		4.0, false, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 3: ApplyAnimation(playerid, "DEALER",			"DEALER_DEAL",			4.0, false, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 4: ApplyAnimation(playerid, "SMOKING",			"M_smklean_loop",		4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 5: ApplyAnimation(playerid, "SMOKING",			"F_smklean_loop",		4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 6: ApplyAnimation(playerid, "BAR",				"dnk_stndF_loop",		4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 7: ApplyAnimation(playerid, "CAMERA",			"camstnd_cmon",			4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 8: ApplyAnimation(playerid, "DEALER",			"DEALER_IDLE",			4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 9: ApplyAnimation(playerid, "GANGS",			"shake_carSH",			4.0, false, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 10: ApplyAnimation(playerid, "INT_SHOP",			"shop_shelf",		4.0, false, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 11: ApplyAnimation(playerid, "KISSING",			"GF_StreetArgue_02",4.0, false, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 12: ApplyAnimation(playerid, "MEDIC",			"CPR",					4.0, false, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 13: ApplyAnimation(playerid, "MISC",				"bitchslap",		4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 14: ApplyAnimation(playerid, "MISC",				"bng_wndw",			4.0, false, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 15: ApplyAnimation(playerid, "MISC",				"KAT_Throw_K",		4.0, false, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 16: ApplyAnimation(playerid, "ON_LOOKERS",		"panic_loop",			4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 17: ApplyAnimation(playerid, "ON_LOOKERS",		"shout_02",				4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 18: ApplyAnimation(playerid, "PAULNMAC",			"Piss_loop",		4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 19: ApplyAnimation(playerid, "ped",				"IDLE_taxi", 		3.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 20: ApplyAnimation(playerid, "POLICE",			"Door_Kick",			4.0, false, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 21: ApplyAnimation(playerid, "POLICE",			"CopTraf_Stop",			4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 22: ApplyAnimation(playerid, "RIOT",				"RIOT_ANGRY_B",		4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 23: ApplyAnimation(playerid, "FINALE",				"FIN_Hang_L",		4.10, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
					    case 24: ApplyAnimation(playerid, "FINALE",				"FIN_Hang_Loop",	4.10, false,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
					}
				}
			}
			case DIALOG_ANIM_LIST_7:
			{
				if(response) // ApplyAnimation(playerid, );
				{
					switch(listitem + 1)
					{
						case 1: ApplyAnimation(playerid, "SWEET",			"sweet_ass_slap",		4.0, false, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 2: ApplyAnimation(playerid, "KISSING",			"Grlfrd_Kiss_01",		4.0, false, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 3: ApplyAnimation(playerid, "KISSING",			"Grlfrd_Kiss_02",		4.0, false, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 4: ApplyAnimation(playerid, "KISSING",			"Grlfrd_Kiss_03",		4.0, false, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
					}
				}
			}
			case DIALOG_ANIM_LIST_8:
			{
				if(response)
				{
					switch(listitem + 1)
					{
						case 1: ApplyAnimation(playerid, "benchpress",		"gym_bp_celebrate",		4.0, true,  0, 1, 1, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 2: ApplyAnimation(playerid, "PARK",				"Tai_Chi_Loop",		4.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 3: ApplyAnimation(playerid, "MISC",				"plyr_shkhead",		4.0, false, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 4: ApplyAnimation(playerid, "GHANDS",			"gsign1LH", 			3.0, true,  0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 5: ApplyAnimation(playerid, "FINALE",			"FIN_Cop1_Stomp", 		4.10, false, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
					}
				}
			}
			case DIALOG_ANIM_LIST_9:
			{
				if(response)
				{
					switch(listitem + 1)
					{
						case 1: ApplyAnimation(playerid, "FOOD",				"EAT_Vomit_P", 		3.0, false, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 2: ApplyAnimation(playerid, "FOOD",				"EAT_Burger", 		3.0, false, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
					}
				}
			}
			case DIALOG_ANIM_LIST_10:
			{
				if(response)
				{
					switch(listitem + 1)
					{
						case 1: ApplyAnimation(playerid, "TATTOOS",				"TAT_ARMR_IN_P", 		4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 2: ApplyAnimation(playerid, "TATTOOS",				"TAT_BACK_IN_P", 		4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 3: ApplyAnimation(playerid, "TATTOOS",				"TAT_BACK_IN_T", 		4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 4: ApplyAnimation(playerid, "TATTOOS",				"TAT_BACK_OUT_O", 		4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 5: ApplyAnimation(playerid, "TATTOOS",				"TAT_BACK_OUT_T", 		4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 6: ApplyAnimation(playerid, "TATTOOS",				"TAT_BACK_POSE_O", 		4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 7: ApplyAnimation(playerid, "TATTOOS",				"TAT_BACK_POSE_P", 		4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 8: ApplyAnimation(playerid, "TATTOOS",				"TAT_BACK_SIT_LOOP_P", 		4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 9: ApplyAnimation(playerid, "TATTOOS",				"TAT_BACK_SIT_OUT_P", 		4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 10: ApplyAnimation(playerid, "TATTOOS",			"TAT_BEL_IN_O", 		4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 11: ApplyAnimation(playerid, "TATTOOS",			"TAT_BEL_IN_T", 		4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
						case 12: ApplyAnimation(playerid, "TATTOOS",			"TAT_BEL_OUT_O", 		4.0, true, 0, 0, 0, 0), SetPlayerData(playerid, P_USE_ANIM, true), CEF_CREATE(playerid, 2, 4, "Interactions", "[[17, \"Выключить анимацию\"]]");
					}
				}
			}
			// -----------------------------------------------------------------
			case DIALOG_OPEN_HOOD_OR_TRUNK:
			{
				new vehicleid = GetPlayerVehicleID(playerid);
				if(vehicleid)
				{
					new E_VEHICLE_PARAMS_STRUCT: param = response ? V_BONNET : V_BOOT;
					new set_status = GetVehicleParam(vehicleid, param) ^ VEHICLE_PARAM_ON;

					SetVehicleParam(vehicleid, param, set_status);
				}
			}
			// -----------------------------------------------------------------
            case DIALOG_DRIVING_TUTORIAL_START:
			{
				if(response)
				{
   	                CEF_CREATE(playerid, 1, 2, "openInterface('Theory')");
					return 1;
				}
			}
			case DIALOG_DRIVING_TUTORIAL_LIST:
			{
				if(response)
				{
					switch(listitem + 1)
					{
					    case 1:
					    {
					        CEF_HIDE(playerid, "DrivingExamTheory");
					        CEF_CREATE(playerid, 2, 4,"DrivingExamTheory", "[0]");
					    }
					    case 2:
					    {
					        CEF_HIDE(playerid, "DrivingExamTheory");
					        CEF_CREATE(playerid, 2, 4,"DrivingExamTheory", "[1]");
					    }
					    case 3:
					    {
					        CEF_HIDE(playerid, "DrivingExamTheory");
					        CEF_CREATE(playerid, 2, 4,"DrivingExamTheory", "[2]");
					    }
					    case 4:
					    {
					        CEF_HIDE(playerid, "DrivingExamTheory");
					        CEF_CREATE(playerid, 2, 4,"DrivingExamTheory", "[3]");
					    }
					    case 5:
					    {
					        CEF_HIDE(playerid, "DrivingExamTheory");
					        CEF_CREATE(playerid, 2, 4,"DrivingExamTheory", "[4]");
					    }
					}
				}
				else
				{
					IntfDialogCallRemote
					(
						playerid, DIALOG_DRIVING_TUTORIAL_START, DIALOG_STYLE_MSGBOX,
						"{FFD83D}Введение",
						"{FFFFFF}Это пособие поможет вам хорошо подготовиться к экзамену по вождению. Для того чтобы начать обучение нажмите \'Далее\'.",
						"Далее", "Отмена"
					);
				}
			}
			case DIALOG_DRIVING_TUTORIAL:
			{
				new step = GetPVarInt(playerid, "driving_tutorial_step");
				if(response)
				{
					step ++;
				}
				else step --;

				if(step >= sizeof driving_tutorial)
				{
					IntfDialogCallRemote
					(
						playerid, DIALOG_DRIVING_TUTORIAL_END, DIALOG_STYLE_MSGBOX,
						"{FFD83D}Завершение",
						"{FFFFFF}Надеемся вы все внимательно прочли и готовы приступить к сдаче экзамена\n"\
						"Если вы сомневаетесь в чем-либо, то рекомендуем не рисковать и прочитать нужный раздел еще раз!\n\n"\
						"{CC9900}Желаем Вам удачи на экзамене!\n"\
						"Для того, чтобы завершить обучение нажмите Выход",
						"Выход", "Назад"
					);
				}
				else if(step < 0)
				{
					ShowPlayerDrivingTutorial(playerid);
				}
				else
				{
					ShowDrivingTutorialSection(playerid, step);

					if(step == 1)
					{
						SpeedometrShowForPlayer(playerid);
					}
					else SpeedometrHideForPlayer(playerid);
				}
			}
			case DIALOG_DRIVING_TUTORIAL_END:
			{
				if(!response)
					ShowDrivingTutorialSection(playerid, sizeof driving_tutorial - 1);
			}
			case DIALOG_DRIVING_EXAM_INFO:
			{
				if(!response) return 1;

				if(GetPlayerData(playerid, P_DRIVING_LIC) >= 1) return SendClientMessage(playerid, 0xCECECEFF, "У Вас уже есть права");

				if(!VerifyIntString(QueryPlayerBalance(playerid), 2500000)) return SendClientMessage(playerid, 0xCECECEFF, "Сдача на права стоит 2500000 рублей");

				ModifyCashBalance(playerid, -2500000, "Сдача на права");
				SetPVarInt(playerid, "autoschool_point",9);

				new vehicleid = AddStaticVehicleEx(15121,1916.3922,1925.9412,15.6825,89.1559,17,17, 300, 0, VEHICLE_ACTION_TYPE_DRIVING_SCH);

				SetPlayerVirtualWorld(playerid, playerid + 1);

				SetVehicleVirtualWorld(vehicleid, playerid + 1);

				PutPlayerInVehicle(playerid, vehicleid, 0);
				SetPlayerInterior(playerid, 0);
				PACKET_215(playerid, 32, vehicleid, 1, GenerateCarNumberRu(), GenerateCarRegRu());
			}
			// -----------------------------------------------------------------
			case DIALOG_ATM:
			{
				if(response)
				{
					switch(listitem+1)
					{
						case 1,2: // Снять\Положить с банковского счета
						{
							ShowPlayerATMSelectSumDialog(playerid, !listitem);
						}
						case 3: // Баланс банковского счета
						{
							new fmt_str[64];
							format(fmt_str, sizeof fmt_str, "{FFFFFF}На Вашем банковском счету {00CC00}%s руб", formatStr(GetPlayerBankMoney(playerid)));

							IntfDialogCallRemote
							(
								playerid, DIALOG_ATM_BALANCE, DIALOG_STYLE_MSGBOX,
								"{FFCD00}Баланс счета",
								fmt_str,
								"Назад", "Выйти"
							);
						}
						case 4: // Снять со счета предприятия
						{
							//ShowPlayerATMCompanyDialog(playerid, true);
							new query[256],
								Cache: result,
								biz_id,
								biz_name[64];

							mysql_format(mysql, query, sizeof query, "SELECT * FROM business WHERE owner_id='%d'", GetPlayerAccountID(playerid));
							result = mysql_query(mysql, query, true);

							new rows = cache_num_rows();

							if(!rows)
								return SendClientMessage(playerid, 0x999999FF, "У вас не одного бизнеса во владении.");

							vibor_biz_atm[playerid] = 2;

							string_dialog[0] = EOS;
							for(new i = 0; i < rows; i ++)
							{
								biz_id = cache_get_field_content_int(i, "id");
								cache_get_field_content(i, "name", biz_name);

								format(query, sizeof query, "{FFFFFF}%d. - %s (№%d)<t>Владелец\n", i + 1, biz_name, biz_id);
								strcat(string_dialog, query);
								SetPlayerListitemValue(playerid, i, biz_id-1);
							}

							IntfDialogCallRemote
							(
								playerid, DIALOG_ATM_BIZ_LIST, DIALOG_STYLE_LIST,
								"{FFCD00}Выберите бизнес",
								string_dialog,
								"Выбрать", "Закрыть"
							);

							cache_delete(result);
						}
						case 5: // Положить на счет предприятия
						{
							//ShowPlayerATMCompanyDialog(playerid, false);
							new query[256],
								Cache: result,
								kiosk_id;

							mysql_format(mysql, query, sizeof query, "SELECT * FROM kiosk WHERE owner_id='%d'", GetPlayerAccountID(playerid));
							result = mysql_query(mysql, query, true);

							new rows = cache_num_rows();

							if(!rows)
								return SendClientMessage(playerid, 0x999999FF, "У вас не одного киоска во владении.");

                            vibor_kiosk_atm[playerid] = 1;

							string_dialog[0] = EOS;
							for(new i = 0; i < rows; i ++)
							{
								kiosk_id = cache_get_field_content_int(i, "id");

								format(query, sizeof query, "{FFFFFF}Киоск №%d\n", kiosk_id);
								strcat(string_dialog, query);
								SetPlayerListitemValue(playerid, i, kiosk_id-1);
							}

							IntfDialogCallRemote
							(
								playerid, DIALOG_ATM_KIOSK_LIST, DIALOG_STYLE_LIST,
								"{FFCD00}Выберите киоск",
								string_dialog,
								"Выбрать", "Закрыть"
							);

							cache_delete(result);
						}
						case 6: // Положить на счет предприятия
						{
							new biz_id,
								biz_name[64],
								query[256],
								Cache: result;

							mysql_format(mysql, query, sizeof query, "SELECT * FROM business WHERE owner_id='%d'", GetPlayerAccountID(playerid));
							result = mysql_query(mysql, query, true);

							new rows = cache_num_rows();

							if(!rows) return SendClientMessage(playerid, 0x999999FF, "У вас не одного бизнеса во владении.");

                            vibor_biz_atm[playerid] = 1;

							string_dialog = "";
							for(new i = 0; i < rows; i ++)
							{
								biz_id = cache_get_field_content_int(i, "id");
								cache_get_field_content(i, "name", biz_name);

								format(query, sizeof query, "{FFFFFF}%d. - %s (№%d)<t>Владелец\n", i + 1, biz_name, biz_id);
								strcat(string_dialog, query);
								SetPlayerListitemValue(playerid, i, biz_id-1);
							}

							IntfDialogCallRemote
							(
								playerid, DIALOG_ATM_BIZ_LIST, DIALOG_STYLE_LIST,
								"{FFCD00}Выберите бизнес",
								string_dialog,
								"Выбрать", "Закрыть"
							);

							cache_delete(result);
						}
						case 7: // Пополнить мобильный телефон
						{
							if(GetPlayerPhone(playerid) != 0)
							{
								IntfDialogCallRemote
								(
									playerid, DIALOG_ATM_PHONE_BALANCE, DIALOG_STYLE_INPUT,
									"{FFD83D}Пополнение мобильного телефона",
									"{FFFFFF}Укажите сумму, на которую хотите пополнить счёт:",
									"Готово", "Назад"
								);
							}
							else
							{
								SendClientMessage(playerid, 0x999999FF, "У Вас нет телефона. Его можно купить в сотовом салоне");
								ShowPlayerATMDialog(playerid);
							}
						}
						case 8: // Безналичный перевод
						{
							if(GetPlayerLevel(playerid) >= 3)
							{
								IntfDialogCallRemote
								(
									playerid, DIALOG_ATM_TRANSFER_MONEY_1, DIALOG_STYLE_INPUT,
									"{FFD83D}Безналичный перевод",
									"{FFFFFF}Укажите номер банковского счета:",
									"Далее", "Отмена"
								);
							}
							else SendClientMessage(playerid, 0x999999FF, "Перевод денег доступен с 3 уровня");
						}
						case 9:
						{
							IntfDialogCallRemote
							(
								playerid, DIALOG_ATM_TICKET_SELECT, DIALOG_STYLE_LIST,
								"{FFD83D}Оплатить штраф",
								"1. Посмотреть список своих штрафов\n"\
								"2. Оплатить штраф по его номеру\n"\
								"3. Оплатить все штрафы",
								"Далее", "Назад"
							);
						}
						case 10: ShowPlayerATMCharityDialog(playerid);
						case 11: // Благотворительность
						{
							new query[256],
								Cache: result,
								biz_id;

							mysql_format(mysql, query, sizeof query, "SELECT * FROM neftenasos WHERE owner_id='%d'", GetPlayerAccountID(playerid));
							result = mysql_query(mysql, query, true);

							new rows = cache_num_rows();

							if(!rows)
								return SendClientMessage(playerid, 0x999999FF, "У вас не одного нефтенасоса во владении.");

							string_dialog[0] = EOS;
							for(new i = 0; i < rows; i ++)
							{
								biz_id = cache_get_field_content_int(i, "id");

								format(query, sizeof query, "{FFFFFF}Нефтенасос №%d\n", biz_id);
								strcat(string_dialog, query);
								SetPlayerListitemValue(playerid, i, biz_id-1);
							}

							IntfDialogCallRemote
							(
								playerid, DIALOG_OWNABLE_NEFTENASOS_LIST, DIALOG_STYLE_LIST,
								"{FFCD00}Выберите нефтяной насос",
								string_dialog,
								"Далее", "Назад"
							);

							cache_delete(result);
						}
						default:
							return 1;
					}
					ApplyAnimation(playerid, "CRIB", "CRIB_Use_Switch", 4.0, 0, 0, 0, 0, 0, 0);
				}
			}
			case DIALOG_ATM_TAKE_MONEY: // снять деньги
			{
				if(response)
				{
					if(0 <= listitem <= 6)
					{
						new sum = atm_item_sum[listitem];
						if(VerifyIntString(GetPlayerBankMoney(playerid), sum))
						{
							format(g_player[playerid][P_BANK], 21, "%s", SetILPlayerInt(playerid, GetPlayerBankMoney(playerid), -sum));
							ModifyCashBalance(playerid, sum, "Снятие денег с банкомата");

							new query[85];
							format(query, sizeof query, "UPDATE accounts_canvasdev SET money=%s,bank=%s WHERE id=%d LIMIT 1", QueryPlayerBalance(playerid), GetPlayerBankMoney(playerid), GetPlayerAccountID(playerid));
							mysql_query(mysql, query, false);

							ApplyAnimation(playerid, "CRIB", "CRIB_Use_Switch", 4.0, 0, 0, 0, 0, 0, 0);
							ShowPlayerATMDialog(playerid);
						}
						else
						{
							SendClientMessage(playerid, 0xCECECEFF, "На Вашем банковском счету недостаточно средств");
							ShowPlayerATMSelectSumDialog(playerid, true);
						}
					}
					else ShowPlayerATMSelectOtherSum(playerid, true);
				}
				else
				{
					ApplyAnimation(playerid, "CRIB", "CRIB_Use_Switch", 4.0, 0, 0, 0, 0, 0, 0);
					ShowPlayerATMDialog(playerid);
				}
			}
			case DIALOG_ATM_TAKE_OTHER_MONEY: // снять деньги (другая сума)
			{
				if(response)
				{
					if(IsILNumeric(inputtext))
					{
						if(GetILPlayerStr(GetPlayerBankMoney(playerid), inputtext))
						{
							new money_str[23];
							format(money_str, sizeof money_str, "-%s", inputtext);

							format(g_player[playerid][P_BANK], 21, "%s", SetILPlayerStr(playerid, GetPlayerBankMoney(playerid), money_str));
							GivePlayerMoneyStr(playerid, inputtext, "Снятие денег с банкомата");

							new query[85];
							format(query, sizeof query, "UPDATE accounts_canvasdev SET bank=%s WHERE id=%d LIMIT 1", GetPlayerBankMoney(playerid), GetPlayerAccountID(playerid));
							mysql_query(mysql, query, false);

							ApplyAnimation(playerid, "CRIB", "CRIB_Use_Switch", 4.0, 0, 0, 0, 0, 0, 0);
							ShowPlayerATMDialog(playerid);
						}
						else
						{
							SendClientMessage(playerid, 0xCECECEFF, "На Вашем банковском счету недостаточно средств");
							ShowPlayerATMSelectOtherSum(playerid, true);
						}
					}
					else ShowPlayerATMSelectOtherSum(playerid, true);
				}
				else
				{
					ApplyAnimation(playerid, "CRIB", "CRIB_Use_Switch", 4.0, 0, 0, 0, 0, 0, 0);
					ShowPlayerATMSelectSumDialog(playerid, true);
				}
			}
			case DIALOG_ATM_PUT_MONEY: // положить деньги
			{
				if(response)
				{
					if(0 <= listitem <= 6)
					{
						new sum = atm_item_sum[listitem];
						if(VerifyIntString(QueryPlayerBalance(playerid), sum))
						{
							format(g_player[playerid][P_BANK], 21, "%s", SetILPlayerInt(playerid, GetPlayerBankMoney(playerid), sum));
							ModifyCashBalance(playerid, -sum, "Пополнение денег в банкомате");

							new query[85];
							format(query, sizeof query, "UPDATE accounts_canvasdev SET money=%s,bank=%s WHERE id=%d LIMIT 1", QueryPlayerBalance(playerid), GetPlayerBankMoney(playerid), GetPlayerAccountID(playerid));
							mysql_query(mysql, query, false);

							ApplyAnimation(playerid, "CRIB", "CRIB_Use_Switch", 4.0, 0, 0, 0, 0, 0, 0);
							ShowPlayerATMDialog(playerid);
						}
						else
						{
							SendClientMessage(playerid, 0xCECECEFF, "У Вас с собой нет столько денег");
							ShowPlayerATMSelectSumDialog(playerid, false);
						}
					}
					else ShowPlayerATMSelectOtherSum(playerid, false);
				}
				else
				{
					ApplyAnimation(playerid, "CRIB", "CRIB_Use_Switch", 4.0, 0, 0, 0, 0, 0, 0);
					ShowPlayerATMDialog(playerid);
				}
			}
	       	case DIALOG_ATM_BIZ_LIST:
			{
				new idx = GetPlayerListitemValue(playerid, listitem) + 1;
				SetPVarInt(playerid, "ownablebiz_id", idx);
				if(vibor_biz_atm[playerid] == 2)
				{
					IntfDialogCallRemote
					(
						playerid, DIALOG_ATM_BIZ_TAKE_MONEY, DIALOG_STYLE_INPUT,
						"{FFCD00}Снятие с счёта бизнеса",
						"{FFFFFF}Укажите сумму, на которую хотите снять счёт данного бизнеса:",
						"Готово", "Назад"
					);
				}
				if(vibor_biz_atm[playerid] == 1)
				{
				    IntfDialogCallRemote
					(
						playerid, DIALOG_ATM_BIZ_PUT_MONEY, DIALOG_STYLE_INPUT,
						"{FFCD00}Пополнение счёта бизнеса",
						"{FFFFFF}Укажите сумму, на которую хотите пополнить счёт:",
						"Готово", "Назад"
					);
				}
             }
            case DIALOG_ATM_KIOSK_LIST:
			{
				new idx = GetPlayerListitemValue(playerid, listitem) + 1;
				new fmt_text[210];
				SetPVarInt(playerid, "ownablekiosk_id", idx);
				if(vibor_kiosk_atm[playerid] == 1)
				{
					format
				    (
				        fmt_text, sizeof fmt_text,
				        "{FFFFFF}Киоск: {006400}№%d\n"\
				        "{FFFFFF}Баланс: {006400}%s руб.\n\n"\
				        "{FFFFFF}Сколько вы хотите снять?",
				        idx, formatStr(GetKioskData(idx, K_BALANCE))
				    );

				    IntfDialogCallRemote(playerid, DIALOG_ATM_KIOSK_TAKE_MONEY, DIALOG_STYLE_INPUT, "{FFCD00}Снятие средств", fmt_text, "Да", "Нет");
				}
    		}
			case DIALOG_ATM_PUT_OTHER_MONEY: // положить деньги (другая сума)
			{
				if(response)
				{
					if(IsILNumeric(inputtext))
					{
						if(!GetILPlayerStr(QueryPlayerBalance(playerid), inputtext)) return SCM(playerid, 0xCECECEFF, "У Вас с собой нет столько денег"), ShowPlayerATMSelectOtherSum(playerid, false);

						format(g_player[playerid][P_BANK], 21, "%s", SetILPlayerStr(playerid, GetPlayerBankMoney(playerid), inputtext));
						
						new money_str[23];
						format(money_str, sizeof money_str, "-%s", inputtext);
						GivePlayerMoneyStr(playerid, money_str, "Пополнение денег в банкомате", true, true);

						new query[149];
						format(query, sizeof query, "UPDATE accounts_canvasdev SET money=%s, bank=%s WHERE id=%d LIMIT 1", QueryPlayerBalance(playerid), GetPlayerBankMoney(playerid), GetPlayerAccountID(playerid));
						mysql_query(mysql, query, false);

						ApplyAnimation(playerid, "CRIB", "CRIB_Use_Switch", 4.0, 0, 0, 0, 0, 0, 0);
						ShowPlayerATMDialog(playerid);
						
					}
					else ShowPlayerATMSelectOtherSum(playerid, false);
				}
				else
				{
					ApplyAnimation(playerid, "CRIB", "CRIB_Use_Switch", 4.0, 0, 0, 0, 0, 0, 0);
					ShowPlayerATMSelectSumDialog(playerid, false);
				}
			}
			case DIALOG_ATM_BALANCE:
			{
				if(response)
				{
					ApplyAnimation(playerid, "CRIB", "CRIB_Use_Switch", 4.0, 0, 0, 0, 0, 0, 0);
					ShowPlayerATMDialog(playerid);
				}
			}
			case DIALOG_ATM_PHONE_BALANCE:
			{
				if(response)
				{
					new sum = strval(inputtext);
					if(sum > 0 && IsNumeric(inputtext))
					{
						if(VerifyIntString(QueryPlayerBalance(playerid), sum))
						{
							new query[128];

							format(query, sizeof query, "UPDATE accounts_canvasdev SET money=%s,phone_balance=%d WHERE id=%d LIMIT 1", SetILPlayerInt(playerid, QueryPlayerBalance(playerid), -sum), GetPlayerData(playerid, P_PHONE_BALANCE)+sum, GetPlayerAccountID(playerid));
							mysql_query(mysql, query, false);

							if(!mysql_errno())
							{
								ModifyCashBalance(playerid, -sum, "Пополнение счета телефона", false, true);
								AddPlayerData(playerid, P_PHONE_BALANCE, +, sum);

								format(query, sizeof query, "Вы пополнили счет мобильного телефона на {FF9900}%d руб", sum);
								SendClientMessage(playerid, 0x66CC00FF, query);

								format(query, sizeof query, "Сейчас на счету %d руб", GetPlayerData(playerid, P_PHONE_BALANCE));
								SendClientMessage(playerid, 0x66CC00FF, query);

								return 1;
							}
							else SendClientMessage(playerid, 0xFF6600FF, "Ошибка сохранения, повторите попытку {FF0000}(equ-code 15)");
						}
						else SendClientMessage(playerid, 0xCECECEFF, "У Вас не хватает денег");

						ApplyAnimation(playerid, "CRIB", "CRIB_Use_Switch", 4.0, 0, 0, 0, 0, 0, 0);
					}

					IntfDialogCallRemote
					(
						playerid, DIALOG_ATM_PHONE_BALANCE, DIALOG_STYLE_INPUT,
						"{FFD83D}Пополнение мобильного телефона",
						"{FFFFFF}Укажите сумму, на которую хотите пополнить счёт:",
						"Готово", "Назад"
					);
				}
				else
				{
					ShowPlayerATMDialog(playerid);
					ApplyAnimation(playerid, "CRIB", "CRIB_Use_Switch", 4.0, 0, 0, 0, 0, 0, 0);
				}
			}
			case DIALOG_ATM_SELECT_COMPANY_TAKE, DIALOG_ATM_SELECT_COMPANY_PUT:
			{
				if(response)
				{
					new bool: action = (dialogid == DIALOG_ATM_SELECT_COMPANY_TAKE);

					switch(listitem + 1)
					{
						case 1:
							ShowPlayerATMBusinessDialog(playerid, action);
					}
				}
				else
				{
					ShowPlayerATMDialog(playerid);
					ApplyAnimation(playerid, "CRIB", "CRIB_Use_Switch", 4.0, 0, 0, 0, 0, 0, 0);
				}
			}
			case DIALOG_TAXI:
			{
				if(!response) return RemovePlayerFromVehicle(playerid);

				new vehicleid = GetPlayerVehicleID(playerid);

				new action_type = GetVehicleData(vehicleid, V_ACTION_TYPE);
				new action_id = GetVehicleData(vehicleid, V_ACTION_ID);

				if(action_type == VEHICLE_ACTION_TYPE_TAXI && action_id == VEHICLE_ACTION_ID_NONE)
				{
					if(VerifyIntString(QueryPlayerBalance(playerid), 15000))
					{
						if(ModifyCashBalance(playerid, -15000, "Аренда такси", true, true) == -1) return false;
                        SetPlayerData(playerid, P_JOB_CAR, vehicleid);
					}
					else SendClientMessage(playerid, 0x999999FF, "У Вас недостаточно денег чтобы заключить договор аренды");
				}
			}
			case DIALOG_BY_EXIT_MVD:
			{
				if(!response) return 1;
				SendClientMessage(playerid,0x008000FF,"{ffffff}Вы успешно выехали из парковки"); // Выводим оповещение
				SetVehiclePos(GetPlayerVehicleID(playerid), 210.4814,1367.2345,12.1203);
				SetVehicleZAngle(GetPlayerVehicleID(playerid), 169.9973);
				SetVehicleVirtualWorld(GetPlayerVehicleID(playerid), 0);
				LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerInterior(playerid, 0);
			}
			case DIALOG_BY_EXIT_FSB:
			{
				if(!response) return 1;
				SendClientMessage(playerid,0x008000FF,"{ffffff}Вы успешно выехали из парковки"); // Выводим оповещение
				SetVehiclePos(GetPlayerVehicleID(playerid), 2303.9138,-1745.8698,22.0086);
				SetVehicleZAngle(GetPlayerVehicleID(playerid), 269.1853);
				SetVehicleVirtualWorld(GetPlayerVehicleID(playerid), 0);
				LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerInterior(playerid, 0);
			}
			case DIALOG_PARKING_RESPAWN:
			{
				if(!response) return 1;

				new vehicleid = GetPlayerVehicleID(playerid);
				if(IsPlayerInAnyVehicle(playerid))
				{
					if(GetVehicleData(vehicleid, V_ACTION_TYPE) == VEHICLE_ACTION_TYPE_ORG_CARS) SetVehicleToRespawn(vehicleid);

                    new idx = GetVehicleData(vehicleid, V_ACTION_ID);
					SetVehicleVirtualWorld(org_cars_canvasdev[idx][ORG_CARS_VEHICLEID], org_cars_canvasdev[idx][ORG_CARS_WORLD]);
		            LinkVehicleToInterior(org_cars_canvasdev[idx][ORG_CARS_VEHICLEID], org_cars_canvasdev[idx][ORG_CARS_INTERIOR]);
				}
			}
   			case DIALOG_BY_EXIT_HOSPITAL:
			{
				if(!response) return 1;
				SendClientMessage(playerid,0x008000FF,"{ffffff}Вы успешно выехали из парковки"); // Выводим оповещение
				SetVehiclePos(GetPlayerVehicleID(playerid), 674.4968,1793.6567,11.8217);
				SetVehicleZAngle(GetPlayerVehicleID(playerid), 131.7351);
				SetVehicleVirtualWorld(GetPlayerVehicleID(playerid), 0);
				LinkVehicleToInterior(GetPlayerVehicleID(playerid), 0);
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerInterior(playerid, 0);
   			}
   			case DIALOG_PARKING:
            {
                if(!response) return 1;

                new team = GetPlayerTeamEx(playerid);

                for(new i = 0; i < MAX_ORG_PARKING; i++)
                {
                    if(org_park_canvasdev[i][ORG_PARK_ID] == team)
                    {
                        new Float:x = org_park_canvasdev[i][ORG_PARK_POS_PLAYER_ENTER][0];
                        new Float:y = org_park_canvasdev[i][ORG_PARK_POS_PLAYER_ENTER][1];
                        new Float:z = org_park_canvasdev[i][ORG_PARK_POS_PLAYER_ENTER][2];
                        new Float:a = org_park_canvasdev[i][ORG_PARK_POS_PLAYER_ENTER][3];

						new interior = org_park_canvasdev[i][ORG_PARK_PARAM_INT_VR][0];
						new virtualworld = org_park_canvasdev[i][ORG_PARK_PARAM_INT_VR][1];

						SetPlayerPosEx(playerid, x, y, z, a, interior, virtualworld);
						OverlayScreen(playerid);
                    }
                }
            }
			case DIALOG_BY_EXIT_SR:
			{
			    if(!response) return 1;
			    new vehicleid = GetPVarInt(playerid, "veh_id");

				new index = GetVehicleData(vehicleid, V_ACTION_ID);
				GetOwnableCarData(index, OC_POS_X) = GetOwnableCarData(index, OC_BY_POS_X);
				GetOwnableCarData(index, OC_POS_Y) = GetOwnableCarData(index, OC_BY_POS_Y);
				GetOwnableCarData(index, OC_POS_Z) = GetOwnableCarData(index, OC_BY_POS_Z);
				GetOwnableCarData(index, OC_ANGLE) = GetOwnableCarData(index, OC_BY_ANGLE);
				
				SendClientMessage(playerid, 0xFFDAB9FF, "Ваше т/с было снято с продажи");
				SendClientMessage(playerid, 0xFFA500FF, "Ваш транспорт был снят с продажи, припаркован на том месте, где находился до аренды и выгружен");
				
				if(GetOwnableCarData(index, OC_BY_ID) == 2)
				{
    				bymestasr[GetOwnableCarData(index, OC_MESTOID)] = 0;
    			}

				new query[190];

			    format(query, sizeof query, "UPDATE ownable_cars SET inter=0,world=0 WHERE id=%d LIMIT 1",GetOwnableCarData(index, OC_SQL_ID));
			    mysql_tquery(mysql, query, "", "");

				SaveOwnableCar(vehicleid);

				UnloadPlayerOwnableCar(true, vehicleid);
			}
			case DIALOG_BY_EXIT:
			{
			    if(!response) return 1;
			    new vehicleid = GetPVarInt(playerid, "veh_id");

				new index = GetVehicleData(vehicleid, V_ACTION_ID);
				GetOwnableCarData(index, OC_POS_X) = GetOwnableCarData(index, OC_BY_POS_X);
				GetOwnableCarData(index, OC_POS_Y) = GetOwnableCarData(index, OC_BY_POS_Y);
				GetOwnableCarData(index, OC_POS_Z) = GetOwnableCarData(index, OC_BY_POS_Z);
				GetOwnableCarData(index, OC_ANGLE) = GetOwnableCarData(index, OC_BY_ANGLE);
				
				SendClientMessage(playerid, 0xFFDAB9FF, "Ваше т/с было снято с продажи");
				SendClientMessage(playerid, 0xFFA500FF, "Ваш транспорт был снят с продажи, припаркован на том месте, где находился до аренды и выгружен");
				
				if(GetOwnableCarData(index, OC_BY_ID) == 1)
				{
    				bymestavis[GetOwnableCarData(index, OC_MESTOID)] = 0;
    			}

				new query[190];

			    format(query, sizeof query, "UPDATE ownable_cars SET inter=0,world=0 WHERE id=%d LIMIT 1",GetOwnableCarData(index, OC_SQL_ID));
			    mysql_tquery(mysql, query, "", "");

				SaveOwnableCar(vehicleid);

				UnloadPlayerOwnableCar(true, vehicleid);
			}
			case DIALOG_SET_MIN_PRICE:
			{
				if(!response) return 1;

				new kiosk_id = GetNearestKiosk(playerid, 7.0);
				new price = strval(inputtext);
				new str_c[128];
				new query[512];

				if(price < 500) return SCM(playerid, 0xCECECEFF, "* Минимальная цена не должна быть меньше 500 руб.");
				if(price > 50000) return SCM(playerid, 0xCECECEFF, "* Минимальная цена не должна быть более чем 50000 руб.");

				mysql_format(mysql, query, sizeof query, "UPDATE kiosk SET min_price=%d WHERE id=%d", price, GetKioskData(kiosk_id, K_SQL_ID));
				mysql_query(mysql, query, false);

				SetKioskData(kiosk_id, K_MIN_PRICE, price);

				format(str_c, sizeof str_c, "Вы успешно поставили минимальную цену в {FFFFFF}%d руб.", price);
				SCM(playerid, 0xADCEEAFF, str_c);
			}
			case DIALOG_SELL_ITEM_KIOSK:
			{
				if(!response) return 1;

				new kiosk_id = GetNearestKiosk(playerid, 7.0);
				new count = strval(inputtext);
				new h_count = GetIteamIndx(playerid, GetPVarInt(playerid, "SellItem"), GetPVarInt(playerid, "SellItemIndx"));

				new str_c[248];

				if(count > h_count) return SCM(playerid, 0xCECECEFF, "* У вас нет столько единиц этого предмета.");
                if(0 >= count) return SCM(playerid, 0xCECECEFF, "* Некорректное значение.");

				SetPVarInt(playerid, "SellItemCount", count);

				format(str_c, sizeof str_c, "{FFFFFF}Введите цену за {006400}1 {FFFFFF}шт.\nЦена не должна быть меньше {006400}%d {FFFFFF}руб.", GetKioskData(kiosk_id, K_MIN_PRICE));

				IntfDialogCallRemote(playerid, DIALOG_SELL_ITEM_PRICE, DIALOG_STYLE_INPUT, "Продажа предмета", str_c, "Далее", "Назад");
			}
			case DIALOG_SELL_NUMBER_KIOSK:
			{
				if(!response) return 1;

				new kiosk_id = GetNearestKiosk(playerid, 7.0);
				new price = strval(inputtext);
				new str_c[248];

				if(!IsILNumeric(inputtext)) return SCM(playerid, COLOR_RED, "Ошибка ввода. Повторите попытку");
					
				if(!GetILPlayerStr("2000000000", inputtext)) return SendClientMessage(playerid, 0xFF6600FF, "Укажите корректную цену, до 2.000.000.000 руб");

				if(price < GetKioskData(kiosk_id, K_MIN_PRICE)) return SCM(playerid, 0xCECECEFF, "Цена не должна быть менее указаной в диалоге");

				SetPVarInt(playerid, "SellItemPrice", price);

				format(str_c, sizeof str_c, "{FFFFFF}Вы собираетесь продать {006400}'Автомобильный номер'{FFFFFF}.\nВ количестве: {006400}1 {FFFFFF}шт.\nЦена за одну единицу товара: {006400}%d {FFFFFF} руб.", GetPVarInt(playerid, "SellItemPrice"));
				IntfDialogCallRemote(playerid, DIALOG_SELL_NUMBER_ACCEPT, DIALOG_STYLE_MSGBOX, "Продажа автомобильного номера", str_c, "Готово", "Назад");
			}
			case DIALOG_SELL_ACS_KIOSK:
			{
				if(!response) return 1;

				new kiosk_id = GetNearestKiosk(playerid, 7.0);

				new price = strval(inputtext);
				new str_c[248];

				if(!IsILNumeric(inputtext)) return SCM(playerid, COLOR_RED, "Ошибка ввода. Повторите попытку");
					
				if(!GetILPlayerStr("2000000000", inputtext)) return SendClientMessage(playerid, 0xFF6600FF, "Укажите корректную цену, до 2.000.000.000 руб");
							
				if(price < GetKioskData(kiosk_id, K_MIN_PRICE)) return SCM(playerid, 0xCECECEFF, "Цена не должна быть менее указаной в диалоге");

				SetPVarInt(playerid, "SellItemPrice", price);

				format(str_c, sizeof str_c, "{FFFFFF}Вы собираетесь продать {006400}'Аксессуар'{FFFFFF}.\nВ количестве: {006400}1 {FFFFFF}шт.\nЦена за одну единицу товара: {006400}%d {FFFFFF} руб.", GetPVarInt(playerid, "SellItemPrice"));
				IntfDialogCallRemote(playerid, DIALOG_SELL_ACS_ACCEPT, DIALOG_STYLE_MSGBOX, "Продажа аксессуара", str_c, "Готово", "Назад");
			}
			case DIALOG_SELL_SKIN_KIOSK:
			{
				if(!response) return 1;

				new kiosk_id = GetNearestKiosk(playerid, 7.0);
				new price = strval(inputtext);
				new str_c[248];

				if(!IsILNumeric(inputtext)) return SCM(playerid, COLOR_RED, "Ошибка ввода. Повторите попытку");
					
				if(!GetILPlayerStr("2000000000", inputtext)) return SendClientMessage(playerid, 0xFF6600FF, "Укажите корректную цену, до 2.000.000.000 руб");

				if(price < GetKioskData(kiosk_id, K_MIN_PRICE)) return SCM(playerid, 0xCECECEFF, "Цена не должна быть менее указаной в диалоге");

				SetPVarInt(playerid, "SellItemPrice", price);

				format(str_c, sizeof str_c, "{FFFFFF}Вы собираетесь продать {006400}'Одежда'{FFFFFF}.\nВ количестве: {006400}1 {FFFFFF}шт.\nЦена за одну единицу товара: {006400}%d {FFFFFF} руб.", GetPVarInt(playerid, "SellItemPrice"));
				IntfDialogCallRemote(playerid, DIALOG_SELL_SKIN_ACCEPT, DIALOG_STYLE_MSGBOX, "Продажа одежды", str_c, "Готово", "Назад");
			}
			case DIALOG_SELL_ITEM_PRICE:
			{
				if(!response) return 1;

				new kiosk_id = GetNearestKiosk(playerid, 7.0);
				new price = strval(inputtext);
				new str_c[248];
				new count = GetPVarInt(playerid, "SellItemCount");

				if(!IsILNumeric(inputtext)) return SCM(playerid, COLOR_RED, "Ошибка ввода. Повторите попытку");
					
				if(!GetILPlayerStr("2000000000", inputtext)) return SendClientMessage(playerid, 0xFF6600FF, "Укажите корректную цену, до 2.000.000.000 руб");

				if(price < GetKioskData(kiosk_id, K_MIN_PRICE)) return SCM(playerid, 0xCECECEFF, "Цена не должна быть менее указаной в диалоге");

				SetPVarInt(playerid, "SellItemPrice", price);

				format(str_c, sizeof str_c, "{FFFFFF}Вы собираетесь продать {006400}'Предмет'{FFFFFF}.\nВ количестве: {006400}%d {FFFFFF}шт.\nЦена за одну единицу товара: {006400}%d {FFFFFF} руб.", GetPVarInt(playerid, "SellItemCount"), GetPVarInt(playerid, "SellItemPrice"));

				if(!(1 <= count)) return SendClientMessage(playerid, 0xCECECEFF, "Неккоректное значение");

				IntfDialogCallRemote(playerid, DIALOG_SELL_ITEM_ACCEPT, DIALOG_STYLE_MSGBOX, "Продажа предмета", str_c, "Готово", "Назад");
			}
			case DIALOG_BY_EXIT_NIZ:
			{
			    if(!response) return 1;
			    new vehicleid = GetPVarInt(playerid, "veh_id");

				new index = GetVehicleData(vehicleid, V_ACTION_ID);
				GetOwnableCarData(index, OC_POS_X) = GetOwnableCarData(index, OC_BY_POS_X);
				GetOwnableCarData(index, OC_POS_Y) = GetOwnableCarData(index, OC_BY_POS_Y);
				GetOwnableCarData(index, OC_POS_Z) = GetOwnableCarData(index, OC_BY_POS_Z);
				GetOwnableCarData(index, OC_ANGLE) = GetOwnableCarData(index, OC_BY_ANGLE);
				
				SendClientMessage(playerid, 0xFFDAB9FF, "Ваше т/с было снято с продажи");
				SendClientMessage(playerid, 0xFFA500FF, "Ваш транспорт был снят с продажи, припаркован на том месте, где находился до аренды и выгружен");

				if(GetOwnableCarData(index, OC_BY_ID) == 3)
				{
					bymestaniz[GetOwnableCarData(index, OC_MESTOID)] = 0;
				}

				new query[190];

			    format(query, sizeof query, "UPDATE ownable_cars SET inter=0,world=0 WHERE id=%d LIMIT 1",GetOwnableCarData(index, OC_SQL_ID));
			    mysql_tquery(mysql, query, "", "");

				SaveOwnableCar(vehicleid);

				UnloadPlayerOwnableCar(true, vehicleid);
			}
			case DIALOG_KIOSK_MIN_PRICE:
			{
				if(!response) return 1;
				if(strlen(inputtext) < 1 || !IsNumeric(inputtext)) return SendClientMessage(playerid, 0xFF6600FF, "Укажите корректную цену налога");
				if(strlen(inputtext) > 9) return SendClientMessage(playerid, 0xFF6600FF, "Не больше 9-ти символов!");
				new nalog = strval(inputtext);
				if(!(500 <= nalog))
					return SendClientMessage(playerid, 0xCECECEFF, "Минимальная цена с 500 рублей.");
				new kiosk_id = GetNearestKiosk(playerid, 7.0);
				SetKioskData(kiosk_id, K_MIN_PRICE,nalog);
				new fmt_text[144];
				mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE kiosk SET min_price=%d WHERE id=%d", GetKioskData(kiosk_id, K_MIN_PRICE), GetKioskData(kiosk_id, K_SQL_ID));
				mysql_query(mysql, fmt_text, false);
				format(fmt_text, sizeof fmt_text,"Вы установили новую минимальную цену на продажу товара {FFFFFF}%d {FFA500}руб.",nalog);
				SendClientMessage(playerid, 0xFFA500FF, fmt_text);
			}
			case DIALOG_SELL_CAR_ELITE:
			{
				if(!response) return 1;
				if(strlen(inputtext) < 1 || !IsNumeric(inputtext)) return SendClientMessage(playerid, 0xFF6600FF, "Укажите корректную цену продажи");
				if(strlen(inputtext) > 9) return SendClientMessage(playerid, 0xFF6600FF, "Не больше 9-ти символов!");
				new sell_price = strval(inputtext);
				new vehicleid = GetPlayerVehicleID(playerid);

				new vehicleid1 = GetPlayerOwnableCarLast(playerid);

				if(vehicleid1 != GetPlayerVehicleID(playerid)) return SendClientMessage(playerid, 0xFF6600FF, "Вы должны находиться в личном транспорте");
                new index = GetVehicleData(vehicleid, V_ACTION_ID);

                //new model_id = GetVehicleData(vehicleid, V_MODELID);
				//new car_price = GetVehicleInfo(model_id, VI_PRICE);

				if(!(3000 <= sell_price))
					return SendClientMessage(playerid, 0xCECECEFF, "Стоимость должа быть от 3000 рублей");

				GetVehiclePos(vehicleid, GetOwnableCarData(index, OC_BY_POS_X), GetOwnableCarData(index, OC_BY_POS_Y), GetOwnableCarData(index, OC_BY_POS_Z));
				GetVehicleZAngle(vehicleid, GetOwnableCarData(index, OC_BY_ANGLE));


				if(bymestavis[1] == 0) SetVehiclePos(vehicleid, g_load_car_market[1][POS_MESTO_X_2],g_load_car_market[1][POS_MESTO_Y_2],g_load_car_market[1][POS_MESTO_Z_2]),SetVehicleZAngle(vehicleid,g_load_car_market[1][POS_MESTO_ANGEL_2]), SetOwnableCarData(index, OC_MESTOID, 1), bymestavis[1] = 1;
                else if(bymestavis[2] == 0) SetVehiclePos(vehicleid, g_load_car_market[2][POS_MESTO_X_2],g_load_car_market[2][POS_MESTO_Y_2],g_load_car_market[2][POS_MESTO_Z_2]),SetVehicleZAngle(vehicleid,g_load_car_market[2][POS_MESTO_ANGEL_2]), SetOwnableCarData(index, OC_MESTOID, 2), bymestavis[2] = 1;
				else if(bymestavis[3] == 0) SetVehiclePos(vehicleid, g_load_car_market[3][POS_MESTO_X_2],g_load_car_market[3][POS_MESTO_Y_2],g_load_car_market[3][POS_MESTO_Z_2]),SetVehicleZAngle(vehicleid,g_load_car_market[3][POS_MESTO_ANGEL_2]), SetOwnableCarData(index, OC_MESTOID, 3), bymestavis[3] = 1;
				else if(bymestavis[4] == 0) SetVehiclePos(vehicleid, g_load_car_market[4][POS_MESTO_X_2],g_load_car_market[4][POS_MESTO_Y_2],g_load_car_market[4][POS_MESTO_Z_2]),SetVehicleZAngle(vehicleid,g_load_car_market[4][POS_MESTO_ANGEL_2]), SetOwnableCarData(index, OC_MESTOID, 4), bymestavis[4] = 1;
				else if(bymestavis[5] == 0) SetVehiclePos(vehicleid, g_load_car_market[5][POS_MESTO_X_2],g_load_car_market[5][POS_MESTO_Y_2],g_load_car_market[5][POS_MESTO_Z_2]),SetVehicleZAngle(vehicleid,g_load_car_market[5][POS_MESTO_ANGEL_2]), SetOwnableCarData(index, OC_MESTOID, 5), bymestavis[5] = 1;
				else if(bymestavis[6] == 0) SetVehiclePos(vehicleid, g_load_car_market[6][POS_MESTO_X_2],g_load_car_market[6][POS_MESTO_Y_2],g_load_car_market[6][POS_MESTO_Z_2]),SetVehicleZAngle(vehicleid,g_load_car_market[6][POS_MESTO_ANGEL_2]), SetOwnableCarData(index, OC_MESTOID, 6), bymestavis[6] = 1;
				else if(bymestavis[7] == 0) SetVehiclePos(vehicleid, g_load_car_market[7][POS_MESTO_X_2],g_load_car_market[7][POS_MESTO_Y_2],g_load_car_market[7][POS_MESTO_Z_2]),SetVehicleZAngle(vehicleid,g_load_car_market[7][POS_MESTO_ANGEL_2]), SetOwnableCarData(index, OC_MESTOID, 7), bymestavis[7] = 1;
				else if(bymestavis[8] == 0) SetVehiclePos(vehicleid, g_load_car_market[8][POS_MESTO_X_2],g_load_car_market[8][POS_MESTO_Y_2],g_load_car_market[8][POS_MESTO_Z_2]),SetVehicleZAngle(vehicleid,g_load_car_market[8][POS_MESTO_ANGEL_2]), SetOwnableCarData(index, OC_MESTOID, 8), bymestavis[8] = 1;
				else if(bymestavis[9] == 0) SetVehiclePos(vehicleid, g_load_car_market[9][POS_MESTO_X_2],g_load_car_market[9][POS_MESTO_Y_2],g_load_car_market[9][POS_MESTO_Z_2]),SetVehicleZAngle(vehicleid,g_load_car_market[9][POS_MESTO_ANGEL_2]), SetOwnableCarData(index, OC_MESTOID, 9), bymestavis[9] = 1;
				else if(bymestavis[10] == 0) SetVehiclePos(vehicleid, g_load_car_market[10][POS_MESTO_X_2],g_load_car_market[10][POS_MESTO_Y_2],g_load_car_market[10][POS_MESTO_Z_2]),SetVehicleZAngle(vehicleid,g_load_car_market[10][POS_MESTO_ANGEL_2]), SetOwnableCarData(index, OC_MESTOID, 10), bymestavis[10] = 1;
				else if(bymestavis[11] == 0) SetVehiclePos(vehicleid, g_load_car_market[11][POS_MESTO_X_2],g_load_car_market[11][POS_MESTO_Y_2],g_load_car_market[11][POS_MESTO_Z_2]),SetVehicleZAngle(vehicleid,g_load_car_market[11][POS_MESTO_ANGEL_2]), SetOwnableCarData(index, OC_MESTOID, 11), bymestavis[11] = 1;
				else if(bymestavis[12] == 0) SetVehiclePos(vehicleid, g_load_car_market[12][POS_MESTO_X_2],g_load_car_market[12][POS_MESTO_Y_2],g_load_car_market[12][POS_MESTO_Z_2]),SetVehicleZAngle(vehicleid,g_load_car_market[12][POS_MESTO_ANGEL_2]), SetOwnableCarData(index, OC_MESTOID, 12), bymestavis[12] = 1;
				else if(bymestavis[13] == 0) SetVehiclePos(vehicleid, g_load_car_market[13][POS_MESTO_X_2],g_load_car_market[13][POS_MESTO_Y_2],g_load_car_market[13][POS_MESTO_Z_2]),SetVehicleZAngle(vehicleid,g_load_car_market[13][POS_MESTO_ANGEL_2]), SetOwnableCarData(index, OC_MESTOID, 13), bymestavis[13] = 1;
				else if(bymestavis[14] == 0) SetVehiclePos(vehicleid, g_load_car_market[14][POS_MESTO_X_2],g_load_car_market[14][POS_MESTO_Y_2],g_load_car_market[14][POS_MESTO_Z_2]),SetVehicleZAngle(vehicleid,g_load_car_market[14][POS_MESTO_ANGEL_2]), SetOwnableCarData(index, OC_MESTOID, 14), bymestavis[14] = 1;
				else if(bymestavis[15] == 0) SetVehiclePos(vehicleid, g_load_car_market[15][POS_MESTO_X_2],g_load_car_market[15][POS_MESTO_Y_2],g_load_car_market[15][POS_MESTO_Z_2]),SetVehicleZAngle(vehicleid,g_load_car_market[15][POS_MESTO_ANGEL_2]), SetOwnableCarData(index, OC_MESTOID, 15), bymestavis[15] = 1;
				else if(bymestavis[16] == 0) SetVehiclePos(vehicleid, g_load_car_market[16][POS_MESTO_X_2],g_load_car_market[16][POS_MESTO_Y_2],g_load_car_market[16][POS_MESTO_Z_2]),SetVehicleZAngle(vehicleid,g_load_car_market[16][POS_MESTO_ANGEL_2]), SetOwnableCarData(index, OC_MESTOID, 16), bymestavis[16] = 1;
				else if(bymestavis[17] == 0) SetVehiclePos(vehicleid, g_load_car_market[17][POS_MESTO_X_2],g_load_car_market[17][POS_MESTO_Y_2],g_load_car_market[17][POS_MESTO_Z_2]),SetVehicleZAngle(vehicleid,g_load_car_market[17][POS_MESTO_ANGEL_2]), SetOwnableCarData(index, OC_MESTOID, 17), bymestavis[17] = 1;
				else if(bymestavis[18] == 0) SetVehiclePos(vehicleid, g_load_car_market[18][POS_MESTO_X_2],g_load_car_market[18][POS_MESTO_Y_2],g_load_car_market[18][POS_MESTO_Z_2]),SetVehicleZAngle(vehicleid,g_load_car_market[18][POS_MESTO_ANGEL_2]), SetOwnableCarData(index, OC_MESTOID, 18), bymestavis[18] = 1;
				else if(bymestavis[19] == 0) SetVehiclePos(vehicleid, g_load_car_market[19][POS_MESTO_X_2],g_load_car_market[19][POS_MESTO_Y_2],g_load_car_market[19][POS_MESTO_Z_2]),SetVehicleZAngle(vehicleid,g_load_car_market[19][POS_MESTO_ANGEL_2]), SetOwnableCarData(index, OC_MESTOID, 19), bymestavis[19] = 1;
				else if(bymestavis[20] == 0) SetVehiclePos(vehicleid, g_load_car_market[20][POS_MESTO_X_2],g_load_car_market[20][POS_MESTO_Y_2],g_load_car_market[20][POS_MESTO_Z_2]),SetVehicleZAngle(vehicleid,g_load_car_market[20][POS_MESTO_ANGEL_2]), SetOwnableCarData(index, OC_MESTOID, 20), bymestavis[20] = 1;
				else return SendClientMessage(playerid, -1, "Все места на бу рынке заняты.");

				new str[300];
				new phone_number[15];

				valstr(phone_number, GetPlayerPhone(playerid));

				format(str, sizeof str,
				"{FFA500}Модель:{FFFFFF} %s\n"\
				"{FFA500}Продавец:{FFFFFF} %s\n"\
				"{FFA500}Цена:{FFFFFF} %s {FFA500}руб\n"\
				"{FFA500}Телефон:{FFFFFF} %s",
				GetVehicleName(vehicleid), GetPlayerNameEx(playerid), formatInt(strval(inputtext)), GetPlayerPhone(playerid) == 0 ? "Нет" : phone_number);

				CreateVehicleLabel(vehicleid, str, 0xFFFFFFFF, 0.0, 0.0, 1.0, 8);

				SendClientMessage(playerid, 0xFFA500FF, "Вы арендовали место на парковке на 60 минут. Сядьте в т/с, если хотите снять его с продажи.");
				SendClientMessage(playerid, 0xFFA500FF, "Внимание! Если вы покинете авторынок более чем на 3 минут(ы) весь ваш транспорт будет снят с продажи.");
				SendClientMessage(playerid, 0xFFA500FF, "Для смены цены продажи транспорта встаньте возле него и используйте {"#cW"}/cm_price.");
				SendClientMessage(playerid, 0xFFA500FF, "Так же можете предложить тест-драйв другому игроку {"#cW"}/cm_test_drive.");

				SetPlayerInBiz(playerid, GetPVarInt(playerid, "by_id"));

				SetVehicleParam(vehicleid, V_ENGINE, false);

				SetPlayerInterior(playerid, 4);
				LinkVehicleToInterior(vehicleid, 4);

				SetPlayerVirtualWorld(playerid, 263);
				SetVehicleVirtualWorld(vehicleid, 263);

				SetPVarInt(playerid, "in_by", 1);
				SetOwnableCarData(index, OC_BY_ID, 1);

				new businessid = GetPVarInt(playerid, "by_id");

				ModifyCashBalance(playerid, -GetBusinessData(businessid, B_ARENDA_PRICE), "место на б/у рынке", true, true);

				AddBusinessProfit(playerid, businessid, GetBusinessData(businessid, B_ARENDA_PRICE), 0);
				return 1;
			}
			case DIALOG_SELL_CAR_NIZ:
			{
				if(!response) return 1;
				if(strlen(inputtext) < 1 || !IsNumeric(inputtext)) return SendClientMessage(playerid, 0xFF6600FF, "Укажите корректную цену продажи");
				if(strlen(inputtext) > 9) return SendClientMessage(playerid, 0xFF6600FF, "Не больше 9-ти символов!");
				new sell_price = strval(inputtext);
				new vehicleid = GetPlayerVehicleID(playerid);

				new vehicleid1 = GetPlayerOwnableCarLast(playerid);

				if(vehicleid1 != GetPlayerVehicleID(playerid)) return SendClientMessage(playerid, 0xFF6600FF, "Вы должны находиться в личном транспорте");
                new index = GetVehicleData(vehicleid, V_ACTION_ID);

				if(!(3000 <= sell_price))
					return SendClientMessage(playerid, 0xCECECEFF, "Стоимость должа быть от 3000 рублей");

				GetVehiclePos(vehicleid, GetOwnableCarData(index, OC_BY_POS_X), GetOwnableCarData(index, OC_BY_POS_Y), GetOwnableCarData(index, OC_BY_POS_Z));
				GetVehicleZAngle(vehicleid, GetOwnableCarData(index, OC_BY_ANGLE));

				if(bymestaniz[1] == 0) SetVehiclePos(vehicleid, g_load_car_market[1][POS_MESTO_X_3],g_load_car_market[1][POS_MESTO_Y_3],g_load_car_market[1][POS_MESTO_Z_3]),SetVehicleZAngle(vehicleid,g_load_car_market[1][POS_MESTO_ANGEL_1]), SetOwnableCarData(index, OC_MESTOID, 1), bymestaniz[1] = 1;
                else if(bymestaniz[2] == 0) SetVehiclePos(vehicleid, g_load_car_market[2][POS_MESTO_X_3],g_load_car_market[2][POS_MESTO_Y_3],g_load_car_market[2][POS_MESTO_Z_3]),SetVehicleZAngle(vehicleid,g_load_car_market[2][POS_MESTO_ANGEL_3]), SetOwnableCarData(index, OC_MESTOID, 2), bymestaniz[2] = 1;
				else if(bymestaniz[3] == 0) SetVehiclePos(vehicleid, g_load_car_market[3][POS_MESTO_X_3],g_load_car_market[3][POS_MESTO_Y_3],g_load_car_market[3][POS_MESTO_Z_3]),SetVehicleZAngle(vehicleid,g_load_car_market[3][POS_MESTO_ANGEL_3]), SetOwnableCarData(index, OC_MESTOID, 3), bymestaniz[3] = 1;
				else if(bymestaniz[4] == 0) SetVehiclePos(vehicleid, g_load_car_market[4][POS_MESTO_X_3],g_load_car_market[4][POS_MESTO_Y_3],g_load_car_market[4][POS_MESTO_Z_3]),SetVehicleZAngle(vehicleid,g_load_car_market[4][POS_MESTO_ANGEL_3]), SetOwnableCarData(index, OC_MESTOID, 4), bymestaniz[4] = 1;
				else if(bymestaniz[5] == 0) SetVehiclePos(vehicleid, g_load_car_market[5][POS_MESTO_X_3],g_load_car_market[5][POS_MESTO_Y_3],g_load_car_market[5][POS_MESTO_Z_3]),SetVehicleZAngle(vehicleid,g_load_car_market[5][POS_MESTO_ANGEL_3]), SetOwnableCarData(index, OC_MESTOID, 5), bymestaniz[5] = 1;
				else if(bymestaniz[6] == 0) SetVehiclePos(vehicleid, g_load_car_market[6][POS_MESTO_X_3],g_load_car_market[6][POS_MESTO_Y_3],g_load_car_market[6][POS_MESTO_Z_3]),SetVehicleZAngle(vehicleid,g_load_car_market[6][POS_MESTO_ANGEL_3]), SetOwnableCarData(index, OC_MESTOID, 6), bymestaniz[6] = 1;
				else if(bymestaniz[7] == 0) SetVehiclePos(vehicleid, g_load_car_market[7][POS_MESTO_X_3],g_load_car_market[7][POS_MESTO_Y_3],g_load_car_market[7][POS_MESTO_Z_3]),SetVehicleZAngle(vehicleid,g_load_car_market[7][POS_MESTO_ANGEL_3]), SetOwnableCarData(index, OC_MESTOID, 7), bymestaniz[7] = 1;
				else if(bymestaniz[8] == 0) SetVehiclePos(vehicleid, g_load_car_market[8][POS_MESTO_X_3],g_load_car_market[8][POS_MESTO_Y_3],g_load_car_market[8][POS_MESTO_Z_3]),SetVehicleZAngle(vehicleid,g_load_car_market[8][POS_MESTO_ANGEL_3]), SetOwnableCarData(index, OC_MESTOID, 8), bymestaniz[8] = 1;
				else if(bymestaniz[9] == 0) SetVehiclePos(vehicleid, g_load_car_market[9][POS_MESTO_X_3],g_load_car_market[9][POS_MESTO_Y_3],g_load_car_market[9][POS_MESTO_Z_3]),SetVehicleZAngle(vehicleid,g_load_car_market[9][POS_MESTO_ANGEL_3]), SetOwnableCarData(index, OC_MESTOID, 9), bymestaniz[9] = 1;
				else if(bymestaniz[10] == 0) SetVehiclePos(vehicleid, g_load_car_market[10][POS_MESTO_X_3],g_load_car_market[10][POS_MESTO_Y_3],g_load_car_market[10][POS_MESTO_Z_3]),SetVehicleZAngle(vehicleid,g_load_car_market[10][POS_MESTO_ANGEL_3]), SetOwnableCarData(index, OC_MESTOID, 10), bymestaniz[10] = 1;
				else if(bymestaniz[11] == 0) SetVehiclePos(vehicleid, g_load_car_market[11][POS_MESTO_X_3],g_load_car_market[11][POS_MESTO_Y_3],g_load_car_market[11][POS_MESTO_Z_3]),SetVehicleZAngle(vehicleid,g_load_car_market[11][POS_MESTO_ANGEL_3]), SetOwnableCarData(index, OC_MESTOID, 11), bymestaniz[11] = 1;
				else if(bymestaniz[12] == 0) SetVehiclePos(vehicleid, g_load_car_market[12][POS_MESTO_X_3],g_load_car_market[12][POS_MESTO_Y_3],g_load_car_market[12][POS_MESTO_Z_3]),SetVehicleZAngle(vehicleid,g_load_car_market[12][POS_MESTO_ANGEL_3]), SetOwnableCarData(index, OC_MESTOID, 12), bymestaniz[12] = 1;
				else if(bymestaniz[13] == 0) SetVehiclePos(vehicleid, g_load_car_market[13][POS_MESTO_X_3],g_load_car_market[13][POS_MESTO_Y_3],g_load_car_market[13][POS_MESTO_Z_3]),SetVehicleZAngle(vehicleid,g_load_car_market[13][POS_MESTO_ANGEL_3]), SetOwnableCarData(index, OC_MESTOID, 13), bymestaniz[13] = 1;
				else return SendClientMessage(playerid, -1, "Все места на бу рынке заняты.");

				new str[300];
				new phone_number[15];

				valstr(phone_number, GetPlayerPhone(playerid));

				format(str, sizeof str,
				"{FFA500}Модель:{FFFFFF} %s\n"\
				"{FFA500}Продавец:{FFFFFF} %s\n"\
				"{FFA500}Цена:{FFFFFF} %s {FFA500}руб\n"\
				"{FFA500}Телефон:{FFFFFF} %s",
				GetVehicleName(vehicleid), GetPlayerNameEx(playerid), formatInt(strval(inputtext)), GetPlayerPhone(playerid) == 0 ? "Нет" : phone_number);

				CreateVehicleLabel(vehicleid, str, 0xFFFFFFFF, 0.0, 0.0, 1.0, 8);

				SendClientMessage(playerid, 0xFFA500FF, "Вы арендовали место на парковке на 60 минут. Сядьте в т/с, если хотите снять его с продажи.");
				SendClientMessage(playerid, 0xFFA500FF, "Внимание! Если вы покинете авторынок более чем на 3 минут(ы) весь ваш транспорт будет снят с продажи.");
				SendClientMessage(playerid, 0xFFA500FF, "Для смены цены продажи транспорта встаньте возле него и используйте {"#cW"}/cm_price.");
				SendClientMessage(playerid, 0xFFA500FF, "Так же можете предложить тест-драйв другому игроку {"#cW"}/cm_test_drive.");

				SetPlayerInBiz(playerid, GetPVarInt(playerid, "by_id"));

				SetVehicleParam(vehicleid, V_ENGINE, false);

				SetPlayerInterior(playerid, 4);
				LinkVehicleToInterior(vehicleid, 4);

				SetPlayerVirtualWorld(playerid, 261);
				SetVehicleVirtualWorld(vehicleid, 261);

				SetPVarInt(playerid, "in_by", 1);
				SetOwnableCarData(index, OC_BY_ID, 3);

				new businessid = GetPVarInt(playerid, "by_id");

				ModifyCashBalance(playerid, -GetBusinessData(businessid, B_ARENDA_PRICE), "место на б/у рынке", true, true);

				AddBusinessProfit(playerid, businessid, GetBusinessData(businessid, B_ARENDA_PRICE), 0);
				return 1;
			}
			case DIALOG_SELL_CAR_SR:
			{
				if(!response) return 1;
				if(strlen(inputtext) < 1 || !IsNumeric(inputtext)) return SendClientMessage(playerid, 0xFF6600FF, "Укажите корректную цену продажи");
				if(strlen(inputtext) > 9) return SendClientMessage(playerid, 0xFF6600FF, "Не больше 9-ти символов!");
				new sell_price = strval(inputtext);
				new vehicleid = GetPlayerVehicleID(playerid);

				new vehicleid1 = GetPlayerOwnableCarLast(playerid);

				if(vehicleid1 != GetPlayerVehicleID(playerid)) return SendClientMessage(playerid, 0xFF6600FF, "Вы должны находиться в личном транспорте");
                new index = GetVehicleData(vehicleid, V_ACTION_ID);

				if(!(3000 <= sell_price))
					return SendClientMessage(playerid, 0xCECECEFF, "Стоимость должа быть от 3000 рублей");

				GetVehiclePos(vehicleid, GetOwnableCarData(index, OC_BY_POS_X), GetOwnableCarData(index, OC_BY_POS_Y), GetOwnableCarData(index, OC_BY_POS_Z));
				GetVehicleZAngle(vehicleid, GetOwnableCarData(index, OC_BY_ANGLE));
					
					
                if(bymestasr[1] == 0) SetVehiclePosAc(vehicleid, g_load_car_market[1][POS_MESTO_X_1],g_load_car_market[1][POS_MESTO_Y_1],g_load_car_market[1][POS_MESTO_Z_1],g_load_car_market[1][POS_MESTO_ANGEL_1]), SetOwnableCarData(index, OC_MESTOID, 1), bymestasr[1] = 1;
                else if(bymestasr[2] == 0) SetVehiclePosAc(vehicleid, g_load_car_market[2][POS_MESTO_X_1],g_load_car_market[2][POS_MESTO_Y_1],g_load_car_market[2][POS_MESTO_Z_1],g_load_car_market[2][POS_MESTO_ANGEL_1]), SetOwnableCarData(index, OC_MESTOID, 2), bymestasr[2] = 1;
				else if(bymestasr[3] == 0) SetVehiclePosAc(vehicleid, g_load_car_market[3][POS_MESTO_X_1],g_load_car_market[3][POS_MESTO_Y_1],g_load_car_market[3][POS_MESTO_Z_1],g_load_car_market[3][POS_MESTO_ANGEL_1]), SetOwnableCarData(index, OC_MESTOID, 3), bymestasr[3] = 1;
				else if(bymestasr[4] == 0) SetVehiclePosAc(vehicleid, g_load_car_market[4][POS_MESTO_X_1],g_load_car_market[4][POS_MESTO_Y_1],g_load_car_market[4][POS_MESTO_Z_1],g_load_car_market[4][POS_MESTO_ANGEL_1]), SetOwnableCarData(index, OC_MESTOID, 4), bymestasr[4] = 1;
				else if(bymestasr[5] == 0) SetVehiclePosAc(vehicleid, g_load_car_market[5][POS_MESTO_X_1],g_load_car_market[5][POS_MESTO_Y_1],g_load_car_market[5][POS_MESTO_Z_1],g_load_car_market[5][POS_MESTO_ANGEL_1]), SetOwnableCarData(index, OC_MESTOID, 5), bymestasr[5] = 1;
				else if(bymestasr[6] == 0) SetVehiclePosAc(vehicleid, g_load_car_market[6][POS_MESTO_X_1],g_load_car_market[6][POS_MESTO_Y_1],g_load_car_market[6][POS_MESTO_Z_1],g_load_car_market[6][POS_MESTO_ANGEL_1]), SetOwnableCarData(index, OC_MESTOID, 6), bymestasr[6] = 1;
				else if(bymestasr[7] == 0) SetVehiclePosAc(vehicleid, g_load_car_market[7][POS_MESTO_X_1],g_load_car_market[7][POS_MESTO_Y_1],g_load_car_market[7][POS_MESTO_Z_1],g_load_car_market[7][POS_MESTO_ANGEL_1]), SetOwnableCarData(index, OC_MESTOID, 7), bymestasr[7] = 1;
				else if(bymestasr[8] == 0) SetVehiclePosAc(vehicleid, g_load_car_market[8][POS_MESTO_X_1],g_load_car_market[8][POS_MESTO_Y_1],g_load_car_market[8][POS_MESTO_Z_1],g_load_car_market[8][POS_MESTO_ANGEL_1]), SetOwnableCarData(index, OC_MESTOID, 8), bymestasr[8] = 1;
				else if(bymestasr[9] == 0) SetVehiclePosAc(vehicleid, g_load_car_market[9][POS_MESTO_X_1],g_load_car_market[9][POS_MESTO_Y_1],g_load_car_market[9][POS_MESTO_Z_1],g_load_car_market[9][POS_MESTO_ANGEL_1]), SetOwnableCarData(index, OC_MESTOID, 9), bymestasr[9] = 1;
				else if(bymestasr[10] == 0) SetVehiclePosAc(vehicleid, g_load_car_market[10][POS_MESTO_X_1],g_load_car_market[10][POS_MESTO_Y_1],g_load_car_market[10][POS_MESTO_Z_1],g_load_car_market[10][POS_MESTO_ANGEL_1]), SetOwnableCarData(index, OC_MESTOID, 10), bymestasr[10] = 1;
				else if(bymestasr[11] == 0) SetVehiclePosAc(vehicleid, g_load_car_market[11][POS_MESTO_X_1],g_load_car_market[11][POS_MESTO_Y_1],g_load_car_market[11][POS_MESTO_Z_1],g_load_car_market[11][POS_MESTO_ANGEL_1]), SetOwnableCarData(index, OC_MESTOID, 11), bymestasr[11] = 1;
				else if(bymestasr[12] == 0) SetVehiclePosAc(vehicleid, g_load_car_market[12][POS_MESTO_X_1],g_load_car_market[12][POS_MESTO_Y_1],g_load_car_market[12][POS_MESTO_Z_1],g_load_car_market[12][POS_MESTO_ANGEL_1]), SetOwnableCarData(index, OC_MESTOID, 12), bymestasr[12] = 1;
				else if(bymestasr[13] == 0) SetVehiclePosAc(vehicleid, g_load_car_market[13][POS_MESTO_X_1],g_load_car_market[13][POS_MESTO_Y_1],g_load_car_market[13][POS_MESTO_Z_1],g_load_car_market[13][POS_MESTO_ANGEL_1]), SetOwnableCarData(index, OC_MESTOID, 13), bymestasr[13] = 1;
				else if(bymestasr[14] == 0) SetVehiclePosAc(vehicleid, g_load_car_market[14][POS_MESTO_X_1],g_load_car_market[14][POS_MESTO_Y_1],g_load_car_market[14][POS_MESTO_Z_1],g_load_car_market[14][POS_MESTO_ANGEL_1]), SetOwnableCarData(index, OC_MESTOID, 14), bymestasr[14] = 1;
				else if(bymestasr[15] == 0) SetVehiclePosAc(vehicleid, g_load_car_market[15][POS_MESTO_X_1],g_load_car_market[15][POS_MESTO_Y_1],g_load_car_market[15][POS_MESTO_Z_1],g_load_car_market[15][POS_MESTO_ANGEL_1]), SetOwnableCarData(index, OC_MESTOID, 15), bymestasr[15] = 1;
				else if(bymestasr[16] == 0) SetVehiclePosAc(vehicleid, g_load_car_market[16][POS_MESTO_X_1],g_load_car_market[16][POS_MESTO_Y_1],g_load_car_market[16][POS_MESTO_Z_1],g_load_car_market[16][POS_MESTO_ANGEL_1]), SetOwnableCarData(index, OC_MESTOID, 16), bymestasr[16] = 1;
				else if(bymestasr[17] == 0) SetVehiclePosAc(vehicleid, g_load_car_market[17][POS_MESTO_X_1],g_load_car_market[17][POS_MESTO_Y_1],g_load_car_market[17][POS_MESTO_Z_1],g_load_car_market[17][POS_MESTO_ANGEL_1]), SetOwnableCarData(index, OC_MESTOID, 17), bymestasr[17] = 1;
				else if(bymestasr[18] == 0) SetVehiclePosAc(vehicleid, g_load_car_market[18][POS_MESTO_X_1],g_load_car_market[18][POS_MESTO_Y_1],g_load_car_market[18][POS_MESTO_Z_1],g_load_car_market[18][POS_MESTO_ANGEL_1]), SetOwnableCarData(index, OC_MESTOID, 18), bymestasr[18] = 1;
				else if(bymestasr[19] == 0) SetVehiclePosAc(vehicleid, g_load_car_market[19][POS_MESTO_X_1],g_load_car_market[19][POS_MESTO_Y_1],g_load_car_market[19][POS_MESTO_Z_1],g_load_car_market[19][POS_MESTO_ANGEL_1]), SetOwnableCarData(index, OC_MESTOID, 19), bymestasr[19] = 1;
				else if(bymestasr[20] == 0) SetVehiclePosAc(vehicleid, g_load_car_market[20][POS_MESTO_X_1],g_load_car_market[20][POS_MESTO_Y_1],g_load_car_market[20][POS_MESTO_Z_1],g_load_car_market[20][POS_MESTO_ANGEL_1]), SetOwnableCarData(index, OC_MESTOID, 20), bymestasr[20] = 1;
				else if(bymestasr[21] == 0) SetVehiclePosAc(vehicleid, g_load_car_market[21][POS_MESTO_X_1],g_load_car_market[21][POS_MESTO_Y_1],g_load_car_market[21][POS_MESTO_Z_1],g_load_car_market[21][POS_MESTO_ANGEL_1]), SetOwnableCarData(index, OC_MESTOID, 21), bymestasr[21] = 1;
				else return SendClientMessage(playerid, -1, "Все места на бу рынке заняты.");

				new str[300];
				new phone_number[15];

				valstr(phone_number, GetPlayerPhone(playerid));

				format(str, sizeof str,
				"{FFA500}Модель:{FFFFFF} %s\n"\
				"{FFA500}Продавец:{FFFFFF} %s\n"\
				"{FFA500}Цена:{FFFFFF} %s {FFA500}руб\n"\
				"{FFA500}Телефон:{FFFFFF} %s",
				GetVehicleName(vehicleid), GetPlayerNameEx(playerid), formatInt(strval(inputtext)), GetPlayerPhone(playerid) == 0 ? "Нет" : phone_number);

				CreateVehicleLabel(vehicleid, str, 0xFFFFFFFF, 0.0, 0.0, 1.0, 8);

				SendClientMessage(playerid, 0xFFA500FF, "Вы арендовали место на парковке на 60 минут. Сядьте в т/с, если хотите снять его с продажи.");
				SendClientMessage(playerid, 0xFFA500FF, "Внимание! Если вы покинете авторынок более чем на 3 минут(ы) весь ваш транспорт будет снят с продажи.");
				SendClientMessage(playerid, 0xFFA500FF, "Для смены цены продажи транспорта встаньте возле него и используйте {"#cW"}/cm_price.");
				SendClientMessage(playerid, 0xFFA500FF, "Так же можете предложить тест-драйв другому игроку {"#cW"}/cm_test_drive.");

				SetPlayerInBiz(playerid, GetPVarInt(playerid, "by_id"));

				SetVehicleParam(vehicleid, V_ENGINE, false);

				SetPlayerInterior(playerid, 4);
				LinkVehicleToInterior(vehicleid, 4);

				SetPlayerVirtualWorld(playerid, 262);
				SetVehicleVirtualWorld(vehicleid, 262);

				SetPVarInt(playerid, "in_by", 1);
				SetOwnableCarData(index, OC_BY_ID, 2);

				new businessid = GetPVarInt(playerid, "by_id");

				ModifyCashBalance(playerid, -GetBusinessData(businessid, B_ARENDA_PRICE), "место на б/у рынке", true, true);
				AddBusinessProfit(playerid, businessid, GetBusinessData(businessid, B_ARENDA_PRICE), 0);
				return 1;
			}
			case DIALOG_KIOSK_NALOG:
			{
				if(!response) return 1;
				if(strlen(inputtext) < 1 || !IsNumeric(inputtext)) return SendClientMessage(playerid, 0xFF6600FF, "Укажите корректную цену налога");
				if(strlen(inputtext) > 9) return SendClientMessage(playerid, 0xFF6600FF, "Не больше 9-ти символов!");
				new nalog = strval(inputtext);
				if(!(1 <= nalog <= 25))
					return SendClientMessage(playerid, 0xCECECEFF, "Процент налога должен быть от 1 до 25.");
				new kiosk_id = GetNearestKiosk(playerid, 7.0);
				SetKioskData(kiosk_id, K_NALOG,nalog);
				new fmt_text[144];
				mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE kiosk SET nalog=%d WHERE id=%d", GetKioskData(kiosk_id, K_NALOG), GetKioskData(kiosk_id, K_SQL_ID));
				mysql_query(mysql, fmt_text, false);
				format(fmt_text, sizeof fmt_text,"Вы установили новый налог на продажу товара {FFFFFF}%d {FFA500}процента(ов).",nalog);
				SendClientMessage(playerid, 0xFFA500FF, fmt_text);
				UpdKioskss(playerid);
			}
			case DIALOG_ATM_BIZ_TAKE_MONEY:
			{
				new businessid = GetPVarInt(playerid, "ownablebiz_id");
				if(businessid != -1)
				{
					if(response)
					{
						new sum = strval(inputtext);

						if(!GetILPlayerStr("2000000000", inputtext)) return SCM(playerid, COLOR_GREY, "С счета предприятия можно снять до 2.000.000.000 руб за раз");

						if(IsILNumeric(inputtext))
						{
							if(VerifyIntString(GetBusinessData(businessid, B_BALANCE), sum))
							{
								new query[128 + 1];

								format(query, sizeof query, "UPDATE accounts_canvasdev a, business b SET a.money=%s,b.balance=%s WHERE a.id=%d AND b.id=%d", SetILPlayerInt(playerid, QueryPlayerBalance(playerid), sum), SetILPlayerInt(playerid, g_business[businessid][B_BALANCE], -sum), GetPlayerAccountID(playerid), GetBusinessData(businessid, B_SQL_ID));
								mysql_query(mysql, query, false);

								if(!mysql_errno())
								{
									format(g_business[businessid][B_BALANCE], 21, "%s", SetILPlayerInt(playerid, g_business[businessid][B_BALANCE], -sum));
									
									ModifyCashBalance(playerid, sum, "+ Снятие средств со счета Бизнеса", false, true);

									ApplyAnimation(playerid, "CRIB", "CRIB_Use_Switch", 4.0, 0, 0, 0, 0, 0, 0);
									ShowPlayerATMDialog(playerid);

									return 1;
								}
								else SendClientMessage(playerid, 0xFF6600FF, "Ошибка сохранения, повторите попытку {FF0000}(equ-code 18)");
							}
							else SendClientMessage(playerid, 0xCECECEFF, "На счету предприятия нет такой суммы");
						}
						else SendClientMessage(playerid, 0xFF6600FF, "Ошибка ввода, повторите попытку");
					}
					else
					{
						ShowPlayerATMDialog(playerid);
						ApplyAnimation(playerid, "CRIB", "CRIB_Use_Switch", 4.0, 0, 0, 0, 0, 0, 0);
					}
				}
			}
			case DIALOG_ATM_KIOSK_TAKE_MONEY:
			{
				new kiosksid = GetPVarInt(playerid, "ownablekiosk_id");
				if(kiosksid != -1)
				{
					if(response)
					{
						if(IsILNumeric(inputtext))
						{
							if(GetILPlayerStr(GetKioskData(kiosksid, K_BALANCE), inputtext))
							{
								new query[128 + 1];

								format(query, sizeof query, "-%s", inputtext);

								format(query, sizeof query, "UPDATE kiosk SET balance=%s WHERE id=%d", 
								SetILPlayerStr(playerid, g_kiosk[kiosksid][K_BALANCE], query), GetKioskData(kiosksid, K_SQL_ID));
								mysql_query(mysql, query, false);

								if(!mysql_errno())
								{
									format(query, sizeof query, "-%s", inputtext);
									format(g_kiosk[kiosksid][K_BALANCE], 21, "%s", SetILPlayerStr(playerid, g_kiosk[kiosksid][K_BALANCE], query));

									GivePlayerMoneyStr(playerid, inputtext, "+ Снятие средств со счета киоска");

									ApplyAnimation(playerid, "CRIB", "CRIB_Use_Switch", 4.0, 0, 0, 0, 0, 0, 0);
									ShowPlayerATMDialog(playerid);

									return 1;
								}
								else SendClientMessage(playerid, 0xFF6600FF, "Ошибка сохранения, повторите попытку {FF0000}(equ-code 18)");
							}
							else SendClientMessage(playerid, 0xCECECEFF, "На счету киоска нет такой суммы");
						}
						else SendClientMessage(playerid, 0xFF6600FF, "Ошибка ввода, повторите попытку");
					}
					else
					{
						ShowPlayerATMDialog(playerid);
						ApplyAnimation(playerid, "CRIB", "CRIB_Use_Switch", 4.0, 0, 0, 0, 0, 0, 0);
					}
				}
			}
			case DIALOG_ATM_NEFTENASOS_PUT_MONEY:
			{
				new neftid = GetPVarInt(playerid, "ownableneft_id");
				if(neftid == -1) return 1;
				if(!response) return ShowPlayerATMDialog(playerid);
				new sum = strval(inputtext);
				if(sum > 0 && IsNumeric(inputtext))
				{
					if(GetNeftData(neftid, N_BALANCE) >= sum)
					{
						new query[128 + 1];

						format(query, sizeof query, "UPDATE accounts_canvasdev a, neftenasos b SET a.money=%s,b.balance=%d WHERE a.id=%d AND b.id=%d", SetILPlayerInt(playerid, QueryPlayerBalance(playerid), sum), GetNeftData(neftid, N_BALANCE)-sum, GetPlayerAccountID(playerid), GetNeftData(neftid, N_SQL_ID));
						mysql_query(mysql, query, false);

						if(!mysql_errno())
						{
							AddNeftData(neftid, N_BALANCE, -, sum);
							ModifyCashBalance(playerid, sum, "+ Снятие средств со счета нефтенасоса", false, true);

							ApplyAnimation(playerid, "CRIB", "CRIB_Use_Switch", 4.0, 0, 0, 0, 0, 0, 0);
							ShowPlayerATMDialog(playerid);

							return 1;
						}
						else SendClientMessage(playerid, 0xFF6600FF, "Ошибка сохранения, повторите попытку {FF0000}(equ-code 18)");
					}
					else SendClientMessage(playerid, 0xCECECEFF, "На счету нефтенасоса нет такой суммы");
				}
				else SendClientMessage(playerid, 0xFF6600FF, "Ошибка ввода, повторите попытку");
			}
			case DIALOG_ATM_BIZ_PUT_MONEY:
			{
				new businessid = GetPVarInt(playerid, "ownablebiz_id");
				if(businessid != -1)
				{
					if(response)
					{
						if(!GetILPlayerStr("2000000000", inputtext)) return SCM(playerid, COLOR_GREY, "На счет предприятия можно положить до 2.000.000.000 руб за раз");

						new sum = strval(inputtext);
						if(IsILNumeric(inputtext))
						{
							if(VerifyIntString(QueryPlayerBalance(playerid), sum))
							{
								new query[128 + 1];

								format(query, sizeof query, "UPDATE accounts_canvasdev a, business b SET a.money=%s,b.balance=%s WHERE a.id=%d AND b.id=%d", SetILPlayerInt(playerid, QueryPlayerBalance(playerid), -sum), SetILPlayerInt(playerid, g_business[businessid][B_BALANCE], sum), GetPlayerAccountID(playerid), GetBusinessData(businessid, B_SQL_ID));
								mysql_query(mysql, query, false);

								if(!mysql_errno())
								{
									format(g_business[businessid][B_BALANCE], 21, "%s", SetILPlayerInt(playerid, g_business[businessid][B_BALANCE], sum));
									ModifyCashBalance(playerid, -sum, "Пополнение счета Бизнеса", false, true);

									ApplyAnimation(playerid, "CRIB", "CRIB_Use_Switch", 4.0, 0, 0, 0, 0, 0, 0);
									ShowPlayerATMDialog(playerid);
									return 1;
								}
								else SendClientMessage(playerid, 0xFF6600FF, "Ошибка сохранения, повторите попытку {FF0000}(equ-code 18)");
							}
							else SendClientMessage(playerid, 0xCECECEFF, "У Вас с собой нет столько денег");
						}
						else SendClientMessage(playerid, 0xFF6600FF, "Ошибка ввода, повторите попытку");
					}
					else
					{
						ShowPlayerATMDialog(playerid);
						ApplyAnimation(playerid, "CRIB", "CRIB_Use_Switch", 4.0, 0, 0, 0, 0, 0, 0);
					}
				}
			}
			case DIALOG_ATM_TRANSFER_MONEY_1:
			{
				if(response)
				{
					new transfer_id = strval(inputtext);

					if(transfer_id > 0 && IsILNumeric(inputtext))
					{
						SetPlayerBankTransfer(playerid, BT_ID, 0);
						SetPlayerBankTransfer(playerid, BT_UID, 0);

						new query[64 + 1];
						new Cache: result;

						format(query, sizeof query, "SELECT id, uid FROM bank_accounts WHERE id=%d LIMIT 1", transfer_id);
						result = mysql_query(mysql, query);

						if(cache_num_rows())
							SetPlayerBankTransfer(playerid, BT_ID, cache_get_row_int(0, 0)),
							SetPlayerBankTransfer(playerid, BT_UID, cache_get_row_int(0, 1));

						cache_delete(result);

					
						if(GetPlayerBankTransfer(playerid, BT_ID))
						{
							new to_player = GetPlayerIDBySqlID(GetPlayerBankTransfer(playerid, BT_UID));

							if(IsPlayerConnected(to_player) && IsPlayerLogged(to_player))
							{
								return ShowPlayerATMTransfer(playerid);
							}
							else SCM(playerid, 0xc7590fFF, "Владелец счета должен находиться на сервере.");
						}
						else SendClientMessage(playerid, 0xFF6600FF, "Счета с таким номером не существует");
					}

					IntfDialogCallRemote
					(
						playerid, DIALOG_ATM_TRANSFER_MONEY_1, DIALOG_STYLE_INPUT,
						"{FFD83D}Безналичный перевод",
						"{FFFFFF}Укажите номер банковского счета:",
						"Далее", "Отмена"
					);
				}
				else ShowPlayerATMDialog(playerid);
			}
			case DIALOG_ATM_TRANSFER_MONEY_2:
			{
				new transfer_id = GetPlayerBankTransfer(playerid, BT_ID);
				if(response && transfer_id)
				{
					if(!GetILPlayerStr("2000000000", inputtext)) return SCM(playerid, COLOR_GREY, "Перевод доступен до 2.000.000.000 руб за один раз"), ShowPlayerATMTransfer(playerid);

					new to_player = GetPlayerIDBySqlID(GetPlayerBankTransfer(playerid, BT_UID));

					if(!IsPlayerConnected(to_player) || !IsPlayerLogged(to_player)) return SCM(playerid, 0xc7590fFF, "Владелец счета должен находиться на сервере."), ShowPlayerATMTransfer(playerid);

					new transfer_sum = strval(inputtext);
					if(IsILNumeric(inputtext))
					{
						if(VerifyIntString(GetPlayerBankMoney(playerid), transfer_sum))
						{
							new fmt_str[155];

							format(fmt_str, sizeof fmt_str, "UPDATE accounts_canvasdev a,bank_accounts ba SET a.bank=%s,ba.balance=%s WHERE a.id=%d AND ba.id=%d", SetILPlayerInt(playerid, GetPlayerBankMoney(playerid), -transfer_sum), SetILPlayerInt(playerid, GetBankAccountBalance(transfer_id), transfer_sum / 100 * 80), GetPlayerAccountID(playerid), transfer_id);
							mysql_query(mysql, fmt_str, false);
							

							if(!mysql_errno())
							{
								format(fmt_str, sizeof fmt_str, "+ Пополнения с банкомата %d руб", transfer_sum / 100 * 80);
								BankAccountLog(playerid, transfer_id, fmt_str);

								format(g_player[playerid][P_BANK], 21, "%s", SetILPlayerInt(playerid, GetPlayerBankMoney(playerid), -transfer_sum));
								format(g_bank_account[to_player][transfer_id][BA_BALANCE], 21, "%s", SetILPlayerInt(playerid, GetBankAccountBalance(transfer_id), transfer_sum / 100 * 80));
								
								format
								(
									fmt_str, sizeof fmt_str,
									"{FFFFFF}Откуда:\t\t\tОсновной счет\n"\
									"Куда:\t\t\t\tСчет №%d\n"\
									"Сумма:\t\t\t\t%d руб\n"\
									"{3caa3c}Коммисия:\t\t\t\t%d руб\n"\
									"{FFFFFF}Остаток на Вашем счету:\t%s руб",
									transfer_id,
									transfer_sum / 100 * 80,
									transfer_sum / 100 * 20,
									formatStr(GetPlayerBankMoney(playerid))
								);
								IntfDialogCallRemote(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, "{99FF00}Перевод завершен", fmt_str, "Закрыть", "");

								new businessid = GetPlayerInBiz(playerid);

								AddBusinessProfit(playerid, businessid, transfer_sum / 100 * 20, 1);

								return PlayerPlaySound(playerid, 1054, 0.0, 0.0, 0.0);
							}
							else SendClientMessage(playerid, 0xFF6600FF, "Ошибка сохранения, повторите попытку {FF0000}(equ-code 11)");
						}
						else SendClientMessage(playerid, 0xFF6600FF, "На основном банковском счете недостаточно денег");
					}
					ShowPlayerATMTransfer(playerid);
				}
				else ShowPlayerATMDialog(playerid);
			}
			case DIALOG_ATM_TICKET_SELECT:
			{
				if(!response) return ShowPlayerATMDialog(playerid);

				switch(listitem + 1)
				{
					case 1:
					{
						type_page_cars[playerid] = 0;
						page_cars[playerid] = 1;
						ShowOwnableTickets(playerid, page_cars[playerid], 0);
					}
					case 2:
					{
						IntfDialogCallRemote
						(
							playerid, DIALOG_ATM_TICKET_PAY, DIALOG_STYLE_INPUT,
							"{FFD83D}Оплата штрафа",
							"{FFFFFF}Введите номер штрафа для оплаты",
							"Далее", "Назад"
						);
					}
					case 3:
					{
						new query[90],
							Cache: result;

						mysql_format(mysql, query, sizeof query, "SELECT * FROM tickets WHERE uid=%d AND status=0", GetPlayerAccountID(playerid));
						result = mysql_query(mysql, query, true);

						new rows = cache_num_rows();

						SetPVarInt(playerid, "AllTickets", 0);

						for(new i; i < rows; i++)
						{
							SetPVarInt(playerid, "AllTickets", GetPVarInt(playerid, "AllTickets") + cache_get_field_content_int(i, "amount"));
						}

						cache_delete(result);

						if(rows)
						{
							string_dialog[0] = EOS;

							format(string_dialog, sizeof string_dialog, "{FFFFFF}На ваше имя выписано {deb308}%d {FFFFFF}штрафов на сумму {deb308}%s руб.", rows, formatInt(GetPVarInt(playerid, "AllTickets")));
							
							IntfDialogCallRemote(playerid, DIALOG_ATM_TICKET_PAY_ALL, DIALOG_STYLE_MSGBOX,"{FFD83D}Оплата всех штрафов",string_dialog,"Далее", "Назад");
						}
						else ShowPlayerATMDialog(playerid), SCM(playerid, -1, "У вас нет штрафов");
					}
				}
			}
			case DIALOG_ATM_TICKET_PAY_ALL:
			{
				if(!response) return ShowPlayerATMDialog(playerid);

				if(!VerifyIntString(QueryPlayerBalance(playerid), GetPVarInt(playerid, "AllTickets"))) return SCM(playerid, 0xe2c977FF, "У вас недостаточно денег для оплаты всех штрафов.");

				ModifyCashBalance(playerid, -GetPVarInt(playerid, "AllTickets"), "Оплата всех штрафов");

				SCMF(playerid, 0xa6caf0FF, "Вы успешно оплатили все свои штрафы на сумму {FFFFFF}%s {a6caf0}руб.", formatInt(GetPVarInt(playerid, "AllTickets")));

				new query[64];
				mysql_format(mysql, query, sizeof query, "UPDATE tickets SET status=1 WHERE uid=%d", GetPlayerAccountID(playerid));
				mysql_query(mysql, query, false);
			}
			case DIALOG_ATM_TICKET_LIST:
			{
				if(!response) return 1;

				if(GetPlayerListitemValue(playerid, listitem)) PayTicket(playerid, GetPlayerListitemValue(playerid, listitem));
				
			}
			case DIALOG_DRAG_RACING:
			{
				if(!response) return 1;

				if(listitem == 0) if(!VerifyIntString(QueryPlayerBalance(playerid), 1)) return SCM(playerid, COLOR_GREY, "У вас недостаточно средств, минимум 1 руб.");
				if(listitem == 1) if(GetIteam(playerid, 293) < 1) return SCM(playerid, COLOR_GREY, "У вас недостаточно средств, минимум 1 фишка.");
				if(listitem == 2) if(QueryPlayerDonationBalance(playerid) < 1) return SCM(playerid, COLOR_GREY, "У вас недостаточно средств, минимум 1 донат.");

				g_drag_racing[g_drag_racing_id[playerid]][E_BET] = listitem;

				CEF_HIDE(playerid, "DragRacingStart");
				CEF_CREATE(playerid, 2, 4, "DragRacingStart", "[1, [1, [2, 2], 0, 0]]");
				g_drag_racing[g_drag_racing_id[playerid]][E_TYPE] = 1;
			}
			case DIALOG_TAKE_CAR_PRIZE:
			{
			    if(!response) return RemovePlayerFromVehicle(playerid);
			   
				if((GetPlayerOwnableCars(playerid) + 1) > GetPlayerCarSlots(playerid)) return GameText(playerid, "~r~Недостаточно~n~слотов на транспорт", 3000, 2), RemovePlayerFromVehicle(playerid);

				new vehicleid = GetPlayerVehicleID(playerid);
				if(vehicleid != INVALID_VEHICLE_ID)
				{
					new model_id = GetVehicleModel(vehicleid);
					if(model_id == 0) return RemovePlayerFromVehicle(playerid);

					new Float: pos_xp, Float: pos_yp, Float: pos_zp,Float: angle = 180.0;
					GetPlayerPos(playerid, pos_xp, pos_yp, pos_zp);

					new query[220];
					format(query, sizeof query, "[Розыгрыш] Игрок: %s[%d] выиграл транспорт: %s", GetPlayerNameEx(playerid), playerid, GetVehicleInfo(model_id , VI_NAME));
					SendClientMessageToAll(0xFFA500FF, query);

					GiveCar(playerid, model_id, 1, 1, -1, -1, pos_xp, pos_yp, pos_zp, angle, gettime());

					DestroyVehicleLabel(vehicleid);
					DestroyVehicle(vehicleid);
					
					SendClientMessage(playerid, 0x66CC00FF, "Поздравляем! Вы успешно забрали транспорт себе! Загрузить: {FFA500}/car");
				}
			}
			case DIALOG_PLAYER_BONUS:
			{
				if(!response) return 1;

				if(listitem == 0)
				{
					new count = GetPVarInt(playerid, "all_player_bonus");

					if(count < 1) return 1;

					ModifyCashBalance(playerid, count, "Забрал все бонусы с /bonus");

					new query[148];
					format(query, sizeof query, "DELETE FROM player_bonus WHERE owner_id=%d", GetPlayerAccountID(playerid));
					mysql_query(mysql, query, false);

					SCMF(playerid, 0x288ef0FF, "Вы забрали все бонусы в размере {ffd010}%s руб", formatInt(count));

					DeletePVar(playerid, "all_player_bonus");
				}
				else
				{
					new query[148],
						text[32],
						Cache: result;

					mysql_format(mysql, query, sizeof query, "SELECT * FROM player_bonus WHERE id=%d LIMIT 1", GetPlayerListitemValue(playerid, listitem - 1));
					result = mysql_query(mysql, query);

					new count = cache_get_field_content_int(0, "count");

					cache_get_field_content(0, "text", text);

					cache_delete(result);

					ModifyCashBalance(playerid, count, "Забрал с бонусов");

					format(query, sizeof query, "DELETE FROM player_bonus WHERE id=%d", GetPlayerListitemValue(playerid, listitem - 1));
					mysql_query(mysql, query, false);

					SCMF(playerid, 0x288ef0FF, "Вы получили бонус в размере {ffd010}%s руб {288ef0}за %s", formatInt(count), text);
				}
			}
			case DIALOG_PLAYER_NOTIFICATION:
			{
				if(!response) return 1;

				new query[148],
					text[148],
					note_text[148],
					time[21],
					Cache: result;

				mysql_format(mysql, query, sizeof query, "SELECT * FROM notification WHERE id=%d LIMIT 1", GetPlayerListitemValue(playerid, listitem));
				result = mysql_query(mysql, query);

				cache_get_field_content(0, "text", text);
				cache_get_field_content(0, "note_text", note_text);
				cache_get_field_content(0, "time", time);

				cache_delete(result);

				string_dialog[0] = EOS;
				format(string_dialog, sizeof string_dialog, "Тип уведомления:\t\t\t%s\nДата и время:\t\t\t%s\n\n%s",text, time, note_text);
				IntfDialogCallRemote(playerid, DIALOG_PLAYER_NOTIFICATION_2, DIALOG_STYLE_MSGBOX, "{FFFFFF}Информация уведомления", string_dialog, "Назад", "Закрыть");

				mysql_format(mysql, query, sizeof query, "UPDATE notification SET status=0 WHERE id=%d", GetPlayerListitemValue(playerid, listitem));
				mysql_query(mysql, query, false);
			}

			case DIALOG_PLAYER_NOTIFICATION_2:
			{
				if(!response) return 1;
				callcmd::notification(playerid);
			}
			case DIALOG_CAR_ACTIVE_ACS_LIST:
            {
                if(!response) return 1;

                new selected_id = GetPlayerListitemValue(playerid, listitem);

                new query[128], Cache:result;
                mysql_format(mysql, query, sizeof query, "SELECT * FROM cars_accessories WHERE id=%d LIMIT 1", selected_id);
                result = mysql_query(mysql, query, true);

                if(!cache_num_rows()){
                    cache_delete(result);
                    return 1;
                }

                new indx = cache_get_field_content_int(0, "indx");
                new model_id = cache_get_field_content_int(0, "model_id");
                cache_delete(result);

                active_acs_id[playerid] = selected_id;

                new Float:x, Float:y, Float:z, Float:a;
                GetPlayerPos(playerid, x, y, z);
                GetPlayerFacingAngle(playerid, a);
                
				new vehicleid = GetPVarInt(playerid, "AcsVehicleCar");
				new index = GetVehicleData(GetPVarInt(playerid, "AcsVehicleCar"), V_ACTION_ID);
				new car_id = GetOwnableCarData(index, OC_SQL_ID);
                
                if(active_acs[playerid] != INVALID_VEHICLE_ID){
                    DestroyVehicle(active_acs[playerid]);
                    active_acs[playerid] = INVALID_VEHICLE_ID;
                    active_acs_id[playerid] = -1;
					LoadCarAccessories(car_id, vehicleid);
					return 1;
                }

                switch(model_id){
                    case 16229: active_acs[playerid] = CreateVehicle(510, x, y, z, a, 0, 0, -1, 0, VEHICLE_ACTION_TYPE_ACTIVE_ACS, 1);
                    case 17163: active_acs[playerid] = CreateVehicle(15683, x, y, z, a, 0, 0, -1, 0, VEHICLE_ACTION_TYPE_ACTIVE_ACS, 1);
                    case 17273: active_acs[playerid] = CreateVehicle(571, x, y, z, a, 0, 0, -1, 0, VEHICLE_ACTION_TYPE_ACTIVE_ACS, 1);
                    case 17607: active_acs[playerid] = CreateVehicle(15699, x, y, z, a, 0, 0, -1, 0, VEHICLE_ACTION_TYPE_ACTIVE_ACS, 1);
                }

                if(IsValidDynamicObject(car_accessories[vehicleid][indx])){
                    DestroyDynamicObject(car_accessories[vehicleid][indx]);
                    car_accessories[vehicleid][indx] = INVALID_OBJECT_ID;
					LoadCarAccessories(car_id, vehicleid, playerid);
				}
                return 1;
            }
			case DIALOG_CAR_ACCESSORIES_LIST:
			{
				if(!response) return 1;

				SetPVarInt(playerid, "SelectedAccessoryID", GetPlayerListitemValue(playerid, listitem));

				IntfDialogCallRemote
                (
                    playerid, DIALOG_CAR_ACCESSORIES_LIST_2, DIALOG_STYLE_LIST,
                    "{FFD83D}Список украшений",
                    "Снять\n"\
					"Изменить позицию",
                    "Выбор", "Выйти"
                );
			}
			case DIALOG_CAR_ACCESSORIES_LIST_2:
			{
                if(!response) return 1;

				new accessory_id = GetPVarInt(playerid, "SelectedAccessoryID");

				switch(listitem + 1)
				{
					case 1:
					{
                        if(GetInventorySlots(playerid) == -1) return GameText(playerid, "~r~В вашем инвентаре~n~нет свободного места", 3000, 2);

				        new query[94],
                            Cache: result;

                        mysql_format(mysql, query, sizeof query, "SELECT * FROM cars_accessories WHERE id=%d LIMIT 1", accessory_id);
                        result = mysql_query(mysql, query, true);

				        new model_id = cache_get_field_content_int(0, "model_id");

                        cache_delete(result);

				        format(query, sizeof query, "DELETE FROM cars_accessories WHERE id=%d", accessory_id);
				        mysql_query(mysql, query, false);

				        GiveAcs(playerid, model_id, 14);

						ApplyAnimationEx(playerid, "BOMBER", "BOM_Plant", 2.0, 0, 0, 0, 0, 0, 0);

				        new vehicleid = GetPVarInt(playerid, "AcsVehicleCar");
				        new index = GetVehicleData(vehicleid, V_ACTION_ID);
				        new car_id = GetOwnableCarData(index, OC_SQL_ID);

				        LoadCarAccessories(car_id, vehicleid);

				        SCM(playerid, 0x2B83DBFF, "Вы сняли украшение с транспорта");
					}
					case 2:
					{
						SCM(playerid, -1, "В разработке by CanVas Dev");
					}
				}
			}
			case DIALOG_ATM_TICKET_PAY:
			{
				if(response)
				{
					new ticketid = strval(inputtext);

					PayTicket(playerid, ticketid);
				}

				ShowPlayerATMDialog(playerid);
			}
			case DIALOG_ATM_CHARITY:
			{
				if(response)
				{
					new put_sum = strval(inputtext);
					if(put_sum > 0 && IsNumeric(inputtext))
					{
						if(VerifyIntString(QueryPlayerBalance(playerid), put_sum))
						{
							new fmt_str[148];
							format(fmt_str, sizeof fmt_str, "INSERT INTO charity (uid,money,time,name) VALUES (%d,%d,%d,'%s')", GetPlayerAccountID(playerid), put_sum, gettime(), GetPlayerNameEx(playerid));
							mysql_query(mysql, fmt_str, false);

							ModifyCashBalance(playerid, -put_sum, "Благотворительность", true, true);

							format(fmt_str, sizeof fmt_str, "Вы сделали пожертвование в размере %d рублей", put_sum);
							SendClientMessage(playerid, 0x3399FFFF, fmt_str);

							if(GetPlayerLevel(playerid) > 4)
							{
                                AddPlayerData(playerid, P_ACHIV_19, +, put_sum);
                                UpdatePlayerDatabaseInt(playerid, "achiv_19", GetPlayerData(playerid, P_ACHIV_19));
        
		                        if(GetPlayerData(playerid, P_ACHIV_19) >= 1000000 && GetPlayerData(playerid, P_ACHIV_19_COMPLETED) == 0)
		                        {
			                        GivePlayerMyPrizes(playerid, "Донат", 10, 0, 0, 25, 0);
                                    SendClientMessage(playerid, COLOR_GREEN, "Поздравляем! Вы получили достижение: {FFFF00}\"Доброжелатель\"");
			                        SendClientMessage(playerid, 0xead671FF, "Вам выдана награда за получение достижения. Используйте {ffffff}клавишу M > Награды, {ead671}чтобы забрать её.");
		    
			                        SetPlayerData(playerid, P_ACHIV_19_COMPLETED, 1);
                                    UpdatePlayerDatabaseInt(playerid, "achiv_19_completed", 1);

								    CEF_CREATE(playerid, 2, 4, "AchievementNotification", "[19, 0, \"Вы получили достижение!\"]");
		                        }
							}

							UpdateCharity();
							SetPlayerData(playerid, P_DOSTIJ20, GetPlayerData(playerid, P_DOSTIJ20) + put_sum);
							UpdatePlayerDatabaseInt(playerid, "dostij20", GetPlayerData(playerid, P_DOSTIJ20) + put_sum);
							OnBattlePass_Perfomance(playerid, 5, put_sum);
						}
						else
						{
							SendClientMessage(playerid, 0xCECECEFF, "У Вас недостаточно денег");
							ShowPlayerATMCharityDialog(playerid);
						}
					}
					else ShowPlayerATMCharityDialog(playerid);
				}
			}
			case DIALOG_HEALTH_BUSINESS:
			{
                if(response)
                {
				    new pickupid = GetPlayerData(playerid, P_LAST_PICKUP);
					new action_id = GetPickupInfo(pickupid, P_ACTION_ID);
				    new businessid = GetPlayerInBiz(playerid);
					if(businessid != -0)
					{
						if(businessid == action_id)
						{
							new time = gettime();
							if(GetPVarInt(playerid, "biz_health_use") <= time)
							{
								new price = BIZ_HEALTH_SERVICE_PRICE;
								if(VerifyIntString(QueryPlayerBalance(playerid), price))
								{
									ModifyCashBalance(playerid, -price, "Использование аптечки в бизнесе", true, true);

									if(GetBusinessData(businessid, B_PRODS) >= 1)
									{
										AddBusinessProfit(playerid, businessid, price, 1);
									}
									SetPlayerHealthEx(playerid, 99.0);
									SetPVarInt(playerid, "biz_health_use", time + 90); // 90 сек (1:30 минут)
						
								}
								else SendClientMessage(playerid, 0x999999FF, "Услуги медпункта стоят 3500 рублей");
							}
							else SendClientMessage(playerid, 0x999999FF, "Недавно Вы уже пользовались услугами медпункта");
						}
					}
				}
			}

			// -----------------------------------------------------------------
			case DIALOG_KIOSK_NAME://надо
			{
				new str_len = strlen(inputtext);
				if(str_len > 25) return SendClientMessage(playerid, 0xCECECEFF, "Максимальная длина текста не более 25 символов");
				
				new kiosk_id = GetNearestKiosk(playerid, 7.0), fmt_text[128];

				mysql_format(mysql, fmt_text, sizeof fmt_text, "UPDATE kiosk SET name='%s' WHERE id=%d", inputtext, GetKioskData(kiosk_id, K_SQL_ID));
				mysql_query(mysql, fmt_text, false);

				format(g_kiosk[kiosk_id][K_NAME],33,inputtext);
		
				STRING_GLOBAL[0] = EOS;
				format(STRING_GLOBAL,sizeof STRING_GLOBAL,"{FF8800}Магазин №%d\n{0E0101}\"%s\"", GetKioskData(kiosk_id, K_SQL_ID),inputtext);
				SetDynamicObjectMaterialText(kiosktext[GetKioskData(kiosk_id, K_SQL_ID)], 0,STRING_GLOBAL, 120, "Arial", 20, 1, 0xFFFFFFFF, 0xFFFFFFFF, 1);
				SendClientMessage(playerid, 0xCECECEFF, "Вы успешно сменили название киоска");
			}
			case DIALOG_PAY_FOR_RENT:
			{
				if(!response) return 1;
				switch(listitem + 1)
				{
					case 1: // Заплатить за дом
					{
						ShowPlayerHousePayForRent(playerid);
						return 1;
					}
					case 2: // Оплатить аренду бизнеса
					{
						new query[256],
							Cache: result,
							biz_id,
							biz_name[64];

						mysql_format(mysql, query, sizeof query, "SELECT * FROM business WHERE owner_id='%d'", GetPlayerAccountID(playerid));
						result = mysql_query(mysql, query, true);

						new rows = cache_num_rows();

						if(!rows)
							return SendClientMessage(playerid, 0x999999FF, "У вас не одного бизнеса во владении.");

						string_dialog[0] = EOS;
						for(new i = 0; i < rows; i ++)
						{
							biz_id = cache_get_field_content_int(i, "id");
							cache_get_field_content(i, "name", biz_name);

							format(query, sizeof query, "{FFFFFF}%d. - %s (№%d)<t>Владелец\n", i + 1, biz_name, biz_id);
							strcat(string_dialog, query);
							SetPlayerListitemValue(playerid, i, biz_id-1);
						}

						IntfDialogCallRemote
						(
							playerid, DIALOG_OWNABLE_BIZ_OPLATA, DIALOG_STYLE_LIST,
							"{FFCD00}Выберите бизнес",
							string_dialog,
							"Выбрать", "Закрыть"
						);

						cache_delete(result);
						return 1;
					}
					case 3: // Оплатить аренду киоска
					{
						new query[256],
							Cache: result,
							biz_id,
							biz_name[64];

						mysql_format(mysql, query, sizeof query, "SELECT * FROM kiosk WHERE owner_id='%d'", GetPlayerAccountID(playerid));
						result = mysql_query(mysql, query, true);

						new rows = cache_num_rows();

						if(!rows) return SendClientMessage(playerid, 0x999999FF, "У вас не одного киоска во владении.");

						string_dialog[0] = EOS;
						for(new i = 0; i < rows; i ++)
						{
							biz_id = cache_get_field_content_int(i, "id");
							cache_get_field_content(i, "name", biz_name);

							format(query, sizeof query, "{FFFFFF}%d. - %s (№%d)\n", i + 1, biz_name, biz_id);
							strcat(string_dialog, query);
							SetPlayerListitemValue(playerid, i, biz_id-1);
						}

						IntfDialogCallRemote
						(
							playerid, DIALOG_OWNABLE_KIOSK_OPLATA, DIALOG_STYLE_LIST,
							"{FFCD00}Выберите киоск",
							string_dialog,
							"Выбрать", "Закрыть"
						);

						cache_delete(result);
						return 1;
					}
					case 4: // Оплатить гараж
					{					
						new query[256],
							Cache: result,
							biz_id;

						mysql_format(mysql, query, sizeof query, "SELECT * FROM garage WHERE owner_id='%d'", GetPlayerAccountID(playerid));
						result = mysql_query(mysql, query, true);

						new rows = cache_num_rows();

						if(!rows) return SendClientMessage(playerid, 0x999999FF, "У вас не одного гаража во владении.");

						string_dialog[0] = EOS;
						for(new i = 0; i < rows; i ++)
						{
							biz_id = cache_get_field_content_int(i, "id");

							format(query, sizeof query, "{FFFFFF}%d. - Гараж (№%d)\n", i + 1, biz_id);
							strcat(string_dialog, query);
							SetPlayerListitemValue(playerid, i, biz_id-1);
						}

						IntfDialogCallRemote
						(
							playerid, DIALOG_OWNABLE_GARAGE_OPLATA, DIALOG_STYLE_LIST,
							"{FFCD00}Выберите киоск",
							string_dialog,
							"Выбрать", "Закрыть"
						);

						cache_delete(result);
						return 1;
					}
					case 5: // Оплатить огород
					{
						new query[256],
							Cache: result,
							garden_id;

						mysql_format(mysql, query, sizeof query, "SELECT * FROM gardens WHERE owner_id='%d'", GetPlayerAccountID(playerid));
						result = mysql_query(mysql, query, true);

						new rows = cache_num_rows();

						if(!rows)
							return SendClientMessage(playerid, 0x999999FF, "У вас нет огородов.");

						string_dialog[0] = EOS;
						for(new i = 0; i < rows; i ++)
						{
							garden_id = cache_get_field_content_int(i, "id");

							format(query, sizeof query, "%d.{FFFFFF} Огород №%d\n",i+1, garden_id);
							strcat(string_dialog, query);
							SetPlayerListitemValue(playerid, i, garden_id);
						}

						IntfDialogCallRemote
						(
							playerid, DIALOG_GARDEN_LIST, DIALOG_STYLE_LIST,
							"{FFCD00}Огороды",
							string_dialog,
							"Выбрать", "Закрыть"
						);

						cache_delete(result);
						return 1;
					}
					case 6:
					{
						new query[256],
							Cache: result;

						format(query, sizeof query, "SELECT * FROM neftenasos WHERE owner_id='%d'", GetPlayerAccountID(playerid));
						result = mysql_query(mysql, query, true);

						new rows = cache_num_rows();

						if(!rows) return SendClientMessage(playerid, 0x999999FF, "У вас не одного нефтенасоса во владении.");

						string_dialog[0] = EOS;
						for(new i; i < rows; i ++)
						{
							new biz_id = cache_get_field_content_int(i, "id");

							format(query, sizeof query, "{FFFFFF}Нефтенасос №%d\n", biz_id);
							strcat(string_dialog, query);
							SetPlayerListitemValue(playerid, i, biz_id);
						}

						IntfDialogCallRemote
						(
							playerid, DIALOG_OWNABLE_NEFTENASOS_LIST2, DIALOG_STYLE_LIST,
							"{FFCD00}Выберите нефтенасос",
							string_dialog,
							"Выбрать", "Закрыть"
						);
						cache_delete(result);
						return 1;
					}
				}
				ShowPlayerPayForRentDialog(playerid);
			}
			case DIALOG_GARDEN_LIST:
			{
			    if(response)
				{
				    new garden = GetPlayerListitemValue(playerid, listitem);
				    if(garden != -1)
				    {
				    	ShowPlayerGardenPayForRent(playerid,garden);
				    }
			    }
			}
			case DIALOG_PAY_FOR_RENT_GARDEN:
			{
				new businessid = GetPVarInt(playerid,"garden_id");
				if(businessid != -1)
				{
					if(response)
					{
						new days = strval(inputtext);
						if(days > 0 && IsNumeric(inputtext))
						{
							new fmt_str[128 + 1];

							new rent_time = GetGardenData(businessid, G_RENT_DATE);

							new rent_price = GetGardenData(businessid, G_RENT_PRICE);

							new total_price = rent_price * days;
							if((rent_time + days) <= 30)
							{
								if(VerifyIntString(GetPlayerBankMoney(playerid), total_price))
								{

									format(fmt_str, sizeof fmt_str, "UPDATE accounts_canvasdev a,gardens b SET a.bank=%s,b.rent=%d WHERE a.id=%d AND b.id=%d", SetILPlayerInt(playerid, GetPlayerBankMoney(playerid), -total_price), days + rent_time, GetPlayerAccountID(playerid), GetGardenData(businessid, G_SQL_ID));
									mysql_query(mysql, fmt_str, false);

									if(!mysql_errno())
									{
										format(g_player[playerid][P_BANK], 21, "%s", SetILPlayerInt(playerid, GetPlayerBankMoney(playerid), -total_price));
										SetGardenData(businessid, G_RENT_DATE, days + rent_time);

										format(fmt_str, sizeof fmt_str, "С банковского счета снято {3399FF}%d руб", total_price);
										SendClientMessage(playerid, 0xFFFFFFFF, fmt_str);

										format(fmt_str, sizeof fmt_str, "Вы успешно продлили аренду огорода еще на {3399FF}%d дней", days);
										SendClientMessage(playerid, 0x66CC00FF, fmt_str);
									}
								}
								else
								{
									SendClientMessage(playerid, 0xB5B500FF, "На основном банковском счету не хватает денег для оплаты");

									format(fmt_str, sizeof fmt_str, "Для продления аренды на %d дней необходимо %d руб", days, total_price);
									SendClientMessage(playerid, 0x999999FF, fmt_str);
								}
							}
							else SendClientMessage(playerid, 0xB5B500FF, "Вы не можете оплатить за аренду больше чем на 30 дней");
						}
						ShowPlayerGardenPayForRent(playerid,businessid);
					}
					else ShowPlayerPayForRentDialog(playerid);
				}
			}
			case DIALOG_PAY_FOR_RENT_BIZ:
			{
				new businessid = GetPVarInt(playerid, "ownablebiz_id");
				if(businessid != -1)
				{
					if(response)
					{
						new days = strval(inputtext);
						if(days > 0 && IsNumeric(inputtext))
						{
							new fmt_str[128 + 1];

							new time = gettime();
							new rent_time = GetBusinessData(businessid, B_RENT_DATE);

							new rent_days = GetElapsedTime(rent_time, time, CONVERT_TIME_TO_DAYS);
							new rent_price = GetBusinessData(businessid, B_IMPROVEMENTS) < 3 ? GetBusinessData(businessid, B_RENT_PRICE) : GetBusinessData(businessid, B_RENT_PRICE) / 2;

							new total_price = rent_price * days;
							if((rent_days + days) <= 30)
							{
								if(VerifyIntString(GetPlayerBankMoney(playerid), total_price))
								{
									rent_time = (rent_time - (rent_time % 86400)) + (days * 86400);

									format(fmt_str, sizeof fmt_str, "UPDATE accounts_canvasdev a,business b SET a.bank=%s,b.rent_time=%d WHERE a.id=%d AND b.id=%d", SetILPlayerInt(playerid, GetPlayerBankMoney(playerid), -total_price), rent_time, GetPlayerAccountID(playerid), GetBusinessData(businessid, B_SQL_ID));
									mysql_query(mysql, fmt_str, false);

									if(!mysql_errno())
									{
										format(g_player[playerid][P_BANK], 21, "%s", SetILPlayerInt(playerid, GetPlayerBankMoney(playerid), -total_price));
										SetBusinessData(businessid, B_RENT_DATE, rent_time);

										format(fmt_str, sizeof fmt_str, "С банковского счета снято {3399FF}%d руб", total_price);
										SendClientMessage(playerid, 0xFFFFFFFF, fmt_str);

										format(fmt_str, sizeof fmt_str, "Вы успешно продлили аренду бизнеса еще на {3399FF}%d дней", days);
										SendClientMessage(playerid, 0x66CC00FF, fmt_str);
									}
								}
								else
								{
									SendClientMessage(playerid, 0xB5B500FF, "На основном банковском счету не хватает денег для оплаты");

									format(fmt_str, sizeof fmt_str, "Для продления аренды на %d дней необходимо %d руб", days, total_price);
									SendClientMessage(playerid, 0x999999FF, fmt_str);
								}
							}
							else SendClientMessage(playerid, 0xB5B500FF, "Вы не можете оплатить за аренду больше чем на 30 дней");
						}
						ShowPlayerBusinessPayForRent(playerid);
					}
					else ShowPlayerPayForRentDialog(playerid);
				}
			}
			case DIALOG_PAY_FOR_RENT_KIOSK:
			{
				new businessid = GetPVarInt(playerid, "ownablekiosk_id");
				if(businessid != -1)
				{
					if(response)
					{
						new days = strval(inputtext);
						if(days > 0 && IsNumeric(inputtext))
						{
							new fmt_str[128 + 1];

							new rent_time = GetKioskData(businessid, K_RENT_DATE);

							new rent_price = GetKioskData(businessid, K_RENT_PRICE);

							new total_price = rent_price * days;
							if((rent_time + days) <= 7)
							{
								if(VerifyIntString(GetPlayerBankMoney(playerid), total_price))
								{

									format(fmt_str, sizeof fmt_str, "UPDATE accounts_canvasdev a,kiosk b SET a.bank=%s,b.rent=%d WHERE a.id=%d AND b.id=%d", SetILPlayerInt(playerid, GetPlayerBankMoney(playerid), -total_price), days + rent_time, GetPlayerAccountID(playerid), GetKioskData(businessid, K_SQL_ID));
									mysql_query(mysql, fmt_str, false);

									if(!mysql_errno())
									{
										format(g_player[playerid][P_BANK], 21, "%s", SetILPlayerInt(playerid, GetPlayerBankMoney(playerid), -total_price));
										SetKioskData(businessid, K_RENT_DATE, days + rent_time);

										format(fmt_str, sizeof fmt_str, "С банковского счета снято {3399FF}%d руб", total_price);
										SendClientMessage(playerid, 0xFFFFFFFF, fmt_str);

										format(fmt_str, sizeof fmt_str, "Вы успешно продлили аренду киоска еще на {3399FF}%d дней", days);
										SendClientMessage(playerid, 0x66CC00FF, fmt_str);
									}
								}
								else
								{
									SendClientMessage(playerid, 0xB5B500FF, "На основном банковском счету не хватает денег для оплаты");

									format(fmt_str, sizeof fmt_str, "Для продления аренды на %d дней необходимо %d руб", days, total_price);
									SendClientMessage(playerid, 0x999999FF, fmt_str);
								}
							}
							else SendClientMessage(playerid, 0xB5B500FF, "Вы не можете оплатить за аренду больше чем на 7 дней");
						}
						ShowPlayerKioskPayForRent(playerid);
					}
					else ShowPlayerPayForRentDialog(playerid);
				}
			}
			
			case DIALOG_PAY_FOR_RENT_GARAGE:
			{
				new garage_id = GetPVarInt(playerid, "ownablegarage_id");
				if(garage_id != -1)
				{
					if(response)
					{
						new days = strval(inputtext);
						if(days > 0 && IsNumeric(inputtext))
						{
							new fmt_str[128 + 1];

							new time = gettime();
							new rent_time = GetGarageData(garage_id, G_RENT_DATE);

							new rent_days = GetElapsedTime(rent_time, time, CONVERT_TIME_TO_DAYS);
							new rent_price = GetGarageData(garage_id, G_IMPROVEMENTS) > 0 ? GetGarageData(garage_id, G_RENT_PRICE) / 2 : GetGarageData(garage_id, G_RENT_PRICE);

							new total_price = rent_price * days;
							if((rent_days + days) <= 30)
							{
								if(VerifyIntString(GetPlayerBankMoney(playerid), total_price))
								{
									rent_time = (rent_time - (rent_time % 86400)) + (days * 86400);

									format(fmt_str, sizeof fmt_str, "UPDATE accounts_canvasdev a,garage g SET a.bank=%s,g.rent_time=%d WHERE a.id=%d AND g.id=%d", SetILPlayerInt(playerid, GetPlayerBankMoney(playerid), -total_price), rent_time, GetPlayerAccountID(playerid), GetGarageData(garage_id, G_SQL_ID));
									mysql_query(mysql, fmt_str, false);

									if(!mysql_errno())
									{
										format(g_player[playerid][P_BANK], 21, "%s", SetILPlayerInt(playerid, GetPlayerBankMoney(playerid), -total_price));
										SetGarageData(garage_id, G_RENT_DATE, rent_time);

										format(fmt_str, sizeof fmt_str, "С банковского счета снято {"#cGold"}%d руб", total_price);
										SendClientMessage(playerid, COLOR_WHITE, fmt_str);

										format(fmt_str, sizeof fmt_str, "Вы успешно оплатили гараж еще на {"#cGold"}%d дней", days);
										SendClientMessage(playerid, COLOR_WHITE, fmt_str);
									}
								}
								else
								{
									SendClientMessage(playerid, COLOR_GOLD, "На основном банковском счету не хватает денег для оплаты");

									format(fmt_str, sizeof fmt_str, "Для продления аренды на %d дней необходимо %d руб", days, total_price);
									SendClientMessage(playerid, 0x999999FF, fmt_str);
								}
							}
							else SendClientMessage(playerid, COLOR_GOLD, "Вы не можете оплатить за аренду гаражa больше чем на 30 дней");
						}
						ShowPlayerGaragePayForRent(playerid);
					}
					else ShowPlayerPayForRentDialog(playerid);
				}
			}
			// -----------------------------------------------------------------
			case DIALOG_BANK:
			{
				if(response)
				{
					switch(listitem + 1)
					{
						case 1:
						{
							ShowPlayerBankAccounts(playerid);
						}
						case 2:
						{
							IntfDialogCallRemote
							(
								playerid, DIALOG_BANK_CREATE_ACCOUNT, DIALOG_STYLE_INPUT,
								"{FFD83D}Создание нового счета",
								"{FFFFFF}Введите название для нового счета.\n"\
								"Максимальная длина 20 символов:",
								"Ок", "Отмена"
							);
						}
					}
				}
			}
			case DIALOG_GARAGE_BUY:
			{
				if(response)
				{
					new garage_id = GetPVarInt(playerid, "buy_garage_id");

					if(IsPlayerInRangeOfPoint(playerid, 7.0, GetGarageData(garage_id, G_POS_X), GetGarageData(garage_id, G_POS_Y), GetGarageData(garage_id, G_POS_Z)))
					{
						if(!IsGarageOwned(garage_id))
						{
							if(VerifyIntString(QueryPlayerBalance(playerid), GetGarageData(garage_id, G_PRICE)))
							{
								if(GetOwnableAuction(2, GetGarageData(garage_id, G_SQL_ID)) > 0) return SCM(playerid, COLOR_GREY, "* Данный гараж выставлен на аукцион");

								SendClientMessage(playerid, COLOR_WHITE, "Поздравляем! Вы купили гараж");
								BuyPlayerGarage(playerid, garage_id);
								if(GetGarageData(garage_id, G_TYPE) == 1)
								{
									AddPlayerData(playerid, P_CAR_SLOTS,+,5);
									UpdatePlayerDatabaseInt(playerid, "car_slots", GetPlayerData(playerid, P_CAR_SLOTS));
								}
								else if(GetGarageData(garage_id, G_TYPE) == 2)
								{
									AddPlayerData(playerid, P_CAR_SLOTS,+,9);
									UpdatePlayerDatabaseInt(playerid, "car_slots", GetPlayerData(playerid, P_CAR_SLOTS));

								}
								else if(GetGarageData(garage_id, G_TYPE) == 3)
								{
									AddPlayerData(playerid, P_CAR_SLOTS,+,15);
									UpdatePlayerDatabaseInt(playerid, "car_slots", GetPlayerData(playerid, P_CAR_SLOTS));
								}
								PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
								IntfDialogCallRemote(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, "{"#cGold"}Новый гараж", "{"#cW"}Вам нужно заплатить за аренду гаража в ближайшем отделением банка {"#cGold"}(H - GPS)", "Ок", "");
							}
							else SendClientMessage(playerid, 0xFF6600FF, "У Вас недостаточно денег для покупки этого гаража");
						}
						else
						{
							new fmt_str[64];

							format(fmt_str, sizeof fmt_str, "Этот гараж уже куплен. Владелец: %s", GetGarageData(garage_id, G_OWNER_NAME));
							SendClientMessage(playerid, 0xFF6600FF, fmt_str);
						}
					}
				}
				DeletePVar(playerid, "buy_biz_id");
			}
			case DIALOG_BIZ_SELL_TEST:
			{
			    new businessid = GetPlayerListitemValue(playerid, listitem) + 1;
			    SetPVarInt(playerid, "ownablebiz_id", businessid);
			    IntfDialogCallRemote
				(
					playerid, DIALOG_BIZ_SELL, DIALOG_STYLE_MSGBOX,
					"{FFCD00}Продажа бизнеса",
					"{FFFFFF}Вы уверены что хотите продать свой бизнес государству?\n\n"\
					"Вам будет возвращено его стоимость за вычитом 30%\n"\
					"Также будет возвращено 60% от стоимости купленных улучшений\n\n"\
					"Если Вы хотите продать бизнес другому игроку,\n"\
					"используйте команду /sellmybiz",
					"Да", "Нет"
				);
			}
			case DIALOG_KIOSK_SELL:
			{
			    SellKiosk(playerid);
			}
			case DIALOG_KIOSK_SELL_LIST:
			{
			    if(!response) return 1;
			    new idx = GetPlayerListitemValue(playerid, listitem) + 1;
			    SetPVarInt(playerid, "ownablekiosk_id", idx);
			    new kiosk_id = idx;
			    if(kiosk_id != -1)
				{
					IntfDialogCallRemote
					(
						playerid, DIALOG_KIOSK_SELL, DIALOG_STYLE_MSGBOX,
						"{FFCD00}Продажа киоска",
						"{FFFFFF}Вы уверены что хотите продать свой киоск государству?\n\n"\
						"Вам будет возвращено его стоимость за вычитом 30%\n"\
						"Также будет возвращено 60% от стоимости купленных улучшений\n\n"\
						"Если Вы хотите продать киоск другому игроку,\n"\
						"используйте команду /sellmystall",
						"Да", "Нет"
					);
				}
			}
			case DIALOG_GARAGE_SELL:
			{
				new garage_id = GetPVarInt(playerid, "ownablegarage_id");
				if(garage_id != -1)
				{
					if(response)
					{
						SellGarage(playerid);
					}
				}
			}
			case DIALOG_GARAGE_INFO:
			{
				if(response)
				{
					new garage_id = GetPVarInt(playerid, "ownablegarage_id");
					if(garage_id != -1)
					{
						ShowPlayerGarageDialog(playerid, GARAGE_OPERATION_PARAMS);
					}
				}
			}
			case DIALOG_GARAGE_ZAEZD:
			{
				new garage_id = GetPlayerUseListitem(playerid);

				if(garage_id >= 0 && response)
				{
					if(!GetGarageData(garage_id, G_LOCK_STATUS))
					{
						ZaezdPlayerToGarage(playerid, garage_id);
					}
					else GameText(playerid, "~r~Закрыт", 3000, 2);
				}
			}
			case DIALOG_GARAGE_PARAMS:
			{
				new garage_id = GetPVarInt(playerid, "ownablegarage_id");
				if(garage_id != -1)
				{
					if(response)
					{
						ShowPlayerGarageDialog(playerid, listitem + 1);
					}
					else callcmd::garage(playerid, "");
				}
			}
			case DIALOG_GARAGE_IMPROVEMENTS:
			{
				new garage_id = GetPVarInt(playerid, "ownablegarage_id");

			    if(response)
			    {
					switch(listitem + 1)
					{
					    case 1:
					    {
					        if(GetGarageData(garage_id, G_IMPROVEMENTS) > 0) return SendClientMessage(playerid, 0xFF6600FF, "Данное улучшение уже куплено");

					        if(!VerifyIntString(QueryPlayerBalance(playerid), 55000)) return SendClientMessage(playerid, 0xFF6600FF, "У Вас недостаточно средств");

							SetGarageData(garage_id, G_IMPROVEMENTS, 1);

							new query[75];
							mysql_format(mysql, query, sizeof query, "UPDATE `garage` SET `improvements`=%d WHERE `id`=%d LIMIT 1", GetGarageData(garage_id, G_IMPROVEMENTS), GetGarageData(garage_id, G_SQL_ID));
							mysql_query(mysql, query, false);

							SendClientMessage(playerid, 0x3399FFFF, "Вы улучшили свой гараж до {FFCD00}первого {3399FF}уровня");
                            SendClientMessage(playerid, 0x66CC00FF, "На Ваше имя была оформлена субсидия, которая дает право платить пониженную арендную плату");
							SendClientMessage(playerid, 0x999999FF, "Благодаря этому, ежедневная арендная плата уменьшена в 2 раза");

							ModifyCashBalance(playerid, -55000, "Улучшение гаража", true, true);
					    }
						case 2:
					    {
							if(GetGarageData(garage_id, G_IMPROVEMENTS) == 0) return SendClientMessage(playerid, 0xFF6600FF, "Сначало купите 1 уровень улучшения");
					        if(GetGarageData(garage_id, G_IMPROVEMENTS) > 1) return SendClientMessage(playerid, 0xFF6600FF, "Данное улучшение уже куплено");

					        if(!VerifyIntString(QueryPlayerBalance(playerid), 200000)) return SendClientMessage(playerid, 0xFF6600FF, "У Вас недостаточно средств");

							SetGarageData(garage_id, G_IMPROVEMENTS, 2);

							new query[75];
							mysql_format(mysql, query, sizeof query, "UPDATE `garage` SET `improvements`=%d WHERE `id`=%d LIMIT 1", GetGarageData(garage_id, G_IMPROVEMENTS), GetGarageData(garage_id, G_SQL_ID));
							mysql_query(mysql, query, false);

							SetGarageData(garage_id, G_WORKBENCH_LABEL, CreateDynamic3DTextLabel("{CB9E3A}Верстак\n{FFFFFF}Подойдите для взаимодействия", COLOR_GOLD, g_garage_pos_workbench[GetGarageData(garage_id, G_TYPE)-1][0],g_garage_pos_workbench[GetGarageData(garage_id, G_TYPE)-1][1],g_garage_pos_workbench[GetGarageData(garage_id, G_TYPE)-1][2] + 0.5, 6.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, garage_id + 2000, -1, -1, 50.0));

							SendClientMessage(playerid, 0x3399FFFF, "Вы улучшили свой гараж до {FFCD00}второго {3399FF}уровня");
							SendClientMessage(playerid, 0x66CC00FF, "В вашем гараже появился верстак. Используйте его для крафта.");

							ModifyCashBalance(playerid, -200000, "Улучшение гаража", true, true);
					    }
						case 3:
					    {
							if(GetGarageData(garage_id, G_IMPROVEMENTS) < 2) return SendClientMessage(playerid, 0xFF6600FF, "Сначало купите 2 уровень улучшения");
					        if(GetGarageData(garage_id, G_IMPROVEMENTS) > 2) return SendClientMessage(playerid, 0xFF6600FF, "Данное улучшение уже куплено");

					        if(!VerifyIntString(QueryPlayerBalance(playerid), 300000)) return SendClientMessage(playerid, 0xFF6600FF, "У Вас недостаточно средств");

							SetGarageData(garage_id, G_IMPROVEMENTS, 3);

							new query[75];
							mysql_format(mysql, query, sizeof query, "UPDATE `garage` SET `improvements`=%d WHERE `id`=%d LIMIT 1", GetGarageData(garage_id, G_IMPROVEMENTS), GetGarageData(garage_id, G_SQL_ID));
							mysql_query(mysql, query, false);

							new plate = GetGarageData(garage_id, G_PLATE_OBJECT);
                            if(!IsValidDynamicObject(plate))
		                    {
                                switch(GetGarageData(garage_id, G_TYPE))
			                    {
                                    case 1: plate = CreateDynamicObject(16931, -1611.69, 1578.99, 2006.93, 0.00, 0.00, 90.00, garage_id + 2000);
                                    case 2: plate = CreateDynamicObject(16930, 2892.99, 2891.19, 1001.50, 0.00, 0.00, 90.00, garage_id + 2000);
				                    case 3: plate = CreateDynamicObject(16929, -1667.14, -460.44, 1001.76, 0.00, 0.00, 90.00, garage_id + 2000);
                                }
                                SetGarageData(garage_id, G_PLATE_OBJECT, plate);
		                    }

							SendClientMessage(playerid, 0x3399FFFF, "Вы улучшили свой гараж до {FFCD00}третьего {3399FF}уровня");
							SendClientMessage(playerid, 0x66CC00FF, "Вы приобрели доску для номерных знаков, подойдите к ней, чтобы воспользоваться.");

							ModifyCashBalance(playerid, -300000, "Улучшение гаража", true, true);
					    }
					}
				}
				else callcmd::garage(playerid, "");

			}
			case DIALOG_GARAGE_ENTER:
			{
				new garage_id = GetPlayerUseListitem(playerid);

				if(garage_id >= 0 && response)
				{
					if(!GetGarageData(garage_id, G_LOCK_STATUS))
					{
						EnterPlayerToGarage(playerid, garage_id);
					}
					else GameText(playerid, "~r~Закрыт", 3000, 2);
				}
			}
			case DIALOG_BANK_ACCOUNTS:
			{
				if(response)
				{
					switch(listitem)
					{
						case 0: ShowPlayerATMDialog(playerid);
						case 1..(MAX_BANK_ACCOUNTS):
						{
							new accountid = GetPlayerListitemValue(playerid, listitem - 1);
							if(IsValidBankAccount(playerid, accountid))
							{
								SetPlayerUseListitem(playerid, accountid);
								IntfDialogCallRemote
								(
									playerid, DIALOG_BANK_ACCOUNT_LOGIN, DIALOG_STYLE_PASSWORD,
									"{FFD83D}Авторизация",
									"{FFFFFF}Введите PIN-код счета:",
									"Ввести", "Отмена"
								);
							}
						}
					}
				}
				else ShowPlayerBankDialog(playerid);
			}
			case DIALOG_BANK_ACCOUNT_LOGIN:
			{
				if(response)
				{
					new accountid = GetPlayerUseListitem(playerid);
					if(IsValidBankAccount(playerid, accountid))
					{
						new len = strlen(inputtext);
						new pin_len = strlen(GetBankAccountData(playerid, accountid, BA_PIN_CODE));
						if(!strcmp(GetBankAccountData(playerid, accountid, BA_PIN_CODE), inputtext, false) && pin_len && len)
						{
							ShowPlayerBankAccountOperation(playerid);
						}
						else
						{
							IntfDialogCallRemote
							(
								playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX,
								"{FF9900}Ошибка",
								"{FFFFFF}Вы допустили ошибку при вводе PIN-кода",
								"Закрыть", ""
							);
						}
					}
				}
			}
			case DIALOG_BANK_ACCOUNT_OPERATION:
			{
				if(response)
				{
					new accountid = GetPlayerUseListitem(playerid);
					if(IsValidBankAccount(playerid, accountid))
					{
						switch(listitem + 1)
						{
							case 1: // Информация о счете
							{
								UpdateBankAccountData(playerid, accountid);

								new fmt_str[128];
								format
								(
									fmt_str, sizeof fmt_str,
									"{FFFFFF}Номер счета:\t\t%d\n"\
									"Наименование:\t%s\n"\
									"Баланс:\t\t{00CC66}%s руб",
									GetBankAccountData(playerid, accountid, BA_ID),
									GetBankAccountData(playerid, accountid, BA_NAME),
									formatStr(GetBankAccountData(playerid, accountid, BA_BALANCE))
								);
								IntfDialogCallRemote(playerid, DIALOG_BANK_ACCOUNT_INFO, DIALOG_STYLE_MSGBOX, "{FFD83D}Информация", fmt_str, "Вернуться", "");
							}
							case 2: // История операций
							{
								ShowPlayerBankAccountLog(playerid, GetBankAccountData(playerid, accountid, BA_ID));
							}
							case 3: // Снять деньги
							{
								IntfDialogCallRemote
								(
									playerid, DIALOG_BANK_ACCOUNT_TAKE_MONEY, DIALOG_STYLE_INPUT,
									"{FFD83D}Снять деньги",
									"{FFFFFF}Укажите сумму:",
									"Снять", "Отмена"
								);
							}
							case 4: // Положить деньги
							{
								IntfDialogCallRemote
								(
									playerid, DIALOG_BANK_ACCOUNT_PUT_MONEY, DIALOG_STYLE_INPUT,
									"{FFD83D}Положить деньги",
									"{FFFFFF}Укажите сумму:",
									"Положить", "Отмена"
								);
							}
							case 5: // Перевести на другой счет
							{
								if(GetPlayerLevel(playerid) > 3)
								{
									IntfDialogCallRemote
									(
										playerid, DIALOG_BANK_ACCOUNT_TRANSFER_1, DIALOG_STYLE_INPUT,
										"{FFD83D}Перевод средств",
										"{FFFFFF}Укажите номер счета, на который\n"\
										"хотите осуществить перевод:",
										"Далее", "Отмена"
									);
								}
								else SendClientMessage(playerid, 0x999999FF, "Перевод денег доступен только со 3 уровня");
							}
							case 6: // Переименовать счет
							{
								IntfDialogCallRemote
								(
									playerid, DIALOG_BANK_ACCOUNT_CHANGE_NAME, DIALOG_STYLE_INPUT,
									"{FFD83D}Переименование счета",
									"{FFFFFF}Введите новое название для этого счета.\n"\
									"Максимальная длина 20 символов:",
									"Ок", "Отмена"
								);
							}
							case 7: // Изменить PIN-код
							{
								IntfDialogCallRemote
								(
									playerid, DIALOG_BANK_ACCOUNT_CHANGE_PIN, DIALOG_STYLE_INPUT,
									"{FFD83D}Изменение PIN-кода",
									"{FFFFFF}Введите новый PIN-код.\n"\
									"Длина от 4 до 8 цифр:",
									"Ок", "Отмена"
								);
							}
						}
					}
				}
				else ShowPlayerBankDialog(playerid);
			}
			case DIALOG_BANK_ACCOUNT_INFO:
			{
				ShowPlayerBankAccountOperation(playerid);
			}
			case DIALOG_BANK_ACCOUNT_TAKE_MONEY:
			{
				new accountid = GetPlayerUseListitem(playerid);
				if(response)
				{
					if(IsValidBankAccount(playerid, accountid))
					{
						if(IsILNumeric(inputtext))
						{
							UpdateBankAccountData(playerid, accountid);

							new fmt_str[155];
							new money_str[23];
							format(money_str, sizeof money_str, "-%s", inputtext);
							if(GetILPlayerStr(GetBankAccountData(playerid, accountid, BA_BALANCE), inputtext))
							{
								format(fmt_str, sizeof fmt_str, "UPDATE bank_accounts SET balance=%s WHERE id=%d", SetILPlayerStr(playerid, GetBankAccountData(playerid, accountid, BA_BALANCE), money_str), GetBankAccountData(playerid, accountid, BA_ID));
								mysql_query(mysql, fmt_str, false);

								if(!mysql_errno())
								{
									GivePlayerMoneyStr(playerid, inputtext, "Снятие с банк. счета (банк)");
									//SetBankAccountData(playerid, accountid, BA_BALANCE, balance - take_sum);
									format(g_bank_account[playerid][accountid][BA_BALANCE], 21, "%s", SetILPlayerStr(playerid, GetBankAccountData(playerid, accountid, BA_BALANCE), money_str));

									format(fmt_str, sizeof fmt_str, "- Снятие наличных %d руб", inputtext);
									BankAccountLog(playerid, GetBankAccountData(playerid, accountid, BA_ID), fmt_str);

									format
									(
										fmt_str, sizeof fmt_str,
										"{FFFFFF}Счет:<t><t>№%d\n"\
										"Вы сняли:<t>{FF9900}%s руб\n"\
										"{FFFFFF}Остаток:<t>%s руб",
										GetBankAccountData(playerid, accountid, BA_ID),
										formatStr(inputtext),
										formatStr(GetBankAccountData(playerid, accountid, BA_BALANCE))
									);
									return IntfDialogCallRemote(playerid, DIALOG_BANK_ACCOUNT_INFO, DIALOG_STYLE_MSGBOX, "{3399FF}Операция завершена успешно", fmt_str, "Вернуться", "");
								}
								else SendClientMessage(playerid, 0xFF6600FF, "Ошибка сохранения, повторите попытку {FF0000}(equ-code 09)");
							}
							else
							{
								format(fmt_str, sizeof fmt_str, "Недостаточно средств. Текущий баланс счета №%d: {009966}%s руб", GetBankAccountData(playerid, accountid, BA_ID), formatStr(GetBankAccountData(playerid, accountid, BA_BALANCE)));
								SendClientMessage(playerid, 0xFFFFFFFF, fmt_str);
							}
						}

						IntfDialogCallRemote
						(
							playerid, DIALOG_BANK_ACCOUNT_TAKE_MONEY, DIALOG_STYLE_INPUT,
							"{FFD83D}Снять деньги",
							"{FFFFFF}Укажите сумму:",
							"Снять", "Отмена"
						);
					}
				}
				else ShowPlayerBankAccountOperation(playerid);
			}
			case DIALOG_BANK_ACCOUNT_PUT_MONEY:
			{
				new accountid = GetPlayerUseListitem(playerid);
				if(response)
				{
					if(IsValidBankAccount(playerid, accountid))
					{
						if(IsILNumeric(inputtext))
						{
							UpdateBankAccountData(playerid, accountid);

							new fmt_str[155];

							new money_str[23];
							format(money_str, sizeof money_str, "-%s", inputtext);

							if(GetILPlayerStr(QueryPlayerBalance(playerid), inputtext))
							{
								format(fmt_str, sizeof fmt_str, "UPDATE bank_accounts SET balance=%s WHERE id=%d", SetILPlayerStr(playerid, GetBankAccountData(playerid, accountid, BA_BALANCE), inputtext), GetBankAccountData(playerid, accountid, BA_ID));
								mysql_query(mysql, fmt_str, false);

								if(!mysql_errno())
								{
									GivePlayerMoneyStr(playerid, money_str, "Пополнение банк. счета (банк)");
					
									format(g_bank_account[playerid][accountid][BA_BALANCE], 21, "%s", SetILPlayerStr(playerid, GetBankAccountData(playerid, accountid, BA_BALANCE), inputtext));

									format(fmt_str, sizeof fmt_str, "+ Пополнение на сумму %d руб", inputtext);
									BankAccountLog(playerid, GetBankAccountData(playerid, accountid, BA_ID), fmt_str);

									format
									(
										fmt_str, sizeof fmt_str,
										"{FFFFFF}Счет:\t\t\t№%d\n"\
										"Вы положили:\t{00CC00}%s руб\n"\
										"{FFFFFF}Итоговый баланс:\t%s руб",
										GetBankAccountData(playerid, accountid, BA_ID),
										formatStr(inputtext),
										formatStr(GetBankAccountData(playerid, accountid, BA_BALANCE))
									);
									return IntfDialogCallRemote(playerid, DIALOG_BANK_ACCOUNT_INFO, DIALOG_STYLE_MSGBOX, "{3399FF}Операция завершена успешно", fmt_str, "Вернуться", "");
								}
								else SendClientMessage(playerid, 0xFF6600FF, "Ошибка сохранения, повторите попытку {FF0000}(equ-code 09)");
							}
							else SendClientMessage(playerid, 0xFFFFFFFF, "Недостаточно средств");
						}

						IntfDialogCallRemote
						(
							playerid, DIALOG_BANK_ACCOUNT_PUT_MONEY, DIALOG_STYLE_INPUT,
							"{FFD83D}Положить деньги",
							"{FFFFFF}Укажите сумму:",
							"Положить", "Отмена"
						);
					}
				}
				else ShowPlayerBankAccountOperation(playerid);
			}
			case DIALOG_BANK_ACCOUNT_TRANSFER_1:
			{
				new accountid = GetPlayerUseListitem(playerid);
				if(response)
				{
					if(IsValidBankAccount(playerid, accountid))
					{
						new transfer_id = strval(inputtext);
						if(transfer_id > 0 && IsNumeric(inputtext))
						{
							new fmt_str[64 + 1];
							new Cache: result;
							new rows;

							format(fmt_str, sizeof fmt_str, "SELECT id,name,uid FROM bank_accounts WHERE id=%d LIMIT 1", transfer_id);
							result = mysql_query(mysql, fmt_str);

							if((rows = cache_num_rows()))
							{
								SetPlayerBankTransfer(playerid, BT_ID, cache_get_row_int(0, 0));
								SetPlayerBankTransfer(playerid, BT_UID, cache_get_row_int(0, 2));
								cache_get_row(0, 1, g_player_bank_transfer[playerid][BT_NAME], mysql, 21);
							}
							cache_delete(result);

							if(rows)
							{
								new to_player = GetPlayerIDBySqlID(GetPlayerBankTransfer(playerid, BT_UID));

								if(IsPlayerConnected(to_player) && IsPlayerLogged(to_player))
								{
									if(GetBankAccountData(playerid, accountid, BA_ID) != GetPlayerBankTransfer(playerid, BT_ID)) return ShowPlayerBankAccountTransfer(playerid, accountid);
									else return SCM(playerid, 0xc7590fFF, "Вы не можете совершить перевод на один и тот же счет.");
								}
								else SCM(playerid, 0xc7590fFF, "Владелец счета должен находиться на сервере.");
							}
							else SendClientMessage(playerid, 0xFF6600FF, "Счета с таким номером не существует");
						}

						IntfDialogCallRemote
						(
							playerid, DIALOG_BANK_ACCOUNT_TRANSFER_1, DIALOG_STYLE_INPUT,
							"{FFD83D}Перевод средств",
							"{FFFFFF}Укажите номер счета, на который\n"\
							"хотите осуществить перевод:",
							"Далее", "Отмена"
						);
					}
				}
				else ShowPlayerBankAccountOperation(playerid);
			}
			case DIALOG_BANK_ACCOUNT_TRANSFER_2:
			{
				new accountid = GetPlayerUseListitem(playerid);
				if(response)
				{
					if(IsValidBankAccount(playerid, accountid))
					{
						new transfer_sum = strval(inputtext);
						new transfer_id = GetPlayerBankTransfer(playerid, BT_ID);
						
						new to_player = GetPlayerIDBySqlID(GetPlayerBankTransfer(playerid, BT_UID));

						if(!IsPlayerConnected(to_player) || !IsPlayerLogged(to_player)) return SCM(playerid, 0xc7590fFF, "Владелец счета должен находиться на сервере."), ShowPlayerATMTransfer(playerid);

						if(!GetILPlayerStr("2000000000", inputtext)) return SCM(playerid, COLOR_GREY, "Перевод доступен до 2.000.000.000 руб за один раз"), ShowPlayerATMTransfer(playerid);

						if(transfer_sum > 0 && IsILNumeric(inputtext))
						{
							//UpdateBankAccountData(playerid, accountid);

							//new balance = GetBankAccountData(playerid, accountid, BA_BALANCE);
							if(VerifyIntString(GetBankAccountData(playerid, accountid, BA_BALANCE), transfer_sum))
							{
								new fmt_str[160];

								if(GetBankAccountData(playerid, accountid, BA_ID) != transfer_id)
								{
									format(fmt_str, sizeof fmt_str, "UPDATE bank_accounts SET balance=%s WHERE id=%d LIMIT 1", SetILPlayerInt(playerid, GetBankAccountData(playerid, accountid, BA_BALANCE), -transfer_sum), GetBankAccountData(playerid, accountid, BA_ID));
									mysql_query(mysql, fmt_str, false);

									format(fmt_str, sizeof fmt_str, "UPDATE bank_accounts SET balance=%s WHERE id=%d LIMIT 1", SetILPlayerInt(playerid, GetBankAccountBalance(transfer_id), transfer_sum / 100 * 80), transfer_id);
									mysql_query(mysql, fmt_str, false);

									//SetBankAccountData(playerid, accountid, BA_BALANCE, balance - transfer_sum);
									format(g_bank_account[playerid][accountid][BA_BALANCE], 21, "%s", SetILPlayerInt(playerid, GetBankAccountData(playerid, accountid, BA_BALANCE), -transfer_sum));

									format(g_bank_account[to_player][transfer_id][BA_BALANCE], 21, "%s", SetILPlayerInt(playerid, GetBankAccountBalance(transfer_id), transfer_sum / 100 * 80));
								}
								format(fmt_str, sizeof fmt_str, "- Перевод %d руб на счет №%d", transfer_sum / 100 * 80, transfer_id);
								BankAccountLog(playerid, GetBankAccountData(playerid, accountid, BA_ID), fmt_str);

								format(fmt_str, sizeof fmt_str, "+ Перевод %d руб со счета №%d", transfer_sum, GetBankAccountData(playerid, accountid, BA_ID));
								BankAccountLog(playerid, transfer_id, fmt_str);

								SetPlayerBankTransfer(playerid, BT_ID, 0);

								format
								(
									fmt_str, sizeof fmt_str,
									"{FFFFFF}Со счета:\t\t\t№%d\n"\
									"На счет:\t\t\t№%d\n"\
									"Cумма перевода:\t\t{FF9900}%s руб\n"\
									"{3caa3c}Коммисия:\t\t\t\t%s руб\n"\
									"{FFFFFF}Остаток на Вашем счете:\t{00CC66}%s руб",
									GetBankAccountData(playerid, accountid, BA_ID),
									transfer_id,
									formatInt(transfer_sum / 100 * 80),
									formatInt(transfer_sum / 100 * 20),
									formatStr(GetBankAccountData(playerid, accountid, BA_BALANCE))
								);
								IntfDialogCallRemote(playerid, DIALOG_BANK_ACCOUNT_INFO, DIALOG_STYLE_MSGBOX, "{3399FF}Перевод успешно выполнен", fmt_str, "Вернуться", "");

								new businessid = GetPlayerInBiz(playerid);

								AddBusinessProfit(playerid, businessid, transfer_sum / 100 * 20, 0);
							}
							else
							{
								SendClientMessage(playerid, 0xFF6600FF, "На счету недостаточно средств для перевода");
								ShowPlayerBankAccountTransfer(playerid, accountid);
							}
						}
						else ShowPlayerBankAccountTransfer(playerid, accountid);
					}
				}
				else ShowPlayerBankAccountOperation(playerid);
			}
			case DIALOG_BANK_ACCOUNT_CHANGE_NAME:
			{
				new accountid = GetPlayerUseListitem(playerid);
				if(response)
				{
					if(IsValidBankAccount(playerid, accountid))
					{
						new len = strlen(inputtext);

						if(3 <= len <= 20)
						{
							if(!IsABadBankAccountName(inputtext))
							{
								new fmt_str[128];

								mysql_format(mysql, fmt_str, sizeof fmt_str, "UPDATE bank_accounts SET name='%e' WHERE id=%d LIMIT 1", inputtext, GetBankAccountData(playerid, accountid, BA_ID));
								mysql_query(mysql, fmt_str, false);

								if(!mysql_errno())
								{
									format(g_bank_account[playerid][accountid][BA_NAME], 21, "%s", inputtext);

									format(fmt_str, sizeof fmt_str, "* Переименование счета на %s", inputtext);
									BankAccountLog(playerid, GetBankAccountData(playerid, accountid, BA_ID), fmt_str);

									format
									(
										fmt_str, sizeof fmt_str,
										"{FFFFFF}Счет успешно переименован.\n"\
										"Теперь он будет доступен под названием %s",
										GetBankAccountData(playerid, accountid, BA_NAME)
									);
									return IntfDialogCallRemote(playerid, DIALOG_BANK_ACCOUNT_INFO, DIALOG_STYLE_MSGBOX, "{FFD83D}Завершение", fmt_str, "Вернуться", "");
								}
								else SendClientMessage(playerid, 0xFF6600FF, "Ошибка сохранения, повторите попытку {FF0000}(equ-code 10)");
							}
							else
							{
								SendClientMessage(playerid, 0xFF6600FF, "Недопустимые символы в новом названии");
								SendClientMessage(playerid, 0xFF6600FF, "Можно использовать {FFCC15}русские {FF6600}и {FFCC15}английские {FF6600}буквы, а также {FFCC15}цифры");
							}
						}
						else SendClientMessage(playerid, 0xFF6600FF, "Длина названия счета может быть от {FFCC15}3 до 20 {FF6600}символов");

						IntfDialogCallRemote
						(
							playerid, DIALOG_BANK_ACCOUNT_CHANGE_NAME, DIALOG_STYLE_INPUT,
							"{FFD83D}Переименование счета",
							"{FFFFFF}Введите новое название для этого счета.\n"\
							"Максимальная длина 20 символов:",
							"Ок", "Отмена"
						);
					}
				}
				else ShowPlayerBankAccountOperation(playerid);
			}
			case DIALOG_BANK_ACCOUNT_CHANGE_PIN:
			{
				new accountid = GetPlayerUseListitem(playerid);
				if(response)
				{
					if(IsValidBankAccount(playerid, accountid))
					{
						new len = strlen(inputtext);

						if(4 <= len <= 8 && IsNumeric(inputtext))
						{
							new fmt_str[128];

							mysql_format(mysql, fmt_str, sizeof fmt_str, "UPDATE bank_accounts SET pin='%e' WHERE id=%d LIMIT 1", inputtext, GetBankAccountData(playerid, accountid, BA_ID));
							mysql_query(mysql, fmt_str, false);

							if(!mysql_errno())
							{
								format(g_bank_account[playerid][accountid][BA_PIN_CODE], 9, "%s", inputtext);
								BankAccountLog(playerid, GetBankAccountData(playerid, accountid, BA_ID), "* Изменение PIN-кода");

								format
								(
									fmt_str, sizeof fmt_str,
									"{FFFFFF}PIN-код успешно изменен.\n"\
									"Рекомендуем сделать скрин (F8) чтобы не забыть его: {CCFF00}%s",
									GetBankAccountData(playerid, accountid, BA_PIN_CODE)
								);
								return IntfDialogCallRemote(playerid, DIALOG_BANK_ACCOUNT_INFO, DIALOG_STYLE_MSGBOX, "{FFD83D}Изменение PIN", fmt_str, "Вернуться", "");
							}
							else SendClientMessage(playerid, 0xFF6600FF, "Ошибка сохранения, повторите попытку {FF0000}(equ-code 10)");
						}

						IntfDialogCallRemote
						(
							playerid, DIALOG_BANK_ACCOUNT_CHANGE_PIN, DIALOG_STYLE_INPUT,
							"{FFD83D}Изменение PIN-кода",
							"{FFFFFF}Введите новый PIN-код.\n"\
							"Длина от 4 до 8 цифр:",
							"Ок", "Отмена"
						);
					}
				}
				else ShowPlayerBankAccountOperation(playerid);
			}
			case DIALOG_RAZDEVALKA:
			{
				if(!response) return 1;
				if(GetPlayerSkin(playerid) == GetPlayerData(playerid, P_OSKIN))
				{
					SetPlayerSkin(playerid, GetPlayerData(playerid, P_SKIN));
					SendClientMessage(playerid, -1, "Вы успешно сняли рабочую форму");
				}
				else
				{
					SetPlayerSkin(playerid, GetPlayerData(playerid, P_OSKIN));
					SendClientMessage(playerid, -1, "Вы успешно надели рабочую форму");
				}
			}
			case DIALOG_ARENDA_STOP:
            {
                if(!response) return 1;

				new garden = GetNearestGarden(playerid, 7.0);
	            if(garden != -1)
	            {
					new strafsum = GetGardenData(garden, G_ARENDA_PRICE);
					new orend_id = GetGardenData(garden, G_OREND_ID);

					new query[367];

	                if(!VerifyIntString(QueryPlayerBalance(playerid), strafsum))
		                return SendClientMessage(playerid, 0x999999FF, "Недостаточно средств.");

                    format(query, sizeof query, "UPDATE accounts_canvasdev SET bank = bank + %d WHERE id=%d LIMIT 1", strafsum, orend_id);
				    mysql_query(mysql, query, false);

					ModifyCashBalance(playerid, -strafsum, "штраф за прекращение аренды гардена", true, true);

					SendClientMessage(playerid, 0xB8CEF6FF, "Аренда огорода завершена досрочно.");

				    SetGardenData(garden, G_OREND_ID, 0);
                    SetGardenData(garden, G_ARENDA_TIME, 0);
					SetGardenData(garden, G_ARENDA_PRICE, 0);

	                format(query, sizeof query, "UPDATE gardens SET orend_id=%d,arenda_time=%d,arenda_price=%d WHERE id=%d", GetGardenData(garden, G_OREND_ID), GetGardenData(garden, G_ARENDA_TIME), GetGardenData(garden, G_ARENDA_PRICE), GetGardenData(garden, G_SQL_ID));
	                mysql_query(mysql, query, false);
				}
			}
			case DIALOG_ARENDA_STOP_2:
            {
                if(!response) return 1;

				new garden = GetNearestGarden(playerid, 7.0);
	            if(garden != -1)
	            {
					new query[367];

				    SetGardenData(garden, G_OREND_ID, 0);
                    SetGardenData(garden, G_ARENDA_TIME, 0);
					SetGardenData(garden, G_ARENDA_PRICE, 0);

	                format(query, sizeof query, "UPDATE gardens SET orend_id=%d,arenda_time=%d,arenda_price=%d WHERE id=%d", GetGardenData(garden, G_OREND_ID), GetGardenData(garden, G_ARENDA_TIME), GetGardenData(garden, G_ARENDA_PRICE), GetGardenData(garden, G_SQL_ID));
	                mysql_query(mysql, query, false);
				}
			}
			case DIALOG_SEND_ORENDA_GARDEN:
            {
                if(!response) return 1;

                new targetid, hours, price;

                if(sscanf(inputtext, "iii", targetid, hours, price))
                    return 1;

                if(!IsPlayerConnected(targetid)) 
                    return SCM(playerid, 0xead671FF, "Игрок оффлайн.");

				if(targetid == playerid)
		            return SCM(playerid, 0xead671FF, "Вы не сможете сдать в аренду огород самому себе.");

				if(!IsPlayerInRangeOfPlayer(playerid, targetid, 7.0)) return SCM(playerid, 0xead671FF, "Вы находитесь далеко друг от друга.");

                if(hours < 2 || hours > 168) 
                    return SCM(playerid, 0xead671FF, "Вы не сможете сдать в аренду огород меньше чем на 2ч. и больше чем на 168 ч.");
    
                new minPrice = 500000, maxPrice = 20000000;

                if(price < minPrice || price > maxPrice)
                    return SCM(playerid, 0xead671FF, "Доступный диапазон стоимости аренды за один час от 500000 до 20000000 руб.");

                new garden = GetNearestGarden(playerid, 7.0);
                if(garden != -1)
                {
                    if(GetGardenData(garden, G_OWNER_ID) == GetPlayerAccountID(playerid))
                    {
                        SendPlayerOffer(playerid, targetid, OFFER_TYPE_ARENDA_GARDEN, garden, hours, price);
                    }
                }
            }
			case DIALOG_SKIN_MANSION:
			{
				if(!response) return 1;
				
				new fam_id = GetPlayerData(playerid, P_FAMILY);

                if(GetFamilyData(fam_id, F_CENTRAL_MANSION) == 1) 
                {
			 	    switch(listitem + 1)
				    {
					    case 1: SetPlayerSkin(playerid, GetPlayerData(playerid, P_SKIN));
					    case 2: SetPlayerSkin(playerid, 111), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:111");
					    case 3: SetPlayerSkin(playerid, 112), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:112");
					    case 4: SetPlayerSkin(playerid, 117), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:117");
					    case 5: SetPlayerSkin(playerid, 125), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:125");
					    case 6: SetPlayerSkin(playerid, 15459), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:15459");
					    case 7: SetPlayerSkin(playerid, 15460), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:15460");
						case 8: SetPlayerSkin(playerid, 15461), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:15461");
						case 9: SetPlayerSkin(playerid, 15462), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:15462");
						case 10: SetPlayerSkin(playerid, 15463), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:15463");
						case 11: SetPlayerSkin(playerid, 15464), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:15464");
					}
				}
                if(GetFamilyData(fam_id, F_WEST_MANSION) == 1) 
                {
			 	    switch(listitem + 1)
				    {
					    case 1: SetPlayerSkin(playerid, GetPlayerData(playerid, P_SKIN));
					    case 2: SetPlayerSkin(playerid, 124), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:124");
					    case 3: SetPlayerSkin(playerid, 126), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:126");
					    case 4: SetPlayerSkin(playerid, 127), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:127");
					    case 5: SetPlayerSkin(playerid, 15474), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:15474");
					    case 6: SetPlayerSkin(playerid, 161), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:161");
					    case 7: SetPlayerSkin(playerid, 114), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:114");
						case 8: SetPlayerSkin(playerid, 15451), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:15451");
						case 9: SetPlayerSkin(playerid, 15450), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:15450");
						case 10: SetPlayerSkin(playerid, 163), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:163");
					}
				}
                if(GetFamilyData(fam_id, F_NORTH_MANSION) == 1) 
                {
			 	    switch(listitem + 1)
				    {
					    case 1: SetPlayerSkin(playerid, GetPlayerData(playerid, P_SKIN));
					    case 2: SetPlayerSkin(playerid, 121), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:121");
					    case 3: SetPlayerSkin(playerid, 122), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:122");
					    case 4: SetPlayerSkin(playerid, 123), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:123");
					    case 5: SetPlayerSkin(playerid, 15465), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:15465");
					    case 6: SetPlayerSkin(playerid, 15467), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:15467");
					    case 7: SetPlayerSkin(playerid, 15466), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:15466");
						case 8: SetPlayerSkin(playerid, 120), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:120");
						case 9: SetPlayerSkin(playerid, 15472), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:15472");
						case 10: SetPlayerSkin(playerid, 15473), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:15473");
						case 11: SetPlayerSkin(playerid, 15468), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:15468");
					}
				}
                if(GetFamilyData(fam_id, F_PELA_BASE) == 1) 
                {
				    switch(listitem + 1)
				    {
					    case 1: SetPlayerSkin(playerid, GetPlayerData(playerid, P_SKIN));
					    case 2: SetPlayerSkin(playerid, 15407), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:15407");
					    case 3: SetPlayerSkin(playerid, 15406), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:15406");
					    case 4: SetPlayerSkin(playerid, 15424), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:15424");
					    case 5: SetPlayerSkin(playerid, 15425), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:15425");
					    case 6: SetPlayerSkin(playerid, 15448), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:15448");
					    case 7: SetPlayerSkin(playerid, 15486), SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в одежду №:15486");
					}
				}
			}
			case DIALOG_RAFFLE_SHOP:
		    {
			    if(!response) return 1;

			    for(new i; i < sizeof g_raffleShop; i++)
			    {
				    if(!IsPlayerInRangeOfPoint(playerid, 4.5, g_pos_car_raffle[i][0],g_pos_car_raffle[i][1],g_pos_car_raffle[i][2])) continue;

                    if(!VerifyIntString(QueryPlayerBalance(playerid), g_info_raffleshopping[g_raffleShop[i][RS_ID]][IRS_PRICE]))
		                return SendClientMessage(playerid, 0x999999FF, "Недостаточно средств.");

					ModifyCashBalance(playerid, -g_info_raffleshopping[g_raffleShop[i][RS_ID]][IRS_PRICE], "Покупка билета в тц", true, true);

				    new query[94];
				    format(query, sizeof query, "INSERT INTO raffle_shop (owner_id, type, ticket_id) VALUES (%d, %d, %d)", GetPlayerAccountID(playerid), i, g_raffleShop[i][RS_TICKETS]);
				    mysql_query(mysql, query, false);

				    g_raffleShop[i][RS_TICKETS]++;
			    }
		    }
			case DIALOG_BUY_LIC:
			{
				switch(listitem + 1)
				{
					case 1: 
					{
						IntfDialogCallRemote
						(
							playerid, DIALOG_BUY_DRIVING_LIC, DIALOG_STYLE_MSGBOX,
							"{FFFFFF}Подтверждение",
							"{FFFFFF}Название: {ffa500}'Водительские права'\n"\
							"{FFFFFF}Стоимость: {ffd700}150.000 руб\n\n"\
							"{FFFFFF}Вы действительно хотите приобрести лицензию?",
							"Купить", "Отмена"
						);
					}
					case 2: 
					{
						IntfDialogCallRemote
						(
							playerid, DIALOG_BUY_GUN_LIC, DIALOG_STYLE_MSGBOX,
							"{FFFFFF}Подтверждение",
							"{FFFFFF}Название: {ffa500}'Разрешение на оружие'\n"\
							"{FFFFFF}Стоимость: {ffd700}350.000 руб\n\n"\
							"{FFFFFF}Вы действительно хотите приобрести лицензию?",
							"Купить", "Отмена"
						);
					}
					case 3:
					{
						IntfDialogCallRemote
						(
							playerid, DIALOG_BUY_DRIVING_LIC_2, DIALOG_STYLE_MSGBOX,
							"{FFFFFF}Подтверждение",
							"{FFFFFF}Название: {ffa500}'Проф. права'\n"\
							"{FFFFFF}Стоимость: {ffd700}200.000 руб\n\n"\
							"{FFFFFF}Вы действительно хотите приобрести лицензию?",
							"Купить", "Отмена"
						);
					}
				}
				if(!response) return 1;
			}
			case DIALOG_BUY_DRIVING_LIC_2:
			{
				if(!response) return 1;

				if(!VerifyIntString(QueryPlayerBalance(playerid), 200000)) return SCM(playerid, -1, "*У вас недостаточно средств.");

				if(GetPlayerData(playerid, P_DRIVING_LIC) == 2) return SendClientMessage(playerid, 0x999999FF, "У вас уже есть лицензия на вождение профессионального уровня");

				ModifyCashBalance(playerid, -200000);

				SetPlayerData(playerid, P_DRIVING_LIC, 2);
				UpdatePlayerDatabaseInt(playerid, "driving_lic", GetPlayerData(playerid, P_DRIVING_LIC));

				SendClientMessage(playerid, COLOR_GREY, "Вы успешно приобрели лицензию \"Проф. права\"");
			}
			case DIALOG_BUY_GUN_LIC:
			{
				if(!response) return 1;

				if(!VerifyIntString(QueryPlayerBalance(playerid), 350000)) return SCM(playerid, -1, "*У вас недостаточно средств.");

				if(GetPlayerData(playerid, P_WEAPON_LIC) == 1) return SendClientMessage(playerid, 0x999999FF, "У вас уже есть лицензия на оружие");

				ModifyCashBalance(playerid, -350000);

				SendClientMessage(playerid, COLOR_GREY, "Вы успешно приобрели лицензию \"Разрешение на оружие\"");

				SetPlayerData(playerid, P_WEAPON_LIC, 1);
				UpdatePlayerDatabaseInt(playerid, "weapon_lic", GetPlayerData(playerid, P_WEAPON_LIC));
			}
			case DIALOG_BUY_DRIVING_LIC:
			{
				if(!response) return 1;

				if(!VerifyIntString(QueryPlayerBalance(playerid), 150000)) return SCM(playerid, -1, "*У вас недостаточно средств.");

				if(GetPlayerData(playerid, P_DRIVING_LIC) >= 1) return SendClientMessage(playerid, 0x999999FF, "У вас уже есть водительское удостоверение");

				ModifyCashBalance(playerid, -150000);

				SetPlayerData(playerid, P_DRIVING_LIC, 1);
				UpdatePlayerDatabaseInt(playerid, "driving_lic", GetPlayerData(playerid, P_DRIVING_LIC));

				SendClientMessage(playerid, COLOR_GREY, "Вы успешно приобрели лицензию \"Водительские права\"");
			}
			case DIALOG_QUEST_END:
			{
				if(response)
				{
				    if(GetPVarInt(playerid, "quest") == 1)
				    {
				        CEF_HIDE(playerid, "QuestsProgressInfo");
				        SetPVarInt(playerid, "quest", 0);
						GiveIteam(playerid, 252, 0, 1, 0);
						SetPlayerData(playerid, P_QUEST_1_STATS, 0);
			            UpdatePlayerDatabaseInt(playerid, "quest_1_stats", GetPlayerData(playerid, P_QUEST_1_STATS));
						LoadMainMenu(playerid, MENU_MAIN_TASKS);
				    }
					if(GetPVarInt(playerid, "quest") == 2)
				    {
				        CEF_HIDE(playerid, "QuestsProgressInfo");
				        SetPVarInt(playerid, "quest", 0);
						SetPlayerData(playerid, P_QUEST_2_STATS, 0);
			            UpdatePlayerDatabaseInt(playerid, "quest_2_stats", GetPlayerData(playerid, P_QUEST_2_STATS));
						LoadMainMenu(playerid, MENU_MAIN_TASKS);
				    }
					if(GetPVarInt(playerid, "quest") == 3)
				    {
				        CEF_HIDE(playerid, "QuestsProgressInfo");
				        SetPVarInt(playerid, "quest", 0);
						SetPlayerData(playerid, P_QUEST_3_STATS, 0);
			            UpdatePlayerDatabaseInt(playerid, "quest_3_stats", GetPlayerData(playerid, P_QUEST_3_STATS));
						LoadMainMenu(playerid, MENU_MAIN_TASKS);
				    }
					if(GetPVarInt(playerid, "quest") == 4)
				    {
				        CEF_HIDE(playerid, "QuestsProgressInfo");
				        SetPVarInt(playerid, "quest", 0);
						SetPlayerData(playerid, P_QUEST_6_STATS, 0);
			            UpdatePlayerDatabaseInt(playerid, "quest_6_stats", GetPlayerData(playerid, P_QUEST_6_STATS));
						LoadMainMenu(playerid, MENU_MAIN_TASKS);
				    }
					if(GetPVarInt(playerid, "quest") == 5)
				    {
				        CEF_HIDE(playerid, "QuestsProgressInfo");
				        SetPVarInt(playerid, "quest", 0);
						SetPlayerData(playerid, P_QUEST_7_STATS, 0);
			            UpdatePlayerDatabaseInt(playerid, "quest_7_stats", GetPlayerData(playerid, P_QUEST_7_STATS));
						LoadMainMenu(playerid, MENU_MAIN_TASKS);
				    }
				}
			}
			case DIALOG_PC_MOBILE:
			{
				if(response){
                    SetPlayerData(playerid, P_MOBILE, 0);
	                UpdatePlayerDatabaseInt(playerid, "mobile", GetPlayerData(playerid, P_MOBILE));
				    SCM(playerid, COLOR_YELLOW, "Вы успешно подключились с PC. Приятной игры на REDAGE ONLINE");
                }
                else{
                    SetPlayerData(playerid, P_MOBILE, 1);
	                UpdatePlayerDatabaseInt(playerid, "mobile", GetPlayerData(playerid, P_MOBILE));
	                SCM(playerid, COLOR_YELLOW, "Вы успешно подключились с MOBILE. Приятной игры на REDAGE ONLINE");
                }
			}
			case DIALOG_BANK_CREATE_ACCOUNT:
			{
				if(response)
				{
					new len = strlen(inputtext);
					if(3 <= len <= 20)
					{
						if(!IsABadBankAccountName(inputtext))
						{
							new query[128];
							new Cache: result;
							new total_accounts;

							format(query, sizeof query, "SELECT COUNT(*) FROM bank_accounts WHERE uid=%d", GetPlayerAccountID(playerid));
							result = mysql_query(mysql, query);

							total_accounts = cache_get_row_int(0, 0);
							cache_delete(result);

							if(total_accounts < MAX_BANK_ACCOUNTS)
							{
								mysql_format(mysql, query, sizeof query, "INSERT INTO bank_accounts (uid,name,reg_time) VALUES (%d,'%e',%d)", GetPlayerAccountID(playerid), inputtext, gettime());
								mysql_query(mysql, query, false);

								if(!mysql_errno())
								{
									IntfDialogCallRemote
									(
										playerid, DIALOG_BANK_CREATED_ACCOUNT, DIALOG_STYLE_MSGBOX,
										"{FFD83D}Счет создан",
										"{FFFFFF}Вы создали новый счет в банке.\n\n"\
										"Для доступа к нему используйте PIN-код {00FF66}0000{FFFFFF}. После входа\n"\
										"настоятельно рекомендуем изменить его на более сложный.\n"\
										"Это поможет защитить счет от несанкционированного доступа.",
										"Готово", ""
									);
								}
							}
							else IntfDialogCallRemote(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, "{FFD83D}Лимит счетов", "{FFFFFF}Можно создать не более восьми банковских счетов", "Ок", "");
						}
						else
						{
							IntfDialogCallRemote
							(
								playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX,
								"{FF3300}Ошибка",
								"{FFFFFF}Операция запрещена. Недопустимые символы в названии счета\n"\
								"Можно использовать {FFCC15}русские {FFFFFF}и {FFCC15}английские {FFFFFF}буквы, а также {FFCC15}цифры",
								"Выход", ""
							);
						}
					}
					else
					{
						IntfDialogCallRemote
						(
							playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX,
							"{FF3300}Ошибка",
							"{FFFFFF}Длина названия счета может быть от {FFCC15}3 до 20 {FFFFFF}символов",
							"Закрыть", ""
						);
					}
				}
				else ShowPlayerBankDialog(playerid);
			}
			case DIALOG_BANK_CREATED_ACCOUNT:
			{
				ShowPlayerBankDialog(playerid);
			}
			// -----------------------------------------------------------------
			case DIALOG_PHONE_CALL:
			{
				if(response)
				{
					new number = strval(inputtext);

					if(number >= 0 && strlen(inputtext))
					{
						new params[16];
						valstr(params, number);

						callcmd::c(playerid, params);
					}
					else SendClientMessage(playerid, 0xCECECEFF, "Ошибка набора");
				}
			}
			case DIALOG_PHONE_CALL_BALANCE:
			{
				SetPlayerPhoneUseState(playerid, false);
			}
			case DIALOG_CONFIG:
			{
				if(!response) return 1;
				switch(listitem)
				{
					case 0:
					{
						if(Test_server == 0)
						{
							Test_server = 1;
							SendClientMessage(playerid, -1, "Вы успешно включили запрет игрокам на тест");
						}
						else
						{
							Test_server = 0;
							SendClientMessage(playerid, -1, "Вы успешно выключили запрет игрокам на тест");
						}
						SaveServerConfig();
					}
					case 1:
					{
						new query[128];
						format(query, sizeof query, "SELECT name FROM test_user");
						mysql_tquery(mysql, query, "ShowTestPlayer", "i", playerid);
					}
					case 2:
					{
						SendClientMessage(playerid, -1, "Используйте /addzbtplayer чтобы добавить");
					}
					case 3:
					{
						SendClientMessage(playerid, -1, "Используйте /delzbtplayer чтобы удалить");
					}
				}
			}
			case DIALOG_ADMIN_PANEL:
			{
				if(!response) return 1;
				switch(listitem)
				{
					case 0:
					{
                       callcmd::adminlist(playerid);
					}
					case 1:
					{
					   callcmd::ahelp(playerid);
					}
				}
			}
			case DIALOG_INFO_HELP:
			{
			    if(!response) return 1;
				switch(listitem + 1)
				{
				    case 1:
				    {
				        IntfDialogCallRemote(playerid, 0, DIALOG_STYLE_MSGBOX, "{FFD83D}Информация о проекте", ""SERVER_NAME" - наилучший и качественный проект среди\nсерверов копий Радмира", "Закрыть", "");
				    }
				    case 2:
				    {
				        IntfDialogCallRemote(playerid, 0, DIALOG_STYLE_MSGBOX, "{FFD83D}Где заработать денег?", "Деньги можно заработать на подработках (шахта, ферма, лесопилка, завод, ферма)\nНайти месторасположение работ можно с помощью GPS (/gps > Работа)", "Закрыть", "");
				    }
				    case 3:
				    {
				        IntfDialogCallRemote(playerid, 0, DIALOG_STYLE_MSGBOX, "{FFD83D}Где получить права на вождение?", "Чтобы получить права на вождение Вам нужно сдать экзамен в автошколе\nGPS > Автошкола за 1000 рублей, либо купить права у инструктора", "Закрыть", "");
				    }
				    case 4:
				    {
				        IntfDialogCallRemote(playerid, 0, DIALOG_STYLE_MSGBOX, "{FFD83D}Как купить жилье?", "Купить дом или квартиру можно у государства или с рук у игрока\nНа Вашем радаре будут отображаться иконки домов\nЕсли иконка зеленая, то дом продается, если красная - нет", "Закрыть", "");
				    }
				    case 5:
				    {
				        IntfDialogCallRemote(playerid, 0, DIALOG_STYLE_MSGBOX, "{FFD83D}Как купить бизнес?", "Бизнес можно купить у государства или с рук у игрока\nНайти бизнес можно с помощью GPS (/gps > Бизнесы)", "Закрыть", "");
				    }
				    case 6:
				    {
				        IntfDialogCallRemote(playerid, 0, DIALOG_STYLE_MSGBOX, "{FFD83D}Как купить авто?", "Автомобиль можно купить в автосалоне (/gps > Автосалоны) или с рук у игрока\nДля того чтобы пользоваться машиной, Вам нужно жилье", "Закрыть", "");
				    }
				    case 7:
				    {
				        IntfDialogCallRemote(playerid, 0, DIALOG_STYLE_MSGBOX, "{FFD83D}Как прокачать уровень?", "Каждый час в XX:00 минут Вам начисляется опыт\nУзнать очки опыта можно в статистике (/mn - Статистика)\nДля получения опыта Вы не должны находиться в AFK", "Закрыть", "");
				    }
				    case 8:
				    {
				        IntfDialogCallRemote(playerid, 0, DIALOG_STYLE_MSGBOX, "{FFD83D}Как вступить в организацию?", "О наборах в государственные организации cообщают в чате\nО наборах в нелегальные организации сообщают в объявлениях СМИ\nДля вступление в организацию Вам потребуется водительские права и от 3-ех лет проживания в области", "Закрыть", "");
				    }
				    case 9:
				    {
				        IntfDialogCallRemote(playerid, 0, DIALOG_STYLE_MSGBOX, "{FFD83D}Как стать агентом поддержки или лидером?", "Для того чтобы стать лицом проекта Вам необходимо иметь опыт в RolePlay режиме,\nзнать на отлично базовый уровень игрока, уметь общаться с людьми,\nсмотреть всегда наперед и показать себя для всех с хорошей стороны\nДля просмотра свободных мест на лидерство посетите наш форум: ", "Закрыть", "");
				    }
				    case 10:
				    {
				        IntfDialogCallRemote(playerid, 0, DIALOG_STYLE_MSGBOX, "{FFD83D}Как найти нужное мне место?", "Любое нужное Вам место можно найти с помощью GPS (/gps)\nЕсли Вы не нашли нужное Вам место - спросите у агентов поддержки (/report - Вопрос)", "Закрыть", "");
				    }
				    case 11:
				    {
				        IntfDialogCallRemote(playerid, 0, DIALOG_STYLE_MSGBOX, "{FFD83D}Где достать оружие?", "Оружие можно купить у любого игрока имеющего оружие\nили приобрести в магазине оружия (/gps - Бизнесы)", "Закрыть", "");
				    }
				    case 12:
				    {
				        IntfDialogCallRemote(playerid, 0, DIALOG_STYLE_MSGBOX, "{FFD83D}Где устроиться на работу?", "Трудоустройство проходит в центре занятости, либо на базах организаций (/gps - Базы организаций)", "Закрыть", "");
				    }
				    case 13:
				    {
				        IntfDialogCallRemote(playerid, 0, DIALOG_STYLE_MSGBOX, "{FFD83D}Как посмотреть команды?", "Для просмотра нужных Вам команд используйте: /mn - Список команд", "Закрыть", "");
				    }
				    case 14:
				    {
				        IntfDialogCallRemote(playerid, 0, DIALOG_STYLE_MSGBOX, "{FFD83D}Как добраться до работы?", "Добраться до работы можно с помощью такси или маршрутки\nЕсли их нет долгое время - воспользуйтесь попуткой", "Закрыть", "");
				    }
				    case 15:
				    {
				        IntfDialogCallRemote(playerid, 0, DIALOG_STYLE_MSGBOX, "{FFD83D}Где купить телефон и SIM-карту?", "Телефон и SIM-карту можно купить в любом из магазинов 24/7\nСтоимость телефона 2000 рублей, SIM-карта 500 рублей", "Закрыть", "");
				    }
				    case 16:
				    {
				        IntfDialogCallRemote(playerid, 0, DIALOG_STYLE_MSGBOX, "{FFD83D}Как мне уволиться из фракции?", "Чтобы покинуть фракцию Вам необходимо сообщить об этом лидеру или заместителю фракции:\nИспользуйте: /r Прошу меня уволить по причине (указать причину)\nПри наличии улучшений аккаунта используйте команду: /leave", "Закрыть", "");
				    }
				    case 17:
				    {
				        IntfDialogCallRemote(playerid, 0, DIALOG_STYLE_MSGBOX, "{FFD83D}Как узнать номер телефона игрока?", "Если игрок находится в игре, то используйте команду: /number [имя игрока]", "Закрыть", "");
				    }
				}
			}
			// -----------------------------------------------------------------
			// -----------------------------------------------------------------
            case DIALOG_ACTION:
			{
				if(response)
				{
					if(1 <= (listitem+1) <= 4)
					{
						new targetid = GetPlayerData(playerid, P_TARGET_ID);

						if(IsPlayerConnected(targetid) && IsPlayerLogged(targetid))
						{
							if(IsPlayerInRangeOfPlayer(playerid, targetid, 10.0))
							{
								new params[5];
								valstr(params, targetid);

								new cmd[4][16] = {"cmd_hi", "cmd_pass", "cmd_lic", "cmd_skill"};
								CallLocalFunction(cmd[listitem], "ds", playerid, params);
							}
							else SendClientMessage(playerid, 0x999999FF, "Игрок находится слишком далеко");
						}
						else SendClientMessage(playerid, 0x999999FF, "Игрок вышел из игры");
					}
					SetPlayerData(playerid, P_TARGET_ID, INVALID_PLAYER_ID);
				}
			}
			// -----------------------------------------------------------------
			case DIALOG_VIEV_JOBS_LIST:
            {
                if(!response) return 1;

				EmploymentUpdate(playerid);
            }
			case DIALOG_END_JOB:
			{
				if(!response) return 1;

				if(stop_bus_job[playerid] == 1)
				{
                    stop_bus_job[playerid] = 0;
	                CEF_HIDE(playerid, "Interactions");
				}
				EndPlayerJob(playerid);
			}
			case DIALOG_END_JOB_ELECT:
			{
				if(!response) return 1;
				EndPlayerJob(playerid);
				EndPlayerTempJob(playerid, TEMP_JOB_ELECTRICIAN);
				KillEndJobTimer(playerid);
				DisablePlayerRaceCheckpoint(playerid);
				RemovePlayerFromVehicle(playerid);
				SetPlayerData(playerid, P_JOB_CAR, INVALID_VEHICLE_ID);
			}
            case DIALOG_YES_BUSINESS:
			{
				new biz_id = g_electrician_listitem[playerid];
				if(response)
				{
					SCMF(playerid, 0x66CC00FF, "Вы выбрали обьект: \"%s\" (№: %d)", g_business[biz_id][B_NAME], g_business[biz_id][B_SQL_ID]);
					SCMF(playerid, -1, "Приблизительное расстояние до него {81c1f0}%.2f метров{ffffff}", GetPlayerDistanceFromPoint(playerid, g_business[biz_id][B_POS_X], g_business[biz_id][B_POS_Y], g_business[biz_id][B_POS_Z]));
					
                    ElectrikUse[playerid] = 0;
                    ElectrikActive[playerid] = 1;

					SetPlayerRaceCheckpoint
					(
						playerid,
						1,
						g_business[biz_id][B_POS_X],
						g_business[biz_id][B_POS_Y],
						g_business[biz_id][B_POS_Z],
						0.0,
						0.0,
						0.0,
						1.0,
						RCP_ACTION_TYPE_ELECT
					);
				}
			}
			case DIALOG_ELECT_BUSINESS:
			{
				if(response)
				{
					new query[512], biz_id = GetPlayerListitemValue(playerid, listitem);
					format(query, sizeof query, "{FFFFFF}Вы выбрали бизнес {FFCD00}'%s (№:%d)'\n{FFFFFF}Он находится на расстоянии {81c1f0}%.2f м{ffffff} от Вас\n\nВы желаете взять этот запрос на починку проводки?", g_business[biz_id][B_NAME], g_business[biz_id][B_SQL_ID], GetPlayerDistanceFromPoint(playerid, g_business[biz_id][B_POS_X], g_business[biz_id][B_POS_Y], g_business[biz_id][B_POS_Z]));
					g_electrician_listitem[playerid] = biz_id;
					IntfDialogCallRemote
					(
						playerid, DIALOG_YES_BUSINESS, DIALOG_STYLE_MSGBOX,
						"Ремонт проводки",
						query,
						"Далее", "Отмена"
					);
				}
			}
			case DIALOG_ELECTRICIAN_RENT_CAR:
			{
				if(response)
				{
					new vehicleid = GetPlayerVehicleID(playerid);

					new action_type = GetVehicleData(vehicleid, V_ACTION_TYPE);
					new action_id = GetVehicleData(vehicleid, V_ACTION_ID);

					if(action_type == VEHICLE_ACTION_TYPE_ELECTRICIAN && action_id == VEHICLE_ACTION_ID_NONE)
					{
						if(VerifyIntString(QueryPlayerBalance(playerid), 1500))
						{
							if(ModifyCashBalance(playerid, -1500, "Аренда машины электрика", true, true) == -1) return false;
							//SetVehicleData(vehicleid, V_ACTION_ID, true);
							
							CEF_CREATE(playerid, 2, 4, "Interactions", "[[47, \"Начать работу\"]]");
                            SetPlayerData(playerid, P_JOB_CAR, vehicleid);
                            return SendClientMessage(playerid, 0x66CC00FF, "Для того, чтобы начать работу электрика {FF9900}нажмите 2");
						}
						else SendClientMessage(playerid, 0x999999FF, "У Вас недостаточно денег чтобы заключить договор аренды");
					}
				}
				RemovePlayerFromVehicle(playerid);
			}
			case DIALOG_BUS_RENT_CAR:
			{
				if(response)
				{
					new vehicleid = GetPlayerVehicleID(playerid);

					new action_type = GetVehicleData(vehicleid, V_ACTION_TYPE);
					new action_id = GetVehicleData(vehicleid, V_ACTION_ID);

					if(action_type == VEHICLE_ACTION_TYPE_BUS_DRIVER && action_id == VEHICLE_ACTION_ID_NONE)
					{
						if(VerifyIntString(QueryPlayerBalance(playerid), 180))
						{
							ModifyCashBalance(playerid, -180, "Аренда автобуса", true, true);

							SetPlayerData(playerid, P_JOB_CAR, vehicleid);
						}
						else SendClientMessage(playerid, 0xFF6600FF, "У Вас недостаточно денег чтобы заключить договор аренды");
					}
				}
				RemovePlayerFromVehicle(playerid);
			}
			case DIALOG_BUS_ROUTE_COST:
			{
				if(response)
				{
					new vehicleid = GetPlayerVehicleID(playerid);

					new action_type = GetVehicleData(vehicleid, V_ACTION_TYPE);
					new action_id = GetVehicleData(vehicleid, V_ACTION_ID);

					if(action_type == VEHICLE_ACTION_TYPE_BUS_DRIVER && action_id == VEHICLE_ACTION_ID_NONE)
					{
						new route_cost = strval(inputtext);

						if(0 <= route_cost <= 50000 && IsNumeric(inputtext))
						{
							SetPlayerData(playerid, P_JOB_TARIFF, route_cost);
							SetPlayerData(playerid, P_JOB_CAR, vehicleid);
							StartPlayerJob(playerid, JOB_BUS_DRIVER);
						}
						else
						{
							IntfDialogCallRemote
							(
								playerid, DIALOG_BUS_ROUTE_COST, DIALOG_STYLE_INPUT,
								"{"#cGold"}Стоимость проезда",
								"{"#cW"}Сколько будет стоить проезд?\n"\
								"Укажите цену от 0 до 50000 рублей",
								"Далее", "Отмена"
							);
						}
					}
				}
			}
			case DIALOG_BUS_ROUTE_SELECTION:
			{
				if(!response) return 1;
				
				switch(listitem + 1)
				{
					case 1:
					{
						if(VerifyIntString(QueryPlayerBalance(playerid), 180))
					    {
						    SetPlayerData(playerid, P_BUS_ROUTE_STEP, 0);
						    SetPlayerData(playerid, P_BUS_ROUTE, 0);

						    new rand_index = RandomEx(1, sizeof(bus_spawn_positions) - 1);
                            new Float:x = bus_spawn_positions[rand_index][0];
                            new Float:y = bus_spawn_positions[rand_index][1];
                            new Float:z = bus_spawn_positions[rand_index][2];
                            new Float:a = bus_spawn_positions[rand_index][3];

                            new vehicleids = CreateVehicle(418, x, y, z, a, 1, 1, -1, 0, VEHICLE_ACTION_TYPE_BUS_DRIVER);
                            PutPlayerInVehicle(playerid, vehicleids, 0);

						    ModifyCashBalance(playerid, -180, "Аренда автобуса", true, false);
						    GameText(playerid, "~o~Аренда автобуса", 3000, 2);
					    }
					    else SendClientMessage(playerid, 0xFF6600FF, "У Вас недостаточно денег чтобы заключить договор аренды");
					}
				}
			}
			case DIALOG_TAXI_RENT_CAR:
			{
				if(response)
				{
					new vehicleid = GetPlayerVehicleID(playerid);

					new action_type = GetVehicleData(vehicleid, V_ACTION_TYPE);
					new action_id = GetVehicleData(vehicleid, V_ACTION_ID);

					if(action_type == VEHICLE_ACTION_TYPE_TAXI_DRIVER && action_id == VEHICLE_ACTION_ID_NONE)
					{
						if(VerifyIntString(QueryPlayerBalance(playerid), 150000))
						{
							ModifyCashBalance(playerid, -150000, "Аренда такси", true, true);

							SetPlayerData(playerid, P_JOB_CAR, vehicleid);
							return SendClientMessage(playerid, COLOR_WHITE, "Для того, чтобы начать работу таксиста {"#cGold"}нажмите ~k~~TOGGLE_SUBMISSIONS~");
						}
						else SendClientMessage(playerid, 0xFF6600FF, "У Вас недостаточно денег чтобы заключить договор аренды");
					}
				}
				RemovePlayerFromVehicle(playerid);
			}
			case DIALOG_RERFECT_RENT_CAR:
			{
				if(response)
				{
					new vehicleid = GetPlayerVehicleID(playerid);

					new action_type = GetVehicleData(vehicleid, V_ACTION_TYPE);
					new action_id = GetVehicleData(vehicleid, V_ACTION_ID);

					if(action_type == VEHICLE_ACTION_TYPE_RERFECT && action_id == VEHICLE_ACTION_ID_NONE)
					{
						if(VerifyIntString(QueryPlayerBalance(playerid), 180))
						{
							ModifyCashBalance(playerid, -180, "Аренда эвакуатора", true, true);
							//SetVehicleData(vehicleid, V_ACTION_ID, true);

							SetPlayerData(playerid, P_JOB_CAR, vehicleid);
							return SendClientMessage(playerid, 0x66CC00FF, "Для того, чтобы начать работу автомеханика {FF9900}нажмите ~k~~TOGGLE_SUBMISSIONS~");
						}
						else SendClientMessage(playerid, 0x999999FF, "У Вас недостаточно денег чтобы заключить договор аренды");
					}
				}
				RemovePlayerFromVehicle(playerid);
			}
			case DIALOG_RERFECT_START_JOB:
			{
				if(response)
				{
					new vehicleid = GetPlayerVehicleID(playerid);

					new action_type = GetVehicleData(vehicleid, V_ACTION_TYPE);
					new action_id = GetVehicleData(vehicleid, V_ACTION_ID);

					if(action_type == VEHICLE_ACTION_TYPE_RERFECT && action_id == VEHICLE_ACTION_ID_NONE)
					{
						IntfDialogCallRemote
						(
							playerid, DIALOG_RERFECT_NAME, DIALOG_STYLE_INPUT,
							"{FFD83D}Автомеханик",
							"{FFFFFF}Введите название для Вашей техслужбы,\n"\
							"или оставьте поле пустым",
							"Готово", "Отмена"
						);
					}
				}
			}
			case DIALOG_RERFECT_NAME:
			{
				if(response)
				{
					new len = strlen(inputtext);

					if(len)
					{
						if(!(1 <= len <= 15))
						{
							IntfDialogCallRemote
							(
								playerid, DIALOG_MECHANIC_NAME, DIALOG_STYLE_INPUT,
								"{FFD83D}Автомеханик",
								"{FFFFFF}Введите название для Вашей техслужбы,\n"\
								"или оставьте поле пустым",
								"Готово", "Отмена"
							);
							return SendClientMessage(playerid, 0xCECECEFF, "Слишком длинное название | 15 символов максимум");
						}
						else format(g_player[playerid][P_JOB_SERVICE_NAME], 17, "%s\n", inputtext);
					}
					else g_player[playerid][P_JOB_SERVICE_NAME][0] = 0;

					StartPlayerJob(playerid, JOB_RERFECT_DRIVER);
				}
			}
			case DIALOG_TAXI_NAME:
			{
				if(response)
				{
					if(!(1 <= strlen(inputtext) <= 15))
					{
						IntfDialogCallRemote
						(
							playerid, DIALOG_TAXI_NAME, DIALOG_STYLE_INPUT,
							"{FFD83D}Название такси",
							"{FFFFFF}Придумайте название для вашего такси\n"\
							"Максимальная длина 15 символов\n\n"\
							"Если вы не хотите как-то называться\n"\
							"нажмите кнопку Пропустить",
							"Далее", "Пропустить"
						);
						return 1;
					}
					else format(g_player[playerid][P_JOB_SERVICE_NAME], 17, "%s\n", inputtext);
				}
				else g_player[playerid][P_JOB_SERVICE_NAME][0] = 0;

				IntfDialogCallRemote
				(
					playerid, DIALOG_TAXI_TARIFF, DIALOG_STYLE_INPUT,
					"{FFD83D}Настройка счетчика",
					"{FFFFFF}Укажите тариф по которому будет работать ваше такси\n"\
					"Эта сумма будет сниматься с пассажира каждые 100 м поездки\n"\
					"Тарифная ставка может быть от 0 до 5000 рублей",
					"Ок", "Отмена"
				);
			}
			case DIALOG_TAXI_TARIFF:
			{
				if(response)
				{
					new vehicleid = GetPlayerVehicleID(playerid);

					new action_type = GetVehicleData(vehicleid, V_ACTION_TYPE);
					new action_id = GetVehicleData(vehicleid, V_ACTION_ID);

					if(action_type == VEHICLE_ACTION_TYPE_TAXI_DRIVER && action_id == VEHICLE_ACTION_ID_NONE)
					{
						new tariff = strval(inputtext);

						if(!(0 <= tariff <= 333333) || !IsNumeric(inputtext))
						{
							IntfDialogCallRemote
							(
								playerid, DIALOG_TAXI_TARIFF, DIALOG_STYLE_INPUT,
								"{FFD83D}Настройка счетчика",
								"{FFFFFF}Укажите тариф по которому будет работать ваше такси\n"\
								"Эта сумма будет сниматься с пассажира каждые 100 м поездки\n"\
								"Тарифная ставка может быть от 0 до 333,333 рублей",
								"Ок", "Отмена"
							);
							return 1;
						}
						else
						{
							SetPlayerData(playerid, P_JOB_TARIFF, tariff);
							StartPlayerJob(playerid, JOB_TAXI_DRIVER);
						}
					}
				}
				g_player[playerid][P_JOB_SERVICE_NAME][0] = 0;
			}
			case DIALOG_MECHANIC_RENT_CAR:
			{
				if(response)
				{
					new vehicleid = GetPlayerVehicleID(playerid);

					new action_type = GetVehicleData(vehicleid, V_ACTION_TYPE);
					new action_id = GetVehicleData(vehicleid, V_ACTION_ID);

					if(action_type == VEHICLE_ACTION_TYPE_MECHANIC && action_id == VEHICLE_ACTION_ID_NONE)
					{
						if(VerifyIntString(QueryPlayerBalance(playerid), 180))
						{
							ModifyCashBalance(playerid, -180, "Аренда эвакуатора", true, true);
							//SetVehicleData(vehicleid, V_ACTION_ID, true);

							SetPlayerData(playerid, P_JOB_CAR, vehicleid);
							return SendClientMessage(playerid, 0x66CC00FF, "Для того, чтобы начать работу автомеханика {FF9900}нажмите ~k~~TOGGLE_SUBMISSIONS~");
						}
						else SendClientMessage(playerid, 0x999999FF, "У Вас недостаточно денег чтобы заключить договор аренды");
					}
				}
				RemovePlayerFromVehicle(playerid);
			}
			case DIALOG_MECHANIC_START_JOB:
			{
				if(response)
				{
					new vehicleid = GetPlayerVehicleID(playerid);

					new action_type = GetVehicleData(vehicleid, V_ACTION_TYPE);
					new action_id = GetVehicleData(vehicleid, V_ACTION_ID);

					if(action_type == VEHICLE_ACTION_TYPE_MECHANIC && action_id == VEHICLE_ACTION_ID_NONE)
					{
						IntfDialogCallRemote
						(
							playerid, DIALOG_MECHANIC_NAME, DIALOG_STYLE_INPUT,
							"{FFD83D}Автомеханик",
							"{FFFFFF}Введите название для Вашей техслужбы,\n"\
							"или оставьте поле пустым",
							"Готово", "Отмена"
						);
					}
				}
			}
			
			case DIALOG_TRUCKER_RENT_CAR:
			{
				if(response)
				{
					new vehicleid = GetPlayerVehicleID(playerid);

					if(!VerifyIntString(QueryPlayerBalance(playerid), 2000000)) return SendClientMessage(playerid, 0x999999FF, "У Вас недостаточно денег чтобы заключить договор аренды");

					ModifyCashBalance(playerid, -2000000, "Аренда грузовика", true, true);

					SetPlayerData(playerid, P_JOB_CAR, vehicleid);

					player_job_active[playerid] = 4;

					SetPlayerData(playerid, P_IN_JOB, true);
					
					STRING_GLOBAL[0] = EOS;
					format(STRING_GLOBAL, sizeof STRING_GLOBAL, "{FFA500}Транспортная компания\n{FFFFFF}%s", GetBusinessData(GetPlayerData(playerid, P_TK_JOB), B_NAME));
					CreateVehicleLabel(vehicleid, STRING_GLOBAL, 0x3399FFFF, 0.0, 2.1, 3.1, 20.0);
					
					SCM(playerid, 0xFFFFFFFF, "Вы начали свой {E6CE7B}рабочий день. Посигнальте {FFFFFF}и выберите необходимый прицеп");
				}
				else RemovePlayerFromVehicle(playerid);
			}
			case DIALOG_TRUCKER_START_JOB:
			{
				if(response)
				{
					StartPlayerJob(playerid, JOB_TRUCKER);
				}
			}
			// -----------------------------------------------------------------
			case DIALOG_PHONE_BOOK:
			{
				if(response && (0 <= listitem <= MAX_PHONE_BOOK_CONTACTS-1))
				{
					ShowPhoneBookOperation(playerid, PHONE_BOOK_OPERATION_OPTIONS, listitem);
				}
			}
			case DIALOG_WOSH_SKIN:
			{
				if(!response) return 1;
				
				if(!GetPlayerSex(playerid))
					SetPlayerSkin(playerid, 252);
				else
					SetPlayerSkin(playerid, 75);

				SendClientMessage(playerid, 0xB0C4DEFF, "Вы запустили стиральную машину. Не покидайте прачечную до окончания стирки");

				woshtimer[playerid] = SetTimerEx("WoshTimer", 2000, true, "i", playerid);

				CEF_CREATE(playerid, 2, 4, "ProgressBar", "[[\"Одежда стирается\", 0, 1000]]");

			    TogglePlayerControllable(playerid, false);

			}
			case DIALOG_PHONE_BOOK_OPTION:
			{
				new contactid = GetPlayerPhoneBookSelectContact(playerid);
				if(contactid != INVALID_PLAYER_ID)
				{
					if(response)
					{
						ShowPhoneBookOperation(playerid, listitem + 1, contactid);
					}
					else ShowPlayerPhoneBook(playerid);
				}
			}
			case DIALOG_PHONE_BOOK_SEND_SMS:
			{
				if(response)
				{
					new len = strlen(inputtext);
					if(len)
					{
						if(len < 65)
						{
							new contactid = GetPlayerPhoneBookSelectContact(playerid);
							new fmt_str[90];

							format(fmt_str, sizeof fmt_str, "%s %s", GetPlayerPhoneBook(playerid, contactid, PB_NUMBER), inputtext);
							callcmd::sms(playerid, fmt_str);
							return 1;
						}
						else SendClientMessage(playerid, 0xCECECEFF, "Слишком длинное сообщение");
					}
					else SendClientMessage(playerid, 0xCECECEFF, "Введите сообщение для отправки");

					ShowPhoneBookOperation(playerid, PHONE_BOOK_OPERATION_SEND_SMS);
				}
				else ShowPhoneBookOperation(playerid, PHONE_BOOK_OPERATION_OPTIONS);
			}
			case DIALOG_PHONE_BOOK_CHANGE_NAME:
			{
				if(response)
				{
					if(3 <= strlen(inputtext) <= 20)
					{
						new contactid = GetPlayerPhoneBookSelectContact(playerid);
						new query[90];

						format(g_player_phone_book[playerid][contactid][PB_NAME], 21, "%s", inputtext);

						mysql_format(mysql, query, sizeof query, "UPDATE phone_books SET name='%e' WHERE id=%d LIMIT 1", inputtext, GetPlayerPhoneBook(playerid, contactid, PB_SQL_ID));
						mysql_query(mysql, query, false);

						SendClientMessage(playerid, 0x99CC33FF, "Имя контакта изменено");
						ShowPlayerPhoneBook(playerid);
					}
					else ShowPhoneBookOperation(playerid, PHONE_BOOK_OPERATION_CHANGE_NAM);
				}
				else ShowPhoneBookOperation(playerid, PHONE_BOOK_OPERATION_OPTIONS);
			}
			case DIALOG_PHONE_BOOK_CHANGE_NUMBER:
			{
				if(response)
				{
					if(3 <= strlen(inputtext) <= 9 && strval(inputtext) > 0 && IsNumeric(inputtext))
					{
						if(!CheckPhoneBookUsedNumber(playerid, inputtext))
						{
							new contactid = GetPlayerPhoneBookSelectContact(playerid);
							new query[90];

							format(g_player_phone_book[playerid][contactid][PB_NUMBER], 10, "%s", inputtext);

							mysql_format(mysql, query, sizeof query, "UPDATE phone_books SET number='%e' WHERE id=%d LIMIT 1", inputtext, GetPlayerPhoneBook(playerid, contactid, PB_SQL_ID));
							mysql_query(mysql, query, false);

							SendClientMessage(playerid, 0x99CC33FF, "Номер контакта изменен");
							ShowPlayerPhoneBook(playerid);
						}
					}
					else ShowPhoneBookOperation(playerid, PHONE_BOOK_OPERATION_CHANGE_NUM);
				}
				else ShowPhoneBookOperation(playerid, PHONE_BOOK_OPERATION_OPTIONS);
			}
			case DIALOG_PHONE_BOOK_ADD_CONTACT:
			{
				if(response)
				{
					new player_name[20 + 1];
					GetPVarString(playerid, "add_contact_name", player_name, sizeof(player_name));

					if(!(3 <= strlen(inputtext) <= 9) || strval(inputtext) < 1 || !IsNumeric(inputtext))
					{
						new fmt_str[64 + 1];

						format(fmt_str, sizeof fmt_str, "{FFFFFF}Введите номер телефона для контакта %s", player_name);
						IntfDialogCallRemote(playerid, DIALOG_PHONE_BOOK_ADD_CONTACT, DIALOG_STYLE_INPUT, "{FFD83D}Добавление нового контакта", fmt_str, "Добавить", "Отмена");

						return 1;
					}
					AddPhoneBookContact(playerid, player_name, inputtext);
				}
				DeletePVar(playerid, "add_contact_name");
			}
			case DIALOG_REPLACE_TIRE:
			{
			    if(response)
				{
					new to_player = GetPVarInt(playerid, "to_player_s");
				    switch(listitem + 1)
				    {
				        case 1:
						{
						    SendPlayerOffer(playerid, to_player, OFFER_TYPE_SHIN, 1, 5000);
						}
						case 2:
						{
						    SendPlayerOffer(playerid, to_player, OFFER_TYPE_SHIN, 2, 5000);
						}
						case 3:
						{
						    SendPlayerOffer(playerid, to_player, OFFER_TYPE_SHIN, 3, 5000);
						}
						case 4:
						{
						    SendPlayerOffer(playerid, to_player, OFFER_TYPE_SHIN, 4, 5000);
						}
					}
				}
			}
			// -----------------------------------------------------------------
			case DIALOG_TEMP_JOB_MINER_START:
			{
				if(!response) return 1;
				
				if(GetPlayerTempJob(playerid) == TEMP_JOB_NONE)
				{
					SetPlayerSkin(playerid, GetTempJobInfo(TEMP_JOB_MINER, TJ_SKIN)[GetPlayerSex(playerid)]);
					//SetPlayerAttachedObject(playerid, A_OBJECT_SLOT_HAND, 18634, A_OBJECT_BONE_RIGHT_HAND, 0.07, 0.03, 0.04, 0.0, 270.0, 270.0, 1.5, 2.1, 1.8, 0);

					SetPlayerJobLoadItems(playerid, 0);
					SetPlayerTempJob(playerid, TEMP_JOB_MINER);
					SetPVarInt(playerid, "miner_1",0);
					SetPlayerTempJobState(playerid, TEMP_JOB_STATE_MINER_LOAD);
					SetPlayerMinerJobLoadCP(playerid);
					SendClientMessage(playerid, 0xff9900FF, "Вы начали работу. Направляйтесь к лифту, чтобы спуститься под землю.");
					
					SetPlayerCheckpoint(playerid, -470.2869,2876.5969,1192.7656, 1.0);
					g_player_mine_cp[playerid] = 1;
					
				}
			}
			case DIALOG_TEMP_JOB_MINER_END:
			{
				if(response)
				{
					EndPlayerTempJob(playerid, TEMP_JOB_MINER);
					DisablePlayerCheckpoint(playerid);
					g_player_mine_cp[playerid] = 0;
					g_player_mine_status[playerid] = 0;
					g_player_mine_object[playerid] = INVALID_OBJECT_ID;
					g_player_mine_sphere[playerid] = 0;
					g_player_mine_rack[playerid] = 0;
					g_player_mine_ore[playerid] = -1;
				}
			}
			case DIALOG_TEMP_JOB_FACTORY_TRUCKER:
			{
				if(response)
				{
					new job = GetPlayerTempJob(playerid);

					switch(job)
					{
						case TEMP_JOB_NONE:
						{
							new skin = GetTempJobInfo(TEMP_JOB_FACTORY_TRUCKER, TJ_SKIN)[GetPlayerSex(playerid)];

							ClearAnimations(playerid);
							SetPlayerSkin(playerid, skin);

							if(GetPlayerSex(playerid))
								SetPlayerAttachedObject(playerid, A_OBJECT_SLOT_HEAD, 18638, A_OBJECT_BONE_HEAD, 0.16, 0.02, 0.0, 0.0, 0.0, 0.0, 1.0, 1.1, 1.12, 0);

							SetPlayerJobLoadItems(playerid, 0);
							SetPlayerTempJob(playerid, TEMP_JOB_FACTORY_TRUCKER);
							SetPlayerTempJobState(playerid, TEMP_JOB_STATE_NONE);

							SendClientMessage(playerid, 0x3399FFFF, "Вы начали работу в службе доставки завода");
							SendClientMessage(playerid, 0x66CC00FF, "Для получения информации воспользуйтесь инструкцией рядом с Вами");

							SetPlayerData(playerid, P_IN_JOB, true);
						}
						case TEMP_JOB_FACTORY_TRUCKER:
						{
							EndPlayerJob(playerid);
						}
					}
				}
			}
			case DIALOG_TEMP_JOB_FACTORY:
			{
				if(response)
				{
					new job = GetPlayerTempJob(playerid);

					switch(job)
					{
						case TEMP_JOB_NONE:
						{
							new skin = GetTempJobInfo(TEMP_JOB_FACTORY, TJ_SKIN)[GetPlayerSex(playerid)];

							ClearAnimations(playerid);
							SetPlayerSkin(playerid, skin);

							TogglePlayerFactoryCP(playerid, true);
							SetPlayerData(playerid, P_JOB_WAGE, 0);

							SetPlayerJobLoadItems(playerid, 0);
							SetPlayerTempJob(playerid, TEMP_JOB_FACTORY);

							SetPlayerTempJobState(playerid, TEMP_JOB_STATE_FACTORY_TAKE_MET);

							SendClientMessage(playerid, 0x3399FFFF, "Вы начали работу в производственном цеху завода");
							SendClientMessage(playerid, 0x66CC00FF, "Для получения информации воспользуйтесь инструкцией у входа в цех");

							DeletePVar(playerid, "factory_skill");
							DeletePVar(playerid, "factory_bad_prods");
							DeletePVar(playerid, "factory_take_metall");
						}
						case TEMP_JOB_FACTORY:
						{
							EndPlayerTempJob(playerid, TEMP_JOB_FACTORY);
						}
					}
				}
			}
			case DIALOG_TEMP_JOB_LUMBERJACK_ST:
			{
				if(response)
				{
					if(GetPlayerTempJob(playerid) == TEMP_JOB_NONE)
					{
						IntfDialogCallRemote(playerid, DIALOG_LESOPILKA, 5, "Выберите специализацию", "{FFFFFF}Наименование<t>{FFFFFF}Требуемый игровой уровень<t>{FFFFFF}Зарплата<n>1. Рамщик<t>1<t>50.000<n>", "Готово", "Назад");
					}
				}
			}
			case DIALOG_TEMP_JOB_LUMBERJACK_END:
			{
				if(response)
				{
					EndPlayerTempJob(playerid, TEMP_JOB_LUMBERJACK);
				}
			}
			case DIALOG_TEMP_JOB_ELECTRICIAN_ST:
			{
				if(response)
				{
					if(GetPlayerTempJob(playerid) == TEMP_JOB_NONE)
					{
						new skin = GetTempJobInfo(TEMP_JOB_ELECTRICIAN, TJ_SKIN)[GetPlayerSex(playerid)];
						SetPlayerSkin(playerid, skin);

						SetPlayerTempJob(playerid, TEMP_JOB_ELECTRICIAN);

						SetPlayerJobLoadItems(playerid, 0);

						player_job_active[playerid] = 6;

                        SendClientMessage(playerid, COLOR_GREEN, "Вы переоделись в рабочую одежду");

						SendClientMessage(playerid, 0xFFFFFFFF, "Садитесь в рабочий транспорт, чтобы начать работу {FFA500}электриком");
					}
				}
			}
			case DIALOG_TEMP_JOB_ELECTRICIAN_END:
			{
				if(response)
				{
					EndPlayerJob(playerid);
					EndPlayerTempJob(playerid, TEMP_JOB_ELECTRICIAN);
					KillEndJobTimer(playerid);
				}
			}
			case DIALOG_TEMP_JOB_FERMER_ST:
			{
			    if(response)
			    {
                    SendClientMessage(playerid, COLOR_GOLD, "Вы начали работу на ферме");
       				SetPlayerSkin(playerid, GetTempJobInfo(TEMP_JOB_FERMER, TJ_SKIN)[GetPlayerSex(playerid)]);

					SetPlayerJobLoadItems(playerid, 0);
     				SetPlayerTempJob(playerid, TEMP_JOB_FERMER);
     				IntfDialogCallRemote(playerid,DIALOG_FERMER,DIALOG_STYLE_LIST,"Выберите работу","1. Перенос урожая\n2. Сбор урожая (2+ уровень)\n3. Вспахивание поля (7+ уровень)","Выбрать","Закрыть");
			    }
			}
			case DIALOG_TEMP_JOB_LOADER_ST:
			{
				if(response)
				{
					if(GetPlayerTempJob(playerid) == TEMP_JOB_NONE)
					{
						TogglePlayerDynamicCP(playerid, help_info_CP, false);

						SetPlayerSkin(playerid, GetTempJobInfo(TEMP_JOB_LOADER, TJ_SKIN)[GetPlayerSex(playerid)]);
						SetPlayerAttachedObject(playerid, A_OBJECT_SLOT_THIGH, 18635, A_OBJECT_BONE_RIGHT_THIGH, 0.2, -0.06, 0.1, 0.0, -90.0, 90.0, 1.0, 1.0, 1.0, 0);

						SetPlayerJobLoadItems(playerid, 0);
						SetPlayerTempJob(playerid, TEMP_JOB_LOADER);

						SetPlayerLoaderJobLoadCP(playerid);

						SendClientMessage(playerid, 0x3399FFFF, "Вы начали работу грузчика");
						SendClientMessage(playerid, COLOR_YELLOW, "Переносите ящики место выдачи и сдачи отмечено на карте");
					}
				}
			}
			case DIALOG_TEMP_JOB_LOADER_END:
			{
				if(response)
				{
					EndPlayerTempJob(playerid, TEMP_JOB_LOADER);
				}
			}
			// -----------------------------------------------------------------
			case DIALOG_FUEL_STATION_BUY_JERRICA:
			{
				if(!response) return true;

				if(!VerifyIntString(QueryPlayerBalance(playerid), 500000)) return SCM(playerid, COLOR_GREY, "Недостаточно средств");

				GiveIteam(playerid, 1, 1, 1, 0);

				ModifyCashBalance(playerid, -500000, "Покупка канистры на АЗС", false, true);

				SendClientMessage(playerid, 0x66CC00FF, "Вы купили канистру с 15 литрами бензина");
				SendClientMessage(playerid, 0x3399FFFF, "Чтобы заправить транспорт, подойдите к нему и нажмите ПКМ");
				SendClientMessage(playerid, 0xCECECEFF, "Примечание: Вы не должны двигаться во время заправки. ПКМ - правая кнопка мышки");
			}
			case DIALOG_FUEL_STATION_PRICE_FUEL:
			{
				new stationid = GetPVarInt(playerid, "ownablebiz_id");
				if(stationid != -1)
				{
					if(response)
					{
						new price = strval(inputtext);
						if(25000 <= price <= 500000 && IsNumeric(inputtext))
						{
							new fmt_str[75];

							new query[64 + 1];
							SetBusinessData(stationid, B_PROD_PRICE, price);

							format(fmt_str, sizeof fmt_str, "Теперь топливо на Вашей заправке будет продаваться по %d руб", price);
							SendClientMessage(playerid, 0x66CC00FF, fmt_str);

							format(query, sizeof query, "UPDATE business SET prod_price=%d WHERE id=%d LIMIT 1", GetBusinessData(stationid, B_PROD_PRICE), GetBusinessData(stationid, B_SQL_ID));
							mysql_query(mysql, query, false);

							UpdateBusinessLabel(stationid);
						}
						else
						{
							SendClientMessage(playerid, 0xCECECEFF, "Укажите отпускную цену от 25.000 до 500.000 рублей за 1 литр");
							return ShowPlayerBusinessDialog(playerid, BIZ_OPERATION_PROD_PRICE);
						}
					}
					ShowPlayerBusinessDialog(playerid, BIZ_OPERATION_PARAMS);
				}
			}
			case DIALOG_FUEL_STATION_BUY_FUEL_PR:
			{
				new stationid = GetPVarInt(playerid, "ownablebiz_id");
				if(stationid != -1)
				{
					if(response)
					{
						new price = strval(inputtext);
						if(2 <= price <= 10 && IsNumeric(inputtext))
						{
							new fmt_str[90];
							format(fmt_str, sizeof fmt_str, "Теперь топливо для Вашей заправки будет закупаться по %d руб за 1 литр", price);
							SendClientMessage(playerid, 0x66CC00FF, fmt_str);
						}
					}
					ShowPlayerBusinessDialog(playerid, BIZ_OPERATION_PARAMS);
				}
			}
			// -----------------------------------------------------------------
			case DIALOG_JERRICAN_FILL_CAR:
			{
				new vehicleid = GetPVarInt(playerid, "jerrican_fill_car");
				new modelid = GetVehicleData(vehicleid, V_MODELID);
				DeletePVar(playerid, "jerrican_fill_car");
				
				if(modelid == 15126)
					return SendClientMessage(playerid, 0xCECECEFF, "В транспортном средстве установлен электродвигатель, вы не сможете заправить его бензином.");

				if(modelid == 543)
					return SendClientMessage(playerid, 0xCECECEFF, "В транспортном средстве установлен электродвигатель, вы не сможете заправить его бензином.");

				if(modelid == 15192)
					return SendClientMessage(playerid, 0xCECECEFF, "В транспортном средстве установлен электродвигатель, вы не сможете заправить его бензином.");

			    if(modelid == 15104)
					return SendClientMessage(playerid, 0xCECECEFF, "В транспортном средстве установлен электродвигатель, вы не сможете заправить его бензином.");

			    if(modelid == 15110)
					return SendClientMessage(playerid, 0xCECECEFF, "В транспортном средстве установлен электродвигатель, вы не сможете заправить его бензином.");

				if(response && vehicleid)
				{
					new Float: x, Float: y, Float: z;
					GetVehiclePos(vehicleid, x, y, z);

					if(IsPlayerInRangeOfPoint(playerid, 2.0, x, y, z))
					{
						if((GetVehicleData(vehicleid, V_FUEL) + 15.0) <= 100.0)
						{
							SetVehicleData(vehicleid, V_FUEL, GetVehicleData(vehicleid, V_FUEL) + 15.0);
							ApplyAnimation(playerid, "CRIB", "CRIB_Use_Switch", 4.0, 0, 0, 0, 0, 0, 0);

							DeletePVar(playerid, "have_jerrican");

							RemovePlayerAttachedObject(playerid, A_OBJECT_SLOT_HAND);
							SendClientMessage(playerid, 0x66CC00FF, "Транспорт заправлен");
							
						 	//BattlePass_Completingtasks(playerid, 1, 9);
							//RemovePlayerItem(playerid, 311, 1);
						    GiveIteam(playerid, 1, 0,1,0);
						}
						else SendClientMessage(playerid, 0xCECECEFF, "В бензобак этого транспорта столько не поместится");
					}
					else SendClientMessage(playerid, 0x999999FF, "Вы находитесь слишком далеко от транспорта");
				}
			}
			// -----------------------------------------------------------------
			case DIALOG_GARDEN:
			{ 
				if(!response) return 1;

				if(GetPlayerWeapon(playerid) != 6) return SCM(playerid, COLOR_GREY,"Для того чтобы посадить семена, требуется лопата в руке.");

				new idmap;
				new garden_id = GetPVarInt(playerid, "garden_id");
				new yamka_id = GetPVarInt(playerid, "yamka_id");
                if(GetGardenData(garden_id, G_IMPROVEMENTS) < 3) if(!IsPlayerInRangeOfPoint(playerid, 0.6, GetGardenData(garden_id, G_POS_X) + GardenGryadka_1[yamka_id][0], GetGardenData(garden_id, G_POS_Y) + GardenGryadka_1[yamka_id][1], GetGardenData(garden_id, G_POS_Z) + GardenGryadka_1[yamka_id][2] + 1)) return 1;
				if(GetGardenData(garden_id, G_IMPROVEMENTS) == 3) if(!IsPlayerInRangeOfPoint(playerid, 0.6, GetGardenData(garden_id, G_POS_X) + GardenGryadka_2[yamka_id][0], GetGardenData(garden_id, G_POS_Y) + GardenGryadka_2[yamka_id][1], GetGardenData(garden_id, G_POS_Z) + GardenGryadka_2[yamka_id][2] + 1)) return 1;
				if(GetGardenData(garden_id, G_IMPROVEMENTS) == 4) if(!IsPlayerInRangeOfPoint(playerid, 0.6, GetGardenData(garden_id, G_POS_X) + GardenGryadka_3[yamka_id][0], GetGardenData(garden_id, G_POS_Y) + GardenGryadka_3[yamka_id][1], GetGardenData(garden_id, G_POS_Z) + GardenGryadka_3[yamka_id][2] + 1)) return 1;

				switch(listitem)
				{
					case 0:
					{
						IntfDialogCallRemote
						(
							playerid, DIALOG_GARDEN, DIALOG_STYLE_LIST,
							"Какое растение вы хотите посадить?",
							"Название\tВремя роста\tИнтервал полива\n\
							{FFFFFF}Помидоры\t{"#cGold"}10 мин.\t4 мин.\n\
							{FFFFFF}Огурцы\t{"#cGold"}20 мин.\t4 мин.\n\
							{FFFFFF}Марихуана\t{"#cGold"}30 мин.\t4 мин.\n\
							{FFFFFF}Картофель\t{"#cGold"}10 мин.\t4 мин.\n\
							{FFFFFF}Свёкла\t{"#cGold"}10 мин.\t4 мин.\n\
							{FFFFFF}Перец\t{"#cGold"}10 мин.\t4 мин.\n\
							{FFFFFF}Баклажан\t{"#cGold"}10 мин.\t4 мин.\n\
							{FFFFFF}Капуста\t{"#cGold"}10 мин.\t4 мин.\n\
							{FFFFFF}Морковь\t{"#cGold"}10 мин.\t4 мин.",
							"Готово", "Закрыть"
						);
						return 1;
					}
					case 1: // Помидоры
					{
						if(GetIteam(playerid, 173) < 1) return SCM(playerid, 0xead671FF, "У вас нет нужых семян.");
						GiveIteam(playerid, 173, 0, 1, 0);
						idmap = 10936;
					}
					case 2: // Огурцы
					{
						if(GetIteam(playerid, 174) < 1) return SCM(playerid, 0xead671FF, "У вас нет нужых семян.");
						GiveIteam(playerid, 174, 0, 1, 0);
						idmap = 10935;
					}
					case 3: // Марихуана
					{
						if(GetIteam(playerid, 172) < 1) return SCM(playerid, 0xead671FF, "У вас нет нужых семян.");
						GiveIteam(playerid, 172, 0, 1, 0);
						idmap = 10937;
					}
					case 4: // Картофель
					{
						if(GetIteamIndx(playerid, 336, 0) < 1) return SCM(playerid, 0xead671FF, "У вас нет нужых семян.");
						GiveIteam(playerid, 336, 0, 1, 0);
						idmap = 16553;
					}
					case 5: // Свёкла
					{
						if(GetIteamIndx(playerid, 336, 1) < 1) return SCM(playerid, 0xead671FF, "У вас нет нужых семян.");
						GiveIteam(playerid, 336, 0, 1, 1);
						idmap = 16550;
					}
					case 6: // Перец
					{
						if(GetIteamIndx(playerid, 336, 2) < 1) return SCM(playerid, 0xead671FF, "У вас нет нужых семян.");
						GiveIteam(playerid, 336, 0, 1, 2);
						idmap = 16551;
					}
					case 7: // Баклажан
					{
						if(GetIteamIndx(playerid, 336, 3) < 1) return SCM(playerid, 0xead671FF, "У вас нет нужых семян.");
						GiveIteam(playerid, 336, 0, 1, 3);
						idmap = 16552;
					}
					case 8: // Капуста
					{
						if(GetIteamIndx(playerid, 336, 4) < 1) return SCM(playerid, 0xead671FF, "У вас нет нужых семян.");
						GiveIteam(playerid, 336, 0, 1, 4);
						idmap = 16549;
					}
					case 9: // морковь
					{
						if(GetIteamIndx(playerid, 336, 5) < 1) return SCM(playerid, 0xead671FF, "У вас нет нужых семян.");
						GiveIteam(playerid, 336, 0, 1, 5);
						idmap = 16548;
					}
				}
				G_TYPE_YAM[garden_id][yamka_id] = listitem;
				if(GetGardenData(garden_id, G_IMPROVEMENTS) < 3) gardendyamka[garden_id][yamka_id] = CreateObject(idmap, GetGardenData(garden_id, G_POS_X) + GardenGryadka_1[yamka_id][0], GetGardenData(garden_id, G_POS_Y) + GardenGryadka_1[yamka_id][1], GetGardenData(garden_id, G_POS_Z) + GardenGryadka_1[yamka_id][2] - 1,   0.00000, 0.00000, 0.0000);
				if(GetGardenData(garden_id, G_IMPROVEMENTS) == 3) gardendyamka[garden_id][yamka_id] = CreateObject(idmap, GetGardenData(garden_id, G_POS_X) + GardenGryadka_2[yamka_id][0], GetGardenData(garden_id, G_POS_Y) + GardenGryadka_2[yamka_id][1], GetGardenData(garden_id, G_POS_Z) + GardenGryadka_2[yamka_id][2] - 1,   0.00000, 0.00000, 0.0000);
				if(GetGardenData(garden_id, G_IMPROVEMENTS) == 4) gardendyamka[garden_id][yamka_id] = CreateObject(idmap, GetGardenData(garden_id, G_POS_X) + GardenGryadka_3[yamka_id][0], GetGardenData(garden_id, G_POS_Y) + GardenGryadka_3[yamka_id][1], GetGardenData(garden_id, G_POS_Z) + GardenGryadka_3[yamka_id][2] - 1,   0.00000, 0.00000, 0.0000);

                garden_kd[playerid] = 2;
				G_STATUS_YAM[garden_id][yamka_id] = 3;
				TogglePlayerControllable(playerid, false);
				SetTimerEx("StopFreeze", 2000, false, "i", playerid);
				ApplyAnimationEx(playerid, "BOMBER", "BOM_Plant", 2.0, 0, 0, 0, 0, 0, 0);

				new fmt_text[148];
				format(fmt_text, sizeof fmt_text,"{FF8800}%s\n{FFFFFF}Прогресс: {FF8800}0.0%\n{FFFFFF}Требуется полив",garden_name[G_TYPE_YAM[garden_id][yamka_id]-1]);
				UpdateDynamic3DTextLabelText(gardendyamkalab[garden_id][yamka_id], 0xFFFF00FF, fmt_text);
				return 1;
			}
			case DIALOG_GARDEN_BUY:
			{
				if(response)
				{
					new garden = GetPVarInt(playerid, "buy_biz_id");

					if(IsPlayerInRangeOfPoint(playerid, 7.0, GetGardenData(garden, G_POS_X), GetGardenData(garden, G_POS_Y), GetGardenData(garden, G_POS_Z)))
					{
						if(!IsGardenOwned(garden))
						{
							if(VerifyIntString(QueryPlayerBalance(playerid), GetGardenData(garden, G_PRICE)))
							{
								if(GetPlayerOwnableGarden(playerid) + 1 > GetPlayerGardenSlots(playerid)) return SendClientMessage(playerid, 0x3399FFFF, "Вы уже имеете максимально количество огородов.");

                                //if(GetPlayerGardens(playerid) > 4) return SendClientMessage(playerid, 0xFFDF87FF, "У вас максимальное кол-во огородов.");
								
								BuyPlayerGarden(playerid, garden);

								PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
								new fmt_str[144];

								format(fmt_str, sizeof fmt_str,"{FFFFFF}Вы успешно приобрели огород {FFA500}№%d {FFFFFF}за {FFA500}%s {FFFFFF}руб.",garden,formatInt(GetGardenData(garden, G_PRICE)));
                                SendClientMessage(playerid, 0xCECECEFF, fmt_str);
							}
							else SendClientMessage(playerid, 0xCECECEFF, "У Вас недостаточно денег для покупки этого огорода");
						}
						else SendClientMessage(playerid, 0xFFDF87FF, "Огород уже куплен другим игроком");

					}
				}
				DeletePVar(playerid, "buy_biz_id");
			}
			case DIALOG_BIZ_BUY:
			{
				if(response)
				{
					new businessid = GetPVarInt(playerid, "buy_biz_id");

					if(IsPlayerInRangeOfPoint(playerid, 7.0, GetBusinessData(businessid, B_POS_X), GetBusinessData(businessid, B_POS_Y), GetBusinessData(businessid, B_POS_Z)))
					{
						if(!IsBusinessOwned(businessid))
						{
							if(VerifyIntString(QueryPlayerBalance(playerid), GetBusinessData(businessid, B_PRICE)))
							{
							    SetPlayerData(playerid, P_DOSTIJ9, GetPlayerData(playerid, P_DOSTIJ9) + 1);
								UpdatePlayerDatabaseInt(playerid, "dostij9", GetPlayerData(playerid, P_DOSTIJ9) + 1);
							
								SendClientMessage(playerid, 0xFFFFFFFF, "Поздравляем! Вы купили бизнес");
								BuyPlayerBusiness(playerid, businessid);

								AddPlayerAchiv(playerid, 8);

								PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
								IntfDialogCallRemote(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, "{3399FF}Новый бизнес", "{FFFFFF}Вам нужно заплатить за аренду бизнеса в ближайшем отделением банка {FFCD00}(/gps)", "Ок", "");
							}
							else SendClientMessage(playerid, 0xCECECEFF, "У Вас недостаточно денег для покупки этого бизнеса");
						}
						else
						{
							new fmt_str[64];

							format(fmt_str, sizeof fmt_str, "Этот бизнес уже куплен. Владелец: %s", GetBusinessData(businessid, B_OWNER_NAME));
							SendClientMessage(playerid, 0xCECECEFF, fmt_str);
						}
					}
				}
				DeletePVar(playerid, "buy_biz_id");
			}
			case DIALOG_BIZ_INFO:
			{
				if(!response) return 1;

				ShowPlayerBusinessDialog(playerid, BIZ_OPERATION_PARAMS);
			}
			case DIALOG_BIZ_PARAMS:
			{
				if(!response) return callcmd::business(playerid, "");

				ShowPlayerBusinessDialog(playerid, listitem + 1);
				
			}
			case DIALOG_BIZ_ARENDA:
			{
			    if(response)
			    {
			        CEF_CREATE(playerid, 2, 4,"Select", "[\"OnPlayerEventRentCar\"]");
			        CEF_HIDE(playerid, "Interactions");
			        TogglePlayerControllable(playerid, false);

			        arendavibor[playerid] = 1;
			        new biz_id = GetPVarInt(playerid, "arenda_id");
					for(new i = 0; i < MAX_VEHICLES; i++)
					{
						if(GetVehicleData(i, V_ACTION_TYPE) == VEHICLE_ACTION_TYPE_RENT_CAR)
						{
						    new index = GetVehicleData(i, V_ACTION_ID);
						    if(GetRentCarData(index, R_RENT_OWNER) == -1)
						    {
								SetPVarInt(playerid, "vehid_arenda", i);
								new Float:X,Float:Y,Float:Z;
								GetVehiclePos(i, X,Y,Z);
								SetPlayerVirtualWorld(playerid, biz_id);
								SetVehicleVirtualWorld(i, biz_id);
								SetPlayerCameraPos(playerid, X+ 7, Y, Z+3);
								SetPlayerCameraLookAt(playerid, X, Y, Z+1, 2);
								return 1;
							}
						 }
					}
			    }
			}
			case DIALOG_BIZ_ARENDA_CAR:
			{
				if(response)
				{
				    new businessid = GetPVarInt(playerid, "ownablebiz_id");
					switch(listitem + 1)
					{
						case 1:
						{
							new query[148],
								Cache: result;

							mysql_format(mysql, query, sizeof query, "SELECT * FROM arenda_cars WHERE owner_id='%d'", businessid);
							result = mysql_query(mysql, query, true);

							new rows = cache_num_rows();

							if(!rows)
								SendClientMessage(playerid, 0x999999FF, "У Вашей аренды авто нет транспорта");

							else
							{
								string_dialog[0] = EOS;
								for(new i = 0; i < rows; i ++)
								{
								    new vehicleid = cache_get_field_content_int(i, "vehicleid");
								    new Float: iznos = cache_get_field_content_float(i, "iznos");
								    new model_id = cache_get_field_content_int(i, "model_id");
								    new price = cache_get_field_content_int(i, "price");

									format(query, sizeof query, "{FFFFFF}%d.  %s (ID: %d)<t>{FFFFFF}Аренда: {6495ED}%d рублей{FFFFFF}<t>Износ: {6495ED}%d% <n>", i+1, GetVehicleInfo(model_id , VI_NAME), vehicleid, price, floatround(iznos));
									strcat(string_dialog, query);
									SetPlayerListitemValue(playerid, i, vehicleid);

								}

				   				IntfDialogCallRemote
								(
									playerid, DIALOG_BIZ_CAR_LIST, DIALOG_STYLE_LIST,
									"Транспорт",
									string_dialog,
									"Выбрать", "Назад"
								);
							}
							cache_delete(result);
						}
						case 2:
						{
			   				if((GetBusinessCars(businessid) + 1) > 8)
								return SendClientMessage(playerid, 0x3399FFFF, "У вашей аренды авто максимальное количество автомобилей!");
						    new inter, world, Float:X, Float:Y, Float:Z, Float:FA;
							GetPlayerPos(playerid, X, Y, Z);
							GetPlayerFacingAngle(playerid, FA);
							inter = GetPlayerInterior(playerid);
							world = GetPlayerVirtualWorld(playerid);

							SetPVarFloat(playerid, "pos_x", X);
							SetPVarFloat(playerid, "pos_y", Y);
							SetPVarFloat(playerid, "pos_z", Z);
							SetPVarFloat(playerid, "angle", FA);
							SetPVarInt(playerid, "player_int", inter);
							SetPVarInt(playerid, "player_world", world);

							SetPlayerVirtualWorld(playerid, playerid + 1);
							SetPlayerPosEx(playerid, 1853.8215,2813.3525,20.1436,270.9554, 0, _, false);
							TogglePlayerControllable(playerid, false);

							SetPlayerData(playerid, P_BUY_CAR, CreateVehicle(400, 1847.1146,2819.2698,20.5752,321.0539, 1, 1, 0));

							SetVehicleVirtualWorld(GetPlayerData(playerid, P_BUY_CAR), playerid + 1);
							LinkVehicleToInterior(GetPlayerData(playerid, P_BUY_CAR), 0);

                            SetPlayerInterior(playerid, 0);

							SetPlayerCameraPos(playerid, 1856.1144, 2822.7991, 22.2357);
							SetPlayerCameraLookAt(playerid, 1847.2103, 2819.2700, 20.5730);

							SetPVarInt(playerid, "STONKScar", 1);
							LoadPlayerCarsShop(playerid);
							SetPVarInt(playerid, "arendacar_buy", 1);
						}
					}
				}
				else
				{
 					ShowPlayerBusinessDialog(playerid, 0);
				}
			}
			case DIALOG_BIZ_ARENDA_CARS:
			{
			    if(response)
			    {
			        new businessid = GetPVarInt(playerid, "arenda_id");
			        new vehicleid = GetPVarInt(playerid, "vehid_arenda");
			        new index = GetVehicleData(vehicleid, V_ACTION_ID);
			        if(GetPlayerData(playerid, P_RENT_CAR) != INVALID_VEHICLE_ID)
			        {
						SendClientMessage(playerid,COLOR_WHITE,"У вас уже есть арендованное авто. /unrent чтобы вернуть его.");
						return 1;
			        }
					if(!VerifyIntString(QueryPlayerBalance(playerid), GetRentCarData(index, R_PRICE)))
					{
						SendClientMessage(playerid,COLOR_WHITE,"У вас недостаточно средств для аренды транспорта.");
						return 1;
					}

					if(GetBusinessData(businessid, B_PRODS) >= 1)
					{
						new carprice = GetRentCarData(index, R_PRICE);

						AddBusinessProfit(playerid, businessid, carprice, 1);
					}
					else
					{
						SendClientMessage(playerid,COLOR_WHITE,"В бизнесе недостаточно продуктов. Аренда авто закрыта.");
						return 1;
					}
			        SetPlayerVirtualWorld(playerid, 0);
			        SetPlayerInterior(playerid, 0);
					SetVehicleVirtualWorld(vehicleid, 0);
                    PutPlayerInVehicle(playerid, vehicleid, 0);
					TogglePlayerControllable(playerid, true);
					CEF_HIDE(playerid, "Select");
					SetCameraBehindPlayer(playerid);
					new string[144];
					format(string, sizeof(string), "{66CC00}Вы арендовали транспорт для временного использования");
					SendClientMessage(playerid,COLOR_WHITE,string);
					SendClientMessage(playerid, 0xFFFFFFFF, "Используйте {3CB371}/lock 2{FFFFFF} для открытия и закрытия дверей");
					SendClientMessage(playerid, 0xFFFFFFFF, "Чтобы разорвать договор аренды введите {3CB371}/unrent");

					ModifyCashBalance(playerid, -GetRentCarData(index, R_PRICE), "Аренда авто");

					SetPlayerData(playerid, P_RENT_CAR, vehicleid);
					SetRentCarData(index, R_RENT_OWNER, playerid);

			    }
			}
			case DIALOG_BIZ_CAR_ARENDA_1:
			{
			    if(response)
			    {
			        new price = strval(inputtext);
			    	if(!(1 <= price <= 1000000)) return CEF_CREATE(playerid, 1, 2, "interface('GameText').add('[2,\"~r~ Цена аренды от 1 до 1.000.000 рублей\",5000,0,-1,1]')");
			    	new vehicleid = GetPVarInt(playerid, "vehicleid");
			    	new index = GetVehicleData(vehicleid, V_ACTION_ID);
			    	SetRentCarData(index, R_PRICE, price);
					new query[144];
					mysql_format(mysql, query, sizeof query, "UPDATE arenda_cars SET price=%d WHERE id=%d", price, GetRentCarData(index, R_SQL_ID));
					mysql_query(mysql, query, false);
					SendClientMessage(playerid, 0x999999FF, "Вы успешно изменили цену аренды авто!");

			    }
			}
			case DIALOG_BIZ_ARENDA_CAR_SELECT:
			{
			    new businessid = GetPlayerData(playerid, P_BUSINESS);
			    if(response)
			    {
					switch(listitem + 1)
					{
						case 1:
						{
						    IntfDialogCallRemote(playerid, DIALOG_BIZ_CAR_ARENDA_1, DIALOG_STYLE_INPUT, "Настройка аренды авто", "{FFFFFF}Введите цену аренды?", "Готово", "Назад");
						}
						case 2:
						{
						    new vehicleid = GetPVarInt(playerid, "vehicleid");
							new fmt_str[256];
                            new model_id = GetVehicleData(vehicleid, V_MODELID);
							new price = GetVehicleInfo(model_id, VI_PRICE);
							new percent = price * 45 / 100;

							format
							(
								fmt_str, sizeof fmt_str,
								"Модель:\t%s (№%d)\n"\
								"Стоимость:\t%d руб\n\n"\
								"Вы уверены что хотите продать транспорт?\n"\
								"На Ваш банковский счет будет начислено %d руб\n\n"\
								"Если Вы хотите продать его другому игроку,\n"\
								"используйте команду /sellmycar",
								GetVehicleName(vehicleid),
								model_id,
								price,
								price - percent
							);
							IntfDialogCallRemote(playerid, DIALOG_BIZ_CAR_SELL, DIALOG_STYLE_MSGBOX, "Продажа транспорта с аренды атво", fmt_str, "Да", "Нет");
						}
					}
			    }
			    else
			    {
					new query[148],
						Cache: result;

					mysql_format(mysql, query, sizeof query, "SELECT * FROM arenda_cars WHERE owner_id='%d'", businessid);
					result = mysql_query(mysql, query, true);

					new rows = cache_num_rows();

					if(!rows)
						SendClientMessage(playerid, 0x999999FF, "У Вашей аренды авто нет транспорта");

					else
					{
						string_dialog[0] = EOS;
						for(new i = 0; i < rows; i ++)
						{
						    new vehicleid = cache_get_field_content_int(i, "vehicleid");
						    new Float: iznos = cache_get_field_content_float(i, "iznos");
						    new model_id = cache_get_field_content_int(i, "model_id");
						    new price = cache_get_field_content_int(i, "price");

							format(query, sizeof query, "{FFFFFF}%d.  %s (ID: %d)<t>{FFFFFF}Аренда: {6495ED}%d рублей{FFFFFF}<t>Износ: {6495ED}%d% <n>", i+1, GetVehicleInfo(model_id , VI_NAME), vehicleid, price, floatround(iznos));
							strcat(string_dialog, query);
							SetPlayerListitemValue(playerid, i, vehicleid);

						}

		   				IntfDialogCallRemote
						(
							playerid, DIALOG_BIZ_CAR_LIST, DIALOG_STYLE_LIST,
							"Транспорт",
							string_dialog,
							"Выбрать", "Назад"
						);
					}
					cache_delete(result);
			    }
			}
			case DIALOG_BIZ_CAR_LIST:
			{
			    if(response)
				{
				    new vehicleid = GetPlayerListitemValue(playerid, listitem);
				    SetPVarInt(playerid, "vehicleid", vehicleid);
				    new index = GetVehicleData(vehicleid, V_ACTION_ID);

				    new msg[244];
				    format(msg, sizeof msg, "1. Аренда {6495ED}%d руб.<n>{FFFFFF}2. Продать",
					GetRentCarData(index, R_PRICE));
					IntfDialogCallRemote
					(
						playerid, DIALOG_BIZ_ARENDA_CAR_SELECT, DIALOG_STYLE_LIST,
						"{FFFFFF}Транспорт",
						msg,
						"Выбрать", "Назад"
					);
				}
				else
				{
				 	IntfDialogCallRemote
					(
						playerid, DIALOG_BIZ_ARENDA_CAR, DIALOG_STYLE_LIST,
						"{FFFFFF}Транспорт",
						"1. Посмотреть\n"\
						"2. Купить",
						"Выбрать", "Назад"
					);
				}
			}
			case DIALOG_BIZ_ARENDA_PRICE:
			{
				new businessid = GetPlayerData(playerid, P_BUSINESS);
				if(businessid != -1)
				{
					if(response)
					{

						if(strlen(inputtext) < 1 || !IsNumeric(inputtext)) return SendClientMessage(playerid, 0xFF6600FF, "Укажите корректную цену продажи");
						if(strlen(inputtext) > 9) return SendClientMessage(playerid, 0xFF6600FF, "Не больше 9-ти символов!");
						new sell_price = strval(inputtext);
						if(sell_price < 3000 || sell_price > 50000) return SendClientMessage(playerid, 0xFF6600FF, "Цена аренды от 3.000 рублей до 50.000 рублей");

						SetBusinessData(businessid, B_ARENDA_PRICE, sell_price);
						new fmt_str[144];
						format(fmt_str, sizeof fmt_str, "UPDATE business SET arenda_price=%d WHERE id=%d LIMIT 1",  GetBusinessData(businessid, B_ARENDA_PRICE) , GetBusinessData(businessid, B_SQL_ID));
						mysql_query(mysql, fmt_str, false);

						format(fmt_str, sizeof fmt_str,
						"Вы успешно поставили цену на место на б/у рынке за %s рублей",
						formatInt(sell_price));
						SendClientMessage(playerid, -1, fmt_str);

					}
					else ShowPlayerBusinessDialog(playerid, BIZ_OPERATION_PARAMS);
				}
			}
			case DIALOG_BIZ_ENTER_PRICE:
			{
				new businessid = GetPVarInt(playerid, "ownablebiz_id");
				if(businessid != -1)
				{
					if(response)
					{
						new price = strval(inputtext);
						if(strlen(inputtext))
						{
							if((0 <= price <= 1000000) && IsNumeric(inputtext))
							{
								new query[64 + 1];
								SetBusinessData(businessid, B_ENTER_PRICE, price);

								format(query, sizeof query, "UPDATE business SET enter_price=%d WHERE id=%d LIMIT 1", GetBusinessData(businessid, B_ENTER_PRICE), GetBusinessData(businessid, B_SQL_ID));
								mysql_query(mysql, query, false);

								UpdateBusinessLabel(businessid);
								SendClientMessage(playerid, 0x66CC00FF, "Цена за вход в бизнес изменена");

								return ShowPlayerBusinessDialog(playerid, BIZ_OPERATION_PARAMS);
							}
							else SendClientMessage(playerid, 0xCECECEFF, "Предел цены от 0 до 1000000 рублей");
						}
						else SendClientMessage(playerid, 0xCECECEFF, "Введите цену за вход в Ваш бизнес");

						ShowPlayerBusinessDialog(playerid, BIZ_OPERATION_ENTER_PRICE);
					}
					else ShowPlayerBusinessDialog(playerid, BIZ_OPERATION_PARAMS);
				}
			}
			case DIALOG_BIZ_PROD_PRICE:
			{
				new businessid = GetPVarInt(playerid, "ownablebiz_id");
				if(businessid != -1)
				{
					if(response)
					{
						if(GetBusinessData(businessid, B_TYPE) == 43)
						{
							new price = strval(inputtext);
							if(strlen(inputtext) && IsNumeric(inputtext))
							{
								if(5000 <= price <= 50000)
								{
									new query[64 + 1];
									SetBusinessData(businessid, B_PROD_PRICE, price);

									format(query, sizeof query, "UPDATE business SET prod_price=%d WHERE id=%d LIMIT 1", GetBusinessData(businessid, B_PROD_PRICE), GetBusinessData(businessid, B_SQL_ID));
									mysql_query(mysql, query, false);
									UpdateBusinessLabel(businessid);

									SendClientMessage(playerid, 0x66CC00FF, "Стоимость продукта изменена");
									return ShowPlayerBusinessDialog(playerid, BIZ_OPERATION_PARAMS);
								}
								else SendClientMessage(playerid, 0xCECECEFF, "Укажите стоимость от 5000 до 50000 рублей");
							}
							else SendClientMessage(playerid, 0xCECECEFF, "Введите стоимость продукта");

							ShowPlayerBusinessDialog(playerid, BIZ_OPERATION_PROD_PRICE);
						}
						else
						{
							new price = strval(inputtext);
							if(strlen(inputtext) && IsNumeric(inputtext))
							{
								if(25 <= price <= 200)
								{
									new query[64 + 1];
									SetBusinessData(businessid, B_PROD_PRICE, price);

									format(query, sizeof query, "UPDATE business SET prod_price=%d WHERE id=%d LIMIT 1", GetBusinessData(businessid, B_PROD_PRICE), GetBusinessData(businessid, B_SQL_ID));
									mysql_query(mysql, query, false);
									UpdateBusinessLabel(businessid);

									SendClientMessage(playerid, 0x66CC00FF, "Стоимость продукта изменена");
									return ShowPlayerBusinessDialog(playerid, BIZ_OPERATION_PARAMS);
								}
								else SendClientMessage(playerid, 0xCECECEFF, "Укажите стоимость от 25 до 200 рублей");
							}
							else SendClientMessage(playerid, 0xCECECEFF, "Введите стоимость продукта");

							ShowPlayerBusinessDialog(playerid, BIZ_OPERATION_PROD_PRICE);
						}
					}
					else ShowPlayerBusinessDialog(playerid, BIZ_OPERATION_PARAMS);
				}
			}
			case DIALOG_BIZ_ORDER_PRODS:
			{
				new businessid = GetPVarInt(playerid, "ownablebiz_id");
				if(businessid != -1)
				{
					if(response)
					{
						if(GetBusinessData(businessid, B_ORDER_ID) != -1)
						{
							SendClientMessage(playerid, 0x999999FF, "Заказ для Вашего предприятии уже оформлен");
							return ShowPlayerBusinessDialog(playerid, BIZ_OPERATION_PARAMS);
						}

						if(GetBusinessData(businessid, B_PROD_PRICE) > 0)
						{
							new order_prods = strval(inputtext);
							new prod_price = GetBusinessData(businessid, B_PROD_PRICE);
							new price = order_prods * prod_price;

							if(order_prods > 0 && IsNumeric(inputtext))
							{
								new fmt_str[256];

								new free_prods_slots = GetBusinessMaxProd(businessid) - GetBusinessData(businessid, B_PRODS);

								if(free_prods_slots > 1000)
									free_prods_slots = 1000;

								if(order_prods <= free_prods_slots)
								{
									if(VerifyIntString(GetBusinessData(businessid, B_BALANCE), price))
									{
										new order_id = CreateOrder(ORDER_TYPE_BUSINESS, businessid, order_prods, prod_price);
										if(order_id != -1)
										{
											
											format(g_business[businessid][B_BALANCE], 21, "%s", SetILPlayerInt(playerid, g_business[businessid][B_BALANCE], -price));
											AddBusinessData(businessid, B_PRODS, +, order_prods);

											format(fmt_str, sizeof fmt_str, "UPDATE business SET balance=%s,products=%d WHERE id=%d LIMIT 1", GetBusinessData(businessid, B_BALANCE), GetBusinessData(businessid, B_PRODS) , GetBusinessData(businessid, B_SQL_ID));
											mysql_query(mysql, fmt_str, false);

											new year, month, day;
											timestamp_to_date(GetOrderData(order_id, O_TIME), year, month, day);

											format
											(
												fmt_str, sizeof fmt_str,
												"{FFFFFF}Параметры заказа:\n\n"\
												"Количество продуктов:\t\t%d шт.\n"\
												"Стоимость 1 продутка:\t\t%d руб\n"\
												"Общая стоимость заказа:\t\t%d руб\n"\
												"Дата оформления заказа:\t\t%02d-%02d-%d\n\n"\
												"Данные были переданы службе развозчиков продуктов\n"\
												"Ожидайте выполнения Вашего заказа",
												order_prods,
												prod_price,
												price,
												day, month, year
											);
											IntfDialogCallRemote(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, "{99CC00}Заказ оформлен", fmt_str, "Закрыть", "");
										}
										else SendClientMessage(playerid, 0x999999FF, "В данный момент Вы не можете оформить заказ");

										return 1;
									}
									else
									{
										format(fmt_str, sizeof fmt_str, "Чтобы оплатить заказ необходимо иметь %d руб на счету бизнеса", price);
										SendClientMessage(playerid, 0xFF6600FF, fmt_str);
									}
								}
								else
								{
									format(fmt_str, sizeof fmt_str, "Вы не можете заказать более %d продуктов", free_prods_slots);
									SendClientMessage(playerid, 0xCECECEFF, fmt_str);
								}
							}
						}
						else
						{
							SendClientMessage(playerid, 0xFF6600FF, "Перед тем как оформить заказ, установите стоимость продукта");
							return ShowPlayerBusinessDialog(playerid, BIZ_OPERATION_PROD_PRICE);
						}
						ShowPlayerBusinessDialog(playerid, BIZ_OPERATION_PROD_ORDER);
					}
					else ShowPlayerBusinessDialog(playerid, BIZ_OPERATION_PARAMS);
				}
			}
			case DIALOG_BIZ_ORDER_CANCEL:
			{
				new businessid = GetPVarInt(playerid, "ownablebiz_id");
				if(businessid != -1)
				{
					if(response)
					{
						new order_id = GetBusinessData(businessid, B_ORDER_ID);
						if(order_id != -1 && GetOrderData(order_id, O_SQL_ID) > 0)
						{
							if(!GetOrderData(order_id, O_USED))
							{
								new fmt_str[128];

								DeleteOrder(order_id);

								format
								(
									fmt_str, sizeof fmt_str,
									"{FFFFFF}Вы отменили заказ продуктов"
								);
								IntfDialogCallRemote(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, "{FF9900}Отмена заказа", fmt_str, "Закрыть", "");

								return 1;
							}
							else SendClientMessage(playerid, 0xFF6600FF, "Ваш заказ выполняется, его нельзя отменить");
						}
					}
					ShowPlayerBusinessDialog(playerid, BIZ_OPERATION_PARAMS);
				}
			}
			case DIALOG_BIZ_ELECT:
			{
				if(!response)
                    return ShowPlayerBusinessDialog(playerid, BIZ_OPERATION_PARAMS);

                new businessid = GetPVarInt(playerid, "ownablebiz_id");

                if(businessid != -1)
                {
                    new elect_id = -1, index = 0;

                    for(new i; i < g_business_loaded; i++)
                    {
                        if(GetBusinessData(i, B_TYPE) != 36) continue;

                        if(index == listitem) 
                        {
                            elect_id = GetBusinessData(i, B_ELECTRICITY);
                            break;
                        }
                        index++;
                    }

                    if(elect_id == -1) 
                        return SCM(playerid, 0xFF0000FF, "Ошибка выбора электростанции!");

                    if(GetBusinessData(businessid, B_ELECTRICITY) == elect_id)
                        return SCM(playerid, 0xafdafcFF, "Вы уже подключены к данной электростанции");

                    else if(GetBusinessData(businessid, B_ELECTRICITY) != 0)
                    {
                        for(new i; i < g_business_loaded; i++)
                        {
                            if(GetBusinessData(i, B_TYPE) != 36) continue;
                            if(GetBusinessData(i, B_ELECTRICITY) != GetBusinessData(businessid, B_ELECTRICITY)) continue;

                            AddBusinessData(i, B_TYPEWETRIKI, -, 1);

                            new query[148];
                            mysql_format(mysql, query, sizeof query, "UPDATE business SET `typewetriki`=%d WHERE `id`=%d LIMIT 1", GetBusinessData(i, B_TYPEWETRIKI), GetBusinessData(i, B_SQL_ID));
                            mysql_query(mysql, query, false);
                        }
                    }

                    for(new i; i < g_business_loaded; i++)
                    {
                        if(GetBusinessData(i, B_TYPE) != 36) continue;
                        if(GetBusinessData(i, B_ELECTRICITY) != elect_id) continue;

                        AddBusinessData(i, B_TYPEWETRIKI, +, 1);

                        new query[148];
                        mysql_format(mysql, query, sizeof query, "UPDATE business SET `typewetriki`=%d WHERE `id`=%d LIMIT 1", GetBusinessData(i, B_TYPEWETRIKI), GetBusinessData(i, B_SQL_ID));
                        mysql_query(mysql, query, false);
                    }

                    SetBusinessData(businessid, B_ELECTRICITY, elect_id);

                    SendClientMessage(playerid, 0xB8CEF6FF, "Вы успешно сменили {FFFFFF} поставщика электричества");
                    GameText(playerid, "~g~Успешно", 2000, 2);

                    new query[148];
                    mysql_format(mysql, query, sizeof query, "UPDATE business SET `electricity`=%d WHERE `id`=%d LIMIT 1", elect_id, GetBusinessData(businessid, B_SQL_ID));
                    mysql_query(mysql, query, false);
                }
			}

			case DIALOG_BIZ_IMPROVEMENT:
			{
				new businessid = GetPVarInt(playerid, "ownablebiz_id");
				if(businessid != -1)
				{
					if(response)
					{
						if(0 <= listitem <= sizeof g_business_improvements - 1)
						{
							new i_level = GetBusinessData(businessid, B_IMPROVEMENTS);
							new i_price = g_business_improvements[listitem][I_PRICE];

							if(i_level < listitem)
							{
								SendClientMessage(playerid, 0xCECECEFF, "Этот уровень улучшений пока недоступен");
							}
							else if(i_level > listitem)
							{
								SendClientMessage(playerid, 0xCECECEFF, "Вы уже купили этот уровень улучшений");
							}
							else if(!VerifyIntString(QueryPlayerBalance(playerid), i_price))
							{
								new fmt_str[64];

								format(fmt_str, sizeof fmt_str, "Для покупки %d уровня улучшений необходимо %d рублей", listitem + 1, i_price);
								SendClientMessage(playerid, 0xCECECEFF, fmt_str);
							}
							else
							{
								new fmt_str[128];

								format(fmt_str, sizeof fmt_str, "UPDATE accounts_canvasdev a, business b SET a.money=%s, b.improvements=%d WHERE a.id=%d AND b.id=%d", SetILPlayerInt(playerid, QueryPlayerBalance(playerid), -i_price), i_level + 1, GetPlayerAccountID(playerid), GetBusinessData(businessid, B_SQL_ID));
								mysql_query(mysql, fmt_str, false);

								if(!mysql_errno())
								{
									new cur_max_prods = GetBusinessMaxProd(businessid);
									ModifyCashBalance(playerid, -i_price, "Покупка улучшений для Бизнеса", false, true);

									format(fmt_str, sizeof fmt_str, "Вы улучшили свой бизнес до {FFCD00}%s {3399FF}уровня", GetNumericName(listitem + 1));
									SendClientMessage(playerid, 0x3399FFFF, fmt_str);

									AddBusinessData(businessid, B_IMPROVEMENTS, +, 1);
									switch(listitem + 1)
									{
										case 1:
										{
											format(fmt_str, sizeof fmt_str, "Количество слотов для продуктов увеличено с %d до %d", cur_max_prods, GetBusinessMaxProd(businessid));
											SendClientMessage(playerid, 0x66CC00FF, fmt_str);

											SendClientMessage(playerid, 0x999999FF, "Теперь можно намного реже пополнять их запас");
										}
										case 2:
										{
											SendClientMessage(playerid, 0x66CC00FF, "Теперь ваши клиенты смогут пользоваться услугами медпункта на территории бизнеса");
											SendClientMessage(playerid, 0x999999FF, "Доходы от этого будут перечисляться на баланс предприятия");

											BusinessHealthPickupInit(businessid);
										}
										case 3:
										{
											SendClientMessage(playerid, 0x66CC00FF, "Благодаря пониженному налогу, вы будете платить за аренду помещения в 2 раза меньше");
											SendClientMessage(playerid, 0x999999FF, "Благодаря этому, вы сможете получать большую прибыль");
										}
										case 4:
										{
											SendClientMessage(playerid, 0x66CC00FF, "Теперь ваши клиенты будут слышать звук при входе в бизнес");
											SendClientMessage(playerid, 0x999999FF, "Вы также можете поменять или выключить его командой {FF9900}/bizmusic");
										}
										case 5:
										{
											SendClientMessage(playerid, 0x66CC00FF, "В Вашем бизнесе был оборудован дополнительный склад продуктов повышенной вместимости");

											format(fmt_str, sizeof fmt_str, "Количество слотов для продуктов увеличено с %d до %d", cur_max_prods, GetBusinessMaxProd(businessid));
											SendClientMessage(playerid, 0x999999FF, fmt_str);
										}
										case 6:
										{
											format(fmt_str, sizeof fmt_str, "INSERT INTO business_gps (bid,time) VALUES (%d,%d)", businessid, gettime());
											mysql_query(mysql, fmt_str, false);

											g_business_gps_init = false;

											SendClientMessage(playerid, 0x66CC00FF, "Теперь Ваш бизнес можно будет найти в списке бизнесов {FF9900}(/gps > Бизнес)");
											SendClientMessage(playerid, 0x999999FF, "Это позволит привлечь дополнительных клиентов, тем самым повысить доходы предприятия");
										}
									}
								}
								else SendClientMessage(playerid, 0xFF6600FF, "Ошибка сохранения, повторите попытку {FF0000}(equ-code 23)");
							}
						}
					}
					ShowPlayerBusinessDialog(playerid, BIZ_OPERATION_PARAMS);
				}
			}
			case DIALOG_BIZ_MANAGER:
			{
			    new businessid = GetPlayerListitemValue(playerid, listitem);
			    SetPVarInt(playerid, "ownablebiz_id", businessid);
			    new to_player = GetPVarInt(playerid, "manager_to_player");
			    SendPlayerOffer(playerid, to_player, OFFER_TYPE_BUSINESS_MANAGER, businessid);
			}
			case DIALOG_BIZ_SELL_MY_BIZ:
			{
			    new businessid = GetPlayerListitemValue(playerid, listitem) + 1;
			    SetPVarInt(playerid, "ownablebiz_id", businessid);
			    IntfDialogCallRemote
				(
					playerid, DIALOG_BIZ_SELL_MY_BIZ2, DIALOG_STYLE_MSGBOX,
					"{FFCD00}Продажа бизнеса",
					"{FFFFFF}Вы уверены что хотите продать свой бизнес?",
					"Да", "Нет"
				);
			}
			case DIALOG_BIZ_SELL_MY_BIZ2:
			{
			    new businessid = GetPVarInt(playerid, "ownablebiz_id");
			    new to_player = GetPVarInt(playerid, "sellmybiz_to_player");
			    new price = GetPVarInt(playerid, "sellmybiz_money");

			    new Float: b_pos_x = GetBusinessData(businessid, B_POS_X);
				new Float: b_pos_y = GetBusinessData(businessid, B_POS_Y);
				new Float: b_pos_z = GetBusinessData(businessid, B_POS_Z);

				if(!(IsPlayerInRangeOfPoint(playerid, 7.0, b_pos_x, b_pos_y, b_pos_z) && IsPlayerInRangeOfPoint(to_player, 7.0, b_pos_x, b_pos_y, b_pos_z)))
					return SendClientMessage(playerid, 0xFF6600FF, "Вы и покупатель должны находиться рядом с бизнесом который хотите продать");

			    SendPlayerOffer(playerid, to_player, OFFER_TYPE_SELL_BUSINESS, businessid, price);
			}
			case DIALOG_BIZ_SELL:
			{
				new businessid = GetPVarInt(playerid, "ownablebiz_id");
				if(businessid != -1)
				{
					if(response)
					{
						if(GetBusinessData(businessid, B_ORDER_ID) != -1)
						{
							IntfDialogCallRemote
							(
								playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX,
								"{FF6600}Продажа бизнеса",
								"{FFFFFF}Перед тем как продать бизнес государству\n"\
								"заказ продуктов нужно {FF3333}отменить",
								"Закрыть", ""
							);
						}
						else //SellBusiness(playerid);
						{
							new biz_price = GetBusinessData(businessid, B_PRICE);
							new biz_percent = biz_price / 100 * 60;
							new biz_improvemnts_price = BusinessImprovementsPrice(businessid);

							if(biz_improvemnts_price)
								biz_improvemnts_price = biz_improvemnts_price / 100 * 35;

							new query[200];
							new return_money = (biz_price - biz_percent) + biz_improvemnts_price;

							SetBusinessData(businessid, B_OWNER_ID, 	0);

							format(g_player[playerid][P_BANK], 21, "%s", SetILPlayerInt(playerid, GetPlayerBankMoney(playerid), return_money));

							BankLog(playerid, return_money, "Продажа бизнеса");

							SetBusinessData(businessid, B_IMPROVEMENTS, 	0);

							SetBusinessData(businessid, B_PRODS, 			0);
							SetBusinessData(businessid, B_PROD_PRICE,		0);

							format(g_business[businessid][B_BALANCE], 21, "0");

							SetBusinessData(businessid, B_RENT_DATE,		0);
							SetBusinessData(businessid, B_ENTER_MUSIC,		0);
							SetBusinessData(businessid, B_LOCK_STATUS,	false);

							BusinessHealthPickupInit(businessid);

							format(query, sizeof query, "UPDATE accounts_canvasdev a,business b SET a.bank=%s,b.owner_id=0,b.products=0,b.prod_price=0,b.lock=0 WHERE a.id=%d AND b.id=%d", GetPlayerData(playerid, P_BANK), GetPlayerAccountID(playerid), GetBusinessData(businessid, B_SQL_ID));
							mysql_query(mysql, query, false);

							format(query, sizeof query, "DELETE FROM business_gps WHERE bid=%d", businessid);
							mysql_query(mysql, query, false);

							g_business_gps_init = false;

							ModifyCashBalance(playerid, 0, "Продажа бизнеса государству", false, false);
							CallLocalFunction("UpdateBusinessLabel", "i", businessid);

							SendClientMessage(playerid, 0x66CC00FF, "Вы продали свой бизнес!");

							format(query, sizeof query, "Налог за продажу бизнеса составил 60 процентов от его стоимости {99CC00}(%d руб)", biz_percent);
							SendClientMessage(playerid, 0xCECECEFF, query);

							//format(query, sizeof query, "Test Biz : %d ID", businessid);
							//SendClientMessage(playerid, 0xCECECEFF, query);

							format(query, sizeof query, "Вам было возвращено 35 процентов от стоимости купленных улучшений: {CCFF00}%d руб", biz_improvemnts_price);
							SendClientMessage(playerid, 0xCECECEFF, query);

							format(query, sizeof query, "Итого на банковский счет перечислено: {3399FF}%d руб", return_money);
							SendClientMessage(playerid, 0xFFFFFFFF, query);
						}
					}
				}
			}
			case DIALOG_BIZ_ENTER_MUSIC:
			{
				new businessid = GetPlayerBusiness(playerid);
				if(businessid != -1)
				{
					if(response)
					{
						if(0 <= listitem <= sizeof g_business_sound)
						{
							new query[64];
							format(query, sizeof query, "UPDATE business SET enter_music=%d WHERE id=%d LIMIT 1", GetBusinessData(businessid, B_ENTER_MUSIC), GetBusinessData(businessid, B_SQL_ID));
							mysql_query(mysql, query, false);

							if(listitem > 0)
								PlayerPlaySound(playerid, g_business_sound[listitem - 1], 0.0, 0.0, 0.0);

							SetBusinessData(businessid, B_ENTER_MUSIC, listitem);
							SendClientMessage(playerid, 0x66CC00FF, "Звук при входе в бизнес изменен");
						}
					}
				}
			}
			case DIALOG_BIZ_ENTER:
			{
				new businessid = GetPVarInt(playerid, "biz_enter") - 1;
				DeletePVar(playerid, "biz_enter");

				if(response)
				{
					if(businessid != -1 && GetBusinessData(businessid, B_ENTER_PRICE) > 0)
					{
						if(IsBusinessOwned(businessid))
						{
							if(IsPlayerInRangeOfPoint(playerid, 5.0, GetBusinessData(businessid, B_POS_X), GetBusinessData(businessid, B_POS_Y), GetBusinessData(businessid, B_POS_Z)))
							{
								new price = GetBusinessData(businessid, B_ENTER_PRICE);
								new take_prods = GetBusinessEnterProdCount(businessid);

								if(!VerifyIntString(QueryPlayerBalance(playerid), price)) return SendClientMessage(playerid, 0xCECECEFF, "У Вас недостаточно денег для входа");
								
								if(GetBusinessData(businessid, B_PRODS) >= take_prods)
								{
									AddBusinessProfit(playerid, businessid, price, take_prods);
								}

								SetPlayerUseListitem(playerid, businessid);
								ModifyCashBalance(playerid, -price, "Оплата за вход в бизнес");

								EnterPlayerToBiz(playerid, businessid);
							}
						}
					}
				}
			}
			case DIALOG_BIZ_CAR_MARKET_SRED:
			{
				if(!response) return 1;

				if(GetPlayerData(playerid, P_DRIVING_LIC) < 1)
                	return GameText(playerid, "У Вас нет лицензии на вождение ТС", 2000, 5);

				if((GetPlayerOwnableCars(playerid) + 1) > GetPlayerCarSlots(playerid))
					return SendClientMessage(playerid, 0x3399FFFF, "Все слоты для транспорта заняты. Вы можете увеличить их: {FFFF00}/menu > Дополнительно");

				SetPlayerVirtualWorld(playerid, playerid + 1);
				TogglePlayerControllable(playerid, false);
				SetPlayerInterior(playerid, 4);

				SetPlayerPosEx(playerid, -2000.7031,-1296.6309,1038.5972, 0.0, _, _, false);
				SetPlayerData(playerid, P_BUY_CAR, CreateVehicle(411, -2000.7031,-1296.6309,1034.5972,170.2028, 1, 1, 4));

				SetVehicleVirtualWorld(GetPlayerData(playerid, P_BUY_CAR), playerid + 1);
				LinkVehicleToInterior(GetPlayerData(playerid, P_BUY_CAR), 4);

				SetPlayerCameraPos(playerid, -1998.716308,-1303.332397,1035.359985);
				SetPlayerCameraLookAt(playerid, -1999.810913,-1298.486938,1034.791137);
				SetPVarInt(playerid, "sredcar", 1);
				LoadPlayerCarsShop(playerid);
				
				return 1;
			}
			case DIALOG_BIZ_CAR_MARKET_GRUZ:
			{
				if(!response) return 1;

				if(GetPlayerData(playerid, P_DRIVING_LIC) < 1)
                	return GameText(playerid, "У Вас нет лицензии на вождение ТС", 2000, 5);
                	
				if((GetPlayerOwnableCars(playerid) + 1) > GetPlayerCarSlots(playerid))
					return SendClientMessage(playerid, 0x3399FFFF, "Все слоты для транспорта заняты. Вы можете увеличить их: {FFFF00}/menu > Дополнительно");

				SetPlayerVirtualWorld(playerid, playerid + 1);
			//	SetPlayerPosEx(playerid, 1026.0604,-1883.5897,34.3527, 180.0, _, _, false);
				TogglePlayerControllable(playerid, false);

				SetPlayerData(playerid, P_BUY_CAR, CreateVehicle(15083, 1027.6141,-1892.0331,34.7166,298.6746, 1, 1, 0));

				SetVehicleVirtualWorld(GetPlayerData(playerid, P_BUY_CAR), playerid + 1);
				LinkVehicleToInterior(GetPlayerData(playerid, P_BUY_CAR), 0);

				SetPlayerInterior(playerid, 0);

				SetPlayerCameraPos(playerid, 1042.315307,-1890.139770,36.3141);
				SetPlayerCameraLookAt(playerid, 1032.475219,-1891.380981,35.0);

				SetPlayerInterior(playerid, 0);

			//	ShowPlayerSelectPanel(playerid, SELECT_PANEL_TYPE_CAR_MARKET);
				SetPVarInt(playerid, "gruzcar", 1);
				LoadPlayerCarsShop(playerid);
				//SelectTextDraw(playerid, 0x00F000FF);

				return 1;
			}
			case DIALOG_BIZ_CAR_MARKET_AVIA:
			{
				if(!response) return 1;

                if(GetPlayerData(playerid, P_DRIVING_LIC) < 1)
                	return GameText(playerid, "У Вас нет лицензии на вождение ТС", 2000, 5);

				if((GetPlayerOwnableCars(playerid) + 1) > GetPlayerCarSlots(playerid))
					return SendClientMessage(playerid, 0x3399FFFF, "Все слоты для транспорта заняты. Вы можете увеличить их: {FFFF00}/menu > Дополнительно");

				SetPlayerVirtualWorld(playerid, playerid + 1);
			//	SetPlayerPosEx(playerid, 1026.0604,-1883.5897,34.3527, 180.0, _, _, false);
				TogglePlayerControllable(playerid, false);

				SetPlayerData(playerid, P_BUY_CAR, CreateVehicle(469, -31.9133,936.1386,21.8680,160.1091, 1, 1, 0));

				SetVehicleVirtualWorld(GetPlayerData(playerid, P_BUY_CAR), playerid + 1);
				LinkVehicleToInterior(GetPlayerData(playerid, P_BUY_CAR), 0);

				SetPlayerInterior(playerid, 0);

				SetPlayerCameraPos(playerid, -27.8507,928.0004,24.5853);
				SetPlayerCameraLookAt(playerid, -34.2980,939.8040,21.7852);

				SetPlayerInterior(playerid, 0);

			//	ShowPlayerSelectPanel(playerid, SELECT_PANEL_TYPE_CAR_MARKET);
				SetPVarInt(playerid, "aviacar", 1);
				LoadPlayerCarsShop(playerid);
				CEF_HIDE(playerid, "Interactions");
				//SelectTextDraw(playerid, 0x00F000FF);
				SetPlayerInBiz(playerid, 4);
				return 1;
			}
			case DIALOG_BIZ_CAR_MARKET_KATER:
			{
				if(!response) return 1;

                if(GetPlayerData(playerid, P_DRIVING_LIC) < 1)
                	return GameText(playerid, "У Вас нет лицензии на вождение ТС", 2000, 5);

				if((GetPlayerOwnableCars(playerid) + 1) > GetPlayerCarSlots(playerid))
					return SendClientMessage(playerid, 0x3399FFFF, "Все слоты для транспорта заняты. Вы можете увеличить их: {FFFF00}/menu > Дополнительно");

				SetPlayerVirtualWorld(playerid, playerid + 1);
			//	SetPlayerPosEx(playerid, 1026.0604,-1883.5897,34.3527, 180.0, _, _, false);
				TogglePlayerControllable(playerid, false);

				SetPlayerData(playerid, P_BUY_CAR, CreateVehicle(469,  2690.7903, -3408.1589, -0.2678, 189.6871, 1, 1, 0));

				SetVehicleVirtualWorld(GetPlayerData(playerid, P_BUY_CAR), playerid + 1);
				LinkVehicleToInterior(GetPlayerData(playerid, P_BUY_CAR), 0);

				SetPlayerInterior(playerid, 0);

				SetPlayerCameraPos(playerid, 2674.085449,-3400.375732,8.293850);
				SetPlayerCameraLookAt(playerid, 2678.323730,-3402.177246,6.346755); 

				SetPlayerInterior(playerid, 0);

			//	ShowPlayerSelectPanel(playerid, SELECT_PANEL_TYPE_CAR_MARKET);
				SetPVarInt(playerid, "katercar", 1);
				LoadPlayerCarsShop(playerid);
				CEF_HIDE(playerid, "Interactions");
				//SelectTextDraw(playerid, 0x00F000FF);
				SetPlayerInBiz(playerid, 5);
				return 1;
			}
			case DIALOG_BIZ_CAR_MARKET_MOTO:
			{
				if(!response) return 1;
				
				if(GetPlayerData(playerid, P_DRIVING_LIC) < 1)
                	return GameText(playerid, "У Вас нет лицензии на вождение ТС", 2000, 5);

				if((GetPlayerOwnableCars(playerid) + 1) > GetPlayerCarSlots(playerid))
					return SendClientMessage(playerid, 0x3399FFFF, "Все слоты для транспорта заняты. Вы можете увеличить их: {FFFF00}/menu > Дополнительно");

				SetPlayerVirtualWorld(playerid, playerid + 1);
			//	SetPlayerPosEx(playerid, 1026.0604,-1883.5897,34.3527, 180.0, _, _, false);
				TogglePlayerControllable(playerid, false);

				SetPlayerData(playerid, P_BUY_CAR, CreateVehicle(15139, -2246.7114,277.0202,23.9346,262.9701, 1, 1, 0));

				SetVehicleVirtualWorld(GetPlayerData(playerid, P_BUY_CAR), playerid + 1);
				LinkVehicleToInterior(GetPlayerData(playerid, P_BUY_CAR), 0);

				SetPlayerInterior(playerid, 0);

				SetPlayerCameraPos(playerid, -2242.3931,281.0331,25.5243);
				SetPlayerCameraLookAt(playerid, -2248.1477,275.5012,24.5337);

				SetPlayerInterior(playerid, 0);

			//	ShowPlayerSelectPanel(playerid, SELECT_PANEL_TYPE_CAR_MARKET);
				SetPVarInt(playerid, "motocar", 1);
				LoadPlayerCarsShop(playerid);
				CEF_HIDE(playerid, "Interactions");
				//SelectTextDraw(playerid, 0x00F000FF);
				SetPlayerInBiz(playerid, 0);
				return 1;
			}
			case DIALOG_BIZ_CAR_MARKET_HOME:
			{
				if(!response) return 1;
				
				if(GetPlayerData(playerid, P_DRIVING_LIC) < 1)
                	return GameText(playerid, "У Вас нет лицензии на вождение ТС", 2000, 5);

				if((GetPlayerOwnableCars(playerid) + 1) > GetPlayerCarSlots(playerid))
					return SendClientMessage(playerid, 0x3399FFFF, "Все слоты для транспорта заняты. Вы можете увеличить их: {FFFF00}/menu > Дополнительно");

				SetPlayerVirtualWorld(playerid, playerid + 1);
			//	SetPlayerPosEx(playerid, 1026.0604,-1883.5897,34.3527, 180.0, _, _, false);
				TogglePlayerControllable(playerid, false);

				SetPlayerData(playerid, P_BUY_CAR, CreateVehicle(15277, -2398.1401,192.3957,21.5556,260.6368, 1, 1, 0));

				SetVehicleVirtualWorld(GetPlayerData(playerid, P_BUY_CAR), playerid + 1);
				LinkVehicleToInterior(GetPlayerData(playerid, P_BUY_CAR), 0);

				SetPlayerInterior(playerid, 0);

				SetPlayerCameraPos(playerid, -2387.3169,202.7339,24.1007);
				SetPlayerCameraLookAt(playerid, -2401.2058,189.0401,21.1746);

				SetPlayerInterior(playerid, 0);

			//	ShowPlayerSelectPanel(playerid, SELECT_PANEL_TYPE_CAR_MARKET);
				SetPVarInt(playerid, "homecar", 1);
				LoadPlayerCarsShop(playerid);
				//SelectTextDraw(playerid, 0x00F000FF);
				
				return 1;
			}
			case DIALOG_BIZ_CAR_MARKET_NIZ:
			{
				if(!response) return 1;
				
				if(GetPlayerData(playerid, P_DRIVING_LIC) < 1) return GameText(playerid, "У Вас нет лицензии на вождение ТС", 2000, 5);

				if((GetPlayerOwnableCars(playerid) + 1) > GetPlayerCarSlots(playerid)) return SendClientMessage(playerid, 0x3399FFFF, "Все слоты для транспорта заняты. Вы можете увеличить их: {FFFF00}/menu > Дополнительно");

				SetPlayerPosEx(playerid, 262.2371,2445.2175,1000.7915, 180.0, _, _, false);
				TogglePlayerControllable(playerid, false);

				SetPlayerData(playerid, P_BUY_CAR, CreateVehicle(411, 262.2371,2431.2175,1000.7915,326.5478, 1, 1, 5));

				SetVehicleVirtualWorld(GetPlayerData(playerid, P_BUY_CAR), playerid + 1);
				LinkVehicleToInterior(GetPlayerData(playerid, P_BUY_CAR), 4);

				SetPlayerVirtualWorld(playerid, playerid + 1);
				SetPlayerInterior(playerid, 4);

				SetPlayerCameraPos(playerid, 261.873260, 2438.841552, 1001.580139);
				SetPlayerCameraLookAt(playerid, 261.866110, 2433.895507, 1000.847534);
			
				LoadPlayerCarsShop(playerid);
				CEF_HIDE(playerid, "Interactions");
				SetPlayerInBiz(playerid, 2);
				return 1;
			}
			case DIALOG_BIZ_CAR_MARKET:
			{
				if(!response) return 1;
				
				if(GetPlayerData(playerid, P_DRIVING_LIC) < 1)
                	return GameText(playerid, "У Вас нет лицензии на вождение ТС", 2000, 5);

				if((GetPlayerOwnableCars(playerid) + 1) > GetPlayerCarSlots(playerid))
					return SendClientMessage(playerid, 0x3399FFFF, "Все слоты для транспорта заняты. Вы можете увеличить их: {FFFF00}/menu > Дополнительно");

				SetPlayerVirtualWorld(playerid, playerid + 1);
				SetPlayerPosEx(playerid, 1853.8215,2813.3525,20.1436,270.9554, 0, _, false);
				TogglePlayerControllable(playerid, false);

				SetPlayerData(playerid, P_BUY_CAR, CreateVehicle(400, 1847.1146,2819.2698,20.5752,321.0539, 1, 1, 0));

				SetVehicleVirtualWorld(GetPlayerData(playerid, P_BUY_CAR), playerid + 1);
				LinkVehicleToInterior(GetPlayerData(playerid, P_BUY_CAR), 0);

				SetPlayerInterior(playerid, 0);

				SetPlayerCameraPos(playerid, 1856.1144, 2822.7991, 22.2357);
				SetPlayerCameraLookAt(playerid, 1847.2103, 2819.2700, 20.5730);

				SetPVarInt(playerid, "STONKScar", 1);
				LoadPlayerCarsShop(playerid);

				SetPlayerInBiz(playerid, 1);
				return 1;
			}
			
			case DIALOG_BIZ_SHOP_ZAKUS:
			{
				new businessid = GetPlayerInBiz(playerid);
				if(businessid != -1)
				{
					if(response)
					{
						if(IsPlayerInBuyPosBiz(playerid, businessid, BUSINESS_TYPE_ZAKUS))
						{
							new price;
							new take_prods;

							switch(listitem + 1)
							{
								case 1:
								{
									price = 10000;
									take_prods = 2;

									if(!VerifyIntString(QueryPlayerBalance(playerid), price)) return SendClientMessage(playerid, 0xFF6600FF, "Стандартный куриный обед стоит 700 рублей");
									
									if(GetBusinessData(businessid, B_PRODS) >= take_prods)
									{
										AddBusinessProfit(playerid, businessid, price, take_prods);
									}

									ModifyCashBalance(playerid, -price, "Покупка стандартного куриного обеда");

									Action(playerid, "купил(а) стандартный куриный обед");
									SendClientMessage(playerid, 0x999999FF, "{CECECE}Используйте {6699FF}/eat {CECECE}чтобы поесть или {6699FF}/put {CECECE}чтобы положить поднос с едой");
									SetPVarInt(playerid,"respeat",1);
									SetPlayerAttachedObject(playerid, 5, 10024, 1, 0.104, 0.365, -0.267, 109.5, 126.1, -43.5, 1.0, 1.0, 1.0);
									ApplyAnimationEx(playerid, "CARRY", "crry_prtial", 4.1, 1, 1, 1, 1, 1, 0, USE_ANIM_TYPE_NONE - 1);
									CEF_CREATE(playerid, 2, 4, "Interactions", "[[5, \"Перекусить\"], [6, \"Выбросить поднос\"]]");
									g_cursor[playerid] = 1;
									
								}
								case 2:
								{
									price = 12500;
									take_prods = 2;

									if(!VerifyIntString(QueryPlayerBalance(playerid), price)) return SendClientMessage(playerid, 0xCECECEFF, "Набор ассорти из курицы стоит 1500 рублей");
									
									if(GetBusinessData(businessid, B_PRODS) >= take_prods)
									{
										AddBusinessProfit(playerid, businessid, price, take_prods);
									}
									ModifyCashBalance(playerid, -price, "Покупка набора ассорти из курицы");
									Action(playerid, "купил(а) набор ассорти из курицы");
									SendClientMessage(playerid, 0x999999FF, "{CECECE}Используйте {6699FF}/eat {CECECE}чтобы поесть или {6699FF}/put {CECECE}чтобы положить поднос с едой");
									SetPVarInt(playerid,"respeat",2);
									SetPlayerAttachedObject(playerid, 5, 10024, 1, 0.104, 0.365, -0.267, 109.5, 126.1, -43.5, 1.0, 1.0, 1.0);
									ApplyAnimationEx(playerid, "CARRY", "crry_prtial", 4.1, 1, 1, 1, 1, 1, 0, USE_ANIM_TYPE_NONE - 1);
									CEF_CREATE(playerid, 2, 4, "Interactions", "[[5, \"Перекусить\"], [6, \"Выбросить поднос\"]]");
									g_cursor[playerid] = 1;
									
								}
								case 3:
								{
									price = 23120;
									take_prods = 2;

         							if(!VerifyIntString(QueryPlayerBalance(playerid), price)) return SendClientMessage(playerid, 0xCECECEFF, "Набор королевского обеда стоит 2500 рублей");
									
									if(GetBusinessData(businessid, B_PRODS) >= take_prods)
									{
										AddBusinessProfit(playerid, businessid, price, take_prods);
									}
									
									ModifyCashBalance(playerid, -price, "Покупка набора королевского обеда");
									Action(playerid, "купил(а) набор королевского обеда");
									SendClientMessage(playerid, 0x999999FF, "{CECECE}Используйте {6699FF}/eat {CECECE}чтобы поесть или {6699FF}/put {CECECE}чтобы положить поднос с едой");
									SetPVarInt(playerid,"respeat",3);
									SetPlayerAttachedObject(playerid, 5, 10024, 1, 0.104, 0.365, -0.267, 109.5, 126.1, -43.5, 1.0, 1.0, 1.0);
									ApplyAnimationEx(playerid, "CARRY", "crry_prtial", 4.1, 1, 1, 1, 1, 1, 0, USE_ANIM_TYPE_NONE - 1);
									CEF_CREATE(playerid, 2, 4, "Interactions", "[[5, \"Перекусить\"], [6, \"Выбросить поднос\"]]");
									g_cursor[playerid] = 1;
								}
        						case 4:
								{
									price = 5768;

									if(!VerifyIntString(QueryPlayerBalance(playerid), price)) return SendClientMessage(playerid, 0x999999FF, "У Вас не хватает денег");

									if(GetBusinessData(businessid, B_PRODS) >= take_prods)
									{
										AddBusinessProfit(playerid, businessid, price, take_prods);
									}
									ModifyCashBalance(playerid, -price, "Покупка в закусочной");
									GiveIteam(playerid, 280, 1, 1, 0);

									Action(playerid, "купил(а) напиток", 	15.0, false);
								}
								case 5:
								{
									price = 4000;

									if(!VerifyIntString(QueryPlayerBalance(playerid), price)) return SendClientMessage(playerid, 0x999999FF, "У Вас не хватает денег");

									if(GetBusinessData(businessid, B_PRODS) >= take_prods)
									{
										AddBusinessProfit(playerid, businessid, price, take_prods);
									}
									ModifyCashBalance(playerid, -price, "Покупка в закусочной");
									GiveIteam(playerid, 280, 1, 1, 7);

									Action(playerid, "купил(а) чай", 	15.0, false);
								}
							}
						}
					}
				}
			}
			case DIALOG_BIZ_SHOP_KONDITER:
			{
				new businessid = GetPlayerInBiz(playerid);
				if(businessid != -1)
				{
					if(response)
					{
						if(IsPlayerInBuyPosBiz(playerid, businessid, BUSINESS_TYPE_KONDITER))
						{
							new price;
							new take_prods;

							switch(listitem + 1)
							{
								case 1:
								{
									price = 630;
									take_prods = 2;

									if(!VerifyIntString(QueryPlayerBalance(playerid), price)) return SendClientMessage(playerid, 0xFF6600FF, "Стандартный куриный обед стоит 630 рублей");

									if(GetBusinessData(businessid, B_PRODS) >= take_prods)
									{
										AddBusinessProfit(playerid, businessid, price, take_prods);
									}
									ModifyCashBalance(playerid, -price, "Покупка маленького десерта");

									Action(playerid, "купил(а) маленький десерт");
									SendClientMessage(playerid, 0x999999FF, "{CECECE}Используйте {6699FF}/eat {CECECE}чтобы поесть или {6699FF}/put {CECECE}чтобы положить поднос с едой");
									SetPVarInt(playerid,"respeat",1);
									SetPlayerAttachedObject(playerid, 5, 10024, 1, 0.104, 0.365, -0.267, 109.5, 126.1, -43.5, 1.0, 1.0, 1.0);
									ApplyAnimationEx(playerid, "CARRY", "crry_prtial", 4.1, 1, 1, 1, 1, 1, 0, USE_ANIM_TYPE_NONE - 1);
									CEF_CREATE(playerid, 2, 4, "Interactions", "[[5, \"Перекусить\"], [6, \"Выбросить поднос\"]]");
									g_cursor[playerid] = 1;

								}
								case 2:
								{
									price = 1120;
									take_prods = 3;

									if(!VerifyIntString(QueryPlayerBalance(playerid), price)) return SendClientMessage(playerid, 0xCECECEFF, "Набор ассорти из курицы стоит 1120 рублей");

									if(GetBusinessData(businessid, B_PRODS) >= take_prods)
									{
										AddBusinessProfit(playerid, businessid, price, take_prods);
									}
									ModifyCashBalance(playerid, -price, "Покупка среднего десерта");
									Action(playerid, "купил(а) средний десерт");
									SendClientMessage(playerid, 0x999999FF, "{CECECE}Используйте {6699FF}/eat {CECECE}чтобы поесть или {6699FF}/put {CECECE}чтобы положить поднос с едой");
									SetPVarInt(playerid,"respeat",2);
									SetPlayerAttachedObject(playerid, 5, 10024, 1, 0.104, 0.365, -0.267, 109.5, 126.1, -43.5, 1.0, 1.0, 1.0);
									ApplyAnimationEx(playerid, "CARRY", "crry_prtial", 4.1, 1, 1, 1, 1, 1, 0, USE_ANIM_TYPE_NONE - 1);
									CEF_CREATE(playerid, 2, 4, "Interactions", "[[5, \"Перекусить\"], [6, \"Выбросить поднос\"]]");
									g_cursor[playerid] = 1;
								}
								case 3:
								{
									price = 1575;
									take_prods = 3;

         							if(!VerifyIntString(QueryPlayerBalance(playerid), price)) return SendClientMessage(playerid, 0xCECECEFF, "Набор королевского обеда стоит 1575 рублей");
									
									if(GetBusinessData(businessid, B_PRODS) >= take_prods)
									{
										AddBusinessProfit(playerid, businessid, price, take_prods);
									}
									ModifyCashBalance(playerid, -price, "Покупка большого десерта");
									Action(playerid, "купил(а) большой десерт");
									SendClientMessage(playerid, 0x999999FF, "{CECECE}Используйте {6699FF}/eat {CECECE}чтобы поесть или {6699FF}/put {CECECE}чтобы положить поднос с едой");
									SetPVarInt(playerid,"respeat",3);
									SetPlayerAttachedObject(playerid, 5, 10024, 1, 0.104, 0.365, -0.267, 109.5, 126.1, -43.5, 1.0, 1.0, 1.0);
									ApplyAnimationEx(playerid, "CARRY", "crry_prtial", 4.1, 1, 1, 1, 1, 1, 0, USE_ANIM_TYPE_NONE - 1);
									CEF_CREATE(playerid, 2, 4, "Interactions", "[[5, \"Перекусить\"], [6, \"Выбросить поднос\"]]");
									g_cursor[playerid] = 1;
									
								}
        						case 4:
								{
									price = 227;

									if(!VerifyIntString(QueryPlayerBalance(playerid), price)) return SendClientMessage(playerid, 0x999999FF, "У Вас не хватает денег");

									if(GetBusinessData(businessid, B_PRODS) >= take_prods)
									{
										AddBusinessProfit(playerid, businessid, price, take_prods);
									}
									ModifyCashBalance(playerid, -price, "Покупка в закусочной");
									GivePlayerDrinkItem(playerid, 0);

									Action(playerid, "купил(а) напиток", 15.0, false);
								}
							}
						}
					}
				}
			}
	case DIALOG_BIZ_VETRIKI:
	{
		if(!response) return 1;

		switch(listitem + 1)
		{
			case 1:
			{
				if(GetIteam(playerid, 167) < 1) return SendClientMessage(playerid, 0xCECECEFF, "{B8CEF6}У вас нет с собой {FFFFFF}требуемого компонента"), GameText(playerid, "~r~Нет требуемого~n~Компонента", 3000, 2);

				Progress_Bar_Menu(playerid, 6, 15, 15);		
			}
			case 2:
			{
				if(GetIteam(playerid, 166) < 1) return SendClientMessage(playerid, 0xCECECEFF, "{B8CEF6}У вас нет с собой {FFFFFF}требуемого компонента"), GameText(playerid, "~r~Нет требуемого~n~Компонента", 3000, 2);

				Progress_Bar_Menu(playerid, 7, 15, 15);
			}
		}
	}
	case DIALOG_ACTION_FISH:
	{
		if(!response)
		{
			CEF_HIDE(playerid, "Fishing");
			CEF_HIDE(playerid, "Interactions");
            CEF_CREATE(playerid, 2, 4, "Interactions", "[[49, \"Начать рыбалку\"]]");
			g_player_status_fish[playerid] = 2;

			SetCameraBehindPlayer(playerid);
			TogglePlayerControllable(playerid,true);
			CEF_CREATE(playerid, 1, 2, "window.setCursorStatus(1, 0)");

			SCM(playerid, 0x56e65eFF, "Вы отпустили рыбу в воду.");

			GameText(playerid, "РЫБАК +4", 3000, 2);
			return true;
		}

		CEF_HIDE(playerid, "Interactions");
	    CEF_CREATE(playerid, 1, 2, "window.setCursorStatus(1, 0)");

		if(g_player_type_fish[playerid] == 9)
		{
			switch(random(15))
			{
				case 0:
				{
					GiveIteam(playerid, 133, 1, g_player_type_fish_ves[playerid], g_player_type_fish[playerid]);
		            SCM(playerid, 0x56e65eFF, "Вы забрали рыбу себе.");

					GiveRandCase(playerid);

		            GameText(playerid, "РЫБАК +2", 3000, 2);

					AddPlayerAchiv(playerid, 25);
				}
				default: 
				{
				    SCM(playerid, 0xead671FF, "Угорь ударил вас током и уплыл.");
			    }
			}
		}
		else
		{
            GiveIteam(playerid, 133, 1, g_player_type_fish_ves[playerid], g_player_type_fish[playerid]);
		    SCM(playerid, 0x56e65eFF, "Вы забрали рыбу себе.");

			GiveRandCase(playerid);

		    GameText(playerid, "РЫБАК +2", 3000, 2);
		}
	}
	case DIALOG_BIZ_SHOP_FISH:
	{
		new businessid = GetNearestBusiness(playerid, 3.0);

		if(businessid == -1) 
			return true;
		
		if(!response) 
			return true;
				
		new price, 
			item_id, 
			indx, 
			count,
			name[24];
				
		switch(listitem + 1)
		{
			case 1: price = 25000, item_id = 132, indx = 0, count = 1, format(name, sizeof name, "Поплавочная удочка");
			case 2:	price = 40000, item_id = 132, indx = 1, count = 1, format(name, sizeof name, "Улучшенная удочка");
			case 3:	price = 70000, item_id = 132, indx = 2, count = 1, format(name, sizeof name, "Спиннинг");
			case 4:	price = 15000, item_id = 325, indx = 0, count = 1, format(name, sizeof name, "Леска 0.15мм");
			case 5:	price = 11000, item_id = 325, indx = 1, count = 1, format(name, sizeof name, "Леска 0.3мм");
			case 6:	price = 20000, item_id = 325, indx = 2, count = 1, format(name, sizeof name, "Леска 0.85мм");
			case 7:	price = 3500, item_id = 326, indx = 0, count = 10, format(name, sizeof name, "Кусочки хлеба");
			case 8:	price = 7000, item_id = 326, indx = 1, count = 10, format(name, sizeof name, "Лягушка");
			case 9:	price = 7000, item_id = 326, indx = 2, count = 10, format(name, sizeof name, "Кузнечик");
			case 10: price = 1000, item_id = 326, indx = 3, count = 10, format(name, sizeof name, "Червь");
			case 11: price = 1500, item_id = 326, indx = 4, count = 10, format(name, sizeof name, "Мотыль");
			case 12: price = 1500, item_id = 326, indx = 5, count = 10, format(name, sizeof name, "Опарыш");
			case 13: price = 35000, item_id = 15576, indx = 0, count = 10, format(name, sizeof name, "Акваланг");
			
		}

		if(GetInventorySlots(playerid) == -1) 
			return SCM(playerid, 0xCECECEFF, "В вашем инвентаре нет свободного места");

		if(!VerifyIntString(QueryPlayerBalance(playerid), price)) 
			return SendClientMessage(playerid, 0xCECECEFF, "Недостаточно средств");

		SCMF(playerid, 0xbacb69FF, "Вы купили \"%s\" за %d руб.", name, price);

		ModifyCashBalance(playerid, -price, "Покупка в магазине рыбалова");

		if(listitem + 1 != 13)
			GiveIteam(playerid, item_id, 1, count, indx);
		else
			GiveSkin(playerid, item_id);

		if(GetBusinessData(businessid, B_PRODS) >= 1)
			AddBusinessProfit(playerid, businessid, price, 1);
	}
	case DIALOG_BIZ_SHOP_24_7_APROVED:
	{
		if(!response) return 0;

		switch(listitem){
			case 4: IntfDialogCallRemote(playerid, DIALOG_LOTTERY, DIALOG_STYLE_TABLIST_HEADERS, "Список лотерей", "Название \t № \t Цена билета \t Бюджет \t Статус\n 1. 'Зимняя сказка' \t №:1 \t 350.000 руб \t 100.000.000 руб \t активна ", "Выбрать", "Закрыть");
		    default:{
                string_dialog[0] = EOS;
                format(string_dialog, sizeof string_dialog, "{FFFFFF}Вы подтверждаете покупку данного товара?\n\n{E0B543}\n\n\t{FFFFFF}Товар: {E0B543}%s\n\t{FFFFFF}Стоимость: {E09043}%d руб", shop24_info[listitem][shop_24_name], shop24_info[listitem][shop_24_price]);     
		        IntfDialogCallRemote(playerid, DIALOG_BIZ_SHOP_24_7, DIALOG_STYLE_MSGBOX, "Подтверждение", string_dialog, "Купить", "Отмена");
			}
		}

		SetPVarInt(playerid, "24_Market_Type", listitem);
	}
    case DIALOG_BIZ_SHOP_24_7:
	{
		if(!response) return callcmd::buy(playerid, "");

		new itemslists = GetPVarInt(playerid, "24_Market_Type");
		new price = shop24_info[itemslists][shop_24_price];
		new item = shop24_info[itemslists][shop_24_id_item];
		new type = shop24_info[itemslists][shop_24_type];

		if(!VerifyIntString(QueryPlayerBalance(playerid), price)) return SCM(playerid, COLOR_GREY, "Недостаточно средств для покупки."), callcmd::buy(playerid, "");

        ModifyCashBalance(playerid, -price, "Покупка в Супермаркете");

        SCMF(playerid, 0xc6e469FF, "Вы купили \"%s\" за %s руб.", shop24_info[itemslists][shop_24_name], formatInt(price));

		if(type == 1){GiveWeapon(playerid, item, 1);}else{GiveIteam(playerid, item, 1, 1, 0);}
			
		if(GetBusinessData(GetPlayerInBiz(playerid), B_PRODS) >= 1) AddBusinessProfit(playerid, GetPlayerInBiz(playerid), price / 100 * 20, 1);

		callcmd::buy(playerid, "");
	}
			case DIALOG_BIZ_SHOP_GARDEN_ACCEPT:
			{
				if(!response)
					return callcmd::buy(playerid, "");

				new businessid = GetPlayerInBiz(playerid);

				new price, item_id, indx;

				new type = GetPVarInt(playerid, "shop_garden_type");

				switch(type)
				{
					case 1: item_id = 173, indx = 0;
					case 2:	item_id = 174, indx = 0;
					case 3: price = 25000, item_id = 168, indx = 0;
					case 4: item_id = 336, indx = 0;
					case 5: item_id = 336, indx = 1;
					case 6: item_id = 336, indx = 2;
					case 7: item_id = 336, indx = 3;
					case 8: item_id = 336, indx = 4;
					case 9: item_id = 336, indx = 5;
					case 10: price = 15000, item_id = 0, indx = 0;
				}

				if(type != 3 && type != 10)
				{
					if(strval(inputtext) > 0 && IsNumeric(inputtext) && strval(inputtext) < 100)
						price = 15000 * strval(inputtext);
					else
						return SCM(playerid, COLOR_GREY, "За один раз можно приобрести от 1 до 100 шт.");
				}

				if(!VerifyIntString(QueryPlayerBalance(playerid), price))
					return SCM(playerid, COLOR_GREY, "Недостаточно средств для покупки."), callcmd::buy(playerid, "");

				if(type == 10)
					GiveWeapon(playerid, 6, 1), SCMF(playerid, 0xc6e469FF, "Вы купили \"Лопата\" за %s руб.", formatInt(price));
				else if(type == 3)
					GiveIteam(playerid, item_id, 1, 1, indx), SCMF(playerid, 0xc6e469FF, "Вы купили \"%s\" за %s руб.", ItemsInfo[item_id], formatInt(price));
				else
					GiveIteam(playerid, item_id, 1, strval(inputtext), indx), SCMF(playerid, 0xc6e469FF, "Вы купили \"%s\" за %s руб.", ItemsInfo[item_id], formatInt(price));

				ModifyCashBalance(playerid, -price, "Покупка в магазине садовод");

				if(GetBusinessData(businessid, B_PRODS) >= 1)
					AddBusinessProfit(playerid, businessid, price / 100 * 20, 1);

				callcmd::buy(playerid, "");
			}
			case DIALOG_BIZ_SHOP_GARDEN:
			{
				new businessid = GetPlayerInBiz(playerid);

				if(businessid != -1)
				{
					if(!response) return 1;

					if(GetInventorySlots(playerid) == -1) return GameText(playerid, "~r~В вашем инвентаре ~n~нет свободного места", 3000, 2);

					if(IsPlayerInBuyPosBiz(playerid, businessid, BUSINESS_TYPE_SHOP_GARDEN))
					{
						switch(listitem + 1)
						{
							case 1:
							{
								IntfDialogCallRemote
								(
								    playerid, DIALOG_BIZ_SHOP_GARDEN_ACCEPT, DIALOG_STYLE_INPUT,
                                    "Подтверждение покупки",
                                    "{FFFFFF}Вы подтверждаете покупку данного товара?\n\n\
                                    {FFFFFF}Товар: {E0B543}Семена томата\n\
                                    {FFFFFF}Стоимость: {E09043}875 руб",
                                    "Купить", "Отмена"
                                );
							}
							case 2:
							{
								IntfDialogCallRemote
								(
									playerid, DIALOG_BIZ_SHOP_GARDEN_ACCEPT, DIALOG_STYLE_INPUT,
									"{FFFFFF}Подтверждение",
									"{FFFFFF}Вы подтверждаете покупку данного товара?\n\n\n\
									{FFFFFF}Товар: {e5bd44}Семена огурцов\n\
									{FFFFFF}Стоимость: {dc8d47}5.700 руб за 1 шт.\n\n\
									{FFFFFF}Укажите количество, которое хотите приобрести:",
									"Купить", "Отмена"
								);
							}
							case 3:
							{
								IntfDialogCallRemote
								(
									playerid, DIALOG_BIZ_SHOP_GARDEN_ACCEPT, DIALOG_STYLE_MSGBOX,
									"{FFFFFF}Подтверждение",
									"{FFFFFF}Вы подтверждаете покупку данного товара?\n\n\n\
									{FFFFFF}Товар: {e5bd44}Лейка\n\
									{FFFFFF}Стоимость: {dc8d47}25.000 руб",
									"Купить", "Отмена"
								);
							}
							case 4:
							{
								IntfDialogCallRemote
								(
									playerid, DIALOG_BIZ_SHOP_GARDEN_ACCEPT, DIALOG_STYLE_INPUT,
									"{FFFFFF}Подтверждение",
									"{FFFFFF}Вы подтверждаете покупку данного товара?\n\n\n\
									{FFFFFF}Товар: {e5bd44}Семена картофеля\n\
									{FFFFFF}Стоимость: {dc8d47}5.700 руб за 1 шт.\n\n\
									{FFFFFF}Укажите количество, которое хотите приобрести:",
									"Купить", "Отмена"
								);
							}
							case 5:
							{
								IntfDialogCallRemote
								(
									playerid, DIALOG_BIZ_SHOP_GARDEN_ACCEPT, DIALOG_STYLE_INPUT,
									"{FFFFFF}Подтверждение",
									"{FFFFFF}Вы подтверждаете покупку данного товара?\n\n\n\
									{FFFFFF}Товар: {e5bd44}Семена свёклы\n\
									{FFFFFF}Стоимость: {dc8d47}5.700 руб за 1 шт.\n\n\
									{FFFFFF}Укажите количество, которое хотите приобрести:",
									"Купить", "Отмена"
								);
							}
							case 6:
							{
								IntfDialogCallRemote
								(
									playerid, DIALOG_BIZ_SHOP_GARDEN_ACCEPT, DIALOG_STYLE_INPUT,
									"{FFFFFF}Подтверждение",
									"{FFFFFF}Вы подтверждаете покупку данного товара?\n\n\n\
									{FFFFFF}Товар: {e5bd44}Семена перца\n\
									{FFFFFF}Стоимость: {dc8d47}5.700 руб за 1 шт.\n\n\
									{FFFFFF}Укажите количество, которое хотите приобрести:",
									"Купить", "Отмена"
								);
							}
							case 7:
							{
								IntfDialogCallRemote
								(
									playerid, DIALOG_BIZ_SHOP_GARDEN_ACCEPT, DIALOG_STYLE_INPUT,
									"{FFFFFF}Подтверждение",
									"{FFFFFF}Вы подтверждаете покупку данного товара?\n\n\n\
									{FFFFFF}Товар: {e5bd44}Семена баклажана\n\
									{FFFFFF}Стоимость: {dc8d47}5.700 руб за 1 шт.\n\n\
									{FFFFFF}Укажите количество, которое хотите приобрести:",
									"Купить", "Отмена"
								);
							}
							case 8:
							{
								IntfDialogCallRemote
								(
									playerid, DIALOG_BIZ_SHOP_GARDEN_ACCEPT, DIALOG_STYLE_INPUT,
									"{FFFFFF}Подтверждение",
									"{FFFFFF}Вы подтверждаете покупку данного товара?\n\n\n\
									{FFFFFF}Товар: {e5bd44}Семена капусты\n\
									{FFFFFF}Стоимость: {dc8d47}5.700 руб за 1 шт.\n\n\
									{FFFFFF}Укажите количество, которое хотите приобрести:",
									"Купить", "Отмена"
								);
							}
							case 9:
							{
								IntfDialogCallRemote
								(
									playerid, DIALOG_BIZ_SHOP_GARDEN_ACCEPT, DIALOG_STYLE_INPUT,
									"{FFFFFF}Подтверждение",
									"{FFFFFF}Вы подтверждаете покупку данного товара?\n\n\n\
									{FFFFFF}Товар: {e5bd44}Семена моркови\n\
									{FFFFFF}Стоимость: {dc8d47}5.700 руб за 1 шт.\n\n\
									{FFFFFF}Укажите количество, которое хотите приобрести:",
									"Купить", "Отмена"
								);
							}
							case 10:
							{
								IntfDialogCallRemote
								(
									playerid, DIALOG_BIZ_SHOP_GARDEN_ACCEPT, DIALOG_STYLE_MSGBOX,
									"{FFFFFF}Подтверждение",
									"{FFFFFF}Вы подтверждаете покупку данного товара?\n\n\n\
									{FFFFFF}Товар: {e5bd44}Лопата\n\
									{FFFFFF}Стоимость: {dc8d47}15.000 руб",
									"Купить", "Отмена"
								);
							}
						}
						SetPVarInt(playerid, "shop_garden_type", listitem + 1);

					}
				}
			}
			case DIALOG_BIZ_AVTOZAP_1:
			{
				new businessid = GetPlayerInBiz(playerid);
				if(response)
				{
    				new price;
			    	new take_prods;
					switch(listitem)
					{
					    case 0:
						{
							price = 200;
							take_prods = 2;
							if(VerifyIntString(QueryPlayerBalance(playerid), price))
							{
								if(GetBusinessData(businessid, B_PRODS) >= take_prods)
								{
									AddBusinessProfit(playerid, businessid, price, take_prods);
								}
								ModifyCashBalance(playerid, -price, "Покупка инструментов");

								SendClientMessage(playerid, 0x66CC00FF, "Вы купили моторное масло. Чтобы его заменить, езжайте в СТО (Арзамас)");

							}
							else SendClientMessage(playerid, 0x888888FF, "Моторное масло стоит 200 рублей");
						}
						case 1:
						{
							price = 300;
							take_prods = 4;
							if(VerifyIntString(QueryPlayerBalance(playerid), price))
							{
								if(GetBusinessData(businessid, B_PRODS) >= take_prods)
								{
									AddBusinessProfit(playerid, businessid, price, take_prods);
								}

								ModifyCashBalance(playerid, -price, "Покупка инструментов");

								GiveIteam(playerid, 166, 1, 1, 0);

								SendClientMessage(playerid, 0x66CC00FF, "Вы купили воздушный фильтр. Чтобы его заменить, езжайте в СТО (Арзамас)");
							}
							else SendClientMessage(playerid, 0x888888FF, "Воздушный фильтр стоит 300 рублей");
						}
						case 2:
						{
							price = 100;
							take_prods = 3;
							if(VerifyIntString(QueryPlayerBalance(playerid), price))
							{
								if(GetBusinessData(businessid, B_PRODS) >= take_prods)
								{
									AddBusinessProfit(playerid, businessid, price, take_prods);
								}
								ModifyCashBalance(playerid, -price, "Покупка инструментов");

								GiveIteam(playerid, 167, 1, 1, 0);

								SendClientMessage(playerid, 0x66CC00FF, "Вы купили маслянный фильтер. Чтобы его заменить, езжайте в СТО (Арзамас)");

							}
							else SendClientMessage(playerid, 0x888888FF, "Маслянный фильтр стоит 100 рублей");
						}
						case 3:
						{
							price = 30000;
							take_prods = 4;
							if(VerifyIntString(QueryPlayerBalance(playerid), price))
							{
								if(GetBusinessData(businessid, B_PRODS) >= take_prods)
								{
									AddBusinessProfit(playerid, businessid, price, take_prods);
								}

								ModifyCashBalance(playerid, -price, "Покупка инструментов");

								SendClientMessage(playerid, 0x33AA33FF, "Вы купили савбуфер.");
								SendClientMessage(playerid, 0xFFFFFFFF, "Установить в авто {33AA33}/sab{FFFFFF}, снять с авто {33AA33}/remove_sab");
							}
							else SendClientMessage(playerid, 0x888888FF, "Савбуфер стоит 30.000 рублей");
						}
						case 4:
						{
							price = 350000;
							take_prods = 2;

							if(VerifyIntString(QueryPlayerBalance(playerid), price))
							{
								if(GetBusinessData(businessid, B_PRODS) >= take_prods)
								{
									AddBusinessProfit(playerid, businessid, price, take_prods);
								}

								ModifyCashBalance(playerid, -price, "Покупка автосигнализации");

								GiveIteam(playerid, 256, 1, 1, 0);
								SendClientMessage(playerid, 0x66CC00FF, "Вы купили автосигнализацию");
								SendClientMessage(playerid, 0x66CC00FF, "Использовать ключ: {2f89f7}/keys");
								
							}
							else SendClientMessage(playerid, 0xCECECEFF, "Автосигнализация стоит 350.000 рублей");
						}
						case 5:
						{
							price = 15000;
							take_prods = 2;

							if(VerifyIntString(QueryPlayerBalance(playerid), price))
							{
								if(GetBusinessData(businessid, B_PRODS) >= take_prods)
								{
									AddBusinessProfit(playerid, businessid, price, take_prods);
								}

								ModifyCashBalance(playerid, -price, "Покупка рем. комплекта");

								GiveIteam(playerid, 44, 1, 1, 0);
									
    								//BattlePass_Completingtasks(playerid, 1, 10);
								SendClientMessage(playerid, 0x66CC00FF, "Вы купили рем. комплект");
								SendClientMessage(playerid, 0x66CC00FF, "Использовать рем. комплект: {2f89f7}через инвентарь или /fixcar");
								
							}
							else SendClientMessage(playerid, 0xCECECEFF, "Рем. комплект стоит 15.000 рублей");
						}
						case 6:
						{
							price = 50000;
							take_prods = 2;

							if(VerifyIntString(QueryPlayerBalance(playerid), price))
							{
								if(GetBusinessData(businessid, B_PRODS) >= take_prods)
								{
									AddBusinessProfit(playerid, businessid, price, take_prods);
								}

								ModifyCashBalance(playerid, -price, "Покупка домкрата");

								GiveIteam(playerid, 361, 1, 1, 0);
									
								SendClientMessage(playerid, 0x66CC00FF, "Вы купили домкрат");
								SendClientMessage(playerid, 0x66CC00FF, "Использовать домкрат: {2f89f7}через инвентарь");
								
							}
							else SendClientMessage(playerid, 0xCECECEFF, "Домкрат стоит 50.000 рублей");
						}
					}
				}
			}
			case DIALOG_BIZ_CELL_SALON:
			{
				new businessid = GetPlayerInBiz(playerid);
				if(businessid != -1)
				{
					if(response)
					{
						if(IsPlayerInBuyPosBiz(playerid, businessid, BUSINESS_TYPE_CELL_SALON))
						{
							new price;
							new take_prods;

							switch(listitem + 1)
							{
								case 1:
								{
									price = 7350;
									take_prods = 2;

									if(!GetPlayerPhone(playerid))
									{
										if(VerifyIntString(QueryPlayerBalance(playerid), price))
										{
											if(GetBusinessData(businessid, B_PRODS) >= take_prods)
											{
												AddBusinessProfit(playerid, businessid, price, take_prods);
											}

											ModifyCashBalance(playerid, -price, "Покупка телефона");
											SetPlayerData(playerid, P_PHONE, GetPlayerAccountID(playerid) + 1000000);
											UpdatePlayerDatabaseInt(playerid, "phone", GetPlayerData(playerid, P_PHONE));
											
											if(GetPVarInt(playerid, "quest") == 3)
											{
												SetPVarInt(playerid, "quest", 0);
											    SetPlayerData(playerid, P_QUEST_3_STATS, 1);
											    CEF_HIDE(playerid, "QuestsProgressInfo");
											    SendClientMessage(playerid, -1, "");
												SendClientMessage(playerid, 0xFFA500FF, "Задание успешно выполнено, Вы получили {"#cGold"}5000 руб {FFA500}и {"#cGold"}2 exp.");
												ShowDisplayText(playerid, "Задание выполнено<br><font color=#F1B50C>5000 руб и 2 EXP", 4000);
												SendClientMessage(playerid, -1, "");
												ModifyCashBalance(playerid, 5000, "выполнение квеста", true, true);
                                                PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
												UpdatePlayerDatabaseInt(playerid, "quest_3_stats", GetPlayerData(playerid, P_QUEST_3_STATS));
												AddPlayerData(playerid, P_EXP, +, 2);
												OnClickQuests(playerid, 3);

                                                if(GetPlayerExp(playerid) > GetExpToNextLevel(playerid))
												{
													SetPlayerData(playerid, P_EXP, 0);
													AddPlayerData(playerid, P_LEVEL, +, 1);
													SendClientMessage(playerid, 0xCECECEFF, "Поздравляем! Ваш уровень повышен");
													SetPlayerLevelInit(playerid);
												}
											}
											
											SendClientMessage(playerid, 0x66CC00FF, "Используйте {FFD83D}/c(/call) или /call [номер телефона] {66CC00}чтобы сделать звонок.");
											SendClientMessage(playerid, 0x66CC00FF, "Для отправки SMS сообщения используйте {FFD83D}/sms{66CC00}. Другие команды: {FFD83D}/menu > Список команд > Общение");


											new query[148];
											format
											(
												query, sizeof query,
												"{FFFFFF}Поздравляем!\n"\
												"Вы купили мобильный телефон. Ваш номер: {FFD83D}%d",
												GetPlayerPhone(playerid)
											);
											IntfDialogCallRemote(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, "{66CC00}Покупка мобильного телефона", query, "Закрыть", "");
										}
										else SendClientMessage(playerid, 0xCECECEFF, "Мобильный телефон стоит 7350 рублей");
									}
									else
									{
										SendClientMessage(playerid, 0x999999FF, "У Вас уже есть мобильный телефон");
									}
								}
								case 2:
								{
									price = 10500;
									take_prods = 4;

									if(!GetPlayerWatch(playerid))
									{
										if(VerifyIntString(QueryPlayerBalance(playerid), price))
										{
											if(GetBusinessData(businessid, B_PRODS) >= take_prods)
											{
												AddBusinessProfit(playerid, businessid, price, take_prods);
											}
											ModifyCashBalance(playerid, -price, "Покупка Apple Watch");
											SetPlayerData(playerid, P_WATCH, GetPlayerAccountID(playerid) + 1000000);

											SendClientMessage(playerid, 0x66CC00FF, "Используйте {FFD83D}/watch для открытия часов.");

											new query[148];
											format
											(
												query, sizeof query,
												"{FFFFFF}Поздравляем!\n"\
												"Вы купили наручные часы - Apple Watch.",
												GetPlayerWatch(playerid)
											);
											IntfDialogCallRemote(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, "{66CC00}Покупка наручных часов", query, "Закрыть", "");
										}
										else SendClientMessage(playerid, 0xCECECEFF, "Apple Watch стоят 10500 рублей");
									}
									else
									{
										SendClientMessage(playerid, 0x999999FF, "* У Вас уже есть Apple Watch");
									}
								}
								case 3:
								{
									price = 1750;
									if(GetPlayerPhone(playerid))
									{
										if(VerifyIntString(QueryPlayerBalance(playerid), price))
										{
											IntfDialogCallRemote
											(
												playerid, DIALOG_BIZ_CHANGE_PHONE_NUMBER, DIALOG_STYLE_INPUT,
												"{66CC00}Изменение номера",
												"{FFFFFF}Введите новый номер в поле ниже\n\n"\
												"{FF6633}Примечания:\n"\
												"{FFD83D}- Номер должен быть шестизначным,\n"\
												"например: 777777\n"\
												"- Номер не должен начинаться с 0\n\n"\
												"{FFFFFF}Вы также можете вернуть свой\n"\
												"стандартный номер. Для этого\n"\
												"введите в поле {3399FF}цифру 0",
												"Сменить", "Отмена"
											);

											return 1;
										}
										else SendClientMessage(playerid, 0xCECECEFF, "Для изменение номера телефона необходимо 1750 рублей");
									}
									else SendClientMessage(playerid, 0x999999FF, "Сначала нужно приобрести мобильный телефон");

									callcmd::buy(playerid, "");
								}
								case 4:
								{
									price = 700;
									if(GetPlayerPhone(playerid))
									{
										if(VerifyIntString(QueryPlayerBalance(playerid), price))
										{
											IntfDialogCallRemote
											(
												playerid, DIALOG_BIZ_CHANGE_PHONE_COLOR, DIALOG_STYLE_LIST,
												"{66CC00}Изменение цвета телефона",
												"1. Карамельный\n"\
												"2. Синий\n"\
												"3. Оранжевый\n"\
												"4. Серебристый\n"\
												"5. Розовый\n"\
												"6. Красный\n"\
												"7. Зеленый\n"\
												"8. Темно-синий\n"\
												"9. Желтый\n"\
												"10. Белый",
												"Поменять", "Отмена"
											);

											return 1;
										}
										else SendClientMessage(playerid, 0xCECECEFF, "Для изменение цвета телефона необходимо 700 рублей");
									}
									else SendClientMessage(playerid, 0x999999FF, "Сначала нужно приобрести мобильный телефон");

									callcmd::buy(playerid, "");
								}
								case 5:
								{
									if(GetPlayerPhone(playerid) != 0)
									{
										IntfDialogCallRemote
										(
											playerid, DIALOG_BIZ_PHONE_BALANCE, DIALOG_STYLE_INPUT,
											"{FFD83D}Пополнение мобильного телефона",
											"{FFFFFF}Укажите сумму, на которую хотите пополнить счёт:",
											"Готово", "Назад"
										);

										return 1;
									}
									else SendClientMessage(playerid, 0x999999FF, "У Вас нет телефона. Его можно купить в сотовом салоне");

									callcmd::buy(playerid, "");
								}
								default:
									return 1;
							}
						}
					}
				}
			}
			case DIALOG_BIZ_PHONE_BALANCE:
			{
				new businessid = GetPlayerInBiz(playerid);
				if(businessid != -1)
				{
					if(IsPlayerInBuyPosBiz(playerid, businessid, BUSINESS_TYPE_CELL_SALON))
					{
						if(response)
						{
							new sum = strval(inputtext);
							if(sum > 0 && IsNumeric(inputtext))
							{
								if(VerifyIntString(QueryPlayerBalance(playerid), sum))
								{
									new query[128];

									format(query, sizeof query, "UPDATE accounts_canvasdev SET money=%s,phone_balance=%d WHERE id=%d LIMIT 1", SetILPlayerInt(playerid, QueryPlayerBalance(playerid), -sum), GetPlayerData(playerid, P_PHONE_BALANCE)+sum, GetPlayerAccountID(playerid));
									mysql_query(mysql, query, false);

									if(!mysql_errno())
									{
										ModifyCashBalance(playerid, -sum, "Пополнение счета телефона", false, true);
										AddPlayerData(playerid, P_PHONE_BALANCE, +, sum);

										format(query, sizeof query, "Вы пополнили счет мобильного телефона на {FF9900}%d руб", sum);
										SendClientMessage(playerid, 0x66CC00FF, query);

										format(query, sizeof query, "Сейчас на счету %d руб", GetPlayerData(playerid, P_PHONE_BALANCE));
										SendClientMessage(playerid, 0x66CC00FF, query);

										return 1;
									}
									else SendClientMessage(playerid, 0xFF6600FF, "Ошибка сохранения, повторите попытку {FF0000}(equ-code 15)");
								}
								else SendClientMessage(playerid, 0xCECECEFF, "У Вас не хватает денег");
							}

							IntfDialogCallRemote
							(
								playerid, DIALOG_BIZ_PHONE_BALANCE, DIALOG_STYLE_INPUT,
								"{FFD83D}Пополнение мобильного телефона",
								"{FFFFFF}Укажите сумму, на которую хотите пополнить счёт:",
								"Готово", "Назад"
							);
						}
						else callcmd::buy(playerid, "");
					}
				}
			}
			case DIALOG_BIZ_CHANGE_PHONE_NUMBER:
			{
				new businessid = GetPlayerInBiz(playerid);
				if(businessid != -1)
				{
					if(IsPlayerInBuyPosBiz(playerid, businessid, BUSINESS_TYPE_CELL_SALON))
					{
						if(response)
						{
							new buffer = strlen(inputtext);
							if((1 <= buffer <= 10) && IsNumeric(inputtext))
							{
								new fmt_str[175];
								new number = strval(inputtext);

								new price = 10000;
								new take_prods = 3;

								if(number > 0)
								{
									if(inputtext[0] != '0' && buffer == 6)
									{
										new Cache: result;
										buffer = 0;

										format(fmt_str, sizeof fmt_str, "SELECT id FROM accounts_canvasdev WHERE phone=%d LIMIT 1", number);
										result = mysql_query(mysql, fmt_str, true);

										buffer = cache_num_rows();
										cache_delete(result);

										if(!buffer)
										{
											if(VerifyIntString(QueryPlayerBalance(playerid), price))
											{
												if(GetBusinessData(businessid, B_PRODS) >= take_prods)
												{
													AddBusinessProfit(playerid, businessid, price, take_prods);
												}

												ModifyCashBalance(playerid, -price, "Смена номера телефона[1]");
												SetPlayerData(playerid, P_PHONE, number);
												UpdatePlayerDatabaseInt(playerid, "phone", GetPlayerData(playerid, P_PHONE));

												format
												(
													fmt_str, sizeof fmt_str,
													"{FFFFFF}Номер телефона изменен\n"\
													"Теперь с Вами  можно связаться по номеру {FFD83D}%d",
													GetPlayerPhone(playerid)
												);
												return IntfDialogCallRemote(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, "{66CC00}Номер изменен", fmt_str, "Закрыть", "");
												
											}
											else
											{
												return SendClientMessage(playerid, 0xCECECEFF, "Недостаточно денег");
											}
										}
										else SendClientMessage(playerid, 0xFF6600FF, "Введенный Вами номер уже занят");
									}
									else SendClientMessage(playerid, 0xFF6600FF, "Номер введен некорректно. Повторите попытку");
								}
								else
								{
									if(VerifyIntString(QueryPlayerBalance(playerid), price))
									{
										if(GetBusinessData(businessid, B_PRODS) >= take_prods)
										{
											AddBusinessProfit(playerid, businessid, price, take_prods);
										}

										ModifyCashBalance(playerid, -price, "Смена номера телефона[2]");
										SetPlayerData(playerid, P_PHONE, GetPlayerAccountID(playerid) + 1000000);
										UpdatePlayerDatabaseInt(playerid, "phone", GetPlayerData(playerid, P_PHONE));

										format(fmt_str, sizeof fmt_str, "{FFFFFF}Установлен Ваш стандартный номер: {FFD83D}%d", GetPlayerPhone(playerid));
										return IntfDialogCallRemote(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, "{66CC00}Номер изменен", fmt_str, "Закрыть", "");
									}
									else
									{
										return SendClientMessage(playerid, 0xCECECEFF, "Недостаточно денег");
									}
								}
							}

							IntfDialogCallRemote
							(
								playerid, DIALOG_BIZ_CHANGE_PHONE_NUMBER, DIALOG_STYLE_INPUT,
								"{66CC00}Изменение номера",
								"{FFFFFF}Введите новый номер в поле ниже\n\n"\
								"{FF6633}Примечания:\n"\
								"{FFD83D}- Номер должен быть шестизначным,\n"\
								"например: 777777\n"\
								"- Номер не должен начинаться с 0\n\n"\
								"{FFFFFF}Вы также можете вернуть свой\n"\
								"стандартный номер. Для этого\n"\
								"введите в поле {3399FF}цифру 0",
								"Сменить", "Отмена"
							);
						}
						else callcmd::buy(playerid, "");
					}
				}
			}
			case DIALOG_BIZ_CHANGE_PHONE_COLOR:
			{
				new businessid = GetPlayerInBiz(playerid);
				if(businessid != -1)
				{
					if(IsPlayerInBuyPosBiz(playerid, businessid, BUSINESS_TYPE_CELL_SALON))
					{
						if(response)
						{
							if(0 <= listitem <= 9)
							{
								new price = 2500;
								new take_prods = 1;

								if(VerifyIntString(QueryPlayerBalance(playerid), price))
								{
									if(GetBusinessData(businessid, B_PRODS) >= take_prods)
									{
										AddBusinessProfit(playerid, businessid, price, take_prods);
									}
									ModifyCashBalance(playerid, -price, "Смена цвета телефона");

									SetPlayerData(playerid, P_PHONE_COLOR, listitem);
									SendClientMessage(playerid, 0x3399FFFF, "Вы изменили цвет своего мобильного телефона");
									
								}
								else SendClientMessage(playerid, 0xCECECEFF, "Для изменение цвета телефона необходимо 2500 рублей");
							}
						}
						else callcmd::buy(playerid, "");
					}
				}
			}
			case DIALOG_BIZ_CLUB:
			{
				new businessid = GetPlayerInBiz(playerid);
				if(businessid != -1)
				{
					if(IsPlayerInBuyPosBiz(playerid, businessid, BUSINESS_TYPE_CLUB, 15.0)
					|| IsPlayerInBuyPosBiz(playerid, businessid, BUSINESS_TYPE_CASINO, 15.0))
					{
						if(response)
						{
							if(0 <= listitem <= 9)
							{
								new const
									item_price[10] = {600, 1000, 2000, 2700, 3000, 4500, 6300, 7500, 500, 800};

								if(VerifyIntString(QueryPlayerBalance(playerid), item_price[listitem]))
								{
									new take_prods = 1;

									if(GetBusinessData(businessid, B_PRODS) >= take_prods)
									{
										AddBusinessProfit(playerid, businessid, item_price[listitem], take_prods);
									}
									ModifyCashBalance(playerid, -item_price[listitem], "Покупка в клубе/казино");
									GivePlayerDrinkItem(playerid, listitem);

									switch(listitem+1)
									{
										case 1: Action(playerid, "купил(а) банку лимонада", 	15.0, false);
										case 2: Action(playerid, "купил(а) бутылку пива", 		15.0, false);
										case 3: Action(playerid, "купил(а) бутылку вина", 		15.0, false);
										case 4: Action(playerid, "купил(а) бутылку шампанского",15.0, false);
										case 5: Action(playerid, "купил(а) бутылку водки", 		15.0, false);
										case 6: Action(playerid, "купил(а) бутылку коньяка",	15.0, false);
										case 7: Action(playerid, "купил(а) бутылку виски", 		15.0, false);
										case 8: Action(playerid, "купил(а) бутылку абсента", 	15.0, false);
										case 9: Action(playerid, "купил(а) закуску", 			15.0, false);
										case 10:Action(playerid, "купил(а) сигару", 			15.0, false);
									}
									
								}
								else SendClientMessage(playerid, 0x999999FF, "У Вас не хватает денег");
							}
						}
					}
				}
			}
			case DIALOG_BIZ_SHOP_APTEKA:
			{
				new businessid = GetPlayerInBiz(playerid);
				if(businessid != -1)
				{
					if(response)
					{
						if(IsPlayerInBuyPosBiz(playerid, businessid, BUSINESS_TYPE_APTEKA))
						{
							new price;
							new take_prods;

							switch(listitem + 1)
							{
								case 1:
								{
									price = 10000;
									take_prods = 1;
                                    if(GetIteam(playerid, 2) == 0)
									{
										if(VerifyIntString(QueryPlayerBalance(playerid), price))
										{
											if(GetBusinessData(businessid, B_PRODS) >= take_prods)
											{
												AddBusinessProfit(playerid, businessid, price, take_prods);
											}

											ModifyCashBalance(playerid, -price, "Покупка аптечек");

											GiveIteam(playerid, 2,1, 2,0);
										}
										else SendClientMessage(playerid, 0xCECECEFF, "Две аптечки стоят 50.000 рублей");
									}
									else SendClientMessage(playerid, 0x999999FF, "Можно иметь всего 2 аптечки");
								}
								
								default:
									return 1;
							}
						}
					}
				}
			}
			case DIALOG_GARAGE_BAR:
			{
				if(response)
				{
					if(0 <= listitem <= 9)
					{
						GivePlayerDrinkItem(playerid, listitem);

						switch(listitem+1)
						{
						    case 1: Action(playerid, "взял(а) банку лимонада", 	15.0, false);
							case 2: Action(playerid, "взял(а) бутылку пива", 		15.0, false);
							case 3: Action(playerid, "взял(а) бутылку вина", 		15.0, false);
							case 4: Action(playerid, "взял(а) бутылку шампанского",15.0, false);
							case 5: Action(playerid, "взял(а) бутылку водки", 		15.0, false);
							case 6: Action(playerid, "взял(а) бутылку коньяка",	15.0, false);
							case 7: Action(playerid, "взял(а) бутылку виски", 		15.0, false);
							case 8: Action(playerid, "взял(а) бутылку абсента", 	15.0, false);
							case 9: Action(playerid, "взял(а) закуску", 			15.0, false);
							case 10:Action(playerid, "взял(а) сигару", 			15.0, false);
						}
				    }
				}
			}
			case DIALOG_BIZ_REALTOR_BIZ_LIST:
			{
				new businessid = GetPlayerInBiz(playerid);
				if(businessid != -1)
				{
					if(IsPlayerInBuyPosBiz(playerid, businessid, BUSINESS_TYPE_REALTOR_BIZ, 15.0))
					{
						if(response)
						{
							if(0 <= listitem <= MAX_BUSINESS-1)
							{
								new price = 2500; //

								if(VerifyIntString(QueryPlayerBalance(playerid), price))
								{
									new fmt_str[300];
									ModifyCashBalance(playerid, -price, "Просмотр инфо о бизнесе (управление статистики)", true, true);

									businessid = g_business_realtor_list_idx[listitem];
									SetPlayerUseListitem(playerid, businessid);

									format
									(
										fmt_str, sizeof fmt_str,
										"{FFFFFF}Название:\t\t\t%s\n"\
										"Номер бизнеса:\t\t%d\n"\
										"Город / область:\t\t%s\n"\
										"Район:\t\t\t\t%s\n"\
										"Стоимость:\t\t\t%s\n\n"\
										"{FFFFFF}Вы также можете посмотреть фотографию бизнеса.\n"\
										"Для этого нажмите кнопку Фото. {FFD83D}Услуга стоит 2500 руб",
										GetBusinessData(businessid, B_NAME),
										businessid,
										GetCityName(GetBusinessData(businessid, B_CITY)),
										GetZoneName(GetBusinessData(businessid, B_ZONE)),
										formatInt(GetBusinessData(businessid, B_PRICE))
									);
									IntfDialogCallRemote(playerid, DIALOG_BIZ_REALTOR_BIZ_INFO, DIALOG_STYLE_MSGBOX, "{CC9900}Информация о выбранном бизнесе", fmt_str, "Фото", "Закрыть");
								}
								else SendClientMessage(playerid, 0x999999FF, "Недостаточно денег");
							}
						}
					}
				}
			}
			case DIALOG_BIZ_REALTOR_BIZ_INFO:
			{
				new businessid = GetPlayerInBiz(playerid);
				if(businessid != -1)
				{
					if(IsPlayerInBuyPosBiz(playerid, businessid, BUSINESS_TYPE_REALTOR_BIZ, 15.0))
					{
						if(response)
						{
							new price = 5000; //

							businessid = GetPlayerUseListitem(playerid);
							if(VerifyIntString(QueryPlayerBalance(playerid), price))
							{
								ModifyCashBalance(playerid, -price, "Просмотр фото бизнеса (управление статистики)", true, true);

								TogglePlayerSpectating(playerid, true);
								//ShowPlayerWaitPanel(playerid);

								SetPlayerVirtualWorld(playerid, playerid + 50);
								SendClientMessage(playerid, 0xFFFFFFFF, "Используйте {99CC00}~k~~PED_SPRINT~ {FFFFFF}для выхода");

								SetPlayerData(playerid, P_REALTOR_TYPE, REALTOR_TYPE_BIZ);
								SetTimerEx("SetRealtorMakePhoto", 1000, false, "iii", playerid, REALTOR_TYPE_BIZ, businessid);
							}
							else SendClientMessage(playerid, 0x999999FF, "Недостаточно денег");
						}
					}
				}
			}
			case DIALOG_BIZ_REALTOR_HOME_GET:
			{
				new businessid = GetPlayerInBiz(playerid);
				if(businessid != -1)
				{
					if(IsPlayerInBuyPosBiz(playerid, businessid, BUSINESS_TYPE_REALTOR_HOME, 15.0))
					{
						if(response)
						{
							new price = 5500;
							new houseid = strval(inputtext);

							if(strlen(inputtext) && IsNumeric(inputtext) && (0 <= houseid <= g_house_loaded-1))
							{
								if(VerifyIntString(QueryPlayerBalance(playerid), price))
								{
									ModifyCashBalance(playerid, -price, "Просмотр инфо о доме (риелторское агенство)", true, true);

									new fmt_str[512];
									new type = GetHouseData(houseid, H_TYPE);

									SetPlayerUseListitem(playerid, houseid);
								
									format
									(
										fmt_str, sizeof fmt_str,
										"{FFFFFF}Тип / название:\t\t%s\n"\
										"Номер дома:\t\t\t%d\n"\
										"Город / область:\t\t%s\n"\
										"Район:\t\t\t\t%s\n"\
										"Стоимость:\t\t\t%s\n"\
										"Количество комнат:\t\t%d\n"\
										"Статус:\t\t\t\t%s\n\n"\
										"{FFFFFF}Вы также можете посмотреть как выглядит этот дом снаружи.\n"\
										"Для этого нажмите кнопку Фото. {FFD83D}Услуга стоит 2500 рублей",
										GetHouseData(houseid, H_NAME),
										houseid,
										GetCityName(GetHouseData(houseid, H_CITY)),
										GetZoneName(GetHouseData(houseid, H_ZONE)),
										formatInt(GetHouseData(houseid, H_PRICE)),
										GetHouseTypeInfo(type, HT_ROOMS),
										IsHouseOwned(houseid) ? ("{FF6600}Дом занят") : ("{00CC33}Дом свободен")
									);
						            IntfDialogCallRemote(playerid, DIALOG_BIZ_REALTOR_HOME_INFO, DIALOG_STYLE_MSGBOX, "{FF9933}Информация о выбранном доме", fmt_str, "Фото", "Назад");
								}
								else SendClientMessage(playerid, 0x999999FF, "Недостаточно денег");
							}
							else
							{
								if(!(0 <= houseid <= g_house_loaded-1))
									SendClientMessage(playerid, 0xCECECEFF, "Этот дом еще не построили");

								ShowPlayerRealtorHomeDialog(playerid);
							}
						}
					}
				}
			}
			case DIALOG_BIZ_REALTOR_HOME_INFO:
			{
				new businessid = GetPlayerInBiz(playerid);
				if(businessid != -1)
				{
					if(IsPlayerInBuyPosBiz(playerid, businessid, BUSINESS_TYPE_REALTOR_HOME, 15.0))
					{
						if(response)
						{
							new price = 3000; //

							if(VerifyIntString(QueryPlayerBalance(playerid), price))
							{
								ModifyCashBalance(playerid, -price, "Просмотр фото дома (риелторское агенство)", true, true);

								TogglePlayerSpectating(playerid, true);
								//ShowPlayerWaitPanel(playerid);

								SetPlayerVirtualWorld(playerid, playerid + 3000);
								SendClientMessage(playerid, 0xFFFFFFFF, "Используйте {00CC99}~k~~PED_SPRINT~ {FFFFFF}для выхода");

								SetPlayerData(playerid, P_REALTOR_TYPE, REALTOR_TYPE_HOUSE);
								SetTimerEx("SetRealtorMakePhoto", 1000, false, "iii", playerid, REALTOR_TYPE_HOUSE, GetPlayerUseListitem(playerid));
							}
							else SendClientMessage(playerid, 0x999999FF, "Недостаточно денег");
						}
						else ShowPlayerRealtorHomeDialog(playerid);
					}
				}
			}
			case DIALOG_BIZ_CLOTHING_BUY:
			{
	            if(!response) return 1;
	            
	            new bizid = GetPlayerInBiz(playerid);
				new str_l[562];

	            if(bizid == -1) return 1;
	            
	            if(IsPlayerInBuyPosBiz(playerid, bizid, BUSINESS_TYPE_CLOTHING_SHOP, 50.0)) 
				{
	                new sex = GetPlayerSex(playerid),
	                    item_ = GetPlayerData(playerid, P_SELECT_SKIN),
	                    price = g_business_clothing_skins[sex][item_][g_cost];

	                if(!VerifyIntString(QueryPlayerBalance(playerid), price)) return GameText(playerid, "~r~Недостаточно~n~средств", 4000, 0);

	                new take_prods = random(200) + 20,
	                    biz_price = price / 100 * 40,
	                    skinid = g_business_clothing_skins[sex][item_][g_model];

					if(GetBusinessData(bizid, B_PRODS) >= take_prods)
						AddBusinessProfit(playerid, bizid, biz_price, take_prods);
					
					GiveSkin(playerid, skinid);
	                
					ModifyCashBalance(playerid, -price, "Покупка скина (магазин одежды)");
					
					OnBattlePass_Perfomance(playerid, 14, 1);

					if(GetPlayerLevel(playerid) > 4)
					{
					    AddPlayerData(playerid, P_ACHIV_13, +, price);
                        UpdatePlayerDatabaseInt(playerid, "achiv_13", GetPlayerData(playerid, P_ACHIV_13));
        
		                if(GetPlayerData(playerid, P_ACHIV_13) >= 1000000 && GetPlayerData(playerid, P_ACHIV_13_COMPLETED) == 0)
		                {
			                GivePlayerMyPrizes(playerid, "Донат", 10, 0, 0, 25, 0);
                            SendClientMessage(playerid, COLOR_GREEN, "Поздравляем! Вы получили достижение: {FFFF00}\"Шопоголик\"");
			                SendClientMessage(playerid, 0xead671FF, "Вам выдана награда за получение достижения. Используйте {ffffff}клавишу M > Награды, {ead671}чтобы забрать её.");
		    
			                SetPlayerData(playerid, P_ACHIV_13_COMPLETED, 1);
                            UpdatePlayerDatabaseInt(playerid, "achiv_13_completed", 1);

						    CEF_CREATE(playerid, 2, 4, "AchievementNotification", "[13, 0, \"Вы получили достижение!\"]");
		                }
					}

					GameText(playerid, "Новая одежда была добавлена в ваш инвентарь", 3000, 2);

					format(str_l, sizeof(str_l), "interface('ClothingStore').setBuy(%d)", price);
			        CEF_CREATE(playerid, 1, 2, str_l);

					SetPlayerData(playerid, P_SELECT_SKIN, -1);
					    
					if(GetPVarInt(playerid, "quest") == 5)
                    {
					    SetPVarInt(playerid, "quest", 0);
					    SetPlayerData(playerid, P_QUEST_7_STATS, 1);
					    CEF_HIDE(playerid, "QuestsProgressInfo");
					    SendClientMessage(playerid, -1, "");
						SendClientMessage(playerid, 0xFFA500FF, "Задание успешно выполнено, Вы получили {"#cGold"}7500 руб {FFA500}и {"#cGold"}1 exp.");
						ShowDisplayText(playerid, "Задание выполнено<br><font color=#F1B50C>7500 руб и 1 EXP", 4000);
						SendClientMessage(playerid, -1, "");
						ModifyCashBalance(playerid, 7500, "выполнение квеста", true, true);
			            PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
						UpdatePlayerDatabaseInt(playerid, "quest_7_stats", GetPlayerData(playerid, P_QUEST_7_STATS));
						AddPlayerData(playerid, P_EXP, +, 1);

						if(GetPlayerExp(playerid) > GetExpToNextLevel(playerid))
						{
							SetPlayerData(playerid, P_EXP, 0);
							AddPlayerData(playerid, P_LEVEL, +, 1);
							SendClientMessage(playerid, 0xCECECEFF, "Поздравляем! Ваш уровень повышен");
						    SetPlayerLevelInit(playerid);
						}
					}
	            }
				return 1;
	        }
			case DIALOG_HOUSE_BUY:
			{
				new houseid = GetPlayerUseListitem(playerid);

				if(houseid >= 1 && response)
				{
					if((GetPlayerOwnableHouse(playerid) + 1) > GetPlayerHouseSlots(playerid)) return SendClientMessage(playerid, 0x3399FFFF, "Вы уже имеете максимально количество домов.");

					if(IsPlayerInRangeOfHouse(playerid, houseid, 5.0))
					{
						if(!IsHouseOwned(houseid))
						{
							if(VerifyIntString(QueryPlayerBalance(playerid), GetHouseData(houseid, H_PRICE)))
							{
								if(GetOwnableAuction(0, GetHouseData(houseid, H_SQL_ID)) > 0) return SCM(playerid, COLOR_GREY, "* Данный дом выставлен на аукцион");

								SendClientMessage(playerid, 0xFFFFFFFF, "Поздравляем! Вы приобрели дом");
								BuyPlayerHouse(playerid, houseid);

								EnterPlayerToHouse(playerid, houseid);
								PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);

								GameText(playerid, "~b~Добро пожаловать ~g~в~n~~y~в новый ~w~ дом!", 4000, 2);
								IntfDialogCallRemote(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, "{3399FF}Новый дом", "{FFFFFF}Вам нужно заплатить за дом в ближайшем отделением банка {FFCD00}(/gps)", "Ок", "");
							}
							else SendClientMessage(playerid, 0xCECECEFF, "У Вас недостаточно денег для покупки этого дома");
						}
						else
						{
							new fmt_str[64];

							format(fmt_str, sizeof fmt_str, "Этот дом уже куплен. Владелец: %s", GetHouseData(houseid, H_OWNER_NAME));
							SendClientMessage(playerid, 0xCECECEFF, fmt_str);
						}
					}
				}
			}
			case DIALOG_HOUSE_SELL:
			{
				if(!response) return 1;
				SellHouse(playerid);
			}
   			case DIALOG_HOUSE_INFO:
			{
				if(response)
				{
					new houseid = GetPVarInt(playerid, "ownablehouse_id");
					if(houseid != -1)
					{
						ShowPlayerHouseDialog(playerid, HOUSE_OPERATION_PARAMS);
					}
				}
			}
			case DIALOG_HOUSE_PARAMS:
			{
				new houseid = GetPVarInt(playerid, "ownablehouse_id");
				if(houseid != -1)
				{
					if(response)
					{
						ShowPlayerHouseDialog(playerid, listitem + 1);
					}
					else callcmd::home(playerid);
				}
			}
			case DIALOG_HOUSE_IMPROVEMENTS:
			{
				new houseid = GetPVarInt(playerid, "ownablehouse_id");
				if(houseid != -1)
				{
					if(response)
					{
						if(0 <= listitem <= sizeof g_house_improvements - 1)
						{
							new i_level = GetHouseData(houseid, H_IMPROVEMENTS);
							new i_price = g_house_improvements[listitem][I_PRICE];

							if(i_level >= sizeof g_house_improvements) SendClientMessage(playerid, 0x999999FF, "Вы уже приобрели все доступные улучшения для дома");
							else if(i_level < listitem) SendClientMessage(playerid, 0xCECECEFF, "Этот уровень улучшений пока недоступен");
							else if(i_level > listitem) SendClientMessage(playerid, 0xCECECEFF, "Вы уже купили этот уровень улучшений");
							else if(!VerifyIntString(QueryPlayerBalance(playerid), i_price))
							{
								new fmt_str[64];

								format(fmt_str, sizeof fmt_str, "Для покупки %d уровня улучшений необходимо %d рублей", listitem + 1, i_price);
								SendClientMessage(playerid, 0xCECECEFF, fmt_str);
							}
							else
							{
								new fmt_str[128];

								format(fmt_str, sizeof fmt_str, "UPDATE accounts_canvasdev a, houses h SET a.money=%s, h.improvements=%d WHERE a.id=%d AND h.id=%d", SetILPlayerInt(playerid, QueryPlayerBalance(playerid),-i_price), i_level + 1, GetPlayerAccountID(playerid), GetHouseData(houseid, H_SQL_ID));
								mysql_query(mysql, fmt_str, false);

								if(!mysql_errno())
								{
									ModifyCashBalance(playerid, -i_price, "Покупка улучшений для дома", false, true);

									format(fmt_str, sizeof fmt_str, "Вы улучшили свой дом до {FFCD00}%s {3399FF}уровня", GetNumericName(listitem + 1));
									SendClientMessage(playerid, 0x3399FFFF, fmt_str);

									AddHouseData(houseid, H_IMPROVEMENTS, +, 1);
									switch(listitem + 1)
									{
										case 1:
										{
											SendClientMessage(playerid, COLOR_ORANGE, "Чтобы прилечь на кровать нажмите ALT, находясь около неё");
										}
										case 2:
										{
											SendClientMessage(playerid, 0x66CC00FF, "Вы можете разрешить людям проживать в Вашем доме с помощью команды {FF9900}/live");
											SendClientMessage(playerid, 0x999999FF, "В доме могут разместиться столько гостей, сколько в нем комнат");
										}
										case 3:
										{
											SendClientMessage(playerid, 0x66CC00FF, "На Ваше имя была оформлена субсидия, которая дает право платить пониженную квартплату");
											SendClientMessage(playerid, 0x999999FF, "Благодаря этому, ежедневная квартплата уменьшена в 2 раза");
										}
										case 4:
										{
											SendClientMessage(playerid, 0x66CC00FF, "Используйте {3399FF}/makestore {66CC00}для размещения шкафа. В нем можно будет хранить различные вещи");
											SendClientMessage(playerid, 0x999999FF, "В любой момент можно перенести шкаф на другое место. Для открытия шкафа напишите {3399FF}/use");

											HouseStoreInit(houseid);
										}
										case 5:
										{
											SendClientMessage(playerid, 0x66CC00FF, "{FFCD00}Поздравляем вас с покупкой нового улучшения для дома `Холодильник`");
											SendClientMessage(playerid, 0x999999FF, "{FFCD00}В вашем доме появился новый холодильник, для того чтобы пополнить холодильник воспользуйтесь доставкой в телефоне.");
										}
										case 6:
										{
											SendClientMessage(playerid, COLOR_ORANGE, "Вы приобрели стиральную машину");
											SendClientMessage(playerid, COLOR_ORANGE, "Постирать одежду можно нажав \"Использовать\" на ней в меню инвентаря находясь у стиральной машины");

										}
										case 7:
										{
											SendClientMessage(playerid, 0x66CC00FF, "Теперь в доме всегда будет доступна аптечка");
											SendClientMessage(playerid, 0x999999FF, "Вы и ваши гости в любой момент можете использовать ее");

											HouseHealthInit(houseid);
										}
										case 8:
										{
											SendClientMessage(playerid, 0x66CC00FF, "В вашем доме появился вход в гардероб. Коллекционируйте в нём различные стили одежды.");
										}
									}
								}
								else SendClientMessage(playerid, 0xFF6600FF, "Ошибка сохранения, повторите попытку {FF0000}(equ-code 35)");
							}
						}
					}
					ShowPlayerHouseDialog(playerid, HOUSE_OPERATION_PARAMS);
				}
			}
			case DIALOG_PROMO_LIST:
			{
				if(!response) return true;

				new idx = GetPlayerListitemValue(playerid, listitem);

				if(GetPlayerPromo(idx, PA_OWNER_ID) != GetPlayerAccountID(playerid)) return 1;
				if(GetPlayerPromo(idx, PA_STATUS) != 0) return 1;

				new query[94],
				type_prize[6],
				id_prize[6],
				count_prize[6],
				Cache: result;

				format(query, sizeof query, "SELECT * FROM prizes_code WHERE name='%s' LIMIT 1", GetPlayerPromo(idx, PA_NAME));
				result = mysql_query(mysql, query, true);

				if(cache_num_rows())
				{
					type_prize[0] = cache_get_field_content_int(0, "type_prize_1");
					id_prize[0] = cache_get_field_content_int(0, "id_prize_1");
					count_prize[0] = cache_get_field_content_int(0, "count_prize_1");

					type_prize[1] = cache_get_field_content_int(0, "type_prize_2");
					id_prize[1] = cache_get_field_content_int(0, "id_prize_2");
					count_prize[1] = cache_get_field_content_int(0, "count_prize_2");
					
					type_prize[2] = cache_get_field_content_int(0, "type_prize_3");
					id_prize[2] = cache_get_field_content_int(0, "id_prize_3");
					count_prize[2] = cache_get_field_content_int(0, "count_prize_3");

					type_prize[3] = cache_get_field_content_int(0, "type_prize_4");
					id_prize[3] = cache_get_field_content_int(0, "id_prize_4");
					count_prize[3] = cache_get_field_content_int(0, "count_prize_4");

					type_prize[4] = cache_get_field_content_int(0, "type_prize_5");
					id_prize[4] = cache_get_field_content_int(0, "id_prize_5");
					count_prize[4] = cache_get_field_content_int(0, "count_prize_5");

					type_prize[5] = cache_get_field_content_int(0, "type_prize_6");
					id_prize[5] = cache_get_field_content_int(0, "id_prize_6");
					count_prize[5] = cache_get_field_content_int(0, "count_prize_6");
				}

				cache_delete(result);

				for(new i; i < MAX_PRIZES_CODE; i++)
				{	
					if(type_prize[i] == 1) 
					{
						GivePlayerMyPrizes(playerid, "Деньги", 5, 0, 0, count_prize[i], 0);
					}
					if(type_prize[i] == 2) 
					{
						GivePlayerMyPrizes(playerid, "Донат", 10, 0, 0, count_prize[i], 0);
					}
					if(type_prize[i] == 3) 
					{
						AddPlayerData(playerid, P_EXP, +, count_prize[i]);
						UpdatePlayerDatabaseInt(playerid, "exp", GetPlayerData(playerid, P_EXP));
					}
					if(type_prize[i] == 4) 
					{
						format(query, sizeof query, "%s", ItemsInfo[id_prize[i]][i_item_name]),
						GivePlayerMyPrizes(playerid, query, 8, id_prize[i], 0, count_prize[i], 0);
					}
					if(type_prize[i] == 5) 
					{
						format(query, sizeof query, "Транспорт[№%d]", id_prize[i]),
						GivePlayerMyPrizes(playerid, query, 3, id_prize[i], 0, 1, -1);
					}
					if(type_prize[i] == 6) 
					{
						AddPlayerData(playerid, P_BIZ_SLOTS, +, count_prize[i]);
						UpdatePlayerDatabaseInt(playerid, "biz_slots", GetPlayerData(playerid, P_BIZ_SLOTS));
					}
					if(type_prize[i] == 7) 
					{
						AddPlayerData(playerid, P_HOUSE_SLOTS, +, count_prize[i]);
						UpdatePlayerDatabaseInt(playerid, "house_slots", GetPlayerData(playerid, P_HOUSE_SLOTS));
					}
					if(type_prize[i] == 8) 
					{
						AddPlayerData(playerid, P_GARAGE_SLOTS, +, count_prize[i]);
						UpdatePlayerDatabaseInt(playerid, "garage_slots", GetPlayerData(playerid, P_GARAGE_SLOTS));
					}
					if(type_prize[i] == 9) 
					{
						AddPlayerData(playerid, P_CAR_SLOTS, +, count_prize[i]);
						UpdatePlayerDatabaseInt(playerid, "car_slots", GetPlayerData(playerid, P_CAR_SLOTS));
					}
					if(type_prize[i] == 10) 
					{
						AddPlayerData(playerid, P_KIOSK_SLOTS, +, count_prize[i]);
						UpdatePlayerDatabaseInt(playerid, "kiosk_slots", GetPlayerData(playerid, P_KIOSK_SLOTS));
					}
					if(type_prize[i] == 11) 
					{
						format(query, sizeof query, "Одежда[№%d]", id_prize[i]),
						GivePlayerMyPrizes(playerid, query, 4, id_prize[i], 0, 1, 0);
					}
					if(type_prize[i] == 12) 
					{
						format(query, sizeof query, "Аксессуар[№%d]", id_prize[i]),
						GivePlayerMyPrizes(playerid, query, 6, id_prize[i], 0, 1, count_prize[i]);
					}
					if(type_prize[i] == 13 && id_prize[i] == 1) 
					{
						format(query, sizeof query, "Купон для выхода из тюрьмы Деморган (%d мин)", count_prize[i]);
						GivePlayerMyPrizes(playerid, query, 16, count_prize[i], 0, 0, 0);
					}
				}

				SCMF(playerid, 0x64be2fFF, "Вы получаете бонус за использование промокода \"%s\"", GetPlayerPromo(idx, PA_NAME));
				SCM(playerid, 0xFFFFFFFF, "Зайдите в {4a92eb}Игровое меню -> мои награды {FFFFFF}чтобы забрать вещи");

				format(query, sizeof query, "UPDATE promocode_activations SET status=-1 WHERE id=%d", GetPlayerPromo(idx, PA_ID));
				mysql_query(mysql, query, false);
				DestroyPromo(idx);
			}
			case DIALOG_HOUSE_RENTERS:
			{
				new houseid = GetPVarInt(playerid, "ownablehouse_id");
				if(houseid != -1)
				{
					if(response)
					{
						if(0 <= listitem <= MAX_HOUSE_ROOMS-1)
						{
							new room = GetPlayerListitemValue(playerid, listitem);
							ShowHouseRenterInfo(playerid, houseid, room);
						}
					}
					else ShowPlayerHouseDialog(playerid, HOUSE_OPERATION_PARAMS);
				}
			}
			case DIALOG_HOUSE_RENTER_INFO:
			{
				new houseid = GetPVarInt(playerid, "ownablehouse_id");
				if(houseid != -1)
				{
					if(response)
					{
						new room = GetPlayerUseListitem(playerid);
						if(IsHouseRoomOwned(houseid, room))
						{
							switch(listitem + 1)
							{
								case 4:
								{
									new fmt_str[95];
									format
									(
										fmt_str, sizeof fmt_str,
										"{FFFFFF}Вы действительно хотите выселить {FFCD00}%s {FFFFFF}из своего дома?",
										GetHouseRenterInfo(houseid, room, HR_OWNER_NAME)
									);
									return IntfDialogCallRemote(playerid, DIALOG_HOUSE_RENTER_EVICT, DIALOG_STYLE_MSGBOX, "{33AACC}Выселение арендатора", fmt_str, "Да", "Нет");
								}
							}
							ShowHouseRenterInfo(playerid, houseid, room);
						}
						else SendClientMessage(playerid, 0x999999FF, "В этой комнате уже никто не проживает");
					}
					else ShowPlayerHouseDialog(playerid, HOUSE_OPERATION_PARAMS);
				}
			}
			case DIALOG_HOUSE_RENTER_EVICT:
			{
				new houseid = GetPVarInt(playerid, "ownablehouse_id");
				if(houseid != -1)
				{
					if(response)
					{
						new room = GetPlayerUseListitem(playerid);
						if(IsHouseRoomOwned(houseid, room))
						{
							new fmt_str[64],
								renter_id = GetPlayerID(GetHouseRenterInfo(houseid, room, HR_OWNER_NAME));

							format(fmt_str, sizeof fmt_str, "Вы выселили %s из своего дома", GetHouseRenterInfo(houseid, room, HR_OWNER_NAME));
							SendClientMessage(playerid, 0x66CC00FF, fmt_str);

							EvictHouseRenter(houseid, room, renter_id, playerid);
						}
						else SendClientMessage(playerid, 0x999999FF, "В этой комнате уже никто не проживает");
					}
					else ShowPlayerHouseDialog(playerid, HOUSE_OPERATION_PARAMS);
				}
			}
			case DIALOG_HOUSE_EVICT:
			{
				new houseid = GetPVarInt(playerid, "ownablehouse_id");
				if(houseid != -1)
				{
					if(response)
					{
						new roomid = GetPlayerData(playerid, P_HOUSE_ROOM);
						new owner_id = GetPlayerID(GetHouseData(houseid, H_OWNER_NAME));

						EvictHouseRenter(houseid, roomid, playerid);

						if(owner_id != INVALID_PLAYER_ID)
						{
							new fmt_str[45 + 1];

							format(fmt_str, sizeof fmt_str, "%s выселился из Вашего дома", GetPlayerNameEx(playerid));
							SendClientMessage(owner_id, 0x66CC00FF, fmt_str);
						}
						SendClientMessage(playerid, 0x66CC00FF, "Вы выселились из дома");
					}
				}
			}
			case DIALOG_HOUSE_MOVE_STORE:
			{
				new houseid = GetPVarInt(playerid, "ownablehouse_id");
				if(houseid != -1)
				{
					if(response)
					{
						if(GetPlayerInHouse(playerid) == houseid)
						{
							if(GetHouseData(houseid, H_IMPROVEMENTS) >= 4)
							{
								new type = GetHouseData(houseid, H_TYPE);
								if(IsPlayerInRangeOfPoint(playerid, 50.0, GetHouseTypeInfo(type, HT_ENTER_POS_X), GetHouseTypeInfo(type, HT_ENTER_POS_Y), GetHouseTypeInfo(type, HT_ENTER_POS_Z)))
								{
									if(GetHouseData(houseid, H_STORE_LABEL) != Text3D:-1)
									{
										new query[128];

										new Float: pos_x, Float: pos_y, Float: pos_z;
										GetPlayerPos(playerid, pos_x, pos_y, pos_z);

										SetHouseData(houseid, H_STORE_X, pos_x);
										SetHouseData(houseid, H_STORE_Y, pos_y);
										SetHouseData(houseid, H_STORE_Z, pos_z);

										DestroyDynamic3DTextLabel(GetHouseData(houseid, H_STORE_LABEL));
										SetHouseData(houseid, H_STORE_LABEL, Text3D:-1);

										HouseStoreInit(houseid);

										format(query, sizeof query, "UPDATE houses SET store_x=%f,store_y=%f,store_z=%f WHERE id=%d LIMIT 1", pos_x, pos_y, pos_z, GetHouseData(houseid, H_SQL_ID));
										mysql_tquery(mysql, query, "", "");
									}
								}
							}
						}
					}
				}
			}
			case DIALOG_HOUSE_ENTER:
			{
				new houseid = GetPlayerUseListitem(playerid);
				if(houseid >= 0 && response && GetPlayerInHouse(playerid) == -1){
					if(!GetHouseData(houseid, H_LOCK_STATUS) || GetPlayerHouse(playerid, HOUSE_TYPE_HOME) == houseid) EnterPlayerToHouse(playerid, houseid);
					else GameText(playerid, "~r~Закрыт", 3000, 2);
				}
			}
			case DIALOG_HOTEL:
			{
				if(response)
				{
					new hotel_id = GetPlayerInHotelID(playerid);
					if(hotel_id != -1)
					{
						switch(listitem + 1)
						{
							case 1:
							{
								ShowPlayerHotelFloorsInfo(playerid, hotel_id);
							}
							case 2:
							{
								if(GetPlayerHouse(playerid, HOUSE_TYPE_HOTEL) == -1)
								{
									new free_room = GetHotelFreeRoom(hotel_id);
									if(free_room != -1)
									{
										SetPlayerUseListitem(playerid, free_room);

										new fmt_str[128];
										format
										(
											fmt_str, sizeof fmt_str,
											"{FFFFFF}Мы предлагаем Вам поселиться в номере %d на %d этаже\n"\
											"Регистрация стоит 1000 рублей. Вы уверены?",
											(free_room % 12) + 1,
											(free_room / 12) + 1
										);
										IntfDialogCallRemote(playerid, DIALOG_HOTEL_REG_ROOM, DIALOG_STYLE_MSGBOX, "{66CC99}Подтверждение регистрации", fmt_str, "Выбрать", "Назад");
									}
									else
									{
										IntfDialogCallRemote
										(
											playerid, DIALOG_HOTEL_FLOOR_INFO, DIALOG_STYLE_MSGBOX,
											"{66CC99}Свободные номера",
											"{FFFFFF}В этой гостинице нет свободных номеров",
											"Назад", "Закрыть"
										);
									}
								}
								else
								{
									IntfDialogCallRemote
									(
										playerid, DIALOG_HOTEL_FLOOR_INFO, DIALOG_STYLE_MSGBOX,
										"{66CC99}Регистрация",
										"{FFFFFF}Вы уже снимаете номер в гостинице",
										"Назад", "Закрыть"
									);
								}
							}
							case 3:
							{
								ShowPlayerHotelClientMenu(playerid, hotel_id);
							}
						}
					}
				}
			}
			case DIALOG_HOTEL_FLOOR_SELECT:
			{
				new hotel_id = GetPlayerInHotelID(playerid);
				if(hotel_id != -1)
				{
					if(response)
					{
						ShowPlayerHotelFloorInfo(playerid, hotel_id, listitem);
					}
					else ShowPlayerHotelDialog(playerid);
				}
			}
			case DIALOG_HOTEL_FLOOR_INFO:
			{
				if(response)
				{
					ShowPlayerHotelDialog(playerid);
				}
			}
			case DIALOG_HOTEL_FLOOR_LIFT:
			{
				if(response)
				{
					new hotel_id = GetPlayerInHotelID(playerid);
					if(hotel_id != -1)
					{
						new max_floors = g_hotel_rooms_loaded[hotel_id] / 12;
						if(0 <= listitem <= max_floors-1)
						{
							new to_floor = GetPlayerListitemValue(playerid, listitem);

							if(!to_floor)
							{
								new businessid = GetPlayerInBiz(playerid);
								new type = GetBusinessData(businessid, B_INTERIOR);

								SetPlayerPosEx(playerid, 730.1479, 599.7930, 1002.9598, 89.9507, GetBusinessInteriorInfo(type, BT_ENTER_INTERIOR), businessid + 255);
							}
							else SetPlayerPosEx(playerid, 1276.0446, -773.2361, 1202.7220, 360.0, to_floor, ((hotel_id + 1) * 200) + (to_floor + 1000));

							SetPlayerData(playerid, P_IN_HOTEL_FLOOR, to_floor);
						}
					}
				}
			}
			case DIALOG_HOTEL_CLIENT_MENU:
			{
				new hotel_id = GetPlayerInHotelID(playerid);
				if(hotel_id == GetPlayerHouse(playerid, HOUSE_TYPE_HOTEL))
				{
					if(response)
					{
						switch(listitem + 1)
						{
							case 1: // Оплатить проживание
							{
								ShowPlayerHotelRoomPayForRent(playerid);
							}
							case 2: // Информация о транспорте
							{
								new vehicleid = GetPlayerOwnableCarLast(playerid);
								if(vehicleid != INVALID_VEHICLE_ID)
								{
									new model_id = GetVehicleData(vehicleid, V_MODELID);
									if(model_id)
									{
										new fmt_str[64];
										new index = GetVehicleData(vehicleid, V_ACTION_ID);

										format(fmt_str, sizeof fmt_str, "Модель: %s (номер модели %d)", GetVehicleName(vehicleid), model_id);
										SendClientMessage(playerid, 0x99FF66FF, fmt_str);

										if(!(GetOwnableCarData(index, OC_COLOR_1) == -1 || GetOwnableCarData(index, OC_COLOR_2) == -1))
										{
											format(fmt_str, sizeof fmt_str, "Цвет 1: ID %d   Цвет 2: ID %d", GetOwnableCarData(index, OC_COLOR_1), GetOwnableCarData(index, OC_COLOR_2));
											SendClientMessage(playerid, 0x99FF66FF, fmt_str);
										}
										else SendClientMessage(playerid, 0x99FF66FF, "Цвета транспорта: случайные");

										format(fmt_str, sizeof fmt_str, "Гос. стоимость: %d руб", GetVehicleInfo(model_id , VI_PRICE));
										SendClientMessage(playerid, 0x99FF66FF, fmt_str);
									}
								}
								else
								{
									if(GetPlayerOwnableCars(playerid) == 0)
										SendClientMessage(playerid, 0x999999FF, "У Вас нет личного транспорта");
									else
										SendClientMessage(playerid, 0x999999FF, "Ваш личный транспорт не загружен на сервер");
								}
							}
							case 3: // Отметить транспорт на GPS
							{
								callcmd::getmycar(playerid, "");
							}
							case 4: // Подогнать транспорт к отелю (1000 руб)
							{
								new vehicleid = GetPlayerOwnableCarLast(playerid);
								if(vehicleid != INVALID_VEHICLE_ID)
								{
									if(!SetVehicleToHotelRespawn(hotel_id, vehicleid))
									{
										SendClientMessage(playerid, 0xCECECEFF, "В данный момент Вы не можете использовать эту функцию");
									}
								}
								else
								{
									if(GetPlayerOwnableCars(playerid) == 0)
										SendClientMessage(playerid, 0x999999FF, "У Вас нет личного транспорта");
									else
										SendClientMessage(playerid, 0x999999FF, "Ваш личный транспорт не загружен на сервер");
								}
							}
							case 6: // Выселиться из отеля
							{
								IntfDialogCallRemote
								(
									playerid, DIALOG_HOTEL_OUT, DIALOG_STYLE_MSGBOX,
									"{66CC99}Выселение",
									"{FFFFFF}Вы уверены что хотите выселиться из отеля?",
									"Да", "Нет"
								);
							}
							default:
								return 1;
						}
					}
					else ShowPlayerHotelDialog(playerid);
				}
			}
			case DIALOG_HOTEL_PAY_FOR_ROOM:
			{
				new hotel_id = GetPlayerInHotelID(playerid);
				new room_id = GetPlayerData(playerid, P_HOUSE_ROOM);

				if(hotel_id == GetPlayerHouse(playerid, HOUSE_TYPE_HOTEL))
				{
					if(response)
					{
						new days = strval(inputtext);
						if(days > 0 && IsNumeric(inputtext))
						{
							new fmt_str[128 + 1];

							new time = gettime();
							new rent_time = GetHotelData(hotel_id, room_id, H_RENT_DATE);

							new rent_days = GetElapsedTime(rent_time, time, CONVERT_TIME_TO_DAYS);
							new total_price = days * 1000;

							if((rent_days + days) <= 7)
							{
								if(VerifyIntString(GetPlayerBankMoney(playerid), total_price))
								{
									rent_time = (rent_time - (rent_time % 86400)) + (days * 86400);

									format(fmt_str, sizeof fmt_str, "UPDATE accounts_canvasdev a, hotels h SET a.bank=%s,h.rent_time=%d WHERE a.id=%d AND h.id=%d", SetILPlayerInt(playerid, GetPlayerBankMoney(playerid), -total_price), rent_time, GetPlayerAccountID(playerid), GetHotelData(hotel_id, room_id, H_SQL_ID));
									mysql_query(mysql, fmt_str, false);

									if(!mysql_errno())
									{
										format(g_player[playerid][P_BANK], 21, "%s", SetILPlayerInt(playerid, GetPlayerBankMoney(playerid), -total_price));
										SetHotelData(hotel_id, room_id, H_RENT_DATE, rent_time);

										format(fmt_str, sizeof fmt_str, "С банковского счета снято {3399FF}%d руб", total_price);
										SendClientMessage(playerid, 0xFFFFFFFF, fmt_str);

										format(fmt_str, sizeof fmt_str, "Вы успешно проживание в отеле еще на {3399FF}%d дней", days);
										SendClientMessage(playerid, 0x66CC00FF, fmt_str);
									}
								}
								else
								{
									SendClientMessage(playerid, 0xB5B500FF, "На основном банковском счету не хватает денег для оплаты");

									format(fmt_str, sizeof fmt_str, "Для продления аренды на %d дней необходимо %d руб", days, total_price);
									SendClientMessage(playerid, 0x999999FF, fmt_str);
								}
							}
							else SendClientMessage(playerid, 0xB5B500FF, "Вы не можете оплатить за аренду больше чем на 7 дней");
						}
						ShowPlayerHotelRoomPayForRent(playerid);
					}
					else ShowPlayerHotelClientMenu(playerid, hotel_id);
				}
			}
			case DIALOG_HOTEL_OUT:
			{
				new hotel_id = GetPlayerInHotelID(playerid);
				new room_id = GetPlayerData(playerid, P_HOUSE_ROOM);

				if(hotel_id == GetPlayerHouse(playerid, HOUSE_TYPE_HOTEL))
				{
					if(response)
					{
						new query[155];

						format(query, sizeof query, "UPDATE accounts_canvasdev a,hotels h SET a.house_type=-1,a.house_room=-1,h.owner_id=0,h.rent_time=0 WHERE a.id=%d AND h.id=%d", GetPlayerAccountID(playerid), GetHotelData(hotel_id, room_id, H_SQL_ID));
						mysql_query(mysql, query, false);

						if(!mysql_errno())
						{
							SetPlayerData(playerid, P_HOUSE, 		-1);
							SetPlayerData(playerid, P_HOUSE_ROOM, 	-1);
							SetPlayerData(playerid, P_HOUSE_TYPE, 	-1);

							SetHotelData(hotel_id, room_id, H_OWNER_ID, 	0);
							SetHotelData(hotel_id, room_id, H_RENT_DATE, 	0);
							SetHotelData(hotel_id, room_id, H_STATUS, 		false);

							SendClientMessage(playerid, 0x3399FFFF, "Вы выселились из отеля");
						}
					}
					else ShowPlayerHotelClientMenu(playerid, hotel_id);
				}
			}
		case DIALOG_BILLBOARD_INPUT1:
		{
		    new bill_id = GetPVarInt(playerid, "select_billboard");
		    new text[144];
		    new fmt_text[144];
			if(response)
			{
				new str_len = strlen(inputtext);
				if(1 <= str_len <= 25)
				{
			        format(BillInfo[bill_id][BillText_1], 25, inputtext);
			        format(text, sizeof text, "%s\n\n%s\n%s", BillInfo[bill_id][BillText_1], BillInfo[bill_id][BillText_2], BillInfo[bill_id][BillText_3]);
					SetDynamicObjectMaterialText(BillInfo[bill_id][BillIDText], 0, text, 130, "Arial", 30, 1, bill_colors[BillInfo[bill_id][BillColor]], 0, 1);

					format(fmt_text, sizeof fmt_text, "%s<n>%s<n>%s<n>", BillInfo[bill_id][BillText_1], BillInfo[bill_id][BillText_2], BillInfo[bill_id][BillText_3]);
					IntfDialogCallRemote(playerid, DIALOG_BILLBOR_SELEC_STROK, DIALOG_STYLE_LIST, "Выберите строку", fmt_text, "Далее", "Закрыть");
				}
			}
			else
			{
				format(fmt_text, sizeof fmt_text, "%s<n>%s<n>%s<n>", BillInfo[bill_id][BillText_1], BillInfo[bill_id][BillText_2], BillInfo[bill_id][BillText_3]);
				IntfDialogCallRemote(playerid, DIALOG_BILLBOR_SELEC_STROK, DIALOG_STYLE_LIST, "Выберите строку", fmt_text, "Далее", "Закрыть");
			}
		}
		case DIALOG_BILLBOARD_INPUT2:
		{
		    new bill_id = GetPVarInt(playerid, "select_billboard");
		    new text[144];
		    new fmt_text[144];
			if(response)
			{
			    new str_len = strlen(inputtext);
				if(1 <= str_len <= 25)
				{
			        format(BillInfo[bill_id][BillText_2], 25, inputtext);
			        format(text, sizeof text, "%s\n\n%s\n%s", BillInfo[bill_id][BillText_1], BillInfo[bill_id][BillText_2], BillInfo[bill_id][BillText_3]);
					SetDynamicObjectMaterialText(BillInfo[bill_id][BillIDText], 0, text, 130, "Arial", 30, 1, bill_colors[BillInfo[bill_id][BillColor]], 0, 1);
					format(fmt_text, sizeof fmt_text, "%s<n>%s<n>%s<n>", BillInfo[bill_id][BillText_1], BillInfo[bill_id][BillText_2], BillInfo[bill_id][BillText_3]);
					IntfDialogCallRemote(playerid, DIALOG_BILLBOR_SELEC_STROK, DIALOG_STYLE_LIST, "Выберите строку", fmt_text, "Далее", "Закрыть");
				}
			}
			else
			{
				format(fmt_text, sizeof fmt_text, "%s<n>%s<n>%s<n>", BillInfo[bill_id][BillText_1], BillInfo[bill_id][BillText_2], BillInfo[bill_id][BillText_3]);
				IntfDialogCallRemote(playerid, DIALOG_BILLBOR_SELEC_STROK, DIALOG_STYLE_LIST, "Выберите строку", fmt_text, "Далее", "Закрыть");
			}
		}
		case DIALOG_BILLBOARD_INPUT3:
		{
		    new bill_id = GetPVarInt(playerid, "select_billboard");
		    new text[144];
		    new fmt_text[144];
			if(response)
			{
			    new str_len = strlen(inputtext);
				if(1 <= str_len <= 25)
				{
			        format(BillInfo[bill_id][BillText_3], 25, inputtext);
			        format(text, sizeof text, "%s\n\n%s\n%s", BillInfo[bill_id][BillText_1], BillInfo[bill_id][BillText_2], BillInfo[bill_id][BillText_3]);
					SetDynamicObjectMaterialText(BillInfo[bill_id][BillIDText], 0, text, 130, "Arial", 30, 1, bill_colors[BillInfo[bill_id][BillColor]], 0, 1);
					format(fmt_text, sizeof fmt_text, "%s<n>%s<n>%s<n>", BillInfo[bill_id][BillText_1], BillInfo[bill_id][BillText_2], BillInfo[bill_id][BillText_3]);
					IntfDialogCallRemote(playerid, DIALOG_BILLBOR_SELEC_STROK, DIALOG_STYLE_LIST, "Выберите строку", fmt_text, "Далее", "Закрыть");
				}
			}
			else
			{
				format(fmt_text, sizeof fmt_text, "%s<n>%s<n>%s<n>", BillInfo[bill_id][BillText_1], BillInfo[bill_id][BillText_2], BillInfo[bill_id][BillText_3]);
				IntfDialogCallRemote(playerid, DIALOG_BILLBOR_SELEC_STROK, DIALOG_STYLE_LIST, "Выберите строку", fmt_text, "Далее", "Закрыть");
			}
		}
		case DIALOG_BILLBORD_SELECT_COL:
		{
		    new bill_id = GetPVarInt(playerid, "select_billboard");
		    new text[144];
			if(response)
			{
				switch(listitem + 1)
				{
				    case 1:
				    {
				        BillInfo[bill_id][BillColor] = 0;
				        format(text, sizeof text, "%s\n\n%s\n%s", BillInfo[bill_id][BillText_1], BillInfo[bill_id][BillText_2], BillInfo[bill_id][BillText_3]);
						SetDynamicObjectMaterialText(BillInfo[bill_id][BillIDText], 0, text, 130, "Arial", 30, 1, bill_colors[BillInfo[bill_id][BillColor]], 0, 1);
						SetPVarInt(playerid, "typebill3", 0);
				    }
				    case 2:
				    {
				        BillInfo[bill_id][BillColor] = 1;
				        format(text, sizeof text, "%s\n\n%s\n%s", BillInfo[bill_id][BillText_1], BillInfo[bill_id][BillText_2], BillInfo[bill_id][BillText_3]);
						SetDynamicObjectMaterialText(BillInfo[bill_id][BillIDText], 0, text, 130, "Arial", 30, 1, bill_colors[BillInfo[bill_id][BillColor]], 0, 1);
						SetPVarInt(playerid, "typebill3", 0);
				    }
				}
			}
			else
			{
			    SetPVarInt(playerid, "typebill3", 0);
			}
		}
		case DIALOG_BILLBOR_TRK_EDIT2:
		{
			if(response)
			{
			    new bill_id = GetPVarInt(playerid, "select_billboard");
				switch(listitem + 1)
				{
				    case 1:
				    {
				        new fmt_text[144];
				        format(fmt_text, sizeof fmt_text, "%s<n>%s<n>%s<n>Разместить рекламу<n>Отказать размещать рекламу<n>", BillInfo[bill_id][BillText_1], BillInfo[bill_id][BillText_2], BillInfo[bill_id][BillText_3]);
				        IntfDialogCallRemote(playerid, DIALOG_BILLBOR_TRK_EDIT, DIALOG_STYLE_LIST, "Выберите строку", fmt_text, "Далее", "Закрыть");
				    }
				    case 2:
				    {
						IntfDialogCallRemote(playerid, DIALOG_BILLBOARD_INPUT4, DIALOG_STYLE_INPUT, "Настройка биллборда", "{FFFFFF}Введите текст строки:", "Готово", "Назад");
				    }
				}
			}
		}
		case DIALOG_BILLBOR_TRK_EDIT3:
		{
			if(response)
			{
			    new bill_id = GetPVarInt(playerid, "select_billboard");
			    new fmt_text[144];
				switch(listitem + 1)
				{
				    case 1:
				    {
					    format(fmt_text, sizeof fmt_text, "%s<n>%s<n>%s<n>Разместить рекламу<n>Отказать размещать рекламу<n>", BillInfo[bill_id][BillText_1], BillInfo[bill_id][BillText_2], BillInfo[bill_id][BillText_3]);
					    IntfDialogCallRemote(playerid, DIALOG_BILLBOR_TRK_EDIT, DIALOG_STYLE_LIST, "Выберите строку", fmt_text, "Далее", "Закрыть");
				    }
				    case 2:
				    {
						IntfDialogCallRemote(playerid, DIALOG_BILLBOARD_INPUT5, DIALOG_STYLE_INPUT, "Настройка биллборда", "{FFFFFF}Введите текст строки:", "Готово", "Назад");
				    }
				}
			}
		}
		case DIALOG_BILLBOR_TRK_EDIT4:
		{
			if(response)
			{
			    new bill_id = GetPVarInt(playerid, "select_billboard");
			    new fmt_text[144];
				switch(listitem + 1)
				{
				    case 1:
				    {
					    format(fmt_text, sizeof fmt_text, "%s<n>%s<n>%s<n>Разместить рекламу<n>Отказать размещать рекламу<n>", BillInfo[bill_id][BillText_1], BillInfo[bill_id][BillText_2], BillInfo[bill_id][BillText_3]);
					    IntfDialogCallRemote(playerid, DIALOG_BILLBOR_TRK_EDIT, DIALOG_STYLE_LIST, "Выберите строку", fmt_text, "Далее", "Закрыть");
				    }
				    case 2:
				    {
						IntfDialogCallRemote(playerid, DIALOG_BILLBOARD_INPUT6, DIALOG_STYLE_INPUT, "Настройка биллборда", "{FFFFFF}Введите текст строки:", "Готово", "Назад");
				    }
				}
			}
		}
		case DIALOG_BILLBOARD_INPUT4:
		{
		    new bill_id = GetPVarInt(playerid, "select_billboard");
		    new fmt_text[144];
			if(response)
			{
			    new str_len = strlen(inputtext);
				if(1 <= str_len <= 25)
				{
			        format(BillInfo[bill_id][BillText_1], 25, inputtext);
					format(fmt_text, sizeof fmt_text, "%s<n>%s<n>%s<n>Разместить рекламу<n>Отказать размещать рекламу<n>", BillInfo[bill_id][BillText_1], BillInfo[bill_id][BillText_2], BillInfo[bill_id][BillText_3]);
					IntfDialogCallRemote(playerid, DIALOG_BILLBOR_TRK_EDIT, DIALOG_STYLE_LIST, "Выберите строку", fmt_text, "Далее", "Закрыть");
				}
			}
			else
			{
				format(fmt_text, sizeof fmt_text, "%s<n>%s<n>%s<n>Разместить рекламу<n>Отказать размещать рекламу<n>", BillInfo[bill_id][BillText_1], BillInfo[bill_id][BillText_2], BillInfo[bill_id][BillText_3]);
				IntfDialogCallRemote(playerid, DIALOG_BILLBOR_TRK_EDIT, DIALOG_STYLE_LIST, "Выберите строку", fmt_text, "Далее", "Закрыть");
			}
		}
		case DIALOG_BILLBOARD_INPUT5:
		{
		    new bill_id = GetPVarInt(playerid, "select_billboard");
		    new fmt_text[144];
			if(response)
			{
			    new str_len = strlen(inputtext);
				if(1 <= str_len <= 25)
				{
			        format(BillInfo[bill_id][BillText_2], 25, inputtext);
					format(fmt_text, sizeof fmt_text, "%s<n>%s<n>%s<n>Разместить рекламу<n>Отказать размещать рекламу<n>", BillInfo[bill_id][BillText_1], BillInfo[bill_id][BillText_2], BillInfo[bill_id][BillText_3]);
					IntfDialogCallRemote(playerid, DIALOG_BILLBOR_TRK_EDIT, DIALOG_STYLE_LIST, "Выберите строку", fmt_text, "Далее", "Закрыть");
				}
			}
			else
			{
				format(fmt_text, sizeof fmt_text, "%s<n>%s<n>%s<n>Разместить рекламу<n>Отказать размещать рекламу<n>", BillInfo[bill_id][BillText_1], BillInfo[bill_id][BillText_2], BillInfo[bill_id][BillText_3]);
				IntfDialogCallRemote(playerid, DIALOG_BILLBOR_TRK_EDIT, DIALOG_STYLE_LIST, "Выберите строку", fmt_text, "Далее", "Закрыть");
			}
		}
		case DIALOG_BILLBOARD_INPUT6:
		{
		    new bill_id = GetPVarInt(playerid, "select_billboard");
		    new fmt_text[144];
			if(response)
			{
			    new str_len = strlen(inputtext);
				if(1 <= str_len <= 25)
				{
			        format(BillInfo[bill_id][BillText_3], 25, inputtext);
					format(fmt_text, sizeof fmt_text, "%s<n>%s<n>%s<n>Разместить рекламу<n>Отказать размещать рекламу<n>", BillInfo[bill_id][BillText_1], BillInfo[bill_id][BillText_2], BillInfo[bill_id][BillText_3]);
					IntfDialogCallRemote(playerid, DIALOG_BILLBOR_TRK_EDIT, DIALOG_STYLE_LIST, "Выберите строку", fmt_text, "Далее", "Закрыть");
				}
			}
			else
			{
				format(fmt_text, sizeof fmt_text, "%s<n>%s<n>%s<n>Разместить рекламу<n>Отказать размещать рекламу<n>", BillInfo[bill_id][BillText_1], BillInfo[bill_id][BillText_2], BillInfo[bill_id][BillText_3]);
				IntfDialogCallRemote(playerid, DIALOG_BILLBOR_TRK_EDIT, DIALOG_STYLE_LIST, "Выберите строку", fmt_text, "Далее", "Закрыть");
			}
		}
		case DIALOG_BILLBOR_TRK_EDIT:
		{
			if(response)
			{
			    new bill_id = GetPVarInt(playerid, "select_billboard");
				switch(listitem + 1)
				{
				    case 1:
				    {
						IntfDialogCallRemote(playerid, DIALOG_BILLBOR_TRK_EDIT2, DIALOG_STYLE_LIST, "Настройка биллборда", "Оставить строку<n>Изменить строку", "Далее", "Закрыть");
				    }
				    case 2:
				    {
						IntfDialogCallRemote(playerid, DIALOG_BILLBOR_TRK_EDIT3, DIALOG_STYLE_LIST, "Настройка биллборда", "Оставить строку<n>Изменить строку", "Далее", "Закрыть");
				    }
				    case 3:
				    {
						IntfDialogCallRemote(playerid, DIALOG_BILLBOR_TRK_EDIT4, DIALOG_STYLE_LIST, "Настройка биллборда", "Оставить строку<n>Изменить строку", "Далее", "Закрыть");
				    }
				    case 4:
				    {
				        new fmt_str[144];
				        new text[144];
						format(fmt_str, sizeof fmt_str, "Ads-%d", BillInfo[bill_id][BillType]);
						SetDynamicObjectMaterial(BillInfo[bill_id][BillID], 2, 3627, "pilorama", fmt_str, 0);
						format(text, sizeof text, "%s\n\n%s\n%s", BillInfo[bill_id][BillText_1], BillInfo[bill_id][BillText_2], BillInfo[bill_id][BillText_3]);
						SetDynamicObjectMaterialText(BillInfo[bill_id][BillIDText], 0, text, 130, "Arial", 30, 1, bill_colors[BillInfo[bill_id][BillColor]], 0, 1);
		                format(fmt_str, sizeof fmt_str, "Ваша реклама успешно размещена на биллборде {FFFFFF}№%d.",bill_id + 1);
		                SCM(BillInfo[bill_id][BillOwnerID], 0xFFA500FF,fmt_str);
		                ModifyCashBalance(playerid, 10000, "зп трк", true, true);
		                BillInfo[bill_id][BillStatus] = 1;
				    }
				    case 5:
				    {
				        new fmt_str[144];
		                format(fmt_str, sizeof fmt_str, "Реклама на биллборде {FFFFFF}№%d {FFA500}была отказана.",bill_id + 1);
		                SCM(BillInfo[bill_id][BillOwnerID], 0xFFA500FF,fmt_str);
					    ModifyCashBalance(BillInfo[bill_id][BillOwnerID], 30000, "аренда биллборда", true, true);
						format(fmt_str, sizeof fmt_str, "Ads-0");
						SetDynamicObjectMaterial(BillInfo[bill_id][BillID], 2, 3627, "pilorama", fmt_str, 0);
						BillInfo[bill_id][BillStatus] = 0;
						BillInfo[bill_id][BillArendaTime] = 0;
						BillInfo[listitem][BillStatus] = 0;
						BillInfo[bill_id][BillOwnerID] = -1;
				    }
				}
			}
		}
		case DIALOG_BILLBOR_SELEC_STROK:
		{
			if(response)
			{
				switch(listitem + 1)
				{
				    case 1:
				    {
						IntfDialogCallRemote(playerid, DIALOG_BILLBOARD_INPUT1, DIALOG_STYLE_INPUT, "Настройка биллборда", "{FFFFFF}Введите текст строки:", "Готово", "Назад");
				    }
				    case 2:
				    {
						IntfDialogCallRemote(playerid, DIALOG_BILLBOARD_INPUT2, DIALOG_STYLE_INPUT, "Настройка биллборда", "{FFFFFF}Введите текст строки:", "Готово", "Назад");
				    }
				    case 3:
				    {
						IntfDialogCallRemote(playerid, DIALOG_BILLBOARD_INPUT3, DIALOG_STYLE_INPUT, "Настройка биллборда", "{FFFFFF}Введите текст строки:", "Готово", "Назад");
				    }

				}
			}
			else
			{
			    SetPVarInt(playerid, "typebill2", 0);
			}
		}
		case DIALOG_BILLBOARD_SELECT:
		{
			if(response)
			{
			    SetPVarInt(playerid, "select_billboard", listitem);
			    if(BillInfo[listitem][BillStatus] == 0)
			    {
			    	IntfDialogCallRemote(playerid, DIALOG_BILLBOARD_ARENDA, DIALOG_STYLE_MSGBOX, "Аренда биллборда", "Хотите арендовать этот биллборд?", "Да", "Назад");
			    }
			    else if(BillInfo[listitem][BillStatus] == 1)
			    {
					SCM(playerid, -1,"Данный билборд арендован или его настраивают!");
				}
				else if(BillInfo[listitem][BillStatus] == 2)
				{
				    if(GetPlayerTeamEx(playerid) == TEAM_TRK)
				    {
				        if(4 <= GetPlayerJob(playerid) <= 10)
				        {
				            new fmt_text[144];
					        format(fmt_text, sizeof fmt_text, "%s<n>%s<n>%s<n>Разместить рекламу<n>Отказать размещать рекламу<n>", BillInfo[listitem][BillText_1], BillInfo[listitem][BillText_2], BillInfo[listitem][BillText_3]);

					        IntfDialogCallRemote(playerid, DIALOG_BILLBOR_TRK_EDIT, DIALOG_STYLE_LIST, "Выберите строку", fmt_text, "Далее", "Закрыть");
				        }
				    }
				}
			}
		}
		case DIALOG_MY_JOBS:
        {
            if(!response) return 1;

            new i = GetPlayerListitemValue(playerid, listitem);

			new job_id = g_player_jobs[playerid][i];

			SetPVarInt(playerid, "jobs_id", job_id);

            string_dialog[0] = EOS;
            format(string_dialog, sizeof string_dialog, "{FFFFFF}Вы действительно хотите уволиться с работы: {FFCD00}\'%s\' {FFFFFF}?", Job_Name[job_id]);
            IntfDialogCallRemote
            (
                playerid, DIALOG_UNINVITE_JOB, DIALOG_STYLE_MSGBOX, 
                "{B3CA5A}Увольнение с работы", 
                string_dialog, 
                "Уволиться", "Закрыть"
            );
        }
        case DIALOG_UNINVITE_JOB:
        {
            if(!response) return 1;

            new job_id = GetPVarInt(playerid, "jobs_id");

			if(job_id < 0 || job_id >= sizeof(Job_Name)){
                printf("[ERROR] Invalid job_id %d for player %d", job_id, playerid);
                return 0;
            }

            SCMF(playerid, 0xff6600FF, "Вы уволились с работы: \"%s\"", Job_Name[job_id]);
            GameText(playerid, "~g~Успешное~n~увольнение", 2500, 2);
            
			for(new i; i < 3; i++)
            {
                if(g_player_jobs[playerid][i] != job_id) continue;
                if(g_player_jobs[playerid][i] == job_id) g_player_jobs[playerid][i] = -1;
		        break;
            }

	        mysql_string[0] = EOS;
            format(mysql_string, sizeof mysql_string, "UPDATE jobs_player SET jobs='%d,%d,%d' WHERE uid = %d LIMIT 1", g_player_jobs[playerid][0], g_player_jobs[playerid][1], g_player_jobs[playerid][2], GetPlayerAccountID(playerid));
            mysql_query(mysql, mysql_string);

			InterfaceEmploymentUpdate(playerid);

			DeletePVar(playerid, "jobs_id");
        }
		case DIALOG_BILLBOARD_ARENDA1:
		{
			if(response)
			{
			    new bill_id = GetPVarInt(playerid, "select_billboard");
		    	new time = strval(inputtext);
			    if(!(2 <= time <= 10)) return CEF_CREATE(playerid, 1, 2, "interface('GameText').add('[2,\"~r~ Допустимый срок: от 2 до 10 часов.\",5000,0,-1,1]')");

			    BillInfo[bill_id][BillArendaTime] = time;
			}
			else
			{
			    SetPVarInt(playerid, "typebill4", 0);
			}
		}
		case DIALOG_BILLBOARD_ARENDA2:
		{
			if(response)
			{
			    new bill_id = GetPVarInt(playerid, "select_billboard");
                SetDynamicObjectMaterialText(BillInfo[bill_id][BillIDText], 0, "Свободный биллборд\n\nДля аренды обратитесь в организацию\n\"ТРК Ритм\" или нажмите N\n", 130, "Arial", 30, 1, 0xFFFFFFFF, 0, 1);
                new fmt_str[144];
				format(fmt_str, sizeof fmt_str, "Ads-0");
				CEF_HIDE(playerid, "Billboard");
				SetDynamicObjectMaterial(BillInfo[bill_id][BillID], 2, 3627, "pilorama", fmt_str, 0);
                BillInfo[bill_id][BillStatus] = 2;
                BillInfo[bill_id][BillOwnerID] = playerid;
                format(fmt_str, sizeof fmt_str, "Вы успешно арендовали биллборд {FFFFFF}№%d {FFA500}за {FFFFFF}30000 рублей. {FFA500}Ожидайте одобрения ТРК для размещения постера",bill_id + 1);
                SCM(playerid, 0xFFA500FF,fmt_str);
                SetCameraBehindPlayer(playerid);
                ModifyCashBalance(playerid, -30000, "аренда биллборда", true, true);
		        SetPlayerPos(playerid, GetPVarFloat(playerid, "pos_x"), GetPVarFloat(playerid, "pos_y"), GetPVarFloat(playerid, "pos_z"));
		        SetPlayerVirtualWorld(playerid, GetPVarInt(playerid, "player_world"));
		        SetPlayerInterior(playerid, GetPVarInt(playerid, "player_int"));
			}
			else
			{
			    SetPVarInt(playerid, "typebill5", 0);
			}
		}
		case DIALOG_BILLBOARD_ARENDA:
		{
			if(response)
			{
			    new bill_id = GetPVarInt(playerid, "select_billboard");

			    if(-200 <= BillInfo[bill_id][BillRotZ] <= -100)
			    {
				    SetPlayerCameraPos(playerid, BillInfo[bill_id][BillPosX] - 7, BillInfo[bill_id][BillPosY] - 2, BillInfo[bill_id][BillPosZ] + 3);
					SetPlayerCameraLookAt(playerid, BillInfo[bill_id][BillPosX], BillInfo[bill_id][BillPosY], BillInfo[bill_id][BillPosZ] + 3, 2);
			    }
			    else if(100 <= BillInfo[bill_id][BillRotZ] <= 200)
			    {
				    SetPlayerCameraPos(playerid, BillInfo[bill_id][BillPosX] - 7, BillInfo[bill_id][BillPosY] + 2, BillInfo[bill_id][BillPosZ] + 3);
					SetPlayerCameraLookAt(playerid, BillInfo[bill_id][BillPosX], BillInfo[bill_id][BillPosY], BillInfo[bill_id][BillPosZ] + 3, 2);
			    }
			    else if(0 <= BillInfo[bill_id][BillRotZ] <= 90)
			    {
				    SetPlayerCameraPos(playerid, BillInfo[bill_id][BillPosX], BillInfo[bill_id][BillPosY] + 8, BillInfo[bill_id][BillPosZ] + 3);
					SetPlayerCameraLookAt(playerid, BillInfo[bill_id][BillPosX], BillInfo[bill_id][BillPosY], BillInfo[bill_id][BillPosZ] + 3, 2);
			    }
			    else if(-90 <= BillInfo[bill_id][BillRotZ] <= -0)
			    {
				    SetPlayerCameraPos(playerid, BillInfo[bill_id][BillPosX], BillInfo[bill_id][BillPosY] - 8, BillInfo[bill_id][BillPosZ] + 3);
					SetPlayerCameraLookAt(playerid, BillInfo[bill_id][BillPosX], BillInfo[bill_id][BillPosY], BillInfo[bill_id][BillPosZ] + 3, 2);
			    }

			    new inter, world, Float:X, Float:Y, Float:Z, Float:FA;
//		     	new Float:health;
				GetPlayerPos(playerid, X, Y, Z);
				GetPlayerFacingAngle(playerid, FA);
				inter = GetPlayerInterior(playerid);
				world = GetPlayerVirtualWorld(playerid);

				SetPVarFloat(playerid, "pos_x", X);
				SetPVarFloat(playerid, "pos_y", Y);
				SetPVarFloat(playerid, "pos_z", Z);
				SetPVarFloat(playerid, "angle", FA);
				SetPVarInt(playerid, "player_int", inter);
				SetPVarInt(playerid, "player_world", world);

		        SetPlayerPos(playerid, BillInfo[bill_id][BillPosX], BillInfo[bill_id][BillPosY], BillInfo[bill_id][BillPosZ]);
		        SetPlayerVirtualWorld(playerid, playerid+1);

                BillInfo[bill_id][BillStatus] = 1;
                format(BillInfo[bill_id][BillText_1], 25, "Пустая строка");
                format(BillInfo[bill_id][BillText_2], 25, "Пустая строка");
                format(BillInfo[bill_id][BillText_3], 25, "Пустая строка");
                BillInfo[bill_id][BillColor] = 0;
                BillInfo[bill_id][BillArendaTime] = 0;
                BillInfo[bill_id][BillOwnerID] = -1;
				SetDynamicObjectMaterialText(BillInfo[bill_id][BillIDText], 0, "\nВведите свой текст", 130, "Arial", 30, 1, 0xFFFFFFFF, 0, 1);
			    CEF_CREATE(playerid, 2, 4, "Billboard", "[\"Фон\", \"Текст\", \"Цвет текста\", \"Длительность аренды\", \"Подтвердить и оплатить\"]");
			}
			else
			{
				callcmd::billboards(playerid);
			}
		}
		case DIALOG_OWNABLE_CAR:
		{
			if(response)
			{
				new idx = GetPVarInt(playerid, "ownablecar_id");
				new vehicleid = INVALID_VEHICLE_ID;

                for(new i = 0; i < MAX_VEHICLES; i++)
				{
				    if(GetVehicleData(i, V_ACTION_TYPE) == VEHICLE_ACTION_TYPE_OWNABLE_CAR)
				    {
					    new iddx = GetVehicleData(i, V_ACTION_ID);
				        if(GetOwnableCarData(iddx,OC_SQL_ID) == idx)
				        {
				            vehicleid = i;
				        }
			        }
				}
				if(vehicleid != INVALID_VEHICLE_ID)
				{
					switch(listitem + 1)
					{
						case 1: // Открыть / закрыть
						{
						    SetPVarInt(playerid, "go_list", 1);
							callcmd::lock(playerid, "1");
						}
						case 2: // Вставить / вытащить ключи
						{
						    SetPVarInt(playerid, "go_list", 1);
							callcmd::key(playerid, "");
						}
						case 3: // Отметить транспорт на GPS
						{
						    SetPVarInt(playerid, "go_list", 1);
							callcmd::getmycar(playerid, "");
						}
						case 4: // Содержимое багажника
						{
							//ShowTrunkDialog(playerid, vehicleid, true);
						}
						case 5: // Документы на транспорт
						{
							ShowOwnableCarPass(playerid, vehicleid);
							SetPVarInt(playerid, "owenrname", playerid);
						}
						case 6: // Припарковать транспорт
						{
							callcmd::park(playerid, "");
						}
						case 7: // Выгрузить транспорт
						{
							if(UnloadPlayerOwnableCar(true, vehicleid))
								SendClientMessage(playerid, 0x66CC33FF, "Ваш транспорт успешно выгружен!");

							else
								SendClientMessage(playerid, 0x999999FF, "С момента загрузки данного транспорта еще не прошло 1 минуты");
						}
						default:
							return 1;
					}
				}
			}
		}
		case DIALOG_SKILL_SHOW:
		{
			if(!response) return 1;

			switch(listitem + 1)
			{
                case 1:
				{   new to_player = GetPVarInt(playerid, "to_player");

                    if(to_player == playerid)
	                {
		                ShowPlayerSkills(playerid);
		                return Action(playerid, "просматривает свои навыки владения оружием", _, false);
	                }

	                if(!IsPlayerInRangeOfPlayer(playerid, to_player, 6.0))
		                return SendClientMessage(playerid, 0x999999FF, "Игрок находится слишком далеко");

	                SendPlayerOffer(playerid, to_player, OFFER_TYPE_SHOW_SKILL);
				}
			}
		}
		case DIALOG_STOYANKA:
		{
			if(!response) return 1;
			page_cars[playerid] = 1;
			type_page_cars[playerid] = 1;
			ShowOwnableCars(playerid, DIALOG_OWNABLE_CAR_LIST2, page_cars[playerid]);
		}
		case DIALOG_OWNABLE_CAR_LOAD:
		{
			if(response)
			{
				new idx = GetPVarInt(playerid, "ownablecar_id"), 
				    Float: x,
				    Float: y,
					Float: z,
					stoyanka,
					Cache: result,
					query[500];

				mysql_format(mysql, query, sizeof query, "SELECT pos_x, pos_y, pos_z,stoyanka FROM ownable_cars WHERE id='%d'", idx);
				result = mysql_query(mysql, query, true);

				if(cache_num_rows())
				{
					x = cache_get_row_float(0, 0);
					y = cache_get_row_float(0, 1);
					z = cache_get_row_float(0, 2);
					stoyanka = cache_get_field_content_int(0, "stoyanka");
				}
				cache_delete(result);

				switch(listitem + 1)
				{
					case 1:
					{
						if(GetPlayerGPSInfo(playerid, G_ENABLED) == GPS_STATUS_OFF)
						{
							EnablePlayerGPS(playerid, 55, x, y, z, "Местоположение Вашего транспорта отмечено на GPS");
							return 1;
						}
						else SendClientMessage(playerid, 0xCECECEFF, "На Вашем GPS уже отмечено место");
					}
					case 2:
					{
                        if(stoyanka == 1) return SCM(playerid, 0xB9C1B8FF, "Ваш личный ТС находится на штрафстоянке");

						if(vehicle_house_id[playerid] != idx)
						{
							if(!IsPlayerInRangeOfPoint(playerid, 45.0, x, y, z))
							{
								SendClientMessage(playerid, 0x999999FF, "Вы слишком далеко от места, где припаркован Ваш транспорт");
							}
							else
							{
								if(LoadOwnableCar(playerid, idx) != -1)
								{
									PlayerOwnableCarInit(playerid, GetPVarInt(playerid, "listitem_car"));
									SendClientMessage(playerid, 0x66CC33FF, "Ваш транспорт успешно загружен!");
								}
								else SendClientMessage(playerid, 0x999999FF, "Ошибка при загрузке личного транспорта");
							}
						}
						else
						{
							if(LoadOwnableCar(playerid, idx) != -1)
							{
								PlayerOwnableCarInit(playerid, GetPVarInt(playerid, "listitem_car"));
								SendClientMessage(playerid, 0x66CC33FF, "Ваш транспорт успешно загружен!");
							}
							else SendClientMessage(playerid, 0x999999FF, "Ошибка при загрузке личного транспорта");
						}
					}
					case 3:
					{
						if(stoyanka == 1) return SCM(playerid, 0xB9C1B8FF, "* Ваш транспорт уже находится на штрафстоянке");

					    if(!VerifyIntString(QueryPlayerBalance(playerid), 500)) return SCM(playerid, -1, "Недостаточно средств");
					    ModifyCashBalance(playerid, -500,"Доставка транспорта на штрафстоянку",true,true);

                        new city_index;

                        if(IsPlayerInRangeOfPoint(playerid, 2000.0, 114.3483,781.5166,11.9461)) 
                            city_index = 0;
                        else 
                            city_index = 1;

                        new rand_index = RandomEx(0, stoyanka_spawn_counts[city_index]);

                        new Float:pos_x = stoyanka_spawn_positions[city_index][rand_index][0];
                        new Float:pos_y = stoyanka_spawn_positions[city_index][rand_index][1];
                        new Float:pos_z = stoyanka_spawn_positions[city_index][rand_index][2];
                        new Float:pos_a = stoyanka_spawn_positions[city_index][rand_index][3];

				 		format(query, sizeof query, "UPDATE ownable_cars SET stoyanka = '1',pos_x=%f,pos_y=%f,pos_z=%f,angle=%f WHERE id=%d LIMIT 1", pos_x, pos_y, pos_z, pos_a, idx);
						mysql_tquery(mysql, query, "", "");
						SCM(playerid, 0x66CC33FF,"Ваш транспорт отправлен на штрафстоянку");
						CreateTicket(playerid, 500, "*Автоматически [ШС]", "*Автоматически [ШС]");
					}
				}
			}
			else
			{
				if(GetPVarInt(playerid, "show_menu"))
				{
					DeletePVar(playerid, "show_menu");
					callcmd::car(playerid, "");
				}
			}
		}
		case DIALOG_OWNABLE_CAR_LIST2:
        {
            if(!response) return 1;

            new idx = GetPlayerListitemValue(playerid, listitem);

            SetPVarInt(playerid, "listitem_car", listitem);
            SetPVarInt(playerid, "ownablecar_id", idx);

            new vehicleid = INVALID_VEHICLE_ID;

            for(new i = 0; i < MAX_VEHICLES; i++)
            {
                if(GetVehicleData(i, V_ACTION_TYPE) == VEHICLE_ACTION_TYPE_OWNABLE_CAR)
                {
                    new iddx = GetVehicleData(i, V_ACTION_ID);
                    if(GetOwnableCarData(iddx, OC_SQL_ID) == idx)
                    {
                        vehicleid = i;
                        break;
                    }
                }
            }

            new query[128];
            mysql_format(mysql, query, sizeof query, "SELECT stoyanka FROM ownable_cars WHERE owner_id=%d AND id=%d", GetPlayerAccountID(playerid), idx);

            new Cache:result = mysql_query(mysql, query, true);

            if(cache_num_rows())
            {
                new stoyanka = cache_get_row_int(0, 0);
                cache_delete(result);

                if(stoyanka != 1)
                {
                    SendClientMessage(playerid, 0x999999FF, "Ваш личный ТС не находится на штрафстоянке");
                    return 1;
                }

                if(vehicleid == INVALID_VEHICLE_ID)
                {
                    new querys[128], Cache:results, rows;
                    mysql_format(mysql, querys, sizeof querys, "SELECT * FROM tickets WHERE uid=%d AND status=0", GetPlayerAccountID(playerid));
                    results = mysql_query(mysql, querys, true);

                    rows = cache_num_rows();
                    new bool:foundTicket = false;

                    for(new i = 0; i < rows; i++)
                    {
                        new id = cache_get_field_content_int(i, "id"), issuer[32];
                        cache_get_field_content(i, "issuer", issuer);

                        if(strcmp(issuer, "*Автоматически [ШС]") == 0)
                        {
                            SCMF(playerid, -1, "{ff2400}Для того чтобы забрать ТС с штрафстоянки, Вы должны оплатить штраф №%d", id);
                            foundTicket = true;
                            break;
                        }
                    }
                    cache_delete(results);

                    if(!foundTicket)
                    {
                        if(LoadOwnableCar(playerid, idx) != -1)
						{
							PlayerOwnableCarInit(playerid, GetPVarInt(playerid, "listitem_car"));
							format(query, sizeof query, "UPDATE ownable_cars SET stoyanka = '0' WHERE id=%d LIMIT 1", idx);
						    mysql_tquery(mysql, query, "", "");
							SendClientMessage(playerid, 0xB9C1B8FF, "Личный транспорт появился в ограниченной местности.");
							SendClientMessage(playerid, 0xB9C1B8FF, "Заберите его не позднее 1 минуты, иначе он будет выгружен.");
							SendClientMessage(playerid, 0xffbe5cFF, "Время стоянки ограничено до 1 мин.");
							OnBattlePass_Perfomance(playerid, 27, 1);
						}
                    }
                }
            }
            else
            {
                cache_delete(result);
            }
        }
		case DIALOG_OWNABLE_CAR_SELECT:
		{
			if(response)
			{
				new fmt_text[144], Cache: result;
				new to_player = GetPVarInt(playerid, "to_player");
				new id = GetPlayerListitemValue(playerid, listitem);

				mysql_format(mysql, fmt_text, sizeof fmt_text, "SELECT * FROM ownable_cars WHERE id='%d'", id);
				result = mysql_query(mysql, fmt_text, true);

				new rows = cache_num_rows();

				for(new i = 0; i < rows; i ++)
				{
					new vehicleid = INVALID_VEHICLE_ID;

					for(new is = 0; is < MAX_VEHICLES; is++)
					{
						if(GetVehicleData(is, V_ACTION_TYPE) == VEHICLE_ACTION_TYPE_OWNABLE_CAR)
						{
							new iddx = GetVehicleData(is, V_ACTION_ID);
							if(GetOwnableCarData(iddx,OC_SQL_ID) == id)
							{
								vehicleid = is;
							}
						}
					}
					if(vehicleid != INVALID_VEHICLE_ID)
					{
						new model_id = cache_get_field_content_int(i, "model_id") ;
						format(fmt_text, sizeof fmt_text, "Вы выбрали транспорт: %s", GetVehicleInfo(model_id, VI_NAME));
						SendClientMessage(playerid, 0xFFFFFFFF, fmt_text);

						new Float: x, Float: y,Float: z;

						GetPlayerPos(to_player, x, y, z);

						SetVehiclePos(vehicleid, x + 2.0, y + 2.0, z);

						SendClientMessage(to_player, COLOR_WHITE, "Вы успешно телепортировали к себе свой личный транспорт");
					}
					else
					{
						LoadOwnableCar(to_player, id);
						for(new is = 0; is < MAX_VEHICLES; is++)
						{
							if(GetVehicleData(is, V_ACTION_TYPE) == VEHICLE_ACTION_TYPE_OWNABLE_CAR)
							{
								new iddx = GetVehicleData(is, V_ACTION_ID);
								if(GetOwnableCarData(iddx,OC_SQL_ID) == id)
								{
									vehicleid = is;
								}
							}
						}
						new Float: x, Float: y,Float: z;

						GetPlayerPos(to_player, x, y, z);
						SetVehiclePos(vehicleid, x + 2.0, y + 2.0, z);
						SendClientMessage(to_player, COLOR_WHITE, "Вы успешно телепортировали к себе свой личный транспорт");
					}
				}
				cache_delete(result);
			}
		}
		case DIALOG_OWNABLE_CAR_SPAWN:
		{
			if(!response) return 1;

			new idx = GetPlayerListitemValue(playerid, listitem);

			SetPVarInt(playerid, "listitem_car", listitem);
			SetPVarInt(playerid, "ownablecar_id", idx);

			new veh_id = INVALID_VEHICLE_ID;

			for(new i = 0; i < MAX_VEHICLES; i++)
			{
				if(GetVehicleData(i, V_ACTION_TYPE) == VEHICLE_ACTION_TYPE_OWNABLE_CAR)
				{
					new iddx = GetVehicleData(i, V_ACTION_ID);
					if(GetOwnableCarData(iddx,OC_SQL_ID) == idx)
					{
						veh_id = i;
					}
				}
			}

			if(veh_id == INVALID_VEHICLE_ID) 
			{
				SCM(playerid, 0x999999FF, "Данный транспорт не загружен на сервер");
				CEF_HIDE(playerid, "SelectSpawn");
				return true;
			}
			new model_id = GetVehicleData(veh_id, V_MODELID);

			for(new i; i < sizeof g_vehicle_house; i++)
			{
				if(g_vehicle_house[i] != model_id) continue;

				SetPlayerData(playerid, P_ID_SPAWN, idx);
				UpdatePlayerDatabaseInt(playerid, "id_spawn", idx);

				SetPlayerData(playerid, P_SPAWN, 5);
				UpdatePlayerDatabaseInt(playerid, "setting_spawn", 5);
				SendClientMessage(playerid, 0x3399FFFF, "Место появления в игре изменено");
				CEF_HIDE(playerid, "SelectSpawn");

				return true;
			}
			SCM(playerid, COLOR_GREY, "Данный транспорт не предназначен для спавна");
			CEF_HIDE(playerid, "SelectSpawn");
		}
		case DIALOG_OWNABLE_CAR_NUMBER:
		{
			if(!response) return 1;

			new idx = g_player_listitem[playerid][listitem];

			SetPVarInt(playerid, "listitem_car", listitem);
			SetPVarInt(playerid, "ownablecar_id", idx);

			new vehicleid = INVALID_VEHICLE_ID;

			for(new i = 0; i < MAX_VEHICLES; i++)
			{
				if(GetVehicleData(i, V_ACTION_TYPE) == VEHICLE_ACTION_TYPE_OWNABLE_CAR)
				{
					new iddx = GetVehicleData(i, V_ACTION_ID);
					if(GetOwnableCarData(iddx,OC_SQL_ID) == idx)
					{
						vehicleid = i;
					}
				}
			}

			if(vehicleid != INVALID_VEHICLE_ID)
			{
				new index = GetVehicleData(vehicleid, V_ACTION_ID);
				if(GetOwnableCarData(index, OC_NUMBER_STATUS) == 0)
				{
					InterfaceShowNumberBuy(playerid, true);
					SetPVarInt(playerid, "ownablecar_id", vehicleid);
				}
				else
				{
					SCM(playerid, COLOR_GREY, "*На данный транспорт уже выдавались номера");
				}
			}
			else
			{
				SendClientMessage(playerid, 0xFF6600FF, "Ваш личный ТС должен находиться на сервере");
			}
		}
		case DIALOG_SELL_CAR:
		{
			if(!response) return 1;

			new idx = GetPlayerListitemValue(playerid, listitem);

			SetPVarInt(playerid, "listitem_car", listitem);
			SetPVarInt(playerid, "ownablecar_id", idx);

			new vehicleid = INVALID_VEHICLE_ID;

			for(new i = 0; i < MAX_VEHICLES; i++)
			{
				if(GetVehicleData(i, V_ACTION_TYPE) == VEHICLE_ACTION_TYPE_OWNABLE_CAR)
				{
					new iddx = GetVehicleData(i, V_ACTION_ID);
					if(GetOwnableCarData(iddx,OC_SQL_ID) == idx)
					{
						vehicleid = i;
					}
				}
			}

			if(vehicleid != INVALID_VEHICLE_ID)
			{
				new model_id = GetVehicleData(vehicleid, V_MODELID);
				if(model_id)
				{
					string_dialog[0] = EOS;

					new price = GetVehicleInfo(model_id, VI_PRICE);
					new percent_default = price / 100 * 60;
					new percent = price / 150 * GetVehicleData(vehicleid, V_IZNOS);

					format
					(
						string_dialog, sizeof string_dialog,
						"Модель:\t%s (№%d)\n"\
						"Вы получите:\t%s руб\n\n"\
						"Вы уверены что хотите утилизировать ТС?\n"\
						"Все предметы из багажника будут удалены\n"\
						"На Ваш банковский счет будет начислено %s руб\n\n"\
						"Если двигатель изношен не полностью, то\n"\
						"Вы также можете продать ТС другому игроку,\n"\
						"{008000}используя команду /sellmycar",
						GetVehicleName(vehicleid),
						model_id,
						formatInt(price - (percent + percent_default)),
						formatInt(price - (percent + percent_default))
					);
					IntfDialogCallRemote(playerid, DIALOG_OWNABLE_CAR_SELL, DIALOG_STYLE_MSGBOX, "Утилизация личного транспорта", string_dialog, "Да", "Нет");
				}
			}
			else
			{
				if(GetPlayerOwnableCars(playerid) == 0) SendClientMessage(playerid, 0xFF6600FF, "У Вас нет личного транспорта");
				else SendClientMessage(playerid, 0xFF6600FF, "Данный транспорт не загружен на сервер");
			}
		}
		case DIALOG_CRAFT_CAR:
        {
            if(!response) return CraftDialog[playerid] = 0;

            new idx = GetPlayerListitemValue(playerid, listitem);

            SetPVarInt(playerid, "listitem_car", listitem);
            SetPVarInt(playerid, "ownablecar_id", idx);

            new vehicleid = INVALID_VEHICLE_ID;

            for(new i = 0; i < MAX_VEHICLES; i++)
            {
                if(GetVehicleData(i, V_ACTION_TYPE) == VEHICLE_ACTION_TYPE_OWNABLE_CAR)
                {
                    new iddx = GetVehicleData(i, V_ACTION_ID);
                    if(GetOwnableCarData(iddx, OC_SQL_ID) == idx)
                    {
                        vehicleid = i;
                        break;
                    }
                }
            }

            new query[128];
            mysql_format(mysql, query, sizeof query, "SELECT model_id, stoyanka FROM ownable_cars WHERE owner_id=%d AND id=%d", GetPlayerAccountID(playerid), idx);

            new Cache:result = mysql_query(mysql, query, true);

            if(cache_num_rows())
            {
                new model_id = cache_get_row_int(0, 0);
                new stoyanka = cache_get_row_int(0, 1);

                if(model_id == CraftSet[playerid])
                {
				    if(stoyanka == 1)
                    {
                        CraftError[playerid] = 2;
					    CraftDialog[playerid] = 0;
                        CraftModel[playerid] = model_id;
                        cache_delete(result);
                        return 1;
                    }

                    if(vehicleid != INVALID_VEHICLE_ID)
                    {
						new ownablecar_id = GetVehicleData(vehicleid, V_ACTION_ID);
                        if(GetOwnableCarData(ownablecar_id, OC_NUMBERTYPE) != 0)
                        {
                            CraftError[playerid] = 3;
                            CraftDialog[playerid] = 0;
                            CraftModel[playerid] = model_id;
                            cache_delete(result);
                            return 1;
                        }

						new accessoryQuery[128];
                        mysql_format(mysql, accessoryQuery, sizeof accessoryQuery, "SELECT id FROM cars_accessories WHERE car_id=%d LIMIT 1", idx);
                        new Cache:accessoryResult = mysql_query(mysql, accessoryQuery, true);

                        if(cache_num_rows() > 0)
                        {
                            CraftError[playerid] = 4;
                            CraftDialog[playerid] = 0;
                            CraftModel[playerid] = model_id;
							cache_delete(result);
                            cache_delete(accessoryResult);
                            return 1;
                        }

						new items_car_query[128];
                        mysql_format(mysql, items_car_query, sizeof items_car_query, "SELECT id FROM items WHERE car_id=%d LIMIT 1", idx);
                        new Cache:Items_car_Result = mysql_query(mysql, items_car_query, true);

                        if(cache_num_rows() > 0)
                        {
                            CraftError[playerid] = 5;
                            CraftDialog[playerid] = 0;
                            CraftModel[playerid] = model_id;
							cache_delete(result);
                            cache_delete(accessoryResult);
							cache_delete(Items_car_Result);
                            return 1;
                        }

						for(new i = 0; i < SelectedCarCount[playerid]; i++)
                        {
                            if(SelectedCars[playerid][i] == idx)
                            {
								CraftDialog[playerid] = 0;
								cache_delete(result);
                                cache_delete(accessoryResult);
								cache_delete(Items_car_Result);
                                return 1;
                            }
                        }

                        switch(SelectedCraft[playerid])
                        {
                            case 0: SelectedCraft[playerid] = 1;
                            case 1: SelectedCraft[playerid] = 2;
                            case 2: SelectedCraft[playerid] = 3;
                            case 3: SelectedCraft[playerid] = 4;
                        }

						SelectedCars[playerid][SelectedCarCount[playerid]] = idx;
                        SelectedCarCount[playerid]++;
						CraftDialog[playerid] = 0;
                    }
                    else
                    {
                        CraftError[playerid] = 1;
					    CraftDialog[playerid] = 0;
                        CraftModel[playerid] = model_id;
					}
                }
				else
                {
                    SelectedCraft[playerid] = 0;
					CraftDialog[playerid] = 0;
                    return 1;
                }
            }
            cache_delete(result);
        }
		case DIALOG_DISKI_CAR:
		{
			if(!response) return 1;

			new idx = GetPlayerListitemValue(playerid, listitem);

			SetPVarInt(playerid, "listitem_car", listitem);
			SetPVarInt(playerid, "ownablecar_id", idx);

			new vehicleid = INVALID_VEHICLE_ID;

            for(new i = 0; i < MAX_VEHICLES; i++)
			{
				if(GetVehicleData(i, V_ACTION_TYPE) == VEHICLE_ACTION_TYPE_OWNABLE_CAR)
				{
					new iddx = GetVehicleData(i, V_ACTION_ID);
					if(GetOwnableCarData(iddx,OC_SQL_ID) == idx)
					{
						vehicleid = i;
					}
				}
			}

			if(vehicleid != INVALID_VEHICLE_ID)
			{
				new Float:x, Float:y, Float:z, Float:a;

				GetVehiclePos(vehicleid, x, y, z);
				GetVehicleZAngle(vehicleid, a);

				if(!IsPlayerInRangeOfPoint(playerid, 15.0, x, y, z)) return SendClientMessage(playerid, 0xead671FF, "Транспорт должен находиться на территории шиномонтажа.");

				new model_id = GetVehicleData(vehicleid, V_MODELID);
				if(model_id)
				{
					DiskiStyling(playerid);
				    
					new Float:c_x, Float:c_y, Float:c_z, Float:c_a;
                    GetVehiclePos(vehicleid, c_x, c_y, c_z);
                    GetVehicleZAngle(vehicleid, c_a);

                    new Float:camX = c_x, Float:camY = c_y, Float:camZ = c_z + 1.5;

                    if((c_a >= 315.0) || (c_a < 45.0))
                        camX += 7.0;
                    else if(c_a >= 45.0 && c_a < 135.0) 
                        camY += 7.0;
                    else if(c_a >= 135.0 && c_a < 225.0)
                        camX -= 7.0;
                    else if(c_a >= 225.0 && c_a < 315.0)
                        camY -= 7.0;

                    SetPlayerCameraPos(playerid, camX, camY, camZ);
                    SetPlayerCameraLookAt(playerid, c_x, c_y, c_z + 0.5, 1);
				}
			}
			else
			{
				if(GetPlayerOwnableCars(playerid) == 0) SendClientMessage(playerid, 0xFF6600FF, "У Вас нет личного транспорта");
				else SendClientMessage(playerid, 0xFF6600FF, "Данный транспорт не загружен на сервер");
			}
		}
		case DIALOG_SELL_OWNABLE_CAR:
		{
			if(!response) return 1;

			new idx = GetPlayerListitemValue(playerid, listitem);

			SetPVarInt(playerid, "listitem_car", listitem);
			SetPVarInt(playerid, "ownablecar_id", idx);

			new veh_id = INVALID_VEHICLE_ID;

			for(new i = 0; i < MAX_VEHICLES; i++)
			{
				if(GetVehicleData(i, V_ACTION_TYPE) == VEHICLE_ACTION_TYPE_OWNABLE_CAR)
				{
					new iddx = GetVehicleData(i, V_ACTION_ID);
					if(GetOwnableCarData(iddx,OC_SQL_ID) == idx)
					{
						veh_id = i;
					}
				}
			}

			if(veh_id == INVALID_VEHICLE_ID) return SCM(playerid, 0x999999FF, "Данный транспорт не загружен на сервер");
			new to_player = GetPVarInt(playerid, "SellCarTo_player");

			new Float: car_x, Float: car_y, Float: car_z;
			GetVehiclePos(veh_id, car_x, car_y, car_z);

			if(IsPlayerInRangeOfPoint(playerid, 15.0, car_x, car_y, car_z) && IsPlayerInRangeOfPoint(to_player, 15.0, car_x, car_y, car_z))
			{
				SendPlayerOffer(playerid, to_player, OFFER_TYPE_SELL_OWNABLE_CAR, 1, veh_id);
			}
			else SendClientMessage(playerid, 0xCECECEFF, "Вы и покупатель должны находиться около ТС");
		}
		case DIALOG_OWNABLE_CAR_LIST:
		{
			if(response)
			{
				new idx = g_player_listitem[playerid][listitem];

				SetPVarInt(playerid, "listitem_car", listitem);
				SetPVarInt(playerid, "ownablecar_id", idx);

				new veh_id = INVALID_VEHICLE_ID;

                for(new i = 0; i < MAX_VEHICLES; i++)
				{
				    if(GetVehicleData(i, V_ACTION_TYPE) == VEHICLE_ACTION_TYPE_OWNABLE_CAR)
				    {
					    new iddx = GetVehicleData(i, V_ACTION_ID);
				        if(GetOwnableCarData(iddx,OC_SQL_ID) == idx)
				        {
				            veh_id = i;
				        }
			        }
				}

				if(veh_id == INVALID_VEHICLE_ID)
				{
					ShowOwnableCarLoadDialog(playerid, idx, true);
				}
				else
				{
					IntfDialogCallRemote
					(
						playerid, DIALOG_OWNABLE_CAR, DIALOG_STYLE_LIST,
						"{0099FF}Система управления транспортом",
						"1. {669900}Открыть {FFFFFF}или {FF3300}закрыть {FFFFFF}транспорт\n"\
						"2. Вставить / вытащить ключи\n"\
						"3. Отметить транспорт на GPS {FF6600}(5000 руб)\n"\
						"4. Содержимое багажника\n"\
						"5. Документы на транспорт\n"\
						"{888888}6. Припарковать транспорт\n"\
						"{888888}7. Выгрузить транспорт с сервера",
						"Выбрать", "Закрыть"
					);
				}
			}
		}
		case DIALOG_PNEWMA_BUY:
		{
			if(!response) return 1;

			new vehicleid = GetPlayerVehicleID(playerid);
			new index = GetVehicleData(vehicleid, V_ACTION_ID);
			new modelid = GetVehicleData(vehicleid, V_MODELID);

			if(GetVehicleHandlingID(modelid) == -1) return GameText(playerid, "~r~На данный транспорт невозможно установить пневму", 3000, 1);

			if(!VerifyIntString(QueryPlayerBalance(playerid), 1000000)) return SendClientMessage(playerid, 0x999999FF, "Недостаточно средств!");

			ModifyCashBalance(playerid, -1000000, "Покупка пневмы", true, true);

			SetOwnableCarData(index, OC_PNEWMA, 1);
			SaveOwnableCar(vehicleid);

			SetPlayerVirtualWorld(playerid, 0);
			SetVehicleVirtualWorld(vehicleid, 0);
			SetVehiclePos(vehicleid, -413.4231,1010.6860,12.0819);
			SetVehicleZAngle(vehicleid, 2.8581);
			SetCameraBehindPlayer(playerid);

			TogglePlayerControllable(playerid, 1);

			SpeedometrShowForPlayer(playerid);

			SCM(playerid, 0xFFFFFFFF, "Вы установили на свой автомобиль пневматическую подвеску за {c07700}1.000.000 RUB{FFFFFF}.");
			SCM(playerid, 0xFFFFFFFF, "Управление подвеской доступно через специальный пульт: {c8c993}/spanel{FFFFFF}.");
			CEF_HIDE(playerid, "TuningPneuma");
		}
        case DIALOG_BIZ_CAR_SELL:
		{
			if(response)
			{
				new vehicleid = GetPVarInt(playerid, "vehicleid");
				if(vehicleid != INVALID_VEHICLE_ID)
				{
					new model_id = GetVehicleData(vehicleid, V_MODELID);

					if(DestroyRentCar(vehicleid))
					{
						new fmt_str[128];

						new car_price = GetVehicleInfo(model_id, VI_PRICE);
						new percent = car_price * 20 / 100;
						new price = car_price - percent;
					
						format(g_player[playerid][P_BANK], 21, "%s", SetILPlayerInt(playerid, GetPlayerBankMoney(playerid), price));

						BankLog(playerid, price, "продажа тс аренды");

						format(fmt_str, sizeof fmt_str, "UPDATE accounts_canvasdev SET bank=%s WHERE id=%d LIMIT 1", GetPlayerBankMoney(playerid), GetPlayerAccountID(playerid));
						mysql_query(mysql, fmt_str, false);

						SendClientMessage(playerid, 0x3399FFFF, "Вы продали транспорт со своей аренды авто");

						format(fmt_str, sizeof fmt_str, "Налоговый сбор составляет 30 процентов от его стоимости {FF9900}(%d руб)", percent);
						SendClientMessage(playerid, 0xFFFFFFFF, fmt_str);

						format(fmt_str, sizeof fmt_str, "На основной банковский счет переведено {FFFF00}%d руб", price);
						SendClientMessage(playerid, 0x66CC00FF, fmt_str);

						format(fmt_str, sizeof fmt_str, "~g~+%d rub", price);
						GameText(playerid, fmt_str, 4000, 2);
					}
				}
			}
		}
		case DIALOG_OWNABLE_CAR_SELL:
		{
			if(!response) return 1;
			
			new idx = GetPVarInt(playerid, "ownablecar_id");

			new vehicleid = INVALID_VEHICLE_ID;

			for(new i = 0; i < MAX_VEHICLES; i++)
			{
				if(GetVehicleData(i, V_ACTION_TYPE) == VEHICLE_ACTION_TYPE_OWNABLE_CAR)
				{
					new iddx = GetVehicleData(i, V_ACTION_ID);
					if(GetOwnableCarData(iddx,OC_SQL_ID) == idx)
					{
						vehicleid = i;
					}
				}
			}

			if(vehicleid != INVALID_VEHICLE_ID)
			{
				new model_id = GetVehicleData(vehicleid, V_MODELID);

				if(DestroyOwnableCar(vehicleid))
				{
					new fmt_str[128];

					new car_price = GetVehicleInfo(model_id, VI_PRICE);
					new percent = car_price / 150 * GetVehicleData(vehicleid, V_IZNOS);
					new percent_default = car_price / 100 * 60;
					new price = car_price - (percent + percent_default);

					format(g_player[playerid][P_BANK], 21, "%s", SetILPlayerInt(playerid, GetPlayerBankMoney(playerid), price));

					format(fmt_str, sizeof fmt_str, "UPDATE accounts_canvasdev SET bank=%s WHERE id=%d LIMIT 1", GetPlayerBankMoney(playerid), GetPlayerAccountID(playerid));
					mysql_query(mysql, fmt_str, false);

					BankLog(playerid, price, "Продажа личного транспорта");

					SendClientMessage(playerid, 0x3399FFFF, "Вы утилизировали личный транспорт");

					format(fmt_str, sizeof fmt_str, "На основной банковский счет переведено {FFFF00}%s руб", formatInt(price));
					SendClientMessage(playerid, 0x66CC00FF, fmt_str);
				}
			}
		}
			case DIALOG_OWNABLE_BIZ_NOTARY:
			{
				if(response)
				{
					new idx = GetPlayerListitemValue(playerid, listitem) + 1;
					SetPVarInt(playerid, "ownablebiz_id", idx);
					new businessid = GetPVarInt(playerid, "ownablebiz_id");
					STRING_GLOBAL[0] = EOS;
					format(STRING_GLOBAL, sizeof STRING_GLOBAL, "interface('Trade').updateData('{\"player1\": {\"item\": 1,\"itemName\": \"Бизнес %s [№%d]\",\"itemPrice\": %d,\"itemSurcharge\": %d,\"state\": 0,\"commission\": 0}}')", GetBusinessData(businessid, B_NAME), businessid, GetBusinessData(businessid, B_PRICE), GetPVarInt(playerid, "itemSurcharge"));
					CEF_CREATE(playerid, 1, 2, STRING_GLOBAL);
					STRING_GLOBAL[0] = EOS;
					format(STRING_GLOBAL, sizeof STRING_GLOBAL, "interface('Trade').updateData('{\"player2\": {\"item\": 1,\"itemName\": \"Бизнес %s [№%d]\",\"itemPrice\": %d,\"itemSurcharge\": %d,\"state\": 0,\"commission\": 0}}')", GetBusinessData(businessid, B_NAME), businessid, GetBusinessData(businessid, B_PRICE), GetPVarInt(GetPVarInt(playerid, "Trade_player1"), "itemSurcharge"));
					CEF_CREATE(GetPVarInt(playerid, "Trade_player1"), 1, 2, STRING_GLOBAL);
					SetPVarInt(playerid, "NotaryObject", 2);
				}
			}	
			case DIALOG_OWNABLE_GARAGE_NOTARY:
			{
				if(response)
				{
					new idx = GetPlayerListitemValue(playerid, listitem) + 1;
					SetPVarInt(playerid, "ownablegarage_id", idx);
					new businessid = GetPVarInt(playerid, "ownablegarage_id");
					STRING_GLOBAL[0] = EOS;
					format(STRING_GLOBAL, sizeof STRING_GLOBAL, "interface('Trade').updateData('{\"player1\": {\"item\": 1,\"itemName\": \"Гараж [№%d]\",\"itemPrice\": %d,\"itemSurcharge\": %d,\"state\": 0,\"commission\": 0}}')", businessid, GetGarageData(businessid, G_PRICE), GetPVarInt(playerid, "itemSurcharge"));
					CEF_CREATE(playerid, 1, 2, STRING_GLOBAL);
					STRING_GLOBAL[0] = EOS;
					format(STRING_GLOBAL, sizeof STRING_GLOBAL, "interface('Trade').updateData('{\"player2\": {\"item\": 1,\"itemName\": \"Гараж [№%d]\",\"itemPrice\": %d,\"itemSurcharge\": %d,\"state\": 0,\"commission\": 0}}')", businessid, GetGarageData(businessid, G_PRICE), GetPVarInt(GetPVarInt(playerid, "Trade_player1"), "itemSurcharge"));
					CEF_CREATE(GetPVarInt(playerid, "Trade_player1"), 1, 2, STRING_GLOBAL);
					SetPVarInt(playerid, "NotaryObject", 8);
				}
			}
			case DIALOG_OWNABLE_NEFTENASOS_LIST2:
			{
				if(!response) return 1;
				new businessid = GetPlayerListitemValue(playerid, listitem);
				SetPVarInt(playerid, "ownableneft_id", businessid);
				
				string_dialog[0] = EOS;

				format
				(
					string_dialog, sizeof string_dialog,
					"{FFFFFF}Нефтенасос {006400}№%d\n\
					{FFFFFF}Оплачено: {006400}%d/5 дн.\n\
					{FFFFFF}Стоимость аренды за 1 день составляет {006400}%d руб.",
					businessid, GetNeftData(businessid, N_RENT_DATE), GetNeftData(businessid, N_RENT_PRICE)
				);

				IntfDialogCallRemote(playerid, DIALOG_ATM_NEFTENASOS_RENT, DIALOG_STYLE_INPUT, "{FFFFFF}Оплата аренды нефтенасоса", string_dialog, "Готово", "Назад");
			}
			case DIALOG_ATM_NEFTENASOS_RENT:
			{
				new businessid = GetPVarInt(playerid, "ownableneft_id");
				if(businessid != -1)
				{
					if(response)
					{
						new days = strval(inputtext);
						if(days > 0 && IsNumeric(inputtext))
						{
							new fmt_str[128 + 1];

							new rent_time = GetNeftData(businessid, N_RENT_DATE);

							new rent_price = GetNeftData(businessid, N_RENT_PRICE);

							new total_price = rent_price * days;
							if((rent_time + days) <= 5)
							{
								if(VerifyIntString(GetPlayerBankMoney(playerid), total_price))
								{

									format(fmt_str, sizeof fmt_str, "UPDATE accounts_canvasdev a,neftenasos b SET a.bank=%s,b.rent=%d WHERE a.id=%d AND b.id=%d", SetILPlayerInt(playerid, GetPlayerBankMoney(playerid), -total_price), days + rent_time, GetPlayerAccountID(playerid), GetNeftData(businessid, N_SQL_ID));
									mysql_query(mysql, fmt_str, false);

									if(!mysql_errno())
									{
										format(g_player[playerid][P_BANK], 21, "%s", SetILPlayerInt(playerid, GetPlayerBankMoney(playerid), -total_price));
										SetNeftData(businessid, N_RENT_DATE, days + rent_time);

										format(fmt_str, sizeof fmt_str, "С банковского счета снято {3399FF}%d руб", total_price);
										SendClientMessage(playerid, 0xFFFFFFFF, fmt_str);

										format(fmt_str, sizeof fmt_str, "Вы успешно продлили аренду нефтенасоса еще на {3399FF}%d дней", days);
										SendClientMessage(playerid, 0x66CC00FF, fmt_str);
									}
								}
								else
								{
									SendClientMessage(playerid, 0xB5B500FF, "На основном банковском счету не хватает денег для оплаты");

									format(fmt_str, sizeof fmt_str, "Для продления аренды на %d дней необходимо %d руб", days, total_price);
									SendClientMessage(playerid, 0x999999FF, fmt_str);
								}
							}
							else SendClientMessage(playerid, 0xB5B500FF, "Вы не можете оплатить за аренду больше чем на 5 дней");
						}
					}
					else ShowPlayerPayForRentDialog(playerid);
				}
			}
			case DIALOG_OWNABLE_NEFTENASOS_LIST:
			{
				if(!response) return ShowPlayerATMDialog(playerid);
				new idx = GetPlayerListitemValue(playerid, listitem) + 1;
				SetPVarInt(playerid, "ownableneft_id", idx);
				new fmt[148];
				format(fmt, sizeof fmt,"{FFFFFF}Нефтенасос {006400}№%d\n{FFFFFF}Баланс: {006400}%d {FFFFFF}руб.\n\nСколько вы хотите снять?", idx, GetNeftData(idx, N_BALANCE));
				IntfDialogCallRemote(playerid, DIALOG_ATM_NEFTENASOS_PUT_MONEY, DIALOG_STYLE_INPUT,"{FFFFFF}Снятие средств",fmt,"Готово", "Назад");
			}
			case DIALOG_OWNABLE_BIZ_LIST:
			{
				if(response)
				{
					new idx = GetPlayerListitemValue(playerid, listitem) + 1;
					SetPVarInt(playerid, "ownablebiz_id", idx);

				    new businessid = idx;
					if(businessid != -1)
					{
						static const
							music_name[6][9] = {"Отключен", "Звук 1", "Звук 2", "Звук 3", "Звук 4", "Звук 5"};

						if(GetBusinessData(businessid, B_ENTER_MUSIC) > sizeof music_name - 1) SetBusinessData(businessid, B_ENTER_MUSIC, sizeof music_name - 1);

						string_dialog[0] = EOS;
						if(GetBusinessData(businessid, B_TYPE) != 36 && GetBusinessData(businessid, B_TYPE) != 37)
						{
							if(GetBusinessData(businessid, B_TYPE) == BUSINESS_TYPE_ARENDA)
							{
								format
								(
									string_dialog, sizeof string_dialog,
									"{FFFFFF}Название:<t><t><t><t>{339999}%s\n"\
									"{FFFFFF}Номер бизнеса:<t><t><t>%d\n"\
									"Владелец:<t><t><t><t>%s\n"\
									"Город / область:<t><t><t>%s\n"\
									"Район:<t><t><t><t><t>%s\n"\
									"Количество продуктов:<t><t>%d из %d\n"\
									"Стоимость 1 продукта:<t><t>%d руб\n"\
									"Уровень улучшений:<t><t><t>%d\n"\
									"Баланс предприятия:<t><t><t>%s руб\n"\
									"Бизнес арендован на:<t><t>%d/30 дней\n"\
									"{FFFFFF}Гос. стоимость:<t><t><t>%s руб\n"\
									"Аренда помещения:<t><t><t>%d руб в день\n"\
									"Тип аренды:<t><t><t><t>%s\n"\
									"{669966}Для открытия панели управления вашим бизнесом\n"\
									"нажмите кнопку Изменить",
									GetBusinessData(businessid, B_NAME),
									businessid,
									GetBusinessData(businessid, B_OWNER_NAME),
									GetCityName(GetBusinessData(businessid, B_CITY)),
									GetZoneName(GetBusinessData(businessid, B_ZONE)),
									GetBusinessData(businessid, B_PRODS),
									GetBusinessMaxProd(businessid),
									GetBusinessData(businessid, B_PROD_PRICE),
									GetBusinessData(businessid, B_IMPROVEMENTS),
									formatStr(GetBusinessData(businessid, B_BALANCE)),
									GetBusinessData(businessid, B_RENT_DATE) <= gettime() ? 0 :
									GetElapsedTime(GetBusinessData(businessid, B_RENT_DATE), gettime(), CONVERT_TIME_TO_DAYS),
									formatInt(GetBusinessData(businessid, B_PRICE)),
									GetBusinessData(businessid, B_IMPROVEMENTS) < 3 ? (GetBusinessData(businessid, B_RENT_PRICE)) : (GetBusinessData(businessid, B_RENT_PRICE) / 2),
									GetBusinessData(businessid, B_IMPROVEMENTS) < 3 ? ("Полная") : ("Льготная")
								);
							}
							else
							{
								new type;
								for(new i; i < g_business_loaded; i ++)
								{
									if(GetBusinessData(i, B_TYPE) != 36) continue;
									if(GetBusinessData(i, B_ELECTRICITY) != GetBusinessData(businessid, B_ELECTRICITY)) continue;

									type = i;

								}

								new fmt_text[148];
								if(type != 0)
								{
									if(GetBusinessData(type, B_VETR_WORK) != 0) 
                                        format(fmt_text, sizeof fmt_text, "{66CC33}%s (Работает)", GetBusinessData(type, B_NAME));
                                    else 
                                        format(fmt_text, sizeof fmt_text, "{CC3333}%s (Сломан)", GetBusinessData(type, B_NAME));
								}
								else 
									format(fmt_text, sizeof fmt_text, "{CC3333}Нет", GetBusinessData(type, B_NAME));

								format
								(
									string_dialog, sizeof string_dialog,
									"{FFFFFF}Название:<t><t><t><t>{339999}%s\n"\
									"{FFFFFF}Номер бизнеса:<t><t><t>%d\n"\
									"Владелец:<t><t><t><t>%s\n"\
									"Город / область:<t><t><t>%s\n"\
									"Район:<t><t><t><t><t>%s\n"\
									"Плата за вход:<t><t><t>%d руб\n"\
									"Количество продуктов:<t><t>%d из %d\n"\
									"Стоимость 1 продукта:<t><t>%d руб\n"\
									"Уровень улучшений:<t><t><t>%d\n"\
									"Баланс предприятия:<t><t><t>%s руб\n"\
									"Бизнес арендован на:<t><t>%d/30 дней\n"\
									"Звук при входе:<t><t><t>{%s}%s\n"\
									"{FFFFFF}Гос. стоимость:<t><t><t>%s руб\n"\
									"Аренда помещения:<t><t><t>%d руб в день\n"\
									"Тип аренды:<t><t><t><t>%s\n"\
									"Статус:<t><t><t><t><t>%s\n\n"\
									"{FFFFFF}Электричество:<t><t><t>%s\n"\
									"{FFFFFF}Потребление за 1 час:<t><t><t>17 кВт\n"\
									"{FFFFFF}Поставщик энергии:<t><t><t><t>%s\n"\
									"{FFFFFF}Тариф за энергию:<t><t><t><t><t>%d руб\n\n"\
									"{669966}Для открытия панели управления вашим бизнесом\n"\
									"нажмите кнопку Изменить",
									GetBusinessData(businessid, B_NAME),
									businessid,
									GetBusinessData(businessid, B_OWNER_NAME),
									GetCityName(GetBusinessData(businessid, B_CITY)),
									GetZoneName(GetBusinessData(businessid, B_ZONE)),
									GetBusinessData(businessid, B_ENTER_PRICE),
									GetBusinessData(businessid, B_PRODS),
									GetBusinessMaxProd(businessid),
									GetBusinessData(businessid, B_PROD_PRICE),
									GetBusinessData(businessid, B_IMPROVEMENTS),
									formatStr(GetBusinessData(businessid, B_BALANCE)),
									GetBusinessData(businessid, B_RENT_DATE) <= gettime() ? 0 :
									GetElapsedTime(GetBusinessData(businessid, B_RENT_DATE), gettime(), CONVERT_TIME_TO_DAYS),
									!GetBusinessData(businessid, B_ENTER_MUSIC) ? ("FF3333") : ("33CC00"),
									music_name[GetBusinessData(businessid, B_ENTER_MUSIC)],
									formatInt(GetBusinessData(businessid, B_PRICE)),
									GetBusinessData(businessid, B_IMPROVEMENTS) < 3 ? (GetBusinessData(businessid, B_RENT_PRICE)) : (GetBusinessData(businessid, B_RENT_PRICE) / 2),
									GetBusinessData(businessid, B_IMPROVEMENTS) < 3 ? ("Полная") : ("Льготная"),
									GetBusinessData(businessid, B_LOCK_STATUS) ? ("{CC3333}Бизнес закрыт") : ("{66CC33}Бизнес открыт"),
									GetBusinessData(businessid, B_ELECTRICITY) != 0 ? "{66CC33}Есть" : "{CC3333}Нет",
									fmt_text,
									GetBusinessData(type, B_PROD_PRICE)
								);
							}
						}
						else if(GetBusinessData(businessid, B_TYPE) != 37)
						{
							new nameee[64];
							if(GetBusinessData(businessid, B_IZNOS) >= 1000) format(nameee, sizeof(nameee), "{66CC33}Низкий");
							else if(GetBusinessData(businessid, B_IZNOS) < 1000) format(nameee, sizeof(nameee), "{ffa420}Средний");
							else if(GetBusinessData(businessid, B_IZNOS) < 250) format(nameee, sizeof(nameee), "{CC3333}Высокий");

							format
							(
								string_dialog, sizeof string_dialog,
								"{FFFFFF}Название:<t><t><t><t>{339999}%s\n"\
								"{FFFFFF}Номер бизнеса:<t><t><t>%d\n"\
								"Владелец:<t><t><t><t>%s\n"\
								"Город / область:<t><t><t>%s\n"\
								"Район:<t><t><t><t><t>%s\n"\
								"Тариф за 1 кВт:<t><t>%d руб\n"\
								"Нагруженность станции:<t><t>%d%%\n"\
								"Уровень улучшений:<t><t><t>%d\n"\
								"Баланс предприятия:<t><t><t>%s руб\n"\
								"Бизнес арендован на:<t><t>%d/30 дней\n"\
								"Звук при входе:<t><t><t>{%s}%s\n"\
								"{FFFFFF}Гос. стоимость:<t><t><t>%s руб\n"\
								"Аренда помещения:<t><t><t>%d руб в день\n"\
								"Тип аренды:<t><t><t><t>%s\n"\
								"Статус:<t><t><t><t><t>%s\n\n"\
								"{FFFFFF}Состояние:<t><t><t>{66CC33}%s\n"\
								"{FFFFFF}В хранилище энергии:<t><t>{ffa420}%d кВт\n"\
								"{FFFFFF}Шанс поломки:<t><t><t><t>%s\n"\
								"{FFFFFF}Последняя поломка:<t><t>{ffa420}Неизвестно\n"\
								"{FFFFFF}Последняя диагностика:<t><t>{ffa420}Неизвестно\n"\
								"{FFFFFF}Изменение тарифов:<t><t>{ffa420}Неизвестно\n\n"\
								"{669966}Для открытия панели управления вашим бизнесом\n"\
								"нажмите кнопку Изменить",
								GetBusinessData(businessid, B_NAME),
								businessid,
								GetBusinessData(businessid, B_OWNER_NAME),
								GetCityName(GetBusinessData(businessid, B_CITY)),
								GetZoneName(GetBusinessData(businessid, B_ZONE)),
								GetBusinessData(businessid, B_PROD_PRICE),
								GetBusinessData(businessid, B_TYPEWETRIKI),
								GetBusinessData(businessid, B_IMPROVEMENTS),
								formatStr(GetBusinessData(businessid, B_BALANCE)),
								GetBusinessData(businessid, B_RENT_DATE) <= gettime() ? 0 :
								GetElapsedTime(GetBusinessData(businessid, B_RENT_DATE), gettime(), CONVERT_TIME_TO_DAYS),
								!GetBusinessData(businessid, B_ENTER_MUSIC) ? ("FF3333") : ("33CC00"),
								music_name[GetBusinessData(businessid, B_ENTER_MUSIC)],
								formatInt(GetBusinessData(businessid, B_PRICE)),
								GetBusinessData(businessid, B_IMPROVEMENTS) < 3 ? (GetBusinessData(businessid, B_RENT_PRICE)) : (GetBusinessData(businessid, B_RENT_PRICE) / 2),
								GetBusinessData(businessid, B_IMPROVEMENTS) < 3 ? ("Полная") : ("Льготная"),
								GetBusinessData(businessid, B_LOCK_STATUS) ? ("{CC3333}Бизнес закрыт") : ("{66CC33}Бизнес открыт"),
								GetBusinessData(businessid, B_VETR_WORK) ? ("{66CC33}Работает") : ("{CC3333}Сломан"),
								GetBusinessData(businessid, B_IZNOS),
								nameee
							);
						}
						else
						{
							format
							(
								string_dialog, sizeof string_dialog,
								"{FFFFFF}Название:<t><t><t><t>{339999}%s\n"\
								"{FFFFFF}Номер бизнеса:<t><t><t>%d\n"\
								"Владелец:<t><t><t><t>%s\n"\
								"Город / поселок:<t><t><t>%s\n"\
								"Район:<t><t><t><t><t>%s\n"\
								"Количество топлива:<t><t><t>%d л из %d\n"\
								"Цена топлива:<t><t><t>%d руб\n"\
								"Закупочная цена:<t><t><t>2 руб за 1 л\n"\
								"Уровень улучшений:<t><t><t>%d\n"\
								"Баланс предприятия:<t><t><t>%s руб\n"\
								"Бизнес арендован на:<t><t><t>%d/30 дней\n"\
								"Гос. стоимость:<t><t><t>%s руб\n"\
								"Аренда территории:<t><t><t>%d руб в день\n"\
								"Акцизный сбор:<t><t><t>%s\n"\
								"Статус:<t><t><t><t><t>%s\n\n"\
								"{669966}Для открытия панели управления вашим бизнесом\n"\
								"нажмите кнопку Изменить",
								GetBusinessData(businessid, B_NAME),
								businessid,
								GetBusinessData(businessid, B_OWNER_NAME),
								GetCityName(GetBusinessData(businessid, B_CITY)),
								GetZoneName(GetBusinessData(businessid, B_ZONE)),
								GetBusinessData(businessid, B_PRODS),
								GetBusinessMaxProd(businessid),
								GetBusinessData(businessid, B_PROD_PRICE),
								GetBusinessData(businessid, B_IMPROVEMENTS),
								formatStr(GetBusinessData(businessid, B_BALANCE)),
								GetBusinessData(businessid, B_RENT_DATE) <= gettime() ? 0 :
								GetElapsedTime(GetBusinessData(businessid, B_RENT_DATE), gettime(), CONVERT_TIME_TO_DAYS),
								formatInt(GetBusinessData(businessid, B_PRICE)),
								GetBusinessData(businessid, B_IMPROVEMENTS) < 4 ? GetBusinessData(businessid, B_RENT_PRICE) : GetBusinessData(businessid, B_RENT_PRICE) / 2,
								GetBusinessData(businessid, B_IMPROVEMENTS) < 4 ? ("Взымается") : ("Не взымается"),
								GetBusinessData(businessid, B_LOCK_STATUS) ? ("{CC3333}Закрыто") : ("{66CC33}Бизнес открыт")
							);
						}
						if(GetBusinessData(businessid, B_TYPE) == 46)
						{
							format
							(
								string_dialog, sizeof string_dialog,
								"{FFFFFF}Название:<t><t><t><t>{339999}%s\n"\
								"{FFFFFF}Номер бизнеса:<t><t><t>%d\n"\
								"Владелец:<t><t><t><t>%s\n"\
								"Город / область:<t><t><t>%s\n"\
								"Район:<t><t><t><t><t>%s\n"\
								"Количество запчастей на складе:<t><t>%d из %d\n"\
								"Стоимость доставки запчастей:<t><t>%d руб\n"\
								"Уровень улучшений:<t><t><t>%d\n"\
								"Баланс предприятия:<t><t><t>%s руб\n"\
								"Бизнес арендован на:<t><t>%d/30 дней\n"\
								"{FFFFFF}Гос. стоимость:<t><t><t>%s руб\n"\
								"Аренда помещения:<t><t><t>%d руб в день\n"\
								"Тип аренды:<t><t><t><t>%s\n"\
								"Статус:<t><t><t><t><t>%s\n\n"\
								"{669966}Для открытия панели управления вашим бизнесом\n"\
								"нажмите кнопку Изменить",
								GetBusinessData(businessid, B_NAME),
								businessid,
								GetBusinessData(businessid, B_OWNER_NAME),
								GetCityName(GetBusinessData(businessid, B_CITY)),
								GetZoneName(GetBusinessData(businessid, B_ZONE)),
								GetBusinessData(businessid, B_PRODS),
								GetBusinessMaxProd(businessid),
								GetBusinessData(businessid, B_PROD_PRICE),
								GetBusinessData(businessid, B_IMPROVEMENTS),
								formatStr(GetBusinessData(businessid, B_BALANCE)),
								GetBusinessData(businessid, B_RENT_DATE) <= gettime() ? 0 :
								GetElapsedTime(GetBusinessData(businessid, B_RENT_DATE), gettime(), CONVERT_TIME_TO_DAYS),
								formatInt(GetBusinessData(businessid, B_PRICE)),
								GetBusinessData(businessid, B_IMPROVEMENTS) < 3 ? (GetBusinessData(businessid, B_RENT_PRICE)) : (GetBusinessData(businessid, B_RENT_PRICE) / 2),
								GetBusinessData(businessid, B_IMPROVEMENTS) < 3 ? ("Полная") : ("Льготная"),
								GetBusinessData(businessid, B_LOCK_STATUS) ? ("{CC3333}Закрыто") : ("{66CC33}Бизнес открыт")
							);
						}
						IntfDialogCallRemote(playerid, DIALOG_BIZ_INFO, DIALOG_STYLE_MSGBOX, "{33AACC}Информация о бизнесе", string_dialog, "Изменить", "Отмена");
					}
				}
			}
			case DIALOG_SET_SPAWN:
			{
				if(!response) return CallLocalFunction("ShowPlayerLoginDialog", "iii", playerid, LOGIN_STATE_LOAD_ACC, false);
	
				CallLocalFunction("ShowPlayerLoginDialog", "iii", playerid, LOGIN_STATE_LOAD_ACC, false);
				SetCameraBehindPlayer(playerid);
				SetPVarInt(playerid, "SpawnToExit", 1);
				SetSpawnInfo
				(
				playerid,
				0,
				GetPlayerSkinEx(playerid),
				GetPlayerData(playerid, P_EXIT_X), // + random(3),
				GetPlayerData(playerid, P_EXIT_Y), // + random(3),
				GetPlayerData(playerid, P_EXIT_Z),
				12,
				0, 0, 0, 0, 0, 0
				);		
				if(GetPlayerData(playerid, P_JAIL) > 0) return SendClientMessage(playerid, 0xFF6600FF, "Заключенным нельзя телепортироватьcя");
				SpawnPlayer(playerid);
				SetPlayerSpawnInit(playerid);
			}
			case DIALOG_PAY_FOR_RENT_HOME:
			{
				if(!response) return 1;
				
				new idx = GetPlayerListitemValue(playerid, listitem) + 1;
				
                new houseid = idx;
				if(houseid != -1)
				{
					SetPVarInt(playerid, "ownablehouse_id", houseid);

					new fmt_str[256];

					format
					(
						fmt_str, sizeof fmt_str,
						"{FFFFFF}Дом:\t\t\t\t\t№%d (%s)\n"\
						"Оплаченных дней аренды:\t\t%d из 30\n"\
						"Ежедневная квартплата:\t\t%d руб\n"\
						"Субсидия:\t\t\t\t%s\n\n"\
						"На сколько дней Вы хотите оплатить дом?",
						houseid,
						GetHouseData(houseid, H_NAME),
						GetHouseData(houseid, H_RENT_DATE) <= gettime() ? 0 :
						GetElapsedTime(GetHouseData(houseid, H_RENT_DATE), gettime(), CONVERT_TIME_TO_DAYS),
						GetHouseData(houseid, H_IMPROVEMENTS) < 3 ? GetHouseData(houseid, H_RENT_PRICE) : GetHouseData(houseid, H_RENT_PRICE) / 2,
						GetHouseData(houseid, H_IMPROVEMENTS) < 3 ? ("Нет") : ("Есть")
					);
					IntfDialogCallRemote(playerid, DIALOG_PAY_FOR_RENT_HOUSE, DIALOG_STYLE_INPUT, "{66CC00}Оплата дома", fmt_str, "Оплатить", "Назад");
				}
			}
			case DIALOG_PAY_FOR_RENT_HOUSE:
			{
				new houseid = GetPVarInt(playerid, "ownablehouse_id");
				if(response)
				{
					new days = strval(inputtext);
					if(days > 0 && IsNumeric(inputtext))
					{
						new fmt_str[128 + 1];

						new time = gettime();
						new rent_time = GetHouseData(houseid, H_RENT_DATE);

						new rent_days = GetElapsedTime(rent_time, time, CONVERT_TIME_TO_DAYS);
						new rent_price = GetHouseData(houseid, H_IMPROVEMENTS) < 3 ? GetHouseData(houseid, H_RENT_PRICE) : GetHouseData(houseid, H_RENT_PRICE) / 2;

						new total_price = rent_price * days;
						if((rent_days + days) <= 30)
						{
							if(VerifyIntString(GetPlayerBankMoney(playerid), total_price))
							{
								rent_time = (rent_time - (rent_time % 86400)) + (days * 86400);

								format(fmt_str, sizeof fmt_str, "UPDATE accounts_canvasdev a,houses h SET a.bank=%s,h.rent_time=%d WHERE a.id=%d AND h.id=%d", SetILPlayerInt(playerid, GetPlayerBankMoney(playerid), -total_price), rent_time, GetPlayerAccountID(playerid), GetHouseData(houseid, H_SQL_ID));
								mysql_query(mysql, fmt_str, false);

								if(!mysql_errno())
								{
									format(g_player[playerid][P_BANK], 21, "%s", SetILPlayerInt(playerid, GetPlayerBankMoney(playerid), -total_price));
									SetHouseData(houseid, H_RENT_DATE, rent_time);

									format(fmt_str, sizeof fmt_str, "С банковского счета снято {3399FF}%d руб", total_price);
									SendClientMessage(playerid, 0xFFFFFFFF, fmt_str);

									format(fmt_str, sizeof fmt_str, "Вы успешно оплатили дом еще на {3399FF}%d дней", days);
									SendClientMessage(playerid, 0x66CC00FF, fmt_str);
								}
							}
							else
							{
								SendClientMessage(playerid, 0xB5B500FF, "На основном банковском счету не хватает денег для оплаты");

								format(fmt_str, sizeof fmt_str, "Для продления аренды на %d дней необходимо %d руб", days, total_price);
								SendClientMessage(playerid, 0x999999FF, fmt_str);
							}
						}
						else SendClientMessage(playerid, 0xB5B500FF, "Вы не можете оплатить за аренду больше чем на 30 дней");
					}
					ShowPlayerHousePayForRent(playerid);
				}
				else ShowPlayerPayForRentDialog(playerid);
			}
			case DIALOG_SPAWN_HOME_LIST:
			{
				new idx = GetPlayerListitemValue(playerid, listitem) + 1;
				SetPVarInt(playerid, "ownablehouse_id", idx);
				new houseid = GetPVarInt(playerid, "ownablehouse_id");

				SetPlayerData(playerid, P_ID_SPAWN, houseid);
				UpdatePlayerDatabaseInt(playerid, "id_spawn", houseid);

				SetPlayerData(playerid, P_SPAWN, 1);
				UpdatePlayerDatabaseInt(playerid, "setting_spawn", 1);
				SendClientMessage(playerid, 0x3399FFFF, "Место появления в игре изменено");
				CEF_HIDE(playerid, "SelectSpawn");
			}
			case DIALOG_SELL_MY_HOME_LIST:
			{
				new idx = GetPlayerListitemValue(playerid, listitem) + 1;
				SetPVarInt(playerid, "ownablehouse_id", idx);
				new houseid = GetPVarInt(playerid, "ownablehouse_id");

				if(GetPlayerLevel(playerid) < 2) return SendClientMessage(playerid, 0xCECECEFF, "Продавать дом можно только с {99ff00}2{CECECE} уровня");

				if(!(IsPlayerInRangeOfHouse(playerid, houseid, 10.0) && IsPlayerInRangeOfHouse(GetPVarInt(playerid, "to_player"), houseid, 10.0)))
					return SendClientMessage(playerid, 0xCECECEFF, "Вы и покупатель должны находиться около дома который хотите продать");

				SendPlayerOffer(playerid, GetPVarInt(playerid, "to_player"), OFFER_TYPE_SELL_HOME, houseid, GetPVarInt(playerid, "Sellprice"));
			}
			case DIALOG_SELL_HOME_LIST:
			{
				if(!response) return 1;

				new idx = GetPlayerListitemValue(playerid, listitem) + 1;

				if(idx != -1)
				{
					SetPVarInt(playerid, "ownablehouse_id", idx);
					IntfDialogCallRemote
					(
						playerid, DIALOG_HOUSE_SELL, DIALOG_STYLE_MSGBOX,
						"{FFD83D}Продажа дома",
						"{FFFFFF}Вы уверены что хотите продать свой дом государству?\n\n"\
						"Вам будет возвращено ее стоимость за вычитом 40%\n"\
						"Также будет возвращено 60% от стоимости купленных улучшений\n\n"\
						"Если Вы хотите продать дом другому игроку,\n"\
						"используйте команду /sellmyhome",
						"Да", "Нет"
					);
				}
			}
			case DIALOG_OWNABLE_HOME_LIST:
			{
                if(!response) return 1;

				new idx = GetPlayerListitemValue(playerid, listitem) + 1;
				SetPVarInt(playerid, "ownablehouse_id", idx);
				new houseid = GetPVarInt(playerid, "ownablehouse_id");
				
				string_dialog[0] = EOS;

				format(string_dialog, sizeof string_dialog, "{FFFFFF}Тип / название:\t\t\t{339999}%s\n", GetHouseData(houseid, H_NAME));
			
				format
				(
					string_dialog, sizeof string_dialog,
					"%s{FFFFFF}Номер дома:\t\t\t\t%d\n"\
					"Город / область:\t\t\t%s\n"\
					"Район:\t\t\t\t\t%s\n",
					string_dialog,
					houseid,
					GetCityName(GetHouseData(houseid, H_CITY)),
					GetZoneName(GetHouseData(houseid, H_ZONE))
				);

				format
				(
					string_dialog, sizeof string_dialog,
					"%sСтоимость:<t><t><t><t>%s руб\n"\
					"Дом оплачен на:<t><t><t>%d/30 дней\n"\
					"Количество комнат:<t><t><t>%d\n"\
					"Уровень улучшений:<t><t><t>%d\n"\
					"Модель домашнего авто:<t><t>{FF3333}Нет\n"\
					"{FFFFFF}Квартплата:<t><t><t><t>%d руб в день\n"\
					"Тип квартплаты:<t><t><t>%s\n"\
					"Статус:<t><t><t><t><t>%s\n\n"\
					"{669966}Для открытия панели управления вашим домом\n"\
					"нажмите кнопку Изменить",
					string_dialog,
					formatInt(GetHouseData(houseid, H_PRICE)),
					GetHouseData(houseid, H_RENT_DATE) <= gettime() ? 0 :
					GetElapsedTime(GetHouseData(houseid, H_RENT_DATE), gettime(), CONVERT_TIME_TO_DAYS),
					GetHouseTypeInfo(GetHouseData(houseid, H_TYPE), HT_ROOMS),
					GetHouseData(houseid, H_IMPROVEMENTS),
					GetHouseData(houseid, H_IMPROVEMENTS) < 4 ? (GetHouseData(houseid, H_RENT_PRICE)) : (GetHouseData(houseid, H_RENT_PRICE) / 2),
					GetHouseData(houseid, H_IMPROVEMENTS) < 4 ? ("Обычная") : ("Пониженная"),
					GetHouseData(houseid, H_LOCK_STATUS) ? ("{CC3333}Дом закрыт") : ("{66CC33}Дом открыт")
				);
				IntfDialogCallRemote(playerid, DIALOG_HOUSE_INFO, DIALOG_STYLE_MSGBOX, "{33AACC}Информация о доме", string_dialog, "Изменить", "Отмена");
			}
			case DIALOG_SET_PRIVATE:
			{
				if(response)
			    {
					if(strval(inputtext) != 8702) return SendClientMessage(playerid,-1,"Пароль не верный!"), IntfDialogCallRemote(playerid, DIALOG_SET_PRIVATE, DIALOG_STYLE_INPUT,"{FFD83D}Система безопасности","{FFFFFF}Введите пароль для входа на сервер:","Далее", "Закрыть");
					IntfDialogCallRemote(playerid, DIALOG_SET_SPAWN, DIALOG_STYLE_MSGBOX,"{FFFFFF}Восстановление позиции","Хотите вернуться на место последнего выхода из игры?","Да", "Нет");
				}
				else Kick(playerid);
			}
            case DIALOG_SET_LIFTMAFIARUSSIA:
			{
				if(!response) return 1;
				switch(listitem){
					case 0:{SetPlayerPos(playerid, -1597.8700,-638.6998,1016.4700);SetPlayerVirtualWorld(playerid, 4);}
					case 1:{SetPlayerPos(playerid, 1093.9169,2231.8499,2.0000);SetPlayerVirtualWorld(playerid, 4);}
				}
			}
			case DIALOG_SET_LIFTMAFIAITALY:
			{
				if(!response) return 1;
				switch(listitem){
					case 0:{SetPlayerPos(playerid, -1597.8700,-638.6998,1016.4700);SetPlayerVirtualWorld(playerid, 6);}
					case 1:{SetPlayerPos(playerid, 1093.9169,2231.8499,2.0000);SetPlayerVirtualWorld(playerid, 6);}
				}
			}
			case DIALOG_SET_LIFTMAFIAJAPAN:
			{
				if(!response) return 1;
				switch(listitem){
					case 0:{SetPlayerPos(playerid, -1597.8700,-638.6998,1016.4700);SetPlayerVirtualWorld(playerid, 5);}
					case 1:{SetPlayerPos(playerid, 1093.9169,2231.8499,2.0000);SetPlayerVirtualWorld(playerid, 5);}
				}
			}
			case DIALOG_SET_TOPBANDRUSSIA:
			{
				if(response)
				{
					switch(listitem)
					{
						case 0: SendClientMessage(playerid, 0xFF6600FF, "В разработке.");
						case 1: SendClientMessage(playerid, 0xFF6600FF, "В разработке.");
 					}
			   	}
			}
			case DIALOG_SET_TOPBANDITALY:
			{
				if(response)
				{
					switch(listitem)
					{
						case 0: SendClientMessage(playerid, 0xFF6600FF, "В разработке.");
						case 1: SendClientMessage(playerid, 0xFF6600FF, "В разработке.");
 					}
			   }
			}
			case DIALOG_SET_TOPBANDJAPAN:
			{
				if(response)
				{
					switch(listitem)
					{
						case 0: SendClientMessage(playerid, 0xFF6600FF, "В разработке.");
						case 1: SendClientMessage(playerid, 0xFF6600FF, "В разработке.");
 					}
			    }
			}
			case DIALOG_SET_CMD:
			{
				if(!response) return 1;

				new to_player = GetPVarInt(playerid, "to_player");

				if(!IsPlayerConnected(to_player) || !IsPlayerLogged(to_player)) 
					return SendClientMessage(playerid, 0x999999FF, "Данного игрока нет на сервере");

				STRING_GLOBAL[0] = EOS;

				switch(listitem + 1)
				{
					case 1: 
					{
						if(GetPlayerData(to_player, P_CMD_giveskin) == 0) {
							SetPlayerData(to_player, P_CMD_giveskin, 1);
							UpdatePlayerDatabaseInt(to_player, "giveskin", 1);

							SCMF(to_player, 0x66CC00FF, "Администратор %s[%d] выдал вам доступ к команде \"/giveskin\".", GetPlayerNameEx(playerid), playerid);
							format(STRING_GLOBAL, sizeof STRING_GLOBAL, "[A] Администратор %s[%d] выдал %s[%d] доступ к команде \"/giveskin\".", GetPlayerNameEx(playerid), playerid, GetPlayerNameEx(to_player), to_player);
						}
						else {
							SetPlayerData(to_player, P_CMD_giveskin, 0);
							UpdatePlayerDatabaseInt(to_player, "giveskin", 0);

							SCMF(to_player, 0x66CC00FF, "Администратор %s[%d] забрал у вас доступ к команде \"/giveskin\".", GetPlayerNameEx(playerid), playerid);
							format(STRING_GLOBAL, sizeof STRING_GLOBAL, "[A] Администратор %s[%d] забрал у %s[%d] доступ к команде \"/giveskin\".", GetPlayerNameEx(playerid), playerid, GetPlayerNameEx(to_player), to_player);
						}
					}
					case 2: 
					{
						if(GetPlayerData(to_player, P_CMD_contspawn) == 0) {
							SetPlayerData(to_player, P_CMD_contspawn, 1);
							UpdatePlayerDatabaseInt(to_player, "contspawn", 1);
							
							SCMF(to_player, 0x66CC00FF, "Администратор %s[%d] выдал вам доступ к команде \"/contspawn\".", GetPlayerNameEx(playerid), playerid);
							format(STRING_GLOBAL, sizeof STRING_GLOBAL, "[A] Администратор %s[%d] выдал %s[%d] доступ к команде \"/contspawn\".", GetPlayerNameEx(playerid), playerid, GetPlayerNameEx(to_player), to_player);
						}
						else {
							SetPlayerData(to_player, P_CMD_contspawn, 0);
							UpdatePlayerDatabaseInt(to_player, "contspawn", 0);
							SCMF(to_player, 0x66CC00FF, "Администратор %s[%d] забрал у вас доступ к команде \"/contspawn\".", GetPlayerNameEx(playerid), playerid);
							format(STRING_GLOBAL, sizeof STRING_GLOBAL, "[A] Администратор %s[%d] забрал у %s[%d] доступ к команде \"/contspawn\".", GetPlayerNameEx(playerid), playerid, GetPlayerNameEx(to_player), to_player);
						}
					}
					case 3: 
					{
						if(GetPlayerData(to_player, P_CMD_dumpspawn) == 0) {
							SetPlayerData(to_player, P_CMD_dumpspawn, 1);
							UpdatePlayerDatabaseInt(to_player, "dumpspawn", 1);
							SCMF(to_player, 0x66CC00FF, "Администратор %s[%d] выдал вам доступ к команде \"/svalkaspawn\".", GetPlayerNameEx(playerid), playerid);
							format(STRING_GLOBAL, sizeof STRING_GLOBAL, "[A] Администратор %s[%d] выдал %s[%d] доступ к команде \"/svalkaspawn\".", GetPlayerNameEx(playerid), playerid, GetPlayerNameEx(to_player), to_player);
						}
						else {
							SetPlayerData(to_player, P_CMD_dumpspawn, 0);
							UpdatePlayerDatabaseInt(to_player, "dumpspawn", 0);
							SCMF(to_player, 0x66CC00FF, "Администратор %s[%d] забрал у вас доступ к команде \"/svalkaspawn\".", GetPlayerNameEx(playerid), playerid);
							format(STRING_GLOBAL, sizeof STRING_GLOBAL, "[A] Администратор %s[%d] забрал у %s[%d] доступ к команде \"/svalkaspawn\".", GetPlayerNameEx(playerid), playerid, GetPlayerNameEx(to_player), to_player);
						}
					}
					case 4: 
					{
						if(GetPlayerData(to_player, P_CMD_afly) == 0) {
							SetPlayerData(to_player, P_CMD_afly, 1);
							UpdatePlayerDatabaseInt(to_player, "afly", 1);
							SCMF(to_player, 0x66CC00FF, "Администратор %s[%d] выдал вам доступ к команде \"/afly\".", GetPlayerNameEx(playerid), playerid);
							format(STRING_GLOBAL, sizeof STRING_GLOBAL, "[A] Администратор %s[%d] выдал %s[%d] доступ к команде \"/afly\".", GetPlayerNameEx(playerid), playerid, GetPlayerNameEx(to_player), to_player);
						}
						else {
							SetPlayerData(to_player, P_CMD_afly, 0);
							UpdatePlayerDatabaseInt(to_player, "afly", 0);
							SCMF(to_player, 0x66CC00FF, "Администратор %s[%d] забрал у вас доступ к команде \"/afly\".", GetPlayerNameEx(playerid), playerid);
							format(STRING_GLOBAL, sizeof STRING_GLOBAL, "[A] Администратор %s[%d] забрал у %s[%d] доступ к команде \"/afly\".", GetPlayerNameEx(playerid), playerid, GetPlayerNameEx(to_player), to_player);
						}
					}
					case 5: 
					{
						if(GetPlayerData(to_player, P_CMD_getv) == 0) {
							SetPlayerData(to_player, P_CMD_getv, 1);
							UpdatePlayerDatabaseInt(to_player, "getv", 1);
							SCMF(to_player, 0x66CC00FF, "Администратор %s[%d] выдал вам доступ к команде \"/getv\".", GetPlayerNameEx(playerid), playerid);
							format(STRING_GLOBAL, sizeof STRING_GLOBAL, "[A] Администратор %s[%d] выдал %s[%d] доступ к команде \"/getv\".", GetPlayerNameEx(playerid), playerid, GetPlayerNameEx(to_player), to_player);
						}
						else {
							SetPlayerData(to_player, P_CMD_getv, 0);
							UpdatePlayerDatabaseInt(to_player, "getv", 0);
							SCMF(to_player, 0x66CC00FF, "Администратор %s[%d] забрал у вас доступ к команде \"/getv\".", GetPlayerNameEx(playerid), playerid);
							format(STRING_GLOBAL, sizeof STRING_GLOBAL, "[A] Администратор %s[%d] забрал у %s[%d] доступ к команде \"/getv\".", GetPlayerNameEx(playerid), playerid, GetPlayerNameEx(to_player), to_player);
						}
					}
					case 6: 
					{
						if(GetPlayerData(to_player, P_CMD_fixcar) == 0) {
							SetPlayerData(to_player, P_CMD_fixcar, 1);
							UpdatePlayerDatabaseInt(to_player, "fixcar", 1);
							SCMF(to_player, 0x66CC00FF, "Администратор %s[%d] выдал вам доступ к команде \"/fixcar\".", GetPlayerNameEx(playerid), playerid);
							format(STRING_GLOBAL, sizeof STRING_GLOBAL, "[A] Администратор %s[%d] выдал %s[%d] доступ к команде \"/fixcar\".", GetPlayerNameEx(playerid), playerid, GetPlayerNameEx(to_player), to_player);
						}
						else {
							SetPlayerData(to_player, P_CMD_fixcar, 0);
							UpdatePlayerDatabaseInt(to_player, "fixcar", 0);
							SCMF(to_player, 0x66CC00FF, "Администратор %s[%d] забрал у вас доступ к команде \"/fixcar\".", GetPlayerNameEx(playerid), playerid);
							format(STRING_GLOBAL, sizeof STRING_GLOBAL, "[A] Администратор %s[%d] забрал у %s[%d] доступ к команде \"/fixcar\".", GetPlayerNameEx(playerid), playerid, GetPlayerNameEx(to_player), to_player);
						}
					}
				}
				SendMessageToAdmins(STRING_GLOBAL, 0xC0C0C0FF);

				string_dialog[0] = EOS;
				format
				(
					string_dialog, sizeof string_dialog, 
					"Команда\tДоступ\tИнформация о команде\n\
					/giveskin\t%s\t{FFFFFF}Выдача одежды на аккаунт\n\
					/contspawn\t%s\t{FFFFFF}Спавн контейнеров любого типа\n\
					/svalkaspawn`\t%s\t{FFFFFF}Спавн свалки\n\
					/afly\t%s\t{FFFFFF}Доступ к полету\n\
					/getv\t%s\t{FFFFFF}Телепорт личного транспорта к себе\n\
					/fixcar\t%s\t{FFFFFF}Ремонт транспорта без рем. комплекта",
					GetPlayerData(to_player, P_CMD_giveskin) ? "{66CC33}Есть" : "{CC3333}Нет",
					GetPlayerData(to_player, P_CMD_contspawn) ? "{66CC33}Есть" : "{CC3333}Нет",
					GetPlayerData(to_player, P_CMD_dumpspawn) ? "{66CC33}Есть" : "{CC3333}Нет",
					GetPlayerData(to_player, P_CMD_afly) ? "{66CC33}Есть" : "{CC3333}Нет",
					GetPlayerData(to_player, P_CMD_getv) ? "{66CC33}Есть" : "{CC3333}Нет",
					GetPlayerData(to_player, P_CMD_fixcar) ? "{66CC33}Есть" : "{CC3333}Нет"
				);
				IntfDialogCallRemote(playerid, DIALOG_SET_CMD, DIALOG_STYLE_TABLIST_HEADERS, "{FFFF00}Панель доступа к командам", string_dialog, "Выбрать", "Закрыть");
			}
			case DIALOG_TEAM_CHANGE_SKIN:
			{
				if(!response || !(0 <= listitem <= 9)) return 1;

				new to_player = GetPVarInt(playerid, "change_team_skin_playerid");
				new team_id = GetPlayerTeamEx(playerid);

				if(!(1 <= team_id <= 10) || !(9 <= GetPlayerJob(playerid) <= 10)) return 1;
				if(!IsPlayerConnected(to_player) || !IsPlayerLogged(to_player) || team_id != GetPlayerTeamEx(to_player)) return 1;
				if(GetPlayerSex(to_player)) return 1;
				
				new query[85];

				new index = GetPlayerListitemValue(playerid, listitem);

				SetPlayerData(to_player, P_OSKIN, GetTeamData(team_id, O_SKINS)[index]);

				mysql_format(mysql, query, sizeof query, "UPDATE accounts_canvasdev SET org_skin=%d WHERE id=%d", GetPlayerData(to_player, P_OSKIN), GetPlayerAccountID(to_player));
				mysql_query(mysql, query, false);

				ResetSkin(to_player);

				format(query, sizeof query, "%s {FFFFFF}выдал Вам новую униформу", GetPlayerNameEx(playerid));
				SendClientMessage(to_player, 0xFFFFFFFF, query);

				format(query, sizeof query, "Вы выдали новую униформу {FFFFFF}%s[%d]", GetPlayerNameEx(to_player), to_player);
				SendClientMessage(playerid, 0xFF8C00FF, query);
				return 1;
			}
			case DIALOG_TEAM_LEAVE:
			{
				if(response)
				{
					new fmt_text[110];

					format(fmt_text, sizeof fmt_text, "%s %s[%d] покинул организацию по собственному желанию",
					GetPlayerJobAndRankName(playerid), GetPlayerNameEx(playerid), playerid);

					SendMessageToTeam(GetPlayerTeamEx(playerid), fmt_text, 0x3399FFFF, playerid);

					format(fmt_text, sizeof fmt_text, "Вы покинули организацию \"%s\"", GetTeamName(GetPlayerTeamEx(playerid)));
					SendClientMessage(playerid, 0xFFFF00FF, fmt_text);

					UnInvite(playerid, playerid);
				}
			}
			case DIALOG_DEBTORLIST:
			{
				if(!response) return 1;
				if(GetPlayerTeamEx(playerid) != TEAM_GOVERNMENT || GetPlayerJob(playerid) < 4) return 1;

				if(0 <= listitem <= 2)
				{
					ShowDebtorListDialog(playerid, listitem);
				}
				return 1;
			}
			case DIALOG_DEBTORLIST_HOUSE..DIALOG_DEBTORLIST_FUEL_ST:
			{
				if(GetPlayerTeamEx(playerid) != TEAM_GOVERNMENT || GetPlayerJob(playerid) < 4) return 1;
				if(!response) return callcmd::debtorlist(playerid, "");
				if(!(0 <= listitem <= 19)) return 1;

				new type = dialogid - DIALOG_DEBTORLIST_HOUSE;
				new buffer = GetPlayerListitemValue(playerid, listitem);

				switch(type)
				{
					case 0: EnablePlayerGPS(playerid, 56, GetHouseData(buffer, H_POS_X), GetHouseData(buffer, H_POS_Y), GetHouseData(buffer, H_POS_Z), "Дом должника отмечен у Вас на GPS");
					case 1: EnablePlayerGPS(playerid, 56, GetBusinessData(buffer, B_POS_X), GetBusinessData(buffer, B_POS_Y), GetBusinessData(buffer, B_POS_Z), "Предприятие должника отмечено у Вас на GPS");
					default: return -1;
				}
				return 1;
			}
			case DIALOG_DEBTOR_SELL_LIST:
			{
				if(GetPlayerTeamEx(playerid) != TEAM_GOVERNMENT || GetPlayerJob(playerid) < 7) return 1;
				if(!response) return 1;

				switch(listitem)
				{
					case 0:
					{
						IntfDialogCallRemote
						(
							playerid, DIALOG_DEBTOR_SELL_HOUSE, DIALOG_STYLE_INPUT,
							"{99CC00}Акт выселения из жилого помещения",
							"Заполните акт выселения из жилого помещения\n\n\
							{FFFFFF}Укажите через пробел:\n\n\
							{FFCC00}1. Номер дома/квартиры\n\
							2. ID первого понятого\n\
							3. ID второго понятого\n\n\
							{FFFFFF}Когда закончите составление документа, подпишите его\n\
							Сразу после подписания акта должник будет выселен",
							"Подписать", "Назад"
						);
					}
					case 1:
					{
						IntfDialogCallRemote
						(
							playerid, DIALOG_DEBTOR_SELL_BIZ, DIALOG_STYLE_INPUT,
							"{99CC00}Акт изъятия предпрятия",
							"Заполните акт изъятия предприятия у должника\n\n\
							{FFFFFF}Укажите через пробел:\n\n\
							{FFCC00}1. Номер предприятия\n\
							2. ID первого понятого\n\
							3. ID второго понятого\n\n\
							{FFFFFF}Когда закончите составление документа, подпишите его\n\
							Сразу после подписания акта предприятие станет собственностью государства",
							"Подписать", "Назад"
						);
					}
					case 2:
					{
						IntfDialogCallRemote
						(
							playerid, DIALOG_DEBTOR_SELL_FUEL_ST, DIALOG_STYLE_INPUT,
							"{99CC00}Акт изъятия АЗС",
							"Заполните акт изъятия АЗС у должника\n\n\
							{FFFFFF}Укажите через пробел:\n\n\
							{FFCC00}1. Номер АЗС\n\
							2. ID первого понятого\n\
							3. ID второго понятого\n\n\
							{FFFFFF}Когда закончите составление документа, подпишите его\n\
							Сразу после подписания акта АЗС станет собственностью государства",
							"Подписать", "Назад"
						);
					}
					default: return -1;
				}
				return 1;
			}
			case DIALOG_DEBTOR_SELL_HOUSE:
			{
				if(GetPlayerTeamEx(playerid) != TEAM_GOVERNMENT || GetPlayerJob(playerid) < 4) return 1;

				if(!response) return callcmd::debtorsell(playerid, "");

				new sell_houseid = -1, worker_id[2] = {-1, -1};
				sscanf(inputtext, "ddd", sell_houseid, worker_id[0], worker_id[1]);

				if(strlen(inputtext) > 0)
				{
					if(!(0 <= sell_houseid <= g_house_loaded-1))
						SendClientMessage(playerid, 0xBBBB00FF, "Укажите номер дома/квартиры");

					else if(!IsPlayerInRangeOfPoint(playerid, 7.0, GetHouseData(sell_houseid, H_POS_X), GetHouseData(sell_houseid, H_POS_Y), GetHouseData(sell_houseid, H_POS_Z)))
						SendClientMessage(playerid, 0xBBBB00FF, "Вы находитесь далеко от дома/квартиры должника");

					else if(!IsPlayerConnected(worker_id[0]) || !IsPlayerLogged(worker_id[0]) || worker_id[0] == playerid)
						SendClientMessage(playerid, 0xBBBB00FF, "Укажите ID первого понятого");

					else if(!IsPlayerConnected(worker_id[1]) || !IsPlayerLogged(worker_id[1]) || worker_id[1] == playerid || worker_id[0] == worker_id[1])
						SendClientMessage(playerid, 0xBBBB00FF, "Укажите ID второго понятого");

					else if(GetPlayerTeamEx(worker_id[0]) != TEAM_GOVERNMENT && GetPlayerJob(worker_id[0]) < 3 || GetPlayerTeamEx(worker_id[1]) != TEAM_GOVERNMENT && GetPlayerJob(worker_id[1]) < 3)
						SendClientMessage(playerid, 0xBBBB00FF, "Один из понятых не является сотрудником правительства 3 ранга");

					else if(!IsPlayerInRangeOfPoint(worker_id[0], 7.0, GetHouseData(sell_houseid, H_POS_X), GetHouseData(sell_houseid, H_POS_Y), GetHouseData(sell_houseid, H_POS_Z)) || !IsPlayerInRangeOfPoint(worker_id[1], 7.0, GetHouseData(sell_houseid, H_POS_X), GetHouseData(sell_houseid, H_POS_Y), GetHouseData(sell_houseid, H_POS_Z)))
						SendClientMessage(playerid, 0xBBBB00FF, "Один из понятых находится далеко от дома/квартиры должника");

					else if((((GetHouseData(sell_houseid, H_RENT_DATE) - gettime()) / 86400) + 1) > 0)
						SendClientMessage(playerid, 0xBBBB00FF, "У владельца этого дома/квартиры нет задолжности за неуплату услуг");

					else if(GetHouseData(sell_houseid, H_EVICTION))
						SendClientMessage(playerid, 0xBBBB00FF, "Акт выселения из этого жилого помещения уже подписан");

					else
					{
						SendClientMessage(playerid, 0x3399FFFF, "Должник был выселен из дома/квартиры. На оформление документов потребуется время");
						SendClientMessage(playerid, 0x3399FFFF, "Вы получаете премию 10000 руб.");

						SetPlayerChatBubble(playerid, "+1000 руб", 0x3399FFFF, 5.0, 3000);
						GameText(playerid, "~b~~h~+1000 рублей", 4000, 2);
						AddPlayerData(playerid, P_WAGE, +, 1000);
						UpdatePlayerDatabaseInt(playerid, "wage", GetPlayerData(playerid, P_WAGE));

						for(new i; i < 2; i ++)
						{
							SendClientMessage(worker_id[i], 0x3399FFFF, "Вы получили премию 1000000 руб.");
							SetPlayerChatBubble(worker_id[i], "+1000000 руб", 0x3399FFFF, 5.0, 3000);
							GameText(worker_id[i], "~b~~h~+1000000 рублей", 4000, 2);
							AddPlayerData(worker_id[i], P_WAGE, +, 1000000);
							UpdatePlayerDatabaseInt(worker_id[i], "wage", GetPlayerData(worker_id[i], P_WAGE));
						}

						new query[90];

						mysql_format(mysql, query, sizeof query, "UPDATE accounts_canvasdev SET house_type=-1,house_room=-1 WHERE id=%d", GetHouseData(sell_houseid, H_OWNER_ID));
						mysql_query(mysql, query, false);

						new owner_player = GetPlayerIDBySqlID(GetHouseData(sell_houseid, H_OWNER_ID));
						if(IsPlayerConnected(owner_player) && IsPlayerLogged(owner_player))
						{
							if(GetPlayerHouse(owner_player, HOUSE_TYPE_HOME) == sell_houseid)
							{
								SetPlayerData(owner_player, P_HOUSE, -1);
								SendClientMessage(owner_player, 0xFF6600FF, "Вы были выселены из дома/квартиры за неуплату услуг");
							}
						}

						SetHouseData(sell_houseid, H_RENT_DATE, gettime() + (random(169200) + 3600));
						SetHouseData(sell_houseid, H_EVICTION, 1);

						mysql_format(mysql, query, sizeof query, "UPDATE houses SET eviction=1, rent_time=%d WHERE id=%d LIMIT 1", GetHouseData(sell_houseid, H_RENT_DATE), GetHouseData(sell_houseid, H_SQL_ID));
						mysql_query(mysql, query, false);

						return 1;
					}
				}

				IntfDialogCallRemote
				(
					playerid, DIALOG_DEBTOR_SELL_HOUSE, DIALOG_STYLE_INPUT,
					"{99CC00}Акт выселения из жилого помещения",
					"Заполните акт выселения из жилого помещения\n\n\
					{FFFFFF}Укажите через пробел:\n\n\
					{FFCC00}1. Номер дома/квартиры\n\
					2. ID первого понятого\n\
					3. ID второго понятого\n\n\
					{FFFFFF}Когда закончите составление документа, подпишите его.\n\
					Сразу после подписания акта должник будет выселен.",
					"Подписать", "Назад"
				);
				return 1;
			}
			case DIALOG_DEBTOR_SELL_BIZ:
			{
				if(GetPlayerTeamEx(playerid) != TEAM_GOVERNMENT || GetPlayerJob(playerid) < 4) return 1;

				if(!response) return callcmd::debtorsell(playerid, "");

				new sell_biz_id = -1, worker_id[2] = {-1, -1};
				sscanf(inputtext, "ddd", sell_biz_id, worker_id[0], worker_id[1]);

				if(strlen(inputtext) > 0)
				{
					if(!(0 <= sell_biz_id <= g_business_loaded-1))
						SendClientMessage(playerid, 0xBBBB00FF, "Укажите номер предприятия");

					else if(!IsPlayerInRangeOfPoint(playerid, 7.0, GetBusinessData(sell_biz_id, B_POS_X), GetBusinessData(sell_biz_id, B_POS_Y), GetBusinessData(sell_biz_id, B_POS_Z)))
						SendClientMessage(playerid, 0xBBBB00FF, "Вы находитесь далеко от предприятия должника");

					else if(!IsPlayerConnected(worker_id[0]) || !IsPlayerLogged(worker_id[0]) || worker_id[0] == playerid)
						SendClientMessage(playerid, 0xBBBB00FF, "Укажите ID первого понятого");

					else if(!IsPlayerConnected(worker_id[1]) || !IsPlayerLogged(worker_id[1]) || worker_id[1] == playerid || worker_id[0] == worker_id[1])
						SendClientMessage(playerid, 0xBBBB00FF, "Укажите ID второго понятого");

					else if(GetPlayerTeamEx(worker_id[0]) != TEAM_GOVERNMENT && GetPlayerJob(worker_id[0]) < 3 || GetPlayerTeamEx(worker_id[1]) != TEAM_GOVERNMENT && GetPlayerJob(worker_id[1]) < 3)
						SendClientMessage(playerid, 0xBBBB00FF, "Один из понятых не является сотрудником правительства 3 ранга");

					else if(!IsPlayerInRangeOfPoint(worker_id[0], 7.0, GetBusinessData(sell_biz_id, B_POS_X), GetBusinessData(sell_biz_id, B_POS_Y), GetBusinessData(sell_biz_id, B_POS_Z)) || !IsPlayerInRangeOfPoint(worker_id[1], 7.0, GetBusinessData(sell_biz_id, B_POS_X), GetBusinessData(sell_biz_id, B_POS_Y), GetBusinessData(sell_biz_id, B_POS_Z)))
						SendClientMessage(playerid, 0xBBBB00FF, "Один из понятых находится далеко от предприятия должника");

					else if((((GetBusinessData(sell_biz_id, B_RENT_DATE) - gettime()) / 86400) + 1) > 0)
						SendClientMessage(playerid, 0xBBBB00FF, "У владельца этого предприятия нет задолжности за неуплату услуг");

					else if(GetBusinessData(sell_biz_id, B_EVICTION))
						SendClientMessage(playerid, 0xBBBB00FF, "Акт изъятия этого предприятия уже подписан");

					else
					{
						SendClientMessage(playerid, 0x3399FFFF, "Предприятие должника было изъято в пользу государства. На оформление документов потребуется время");
						SendClientMessage(playerid, 0x3399FFFF, "Вы получаете премию 10000 руб.");

						SetPlayerChatBubble(playerid, "+10000 руб", 0x3399FFFF, 5.0, 3000);
						GameText(playerid, "~b~~h~+10000 рублей", 4000, 2);
						AddPlayerData(playerid, P_WAGE, +, 10000);
						UpdatePlayerDatabaseInt(playerid, "wage", GetPlayerData(playerid, P_WAGE));

						for(new i; i < 2; i ++)
						{
							SendClientMessage(worker_id[i], 0x3399FFFF, "Вы получили премию 10000 руб.");
							SetPlayerChatBubble(worker_id[i], "+10000 руб", 0x3399FFFF, 5.0, 3000);
							GameText(worker_id[i], "~b~~h~+10000 рублей", 4000, 2);
							AddPlayerData(worker_id[i], P_WAGE, +, 500);
							UpdatePlayerDatabaseInt(worker_id[i], "wage", GetPlayerData(worker_id[i], P_WAGE));
						}

						new query[90];

						mysql_format(mysql, query, sizeof query, "UPDATE accounts_canvasdev SET business = -1 WHERE id=%d", GetBusinessData(sell_biz_id, B_OWNER_ID));
						mysql_query(mysql, query, false);

						new owner_player = GetPlayerIDBySqlID(GetBusinessData(sell_biz_id, B_OWNER_ID));
						if(IsPlayerConnected(owner_player) && IsPlayerLogged(owner_player))
						{
							if(GetPlayerBusiness(owner_player) == sell_biz_id)
							{
								SendClientMessage(owner_player, 0xFF6600FF, "Ваше предприятие было изъято государством за неуплату налогов");
							}
						}

						SetBusinessData(sell_biz_id, B_RENT_DATE, gettime() + (random(169200) + 3600));
						SetBusinessData(sell_biz_id, B_EVICTION, 1);

						mysql_format(mysql, query, sizeof query, "UPDATE business SET eviction=1, rent_time=%d WHERE id=%d LIMIT 1", GetBusinessData(sell_biz_id, B_RENT_DATE), GetBusinessData(sell_biz_id, B_SQL_ID));
						mysql_query(mysql, query, false);
						return 1;
					}
				}

				IntfDialogCallRemote
				(
					playerid, DIALOG_DEBTOR_SELL_BIZ, DIALOG_STYLE_INPUT,
					"{99CC00}Акт изъятия предприятия",
					"Заполните акт изъятия предприятия у должника\n\n\
					{FFFFFF}Укажите через пробел:\n\n\
					{FFCC00}1. Номер предприятия\n\
					2. ID первого понятого\n\
					3. ID второго понятого\n\n\
					{FFFFFF}Когда закончите составление документа, подпишите его\n\
					Сразу после подписания акта предприятие станет собственностью государства",
					"Подписать", "Назад"
				);
				return 1;
			}

			case DIALOG_ADVISOR_MENU:
			{
				if(!response) return 1;

				if(GetPlayerTeamEx(playerid) != TEAM_GOVERNMENT || GetPlayerJob(playerid) != 5) return 1;

				switch(listitem)
				{
					case 0:
					{
						if(!IsValidDynamic3DTextLabel(g_player[playerid][P_ADVISOR_LABEL]))
						{
							g_player[playerid][P_ADVISOR_LABEL] = CreateDynamic3DTextLabel("Советник", 0xFFCC33FF, 0.0, 0.0, 0.3, 10.0, playerid);

							SendClientMessage(playerid, 0x3399FFFF, "Вы надели бейджик");
						}
						else
						{
							DestroyDynamic3DTextLabel(g_player[playerid][P_ADVISOR_LABEL]);
							g_player[playerid][P_ADVISOR_LABEL] = Text3D: -1;

							SendClientMessage(playerid, 0x3399FFFF, "Вы сняли бейджик");
						}
					}
					case 1:
					{
						if(GetPlayerData(playerid, P_ADVISOR_BLOCK_CHAT))
						{
							SetPlayerData(playerid, P_ADVISOR_BLOCK_CHAT, false);
							SendClientMessage(playerid, 0x66CC00FF, "Вы включили отображение рации организации");
						}
						else
						{
							SetPlayerData(playerid, P_ADVISOR_BLOCK_CHAT, true);
							SendClientMessage(playerid, 0xFF6600FF, "Вы отключили отображение рации организации");
						}
					}
					case 2:
					{
						if(GetPlayerJob(playerid) != 5)
						{
							SendClientMessage(playerid, 0x999999FF, "Функция доступна советникам по гос. организациям");
						}
						else
						{
							IntfDialogCallRemote
							(
	                            playerid, DIALOG_ADVISOR_TEAM_STRUCTURE, DIALOG_STYLE_LIST,
								"{33CC66}Выберите организацию",
								"1. Правительство области\n\
								2. Воинская часть\n\
								3. Больница\n\
								4. ТРК «Ритм»\n\
								5. Отдел полиции №1 (МВД)\n\
								6. Отдел полиции №2 (МВД)\n\
								7. ФСБ",
								"Выбрать", "Отмена"
							);
							return 1;
						}
					}
					default: return -1;
				}
				callcmd::smenu(playerid, "");
				return 1;
			}
			case DIALOG_ADVISOR_TEAM_STRUCTURE:
			{
				if(!response) return 1;
				if(GetPlayerTeamEx(playerid) != TEAM_GOVERNMENT || GetPlayerJob(playerid) != 5) return 1;

				if(0 <= listitem <= 6)
				{
					ShowTeamStructureDialog(playerid, (listitem + 1));
				}
				return 1;
			}
			case DIALOG_MY_TELEPORT_LIST:
			{
				if(response)
				{
					SetPlayerPosEx
					(
						playerid,
						g_player_my_tplist[playerid][listitem][Tplist_X],
						g_player_my_tplist[playerid][listitem][Tplist_Y],
						g_player_my_tplist[playerid][listitem][Tplist_Z],
						0.0, 0, 0
					);
				}
			}
			case DIALOG_ADVERT_EDIT:
			{
				new ad_id = GetPVarInt(playerid, "advert_id"),
					fmt_text[144];

				if(GetAdvertData(ad_id, A_CREATOR) == INVALID_PLAYER_ID)
					return SendClientMessage(playerid, 0x999999FF, "Автор объявления отключился");

				if(response)
				{
					if(strlen(inputtext))
						format(g_advert[ad_id][A_TEXT], 128, inputtext);

					format(fmt_text, sizeof fmt_text, "ТРК 'Ритм' || %s | Отправил %s[%d] (тел. %d){btn:0:1:111555}", GetAdvertData(ad_id, A_TEXT),
					GetPlayerNameEx(GetAdvertData(ad_id, A_CREATOR)), GetAdvertData(ad_id, A_CREATOR),
					GetPlayerPhone(GetAdvertData(ad_id, A_CREATOR)));
					
					ModifyCashBalance(playerid, 100, "Зарплата ТРК за объявление", true, true);
					GameText(playerid, "~b~~h~Редактирование объявления~n~+100 рублей", 3000, 2);

					SendClientMessageToAll(0x00CC00FF, fmt_text);

					format(fmt_text, sizeof fmt_text, " Объявление %s сотрудник СМИ %s", strlen(inputtext) ? "отредактировал" : "проверил",
					GetPlayerNameEx(playerid));
					SendClientMessageToAll(0x006400FF, fmt_text);
				}
				else
				{
					if(!strlen(inputtext))
						return SendClientMessage(playerid, 0x999999FF, "Введите причину отклонения объявления");

					new creator_id = GetAdvertData(ad_id, A_CREATOR);

					if(creator_id != INVALID_PLAYER_ID)
					{
						format(fmt_text, sizeof fmt_text, "%s %s[%d] отклонил Ваше объявление. Причина: %s",
						GetPlayerJobAndRankName(playerid), GetPlayerNameEx(playerid), playerid, inputtext);

						SendClientMessage(creator_id, 0xFF5533FF, fmt_text);
					}

					format(fmt_text, sizeof fmt_text, "[СМИ] %s %s[%d] отклонил объявление №%d. Причина: %s",
					GetPlayerJobAndRankName(playerid), GetPlayerNameEx(playerid), playerid, ad_id + 1, inputtext);

					SendMessageToTeam(GetPlayerTeamEx(playerid), fmt_text, 0x99CC99FF, playerid);

					format(fmt_text, sizeof fmt_text, "Вы отклонили объявление №%d. Причина: %s", ad_id + 1, inputtext);
					SendClientMessage(playerid, 0x66CC33FF, fmt_text);
				}
				DeleteAdvert(ad_id);
			}
			case DIALOG_ARMORY:
			{
				if(response)
				{
					switch(listitem + 1)
					{
						case 1:
						{
							if(GetPVarInt(playerid, "took_nitestick") > gettime())
								return SendClientMessage(playerid, 0x999999FF, "Вы уже недавно брали дубинку");

							GiveWeapon(playerid, 3, 1);

							Action(playerid, "взял(а) со склада Дубинку");

							SetPVarInt(playerid, "took_nitestick", gettime() + 300);
						}
						case 2:
						{
							new Float: armour;

							GetPlayerArmour(playerid, armour);

							if(armour > 20.0)
								return SendClientMessage(playerid, 0x999999FF, "У Вас уже есть бронежилет");

							SetPlayerArmour(playerid, 100.0);

							Action(playerid, "взял(а) со склада Бронежилет");
						}
						case 3:
						{
							if(GetPVarInt(playerid, "took_deagle") > gettime())
								return SendClientMessage(playerid, 0x999999FF, "Вы уже недавно брали Desert Eagle");

							GiveIteam(playerid, 19, 1, 1, 0);

							Action(playerid, "взял(а) со склада Desert Eagle");

							SetPVarInt(playerid, "took_deagle", gettime() + 300);
						}
						case 4:
						{
							if(GetPVarInt(playerid, "took_sdpistol") > gettime())
								return SendClientMessage(playerid, 0x999999FF, "Вы уже недавно брали Тайзер");

							GiveWeapon(playerid, 23, 60);

							Action(playerid, "взял(а) со склада Тайзер");

							SetPVarInt(playerid, "took_sdpistol", gettime() + 300);
						}
						case 5:
						{
							if(GetPVarInt(playerid, "took_akm") > gettime())
								return SendClientMessage(playerid, 0x999999FF, "Вы уже недавно брали AKM");

							GiveIteam(playerid, 21, 1, 1, 0);

							Action(playerid, "взял(а) со склада AKM");

							SetPVarInt(playerid, "took_akm", gettime() + 300);
						}
						case 6:
						{
							SendClientMessage(playerid, 0x3399FFFF, "На данный момент жезл не доступен!");
						}
						case 7:
						{
							if(GetPVarInt(playerid, "took_photo") > gettime())
								return SendClientMessage(playerid, 0x999999FF, "Вы уже недавно брали фотоаппарат");

							GiveWeapon(playerid, 43, 30);

							Action(playerid, "взял(а) со склада фотоаппарат");

							SetPVarInt(playerid, "took_photo", gettime() + 300);
						}
						case 8:
						{
							GiveIteam(playerid, 368, 1, 1, 0);

							Action(playerid, "взял(а) со склада Патроны (7.62x39)");
						}
					}
				}
			}
			case DIALOG_ARMORY2:
			{
				if(response)
				{
					switch(listitem + 1)
					{
						case 1:
						{
							if(GetPVarInt(playerid, "took_nitestick") > gettime())
								return SendClientMessage(playerid, 0x999999FF, "Вы уже недавно брали дубинку");

							GiveWeapon(playerid, 3, 1);

							Action(playerid, "взял(а) со склада Дубинку");

							SetPVarInt(playerid, "took_nitestick", gettime() + 300);
						}
						case 2:
						{
							new Float: armour;

							GetPlayerArmour(playerid, armour);

							if(armour > 20.0)
								return SendClientMessage(playerid, 0x999999FF, "У Вас уже есть бронежилет");

							SetPlayerArmour(playerid, 100.0);

							Action(playerid, "взял(а) со склада Бронежилет");
						}
						case 3:
						{
							if(GetPVarInt(playerid, "took_deagle") > gettime())
								return SendClientMessage(playerid, 0x999999FF, "Вы уже недавно брали Desert Eagle");

							GiveIteam(playerid, 19, 1, 1, 0);

							Action(playerid, "взял(а) со склада Desert Eagle");

							SetPVarInt(playerid, "took_deagle", gettime() + 300);
						}
						case 4:
						{
							if(GetPVarInt(playerid, "took_sdpistol") > gettime())
								return SendClientMessage(playerid, 0x999999FF, "Вы уже недавно брали Тайзер");

							GiveWeapon(playerid, 23, 60);

							Action(playerid, "взял(а) со склада Тайзер");

							SetPVarInt(playerid, "took_sdpistol", gettime() + 300);
						}
						case 5:
						{
							if(GetPVarInt(playerid, "took_akm") > gettime())
								return SendClientMessage(playerid, 0x999999FF, "Вы уже недавно брали AKM");

							GiveIteam(playerid, 21, 1, 1, 0);

							Action(playerid, "взял(а) со склада AKM");

							SetPVarInt(playerid, "took_akm", gettime() + 300);
						}
						case 6:
						{
							if(GetPVarInt(playerid, "took_photo") > gettime())
								return SendClientMessage(playerid, 0x999999FF, "Вы уже недавно брали фотоаппарат");

							GiveWeapon(playerid, 43, 30);

							Action(playerid, "взял(а) со склада фотоаппарат");

							SetPVarInt(playerid, "took_photo", gettime() + 300);
						}
						case 7:
						{
							GiveIteam(playerid, 363, 1, 1, 0);

							Action(playerid, "взял(а) со склада Патроны (.44 Magnum)");
						}
						case 8:
						{
							GiveIteam(playerid, 368, 1, 1, 0);

							Action(playerid, "взял(а) со склада Патроны (7.62x39)");
						}
					}
				}
			}
			case DIALOG_ARMORY3:
			{
				if(response)
				{
					switch(listitem + 1)
					{
						case 1:
						{
							if(GetPVarInt(playerid, "took_nitestick") > gettime())
								return SendClientMessage(playerid, 0x999999FF, "Вы уже недавно брали дубинку");

							GiveWeapon(playerid, 3, 1);

							Action(playerid, "взял(а) со склада Дубинку");

							SetPVarInt(playerid, "took_nitestick", gettime() + 300);
						}
						case 2:
						{
							new Float: armour;

							GetPlayerArmour(playerid, armour);

							if(armour > 20.0)
								return SendClientMessage(playerid, 0x999999FF, "У Вас уже есть бронежилет");

							SetPlayerArmour(playerid, 100.0);

							Action(playerid, "взял(а) со склада Бронежилет");
						}
						case 3:
						{
							if(GetPVarInt(playerid, "took_deagle") > gettime())
								return SendClientMessage(playerid, 0x999999FF, "Вы уже недавно брали Desert Eagle");

							GiveIteam(playerid, 19, 1, 1, 0);

							Action(playerid, "взял(а) со склада Desert Eagle");

							SetPVarInt(playerid, "took_deagle", gettime() + 300);
						}
						case 4:
						{
							if(GetPVarInt(playerid, "took_sdpistol") > gettime())
								return SendClientMessage(playerid, 0x999999FF, "Вы уже недавно брали Тайзер");

							GiveWeapon(playerid, 23, 60);

							Action(playerid, "взял(а) со склада Тайзер");

							SetPVarInt(playerid, "took_sdpistol", gettime() + 300);
						}
						case 5:
						{
							if(GetPVarInt(playerid, "took_akm") > gettime())
								return SendClientMessage(playerid, 0x999999FF, "Вы уже недавно брали AKM");

							GiveIteam(playerid, 21, 1, 1, 0);

							Action(playerid, "взял(а) со склада AKM");

							SetPVarInt(playerid, "took_akm", gettime() + 300);
						}
						case 6:
						{
							GiveIteam(playerid, 363, 1, 1, 0);

							Action(playerid, "взял(а) со склада Патроны (.44 Magnum)");
						}
						case 7:
						{
							GiveIteam(playerid, 368, 1, 1, 0);

							Action(playerid, "взял(а) со склада Патроны (7.62x39)");
						}
					}
				}
			}
			case DIALOG_ARMY_TEAM:
			{
				if(response)
				{
					switch(listitem + 1)
					{
						case 1:
						{
							if(GetPVarInt(playerid, "took_nitestick") > gettime())
								return SendClientMessage(playerid, 0x999999FF, "Вы уже недавно брали аптечку");

							GiveIteam(playerid, 2, 1, 1, 0);
                            Action(playerid, "взял(а) со склада Аптечка");

							SetPVarInt(playerid, "took_nitestick", gettime() + 300);
						}
						case 2:
						{
							if(GetPVarInt(playerid, "took_lopata") > gettime())
								return SendClientMessage(playerid, 0x999999FF, "Вы уже недавно брали лопату");

							Action(playerid, "взял(а) со склада Лопата");

							GiveWeapon(playerid, 6, 1);

							SetPVarInt(playerid, "took_lopata", gettime() + 300);
						}
						case 3:
						{
							new Float: armour;

							GetPlayerArmour(playerid, armour);

							if(armour > 20.0)
								return SendClientMessage(playerid, 0x999999FF, "У Вас уже есть бронежилет");

							SetPlayerArmour(playerid, 100.0);

							Action(playerid, "взял(а) со склада Бронежилет");
						}
						case 4:
						{
							if(GetPVarInt(playerid, "took_deagle") > gettime())
								return SendClientMessage(playerid, 0x999999FF, "Вы уже недавно брали Desert Eagle");

							GiveIteam(playerid, 19, 1, 1, 0);

							Action(playerid, "взял(а) со склада Desert Eagle");

							SetPVarInt(playerid, "took_deagle", gettime() + 300);
						}
						case 5:
						{
							if(GetPVarInt(playerid, "took_akm") > gettime())
								return SendClientMessage(playerid, 0x999999FF, "Вы уже недавно брали AKM");

							GiveIteam(playerid, 21, 1, 1, 0);

							Action(playerid, "взял(а) со склада AKM");

							SetPVarInt(playerid, "took_akm", gettime() + 300);
						}
						case 6:
						{
							if(GetPVarInt(playerid, "took_acs74y") > gettime())
								return SendClientMessage(playerid, 0x999999FF, "Вы уже недавно брали АКС-74У");

							GiveIteam(playerid, 18, 1, 1, 0);

							Action(playerid, "взял(а) со склада АКС-74У");

							SetPVarInt(playerid, "took_acs74y", gettime() + 300);
						}
						case 7:
						{
							if(GetPVarInt(playerid, "took_remington") > gettime())
								return SendClientMessage(playerid, 0x999999FF, "Вы уже недавно брали Remington 870");

							GiveIteam(playerid, 14, 1, 1, 0);

							Action(playerid, "взял(а) со склада Remington 870");

							SetPVarInt(playerid, "took_remington", gettime() + 300);
						}
						case 8:
						{
							GiveIteam(playerid, 363, 1, 1, 0);

							Action(playerid, "взял(а) со склада Патроны (.44 Magnum)");
						}
						case 9:
						{
							GiveIteam(playerid, 368, 1, 1, 0);

							Action(playerid, "взял(а) со склада Патроны (7.62x39)");
						}
						case 10:
						{
							GiveIteam(playerid, 366, 1, 1, 0);

							Action(playerid, "взял(а) со склада Патроны (5.45x39)");
						}
						case 11:
						{
							GiveIteam(playerid, 365, 1, 1, 0);

							Action(playerid, "взял(а) со склада Патроны (12x70)");
						}
					}
				}
			}
			case DIALOG_ARMORY1:
			{
				if(response)
				{
					switch(listitem + 1)
					{
						case 1:
						{
							if(GetPVarInt(playerid, "took_nitestick") > gettime())
								return SendClientMessage(playerid, 0x999999FF, "Вы уже недавно брали дубинку");

							GiveWeapon(playerid, 3, 1);

							Action(playerid, "взял(а) со склада Дубинку");

							SetPVarInt(playerid, "took_nitestick", gettime() + 300);
						}
						case 2:
						{
							new Float: armour;

							GetPlayerArmour(playerid, armour);

							if(armour > 20.0)
								return SendClientMessage(playerid, 0x999999FF, "У Вас уже есть бронежилет");

							SetPlayerArmour(playerid, 100.0);

							Action(playerid, "взял(а) со склада Бронежилет");
						}
						case 3:
						{
							if(GetPVarInt(playerid, "took_deagle") > gettime())
								return SendClientMessage(playerid, 0x999999FF, "Вы уже недавно брали Desert Eagle");

							GiveIteam(playerid, 19, 1, 1, 0);

							Action(playerid, "взял(а) со склада Desert Eagle");

							SetPVarInt(playerid, "took_deagle", gettime() + 300);
						}
						case 4:
						{
							if(GetPVarInt(playerid, "took_sdpistol") > gettime())
								return SendClientMessage(playerid, 0x999999FF, "Вы уже недавно брали Тайзер");

							GiveWeapon(playerid, 23, 60);

							Action(playerid, "взял(а) со склада Тайзер");

							SetPVarInt(playerid, "took_sdpistol", gettime() + 300);
						}
						case 5:
						{
							if(GetPVarInt(playerid, "took_akm") > gettime())
								return SendClientMessage(playerid, 0x999999FF, "Вы уже недавно брали AKM");

							GiveIteam(playerid, 21, 1, 1, 0);

							Action(playerid, "взял(а) со склада AKM");

							SetPVarInt(playerid, "took_akm", gettime() + 300);
						}
						case 6:
						{
							SendClientMessage(playerid, 0x3399FFFF, "На данный момент жезл не доступен!");
						}
						case 7:
						{
							if(GetPVarInt(playerid, "took_photo") > gettime())
								return SendClientMessage(playerid, 0x999999FF, "Вы уже недавно брали фотоаппарат");

							GiveWeapon(playerid, 43, 30);

							Action(playerid, "взял(а) со склада фотоаппарат");

							SetPVarInt(playerid, "took_photo", gettime() + 300);
						}
						case 8:
						{
							GiveIteam(playerid, 276, 1, 1, 0);
							Action(playerid, "взял(а) со склада Тауметр");
						}
						case 9:
						{
							GiveIteam(playerid, 255, 1, 1, 0);
							Action(playerid, "взял(а) со склада Апарат для диагностики");
						}
						case 10:
						{
							GiveIteam(playerid, 363, 1, 1, 0);

							Action(playerid, "взял(а) со склада Патроны (.44 Magnum)");
						}
						case 11:
						{
							GiveIteam(playerid, 368, 1, 1, 0);

							Action(playerid, "взял(а) со склада Патроны (7.62x39)");
						}
					}
				}
			}
			case DIALOG_BIZ_ORDERS:
			{
				if(!response) return 1;

				if(GetPlayerData(playerid, P_IN_JOB) == false) return SCM(playerid, COLOR_GREY, "Вы должны начать рабочий день");
				
				new vehicleid = GetPlayerVehicleID(playerid);
				
				new modelid = GetVehicleData(vehicleid, V_MODELID);

	            if(!IsNoTrailerTruck(modelid, 0)) if(!IsTrailerAttachedToVehicle(vehicleid)) return SCM(playerid, COLOR_GREY, "Вы должны взять соответствующий прицеп из гаража компании");
                    
				new order_id = GetPlayerListitemValue(playerid, listitem);

				SetPVarInt(playerid, "order_id", order_id);

				if(GetPlayerData(playerid, P_ORDER) != -1) return SendClientMessage(playerid, 0xCECECEFF, "Выполните текущий заказ перед тем как взять новый");

				if(!GetOrderData(order_id, O_AMOUNT)) return SendClientMessage(playerid, 0xFF6600FF, "Ошибка: Выбранный заказ не найден");

				if(GetOrderData(order_id, O_USED)) return SendClientMessage(playerid, -1, "Этот заказ уже принял другой дальнобойщик");

				string_dialog[0] = EOS;
				format
				(
					string_dialog, sizeof string_dialog,
					"{FFFFFF}Название предприятия: {f0c94f}%s\n\
					{FFFFFF}Необходимый товар: {f0e94f}Продукты\n\
					{FFFFFF}Длина пути от места загрузки: {f0c94f}Неизвестно.\n\n\
					{FFFFFF}Необходимое количество: {f0c94f}%d {FFFFFF}ед.\n\
					{FFFFFF}Оплата за всю работу: {aef04f}%s {FFFFFF}руб.\n\n\
					{FFFFFF}Комиссия компании составляет: {ffe36c}25%\n\n\
					{FFFFFF}Примерное количество заездов: {f0c94f}%d {FFFFFF}кр.",
					GetBusinessData(GetOrderData(order_id, O_COMPANY_ID), B_NAME),
					GetOrderData(order_id, O_AMOUNT),
					formatInt(GetOrderData(order_id, O_PRICE)),
					GetOrderData(order_id, O_AMOUNT) / 2500
				);
				IntfDialogCallRemote(playerid, DIALOG_BIZ_ORDERS_INVITE, DIALOG_STYLE_MSGBOX, "{FFFFFF}Заказ на поставку груза", string_dialog, "Принять", "Назад");
			}
			case DIALOG_FUEL_ORDERS:
			{
				if(!response) return 1;

				if(GetPlayerData(playerid, P_IN_JOB) == false) return SCM(playerid, COLOR_GREY, "Вы должны начать рабочий день");
				
				new vehicleid = GetPlayerVehicleID(playerid);
				
				new modelid = GetVehicleData(vehicleid, V_MODELID);

	            if(!IsNoTrailerTruck(modelid, 1)) if(!IsTrailerAttachedToVehicle(vehicleid)) return SCM(playerid, COLOR_GREY, "Вы должны взять соответствующий прицеп из гаража компании");

                new order_id = GetPlayerListitemValue(playerid, listitem);

				SetPVarInt(playerid, "order_id", order_id);

				if(GetPlayerData(playerid, P_FUELORDER) != -1) return SendClientMessage(playerid, 0xCECECEFF, "Выполните текущий заказ перед тем как взять новый");

				if(!GetFuelOrderData(order_id, F_AMOUNT)) return SendClientMessage(playerid, 0xFF6600FF, "Ошибка: Выбранный заказ не найден");

				if(GetFuelOrderData(order_id, F_USED)) return SendClientMessage(playerid, -1, "Этот заказ уже принял другой дальнобойщик");

				string_dialog[0] = EOS;
				format
				(
					string_dialog, sizeof string_dialog,
					"{FFFFFF}Название предприятия: {f0c94f}%s\n\
					{FFFFFF}Необходимый товар: {f0e94f}Топливо\n\
					{FFFFFF}Длина пути от места загрузки: {f0c94f}Неизвестно.\n\n\
					{FFFFFF}Необходимое количество: {f0c94f}%d {FFFFFF}ед.\n\
					{FFFFFF}Оплата за всю работу: {aef04f}%s {FFFFFF}руб.\n\n\
					{FFFFFF}Комиссия компании составляет: {ffe36c}25%\n\n\
					{FFFFFF}Примерное количество заездов: {f0c94f}%d {FFFFFF}кр.",
					GetBusinessData(GetFuelOrderData(order_id, F_COMPANY_ID), B_NAME),
					GetFuelOrderData(order_id, F_AMOUNT),
					formatInt(GetFuelOrderData(order_id, F_PRICE)),
					GetFuelOrderData(order_id, F_AMOUNT) / 2500
				);

				IntfDialogCallRemote(playerid, DIALOG_FUEL_ORDERS_INVITE, DIALOG_STYLE_MSGBOX, "{FFFFFF}Заказ на поставку груза", string_dialog, "Принять", "Назад");
			}
			case DIALOG_FUEL_ORDERS_INVITE:
			{
				if(!response) return callcmd::fuellist(playerid);
				
				new vehicleid = GetPlayerVehicleID(playerid);
				
				new modelid = GetVehicleData(vehicleid, V_MODELID);

	            if(!IsNoTrailerTruck(modelid, 1)) if(!IsTrailerAttachedToVehicle(vehicleid)) return SCM(playerid, COLOR_GREY, "У вас нет прицепа");
				
				new order_id = GetPVarInt(playerid, "order_id");

				if(GetPlayerData(playerid, P_FUELORDER) != -1) return SendClientMessage(playerid, 0xCECECEFF, "Выполните текущий заказ перед тем как взять новый");

				if(!GetFuelOrderData(order_id, F_AMOUNT)) return SendClientMessage(playerid, 0xFF6600FF, "Ошибка: Выбранный заказ не найден");

				if(GetFuelOrderData(order_id, F_USED)) return SendClientMessage(playerid, -1, "Этот заказ уже принял другой дальнобойщик");

				SetFuelOrderData(order_id, F_USED, true);
				SetPlayerData(playerid, P_FUELORDER, order_id);

				SendClientMessage(playerid, 0xFFFFFFFF, "Вы начали выполнение заказа. Загрузите необходимое количество {ddbe86}топлива {FFFFFF}на нефтезаводе ({d6964e}(Отмечено красной точкой){FFFFFF})");
                SendClientMessage(playerid, 0xFFFFFFFF, "После этого отправляйтесь к {ddbe86}заправочной станции {FFFFFF}которая будет отмечена {BE2D2D}красной точкой на {FFFFFF}карте");
				SendClientMessage(playerid, 0xFFFFFFFF, "{d6964e}Совет по работе: {FFFFFF}Если выполнение контракта сильно затянется, то Вы получите временный запрет на взятие заказов");

				SetPlayerRaceCheckpoint(playerid, 2, 2649.1155, 634.5281, 14.1951, 0.0, 0.0, 0.0, 4.0, RCP_ACTION_TYPE_ORDER2_INVITE);
			}
			case DIALOG_BIZ_ORDERS_INVITE:
			{
				if(!response) return callcmd::bizlist(playerid);
				
				new vehicleid = GetPlayerVehicleID(playerid);
				
				new modelid = GetVehicleData(vehicleid, V_MODELID);

	            if(!IsNoTrailerTruck(modelid, 0)) if(!IsTrailerAttachedToVehicle(vehicleid)) return SCM(playerid, COLOR_GREY, "У вас нет прицепа");
				
				new order_id = GetPVarInt(playerid, "order_id");

				if(GetPlayerData(playerid, P_ORDER) != -1) return SendClientMessage(playerid, 0xCECECEFF, "Выполните текущий заказ перед тем как взять новый");

				if(!GetOrderData(order_id, O_AMOUNT)) return SendClientMessage(playerid, 0xFF6600FF, "Ошибка: Выбранный заказ не найден");

				if(GetOrderData(order_id, O_USED)) return SendClientMessage(playerid, -1, "Этот заказ уже принял другой дальнобойщик");

				SetOrderData(order_id, O_USED, true);
				SetPlayerData(playerid, P_ORDER, order_id);

				SendClientMessage(playerid, 0xFFFFFFFF, "Вы начали выполнение заказа. Загрузите необходимое количество {ddbe86}товара {FFFFFF}на заводе ({d6964e}(Отмечено красной точкой){FFFFFF})");

				SetPlayerRaceCheckpoint(playerid, 2, -1044.0236, 2203.1716, 38.1194, 0.0, 0.0, 0.0, 4.0, RCP_ACTION_TYPE_ORDER_INVITE);
			}
			case 4567:
			{
				if(!response) return 1;
				new vehicleid = GetPlayerVehicleID(playerid);
				RepairVehicle(vehicleid);
				if(IsAOwnableCar(vehicleid)) SetVehicleData(vehicleid, V_HEALTH, 1000.0);
				scm(playerid, COLOR_GREEN, "Вы успешно починили данный автомобиль");
			}
			case 1216:
			{
				if(!response) return 1;
				if(GetPlayerTeamEx(playerid) > 0 || g_player[playerid][P_JOB] == 9)
				{
					extract inputtext -> new player:id; else return IntfDialogCallRemote(playerid,1216,DIALOG_STYLE_INPUT,"Приглашение","Введите ид игрока которого хотите принять","Далее","Oтмена");
					callcmd::invite(playerid, IntToString(id));
				}
			}
			case 1234:
			{
				if(response)
				{
					switch(listitem)
					{
						case 0: 
						{
							string_dialog[0] = EOS;
							format(string_dialog, sizeof string_dialog, "{FFFFFF}Вы выдаете префикс: {42B02C}%s\n{FFFFFF}Для того чтобы выдать префикс, нужно ввести название и цвет через запятую.\nПример: Главный админ, FF6347-Красный, FDE910-Желтый, 42AAFF-Синий.\nПолучится в итоге так: {FF6347}Главный админ\n{FFFFFF}Посмотреть цвета можно через hex color.", GetPlayerNameEx(GetPVarInt(playerid,"PrefixID")));
							IntfDialogCallRemote(playerid, 1235, 1, "{FF6347}Ввод префикса{FFFFFF}", string_dialog, "Выбрать","Отмена");
						}
						case 1:
						{
							string_dialog[0] = EOS;
							format(string_dialog, sizeof(string_dialog), "[TAG-CMD] Администратор %s[%i] забрал префикс [ {%s}%s {ffffff}] у администратора %s[%i]", GetPlayerNameEx(playerid), playerid, g_player[GetPVarInt(playerid,"PrefixID")][P_MYPREFIX_COLOR], g_player[GetPVarInt(playerid,"PrefixID")][P_MYPREFIX], GetPlayerNameEx(GetPVarInt(playerid,"PrefixID")), GetPVarInt(playerid,"PrefixID"));
							SendMessageToAdmins(string_dialog, -1);

							g_player[GetPVarInt(playerid,"PrefixID")][P_MYPREFIX] = EOS;
							g_player[GetPVarInt(playerid,"PrefixID")][P_MYPREFIX_COLOR] = EOS;

							UpdatePlayerDataStr(GetPVarInt(playerid,"PrefixID"), "myprefix", g_player[GetPVarInt(playerid,"PrefixID")][P_MYPREFIX]);
							UpdatePlayerDataStr(GetPVarInt(playerid,"PrefixID"), "myprefixcolor", g_player[GetPVarInt(playerid,"PrefixID")][P_MYPREFIX_COLOR]);
							DeletePVar(playerid, "PrefixID");
						}
					}
				}
			}
			case 1235:
			{
				string_dialog[0] = EOS;
				if(response)
				{ 
					static prefix[120];
					static color[8];
					sscanf(inputtext,"p<,>s[120]s[7]",prefix,color);
					if(!strlen(inputtext))
					{
						format(string_dialog, sizeof(string_dialog), "{FFFFFF}Вы выдаете префикс: {42B02C}%s\n{FFFFFF}Для того чтобы выдать префикс, нужно ввести название и цвет через запятую.\nПример: Главный админ, FF6347.\nПолучится в итоге так: {FF6347}Главный админ\n{FFFFFF}Посмотреть цвета можно через hex color.\n{BE2D2D}Ошибка, вы ничего не ввели", GetPlayerNameEx(GetPVarInt(playerid,"PrefixID")));
						IntfDialogCallRemote(playerid, 1235, 1, "{FF6347}Ввод префикса{FFFFFF}", string_dialog, "Выбрать","Отмена");
					}
					if(strlen(prefix) <= 1 || strlen(prefix) > 120 || strlen(color) <= 1 || strlen(color) > 7)
					{
						format(string_dialog, sizeof(string_dialog), "{FFFFFF}Вы выдаете префикс: {42B02C}%s\n{FFFFFF}Для того чтобы выдать префикс, нужно ввести название и цвет через запятую.\nПример: Главный админ, FF6347.\nПолучится в итоге так: {FF6347}Главный админ\n{FFFFFF}Посмотреть цвета можно через hex color.\n{BE2D2D}Ошибка, вы не правильно указали имя префикс\n{BE2D2D}Или указан некорректный цвет", GetPlayerNameEx(GetPVarInt(playerid,"PrefixID")));
						IntfDialogCallRemote(playerid, 1235, 1, "{FF6347}Ввод префикса{FFFFFF}", string_dialog, "Выбрать","Отмена");
					}
					else
					{
						g_player[GetPVarInt(playerid,"PrefixID")][P_MYPREFIX] = EOS;
						strcat(g_player[GetPVarInt(playerid,"PrefixID")][P_MYPREFIX], prefix);
						g_player[GetPVarInt(playerid,"PrefixID")][P_MYPREFIX_COLOR] = EOS;
						strcat(g_player[GetPVarInt(playerid,"PrefixID")][P_MYPREFIX_COLOR], color);
						format(string_dialog, sizeof(string_dialog), "[TAG-CMD] Администратор %s[%i] выдал префикс [ {%s}%s {ffffff}] администратору %s[%i]", GetPlayerNameEx(playerid), playerid, color, prefix, GetPlayerNameEx(GetPVarInt(playerid,"PrefixID")), GetPVarInt(playerid,"PrefixID"));
						SendMessageToAdmins(string_dialog, -1);
						UpdatePlayerDataStr(GetPVarInt(playerid,"PrefixID"), "myprefix", g_player[GetPVarInt(playerid,"PrefixID")][P_MYPREFIX]);
						UpdatePlayerDataStr(GetPVarInt(playerid,"PrefixID"), "myprefixcolor", g_player[GetPVarInt(playerid,"PrefixID")][P_MYPREFIX_COLOR]);
						DeletePVar(playerid, "PrefixID");
					}
				}
			}
			case DIALOG_MAFIA_YGON:
			{
			    if(!response) return 1;
				if(GetPVarInt(playerid,"ygnal1") == 0) return SendClientMessage(playerid, 0x999999FF, "Вы ещё не угнали прошлое транспортное средство");
				SendClientMessage(playerid, 0xFF6600FF, "* Доставьте машину к отмеченому месту на карте");
				SetPlayerRaceCheckpoint(playerid, 1, -2553.7964,-781.6291,29.5735, 0.0,0.0,0.0, 6.0, RCP_ACTION_TYPE_YGON);
				SetPVarInt(playerid,"ygnal1", 0);
			}
			
      	case DIALOG_RENT_MOP:
        {
            if(!response)
                return 1;

            new level = GetPlayerLevel(playerid);
            new price;

            if(level == 1) {
                price = 100;
            } else if(level == 2) {
                price = 250; 
            } else if(level == 3) {
                price = 500;
            } else if(level == 4) {
                price = 500;
            } else {
                SCM(playerid, 0xeed985FF, "Аренда скутеров доступно только новичкам.");
                SCM(playerid, 0xeed985FF, "Вы можете воспользоваться услугами такси при помощи приложения в телефоне");
                return true;
            }

            if(!VerifyIntString(QueryPlayerBalance(playerid), price))
               return SCM(playerid, COLOR_GREY, "Недостаточно средств.");

            if(GetPlayerData(playerid, P_RENT_MOPED) != INVALID_VEHICLE_ID) {
               DestroyVehicle(GetPlayerData(playerid, P_RENT_MOPED));
               SetPlayerData(playerid, P_RENT_MOPED, INVALID_VEHICLE_ID);
               SCM(playerid, 0xe3bb42FF, "Срок действия Вашего транспорта истёк или он был уничтожен.");
            }

            ModifyCashBalance(playerid, -price, "Аренда скутера");
            SetPVarInt(playerid, "rent_moped_time", gettime() + 3600);

            SCM(playerid, 0xe3bb42FF, "Транспортное средство арендовано для Вас и другие игроки не могут использовать его.");
			SCM(playerid, 0xe3bb42FF, "Используйте /lock 2 (ALT + 1) чтобы открыть/закрыть арендованный транспорт");

            new Float: x, Float: y, Float: a, Float: z;

            GetPlayerPos(playerid, x, y, z);
            GetPlayerFacingAngle(playerid, a);

            SetPlayerData(playerid, P_RENT_MOPED, CreateVehicle(462, x, y, z, a, 7, 7, 300, 0, VEHICLE_ACTION_TYPE_RENT_MOPED));
            PutPlayerInVehicle(playerid, GetPlayerData(playerid, P_RENT_MOPED), 0);
            return 1;
		}
		case DIALOG_KIOSK_INTER:
		{
			if(!response) return SetPVarInt(playerid, "kiosk_inter",0);

			SetPVarInt(playerid, "kiosk_inter",listitem +1);

			if(GetPVarInt(playerid, "kiosk_inter") == 1) SetPVarInt(playerid, "modelid_inter", 15933), SetPVarInt(playerid, "price_inter", 1000000);
			if(GetPVarInt(playerid, "kiosk_inter") == 2) SetPVarInt(playerid, "modelid_inter", 15930), SetPVarInt(playerid, "price_inter", 1500000);
			if(GetPVarInt(playerid, "kiosk_inter") == 3) SetPVarInt(playerid, "modelid_inter", 15932), SetPVarInt(playerid, "price_inter", 2000000);
			if(GetPVarInt(playerid, "kiosk_inter") == 4) SetPVarInt(playerid, "modelid_inter", 15931), SetPVarInt(playerid, "price_inter", 3000000);

			IntfDialogCallRemote(playerid, DIALOG_KIOSK_CHEK, DIALOG_STYLE_LIST,"{FFFF00}Выберите действие","1.Посмотреть интерьер\n2.Купить интерьер","Далее", "Назад");
		}
		case DIALOG_KIOSK_CHEK:
		{
			if(!response) return IntfDialogCallRemote(playerid, DIALOG_KIOSK_CHEK, DIALOG_STYLE_LIST,"{FFFF00}Выберите действие","1.Посмотреть интерьер\n2.Купить интерьер","Далее", "Назад");

			if(listitem == 0)
			{
				SetPlayerCameraPos(playerid,5946.068359,-692.841613,1851.135986);
				SetPlayerCameraLookAt(playerid, 5942.020019,-690.176330,1849.908813);

				SetPVarInt(playerid, "kiosk_object",CreatePlayerObject(playerid, GetPVarInt(playerid, "modelid_inter"), 5941.37, -694.848, 1848.88, 0.0, 0.0, 0.0));
				CEF_CREATE(playerid, 2, 4, "Interactions","[[9, \"Закончить просмотр\"]]");
			}
			if(listitem == 1)
			{
				string_dialog[0] = EOS;
				format(string_dialog, sizeof string_dialog, "{FFFFFF}Вы уверены что хотите приобрести интерьер {ffa500}№%d?\n{FFFFFF}Стоимость: {ffa500}%d руб.\n\n{FFFFFF}Внимание! С интерьера будут убраны все размещенные аксессуары!", GetPVarInt(playerid, "kiosk_inter"), GetPVarInt(playerid, "price_inter"));
				IntfDialogCallRemote(playerid, DIALOG_KIOSK_BUY_INTER, DIALOG_STYLE_MSGBOX, "{FFFFFF}Покупка интерьера", string_dialog, "Да", "Назад");
			}
		}
		case DIALOG_KIOSK_BUY_INTER:
		{
			if(!response) return 1;
			
			new query[84], idx = GetNearestKiosk(playerid, 5.0);

			if(!VerifyIntString(QueryPlayerBalance(playerid), GetPVarInt(playerid, "price_inter"))) return SendClientMessage(playerid, 0xFF6600FF, "*Недостаточно средств.");

			ModifyCashBalance(playerid, -GetPVarInt(playerid, "price_inter"));

			if(IsValidDynamicObject(kioskobj[idx])) DestroyDynamicObject(kioskobj[idx]);

			kioskobj[idx] = CreateDynamicObject(GetPVarInt(playerid, "modelid_inter"), GetKioskData(idx, K_POS_X_INTER), GetKioskData(idx, K_POS_Y_INTER), 1000, 0.0, 0.0, GetKioskData(idx, K_POS_ANGEL_INTER));
			
			mysql_format(mysql, query, sizeof query, "UPDATE kiosk SET inter=%d WHERE id=%d", GetPVarInt(playerid, "modelid_inter"), idx);
			mysql_query(mysql, query, false);
		}
		case DIALOG_LESOPILKA:
		{
			if(!response) return 1;
			switch(listitem + 1)
			{
				case 1:
				{
                    SetPlayerSkin(playerid, GetTempJobInfo(TEMP_JOB_LUMBERJACK, TJ_SKIN)[GetPlayerSex(playerid)]);

					SetPlayerJobLoadItems(playerid, 0);
					SetPlayerTempJob(playerid, TEMP_JOB_LUMBERJACK);

					SetPlayerCheckpoint(playerid, 477.8635, -2439.0234, 34.762901, 2.0);
					lesopilka_cp[playerid] = 1;
					Lesopilka[playerid] = 1;

					TotalEarnings[playerid] = 0;

					SendClientMessage(playerid, 0xabcdefFF, "Возьмите бревно со склада и отнесите на пилораму, чтобы начать работать.");
				}
			}
		}
		case DIALOG_FERMER:
		{
			if(!response) return 1;
			switch(listitem + 1)
			{
				case 1:
				{
                   SendClientMessage(playerid, COLOR_GOLD, "Возьмите пщеницу в мельнице и отнесите на склад");
                   SetPlayerTempJobState(playerid, TEMP_JOB_STATE_FERMER_CHOP);
				   SetPlayerFermerChopCP(playerid);
				}
				case 2:
				{
                   if(GetPlayerLevel(playerid) < 2) return SCM(playerid, -1, "Вам не доступно данное занятие");
                   SendClientMessage(playerid, COLOR_GOLD, "Собирайте урожай и относите его на мельницу");
                   SetPlayerTempJobState(playerid, TEMP_JOB_STATE_FERMER_SBOR);
				   SetPlayerFermerChopCPSbor(playerid);
				}
				case 3:
				{
                   if(GetPlayerLevel(playerid) < 7) return SCM(playerid, -1, "Вам не доступно данное занятие");
                   SendClientMessage(playerid, COLOR_GOLD, "Возьмите трактор и езжайте на поле");
                   SetPVarInt(playerid, "fermawork",1);
				}
			}
		}
		case DIALOG_FERMER_END:
		{
			if(!response) return 1;
			switch(listitem + 1)
			{
				case 1:
				{
                   IntfDialogCallRemote(playerid,DIALOG_FERMER,DIALOG_STYLE_LIST,"Выберите работу","1. Перенос урожая\n2. Сбор урожая (2+ уровень)\n3. Вспахивание поля (7+ уровень)","Выбрать","Закрыть");
				}
				case 2:
				{
                   EndPlayerTempJob(playerid, TEMP_JOB_FERMER);
				}
			}
		}
		case DIALOG_OZERO:
		{
			if(!response) return 1;
			if(GetIteam(playerid, 130) < 1) return SCM(playerid, 0xCECECEFF, "* У вас нет надувной лодки");
	        g_temp_vehicle2[playerid] = CreateVehicle(473, -407.2072, 2503.5723, -0.2693, 153.6670, 1, 1, -1);
	        PutPlayerInVehicle(playerid, g_temp_vehicle2[playerid], 0);
			Ozerolodka[playerid] = 1;
	        SendClientMessage(playerid, 0x2e9f5eFF, "{00FF00}Вы успешно развернули надувную лодку");
	        SendClientMessage(playerid, 0x2e9f5eFF, "{00FF00}Не создавайте много шума чтобы не спугнуть добычу");
		}
		case DIALOG_OZERO_END:
		{
			if(!response) return 1;
	        SendClientMessage(playerid, 0x2e9f5eFF, "{00FF00}Вы успешно убрали надувную лодку");
	        Ozerolodka[playerid] = 0;
	        DestroyVehicle(g_temp_vehicle2[playerid]);
            g_temp_vehicle2[playerid] = INVALID_VEHICLE_ID;
		}
		case DIALOG_NEFT:
		{
			if(!response) return 1;
			selectedNeftType[playerid] = listitem;

			switch(listitem)
			{
				case 0:
				{
					IntfDialogCallRemote(playerid, DIALOG_CREATE_NEFTENASOS, DIALOG_STYLE_MSGBOX,"{FFFFFF}Подтверждение строительства","{FFFFFF}Стоимость постройки {ffa500}1.000.000 {FFFFFF}руб.\n{FFFFFF}Хотите начать строительство нефтяного насоса?\n\n{ffa500}Внимние! {FFFFFF}Если рядом есть транспорт советуем его припарковать подальше.","Да", "Нет");
				}
				case 1:
				{
                    IntfDialogCallRemote(playerid, DIALOG_CREATE_NEFTENASOS, DIALOG_STYLE_MSGBOX,"{FFFFFF}Подтверждение строительства","{FFFFFF}Стоимость постройки {ffa500}5.000.000 {FFFFFF}руб.\n{FFFFFF}Хотите начать строительство нефтяного насоса?\n\n{ffa500}Внимние! {FFFFFF}Если рядом есть транспорт советуем его припарковать подальше.","Да", "Нет");
				}
			}
		}
		case DIALOG_CREATE_NEFTENASOS:
		{
			if(!response) return 1;
            
			switch(selectedNeftType[playerid])
			{
                case 0:{
					if(!VerifyIntString(QueryPlayerBalance(playerid), 1000000)) return GameText(playerid, "~r~Недостаточно~n~средств", 3000, 2);
			        ModifyCashBalance(playerid, -1000000);
					CreatePlayerNeft(playerid, 0);
					SendClientMessage(playerid, 0x999999FF, "{ffa500}Вы успешно начали строительство нефтяного насоса. Длительность: {FFFFFF} 29 мин.");
				}
				case 1:{
                    if(!VerifyIntString(QueryPlayerBalance(playerid), 5000000)) return GameText(playerid, "~r~Недостаточно~n~средств", 3000, 2);
			        ModifyCashBalance(playerid, -5000000);
			        CreatePlayerNeft(playerid, 1);
					SendClientMessage(playerid, 0x999999FF, "{ffa500}Вы успешно начали строительство нефтяного насоса. Длительность: {FFFFFF} 1 мин. и 0 сек.");
				}
			}
			
			GiveIteam(playerid, 288, 0, 1, 0);
			DisablePlayerCheckpoint(playerid);
			neft_cp[playerid] = 0;
			SendClientMessage(playerid, 0x999999FF, "{ffa500}Управление осуществляется через пикап. Не забудьте оплатить нефтяной насос в банке!");
		}
		case DIALOG_NEFTENASOS:
		{
			if(!response) return 1;
			new neft = GetPVarInt(playerid, "ownableneft");
			switch(listitem + 1)
			{
				case 1:
				{
					if(GetNeftData(neft, N_WORK_STATUS) == 0) return ShowMenuNeft(playerid), SCM(playerid, -1, "*На данный момент вам это не доступно.");
					if(GetNeftData(neft, N_WORK_STATUS) == 1)
					{
	                    if(GetNeftData(neft, N_IMPROVEMENTS) == 0){
                            if(GetNeftData(neft, N_FUELS) != 4500){
                                SetNeftData(neft, N_WORK_STATUS, 2);
                                SCM(playerid, -1, "{ffa500}Вы{FFFFFF} включили {ffa500}нефтенасос.");
                            }
                            else SCM(playerid, COLOR_ORANGE, "Резервуар с нефтью заполнен, нет смысла включать насос, закажите экспорт.");
	                    }
                        else if(GetNeftData(neft, N_FUELS) != 6700){
                            SetNeftData(neft, N_WORK_STATUS, 2);
		                    SCM(playerid, -1, "{ffa500}Вы{FFFFFF} включили {ffa500}нефтенасос.");
	                    }
	                    else SCM(playerid, COLOR_ORANGE, "Резервуар с нефтью заполнен, нет смысла включать насос, закажите экспорт.");
						ShowMenuNeft(playerid);
					}
					else if(GetNeftData(neft, N_WORK_STATUS) == 2)
					{
                        SetNeftData(neft, N_WORK_STATUS, 1);
						ShowMenuNeft(playerid);
						SCM(playerid, -1, "{ffa500}Вы{FFFFFF} выключили {ffa500}нефтенасос.");
					} 
				}
				case 2:
				{
                    if(GetNeftData(neft, N_FUELS) < 1000) return ShowMenuNeft(playerid), SCM(playerid, COLOR_ORANGE, "Экспорт нефти недоступен: в резервуаре меньше 1000 литров.");
                    if(!response) return ShowMenuNeft(playerid);
					IntfDialogCallRemote
	                (
                        playerid, DIALOG_NEFTENASOS2, DIALOG_STYLE_MSGBOX,
		                "Создание контракта",
		                "{FFFFFF}Выберите тип заказа: премиум или обычный. За премиум-заказ придётся доплатить {ffa500} 5.000 {FFFFFF} рублей.\n"\
		                "\n"\
		                "{ffa500}Примечание: {FFFFFF}дальнобойщики выбранной компании выполняют Ваш премиум-заказ без очереди.",
		                "Премиум", "Обычный"
	                );
				}
				case 3: SendClientMessage(playerid, 0x999999FF, "*На данный момент нет активных заказов.");
				case 4:
				{
					new fmt2[148];

					string_dialog[0] = EOS;
					format(fmt2, sizeof fmt2, "{FFFFFF}Нефтяной насос №%d", neft);
					format
					(
						string_dialog, sizeof string_dialog,
						"{FFFFFF}Баланс: {ffa500}%d руб.\n"\
						"{FFFFFF}Оплачен на {ffa500}%d/5 дн.\n"\
						"{FFFFFF}Резервуар: {ffa500}%d.%d/%d\n\n"\
						"{FFFFFF}После включения нефтенасос начинает постепенно добывать нефть, которую нужно экспортировать\n"\
						"{FFFFFF}когда резервуар полностью заполнится. Учтите, что во время добычи может произойти пожар\n"\
						"{FFFFFF}из-за чего работа нефтенасоса будет приостановлена и вам нужно будет включить его заново.",
						GetNeftData(neft, N_BALANCE),
						GetNeftData(neft, N_RENT_DATE),
						GetNeftData(neft, N_FUELS),
						fuels_neft[neft],
						neftfuels[neft]
					);
					return IntfDialogCallRemote(playerid, -1, DIALOG_STYLE_MSGBOX, fmt2, string_dialog, "", "Закрыть");
				}
				case 5: IntfDialogCallRemote(playerid, DIALOG_NEFTENASOS4, DIALOG_STYLE_TABLIST_HEADERS,"Выберите улучшение","{FFFFFF}Наименование \t {FFFFFF}Цена\n{FFFFFF}1. Подземный резервуар \t {ffa500}15.000.000 руб\n{FFFFFF}2. Модуль включения \t {ffa500}10.000.000 руб","Далее", "Назад");
				case 6: IntfDialogCallRemote(playerid, DIALOG_SELL_NEFTENASOS, DIALOG_STYLE_INPUT,"{FFFFFF}Продажа нефтенасоса","{FFFFFF}Введите ID покупателя и цену используя пробел.\nПример: 0 700000 - продать игроку 0 ID нефтенасос за 700.000 руб.","Готово", "Назад");
				case 7: IntfDialogCallRemote(playerid, DIALOG_DESTROY_NEFTENASOS, DIALOG_STYLE_MSGBOX,"{FFFFFF}Подтвердите действие","{FFFFFF}Вы уверены, что хотите демонтировать нефтенасос? Ценная бумага возвращена не будет!\n{ffa500}Демонтированное оборудование будет продано за 700.000 руб.","Да", "Нет");
			}
		}
		case DIALOG_NEFTENASOS2: 
		{
			if(!response) return PremiumNeft(playerid);
			
			IntfDialogCallRemote(playerid, DIALOG_NEFTENASOS3, DIALOG_STYLE_MSGBOX,"{FFFFFF}Заказ у транспортных компаний","{FFFFFF}Вы действительно желаете заказать экспорт нефти с Вашего нефтенасоса?","Далее", "Назад");
		}
		case DIALOG_DESTROY_NEFTENASOS:
		{
			if(!response) return 1;
			new neft = GetPVarInt(playerid, "ownableneft");
			ModifyCashBalance(playerid, 700000);
			SendClientMessage(playerid, 0x999999FF, "{FFFFFF}Вы демонтировали {f2e8c9}нефтяной насос, {FFFFFF}вам было возвращено 700 000 руб.");
			if(GetNeftData(neft, N_WORK_STATUS) == 0) if(IsValidDynamicObject(neftobj[neft])) DestroyDynamicObject(neftobj[neft]); 
			if(GetNeftData(neft, N_WORK_STATUS) > 0)
			{
				if(IsValidDynamicObject(neftobj1[neft])) DestroyDynamicObject(neftobj1[neft]);
				if(IsValidDynamicObject(neftobj2[neft])) DestroyDynamicObject(neftobj2[neft]);
				if(IsValidDynamicObject(neftobj3[neft])) DestroyDynamicObject(neftobj3[neft]);
				if(IsValidDynamicObject(neftobj4[neft])) DestroyDynamicObject(neftobj4[neft]);
				if(IsValidDynamicObject(neftobj5[neft])) DestroyDynamicObject(neftobj5[neft]);
			}
			if(IsValidDynamicObject(neftobj6[neft])) DestroyDynamicObject(neftobj6[neft]);
			DestroyPickup(neftpickup[neft]);
			DestroyDynamic3DTextLabel(neftlabelty[neft]);
			DestroyDynamic3DTextLabel(neftlabel[neft]);

			new query[148];
			mysql_format(mysql, query, sizeof query, "UPDATE neftenasos SET owner_id=0 WHERE id=%d", neft);
			mysql_query(mysql, query, false);
		}
		case DIALOG_NEFTENASOS3:
		{
            if(!VerifyIntString(QueryPlayerBalance(playerid), 5000)) return GameText(playerid, "~r~Недостаточно~n~средств", 3000, 2);
			new neft = GetPVarInt(playerid, "ownableneft");
			string_dialog[0] = EOS;
			new fmt1[64];
			new fmt2[64];

			new day, month, year;
			getdate(day, month, year);

			if(year < 10) format(fmt1, sizeof fmt1,"0%d", year);
			else format(fmt1, sizeof fmt1,"%d", year);

			if(month < 10) format(fmt2, sizeof fmt2,"0%d", month);
			else format(fmt2, sizeof fmt2,"%d", month);

			format
			(
				string_dialog, sizeof string_dialog,
				"{ffd700}- Параметры заказа:\n\n"\
				"{FFFFFF}Количество литров нефти: \t %d ед.\n"\
				"{FFFFFF}Стоимость одного литра нефти: \t 9400 руб\n"\
				"{FFFFFF}Общая стоимость заказа: \t %d руб\n"\
				"{FFFFFF}Дата оформления заказа: \t %s-%s-%d\n\n"\
				"{FFFFFF}Мы уведомили свободных сотрудников транспортных компаний о новом контракте.\n"\
				"{FFFFFF}Обратите внимание, что начисление денег за экспорт происходит после полного завершения заказа.\n"\
				"{FFFFFF}Премиум-заказ послужит дополнительным стимулом для дальнобойщиков.",
				GetNeftData(neft, N_FUELS),
				GetNeftData(neft, N_FUELS) * 9400,
				fmt1,
				fmt2,
				day
			);
		    new neftbalance = GetNeftData(neft, N_FUELS) * 9400;
			SetNeftData(neft, N_BALANCE, GetNeftData(neft, N_BALANCE) + neftbalance), SetNeftData(neft, N_FUELS, 0);
			new query[240];
			format(query, sizeof query, "UPDATE neftenasos SET neftfuels=%d, balance=%d WHERE id=%d", GetNeftData(neft, N_FUELS), GetNeftData(neft, N_BALANCE), GetNeftData(neft, N_SQL_ID));
			mysql_query(mysql, query, false);

			CallLocalFunction("UpdateNeftLabel", "i", neft);
			ModifyCashBalance(playerid, -5000);

			return IntfDialogCallRemote(playerid, -1, DIALOG_STYLE_MSGBOX, "{FFFFFF}Заказ оформлен", string_dialog, "", "Закрыть");
		}
		case DIALOG_NEFTENASOS4:
		{
			if(!response) return ShowMenuNeft(playerid);
			switch(listitem + 1){
				case 1: SetPVarInt(playerid, "neftulu", 1), IntfDialogCallRemote(playerid, DIALOG_NEFTENASOS5, DIALOG_STYLE_MSGBOX,"{FFFFFF}Подземный резервуар","{FFFFFF}Второй резервуар будет расположен под землёй.\n{FFFFFF}Таким образом общая вместительность составит {ffa500}6700 литров.\n{FFFFFF}Стоимость: {ffa500}15.000.000 руб.","Купить", "Назад");
				case 2: SetPVarInt(playerid, "neftulu", 2), IntfDialogCallRemote(playerid, DIALOG_NEFTENASOS5, DIALOG_STYLE_MSGBOX,"{FFFFFF}Модуль включения","{FFFFFF}Модуль, который будет вкрючать нефтенасос после пожара.\n{FFFFFF}Таким образом вам нужно будет меньше следить за нефтяным насосом.\n{FFFFFF}Стоимость: {ffa500}10.000.000 руб.","Купить", "Назад");
			}
		}
		case DIALOG_NEFTENASOS5:
		{
			if(!response) return ShowMenuNeft(playerid);
			new neft = GetPVarInt(playerid, "ownableneft");
			new query[240];
			if(GetPVarInt(playerid, "neftulu") == 1){
				if(GetNeftData(neft, N_IMPROVEMENTS) > 0) return SendClientMessage(playerid, 0xead671FF, "Это улучшение уже приобретено.");
				if(!VerifyIntString(QueryPlayerBalance(playerid), 15000000)) return SendClientMessage(playerid, 0x999999FF, "*Недостаточно денег.");
				ModifyCashBalance(playerid, -15000000), SetNeftData(neft, N_IMPROVEMENTS, 1), neftfuels[neft] = 6700;
				CallLocalFunction("UpdateNeftLabel", "i", neft);
			}
			if(GetPVarInt(playerid, "neftulu") == 2){
				if(GetNeftData(neft, N_IMPROVEMENTS) > 1 || GetNeftData(neft, N_IMPROVEMENTS) != 1) return SendClientMessage(playerid, 0xead671FF, "Это улучшение уже приобретено.");
				if(!VerifyIntString(QueryPlayerBalance(playerid), 10000000)) return SendClientMessage(playerid, 0x999999FF, "*Недостаточно денег.");
				ModifyCashBalance(playerid, -10000000), SetNeftData(neft, N_IMPROVEMENTS, 2);
			}
			format(query, sizeof query, "UPDATE neftenasos SET improvements=%d WHERE id=%d", GetNeftData(neft, N_IMPROVEMENTS), GetNeftData(neft, N_SQL_ID));
			mysql_query(mysql, query, false);
			DeletePVar(playerid, "neftulu");
		}
		case DIALOG_SELL_NEFTENASOS:
		{
			if(!response) return ShowMenuNeft(playerid);
			new neft = GetPVarInt(playerid, "ownableneft");
            new targetid, price;

            if(sscanf(inputtext, "ii", targetid, price))
                return 1;

            if(!IsPlayerConnected(targetid)) 
                return SCM(playerid, 0xead671FF, "Игрок оффлайн.");

			//if(targetid == playerid)
		        //return SCM(playerid, 0xead671FF, "Вы не сможете сдать в аренду огород самому себе.");

			if(!IsPlayerInRangeOfPlayer(playerid, targetid, 7.0)) return SCM(playerid, 0xead671FF, "Вы находитесь далеко друг от друга.");

            if(price < 3000)
                return SCM(playerid, 0xead671FF, "Вы не можете продать нефтяной насос менее чем за 3.000 руб.");

            SendPlayerOffer(playerid, targetid, OFFER_TYPE_SELL_NEFTENASOS, neft, price);
		}
		case DIALOG_NEFT_PREMIUM:
		{
			new neft = GetPVarInt(playerid, "ownableneft");
			string_dialog[0] = EOS;
			new fmt1[64];
			new fmt2[64];

			new day, month, year;
			getdate(day, month, year);

			if(year < 10) format(fmt1, sizeof fmt1,"0%d", year);
			else format(fmt1, sizeof fmt1,"%d", year);

			if(month < 10) format(fmt2, sizeof fmt2,"0%d", month);
			else format(fmt2, sizeof fmt2,"%d", month);

			format
			(
				string_dialog, sizeof string_dialog,
				"{ffd700}- Параметры заказа:\n\n"\
				"{FFFFFF}Количество литров нефти: \t %d ед.\n"\
				"{FFFFFF}Стоимость одного литра нефти: \t 9400 руб\n"\
				"{FFFFFF}Общая стоимость заказа: \t %d руб\n"\
				"{FFFFFF}Дата оформления заказа: \t %s-%s-%d\n\n"\
				"{FFFFFF}Мы уведомили свободных сотрудников транспортных компаний о новом контракте.\n"\
				"{FFFFFF}Обратите внимание, что начисление денег за экспорт происходит после полного завершения заказа.\n"\
				"{FFFFFF}Премиум-заказ послужит дополнительным стимулом для дальнобойщиков.",
				GetNeftData(neft, N_FUELS),
				GetNeftData(neft, N_FUELS) * 9400,
				fmt1,
				fmt2,
				day
			);
		    new neftbalance = GetNeftData(neft, N_FUELS) * 9400;
			SetNeftData(neft, N_BALANCE, GetNeftData(neft, N_BALANCE) + neftbalance), SetNeftData(neft, N_FUELS, 0);
			new query[240];
			format(query, sizeof query, "UPDATE neftenasos SET neftfuels=%d, balance=%d WHERE id=%d", GetNeftData(neft, N_FUELS), GetNeftData(neft, N_BALANCE), GetNeftData(neft, N_SQL_ID));
			mysql_query(mysql, query, false);

			CallLocalFunction("UpdateNeftLabel", "i", neft);

			return IntfDialogCallRemote(playerid, -1, DIALOG_STYLE_MSGBOX, "{FFFFFF}Заказ оформлен", string_dialog, "", "Закрыть");
		}
		case DIALOG_OWNABLE_BLACK_MARKET:
		{
			if(!response) return 1;
			
			new idx = GetPlayerListitemValue(playerid, listitem);
			new query[64],
			Cache: result;

			mysql_format(mysql, query, sizeof query, "SELECT * FROM black_market WHERE id='%d'", idx);
			result = mysql_query(mysql, query, true);

			if(cache_num_rows())
			{
				if(cache_get_field_content_int(0, "type") == 0) GiveCar(playerid, cache_get_field_content_int(0, "modelid"), 1, 1, -1, -1, -1765.9470, 2911.2585, 5.8822, 90.4859, gettime()), SendClientMessage(playerid, -1, "Вы забрали автомобиль");
				if(cache_get_field_content_int(0, "type") == 1) GiveSkin(playerid, cache_get_field_content_int(0, "modelid")), SendClientMessage(playerid, -1, "Вы забрали скин");
			}
			mysql_format(mysql, query, sizeof query, "DELETE FROM black_market WHERE id=%d", idx);
			mysql_query(mysql, query, false);

			cache_delete(result);
		}
		case DIALOG_GAUTH_SETUP:
		{
			if(!response)
			{
				format(g_player[playerid][P_AUTH_TOKEN], TOKEN_BUFFER, "");
                return 1;
			}

			if(strlen(inputtext) != 6 || !IsNumeric(inputtext)) 
			{
				format(g_player[playerid][P_AUTH_TOKEN], TOKEN_BUFFER, "");
				SendClientMessage(playerid, COLOR_GREEN, "[GA] Неверный код. Введите 6 цифр из Google Authenticator.");
				return 1;
			}

            new time_now = gettime();
            new entered = strval(inputtext);

            new expectedNow = GoogleAuthenticatorCode(g_player[playerid][P_AUTH_TOKEN], time_now);
            new expectedPrev = GoogleAuthenticatorCode(g_player[playerid][P_AUTH_TOKEN], time_now - 30);
            new expectedNext = GoogleAuthenticatorCode(g_player[playerid][P_AUTH_TOKEN], time_now + 30);

            if(entered == expectedNow || entered == expectedPrev || entered == expectedNext)
            {
                SendClientMessage(playerid, COLOR_GREEN, "[GA] Google Authenticator успешно привязан к вашему аккаунту!");

				SetPlayerData(playerid, P_2FA_ENABLED, 1);

				new fmt_msg[256];
                mysql_format(mysql, fmt_msg, sizeof fmt_msg, 
                "UPDATE accounts_canvasdev SET auth_token='%e', 2fa_enabled=%d WHERE id=%d", 
                g_player[playerid][P_AUTH_TOKEN], GetPlayerData(playerid, P_2FA_ENABLED), GetPlayerAccountID(playerid));
                mysql_query(mysql, fmt_msg, false);
            }
            else
			{
				format(g_player[playerid][P_AUTH_TOKEN], TOKEN_BUFFER, "");
				SendClientMessage(playerid, COLOR_GREEN, "[GA] Неверный код Google Authenticator.");
			}
		}
		case DIALOG_GAUTH_DEACTIVATE:
        {
            if(!response) return 1;

            if(strlen(inputtext) != 6 || !IsNumeric(inputtext))
            {
                SendClientMessage(playerid, COLOR_RED, "[GA] Неверный код. Введите 6 цифр из Google Authenticator.");
                return 1;
            }

            new time_now = gettime();
            new entered = strval(inputtext);

            new expectedNow = GoogleAuthenticatorCode(g_player[playerid][P_AUTH_TOKEN], time_now);
            new expectedPrev = GoogleAuthenticatorCode(g_player[playerid][P_AUTH_TOKEN], time_now - 30);
            new expectedNext = GoogleAuthenticatorCode(g_player[playerid][P_AUTH_TOKEN], time_now + 30);

            if(entered == expectedNow || entered == expectedPrev || entered == expectedNext)
            {
                format(g_player[playerid][P_AUTH_TOKEN], TOKEN_BUFFER, "");
                SetPlayerData(playerid, P_2FA_ENABLED, 0);

                new fmt_msg[128];
                mysql_format(mysql, fmt_msg, sizeof fmt_msg,
                "UPDATE accounts_canvasdev SET auth_token='', 2fa_enabled=0 WHERE id=%d",
                GetPlayerAccountID(playerid));
                mysql_query(mysql, fmt_msg, false);

                SendClientMessage(playerid, COLOR_GREEN, "[GA] Google Authenticator успешно отключён.");
            }
            else
            {
                SendClientMessage(playerid, COLOR_RED, "[GA] Неверный код Google Authenticator.");
            }
		}
		case DIALOG_ACTIVATE_2FA:
		{
			if(!response) return 1;

			GenerateGoogleToken(playerid);

			string_dialog[0] = EOS;
            format
            (
                string_dialog, sizeof string_dialog,
                "{FFFFFF}Чтобы подключить защиту через Google Authenticator:\n\n"\
                "1. Скачайте приложение Google Authenticator на телефон.\n"\
				"2. Добавьте новый аккаунт вручную.\n"\
                "3. Введите следующий секретный ключ:\n\n"\
                "{00CC66}%s\n\n"\
                "{FFFFFF}Введите 6-значный код из приложения для подтверждения.",
                g_player[playerid][P_AUTH_TOKEN]
            );

            IntfDialogCallRemote
            (
                playerid, DIALOG_GAUTH_SETUP, DIALOG_STYLE_INPUT, 
                "{C0D897}Подключение Google Authenticator", 
                string_dialog,
                "Привязать", "Отмена"
            );
		}
		case DIALOG_DEACTIVATE_2FA:
		{
			if(!response) return 1;

			IntfDialogCallRemote(playerid, DIALOG_GAUTH_DEACTIVATE, DIALOG_STYLE_INPUT, "{C0D897}Отключение Google Authenticator", "{FFFFFF}Для отключения Google Authenticator введите 6-значный код из приложения.", "Отключить", "Отмена");
		}
		case DIALOG_TRAINING_EDA:
		{
			if(!response) return 1;

			SetPVarInt(playerid,"respeat", 1);
			SetPVarInt(playerid,"training", 1);
			SetPVarInt(playerid,"Holodos", 0);
			SCM(playerid, -1, "{abcf1b}Для того, чтобы перекусить, используйте меню взаимодействия");
			SetPlayerAttachedObject(playerid, 5, 10024, 1, 0.104, 0.365, -0.267, 109.5, 126.1, -43.5, 1.0, 1.0, 1.0);
			CEF_CREATE(playerid, 2, 4, "Interactions", "[[5, \"Перекусить\"], [6, \"Выбросить поднос\"]]");

		}
		case DIALOG_FORBES_MENU:
		{
			if(!response) return 1;

			switch(listitem + 1)
			{
				case 1:
				{
                    new query[512];
                    format(query, sizeof(query), "SELECT name, CAST(money AS UNSIGNED) + CAST(bank AS UNSIGNED) AS total_money FROM accounts_canvasdev WHERE (CAST(money AS UNSIGNED) + CAST(bank AS UNSIGNED)) >= 500000000 ORDER BY total_money DESC LIMIT 20");
                    mysql_tquery(mysql, query, "ShowForbesMoney", "i", playerid);
				}
				case 2:
				{
					new query[256];
                    format(query, sizeof(query), "SELECT name, donate_current AS total_donate FROM accounts_canvasdev WHERE donate_current >= 10000 ORDER BY donate_current DESC LIMIT 20");
                    mysql_tquery(mysql, query, "ShowForbesDonate", "i", playerid);
				}
			    case 3:
				{
					new query[512];
                    format(query, sizeof(query), "SELECT i.owner_id, i.count AS total_count, a.name FROM items i LEFT JOIN accounts_canvasdev a ON i.owner_id = a.id WHERE i.item = 293 AND i.count >= 1000000 ORDER BY i.count DESC LIMIT 20");
                    mysql_tquery(mysql, query, "OnShowForbesChips", "i", playerid);
				}
			}
		}
		case DIALOG_LOTTERY:
		{
			new businessid = GetPlayerInBiz(playerid);
			if(businessid != -1)
			{
				if(response)
				{
					if(IsPlayerInBuyPosBiz(playerid, businessid, BUSINESS_TYPE_SHOP_24_7))
					{
						new price;
						new take_prods;

						switch(listitem + 1)
						{
							case 1:
							{
								price = 350000;
								take_prods = 2;

								if(VerifyIntString(QueryPlayerBalance(playerid), price))
								{
									if(GetBusinessData(businessid, B_PRODS) >= take_prods)
									{
										AddBusinessProfit(playerid, businessid, price * 20 / 100, take_prods);
									}
									ModifyCashBalance(playerid, -price, "Покупка лотерейного билета");

									GiveIteam(playerid, 257, 1, 1, 0);

									SendClientMessage(playerid, 0x66CC00FF, "Вы купили лотерейный билет");
									SendClientMessage(playerid, 0x66CC00FF, "Использовать его можно через инвентарь или /lottery");
								}
								else SendClientMessage(playerid, 0xCECECEFF, "Лотерейный билет стоит 350.000 рублей");
							}
							default:
								return 1;
						}
					}
				}
			}
		}
	}
	return 1;
}