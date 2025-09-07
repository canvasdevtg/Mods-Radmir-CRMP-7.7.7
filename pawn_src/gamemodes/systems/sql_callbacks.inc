#if defined _sql_callbacks_included
    #endinput
#endif
#define _sql_callbacks_included

forward ShowForbesMoney(playerid);
public ShowForbesMoney(playerid)
{
    STRING_GLOBAL[0] = EOS;

    new rows = cache_num_rows();
    if(rows == 0)
    {
        SendClientMessage(playerid, 0xFF0000FF, "На данный момент список Forbes пуст.");
        return 1;
    }

    for(new i = 0; i < rows; i++)
    {
        new name[64], total_money[32];
        cache_get_field_content(i, "name", name, sizeof(name));
        cache_get_field_content(i, "total_money", total_money, sizeof(total_money));

        new buffer[128];
        format(buffer, sizeof(buffer), "[%d,\"%s\",\"%s\"]", i + 1, name, formatStr(total_money));

        if(i > 0) strcat(STRING_GLOBAL, ",");

        strcat(STRING_GLOBAL, buffer);
    }

    new finalString[2048];
    format(finalString, sizeof(finalString),
        "[\"FORBES - Игровая Валюта\", \"Игровой Валюты\", 0, [%s]]", STRING_GLOBAL);

    CEF_CREATE(playerid, 2, 4, "Rating", finalString);

    return 1;
}

forward ShowForbesDonate(playerid);
public ShowForbesDonate(playerid)
{
    STRING_GLOBAL[0] = EOS;

    new rows = cache_num_rows();

	if(rows == 0)
    {
        SendClientMessage(playerid, 0xFF0000FF, "На данный момент список Forbes пуст.");
        return 0;
    }

    for(new i = 0; i < rows; i++)
    {
        new name[64];
        cache_get_field_content(i, "name", name, sizeof(name));

        new total_donate = cache_get_field_content_int(i, "total_donate");

        new buffer[128];
        format(buffer, sizeof buffer, "[%d,\"%s\",\"%s\"]", i + 1, name, formatInt(total_donate));

        if(i > 0) strcat(STRING_GLOBAL, ",");

        strcat(STRING_GLOBAL, buffer);
    }

    new finalString[2046];
    format(finalString, sizeof finalString, "[\"FORBES - Донат Валюта\", \"DCOINS\", 0, [%s]]", STRING_GLOBAL);

    CEF_CREATE(playerid, 2, 4, "Rating", finalString);

    return 1;
}

forward OnShowForbesChips(playerid);
public OnShowForbesChips(playerid)
{
    STRING_GLOBAL[0] = EOS;

    new rows = cache_num_rows();

    if(rows == 0)
    {
        SendClientMessage(playerid, 0xFF0000FF, "На данный момент список Forbes пуст.");
        return 0;
    }

    for(new i = 0; i < rows; i++)
    {
        new total_count = cache_get_field_content_int(i, "total_count");

        new name[64];
        cache_get_field_content(i, "name", name, sizeof(name));

        new buffer[128];
        format(buffer, sizeof(buffer), "[%d,\"%s\",\"%s\"]", i + 1, name, formatInt(total_count));

        if(i > 0) strcat(STRING_GLOBAL, ",");
        strcat(STRING_GLOBAL, buffer);
    }

    new finalString[2048];
    format(finalString, sizeof(finalString), "[\"FORBES - Фишки\", \"Фишек\", 0, [%s]]", STRING_GLOBAL);

    CEF_CREATE(playerid, 2, 4, "Rating", finalString);

    return 1;
}
