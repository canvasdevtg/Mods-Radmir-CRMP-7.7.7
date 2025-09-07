#if defined _garbage_included
    #endinput
#endif
#define _garbage_included

#define Garbage: Garbage_

new GarbageTimer = 600;

const MAX_GARBAGE_PLACE = 39;

enum eGarbageStruct
{
    Float:eGarbageX,
    Float:eGarbageY,
    Float:eGarbageZ,
    bool:eGarbageState
};

new e_Garbage[MAX_GARBAGE_PLACE][eGarbageStruct] = 
{
    {496.5676,-1885.2161,34.6016},
    {518.6489,-1890.3241,34.5580},
    {522.0764,-1907.4651,34.5088},
    {547.9340,-1899.4492,34.5088},
    {546.0768,-1924.1914,34.7244},
    {526.7225,-1922.8893,34.6292},
    {528.0508,-1932.3323,35.3152},
    {551.0677,-1940.0347,35.7462},
    {557.2570,-1955.5370,35.9049},
    {574.9286,-1970.0782,35.1139},
    {584.8649,-1957.8708,35.7182}, 
    {577.2258,-1985.0500,34.5175}, 
    {581.9025,-2012.3169,35.2736}, 
    {548.1730,-2008.1343,35.1220}, 
    {506.8214,-2013.1544,34.7339}, 
    {490.1305,-1990.4449,35.9491}, 
    {477.4425,-1963.0120,36.7863}, 
    {452.9829,-1977.2067,37.2910}, 
    {447.8906,-2008.0708,36.1823}, 
    {408.6859,-2019.1920,36.1588}, 
    {381.7986,-2032.4929,36.3453}, 
    {373.1428,-1981.6527,35.3052}, 
    {342.3338,-1993.1019,35.5310}, 
    {333.2878,-2027.1139,37.4395}, 
    {293.8658,-2018.2133,34.6752}, 
    {257.2776,-2015.8613,34.5242}, 
    {239.2600,-1966.8171,34.3366}, 
    {273.8426,-1943.4192,34.0997},
    {301.6636,-1955.9194,34.2084},
    {321.9396,-1915.1765,33.7646},
    {287.0645,-1887.7290,33.9103},
    {254.2784,-1871.0071,34.1404},
    {325.1764,-1874.3593,33.6309},
    {362.0484,-1883.9510,34.0781},
    {398.2675,-1867.9445,34.5304}, 
    {421.5326,-1904.1945,34.4757},
    {444.5877,-1931.2876,34.5318},
    {501.6817,-1867.0184,34.7898},
    {543.6496,-1874.0852,34.7310}
};

enum ePlayerGarbage
{
    ePGarbageID,
    ePGarbageState,
    ePGarbageSignal,
    ePGarbageCount,
    ePGarbagePrize,
    ePGarbageCount2,
    ePGarbageSlot,
    ePGarbageDist100,
    Float:ePGarbageLastDist,
    ePGarbageBatter,
    ePGarbageBatteryTick,
    ePGarbageModel,
};
new e_PlayerGarbage[MAX_PLAYERS][ePlayerGarbage];

new Dist93[MAX_PLAYERS];
new Dig[MAX_PLAYERS];

#define MAX_HOLES 10

new objectID[MAX_PLAYERS][MAX_HOLES];
new objectTimersRaise[MAX_PLAYERS][MAX_HOLES];
new objectTimersDestroy[MAX_PLAYERS][MAX_HOLES];
new Float:objectZOffsets[MAX_PLAYERS][MAX_HOLES];

stock Garbage:OnPlayerKeyStateChange(playerid,newkeys,oldkeys)
{
    if(RELEASED(KEY_WALK))
    {
        if(detector[playerid] == 1)
        {
            if(g_playerInZone[playerid] == true)
            {
                str_q[0] = EOS;

                e_PlayerGarbage[playerid][ePGarbageState] = 0;
                e_PlayerGarbage[playerid][ePGarbageSignal] = 0;

                format(str_q,150,"interface('GarbageMetalSearch').getSearchInfo('[%d,%d,%d]')",e_PlayerGarbage[playerid][ePGarbageState],e_PlayerGarbage[playerid][ePGarbageSignal],e_PlayerGarbage[playerid][ePGarbageBatter]);
                CEF_CREATE(playerid, 1, 2,str_q);  
            }
            else
            {
                str_q[0] = EOS;

                e_PlayerGarbage[playerid][ePGarbageState] = 0;
                e_PlayerGarbage[playerid][ePGarbageSignal] = 0;

                format(str_q,150,"interface('GarbageMetalSearch').getSearchInfo('[%d,%d,%d]')",e_PlayerGarbage[playerid][ePGarbageState],e_PlayerGarbage[playerid][ePGarbageSignal],e_PlayerGarbage[playerid][ePGarbageBatter]);
                CEF_CREATE(playerid, 1, 2,str_q);
            }            
        }        
    }
    if(PRESSED(KEY_WALK))
    {
        if(detector[playerid] == 1)
        {
            if(g_playerInZone[playerid] == true)
            {
                e_PlayerGarbage[playerid][ePGarbageState] = 1;
            }
        }
    }
    if(PRESSED(KEY_CROUCH))//c
    {
        if(detector[playerid] == 1)
        {
            if(g_playerInZone[playerid] == true)
            {
                if(GetPlayerWeapon(playerid) != 6) return SCM(playerid, 0xead671FF, "Сначала возьмите в руки лопату.");
                if(Dig[playerid] != 1) 
                {
                    SCM(playerid, -1, "{B8CEF6}Вы начали копать землю.");
                    ApplyAnimationEx(playerid, "ped", "a_dig", 4.0, true, 0, 0, 1, 0, 0, USE_ANIM_TYPE_NONE);
                    UseMetalDetector(playerid);
                    e_PlayerGarbage[playerid][ePGarbagePrize] = 1;
                    Dig[playerid] = 1;
                }
            }
        }
    }
    return 1;
}

stock Garbage:ClearGarbageInfo(playerid)
{
    e_PlayerGarbage[playerid][ePGarbagePrize] = 0;		
	e_PlayerGarbage[playerid][ePGarbageCount] = 0;	
	e_PlayerGarbage[playerid][ePGarbageCount2] = 0;	
	e_PlayerGarbage[playerid][ePGarbageSignal] = 0;	
	e_PlayerGarbage[playerid][ePGarbageState] = 0;
    e_PlayerGarbage[playerid][ePGarbageBatteryTick] = 0;
    e_PlayerGarbage[playerid][ePGarbageModel] = 0;

    Dist93[playerid] = 0;

    Dig[playerid] = 0;

    e_PlayerGarbage[playerid][ePGarbageLastDist] = 100.0;

	detector[playerid] = 0;
	RemovePlayerAttachedObject(playerid, A_OBJECT_SLOT_HAND);
	CEF_HIDE(playerid, "GarbageMetalSearch");    

    e_PlayerGarbage[playerid][ePGarbageSlot] = -1;
    return 1;
}
public: Garbage:OnGarbageTimer(playerid)
{
    if(e_PlayerGarbage[playerid][ePGarbageState] == 1)
    {
        str_2[0] = EOS;
        format(str_2,200,"interface('GarbageMetalSearch').getSearchInfo('[%d,%d,%d]')",e_PlayerGarbage[playerid][ePGarbageState],e_PlayerGarbage[playerid][ePGarbageSignal],e_PlayerGarbage[playerid][ePGarbageBatter]);
        CEF_CREATE(playerid, 1, 2,str_2);     

        for(new i; i < MAX_GARBAGE_PLACE; i++)
        {           
            if(e_Garbage[i][eGarbageState] == true)
            {
                if(!IsPlayerInRangeOfPoint(playerid, 8.0, e_Garbage[i][eGarbageX], e_Garbage[i][eGarbageY], e_Garbage[i][eGarbageZ])) continue;
                if(IsPlayerInRangeOfPoint(playerid, 8.0, e_Garbage[i][eGarbageX], e_Garbage[i][eGarbageY], e_Garbage[i][eGarbageZ]))
                {
                    new Float:dist = GetPlayerDistanceFromPoint(playerid, e_Garbage[i][eGarbageX],e_Garbage[i][eGarbageY],e_Garbage[i][eGarbageZ]);
                    if(e_PlayerGarbage[playerid][ePGarbageLastDist] > dist) 
                    {
                        e_PlayerGarbage[playerid][ePGarbageSignal]+=20;
                        if(dist > 1.0 && e_PlayerGarbage[playerid][ePGarbageSignal] > 80) e_PlayerGarbage[playerid][ePGarbageSignal] = 80;
                    }
                    else 
                    {
                        e_PlayerGarbage[playerid][ePGarbageSignal]-=20;
                        if(e_PlayerGarbage[playerid][ePGarbageSignal] < 0) e_PlayerGarbage[playerid][ePGarbageSignal] = 0;
                    }
                    e_PlayerGarbage[playerid][ePGarbageLastDist] = dist;
                    if(dist < 1.0)
                    {
                        e_PlayerGarbage[playerid][ePGarbageSignal] = 100;
                        CEF_CREATE(playerid, 1, 2, "interface('GarbageMetalSearch').playSignal('4')");

                        if(Dist93[playerid] != 1){
                            Dist93[playerid] = 1;
                        }

                        SCM(playerid, COLOR_ORANGE, "Прибор что-то обнаружил. Нажмите клавишу {ffffff}\"C\" {FAAC58}если хотите выкопать найденное.");
                        e_PlayerGarbage[playerid][ePGarbageID] = i;
                    }
                    else if(1.5 < dist < 3.0)
                    {
                        CEF_CREATE(playerid, 1, 2,"interface('GarbageMetalSearch').playSignal('3')");
                        Dist93[playerid] = 0;
                    }
                    else if(3.0 < dist < 8.0)
                    {
                        CEF_CREATE(playerid, 1, 2,"interface('GarbageMetalSearch').playSignal('1')");
                        Dist93[playerid] = 0;
                    }                       
                }
            }
        }
        if(e_PlayerGarbage[playerid][ePGarbageBatter] <= 0)
        {
            Garbage:ClearGarbageInfo(playerid);
            SCM(playerid, COLOR_ORANGE, "Ваш металлоискатель разрядился, замените батарейки.");
        }
    }
    if(detector[playerid] == 1)
    {
        if(e_PlayerGarbage[playerid][ePGarbageBatter] > 0)
        {
            switch(e_PlayerGarbage[playerid][ePGarbageModel])
            {
                case 1: // обычная
                {
                    e_PlayerGarbage[playerid][ePGarbageBatteryTick]++;
                    if(e_PlayerGarbage[playerid][ePGarbageBatteryTick] >= 20)
                    {
                        e_PlayerGarbage[playerid][ePGarbageBatter]--;
                        e_PlayerGarbage[playerid][ePGarbageBatteryTick] = 0;
                    }
                }
                case 2: // дорогая
                {
                    e_PlayerGarbage[playerid][ePGarbageBatteryTick]++;
                    if(e_PlayerGarbage[playerid][ePGarbageBatteryTick] >= 13)
                    {
                        e_PlayerGarbage[playerid][ePGarbageBatter]--;
                        e_PlayerGarbage[playerid][ePGarbageBatteryTick] = 0;
                    }
                }
            }
            str_2[0] = EOS;
            format(str_2,200,"interface('GarbageMetalSearch').getSearchInfo('[%d,%d,%d]')",e_PlayerGarbage[playerid][ePGarbageState],e_PlayerGarbage[playerid][ePGarbageSignal],e_PlayerGarbage[playerid][ePGarbageBatter]);
            CEF_CREATE(playerid, 1, 2,str_2);
        }    
    }
    if(e_PlayerGarbage[playerid][ePGarbagePrize] == 1)
    {
        e_PlayerGarbage[playerid][ePGarbageCount2]++;
        if(e_PlayerGarbage[playerid][ePGarbageCount2] == 4)
        {
            if(Dist93[playerid] == 1) 
            {
                ClearAnimations(playerid);

                DropMetal(playerid);
                GiveRandCase(playerid);

                e_PlayerGarbage[playerid][ePGarbagePrize] = 0;
                e_PlayerGarbage[playerid][ePGarbageCount2] = 0;

                Dist93[playerid] = 0;
                Dig[playerid] = 0;

                e_Garbage[e_PlayerGarbage[playerid][ePGarbageID]][eGarbageState] = false;
            }
            else
            {
                SCM(playerid, COLOR_ORANGE, "Вы ничего не нашли (металлоискатель должен показывать сигнал не меньше 93 процентов).");
                ClearAnimations(playerid);
                e_PlayerGarbage[playerid][ePGarbagePrize] = 0;
                e_PlayerGarbage[playerid][ePGarbageCount2] = 0;
                Dig[playerid] = 0;
            }
        }
    }
    return 1;
}

public: UseMetalDetector(playerid)
{
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);

    new Float:angle;
    GetPlayerFacingAngle(playerid, angle);

    new Float:offset = 1.0;
    new Float:dx = floatsin(-angle, degrees) * offset;
    new Float:dy = floatcos(-angle, degrees) * offset;

    x += dx;
    y += dy;

    new holeIndex = -1;
    for(new i = 0; i < MAX_HOLES; i++)
    {
        if(objectID[playerid][i] == 0)
        {
            holeIndex = i;
            break;
        }
    }
    if(holeIndex == -1)
    {
        DestroyObject(objectID[playerid][0]);
        KillTimer(objectTimersRaise[playerid][0]);
        KillTimer(objectTimersDestroy[playerid][0]);
        objectID[playerid][0] = 0;
        holeIndex = 0;
    }

    objectZOffsets[playerid][holeIndex] = 0.0; 
    objectID[playerid][holeIndex] = CreateObject(18372, x, y, z - 3.0, 0.0, 0.0, angle);

    objectTimersRaise[playerid][holeIndex] = SetTimerEx("RaiseHole", 30, true, "ii", playerid, holeIndex);

    objectTimersDestroy[playerid][holeIndex] = SetTimerEx("DestroyDiggingHole", 60000, false, "ii", playerid, holeIndex);
    return 1;
}

forward RaiseHole(playerid, holeIndex);
public RaiseHole(playerid, holeIndex)
{
    if(objectID[playerid][holeIndex] == 0) return 0;

    objectZOffsets[playerid][holeIndex] += 0.03;
    new Float:x, Float:y, Float:z;
    GetObjectPos(objectID[playerid][holeIndex], x, y, z);
    SetObjectPos(objectID[playerid][holeIndex], x, y, z + 0.03);

    if(objectZOffsets[playerid][holeIndex] >= 2.0) // поднялись на 2 метра
    {
        objectZOffsets[playerid][holeIndex] = 2.0;
        KillTimer(objectTimersRaise[playerid][holeIndex]);
    }
    return 1;
}

forward DestroyDiggingHole(playerid, holeIndex);
public DestroyDiggingHole(playerid, holeIndex)
{
    if(objectID[playerid][holeIndex] != 0)
    {
        DestroyObject(objectID[playerid][holeIndex]);
        objectID[playerid][holeIndex] = 0;
    }
    KillTimer(objectTimersRaise[playerid][holeIndex]);
    KillTimer(objectTimersDestroy[playerid][holeIndex]);
    return 1;
}

stock DropMetal(playerid)
{
    switch(random(10))
    {
        case 0:
        {
            new garbageitem_id[] = {224, 48, 56, 57, 62, 63, 64, 65, 111, 112, 113, 316, 114}; 
            new garbage_index = RandomEx(0, sizeof(garbageitem_id) - 1);
            new garbageprizes = garbageitem_id[garbage_index];

            GiveIteam(playerid, garbageprizes, 1, 1, 0);
       
            SCMF(playerid, COLOR_WHITE, "Вы откопали {008000} \"%s\" (1 шт)", ItemsInfo[garbageprizes]);
            SCM(playerid, -1, "Вы можете продать свою находку в антикварной лавке.");
        }
        case 1..9:
        {
            new garbagemetal = RandomEx (3,10);
            GiveIteam(playerid, 124, 1, garbagemetal, 0);
       
            SCMF(playerid, COLOR_WHITE, "Вы откопали {008000} \"Металлолом\" (%d шт)", garbagemetal);
        }
    }
    return 1;
}