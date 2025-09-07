#if defined _settings_included
    #endinput
#endif
#define _settings_included

#define MAX_SETTINGS 14

#define SAFE_MODE_URL "https://hassle.fra1.cdn.digitaloceanspaces.com/banned-words/words.json"

enum
{
    SET_ORG_CHAT,
    SET_NAMES_ABOVE,
    SET_NAMES_CHAT,
    SET_IDS_CHAT,
    SET_BOOMBOX_SOUND,
    SET_CASINO_MUSIC,
    SET_KILL_LIST,
    SET_SHOW_CONTROLS,
    SET_HEALTH_EFFECTS,
    SET_PROPERTY_INFO,
    SET_CHAT_FADEOUT,
    SET_HUD_NUMBERS,
    SET_CHAT_ANNOUNCEMENTS,
    SET_SAFE_MODE
};

new g_player_settings_sql[MAX_PLAYERS][MAX_SETTINGS];

enum setting_entry
{
    setting_title[64],         // Название настройки
    setting_index,             // Индекс для интерфейса
    setting_sql_id,            // Индекс
    setting_description[356],  // Подробное описание для интерфейса
};

new const settings[MAX_SETTINGS][setting_entry] =
{
    {"Чат организации",              0, SET_ORG_CHAT, "Этот параметр управляет отображением чата организации, в которой вы находитесь"},
    {"Ники над игроками",           1, SET_NAMES_ABOVE, "Настройка позволяет отображать имена персонажей (никнеймы) и полоску здоровья, название семьи/банды над моделями персонажей в игровом мире."},
    {"Ники в чате",                 2, SET_NAMES_CHAT, "Настройка позволяет отображать имена персонажей в игровом чате."},
    {"ID игроков в чате",           3, SET_IDS_CHAT, "Параметр отвечает за отображение идентификатора (ID) игроков в чате"},
    {"Музыка бумбокса/сабвуфера",   4, SET_BOOMBOX_SOUND, "Отключить/включить музыку из бумбокса или сабвуфера"},
    {"Музыка в казино",             6, SET_CASINO_MUSIC, "Актививрует фоновый звук в казино"},
    {"Классический Kill-List",      7, SET_KILL_LIST, "Активация стандартного списка убийств на захвате территории"},
    {"Подсказка кнопок управления", 8, SET_SHOW_CONTROLS, "Скрывает кнопки управления под чатом"},
    {"Эффекты изменения здоровья",  9, SET_HEALTH_EFFECTS, "При изменении здоровья отображаются визуальные эффекты: красные вспышки сигнализируют об уроне, а зеленые – о восстановлении здоровья. Эти эффекты помогают быстрее ориентироваться в боевой ситуации"},
    {"Информация о недвижимости",  10, SET_PROPERTY_INFO, "Предоставляет детальную информацию о недвижимости на входной точке"},
    {"Затухание чата",             14, SET_CHAT_FADEOUT, "Функция, которая делает чат полупрозрачным при отсутствии новых сообщений. Это освобождает экран от лишних элементов, сохраняя возможность видеть чат при необходимости."},
    {"Отображение чисел в худе",   15, SET_HUD_NUMBERS, "Показывает точные цифровые значения здоровья, брони и уровня сытости на экране. Удобно для контроля состояния персонажа в любой момент"},
    {"Объявления в чате",          21, SET_CHAT_ANNOUNCEMENTS, "Настройка скрывает объявления от игроков в чате"},
    {"Безопасный режим",           22, SET_SAFE_MODE, "При включении безопасного режима Вы будете защищены от нежелательных сообщений, содержащих рекламу/ассоциальное поведение."}
};

stock SettingsInterface(playerid)
{
    new entry[512];
    
    STRING_GLOBAL[0] = EOS;

    format(STRING_GLOBAL, sizeof STRING_GLOBAL,
        "interface('MainMenu').onServerResponse(10, '[\
        [0,\"Электронная почта\",0,\"%s\",1,5,0],\
        [0,\"Сменить пароль\",1,\"\",0,9,0],\
        [0,\"Настройки безопасности\",2,\"\",0,8,0],\
        [0,\"Сменить NonRP ник\",3,\"\",0,6,0],\
        [0,\"Привязать Telegram\",4,\"\",0,7,0],\
        [0,\"Привязать/Отвязать Google Authenticator\",5,\"\",0,0,0,\"\",\"Привязать двухфакторную аутентификацию/Отвязать двухфакторную аутентификацию\"],",
        GetPlayerData(playerid, P_EMAIL)
    );

    for(new i = 0; i < MAX_SETTINGS; i++)
    {
        format(entry, sizeof entry,
            "[1,\"%s\",%d,\"[0,1]\",%d,1,0,\"\",\"%s\"]%s",
            settings[i][setting_title],
            settings[i][setting_index],
            g_player_settings_sql[playerid][ settings[i][setting_sql_id] ],
            settings[i][setting_description],
            (i + 1 < MAX_SETTINGS) ? "," : ""
        );
        strcat(STRING_GLOBAL, entry);
    }

    strcat(STRING_GLOBAL, "]')");
    CEF_CREATE(playerid, 1, 2, STRING_GLOBAL);
    return 1;
}

stock settings_type(event)
{
    switch(event)
	{
		case 0: return SET_ORG_CHAT;
		case 1: return SET_NAMES_ABOVE;
		case 2: return SET_NAMES_CHAT;
		case 3: return SET_IDS_CHAT;
		case 4: return SET_BOOMBOX_SOUND;
		case 6: return SET_CASINO_MUSIC;
		case 7: return SET_KILL_LIST;
		case 8: return SET_SHOW_CONTROLS;
		case 9: return SET_HEALTH_EFFECTS;
		case 10: return SET_PROPERTY_INFO;
		case 14: return SET_CHAT_FADEOUT;
		case 15: return SET_HUD_NUMBERS;
		case 21: return SET_CHAT_ANNOUNCEMENTS;
		case 22: return SET_SAFE_MODE;
	}
    return INVALID_RETURN;
}

stock PlayerSetting_OnPlayerRequest(playerid, event, status)
{
    new string_settings[256];
    string_settings[0] = EOS;

    switch(event)
	{
		case 1:
		{
			if(status == 0) 
		        CEF_CREATE(playerid, 1, 2, "window.setDrawLabelTrueStateBlocker(true)");
            else{
		        CEF_CREATE(playerid, 1, 2, "window.setDrawLabelTrueStateBlocker(false)"); 
		        CEF_CREATE(playerid, 1, 2, "window.setDrawLabelStatus(false)");
		    }
		}
		case 8:
		{
			format(string_settings, sizeof string_settings, "interface('Hud').setShowControls(%d)", status);
		}
		case 9:
		{
			format(string_settings, sizeof string_settings, "interface('Hud').setEffectEnabled(%d)", status);
		}
		case 14:
		{
			format(string_settings, sizeof string_settings, "interface('Hud').setCanChatFadeout(%d)", status);
		}
		case 15:
		{
			format(string_settings, sizeof string_settings, "interface('Hud').setInfoValuesVisible(%d)", status);
		}
		case 22:
		{
            if(status == 0 || status == 1)
            {
                new updateType = (status == 1) ? 2 : 1;
                format(string_settings, sizeof string_settings, "window.updateConfigurationBannedMessage(%d, \"%s\")", updateType, SAFE_MODE_URL);
			}
		}
	}

    if(string_settings[0] != EOS && event != 1)
    {
        CEF_CREATE(playerid, 1, 2, string_settings);
    }

    new type = settings_type(event);
    if(type != -1)
    {
        g_player_settings_sql[playerid][type] = status;
        UpdateSinglePlayerSetting(playerid, type);
    }
    return 1;
}

stock UpdateSinglePlayerSetting(playerid, index_st)
{
    if(index_st < 0 || index_st >= MAX_SETTINGS) return;

    new query[128];
    format(query, sizeof query, "UPDATE player_settings SET player_settings_%d = %d WHERE uid = %d", index_st + 1, g_player_settings_sql[playerid][index_st], GetPlayerAccountID(playerid));
    mysql_pquery(mysql, query);
}

stock PlayerSetting_OnPlayerButton(playerid, number_call_event)
{
    switch(number_call_event){
		case 5:{ 
			if(GetPlayerData(playerid, P_2FA_ENABLED) != 1){IntfDialogCallRemote(playerid, DIALOG_ACTIVATE_2FA, DIALOG_STYLE_MSGBOX, "Безопасность аккаунта", "{EBEBEB}Вы действительно хотите {00CC66}привязать{EBEBEB} Google Authenticator к вашему аккаунту?", "Да", "Нет");}
			else{IntfDialogCallRemote(playerid, DIALOG_DEACTIVATE_2FA, DIALOG_STYLE_MSGBOX, "Безопасность аккаунта", "{EBEBEB}Вы действительно хотите {CC0000}отвязать{EBEBEB} Google Authenticator от аккаунта?", "Да", "Нет");}
		}
	}
	return 1;
}

stock LoadPlayerSettings(playerid)
{
	mysql_string[0] = EOS;
	format(mysql_string, sizeof mysql_string, "SELECT * FROM player_settings WHERE uid=%d LIMIT 1", GetPlayerAccountID(playerid));
	mysql_pquery(mysql, mysql_string, "CB_Settings", "i", playerid);
}

public: CB_Settings(playerid)
{
	if(cache_num_rows())
	{
		new fieldName[32];
        for(new i = 0; i < MAX_SETTINGS; i++)
        {
            format(fieldName, sizeof(fieldName), "player_settings_%d", i+1);
            g_player_settings_sql[playerid][i] = cache_get_field_content_int(0, fieldName);
        }

		UpdateSettingsInterface(playerid);
	}
	else
	{
        new const default_settings[MAX_SETTINGS] = {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0};

        new query[512], values[256];
        format(query, sizeof query, "INSERT INTO player_settings (uid");

        for(new i = 0; i < MAX_SETTINGS; i++)
        {
            format(query, sizeof query, "%s, player_settings_%d", query, i + 1);
            format(values, sizeof values, "%s%d%s", values, default_settings[i], (i + 1 < MAX_SETTINGS) ? "," : "");
        }

        format(query, sizeof query, "%s) VALUES (%d,%s)", query, GetPlayerAccountID(playerid), values);
        mysql_pquery(mysql, query);
	}
}

stock UpdateSettingsInterface(playerid)
{
    new buffer[256];

	if(g_player_settings_sql[playerid][SET_NAMES_ABOVE] == 0) 
		CEF_CREATE(playerid, 1, 2, "window.setDrawLabelTrueStateBlocker(true)");
    else{
		CEF_CREATE(playerid, 1, 2, "window.setDrawLabelTrueStateBlocker(false)"); 
		CEF_CREATE(playerid, 1, 2, "window.setDrawLabelStatus(false)");
	}

	format(buffer, sizeof buffer, "interface('Hud').setShowControls(%d)", g_player_settings_sql[playerid][SET_SHOW_CONTROLS]);
    CEF_CREATE(playerid, 1, 2, buffer);

	format(buffer, sizeof buffer, "interface('Hud').setEffectEnabled(%d)", g_player_settings_sql[playerid][SET_HEALTH_EFFECTS]);
    CEF_CREATE(playerid, 1, 2, buffer);

	format(buffer, sizeof buffer, "interface('Hud').setCanChatFadeout(%d)", g_player_settings_sql[playerid][SET_CHAT_FADEOUT]);
    CEF_CREATE(playerid, 1, 2, buffer);

	format(buffer, sizeof buffer, "interface('Hud').setInfoValuesVisible(%d)", g_player_settings_sql[playerid][SET_HUD_NUMBERS]);
    CEF_CREATE(playerid, 1, 2, buffer);

	new safeMode = g_player_settings_sql[playerid][SET_SAFE_MODE];
    if(safeMode == 0 || safeMode == 1)
    {
        new updateType = (safeMode == 1) ? 2 : 1;
        format(buffer, sizeof buffer, "window.updateConfigurationBannedMessage(%d, \"https://hassle.fra1.cdn.digitaloceanspaces.com/banned-words/words.json\")", updateType);
        CEF_CREATE(playerid, 1, 2, buffer);
    }
}
