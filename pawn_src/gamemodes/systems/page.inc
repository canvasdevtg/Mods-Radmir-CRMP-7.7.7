#if defined _page_included
    #endinput
#endif
#define _page_included

#define ITEMS_PER_PAGE 12
#define ITEMS_ACS_PAGE 12

new player_decoration_page[MAX_PLAYERS];
new player_acs_page[MAX_PLAYERS];
new player_car_acs_page[MAX_PLAYERS];

enum E_DECORATION_STRUCT
{
	E_DIR_NAME[80],
	E_NAME[32],
	E_PRICE[40],
	E_MODEL
}

new g_decoration_data[][E_DECORATION_STRUCT] =
{
	{"/poperty_accessories/3038","Украшение №1", "150", 3038},
	{"/poperty_accessories/5469","Украшение №2", "150", 5469},
	{"/poperty_accessories/5470","Украшение №3", "150", 5470},
	{"/poperty_accessories/14083","Украшение №4", "150", 14083},
	{"/poperty_accessories/14084","Украшение №5", "150", 14084},
	{"/poperty_accessories/14085","Украшение №6", "150", 14085},
	{"/poperty_accessories/14086","Украшение №7", "150", 14086},
	{"/poperty_accessories/14087","Украшение №8", "150", 14087},
	{"/poperty_accessories/14088","Украшение №9", "150", 14088},
	{"/poperty_accessories/14089","Украшение №10", "150", 14089},
	{"/poperty_accessories/14090","Украшение №11", "150", 14090},
	{"/poperty_accessories/14091","Украшение №12", "150", 14091},
	{"/poperty_accessories/14092","Украшение №13", "150", 14092},
	{"/poperty_accessories/14158","Украшение №14", "150", 14158},
	{"/poperty_accessories/14159","Украшение №15", "150", 14159},
	{"/poperty_accessories/14160","Украшение №16", "150", 14160},
	{"/poperty_accessories/14161","Украшение №17", "150", 14161},
	{"/poperty_accessories/14162","Украшение №18", "150", 14162},
	{"/poperty_accessories/14163","Украшение №19", "150", 14163},
	{"/poperty_accessories/14164","Украшение №20", "150", 14164},
	{"/poperty_accessories/14165","Украшение №21", "150", 14165},
	{"/poperty_accessories/14166","Украшение №22", "150", 14166},
	{"/poperty_accessories/14167","Украшение №23", "150", 14167},
	{"/poperty_accessories/14168","Украшение №24", "150", 14168},
	{"/poperty_accessories/14169","Украшение №25", "150", 14169},
	{"/poperty_accessories/14170","Украшение №26", "150", 14170},
	{"/poperty_accessories/14171","Украшение №27", "150", 14171},
	{"/poperty_accessories/14172","Украшение №28", "150", 14172},
	{"/poperty_accessories/14173","Украшение №29", "150", 14173},
	{"/poperty_accessories/14174","Украшение №30", "150", 14174},
	{"/poperty_accessories/14175","Украшение №31", "150", 14175},
	{"/poperty_accessories/14176","Украшение №32", "150", 14176},
	{"/poperty_accessories/14177","Украшение №33", "150", 14177},
	{"/poperty_accessories/14178","Украшение №34", "150", 14178},
	{"/poperty_accessories/14179","Украшение №35", "150", 14179},
	{"/poperty_accessories/14181","Украшение №36", "150", 14181},
	{"/poperty_accessories/14187","Украшение №37", "150", 14187},
	{"/poperty_accessories/14190","Украшение №38", "150", 14190},
	{"/poperty_accessories/14750","Украшение №39", "150", 14750},
	{"/poperty_accessories/14751","Украшение №40", "150", 14751},
	{"/poperty_accessories/14752","Украшение №41", "150", 14752},
	{"/poperty_accessories/14753","Украшение №42", "150", 14753},
	{"/poperty_accessories/14754","Украшение №43", "150", 14754},
	{"/poperty_accessories/14755","Украшение №44", "150", 14755},
	{"/poperty_accessories/14756","Украшение №45", "150", 14756},
	{"/poperty_accessories/14757","Украшение №46", "150", 14757},
	{"/poperty_accessories/14758","Украшение №47", "150", 14758},
	{"/poperty_accessories/14759","Украшение №48", "150", 14759},
	{"/poperty_accessories/14760","Украшение №49", "150", 14760},
	{"/poperty_accessories/14761","Украшение №50", "150", 14761},
	{"/poperty_accessories/15804","Украшение №51", "150", 15804},
	{"/poperty_accessories/15805","Украшение №52", "150", 15805},
	{"/poperty_accessories/15807","Украшение №53", "150", 15807},
	{"/poperty_accessories/16613","Украшение №54", "150", 16613},
	{"/poperty_accessories/16614","Украшение №55", "150", 16614},
	{"/poperty_accessories/16615","Украшение №56", "150", 16615},
	{"/poperty_accessories/16616","Украшение №57", "150", 16616},
	{"/poperty_accessories/16617","Украшение №58", "150", 16617},
	{"/poperty_accessories/16618","Украшение №59", "150", 16618},
	{"/poperty_accessories/16619","Украшение №60", "150", 16619},
	{"/poperty_accessories/16620","Украшение №61", "150", 16620},
	{"/poperty_accessories/16621","Украшение №62", "150", 16621},
	{"/poperty_accessories/16622","Украшение №63", "150", 16622},
	{"/poperty_accessories/16623","Украшение №64", "150", 16623},
	{"/poperty_accessories/16624","Украшение №65", "150", 16624},
	{"/poperty_accessories/16626","Украшение №66", "150", 16626},
	{"/poperty_accessories/16627","Украшение №67", "150", 16627},
	{"/poperty_accessories/16628","Украшение №68", "150", 16628},
	{"/poperty_accessories/16629","Украшение №69", "150", 16629},
	{"/poperty_accessories/16630","Украшение №70", "150", 16630},
	{"/poperty_accessories/16631","Украшение №71", "150", 16631},
	{"/poperty_accessories/16632","Украшение №72", "150", 16632},
	{"/poperty_accessories/16633","Украшение №73", "150", 16633},
	{"/poperty_accessories/16635","Украшение №74", "150", 16635},
	{"/poperty_accessories/16636","Украшение №75", "150", 16636},
	{"/poperty_accessories/16637","Украшение №76", "150", 16637},
	{"/poperty_accessories/16639","Украшение №77", "150", 16639},
	{"/poperty_accessories/16640","Украшение №78", "150", 16640},
	{"/poperty_accessories/16641","Украшение №79", "150", 16641},
	{"/poperty_accessories/17154","Украшение №80", "150", 17154},
	{"/poperty_accessories/17258","Украшение №81", "150", 17258},
	{"/poperty_accessories/17976","Украшение №82", "150", 17976}
};

enum E_ACCESSORY_CAR_STRUCT
{
	E_ACS_CAR_IMAGE[80],
	E_NAME[32],
	E_PRICE[40],
	E_MODEL
}

new g_accessory_car_data[][E_ACCESSORY_CAR_STRUCT] =
{
	{"/accessories/15736", "Ёлка на крышу", "500", 15736},
	{"/accessories/15737", "Антены", "500", 15737},
	{"/accessories/15738", "Сноуборд", "500", 15738},
	{"/accessories/15739", "Автобокс", "500", 15739},
	{"/accessories/15740", "Ватрушка", "500", 15740},
	{"/accessories/15741", "Багажник на крышу", "500", 15741},
	{"/accessories/15892", "Канистры", "500", 15892},
	{"/accessories/15894", "Маскировочная сеть", "500", 15894},
	{"/accessories/15895", "Маскировочная сеть", "500", 15895},
	{"/accessories/15896", "Колючая проволока", "500", 15896},
	{"/accessories/15967", "Кенгурятник", "500", 15967},
	{"/accessories/16229", "Велосипед", "500", 16229},
	{"/accessories/16512", "Доска для серфинга", "500", 16512},
	{"/accessories/16866", "Подарки", "500", 16866},
	{"/accessories/16867", "Феерверки", "500", 16867},
	{"/accessories/17163", "Гидроцикл", "500", 17163},
	{"/accessories/17273", "Мини гелик", "500", 17273},
	{"/accessories/17637", "Труп", "500", 17637},
	{"/accessories/17272", "Лодка", "500", 17272},
	{"/accessories/17607", "Иж педальный", "500", 17607},
	{"/accessories/18540", "Пуш бампер", "500", 18540}
};

enum E_ACCESSORY_STRUCT
{
    E_MODEL_ID,
    E_NAME[50],
    E_ITEM_ID,
    E_PRICE[40],
	E_ACS_IMAGE[80]
}

new g_accessory_data[][E_ACCESSORY_STRUCT] = 
{
    {10983, "Шапка c Рогами", 185, "333", "/accessories/10983"},
    {10984, "Маска Оленя", 183, "333", "/accessories/10984"},
    {10985, "Маска Лося", 183, "333", "/accessories/10985"},
    {10986, "Снеговик", 183, "333", "/accessories/10986"},
    {10987, "Новогодний Пёс", 183, "333", "/accessories/10987"}, 
    {10988, "Снеговик №2", 183, "333", "/accessories/10988"},
    {10989, "Бык", 183, "333", "/accessories/10989"},
    {10990, "Стакан Гучи", 221, "222", "/accessories/10990"},
    {10991, "Леденец в руку", 221, "333", "/accessories/10991"},
    {10992, "Леденец в руку №2", 221, "333", "/accessories/10992"},
    {10996, "Йода", 183, "555", "/accessories/10996"},  
    {10997, "Жираф", 183, "1111", "/accessories/10997"},
    {10998, "Грязная Ушанка", 185, "333", "/accessories/10998"},
    {10999, "Розовая Ушанка", 185, "666", "/accessories/10999"},
    {11000, "Шапка с Оленями", 185, "222", "/accessories/11000"},
    {11002, "Шарф", 246, "333", "/accessories/11002"},
    {11003, "Шарф №2", 246, "333", "/accessories/11003"},
    {11004, "Рога", 185, "111", "/accessories/11004"},
    {11005, "Снеговик №3", 183, "222", "/accessories/11005"},
    {11006, "Снеговик №4", 275, "444", "/accessories/11006"},
    {11007, "Рога №2", 185, "222", "/accessories/11007"},
    {11008, "Рога №3", 185, "333", "/accessories/11008"},
    {11009, "Рога №4", 185, "444", "/accessories/11009"},
    {14046, "Клоун", 183, "333", "/accessories/14046"},
    {14047, "Гоблин", 183, "333", "/accessories/14047"},
    {14048, "Испытуемый", 183, "333", "/accessories/14048"},
    {14049, "Джокер", 183, "333", "/accessories/14049"},
    {14050, "Зомбо", 183, "333", "/accessories/14050"},
    {14051, "Техаский", 183, "333", "/accessories/14051"},
    {14052, "Тыква", 183, "333", "/accessories/14052"},
    {14053, "Маерс", 183, "333", "/accessories/14053"},
    {14054, "Косто", 183, "333", "/accessories/14054"},
    {14055, "Чёртик", 183, "333", "/accessories/14055"},
    {14056, "Крик", 183, "333", "/accessories/14056"},
    {14057, "Уродец", 183, "333", "/accessories/14057"},
    {14058, "Аристократ", 183, "333", "/accessories/14058"},
    {14059, "Оно", 183, "333", "/accessories/14059"},
    {14060, "Техас", 183, "333", "/accessories/14060"},
    {14061, "Зомби", 183, "333", "/accessories/14061"},
    {14062, "Краснозомб", 183, "333", "/accessories/14062"},
    {14063, "Инопланетян", 183, "333", "/accessories/14063"},
    {14064, "Инфицированный", 183, "333", "/accessories/14064"},
    {14065, "Вурхис", 183, "333", "/accessories/14065"},
    {14066, "Психозомбо", 183, "333", "/accessories/14066"},
    {14067, "Двухзомбо", 183, "333", "/accessories/14067"},
    {14069, "Чужой", 183, "333", "/accessories/14069"},
    {14070, "Охотник", 183, "333", "/accessories/14070"},
    {14071, "Бабаяга", 183, "333", "/accessories/14071"},
    {14072, "Анонимус", 183, "333", "/accessories/14072"},
    {14073, "Ктулху", 183, "333", "/accessories/14073"},
    {14074, "Сумка Модника", 219, "111", "/accessories/14074"},
    {14075, "Рюкзак Хеллуин", 222, "333", "/accessories/14075"},
    {14076, "Летучая Мышь", 246, "111", "/accessories/14076"},
    {14077, "Привидение", 183, "333", "/accessories/14077"},
    {14195, "Мешок Конфет", 222, "333", "/accessories/14195"},
    {14196, "New Year Посох", 221, "1111", "/accessories/14196"},
    {14197, "New Year Посох", 221, "1111", "/accessories/14197"},
    {14200, "Галстук", 246, "111", "/accessories/14200"},
    {14201, "Гринч", 183, "444", "/accessories/14201"},
    {14202, "Борода", 183, "222", "/accessories/14202"},
    {14203, "Фрости Шапка", 185, "111", "/accessories/14203"},
    {14204, "Рога №5", 185, "333", "/accessories/14204"},
    {14205, "Диадема", 185, "555", "/accessories/14205"},
    {14206, "Ободок", 185, "333", "/accessories/14206"},
    {14207, "Рюкзак Ангела", 222, "444", "/accessories/14207"},
    {14456, "Черный Аноним", 183, "333", "/accessories/14456"},
    {14457, "Колючий Чокер", 260, "111", "/accessories/14457"},
    {14458, "Розовый Чокер", 260, "111", "/accessories/14458"},
    {14459, "Черный Чокер", 260, "111", "/accessories/14459"},
    {14460, "Шапка из Фольги", 185, "111", "/accessories/14460"},
    {14461, "Противогаз", 183, "111", "/accessories/14461"},
    {14462, "Очки Богдана", 181, "111", "/accessories/14462"},
    {14463, "Ободок Дьявола", 185, "111", "/accessories/14463"},
    {14464, "Ободок Кошки", 185, "111", "/accessories/14464"},
    {14465, "Маска Кошки", 183, "111", "/accessories/14465"},
    {14466, "Модный Чокер", 260, "111", "/accessories/14466"},
    {14519, "Крестик", 246, "111", "/accessories/14519"},
    {14520, "Маска Грабителя", 183, "111", "/accessories/14520"},
    {14521, "Маска Богача", 183, "111", "/accessories/14521"},
    {14522, "Маска Гонщика", 183, "111", "/accessories/14522"},
    {14596, "Скрипка", 291, "222", "/accessories/14596"},
    {14597, "Острые Козырьки", 185, "333", "/accessories/14597"},
    {14598, "Златые Часы", 221, "111", "/accessories/14598"},
    {14599, "Шляпа Мафиози", 185, "222", "/accessories/14599"},
    {14600, "Чемоданчик", 221, "333", "/accessories/14600"},
    {14613, "Часы", 225, "111", "/accessories/14613"},
    {14614, "Ролекс", 225, "111", "/accessories/14614"},
    {14615, "Часы №2", 225, "111", "/accessories/14615"},
    {14616, "Ролекс №2", 225, "111", "/accessories/14616"},
    {14617, "Часы №3", 225, "111", "/accessories/14617"},
    {14618, "Миронов Ролекс", 225, "111", "/accessories/14618"},
    {14619, "Ролекс №3", 225, "111", "/accessories/14619"},
    {14620, "Златый Браслет", 221, "111", "/accessories/14620"},
    {14621, "Серый Браслет", 221, "111", "/accessories/14621"},
    {14622, "Картье", 246, "111", "/accessories/14622"},
    {14623, "Пришелец", 246, "111", "/accessories/14623"},
    {14624, "Череп", 246, "111", "/accessories/14624"},
    {14625, "Инь Янь", 246, "111", "/accessories/14625"},
    {14627, "Питбуль", 246, "111", "/accessories/14627"},
    {14628, "Цепочка Дьявола", 246, "333", "/accessories/14628"},
    {14695, "Тыква", 183, "111", "/accessories/14695"},
    {14696, "Рога Дьявола", 185, "111", "/accessories/14696"},
    {14704, "Плащ", 263, "1111", "/accessories/14704"},
    {14705, "Лавовый плащ", 263, "666", "/accessories/14705"},
    {14706, "Рюкзак Панцирь", 222, "444", "/accessories/14706"},
    {14707, "Рюкзак Котёл", 222, "333", "/accessories/14707"},
    {14708, "Рюкзак Из Китая", 222, "333", "/accessories/14708"},
    {14709, "Мешок Леденец", 222, "333", "/accessories/14709"},
    {14724, "Шляпа Скелета", 185, "333", "/accessories/14724"},
    {14725, "Король Птиц", 183, "333", "/accessories/14725"},
    {14726, "Самурай", 185, "333", "/accessories/14726"},
    {14727, "Маска Лешего", 183, "333", "/accessories/14727"},
    {14728, "Древесная Маска", 183, "333", "/accessories/14728"},
    {14729, "Привидение", 183, "333", "/accessories/14729"},
    {14734, "Викинг", 183, "333", "/accessories/14734"},
    {14735, "Гадюка", 246, "333", "/accessories/14735"},
    {14736, "Сова", 275, "333", "/accessories/14736"},
    {14737, "Доспехи", 246, "333", "/accessories/14737"},
    {14738, "Привидение", 275, "222", "/accessories/14738"},
    {14739, "Крылья Гаргуньи", 263, "444", "/accessories/14739"},
    {14740, "Коса", 221, "333", "/accessories/14740"},
    {14741, "Шляпа Крюгера", 185, "333", "/accessories/14741"},
    {14742, "Когти Крюгера", 221, "111", "/accessories/14742"},
    {14743, "Цепочка Смерти", 246, "111", "/accessories/14743"},
    {14778, "Крылья Вампира", 263, "666", "/accessories/14778"},
    {14779, "Зеленые Крылья", 263, "444", "/accessories/14779"},
    {14780, "Красные Крылья", 263, "444", "/accessories/14780"},
    {14781, "Синие Крылья", 263, "444", "/accessories/14781"},
    {14782, "Черные Крылья", 263, "444", "/accessories/14782"},
    {14790, "Респиратор", 183, "222", "/accessories/14790"},
    {14792, "Шапка СССР", 185, "333", "/accessories/14792"},
    {14793, "Шапка СССР №2", 185, "333", "/accessories/14793"},
    {14794, "Шлем Алтынь", 183, "333", "/accessories/14794"},
    {14795, "Шлем Алтынь №2", 183, "333", "/accessories/14795"},
    {14796, "Белый Броник", 277, "222", "/accessories/14796"},
    {14797, "Гуччи Броник", 277, "333", "/accessories/14797"},
    {14798, "Луи Броник", 277, "333", "/accessories/14798"},
    {15744, "Рюкзак Лесоруба", 222, "333", "/accessories/15744"},
    {15745, "Рюкзак Шахтера", 222, "333", "/accessories/15745"},
    {15746, "Рюкзак Пингвин", 222, "333", "/accessories/15746"},
    {15747, "Рюкзак Фейерверк", 222, "333", "/accessories/15747"},
    {15748, "Рюкзак Бочка", 222, "333", "/accessories/15748"},
    {15749, "Рюкзак Печь", 222, "333", "/accessories/15749"},
    {15750, "Рюкзак Акула", 222, "333", "/accessories/15750"},
    {15751, "C.P Шапка", 185, "222", "/accessories/15751"},
    {15752, "Шапка", 185, "111", "/accessories/15752"},
    {15753, "Мишапка", 183, "333", "/accessories/15753"},
    {15754, "Звезда", 185, "333", "/accessories/15754"},
    {15755, "Шапка СССР №3", 185, "333", "/accessories/15755"},
    {15777, "Нимб", 185, "444", "/accessories/15777"},
    {15778, "Шапка Лётчика", 185, "222", "/accessories/15778"},
    {15779, "Очки Зимние", 181, "111", "/accessories/15779"},
    {15780, "Очки Учёного", 181, "111", "/accessories/15780"},
    {15781, "Очки Учёной", 181, "111", "/accessories/15781"},
    {15782, "Рюкзак Бинокль", 222, "222", "/accessories/15782"},
    {15783, "Шляпа Мороз", 185, "333", "/accessories/15783"},
    {15784, "Рюкзак Сундук", 222, "333", "/accessories/15784"},
    {15785, "Зимний Король", 183, "333", "/accessories/15785"},
    {15786, "Щелкунчик", 183, "222", "/accessories/15786"},
    {15787, "Рога", 185, "111", "/accessories/15787"},
    {15788, "Шарфик", 246, "111", "/accessories/15788"},
    {15789, "Маска Волка", 183, "222", "/accessories/15789"},
    {15790, "Маска Ёлка", 183, "333", "/accessories/15790"},
    {15791, "Посох Шар", 221, "1111", "/accessories/15791"},
    {15792, "Якорь", 221, "666", "/accessories/15792"},
    {15793, "Кирка", 221, "666", "/accessories/15793"},
    {15794, "Посох Леденец", 221, "1111", "/accessories/15794"},
    {15797, "Шляпа Моряка", 185, "111", "/accessories/15797"},
    {15810, "Шапка Ушанка", 185, "111", "/accessories/15810"},
    {15847, "Золотая Маска", 183, "111", "/accessories/15847"},
    {15848, "Корона", 185, "333", "/accessories/15848"},
    {15849, "Куфия", 185, "222", "/accessories/15849"},
    {15850, "Кинжал", 292, "111", "/accessories/15850"},
    {15851, "Сумка Бейп", 222, "444", "/accessories/15851"},
    {15875, "Курица", 183, "555", "/accessories/15875"},
    {15876, "Маска Заяц", 183, "555", "/accessories/15876"},
    {15877, "Пасхальное Яйцо", 222, "444", "/accessories/15877"},
    {15878, "Заяц Фиолетовый", 222, "1111", "/accessories/15878"},
    {15879, "Заяц Розовый", 222, "1111", "/accessories/15879"},
    {15880, "Космонавт", 183, "111", "/accessories/15880"},
    {15881, "Шляпа Медведь", 183, "333", "/accessories/15881"},
    {15882, "Шляпа Волчонок", 183, "333", "/accessories/15882"},
    {15883, "Панама", 185, "333", "/accessories/15883"},
    {15884, "Черные Ушки", 185, "11111", "/accessories/15884"},
    {15885, "Розовые Ушки", 185, "11111", "/accessories/15885"},
    {15886, "Шляпа Мальборо", 185, "333", "/accessories/15886"},
    {15887, "Два Ножа", 292, "333", "/accessories/15887"},
    {15888, "Кобура Гучи", 292, "666", "/accessories/15888"},
    {15889, "Патронаши", 277, "444", "/accessories/15889"},
    {15890, "Военный Броник", 277, "666", "/accessories/15890"},
    {15891, "Военный Рюкзак", 222, "666", "/accessories/15891"},
    {15902, "Мотошлём", 183, "111", "/accessories/15902"},
    {15968, "Водолаз", 183, "111", "/accessories/15968"},
    {15969, "Бурундук", 275, "333", "/accessories/15969"},
    {16194, "Маска Водолаза", 183, "222", "/accessories/16194"},
    {16195, "Круг Собачка", 220, "444", "/accessories/16195"},
    {16221, "Круг Единорог", 220, "444", "/accessories/16221"},
    {16222, "Круг Уточка", 220, "444", "/accessories/16222"},
    {16223, "Рюкзак Уточка", 222, "333", "/accessories/16223"},
    {16224, "Кепка Ушки", 185, "333", "/accessories/16224"},
    {16225, "Маска Лягушка", 183, "555", "/accessories/16225"},
    {16226, "Шляпа Арбузик", 183, "444", "/accessories/16226"},
    {16227, "Фараон", 183, "333", "/accessories/16227"},
    {16228, "Рюкзак Кобра", 222, "555", "/accessories/16228"},
    {16454, "Рюкзак Хамелеон", 222, "444", "/accessories/16454"},
    {16455, "Желтый Рюкзак", 222, "444", "/accessories/16455"},
    {16456, "Рюкзак Дракон", 222, "444", "/accessories/16456"},
    {16457, "Рюкзак Банан", 222, "444", "/accessories/16457"},
    {16458, "Рюкзак Бамбук", 222, "444", "/accessories/16458"},
    {16459, "Рюкзак Акулка", 222, "555", "/accessories/16459"},
    {16460, "Рюкзак Йода", 222, "555", "/accessories/16460"},
    {16462, "Золотое Ожерелье", 246, "444", "/accessories/16462"},
    {16463, "Скейт №1", 324, "2222", "/accessories/16463"},
    {16464, "Скейт №2", 324, "2222", "/accessories/16464"},
    {16465, "Скейт №3", 324, "2222", "/accessories/16465"},
    {16466, "Ожерелье Цветы", 246, "111", "/accessories/16466"},
    {16468, "Рюкзак Чешуя", 222, "666", "/accessories/16468"},
    {16469, "Золотой Мешок", 222, "666", "/accessories/16469"},
    {16470, "Рюкзак Грут", 222, "1111", "/accessories/16470"},
    {16471, "Рюкзак Анаконда", 222, "666", "/accessories/16471"},
    {16472, "Денежный Мешок", 222, "444", "/accessories/16472"},
    {16473, "Змеиный Посох", 221, "1111", "/accessories/16473"},
    {16507, "Динозаврик", 183, "666", "/accessories/16507"},
    {16508, "Красный Дино", 183, "444", "/accessories/16508"},
    {16509, "Золотое Ожерелье", 246, "111", "/accessories/16509"},
    {16510, "Маска Тропика", 183, "666", "/accessories/16510"},
    {16511, "Маска Фараона", 183, "444", "/accessories/16511"},
    {16512, "Доска для Серфа", 291, "333", "/accessories/16512"},
    {16591, "Рюкзак Гробик", 222, "333", "/accessories/16591"},
    {16592, "Рюкзак Паук", 222, "444", "/accessories/16592"},
    {16593, "Красный Рюкзак", 222, "222", "/accessories/16593"},
    {16594, "Черный Рюкзак", 222, "222", "/accessories/16594"},
    {16595, "Хаги Ваги", 222, "555", "/accessories/16595"},
    {16596, "Черный Медведь", 222, "666", "/accessories/16596"},
    {16597, "Крысиная Тыква", 219, "444", "/accessories/16597"},
    {16598, "Летучая Мышь", 219, "555", "/accessories/16598"},
    {16599, "Чумной Доктор", 183, "666", "/accessories/16599"},
    {16600, "Рука на Плечо", 275, "444", "/accessories/16600"},
    {16601, "Рюкзак Пила", 222, "555", "/accessories/16601"},
    {16602, "Рюкзак Детонатор", 222, "555", "/accessories/16602"},
    {16603, "Рюкзак Глазастик", 222, "555", "/accessories/16603"},
    {16604, "Крылья Черные", 291, "666", "/accessories/16604"},
    {16605, "Очки Крылья", 181, "111", "/accessories/16605"},
    {16606, "Бронежилет Зомби", 277, "222", "/accessories/16606"},
    {16607, "Рюкзак Клетка", 222, "444", "/accessories/16607"},
    {16608, "Монстрик", 222, "555", "/accessories/16608"},
    {16609, "Гробик №1", 222, "555", "/accessories/16609"},
    {16610, "Гробик №2", 222, "555", "/accessories/16610"},
    {16611, "Гробик №3", 222, "555", "/accessories/16611"},
    {16665, "Красный Меч", 221, "888", "/accessories/16665"},
    {16678, "Скейт №4", 324, "2222", "/accessories/16678"},
    {16679, "Скейт №5", 324, "2222", "/accessories/16679"},
    {16682, "Синий Меч", 221, "888", "/accessories/16682"},
    {16697, "Дракон", 275, "6666", "/accessories/16697"},
    {16740, "Рога Оленя", 185, "222", "/accessories/16740"},
    {16741, "Пингвинчики", 185, "111", "/accessories/16741"},
    {16742, "Очки Снежинки", 181, "222", "/accessories/16742"},
    {16743, "Нос Моркова", 183, "222", "/accessories/16743"},
    {16744, "Шапка №1", 185, "222", "/accessories/16744"},
    {16745, "Шапка №2", 185, "222", "/accessories/16745"},
    {16746, "Шапка №3", 185, "222", "/accessories/16746"},
    {16747, "Шапка №4", 185, "333", "/accessories/16747"},
    {16748, "Рюкзак Гусь", 222, "333", "/accessories/16748"},
    {16749, "Рюкзак Олень", 222, "444", "/accessories/16749"},
    {16774, "Зимний Топор", 221, "555", "/accessories/16774"},
    {16775, "Неоновые Очки", 181, "555", "/accessories/16775"},
    {16776, "Шарф Гучи", 246, "444", "/accessories/16776"},
    {16777, "Куфия Клечатая", 183, "333", "/accessories/16777"},
    {16778, "Рога Новогодние", 185, "444", "/accessories/16778"},
    {16779, "Плащ Новогодний", 263, "666", "/accessories/16779"},
    {16780, "Пурпурный Мешок", 222, "444", "/accessories/16780"},
    {16781, "Оранжевый Мешок", 222, "444", "/accessories/16781"},
    {16782, "Кошмарный Санта", 222, "666", "/accessories/16782"},
    {16783, "Шляпка", 185, "333", "/accessories/16783"},
    {16784, "Маска Робосанты", 183, "444", "/accessories/16784"},
    {16785, "Рюкзак Сиба Ину", 222, "555", "/accessories/16785"},
    {16786, "Сумка Тетрис", 219, "333", "/accessories/16786"},
    {16787, "Рюкзак с Ушами", 222, "333", "/accessories/16787"}
};

stock SendDecorationPage(playerid, page)
{
    STRING_GLOBAL[0] = EOS;

    new total_items = sizeof g_decoration_data;
    new total_pages = (total_items + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE;

    new start_idx = page * ITEMS_PER_PAGE;
    new end_idx = start_idx + ITEMS_PER_PAGE;

    if(start_idx >= total_items)
    {
        start_idx = total_items - ITEMS_PER_PAGE;
        if(start_idx < 0) start_idx = 0;
    }

    if(end_idx > total_items)
    {
        end_idx = total_items;
    }

    new back_text[32] = "Назад";
    new forward_text[32] = "Вперед";

    if(page == 0)
    {
        format(back_text, sizeof back_text, "Недоступно");
    }
    if(page >= total_pages - 1)
    {
        format(forward_text, sizeof forward_text, "Недоступно");
    }

    format(STRING_GLOBAL, sizeof STRING_GLOBAL, "[\"Украшения для дома\",[\"%d / %d\",\"%s\",\"%s\"],[", page + 1, total_pages, back_text, forward_text);

    for(new idx = start_idx; idx < end_idx; idx++)
    {
        format(STRING_GLOBAL, sizeof STRING_GLOBAL, "%s[\"%s\",\"%s\",\"%s\",%d],",
            STRING_GLOBAL,
            g_decoration_data[idx][E_DIR_NAME],
            g_decoration_data[idx][E_NAME],
            g_decoration_data[idx][E_PRICE],
            idx + 1
        );
    }

    new str_len = strlen(STRING_GLOBAL);
    if(str_len > 0) strdel(STRING_GLOBAL, str_len - 1, str_len);

    strcat(STRING_GLOBAL, "],1]");

    CEF_CREATE(playerid, 2, 4, "ItemStore", STRING_GLOBAL);

    return 1;
}

stock SendAcsPage(playerid, page_acs)
{
    STRING_GLOBAL[0] = EOS;

    new total_items_acs = sizeof g_accessory_data;
    new total_pages_acs = (total_items_acs + ITEMS_ACS_PAGE - 1) / ITEMS_ACS_PAGE;

    new start_idx_acs = page_acs * ITEMS_ACS_PAGE;
    new end_idx_acs = start_idx_acs + ITEMS_ACS_PAGE;

    if(start_idx_acs >= total_items_acs)
    {
        start_idx_acs = total_items_acs - ITEMS_ACS_PAGE;
        if(start_idx_acs < 0) start_idx_acs = 0;
    }

    if(end_idx_acs > total_items_acs)
    {
        end_idx_acs = total_items_acs;
    }

    new back_text[32] = "Назад";
    new forward_text[32] = "Вперед";

    if(page_acs == 0)
    {
        format(back_text, sizeof back_text, "Недоступно");
    }
    if(page_acs >= total_pages_acs - 1)
    {
        format(forward_text, sizeof forward_text, "Недоступно");
    }

    format(STRING_GLOBAL, sizeof STRING_GLOBAL, "[\"Эксклюзивные аксессуары\",[\"%d / %d\",\"%s\",\"%s\"],[", page_acs + 1, total_pages_acs, back_text, forward_text);

    for(new idx = start_idx_acs; idx < end_idx_acs; idx++)
    {
        format(STRING_GLOBAL, sizeof STRING_GLOBAL, "%s[\"%s\",\"%s\",\"%s\",%d],",
            STRING_GLOBAL,
            g_accessory_data[idx][E_ACS_IMAGE],
            g_accessory_data[idx][E_NAME],
            g_accessory_data[idx][E_PRICE],
            idx + 1
        );
    }

    new str_len = strlen(STRING_GLOBAL);
    if(str_len > 0) strdel(STRING_GLOBAL, str_len - 1, str_len);

    strcat(STRING_GLOBAL, "],1]");

    CEF_CREATE(playerid, 2, 4, "ItemStore", STRING_GLOBAL);

    return 1;
}

stock SendCarAcsPage(playerid, page_car_acs)
{
    STRING_GLOBAL[0] = EOS;

    new total_items_car_acs = sizeof g_accessory_car_data;
    new total_pages_car_acs = (total_items_car_acs + 12 - 1) / 12;

    new start_idx_car_acs = page_car_acs * 12;
    new end_idx_car_acs = start_idx_car_acs + 12;

    if(start_idx_car_acs >= total_items_car_acs)
    {
        start_idx_car_acs = total_items_car_acs - 12;
        if(start_idx_car_acs < 0) start_idx_car_acs = 0;
    }

    if(end_idx_car_acs > total_items_car_acs)
    {
        end_idx_car_acs = total_items_car_acs;
    }

    new back_text[32] = "Назад";
    new forward_text[32] = "Вперед";

    if(page_car_acs == 0)
    {
        format(back_text, sizeof back_text, "Недоступно");
    }
    if(page_car_acs >= total_pages_car_acs - 1)
    {
        format(forward_text, sizeof forward_text, "Недоступно");
    }

    format(STRING_GLOBAL, sizeof STRING_GLOBAL, "[\"Украшения для транспорта\",[\"%d / %d\",\"%s\",\"%s\"],[", page_car_acs + 1, total_pages_car_acs, back_text, forward_text);

    for(new idx = start_idx_car_acs; idx < end_idx_car_acs; idx++)
    {
		format(STRING_GLOBAL, sizeof STRING_GLOBAL, "%s[\"%s\",\"%s\",\"%s\",%d],",
            STRING_GLOBAL,
            g_accessory_car_data[idx][E_ACS_CAR_IMAGE],
            g_accessory_car_data[idx][E_NAME],
            g_accessory_car_data[idx][E_PRICE],
            idx + 1
        );
    }

    new str_len = strlen(STRING_GLOBAL);
    if(str_len > 0) strdel(STRING_GLOBAL, str_len - 1, str_len);

    strcat(STRING_GLOBAL, "],1]");

    CEF_CREATE(playerid, 2, 4, "ItemStore", STRING_GLOBAL);

    return 1;
}

public: ItemStoreMenu_OnCategory(playerid, category)
{
    if(category == 1)
    {
		if(GetPVarInt(playerid, "BuyHomeAcs") == 1)
	    {
            if(player_decoration_page[playerid] > 0)
            {
                player_decoration_page[playerid]--;
                CEF_HIDE(playerid, "ItemStore");
			    PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
                return SendDecorationPage(playerid, player_decoration_page[playerid]);
            }
		    else
		    {
			    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		    }
        }
		if(GetPVarInt(playerid, "BuyDonateAcs") == 1)
	    {
			if(player_acs_page[playerid] > 0)
            {
                player_acs_page[playerid]--;
                CEF_HIDE(playerid, "ItemStore");
			    PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
                return SendAcsPage(playerid, player_acs_page[playerid]);
            }
		    else
		    {
			    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		    }
		}
		if(GetPVarInt(playerid, "BuyDonateCarAcs") == 1)
	    {
			if(player_car_acs_page[playerid] > 0)
            {
                player_car_acs_page[playerid]--;
                CEF_HIDE(playerid, "ItemStore");
			    PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
                return SendCarAcsPage(playerid, player_car_acs_page[playerid]);
            }
		    else
		    {
			    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		    }
		}
	}
    else if(category == 2)
    {
		if(GetPVarInt(playerid, "BuyHomeAcs") == 1)
	    {
            new total_pages = (sizeof g_decoration_data + ITEMS_PER_PAGE - 1) / ITEMS_PER_PAGE;

            if(player_decoration_page[playerid] < (total_pages - 1))
            {
                player_decoration_page[playerid]++;
                CEF_HIDE(playerid, "ItemStore");
			    PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
			    return SendDecorationPage(playerid, player_decoration_page[playerid]);
		    }
		    else
		    {
			    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		    } 
	    }
		if(GetPVarInt(playerid, "BuyDonateAcs") == 1)
	    {
            new total_pages_acs = (sizeof g_accessory_data + ITEMS_ACS_PAGE - 1) / ITEMS_ACS_PAGE;

            if(player_acs_page[playerid] < (total_pages_acs - 1))
            {
                player_acs_page[playerid]++;
                CEF_HIDE(playerid, "ItemStore");
			    PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
			    return SendAcsPage(playerid, player_acs_page[playerid]);
		    }
		    else
		    {
			    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		    } 
		}
		if(GetPVarInt(playerid, "BuyDonateCarAcs") == 1)
	    {
            new total_pages_acs = (sizeof g_accessory_car_data + 12 - 1) / 12;

            if(player_car_acs_page[playerid] < (total_pages_acs - 1))
            {
                player_car_acs_page[playerid]++;
                CEF_HIDE(playerid, "ItemStore");
			    PlayerPlaySound(playerid, 1057, 0.0, 0.0, 0.0);
			    return SendCarAcsPage(playerid, player_car_acs_page[playerid]);
		    }
		    else
		    {
			    PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
		    } 
		}  
    }
    return 1;
}

public:ItemStoreMenu_OnBuy(playerid, event)
{
	if(GetPVarInt(playerid, "Items") == 1)
	{
		if(item_store_kd[playerid] != 0) return 1;

        if(QueryPlayerDonationBalance(playerid) < 3500) return GameText(playerid, "~r~Недостаточно Средств", 4000, 3);
					
		if(GetInventorySlots(playerid) == -1) return GameText(playerid, "В вашем инвентаре нет свободного места", 3000, 0);

		ProcessPlayerCredit(playerid, -3500);

	    GiveIteam(playerid, 288, 1, 1, 0);

		SCM(playerid, 0xFFFFFFFF, "{"SERVER_COLOR"}Вы успешно приобрели: {FFFFFF}Ценная бумага {"SERVER_COLOR"}в количестве {FFFFFF}1 шт. {"SERVER_COLOR"}за {FFFFFF}3500 [DCOINS]");
	}
	if(GetPVarInt(playerid, "Items") == 2)
	{
		if(item_store_kd[playerid] != 0) return 1;

        if(QueryPlayerDonationBalance(playerid) < 200) return GameText(playerid, "~r~Недостаточно Средств", 4000, 3);
					
		if(GetInventorySlots(playerid) == -1) return GameText(playerid, "В вашем инвентаре нет свободного места", 3000, 0);

		ProcessPlayerCredit(playerid, -200);

	    GiveIteam(playerid, 361, 1, 1, 0);

		SCM(playerid, 0xFFFFFFFF, "{"SERVER_COLOR"}Вы успешно приобрели: {FFFFFF}Домкрат {"SERVER_COLOR"}в количестве {FFFFFF}1 шт. {"SERVER_COLOR"}за {FFFFFF}200 [DCOINS]");
	}
	if(GetPVarInt(playerid, "Items") == 3)
	{
		if(item_store_kd[playerid] != 0) return 1;

        if(QueryPlayerDonationBalance(playerid) < 250) return GameText(playerid, "~r~Недостаточно Средств", 4000, 3);
					
		if(GetInventorySlots(playerid) == -1) return GameText(playerid, "В вашем инвентаре нет свободного места", 3000, 0);

		ProcessPlayerCredit(playerid, -250);

	    GiveIteam(playerid, 369, 1, 1, 0);

		SCM(playerid, 0xFFFFFFFF, "{"SERVER_COLOR"}Вы успешно приобрели: {FFFFFF}Болгарка {"SERVER_COLOR"}в количестве {FFFFFF}1 шт. {"SERVER_COLOR"}за {FFFFFF}200 [DCOINS]");
	}
	if(GetPVarInt(playerid, "Items") == 4)
	{
		if(item_store_kd[playerid] != 0) return 1;

        if(QueryPlayerDonationBalance(playerid) < 150) return GameText(playerid, "~r~Недостаточно Средств", 4000, 3);
					
		if(GetInventorySlots(playerid) == -1) return GameText(playerid, "В вашем инвентаре нет свободного места", 3000, 0);

		ProcessPlayerCredit(playerid, -150);

	    GiveIteam(playerid, 44, 1, 1, 0);

		SCM(playerid, 0xFFFFFFFF, "{"SERVER_COLOR"}Вы успешно приобрели: {FFFFFF}Рем комплект {"SERVER_COLOR"}в количестве {FFFFFF}1 шт. {"SERVER_COLOR"}за {FFFFFF}200 [DCOINS]");
	}
    if(GetPVarInt(playerid, "Cases") == 1)
	{
		if(item_store_kd[playerid] != 0) return 1;

        if(QueryPlayerDonationBalance(playerid) < 150) return GameText(playerid, "~r~Недостаточно Средств", 4000, 3);
					
		if(GetInventorySlots(playerid) == -1) return GameText(playerid, "В вашем инвентаре нет свободного места", 3000, 0);

		ProcessPlayerCredit(playerid, -150);

	    GiveIteam(playerid, 258, 1, 1, 0);

		SCM(playerid, 0xFFFFFFFF, "{"SERVER_COLOR"}Вы успешно приобрели: {FFFFFF}Кейс Форсаж {"SERVER_COLOR"}в количестве {FFFFFF}1 шт. {"SERVER_COLOR"}за {FFFFFF}150 [DCOINS]");
	}
	if(GetPVarInt(playerid, "Cases") == 2)
	{
		if(item_store_kd[playerid] != 0) return 1;

        if(QueryPlayerDonationBalance(playerid) < 150) return GameText(playerid, "~r~Недостаточно Средств", 4000, 3);
					
		if(GetInventorySlots(playerid) == -1) return GameText(playerid, "В вашем инвентаре нет свободного места", 3000, 0);

		ProcessPlayerCredit(playerid, -150);

	    GiveIteam(playerid, 261, 1, 1, 0);

		SCM(playerid, 0xFFFFFFFF, "{"SERVER_COLOR"}Вы успешно приобрели: {FFFFFF}Кейс Темные дела {"SERVER_COLOR"}в количестве {FFFFFF}1 шт. {"SERVER_COLOR"}за {FFFFFF}150 [DCOINS]");
	}
	if(GetPVarInt(playerid, "Cases") == 3)
	{
		if(item_store_kd[playerid] != 0) return 1;

        if(QueryPlayerDonationBalance(playerid) < 150) return GameText(playerid, "~r~Недостаточно Средств", 4000, 3);
					
		if(GetInventorySlots(playerid) == -1) return GameText(playerid, "В вашем инвентаре нет свободного места", 3000, 0);

		ProcessPlayerCredit(playerid, -150);

	    GiveIteam(playerid, 272, 1, 1, 0);

		SCM(playerid, 0xFFFFFFFF, "{"SERVER_COLOR"}Вы успешно приобрели: {FFFFFF}Кейс Велесова ночь {"SERVER_COLOR"}в количестве {FFFFFF}1 шт. {"SERVER_COLOR"}за {FFFFFF}150 [DCOINS]");
	}
	if(GetPVarInt(playerid, "Cases") == 4)
	{
		if(item_store_kd[playerid] != 0) return 1;

        if(QueryPlayerDonationBalance(playerid) < 150) return GameText(playerid, "~r~Недостаточно Средств", 4000, 3);
					
		if(GetInventorySlots(playerid) == -1) return GameText(playerid, "В вашем инвентаре нет свободного места", 3000, 0);

		ProcessPlayerCredit(playerid, -150);

	    GiveIteam(playerid, 278, 1, 1, 0);

		SCM(playerid, 0xFFFFFFFF, "{"SERVER_COLOR"}Вы успешно приобрели: {FFFFFF}Кейс Оперской {"SERVER_COLOR"}в количестве {FFFFFF}1 шт. {"SERVER_COLOR"}за {FFFFFF}150 [DCOINS]");
	}
	if(GetPVarInt(playerid, "Cases") == 5)
	{
		if(item_store_kd[playerid] != 0) return 1;

        if(QueryPlayerDonationBalance(playerid) < 150) return GameText(playerid, "~r~Недостаточно Средств", 4000, 3);
					
		if(GetInventorySlots(playerid) == -1) return GameText(playerid, "В вашем инвентаре нет свободного места", 3000, 0);

		ProcessPlayerCredit(playerid, -150);

	    GiveIteam(playerid, 284, 1, 1, 0);

		SCM(playerid, 0xFFFFFFFF, "{"SERVER_COLOR"}Вы успешно приобрели: {FFFFFF}Кейс Новогодний {"SERVER_COLOR"}в количестве {FFFFFF}1 шт. {"SERVER_COLOR"}за {FFFFFF}150 [DCOINS]");
	}
	if(GetPVarInt(playerid, "Cases") == 6)
	{
		if(item_store_kd[playerid] != 0) return 1;

        if(QueryPlayerDonationBalance(playerid) < 150) return GameText(playerid, "~r~Недостаточно Средств", 4000, 3);
					
		if(GetInventorySlots(playerid) == -1) return GameText(playerid, "В вашем инвентаре нет свободного места", 3000, 0);

		ProcessPlayerCredit(playerid, -150);

	    GiveIteam(playerid, 290, 1, 1, 0);

		SCM(playerid, 0xFFFFFFFF, "{"SERVER_COLOR"}Вы успешно приобрели: {FFFFFF}Кейс Черное золото {"SERVER_COLOR"}в количестве {FFFFFF}1 шт. {"SERVER_COLOR"}за {FFFFFF}150 [DCOINS]");
	}
	if(GetPVarInt(playerid, "Cases") == 7)
	{
		if(item_store_kd[playerid] != 0) return 1;

        if(QueryPlayerDonationBalance(playerid) < 150) return GameText(playerid, "~r~Недостаточно Средств", 4000, 3);
					
		if(GetInventorySlots(playerid) == -1) return GameText(playerid, "В вашем инвентаре нет свободного места", 3000, 0);

		ProcessPlayerCredit(playerid, -150);

	    GiveIteam(playerid, 300, 1, 1, 0);

		SCM(playerid, 0xFFFFFFFF, "{"SERVER_COLOR"}Вы успешно приобрели: {FFFFFF}Кейс Охотничий {"SERVER_COLOR"}в количестве {FFFFFF}1 шт. {"SERVER_COLOR"}за {FFFFFF}150 [DCOINS]");
	}
	if(GetPVarInt(playerid, "Cases") == 8)
	{
		if(item_store_kd[playerid] != 0) return 1;

        if(QueryPlayerDonationBalance(playerid) < 150) return GameText(playerid, "~r~Недостаточно Средств", 4000, 3);
					
		if(GetInventorySlots(playerid) == -1) return GameText(playerid, "В вашем инвентаре нет свободного места", 3000, 0);

		ProcessPlayerCredit(playerid, -150);

	    GiveIteam(playerid, 328, 1, 1, 0);

		SCM(playerid, 0xFFFFFFFF, "{"SERVER_COLOR"}Вы успешно приобрели: {FFFFFF}Кейс Египетская сила {"SERVER_COLOR"}в количестве {FFFFFF}1 шт. {"SERVER_COLOR"}за {FFFFFF}150 [DCOINS]");
	}
	if(GetPVarInt(playerid, "Cases") == 9)
	{
		if(item_store_kd[playerid] != 0) return 1;

        if(QueryPlayerDonationBalance(playerid) < 150) return GameText(playerid, "~r~Недостаточно Средств", 4000, 3);
					
		if(GetInventorySlots(playerid) == -1) return GameText(playerid, "В вашем инвентаре нет свободного места", 3000, 0);

		ProcessPlayerCredit(playerid, -150);

	    GiveIteam(playerid, 344, 1, 1, 0);

		SCM(playerid, 0xFFFFFFFF, "{"SERVER_COLOR"}Вы успешно приобрели: {FFFFFF}Кейс Велесова ночь 2 {"SERVER_COLOR"}в количестве {FFFFFF}1 шт. {"SERVER_COLOR"}за {FFFFFF}150 [DCOINS]");
	}
	if(GetPVarInt(playerid, "Cases") == 10)
	{
		if(item_store_kd[playerid] != 0) return 1;

        if(QueryPlayerDonationBalance(playerid) < 150) return GameText(playerid, "~r~Недостаточно Средств", 4000, 3);
					
		if(GetInventorySlots(playerid) == -1) return GameText(playerid, "В вашем инвентаре нет свободного места", 3000, 0);

		ProcessPlayerCredit(playerid, -150);

	    GiveIteam(playerid, 348, 1, 1, 0);

		SCM(playerid, 0xFFFFFFFF, "{"SERVER_COLOR"}Вы успешно приобрели: {FFFFFF}Кейс Рождественский экспресс {"SERVER_COLOR"}в количестве {FFFFFF}1 шт. {"SERVER_COLOR"}за {FFFFFF}150 [DCOINS]");
	}
	if(GetPVarInt(playerid, "Cases") == 11)
	{
		if(item_store_kd[playerid] != 0) return 1;

        if(QueryPlayerDonationBalance(playerid) < 150) return GameText(playerid, "~r~Недостаточно Средств", 4000, 3);
					
		if(GetInventorySlots(playerid) == -1) return GameText(playerid, "В вашем инвентаре нет свободного места", 3000, 0);

		ProcessPlayerCredit(playerid, -150);

	    GiveIteam(playerid, 350, 1, 1, 0);

		SCM(playerid, 0xFFFFFFFF, "{"SERVER_COLOR"}Вы успешно приобрели: {FFFFFF}Кейс Путь воина {"SERVER_COLOR"}в количестве {FFFFFF}1 шт. {"SERVER_COLOR"}за {FFFFFF}150 [DCOINS]");
	}
	if(GetPVarInt(playerid, "Cases") == 12)
	{
		if(item_store_kd[playerid] != 0) return 1;

        if(QueryPlayerDonationBalance(playerid) < 150) return GameText(playerid, "~r~Недостаточно Средств", 4000, 3);
					
		if(GetInventorySlots(playerid) == -1) return GameText(playerid, "В вашем инвентаре нет свободного места", 3000, 0);

		ProcessPlayerCredit(playerid, -150);

	    GiveIteam(playerid, 355, 1, 1, 0);

		SCM(playerid, 0xFFFFFFFF, "{"SERVER_COLOR"}Вы успешно приобрели: {FFFFFF}Кейс Пиратский {"SERVER_COLOR"}в количестве {FFFFFF}1 шт. {"SERVER_COLOR"}за {FFFFFF}150 [DCOINS]");
	}
	if(GetPVarInt(playerid, "Cases") == 13)
	{
		if(item_store_kd[playerid] != 0) return 1;

        if(QueryPlayerDonationBalance(playerid) < 150) return GameText(playerid, "~r~Недостаточно Средств", 4000, 3);
					
		if(GetInventorySlots(playerid) == -1) return GameText(playerid, "В вашем инвентаре нет свободного места", 3000, 0);

		ProcessPlayerCredit(playerid, -150);

	    GiveIteam(playerid, 356, 1, 1, 0);

		SCM(playerid, 0xFFFFFFFF, "{"SERVER_COLOR"}Вы успешно приобрели: {FFFFFF}Кейс Проклятие {"SERVER_COLOR"}в количестве {FFFFFF}1 шт. {"SERVER_COLOR"}за {FFFFFF}150 [DCOINS]");
	}
	if(GetPVarInt(playerid, "Cases") == 14)
	{
		if(item_store_kd[playerid] != 0) return 1;

        if(QueryPlayerDonationBalance(playerid) < 150) return GameText(playerid, "~r~Недостаточно Средств", 4000, 3);
					
		if(GetInventorySlots(playerid) == -1) return GameText(playerid, "В вашем инвентаре нет свободного места", 3000, 0);

		ProcessPlayerCredit(playerid, -150);

	    GiveIteam(playerid, 360, 1, 1, 0);

		SCM(playerid, 0xFFFFFFFF, "{"SERVER_COLOR"}Вы успешно приобрели: {FFFFFF}Кейс Зимняя сказка {"SERVER_COLOR"}в количестве {FFFFFF}1 шт. {"SERVER_COLOR"}за {FFFFFF}150 [DCOINS]");
	}
	if(GetPVarInt(playerid, "Cases") == 15)
	{
		if(item_store_kd[playerid] != 0) return 1;

        if(QueryPlayerDonationBalance(playerid) < 250) return GameText(playerid, "~r~Недостаточно Средств", 4000, 3);
					
		if(GetInventorySlots(playerid) == -1) return GameText(playerid, "В вашем инвентаре нет свободного места", 3000, 0);

		ProcessPlayerCredit(playerid, -250);

	    GiveIteam(playerid, 259, 1, 1, 0);

		SCM(playerid, 0xFFFFFFFF, "{"SERVER_COLOR"}Вы успешно приобрели: {FFFFFF}Ключ от кейса {"SERVER_COLOR"}в количестве {FFFFFF}1 шт. {"SERVER_COLOR"}за {FFFFFF}150 [DCOINS]");
	}
	if(GetPVarInt(playerid, "BuyHomeAcs") == 1)
	{
		if(item_store_kd[playerid] != 0) return 1;

	    new price = strval(g_decoration_data[event-1][E_PRICE]);

		if(QueryPlayerDonationBalance(playerid) < price) return GameText(playerid, "~r~Недостаточно Средств", 4000, 3);

		GiveAcs(playerid, g_decoration_data[event-1][E_MODEL], 23);

		ProcessPlayerCredit(playerid, -price);

	    GameText(playerid, "~g~Успешно", 4000, 3);
	}
	if(GetPVarInt(playerid, "BuyDonateAcs") == 1)
	{
		if(item_store_kd[playerid] != 0) return 1;

	    new price = strval(g_accessory_data[event-1][E_PRICE]);

		if(QueryPlayerDonationBalance(playerid) < price) return GameText(playerid, "~r~Недостаточно Средств", 4000, 3);

		GiveAcs(playerid, g_accessory_data[event-1][E_MODEL_ID], g_accessory_data[event-1][E_ITEM_ID]);

		ProcessPlayerCredit(playerid, -price);

		SCMF(playerid, 0xFFFFFFFF, "{"SERVER_COLOR"}Вы успешно приобрели аксессуар: {FFFFFF}\"%s\" {"SERVER_COLOR"}в количестве {FFFFFF}1 шт. {"SERVER_COLOR"}за {FFFFFF}%d [DCOINS]", g_accessory_data[event-1][E_NAME], price);

	    GameText(playerid, "~g~Успешно", 4000, 3);
	}
	if(GetPVarInt(playerid, "BuyDonateCarAcs") == 1)
	{
		if(item_store_kd[playerid] != 0) return 1;

	    new price = strval(g_accessory_car_data[event-1][E_PRICE]);

		if(QueryPlayerDonationBalance(playerid) < price) return GameText(playerid, "~r~Недостаточно Средств", 4000, 3);

		GiveAcs(playerid, g_accessory_car_data[event-1][E_MODEL], 14);

		ProcessPlayerCredit(playerid, -price);

		SCMF(playerid, 0xFFFFFFFF, "{"SERVER_COLOR"}Вы успешно приобрели аксессуар: {FFFFFF}\"%s\" {"SERVER_COLOR"}в количестве {FFFFFF}1 шт. {"SERVER_COLOR"}за {FFFFFF}%d [DCOINS]", g_accessory_car_data[event-1][E_NAME], price);

	    GameText(playerid, "~g~Успешно", 4000, 3);
	}
	CEF_HIDE(playerid, "ItemStore");
	item_store_kd[playerid] = 5;
	ItemStoreMenu_OnClose(playerid);
	return 1;
}

public: ItemStoreMenu_OnClose(playerid)
{
	DeletePVar(playerid, "Cases");
	DeletePVar(playerid, "Items");
	DeletePVar(playerid, "BuyCase");
	DeletePVar(playerid, "BuyItems");
	DeletePVar(playerid, "BuyHomeAcs");
	DeletePVar(playerid, "BuyDonateAcs");
	DeletePVar(playerid, "BuyDonateCarAcs");
	return 1;
}

public:ItemStoreMenu_OnClick(playerid, event)
{
	DeletePVar(playerid, "Cases");
	DeletePVar(playerid, "items");

	if(GetPVarInt(playerid, "BuyItems") == 1)
	{
	    switch(event)
	    {
		    case 0: SetPVarInt(playerid, "Items", 1);
		    case 1: SetPVarInt(playerid, "Items", 2);
		    case 2: SetPVarInt(playerid, "Items", 3);
		    case 3: SetPVarInt(playerid, "Items", 4);
	    }
	}
	if(GetPVarInt(playerid, "BuyCase") == 1)
	{
	    switch(event)
	    {
		    case 0: SetPVarInt(playerid, "Cases", 1);
		    case 1: SetPVarInt(playerid, "Cases", 2);
		    case 2: SetPVarInt(playerid, "Cases", 3);
		    case 3: SetPVarInt(playerid, "Cases", 4);
		    case 4: SetPVarInt(playerid, "Cases", 5);
		    case 5: SetPVarInt(playerid, "Cases", 6);
		    case 6: SetPVarInt(playerid, "Cases", 7);
		    case 7: SetPVarInt(playerid, "Cases", 8);
		    case 8: SetPVarInt(playerid, "Cases", 9);
		    case 9: SetPVarInt(playerid, "Cases", 10);
		    case 10: SetPVarInt(playerid, "Cases", 11);
		    case 11: SetPVarInt(playerid, "Cases", 12);
		    case 12: SetPVarInt(playerid, "Cases", 13);
		    case 13: SetPVarInt(playerid, "Cases", 14);
		    case 14: SetPVarInt(playerid, "Cases", 15);
	    }
	}
}