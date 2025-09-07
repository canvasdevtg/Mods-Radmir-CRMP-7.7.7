#if defined _daily_rewards_included
    #endinput
#endif
#define _daily_rewards_included

new daily_timer;

stock MainMenu_OnPlayerRewardOpen(playerid, index)
{
	new type = random(5);

	if(!GetPlayerData(playerid, P_WARDS_PRIZE)) return 0;

    switch(type)
	{
		case 0:
		{
            new skin_id[] = {15576, 15578, 15581, 15586, 15592, 15595, 15598, 17042, 17046, 17049, 14, 18, 22, 32, 40, 43,
		    44, 46, 54, 64, 69, 77, 93, 95, 97, 270, 15310, 15319, 15320, 15337, 15360, 15361, 15395, 15433, 15482, 15501,
		    15526, 15528, 15527, 15537, 15540, 15546, 15549, 15550, 15551, 15552};
            new skin_index = RandomEx(0, sizeof(skin_id) - 1);
            new skin_give = skin_id[skin_index];

		    DailyIndex(playerid, index, skin_give, 4);

		    new query[94];
            format(query, sizeof query, "Одежда №%d", skin_give),
		    GivePlayerMyPrizes(playerid, query, 4, skin_give, 0, 1, 0);
		}
		case 1:
		{
			new money = RandomEx(50000, 5000000);

			DailyIndex(playerid, index, 1, 5);

			GivePlayerMyPrizes(playerid, "Деньги", 5, 1, 0, money, 0);
		}
		case 2:
		{
			new items_id[] = {258, 261, 272, 278, 284, 290, 300, 328, 344, 348, 350, 355, 356, 360, 259, 63, 75, 78, 
			81, 82, 80, 104, 105, 106, 107, 110, 111, 112, 113, 114, 122, 68, 69, 70, 123, 128, 138, 148, 149, 150,
			153, 154, 155, 156, 188, 189, 190, 191, 192, 200, 218, 257, 301, 317, 318, 319, 361, 293, 2};
            new items_index = RandomEx(0, sizeof(items_id) - 1);
            new items_give = items_id[items_index];
                
			DailyIndex(playerid, index, items_give, 8);
                
			if(items_give == 293)
			{
				new chip = RandomEx(25, 500);

                new query[94];
                format(query, sizeof query, "%s", ItemsInfo[items_give]),
			    GivePlayerMyPrizes(playerid, query, 8, items_give, 0, chip, 0);
			}
			else
			{
                new query[94];
                format(query, sizeof query, "%s", ItemsInfo[items_give]),
			    GivePlayerMyPrizes(playerid, query, 8, items_give, 0, 1, 0);
			}
		}
		case 3:
		{
			DailyIndex(playerid, index, 1, 10);

			new donate = RandomEx(10, 150);

			GivePlayerMyPrizes(playerid, "Донат", 10, 0, 0, donate, 0);
		}
		case 4:
		{
			DailyIndex(playerid, index, 1, 2);

			new exp = RandomEx(1, 7);

			GivePlayerMyPrizes(playerid, "Игровой опыт", 2, 0, 0, exp, exp);
		}
	}
	AddPlayerData(playerid, P_WARDS_PRIZE, -, 1);
	UpdatePlayerDatabaseInt(playerid, "wards_prize", GetPlayerData(playerid, P_WARDS_PRIZE));
            
    UpdateDaily(playerid);
	GameText(playerid, "~g~Успешно!", 4000, 3);

	return 1;
}

const MAX_DAILY = 28;

new const daily_item_db_keys[MAX_DAILY][32] = {
    "daily_items_1", "daily_items_2", "daily_items_3", "daily_items_4",
    "daily_items_5", "daily_items_6", "daily_items_7", "daily_items_8",
    "daily_items_9", "daily_items_10", "daily_items_11", "daily_items_12",
    "daily_items_13", "daily_items_14", "daily_items_15", "daily_items_16",
    "daily_items_17", "daily_items_18", "daily_items_19", "daily_items_20",
    "daily_items_21", "daily_items_22", "daily_items_23", "daily_items_24",
    "daily_items_25", "daily_items_26", "daily_items_27", "daily_items_28"
};

new const daily_open_db_keys[MAX_DAILY][32] = {
    "daily_open_1", "daily_open_2", "daily_open_3", "daily_open_4",
    "daily_open_5", "daily_open_6", "daily_open_7", "daily_open_8",
    "daily_open_9", "daily_open_10", "daily_open_11", "daily_open_12",
    "daily_open_13", "daily_open_14", "daily_open_15", "daily_open_16",
    "daily_open_17", "daily_open_18", "daily_open_19", "daily_open_20",
    "daily_open_21", "daily_open_22", "daily_open_23", "daily_open_24",
    "daily_open_25", "daily_open_26", "daily_open_27", "daily_open_28"
};

new const daily_type_db_keys[MAX_DAILY][32] = {
    "daily_type_1", "daily_type_2", "daily_type_3", "daily_type_4",
    "daily_type_5", "daily_type_6", "daily_type_7", "daily_type_8",
    "daily_type_9", "daily_type_10", "daily_type_11", "daily_type_12",
    "daily_type_13", "daily_type_14", "daily_type_15", "daily_type_16",
    "daily_type_17", "daily_type_18", "daily_type_19", "daily_type_20",
    "daily_type_21", "daily_type_22", "daily_type_23", "daily_type_24",
    "daily_type_25", "daily_type_26", "daily_type_27", "daily_type_28"
};

stock DailyIndex(playerid, index, items_give, type)
{
	if(index < 0 || index >= MAX_DAILY) return 0;

    g_player_daily_items[playerid][index] = items_give;
    g_player_daily_open[playerid][index] = 1;
    g_player_daily_type[playerid][index] = type;

    mysql_string[0] = EOS;
    format(mysql_string, sizeof mysql_string, "UPDATE daily_rewards_players SET %s=%d, %s=1, %s=%d WHERE uid =%d", 
        daily_item_db_keys[index], 
        items_give, 
        daily_open_db_keys[index], 
        daily_type_db_keys[index], 
        type, 
        GetPlayerAccountID(playerid)
    );
    mysql_pquery(mysql, mysql_string);

	return 1;
}

stock UpdateDaily(playerid)
{
    new tmpStr[2048];
    tmpStr[0] = '\0';

    for(new i = 0; i < 28; i++)
    {
        new tmp[64];
        format(tmp, sizeof(tmp), "[%d,%d,0,0,\"\",%d],",
            g_player_daily_type[playerid][i],
            g_player_daily_items[playerid][i],
            g_player_daily_open[playerid][i]
        );
        strcat(tmpStr, tmp, sizeof(tmpStr));
    }

    if(strlen(tmpStr) > 0)
        tmpStr[strlen(tmpStr) - 1] = '\0';

    new case_7_name[117], case_14_name[117], case_21_name[117], case_28_name[117];

    GetCaseNameById(GetPlayerData(playerid, P_DAILY_CASE_7_ID), case_7_name);
    GetCaseNameById(GetPlayerData(playerid, P_DAILY_CASE_14_ID), case_14_name);
    GetCaseNameById(GetPlayerData(playerid, P_DAILY_CASE_21_ID), case_21_name);
    GetCaseNameById(GetPlayerData(playerid, P_DAILY_CASE_28_ID), case_28_name);

    format(STRING_GLOBAL, sizeof(STRING_GLOBAL),
        "interface('MainMenu').onServerResponse(8, '[%d,%d,7200,%d,[%s],[[21,%d,0,0,\"%s\",[%d,7]],[21,%d,0,0,\"%s\",[%d,14]],[21,%d,0,0,\"%s\",[%d,21]],[21,%d,0,0,\"%s\",[%d,28]]]]')",
        MonthDaily(),
        DailyreWards_Time[playerid],
        GetPlayerData(playerid, P_WARDS_PRIZE),
        tmpStr,
        GetPlayerData(playerid, P_DAILY_CASE_7_ID),
        case_7_name,
        GetPlayerData(playerid, P_DAILY_CLAIM_7),
        GetPlayerData(playerid, P_DAILY_CASE_14_ID),
        case_14_name,
        GetPlayerData(playerid, P_DAILY_CLAIM_14),
        GetPlayerData(playerid, P_DAILY_CASE_21_ID),
        case_21_name,
        GetPlayerData(playerid, P_DAILY_CLAIM_21),
        GetPlayerData(playerid, P_DAILY_CASE_28_ID),
        case_28_name,
        GetPlayerData(playerid, P_DAILY_CLAIM_28)
    );

    CEF_CREATE(playerid, 1, 2, STRING_GLOBAL);

    return 1;
}

stock GetCaseNameById(caseId, caseName[], size = 128)
{
    switch(caseId)
    {
        case 0: format(caseName, size, "Открытие кейса Форсаж");
        case 1: format(caseName, size, "Открытие кейса Темные дела");
        case 2: format(caseName, size, "Открытие кейса Велесова ночь");
        case 3: format(caseName, size, "Открытие кейса Оперской");
        case 4: format(caseName, size, "Открытие кейса Новогодний");
        case 5: format(caseName, size, "Открытие кейса Черное золото");
        case 6: format(caseName, size, "Открытие кейса Охотничий");
        case 7: format(caseName, size, "Открытие кейса Египетская сила");
        case 8: format(caseName, size, "Открытие кейса Велесова ночь 2");
        case 9: format(caseName, size, "Открытие кейса Рождественский экспресс");
        case 10: format(caseName, size, "Открытие кейса Путь воина");
        case 11: format(caseName, size, "Открытие кейса Пиратский");
        case 12: format(caseName, size, "Открытие кейса Проклятие");
        case 13: format(caseName, size, "Открытие кейса Зимняя сказка");
    }
}

#define SECONDS_IN_A_DAY 86400

new daily_reset_str[2048];
new tempst[128];
new queryst[2048];

public: CheckReset()
{
    new currentTime = gettime(); 
    new timeDifference = currentTime - daily_timer; 

    new secondsInDay = SECONDS_IN_A_DAY;
    new daysPassed = timeDifference / secondsInDay;

    new day = MonthDailyReset();

    if(daysPassed >= day)
    {
        daily_reset_str[0] = '\0';

        for(new i = 0; i < MAX_DAILY; i++)
        {
            format(tempst, sizeof(tempst), "%s=0, %s=0, %s=0%s",
                daily_item_db_keys[i],
                daily_open_db_keys[i],
                daily_type_db_keys[i],
                (i < MAX_DAILY - 1) ? ", " : ""
            );
            strcat(daily_reset_str, tempst, sizeof(daily_reset_str));
        }

        format(queryst, sizeof(queryst), "UPDATE daily_rewards_players SET %s", daily_reset_str);
        mysql_tquery(mysql, queryst);

        mysql_tquery(mysql, "UPDATE accounts_canvasdev SET daily_claim_7=0, daily_claim_14=0, daily_claim_21=0, daily_claim_28=0, daily_case_7_id=0, daily_case_14_id=0, daily_case_21_id=0, daily_case_28_id=0, daily_complete=0");

        for(new playerid = 0; playerid < MAX_PLAYERS; playerid++) 
        {
            if(IsPlayerConnected(playerid)) 
            {
                for(new i = 0; i < MAX_DAILY; i++)
                {
                    g_player_daily_items[playerid][i] = 0;
                    g_player_daily_open[playerid][i] = 0;
                    g_player_daily_type[playerid][i] = 0;
                }

                SetPlayerData(playerid, P_DAILY_CASE_7_ID, 0);
                SetPlayerData(playerid, P_DAILY_CASE_14_ID, 0);
                SetPlayerData(playerid, P_DAILY_CASE_21_ID, 0);
                SetPlayerData(playerid, P_DAILY_CASE_28_ID, 0);
                SetPlayerData(playerid, P_DAILY_CLAIM_7, 0);
                SetPlayerData(playerid, P_DAILY_CLAIM_14, 0);
                SetPlayerData(playerid, P_DAILY_CLAIM_21, 0);
                SetPlayerData(playerid, P_DAILY_CLAIM_28, 0);
                SetPlayerData(playerid, P_DAILY_CLAIM_COMPLETE, 0);
            }
        }

        format(tempst, sizeof(tempst), "UPDATE server_config SET time_daily = %d", currentTime);
        mysql_tquery(mysql, tempst);

        daily_timer = currentTime;

        printf("[DAILY RESET] Сброс ежедневных наград выполнен. Обновлён таймер: %d", currentTime);
    }
}

stock DailyClaimReward()
{
	new fmt_msg[248];
    format(fmt_msg, sizeof fmt_msg, "UPDATE accounts_canvasdev SET daily_claim = 0");
    mysql_tquery(mysql, fmt_msg);

	for(new playerid = 0; playerid < MAX_PLAYERS; playerid++) 
	{
        if(IsPlayerConnected(playerid)) 
		{
            SetPlayerData(playerid, P_DAILY_CLAIM, 0);

            DailyreWards_Time[playerid] = 7200;
		}
    }
    return 1;
}

stock MonthDaily()
{
    new year, month, day;
    getdate(year, month, day);

    switch(month)
    {
        case 1: return 0;   // Январь
        case 2: return 1;   // Февраль
        case 3: return 2;   // Март
        case 4: return 3;   // Апрель
        case 5: return 4;  // Май
        case 6: return 5;   // Июнь
        case 7: return 6;  // Июль
        case 8: return 7;   // Август
        case 9: return 8;   // Сентябрь
        case 10: return 9;  // Октябрь
        case 11: return 10; // Ноябрь
        case 12: return 11;  // Декабрь
    }
	return 1;
}

stock MonthDailyReset()
{
    new year, month, day;
    getdate(year, month, day);

    switch(month)
    {
        case 1: return 31;   // Январь
        case 2: return 28;   // Февраль
        case 3: return 31;   // Март
        case 4: return 30;   // Апрель
        case 5: return 31;  // Май
        case 6: return 30;   // Июнь
        case 7: return 31;  // Июль
        case 8: return 31;   // Август
        case 9: return 30;   // Сентябрь
        case 10: return 31;  // Октябрь
        case 11: return 30; // Ноябрь
        case 12: return 31;  // Декабрь
    }
	return 1;
}

stock LoadPlayerDaily(playerid)
{
	mysql_string[0] = EOS;
	format(mysql_string, sizeof mysql_string, "SELECT * FROM daily_rewards_players WHERE uid=%d LIMIT 1", GetPlayerAccountID(playerid));
	mysql_pquery(mysql, mysql_string, "CB_DailyRewards", "i", playerid);
}

public: CB_DailyRewards(playerid)
{
	if(cache_num_rows())
	{
		new fieldName[32];
        for(new i = 0; i < 28; i++)
        {
            format(fieldName, sizeof(fieldName), "daily_items_%d", i+1);
            g_player_daily_items[playerid][i] = cache_get_field_content_int(0, fieldName);

            format(fieldName, sizeof(fieldName), "daily_open_%d", i+1);
            g_player_daily_open[playerid][i] = cache_get_field_content_int(0, fieldName);

            format(fieldName, sizeof(fieldName), "daily_type_%d", i+1);
            g_player_daily_type[playerid][i] = cache_get_field_content_int(0, fieldName);
        }
	}
	else
	{
        format(mysql_string, sizeof mysql_string,
            "INSERT INTO `daily_rewards_players` (\
                `uid`, \
                `daily_items_1`, `daily_open_1`, `daily_type_1`, \
                `daily_items_2`, `daily_open_2`, `daily_type_2`, \
                `daily_items_3`, `daily_open_3`, `daily_type_3`, \
                `daily_items_4`, `daily_open_4`, `daily_type_4`, \
                `daily_items_5`, `daily_open_5`, `daily_type_5`, \
                `daily_items_6`, `daily_open_6`, `daily_type_6`, \
                `daily_items_7`, `daily_open_7`, `daily_type_7`, \
                `daily_items_8`, `daily_open_8`, `daily_type_8`, \
                `daily_items_9`, `daily_open_9`, `daily_type_9`, \
                `daily_items_10`, `daily_open_10`, `daily_type_10`, \
                `daily_items_11`, `daily_open_11`, `daily_type_11`, \
                `daily_items_12`, `daily_open_12`, `daily_type_12`, \
                `daily_items_13`, `daily_open_13`, `daily_type_13`, \
                `daily_items_14`, `daily_open_14`, `daily_type_14`, \
                `daily_items_15`, `daily_open_15`, `daily_type_15`, \
                `daily_items_16`, `daily_open_16`, `daily_type_16`, \
                `daily_items_17`, `daily_open_17`, `daily_type_17`, \
                `daily_items_18`, `daily_open_18`, `daily_type_18`, \
                `daily_items_19`, `daily_open_19`, `daily_type_19`, \
                `daily_items_20`, `daily_open_20`, `daily_type_20`, \
                `daily_items_21`, `daily_open_21`, `daily_type_21`, \
                `daily_items_22`, `daily_open_22`, `daily_type_22`, \
                `daily_items_23`, `daily_open_23`, `daily_type_23`, \
                `daily_items_24`, `daily_open_24`, `daily_type_24`, \
                `daily_items_25`, `daily_open_25`, `daily_type_25`, \
                `daily_items_26`, `daily_open_26`, `daily_type_26`, \
                `daily_items_27`, `daily_open_27`, `daily_type_27`, \
                `daily_items_28`, `daily_open_28`, `daily_type_28`\
            ) VALUES (\
                %d, \
                0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, \
                0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, \
                0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, \
                0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, \
                0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, \
                0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, \
                0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0)", 
            GetPlayerAccountID(playerid)
        );
        mysql_pquery(mysql, mysql_string);
	}
}


