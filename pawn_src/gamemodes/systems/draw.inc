#if defined _draw_included
    #endinput
#endif
#define _draw_included

#define MAX_RAFFLESHOP 2
#define RAFFLE_HOURS 172800

enum E_RAFFLE_SHOP
{
	RS_ID,
	RS_VEHICLE,
	RS_STATUS,
	RS_AREA,
	RS_TIME,
	RS_TICKETS
};

new g_raffleShop[MAX_RAFFLESHOP][E_RAFFLE_SHOP];

new Float: g_pos_car_raffle[MAX_RAFFLESHOP][4] =
{
	{983.79860, 2801.5598, 1001.2399, 182.4524},
	{1014.5068, 2801.6160, 1001.2430, 178.9288}
};

enum E_INFO_RAFFLE_SHOPPING_STRUCT
{
	IRS_CAR_ID,
	IRS_PRICE
};

new g_info_raffleshopping[54][E_INFO_RAFFLE_SHOPPING_STRUCT] = 
{
	{400, 24000},
    {402, 24000},
    {409, 24000},
    {410, 24000},
    {419, 24000},
    {421, 24000},
    {429, 24000},
    {436, 24000},
    {445, 24000},
    {451, 24000},
    {458, 24000},
    {461, 24000},
    {462, 24000},
    {463, 24000},
    {466, 24000},
    {468, 24000},
    {475, 24000},
    {477, 24000},
    {480, 24000},
    {489, 24000},
    {490, 24000},
    {491, 24000},
    {495, 24000},
    {494, 24000},
    {502, 24000},
    {503, 24000},
    {506, 24000},
    {505, 24000},
    {507, 24000},
    {515, 24000},
    {516, 24000},
    {534, 24000},
    {536, 24000},
    {543, 24000},
    {551, 24000},
    {550, 24000},
    {559, 24000},
    {560, 24000},
    {612, 24000},
    {999, 24000},
    {909, 24000},
    {795, 24000},
    {796, 24000},
    {797, 24000},
    {908, 24000},
    {907, 24000},
    {15065, 24000},
    {15066, 24000},
    {15068, 24000},
    {15069, 24000},
    {15071, 24000},
    {15076, 24000},
    {15085, 24000},
    {15107, 24000}
};

stock CreateRaffleShopping()
{
	for(new i; i < sizeof g_raffleShop; i++)
	{
		if(g_raffleShop[i][RS_ID] == -1) 
			g_raffleShop[i][RS_ID] = random(53);

		g_raffleShop[i][RS_AREA] = CreateDynamicSphere(g_pos_car_raffle[i][0],g_pos_car_raffle[i][1],g_pos_car_raffle[i][2],4.5,-1,-1);
		
		if(g_raffleShop[i][RS_TIME] == 0) 
			g_raffleShop[i][RS_TIME] = gettime() + RAFFLE_HOURS;

		g_raffleShop[i][RS_STATUS] = 1;

        if(g_raffleShop[i][RS_VEHICLE] != INVALID_VEHICLE_ID)
        {
            DestroyVehicle(g_raffleShop[i][RS_VEHICLE]);
            g_raffleShop[i][RS_VEHICLE] = INVALID_VEHICLE_ID;
        }
		
		g_raffleShop[i][RS_VEHICLE] = CreateVehicle(
			g_info_raffleshopping[g_raffleShop[i][RS_ID]][IRS_CAR_ID],
			g_pos_car_raffle[i][0],
			g_pos_car_raffle[i][1],
			g_pos_car_raffle[i][2],
			g_pos_car_raffle[i][3],
			1,
			1,
			-1,
			0,
			VEHICLE_ACTION_TYPE_RAFFLE_SHOP,
			i
		);

		SetVehicleVirtualWorld(g_raffleShop[i][RS_VEHICLE], 9);
		LinkVehicleToInterior(g_raffleShop[i][RS_VEHICLE], 9);

		new query[148];
		mysql_format(mysql, query, sizeof query, "UPDATE server_config SET id_raffleshopping_%d='%d', time_raffleshopping_%d='%d' LIMIT 1", i + 1, g_raffleShop[i][RS_ID], i + 1, g_raffleShop[i][RS_TIME]);
		mysql_query(mysql, query, false);
	}
}

stock timeRaffleShopping()
{
	for(new i; i < sizeof g_raffleShop; i++)
	{
		if(g_raffleShop[i][RS_STATUS] != 1) 
			continue;

		new Float: x, Float: y, Float: z;
		GetVehiclePos(g_raffleShop[i][RS_VEHICLE], x, y, z);

		if(x != g_pos_car_raffle[i][0] || y != g_pos_car_raffle[i][1])
		{
			SetVehiclePos(g_raffleShop[i][RS_VEHICLE], g_pos_car_raffle[i][0],g_pos_car_raffle[i][1],g_pos_car_raffle[i][2] + 0.1);
			SetVehicleZAngle(g_raffleShop[i][RS_VEHICLE], g_pos_car_raffle[i][3]);

			SetVehicleVirtualWorld(g_raffleShop[i][RS_VEHICLE], 9);
			LinkVehicleToInterior(g_raffleShop[i][RS_VEHICLE], 9);
		}

		if(g_raffleShop[i][RS_TIME] < gettime())
        {
            new fmt_text[256], Cache: result, prize_name[128];

            mysql_format(mysql, fmt_text, sizeof fmt_text, "SELECT * FROM raffle_shop WHERE type=%d", i);
            result = mysql_query(mysql, fmt_text, true);

            new rows = cache_num_rows();

            if(!rows) return cache_delete(result);
            
            new random_win = random(rows);
            new owner_id = cache_get_field_content_int(random_win, "owner_id");

            cache_delete(result);

            format(prize_name, sizeof prize_name, "%s [№%d]", GetVehicleInfo(g_info_raffleshopping[g_raffleShop[i][RS_ID]][IRS_CAR_ID], VI_NAME), g_info_raffleshopping[g_raffleShop[i][RS_ID]][IRS_CAR_ID]);
            format(fmt_text, sizeof fmt_text, "INSERT INTO prizes (owner_id, name, size, item, type, count, indx) VALUES (%d, '%s', %d, %d, %d, %d, %d)", owner_id, prize_name, 3, g_info_raffleshopping[g_raffleShop[i][RS_ID]][IRS_CAR_ID], 0, 1, -1);
            mysql_tquery(mysql, fmt_text, "", "");

            CreatePlayerNotification(owner_id, "Выигрыш в розыгрыше", "Вы выиграли в розыгрыше автомобиля.\nОн находится в Мои награды");

            format(fmt_text, sizeof fmt_text, "DELETE FROM raffle_shop WHERE type=%d", i);
            mysql_query(mysql, fmt_text, false);

            g_raffleShop[i][RS_TIME] = 0;
            g_raffleShop[i][RS_ID] = -1;

            if(g_raffleShop[i][RS_VEHICLE] != INVALID_VEHICLE_ID)
            {
                DestroyVehicle(g_raffleShop[i][RS_VEHICLE]);
                g_raffleShop[i][RS_VEHICLE] = INVALID_VEHICLE_ID;
            }

            g_raffleShop[i][RS_STATUS] = 0;

            CreateRaffleShopping();
        }
	}
    return 1;
}

stock GetBoughtTickets(raffle_type, owner_id)
{
    new query[256];
    format(query, sizeof(query), "SELECT COUNT(*) AS ticket_count FROM raffle_shop WHERE type=%d AND owner_id=%d", raffle_type, owner_id);

    new Cache: result = mysql_query(mysql, query, true);
    if(!result) return 0;

    new tickets = cache_get_field_content_int(0, "ticket_count");
    cache_delete(result);

    return tickets;
}

stock FormatTicketsCount(count, buffer[], maxlen)
{
    format(buffer, maxlen, "%d {FFFFFF}%s", count, ((count % 100) >= 11 && (count % 100) <= 14) ? "билетов" : ((count % 10) == 1) ? "билет" : ((count % 10) >= 2 && (count % 10) <= 4) ? "билета" : "билетов");
}

stock openRaffleShop(playerid)
{
	for(new i; i < sizeof g_raffleShop; i++)
	{
		if(!IsPlayerInRangeOfPoint(playerid, 4.5, g_pos_car_raffle[i][0],g_pos_car_raffle[i][1],g_pos_car_raffle[i][2])) 
			continue;

		string_dialog[0] = EOS;

        new raffle_time = g_raffleShop[i][RS_TIME] - gettime();

        new hours = raffle_time / 3600;
        new minutes = (raffle_time % 3600) / 60;

        new tickets = GetBoughtTickets(i, GetPlayerAccountID(playerid));

        new ticket_str[32];
        FormatTicketsCount(tickets, ticket_str, sizeof ticket_str);

		format
		(
			string_dialog, sizeof string_dialog, 
			"{FFFFFF}На данный момент розыгрывается {fdc53c}%s\n\
			{FFFFFF}В конце розыгрыша один из участников случайным образом станет победителем и заберёт автомобиль.\n\n\
			{FFFFFF}До завершения осталось: {fdc53c}%d часов %d минут\n\
            {FFFFFF}Вы приобрели уже {fdc53c}%s участника розыгрыша\n\
			{FFFFFF}Вы готовы заплатить {fdc53c}%d руб. {FFFFFF}за участие?",
            GetVehicleInfo(g_info_raffleshopping[g_raffleShop[i][RS_ID]][IRS_CAR_ID], VI_NAME),
			hours, minutes, ticket_str, g_info_raffleshopping[g_raffleShop[i][RS_ID]][IRS_PRICE]
		);
		IntfDialogCallRemote(playerid, DIALOG_RAFFLE_SHOP, DIALOG_STYLE_MSGBOX, "{FFFFFF}Розыгрыш", string_dialog, "Да", "Нет");

		return true;
	}

	return true;
}

