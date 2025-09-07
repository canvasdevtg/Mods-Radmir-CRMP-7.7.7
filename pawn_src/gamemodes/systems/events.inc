#define MAX_DMZONE_PLAYERS 30
#define MIN_DMZONE_PLAYERS 3
#define DMZONE_VIRTUAL_WORLD 4
#define MAX_GUN_POSITION 9
#define MAX_SPAWN_POSITION 14
#define MAX_MEDKIT_POSITION 5

#define DMZONE_REGISTER_POSITION 3376.8652,2274.6125,6.0974

new Iterator:DmZonePlayers<MAX_PLAYERS>;
new top_kills[MAX_PLAYERS], top_deaths[MAX_PLAYERS], top_players[MAX_PLAYERS];
new top_players_count = 0;
new TopPlayerNames[MAX_PLAYERS][32];

enum E_DMZONE_STRUCT
{
    E_DMZONE_TIMER,
    E_DMZONE_WAIT,
    bool:E_DMZONE_STATUS,
    bool:E_DMZONE_STARTED,
    E_DMZONE_COUNT_PLAYER
}

new g_dmzone_data[E_DMZONE_STRUCT];

new const Float:g_dmzone_player_pos[MAX_SPAWN_POSITION][3] = 
{
    {3431.9446, 2356.5981, 6.5001},
    {3451.5374, 2363.4900, 6.4997},
    {3444.5481, 2357.2815, 11.6091},
    {3434.7249, 2360.1045, 6.4620},
    {3425.0828, 2363.2466, 6.5046},
    {3435.0623, 2374.4172, 6.1186},
    {3455.7900, 2417.9570, 5.4552},
    {3489.8608, 2390.9883, 6.0552},
    {3499.3047, 2367.9844, 6.6755},
    {3509.5007, 2355.0415, 2.9453},
    {3508.6155, 2372.5737, 6.6328},
    {3474.9343, 2313.2568, 6.6849},
    {3457.7483, 2299.6895, 5.7941},
    {3424.6663, 2293.8889, 5.9512}
};

enum E_MEDKIT_STRUCT
{
    Float:MEDKIT_POS_X,
    Float:MEDKIT_POS_Y,
    Float:MEDKIT_POS_Z,
    MEDKIT_PICKUP_ID,
    bool:MEDKIT_ACTIVE
}

new g_dmzone_medkits[MAX_MEDKIT_POSITION][E_MEDKIT_STRUCT] =
{
    {3440.123, 2360.456, 6.5, -1, true},
    {3480.789, 2345.123, 6.5, -1, true},
    {3428.345, 2334.567, 6.5, -1, true},
    {3466.890, 2300.234, 6.5, -1, true},
    {3435.678, 2390.789, 6.5, -1, true}
};

stock dmzone_OnGameModeInit()
{
    CreatePickup(1313, 23, DMZONE_REGISTER_POSITION, 0);
    CreateDynamic3DTextLabel("{fab13b}Регистрация на пейнтбол\n{abcdef}Для регистрации используйте клавишу {ffa500}ALT", 0xfab13bFF, 3376.8652, 2274.6125, 6.0974 + 0.5, 5.0);
    return 1;
}

stock dmzone_OnPlayerKeyStateChange(playerid, newkeys)
{
    if(newkeys == KEY_WALK)
    {
        if(g_dmzone_data[E_DMZONE_STARTED])
        {
            for(new i; i < sizeof g_dmzone_medkits; i++)
            {
                if(g_dmzone_medkits[i][MEDKIT_ACTIVE] && IsPlayerInRangeOfPoint(playerid, 2.0, g_dmzone_medkits[i][MEDKIT_POS_X], g_dmzone_medkits[i][MEDKIT_POS_Y], g_dmzone_medkits[i][MEDKIT_POS_Z]))
                {
                    new Float:health;
                    GetPlayerHealth(playerid, health);

                    if(health < 100.0)
                    {
                        SetPlayerHealth(playerid, floatmin(health + 50.0, 100.0));
                        DestroyPickup(g_dmzone_medkits[i][MEDKIT_PICKUP_ID]);
                        g_dmzone_medkits[i][MEDKIT_ACTIVE] = false;
                        SendClientMessage(playerid, 0x00FF00FF, "Вы подобрали аптечку и восстановили здоровье.");
                    }
                    else
                    {
                        SendClientMessage(playerid, 0xC0C0C0FF, "Ваше здоровье и так на максимуме.");
                    }
                }
            }
        }
        if(IsPlayerInRangeOfPoint(playerid, 1.5, DMZONE_REGISTER_POSITION))
        {
            if(g_dmzone_data[E_DMZONE_STATUS])
            {
                if(Iter_Contains(DmZonePlayers, playerid)) return SCMF(playerid, 0xC0C0C0FF, "Вы уже зарегистрированы на мероприятие. До начала мероприятия осталось - %d секунд", g_dmzone_data[E_DMZONE_WAIT]);

                if(Iter_Count(DmZonePlayers) >= MAX_DMZONE_PLAYERS)
                {
                    return SendClientMessage(playerid, 0xC0C0C0FF, "На пейнтбол зарегистрировано максимальное количество участников");
                }
                else
                {
                    Iter_Add(DmZonePlayers, playerid);
                    SendClientMessage(playerid, 0xabcdefFF, "Ожидайте уведомления о начале битвы маньяков");
                    SCMF(playerid, 0xfab13bFF, "Вы успешно зарегистрировались на мероприятие под номером: {abcdef}%d", Iter_Count(DmZonePlayers));
                }
            }
            else
            {
                return SCM(playerid, 0xC0C0C0FF, "{fab13b}В данный момент регистрация на Битву маньяков - {ff0000}Закрыта");
            }
        }
    }

    return false;
}

stock StartDmZone()
{
    g_dmzone_timer = -1;
    g_dmzone_data[E_DMZONE_STATUS] = false;
    g_dmzone_data[E_DMZONE_STARTED] = true;
    g_dmzone_data[E_DMZONE_TIMER] = 600;

    for(new i; i < sizeof g_dmzone_medkits; i++)
    {
        g_dmzone_medkits[i][MEDKIT_PICKUP_ID] = CreatePickup(1240, 23, g_dmzone_medkits[i][MEDKIT_POS_X], g_dmzone_medkits[i][MEDKIT_POS_Y], g_dmzone_medkits[i][MEDKIT_POS_Z], DMZONE_VIRTUAL_WORLD);
        g_dmzone_medkits[i][MEDKIT_ACTIVE] = true;
    }

    new index;

    SCMTA(0xffa500ff, "Внимание! Стартовало Мероприятие: [Битва маньяков]");

    foreach (new i : DmZonePlayers)
    {
        SetPlayerInterior(i, 0);
        SetPlayerVirtualWorld(i, DMZONE_VIRTUAL_WORLD);
        SetPlayerPos(i, g_dmzone_player_pos[index][0], g_dmzone_player_pos[index][1], g_dmzone_player_pos[index][2]);
        index++;

        GivePlayerWeapon(i, 24, 100);
        TogglePlayerControllable(i, true);
        SetPlayerSkin(i, 230);
    }

    return 1;
}

stock EndDmZone()
{
    new j, temp;
    foreach(new i : DmZonePlayers)
    {
        top_kills[i] = g_player[i][P_DM_KILLS];
        top_deaths[i] = g_player[i][P_DM_DEATH];
        strcat(TopPlayerNames[i], GetPlayerNameEx(i));
        top_players[i] = i;
        top_players_count++;
    }
    for(new i = 0; i < MAX_PLAYERS - 1; i++)
    {
        for(j = i + 1; j < MAX_PLAYERS; j++)
        {
            if(top_kills[i] < top_kills[j])
            {
                temp = top_kills[i];
                top_kills[i] = top_kills[j];
                top_kills[j] = temp;

                temp = top_deaths[i];
                top_deaths[i] = top_deaths[j];
                top_deaths[j] = temp;

                temp = top_players[i];
                top_players[i] = top_players[j];
                top_players[j] = temp;
            }
        }
    }

    ProcessPlayerCredit(top_players[0], 45, "Победитель пейнтболла");
    ProcessPlayerCredit(top_players[1], 30, "Победитель пейнтболла");
    ProcessPlayerCredit(top_players[2], 15, "Победитель пейнтболла");

    SCM(top_players[0], 0xfab13bFF, "Поздравляем! Вы заняли первое место");
    SCM(top_players[1], 0xfab13bFF, "Поздравляем! Вы заняли второе место");
    SCM(top_players[2], 0xfab13bFF, "Поздравляем! Вы заняли третье место");

    SCMTA(0xabcdefFF, "Внимание! Пейнтбол окончен. Список победителей /painlist");

    foreach (new idx : DmZonePlayers)
    {
        SetPlayerInterior(idx, 1);
        SetPlayerArmedWeapon(idx, 0);
        SetPlayerVirtualWorld(idx, 0);
        SetPlayerPos(idx, DMZONE_REGISTER_POSITION);
    }

    g_dmzone_data[E_DMZONE_STATUS] = false;
    g_dmzone_timer = 900;
}