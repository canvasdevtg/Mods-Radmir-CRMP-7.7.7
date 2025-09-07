#if defined _custom_syncs_car_included
    #endinput
#endif
#define _custom_syncs_car_included

public OnOutgoingRPC(playerid, rpcid, BitStream:bs)
{
    if(rpcid == 164)
    {
        CustomSyncs(bs);
    }

    return 1;
}

enum SyncsCars
{
    car_id,
    car_modelId,
    Float:car_pos[4],
    inter_color[2],
    Float:health,
    inter,
    damage[4],
    addsiren,
    modslot[14],
    paintjob,
    car_color[2]
};

stock CustomSyncs(BitStream:bs)
{
    new Syncs[SyncsCars];

    BS_ReadValue(
        bs,
        PR_UINT16, Syncs[car_id],
        PR_UINT32, Syncs[car_modelId],
        PR_FLOAT3, Syncs[car_pos],
        PR_FLOAT, Syncs[car_pos][3]
    );

    for(new i = 0; i < 2; i++)
        BS_ReadValue(bs, PR_UINT8, Syncs[inter_color][i]);

    BS_ReadValue(bs,
        PR_FLOAT, Syncs[health],
        PR_UINT8, Syncs[inter]
    );

    for(new i = 0; i < 4; i++)
    {
        if(i < 2) BS_ReadValue(bs, PR_UINT32, Syncs[damage][i]);
        else BS_ReadValue(bs, PR_UINT8, Syncs[damage][i]);
    }

    BS_ReadValue(bs, PR_UINT8, Syncs[addsiren]);

    for(new i = 0; i < 14; i++)
        BS_ReadValue(bs, PR_UINT8, Syncs[modslot][i]);

    BS_ReadValue(bs, PR_UINT8, Syncs[paintjob]);

    for(new i = 0; i < 2; i++)
        BS_ReadValue(bs, PR_UINT32, Syncs[car_color][i]);

    if(IsValidVehicle(Syncs[car_id]))
    {
        BS_Reset(bs);

        new Float:qwuat[4] = {0.0,0.0,0.0,0.0};
        
        new Float:rot_w, Float:rot_z;
        Quaternion(Syncs[car_pos][3], rot_w, rot_z);
        qwuat[0] = rot_w;
        qwuat[3] = rot_z;

        BS_WriteValue(
            bs,
            PR_UINT16, Syncs[car_id],
            PR_UINT32, Syncs[car_modelId],
            PR_FLOAT, Syncs[car_pos][0],
            PR_FLOAT, Syncs[car_pos][1],
            PR_FLOAT, Syncs[car_pos][2],
            PR_NORM_QUAT, qwuat
        );

        for(new i = 0; i < 2; i++)
            BS_WriteValue(bs, PR_UINT8, Syncs[inter_color][i]);

        BS_WriteValue(bs,
            PR_FLOAT, Syncs[health],
            PR_UINT8, Syncs[inter]
        );

        for(new i = 0; i < 4; i++)
        {
            if(i < 2) BS_WriteValue(bs, PR_UINT32, Syncs[damage][i]);
            else BS_WriteValue(bs, PR_UINT8, Syncs[damage][i]);
        }

        BS_WriteValue(bs, PR_UINT8, Syncs[addsiren]);

        for(new i = 0; i < 14; i++)
            BS_WriteValue(bs, PR_UINT8, Syncs[modslot][i]);

        BS_WriteValue(bs, PR_UINT8, Syncs[paintjob]);

        for(new i = 0; i < 2; i++)
            BS_WriteValue(bs, PR_UINT32, Syncs[car_color][i]);
    }
}

stock Quaternion(Float:angle_rot, &Float:w_rot, &Float:z_rot)
{
    new Float:angle = -angle_rot * 0.01745329251;

    w_rot = floatcos(angle / 2);
    z_rot = floatsin(angle / 2);
}
