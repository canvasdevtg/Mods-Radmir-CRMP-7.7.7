
public: FAMTBL_OnPlayerOpenTab(playerid, event)
{
    switch(event)
    {
        case 0:
        {
            new fam_id = GetPlayerFamily(playerid);
            new index = GetFamilyData(fam_id, F_COLOR);

            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof STRING_GLOBAL, "interface('Tablet').getCurrentApp().setMainParams([\"%s\",%d,\"%s\",%d,0,%d,\"%s\"])", 
            GetFamilyData(fam_id, F_NAME), GetFamilyData(fam_id, F_GANG), GetPlayerNameEx(playerid), GetPlayerData(playerid, P_FAMILY_RANK), GetPlayerSkin(playerid),
			family_colors_cef[index]);
            CEF_CREATE(playerid, 1, 2, STRING_GLOBAL);
        }
        case 1:
        {
            new fam_id = GetPlayerFamily(playerid);

            new query[144], name[25], rows;

	        mysql_format(mysql, query, sizeof query, "SELECT * FROM accounts_canvasdev WHERE family='%d'", fam_id);
	        new Cache:result = mysql_query(mysql, query);

	        rows = cache_num_rows();

	        for(new i; i < rows; i ++)
	        {
	            new family_rank = cache_get_field_content_int(i, "family_rank");
	            if(family_rank == 10)
	            {
	    	        cache_get_field_content(i, "name", name);
	            }
	        }
	        cache_delete(result);

            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof STRING_GLOBAL, "interface('Tablet').getCurrentApp().setAsideStatsData([\"%s\",0,[[\"Участников\",0,15,0],[\"Домов\",1,5,5],[\"Автомобилей\",2,6,15],[\"Гаражей\",3,2,5]],1039,[[\"Admin\",\"Лидер получил предупреждение\",1747739234]],3])", 
            name);
            CEF_CREATE(playerid, 1, 2, STRING_GLOBAL);
        }
    }
    return 1;
}