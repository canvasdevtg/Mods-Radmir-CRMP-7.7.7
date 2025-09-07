#if defined _anti_cheat_included
    #endinput
#endif
#define _anti_cheat_included

stock IsWeaponAllowed(weaponid){
    switch(weaponid){
        case 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 17, 22, 23, 24,
        25, 26, 27, 28, 29, 30, 31, 32, 33, 
        34, 41, 42, 43, 44, 45, 46: return true;
    }
    return false;
}

stock IsWeaponAllowedInv(playerid, weaponid)
{
    if(IsWeaponAllowed(weaponid))
    {
        switch(weaponid)
        {
            case 1: return true;
            case 2: return true;
            case 3: return true;
            case 4: return true;
            case 5: return true;
            case 6: return true;
            case 7: return true;
            case 8: return true;
            case 9: return true;
            case 10: return true;
            case 11: return true;
            case 12: return true;
            case 13: return true;
            case 14: return true;
            case 15: return true;
            case 17: return true;
            case 23: return true;
            case 41: return true;
            case 42: return true;
            case 43: return true;
            case 44: return true;
            case 45: return true;
            case 46: return true;
            case 22: return (GetIteam(playerid, 12) > 0);
            case 24: return (GetIteam(playerid, 19) > 0);
            case 25: return (GetIteam(playerid, 14) > 0);
            case 26: return (GetIteam(playerid, 15) > 0);
            case 27: return (GetIteam(playerid, 16) > 0);
            case 28: return (GetIteam(playerid, 17) > 0);
            case 29: return (GetIteam(playerid, 18) > 0);
            case 30: return (GetIteam(playerid, 21) > 0);
            case 31: return (GetIteam(playerid, 20) > 0);
            case 33: return (GetIteam(playerid, 42) > 0);
            case 34: return (GetIteam(playerid, 22) > 0);
        }
    }
    return false;
}

stock GetAmmoCountFromInventory(playerid, weaponid)
{
    switch(weaponid)
    {
        case 1: return true;
        case 2: return true;
        case 3: return true;
        case 4: return true;
        case 5: return true;
        case 6: return true;
        case 7: return true;
        case 8: return true;
        case 9: return true;
        case 10: return true;
        case 11: return true;
        case 12: return true;
        case 13: return true;
        case 14: return true;
        case 15: return true;
        case 17: return true;
        case 23: return true;
        case 41: return true;
        case 42: return true;
        case 43: return true;
        case 44: return true;
        case 45: return true;
        case 46: return true;
        case 22: return GetIteam(playerid, 362);
        case 24: return GetIteam(playerid, 363);
        case 25: return GetIteam(playerid, 365);
        case 26: return GetIteam(playerid, 365);
        case 27: return GetIteam(playerid, 365);
        case 28: return GetIteam(playerid, 366);
        case 29: return GetIteam(playerid, 366);
        case 30: return GetIteam(playerid, 368);
        case 31: return GetIteam(playerid, 367);
        case 33: return GetIteam(playerid, 364);
        case 34: return GetIteam(playerid, 364);
    }
    return false;
}

stock DellInvalidWeapon(playerid)
{
	ResetPlayerWeapons(playerid);
    return true;
}

stock ShowCheatKickDialog(playerid) 
{
    DellInvalidWeapon(playerid);    
    return true;
}

new lastAmmo[MAX_PLAYERS];

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
    if(!IsWeaponTracked(weaponid)) return false;

    lastAmmo[playerid] = GetPlayerAmmo(playerid);

    SetTimerEx("SyncAmmoWithInventory", 50, false, "ii", playerid, weaponid);

    return true;
}

stock GetAmmoIDForWeapon(weaponid)
{
    switch(weaponid)
    {
        case 22: return 362;
        case 24: return 363;
        case 25, 26, 27: return 365;
        case 28, 29: return 366;
        case 30: return 368;
        case 31: return 367;
        case 33, 34: return 364;
    }
    return false;
}

stock IsWeaponTracked(weaponid)
{
    switch(weaponid)
    {
        case 22, 24, 25..27, 28, 29, 30, 31, 33, 34: return true;
    }
    return false;
}

#define WEAPON_AK47 (30)
#define WEAPON_M4 (31)

forward SyncAmmoWithInventory(playerid, weaponid);
public SyncAmmoWithInventory(playerid, weaponid)
{
    if(!IsPlayerConnected(playerid)) return false;

    new ammoNow = GetPlayerAmmo(playerid);
    new used = lastAmmo[playerid] - ammoNow;

    if(weaponid == WEAPON_AK47 || weaponid == WEAPON_M4)
    {
        if(used <= 0 || used > 30) return false;
    }
    else
    {
        if(used <= 0 || used > 10) return false;
    }

    new ammoID = GetAmmoIDForWeapon(weaponid);
    if(ammoID == 0) return false;

    if(GetIteam(playerid, ammoID) < used)
    {
        ShowCheatKickDialog(playerid);
        return false;
    }

    GiveIteam(playerid, ammoID, 0, used, 0);

    return true;
}