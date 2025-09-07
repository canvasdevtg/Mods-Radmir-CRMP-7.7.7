#if defined _detailyng_included
    #endinput
#endif
#define _detailyng_included

stock OnDetailingVinylsCamera(playerid)
{
	switch(camera_detailyng[playerid])
	{
		case 0:
		{
			InterpolateCameraPos(playerid, -3.65, 498.80, 1001.89, -3.96, 506.24, 1001.89, 2000, 1);
			InterpolateCameraLookAt(playerid, -6.65, 501.99, 1001.29, -6.65, 502.49, 1001.29, 2000, 1);

			camera_detailyng[playerid] = 1;
		}
		case 1:
		{
			InterpolateCameraPos(playerid, -3.96, 506.24, 1001.89, -5.61, 507.86, 1001.89, 2000, 1);
			InterpolateCameraLookAt(playerid, -6.65, 502.49, 1001.29, -6.65, 502.49, 1001.29, 2000, 1);

			camera_detailyng[playerid] = 2;
		}
		case 2:
		{
			InterpolateCameraPos(playerid, -5.61, 507.86, 1001.89, -3.65, 498.80, 1001.89, 2000, 1);
			InterpolateCameraLookAt(playerid, -6.65, 502.49, 1001.29, -6.65, 501.99, 1001.29, 2000, 1);

			camera_detailyng[playerid] = 0;
		}
	}
}