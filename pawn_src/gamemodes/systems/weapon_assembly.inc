#if defined _weapon_assembly_included
    #endinput
#endif
#define _weapon_assembly_included

new AmmoAssemblyType[MAX_PLAYERS];
new AssemblyComplete[MAX_PLAYERS];

new const AmmoAssembly[][] =
{
    "",
    "7.62x39",
    ".44 Magnum",
    "5.56x39",
    "12x70"
};

public: WeaponAssemb_OnCloseInterface(playerid)
{
    AmmoAssemblyType[playerid] = 0;
    ClearPlayerAnim(playerid);
    GameText(playerid, "~r~Неудача", 3000, 2);
    SendClientMessage(playerid, COLOR_WHITE, "Вы не смогли произвести продукцию");
}

public: WeaponAssemb_OnPlayerEnd(playerid)
{
    GameText(playerid, "~g~Успешно", 3000, 2);

    new fmt_text[148];
    format(fmt_text, sizeof fmt_text, "{FF8000} Вы успешно произвели {ffffff} `Патроны (%s)` (1 шт.){FF8000}, отнесите продукцию на {ffffff} главный склад", AmmoAssembly[AmmoAssemblyType[playerid]]);
	SendClientMessage(playerid, 0xB8CEF6FF, fmt_text);

    SetPlayerAttachedObject(playerid, 3, 2969, 6, 0.06, 0.08, -0.23, -105.60, 1.20, -90.40, 1.00, 1.00, 1.00);

    AssemblyComplete[playerid] = 1;

    ApplyAnimationEx(playerid, "CARRY", "crry_prtial", 4.1, 1, 1, 1, 1, 1, 0, USE_ANIM_TYPE_NONE - 1);
	return 1;
}

stock SkladAssembly(playerid)
{
    if(AssemblyComplete[playerid] == 0) return 0;

    new fmt_text[148];
    format(fmt_text, sizeof fmt_text, "{FF8000} Вы {ffffff} успешно {FF8000} положили изготовленный предмет {ffffff} `Патроны (%s)`(1 шт.) {FF8000} на главный склад", AmmoAssembly[AmmoAssemblyType[playerid]]);
	SendClientMessage(playerid, 0xB8CEF6FF, fmt_text);

    ApplyAnimationEx(playerid, "CARRY", "PUTDWN", 4.0, 0, 0, 0, 0, 0, 0, USE_ANIM_TYPE_NONE);
    RemovePlayerAttachedObject(playerid, 3);

    AmmoAssemblyType[playerid] = 0;
    AssemblyComplete[playerid] = 0;

    ModifyCashBalance(playerid, 50000, "WeaponAssembly", true, true);
    GiveRandCase(playerid);

    return 1;
}

stock AltAssembly(playerid)
{
    if(IsPlayerInRangeOfPoint(playerid, 1.0, -1596.4178,-634.2460,1016.4700) || 
    IsPlayerInRangeOfPoint(playerid, 1, -1597.1029,-636.3106,1016.4700) ||
    IsPlayerInRangeOfPoint(playerid, 1, -1603.0717,-639.7767,1016.4700))
	{
        if(AssemblyComplete[playerid] != 1)
        {
            new type = RandomEx(1, 5);

            switch(type){
		        case 1: CEF_CREATE(playerid, 2, 4, "WeaponAssembly", "[2]");
		        case 2: CEF_CREATE(playerid, 2, 4, "WeaponAssembly", "[0]");
		        case 3: CEF_CREATE(playerid, 2, 4, "WeaponAssembly", "[1]");
		        case 4: CEF_CREATE(playerid, 2, 4, "WeaponAssembly", "[3]");
		    }

            AmmoAssemblyType[playerid] = type;
            ApplyAnimationEx(playerid, "OTB", "betslp_loop", 4.1, 1, 0, 0, 1, 1, 1, USE_ANIM_TYPE_NONE - 1);
        }
		else
		{
			SendClientMessage(playerid, COLOR_RED, "{FF0000} Отнесите готовую продукцию на {ffffff} главный склад");
			GameText(playerid, "~r~Ошибка", 3000, 2);
		}
	}
    return 1;
}

stock TextAssemblyInt()
{
    CreateDynamic3DTextLabel("{FC7121}Склад\nДенег в предприятии: {3DF22B}0 руб\n{FC7121}Выплата за производство шт: {3DF22B}50000 руб\n{FC7121}Выплата за системное производство шт: {3DF22B}50000 руб", 0xFFFFFFFF, -1602.51, -629.67, 1017.17, 13.0);//Оружие
    
    CreatePickup(1210, 23, -1602.51, -629.67, 1017.17 - 1.0, -1, -1);
}