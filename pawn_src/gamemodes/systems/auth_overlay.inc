#if defined _auth_overlay_included
    #endinput
#endif
#define _auth_overlay_included

//====================[Настройки сцены]==================//

new AuthActor[MAX_PLAYERS];
new AuthActorNPC[MAX_PLAYERS][4];
new AuthVeh[MAX_PLAYERS];
new AuthVehNPC[MAX_PLAYERS][5];

enum A_CARS_ACTOR
{
    modelid,
    Float:x,
    Float:y,
    Float:z,
    Float:a,
    car_color_1,
    car_color_2
}

enum A_ACTORS
{
    actor_skin,
    Float:x,
    Float:y,
    Float:z,
    Float:a,
    animlib[32],
    anim[32]
}

#define MAX_SCENES 4
#define MAX_VEHICLES_PER_SCENE 5
#define MAX_ACTORS_PER_SCENE 4

#define MAX_AUTH_NPC_VEHICLES 5
#define MAX_AUTH_NPC_ACTORS   4

new const scene_vehicles[MAX_SCENES][MAX_VEHICLES_PER_SCENE][A_CARS_ACTOR] =
{
    // Сцена 0
    {
        {15213, 2549.07, -1755.58, 21.60, 89.92, 3, 3},
        {0, 0.0, 0.0, 0.0, 0.0, 0, 0},
        {0, 0.0, 0.0, 0.0, 0.0, 0, 0},
        {0, 0.0, 0.0, 0.0, 0.0, 0, 0},
        {0, 0.0, 0.0, 0.0, 0.0, 0, 0}
    },

    // Сцена 1
    {
        {796, 1943.03, -0.56, 6.62, 130.22, 0, 0},
        {15120, 1949.70, 2.10, 6.35, 91.44, 1, 1},
        {796, 1956.30, -0.23, 6.61, 57.37, 0, 0},
        {0, 0.0, 0.0, 0.0, 0.0, 0, 0},
        {0, 0.0, 0.0, 0.0, 0.0, 0, 0}
    },

    // Сцена 2
    {
        {0, 0.0, 0.0, 0.0, 0.0, 0, 0},
        {0, 0.0, 0.0, 0.0, 0.0, 0, 0},
        {0, 0.0, 0.0, 0.0, 0.0, 0, 0},
        {0, 0.0, 0.0, 0.0, 0.0, 0, 0},
        {0, 0.0, 0.0, 0.0, 0.0, 0, 0}
    },

    // Сцена 3
    {
        {15626, 1893.70, -1968.41, 31.12, -28.55, 0, 0},
        {15637, 1901.21, -1972.76, 31.45, -29.20, 1, 1},
        {15224, 1916.68, -1965.64, 31.24, 149.14, 0, 0},
        {15633, 1912.66, -1963.25, 31.43, 149.75, 0, 0},
        {15282, 1914.41, -1942.99, 31.52, 59.00, 0, 0}
    }
};

new const scene_actors[MAX_SCENES][MAX_ACTORS_PER_SCENE][A_ACTORS] =
{
    // Сцена 0
    {
        {17010, 2547.69, -1756.86, 21.82, 178.61, "SMOKING", "M_SMKLEAN_LOOP"},
        {0, 0.0, 0.0, 0.0, 0.0, "", ""},
        {0, 0.0, 0.0, 0.0, 0.0, "", ""},
        {0, 0.0, 0.0, 0.0, 0.0, "", ""}
    },

    // Сцена 1
    {
        {17061, 1955.27, -1.81, 6.43, 148.07, "DEALER", "DEALER_IDLE"},
        {0, 0.0, 0.0, 0.0, 0.0, "", ""},
        {0, 0.0, 0.0, 0.0, 0.0, "", ""},
        {0, 0.0, 0.0, 0.0, 0.0, "", ""}
    },

    // Сцена 2
    {
        {0, 0.0, 0.0, 0.0, 0.0, "", ""},
        {0, 0.0, 0.0, 0.0, 0.0, "", ""},
        {0, 0.0, 0.0, 0.0, 0.0, "", ""},
        {0, 0.0, 0.0, 0.0, 0.0, "", ""}
    },

    // Сцена 3
    {
        {17025, 1910.11, -1965.16, 31.55, 92.22, "PED", "IDLE_CHAT"},
        {15467, 1908.61, -1965.04, 31.55, 255.28, "PED", "IDLE_CHAT"},
        {15456, 1924.91, -1937.75, 31.79, 331.79, "PED", "ATM"},
        {15458, 1916.47, -1930.69, 35.05, 145.74, "BD_FIRE", "F_SMKLEAN_LOOP"}
    }
};

//====================[Создание сцены]==================//

stock CreateScene(playerid, scene_id)
{
    for(new i = 0; i < MAX_VEHICLES_PER_SCENE; i++)
    {
        if(scene_vehicles[scene_id][i][modelid] == 0) continue;

        new model = scene_vehicles[scene_id][i][modelid];
        new Float:pos_x = scene_vehicles[scene_id][i][x];
        new Float:pos_y = scene_vehicles[scene_id][i][y];
        new Float:pos_z = scene_vehicles[scene_id][i][z];
        new Float:pos_a = scene_vehicles[scene_id][i][a];
        new c1 = scene_vehicles[scene_id][i][car_color_1];
        new c2 = scene_vehicles[scene_id][i][car_color_2];

        AuthVehNPC[playerid][i] = CreateVehicle(model, pos_x, pos_y, pos_z, pos_a, c1, c2, 0, -1);
        SetVehicleVirtualWorld(AuthVehNPC[playerid][i], 33 + playerid);
    }

    for(new i = 0; i < MAX_ACTORS_PER_SCENE; i++)
    {
        if(scene_actors[scene_id][i][actor_skin] == 0) continue;

        new skin = scene_actors[scene_id][i][actor_skin];
        new Float:pos_x = scene_actors[scene_id][i][x];
        new Float:pos_y = scene_actors[scene_id][i][y];
        new Float:pos_z = scene_actors[scene_id][i][z];
        new Float:pos_a = scene_actors[scene_id][i][a];

        AuthActorNPC[playerid][i] = CreateActor(skin, pos_x, pos_y, pos_z, pos_a);
        SetActorVirtualWorld(AuthActorNPC[playerid][i], 33 + playerid);
        ApplyActorAnimation(AuthActorNPC[playerid][i], scene_actors[scene_id][i][animlib], scene_actors[scene_id][i][anim], 4.10, true, false, false, false, 0);
        ApplyActorAnimation(AuthActorNPC[playerid][i], scene_actors[scene_id][i][animlib], scene_actors[scene_id][i][anim], 4.10, true, false, false, false, 0);
    }
}

//====================[Иницилизация транспорта для тех у кого нету тс]==================//

new cars_auth[2];

stock CarsInitAuth()
{
    cars_auth[0] = CreateVehicle(462, 435.72, 1539.14, 11.74, 125.94, 1, 1, 0, -1);
    cars_auth[1] = CreateVehicle(418, 438.92, 1544.84, 12.51, 85.09, 1, 1, 0, -1);

    SetVehicleVirtualWorld(cars_auth[0], 33);
    SetVehicleVirtualWorld(cars_auth[1], 33);
}

//====================[Выбор]==================//

stock AuthOverlay(playerid, type)
{
    switch(type)
    {
        case 0:
        {
            InterpolateCameraPos(playerid, 430.63, 1535.41, 12.89, 432.13, 1537.95, 12.66, 30000);
            InterpolateCameraLookAt(playerid, 431.15, 1536.26, 12.80, 432.84, 1538.64, 12.53, 30000);
        }
        case 1:
        {
            new query[117];
            mysql_format(mysql, query, sizeof query, "SELECT * FROM ownable_cars WHERE owner_id='%d' ORDER BY RAND() LIMIT 1", GetPlayerData(playerid, P_ACCOUNT_ID));
	        mysql_tquery(mysql, query, "OnPlayerAuthCars", "i", playerid);
        }
    }
}

//====================[Загрузка]==================//

forward OnPlayerAuthCars(playerid);
public OnPlayerAuthCars(playerid)
{
    if(cache_num_rows() == 0)
        return false;

    new model_id;
    new color_1;
    new color_2;
    new diski;
    new vinil;
    new viniltype;
    new typenumber;
    new number[32];
    new region[32];

    model_id    = cache_get_field_content_int(0, "model_id");
    color_1     = cache_get_field_content_int(0, "color_1");
    color_2     = cache_get_field_content_int(0, "color_2");
    diski     = cache_get_field_content_int(0, "diski");
    vinil       = cache_get_field_content_int(0, "vinil");
    viniltype   = cache_get_field_content_int(0, "viniltype");
    typenumber  = cache_get_field_content_int(0, "typenumber");

    cache_get_field_content(0, "number", number);
    cache_get_field_content(0, "region", region);

    new RandAuth = random(4);
    
    OverlayCamera(playerid, RandAuth);
    CreateScene(playerid, RandAuth);

    new skin = GetPlayerData(playerid, P_SKIN);

    switch(RandAuth)
    {
        case 0:{ 
            AuthActor[playerid] = CreateActor(skin, 2542.96, -1786.56, 21.96, 159.02); 
            AuthVeh[playerid] = CreateVehicle(model_id, 2541.03, -1784.98, 21.65, -179.37, color_1, color_2, 0, -1); 
            SendCreateNPC(playerid, playerid + 1, 17003, 2560.09, -1752.43, 21.96, 89.40); 
            SendMoveNPC(playerid, playerid + 1, 2504.77, -1751.85, 21.96, 1.55, 50.00);
            SetPVarInt(playerid, "NPC_CREATED", 1);
        }
        case 1:{ AuthActor[playerid] = CreateActor(skin, 1949.91, -17.54, 6.43, 110.92); AuthVeh[playerid] = CreateVehicle(model_id, 1951.13, -14.82, 6.27, 118.82, color_1, color_2, 0, -1); }
        case 2:{ AuthActor[playerid] = CreateActor(skin, -425.61, 777.72, 12.55, 230.88); AuthVeh[playerid] = CreateVehicle(model_id, -428.05, 777.71, 12.39, -141.63, color_1, color_2, 0, -1); }
        case 3:{ AuthActor[playerid] = CreateActor(skin, 1904.31, -1962.13, 31.55, 112.15); AuthVeh[playerid] = CreateVehicle(model_id, 1904.54, -1958.10, 31.57, 150.07, color_1, color_2, 0, -1); }
    }

    SetActorVirtualWorld(AuthActor[playerid], 33 + playerid);
    SetVehicleVirtualWorld(AuthVeh[playerid], 33 + playerid);

    AcsActorActive(playerid, AuthActor[playerid]);

    ApplyActorAnimation(AuthActor[playerid], "COP_AMBIENT", "COPLOOK_LOOP", 4.10, true, false, false, false, 0);
    ApplyActorAnimation(AuthActor[playerid], "COP_AMBIENT", "COPLOOK_LOOP", 4.10, true, false, false, false, 0);

    switch(viniltype)
    {
        case 0: ChangeVehicleDefaultViniljob(AuthVeh[playerid], vinil);
        case 1: ChangeVehicleViniljob(AuthVeh[playerid], vinil);
    }

    if(diski != 0)
    {
        PACKET_215(playerid, 17, AuthVeh[playerid], diski);
    }

    SetVehicleNumber(AuthVeh[playerid], typenumber, number, region);
    PACKET_215(playerid, 32, AuthVeh[playerid], typenumber, number, region);

    return true;
}

//====================[Удаление]==================//

stock DestroyAuth(playerid)
{
    if(IsValidActor(AuthActor[playerid]))
    {
        DestroyActor(AuthActor[playerid]);
        AuthActor[playerid] = INVALID_ACTOR_ID;
    }

    if(IsValidVehicle(AuthVeh[playerid]))
    {
        DestroyVehicle(AuthVeh[playerid]);
        AuthVeh[playerid] = INVALID_VEHICLE_ID;
    }

    for(new i = 0; i < MAX_AUTH_NPC_ACTORS; i++)
    {
        if(IsValidActor(AuthActorNPC[playerid][i]))
        {
            DestroyActor(AuthActorNPC[playerid][i]);
            AuthActorNPC[playerid][i] = INVALID_ACTOR_ID;
        }
    }

    for(new i = 0; i < MAX_AUTH_NPC_VEHICLES; i++)
    {
        if(IsValidVehicle(AuthVehNPC[playerid][i]))
        {
            DestroyVehicle(AuthVehNPC[playerid][i]);
            AuthVehNPC[playerid][i] = INVALID_VEHICLE_ID;
        }
    }

    RemoveActorAttachedObject(playerid);

    if(GetPVarInt(playerid, "NPC_CREATED") == 1)
    {
        SendDeleteNPC(playerid, playerid + 1);
        DeletePVar(playerid, "NPC_CREATED");
    }

    return 1;
}

//====================[Настройки камеры]==================//

enum CAMERA
{
    Float: CAMERA_POS[6],
	Float: CAMERA_POS_LOCK[6]
}

static const camera_pos[4][CAMERA] =
{
   {{2539.16, -1794.51, 22.50, 2542.57, -1791.10, 22.38},{2539.36, -1793.53, 22.47, 2542.35, -1790.14, 22.26}}, // ЖК
   {{1944.60, -20.84, 6.96, 1946.48, -18.97, 7.09},{1945.14, -20.00, 6.90, 1947.12, -18.22, 6.93}}, // Особняк
   {{-421.32, 774.29, 13.27, -423.29, 775.53, 13.12},{-422.27, 774.58, 13.18, -424.23, 775.84, 12.94}}, // МГУ
   {{1897.59,-1964.46,32.21,1901.84,-1964.04,31.80},{1898.28,-1963.73,32.25,1902.26,-1963.14,31.70}} // Казино
};

stock OverlayCamera(playerid, type)
{
    SetPlayerVirtualWorld(playerid, 33 + playerid);

    InterpolateCameraPos(playerid, camera_pos[type][CAMERA_POS][0], camera_pos[type][CAMERA_POS][1], camera_pos[type][CAMERA_POS][2], camera_pos[type][CAMERA_POS][3], camera_pos[type][CAMERA_POS][4], camera_pos[type][CAMERA_POS][5], 30000);
    InterpolateCameraLookAt(playerid, camera_pos[type][CAMERA_POS_LOCK][0], camera_pos[type][CAMERA_POS_LOCK][1], camera_pos[type][CAMERA_POS_LOCK][2], camera_pos[type][CAMERA_POS_LOCK][3], camera_pos[type][CAMERA_POS_LOCK][4], camera_pos[type][CAMERA_POS_LOCK][5], 30000);
}