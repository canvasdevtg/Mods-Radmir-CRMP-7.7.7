#if defined _mysql_included
    #endinput
#endif
#define _mysql_included

#define SERVER_NAME         "RedAge Online"
#define SERVER_ID 	        "Сервер: 01" 
#define SERVER_SITE         ""
#define SERVER_DONATE       "DCOINS"
#define SERVER_TELEGRAM     "t.me/canvasdevtg"
#define SERVER_NUMBER_CARSH "REDAGE"
#define SERVER_MAP_NAME 	"RedAge Online"
#define SERVER_VERSION		"RD - 1 Server v7.7.7"
#define SERVER_COLOR		"ffff00"

#define SERVER 1 // Номер сервера

#define SERVER_HUD_HELLOWEEN 0
#define SERVER_HUD_NEW_YEAR 0
#define SERVER_HUD_EASTER 0

new const authorizedIP[] = "";
new const authorizedPort = ;

#define RD_HOST "127..0.1"
#define RD_USER ""
#define RD_BD ""
#define RD_PASSWORD ""

new mysql;

stock ServerConfig(const bind[], port)
{
    if(!strcmp(bind, authorizedIP) && port == authorizedPort)
	{
		SendRconCommand("hostname  "SERVER_NAME" | "SERVER_ID"");
	    SendRconCommand("weburl "SERVER_SITE"");
	    SendRconCommand("mapname "SERVER_MAP_NAME"");

        SetGameModeText(""SERVER_VERSION"");

        mysql = mysql_connect(RD_HOST, RD_USER, RD_BD, RD_PASSWORD);
	}
    else
    {
        printf("[ERROR] Не подключена база данных");
        SendRconCommand("exit");
    }
    return 1;
}

