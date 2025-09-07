#if defined _dayving_included
    #endinput
#endif
#define _dayving_included

#define MAX_ZONE_DAYVING 2
#define DAYVING_ZONE_RADIUS 500.0

new dayving_zone[MAX_ZONE_DAYVING];

new const Float:dayving_zone_cord[2][3] = {{938.4370,4534.8887,31.6347}, {3560.0432,962.5114,31.4521}};

enum E_DIVING_CHEST_STRUCT
{
	Float: E_POS[3],
	E_OBJECT,
	Text3D: E_LABEL,
	E_STATUS,
	E_TIMER,
	E_INTERACTION,
}

new const diving_chest[][E_DIVING_CHEST_STRUCT] =
{
    {{873.616, 4500.19, -11.558}},
	{{849.186, 4517.52, -17.4392}},
	{{854.493, 4562.61, -17.1475}},
	{{885.592, 4616.83, -19.9283}},
	{{905.284, 4620.38, -18.1728}},
	{{978.937, 4570.58, -12.0472}},
    {{975.447, 4618.59, -21.1197}},
    {{1009.58, 4566.72, -14.7724}},
    {{1009.81, 4516.56, -11.3142}},
    {{985.742, 4473.67, -9.05904}},
    {{1011.85, 4475.95, -13.2064}},
    {{1011.84, 4448.02, -17.7671}},
    {{921.331, 4441.38, -12.284}},
    {{931.069, 4431.62, -14.8451}},
    {{955.67, 4443.77, -9.82583}},
    {{982.943, 4429.63, -18.1612}},
    {{896.122, 4452.66, -11.7656}},
    {{850.397, 4481.22, -15.9946}},
    {{819.366, 4499.03, -24.1109}},
    {{832.78, 4549.21, -19.8384}},
    {{854.846, 4591.71, -17.5381}},
    {{903.915, 4605.56, -17.4038}},
    {{987.544, 4598.16, -16.4798}}
};

stock DayvingInit()
{
    for(new i; i < sizeof(diving_chest); i++)
	{
		diving_chest[i][E_OBJECT] = CreateDynamicObject(16500, diving_chest[i][E_POS][0], diving_chest[i][E_POS][1], diving_chest[i][E_POS][2], 0.0, 0.0, 0.0);
		diving_chest[i][E_LABEL] = CreateDynamic3DTextLabel("Сундук", 0xFF7A00FF, diving_chest[i][E_POS][0], diving_chest[i][E_POS][1], diving_chest[i][E_POS][2], 5.0);
		diving_chest[i][E_STATUS] = 1;
		diving_chest[i][E_TIMER] = -1;
		diving_chest[i][E_INTERACTION] = CreateDynamicSphere(diving_chest[i][E_POS][0], diving_chest[i][E_POS][1], diving_chest[i][E_POS][2], 4.0, -1, -1);
	}

    for(new i = 0; i < MAX_ZONE_DAYVING; i++)
    {
        dayving_zone[i] = CreateDynamicSphere(dayving_zone_cord[i][0],dayving_zone_cord[i][1],dayving_zone_cord[i][2], DAYVING_ZONE_RADIUS);
    }
}

stock ChestUse(playerid)
{
    for(new i; i < sizeof(diving_chest); i++)
    {
        if(!IsPlayerInRangeOfPoint(playerid, 2.5, diving_chest[i][E_POS][0], diving_chest[i][E_POS][1], diving_chest[i][E_POS][2])) continue;

		if(diving_chest[i][E_STATUS] == 0) return 0;
		if(GetInventorySlots(playerid) == -1) return GameText(playerid, "~r~В вашем инвентаре~n~нет свободного места", 3000, 2);

		if(GetPlayerSkin(playerid) != 15576) return SendClientMessage(playerid, COLOR_RED, "Вы должны быть в костюме водолаза");
		
		Progress_Bar_Menu(playerid, 3, 5, 5);
    }
    return 1;
}

stock ItemDayving(playerid)
{
    new const Dayving_Item[18] = {286, 124, 111, 112, 113, 114, 320, 148, 312, 313, 107, 317, 61, 62, 123, 223, 226};

    new rand = RandomEx(0, sizeof(Dayving_Item) - 1);

    GiveIteam(playerid, Dayving_Item[rand], 1, 1, 0);
    SCMF(playerid, 0xFFD700FF, "{ecf96a}[{ffffff}Сундук{ecf96a}]{ecf96a} Вы нашли {ffffff}%s (1 шт.), {ecf96a}он добавлен в Ваш инвентарь.", ItemsInfo[Dayving_Item[rand]][i_item_name]);
    
    UpdateSkinWearAsync();
    return 1;
}

#define OXYGEN_UPDATE_INTERVAL 5000

stock SetPlayerOxygen(playerid, Float:oxygen)
{
    new tick = GetTickCount();
    new lastTick = GetPVarInt(playerid, "OxygenTick");

    if(tick - lastTick < OXYGEN_UPDATE_INTERVAL) return;

    new str[128];
    format(str, sizeof(str), "window.setPlayerOxygen(%f);", oxygen);
    CEF_CREATE(playerid, 1, 2, str);
    SetPVarInt(playerid, "OxygenTick", tick);
}