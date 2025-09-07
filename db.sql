-- phpMyAdmin SQL Dump
-- version 4.9.7
-- https://www.phpmyadmin.net/
--
-- Хост: 127.0.0.1:3306
-- Время создания: Сен 07 2025 г., 02:57
-- Версия сервера: 11.7.2-MariaDB
-- Версия PHP: 7.4.33

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- База данных: `gs95592`
--

-- --------------------------------------------------------

--
-- Структура таблицы `accounts_canvasdev`
--

CREATE TABLE `accounts_canvasdev` (
  `id` int(11) NOT NULL,
  `name` varchar(21) NOT NULL,
  `players_password` varchar(85) NOT NULL,
  `email` varchar(61) NOT NULL DEFAULT 'None',
  `confirm_email` int(11) NOT NULL,
  `skin` int(11) NOT NULL DEFAULT 223,
  `exp` int(11) NOT NULL,
  `level` int(11) NOT NULL DEFAULT 1,
  `refer` int(11) NOT NULL,
  `sex` int(11) NOT NULL,
  `money` varchar(21) NOT NULL DEFAULT '0',
  `voennik` int(11) NOT NULL,
  `bank` varchar(21) NOT NULL DEFAULT '0',
  `admin` int(11) NOT NULL,
  `buyadmin` int(11) NOT NULL,
  `yadmin` int(11) NOT NULL,
  `full` int(11) NOT NULL,
  `mind` int(11) NOT NULL,
  `givefull` int(11) NOT NULL,
  `driving_lic` int(11) NOT NULL,
  `weapon_lic` int(11) NOT NULL,
  `suspect` int(11) NOT NULL,
  `phone` int(11) NOT NULL,
  `phone_balance` int(11) NOT NULL,
  `phone_color` int(11) NOT NULL DEFAULT 9,
  `watch` int(11) NOT NULL,
  `law_abiding` int(11) NOT NULL,
  `improvements` int(11) NOT NULL,
  `power` int(11) NOT NULL,
  `brak` int(11) NOT NULL,
  `team` int(11) NOT NULL,
  `subdivison` int(11) NOT NULL,
  `wage` int(11) NOT NULL,
  `job` int(11) NOT NULL,
  `house_type` int(11) NOT NULL DEFAULT -1,
  `house_room` int(11) NOT NULL DEFAULT -1,
  `house_slots` int(11) NOT NULL DEFAULT 1,
  `id_spawn` int(11) NOT NULL DEFAULT -1,
  `garage_slots` int(11) NOT NULL DEFAULT -1,
  `biz_slots` int(11) NOT NULL DEFAULT 1,
  `reg_time` int(11) NOT NULL,
  `reg_ip` varchar(16) NOT NULL,
  `last_ip` varchar(16) NOT NULL,
  `last_login` int(11) NOT NULL,
  `last_exit` int(11) NOT NULL,
  `game_for_hour` int(11) NOT NULL,
  `game_for_day` int(11) NOT NULL,
  `game_for_day_prev` int(11) NOT NULL,
  `setting_phone` varchar(13) NOT NULL DEFAULT 'None',
  `setting_pin_code` varchar(5) NOT NULL DEFAULT 'None',
  `request_phone` int(11) NOT NULL,
  `request_pin` int(11) NOT NULL,
  `setting1` int(11) NOT NULL DEFAULT 2,
  `setting2` int(11) NOT NULL DEFAULT 1,
  `setting4` int(11) NOT NULL DEFAULT 1,
  `setting5` int(11) NOT NULL DEFAULT 0,
  `setting6` int(11) NOT NULL DEFAULT 1,
  `warn` int(11) NOT NULL,
  `warn_time` int(11) NOT NULL,
  `mute` int(11) NOT NULL,
  `rmute` int(11) NOT NULL,
  `vmute` int(11) NOT NULL,
  `skill_colt` int(11) NOT NULL,
  `skill_sdpistol` int(11) NOT NULL,
  `skill_deagle` int(11) NOT NULL,
  `skill_shotgun` int(11) NOT NULL,
  `skill_mp5` int(11) NOT NULL,
  `skill_ak47` int(11) NOT NULL,
  `skill_m4` int(11) NOT NULL,
  `skill_sniper_rifle` int(11) NOT NULL,
  `skill_sawnoff` int(11) NOT NULL,
  `skill_combat_sg` int(11) NOT NULL,
  `skill_micro_uzi` int(11) NOT NULL,
  `donate_current` int(11) NOT NULL,
  `donate_total` int(11) NOT NULL,
  `org_skin` int(11) NOT NULL,
  `setting_spawn` int(11) NOT NULL,
  `hospital` int(11) NOT NULL,
  `health` float NOT NULL DEFAULT 100,
  `car_slots` int(11) NOT NULL DEFAULT 3,
  `jail` int(11) NOT NULL,
  `premium` int(11) NOT NULL DEFAULT 1,
  `premium_time` int(11) NOT NULL,
  `ruletka` int(11) NOT NULL,
  `e_player` varchar(350) NOT NULL,
  `rppoint` int(11) NOT NULL,
  `disease_0` int(11) NOT NULL,
  `disease_1` int(11) NOT NULL,
  `a_rmute` int(11) NOT NULL,
  `a_unrmute` int(11) NOT NULL,
  `style1` int(11) NOT NULL,
  `style2` int(11) NOT NULL,
  `style3` int(11) NOT NULL,
  `style4` int(11) NOT NULL,
  `style5` int(11) NOT NULL,
  `weapons` int(11) NOT NULL,
  `patrons` int(11) NOT NULL,
  `donate` int(11) NOT NULL,
  `score` int(11) DEFAULT NULL,
  `myprefix` varchar(64) NOT NULL,
  `myprefixcolor` varchar(64) NOT NULL,
  `hunger` int(11) NOT NULL,
  `after_x` float NOT NULL,
  `after_y` float NOT NULL,
  `after_z` float NOT NULL,
  `afterpos` int(11) NOT NULL,
  `family` int(11) NOT NULL,
  `family_rank` int(11) NOT NULL,
  `fmute` int(11) NOT NULL,
  `fwarn` int(11) NOT NULL,
  `kiosk_slots` int(11) NOT NULL DEFAULT 1,
  `garden_slots` int(11) NOT NULL DEFAULT 1,
  `dance_0` int(11) NOT NULL,
  `dance_1` int(11) NOT NULL,
  `dance_2` int(11) NOT NULL,
  `dance_3` int(11) NOT NULL,
  `dance_4` int(11) NOT NULL,
  `dance_5` int(11) NOT NULL,
  `dance_6` int(11) NOT NULL,
  `dance_7` int(11) NOT NULL,
  `dance_8` int(11) NOT NULL,
  `dance_9` int(11) NOT NULL,
  `dance_10` int(11) NOT NULL,
  `dance_11` int(11) NOT NULL,
  `dance_12` int(11) NOT NULL,
  `dance_13` int(11) NOT NULL,
  `dance_14` int(11) NOT NULL,
  `dance_15` int(11) NOT NULL,
  `dance_16` int(11) NOT NULL,
  `dance_17` int(11) NOT NULL,
  `dance_18` int(11) NOT NULL,
  `dance_19` int(11) NOT NULL,
  `dance_20` int(11) NOT NULL,
  `dance_21` int(11) NOT NULL,
  `dance_22` int(11) NOT NULL,
  `dance_23` int(11) NOT NULL,
  `dance_24` int(11) NOT NULL,
  `dance_25` int(11) NOT NULL,
  `dance_26` int(11) NOT NULL,
  `dance_27` int(11) NOT NULL,
  `dance_28` int(11) NOT NULL,
  `dance_29` int(11) NOT NULL,
  `dance_30` int(11) NOT NULL,
  `dance_31` int(11) NOT NULL,
  `dance_32` int(11) NOT NULL,
  `dance_33` int(11) NOT NULL,
  `quest_1_stats` int(11) NOT NULL,
  `quest_2_value` int(11) NOT NULL,
  `quest_2_stats` int(11) NOT NULL,
  `quest_3_stats` int(11) NOT NULL,
  `quest_4_value` int(11) NOT NULL,
  `quest_4_stats` int(11) NOT NULL,
  `quest_5_stats` int(11) NOT NULL,
  `quest_6_stats` int(11) NOT NULL,
  `quest_7_stats` int(11) NOT NULL,
  `quest_8_stats` int(11) NOT NULL,
  `quest_9_stats` int(11) NOT NULL,
  `quest_10_stats` int(11) NOT NULL,
  `quest_11_stats` int(11) NOT NULL,
  `quest_12_stats` int(11) NOT NULL,
  `quest_13_stats` int(11) NOT NULL,
  `quest_14_stats` int(11) NOT NULL,
  `quest_15_stats` int(11) NOT NULL,
  `quest_16_stats` int(11) NOT NULL,
  `quest_17_stats` int(11) NOT NULL,
  `quest_18_stats` int(11) NOT NULL,
  `quest_19_stats` int(11) NOT NULL,
  `quest_20_stats` int(11) NOT NULL,
  `quest_21_stats` int(11) NOT NULL,
  `quest_11_value` int(11) NOT NULL,
  `auction_id` int(11) NOT NULL DEFAULT -1,
  `auction_price` int(11) NOT NULL,
  `auction_status` int(11) NOT NULL,
  `adminspasslogin` varchar(22) NOT NULL DEFAULT '999999',
  `nakolka` int(11) NOT NULL,
  `dostij1` int(11) NOT NULL,
  `dostij2` int(11) NOT NULL,
  `dostij3` int(11) NOT NULL,
  `dostij4` int(11) NOT NULL,
  `dostij5` int(11) NOT NULL,
  `dostij6` int(11) NOT NULL,
  `dostij7` int(11) NOT NULL,
  `dostij8` int(11) NOT NULL,
  `dostij9` int(11) NOT NULL,
  `dostij10` int(11) NOT NULL,
  `dostij11` int(11) NOT NULL,
  `dostij12` int(11) NOT NULL,
  `dostij13` int(11) NOT NULL,
  `dostij14` int(11) NOT NULL,
  `dostij15` int(11) NOT NULL,
  `dostij16` int(11) NOT NULL,
  `dostij17` int(11) NOT NULL,
  `dostij18` int(11) NOT NULL,
  `dostij19` int(11) NOT NULL,
  `dostij20` int(11) NOT NULL,
  `dostij21` int(11) NOT NULL,
  `dostij22` int(11) NOT NULL,
  `dostij23` int(11) NOT NULL,
  `dostij24` int(11) NOT NULL,
  `dostij25` int(11) NOT NULL,
  `admdemorgan` int(11) NOT NULL,
  `admreport` int(11) NOT NULL,
  `admkick` int(11) NOT NULL,
  `wards_prize` int(11) NOT NULL DEFAULT -1,
  `wards_type_prizes` int(11) NOT NULL,
  `serialid` varchar(250) NOT NULL,
  `serialid_temp` varchar(250) NOT NULL,
  `drag_score` int(11) NOT NULL,
  `coins` int(11) NOT NULL,
  `tk_job` int(11) NOT NULL,
  `tk_job_type` int(11) NOT NULL,
  `bp_premium` int(11) NOT NULL,
  `bp_level` int(11) NOT NULL,
  `bp_time_tasks` int(11) NOT NULL,
  `bp_task_1` int(11) NOT NULL,
  `bp_task_2` int(11) NOT NULL,
  `bp_task_3` int(11) NOT NULL,
  `bp_task_4` int(11) NOT NULL,
  `bp_task_5` int(11) NOT NULL,
  `bp_task_6` int(11) NOT NULL,
  `bp_point_1` int(11) NOT NULL,
  `bp_point_2` int(11) NOT NULL,
  `bp_point_3` int(11) NOT NULL,
  `bp_point_4` int(11) NOT NULL,
  `bp_point_5` int(11) NOT NULL,
  `bp_point_6` int(11) NOT NULL,
  `bp_prize_1` int(11) NOT NULL,
  `bp_prize_2` int(11) NOT NULL,
  `bp_exp` int(11) NOT NULL,
  `auction_slots` int(11) NOT NULL,
  `easter` int(11) NOT NULL,
  `vipprefix` varchar(64) NOT NULL DEFAULT '{ffa500}[Игрок]',
  `giveskin` int(11) NOT NULL,
  `contspawn` int(11) NOT NULL,
  `dumpspawn` int(11) NOT NULL,
  `givecar` int(11) NOT NULL,
  `givemoney` int(11) NOT NULL,
  `givedonate` int(11) NOT NULL,
  `afly` int(11) NOT NULL,
  `getv` int(11) NOT NULL,
  `fixcar` int(11) NOT NULL,
  `exit_x` float NOT NULL,
  `exit_y` float NOT NULL,
  `exit_z` float NOT NULL,
  `vipoff` int(11) NOT NULL,
  `mobile` int(11) NOT NULL,
  `snow` int(11) NOT NULL DEFAULT 1,
  `snow_insible` int(11) NOT NULL,
  `podarok` int(11) NOT NULL,
  `achiv_1` int(11) NOT NULL,
  `achiv_1_completed` int(11) NOT NULL,
  `achiv_2` int(11) NOT NULL,
  `achiv_3` int(11) NOT NULL,
  `achiv_4` int(11) NOT NULL,
  `achiv_5` int(11) NOT NULL,
  `achiv_6` int(11) NOT NULL,
  `achiv_7` int(11) NOT NULL,
  `achiv_8` int(11) NOT NULL,
  `achiv_9` int(11) NOT NULL,
  `achiv_10` int(11) NOT NULL,
  `achiv_11` int(11) NOT NULL,
  `achiv_12` int(11) NOT NULL,
  `achiv_13` int(11) NOT NULL,
  `achiv_14` int(11) NOT NULL,
  `achiv_15` int(11) NOT NULL,
  `achiv_16` int(11) NOT NULL,
  `achiv_17` int(11) NOT NULL,
  `achiv_18` int(11) NOT NULL,
  `achiv_19` int(11) NOT NULL,
  `achiv_20` int(11) NOT NULL,
  `achiv_21` int(11) NOT NULL,
  `achiv_22` int(11) NOT NULL,
  `achiv_23` int(11) NOT NULL,
  `achiv_24` int(11) NOT NULL,
  `achiv_25` int(11) NOT NULL,
  `achiv_26` int(11) NOT NULL,
  `achiv_27` int(11) NOT NULL,
  `achiv_28` int(11) NOT NULL,
  `achiv_29` int(11) NOT NULL,
  `achiv_30` int(11) NOT NULL,
  `achiv_31` int(11) NOT NULL,
  `achiv_32` int(11) NOT NULL,
  `achiv_33` int(11) NOT NULL,
  `achiv_34` int(11) NOT NULL,
  `achiv_35` int(11) NOT NULL,
  `achiv_36` int(11) NOT NULL,
  `achiv_37` int(11) NOT NULL,
  `achiv_38` int(11) NOT NULL,
  `achiv_39` int(11) NOT NULL,
  `achiv_40` int(11) NOT NULL,
  `achiv_41` int(11) NOT NULL,
  `achiv_42` int(11) NOT NULL,
  `achiv_43` int(11) NOT NULL,
  `achiv_44` int(11) NOT NULL,
  `achiv_2_completed` int(11) NOT NULL,
  `achiv_3_completed` int(11) NOT NULL,
  `achiv_4_completed` int(11) NOT NULL,
  `achiv_5_completed` int(11) NOT NULL,
  `achiv_6_completed` int(11) NOT NULL,
  `achiv_7_completed` int(11) NOT NULL,
  `achiv_8_completed` int(11) NOT NULL,
  `achiv_9_completed` int(11) NOT NULL,
  `achiv_10_completed` int(11) NOT NULL,
  `achiv_11_completed` int(11) NOT NULL,
  `achiv_12_completed` int(11) NOT NULL,
  `achiv_13_completed` int(11) NOT NULL,
  `achiv_14_completed` int(11) NOT NULL,
  `achiv_15_completed` int(11) NOT NULL,
  `achiv_16_completed` int(11) NOT NULL,
  `achiv_17_completed` int(11) NOT NULL,
  `achiv_18_completed` int(11) NOT NULL,
  `achiv_19_completed` int(11) NOT NULL,
  `achiv_20_completed` int(11) NOT NULL,
  `achiv_21_completed` int(11) NOT NULL,
  `achiv_22_completed` int(11) NOT NULL,
  `achiv_23_completed` int(11) NOT NULL,
  `achiv_24_completed` int(11) NOT NULL,
  `achiv_25_completed` int(11) NOT NULL,
  `achiv_26_completed` int(11) NOT NULL,
  `achiv_27_completed` int(11) NOT NULL,
  `achiv_28_completed` int(11) NOT NULL,
  `achiv_29_completed` int(11) NOT NULL,
  `achiv_30_completed` int(11) NOT NULL,
  `achiv_31_completed` int(11) NOT NULL,
  `achiv_32_completed` int(11) NOT NULL,
  `achiv_33_completed` int(11) NOT NULL,
  `achiv_34_completed` int(11) NOT NULL,
  `achiv_35_completed` int(11) NOT NULL,
  `achiv_36_completed` int(11) NOT NULL,
  `achiv_37_completed` int(11) NOT NULL,
  `achiv_38_completed` int(11) NOT NULL,
  `achiv_39_completed` int(11) NOT NULL,
  `achiv_40_completed` int(11) NOT NULL,
  `achiv_41_completed` int(11) NOT NULL,
  `achiv_42_completed` int(11) NOT NULL,
  `achiv_43_completed` int(11) NOT NULL,
  `achiv_44_completed` int(11) NOT NULL,
  `yt_promo` int(11) NOT NULL,
  `daily_claim` int(11) NOT NULL,
  `daily_claim_7` int(11) NOT NULL,
  `daily_claim_14` int(11) NOT NULL,
  `daily_claim_21` int(11) NOT NULL,
  `daily_claim_28` int(11) NOT NULL,
  `daily_case_7_id` int(11) NOT NULL,
  `daily_case_14_id` int(11) NOT NULL,
  `daily_case_21_id` int(11) NOT NULL,
  `daily_case_28_id` int(11) NOT NULL,
  `daily_complete` int(11) NOT NULL,
  `auth_token` char(16) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL,
  `2fa_enabled` int(11) NOT NULL,
  `bp_golds` int(11) NOT NULL,
  `bp_task_7` int(11) NOT NULL,
  `bp_task_8` int(11) NOT NULL,
  `bp_task_9` int(11) NOT NULL,
  `bp_task_10` int(11) NOT NULL,
  `bp_task_11` int(11) NOT NULL,
  `bp_task_12` int(11) NOT NULL,
  `bp_point_7` int(11) NOT NULL,
  `bp_point_8` int(11) NOT NULL,
  `bp_point_9` int(11) NOT NULL,
  `bp_point_10` int(11) NOT NULL,
  `bp_point_11` int(11) NOT NULL,
  `bp_point_12` int(11) NOT NULL,
  `dance_slide` int(11) NOT NULL,
  `dance_crip_uok` int(11) NOT NULL,
  `dance_flow` int(11) NOT NULL,
  `dance_astronaut` int(11) NOT NULL,
  `dance_three_pointed` int(11) NOT NULL,
  `uid_fsb` int(11) NOT NULL,
  `reg_data_fsb` int(11) NOT NULL,
  `expire_data_fsb` int(11) NOT NULL,
  `driving_lic_prof` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `action_log`
--

CREATE TABLE `action_log` (
  `id` int(11) NOT NULL,
  `acc_id` int(11) NOT NULL,
  `uip` varchar(16) NOT NULL DEFAULT '255.255.255.255',
  `type` int(11) NOT NULL,
  `description` varchar(128) NOT NULL,
  `time` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `alogs`
--

CREATE TABLE `alogs` (
  `acc_id` int(11) NOT NULL,
  `type` varchar(61) NOT NULL,
  `name_adm` varchar(32) NOT NULL,
  `time` int(11) NOT NULL,
  `reason` varchar(61) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `anticheat_settings`
--

CREATE TABLE `anticheat_settings` (
  `ac_code` int(2) NOT NULL,
  `ac_code_trigger_type` int(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

--
-- Дамп данных таблицы `anticheat_settings`
--

INSERT INTO `anticheat_settings` (`ac_code`, `ac_code_trigger_type`) VALUES
(0, 1),
(1, 1),
(2, 1),
(3, 1),
(4, 1),
(5, 1),
(6, 1),
(7, 1),
(8, 1),
(9, 1),
(10, 1),
(11, 1),
(12, 1),
(13, 1),
(14, 1),
(15, 1),
(16, 1),
(17, 1),
(18, 1),
(19, 1),
(20, 1),
(21, 1),
(22, 1),
(23, 1),
(24, 1),
(25, 1),
(26, 1),
(27, 1),
(28, 1),
(29, 1),
(30, 1),
(31, 1),
(32, 1),
(33, 1),
(34, 1),
(35, 1),
(36, 1),
(37, 1),
(38, 1),
(39, 1),
(40, 1),
(41, 1),
(42, 1),
(43, 1),
(44, 1),
(45, 1),
(46, 1),
(47, 1),
(48, 1),
(49, 1),
(50, 1),
(51, 1),
(52, 1);

-- --------------------------------------------------------

--
-- Структура таблицы `arenda_cars`
--

CREATE TABLE `arenda_cars` (
  `id` int(11) NOT NULL,
  `owner_id` int(11) NOT NULL,
  `model_id` int(11) NOT NULL,
  `color_1` int(11) NOT NULL,
  `color_2` int(11) NOT NULL,
  `pos_x` float NOT NULL,
  `pos_y` float NOT NULL,
  `pos_z` float NOT NULL,
  `angle` float NOT NULL,
  `create_time` int(11) NOT NULL,
  `iznos` float NOT NULL,
  `maslo` float NOT NULL,
  `world` int(11) NOT NULL,
  `price` int(11) NOT NULL DEFAULT 11111,
  `mesto` int(11) NOT NULL,
  `koleso_1` float NOT NULL,
  `koleso_2` float NOT NULL,
  `koleso_3` float NOT NULL,
  `koleso_4` float NOT NULL,
  `milleage` float NOT NULL,
  `vehicleid` int(11) NOT NULL DEFAULT -1
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `auction`
--

CREATE TABLE `auction` (
  `id` int(11) NOT NULL,
  `owner_id` int(11) NOT NULL,
  `owner_name` varchar(21) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL DEFAULT 'ГОСУДАРСТВО',
  `id_im` int(11) NOT NULL,
  `player_id` int(11) NOT NULL DEFAULT -1,
  `type` int(11) NOT NULL,
  `stavka` int(11) NOT NULL,
  `phone` int(11) NOT NULL,
  `number` varchar(10) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `region` varchar(10) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `type_number` int(11) NOT NULL,
  `car_id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Дамп данных таблицы `auction`
--

INSERT INTO `auction` (`id`, `owner_id`, `owner_name`, `id_im`, `player_id`, `type`, `stavka`, `phone`, `number`, `region`, `type_number`, `car_id`) VALUES
(1992, 0, 'ГОСУДАРСТВО', 0, -1, 7, 300000, 0, '', '', 0, 0),
(1993, 0, 'ГОСУДАРСТВО', 1, -1, 7, 300000, 0, '', '', 0, 0),
(1994, 0, 'ГОСУДАРСТВО', 2, -1, 7, 300000, 0, '', '', 0, 0),
(1995, 0, 'ГОСУДАРСТВО', 3, -1, 7, 300000, 0, '', '', 0, 0),
(1996, 0, 'ГОСУДАРСТВО', 4, -1, 7, 300000, 0, '', '', 0, 0),
(1997, 0, 'ГОСУДАРСТВО', 5, -1, 7, 300000, 0, '', '', 0, 0),
(1998, 0, 'ГОСУДАРСТВО', 6, -1, 7, 300000, 0, '', '', 0, 0);

-- --------------------------------------------------------

--
-- Структура таблицы `auction_bet`
--

CREATE TABLE `auction_bet` (
  `id` int(11) NOT NULL,
  `owner_id` int(11) NOT NULL,
  `auction_id` int(11) NOT NULL,
  `bet` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `banip_list`
--

CREATE TABLE `banip_list` (
  `id` int(11) NOT NULL,
  `time` datetime NOT NULL,
  `ip` varchar(16) NOT NULL,
  `description` varchar(32) NOT NULL,
  `admin` varchar(24) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `bank_accounts`
--

CREATE TABLE `bank_accounts` (
  `id` int(11) NOT NULL,
  `uid` int(11) NOT NULL,
  `name` varchar(21) NOT NULL DEFAULT 'None',
  `balance` varchar(21) NOT NULL DEFAULT '0',
  `pin` varchar(9) NOT NULL DEFAULT '0000',
  `reg_time` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `bank_accounts_log`
--

CREATE TABLE `bank_accounts_log` (
  `id` int(11) NOT NULL,
  `acc_id` int(11) NOT NULL,
  `uip` varchar(16) NOT NULL DEFAULT '255.255.255.255',
  `time` int(11) NOT NULL,
  `description` varchar(64) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `ban_list`
--

CREATE TABLE `ban_list` (
  `id` int(11) NOT NULL,
  `user_id` int(11) NOT NULL,
  `time` int(11) NOT NULL,
  `ban_time` int(11) NOT NULL,
  `ip` varchar(16) NOT NULL,
  `description` varchar(32) NOT NULL,
  `admin` varchar(24) NOT NULL,
  `data` varchar(15) NOT NULL DEFAULT '0.0.0000',
  `name` varchar(24) NOT NULL DEFAULT 'None'
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `billboard`
--

CREATE TABLE `billboard` (
  `id` int(11) NOT NULL,
  `id_text` int(11) NOT NULL,
  `type` int(11) NOT NULL,
  `color` int(5) NOT NULL,
  `pos_x` float NOT NULL,
  `pos_y` float NOT NULL,
  `pos_z` float NOT NULL,
  `rot_x` float NOT NULL,
  `rot_y` float NOT NULL,
  `rot_z` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

--
-- Дамп данных таблицы `billboard`
--

INSERT INTO `billboard` (`id`, `id_text`, `type`, `color`, `pos_x`, `pos_y`, `pos_z`, `rot_x`, `rot_y`, `rot_z`) VALUES
(1, 1, 4, 1, 363.194, 1671.06, 15.6095, 0, 0, 138.7),
(2, 2, 5, 1, 429.828, 1980.42, 10.7181, 0, 0, 74.2),
(4, 4, 1, 3, 707.56, 631.524, 15.98, 0, 0, -163.7),
(5, 0, 0, 0, 1564.55, -661.495, 28.8764, 0, 0, 113.9),
(6, 0, 0, 0, 185.068, 794.877, 16.131, 0, 0, 66.6);

-- --------------------------------------------------------

--
-- Структура таблицы `bugreport`
--

CREATE TABLE `bugreport` (
  `id` int(11) NOT NULL,
  `owner_id` int(11) NOT NULL,
  `owner_name` varchar(24) NOT NULL,
  `bug_text` varchar(144) NOT NULL,
  `status` int(11) NOT NULL,
  `time` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `business`
--

CREATE TABLE `business` (
  `id` int(11) NOT NULL,
  `owner_id` int(11) NOT NULL,
  `name` varchar(30) NOT NULL,
  `city` int(11) NOT NULL DEFAULT -1,
  `zone` int(11) NOT NULL DEFAULT -1,
  `improvements` int(11) NOT NULL,
  `products` int(11) NOT NULL,
  `prod_price` int(11) NOT NULL,
  `balance` varchar(21) NOT NULL DEFAULT '0',
  `rent_time` int(11) NOT NULL,
  `price` int(11) NOT NULL,
  `rent_price` int(11) NOT NULL,
  `type` int(11) NOT NULL,
  `interior` int(11) NOT NULL,
  `enter_price` int(11) NOT NULL,
  `enter_music` int(11) NOT NULL,
  `lock` int(11) NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `exit_x` float NOT NULL,
  `exit_y` float NOT NULL,
  `exit_z` float NOT NULL,
  `exit_angle` float NOT NULL,
  `gang` int(11) NOT NULL,
  `eviction` int(11) NOT NULL,
  `electricity` int(11) NOT NULL,
  `countlight` int(11) NOT NULL,
  `iznos` int(11) NOT NULL,
  `timerepairone` int(11) NOT NULL,
  `timerepairtwo` int(11) NOT NULL,
  `timerepairlast` int(11) NOT NULL,
  `typewetriki` int(11) NOT NULL,
  `work` int(11) NOT NULL,
  `work_2` int(11) NOT NULL,
  `vetr_work` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

--
-- Дамп данных таблицы `business`
--

INSERT INTO `business` (`id`, `owner_id`, `name`, `city`, `zone`, `improvements`, `products`, `prod_price`, `balance`, `rent_time`, `price`, `rent_price`, `type`, `interior`, `enter_price`, `enter_music`, `lock`, `x`, `y`, `z`, `exit_x`, `exit_y`, `exit_z`, `exit_angle`, `gang`, `eviction`, `electricity`, `countlight`, `iznos`, `timerepairone`, `timerepairtwo`, `timerepairlast`, `typewetriki`, `work`, `work_2`, `vetr_work`) VALUES
(0, 0, 'Автосалон Мото-Вело', 14, 0, 0, 0, 0, '0', 1735344000, 7500000, 25000, 41, 0, 0, 0, 0, -2243.66, 263.234, 24.5337, -2243.48, 264.718, 24.5337, 354.129, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(1, 0, 'Автосалон Элитный', 5, 0, 0, 0, 0, '0', 1752537600, 15000000, 25000, 7, 6, 0, 0, 0, 1861.59, 2824.02, 12, 1868.9, 2822.18, 12.14, 270.238, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(2, 0, 'Автосалон Низкий', 15, 0, 0, 0, 0, '0', 1738800000, 7500000, 25000, 38, 0, 0, 1, 0, 2597.37, -625.377, 12.0825, 2597.08, -628.173, 12.0825, 180.01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(3, 0, 'Автосалон Средний', 15, 0, 0, 0, 0, '0', 1750032000, 10000000, 25000, 42, 33, 0, 0, 0, 392.461, 798.555, 12.2102, 391.884, 796.014, 12.2102, 161.081, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(4, 0, 'Авиасалон', 7, 0, 0, 0, 0, '0', 1734912000, 9500000, 25000, 39, 0, 0, 0, 0, -42.3874, 925.924, 12.3321, -44.1625, 922.477, 12, 157.585, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(5, 0, 'Автосалон Водный', 1, 0, 0, 0, 0, '0', 1734998400, 7750000, 25000, 40, 0, 0, 0, 0, 2642.47, -3434.21, 3.2069, 2641.96, -3432.24, 3.20687, 9.58858, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(6, 0, 'Авторынок Низкий', 15, 0, 0, 0, 0, '0', 1740441600, 5500000, 25000, 35, 19, 0, 0, 0, 2207.99, 2333.18, 13.5938, 2204.43, 2333.01, 13.5938, 87.7344, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(7, 0, 'Авторынок Средний', 15, 0, 0, 0, 0, '0', 1736553600, 9500000, 25000, 35, 20, 0, 0, 0, 2702.24, -2442.5, 21.8921, 2702.08, -2445.44, 21.8921, 178.625, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(8, 0, 'Авторынок Высокий', 5, 0, 0, 0, 0, '0', 1745539200, 11500000, 25000, 35, 21, 0, 0, 0, -1896.08, 1911.66, 176.156, -1899.5, 1911.63, 175.923, 88.7895, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(9, 0, 'СТО 1', 15, 0, 0, 0, 0, '0', 1750032000, 16500000, 25000, 17, 16, 0, 0, 0, -313.182, 299.628, 13.1182, -313.106, 302.364, 13.1182, 351.117, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(10, 0, 'СТО 2', 15, 0, 0, 0, 0, '0', 1750032000, 16500000, 25000, 17, 16, 0, 0, 0, -2519.01, 1086.61, 8.71723, -2517.11, 1090.91, 8.72223, 338.983, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(11, 0, 'СТО 3', 15, 0, 0, 0, 0, '0', 1752537600, 16500000, 25000, 17, 16, 0, 0, 0, 2130.45, -1845.37, 18.8213, 2130.45, -1845.37, 18.8213, 271.995, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(12, 0, 'Детейлинг Центр', 15, 0, 0, 0, 0, '0', 1743292800, 10000000, 25000, 28, 17, 0, 0, 0, 2215.2, -2577.69, 21.9638, 2215.17, -2572.25, 21.9615, 359.926, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(13, 0, 'Детейлинг Центр', 15, 0, 0, 0, 0, '0', 1752537600, 10000000, 25000, 28, 17, 0, 5, 0, -2509.75, 1147.82, 8.76625, -2514.47, 1149.7, 8.76625, 67.9703, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(14, 0, 'Детейлинг Центр', 10, 0, 0, 0, 0, '0', 1750291200, 10000000, 25000, 28, 17, 0, 0, 0, 1810.62, 2342.52, 15.365, 1811.42, 2353.93, 15.3967, 303.599, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(15, 0, 'Парикмахерская', 7, 0, 0, 0, 0, '0', 1722038400, 8000000, 25000, 25, 24, 0, 0, 0, -2521.38, 2937.35, 38.1184, -2521.67, 2935.24, 37.634, 181.445, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(16, 0, 'Магазин Одежды', 14, 0, 0, 0, 0, '0', 1722297600, 9500000, 25000, 5, 4, 0, 0, 0, -2171.88, 148.298, 25.7427, -2169.74, 149.251, 25.571, 288.92, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(17, 0, 'Продуктовый Магазин', 7, 0, 0, 0, 0, '0', 1721260800, 3500000, 25000, 1, 0, 0, 2, 0, -2168.27, 139.056, 26.3514, -2183.42, 179.343, 24.5476, 295.523, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(18, 0, 'Казино Южное', 15, 0, 0, 0, 0, '0', 1750032000, 25000000, 25000, 8, 7, 0, 2, 0, 1920.38, -1933.57, 31.7932, 1918.69, -1936.48, 31.7932, 151.318, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(19, 0, 'Казино Бендер', 15, 0, 0, 0, 0, '0', 1752537600, 15000000, 25000, 8, 7, 0, 0, 0, -2195.77, -301.156, 23.5148, -2201.69, -300.198, 23.5178, 78.624, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(20, 0, 'Супермаркет', 1, 0, 0, 0, 0, '0', 1721433600, 3500000, 25000, 1, 0, 0, 0, 0, 253.784, 1055.03, 12.2556, 257.047, 1054.84, 12.1697, 263.594, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(21, 0, 'Минимаркет', 15, 0, 0, 0, 0, '0', 1722297600, 3500000, 25000, 1, 0, 0, 1, 0, 265.483, 2735.31, 11, 261.035, 2735.29, 11, 91.8073, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(22, 0, 'Супермаркет', 15, 0, 0, 0, 0, '0', 1735171200, 3500000, 25000, 1, 0, 0, 0, 0, 718.722, 2571.24, 12.1875, 719.645, 2569.12, 12.1875, 205.595, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(23, 0, 'Закусочная', 8, 0, 0, 0, 0, '0', 1737417600, 5500000, 25000, 31, 29, 0, 2, 0, 307.678, 1666.33, 12, 307.947, 1668.46, 12.034, 307.696, 0, 0, 0, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(24, 0, 'Супермаркет', 7, 0, 0, 0, 0, '0', 1738800000, 3500000, 25000, 1, 0, 0, 0, 0, -335.39, 986.532, 12.1494, -335.816, 984.081, 12.1494, 178.238, 0, 0, 1, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(25, 0, 'Супермаркет', 7, 0, 0, 0, 0, '0', 1745107200, 3500000, 25000, 1, 0, 0, 0, 0, 119.338, 662.127, 12.3947, 121.653, 661.458, 12.2667, 249.497, 0, 0, 0, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(26, 0, 'Сотовый Салон', 7, 0, 0, 0, 0, '0', 1743638400, 5500000, 25000, 9, 8, 0, 1, 0, 290.913, 972.861, 12.4812, 287.358, 973.058, 12.3362, 83.9741, 0, 0, 3, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(27, 0, 'Сотовый Салон', 14, 0, 0, 0, 0, '0', 1750032000, 5500000, 25000, 9, 8, 0, 0, 0, -2386.48, 259.489, 23.932, -2386.62, 256.495, 23.7133, 170.118, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(28, 0, 'Сотовый Салон', 15, 0, 0, 0, 0, '0', 1733616000, 5500000, 25000, 9, 8, 0, 0, 0, -610.818, -1602.63, 41.3544, -610.375, -1601.9, 41.2372, 330.318, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(29, 0, 'Магазин Одежды', 7, 0, 0, 0, 0, '0', 1750032000, 9500000, 25000, 5, 4, 0, 0, 0, 203.657, 828.66, 13.3831, 202.651, 824.677, 12.4385, 175.155, 0, 0, 6, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(30, 0, 'Магазин Одежды', 10, 0, 0, 0, 0, '0', 1733184000, 9500000, 25000, 5, 4, 0, 0, 0, 1945.65, 2069.14, 16.1989, 1945.4, 2065.31, 15.7053, 177.54, 0, 0, 0, 0, 0, 0, 0, 0, 99, 0, 0, 0),
(31, 0, 'Магазин Одежды', 15, 0, 0, 0, 0, '0', 1734220800, 9500000, 25000, 5, 4, 0, 0, 0, 2261.07, -2100.69, 21.9688, 2257.26, -2100.69, 21.9688, 90.8905, 0, 0, 0, 0, 0, 0, 0, 0, 99, 0, 0, 0),
(32, 0, 'Супермаркет', 4, 0, 0, 0, 0, '0', 1745539200, 3500000, 25000, 1, 0, 0, 0, 0, -2328.13, 1768.64, 53.5171, -2329.84, 1771.87, 53.2455, 26.9033, 0, 0, 0, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(33, 0, 'Минимаркет', 14, 0, 0, 0, 0, '0', 1743120000, 3500000, 25000, 1, 0, 0, 0, 0, -2596.29, 220.96, 12.7452, -2596.32, 226.959, 12.273, 356.196, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(34, 0, 'Бар Лыткарино', 14, 0, 0, 0, 0, '0', 1722556800, 3500000, 25000, 2, 1, 0, 0, 0, -2374.39, 191.454, 22.585, -2377.89, 192.157, 21.4604, 78.436, 0, 0, 0, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(35, 0, 'Бар Арзамас', 7, 0, 0, 0, 0, '0', 1722384000, 3500000, 25000, 2, 1, 0, 5, 0, -314.757, 410.387, 13.1136, -318.945, 410.909, 12.7574, 81.2002, 0, 0, 0, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(36, 0, 'Бар Батырево', 10, 0, 0, 0, 0, '0', 1719792000, 3500000, 25000, 2, 1, 0, 0, 0, 1890.89, 1887.5, 13.7548, 1890.9, 1891.4, 13.2227, 2.84345, 0, 0, 0, 0, 0, 0, 0, 0, 98, 0, 0, 0),
(37, 0, 'Минимаркет Лидер', 10, 0, 0, 0, 0, '0', 1745366400, 3500000, 25000, 1, 0, 0, 3, 0, 1921.68, 2093, 16.1989, 1917.67, 2093.06, 15.7053, 89.1557, 0, 0, 0, 0, 0, 0, 0, 0, 99, 0, 0, 0),
(38, 0, 'Частный Банк Центр', 7, 0, 0, 0, 0, '0', 1752537600, 12000000, 25000, 12, 11, 0, 0, 0, 556.529, 493.868, 16.6632, 555.15, 490.987, 16.6632, 158.479, 0, 0, 1, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(39, 0, 'Частный Банк Вектор', 10, 0, 0, 0, 0, '0', 1747526400, 12000000, 25000, 12, 11, 0, 0, 0, -420.411, -1541.55, 40.8522, -419.064, -1541.93, 40.4389, 252.914, 0, 0, 0, 0, 0, 0, 0, 0, 99, 0, 0, 0),
(40, 0, 'Частный Банк Рубль', 15, 0, 0, 0, 0, '0', 1734998400, 12000000, 25000, 12, 11, 0, 1, 0, 2376.6, -2139.26, 22.0776, 2376.57, -2142.28, 21.9584, 178.892, 0, 0, 0, 0, 0, 0, 0, 0, 99, 0, 0, 0),
(41, 0, 'Супермаркет', 7, 0, 0, 0, 0, '0', 1745020800, 3500000, 25000, 1, 0, 0, 0, 0, 696.786, 588.677, 12.213, 695.057, 589.479, 12.0021, 68.1279, 0, 0, 0, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(42, 0, 'Супермаркет', 7, 0, 0, 0, 0, '0', 1721433600, 3500000, 25000, 1, 0, 0, 0, 0, 293.406, 1549.33, 12, 295.201, 1549.06, 12, 266.255, 0, 0, 0, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(43, 0, 'Строющийся Ларёк', 15, 0, 0, 0, 0, '0', 1721347200, 7500000, 25000, 21, 0, 0, 0, 0, 2420.03, -2313.61, 21.9739, 2417.17, -2313.63, 21.9698, 88.6558, 0, 0, 0, 0, 0, 0, 0, 0, 99, 0, 0, 0),
(44, 0, 'Продуктовый Магазин', 15, 0, 0, 0, 0, '0', 1722470400, 3500000, 25000, 1, 0, 0, 0, 0, 2352.92, -1678.76, 22.2844, 2352.86, -1681.37, 21.9619, 180.192, 0, 0, 0, 0, 0, 0, 0, 0, 98, 0, 0, 0),
(45, 0, 'Супермаркет Лесной', 15, 0, 0, 0, 0, '0', 1735257600, 3500000, 25000, 1, 0, 0, 0, 0, -2136.09, -1943.89, 9.27954, -2134.05, -1942.36, 8.82145, 307.696, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(46, 0, 'Строющийся минимаркет', 4, 0, 0, 0, 0, '0', 1719273600, 7500000, 25000, 21, 0, 0, 0, 0, -2295.19, 1808.37, 53.2116, -2294.09, 1806.26, 53.1847, 210.562, 0, 0, 0, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(47, 0, 'Минимаркет', 2, 0, 0, 0, 0, '0', 1721260800, 3500000, 25000, 1, 0, 0, 0, 0, -2385.03, 2901.4, 38.009, -2383.14, 2901.52, 37.634, 269.614, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(48, 0, 'Магазин Одежды', 2, 0, 0, 0, 0, '0', 1734134400, 9500000, 25000, 5, 4, 0, 0, 0, -2494.26, 2937.34, 38.1184, -2494.18, 2934.87, 37.634, 179.71, 0, 0, 4, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(49, 0, 'Аптека Здоровье', 2, 0, 0, 0, 0, '0', 1733529600, 4000000, 25000, 32, 30, 0, 0, 0, -2555.89, 2952.54, 38.1887, -2550.72, 2934.48, 37.634, 181.422, 0, 0, 0, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(50, 0, 'Частный Банк Развитие', 2, 0, 0, 0, 0, '0', 1743292800, 12000000, 25000, 12, 11, 0, 0, 0, -2579.85, 2876.02, 37.6516, -2579.95, 2873.66, 37.634, 181.109, 0, 0, 3, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(51, 0, 'Парикмахерская', 15, 0, 0, 0, 0, '0', 1722556800, 8000000, 25000, 25, 24, 0, 0, 0, -2140.4, -186.626, 26.982, -2139.95, -184.421, 26.4351, 349.104, 0, 0, 0, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(52, 0, 'Шиномонтаж Высокий №2', 14, 0, 0, 0, 0, '0', 1737504000, 4000000, 25000, 23, 0, 0, 0, 0, -2152.82, 221.033, 24.4125, -2147.53, 226.478, 24.4125, 213.358, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(53, 0, 'Шиномонтаж Арзамас', 8, 0, 0, 0, 0, '0', 1752537600, 4000000, 25000, 23, 0, 0, 0, 0, -325.587, 333.067, 13.1182, -298.634, 338.112, 13.1133, 320.251, 0, 0, 4, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(54, 0, 'Шиномонтаж Средний №1', 13, 0, 0, 0, 0, '0', 1722211200, 4000000, 25000, 23, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99, 0, 0, 0),
(55, 0, 'Шиномонтаж Южный', 15, 0, 0, 0, 0, '0', 1734825600, 4000000, 25000, 23, 0, 0, 0, 0, 2178.19, -1846.22, 18.8225, 2175.37, -1848.26, 18.7993, 190.712, 0, 0, 0, 0, 0, 0, 0, 0, 99, 0, 0, 0),
(56, 0, 'Аренда авто', 8, 0, 0, 0, 0, '0', 1745020800, 7000000, 25000, 16, 15, 0, 0, 0, 478.233, 1737.51, 11.6863, 477.544, 1735.16, 11.6863, 163.478, 0, 0, 3, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(57, 0, 'Аренда авто', 15, 0, 0, 0, 0, '0', 1752451200, 7000000, 25000, 16, 15, 0, 0, 0, 2121.17, -1802.25, 18.9854, 2121.17, -1802.25, 18.9854, 270.845, 0, 0, 0, 0, 0, 0, 0, 0, 99, 0, 0, 0),
(58, 0, 'Аренда авто', 10, 0, 0, 0, 0, '0', 1745020800, 7000000, 25000, 16, 15, 0, 0, 0, 1730.73, 2467.89, 15.5433, 1732.01, 2468.81, 15.5433, 307.358, 0, 0, 0, 0, 0, 0, 0, 0, 99, 0, 0, 0),
(59, 0, 'Минимаркет', 7, 0, 0, 0, 0, '0', 1743120000, 3500000, 25000, 1, 0, 0, 0, 0, 583.366, 469.57, 16.6632, 581.072, 471.059, 16.6632, 55.6788, 0, 0, 4, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(60, 0, 'Минимаркет', 7, 0, 0, 0, 0, '0', 1721433600, 3500000, 25000, 1, 0, 0, 1, 0, 323.161, 778.981, 12.1719, 322.043, 776.254, 12.001, 159.32, 0, 0, 0, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(61, 0, 'Закусочная', 7, 0, 0, 0, 0, '0', 1750982400, 5500000, 25000, 31, 29, 0, 0, 0, 833.398, 645.386, 16.0282, 833.402, 643.548, 15.8857, 181.322, 0, 0, 0, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(62, 0, 'Минимаркет', 7, 0, 0, 0, 0, '0', 1722556800, 3500000, 25000, 1, 0, 0, 0, 0, 60.1198, 396.516, 10.9544, 56.5933, 398.802, 10.0171, 55.7735, 0, 0, 0, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(63, 0, 'Универсам', 7, 0, 0, 0, 0, '0', 1722470400, 3500000, 25000, 1, 0, 0, 1, 0, 155.578, 571.784, 12.2188, 151.563, 573.364, 12, 69.7289, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(64, 0, 'Закусочная', 7, 0, 0, 0, 0, '0', 1739318400, 5500000, 25000, 31, 29, 0, 0, 0, 588.92, 484.082, 16.6632, 586.816, 485.093, 16.6632, 73.4646, 0, 0, 4, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(65, 0, 'Сотовый Салон', 7, 0, 0, 0, 0, '0', 1739318400, 5500000, 25000, 9, 8, 0, 0, 0, 649.684, 654.404, 12.4325, 648.608, 651.569, 12, 159.27, 0, 0, 1, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(66, 0, 'Садовод Лесной', 15, 0, 0, 0, 0, '0', 1736121600, 7500000, 25000, 24, 23, 0, 0, 0, -2330.08, -1658.15, 8.79686, -2328.02, -1652.88, 8.65624, 33.8635, 0, 0, 0, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(67, 0, 'Аптека Батырево', 8, 0, 0, 0, 0, '0', 1721520000, 4000000, 25000, 32, 30, 0, 0, 0, 1981.2, 1893.36, 15.528, 1979.29, 1893.32, 15.528, 90.2554, 0, 0, 0, 0, 0, 0, 0, 0, 99, 0, 0, 0),
(68, 0, 'Барбер Шоп', 7, 0, 0, 0, 0, '0', 1750032000, 8000000, 25000, 25, 24, 0, 0, 0, 207.61, 829.749, 13.3831, 209.108, 827.279, 12.4385, 219.491, 0, 0, 3, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(69, 0, 'Автозапчасти Форсаж', 7, 0, 0, 0, 0, '0', 1745107200, 7700000, 25000, 26, 25, 0, 0, 0, 126.918, 681.441, 12.3947, 129.005, 680.396, 12.2667, 247.067, 0, 0, 3, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(70, 0, 'Автозапчасти Драйв', 15, 0, 0, 0, 0, '0', 1739059200, 7700000, 25000, 26, 25, 0, 0, 0, -430.215, -1584.68, 40.6123, -429.469, -1584.75, 40.4626, 255.203, 0, 0, 1, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(71, 0, 'Управление статистики', 7, 0, 0, 0, 0, '0', 1745539200, 3500000, 25000, 3, 2, 0, 1, 0, -315.982, 401.247, 13.5994, -319.503, 401.218, 12.6491, 81.7574, 0, 0, 0, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(72, 0, 'Статистика домов', 7, 0, 0, 0, 0, '0', 1745107200, 3500000, 25000, 4, 3, 0, 0, 0, 130.561, 690.728, 12.3947, 133.081, 689.978, 12.2667, 250.625, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(73, 0, 'Супермаркет', 15, 0, 0, 0, 0, '0', 1721347200, 3500000, 25000, 1, 0, 0, 0, 0, -596.403, -1490.4, 40.854, -595.117, -1491.24, 40.8184, 230.552, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(74, 0, 'Нотариус', 7, 0, 0, 0, 0, '0', 1743552000, 7500000, 25000, 29, 27, 0, 0, 0, -359.943, 1024.99, 13.2432, -366.886, 1024.87, 12.1494, 90.8673, 0, 0, 3, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(75, 0, 'Ресторан `Граф`', 7, 0, 0, 0, 0, '0', 1747612800, 5500000, 25000, 31, 29, 0, 0, 0, 111.751, 642.793, 12.3947, 113.899, 642.325, 12.2667, 248.933, 0, 0, 5, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(76, 0, 'Тир Шот', 15, 0, 0, 0, 0, '0', 1737417600, 7500000, 25000, 27, 26, 0, 0, 0, -2714.46, 2932.66, 37.7731, -2711.36, 2932.72, 37.7731, 269.518, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(77, 0, 'Тир Молния', 7, 0, 0, 0, 0, '0', 1747008000, 7500000, 25000, 27, 26, 0, 0, 0, 104.125, 623.361, 12.3947, 106.519, 622.661, 12.2667, 249.81, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(78, 0, 'Супермаркет', 15, 0, 0, 0, 0, '0', 1733616000, 3500000, 25000, 1, 0, 0, 0, 0, 198.581, 1504.56, 12.0004, 199.958, 1504.04, 12.0074, 266.069, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(79, 0, 'Супермаркет', 0, 0, 0, 0, 0, '0', 1722556800, 3500000, 25000, 1, 0, 0, 0, 0, 2533.53, -230.645, 2.56719, 2533.65, -229.164, 2.56719, 2.21655, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(80, 0, 'Супермаркет', 14, 0, 0, 0, 0, '0', 1721433600, 3500000, 25000, 1, 0, 0, 0, 0, -2349.09, 86.6462, 21.3267, -2347.87, 86.3275, 21.315, 258.502, 0, 0, 0, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(81, 0, 'Супермаркет', 8, 0, 0, 0, 0, '0', 1719446400, 3500000, 25000, 1, 0, 0, 0, 0, 45.2923, 1758.7, 9.42, 47.2911, 1758.85, 9.42, 273.566, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(82, 0, 'Супермаркет', 15, 0, 0, 0, 0, '0', 1741910400, 3500000, 25000, 1, 0, 0, 1, 0, -886.485, 1931.79, 45.5092, -885.056, 1931.7, 45.5166, 267.636, 0, 0, 6, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(83, 0, 'Прачечная Лаванда', 7, 0, 0, 0, 0, '0', 1745107200, 5000000, 25000, 30, 28, 0, 0, 0, 107.966, 633.148, 12.3947, 110.279, 632.665, 12.2667, 252.38, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(84, 0, 'Магазин Оружия №1', 7, 0, 0, 0, 0, '0', 1741564800, 8500000, 25000, 11, 10, 0, 0, 0, 2493.41, -325.528, 1.7662, 2493.5, -323.618, 1.21304, 1.41872, 0, 0, 6, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(85, 0, 'Магазин Оружия №2', 15, 0, 0, -1, 0, '52800', 1747267200, 7500000, 25000, 11, 10, 0, 0, 0, 2247.42, -1778.08, 22.0229, 2250.63, -1778.03, 22.0229, 267.903, 0, 0, 4, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(86, 0, 'Супермаркет', 8, 0, 0, 0, 0, '0', 1741478400, 3500000, 25000, 1, 0, 0, 0, 0, 300.421, 1784.2, 12.2032, 300.055, 1780.34, 12.1484, 176.534, 0, 0, 0, 0, 0, 0, 0, 0, 99, 0, 0, 0),
(87, 0, 'Спортзал Протеин', 7, 0, 0, 0, 0, '0', 1745107200, 6500000, 25000, 14, 13, 0, 0, 0, 253.053, 461.397, 12.0625, 253.691, 463.028, 12, 337.791, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(88, 0, 'Закусочная Гриль BBQ', 15, 0, 0, 0, 0, '0', 1722556800, 5500000, 25000, 31, 29, 0, 0, 0, 2692.45, -2137.34, 21.9932, 2692.43, -2138.7, 21.9932, 182.806, 0, 0, 0, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(89, 0, 'Аптека Доктор', 8, 0, 0, 0, 0, '0', 1745020800, 4000000, 25000, 32, 30, 0, 0, 0, 301.71, 1619.03, 12, 303.48, 1618.84, 12, 264.014, 0, 0, 5, 0, 0, 0, 0, 0, 99, 0, 0, 0),
(90, 0, 'Зоомагазин', 7, 0, 0, 0, 0, '0', 1722556800, 15000000, 25000, 34, 31, 0, 0, 0, -14.7438, 594.164, 12.7369, -14.1677, 596.258, 12.1963, 339.968, 0, 0, 0, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(91, 0, 'Супермаркет', 15, 0, 0, 0, 0, '0', 1744243200, 3500000, 25000, 1, 0, 0, 1, 0, 297.007, 1571.87, 12, 299.603, 1571.44, 12, 265.788, 0, 0, 0, -2, 2001, 0, 0, 0, 96, 0, 0, 0),
(92, 0, 'Ветряная электростанция №1', 15, 0, 0, 0, 0, '0', 1752537600, 15000000, 25000, 36, 32, 0, 0, 0, 928.054, 86.918, 12.0037, 928.43, 88.6804, 12.0037, 359.619, 0, 0, 1, -2, 10000, 0, 0, 0, 127, 0, 0, 0),
(93, 0, 'Ветряная электростанция №2', 15, 0, 0, 0, 0, '0', 1752537600, 15000000, 25000, 36, 32, 0, 0, 0, 884.164, 133.401, 12.0037, 883.837, 136.705, 12.0037, 9.4965, 0, 0, 2, -82, 10000, 0, 0, 0, 260, 0, 0, 0),
(94, 0, 'Закусочная', 15, 0, 0, 0, 0, '0', 1745020800, 5500000, 25000, 31, 29, 0, 1, 0, -2529.16, 2850.61, 37.634, -2529.19, 2848.94, 37.634, 181.109, 0, 0, 0, -2, 2001, 0, 0, 0, 103, 0, 0, 0),
(95, 0, 'Ветряная электростанция №3', 7, 0, 0, 0, 0, '0', 1741564800, 15000000, 25000, 36, 32, 0, 0, 0, -2059.49, 2644.18, 52.9135, -2059.32, 2646.26, 52.9163, 1.973, 0, 0, 3, -110, 10000, 0, 0, 0, 130, 0, 0, 0),
(96, 0, 'Ветряная электростанция №4', 7, 0, 0, 0, 0, '0', 1741392000, 15000000, 25000, 36, 32, 0, 0, 0, -1994.97, 2679.17, 48.6214, -1994.99, 2681.58, 48.4469, 4.8871, 0, 0, 4, -110, 10000, 0, 0, 0, 117, 0, 0, 0),
(97, 0, 'Ветряная электростанция №5', 7, 0, 0, 0, 0, '0', 1742428800, 15000000, 25000, 36, 32, 0, 0, 0, 2582.66, 1233.44, 16.0607, 2582.66, 1236.04, 16.0939, 12.7389, 0, 0, 5, -6, 10000, 0, 0, 0, 116, 0, 0, 0),
(98, 0, 'Ветряная электростанция №6', 7, 0, 0, 0, 0, '0', 1749081600, 15000000, 25000, 36, 32, 0, 0, 0, 2553.56, 1278.33, 13.5612, 2553.42, 1280.76, 13.4949, 11.1201, 0, 0, 6, 0, 35380, 0, 0, 0, 95, 0, 0, 0),
(99, 0, 'АЗС Кольцевая', 7, 0, 0, 0, 0, '0', 1750032000, 8925000, 25000, 37, 0, 0, 1, 0, 512.768, 431.684, 12, 515.089, 430.869, 12, 71.4642, 0, 0, 0, 0, 0, 0, 0, 0, 111, 0, 0, 0),
(100, 0, 'АЗС Мирный', 7, 0, 0, 0, 0, '0', 1750032000, 8925000, 25000, 37, 0, 0, 1, 0, 550.892, 1209.29, 4.9099, 551.365, 1212.98, 4.90209, 172.962, 0, 0, 0, 0, 0, 0, 0, 0, 99, 0, 0, 0),
(101, 0, 'АЗС Военная часть', 15, 0, 0, 0, 0, '0', 1752537600, 8925000, 25000, 37, 0, 0, 1, 0, 726.887, 2559.55, 12.1875, -2529.19, 2848.94, 37.634, 181.109, 0, 0, 0, 0, 0, 0, 0, 0, 99, 0, 0, 0),
(102, 0, 'АЗС Рублевская', 1, 0, 0, 0, 0, '0', 1746748800, 8925000, 25000, 37, 0, 0, 1, 0, 1890.06, -2909.72, 3.8898, -2529.19, 2848.94, 37.634, 181.109, 0, 0, 0, 0, 0, 0, 0, 0, 99, 0, 0, 0),
(103, 0, 'АЗС Старое Бусаево', 15, 0, 0, 0, 0, '0', 1735776000, 8925000, 25000, 37, 0, 0, 1, 0, -435.317, -1363.72, 40.3684, -2529.19, 2848.94, 37.634, 181.109, 0, 0, 0, 0, 0, 0, 0, 0, 99, 0, 0, 0),
(104, 0, 'АЗС Лесная', 15, 0, 0, 0, 0, '0', 1737590400, 8925000, 25000, 37, 0, 0, 1, 0, -2037.01, -2007.55, 8.5077, -2529.19, 2848.94, 37.634, 181.109, 0, 0, 0, 0, 0, 0, 0, 0, 99, 0, 0, 0),
(105, 0, 'АЗС Лыткарино', 14, 0, 0, 0, 0, '0', 1752537600, 8925000, 25000, 37, 0, 0, 1, 0, -2620.5, -37.8617, 12.1909, -2529.19, 2848.94, 37.634, 181.109, 0, 0, 0, 0, 0, 0, 0, 0, 99, 0, 0, 0),
(106, 0, 'АЗС Нижегородская', 4, 0, 0, 0, 0, '0', 1744588800, 8925000, 25000, 37, 0, 0, 1, 0, -2583.21, 1964.54, 52.9992, -2529.19, 2848.94, 37.634, 181.109, 0, 0, 0, 0, 0, 0, 0, 0, 99, 0, 0, 0),
(107, 0, 'АЗС Анашан', 15, 0, 0, 0, 0, '0', 1741824000, 8925000, 25000, 37, 0, 0, 1, 0, 1931.92, -850.887, 15.7839, -2529.19, 2848.94, 37.634, 181.109, 0, 0, 0, 0, 0, 0, 0, 0, 99, 0, 0, 0),
(108, 0, 'АЗС Воздушная', 12, 0, 0, 0, 0, '0', 1735084800, 8925000, 25000, 37, 0, 0, 1, 0, 1913.65, 1706.91, 15.94, -2529.19, 2848.94, 37.634, 181.109, 0, 0, 0, 0, 0, 0, 0, 0, 99, 0, 0, 0),
(109, 0, 'АЗС Южная', 15, 0, 0, 0, 0, '0', 1742601600, 8925000, 25000, 37, 0, 0, 1, 0, 2247.17, -1715.46, 22.0362, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99, 0, 0, 0),
(110, 0, 'АЗС Южная - 2', 15, 0, 0, 0, 0, '0', 1722297600, 8925000, 25000, 37, 0, 0, 1, 0, 2553.96, -2424.09, 21.8579, 2571.73, -1830.78, 21.98, 180.458, 0, 0, 0, 0, 0, 0, 0, 0, 99, 0, 0, 0),
(111, 0, 'АЗС Барвиха', 15, 0, 0, 0, 0, '0', 1743292800, 8925000, 25000, 37, 0, 0, 0, 0, 3980.1, 4324.28, 7.9306, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99, 0, 0, 0),
(112, 0, 'Продуктовый магазин', 15, 0, 0, 0, 0, '0', 1748390400, 3500000, 25000, 1, 0, 0, 0, 0, 2577.56, -2377.65, 22.9376, 2578.59, -2379.51, 21.9938, 178.071, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(113, 0, 'Частный банк `Рубль`', 15, 0, 0, 0, 0, '0', 1742083200, 12000000, 25000, 12, 11, 0, 0, 0, 2417.61, -1841.66, 22.1135, 2417.62, -1843.78, 21.8569, 176.005, 0, 0, 4, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(114, 0, 'Аптека Оптимальная', 15, 0, 0, 0, 0, '0', 1722211200, 4000000, 25000, 32, 30, 0, 0, 0, 2310.73, -1911.68, 21.9677, 2308.14, -1911.7, 21.8248, 91.1803, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(115, 0, 'Сотовый Салон', 15, 0, 0, 0, 0, '0', 1733097600, 5500000, 25000, 9, 8, 0, 0, 0, 2629.66, -2415.11, 22.7873, 2627.31, -2415.07, 22.0938, 89.0895, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(116, 0, 'Закусочная', 7, 0, 0, 0, 0, '0', 1736035200, 5500000, 25000, 31, 29, 0, 0, 0, 71.4358, 516.388, 12.5671, 73.4439, 519.386, 12.1029, 322.14, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(117, 0, 'Закусочная', 7, 0, 0, 0, 0, '0', 1721692800, 5500000, 25000, 31, 29, 0, 0, 0, 13.0411, 911.113, 12.3073, 13.7443, 909.57, 12.1042, 210.249, 0, 0, 0, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(118, 0, 'Нотариус', 7, 0, 0, 0, 0, '0', 1752537600, 7600000, 25000, 29, 27, 0, 0, 0, 123.15, 671.841, 12.3947, 125.737, 671.205, 12.2667, 250.186, 0, 0, 1, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(119, 0, 'Садовод `Егерь`', 10, 0, 0, 0, 0, '0', 1750032000, 5500000, 25000, 24, 23, 0, 0, 0, 1986.44, 1932.66, 15.8253, 1986.35, 1930.62, 15.8253, 179.518, 0, 0, 2, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(120, 0, 'Закусочная', 8, 0, 0, 0, 0, '0', 1737590400, 5500000, 25000, 31, 29, 0, 0, 0, 405.65, 1960.71, 8.16406, 408.231, 1960.24, 8.16406, 263.939, 0, 0, 0, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(121, 0, 'Бистро Юность', 10, 0, 0, 0, 0, '0', 1722124800, 5500000, 25000, 31, 29, 0, 0, 0, 1949.89, 1912.65, 15.4655, 1952.02, 1912.6, 15.4655, 272.164, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(122, 0, 'Ресторан Нива', 10, 0, 0, 0, 0, '0', 1733443200, 5500000, 25000, 31, 29, 0, 0, 0, 1856.28, 2251.3, 15.6172, 1859.05, 2251.18, 15.2729, 275.007, 0, 0, 0, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(123, 0, 'Автомойка', 10, 0, 0, 0, 0, '0', 1740441600, 5000000, 25000, 43, 0, 0, 0, 0, 526.776, 441.937, 12, 526.776, 441.937, 12, 275.007, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(124, 0, 'Автомойка', 10, 0, 0, 0, 0, '0', 1721520000, 5000000, 25000, 43, 0, 0, 0, 0, -2603.46, -23.6715, 12.1909, -2603.46, -23.6715, 12.1909, 275.007, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(125, 0, 'Автомойка', 10, 0, 0, 0, 0, '0', 1721174400, 5000000, 25000, 43, 0, 0, 0, 0, -2563.77, 1965.22, 52.9992, -2563.77, 1965.22, 52.9992, 275.007, 0, 0, 0, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(126, 0, 'Автомойка', 10, 0, 0, 0, 0, '0', 1721952000, 5000000, 25000, 43, 0, 0, 0, 0, 3992.24, 4341.27, 7.9306, 3992.24, 4341.27, 7.9306, 275.007, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(127, 0, 'Автомойка', 10, 0, 0, 0, 0, '0', 1721520000, 5000000, 25000, 43, 0, 0, 0, 0, 706.949, 2568.74, 12.1875, 706.949, 2568.74, 12.1875, 275.007, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(128, 0, 'Автомойка', 10, 0, 0, 0, 0, '0', 1721433600, 5000000, 25000, 43, 0, 0, 0, 0, 1896.01, -847.62, 14.7136, 1896.01, -847.62, 14.7136, 275.007, 0, 0, 0, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(129, 0, 'ТК `Лыткарино`', 13, 0, 0, 0, 0, '0', 1743120000, 9500000, 25000, 44, 0, 0, 0, 0, -2450.08, -80.6664, 13.9453, -2447.51, -69.3339, 13.9453, 346.645, 0, 0, 0, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(130, 0, 'ТК `Южный`', 13, 0, 0, 0, 0, '0', 1737504000, 9500000, 25000, 44, 0, 0, 0, 0, 2400.51, -735.415, 12.2941, 2428.02, -721.919, 12.3395, 346.645, 0, 0, 0, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(131, 0, 'ТК `Батырево`', 13, 0, 0, 0, 0, '0', 1735171200, 9500000, 25000, 44, 0, 0, 0, 0, 2049.79, 1862.34, 15.2734, 2049.83, 1850.77, 15.2734, 346.645, 0, 0, 3, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(132, 0, 'Магазин Улов', 13, 0, 0, 0, 0, '0', 1734134400, 70000000, 25000, 45, 0, 0, 0, 0, 2250.87, 1370.83, 11.4509, 2250.87, 1370.83, 11.4509, 346.645, 0, 0, 0, 0, 0, 0, 0, 0, 97, 0, 0, 0),
(133, 0, 'Магазин Рыбалка', 13, 0, 0, 0, 0, '0', 1722297600, 70000000, 25000, 45, 0, 0, 0, 0, -372.301, -1529.73, 40.4245, -60.9936, -977.736, 41.115, 346.645, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(134, 0, 'Магазин На крючке', 13, 0, 0, 0, 0, '0', 1737590400, 70000000, 25000, 45, 0, 0, 0, 0, 553.136, 1196.96, 4.9021, 553.136, 1196.96, 4.9021, 346.645, 0, 0, 3, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(135, 0, 'Продуктовый Магазин', 15, 0, 0, 0, 0, '0', 0, 5000000, 25000, 1, 0, 0, 0, 0, -377.045, -1491.19, 40.5495, -376.549, -1490.15, 40.4949, 331.277, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(136, 0, 'Магазин Оружия №3', 15, 0, 0, 0, 0, '0', 1751414400, 10000000, 25000, 11, 10, 0, 0, 0, -520.399, -1454.19, 41.6534, -519.969, -1454.86, 41.6534, 215.681, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(137, 0, 'АЗС \'Бусаевская\'', 15, 0, 0, 0, 0, '0', 1736812800, 8925000, 25000, 37, 0, 0, 1, 0, -479.805, -1835.86, 41.3267, -2529.19, 2848.94, 37.634, 181.109, 0, 0, 0, 0, 0, 0, 0, 0, 99, 0, 0, 0),
(138, 0, 'Нотариус', 15, 0, 0, 0, 0, '0', 1737504000, 7600000, 25000, 29, 27, 0, 0, 0, -319.472, -1439.69, 40.8313, -317.704, -1440.07, 40.5088, 258.42, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0, 0),
(139, 0, 'Таксопарк Арзамас', 15, 0, 0, 0, 0, '0', 1741564800, 7600000, 25000, 46, 16, 0, 0, 0, 217.492, 248.727, 11.594, 217.492, 248.727, 11.594, 249.915, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Структура таблицы `business_gps`
--

CREATE TABLE `business_gps` (
  `id` int(11) NOT NULL,
  `bid` int(11) NOT NULL,
  `pos` int(11) NOT NULL,
  `time` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `business_profit`
--

CREATE TABLE `business_profit` (
  `id` int(11) NOT NULL,
  `business_id` int(11) NOT NULL,
  `player_id` int(11) NOT NULL,
  `time` int(11) NOT NULL,
  `money` int(11) NOT NULL,
  `view` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `carsharing_cars`
--

CREATE TABLE `carsharing_cars` (
  `id` int(11) NOT NULL,
  `model_id` int(11) NOT NULL,
  `color_1` int(11) NOT NULL,
  `color_2` int(11) NOT NULL,
  `vinil` int(11) NOT NULL,
  `iznos` float NOT NULL,
  `maslo` int(11) NOT NULL,
  `pos_x` float NOT NULL,
  `pos_y` float NOT NULL,
  `pos_z` float NOT NULL,
  `angle` float NOT NULL,
  `number` varchar(22) NOT NULL DEFAULT 'PRIDE',
  `region` varchar(22) NOT NULL,
  `typenumber` int(22) NOT NULL DEFAULT 5,
  `price` int(11) NOT NULL DEFAULT 500,
  `alarm` int(2) NOT NULL,
  `key_in` int(2) NOT NULL,
  `create_time` int(11) NOT NULL,
  `milleage` float NOT NULL,
  `fuel` float NOT NULL DEFAULT 45
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Дамп данных таблицы `carsharing_cars`
--

INSERT INTO `carsharing_cars` (`id`, `model_id`, `color_1`, `color_2`, `vinil`, `iznos`, `maslo`, `pos_x`, `pos_y`, `pos_z`, `angle`, `number`, `region`, `typenumber`, `price`, `alarm`, `key_in`, `create_time`, `milleage`, `fuel`) VALUES
(2, 15195, 1, 1, 2, 246.826, 0, 316.799, 1619.7, 11.8677, 264.892, 'RADMIR', '', 5, 2000, 0, 0, 1651657434, 998.619, 45),
(3, 15198, 1, 1, 3, 0, 0, 1657.45, 2277.92, 13.8125, 92.6, 'RADMIR', '', 5, 2000, 0, 0, 1651657511, 547.071, 45),
(4, 15202, 1, 1, 0, 0, 0, -2456.01, 2858.76, 37.631, 91.4147, 'RADMIR', '', 5, 2000, 0, 0, 1651657633, 2206.88, 45),
(5, 15199, 1, 1, 0, 0, 0, -2680.39, 226.261, 12.0593, 269.115, 'RADMIR', '', 5, 2000, 0, 0, 1651657707, 1155.96, 45),
(6, 15195, 1, 1, 1, 0, 0, -2226.62, -334.402, 23.1819, 277.933, 'RADMIR', '', 5, 2000, 0, 0, 1651657815, 684.899, 45),
(7, 15197, 1, 1, 2, 0, 0, -497.593, 3355.25, 29.6387, 90.438, 'RADMIR', '', 5, 2000, 0, 0, 1651657908, 1250.54, 45),
(8, 15202, 1, 1, 3, 0, 0, 2437.09, -2667.91, 22.4297, 359.723, 'RADMIR', '', 5, 2000, 0, 0, 1651657993, 989.804, 45),
(9, 15198, 1, 1, 1, 0, 0, 2338.81, -1907.22, 21.4691, 90.4757, 'RADMIR', '', 5, 2000, 0, 0, 1651658043, 441.658, 45),
(10, 15195, 1, 1, 0, 0, 0, 192.644, 822.075, 11.8782, 160.977, 'RADMIR', '', 5, 2000, 0, 0, 1652513787, 1322.07, 45),
(11, 15198, 1, 1, 1, 0, 0, 2728.58, -2085.67, 20.894, 179.728, 'RADMIR', '', 5, 2000, 0, 0, 1652513950, 199.697, 45),
(12, 15197, 1, 1, 2, 0, 0, 2388.25, -2111.68, 21.762, 89.7402, 'RADMIR', '', 5, 2000, 0, 0, 1652514008, 489.09, 45),
(13, 15196, 1, 1, 3, 0, 0, 417.235, -2445.2, 34.5541, 90.057, 'RADMIR', '', 5, 2000, 0, 0, 1652514084, 572.43, 45),
(14, 15202, 1, 1, 0, 0, 0, -2448.14, 108.428, 18.3812, 78.8552, 'RADMIR', '', 5, 2000, 0, 0, 1652514215, 123.312, 45),
(15, 15201, 1, 1, 2, 0, 0, -2580.94, 1992.8, 52.835, 78.9532, 'RADMIR', '', 5, 2000, 0, 0, 1652514288, 370.446, 45),
(18, 15195, 1, 1, 1, 0, 0, 862.637, 545.25, 15.8857, 91.4126, 'RADMIR', '', 5, 5000, 0, 0, 1653031695, 303.684, 45),
(19, 15195, 1, 1, 1, 0, 0, 863.333, 541.292, 15.8857, 88.1122, 'RADMIR', '', 5, 5000, 0, 0, 1653031702, 422.813, 45),
(114, 15202, 1, 1, 1, 0, 0, 272.45, 1402.91, 12.0118, 80.325, 'RADMIR', '', 5, 2000, 0, 0, 1670071611, 992.958, 45);

-- --------------------------------------------------------

--
-- Структура таблицы `cars_accessories`
--

CREATE TABLE `cars_accessories` (
  `id` int(11) NOT NULL,
  `car_id` int(11) NOT NULL,
  `model_id` int(11) NOT NULL,
  `indx` int(11) NOT NULL,
  `PosX` float NOT NULL,
  `PosY` float NOT NULL,
  `PosZ` float NOT NULL,
  `RotX` float NOT NULL,
  `RotY` float NOT NULL,
  `RotZ` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `car_market`
--

CREATE TABLE `car_market` (
  `id` int(11) NOT NULL,
  `modelid` int(11) NOT NULL,
  `count` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

--
-- Дамп данных таблицы `car_market`
--

INSERT INTO `car_market` (`id`, `modelid`, `count`) VALUES
(1, 401, 1000),
(2, 404, 1000),
(3, 412, 1000),
(4, 421, 1000),
(5, 422, 1000),
(6, 439, 1000),
(7, 467, 1000),
(8, 478, 1000),
(9, 492, 1000),
(10, 496, 1000),
(11, 526, 1000),
(12, 527, 1000),
(13, 536, 1000),
(14, 542, 1000),
(15, 546, 1000),
(16, 547, 1000),
(17, 549, 1000),
(18, 555, 1000),
(19, 561, 1000),
(20, 565, 1000),
(21, 566, 1000),
(22, 567, 1000),
(23, 576, 1000),
(24, 600, 1000),
(25, 799, 1000),
(26, 15070, 1000),
(27, 15074, 1000),
(28, 15078, 1000),
(29, 15079, 1000),
(30, 15080, 1000),
(31, 15084, 1000),
(32, 15124, 1000),
(33, 15145, 1000),
(34, 15150, 1000),
(35, 15151, 1000),
(36, 436, 1000),
(37, 445, 1000),
(38, 458, 1000),
(39, 479, 1000),
(40, 491, 1000),
(41, 508, 1000),
(42, 534, 1000),
(43, 550, 1000),
(44, 554, 1000),
(45, 613, 1000),
(46, 15119, 1000),
(47, 15121, 1000),
(48, 15184, 1000),
(49, 15207, 1000),
(50, 15262, 1000),
(51, 15272, 1000),
(52, 15281, 1000),
(53, 15603, 1000),
(54, 15296, 1000),
(55, 15600, 1000),
(56, 15621, 1000),
(57, 15641, 1000),
(58, 15648, 1000),
(59, 15654, 1000),
(60, 15655, 1000),
(61, 15663, 1000),
(62, 517, 1000),
(63, 15698, 1000),
(64, 17403, 1000),
(65, 411, 993),
(66, 419, 999),
(67, 475, 1000),
(68, 477, 1000),
(69, 495, 1000),
(70, 507, 1000),
(71, 516, 995),
(72, 540, 1000),
(73, 551, 999),
(74, 559, 1000),
(75, 560, 1000),
(76, 562, 1000),
(77, 585, 1000),
(78, 589, 1000),
(79, 612, 999),
(80, 614, 1000),
(81, 908, 1000),
(82, 15065, 1000),
(83, 15066, 1000),
(84, 15067, 1000),
(85, 15068, 1000),
(86, 15069, 1000),
(87, 15072, 1000),
(88, 15077, 1000),
(89, 15081, 1000),
(90, 15086, 1000),
(91, 15087, 1000),
(92, 15088, 1000),
(93, 15090, 1000),
(94, 15093, 1000),
(95, 15115, 1000),
(96, 15118, 1000),
(97, 15125, 1000),
(98, 15128, 1000),
(99, 15131, 1000),
(100, 15141, 999),
(101, 15144, 1000),
(102, 15149, 1000),
(103, 15152, 1000),
(104, 587, 1000),
(105, 793, 1000),
(106, 798, 1000),
(107, 1326, 1000),
(108, 15073, 1000),
(109, 15092, 1000),
(110, 15106, 1000),
(111, 15147, 1000),
(112, 15140, 1000),
(113, 15157, 1000),
(114, 15162, 1000),
(115, 15163, 1000),
(116, 15168, 1000),
(117, 15171, 1000),
(118, 15180, 1000),
(119, 15181, 1000),
(120, 15183, 1000),
(121, 15185, 1000),
(122, 15191, 1000),
(123, 15209, 1000),
(124, 15219, 1000),
(125, 15203, 1000),
(126, 15240, 1000),
(127, 15226, 1000),
(128, 15214, 1000),
(129, 15221, 1000),
(130, 15220, 1000),
(131, 15231, 1000),
(132, 15265, 1000),
(133, 15271, 1000),
(134, 15273, 1000),
(135, 15274, 1000),
(136, 15276, 1000),
(137, 602, 1000),
(138, 699, 1000),
(139, 15275, 1000),
(140, 15602, 1000),
(141, 15605, 1000),
(142, 15619, 1000),
(143, 15645, 1000),
(144, 15651, 999),
(145, 15664, 1000),
(146, 15675, 1000),
(147, 15677, 1000),
(148, 474, 1000),
(149, 15693, 1000),
(150, 15280, 998),
(151, 17412, 1000),
(152, 909, 1000),
(153, 400, 997),
(154, 402, 996),
(155, 405, 999),
(156, 409, 1000),
(157, 410, 1000),
(158, 415, 1000),
(159, 429, 1000),
(160, 451, 1000),
(161, 466, 1000),
(162, 480, 1000),
(163, 489, 1000),
(164, 490, 1000),
(165, 494, 1000),
(166, 502, 1000),
(167, 503, 1000),
(168, 505, 1000),
(169, 506, 1000),
(170, 541, 1000),
(171, 543, 1000),
(172, 558, 1000),
(173, 573, 1000),
(174, 579, 1000),
(175, 604, 1000),
(176, 605, 1000),
(177, 794, 1000),
(178, 795, 999),
(179, 796, 1000),
(180, 797, 1000),
(181, 907, 1000),
(182, 965, 1000),
(183, 999, 1000),
(184, 15071, 1000),
(185, 15075, 1000),
(186, 15076, 1000),
(187, 15082, 1000),
(188, 15085, 1000),
(189, 15089, 1000),
(190, 15094, 1000),
(191, 15105, 1000),
(192, 15107, 1000),
(193, 15108, 1000),
(194, 15109, 1000),
(195, 15113, 1000),
(196, 15114, 1000),
(197, 15116, 1000),
(198, 15120, 1000),
(199, 15126, 1000),
(200, 15137, 1000),
(201, 15142, 1000),
(202, 15146, 998),
(203, 15148, 1000),
(204, 15153, 1000),
(205, 15158, 999),
(206, 15159, 1000),
(207, 15164, 1000),
(208, 15165, 999),
(209, 15166, 1000),
(210, 15167, 1000),
(211, 15169, 1000),
(212, 15170, 1000),
(213, 15172, 1000),
(214, 15173, 1000),
(215, 15178, 1000),
(216, 15187, 1000),
(217, 15188, 1000),
(218, 15192, 1000),
(219, 15225, 1000),
(220, 15237, 1000),
(221, 15211, 999),
(222, 15213, 1000),
(223, 15206, 1000),
(224, 15236, 1000),
(225, 15212, 999),
(226, 15224, 1000),
(227, 15216, 1000),
(228, 15210, 1000),
(229, 15228, 1000),
(230, 15217, 1000),
(231, 15215, 1000),
(232, 15222, 1000),
(233, 15227, 1000),
(234, 15218, 1000),
(235, 15204, 1000),
(236, 15235, 1000),
(237, 15230, 1000),
(238, 15266, 1000),
(239, 15246, 1000),
(240, 15247, 1000),
(241, 15248, 1000),
(242, 15249, 1000),
(243, 15250, 999),
(244, 15252, 1000),
(245, 15259, 1000),
(246, 15261, 1000),
(247, 15263, 1000),
(248, 15264, 1000),
(249, 15269, 1000),
(250, 15270, 1000),
(251, 533, 1000),
(252, 15286, 1000),
(253, 15284, 1000),
(254, 15288, 1000),
(255, 15289, 1000),
(256, 15290, 1000),
(257, 15287, 1000),
(258, 15601, 1000),
(259, 15298, 1000),
(260, 15611, 1000),
(261, 15622, 1000),
(262, 15626, 1000),
(263, 15628, 1000),
(264, 15630, 1000),
(265, 15637, 1000),
(266, 15640, 1000),
(267, 15653, 1000),
(268, 15652, 1000),
(269, 15662, 1000),
(270, 15666, 1000),
(271, 15669, 1000),
(272, 15673, 1000),
(273, 15678, 1000),
(274, 15690, 1000),
(275, 15613, 1000),
(276, 15205, 1000),
(277, 17415, 1000),
(278, 17416, 999),
(279, 17417, 999),
(280, 17418, 1000),
(281, 406, 1000),
(282, 435, 1000),
(283, 450, 1000),
(284, 456, 1000),
(285, 459, 1000),
(286, 482, 1000),
(287, 499, 1000),
(288, 514, 1000),
(289, 518, 1000),
(290, 584, 1000),
(291, 15083, 1000),
(292, 15095, 1000),
(293, 15096, 1000),
(294, 15098, 1000),
(295, 15099, 1000),
(296, 15100, 1000),
(297, 15101, 1000),
(298, 15102, 1000),
(299, 15103, 1000),
(300, 15232, 1000),
(301, 15268, 1000),
(302, 15097, 1000),
(303, 609, 1000),
(304, 469, 1000),
(305, 487, 1000),
(306, 15285, 1000),
(307, 15291, 1000),
(308, 446, 1000),
(309, 452, 1000),
(310, 454, 1000),
(311, 473, 1000),
(312, 493, 1000),
(313, 595, 1000),
(314, 15243, 1000),
(315, 15244, 1000),
(316, 15292, 1000),
(317, 15649, 1000),
(318, 15277, 1000),
(319, 15278, 1000),
(320, 15279, 1000),
(321, 424, 1000),
(322, 461, 999),
(323, 462, 1000),
(324, 463, 1000),
(325, 468, 1000),
(326, 471, 1000),
(327, 481, 1000),
(328, 483, 1000),
(329, 510, 1000),
(330, 521, 1000),
(331, 581, 1000),
(332, 586, 1000),
(333, 15127, 998),
(334, 15129, 1000),
(335, 15130, 1000),
(336, 15132, 1000),
(337, 15133, 1000),
(338, 15134, 998),
(339, 15135, 1000),
(340, 15136, 1000),
(341, 15139, 1000),
(342, 15245, 1000);

-- --------------------------------------------------------

--
-- Структура таблицы `change_names`
--

CREATE TABLE `change_names` (
  `id` int(11) NOT NULL,
  `owner_id` int(11) NOT NULL,
  `name` varchar(21) NOT NULL,
  `time` int(11) NOT NULL,
  `ip` varchar(16) NOT NULL DEFAULT '255.255.255.255'
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `charity`
--

CREATE TABLE `charity` (
  `id` int(11) NOT NULL,
  `uid` int(11) NOT NULL,
  `money` int(11) NOT NULL,
  `time` int(11) NOT NULL,
  `name` varchar(21) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `create_objects`
--

CREATE TABLE `create_objects` (
  `Name` varchar(30) NOT NULL,
  `Model` int(11) NOT NULL,
  `PosX` float NOT NULL,
  `PosY` float NOT NULL,
  `PosZ` float NOT NULL,
  `RotX` float NOT NULL,
  `RotY` float NOT NULL,
  `RotZ` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=cp1251 COLLATE=cp1251_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `daily_rewards_players`
--

CREATE TABLE `daily_rewards_players` (
  `id` int(11) NOT NULL,
  `uid` int(11) NOT NULL,
  `daily_items_1` int(11) NOT NULL,
  `daily_items_2` int(11) NOT NULL,
  `daily_items_3` int(11) NOT NULL,
  `daily_items_4` int(11) NOT NULL,
  `daily_items_5` int(11) NOT NULL,
  `daily_items_6` int(11) NOT NULL,
  `daily_items_7` int(11) NOT NULL,
  `daily_items_8` int(11) NOT NULL,
  `daily_items_9` int(11) NOT NULL,
  `daily_items_10` int(11) NOT NULL,
  `daily_items_11` int(11) NOT NULL,
  `daily_items_12` int(11) NOT NULL,
  `daily_items_13` int(11) NOT NULL,
  `daily_items_14` int(11) NOT NULL,
  `daily_items_15` int(11) NOT NULL,
  `daily_items_16` int(11) NOT NULL,
  `daily_items_17` int(11) NOT NULL,
  `daily_items_18` int(11) NOT NULL,
  `daily_items_19` int(11) NOT NULL,
  `daily_items_20` int(11) NOT NULL,
  `daily_items_21` int(11) NOT NULL,
  `daily_items_22` int(11) NOT NULL,
  `daily_items_23` int(11) NOT NULL,
  `daily_items_24` int(11) NOT NULL,
  `daily_items_25` int(11) NOT NULL,
  `daily_items_26` int(11) NOT NULL,
  `daily_items_27` int(11) NOT NULL,
  `daily_items_28` int(11) NOT NULL,
  `daily_open_1` int(11) NOT NULL,
  `daily_open_2` int(11) NOT NULL,
  `daily_open_3` int(11) NOT NULL,
  `daily_open_4` int(11) NOT NULL,
  `daily_open_5` int(11) NOT NULL,
  `daily_open_6` int(11) NOT NULL,
  `daily_open_7` int(11) NOT NULL,
  `daily_open_8` int(11) NOT NULL,
  `daily_open_9` int(11) NOT NULL,
  `daily_open_10` int(11) NOT NULL,
  `daily_open_11` int(11) NOT NULL,
  `daily_open_12` int(11) NOT NULL,
  `daily_open_13` int(11) NOT NULL,
  `daily_open_14` int(11) NOT NULL,
  `daily_open_15` int(11) NOT NULL,
  `daily_open_16` int(11) NOT NULL,
  `daily_open_17` int(11) NOT NULL,
  `daily_open_18` int(11) NOT NULL,
  `daily_open_19` int(11) NOT NULL,
  `daily_open_20` int(11) NOT NULL,
  `daily_open_21` int(11) NOT NULL,
  `daily_open_22` int(11) NOT NULL,
  `daily_open_23` int(11) NOT NULL,
  `daily_open_24` int(11) NOT NULL,
  `daily_open_25` int(11) NOT NULL,
  `daily_open_26` int(11) NOT NULL,
  `daily_open_27` int(11) NOT NULL,
  `daily_open_28` int(11) NOT NULL,
  `daily_type_1` int(11) NOT NULL,
  `daily_type_2` int(11) NOT NULL,
  `daily_type_3` int(11) NOT NULL,
  `daily_type_4` int(11) NOT NULL,
  `daily_type_5` int(11) NOT NULL,
  `daily_type_6` int(11) NOT NULL,
  `daily_type_7` int(11) NOT NULL,
  `daily_type_8` int(11) NOT NULL,
  `daily_type_9` int(11) NOT NULL,
  `daily_type_10` int(11) NOT NULL,
  `daily_type_11` int(11) NOT NULL,
  `daily_type_12` int(11) NOT NULL,
  `daily_type_13` int(11) NOT NULL,
  `daily_type_14` int(11) NOT NULL,
  `daily_type_15` int(11) NOT NULL,
  `daily_type_16` int(11) NOT NULL,
  `daily_type_17` int(11) NOT NULL,
  `daily_type_18` int(11) NOT NULL,
  `daily_type_19` int(11) NOT NULL,
  `daily_type_20` int(11) NOT NULL,
  `daily_type_21` int(11) NOT NULL,
  `daily_type_22` int(11) NOT NULL,
  `daily_type_23` int(11) NOT NULL,
  `daily_type_24` int(11) NOT NULL,
  `daily_type_25` int(11) NOT NULL,
  `daily_type_26` int(11) NOT NULL,
  `daily_type_27` int(11) NOT NULL,
  `daily_type_28` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `decoration`
--

CREATE TABLE `decoration` (
  `id` int(11) NOT NULL,
  `Model` int(11) NOT NULL,
  `PosX` float NOT NULL,
  `PosY` float NOT NULL,
  `PosZ` float NOT NULL,
  `RotX` float NOT NULL,
  `RotY` float NOT NULL,
  `RotZ` float NOT NULL,
  `Owner` int(11) NOT NULL,
  `Status` int(11) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `donate_items`
--

CREATE TABLE `donate_items` (
  `id` int(11) NOT NULL,
  `type` int(11) NOT NULL,
  `name` varchar(48) NOT NULL,
  `item_id` int(11) NOT NULL,
  `price` int(11) NOT NULL,
  `count` int(11) NOT NULL,
  `indx` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

--
-- Дамп данных таблицы `donate_items`
--

INSERT INTO `donate_items` (`id`, `type`, `name`, `item_id`, `price`, `count`, `indx`) VALUES
(5, 4, 'Дополнительный слот на жилье', 0, 350, 1, 1),
(6, 4, 'Дополнительный слот на бизнес', 0, 400, 1, 2),
(7, 4, 'Дополнительный слот на гараж', 0, 350, 1, 3),
(8, 4, 'Дополнительный слот на транспорт', 0, 250, 10, 4),
(9, 4, 'Дополнительный слот на огород', 0, 400, 1, 5),
(10, 4, 'Дополнительный слот на киоск', 0, 400, 1, 6),
(11, 4, 'Дополнительный слот на лот в аукционе', 0, 400, 1, 7),
(64, 2, 'Дед Мороз', 1, 333, 1, 0),
(65, 2, 'Мужчина в рубашке', 4, 350, 1, 0),
(66, 2, 'Рикардо Милос', 5, 350, 1, 0),
(67, 2, 'Мужчина', 6, 350, 1, 0),
(68, 2, 'Мужчина №2', 8, 350, 1, 0),
(69, 2, 'Дедушка', 10, 350, 1, 0),
(70, 2, 'Афроамериканец', 18, 350, 1, 0),
(71, 2, 'Футболистка', 19, 350, 1, 0),
(72, 2, 'Школьник', 35, 350, 1, 0),
(73, 2, 'Школьник-футболист', 36, 350, 1, 0),
(74, 2, 'Женщина', 40, 350, 1, 0),
(75, 2, 'Женщина №2', 41, 350, 1, 0),
(76, 2, 'Опер', 43, 350, 1, 0),
(77, 2, 'Паша Пэл (старый)', 47, 400, 1, 0),
(78, 2, 'Ковбой', 48, 350, 1, 0),
(79, 2, 'Качок', 51, 350, 1, 0),
(80, 2, 'Дед', 54, 350, 1, 0),
(81, 2, 'Мужчина №3', 58, 350, 1, 0),
(82, 2, 'Женщина №3', 63, 350, 1, 0),
(83, 2, 'Женщина №4', 64, 350, 1, 0),
(84, 2, 'Женщина №5', 65, 350, 1, 0),
(85, 2, 'Физрук', 66, 350, 1, 0),
(86, 2, 'Женщина №6', 69, 350, 1, 0),
(87, 2, 'Модник Off-White', 79, 350, 1, 0),
(88, 2, 'Хамез Родригес', 94, 350, 1, 0),
(89, 2, 'Гопник', 104, 350, 1, 0),
(90, 2, 'Модник Louis-Vitton', 115, 350, 1, 0),
(91, 2, 'Араб', 116, 400, 1, 0),
(92, 2, 'Женщина №6', 139, 350, 1, 0),
(93, 2, 'Женщина №7', 142, 350, 1, 0),
(94, 2, 'Мафиозий', 161, 350, 1, 0),
(95, 2, 'Мужчина №3', 166, 350, 1, 0),
(96, 2, 'Скала (старый)', 167, 350, 1, 0),
(97, 2, 'Мужчина №4', 174, 350, 1, 0),
(98, 2, 'Конор МакГрегор №1', 175, 450, 1, 0),
(99, 2, 'Ковбой №2', 176, 350, 1, 0),
(100, 2, 'Белый Adidas', 182, 399, 1, 0),
(101, 2, 'Монстр', 194, 400, 1, 0),
(102, 2, 'Мужчина №5', 206, 400, 1, 0),
(103, 2, 'Женщина №8', 244, 400, 1, 0),
(104, 2, 'Женщина №9', 245, 400, 1, 0),
(105, 2, 'Мужчина №6', 250, 400, 1, 0),
(106, 2, 'Вин Дизель', 258, 350, 1, 0),
(107, 2, 'Маленькая девочка', 264, 400, 1, 0),
(108, 2, 'Толстый', 269, 400, 1, 0),
(109, 2, 'Марлон Уэйанс', 270, 400, 1, 0),
(110, 2, 'Майк Тайсон', 271, 400, 1, 0),
(111, 2, 'Басскетболист', 292, 400, 1, 0),
(112, 2, 'Моргенштерн', 15320, 400, 1, 0),
(113, 2, 'Петров', 15336, 400, 1, 0),
(114, 2, 'Andy Fy', 15356, 400, 1, 0),
(115, 2, 'Булкин', 15357, 350, 1, 0),
(116, 2, 'Fresh', 15358, 350, 1, 0),
(117, 2, 'Пабло Эскобар', 15362, 350, 1, 0),
(118, 2, 'Паша Пэл (новый)', 15407, 350, 1, 0),
(119, 2, 'Супер Сус', 15414, 350, 1, 0),
(120, 2, 'Монстр с крыльями', 15415, 500, 1, 0),
(121, 2, 'Оно', 15416, 350, 1, 0),
(122, 2, 'Снегурочка', 15417, 350, 1, 0),
(123, 2, 'Lyashov', 15419, 350, 1, 0),
(124, 2, 'Slava Marlow', 15421, 350, 1, 0),
(125, 2, 'Grand', 15422, 350, 1, 0),
(126, 2, 'Валакас', 15423, 350, 1, 0),
(127, 2, 'Мужчина №7', 15427, 350, 1, 0),
(128, 2, 'Женщина №10', 15428, 350, 1, 0),
(129, 2, 'TheAronPlay', 15434, 350, 1, 0),
(130, 2, 'Despair Channel', 15436, 350, 1, 0),
(131, 2, 'Пол Уокер', 15453, 350, 1, 0),
(132, 2, 'Тони Монтана', 15454, 350, 1, 0),
(133, 2, 'Зубенко Михаил', 15455, 350, 1, 0),
(134, 2, 'Маленький монстр', 15480, 350, 1, 0),
(135, 2, 'Almazov', 15483, 350, 1, 0),
(136, 2, 'Бородач', 15484, 350, 1, 0),
(137, 2, 'Сергей Бурунов', 15485, 350, 1, 0),
(138, 2, 'Chekande', 15486, 350, 1, 0),
(139, 2, 'Coffy', 15487, 350, 1, 0),
(140, 2, 'Данилыч', 15488, 350, 1, 0),
(141, 2, 'Demartini', 15489, 350, 1, 0),
(142, 2, 'Teddy Guevara', 15490, 350, 1, 0),
(143, 2, 'Matrix', 15491, 350, 1, 0),
(144, 2, 'Чак Норрис', 15492, 400, 1, 0),
(145, 2, 'Скала (новый)', 15493, 350, 1, 0),
(146, 2, 'Skipper', 15494, 350, 1, 0),
(147, 2, 'Джейсон Стетхэм', 15496, 350, 1, 0),
(148, 2, 'TONINITE', 15497, 450, 1, 0),
(149, 2, 'Хасбик №1', 15498, 500, 1, 0),
(150, 2, 'Max Deep', 15499, 350, 1, 0),
(151, 2, 'Чёрно-белый мужчина', 15501, 350, 1, 0),
(152, 2, 'Гонщик', 15502, 350, 1, 0),
(153, 2, 'Леонардо ДиКаприо', 15504, 350, 1, 0),
(154, 2, 'Женщина №11', 15505, 350, 1, 0),
(155, 2, 'Мужчина №8', 15506, 350, 1, 0),
(156, 2, 'Мурад', 15515, 350, 1, 0),
(157, 2, 'Верка Сердючка', 15516, 350, 1, 0),
(158, 2, 'Джин Керри', 15517, 350, 1, 0),
(159, 2, 'Mellstroy', 15518, 350, 1, 0),
(160, 2, 'MYERS', 15519, 350, 1, 0),
(161, 2, 'Роман Абрамович', 15520, 350, 1, 0),
(162, 2, 'Бустер', 15528, 350, 1, 0),
(163, 2, 'Мужчина №9', 15529, 350, 1, 0),
(164, 2, 'Павел Дуров', 15530, 350, 1, 0),
(165, 2, 'Марк Грозный', 15533, 350, 1, 0),
(166, 2, 'Игорь Коломойский', 15534, 350, 1, 0),
(167, 2, 'Шейх', 15535, 500, 1, 0),
(168, 2, 'Tags', 15536, 450, 1, 0),
(169, 2, 'Уэнздей', 15538, 400, 1, 0),
(170, 2, 'Андрэ Боярский', 15543, 350, 1, 0),
(171, 2, 'Антоха', 15544, 350, 1, 0),
(172, 2, 'Колян', 15547, 350, 1, 0),
(173, 2, 'Вован', 15553, 350, 1, 0),
(174, 2, 'Макс Корж', 15548, 350, 1, 0),
(175, 2, 'Кролик', 15551, 350, 1, 0),
(176, 2, 'Паша Техник', 15552, 350, 1, 0),
(177, 2, 'Зубарев', 15554, 350, 1, 0),
(178, 2, 'Конор МакГрегор №2', 15558, 400, 1, 0),
(179, 2, 'Конор МакГрегор №3', 15559, 400, 1, 0),
(180, 2, 'Конор МакГрегор №4', 15560, 400, 1, 0),
(181, 2, 'Хасбик №2', 15563, 450, 1, 0),
(182, 2, 'Хасбик №3', 15564, 450, 1, 0),
(183, 2, 'Хасбик №4', 15565, 450, 1, 0),
(184, 2, 'Асхаб Тамаев', 15567, 400, 1, 0),
(185, 2, 'Тесак', 15568, 350, 1, 0),
(186, 2, 'Молодой Банан', 15586, 350, 1, 0),
(187, 2, 'Богатый Богдан', 15587, 350, 1, 0),
(188, 2, 'Нищий Богдан', 15588, 350, 1, 0),
(189, 2, 'Богдан СуперГерой', 15589, 350, 1, 0),
(190, 1, 'KIA K5 (полицейская)', 15620, 550, 1, 0),
(191, 1, 'BMW G30 (МВД) ', 598, 850, 1, 0),
(192, 1, 'Mercedes Benz GLS 63 AMG (МВД)', 15606, 850, 1, 0),
(193, 1, 'ВАЗ 2107 (МВД)', 596, 500, 1, 0),
(194, 1, 'Lada Vesta (МВД)', 15123, 550, 1, 0),
(195, 1, 'Skoda Octavia (МВД) ', 15186, 850, 1, 0),
(196, 1, 'BMW 1000R (МВД)', 15610, 850, 1, 0),
(197, 1, 'УАЗ Патриот (МВД)', 528, 550, 1, 0),
(198, 1, 'Tayota Camry (МВД)', 15241, 650, 1, 0),
(199, 1, 'BMW X5M (МВД)', 15608, 850, 1, 0),
(200, 1, 'Lada Granta (МВД)', 15607, 550, 1, 0),
(201, 1, 'Porshe 911 992 (МВД)', 15609, 850, 1, 0),
(202, 1, 'Audi RS-6 Avant (МВД)', 405, 850, 1, 0),
(203, 1, 'Служебный вертолёт \"Polmav (МВД)\"', 497, 950, 1, 0),
(204, 1, 'Mercedes AMG C63 S (МВД)', 15143, 850, 1, 0),
(208, 1, 'ВАЗ 2107 (МВД)', 596, 500, 1, 0),
(220, 1, 'Буханка «Инкассация»', 15117, 350, 1, 0),
(221, 1, 'Subaru Impreza RS SPORT', 535, 350, 1, 0),
(222, 1, 'Ferrari LaFerrari', 15182, 350, 1, 0),
(223, 1, 'BMW M5 F90 CS', 15175, 350, 1, 0),
(224, 1, 'Mercedes-Benz SLS AMG', 15176, 350, 1, 0),
(225, 1, 'HUMMER H1', 15177, 350, 1, 0),
(226, 1, 'Bentley 1928 8 litr', 15179, 350, 1, 0),
(227, 1, 'BMW 850', 15161, 350, 1, 0),
(228, 1, 'Bentley Turbo R', 15156, 350, 1, 0),
(229, 1, 'Mercedes Benz AMG McLaren SLR', 15160, 350, 1, 0),
(230, 1, 'Tesla Cybertruck', 15104, 350, 1, 0),
(232, 1, 'Lamborghini Aventador J', 15223, 350, 1, 0),
(233, 1, 'Mercedes Benz CLK-GTR', 15229, 350, 1, 0),
(234, 1, 'Mersedes W124 Coupe AMG', 15155, 350, 1, 0),
(235, 1, 'Mercedes-Benz 280sl', 15190, 350, 1, 0),
(236, 1, 'Dodge RAM srt', 15189, 350, 1, 0),
(237, 1, 'Quadra V-Tech', 15238, 350, 1, 0),
(238, 1, 'BMW M3 G80 CS', 15636, 400, 1, 0),
(239, 1, 'Bandito Багги', 568, 400, 1, 0),
(240, 1, 'Shelby Cobra Шелби Кобра', 15174, 450, 1, 0),
(241, 1, 'Napier Railton', 15233, 450, 1, 0),
(242, 1, 'ZAZ-4', 15639, 400, 1, 0),
(243, 1, 'Mercedes-Benz W126', 529, 350, 1, 0),
(245, 1, 'Ford Mustang 1967', 15177, 350, 1, 0),
(246, 1, 'Ford Hot Rod', 15229, 350, 1, 0),
(247, 1, 'Mercedes Benz G63 P900 ROCKET HE', 15294, 450, 1, 0),
(248, 1, 'Bentley UltraTank', 15616, 400, 1, 0),
(249, 1, 'International ProStar LT', 15618, 350, 1, 0),
(250, 1, 'ВОЛГА КГБ', 15604, 450, 1, 0),
(251, 1, 'Rolls-Royce Cullinan Bunker', 15282, 350, 1, 0),
(252, 1, 'Rolls-Royce Phantom VIII Bunker', 15283, 350, 1, 0),
(253, 1, 'Ferrari Enzo', 15624, 350, 1, 0),
(254, 1, 'Mercedes-Benz Puch', 15634, 350, 1, 0),
(255, 1, 'УАЗ-452 Пикап', 15635, 450, 1, 0),
(256, 1, 'БРДМ Охотник', 444, 350, 1, 0),
(257, 1, 'Lamborghini Tecnomar (Яхта)', 15646, 350, 1, 0),
(258, 1, 'Lamborghini Diablo', 15650, 400, 1, 0),
(259, 1, 'Chopper Skeleton', 15657, 350, 1, 0),
(260, 1, 'Phantom VII H', 15658, 350, 1, 0),
(261, 1, 'Phantom VII P', 15659, 350, 1, 0),
(262, 1, 'Tesla Semi', 15665, 350, 1, 0),
(263, 1, 'Mercedes Benz Brabus P900 Rocket', 15297, 450, 1, 0),
(264, 1, 'Гоночный ВАЗ 2101', 15617, 400, 1, 0),
(265, 1, 'Bentley Continental', 15623, 400, 1, 0),
(266, 1, 'BMW M4 CSL', 15633, 450, 1, 0),
(267, 1, 'Mercedes-AMG Project One', 15643, 450, 1, 0),
(268, 1, 'Honda NSX GP', 504, 450, 1, 0),
(269, 1, 'MB Brabus Crawler', 556, 450, 1, 0),
(270, 1, 'ГАЗ-82 \"ТАЙГА\"', 15612, 500, 1, 0),
(271, 1, 'Snow Snow', 15615, 350, 1, 0),
(272, 1, 'LC300 Safari', 15632, 450, 1, 0),
(273, 1, 'UAZ-452 Concept', 15631, 450, 1, 0),
(274, 1, 'ZAZ Project 965', 15638, 450, 1, 0),
(275, 1, 'Lamborghini Urus Mansory Travis edition', 15642, 450, 1, 0),
(276, 1, 'Toyota Supra A90 H', 15656, 450, 1, 0),
(277, 1, 'Lamborghini Huracan Sterrato', 15660, 450, 1, 0),
(278, 1, 'Bugatti Mistral', 15661, 500, 1, 0),
(279, 1, 'BMW M4 G82 Camper', 15668, 500, 1, 0),
(280, 1, 'ПАЗ-672', 413, 450, 1, 0),
(281, 1, 'ЛиАЗ-5256', 414, 450, 1, 0),
(282, 1, 'Daewoo Matiz Limousine', 426, 450, 1, 0),
(283, 1, 'Икаруc', 437, 400, 1, 0),
(284, 1, 'ГАЗ М1', 442, 400, 1, 0),
(285, 1, 'ГАЗ-24 «Волга»', 485, 400, 1, 0),
(286, 1, 'ПАЗ - 3205', 483, 400, 1, 0),
(287, 1, 'ЛАЗ - 695', 498, 400, 1, 0),
(288, 1, 'РАФ-2203 «Латвия»', 517, 400, 1, 0),
(289, 1, 'ГАЗ-М-20 «Победа»', 575, 400, 1, 0),
(290, 1, 'Москвич (АЗЛК - 400)', 545, 400, 1, 0),
(291, 1, 'ГАЗ-13 (Чайка)', 580, 400, 1, 0),
(292, 1, 'ЛиАЗ', 588, 400, 1, 0),
(293, 1, 'Avia A31', 609, 400, 1, 0),
(294, 1, 'Новогодняя Tesla Cybertruck', 15110, 400, 1, 0),
(295, 1, 'СМЗ СЗА', 15208, 400, 1, 0),
(296, 1, 'Volga Gladiator', 15267, 600, 1, 0),
(314, 5, 'Чертеж тюнинга MANSORY', 354, 777, 1, 0),
(315, 3, 'Рюкзак с топором', 15744, 250, 1, 8),
(316, 3, 'Рюкзак кристал', 15745, 300, 1, 8),
(317, 3, 'Рюкзак с феерверками ', 15747, 305, 1, 8),
(318, 3, 'Рюкзак бочка', 15748, 200, 1, 8),
(319, 3, 'Рюкзак печка', 15749, 300, 1, 8),
(320, 3, 'Рюкзак бинокль ', 15782, 400, 1, 8),
(321, 3, 'Ледяная шляпа мага', 15783, 500, 1, 4),
(322, 3, 'Посох шар', 15791, 500, 1, 12),
(323, 3, 'Украшение в руку якорь', 15792, 444, 1, 7),
(324, 3, 'Украшение в руку кирка', 15793, 444, 1, 7),
(325, 3, 'Украшение в руку леденец', 15794, 444, 1, 7),
(326, 3, 'Сумка с деньгами', 15851, 999, 1, 5),
(327, 3, 'Рюкзак зайка', 15878, 333, 1, 8),
(328, 3, 'Рюкзак зайка розовый', 15879, 333, 1, 8),
(329, 3, 'Бронижелет охотничий', 15890, 777, 1, 11),
(330, 3, 'Рюкзак охотничий', 15891, 777, 1, 8),
(331, 3, 'Рюкзак дельфинчик', 16459, 222, 1, 8),
(332, 3, 'Скейт', 16463, 555, 1, 18),
(333, 3, 'Скейт 2', 16464, 555, 1, 18),
(334, 3, 'Скейт с фруктами', 16465, 666, 1, 18),
(335, 3, 'Посох змея', 16473, 444, 1, 12),
(336, 3, 'Рюкзак паук', 16592, 888, 1, 8),
(337, 3, 'Рюкзак черный мишка', 16596, 333, 1, 8),
(338, 3, 'Джедайский меч красный', 16665, 222, 1, 7),
(339, 3, 'Джедайский меч синий', 16682, 333, 1, 7),
(340, 3, 'Две катаны', 16938, 250, 1, 22),
(341, 3, 'Шляпа самурая', 16936, 333, 1, 4),
(342, 3, 'Посох полумесяц', 16972, 222, 1, 12),
(343, 3, 'Посох любви', 16973, 333, 1, 12),
(344, 3, 'Шапка ушанка (Розовая)', 10999, 750, 1, 4),
(345, 3, 'Шапка Балаклава (Бежевая)', 15753, 750, 1, 4),
(346, 3, 'Рюкзак SPRAYGROUND', 17249, 1000, 1, 8),
(347, 3, 'Гоночный шлем', 15902, 1000, 1, 2),
(348, 5, 'Аксесуар \"Гелик\"', 17273, 5000, 1, 0),
(349, 3, 'Чемодан #1', 17151, 1000, 1, 7),
(350, 1, 'Mercedes-Benz SL63', 15684, 500, 1, 0),
(351, 1, 'Mercedes-Benz SL 63 Mansory', 15685, 1000, 1, 0),
(352, 1, 'Rolls Royce Spectre', 15686, 2000, 1, 0),
(353, 1, 'Porsche Gemballa Marsien', 15688, 2000, 1, 0),
(354, 2, 'Bosow', 15501, 500, 1, 0),
(355, 2, 'Космонавт', 15546, 444, 1, 0),
(356, 2, 'Масхалат', 15549, 777, 1, 0),
(357, 2, 'Петрович', 15569, 300, 1, 0),
(358, 2, 'Инстасамка', 15573, 222, 1, 0),
(359, 2, 'Олень', 15555, 1111, 1, 0),
(360, 2, 'Медведь', 15556, 1111, 1, 0),
(361, 2, 'Историк 6.2', 15579, 350, 1, 0),
(362, 2, 'Ахмед Венгалби', 15586, 555, 1, 0),
(363, 2, 'Big Baby Tape', 15595, 450, 1, 0),
(364, 2, 'Чумной доктор', 17005, 444, 1, 0),
(365, 2, 'Пальто', 17022, 333, 1, 0),
(366, 2, 'Марат', 17023, 333, 1, 0),
(367, 2, 'Усатый брабус', 17025, 777, 1, 0),
(368, 2, 'Янг Харди', 17048, 500, 1, 0),
(369, 2, 'Акула', 17049, 444, 1, 0),
(370, 2, 'Темнокожий Исполнитель', 17050, 650, 1, 0),
(371, 2, 'iShowSpeed', 17069, 555, 1, 0),
(372, 2, 'Фредди', 17071, 666, 1, 0),
(373, 2, 'Девушка Фредди', 17072, 666, 1, 0),
(374, 2, 'Джокер', 17075, 666, 1, 0),
(375, 2, 'Девушка Джокера', 17076, 666, 1, 0),
(376, 2, 'Девушка Пила', 17077, 666, 1, 0),
(377, 5, 'Аккамулятор', 156, 25, 2, 0),
(378, 5, 'Колесо', 155, 15, 1, 0),
(379, 5, 'Руль Mercedes AMG', 119, 20, 1, 0),
(380, 5, 'Инструменты', 153, 15, 1, 0),
(381, 5, 'Сварка', 154, 15, 1, 0),
(382, 5, 'Старый руль AMG', 189, 30, 1, 0),
(383, 5, 'Запчасти к рулю AMG', 190, 20, 2, 0),
(384, 5, 'Двигатель', 188, 40, 1, 0),
(385, 3, 'Шапка ушанка \"Розовая\"', 10999, 1000, 1, 4),
(386, 1, 'BMW M5 F90 ОБД', 15107, 500, 1, 0);

-- --------------------------------------------------------

--
-- Структура таблицы `donate_log`
--

CREATE TABLE `donate_log` (
  `id` int(11) NOT NULL,
  `uid` int(11) NOT NULL,
  `uip` varchar(16) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL DEFAULT '255.255.255.255',
  `time` int(11) NOT NULL,
  `donate` int(11) NOT NULL,
  `description` varchar(64) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL DEFAULT 'None'
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `donations`
--

CREATE TABLE `donations` (
  `id` int(11) NOT NULL,
  `acc_id` int(11) NOT NULL,
  `amount` int(11) NOT NULL,
  `time` varchar(16) NOT NULL,
  `date` varchar(16) NOT NULL,
  `activated` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `entrances`
--

CREATE TABLE `entrances` (
  `id` int(11) NOT NULL,
  `city` int(11) NOT NULL DEFAULT -1,
  `zone` int(11) NOT NULL DEFAULT -1,
  `floors` int(11) NOT NULL DEFAULT 2,
  `pos_x` float NOT NULL,
  `pos_y` float NOT NULL,
  `pos_z` float NOT NULL,
  `exit_x` float NOT NULL,
  `exit_y` float NOT NULL,
  `exit_z` float NOT NULL,
  `exit_angle` float NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `family`
--

CREATE TABLE `family` (
  `id` int(11) NOT NULL,
  `name` varchar(64) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `u_id` int(11) NOT NULL,
  `time` int(11) NOT NULL,
  `color` int(11) NOT NULL,
  `level` int(11) NOT NULL,
  `exp` int(11) NOT NULL,
  `rank1` varchar(32) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL DEFAULT 'Пусто',
  `rank2` varchar(32) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL DEFAULT 'Пусто',
  `rank3` varchar(32) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL DEFAULT 'Пусто',
  `rank4` varchar(32) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL DEFAULT 'Пусто',
  `rank5` varchar(32) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL DEFAULT 'Пусто',
  `rank6` varchar(32) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL DEFAULT 'Пусто',
  `rank7` varchar(32) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL DEFAULT 'Пусто',
  `rank8` varchar(32) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL DEFAULT 'Пусто',
  `rank9` varchar(32) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL DEFAULT 'Пусто',
  `rank10` varchar(32) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL DEFAULT 'Пусто',
  `money` int(11) NOT NULL,
  `drugs` int(11) NOT NULL,
  `tree` int(11) NOT NULL,
  `metal` int(11) NOT NULL,
  `ammo` int(11) NOT NULL,
  `house_id` int(11) NOT NULL DEFAULT -1,
  `score` int(11) NOT NULL,
  `pos_x` float NOT NULL,
  `pos_y` float NOT NULL,
  `pos_z` float NOT NULL,
  `pos_fa` float NOT NULL,
  `inter` float NOT NULL,
  `world` float NOT NULL,
  `r_TakeMoney` int(11) NOT NULL,
  `r_TakeDrugs` int(11) NOT NULL,
  `r_TakeMetall` int(11) NOT NULL,
  `r_TakeAmmo` int(11) NOT NULL,
  `r_Inv` int(11) NOT NULL,
  `r_UnInv` int(11) NOT NULL,
  `r_Mute` int(11) NOT NULL,
  `r_UnMute` int(11) NOT NULL,
  `r_Warn` int(11) NOT NULL,
  `r_UnWarn` int(11) NOT NULL,
  `r_GiveRang` int(11) NOT NULL,
  `family_cars` int(11) NOT NULL,
  `gang` int(11) NOT NULL,
  `day` int(11) NOT NULL,
  `year` int(11) NOT NULL,
  `mounth` int(11) NOT NULL,
  `hour` int(11) NOT NULL,
  `minute` int(11) NOT NULL,
  `second` int(11) NOT NULL,
  `skladst` int(11) NOT NULL,
  `mon_rank1` int(11) NOT NULL DEFAULT 100000,
  `mon_rank2` int(11) NOT NULL DEFAULT 100000,
  `mon_rank3` int(11) NOT NULL DEFAULT 100000,
  `mon_rank4` int(11) NOT NULL DEFAULT 100000,
  `mon_rank5` int(11) NOT NULL DEFAULT 100000,
  `mon_rank6` int(11) NOT NULL DEFAULT 100000,
  `mon_rank7` int(11) NOT NULL DEFAULT 100000,
  `mon_rank8` int(11) NOT NULL DEFAULT 100000,
  `mon_rank9` int(11) NOT NULL DEFAULT 100000,
  `mon_rank10` int(11) NOT NULL DEFAULT 100000,
  `pat_rank1` int(11) NOT NULL DEFAULT 100,
  `pat_rank2` int(11) NOT NULL DEFAULT 100,
  `pat_rank3` int(11) NOT NULL DEFAULT 100,
  `pat_rank4` int(11) NOT NULL DEFAULT 100,
  `pat_rank5` int(11) NOT NULL DEFAULT 100,
  `pat_rank6` int(11) DEFAULT 100,
  `pat_rank7` int(11) NOT NULL DEFAULT 100,
  `pat_rank8` int(11) NOT NULL DEFAULT 100,
  `pat_rank9` int(11) NOT NULL DEFAULT 100,
  `pat_rank10` int(11) NOT NULL DEFAULT 100,
  `mafia` int(11) NOT NULL,
  `CentralMansion` int(11) NOT NULL,
  `WestMansion` int(11) NOT NULL,
  `NorthMansion` int(11) NOT NULL,
  `PelaBase` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci ROW_FORMAT=COMPACT;

-- --------------------------------------------------------

--
-- Структура таблицы `family_cars`
--

CREATE TABLE `family_cars` (
  `id` int(11) NOT NULL,
  `owner_id` int(11) NOT NULL,
  `model_id` int(11) NOT NULL,
  `color_1` int(11) NOT NULL,
  `color_2` int(11) NOT NULL,
  `rang` int(11) NOT NULL,
  `pos_x` float NOT NULL,
  `pos_y` float NOT NULL,
  `pos_z` float NOT NULL,
  `angle` float NOT NULL,
  `fuel` float NOT NULL DEFAULT 40,
  `create_time` int(11) NOT NULL,
  `statusts` int(11) NOT NULL,
  `gryaz` float NOT NULL,
  `iznos` int(11) NOT NULL,
  `number` varchar(22) NOT NULL,
  `region` varchar(11) NOT NULL DEFAULT '---',
  `typenumber` int(11) NOT NULL,
  `diski` int(12) NOT NULL,
  `nitro` int(12) NOT NULL,
  `gidra` int(12) NOT NULL,
  `vinil` int(11) NOT NULL DEFAULT 4,
  `stcar` int(11) NOT NULL,
  `mileage` float NOT NULL,
  `status` int(11) NOT NULL,
  `alarm` int(11) NOT NULL,
  `health` float NOT NULL,
  `key_in` int(11) NOT NULL,
  `obves` varchar(111) NOT NULL,
  `toner` varchar(111) NOT NULL,
  `tonerinstall` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `family_log`
--

CREATE TABLE `family_log` (
  `id` int(11) NOT NULL,
  `fam_id` int(11) NOT NULL,
  `name` varchar(64) NOT NULL,
  `text` varchar(64) NOT NULL,
  `type` int(11) NOT NULL,
  `item` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_unicode_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `fuel_orders`
--

CREATE TABLE `fuel_orders` (
  `id` int(11) NOT NULL,
  `type` int(11) NOT NULL,
  `company` int(11) NOT NULL,
  `amount` int(11) NOT NULL,
  `price` int(11) NOT NULL,
  `time` int(11) NOT NULL,
  `btype` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `gang_repositories`
--

CREATE TABLE `gang_repositories` (
  `id` int(11) NOT NULL,
  `metall` int(11) NOT NULL,
  `ammo` int(11) NOT NULL,
  `drugs` int(11) NOT NULL,
  `money` int(11) NOT NULL,
  `lock` int(11) NOT NULL,
  `heal` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

--
-- Дамп данных таблицы `gang_repositories`
--

INSERT INTO `gang_repositories` (`id`, `metall`, `ammo`, `drugs`, `money`, `lock`, `heal`) VALUES
(1, 0, 0, 0, 0, 0, 0),
(2, 0, 0, 0, 0, 0, 0),
(3, 0, 0, 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Структура таблицы `gang_zones`
--

CREATE TABLE `gang_zones` (
  `id` int(11) NOT NULL,
  `min_x` float NOT NULL,
  `min_y` float NOT NULL,
  `max_x` float NOT NULL,
  `max_y` float NOT NULL,
  `fraction` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `garage`
--

CREATE TABLE `garage` (
  `id` int(11) NOT NULL,
  `owner_id` int(11) NOT NULL,
  `miami` int(11) NOT NULL DEFAULT 0,
  `rent_time` int(11) NOT NULL,
  `price` int(11) NOT NULL,
  `rent_price` int(11) NOT NULL,
  `lock` int(11) NOT NULL,
  `improvements` int(11) NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `angle` float NOT NULL,
  `exit_x` float NOT NULL,
  `exit_y` float NOT NULL,
  `exit_z` float NOT NULL,
  `exit_angle` float NOT NULL,
  `car_x` float NOT NULL,
  `car_y` float NOT NULL,
  `car_z` float NOT NULL,
  `car_angle` float NOT NULL,
  `eviction` float NOT NULL,
  `repairs` int(11) NOT NULL,
  `drugs` int(11) NOT NULL,
  `metall` int(11) NOT NULL,
  `ammo` int(11) NOT NULL,
  `money` int(11) NOT NULL,
  `type` int(11) NOT NULL DEFAULT 1
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci ROW_FORMAT=COMPACT;

--
-- Дамп данных таблицы `garage`
--

INSERT INTO `garage` (`id`, `owner_id`, `miami`, `rent_time`, `price`, `rent_price`, `lock`, `improvements`, `x`, `y`, `z`, `angle`, `exit_x`, `exit_y`, `exit_z`, `exit_angle`, `car_x`, `car_y`, `car_z`, `car_angle`, `eviction`, `repairs`, `drugs`, `metall`, `ammo`, `money`, `type`) VALUES
(0, 0, 0, 1746316800, 10500000, 15000, 0, 0, 513.692, 484.02, 12.1586, 0, 2314.67, 1562.93, 11.3457, 93.1619, 2419.91, -1436.62, 81.0489, 180.277, 0, 0, 0, 0, 0, 0, 3),
(1, 0, 0, 1737676800, 10500000, 15000, 0, 0, -1258.61, -2339.82, 30.9343, 0, -1262.06, -2338.52, 30.9418, 70.1678, -1265.09, -2337.31, 30.5185, 70.0488, 0, 0, 0, 0, 0, 0, 3),
(2, 0, 0, 1737504000, 10500000, 15000, 0, 0, -1241.44, -2292.68, 30.9418, 0, -1245.03, -2291.29, 30.9418, 70.1739, -1247.97, -2290.33, 30.519, 69.9272, 0, 0, 0, 0, 0, 0, 3),
(3, 0, 0, 1737504000, 10500000, 15000, 0, 0, -1224.28, -2245.51, 30.9343, 0, -1228.03, -2244.17, 30.9418, 69.967, -1230.79, -2243.29, 30.5197, 70.0457, 0, 0, 0, 0, 0, 0, 3),
(4, 0, 0, 1736899200, 10500000, 15000, 0, 0, -1207.11, -2198.36, 30.9418, 0, -1210.65, -2197.13, 30.9343, 70.7734, -1213.46, -2196, 30.5148, 71.2563, 0, 0, 0, 0, 0, 0, 3),
(5, 0, 0, 1737417600, 10500000, 15000, 0, 2, -1189.95, -2151.2, 30.9408, 0, -1193.4, -2149.91, 30.9408, 70.3667, -1196.32, -2148.95, 30.5175, 69.6376, 0, 0, 0, 0, 0, 0, 3),
(6, 0, 0, 1721347200, 10500000, 15000, 0, 0, -1172.77, -2104.01, 30.9408, 0, -1176.62, -2102.63, 30.9408, 70.573, -1179.36, -2101.82, 30.5187, 71.1392, 0, 0, 0, 0, 0, 0, 3),
(7, 0, 0, 1721865600, 10500000, 15000, 0, 2, -1155.63, -2056.92, 30.9408, 0, -1159.1, -2055.7, 30.9408, 70.1843, -1162.07, -2054.64, 30.5173, 68.8237, 0, 0, 0, 0, 0, 0, 3),
(8, 0, 0, 1721952000, 10500000, 15000, 0, 2, -1138.45, -2009.71, 30.9408, 0, -1141.11, -2008.51, 30.9408, 71.1242, -1144.67, -2007.48, 30.5187, 70.9596, 0, 0, 0, 0, 0, 0, 3),
(9, 0, 0, 1755043200, 10500000, 15000, 0, 3, -1121.27, -1962.52, 30.9408, 0, -1124.77, -1961.28, 30.9408, 69.992, -1127.57, -1960.3, 30.5185, 69.6379, 0, 0, 0, 0, 0, 0, 3),
(10, 0, 0, 1754956800, 10500000, 15000, 0, 3, -1156.31, -1937.77, 30.9408, 0, -1157.56, -1941.28, 30.9408, 161.131, -1158.58, -1944.3, 30.5187, 159.732, 0, 0, 0, 0, 0, 0, 3),
(11, 0, 0, 1754956800, 10500000, 15000, 0, 0, -1216.97, -1902.86, 30.9408, 0, -1213.53, -1904.07, 30.9408, 250.25, -1210.79, -1904.97, 30.5158, 250.964, 0, 0, 0, 0, 0, 0, 3),
(12, 0, 0, 1722211200, 10500000, 15000, 0, 2, -1234.16, -1950.07, 30.9408, 0, -1230.78, -1951.21, 30.9408, 250.736, -1227.62, -1952.33, 30.5183, 250.298, 0, 0, 0, 0, 0, 0, 3),
(13, 0, 0, 1722124800, 10500000, 15000, 0, 2, -1251.32, -1997.23, 30.9408, 0, -1248.25, -1998.26, 30.9408, 249.189, -1244.69, -1999.49, 30.5201, 250.893, 0, 0, 0, 0, 0, 0, 3),
(14, 0, 0, 1746316800, 10500000, 15000, 0, 0, -1268.49, -2044.39, 30.9408, 0, -1265.16, -2045.62, 30.9408, 250.346, -1262.14, -2046.39, 30.5157, 251.457, 0, 0, 0, 0, 0, 0, 3),
(15, 0, 0, 1722556800, 10500000, 15000, 0, 2, -1285.65, -2091.54, 30.9408, 0, -1282.24, -2092.73, 30.9408, 250.312, -1279.16, -2093.79, 30.5253, 250.553, 0, 0, 0, 0, 0, 0, 3),
(16, 0, 0, 1722556800, 10500000, 15000, 0, 0, -1302.83, -2138.75, 30.9418, 0, -1299.62, -2139.84, 30.9343, 250.264, -1296.68, -2140.95, 30.5207, 250.142, 0, 0, 0, 0, 0, 0, 3),
(17, 0, 0, 1722038400, 10500000, 15000, 0, 2, -1319.98, -2185.86, 30.9343, 0, -1316.77, -2187.01, 30.9418, 250.213, -1313.79, -2187.98, 30.5222, 249.075, 0, 0, 0, 0, 0, 0, 3),
(18, 0, 0, 1721606400, 10500000, 15000, 0, 0, -1337.15, -2233.04, 30.9418, 0, -1333.78, -2234.37, 30.9343, 249.341, -1330.65, -2235.41, 30.5194, 249.289, 0, 0, 0, 0, 0, 0, 3),
(19, 0, 0, 1737504000, 10500000, 15000, 0, 0, -1354.32, -2280.22, 30.9343, 0, -1350.91, -2281.4, 30.9418, 251.381, -1347.76, -2282.43, 30.5195, 250.696, 0, 0, 0, 0, 0, 0, 3),
(20, 0, 0, 1754956800, 10500000, 15000, 0, 3, -1371.47, -2327.32, 30.9418, 0, -1368.14, -2328.42, 30.9343, 250.504, -1365.11, -2329.5, 30.5177, 250.786, 0, 0, 0, 0, 0, 0, 3),
(21, 0, 0, 1754956800, 10500000, 15000, 0, 0, -1336.46, -2352.17, 30.9418, 0, -1335.24, -2348.85, 30.9418, 340.67, -1334.21, -2345.92, 30.5168, 340.143, 0, 0, 0, 0, 0, 0, 3),
(22, 0, 0, 1741564800, 10500000, 15000, 0, 0, -1278.52, -2307.73, 30.9418, 0, -1275.16, -2308.87, 30.9418, 250.082, -1272.22, -2309.97, 30.5166, 250.055, 0, 0, 0, 0, 0, 0, 3),
(23, 0, 0, 1737158400, 10500000, 15000, 0, 0, -1261.37, -2260.62, 30.9418, 0, -1258.15, -2261.86, 30.9418, 249.701, -1255.09, -2262.88, 30.52, 251.187, 0, 0, 0, 0, 0, 0, 3),
(24, 0, 0, 1734998400, 10500000, 15000, 0, 0, -1244.24, -2213.54, 30.9343, 0, -1240.81, -2214.67, 30.9418, 250.283, -1237.95, -2215.7, 30.517, 250.893, 0, 0, 0, 0, 0, 0, 3),
(25, 0, 0, 1734998400, 10500000, 15000, 0, 0, -1227.05, -2166.32, 30.9418, 0, -1223.55, -2167.62, 30.9343, 250.669, -1220.68, -2168.69, 30.5179, 251.109, 0, 0, 0, 0, 0, 0, 3),
(26, 0, 0, 1734998400, 10500000, 15000, 0, 0, -1209.88, -2119.12, 30.9408, 0, -1206.72, -2120.19, 30.9408, 250.335, -1203.83, -2121.19, 30.5192, 251.581, 0, 0, 0, 0, 0, 0, 3),
(27, 0, 0, 1722470400, 10500000, 15000, 0, 2, -1192.71, -2072, 30.9408, 0, -1189.58, -2073.19, 30.9408, 249.759, -1186.6, -2074.22, 30.5171, 250.822, 0, 0, 0, 0, 0, 0, 3),
(28, 0, 0, 1722211200, 10500000, 15000, 0, 2, -1175.55, -2024.82, 30.9408, 0, -1172.25, -2025.98, 30.9408, 249.395, -1169.05, -2027.13, 30.5182, 248.903, 0, 0, 0, 0, 0, 0, 3),
(29, 0, 0, 1755043200, 10500000, 15000, 0, 3, -1158.38, -1977.64, 30.9408, 0, -1155.17, -1978.77, 30.9408, 250.111, -1152.06, -1979.96, 30.5177, 250.419, 0, 0, 0, 0, 0, 0, 3),
(30, 0, 0, 1722297600, 10500000, 15000, 0, 0, -1214.22, -1982.14, 30.9408, 0, -1217.56, -1980.84, 30.9408, 70.1728, -1220.28, -1979.94, 30.5198, 70.266, 0, 0, 0, 0, 0, 0, 3),
(31, 0, 0, 1722470400, 10500000, 15000, 0, 2, -1231.4, -2029.31, 30.9408, 0, -1234.61, -2028.08, 30.9408, 70.2747, -1237.59, -2027, 30.517, 70.4788, 0, 0, 0, 0, 0, 0, 3),
(32, 0, 0, 1734998400, 10500000, 15000, 0, 0, -1248.54, -2076.44, 30.9408, 0, -1251.78, -2075.22, 30.9408, 69.0739, -1254.83, -2074.11, 30.535, 69.5726, 0, 0, 0, 0, 0, 0, 3),
(33, 0, 0, 1722038400, 10500000, 15000, 0, 0, -1265.72, -2123.63, 30.9408, 0, -1268.98, -2122.46, 30.9408, 69.0848, -1271.97, -2121.24, 30.5167, 70.2226, 0, 0, 0, 0, 0, 0, 3),
(34, 0, 0, 1721692800, 10500000, 15000, 0, 2, -1282.88, -2170.77, 30.9418, 0, -1286.21, -2169.44, 30.9343, 68.9021, -1289.03, -2168.4, 30.5168, 69.8002, 0, 0, 0, 0, 0, 0, 3),
(35, 0, 0, 1721347200, 10500000, 15000, 0, 0, -1300.05, -2217.93, 30.9418, 0, -1303.15, -2216.81, 30.9418, 70.4763, -1306.24, -2215.71, 30.5185, 68.9171, 0, 0, 0, 0, 0, 0, 3),
(36, 0, 0, 1737158400, 10500000, 15000, 0, 0, -1317.22, -2265.11, 30.9418, 0, -1320.57, -2263.81, 30.9343, 70.168, -1323.29, -2262.77, 30.5181, 69.0438, 0, 0, 0, 0, 0, 0, 3),
(37, 0, 0, 1734825600, 10500000, 15000, 0, 0, -1334.36, -2312.2, 30.9343, 0, -1337.56, -2311.03, 30.9418, 70.1089, -1340.45, -2309.97, 30.5223, 69.5561, 0, 0, 0, 0, 0, 0, 3),
(38, 0, 0, 1741737600, 7500000, 15000, 0, 0, 1637.62, 2371.02, 13.1821, 0, 1643.24, 2371.17, 13.1896, 273.664, 1645.7, 2371.31, 13.2274, 271.478, 0, 0, 0, 0, 0, 0, 2),
(39, 0, 0, 1733011200, 7500000, 15000, 0, 2, 1637.62, 2390.22, 13.1821, 0, 1641.08, 2390.27, 13.1821, 272.302, 1646.11, 2390.32, 13.225, 271.498, 0, 0, 0, 0, 0, 0, 2),
(40, 0, 0, 1722384000, 7500000, 15000, 0, 0, 1637.61, 2411.61, 13.1821, 0, 1640.95, 2411.79, 13.1821, 270.051, 1645.49, 2411.53, 13.2263, 271.031, 0, 0, 0, 0, 0, 0, 2),
(41, 0, 0, 1721520000, 7500000, 15000, 0, 0, 1637.6, 2430.81, 13.1821, 0, 1640.9, 2430.67, 13.1821, 271.206, 1645.24, 2430.81, 13.2221, 270.936, 0, 0, 0, 0, 0, 0, 2),
(42, 0, 0, 1721952000, 7500000, 15000, 0, 2, 1633.74, 2463.63, 13.1836, 0, 1633.76, 2466.69, 13.1836, 0.211217, 1633.5, 2471.83, 13.2238, 1.21853, 0, 0, 0, 0, 0, 0, 2),
(43, 0, 0, 1722124800, 7500000, 15000, 0, 1, 1614.65, 2463.63, 13.1836, 0, 1614.51, 2466.26, 13.1836, 0.027976, 1614.42, 2471.18, 13.2239, 0.974783, 0, 0, 0, 0, 0, 0, 2),
(44, 0, 0, 1721779200, 7500000, 15000, 0, 2, 1613.07, 2483.2, 13.1836, 0, 1613.22, 2479.5, 13.1836, 176.171, 1613.53, 2475.59, 13.2231, 183.315, 0, 0, 0, 0, 0, 0, 2),
(45, 0, 0, 1721606400, 7500000, 15000, 0, 2, 1632.24, 2483.2, 13.1836, 0, 1632.33, 2479.93, 13.1836, 175.8, 1632.53, 2474.97, 13.2239, 182.679, 0, 0, 0, 0, 0, 0, 2),
(46, 0, 0, 1721433600, 7500000, 15000, 0, 0, 1632.17, 2520.91, 13.1836, 0, 1632.37, 2524.17, 13.1836, 356.27, 1631.96, 2528.32, 13.2207, 2.04383, 0, 0, 0, 0, 0, 0, 2),
(47, 0, 0, 1721260800, 7500000, 15000, 0, 0, 1613.17, 2520.91, 13.1836, 0, 1613.05, 2524.4, 13.1836, 3.29063, 1613.02, 2528.31, 13.2201, 0.908061, 0, 0, 0, 0, 0, 0, 2),
(48, 0, 0, 1721260800, 7500000, 15000, 0, 0, 1613.14, 2540.49, 13.1836, 0, 1613.13, 2537.5, 13.1836, 181.504, 1613.14, 2532.77, 13.2261, 182.782, 0, 0, 0, 0, 0, 0, 2),
(49, 0, 0, 1721260800, 7500000, 15000, 0, 0, 1632.3, 2540.48, 13.1836, 0, 1632.31, 2537.49, 13.1836, 181.593, 1632.24, 2532.74, 13.2232, 181.654, 0, 0, 0, 0, 0, 0, 2),
(50, 0, 0, 1722470400, 7500000, 15000, 0, 2, 1632.19, 2580.22, 13.1836, 0, 1632.15, 2582.9, 13.1836, 6.60951, 1632.49, 2587.45, 13.2221, 0.542486, 0, 0, 0, 0, 0, 0, 2),
(51, 0, 0, 1721260800, 7500000, 15000, 0, 0, 1613.08, 2580.22, 13.1836, 0, 1613.03, 2583, 13.1836, 0.34378, 1613.16, 2587.88, 13.2204, 0.793523, 0, 0, 0, 0, 0, 0, 2),
(52, 0, 0, 1745020800, 7500000, 15000, 0, 0, 1613.12, 2599.79, 13.1836, 0, 1613.09, 2597.37, 13.1836, 180.488, 1613.14, 2591.92, 13.2223, 180.331, 0, 0, 0, 0, 0, 0, 2),
(53, 0, 0, 1720742400, 7500000, 15000, 0, 0, 1632.27, 2599.79, 13.1836, 0, 1632.47, 2596.98, 13.1836, 184.739, 1631.83, 2592.09, 13.2225, 180.61, 0, 0, 0, 0, 0, 0, 2),
(54, 0, 0, 1721433600, 7500000, 15000, 0, 0, 1662.91, 2599.32, 13.1836, 0, 1663.12, 2596.46, 13.1836, 184.568, 1662.65, 2591.92, 13.2223, 180.585, 0, 0, 0, 0, 0, 0, 2),
(55, 0, 0, 1721779200, 7500000, 15000, 0, 0, 1681.99, 2599.32, 13.1836, 0, 1682.1, 2596.89, 13.1836, 181.821, 1681.77, 2591.87, 13.2248, 180.602, 0, 0, 0, 0, 0, 0, 2),
(56, 0, 0, 1722556800, 7500000, 15000, 0, 2, 1681.88, 2579.75, 13.1836, 0, 1681.84, 2582.51, 13.1836, 3.10129, 1681.95, 2587.68, 13.2233, 2.11341, 0, 0, 0, 0, 0, 0, 2),
(57, 0, 0, 1722470400, 7500000, 15000, 0, 0, 1662.86, 2579.74, 13.1836, 0, 1662.97, 2582.77, 13.1836, 2.92556, 1663.22, 2587.34, 13.2212, 1.01799, 0, 0, 0, 0, 0, 0, 2),
(58, 0, 0, 1740960000, 7500000, 15000, 0, 0, 1662.99, 2540.02, 13.1836, 0, 1662.9, 2536.97, 13.1836, 180.28, 1662.88, 2532.6, 13.2231, 181.413, 0, 0, 0, 0, 0, 0, 2),
(59, 0, 0, 1743292800, 7500000, 15000, 0, 2, 1682.09, 2540.02, 13.1836, 0, 1682.16, 2537.33, 13.1836, 181.569, 1681.88, 2532.21, 13.2255, 181.916, 0, 0, 0, 0, 0, 0, 2),
(60, 0, 0, 1722211200, 7500000, 15000, 0, 0, 1681.99, 2520.44, 13.1836, 0, 1681.96, 2523.56, 13.1836, 355.171, 1682.1, 2528.14, 13.2252, 2.19125, 0, 0, 0, 0, 0, 0, 2),
(61, 0, 0, 1722556800, 7500000, 15000, 0, 2, 1662.8, 2520.44, 13.1836, 0, 1662.82, 2522.91, 13.1836, 3.02905, 1663.25, 2528.12, 13.2261, 0.805274, 0, 0, 0, 0, 0, 0, 2),
(62, 0, 0, 1722038400, 7500000, 15000, 0, 1, 1662.87, 2480.73, 13.1836, 0, 1662.92, 2479.02, 13.1836, 192.624, 1662.92, 2473.89, 12.7608, 179.353, 0, 0, 0, 0, 0, 0, 2),
(63, 0, 0, 1722556800, 7500000, 15000, 0, 0, 1682.01, 2480.73, 13.1836, 0, 1682.16, 2478.89, 13.1836, 180.297, 1682.14, 2474.34, 12.7671, 179.072, 0, 0, 0, 0, 0, 0, 2),
(64, 0, 0, 1722211200, 7500000, 15000, 0, 2, 1682.07, 2461.15, 13.1836, 0, 1682.03, 2463.9, 13.1836, 359.481, 1682.15, 2468.25, 12.7614, 359.219, 0, 0, 0, 0, 0, 0, 2),
(65, 0, 0, 1733011200, 7500000, 15000, 0, 0, 1662.92, 2461.15, 13.1836, 0, 1663.01, 2463.18, 13.1836, 357.501, 1662.9, 2467.83, 12.7617, 0.485671, 0, 0, 0, 0, 0, 0, 2),
(66, 0, 0, 1737244800, 7500000, 15000, 0, 2, 1662.86, 2421.3, 13.1821, 0, 1662.95, 2419.3, 13.1821, 177.631, 1662.98, 2414.98, 12.7619, 179.264, 0, 0, 0, 0, 0, 0, 2),
(67, 0, 0, 1721433600, 7500000, 15000, 0, 2, 1681.99, 2421.3, 13.1821, 0, 1682, 2419.37, 13.1821, 181.673, 1682.08, 2415.09, 12.763, 179.224, 0, 0, 0, 0, 0, 0, 2),
(68, 0, 0, 1741910400, 7500000, 15000, 0, 0, 1682, 2401.73, 13.1821, 0, 1682.07, 2404.05, 13.1821, 357.204, 1682.04, 2408.3, 12.7613, 1.1931, 0, 0, 0, 0, 0, 0, 2),
(69, 0, 0, 1722556800, 7500000, 15000, 0, 1, 1662.86, 2401.73, 13.1821, 0, 1662.91, 2404.11, 13.1821, 359.885, 1662.99, 2408.36, 12.7659, 0.442818, 0, 0, 0, 0, 0, 0, 2),
(70, 0, 0, 1755043200, 7500000, 15000, 0, 3, 1662.9, 2362, 13.1821, 0, 1662.87, 2359.99, 13.1821, 183.105, 1662.78, 2355.59, 12.7655, 178.905, 0, 0, 0, 0, 0, 0, 2),
(71, 0, 0, 1735084800, 7500000, 15000, 0, 0, 1681.99, 2362, 13.1821, 0, 1682.09, 2360.22, 13.1821, 185.94, 1682.08, 2355.61, 12.7598, 179.355, 0, 0, 0, 0, 0, 0, 2),
(72, 0, 0, 1721865600, 3500000, 15000, 0, 1, 2350.94, -2366.05, 21.971, 0, 2348.99, -2365.36, 22.0089, 89.9464, 2345.07, -2365.23, 21.8593, 90.115, 0, 0, 0, 0, 0, 0, 1),
(73, 0, 0, 1716768000, 3500000, 15000, 0, 0, 2350.94, -2370.11, 21.971, 0, 2349.12, -2369.96, 22.0062, 90.92, 2344.79, -2370.07, 21.8575, 92.2317, 0, 0, 0, 0, 0, 0, 1),
(74, 0, 0, 0, 3500000, 15000, 0, 0, 2350.94, -2374.32, 21.971, 0, 2349.31, -2373.57, 22.0024, 97.8384, 2345.39, -2373.74, 21.8601, 92.4767, 0, 0, 0, 0, 0, 0, 1),
(75, 0, 0, 1715299200, 3500000, 15000, 0, 0, 2350.94, -2378.38, 21.971, 0, 2349.61, -2377.7, 21.9963, 92.3376, 2345.82, -2377.91, 21.86, 93.4455, 0, 0, 0, 0, 0, 0, 1),
(76, 0, 0, 0, 3500000, 15000, 0, 0, 2350.94, -2382.48, 21.971, 0, 2349.59, -2381.82, 21.9967, 95.8835, 2345.79, -2381.86, 21.8597, 91.9694, 0, 0, 0, 0, 0, 0, 1),
(77, 0, 0, 0, 3500000, 15000, 0, 0, 2350.94, -2386.65, 21.971, 0, 2349.55, -2385.97, 21.9977, 95.0359, 2345.64, -2386.06, 21.8601, 91.4807, 0, 0, 0, 0, 0, 0, 1),
(78, 0, 0, 0, 3500000, 15000, 0, 0, 2350.9, -2390.83, 21.971, 0, 2349.75, -2390.11, 21.9935, 93.7991, 2346.16, -2390.05, 21.8585, 91.5253, 0, 0, 0, 0, 0, 0, 1),
(79, 0, 0, 1718582400, 3500000, 15000, 0, 0, 2350.94, -2394.94, 21.971, 0, 2349.63, -2394.34, 21.9959, 89.8228, 2346.09, -2394.19, 21.8588, 89.9356, 0, 0, 0, 0, 0, 0, 1),
(80, 0, 0, 0, 3500000, 15000, 1, 0, 2350.95, -2398.2, 21.971, 0, 2349.71, -2397.52, 21.9943, 88.9066, 2345.84, -2397.56, 21.8585, 91.3996, 0, 0, 0, 0, 0, 0, 1),
(81, 0, 0, 0, 3500000, 15000, 0, 0, 2350.95, -2402.33, 21.971, 0, 2349.5, -2401.8, 21.9986, 78.9015, 2345.85, -2401.77, 21.859, 91.7246, 0, 0, 0, 0, 0, 0, 1),
(82, 0, 0, 0, 3500000, 15000, 0, 0, 2350.95, -2406.48, 21.971, 0, 2349.6, -2405.82, 21.9965, 93.8126, 2345.6, -2405.69, 21.8592, 90.757, 0, 0, 0, 0, 0, 0, 1),
(83, 0, 0, 0, 3500000, 15000, 0, 0, 2350.95, -2410.63, 21.971, 0, 2349.64, -2409.94, 21.9957, 94.5918, 2345.35, -2409.83, 21.8607, 90.6706, 0, 0, 0, 0, 0, 0, 1),
(84, 0, 0, 0, 3500000, 15000, 0, 0, 2350.95, -2414.78, 21.971, 0, 2349.67, -2414.17, 21.9952, 98.3895, 2345.37, -2414.26, 21.8602, 92.2698, 0, 0, 0, 0, 0, 0, 1),
(85, 0, 0, 1715644800, 3500000, 15000, 0, 0, 2350.95, -2418.93, 21.971, 0, 2349.55, -2418.14, 21.9976, 90.5888, 2345.2, -2418.2, 21.8608, 92.2371, 0, 0, 0, 0, 0, 0, 1),
(86, 0, 0, 1718496000, 3500000, 15000, 0, 0, 2369.21, -203.108, 2.1775, 0, 2369.18, -205.159, 2.1775, 183.567, 2369.35, -209.717, 1.98688, 180.65, 0, 0, 0, 0, 0, 0, 1),
(87, 0, 0, 1743984000, 7500000, 15000, 0, 0, -2051.63, -1948.19, 8.539, 0, -2057.08, -1946.41, 8.539, 67.3906, -2055.28, -1946.74, 8.12036, 68.5324, 0, 0, 0, 0, 0, 0, 2),
(88, 0, 0, 1720483200, 7500000, 15000, 0, 0, -2070.64, -1815.46, 8.539, 0, -2073.06, -1819.08, 8.539, 123.588, -2074.27, -1817.67, 8.11601, 121.568, 0, 0, 0, 0, 0, 0, 2),
(89, 0, 0, 1721433600, 7500000, 15000, 0, 0, -2223.55, -1680.97, 8.53655, 0, -2220.9, -1677.06, 8.53655, 302.621, -2219.81, -1678.49, 8.1141, 303.087, 0, 0, 0, 0, 0, 0, 2),
(90, 0, 0, 1721260800, 7500000, 15000, 0, 2, -2126.72, -1825.61, 8.539, 0, -2124.18, -1821.93, 8.539, 301.026, -2122.47, -1823, 8.11744, 302.505, 0, 0, 0, 0, 0, 0, 2),
(91, 0, 0, 1720828800, 7500000, 15000, 0, 2, -2293.48, -1631.15, 8.53655, 0, -2296.29, -1634.68, 8.53655, 122.826, -2297.33, -1633.38, 8.11477, 121.992, 0, 0, 0, 0, 0, 0, 2),
(92, 0, 0, 1722038400, 7500000, 15000, 0, 0, -2226.42, -1823.25, 8.539, 0, -2224.03, -1819.51, 8.539, 302.757, -2223, -1821.08, 8.11624, 303.884, 0, 0, 0, 0, 0, 0, 2),
(93, 0, 0, 1744243200, 3500000, 15000, 0, 0, -49.3745, 2850.34, 7.427, 0, -49.2967, 2848.15, 7.4163, 178.977, -49.1057, 2848.19, 7.2336, 90.2558, 0, 0, 0, 0, 0, 0, 1),
(94, 0, 0, 1744329600, 3500000, 15000, 0, 0, -140.127, 2850.53, 7.4338, 0, -140.091, 2849.29, 7.4017, 177.524, -139.612, 2847.73, 7.2086, 90.5271, 0, 0, 0, 0, 0, 0, 1),
(95, 0, 0, 1721433600, 3500000, 15000, 0, 0, -204.313, 2833.6, 7.4262, 0, -204.15, 2835.27, 7.4176, 359.186, -204.203, 2839.97, 7.2111, 0.8485, 0, 0, 0, 0, 0, 0, 1),
(96, 0, 0, 1721433600, 3500000, 15000, 0, 0, -234.144, 2875.44, 7.0234, 0, -233.356, 2875.94, 7.1674, 296.489, -232.711, 2877.47, 7.1359, 208.525, 0, 0, 0, 0, 0, 0, 1),
(97, 0, 0, 1712793600, 3500000, 15000, 0, 0, -140.219, 2935.15, 7.4062, 0, -140.337, 2934.36, 7.3595, 179.097, -140.241, 2932.72, 7.2361, 270.271, 0, 0, 0, 0, 0, 0, 1),
(98, 0, 0, 1720310400, 3500000, 15000, 0, 0, -49.417, 2934.97, 7.397, 0, -49.3519, 2933.68, 7.3652, 178.051, -48.8681, 2932.16, 7.2568, 268.605, 0, 0, 0, 0, 0, 0, 1),
(99, 0, 0, 1721433600, 3500000, 15000, 0, 0, -354.052, 2911.31, 7.0327, 0, -353.042, 2911.87, 7.1922, 296.587, -351.824, 2914.61, 7.2208, 208.55, 0, 0, 0, 0, 0, 0, 1),
(100, 0, 0, 1741564800, 7500000, 15000, 0, 0, 1993.63, 1287.03, 24.7572, 0, 1993.41, 1290.36, 24.7579, 0.2282, 1993.41, 1295.4, 24.4067, 359.188, 0, 0, 0, 0, 0, 0, 2),
(101, 0, 0, 1754870400, 500000, 15000, 0, 3, -244.721, -1516.56, 40.4139, 0, -244.721, -1516.56, 40.4139, 258.199, -248.284, -1515.92, 40.4063, 78.6588, 0, 0, 0, 0, 0, 0, 1),
(102, 0, 0, 1734393600, 500000, 15000, 0, 0, -279.033, -1636.7, 40.6403, 0, -279.033, -1636.7, 40.6403, 207.917, -281.135, -1633.12, 40.4086, 29.6731, 0, 0, 0, 0, 0, 0, 1),
(103, 0, 0, 1755043200, 500000, 15000, 0, 3, -242.18, -1491.45, 40.4063, 0, -242.18, -1491.45, 40.4063, 256.665, -245.331, -1490.88, 40.4063, 77.1243, 0, 0, 0, 0, 0, 0, 1),
(104, 0, 0, 1733616000, 500000, 15000, 0, 0, -291.623, -1414.59, 40.3902, 0, -291.623, -1414.59, 40.3902, 348.051, -292.336, -1418.63, 40.3883, 168.281, 0, 0, 0, 0, 0, 0, 1),
(105, 0, 0, 1721347200, 7500000, 15000, 0, 0, 3603.59, 4059.19, 7.99867, 0, 3603.89, 4061.63, 7.99867, 350.287, 3604.12, 4062.6, 8.05803, 348.695, 0, 0, 0, 0, 0, 0, 2),
(106, 0, 1, 1722211200, 7500000, 15000, 0, 2, 3794.13, 4314.49, 8.00872, 0, 3795.04, 4312.13, 8.00872, 199.885, 3952.45, 3911.03, 7.81648, 108.05, 0, 0, 0, 0, 0, 0, 2),
(107, 0, 0, 1720483200, 7500000, 15000, 0, 2, 3956.28, 3912.24, 8.00033, 0, 3954.56, 3911.86, 8.00033, 105.618, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2),
(108, 0, 0, 1743292800, 7500000, 15000, 0, 0, 3715.3, 3960.74, 7.99867, 0, 3715.28, 3963.5, 7.99867, 1.32352, 3715.28, 3963.5, 8.00488, 1.32352, 0, 0, 0, 0, 0, 0, 2),
(109, 0, 0, 1721433600, 7500000, 15000, 0, 2, 3820.57, 3923.8, 8.00033, 0, 3818.49, 3923.19, 8.00033, 102.555, 3817.42, 3922.95, 8.0599, 102.555, 0, 0, 0, 0, 0, 0, 2),
(110, 0, 0, 1721001600, 7500000, 15000, 0, 2, 3819.18, 3884.72, 8.00033, 0, 3819.62, 3882.62, 8.00033, 191.773, 3819.86, 3881.46, 8.06001, 191.773, 0, 0, 0, 0, 0, 0, 2),
(111, 0, 0, 1721347200, 7500000, 15000, 0, 0, 3744.99, 4012.93, 7.99867, 0, 3746.69, 4013.18, 7.99867, 282.689, 3748.27, 4013.05, 8.05824, 272.078, 0, 0, 0, 0, 0, 0, 2),
(112, 0, 0, 1737504000, 7500000, 15000, 0, 0, 3712.81, 4020.58, 7.99867, 0, 3710.57, 4020.67, 7.99867, 90.4823, 3709.17, 4020.63, 8.05828, 91.4057, 0, 0, 0, 0, 0, 0, 2),
(113, 0, 0, 1722470400, 7500000, 15000, 0, 0, 3983.25, 3956.93, 8.00033, 0, 3985.24, 3957.33, 8.00033, 286.558, 3986.99, 3957.84, 8.05969, 286.558, 0, 0, 0, 0, 0, 0, 2),
(114, 0, 0, 1720915200, 7500000, 15000, 0, 0, 3973.83, 4027, 8.00033, 0, 3971.23, 4026.43, 8.00033, 109.887, 3970.48, 4026.16, 8.06013, 109.887, 0, 0, 0, 0, 0, 0, 2),
(115, 0, 0, 1720656000, 7500000, 15000, 0, 0, 3827.18, 4086.27, 8.00033, 0, 3829.59, 4086.83, 8.00033, 283.889, 3830.6, 4087.08, 8.05973, 283.889, 0, 0, 0, 0, 0, 0, 2),
(116, 0, 1, 1743638400, 7500000, 15000, 0, 0, 3606.46, 4149.56, 8.00145, 0, 3608.16, 4149.25, 8.00145, 264.587, 3610.3, 4149.04, 8.06104, 264.587, 0, 0, 0, 0, 0, 0, 2),
(117, 0, 1, 1721606400, 7500000, 15000, 0, 0, 3691.59, 4270.78, 8.00145, 0, 3690.01, 4269.99, 8.00145, 121.366, 3688.08, 4268.81, 8.06095, 121.406, 0, 0, 0, 0, 0, 0, 2),
(118, 0, 1, 1721520000, 7500000, 15000, 0, 0, 3715.29, 4285.46, 8.00145, 0, 3715.91, 4283.55, 8.00145, 203.422, 3716.47, 4282.27, 8.06102, 203.422, 0, 0, 0, 0, 0, 0, 2),
(119, 0, 1, 1721088000, 7500000, 15000, 0, 0, 3874.78, 4346.71, 8.00091, 0, 3875.42, 4344.75, 8.00091, 203.084, 3876.05, 4343.27, 8.06038, 203.084, 0, 0, 0, 0, 0, 0, 2),
(120, 0, 1, 1719014400, 7500000, 15000, 0, 2, 3902.75, 4293.84, 8.07122, 0, 3904.59, 4294.09, 8.07122, 286.758, 3906.26, 4294.65, 8.13065, 286.743, 0, 0, 0, 0, 0, 0, 2),
(121, 0, 1, 1720310400, 7500000, 15000, 0, 0, 3880.44, 4293.29, 8.07122, 0, 3878.03, 4292.37, 8.07122, 112.024, 3876.33, 4291.68, 8.12882, 112.02, 0, 0, 0, 0, 0, 0, 2),
(122, 0, 1, 1718755200, 7500000, 15000, 0, 2, 3792.63, 4238.25, 8.07903, 0, 3791.67, 4240.8, 8.07903, 17.4963, 3791.37, 4241.75, 8.13474, 17.4969, 0, 0, 0, 0, 0, 0, 2),
(123, 0, 1, 1721260800, 7500000, 15000, 0, 0, 3736.18, 4226.87, 8.00145, 0, 3735.12, 4229.05, 8.00145, 24.9436, 3734.63, 4230.11, 8.06087, 24.9435, 0, 0, 0, 0, 0, 0, 2),
(124, 0, 1, 1721433600, 7500000, 15000, 0, 0, 3686.88, 4212.86, 8.00145, 0, 3685.17, 4211.59, 8.00145, 131.05, 3684, 4210.57, 8.06097, 131.05, 0, 0, 0, 0, 0, 0, 2),
(125, 0, 1, 1721692800, 7500000, 15000, 0, 0, 3662.56, 4142.3, 8.0014, 0, 3662.86, 4139.35, 8.00145, 179.078, 3662.85, 4138.3, 8.06116, 179.078, 0, 0, 0, 0, 0, 0, 2),
(126, 0, 1, 1721433600, 7500000, 15000, 0, 0, 3699.17, 4134.58, 8.00145, 0, 3701.58, 4134.51, 8.00145, 271.493, 3702.88, 4134.57, 8.06105, 272.139, 0, 0, 0, 0, 0, 0, 2),
(127, 0, 0, 1718755200, 7500000, 15000, 0, 0, 3876.85, 4100.97, 8.00091, 0, 3877.25, 4098.91, 8.00091, 193.496, 3877.62, 4097.41, 8.06023, 194.178, 0, 0, 0, 0, 0, 0, 2),
(128, 0, 0, 1746316800, 7500000, 15000, 0, 3, 460.759, 1296.6, 5.04271, 0, 460.308, 1294.26, 5.04271, 170.9, 460.105, 1293, 5.10231, 170.9, 0, 0, 0, 0, 0, 0, 2),
(129, 0, 0, 1738281600, 7500000, 15000, 0, 0, 539.184, 1321.66, 5.04271, 0, 540.065, 1319.97, 5.04271, 208.649, 540.913, 1318.42, 5.10219, 208.632, 0, 0, 0, 0, 0, 0, 2),
(130, 0, 0, 1722297600, 7500000, 15000, 0, 2, 545.992, 1332.92, 5.03491, 0, 546.768, 1331.05, 5.04271, 202.72, 547.485, 1329.34, 5.10251, 202.707, 0, 0, 0, 0, 0, 0, 2),
(131, 0, 0, 1737590400, 7500000, 15000, 1, 2, 619.259, 1381.32, 5.04271, 0, 620.525, 1379.53, 5.04271, 218.643, 621.546, 1378.26, 5.10218, 218.643, 0, 0, 0, 0, 0, 0, 2),
(132, 0, 0, 1741478400, 7500000, 15000, 0, 0, 633.608, 1399.68, 5.04271, 0, 634.454, 1397.63, 5.04271, 206.208, 635.524, 1395.45, 5.10033, 206.21, 0, 0, 0, 0, 0, 0, 2),
(133, 0, 0, 1721088000, 7500000, 15000, 0, 0, 682.016, 1425.46, 5.0412, 0, 683.326, 1423.16, 5.0412, 209.052, 683.326, 1423.16, 5.04129, 209.052, 0, 0, 0, 0, 0, 0, 2),
(134, 0, 0, 1739145600, 7500000, 15000, 0, 0, 736.998, 1454.29, 5.0412, 0, 737.577, 1452.59, 5.0412, 207.172, 738.31, 1451.16, 5.10081, 207.172, 0, 0, 0, 0, 0, 0, 2),
(135, 0, 0, 1748390400, 7500000, 15000, 0, 3, 760.926, 1465.73, 5.0412, 0, 761.804, 1463.72, 5.0412, 197.406, 762.191, 1462.49, 5.10136, 197.437, 0, 0, 0, 0, 0, 0, 2),
(136, 0, 0, 1721606400, 7500000, 15000, 0, 2, 823.619, 1484.71, 5.0412, 0, 822.59, 1482.06, 5.0412, 156.621, 822.214, 1481.19, 5.10109, 156.621, 0, 0, 0, 0, 0, 0, 2),
(137, 0, 0, 1721433600, 7500000, 15000, 0, 0, 869.182, 1429.3, 5.0412, 0, 867.172, 1429.33, 5.0412, 92.3264, 865.716, 1429.28, 5.1008, 92.3264, 0, 0, 0, 0, 0, 0, 2),
(138, 0, 0, 1721260800, 7500000, 15000, 0, 0, 864.46, 1374.75, 5.03431, 0, 862.65, 1375.83, 5.03431, 61.9814, 861.108, 1376.65, 5.04473, 61.9836, 0, 0, 0, 0, 0, 0, 2),
(139, 0, 0, 1722124800, 7500000, 15000, 0, 2, 850.324, 1341.87, 5.0412, 0, 848.287, 1342.99, 5.0412, 62.3809, 846.666, 1343.84, 5.10074, 62.3809, 0, 0, 0, 0, 0, 0, 2),
(140, 0, 0, 1722297600, 7500000, 15000, 0, 0, 859.146, 1291.09, 5.03431, 0, 857.712, 1290.56, 5.03431, 113.578, 855.732, 1289.24, 5.09901, 118.419, 0, 0, 0, 0, 0, 0, 2),
(141, 0, 0, 1721779200, 7500000, 15000, 0, 0, 869.398, 1219.33, 5.0412, 0, 867.683, 1219.69, 5.0412, 83.7527, 866.25, 1219.8, 5.10081, 83.7534, 0, 0, 0, 0, 0, 0, 2),
(142, 0, 0, 1722211200, 7500000, 15000, 0, 0, 870.951, 1182.11, 5.04422, 0, 868.94, 1183.51, 5.04422, 60.6004, 868.072, 1183.99, 5.10384, 60.6004, 0, 0, 0, 0, 0, 0, 2),
(143, 0, 0, 1721347200, 7500000, 15000, 0, 0, 839.876, 1123.95, 5.04422, 0, 838.061, 1125.36, 5.04422, 52.2827, 837.16, 1126.06, 5.10379, 52.2824, 0, 0, 0, 0, 0, 0, 2),
(144, 0, 0, 1720742400, 7500000, 15000, 0, 2, 797.101, 1060.4, 5.0442, 0, 795.57, 1062.2, 5.04422, 45.8639, 794.515, 1063.22, 5.10358, 45.8639, 0, 0, 0, 0, 0, 0, 2),
(145, 0, 0, 1749945600, 7500000, 15000, 0, 2, 755.579, 1034.33, 5.04422, 0, 754.439, 1036.46, 5.04422, 29.3933, 753.723, 1037.73, 5.10362, 29.3932, 0, 0, 0, 0, 0, 0, 2),
(146, 0, 0, 1743033600, 7500000, 15000, 0, 0, 738.532, 1018.23, 5.0369, 0, 737.96, 1020.44, 5.04422, 15.6675, 737.517, 1022.02, 5.10179, 15.6706, 0, 0, 0, 0, 0, 0, 2),
(147, 0, 0, 1721088000, 7500000, 15000, 0, 0, 675.052, 1010.7, 5.0369, 0, 675.497, 1012.91, 5.0369, 356.615, 675.604, 1014.68, 5.10177, 356.615, 0, 0, 0, 0, 0, 0, 2),
(148, 0, 0, 1721260800, 7500000, 15000, 0, 0, 639.828, 1019.9, 5.04422, 0, 640.555, 1021.83, 5.04422, 334.178, 641.282, 1023.33, 5.10362, 334.178, 0, 0, 0, 0, 0, 0, 2),
(149, 0, 0, 1718409600, 7500000, 15000, 0, 2, 594.315, 1057.53, 5.0369, 0, 596.162, 1058.61, 5.0369, 300.461, 597.874, 1059.61, 5.09832, 300.454, 0, 0, 0, 0, 0, 0, 2),
(150, 0, 0, 1722470400, 7500000, 15000, 0, 2, 561.425, 1112.54, 5.03491, 0, 563.478, 1112.89, 5.04271, 287.754, 565.382, 1113.5, 5.1023, 287.768, 0, 0, 0, 0, 0, 0, 2),
(151, 0, 0, 1722470400, 7500000, 15000, 0, 2, 550.429, 1133.09, 5.04271, 0, 552.562, 1133.1, 5.04271, 272.536, 554.638, 1133.19, 5.10231, 272.536, 0, 0, 0, 0, 0, 0, 2),
(152, 0, 0, 1721088000, 7500000, 15000, 0, 0, 654.154, 1353.03, 5.04274, 0, 654.109, 1350.92, 5.04274, 175.739, 654.003, 1349.49, 5.10237, 175.739, 0, 0, 0, 0, 0, 0, 2),
(153, 0, 0, 1721433600, 7500000, 15000, 0, 0, 696.462, 1348.98, 5.04274, 0, 696.072, 1346.7, 5.04274, 168.681, 695.726, 1344.97, 5.10221, 168.681, 0, 0, 0, 0, 0, 0, 2),
(154, 0, 0, 1737331200, 7500000, 15000, 0, 0, 749.43, 1348.42, 5.04274, 0, 749.485, 1346.27, 5.04274, 175.886, 749.337, 1344.2, 5.10232, 175.886, 0, 0, 0, 0, 0, 0, 2),
(155, 0, 0, 1722470400, 7500000, 15000, 0, 0, 792.979, 1338.11, 5.04274, 0, 794.723, 1337.44, 5.04274, 249.105, 795.929, 1336.98, 5.10236, 249.105, 0, 0, 0, 0, 0, 0, 2),
(156, 0, 0, 1721088000, 7500000, 15000, 0, 1, 814.179, 1390.03, 5.04274, 0, 816.231, 1388.19, 5.04274, 225.854, 816.969, 1387.47, 5.10236, 225.854, 0, 0, 0, 0, 0, 0, 2),
(157, 0, 0, 1721952000, 7500000, 15000, 0, 2, 768.483, 1413.87, 5.04274, 0, 767.693, 1415.7, 5.04274, 26.145, 767.07, 1416.97, 5.10235, 26.1667, 0, 0, 0, 0, 0, 0, 2),
(158, 0, 0, 1720828800, 7500000, 15000, 0, 0, 740.142, 1400.39, 5.04274, 0, 739.253, 1402.87, 5.04274, 32.184, 738.493, 1403.41, 5.1023, 27.8486, 0, 0, 0, 0, 0, 0, 2),
(159, 0, 0, 1722556800, 7500000, 15000, 0, 0, 696.513, 1384.64, 5.04274, 0, 698.323, 1385.18, 5.04274, 284.809, 700.467, 1385.75, 5.10231, 284.809, 0, 0, 0, 0, 0, 0, 2),
(160, 0, 0, 1741910400, 7500000, 15000, 0, 0, 558.39, 1284.56, 5.04064, 0, 557.324, 1286.23, 5.04064, 30.0933, 556.631, 1287.43, 5.10004, 30.0933, 0, 0, 0, 0, 0, 0, 2),
(161, 0, 0, 1721433600, 7500000, 15000, 0, 0, 607.518, 1311.9, 5.04064, 0, 607.786, 1314.47, 5.04064, 0.034264, 607.786, 1315.39, 5.10072, 0.027976, 0, 0, 0, 0, 0, 0, 2),
(162, 0, 0, 1734825600, 7500000, 15000, 0, 0, 633.709, 1309.6, 5.04064, 0, 633.948, 1311.85, 5.04064, 359.381, 633.969, 1313.78, 5.10015, 359.372, 0, 0, 0, 0, 0, 0, 2),
(163, 0, 0, 1720483200, 7500000, 15000, 0, 1, 705.353, 1307.97, 5.04064, 0, 705.524, 1309.44, 5.04064, 1.05851, 705.244, 1312.03, 5.1, 355.983, 0, 0, 0, 0, 0, 0, 2),
(164, 0, 0, 1719964800, 7500000, 15000, 0, 0, 738.652, 1308.85, 5.04064, 0, 738.958, 1310.74, 5.04064, 357.587, 739.031, 1312.46, 5.10015, 357.587, 0, 0, 0, 0, 0, 0, 2),
(165, 0, 0, 1722470400, 7500000, 15000, 0, 0, 777.506, 1302.76, 5.04064, 0, 780.614, 1302.66, 5.10013, 268.7, 780.614, 1302.66, 5.10013, 268.7, 0, 0, 0, 0, 0, 0, 2),
(166, 0, 0, 1721433600, 7500000, 15000, 0, 2, 830.498, 1236.68, 5.04064, 0, 830.079, 1234.41, 5.04064, 172.138, 829.885, 1233, 5.10025, 172.138, 0, 0, 0, 0, 0, 0, 2),
(167, 0, 0, 1733011200, 7500000, 15000, 0, 0, 770.914, 1245.95, 5.04064, 0, 770.499, 1242.57, 5.04064, 173.113, 770.499, 1242.57, 5.04074, 173.113, 0, 0, 0, 0, 0, 0, 2),
(168, 0, 0, 1721433600, 7500000, 15000, 0, 0, 746.317, 1248.27, 5.04064, 0, 745.896, 1246.65, 5.04064, 176.898, 745.924, 1245.09, 5.10027, 175.584, 0, 0, 0, 0, 0, 0, 2),
(169, 0, 0, 1721347200, 7500000, 15000, 0, 0, 693.296, 1245.42, 5.04843, 0, 693.059, 1242.67, 5.04843, 177.235, 693.018, 1241.88, 5.10606, 177.247, 0, 0, 0, 0, 0, 0, 2),
(170, 0, 0, 1721952000, 7500000, 15000, 0, 0, 627.134, 1248.75, 5.04064, 0, 626.58, 1246.8, 5.04064, 168.398, 626.254, 1245.21, 5.10027, 168.398, 0, 0, 0, 0, 0, 0, 2),
(171, 0, 0, 1738195200, 7500000, 15000, 0, 0, 592.654, 1253.46, 5.04064, 0, 591.688, 1251.48, 5.04064, 157.682, 591.046, 1249.89, 5.1, 157.995, 0, 0, 0, 0, 0, 0, 2),
(172, 0, 0, 1720569600, 7500000, 15000, 0, 0, 748.547, 1202.58, 5.03214, 0, 748.62, 1204.81, 5.03214, 353.994, 748.743, 1205.95, 5.0937, 353.967, 0, 0, 0, 0, 0, 0, 2),
(173, 0, 0, 1756339200, 7500000, 15000, 0, 0, 783.438, 1196.59, 5.03996, 0, 784.042, 1199.13, 5.03996, 344.474, 784.346, 1200.23, 5.09928, 344.474, 0, 0, 0, 0, 0, 0, 2),
(174, 0, 0, 1720137600, 7500000, 15000, 0, 2, 803.316, 1167.78, 5.03996, 0, 805.76, 1167.06, 5.03996, 256.928, 807.233, 1166.72, 5.0993, 256.827, 0, 0, 0, 0, 0, 0, 2),
(175, 0, 0, 1722211200, 7500000, 15000, 0, 0, 776.921, 1111.9, 5.03996, 0, 778.839, 1110.13, 5.03996, 232.653, 779.736, 1109.45, 5.09948, 232.653, 0, 0, 0, 0, 0, 0, 2),
(176, 0, 0, 1721606400, 7500000, 15000, 0, 2, 759.709, 1094.83, 5.03996, 0, 761.184, 1092.84, 5.03996, 218.904, 761.8, 1092.07, 5.09952, 218.904, 0, 0, 0, 0, 0, 0, 2),
(177, 0, 0, 1721433600, 7500000, 15000, 0, 0, 724.195, 1071.68, 5.03996, 0, 724.45, 1069.65, 5.03996, 193.825, 724.825, 1068.13, 5.0995, 193.824, 0, 0, 0, 0, 0, 0, 2),
(178, 0, 0, 1745020800, 7500000, 15000, 0, 0, 640.154, 1081.52, 5.03214, 0, 638.982, 1079.88, 5.03214, 146.812, 638.1, 1078.53, 5.09149, 146.812, 0, 0, 0, 0, 0, 0, 2),
(179, 0, 0, 1721433600, 7500000, 15000, 0, 2, 625.493, 1089.61, 5.03996, 0, 623.67, 1087.5, 5.03996, 134.868, 622.855, 1086.69, 5.09945, 134.868, 0, 0, 0, 0, 0, 0, 2),
(180, 0, 0, 1733356800, 7500000, 15000, 0, 0, 603.327, 1165.5, 5.03996, 0, 601.008, 1165.76, 5.03996, 80.6732, 599.359, 1166.03, 5.09941, 80.6732, 0, 0, 0, 0, 0, 0, 2),
(181, 0, 0, 1741305600, 7500000, 15000, 0, 1, 603.152, 1181.29, 5.03996, 0, 600.387, 1182.13, 5.03996, 72.8529, 599.922, 1182.28, 5.09682, 72.8527, 0, 0, 0, 0, 0, 0, 2),
(182, 0, 0, 1722384000, 7500000, 15000, 0, 0, 658.029, 1182.54, 5.03996, 0, 660.363, 1182.51, 5.03996, 269.692, 661.461, 1182.5, 5.09957, 269.692, 0, 0, 0, 0, 0, 0, 2),
(183, 0, 0, 1721606400, 7500000, 15000, 0, 2, 656.254, 1159.96, 5.03996, 0, 658.332, 1159.36, 5.03996, 261.959, 659.682, 1159.17, 5.09928, 261.959, 0, 0, 0, 0, 0, 0, 2),
(184, 0, 0, 1722384000, 7500000, 15000, 0, 0, 682.029, 1125.34, 5.03214, 0, 682.341, 1126.68, 5.03996, 351.586, 682.628, 1128.62, 5.09956, 351.593, 0, 0, 0, 0, 0, 0, 2),
(185, 0, 0, 1721606400, 7500000, 15000, 0, 2, 717.488, 1138.1, 5.03996, 0, 715.782, 1139.09, 5.03214, 60.4317, 714.28, 1139.94, 5.09742, 60.4313, 0, 0, 0, 0, 0, 0, 2),
(186, 0, 0, 1745020800, 7500000, 15000, 0, 0, 720.684, 1169.18, 5.03996, 0, 718.34, 1168.97, 5.03996, 98.6964, 716.714, 1168.72, 5.09941, 98.6964, 0, 0, 0, 0, 0, 0, 2),
(187, 0, 0, 1753574400, 7500000, 15000, 0, 0, 1974.42, -2904.98, 4.01797, 0, 1976.71, -2905.6, 4.01672, 254.204, 1977.76, -2905.9, 4.0759, 254.391, 0, 0, 0, 0, 0, 0, 2),
(188, 0, 0, 1749513600, 7500000, 15000, 0, 3, 2052.28, -2893.84, 4.02363, 0, 2054.89, -2893.98, 4.03047, 261.159, 2056.11, -2894.17, 4.08848, 261.183, 0, 0, 0, 0, 0, 0, 2),
(189, 0, 0, 1736035200, 10500000, 15000, 0, 0, 1897.31, -3067.67, 4.02545, 0, 1896.39, -3070.24, 4.02545, 164.216, 1896, -3071.62, 4.08481, 164.216, 0, 0, 0, 0, 0, 0, 3),
(190, 0, 0, 1737504000, 7500000, 15000, 0, 0, 1932.96, -3180.97, 4.01759, 0, 1934.97, -3181.17, 4.01754, 274.85, 1936.69, -3180.71, 4.08191, 273.626, 0, 0, 0, 0, 0, 0, 2),
(191, 0, 0, 1721520000, 7500000, 15000, 0, 2, 1957.4, -3263.32, 4.02836, 0, 1960.83, -3264.01, 4.02836, 259.708, 1960.83, -3264.01, 4.02603, 259.708, 0, 0, 0, 0, 0, 0, 2),
(192, 0, 0, 1720828800, 7500000, 15000, 0, 0, 1957.05, -3314.25, 4.02226, 0, 1956.64, -3316.04, 4.02226, 155.426, 1956.82, -3317.98, 4.08183, 177.254, 0, 0, 0, 0, 0, 0, 2),
(193, 0, 0, 1718841600, 7500000, 15000, 0, 1, 1873.49, -3394.76, 4.02662, 0, 1871.38, -3396.06, 4.02662, 121.681, 1870.1, -3396.85, 4.08608, 121.681, 0, 0, 0, 0, 0, 0, 2),
(194, 0, 0, 1722384000, 7500000, 15000, 0, 0, 1711.43, -3390.82, 4.02662, 0, 1713.21, -3389.55, 4.02662, 306.472, 1714.42, -3388.66, 4.08618, 306.461, 0, 0, 0, 0, 0, 0, 2),
(195, 0, 0, 1717804800, 7500000, 15000, 0, 0, 1666.68, -3338.71, 4.01738, 0, 1665.6, -3336.79, 4.01764, 31.9991, 1664.57, -3335.13, 4.07748, 32.0005, 0, 0, 0, 0, 0, 0, 2),
(196, 0, 0, 1720483200, 7500000, 15000, 0, 0, 1527.22, -3248.99, 4.01913, 0, 1525.46, -3250.89, 4.01959, 137.543, 1524.5, -3251.94, 4.07935, 137.543, 0, 0, 0, 0, 0, 0, 2),
(197, 0, 0, 1737244800, 10500000, 15000, 0, 2, 2035.86, -3200.97, 4.02836, 0, 2033.52, -3200.67, 4.02836, 83.9359, 2032.46, -3201.72, 4.08794, 104.487, 0, 0, 0, 0, 0, 0, 3),
(198, 0, 0, 1720742400, 7500000, 15000, 0, 0, 2045.08, -3306.82, 4.02226, 0, 2044.78, -3309.15, 4.02226, 178.617, 2044.75, -3310.45, 4.08188, 178.617, 0, 0, 0, 0, 0, 0, 2),
(199, 0, 0, 1722211200, 7500000, 15000, 0, 0, 1942.94, -3452.97, 4.02226, 0, 1945.7, -3452.91, 4.02226, 269.031, 1946.46, -3452.92, 4.08187, 269.031, 0, 0, 0, 0, 0, 0, 2),
(200, 0, 0, 1720742400, 7500000, 15000, 0, 0, 1336.19, -3170.95, 4.02527, 0, 1336.95, -3172.81, 4.02527, 203.908, 1338.14, -3173.78, 4.08489, 213.715, 0, 0, 0, 0, 0, 0, 2),
(201, 0, 0, 1720828800, 7500000, 15000, 0, 0, 1452.83, -3246.02, 4.02527, 0, 1450.83, -3244.25, 4.02527, 50.1537, 1450.09, -3243.64, 4.08168, 50.1523, 0, 0, 0, 0, 0, 0, 2),
(202, 0, 0, 1720656000, 7500000, 15000, 0, 0, 1505.42, -3319.83, 4.02527, 0, 1503.97, -3317.47, 4.02527, 35.9911, 1503.59, -3316.96, 4.08185, 35.9912, 0, 0, 0, 0, 0, 0, 2),
(203, 0, 0, 1722297600, 7500000, 15000, 0, 2, 1538.59, -3316.97, 4.02527, 0, 1539.7, -3318.82, 4.02527, 224.118, 1540.61, -3319.76, 4.08489, 224.118, 0, 0, 0, 0, 0, 0, 2),
(204, 0, 0, 1721692800, 10500000, 15000, 0, 2, 1631.52, -3359.95, 4.02662, 0, 1633.16, -3362.49, 4.02662, 214.516, 1633.43, -3362.88, 4.08103, 214.517, 0, 0, 0, 0, 0, 0, 3),
(205, 0, 0, 1720051200, 7500000, 15000, 0, 0, 1745.03, -3460.99, 4.02025, 0, 1742.78, -3459.33, 4.02662, 60.0648, 1742.16, -3458.98, 4.08201, 60.0646, 0, 0, 0, 0, 0, 0, 2),
(206, 0, 0, 1721433600, 7500000, 15000, 0, 0, 1788.93, -3483.25, 4.02662, 0, 1790, -3480.75, 4.02662, 332.782, 1790.64, -3479.5, 4.08599, 332.782, 0, 0, 0, 0, 0, 0, 2),
(207, 0, 0, 1722038400, 10500000, 15000, 0, 0, 1933.3, -3509.24, 4.02226, 0, 1931.03, -3508.62, 4.02226, 78.3638, 1929.68, -3508.34, 4.08161, 78.3638, 0, 0, 0, 0, 0, 0, 3),
(208, 0, 0, 1720224000, 7500000, 15000, 0, 0, 1960.12, -3512.12, 4.01508, 0, 1963.14, -3512.34, 4.07464, 257.926, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2),
(209, 0, 0, 1722124800, 10500000, 15000, 0, 2, 2093.73, -3484.23, 4.02226, 0, 2090.76, -3483.94, 4.02226, 89.0926, 2090.36, -3483.93, 4.08117, 89.0926, 0, 0, 0, 0, 0, 0, 3),
(210, 0, 0, 1722556800, 7500000, 15000, 0, 2, 2117.81, -3499.81, 4.02226, 0, 2120.55, -3500.25, 4.01508, 271.757, 2121.04, -3500.24, 4.07182, 271.757, 0, 0, 0, 0, 0, 0, 2),
(211, 0, 0, 1722470400, 7500000, 15000, 0, 2, 2261.03, -3474.93, 4.02835, 0, 2262.87, -3474.96, 4.02835, 279.139, 2264.33, -3474.73, 4.0879, 279.139, 0, 0, 0, 0, 0, 0, 2),
(212, 0, 0, 1720224000, 7500000, 15000, 0, 0, 2391.88, -3428.57, 4.02138, 0, 2389.38, -3429.31, 4.02138, 113.041, 2388.73, -3429.59, 4.081, 113.041, 0, 0, 0, 0, 0, 0, 2),
(213, 0, 0, 1720051200, 10500000, 15000, 0, 0, 2419.16, -3436, 4.02835, 0, 2418.27, -3433.9, 4.02835, 23.4852, 2417.77, -3432.81, 4.08788, 24.7385, 0, 0, 0, 0, 0, 0, 3),
(214, 0, 0, 1721347200, 10500000, 15000, 0, 2, 2397.74, -3314.58, 4.02835, 0, 2397.63, -3316.69, 4.02835, 188.438, 2397.81, -3317.94, 4.08774, 188.438, 0, 0, 0, 0, 0, 0, 3),
(215, 0, 0, 1717804800, 3500000, 15000, 0, 0, 2483.6, -3203.77, 4.02763, 0, 2480.51, -3202.51, 4.02763, 68.4427, 2480.12, -3202.09, 4.08723, 61.2309, 0, 0, 0, 0, 0, 0, 1),
(216, 0, 0, 1722038400, 3500000, 15000, 0, 2, 2479.57, -3210.89, 4.02763, 0, 2477.03, -3210.02, 4.02763, 73.6443, 2476.6, -3209.21, 4.08722, 61.0509, 0, 0, 0, 0, 0, 0, 1),
(217, 0, 0, 1722124800, 7500000, 15000, 0, 2, 2551.36, -3316.17, 4.02718, 0, 2553.59, -3315.53, 4.02718, 295.977, 2554.71, -3314.99, 4.08648, 295.977, 0, 0, 0, 0, 0, 0, 2),
(218, 0, 0, 1722470400, 7500000, 15000, 0, 0, 2568.4, -3349.79, 4.02036, 0, 2570.74, -3348.62, 4.02036, 303.547, 2571.94, -3347.83, 4.08195, 303.543, 0, 0, 0, 0, 0, 0, 2),
(219, 0, 0, 1721433600, 7500000, 15000, 0, 0, 2618.77, -3290.2, 4.02718, 0, 2617.95, -3287.37, 4.02718, 19.4964, 2616.68, -3286.86, 4.08671, 32.2313, 0, 0, 0, 0, 0, 0, 2),
(220, 0, 0, 1721347200, 10500000, 15000, 0, 0, 2677.9, -3232.72, 4.02718, 0, 2676, -3234.04, 4.02718, 126.515, 2675.04, -3234.75, 4.0865, 126.515, 0, 0, 0, 0, 0, 0, 3),
(221, 0, 0, 1720656000, 7500000, 15000, 0, 0, 2755.34, -3179.75, 4.02718, 0, 2753.76, -3180.56, 4.02718, 126.553, 2753.05, -3182.43, 4.08676, 140.696, 0, 0, 0, 0, 0, 0, 2),
(222, 0, 0, 1719792000, 7500000, 15000, 0, 0, 2775.28, -3153.58, 4.02895, 0, 2776.5, -3151.2, 4.02895, 335.236, 2776.94, -3150.25, 4.08504, 335.236, 0, 0, 0, 0, 0, 0, 2),
(223, 0, 0, 1722211200, 7500000, 15000, 0, 0, 2816.62, -3038.88, 4.02895, 0, 2817.36, -3041.91, 4.02895, 194.596, 2818.02, -3041.82, 4.08854, 205.9, 0, 0, 0, 0, 0, 0, 2),
(224, 0, 0, 1718928000, 7500000, 15000, 0, 2, 2774.91, -3017.58, 4.02895, 0, 2771.98, -3018.02, 4.02895, 104.353, 2770.89, -3019.54, 4.08855, 116.128, 0, 0, 0, 0, 0, 0, 2),
(225, 0, 0, 1719014400, 7500000, 15000, 0, 0, 2730.78, -3023.42, 4.02895, 0, 2727.48, -3023.2, 4.02895, 91.0411, 2727.09, -3023.21, 4.0891, 91.0411, 0, 0, 0, 0, 0, 0, 2),
(226, 0, 0, 1722384000, 7500000, 15000, 0, 0, 2649.25, -3035.53, 4.02895, 0, 2646.3, -3035.6, 4.02895, 95.5784, 2645.91, -3036.4, 4.08854, 105.467, 0, 0, 0, 0, 0, 0, 2),
(227, 0, 0, 1722124800, 7500000, 15000, 0, 2, 2481.11, -3040.14, 4.02763, 0, 2482.93, -3039.93, 4.02763, 278.051, 2484.98, -3039.65, 4.08713, 278.041, 0, 0, 0, 0, 0, 0, 2),
(228, 0, 0, 1721433600, 7500000, 15000, 0, 0, 2370.64, -3056.57, 4.02044, 0, 2372.99, -3056.72, 4.02044, 273.226, 2374.13, -3056.65, 4.08357, 273.234, 0, 0, 0, 0, 0, 0, 2),
(229, 0, 0, 1722556800, 7500000, 15000, 0, 0, 2284.11, -3054.46, 4.02763, 0, 2286.58, -3054.16, 4.02763, 276.509, 2287.22, -3053.06, 4.08717, 293.831, 0, 0, 0, 0, 0, 0, 2),
(230, 0, 0, 1721692800, 7500000, 15000, 0, 2, 2256.84, -3063.24, 4.02044, 0, 2253.94, -3063.39, 4.02044, 101.102, 2253.42, -3064.6, 4.07998, 111.529, 0, 0, 0, 0, 0, 0, 2),
(231, 0, 0, 1741737600, 7500000, 15000, 0, 0, 2155.49, -3093.37, 4.02836, 0, 2155.54, -3096.64, 4.02836, 183.196, 2155.54, -3096.64, 4.03419, 183.196, 0, 0, 0, 0, 0, 0, 2),
(232, 0, 0, 1721520000, 7500000, 15000, 0, 0, 2082.92, -3115.52, 4.02836, 0, 2085.71, -3115.43, 4.02836, 274.577, 2087.23, -3115.31, 4.08771, 274.577, 0, 0, 0, 0, 0, 0, 2),
(233, 0, 0, 1755043200, 7500000, 15000, 0, 3, 2057.08, -3111.01, 4.02836, 0, 2054.7, -3111.22, 4.02836, 92.69, 2053.17, -3111.29, 4.08777, 92.69, 0, 0, 0, 0, 0, 0, 2),
(234, 0, 0, 1717286400, 7500000, 15000, 0, 2, 2576.84, -3243.04, 4.02718, 0, 2578.77, -3242.27, 4.02718, 294.882, 2580.2, -3240.91, 4.08676, 301.242, 0, 0, 0, 0, 0, 0, 2),
(235, 0, 0, 1741824000, 10500000, 15000, 0, 0, 2733.3, -3115.25, 4.02895, 0, 2731.2, -3112.87, 4.02895, 42.1301, 2730.01, -3113.42, 4.08857, 60.493, 0, 0, 0, 0, 0, 0, 3),
(236, 0, 0, 1740700800, 7500000, 15000, 0, 1, 2101.24, -3368.11, 4.01508, 0, 2100.53, -3370.1, 4.02226, 166.36, 2101.62, -3372.75, 4.08238, 185.13, 0, 0, 0, 0, 0, 0, 2),
(237, 0, 0, 1721520000, 7500000, 15000, 0, 0, 2106.8, -3293.78, 4.02226, 0, 2104.07, -3293.41, 4.02226, 89.2162, 2102.33, -3293.85, 4.08179, 90.0289, 0, 0, 0, 0, 0, 0, 2),
(238, 0, 0, 1721260800, 7500000, 15000, 0, 2, 2131.85, -3160.2, 4.02836, 0, 2131.87, -3157.79, 4.02836, 2.78509, 2131.81, -3156.66, 4.08792, 2.78502, 0, 0, 0, 0, 0, 0, 2),
(239, 0, 0, 1721260800, 7500000, 15000, 0, 0, 2206.25, -3137.52, 4.02044, 0, 2209.07, -3135.51, 4.02044, 307.975, 2209.07, -3135.51, 4.01984, 308.005, 0, 0, 0, 0, 0, 0, 2),
(240, 0, 0, 1718755200, 7500000, 15000, 0, 0, 2382.45, -3183.74, 4.02763, 0, 2384.49, -3182.89, 4.02763, 298.524, 2385.83, -3182.16, 4.08695, 298.523, 0, 0, 0, 0, 0, 0, 2),
(241, 0, 0, 1716422400, 7500000, 15000, 0, 0, 2378.96, -3178.76, 4.02763, 0, 2380.54, -3178.21, 4.02763, 306.87, 2381.43, -3176.94, 4.03087, 306.017, 0, 0, 0, 0, 0, 0, 2),
(242, 0, 0, 1720828800, 7500000, 15000, 0, 0, 2506.03, -3155.46, 4.02763, 0, 2503.33, -3154.91, 4.02763, 80.4511, 2502.65, -3154.8, 4.08722, 80.4509, 0, 0, 0, 0, 0, 0, 2),
(243, 0, 0, 1720396800, 7500000, 15000, 0, 0, 2539.42, -3106.41, 4.02895, 0, 2540.32, -3104.89, 4.02895, 338.878, 2540.12, -3102.39, 4.08854, 349.537, 0, 0, 0, 0, 0, 0, 2),
(244, 0, 0, 1722211200, 7500000, 15000, 0, 0, 2345.38, -3251.52, 4.02138, 0, 2345.37, -3249.29, 4.02835, 355.323, 2345.52, -3247.52, 4.08824, 355.259, 0, 0, 0, 0, 0, 0, 2),
(245, 0, 0, 1722211200, 7500000, 15000, 0, 0, 2346.75, -3290.88, 4.02138, 0, 2347.03, -3293.23, 4.02138, 192.162, 2347.35, -3294.73, 4.08253, 192.166, 0, 0, 0, 0, 0, 0, 2),
(246, 0, 0, 1720483200, 7500000, 15000, 0, 0, 2300.05, -3406.88, 4.01791, 0, 2300.09, -3410.38, 4.01875, 187.036, 2301.13, -3410.3, 4.0804, 196.2, 0, 0, 0, 0, 0, 0, 2),
(247, 0, 0, 1722211200, 7500000, 15000, 0, 0, 1468.66, -3109.17, 4.00251, 0, 1470.54, -3106.59, 4.00108, 321.589, 1471.33, -3105.59, 4.06113, 321.588, 0, 0, 0, 0, 0, 0, 2),
(248, 0, 0, 1718150400, 7500000, 15000, 0, 0, 1529.55, -3027.59, 4.00277, 0, 1531.69, -3026.43, 4.00277, 287.748, 1532.47, -3024.96, 4.06234, 308.902, 0, 0, 0, 0, 0, 0, 2),
(249, 0, 0, 1720742400, 7500000, 15000, 0, 0, 1647.35, -2999.26, 4.00202, 0, 1646.81, -3002.24, 4.00202, 173.13, 1647.4, -3003.86, 4.06162, 179.934, 0, 0, 0, 0, 0, 0, 2),
(250, 0, 0, 1754870400, 7500000, 15000, 0, 3, 1701.55, -3014.12, 4.00202, 0, 1703.11, -3016.25, 4.00202, 221.695, 1705.44, -3016.55, 4.06154, 237.438, 0, 0, 0, 0, 0, 0, 2),
(251, 0, 0, 1750032000, 7500000, 15000, 0, 0, 1714.79, -3105.26, 4.00054, 0, 1716.41, -3104.45, 4.00014, 295.775, 1718.35, -3103.26, 4.05981, 295.769, 0, 0, 0, 0, 0, 0, 2),
(252, 0, 0, 1721001600, 7500000, 15000, 0, 0, 1677.23, -3065.33, 4.0017, 0, 1675.37, -3063.37, 4.00218, 43.6616, 1674.3, -3062.24, 4.06199, 43.6615, 0, 0, 0, 0, 0, 0, 2),
(253, 0, 0, 1721606400, 7500000, 15000, 0, 2, 1570.96, -3076.02, 4.00277, 0, 1568.21, -3077.93, 4.00277, 128.536, 1567.9, -3078.17, 4.06254, 128.536, 0, 0, 0, 0, 0, 0, 2),
(254, 0, 0, 1719273600, 3500000, 15000, 0, 0, 2416.41, -1433.62, 80.95, 0, 2416.03, -1435.17, 80.95, 172.584, 2416.44, -1436.74, 81.0095, 179.649, 0, 0, 0, 0, 0, 0, 1),
(255, 0, 0, 1720224000, 3500000, 15000, 0, 0, 2420.14, -1433.49, 80.95, 0, 2420.2, -1434.91, 80.95, 182.08, 2419.91, -1436.62, 81.0489, 180.277, 0, 0, 0, 0, 0, 0, 1),
(256, 0, 0, 0, 3500000, 15000, 0, 0, 2423.75, -1433.69, 80.95, 0, 2423.74, -1435.68, 80.95, 184.287, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1),
(257, 0, 0, 1713139200, 3500000, 15000, 0, 0, 2427.53, -1433.63, 80.95, 0, 2427.62, -1435.57, 80.95, 179.878, 2427.27, -1436.91, 81.0538, 179.934, 0, 0, 0, 0, 0, 0, 1),
(258, 0, 0, 1720656000, 3500000, 15000, 0, 0, 2315.99, -203.536, 2.1675, 0, 2315.89, -206.662, 2.1675, 181.631, 2315.9, -207.621, 2.22415, 180.69, 0, 0, 0, 0, 0, 0, 1),
(259, 0, 0, 1701648000, 3500000, 15000, 0, 1, -313.615, 1294.61, 12.4541, 0, -313.539, 1291.97, 12.4525, 183.014, -313.524, 1290.71, 12.5153, 180.47, 0, 0, 0, 0, 0, 0, 1),
(260, 0, 0, 1699228800, 3500000, 15000, 0, 1, -271.184, 1295.59, 12.2369, 0, -271.075, 1293.22, 12.2997, 180.355, -271.025, 1292.16, 12.382, 182.865, 0, 0, 0, 0, 0, 0, 1),
(261, 0, 0, 1750032000, 10500000, 15000, 0, 0, -1275.78, -2387.03, 30.9418, 0, -1277.39, -2386.13, 30.9418, 76.4584, -1279.78, -2385.47, 31.0013, 69.0734, 0, 0, 0, 0, 0, 0, 3),
(262, 0, 0, 1702684800, 3500000, 15000, 0, 0, -333.9, 1359.2, 12.2934, 0, -333.743, 1356.92, 12.351, 179.354, -333.811, 1356.05, 12.2492, 180.574, 0, 0, 0, 0, 0, 0, 1),
(263, 0, 0, 1702684800, 3500000, 15000, 0, 0, -284.459, 1216.5, 12.5762, 0, -284.551, 1214.43, 12.6347, 178.124, -284.426, 1213.18, 12.7107, 180.034, 0, 0, 0, 0, 0, 0, 1),
(264, 0, 0, 1744934400, 10500000, 15000, 0, 0, 582.703, 457.614, 12.1741, 0, 581.941, 455.809, 12.1127, 162.617, 581.538, 454.637, 12.1339, 159.899, 0, 0, 0, 0, 0, 0, 3),
(265, 0, 0, 1752537600, 10500000, 15000, 0, 0, 610.92, 601.248, 12.1478, 0, 611.576, 603.2, 12.0325, 339.703, 612.681, 606.028, 12.0595, 338.908, 0, 0, 0, 0, 0, 0, 3),
(266, 0, 0, 1740700800, 25000000, 15000, 0, 0, 2316.28, 1562.96, 11.3457, 0, 2315.59, 1563.12, 11.3457, 268.72, 2312.8, 1563.06, 10.8522, 180.306, 0, 0, 0, 0, 0, 0, 2),
(267, 0, 0, 0, 50000000, 15000, 0, 0, 224.258, -2851.23, 1.26688, 0, 224.575, -2849.66, 1.29049, 349.961, 225.048, -2847.14, 0.757944, 348.949, 0, 0, 0, 0, 0, 0, 2),
(268, 0, 0, 0, 50000000, 15000, 0, 0, 214.771, -2849.27, 1.21724, 0, 215.193, -2846.45, 1.32293, 352.404, 215.468, -2844.13, 0.775088, 350.382, 0, 0, 0, 0, 0, 0, 2),
(269, 0, 0, 0, 500000, 15000, 0, 0, -299.015, -1617.84, 40.1987, 0, -299.931, -1617.64, 40.0609, 75.0556, -300.308, -1617.52, 39.9029, 349.065, 0, 0, 0, 0, 0, 0, 1),
(270, 0, 0, 0, 500000, 15000, 0, 0, -298.148, -1613.77, 40.2851, 0, -298.148, -1613.77, 40.2851, 256.287, -299.455, -1613.11, 39.8416, 348.181, 0, 0, 0, 0, 0, 0, 1),
(271, 0, 0, 0, 500000, 15000, 0, 0, -297.282, -1609.65, 40.2573, 0, -297.282, -1609.65, 40.2573, 253.3, -298.827, -1609.43, 39.8388, 349.329, 0, 0, 0, 0, 0, 0, 1),
(272, 0, 0, 0, 500000, 15000, 0, 0, -296.423, -1605.61, 40.2662, 0, -296.423, -1605.61, 40.2662, 256.228, -297.866, -1605.28, 39.8757, 345.43, 0, 0, 0, 0, 0, 0, 1),
(273, 0, 0, 0, 500000, 15000, 0, 0, -295.565, -1601.59, 40.2649, 0, -295.565, -1601.59, 40.2649, 251.767, -297.126, -1601.21, 39.8518, 347.095, 0, 0, 0, 0, 0, 0, 1),
(274, 0, 0, 0, 500000, 15000, 0, 0, -294.727, -1597.65, 40.2128, 0, -294.727, -1597.65, 40.2128, 256.204, -296.223, -1597.37, 39.8437, 347.103, 0, 0, 0, 0, 0, 0, 1),
(275, 0, 0, 1737590400, 500000, 15000, 0, 0, -293.851, -1593.53, 40.1986, 0, -293.851, -1593.53, 40.1986, 256.165, -295.276, -1593.17, 39.8381, 347.277, 0, 0, 0, 0, 0, 0, 1),
(276, 0, 0, 0, 500000, 15000, 0, 0, -293.017, -1589.61, 40.194, 0, -293.017, -1589.61, 40.194, 256, -294.415, -1589.48, 39.8461, 347.143, 0, 0, 0, 0, 0, 0, 1),
(277, 0, 0, 0, 500000, 15000, 0, 0, -298.808, -1586.21, 40.276, 0, -298.808, -1586.21, 40.276, 73.138, -297.535, -1586.82, 39.9079, 166.321, 0, 0, 0, 0, 0, 0, 1),
(278, 0, 0, 0, 500000, 15000, 0, 0, -299.672, -1590.36, 40.2599, 0, -299.672, -1590.36, 40.2599, 76.695, -298.625, -1591.14, 39.9094, 165.977, 0, 0, 0, 0, 0, 0, 1),
(279, 0, 0, 0, 500000, 15000, 0, 0, -300.561, -1594.45, 40.6157, 0, -300.561, -1594.45, 40.6157, 72.5633, -299.245, -1594.25, 39.887, 167.902, 0, 0, 0, 0, 0, 0, 1),
(280, 0, 0, 0, 500000, 15000, 0, 0, -301.36, -1598.2, 40.6013, 0, -301.36, -1598.2, 40.6013, 74.0505, -300.118, -1598.62, 39.8722, 167.855, 0, 0, 0, 0, 0, 0, 1),
(281, 0, 0, 0, 500000, 15000, 0, 0, -302.271, -1602.5, 40.1738, 0, -302.271, -1602.5, 40.1738, 72.8288, -300.906, -1603.2, 39.8252, 167.928, 0, 0, 0, 0, 0, 0, 1),
(282, 0, 0, 0, 500000, 15000, 0, 0, -303.139, -1606.57, 40.1895, 0, -303.125, -1606.49, 40.1892, 75.6046, -301.64, -1606.64, 39.8376, 168.192, 0, 0, 0, 0, 0, 0, 1),
(283, 0, 0, 0, 500000, 15000, 0, 0, -303.975, -1610.46, 40.2047, 0, -303.989, -1610.52, 40.2047, 77.986, -301.848, -1610.8, 39.8161, 169.353, 0, 0, 0, 0, 0, 0, 1),
(284, 0, 0, 0, 500000, 15000, 0, 0, -304.822, -1614.45, 40.2626, 0, -304.822, -1614.45, 40.2626, 72.3564, -303.175, -1615.1, 39.847, 168.719, 0, 0, 0, 0, 0, 0, 1),
(285, 0, 0, 0, 500000, 15000, 0, 0, -305.691, -1618.52, 40.2737, 0, -305.691, -1618.52, 40.2737, 74.3234, -303.976, -1618.99, 39.8203, 168.018, 0, 0, 0, 0, 0, 0, 1),
(286, 0, 0, 0, 500000, 15000, 0, 0, -306.522, -1622.42, 40.2704, 0, -306.522, -1622.42, 40.2704, 73.5145, -304.698, -1622.44, 39.8573, 169.639, 0, 0, 0, 0, 0, 0, 1),
(287, 0, 0, 0, 500000, 15000, 0, 0, -307.383, -1626.47, 40.2737, 0, -307.383, -1626.47, 40.2737, 75.5558, -305.334, -1625.54, 39.9032, 167.278, 0, 0, 0, 0, 0, 0, 1),
(288, 0, 0, 0, 25000000, 25000, 0, 0, -483.835, -2054.5, 41.1155, 0, -484.757, -2053.93, 41.0792, 68.9108, -486.804, -2053.39, 41.159, 72.3022, 0, 0, 0, 0, 0, 0, 3);

-- --------------------------------------------------------

--
-- Структура таблицы `gardens`
--

CREATE TABLE `gardens` (
  `id` int(11) NOT NULL,
  `owner_id` int(11) NOT NULL,
  `owner_name` varchar(33) NOT NULL,
  `status` int(11) NOT NULL DEFAULT -1,
  `price` int(11) NOT NULL,
  `rent_price` int(11) NOT NULL,
  `rent` int(11) NOT NULL,
  `g_lock` int(11) NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `improvements` int(11) NOT NULL,
  `orend_id` int(11) NOT NULL,
  `arenda_time` int(11) NOT NULL,
  `arenda_price` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

--
-- Дамп данных таблицы `gardens`
--

INSERT INTO `gardens` (`id`, `owner_id`, `owner_name`, `status`, `price`, `rent_price`, `rent`, `g_lock`, `x`, `y`, `z`, `improvements`, `orend_id`, `arenda_time`, `arenda_price`) VALUES
(0, 0, 'None', 0, 500000, 10000, 0, 0, -2054.01, -1930.82, 7.44429, 0, 0, 0, 0),
(1, 0, 'None', 0, 500000, 10000, 0, 0, -2302.07, -1603.45, 7.56559, 0, 0, 0, 0),
(2, 0, 'None', 0, 500000, 10000, 0, 0, -2031.99, -1922.07, 7.50833, 0, 0, 0, 0),
(3, 0, 'None', 0, 500000, 10000, 9, 0, -2037.75, -1884.59, 7.54854, 0, 0, 0, 0),
(4, 0, 'None', 0, 500000, 10000, 0, 0, -2267.74, -1654.63, 7.53559, 0, 0, 0, 0),
(5, 0, 'None', 0, 500000, 10000, 0, 0, -2052.38, -1858.09, 7.52896, 0, 0, 0, 0),
(6, 0, 'None', 0, 500000, 10000, 0, 0, -2251.41, -1678.86, 7.48558, 0, 0, 0, 0),
(7, 0, 'None', 0, 500000, 10000, 0, 0, -2069.03, -1833.17, 7.51671, 0, 0, 0, 0),
(8, 0, 'None', 0, 500000, 10000, 0, 0, -2217.53, -1728.34, 7.54559, 0, 0, 0, 0),
(9, 0, 'None', 0, 500000, 10000, 12, 0, -2085.78, -1808.25, 7.51376, 0, 0, 0, 0),
(10, 0, 'None', 0, 500000, 10000, 0, 0, -2201.21, -1753.9, 7.57559, 0, 0, 0, 0),
(11, 0, 'None', 0, 500000, 10000, 0, 0, -2077.12, -1789.62, 7.51777, 0, 0, 0, 0),
(12, 0, 'None', 0, 500000, 10000, 0, 0, -2093.81, -1764.72, 7.49328, 0, 0, 0, 0),
(13, 0, 'None', 0, 500000, 10000, 0, 0, -2135.78, -1733.45, 7.55556, 0, 0, 0, 0),
(14, 0, 'None', 0, 500000, 10000, 7, 0, -2127.18, -1714.85, 7.5202, 0, 0, 0, 0),
(15, 0, 'None', 0, 500000, 10000, 0, 0, -2101.36, -1875.15, 7.54382, 0, 0, 0, 0),
(16, 0, 'None', 0, 500000, 10000, 0, 0, -2266.99, -1778.78, 7.50795, 0, 0, 0, 0),
(17, 0, 'None', 0, 500000, 10000, 6, 0, -2120.07, -1851.47, 7.52275, 0, 0, 0, 0),
(18, 0, 'None', 0, 500000, 10000, 9, 0, -2111.43, -1832.91, 7.52472, 0, 0, 0, 0),
(19, 0, 'None', 0, 500000, 10000, 0, 0, -2153.47, -1801.6, 7.53135, 0, 0, 0, 0),
(20, 0, 'None', 0, 500000, 10000, 7, 0, -2167.44, -1774.87, 7.52312, 0, 0, 0, 0),
(21, 0, 'None', 0, 500000, 10000, 0, 0, -2192.51, -1797.18, 7.51395, 0, 0, 0, 0),
(22, 0, 'None', 0, 500000, 10000, 27, 0, -2086.84, -1923.78, 7.53736, 0, 0, 0, 0),
(23, 0, 'None', 0, 500000, 10000, 26, 0, -2103.11, -1899.5, 7.53509, 0, 0, 0, 0),
(24, 0, 'None', 0, 500000, 10000, 0, 0, -2157.43, -1850.16, 7.51548, 0, 0, 0, 0),
(25, 0, 'None', 0, 500000, 10000, 2, 0, -2119.72, -1874.54, 7.56206, 0, 0, 0, 0),
(26, 0, 'None', 0, 500000, 10000, 0, 0, -2771.66, -693.402, 5.84362, 0, 0, 0, 0),
(27, 0, 'None', 0, 500000, 10000, 0, 0, -2064.39, -1959.1, 7.51968, 0, 0, 0, 0),
(28, 0, 'None', 0, 500000, 10000, 0, 0, 1967.05, -2888.38, 3.00196, 0, 0, 0, 0),
(29, 0, 'None', 0, 500000, 10000, 0, 0, 2046.37, -2878.86, 3.03461, 0, 0, 0, 511128),
(30, 0, 'None', 0, 500000, 10000, 0, 0, 2056.85, -3067.19, 3.00789, 0, 0, 0, 0),
(31, 0, 'None', 0, 500000, 10000, 14, 1, 2093.72, -3065.12, 3.00993, 0, 0, 0, 0),
(32, 0, 'None', 0, 500000, 10000, 0, 0, 2163.52, -3065.45, 3.05187, 0, 0, 0, 0),
(33, 0, 'None', 0, 500000, 10000, 0, 0, 1938.91, -3049.75, 2.96816, 0, 0, 0, 0),
(34, 0, 'None', 0, 500000, 10000, 0, 0, 2211.62, -3018.61, 2.98927, 0, 0, 0, 0),
(35, 0, 'None', 0, 500000, 10000, 8, 0, 1991.19, -3142.56, 3.06405, 0, 0, 0, 0),
(36, 0, 'None', 0, 500000, 10000, 0, 0, 2326.3, -2995.84, 3.01683, 0, 0, 0, 0),
(37, 0, 'None', 0, 500000, 10000, 0, 0, 1936.25, -3270.49, 3.02558, 0, 0, 0, 0),
(38, 0, 'None', 0, 500000, 10000, 1, 0, 2401.53, -3000.87, 3.00381, 0, 0, 0, 0),
(39, 0, 'None', 0, 500000, 10000, 13, 0, 1903.05, -3371.32, 2.99159, 0, 0, 0, 0),
(40, 0, 'None', 0, 500000, 10000, 3, 0, 2527.84, -2987.43, 3.06227, 0, 0, 0, 0),
(41, 0, 'None', 0, 500000, 10000, 0, 0, 1868.64, -3382.31, 3.04741, 0, 0, 0, 0),
(42, 0, 'None', 0, 500000, 10000, 0, 0, 1696.73, -3375.21, 3.02922, 0, 0, 0, 0),
(43, 0, 'None', 0, 500000, 10000, 0, 0, 2647.89, -2973.16, 2.94017, 0, 0, 0, 0),
(44, 0, 'None', 0, 500000, 10000, 0, 0, 2750.4, -2975.81, 3.04131, 0, 0, 0, 0),
(45, 0, 'None', 0, 500000, 10000, 0, 0, 2818.28, -3013.04, 3.00528, 0, 0, 0, 0),
(46, 0, 'None', 0, 500000, 10000, 1, 0, 1318.2, -3172.8, 2.96193, 0, 0, 0, 0),
(47, 0, 'None', 0, 500000, 10000, 11, 0, 2834.69, -3062.93, 3.03929, 0, 0, 0, 0),
(48, 0, 'None', 0, 500000, 10000, 0, 0, 1444.97, -3261.63, 3.01509, 0, 0, 0, 0),
(49, 0, 'None', 0, 500000, 10000, 0, 0, 1523.04, -3302.91, 3.04551, 0, 0, 0, 0),
(50, 0, 'None', 0, 500000, 10000, 0, 0, 2847.69, -3117.12, 2.99004, 0, 0, 0, 0),
(51, 0, 'None', 0, 500000, 10000, 12, 0, 2783.08, -3183.28, 3.00905, 0, 0, 0, 0),
(52, 0, 'None', 0, 500000, 10000, 0, 0, 1596.4, -3381.41, 3.04634, 0, 0, 0, 0),
(53, 0, 'None', 0, 500000, 10000, 5, 0, 2702.82, -3235.73, 3.02553, 0, 0, 0, 0),
(54, 0, 'None', 0, 500000, 10000, 1, 0, 1743.74, -3481.52, 2.98143, 0, 0, 0, 0),
(55, 0, 'None', 0, 500000, 10000, 0, 0, 1781.18, -3505.34, 2.96096, 0, 0, 0, 0),
(56, 0, 'None', 0, 500000, 10000, 0, 0, 1938.53, -3543.02, 3.08382, 0, 0, 0, 0),
(57, 0, 'None', 0, 500000, 10000, 0, 0, 2642.59, -3296.3, 3.00144, 0, 0, 0, 0),
(58, 0, 'None', 0, 500000, 10000, 0, 0, 1953.57, -3533.08, 3.06763, 0, 0, 0, 0),
(59, 0, 'None', 0, 500000, 10000, 0, 0, 2036.93, -3502.21, 3.05296, 0, 0, 0, 0),
(60, 0, 'None', 0, 500000, 10000, 1, 0, 2115.66, -3524.56, 3.02, 0, 0, 0, 0),
(61, 0, 'None', 0, 500000, 10000, 0, 0, 2540.08, -3349.67, 3.05611, 0, 0, 0, 0),
(62, 0, 'None', 0, 500000, 10000, 0, 0, 2247.13, -3487.3, 2.96348, 0, 0, 0, 0),
(63, 0, 'None', 0, 500000, 10000, 12, 0, 2512.73, -3219.68, 3.01633, 0, 0, 0, 0),
(64, 0, 'None', 0, 500000, 10000, 0, 0, 2458.3, -3241.03, 3.02922, 0, 0, 0, 0),
(65, 0, 'None', 0, 500000, 10000, 0, 0, 2386.27, -3264.03, 3.01123, 0, 0, 0, 0),
(66, 0, 'None', 0, 500000, 10000, 0, 0, 1522.98, -3420.31, 3.00864, 0, 0, 0, 0),
(67, 0, 'None', 0, 500000, 10000, 0, 0, 2458.2, -3379.86, 2.99965, 0, 0, 0, 0),
(68, 0, 'None', 0, 500000, 10000, 3, 0, 2291.77, -3390.08, 2.81811, 0, 0, 0, 0),
(69, 0, 'None', 0, 500000, 10000, 0, 0, 2327.55, -3305.6, 3.02854, 0, 0, 0, 0),
(70, 0, 'None', 0, 500000, 10000, 0, 0, 2323.02, -3229.01, 3.05181, 0, 0, 0, 0),
(71, 0, 'None', 0, 500000, 10000, 1, 0, 2245.74, -3147.94, 3.02928, 0, 0, 0, 0),
(72, 0, 'None', 0, 500000, 10000, 0, 0, 2095.27, -3208.35, 2.98618, 0, 0, 0, 0),
(73, 0, 'None', 0, 500000, 10000, 0, 0, 2412.96, -3144.15, 3.01784, 0, 0, 0, 0),
(74, 0, 'None', 0, 500000, 10000, 1, 0, 2497.67, -3135.35, 3.05037, 0, 0, 0, 0),
(75, 0, 'None', 0, 500000, 10000, 0, 0, 2534.92, -3121.5, 2.96101, 0, 0, 0, 0),
(76, 0, 'None', 0, 500000, 10000, 0, 0, 2574.27, -3213.7, 3.02308, 0, 0, 0, 0),
(77, 0, 'None', 0, 500000, 10000, 1, 0, 2719.55, -3066.88, 3.02617, 0, 0, 0, 0),
(78, 0, 'None', 0, 500000, 10000, 0, 0, 2124.79, -3361.98, 2.98429, 0, 0, 0, 0),
(79, 0, 'None', 0, 500000, 10000, 0, 0, 2093.59, -3262.18, 3.035, 0, 0, 0, 0),
(80, 0, 'None', 0, 500000, 10000, 13, 0, 1980.2, -3407.81, 2.92991, 0, 0, 0, 0),
(81, 0, 'None', 0, 500000, 10000, 0, 0, 2014.57, -3336.27, 3.03022, 0, 0, 0, 0),
(82, 0, 'None', 0, 500000, 10000, 0, 0, 2048.32, -3227.37, 3.06516, 0, 0, 0, 0),
(83, 0, 'None', 0, 500000, 10000, 0, 0, 1455.81, -3001.3, 2.9862, 0, 0, 0, 0),
(84, 0, 'None', 0, 500000, 10000, 11, 0, 1549.22, -2951.11, 3.01545, 0, 0, 0, 0),
(85, 0, 'None', 0, 500000, 10000, 14, 0, 1640.79, -2975.79, 3.03748, 0, 0, 0, 0),
(86, 0, 'None', 0, 500000, 10000, 0, 0, 1708.35, -2996.27, 2.99732, 0, 0, 0, 0),
(87, 0, 'None', 0, 500000, 10000, 0, 1, 1761.25, -3161.32, 3.00765, 0, 0, 0, 0),
(88, 0, 'None', 0, 500000, 10000, 0, 0, 1694.52, -3077.14, 2.99803, 0, 0, 0, 0),
(89, 0, 'None', 0, 500000, 10000, 0, 0, 1582.81, -3057.7, 2.91458, 0, 0, 0, 0),
(90, 0, 'None', 0, 500000, 10000, 0, 0, 484.272, 1325.39, 4.0613, 0, 0, 0, 0),
(91, 0, 'None', 0, 500000, 10000, 27, 0, 498.437, 1330.73, 4.07583, 0, 0, 0, 0),
(92, 0, 'None', 0, 500000, 10000, 1, 0, 561.054, 1370.82, 4.04327, 0, 0, 0, 0),
(93, 0, 'None', 0, 500000, 10000, 0, 0, 607.842, 1403.89, 4.07931, 0, 0, 0, 0),
(94, 0, 'None', 0, 500000, 10000, 0, 0, 659.582, 1424.59, 4.01469, 0, 0, 0, 0),
(95, 0, 'None', 0, 500000, 10000, 0, 0, 666.254, 1447.96, 4.01174, 0, 0, 0, 0),
(96, 0, 'None', 0, 500000, 10000, 7, 0, 707.507, 1471.33, 4.02694, 0, 0, 0, 0),
(97, 0, 'None', 0, 500000, 10000, 0, 0, 792.608, 1499.64, 4.00371, 0, 0, 0, 0),
(98, 0, 'None', 0, 500000, 10000, 0, 0, 852.46, 1483.67, 4.12816, 0, 0, 0, 0),
(99, 0, 'None', 0, 500000, 10000, 0, 0, 880.564, 1460.15, 3.98254, 0, 0, 0, 0),
(100, 0, 'None', 0, 500000, 10000, 0, 0, 897.823, 1399.66, 4.00212, 0, 0, 0, 0),
(101, 0, 'None', 0, 500000, 10000, 6, 0, 877.782, 1342.77, 4.05398, 0, 0, 0, 0),
(102, 0, 'None', 0, 500000, 10000, 0, 0, 879.959, 1312.6, 4.03233, 0, 0, 0, 0),
(103, 0, 'None', 0, 500000, 10000, 0, 0, 888.14, 1223.24, 4.05135, 0, 0, 0, 0),
(104, 0, 'None', 0, 500000, 10000, 1, 1, 869.397, 1155.8, 4.0604, 0, 0, 0, 0),
(105, 0, 'None', 0, 500000, 10000, 0, 0, 844.189, 1141.48, 4.07366, 0, 0, 0, 0),
(106, 0, 'None', 0, 500000, 10000, 0, 0, 818.037, 1096.07, 4.04366, 0, 0, 0, 0),
(107, 0, 'None', 0, 500000, 10000, 0, 0, 793.919, 1034.27, 4.08568, 0, 0, 0, 0),
(108, 0, 'None', 0, 500000, 10000, 0, 0, 748.089, 1006.41, 4.00944, 0, 0, 0, 0),
(109, 0, 'None', 0, 500000, 10000, 13, 0, 656.815, 1021.37, 4.0546, 0, 0, 0, 0),
(110, 0, 'None', 0, 500000, 10000, 0, 0, 586.86, 1021.38, 4.08729, 0, 0, 0, 0),
(111, 0, 'None', 0, 500000, 10000, 0, 0, 580.851, 1081.89, 4.04431, 0, 0, 0, 0),
(112, 0, 'None', 0, 500000, 10000, 0, 0, 559.09, 1120.08, 4.03073, 0, 0, 0, 0),
(113, 0, 'None', 0, 500000, 10000, 13, 0, 558.081, 1178.58, 4.04295, 0, 0, 0, 0),
(114, 0, 'None', 0, 500000, 10000, 0, 0, 571.877, 1283.73, 4.01846, 0, 0, 0, 0),
(115, 0, 'None', 0, 500000, 10000, 0, 0, 617.102, 1286.66, 4.05664, 0, 0, 0, 0),
(116, 0, 'None', 0, 500000, 10000, 0, 0, 630.082, 1283.71, 3.96685, 0, 0, 0, 0),
(117, 0, 'None', 0, 500000, 10000, 4, 0, 699.626, 1258.98, 4.07153, 0, 0, 0, 0),
(118, 0, 'None', 0, 500000, 10000, 0, 0, 712.321, 1258.1, 4.05201, 0, 0, 0, 0),
(119, 0, 'None', 0, 500000, 10000, 0, 0, 758.513, 1238.72, 4.02415, 0, 0, 0, 0),
(120, 0, 'None', 0, 500000, 10000, 0, 0, 831.873, 1252.26, 3.82301, 0, 0, 0, 0),
(121, 0, 'None', 0, 500000, 10000, 0, 0, 772.539, 1296.3, 4.04384, 0, 0, 0, 0),
(122, 0, 'None', 0, 500000, 10000, 14, 0, 748.994, 1285.75, 4.04404, 0, 0, 0, 0),
(123, 0, 'None', 0, 500000, 10000, 0, 0, 704.407, 1293.77, 4.07523, 0, 0, 0, 0),
(124, 0, 'None', 0, 500000, 10000, 0, 0, 674.094, 1291.35, 4.19964, 0, 0, 0, 0),
(125, 0, 'None', 0, 500000, 10000, 14, 0, 621.112, 1317.99, 4.09796, 0, 0, 0, 0),
(126, 0, 'None', 0, 500000, 10000, 0, 0, 640.142, 1212.34, 4.04906, 0, 0, 0, 0),
(127, 0, 'None', 0, 500000, 10000, 1, 0, 627.465, 1213.39, 3.99484, 0, 0, 0, 0),
(128, 0, 'None', 0, 500000, 10000, 0, 0, 622.725, 1154.62, 3.95317, 0, 0, 0, 0),
(129, 0, 'None', 0, 500000, 10000, 11, 1, 621.019, 1129.16, 4.00429, 0, 0, 0, 0),
(130, 0, 'None', 0, 500000, 10000, 0, 0, 667.826, 1074.03, 4.08501, 0, 0, 0, 0),
(131, 0, 'None', 0, 500000, 10000, 1, 0, 692.135, 1058.35, 4.05559, 0, 0, 0, 0),
(132, 0, 'None', 0, 500000, 10000, 0, 0, 776.312, 1098.49, 4.03447, 0, 0, 0, 0),
(133, 0, 'None', 0, 500000, 10000, 1, 0, 766.867, 1146.59, 4.04588, 0, 0, 0, 0),
(134, 0, 'None', 0, 500000, 10000, 0, 0, 773.125, 1157.93, 4.04526, 0, 0, 0, 0),
(135, 0, 'None', 0, 500000, 10000, 0, 0, 818.863, 1196.22, 4.05567, 0, 0, 0, 0),
(136, 0, 'None', 0, 500000, 10000, 0, 0, 707.654, 1211.84, 4.02224, 0, 0, 0, 0),
(137, 0, 'None', 0, 500000, 10000, 0, 0, 749.882, 1165.61, 4.10204, 0, 0, 0, 0),
(138, 0, 'None', 0, 500000, 10000, 14, 0, 741.268, 1134.52, 4.0555, 0, 0, 0, 0),
(139, 0, 'None', 0, 500000, 10000, 0, 0, 689.266, 1105.08, 4.00264, 0, 0, 0, 0),
(140, 0, 'None', 0, 500000, 10000, 0, 0, 644.007, 1146.7, 4.03491, 0, 0, 0, 0),
(141, 0, 'None', 0, 500000, 10000, 7, 0, 663.668, 1367.33, 4.04491, 0, 0, 0, 0),
(142, 0, 'None', 0, 500000, 10000, 1, 0, 722.654, 1383.65, 4.05522, 0, 0, 0, 0),
(143, 0, 'None', 0, 500000, 10000, 0, 0, 734.716, 1385.15, 3.93925, 0, 0, 0, 0),
(144, 0, 'None', 0, 500000, 10000, 14, 0, 769.771, 1400.74, 4.07626, 0, 0, 0, 0),
(145, 0, 'None', 0, 500000, 10000, 0, 0, 830.33, 1431.71, 4.13385, 0, 0, 0, 0),
(146, 0, 'None', 0, 500000, 10000, 0, 0, 788.662, 1371.5, 4.00663, 0, 0, 0, 0),
(147, 0, 'None', 0, 500000, 10000, 0, 0, 734.048, 1353.25, 4.06136, 0, 0, 0, 0),
(148, 0, 'None', 0, 500000, 10000, 25, 0, 760.694, 1369.09, 3.89123, 0, 0, 0, 0),
(149, 0, 'None', 0, 500000, 10000, 0, 0, 497.213, 2720.37, 9.64437, 0, 0, 0, 0),
(150, 0, 'None', 0, 500000, 10000, 1, 0, 476.74, 2720.39, 9.63813, 0, 0, 0, 0),
(151, 0, 'None', 0, 500000, 10000, 0, 0, 456.859, 2720.35, 9.69, 0, 0, 0, 0),
(152, 0, 'None', 0, 500000, 10000, 0, 0, 434.915, 2720.32, 9.70399, 0, 0, 0, 0),
(153, 0, 'None', 0, 500000, 10000, 0, 0, 415.346, 2720.16, 9.73217, 0, 0, 0, 0),
(154, 0, 'None', 0, 500000, 10000, 1, 0, 393.017, 2720.45, 9.72351, 0, 0, 0, 0),
(155, 0, 'None', 0, 500000, 10000, 0, 0, 372.055, 2720.53, 9.69806, 0, 0, 0, 0),
(156, 0, 'None', 0, 500000, 10000, 0, 0, 352.603, 2720.43, 9.71016, 0, 0, 0, 0),
(157, 0, 'None', 0, 500000, 10000, 1, 0, 330.824, 2720.45, 9.74513, 0, 0, 0, 0),
(158, 0, 'None', 0, 500000, 10000, 0, 0, 310.477, 2720.32, 9.81464, 0, 0, 0, 0),
(159, 0, 'None', 0, 500000, 10000, 5, 0, 289.431, 2720.3, 9.75314, 0, 0, 0, 0),
(160, 0, 'None', 0, 500000, 10000, 1, 0, -33.2834, 2829.97, 6.33236, 0, 0, 0, 0),
(161, 0, 'None', 0, 500000, 10000, 0, 0, -76.0087, 2830.4, 6.36974, 0, 0, 0, 0),
(162, 0, 'None', 0, 500000, 10000, 0, 0, -90.5409, 2830.24, 6.32928, 0, 0, 0, 0),
(163, 0, 'None', 0, 500000, 10000, 0, 0, -132.947, 2811.5, 6.43878, 0, 0, 0, 0),
(164, 0, 'None', 0, 500000, 10000, 0, 0, -165.587, 2830.27, 6.40104, 0, 0, 0, 0),
(165, 0, 'None', 0, 500000, 10000, 0, 0, -179.994, 2830.38, 6.31497, 0, 0, 0, 0),
(166, 0, 'None', 0, 500000, 10000, 1, 0, -213.283, 2830.16, 6.35147, 0, 0, 0, 0),
(167, 0, 'None', 0, 500000, 10000, 0, 0, -239.151, 2812.71, 6.46019, 0, 0, 0, 0),
(168, 0, 'None', 0, 500000, 10000, 1, 0, -267.892, 2830.27, 6.4633, 0, 0, 0, 0),
(169, 0, 'None', 0, 500000, 10000, 15, 0, -29.2367, 2883.03, 6.42885, 0, 0, 0, 0),
(170, 0, 'None', 0, 500000, 10000, 0, 0, -76.1953, 2860.09, 6.4349, 0, 0, 0, 0),
(171, 0, 'None', 0, 500000, 10000, 9, 0, -88.9265, 2882.97, 6.37661, 0, 0, 0, 0),
(172, 0, 'None', 0, 500000, 10000, 0, 0, -136.358, 2861.95, 6.45995, 0, 0, 0, 0),
(173, 0, 'None', 0, 500000, 10000, 8, 0, -149.12, 2882.78, 6.47495, 0, 0, 0, 0),
(174, 0, 'None', 0, 500000, 10000, 12, 0, -200.268, 2876.87, 6.3776, 0, 0, 0, 0),
(175, 0, 'None', 0, 500000, 10000, 0, 0, -200.615, 2918.11, 6.36006, 0, 0, 0, 0),
(176, 0, 'None', 0, 500000, 10000, 5, 0, -165.52, 2918.07, 6.37645, 0, 0, 0, 0),
(177, 0, 'None', 0, 500000, 10000, 4, 0, -132.327, 2898.6, 6.41868, 0, 0, 0, 0),
(178, 0, 'None', 0, 500000, 10000, 0, 0, -90.4153, 2915.14, 6.44531, 0, 0, 0, 0),
(179, 0, 'None', 0, 500000, 10000, 0, 0, -75.852, 2918, 6.40866, 0, 0, 0, 0),
(180, 0, 'None', 0, 500000, 10000, 0, 0, -30.7942, 2915.31, 6.38758, 0, 0, 0, 0),
(181, 0, 'None', 0, 500000, 10000, 3, 0, -30.0034, 2967.65, 6.4188, 0, 0, 0, 0),
(182, 0, 'None', 0, 500000, 10000, 0, 0, -60.2318, 2967.92, 6.42306, 0, 0, 0, 0),
(183, 0, 'None', 0, 500000, 10000, 0, 0, -89.6227, 2967.49, 6.37405, 0, 0, 0, 0),
(184, 0, 'None', 0, 500000, 10000, 5, 1, -136.304, 2967.84, 6.41281, 0, 0, 0, 0),
(185, 0, 'None', 0, 500000, 10000, 0, 0, -149.205, 2967.74, 6.33518, 0, 0, 0, 0),
(186, 0, 'None', 0, 500000, 10000, 1, 0, -190.058, 2967.67, 6.42906, 0, 0, 0, 0),
(187, 0, 'None', 0, 500000, 10000, 0, 0, -225.54, 2967.39, 6.42732, 0, 0, 0, 0),
(188, 0, 'None', 0, 500000, 10000, 1, 0, -249.384, 2869.94, 5.9877, 0, 0, 0, 0),
(189, 0, 'None', 0, 500000, 10000, 3, 0, -282.133, 2907.75, 5.98693, 0, 0, 0, 0),
(190, 0, 'None', 0, 500000, 10000, 0, 0, -271.606, 2926.09, 5.90402, 0, 0, 0, 0),
(191, 0, 'None', 0, 500000, 10000, 30, 0, -326.536, 2951.1, 5.97168, 0, 0, 0, 0),
(192, 0, 'None', 0, 500000, 10000, 1, 0, -328.857, 2916.17, 5.91223, 0, 0, 0, 0),
(193, 0, 'None', 0, 500000, 10000, 8, 0, -315.777, 2889.08, 5.96162, 0, 0, 0, 0),
(194, 0, 'None', 0, 500000, 10000, 1, 0, -344.852, 2838.2, 5.9416, 0, 0, 0, 0),
(195, 0, 'None', 0, 500000, 10000, 0, 0, -341.141, 2874.8, 5.99001, 0, 0, 0, 0),
(196, 0, 'None', 0, 500000, 10000, 0, 0, -348.698, 2887.91, 5.97959, 0, 0, 0, 0),
(197, 0, 'None', 0, 500000, 10000, 1, 0, -365.881, 2916.34, 5.97182, 0, 0, 0, 0),
(198, 0, 'None', -1, 500000, 10000, 1, 0, -16.766, 2800.78, 6.31072, 0, 0, 0, 0),
(199, 0, 'None', -1, 500000, 10000, 0, 0, -4.47884, 2800.8, 6.22223, 0, 0, 0, 0),
(200, 0, 'None', -1, 500000, 10000, 14, 0, -16.4386, 2808.47, 6.30667, 0, 0, 0, 0),
(201, 0, 'None', -1, 500000, 10000, 13, 0, -4.47884, 2808.54, 6.20499, 0, 0, 0, 0),
(202, 0, 'None', -1, 500000, 10000, 14, 0, -16.413, 2816.44, 6.24155, 0, 0, 0, 0),
(203, 0, 'None', -1, 500000, 10000, 1, 0, -4.43092, 2816.51, 6.10061, 0, 0, 0, 0),
(204, 0, 'None', -1, 500000, 10000, 1, 0, -7.49615, 2826.62, 6.19747, 0, 0, 0, 0),
(205, 0, 'None', -1, 500000, 10000, 0, 0, 374.47, 2667.25, 11.029, 0, 0, 0, 0),
(206, 0, 'None', -1, 500000, 10000, 0, 0, 388.608, 2667.25, 11.029, 0, 0, 0, 0),
(207, 0, 'None', -1, 500000, 10000, 1, 0, 402.523, 2667.25, 11.029, 0, 0, 0, 0),
(208, 0, 'None', -1, 500000, 10000, 0, 0, 414.78, 2667.25, 11.029, 0, 0, 0, 0),
(209, 0, 'None', -1, 500000, 10000, 0, 0, 428.18, 2667.25, 11.029, 0, 0, 0, 0),
(210, 0, 'None', -1, 500000, 10000, 9, 0, 374.47, 2657.55, 11.029, 0, 0, 0, 0),
(211, 0, 'None', -1, 500000, 10000, 0, 0, 388.608, 2657.55, 11.029, 0, 0, 0, 0),
(212, 0, 'None', -1, 500000, 10000, 0, 0, 402.523, 2657.55, 11.029, 0, 0, 0, 0),
(213, 0, 'None', -1, 500000, 10000, 2, 0, 414.78, 2657.55, 11.029, 0, 0, 0, 0),
(214, 0, 'None', -1, 500000, 10000, 0, 0, 428.18, 2657.55, 11.029, 0, 0, 0, 0),
(215, 0, 'None', 0, 500000, 10000, 0, 0, 3577.93, 4091.81, 7.02589, 0, 0, 0, 0),
(216, 0, 'None', 0, 500000, 10000, 0, 0, 3582.31, 4132.28, 6.88781, 0, 0, 0, 0),
(217, 0, 'None', 0, 500000, 10000, 0, 0, 3598.51, 4187.16, 7.00177, 0, 0, 0, 0),
(218, 0, 'None', 0, 500000, 10000, 8, 0, 3613.35, 4235.41, 7.59938, 0, 0, 0, 0),
(219, 0, 'None', 0, 500000, 10000, 9, 0, 3650.61, 4271.95, 7.00577, 0, 0, 0, 0),
(220, 0, 'None', 0, 500000, 10000, 0, 0, 3688.68, 4298.08, 6.92525, 0, 0, 0, 0),
(221, 0, 'None', 0, 500000, 10000, 3, 0, 3724.83, 4313.34, 7.0054, 0, 0, 0, 0),
(222, 0, 'None', 0, 500000, 10000, 0, 0, 3763.98, 4328.38, 6.97943, 0, 0, 0, 0),
(223, 0, 'None', 0, 500000, 10000, 0, 0, 3810.3, 4346.13, 7.01837, 0, 0, 0, 0),
(224, 0, 'None', 0, 500000, 10000, 0, 0, 3829.56, 4333.5, 7.07622, 0, 0, 0, 0),
(225, 0, 'None', 0, 500000, 10000, 1, 0, 3881.19, 4372.93, 6.931, 0, 0, 0, 0),
(226, 0, 'None', 0, 500000, 10000, 0, 0, 3902.9, 4283.44, 7.07251, 0, 0, 0, 0),
(227, 0, 'None', 0, 500000, 10000, 12, 0, 3888.13, 4284.38, 7.01764, 0, 0, 0, 0),
(228, 0, 'None', 0, 500000, 10000, 13, 0, 3822.69, 4277.9, 7.05993, 0, 0, 0, 0),
(229, 0, 'None', 0, 500000, 10000, 0, 0, 3853.91, 4235.17, 7.05552, 0, 0, 0, 0),
(230, 0, 'None', 0, 500000, 10000, 0, 0, 3880.35, 4202.67, 6.97645, 0, 0, 0, 0),
(231, 0, 'None', 0, 500000, 10000, 0, 0, 3856.45, 4154.37, 6.88291, 0, 0, 0, 0),
(232, 0, 'None', 0, 500000, 10000, 0, 0, 3905.69, 4116.34, 7.00504, 0, 0, 0, 0),
(233, 0, 'None', 0, 500000, 10000, 1, 0, 3917.07, 4077.16, 7.00391, 0, 0, 0, 0),
(234, 0, 'None', 0, 500000, 10000, 9, 1, 3922.97, 4120.53, 6.9455, 0, 0, 0, 0),
(235, 0, 'None', 0, 500000, 10000, 2, 0, 3906.89, 4167.64, 7.01575, 0, 0, 0, 0),
(236, 0, 'None', 0, 500000, 10000, 0, 0, 3894.47, 4201.77, 6.96665, 0, 0, 0, 0),
(237, 0, 'None', 0, 500000, 10000, 0, 0, 3934.53, 4261.17, 6.97127, 0, 0, 0, 0),
(238, 0, 'None', 0, 500000, 10000, 4, 0, 3789.19, 4169.73, 7.06026, 0, 0, 0, 0),
(239, 0, 'None', 0, 500000, 10000, 0, 0, 3804.51, 4217.37, 6.96765, 0, 0, 0, 0),
(240, 0, 'None', 0, 500000, 10000, 0, 0, 3756.46, 4242.71, 7.10396, 0, 0, 0, 0),
(241, 0, 'None', 0, 500000, 10000, 0, 0, 3740.11, 4199.16, 7.07607, 0, 0, 0, 0),
(242, 0, 'None', 0, 500000, 10000, 0, 0, 3707.84, 4182.82, 6.9743, 0, 0, 0, 0),
(243, 0, 'None', 0, 500000, 10000, 0, 0, 3660.16, 4165.96, 6.99583, 0, 0, 0, 0),
(244, 0, 'None', 0, 500000, 10000, 0, 0, 3708.82, 4169.68, 6.9992, 0, 0, 0, 0),
(245, 0, 'None', 0, 500000, 10000, 0, 0, 3749.47, 4172.07, 6.95847, 0, 0, 0, 0),
(246, 0, 'None', 0, 500000, 10000, 0, 0, 3788.93, 4100.56, 6.963, 0, 0, 0, 0),
(247, 0, 'None', 0, 500000, 10000, 0, 0, 3767.38, 4100.03, 7.00395, 0, 0, 0, 0),
(248, 0, 'None', 0, 500000, 10000, 0, 0, 3725.49, 4099.88, 6.98478, 0, 0, 0, 0),
(249, 0, 'None', 0, 500000, 10000, 0, 0, 3671.63, 4098.6, 7.02461, 0, 0, 0, 0),
(250, 0, 'None', 0, 500000, 10000, 0, 0, 3660.64, 4048.46, 6.94286, 0, 0, 0, 0),
(251, 0, 'None', 0, 500000, 10000, 26, 1, 3720.68, 4048.35, 6.99967, 0, 0, 0, 0),
(252, 0, 'None', 0, 500000, 10000, 0, 0, 3763.48, 4049.2, 7.0279, 0, 0, 0, 0),
(253, 0, 'None', 0, 500000, 10000, 4, 0, 3783, 4056.87, 7.01958, 0, 0, 0, 0),
(254, 0, 'None', 0, 500000, 10000, 0, 0, 3820.57, 4061.84, 7.01075, 0, 0, 0, 0),
(255, 0, 'None', 0, 500000, 10000, 0, 0, 3846.83, 3992.25, 6.89184, 0, 0, 0, 0),
(256, 0, 'None', 0, 500000, 10000, 0, 0, 3799.16, 3977.23, 6.99399, 0, 0, 0, 0),
(257, 0, 'None', 0, 500000, 10000, 0, 0, 3881.97, 3948.16, 7.0114, 0, 0, 0, 0),
(258, 0, 'None', 0, 500000, 10000, 11, 0, 3893.93, 3910.55, 7.00934, 0, 0, 0, 0),
(259, 0, 'None', 0, 500000, 10000, 5, 0, 3875.01, 3863.53, 6.99844, 0, 0, 0, 0),
(260, 0, 'None', 0, 500000, 10000, 0, 0, 3823.11, 3850.1, 7.00284, 0, 0, 0, 0),
(261, 0, 'None', 0, 500000, 10000, 0, 0, 3840.59, 3896.16, 6.97258, 0, 0, 0, 0),
(262, 0, 'None', 0, 500000, 10000, 0, 0, 3838.45, 3935.46, 7.02464, 0, 0, 0, 0),
(263, 0, 'None', 0, 500000, 10000, 0, 0, 3986.75, 3875.83, 7.0068, 0, 0, 0, 0),
(264, 0, 'None', 0, 500000, 10000, 0, 0, 3987.64, 3911.06, 6.98816, 0, 0, 0, 0),
(265, 0, 'None', 0, 500000, 10000, 5, 1, 3992.56, 3975.02, 7.02597, 0, 0, 0, 0),
(266, 0, 'None', 0, 500000, 10000, 4, 0, 3972.96, 3994.73, 7.03651, 0, 0, 0, 0),
(267, 0, 'None', 0, 500000, 10000, 10, 0, 3916.07, 4015.78, 6.99946, 0, 0, 0, 0),
(268, 0, 'None', 0, 500000, 10000, 0, 0, 3944.07, 3968.84, 6.96449, 0, 0, 0, 0),
(269, 0, 'None', 0, 500000, 10000, 0, 0, 3768.09, 3950.41, 6.93015, 0, 0, 0, 0),
(270, 0, 'None', 0, 500000, 10000, 5, 0, 3697.61, 3979.3, 7.00168, 0, 0, 0, 0),
(271, 0, 'None', 0, 500000, 10000, 0, 0, 3659.6, 3979.88, 7.00976, 0, 0, 0, 0),
(272, 0, 'None', 0, 500000, 10000, 0, 0, 1931.8, 1776.41, 14.4478, 0, 0, 0, 0),
(273, 0, 'None', 0, 500000, 10000, 0, 0, 1942.5, 1830.95, 14.4957, 0, 0, 0, 0),
(274, 0, 'None', 0, 500000, 10000, 0, 0, 1981.26, 1787.44, 14.5324, 0, 0, 0, 0),
(275, 0, 'None', 0, 500000, 10000, 13, 0, 1985.5, 1752.21, 14.6735, 0, 0, 0, 0),
(276, 0, 'None', 0, 500000, 10000, 0, 0, 2011.04, 1865.63, 14.53, 0, 0, 0, 0),
(277, 0, 'None', -1, 500000, 10000, 9, 0, 374.47, 2647.54, 11.0052, 0, 0, 0, 0),
(278, 0, 'None', -1, 500000, 10000, 12, 0, 388.608, 2647.54, 10.987, 0, 0, 0, 0),
(279, 0, 'None', -1, 500000, 10000, 0, 0, 402.523, 2647.54, 10.9477, 0, 0, 0, 0),
(280, 0, 'None', -1, 500000, 10000, 0, 0, 414.78, 2647.54, 10.8541, 0, 0, 0, 0),
(281, 0, 'None', -1, 500000, 10000, 0, 0, 428.18, 2647.54, 10.8668, 0, 0, 0, 0),
(282, 0, 'None', -1, 500000, 10000, 8, 0, 374.47, 2637.9, 10.9728, 0, 0, 0, 0),
(283, 0, 'None', -1, 500000, 10000, 0, 0, 388.608, 2638, 11.0077, 0, 0, 0, 0),
(284, 0, 'None', -1, 500000, 10000, 0, 0, 402.523, 2638, 10.9275, 0, 0, 0, 0),
(285, 0, 'None', -1, 500000, 10000, 0, 0, 414.78, 2638.41, 10.9014, 0, 0, 0, 0),
(286, 0, 'None', -1, 500000, 10000, 0, 0, 428.198, 2638.51, 10.9821, 0, 0, 0, 0),
(287, 0, 'None', -1, 500000, 10000, 0, 0, 1980.84, 1270.65, 24.7888, 0, 0, 0, 0),
(288, 0, 'None', -1, 500000, 10000, 0, 0, 1550.31, -3252.3, 3.02527, 0, 0, 0, 0),
(289, 0, 'None', -1, 500000, 10000, 1, 0, 2757.39, -292.469, 2.6159, 0, 0, 0, 0),
(290, 0, 'None', -1, 500000, 10000, 0, 0, 2763.46, -266.209, 2.5903, 0, 0, 0, 0),
(291, 0, 'None', -1, 500000, 10000, 0, 0, 2745.62, -253.071, 2.61003, 0, 0, 0, 0),
(292, 0, 'None', -1, 500000, 10000, 0, 0, 2722.07, -247.415, 2.58945, 0, 0, 0, 0),
(293, 0, 'None', -1, 500000, 10000, 1, 0, 2691.45, -247.721, 3.16366, 0, 0, 0, 0),
(294, 0, 'None', -1, 500000, 10000, 0, 0, 2631.96, -247.727, 2.97921, 0, 0, 0, 0),
(295, 0, 'None', -1, 500000, 10000, 7, 0, 2587.4, -247.102, 3.09197, 0, 0, 0, 0),
(296, 0, 'None', -1, 500000, 10000, 1, 0, 2524.58, -191.343, 2.10959, 0, 0, 0, 0),
(297, 0, 'None', -1, 500000, 10000, 0, 0, 2429.74, -231.669, 1.05262, 0, 0, 0, 0),
(298, 0, 'None', 0, 500000, 10000, 13, 0, -2316.76, -1580.4, 7.55861, 0, 0, 0, 0),
(299, 0, 'None', 0, 500000, 10000, 1, 0, -2308.66, -1623.94, 7.54583, 0, 0, 0, 0),
(300, 0, 'None', 0, 500000, 10000, 3, 0, -2314.54, -1699.94, 7.56749, 0, 0, 0, 0),
(301, 0, 'None', 0, 500000, 10000, 0, 0, -2299.54, -1725.96, 7.53512, 0, 0, 0, 0),
(302, 0, 'None', 0, 500000, 10000, 10, 0, -2282.73, -1750.91, 7.52897, 0, 0, 0, 0),
(303, 0, 'None', 0, 500000, 10000, 1, 0, -2250.31, -1656.94, 7.52051, 0, 0, 0, 0),
(304, 0, 'None', 0, 500000, 10000, 0, 0, -2208.23, -1688.28, 7.3095, 0, 0, 0, 0),
(305, 0, 'None', 0, 500000, 10000, 0, 0, -2214.57, -1706.65, 7.55854, 0, 0, 0, 0),
(306, 0, 'None', 0, 500000, 10000, 0, 0, -2200.16, -1731.79, 7.50552, 0, 0, 0, 0),
(307, 0, 'None', 0, 500000, 10000, 0, 0, -2212.11, -1830.3, 7.55192, 0, 0, 0, 0),
(308, 0, 'None', 0, 500000, 10000, 0, 0, -2219.35, -1847.93, 7.53747, 0, 0, 0, 0),
(309, 0, 'None', 0, 500000, 10000, 0, 0, -2201.85, -1872.33, 7.52439, 0, 0, 0, 0),
(310, 0, 'None', 0, 500000, 10000, 5, 0, -2258.44, -1698.68, 7.42236, 0, 0, 0, 0),
(311, 0, 'None', -1, 500000, 10000, 0, 0, 1650.88, -3261.52, 3.02662, 0, 0, 0, 0),
(312, 0, 'None', -1, 500000, 10000, 1, 1, 2391.67, -3466.2, 3.00074, 0, 0, 0, 0),
(313, 0, 'None', -1, 500000, 10000, 0, 0, 576.052, 1041.11, 4.01414, 0, 0, 0, 0),
(314, 0, 'None', -1, 500000, 10000, 6, 0, 360.86, 2667.22, 11.0321, 0, 0, 0, 0),
(315, 0, 'None', -1, 500000, 10000, 0, 0, 360.877, 2657.65, 11.0374, 0, 0, 0, 0),
(316, 0, 'None', -1, 500000, 10000, 0, 0, 360.86, 2647.56, 11.0374, 0, 0, 0, 0),
(317, 0, 'None', -1, 500000, 10000, 8, 0, 360.872, 2637.97, 11.0274, 0, 0, 0, 0),
(318, 0, 'None', -1, 500000, 10000, 0, 0, 345.049, 2667.21, 10.9674, 0, 0, 0, 0),
(319, 0, 'None', -1, 500000, 10000, 0, 0, 345.015, 2657.66, 11.0374, 0, 0, 0, 0),
(320, 0, 'None', -1, 500000, 10000, 0, 0, 344.973, 2647.56, 11.0392, 0, 0, 0, 0),
(321, 0, 'None', -1, 500000, 10000, 10, 0, 344.893, 2637.97, 11.0439, 0, 0, 0, 0),
(322, 0, 'None', -1, 500000, 10000, 0, 0, 329.235, 2667.22, 11.0374, 0, 0, 0, 0),
(323, 0, 'None', -1, 500000, 10000, 1, 0, 329.245, 2657.6, 11.0474, 0, 0, 0, 0),
(324, 0, 'None', -1, 500000, 10000, 1, 0, 312.753, 2667.22, 11.0374, 0, 0, 0, 0),
(325, 0, 'None', -1, 500000, 10000, 1, 0, 329.105, 2647.57, 11.0484, 0, 0, 0, 0),
(326, 0, 'None', -1, 500000, 10000, 1, 0, 329.048, 2637.97, 11.0472, 0, 0, 0, 0),
(327, 0, 'None', -1, 500000, 10000, 0, 0, -207.813, -1449.55, 39.4379, 0, 0, 0, 0),
(328, 0, 'None', -1, 500000, 10000, 0, 0, -210.377, -1486.35, 39.5302, 0, 0, 0, 0),
(329, 0, 'None', -1, 500000, 10000, 0, 0, -215.408, -1501.41, 39.4951, 0, 0, 0, 0),
(330, 0, 'None', -1, 500000, 10000, 0, 0, -222.855, -1528.47, 39.4858, 0, 0, 0, 0),
(331, 0, 'None', -1, 500000, 10000, 0, 0, -236.813, -1576.99, 39.4768, 0, 0, 0, 0),
(332, 0, 'None', -1, 500000, 10000, 26, 0, -210.896, -1618.99, 39.7334, 0, 0, 0, 0),
(333, 0, 'None', -1, 500000, 10000, 0, 0, -242.868, -1642.54, 40.0265, 0, 0, 0, 0),
(334, 0, 'None', -1, 500000, 10000, 0, 0, -171.898, -1630.54, 39.9175, 0, 0, 0, 0),
(335, 0, 'None', -1, 500000, 10000, 0, 0, -183.821, -1677.98, 39.7734, 0, 0, 0, 0),
(336, 0, 'None', -1, 500000, 10000, 0, 0, -197.564, -1709.67, 40.1459, 0, 0, 0, 0),
(337, 0, 'None', -1, 500000, 10000, 0, 0, -231.003, -1690.76, 39.8347, 0, 0, 0, 0),
(338, 0, 'None', -1, 500000, 10000, 0, 0, -213.835, -1764.82, 39.8962, 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Структура таблицы `hardware_bans`
--

CREATE TABLE `hardware_bans` (
  `id` int(11) NOT NULL,
  `acc_id` int(11) NOT NULL,
  `hardware_id` varchar(250) NOT NULL,
  `type` int(11) NOT NULL,
  `reason` varchar(32) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `hotels`
--

CREATE TABLE `hotels` (
  `id` int(11) NOT NULL,
  `hotel_id` int(11) NOT NULL,
  `owner_id` int(11) NOT NULL,
  `rent_time` int(11) NOT NULL,
  `status` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `houses`
--

CREATE TABLE `houses` (
  `id` int(11) NOT NULL,
  `owner_id` int(11) NOT NULL,
  `name` varchar(20) NOT NULL,
  `city` int(11) NOT NULL DEFAULT -1,
  `zone` int(11) NOT NULL DEFAULT -1,
  `miami` int(11) NOT NULL DEFAULT 0,
  `improvements` int(11) NOT NULL,
  `rent_time` int(11) NOT NULL,
  `price` int(11) NOT NULL,
  `rent_price` int(11) NOT NULL,
  `type` int(11) NOT NULL,
  `entrance` int(11) NOT NULL DEFAULT -1,
  `lock` int(11) NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `exit_x` float NOT NULL,
  `exit_y` float NOT NULL,
  `exit_z` float NOT NULL,
  `exit_angle` float NOT NULL,
  `car_x` float NOT NULL,
  `car_y` float NOT NULL,
  `car_z` float NOT NULL,
  `car_angle` float NOT NULL,
  `store_x` float NOT NULL,
  `store_y` float NOT NULL,
  `store_z` float NOT NULL,
  `eviction` int(11) NOT NULL,
  `store_metall` int(11) NOT NULL,
  `store_drugs` int(11) NOT NULL,
  `store_weapon` int(11) NOT NULL,
  `store_ammo` int(11) NOT NULL,
  `store_skin` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

--
-- Дамп данных таблицы `houses`
--

INSERT INTO `houses` (`id`, `owner_id`, `name`, `city`, `zone`, `miami`, `improvements`, `rent_time`, `price`, `rent_price`, `type`, `entrance`, `lock`, `x`, `y`, `z`, `exit_x`, `exit_y`, `exit_z`, `exit_angle`, `car_x`, `car_y`, `car_z`, `car_angle`, `store_x`, `store_y`, `store_z`, `eviction`, `store_metall`, `store_drugs`, `store_weapon`, `store_ammo`, `store_skin`) VALUES
(0, 0, '', 15, 0, 0, 0, 2505600, 5000000, 500000, 1, -1, 0, 1081.55, 1718.89, 4224.33, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(1, 0, '', 15, 0, 0, 0, 1754697600, 9000000, 900000, 4, -1, 0, -2061.09, -1970.28, 8.8204, -2063.22, -1969.17, 8.539, 69.7076, -2069.43, -1977.53, 8.539, 68.3186, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(2, 0, '', 15, 0, 0, 0, 1742342400, 9000000, 900000, 4, -1, 0, -2048.68, -1939.03, 8.90634, -2050.1, -1938.3, 8.539, 68.3071, -2059.39, -1948.51, 8.539, 71.5463, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(3, 0, '', 15, 0, 0, 0, 1721433600, 9000000, 900000, 4, -1, 0, -2039.07, -1913.28, 9.08302, -2039.52, -1914.69, 9.07821, 158.955, -2049.01, -1920.37, 8.539, 69.2746, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(4, 0, '', 15, 0, 0, 0, 1721433600, 9000000, 900000, 4, -1, 0, -2023.7, -1888.53, 9.4561, -2024.96, -1889.04, 9.4586, 71.037, -2035.75, -1893.91, 8.539, 70.4495, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(5, 0, '', 15, 0, 0, 0, 1722556800, 9000000, 900000, 4, -1, 0, -2042.95, -1858.64, 9.04696, -2044.27, -1859.62, 8.539, 121.198, -2039.19, -1870.73, 8.539, 123.537, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(6, 0, '', 15, 0, 0, 0, 1721606400, 9000000, 900000, 4, -1, 0, -2076.46, -1807.78, 8.90634, -2077.77, -1808.58, 8.539, 122.953, -2074.76, -1822.47, 8.539, 124.077, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(7, 0, '', 15, 0, 0, 0, 1722556800, 9000000, 900000, 4, -1, 0, -2091.98, -1785.1, 9.08302, -2091.13, -1786.45, 9.07821, 213.68, -2089.39, -1795.85, 8.54669, 126.623, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(8, 0, '', 15, 0, 0, 0, 1721433600, 9000000, 900000, 4, -1, 0, -2103.44, -1758.32, 9.45609, -2104.06, -1759.84, 9.45855, 124.508, -2106.11, -1771.07, 8.539, 123.96, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(9, 0, '', 15, 0, 0, 0, 1721174400, 9000000, 900000, 4, -1, 0, -2121.58, -1733.1, 8.81259, -2120.54, -1735.2, 8.81259, 213.288, -2123.36, -1745.96, 8.539, 123.725, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(10, 0, '', 15, 0, 0, 0, 1722556800, 9000000, 900000, 4, -1, 0, -2141.34, -1711.35, 8.8204, -2142.54, -1712.29, 8.53655, 124.888, -2141.05, -1721.57, 8.53655, 126.051, 1604.47, -410.96, 1051, 0, 0, 0, 0, 0, 0),
(11, 0, '', 15, 0, 0, 0, 1721347200, 9000000, 900000, 4, -1, 0, -2236.23, -1660.52, 8.8204, -2234.42, -1659.09, 8.53655, 305.072, -2235.93, -1649.16, 8.53655, 303.22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(12, 0, '', 15, 0, 0, 0, 1743292800, 9000000, 900000, 4, -1, 0, -2217.76, -1688.6, 8.90634, -2216.91, -1687.77, 8.53655, 306.694, -2219.33, -1674.38, 8.54436, 304.646, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(13, 0, '', 15, 0, 0, 0, 1719705600, 9000000, 900000, 4, -1, 0, -2202.2, -1711.33, 9.08302, -2203.83, -1709.33, 9.07821, 32.8769, -2203.53, -1699.94, 8.53655, 305.664, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(14, 0, '', 15, 0, 0, 0, 1719792000, 9000000, 900000, 4, -1, 0, -2190.65, -1738.04, 9.45609, -2189.32, -1735.86, 9.15421, 303.04, -2154.46, -1782.37, 9.04696, 127.806, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(15, 0, '', 15, 0, 0, 0, 1720828800, 9000000, 900000, 4, -1, 0, -2154.46, -1782.37, 9.04696, -2152.6, -1781.39, 8.539, 298.719, -2156.07, -1768.71, 8.539, 302.664, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(16, 0, '', 15, 0, 0, 0, 1720828800, 9000000, 900000, 4, -1, 0, -2139.38, -1805.2, 8.8204, -2138.52, -1804.5, 8.8204, 303.396, -2138.86, -1793.5, 8.539, 305.03, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(17, 0, '', 15, 0, 0, 0, 1721606400, 9000000, 900000, 4, -1, 0, -2120.88, -1833.31, 8.90634, -2119.36, -1832.37, 8.539, 301.689, -2121.65, -1818.57, 8.539, 304.967, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(18, 0, '', 15, 0, 0, 0, 1720828800, 9000000, 900000, 4, -1, 0, -2105.36, -1855.99, 9.08302, -2106.51, -1854.13, 9.07821, 34.1776, -2106.46, -1844.18, 8.539, 302.108, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(19, 0, '', 15, 0, 0, 0, 1735257600, 9000000, 900000, 4, -1, 0, -2093.88, -1882.75, 9.45609, -2092.98, -1881.09, 9.45847, 301.324, -2090.75, -1869.37, 8.539, 304.81, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(20, 0, '', 15, 0, 0, 0, 1737504000, 9000000, 900000, 4, -1, 0, -2097.48, -1917.74, 8.81259, -2096.87, -1918.65, 8.81259, 211.855, -2096.87, -1928.88, 8.539, 127.54, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(21, 0, '', 15, 0, 0, 0, 1737504000, 9000000, 900000, 4, -1, 0, -2118.85, -1889.22, 9.08302, -2122.31, -1891.81, 8.539, 122.515, 694.822, 589.799, 12.0021, 66.9641, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(22, 0, '', 15, 0, 0, 0, 1737763200, 9000000, 900000, 4, -1, 1, -2129.35, -1868.21, 9.45611, -2130.14, -1869.9, 9.4587, 123.443, -2131.58, -1880.45, 8.539, 124.775, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(23, 0, '', 15, 0, 0, 0, 1721433600, 9000000, 900000, 4, -1, 0, -2147.54, -1843.05, 8.81259, -2146.3, -1844.16, 8.81259, 214.143, -2150.52, -1857, 8.539, 126.577, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(24, 0, '', 15, 0, 0, 0, 1722211200, 9000000, 900000, 4, -1, 0, -2163.93, -1819.4, 9.04696, -2162.9, -1820.6, 8.539, 211.009, -2165.43, -1831.17, 8.54669, 121.172, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(25, 0, '', 15, 0, 0, 0, 1722038400, 9000000, 900000, 4, -1, 0, -2183.93, -1796.28, 8.8204, -2185.56, -1797.4, 8.539, 124.607, -2699.22, 2723.86, 37.4336, 316.446, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(26, 0, '', 15, 0, 0, 0, 1746921600, 9000000, 900000, 4, -1, 0, -2214.63, -1750.37, 9.08302, -2213.43, -1751.68, 9.07821, 213.532, -2213, -1761.59, 8.53655, 122.793, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(27, 0, '', 15, 0, 0, 0, 1721692800, 9000000, 900000, 4, -1, 0, -2226.32, -1723.75, 9.4561, -2226.77, -1724.98, 9.45816, 123.107, -2231.86, -1738.75, 8.54436, 120.326, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(28, 0, '', 15, 0, 0, 0, 1737590400, 9000000, 900000, 4, -1, 1, -2244.37, -1698.36, 8.81259, -2243.83, -1698.66, 8.81259, 207.438, -2239.68, -1703.73, 8.53655, 125.344, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(29, 0, '', 15, 0, 0, 0, 1721433600, 9000000, 900000, 4, -1, 0, -2265.79, -1674.31, 9.04696, -2267.28, -1675.37, 8.53655, 122.547, -2264.34, -1687.23, 8.54436, 126.099, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(30, 0, '', 15, 0, 0, 0, 1735257600, 9000000, 900000, 4, -1, 0, -2280.76, -1651.63, 8.8204, -2282.56, -1652.45, 8.53655, 124.756, -2280.57, -1662.83, 8.54436, 122.277, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(31, 0, '', 15, 0, 0, 0, 1722211200, 9000000, 900000, 4, -1, 0, -2299.31, -1623.46, 8.90634, -2300.51, -1624.38, 8.53655, 126.965, -2297.6, -1637.62, 8.53655, 123.076, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(32, 0, '', 15, 0, 0, 0, 1721779200, 9000000, 900000, 4, -1, 0, -2314.82, -1600.73, 9.08302, -2313.83, -1601.81, 9.07821, 213.971, -2314.26, -1612.65, 8.53655, 125.308, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(33, 0, '', 15, 0, 0, 0, 1741478400, 9000000, 900000, 4, -1, 0, -2326.39, -1574.06, 9.45617, -2326.58, -1575.4, 9.45888, 126.248, -2328.86, -1586.4, 8.53655, 125.308, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(34, 0, '', 15, 0, 0, 0, 1722556800, 9000000, 900000, 4, -1, 0, -2304.24, -1706.57, 9.08302, -2305.09, -1704.95, 9.07821, 34.4552, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(35, 0, '', 15, 0, 0, 0, 1738368000, 9000000, 900000, 4, -1, 0, -2292.13, -1733.69, 9.45609, -2291.86, -1731.98, 9.45952, 303.325, -2288.15, -1720.58, 8.53655, 305.009, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(36, 0, '', 15, 0, 0, 0, 1737331200, 9000000, 900000, 4, -1, 0, -2274.1, -1759.09, 8.81259, -2274.62, -1758.26, 8.81259, 34.6119, -2275.09, -1748.25, 8.53655, 304.657, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(37, 0, '', 15, 0, 0, 0, 1745366400, 9000000, 900000, 4, -1, 0, -2252.62, -1782.5, 9.04696, -2251.45, -1781.55, 8.53655, 297.909, -2253.3, -1769.73, 8.54436, 306.709, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(38, 0, '', 15, 0, 0, 0, 1722124800, 9000000, 900000, 4, -1, 0, -2220.63, -1830.88, 8.90634, -2219.04, -1829.68, 8.539, 302.115, -2223.54, -1816.85, 8.539, 302.73, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(39, 0, '', 15, 0, 0, 0, 1734393600, 9000000, 900000, 4, -1, 0, -2206.32, -1852.89, 9.08302, -2207.3, -1851.99, 9.07821, 33.2727, -2206.58, -1841.62, 8.539, 303.474, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(40, 0, '', 15, 0, 0, 0, 1738195200, 9000000, 900000, 4, -1, 0, -2194.4, -1880, 9.4561, -2195.22, -1878.95, 9.45967, 217.607, -2193.07, -1868.82, 8.54669, 305.276, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(41, 0, '', 15, 0, 0, 0, 1754697600, 5000000, 500000, 1, -1, 0, 491.455, 2729.44, 10.5885, 489.48, 2729.23, 10.5954, 88.7524, 488.513, 2730.81, 10.5954, 176.333, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(42, 0, '', 15, 0, 0, 0, 1750032000, 5000000, 500000, 1, -1, 0, 463.094, 2688.71, 11.9947, 464.647, 2688.68, 12.002, 272.532, 465.919, 2687.52, 12.002, 0.490986, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(43, 0, '', 15, 0, 0, 0, 1722556800, 5000000, 500000, 1, -1, 0, 476.127, 2733.84, 10.5885, 476.015, 2735.35, 10.7616, 357.562, 467.82, 2731.27, 10.5885, 177.353, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(44, 0, '', 15, 0, 0, 0, 1721433600, 5000000, 500000, 1, -1, 0, 435.822, 2684.74, 11.9947, 435.913, 2683.22, 11.9947, 184.12, 445.41, 2686.92, 12.002, 352.004, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(45, 0, '', 15, 0, 0, 0, 1721433600, 5000000, 500000, 1, -1, 0, 456.182, 2733.58, 10.5885, 455.955, 2734.99, 10.5885, 0.737013, 447.183, 2727.82, 10.5885, 181.908, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(46, 0, '', 15, 0, 0, 0, 1722384000, 5000000, 500000, 1, -1, 1, 420.922, 2688.92, 11.9947, 422.427, 2688.89, 12.002, 269.357, 423.8, 2687.74, 12.002, 355.765, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(47, 0, '', 15, 0, 0, 0, 1721347200, 5000000, 500000, 1, -1, 0, 429.437, 2728.82, 10.5885, 427.644, 2728.8, 10.5885, 86.3712, 426.22, 2729.35, 10.5885, 182.701, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(48, 0, '', 15, 0, 0, 0, 1721606400, 5000000, 500000, 1, -1, 1, 400.462, 2689.69, 11.9947, 401.819, 2689.84, 12.002, 270.548, 403.515, 2688.51, 12.002, 354.453, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(49, 0, '', 15, 0, 0, 0, 1741824000, 5000000, 500000, 1, -1, 0, 415.015, 2733.61, 10.5954, 414.727, 2734.74, 10.5885, 3.02375, 406.88, 2729.45, 10.5885, 180.821, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(50, 0, '', 15, 0, 0, 0, 1720224000, 5000000, 500000, 1, -1, 0, 373.333, 2684.63, 11.9947, 373.113, 2683.27, 11.9947, 180.548, 383.242, 2687.87, 11.9947, 357.854, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(51, 0, '', 15, 0, 0, 0, 1721433600, 5000000, 500000, 1, -1, 0, 394.026, 2733.83, 10.5885, 393.836, 2735.45, 10.5885, 2.43783, 383.885, 2729.63, 10.5885, 175.654, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(52, 0, '', 15, 0, 0, 0, 1720656000, 5000000, 500000, 1, -1, 0, 352.327, 2684.86, 11.9947, 352.358, 2683.34, 11.9947, 177.846, 360.941, 2688.46, 12.002, 0.624009, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(53, 0, '', 15, 0, 0, 0, 1734652800, 5000000, 500000, 1, -1, 0, 366.884, 2728.69, 10.5885, 1888.42, -3095.8, 4.50493, 75.9141, 362.948, 2729.07, 10.5885, 178.035, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(54, 0, '', 15, 0, 0, 0, 1720915200, 5000000, 500000, 1, -1, 1, 337.914, 2689.56, 12.002, 339.762, 2689.84, 11.9947, 271.531, 341.773, 2689.52, 11.9947, 354.86, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(55, 0, '', 15, 0, 0, 0, 1719705600, 5000000, 500000, 1, -1, 0, 346.432, 2729.5, 10.5885, 3820.07, 3881.66, 8.00033, 12.1073, 343.091, 2728.92, 10.5885, 172.289, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(56, 0, '', 15, 0, 0, 0, 1720396800, 5000000, 500000, 1, -1, 0, 311.226, 2684.89, 11.9947, 311.074, 2683.07, 11.9947, 182.609, 319.99, 2688.11, 11.9947, 354.671, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(57, 0, '', 15, 0, 0, 0, 1721433600, 5000000, 500000, 1, -1, 0, 331.393, 2733.73, 10.5885, 330.792, 2735.12, 10.5885, 1.62558, 321.502, 2730.91, 10.5954, 178.847, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(58, 0, '', 15, 0, 0, 0, 1720396800, 5000000, 500000, 1, -1, 0, 291.211, 2684.63, 11.9947, 290.582, 2682.89, 11.9947, 177.712, 299.809, 2687.31, 11.9947, 359.849, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(59, 0, '', 15, 0, 0, 0, 1721433600, 5000000, 500000, 1, -1, 0, 304.259, 2729.77, 10.5885, 302.413, 2729.62, 10.5954, 92.1719, 301.375, 2730.99, 10.5954, 176.863, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(60, 0, '', 15, 0, 0, 0, 1721433600, 5000000, 500000, 1, -1, 0, 275.898, 2689.14, 11.9947, 278.201, 2689.24, 12.002, 278.315, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(61, 0, '', 15, 0, 0, 0, 1722124800, 5000000, 500000, 1, -1, 0, 283.557, 2728.75, 10.5885, 281.696, 2728.75, 10.5954, 89.3756, 280.103, 2729.7, 10.5954, 175.691, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(62, 0, '', 11, 0, 0, 0, 1734998400, 5000000, 500000, 1, -1, 0, 1995, 1746.31, 15.6921, 1994.99, 1746.08, 15.6921, 87.5388, 1972.35, 1744.63, 15.4499, 176.632, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(63, 0, '', 11, 0, 0, 0, 1721865600, 5000000, 500000, 1, -1, 1, 1943.52, 1752.96, 15.3569, 1943.52, 1753.14, 15.3568, 269.712, 1955.52, 1752.2, 15.4499, 182.585, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(64, 0, '', 15, 0, 0, 0, 1722038400, 5000000, 500000, 1, -1, 0, 1977.74, 1719.81, 15.6912, 1977.52, 1719.81, 15.6927, 176.424, 1970.3, 1717.41, 15.7789, 184.948, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(65, 0, '', 15, 0, 0, 0, 1720310400, 5000000, 500000, 1, -1, 0, 1955.59, 1704.92, 16.1656, 1955.53, 1705.14, 16.1656, 281.204, 1961.24, 1701.33, 15.7168, 202.015, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(66, 0, '', 15, 0, 0, 0, 1720828800, 5000000, 500000, 1, -1, 0, 1984.83, 1699.57, 16.1287, 1985.02, 1699.61, 16.1287, 190.694, 1974.28, 1694.44, 15.7318, 195.646, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(67, 0, '', 15, 0, 0, 0, 1720224000, 5000000, 500000, 1, -1, 0, 1963.98, 1678.22, 15.7563, 1963.79, 1678.16, 15.7563, 16.0431, 1968.21, 1681.71, 15.7055, 203.187, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(68, 0, '', 15, 0, 0, 0, 1719273600, 5000000, 500000, 1, -1, 0, 1990.37, 1688.7, 16.0556, 1990.3, 1688.93, 16.0556, 283.549, 1980.09, 1673.38, 15.7967, 196.422, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(69, 0, '', 15, 0, 0, 0, 1720483200, 5000000, 500000, 1, -1, 0, 1966.7, 1663.95, 15.6948, 1966.64, 1664.16, 15.695, 287.915, 1973.99, 1662.86, 15.6937, 209.916, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(70, 0, '', 15, 0, 0, 0, 1720310400, 5000000, 500000, 1, -1, 0, 1972.94, 1636.24, 15.6617, 1972.94, 1636.24, 15.6617, 196.819, 1980.1, 1643.13, 15.6683, 199.994, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(71, 0, '', 15, 0, 0, 0, 1719446400, 5000000, 500000, 1, -1, 0, 1997.96, 1639.45, 15.7662, 1998.14, 1639.51, 15.7662, 198.199, 1994.06, 1636.39, 15.6264, 196.403, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(72, 0, '', 15, 0, 0, 0, 1720915200, 5000000, 500000, 1, -1, 0, 1980.48, 1628.7, 16.1656, 1980.82, 1628.38, 16.1656, 288.69, 1986.53, 1625.57, 15.638, 196.007, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(73, 0, '', 15, 0, 0, 0, 1715904000, 5000000, 500000, 1, -1, 0, 2008.44, 1618.28, 15.5235, 2008.63, 1618.34, 15.522, 16.8004, 2000.52, 1616.18, 15.6002, 200.183, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(74, 0, '', 15, 0, 0, 0, 1718928000, 5000000, 500000, 1, -1, 0, 1987.44, 1600.55, 15.6763, 1987.63, 1600.52, 15.6763, 9.25947, 1993.39, 1602.99, 15.6066, 182.115, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(75, 0, '', 15, 0, 0, 0, 1714867200, 5000000, 500000, 1, -1, 0, 2010.04, 1603.89, 15.5273, 2010.04, 1603.89, 15.5273, 275.764, 2002.8, 1602.91, 15.6833, 185.652, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(76, 0, '', 15, 0, 0, 0, 1716422400, 5000000, 500000, 1, -1, 0, 2009.98, 1571, 15.8456, 2009.98, 1570.83, 15.8456, 92.1745, 2005.41, 1575.34, 15.5463, 182.458, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(77, 0, '', 15, 0, 0, 0, 1713830400, 5000000, 500000, 1, -1, 0, 1982.28, 1560.59, 15.4122, 1982.06, 1560.59, 15.4106, 359.284, 1994.29, 1560.67, 15.5002, 182.855, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(78, 0, '', 15, 0, 0, 0, 1713830400, 5000000, 500000, 1, -1, 0, 2020.06, 1561.8, 15.3961, 2019.87, 1561.8, 15.3974, 175.504, 2005.31, 1556.21, 15.5489, 178.868, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(79, 0, '', 15, 0, 0, 0, 1720396800, 5000000, 500000, 1, -1, 0, 1984.47, 1538.26, 15.4992, 1984.51, 1538.08, 15.5073, 271.948, 1993.73, 1544.53, 15.5229, 180.852, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(80, 0, '', 15, 0, 0, 0, 1719446400, 5000000, 500000, 1, -1, 0, 2012, 1542.78, 16.0887, 2012.01, 1542.58, 16.0887, 91.3439, 2004.29, 1543.97, 15.7033, 178.056, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(81, 0, '', 13, 0, 0, 0, 1720742400, 5000000, 500000, 1, -1, 0, 1866.35, 1472.52, 10.3081, 1866.37, 1472.71, 10.3081, 267.564, 1870.74, 1476.45, 9.77439, 270.174, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(82, 0, '', 13, 0, 0, 0, 1718928000, 5000000, 500000, 1, -1, 0, 1866.01, 1439.84, 10.1865, 1866.2, 1439.84, 10.1865, 0.059347, 1868.98, 1441.87, 9.75565, 270.168, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(83, 0, '', 13, 0, 0, 0, 1716768000, 5000000, 500000, 1, -1, 0, 1864.69, 1419.24, 10.2651, 1864.69, 1419.06, 10.2651, 269.567, 1869.39, 1423.18, 9.75565, 358.282, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(84, 0, '', 13, 0, 0, 0, 1721433600, 5000000, 500000, 1, -1, 0, 1859.41, 1405.14, 9.75565, 1859.25, 1405.11, 9.75565, 179.473, 1869.95, 1405.06, 9.75565, 8.20399, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(85, 0, '', 13, 0, 0, 0, 1718409600, 5000000, 500000, 1, -1, 0, 1865.33, 1358.2, 10.2231, 1865.13, 1358.23, 10.2231, 355.711, 2348.16, 1486.61, 11.53, 128.938, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(86, 0, '', 13, 0, 0, 0, 1720224000, 5000000, 500000, 1, -1, 0, 1865.91, 1337.14, 10.3209, 1869.44, 1339.14, 9.75565, 184.821, 1869.68, 1336.24, 9.75565, 184.821, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(87, 0, '', 13, 0, 0, 0, 1745020800, 5000000, 500000, 1, -1, 0, 2038.95, 1339.85, 26.7362, 2039.14, 1339.85, 26.7362, 180.266, 2037.8, 1328.06, 26.1484, 270.55, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(88, 0, '', 13, 0, 0, 0, 1734912000, 5000000, 500000, 1, -1, 0, 2060.34, 1339.85, 26.635, 2060.4, 1336.4, 26.1504, 174.087, 2059.99, 1327.7, 26.1483, 268.15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(89, 0, '', 13, 0, 0, 0, 1722556800, 5000000, 500000, 1, -1, 0, 2207.32, 1363.39, 11.3589, 2207.31, 1363.61, 11.3587, 272.705, 2213.59, 1355.52, 11.3665, 274.085, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(90, 0, '', 13, 0, 0, 0, 1734652800, 5000000, 500000, 1, -1, 0, -36.7337, 2818.36, 7.4378, -39.9072, 2818.46, 7.4378, 88.4516, 2295.17, 1450.8, 11.6, 266.337, 0, 0, 0, 0, 0, 0, 0, 0, 1),
(91, 0, '', 15, 0, 0, 0, 1736121600, 5000000, 500000, 1, -1, 0, -69.4337, 2809.1, 7.8697, -66.7455, 2809.1, 7.4378, 271.083, 2293.74, 1545.47, 11.5818, 270.666, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(92, 0, '', 15, 0, 0, 0, 1721433600, 5000000, 500000, 1, -1, 1, -88.3026, 2817.37, 7.8152, -88.4052, 2820.06, 7.4378, 1.5961, 2340.85, 1534.45, 11.5791, 87.4904, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(93, 0, '', 13, 0, 0, 0, 1719792000, 5000000, 500000, 1, -1, 1, -129.971, 2823.82, 8.1727, -129.855, 2826.26, 7.4378, 359.844, 2348.42, 1522.66, 11.5835, 112.873, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(94, 0, '', 13, 0, 0, 0, 1721347200, 5000000, 500000, 1, -1, 0, -152.286, 2815.42, 7.4378, -153.789, 2815.43, 7.4378, 89.7735, 2348.64, 1475.77, 11.53, 40.0526, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(95, 0, '', 13, 0, 0, 0, 1721433600, 5000000, 500000, 1, -1, 0, -188.188, 2811.25, 7.8951, -190.081, 2810.98, 7.4378, 90.7993, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(96, 0, '', 15, 0, 0, 0, 1719014400, 5000000, 500000, 1, -1, 0, -844.376, 1915.41, 46.2944, -846.03, 1915.36, 45.9744, 84.5745, -850.785, 1928.24, 45.5172, 97.6355, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(97, 0, '', 15, 0, 0, 0, 1687478400, 5000000, 500000, 1, -1, 0, -848.89, 1872.28, 45.514, -850.688, 1872.44, 45.5187, 84.1777, -853.341, 1883.6, 45.5171, 86.5041, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(98, 0, '', 15, 0, 0, 0, 1701734400, 5000000, 500000, 1, -1, 0, -811.32, 1880.37, 45.5263, -811.611, 1878.66, 45.5251, 173.875, -819.767, 1873.49, 45.5213, 174.993, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(99, 0, '', 15, 0, 0, 0, 1719705600, 5000000, 500000, 1, -1, 0, -810.087, 1827.85, 45.5681, -809.857, 1829.44, 45.5051, 356.067, -812.44, 1834.98, 45.5064, 1.13539, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(100, 0, '', 15, 0, 0, 0, 1719360000, 5000000, 500000, 1, -1, 0, -776.506, 1880.42, 45.5481, -776.585, 1878.84, 45.5252, 174.858, -777.5, 1871.99, 45.5202, 178.15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(101, 0, '', 15, 0, 0, 0, 1721174400, 5000000, 500000, 1, -1, 0, -775.262, 1823.45, 46.2344, -774.869, 1825.5, 45.735, 354.651, -767.455, 1831.36, 45.5055, 355.75, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(102, 0, '', 15, 0, 0, 0, 1750464000, 9000000, 900000, 4, -1, 0, 2461.76, -1446.79, 81.8872, 2461.54, -1449.05, 81.8872, 181.371, 2476.29, -1441.7, 80.78, 89.2225, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(103, 0, '', 15, 0, 0, 0, 1719187200, 5000000, 500000, 1, -1, 0, -786.471, 1919.91, 46.2044, -786.064, 1921.26, 46.0077, 352.062, -777.025, 1925.63, 45.5292, 356.165, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(104, 0, '', 15, 0, 0, 0, 1716595200, 5000000, 500000, 1, -1, 0, -832.747, 1925.72, 45.5481, -832.271, 1927.58, 45.5278, 356.409, -815.359, 1932.9, 45.5239, 356.959, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(105, 0, '', 15, 0, 0, 0, 1721174400, 5000000, 500000, 1, -1, 0, -855.476, 1979.44, 45.5067, -855.886, 1977.28, 45.507, 179.169, -867.788, 1978.71, 45.5157, 1.72181, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(106, 0, '', 15, 0, 0, 0, 1719014400, 5000000, 500000, 1, -1, 0, -857.385, 2006.15, 45.5081, -859.314, 2006.22, 45.5095, 90.6619, -867.436, 2006.03, 45.5155, 0.927673, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(107, 0, '', 15, 0, 0, 0, 1695600000, 5000000, 500000, 1, -1, 0, -860.613, 2027.3, 45.6662, -860.901, 2025.28, 45.5107, 173.82, -865.959, 2026.2, 45.5144, 2.51559, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(108, 0, '', 15, 0, 0, 0, 1720569600, 5000000, 500000, 1, -1, 0, -835.617, 1974.8, 45.501, -833.38, 1974.61, 45.5012, 266.693, -829.242, 1976.73, 45.4996, 270.04, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(109, 0, '', 15, 0, 0, 0, 1755734400, 5000000, 500000, 1, -1, 0, -773.35, 1972.76, 46.1944, -775.244, 1972.73, 45.7718, 83.7254, -785.2, 1981.39, 45.4962, 83.0848, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(110, 0, '', 15, 0, 0, 0, 1715731200, 5000000, 500000, 1, -1, 0, -839.703, 2028.07, 46.3444, -837.901, 2027.84, 45.954, 263.933, -828.487, 2019.81, 45.4854, 264.862, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(111, 0, '', 15, 0, 0, 0, 1720569600, 5000000, 500000, 1, -1, 1, -776.826, 2024.93, 45.5281, -776.808, 2025.13, 45.5281, 84.0678, -783.832, 2023.28, 45.4854, 94.9916, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(112, 0, '', 15, 0, 0, 0, 1719100800, 5000000, 500000, 1, -1, 0, -835.276, 2060.11, 45.5181, -832.751, 2059.96, 45.4901, 267.09, -829.074, 2059.84, 45.4854, 266.449, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(113, 0, '', 15, 0, 0, 0, 1719187200, 5000000, 500000, 1, -1, 0, -778.032, 2096.16, 45.4969, -778.032, 2096.16, 45.4969, 268.037, -786.797, 2091.41, 45.4915, 88.2445, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(114, 0, '', 15, 0, 0, 0, 1719360000, 5000000, 500000, 1, -1, 0, -756.027, 2084.05, 45.5281, -756.012, 2083.88, 45.5281, 265.466, -746.704, 2087.21, 45.5054, 267.243, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(115, 0, '', 15, 0, 0, 0, 1714867200, 5000000, 500000, 1, -1, 1, -760.144, 2048.46, 46.2044, -760.127, 2048.7, 46.2044, 265.466, -751.697, 2038.22, 45.5017, 267.64, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(116, 0, '', 15, 0, 0, 0, 1721347200, 5000000, 500000, 1, -1, 0, -702.412, 2021.28, 45.4781, -702.397, 2021.47, 45.4781, 87.64, -709.171, 2018.1, 45.3891, 88.6413, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(117, 0, '', 15, 0, 0, 0, 1715299200, 5000000, 500000, 1, -1, 0, -753.528, 1991.18, 45.5004, -753.52, 1992.75, 45.5004, 358.394, -750.816, 1998.23, 45.5023, 273.593, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(118, 0, '', 15, 0, 0, 0, 1733529600, 9000000, 900000, 4, -1, 0, -611.488, -1618.76, 40.8847, -611.514, -1618.76, 40.8847, 332.118, -615.643, -1624.58, 40.5463, 60.3537, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(119, 0, '', 15, 0, 0, 0, 1750032000, 9000000, 900000, 4, -1, 0, -510.443, -1775.75, 41.5158, -510.443, -1775.75, 41.5158, 260.046, -517.195, -1773.16, 40.9478, 351.499, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(120, 0, '', 15, 0, 0, 0, 1750032000, 5000000, 500000, 1, -1, 0, -487.241, -1777.74, 41.542, -487.259, -1777.74, 41.5419, 175.257, -492.511, -1775.34, 41.1825, 175.027, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(121, 0, '', 15, 0, 0, 0, 1733356800, 5000000, 500000, 1, -1, 0, -467.177, -1793.71, 41.3468, -467.177, -1793.71, 41.3468, 265.331, -464.676, -1805.41, 41.1233, 267.629, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(122, 0, '', 15, 0, 0, 0, 1740441600, 5000000, 500000, 1, -1, 0, -421.446, -1316.6, 40.5495, -421.439, -1316.58, 40.5495, 245.735, -428.999, -1312.19, 40.5937, 64.2739, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(123, 0, '', 15, 0, 0, 0, 1741737600, 5000000, 500000, 1, -1, 0, -413.153, -1299.22, 40.8383, -413.153, -1299.22, 40.8383, 69.0989, -416.28, -1303.5, 40.6047, 65.6522, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(124, 0, '', 15, 0, 0, 0, 1755043200, 5000000, 500000, 1, -1, 0, -234.21, -1480.13, 40.4927, -234.21, -1480.13, 40.4927, 349.137, -243.587, -1482.6, 40.4062, 67.0977, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(125, 0, '', 15, 0, 0, 0, 1741564800, 5000000, 500000, 1, -1, 0, -222.712, -1454.18, 40.7277, -222.376, -1454.37, 40.724, 170.563, -226.338, -1460, 40.3984, 77.5018, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(126, 0, '', 7, 0, 0, 0, 1721433600, 2500000, 250000, 0, -1, 0, 1943.52, 1806.77, 15.7021, 1943.65, 1808.55, 15.403, 2.55367, 1958.13, 1801.17, 15.611, 359.528, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(127, 0, '', 7, 0, 0, 0, 1744243200, 2500000, 250000, 0, -1, 0, 1989.36, 1793.99, 15.7392, 1987.31, 1793.93, 15.5338, 91.2041, 1970.63, 1786.51, 15.6032, 359.474, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(128, 0, '', 7, 0, 0, 0, 1738800000, 2500000, 250000, 0, -1, 0, 1985.88, 1831.9, 16.111, 1984.84, 1834.56, 15.5124, 0.963271, 1970.57, 1821.49, 15.6112, 359.474, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(129, 0, '', 7, 0, 0, 0, 1735257600, 2500000, 250000, 0, -1, 0, 1749.78, 2188.99, 15.9263, 1751.54, 2188.95, 15.8666, 269.156, 0, 0, 0, 0, 2347.93, -2455.88, 1199.37, 0, 0, 0, 0, 0, 0),
(130, 0, '', 7, 0, 0, 0, 1734998400, 2500000, 250000, 0, -1, 0, 1747.32, 2155.08, 16.7052, 1747.23, 2153.36, 16.1245, 183.302, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(131, 0, '', 7, 0, 0, 0, 1733616000, 2500000, 250000, 0, -1, 1, 1745.89, 2115.24, 15.9475, 1747.91, 2115.41, 15.9501, 287.643, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(132, 0, '', 7, 0, 0, 0, 1735084800, 2500000, 250000, 0, -1, 0, 1749.3, 2076.43, 16.575, 1750.4, 2074.1, 16.0256, 181.109, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(133, 0, '', 7, 0, 0, 0, 1715731200, 2500000, 250000, 0, -1, 0, 1838.16, 1338.58, 10.2797, 1838.29, 1336.88, 9.75565, 179.566, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(134, 0, '', 7, 0, 0, 0, 1721260800, 2500000, 250000, 0, -1, 0, 1809.15, 1339.24, 10.6846, 1809.17, 1341.61, 9.75565, 1.30041, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(135, 0, '', 7, 0, 0, 0, 1719619200, 2500000, 250000, 0, -1, 0, 1800.69, 1337.78, 10.2236, 1800.56, 1335.83, 9.75565, 183.035, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(136, 0, '', 7, 0, 0, 0, 1718150400, 2500000, 250000, 0, -1, 0, 1764.07, 1334.23, 10.1264, 1765.78, 1334.18, 9.75565, 272.336, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(137, 0, '', 15, 0, 0, 0, 1721088000, 5000000, 500000, 1, -1, 0, 1945.14, 1845.31, 15.4186, 1946.59, 1845.34, 15.4186, 268.474, 1958.15, 1853.66, 15.5799, 179.253, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(138, 0, '', 15, 0, 0, 0, 1721433600, 9000000, 900000, 4, -1, 0, 826.363, -1387.18, 40.7036, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(139, 0, '', 15, 0, 0, 0, 1750982400, 9000000, 900000, 4, -1, 0, 2315.94, 1767.13, 0.99, 2318.26, 1767.04, 0.99, 267.425, 2322.35, 1757.91, 1.17804, 180.57, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(140, 0, '', 15, 0, 0, 0, 1750032000, 9000000, 900000, 4, -1, 0, 2006.86, 1289.98, 26.805, 2006.82, 1292.4, 26.805, 359.059, 1973.88, 1302.21, 24.2543, 356.343, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(141, 0, '', 15, 0, 0, 0, 1721433600, 5000000, 500000, 1, -1, 0, -216.432, 2808.52, 8.01442, -213.571, 2808.42, 7.43779, 268.759, -210.811, 2803.03, 7.07325, 7.60633, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(142, 0, '', 15, 0, 0, 0, 1698796800, 5000000, 500000, 1, -1, 0, -242.126, 2820.37, 8.00876, -242.058, 2818.18, 7.43779, 180.846, -254.163, 2820.76, 7.0744, 0.474976, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(143, 0, '', 15, 0, 0, 0, 1721433600, 5000000, 500000, 1, -1, 0, -270.582, 2812.49, 8.11466, -270.521, 2814.86, 7.43779, 359.481, -276.292, 2825.84, 7.07348, 359.445, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(144, 0, '', 15, 0, 0, 0, 1722211200, 5000000, 500000, 1, -1, 0, -325.389, 2842.1, 7.70671, -323.463, 2843.09, 6.96904, 299.891, -324.602, 2830.61, 6.6057, 298.519, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(145, 0, '', 15, 0, 0, 0, 1720828800, 5000000, 500000, 1, -1, 1, -343.807, 2857.19, 6.96904, -344.414, 2858.35, 6.96904, 28.4525, -351.487, 2865.13, 6.6057, 299.745, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(146, 0, '', 15, 0, 0, 0, 1721606400, 5000000, 500000, 1, -1, 1, -365.35, 2886.21, 7.42907, -365.947, 2887.44, 6.96904, 26.328, -352.847, 2890.25, 6.60475, 298.957, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(147, 0, '', 15, 0, 0, 0, 1721433600, 5000000, 500000, 1, -1, 0, -381.851, 2909.3, 7.54832, -380.588, 2906.98, 6.97679, 208.652, -369.632, 2919.01, 6.60495, 298.297, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(148, 0, '', 15, 0, 0, 0, 1744243200, 5000000, 500000, 1, -1, 0, -36.6639, 2870.41, 8.30528, -36.6307, 2868.22, 7.43779, 180.028, -30.3787, 2871.22, 7.07348, 271.272, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(149, 0, '', 15, 0, 0, 0, 1721433600, 5000000, 500000, 1, -1, 0, -73.9197, 2871.63, 8.11466, -74.0145, 2869.59, 7.43779, 180.402, -62.3122, 2875.22, 7.07277, 179.798, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(150, 0, '', 15, 0, 0, 0, 1741910400, 5000000, 500000, 1, -1, 0, -102.371, 2863.75, 8.00876, -102.343, 2865.51, 7.43779, 1.28115, -95.7713, 2862.75, 7.07437, 180.892, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(151, 0, '', 15, 0, 0, 0, 1741824000, 5000000, 500000, 1, -1, 0, -123.094, 2870.28, 8.01442, -123.068, 2867.55, 7.43779, 180.044, -120.533, 2861.67, 7.07439, 180.202, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(152, 0, '', 15, 0, 0, 0, 1721001600, 5000000, 500000, 1, -1, 0, -155.627, 2872.88, 7.89507, -153.915, 2872.45, 7.43779, 269.371, -152.478, 2863.52, 7.07452, 180.04, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(153, 0, '', 15, 0, 0, 0, 1719619200, 5000000, 500000, 1, -1, 0, -182.615, 2874.28, 7.86971, -182.572, 2876.19, 7.43779, 2.02941, -183.442, 2883.27, 7.07113, 90.3174, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(154, 0, '', 15, 0, 0, 0, 1722556800, 5000000, 500000, 1, -1, 0, -191.894, 2906.97, 7.43779, -191.876, 2905.33, 7.43779, 180.295, -187.198, 2904.33, 7.06959, 88.0576, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(155, 0, '', 15, 0, 0, 0, 1721260800, 5000000, 500000, 1, -1, 0, -152.341, 2902.03, 8.30528, -150.288, 2902.06, 7.43779, 267.439, -154.794, 2910.63, 7.07325, 1.48941, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(156, 0, '', 15, 0, 0, 0, 1719619200, 5000000, 500000, 1, -1, 0, -129.168, 2910.69, 8.17271, -126.899, 2910.74, 7.43003, 268.728, -124.704, 2906.85, 7.06763, 359.9, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(157, 0, '', 15, 0, 0, 0, 1720396800, 5000000, 500000, 1, -1, 0, -88.2819, 2905.12, 7.81518, -88.4897, 2907.84, 7.43779, 2.08657, -103.704, 2901.52, 7.07331, 359.156, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(158, 0, '', 15, 0, 0, 0, 1720828800, 5000000, 500000, 1, -1, 0, -69.4339, 2896.86, 7.86971, -67.3833, 2896.99, 7.43779, 272.775, -60.7422, 2896.43, 7.06738, 359.603, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(159, 0, '', 15, 0, 0, 0, 1722470400, 5000000, 500000, 1, -1, 0, -36.7338, 2906.15, 7.43779, -38.7534, 2906.11, 7.43779, 93.6537, -39.5341, 2899.95, 7.07343, 359.263, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(160, 0, '', 15, 0, 0, 0, 1721347200, 5000000, 500000, 1, -1, 0, -36.6642, 2955.04, 8.30528, -36.531, 2952.78, 7.43779, 179.98, -30.5794, 2955.75, 7.07462, 179.698, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(161, 0, '', 15, 0, 0, 0, 1719619200, 5000000, 500000, 1, -1, 0, -102.341, 2948.38, 8.00876, -102.35, 2950.43, 7.43779, 1.49253, -95.8061, 2945.56, 7.07449, 181.078, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(162, 0, '', 15, 0, 0, 0, 1721347200, 5000000, 500000, 1, -1, 0, -128.036, 2960.23, 8.01442, -130.725, 2960.29, 7.43779, 89.8971, -120.692, 2944.95, 7.07343, 180.599, -2506.74, -2802.61, 1049.86, 0, 0, 0, 0, 0, 0),
(163, 0, '', 15, 0, 0, 0, 1720569600, 5000000, 500000, 1, -1, 1, -156.28, 2957.49, 7.89507, -154.304, 2957.4, 7.43779, 269.512, -152.278, 2948.56, 7.07497, 179.906, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(164, 0, '', 15, 0, 0, 0, 1719705600, 5000000, 500000, 1, -1, 0, -192.181, 2953.32, 7.43779, -190.77, 2953.31, 7.43779, 270.056, -181.724, 2956.28, 7.07477, 179.396, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(165, 0, '', 15, 0, 0, 0, 1742256000, 5000000, 500000, 1, -1, 0, -214.758, 2946.44, 7.81518, -214.736, 2943.33, 7.43779, 180.61, -219.8, 2950.2, 7.0734, 178.876, -2506, -2794.73, 1049.86, 0, 0, 0, 0, 0, 0),
(166, 0, '', 15, 0, 0, 0, 1721433600, 5000000, 500000, 1, -1, 0, -261.942, 2873.42, 7.54832, -260.513, 2870.74, 6.96904, 207.72, -252.687, 2887.27, 6.60552, 299.437, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(167, 0, '', 15, 0, 0, 0, 1719532800, 5000000, 500000, 1, -1, 0, -264.513, 2901.58, 7.54269, -266.169, 2900.74, 6.97679, 120.201, -264.844, 2909.15, 6.60441, 300.469, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(168, 0, '', 15, 0, 0, 0, 1720915200, 5000000, 500000, 1, -1, 0, -285.57, 2922.3, 7.64863, -283.411, 2923.47, 6.96904, 299.323, -293.627, 2931.28, 6.60489, 299.425, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(169, 0, '', 15, 0, 0, 0, 1721260800, 5000000, 500000, 1, -1, 0, -296.849, 2887.11, 7.42907, -295.835, 2885.41, 6.96904, 209.556, -303.5, 2878.77, 6.60515, 119.541, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(170, 0, '', 15, 0, 0, 0, 1721174400, 5000000, 500000, 1, -1, 1, -318.404, 2916.13, 6.96904, -317.52, 2914.77, 6.96904, 209.049, -326.907, 2907.88, 6.6077, 120.54, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(171, 0, '', 15, 0, 0, 0, 1734912000, 5000000, 500000, 1, -1, 0, -336.868, 2931.28, 7.70661, -338.586, 2930.29, 6.96904, 119.771, -336.099, 2937.66, 6.60431, 119.555, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(172, 0, '', 15, 0, 0, 0, 1722470400, 13000000, 1300000, 5, -1, 0, 3819.92, 3916.49, 8.78906, 3819.92, 3916.5, 8.78906, 277.293, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(173, 0, '', 15, 0, 0, 0, 1722470400, 13000000, 1300000, 5, -1, 0, 3817.2, 3957.5, 8.29688, 3817.2, 3957.5, 8.29688, 89.0009, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(174, 0, '', 15, 0, 0, 0, 1722470400, 13000000, 1300000, 5, -1, 0, 3856.15, 3976.15, 8.65625, 3856.15, 3976.15, 8.65625, 196.162, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(175, 0, '', 15, 0, 0, 0, 1721088000, 13000000, 1300000, 5, -1, 0, 3931.42, 3999.76, 8.66406, 3931.42, 3999.76, 8.66406, 16.3305, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0),
(176, 0, '', 15, 0, 0, 0, 1721347200, 13000000, 1300000, 5, -1, 0, 3964.34, 4013.87, 8.4375, 3964.34, 4013.87, 8.4375, 195.849, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0),
(177, 0, '', 15, 0, 0, 0, 1722470400, 13000000, 1300000, 5, -1, 1, 3983.92, 3964.3, 8.78906, 3983.92, 3964.3, 8.78906, 105.294, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(178, 0, '', 15, 0, 0, 0, 1721865600, 13000000, 1300000, 5, -1, 0, 3974.02, 3909.12, 10.1016, 3974.02, 3909.12, 10.1016, 101.534, 0, 0, 0, 0, -1713.33, 2749.14, 1001.04, 0, 0, 0, 0, 0, 0),
(179, 0, '', 15, 0, 0, 0, 1721433600, 13000000, 1300000, 5, -1, 1, 3968.27, 3863.99, 8.60938, 3968.27, 3863.99, 8.60938, 285.15, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0),
(180, 0, '', 15, 0, 0, 0, 1720742400, 13000000, 1300000, 5, -1, 1, 3889.84, 3846.07, 8.77344, 3889.84, 3846.07, 8.77344, 121.275, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(181, 0, '', 15, 0, 0, 0, 1722124800, 13000000, 1300000, 5, -1, 0, 3847.36, 3839.88, 8.29688, 3847.36, 3839.88, 8.29688, 281.68, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(182, 0, '', 15, 0, 0, 0, 1722124800, 13000000, 1300000, 5, -1, 0, 3831.77, 3873.87, 8.4375, 3831.77, 3873.87, 8.4375, 282.62, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(183, 0, '', 15, 0, 0, 0, 1720828800, 13000000, 1300000, 5, -1, 0, 3875.61, 3884.81, 8.60938, 3875.61, 3884.81, 8.60938, 102.764, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0),
(184, 0, '', 15, 0, 0, 0, 1721347200, 13000000, 1300000, 5, -1, 0, 3858.66, 3931.08, 8.66406, 3858.66, 3931.08, 8.66406, 188.329, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0),
(185, 0, '', 15, 0, 0, 0, 1721433600, 13000000, 1300000, 5, -1, 0, 3934.33, 3949.67, 8.65625, 3934.33, 3949.67, 8.65625, 283.896, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0),
(186, 0, '', 15, 0, 0, 0, 1721001600, 13000000, 1300000, 5, -1, 0, 3909.92, 4062.98, 8.60938, 3909.92, 4062.98, 8.60938, 276.063, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0),
(187, 0, '', 15, 0, 1, 0, 1722384000, 13000000, 1300000, 5, -1, 0, 3900.46, 4100.64, 8.62831, 3900.46, 4100.64, 8.62831, 195.535, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(188, 0, '', 15, 0, 1, 0, 1722038400, 13000000, 1300000, 5, -1, 0, 3890.99, 4142.46, 10.1016, 3890.99, 4142.46, 10.1016, 102.498, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(189, 0, '', 15, 0, 1, 0, 1720569600, 13000000, 1300000, 5, -1, 0, 3871.49, 4182.38, 8.77344, 3871.49, 4182.38, 8.77344, 301.756, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(190, 0, '', 15, 0, 1, 0, 1720310400, 13000000, 1300000, 5, -1, 0, 3867.98, 4218.45, 8.66406, 3867.98, 4218.45, 8.66406, 18.2103, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(191, 0, '', 15, 0, 1, 0, 1742515200, 13000000, 1300000, 5, -1, 0, 3845.24, 4257.48, 8.6806, 3845.24, 4257.48, 8.6806, 197.752, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(192, 0, '', 15, 0, 1, 0, 1721779200, 13000000, 1300000, 5, -1, 0, 3882.01, 4269.44, 8.69889, 3882.01, 4269.44, 8.69889, 110.644, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(193, 0, '', 15, 0, 1, 0, 1743292800, 13000000, 1300000, 5, -1, 0, 3913.7, 4286.3, 8.8056, 3913.7, 4286.3, 8.8056, 202.428, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(194, 0, '', 15, 0, 1, 0, 1735257600, 13000000, 1300000, 5, -1, 0, 3925.51, 4240.11, 8.4375, 3925.51, 4240.11, 8.4375, 98.424, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(195, 0, '', 15, 0, 1, 0, 1722556800, 13000000, 1300000, 5, -1, 0, 3922.11, 4192.91, 8.29688, 3922.11, 4192.91, 8.29688, 5.04981, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(196, 0, '', 15, 0, 1, 0, 1721433600, 13000000, 1300000, 5, -1, 0, 3928.3, 4147.11, 8.73438, 3928.3, 4147.11, 8.73438, 94.3507, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(197, 0, '', 15, 0, 0, 0, 1721433600, 13000000, 1300000, 5, -1, 0, 3940.99, 4093.05, 8.65625, 3940.99, 4093.05, 8.65625, 194.618, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0),
(198, 0, '', 15, 0, 0, 0, 1722556800, 13000000, 1300000, 5, -1, 0, 3840.46, 4049.62, 8.29688, 3840.46, 4049.62, 8.29688, 284.186, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(199, 0, '', 15, 0, 1, 0, 1722124800, 13000000, 1300000, 5, -1, 1, 3827.71, 4093.81, 8.78906, 3831.29, 4094.32, 8.00033, 282.653, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(200, 0, '', 15, 0, 1, 0, 1721174400, 13000000, 1300000, 5, -1, 0, 3806.04, 4153.84, 8.73077, 3806.04, 4153.84, 8.73077, 102.788, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(201, 0, '', 15, 0, 1, 0, 1719619200, 13000000, 1300000, 5, -1, 0, 3786.19, 4195.52, 8.3714, 3786.19, 4195.52, 8.3714, 18.1867, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(202, 0, '', 15, 0, 1, 0, 1721692800, 13000000, 1300000, 5, -1, 0, 3778.97, 4247.48, 8.51353, 3778.97, 4247.48, 8.51353, 109.368, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(203, 0, '', 15, 0, 1, 0, 1722211200, 13000000, 1300000, 5, -1, 0, 3757.64, 4309.5, 8.77344, 3757.64, 4309.5, 8.77344, 22.8868, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(204, 0, '', 15, 0, 1, 0, 1722211200, 13000000, 1300000, 5, -1, 0, 3801.63, 4317.87, 10.1016, 3801.63, 4317.87, 10.1016, 22.2601, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(205, 0, '', 15, 0, 1, 0, 1721952000, 13000000, 1300000, 5, -1, 0, 3843.68, 4349.07, 8.66406, 3843.68, 4349.07, 8.66406, 105.608, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(206, 0, '', 15, 0, 1, 0, 1721347200, 13000000, 1300000, 5, -1, 0, 3882.09, 4347.04, 8.78906, 3881.99, 4347.33, 8.78906, 18.5236, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(207, 0, '', 15, 0, 1, 0, 1721433600, 13000000, 1300000, 5, -1, 0, 3722.9, 4285.5, 8.78906, 3722.9, 4285.5, 8.78906, 20.0667, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(208, 0, '', 15, 0, 1, 0, 1721606400, 13000000, 1300000, 5, -1, 0, 3679.99, 4276.69, 8.73438, 3679.91, 4276.83, 8.73438, 28.84, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(209, 0, '', 15, 0, 1, 0, 1721347200, 13000000, 1300000, 5, -1, 0, 3642.6, 4254.81, 8.66406, 3606.84, 4207.97, 8.60938, 62.6802, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(210, 0, '', 15, 0, 1, 0, 1722124800, 13000000, 1300000, 5, -1, 0, 3606.84, 4207.97, 8.60938, 3606.84, 4207.97, 8.60938, 62.6802, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(211, 0, '', 15, 0, 1, 0, 1742428800, 13000000, 1300000, 5, -1, 0, 3606.73, 4157.54, 10.1016, 3606.73, 4157.54, 10.1016, 76.467, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(212, 0, '', 15, 0, 1, 0, 1721433600, 13000000, 1300000, 5, -1, 0, 3594.84, 4114.47, 8.77344, 3594.84, 4114.47, 8.77344, 90.2539, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(213, 0, '', 15, 0, 0, 0, 1721779200, 13000000, 1300000, 5, -1, 0, 3596.08, 4073.56, 8.4375, 3596.08, 4073.56, 8.4375, 84.9273, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(214, 0, '', 15, 0, 0, 0, 1721433600, 13000000, 1300000, 5, -1, 0, 3655.93, 4066.37, 8.66406, 3655.93, 4066.37, 8.66406, 271.989, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(215, 0, '', 15, 0, 0, 0, 1722556800, 13000000, 1300000, 5, -1, 0, 3707.46, 4078.88, 8.65625, 3707.46, 4078.88, 8.65625, 183.001, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(216, 0, '', 15, 0, 0, 0, 1722556800, 13000000, 1300000, 5, -1, 0, 3752.28, 4073.99, 8.73438, 3752.28, 4073.99, 8.73438, 180.808, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(217, 0, '', 15, 0, 0, 0, 1720828800, 13000000, 1300000, 5, -1, 0, 3802.18, 4036.57, 8.77344, 3802.18, 4036.57, 8.77344, 7.86988, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(218, 0, '', 15, 0, 0, 0, 1721347200, 13000000, 1300000, 5, -1, 0, 3757.36, 4021.92, 8.62515, 3757.36, 4021.92, 8.62515, 0.348865, 0, 0, 0, 0, -1712.88, 2748.93, 1001.04, 0, 0, 0, 0, 0, 0),
(219, 0, '', 15, 0, 0, 0, 1748304000, 13000000, 1300000, 5, -1, 0, 3705.18, 4031.3, 8.73438, 3705.18, 4031.3, 8.73438, 359.096, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(220, 0, '', 15, 0, 0, 0, 1744156800, 13000000, 1300000, 5, -1, 0, 3657.45, 4025.28, 8.65625, 3657.45, 4025.28, 8.65625, 1.91653, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(221, 0, '', 15, 0, 0, 0, 1722124800, 13000000, 1300000, 5, -1, 0, 3668.67, 3951.95, 8.29688, 3668.67, 3951.95, 8.29688, 90.2774, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(222, 0, '', 15, 0, 0, 0, 1753574400, 13000000, 1300000, 5, -1, 0, 3708.07, 3963.25, 8.78906, 3708.07, 3963.25, 8.78906, 179.892, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0),
(223, 0, '', 15, 0, 0, 0, 1721952000, 13000000, 1300000, 5, -1, 0, 3748.19, 3953.66, 8.77344, 3748.19, 3953.66, 8.77344, 180.517, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(224, 0, '', 15, 0, 1, 0, 1722556800, 13000000, 1300000, 5, -1, 0, 3745.97, 4156.24, 8.60938, 3745.97, 4156.24, 8.60938, 359.434, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(225, 0, '', 15, 0, 1, 0, 1721433600, 13000000, 1300000, 5, -1, 0, 3712.02, 4144.95, 8.4375, 3712.02, 4144.95, 8.4375, 0.059347, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(226, 0, '', 15, 0, 1, 0, 1722038400, 13000000, 1300000, 5, -1, 0, 3669.77, 4140.53, 8.78906, 3669.77, 4140.53, 8.78906, 3.50638, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(227, 0, '', 15, 0, 1, 0, 1721433600, 13000000, 1300000, 5, -1, 0, 3682.52, 4198.3, 8.62515, 3682.52, 4198.3, 8.62515, 214.695, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(228, 0, '', 15, 0, 1, 0, 1721347200, 13000000, 1300000, 5, -1, 0, 3729.33, 4222.63, 10.1016, 3729.33, 4222.63, 10.1016, 204.041, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(229, 0, '', 5, 0, 0, 0, 1741996800, 9000000, 900000, 4, -1, 1, -1955.72, 1561.57, 126.334, -1955.81, 1563.21, 126.325, 181.55, -1955.21, 1571.52, 126.298, 1.54965, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(230, 0, '', 0, 0, 0, 0, 1721433600, 9000000, 900000, 3, -1, 0, 2487.49, -252.678, 1.85722, 2487.49, -252.678, 1.85722, 89.0656, 2497.12, -260.651, 1.68644, 237.261, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(231, 0, '', 15, 0, 0, 0, 1743465600, 9000000, 900000, 4, -1, 0, -2445.8, 2193.04, 54.4822, -2444.63, 2193.71, 54.4678, 125.546, -2439.47, 2203.8, 54.2805, 20.0302, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(232, 0, '', 15, 0, 0, 0, 1714435200, 5000000, 500000, 1, -1, 0, -721.896, -1638.69, 42.375, -721.92, -1638.73, 42.3771, 56.2307, -717.111, -1644.25, 41.8031, 147.453, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(233, 0, '', 15, 0, 0, 0, 1754870400, 9000000, 900000, 3, -1, 0, -241.635, -1506.6, 40.7278, -241.635, -1506.6, 40.7278, 345.821, -248.906, -1510.27, 40.4062, 162.621, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(234, 0, '', 15, 0, 0, 0, 1733356800, 5000000, 500000, 1, -1, 0, -740.857, -1625.79, 42.3049, -740.967, -1625.73, 42.3054, 327.601, -737.066, -1630.4, 42.0369, 329.669, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(235, 0, '', 15, 0, 0, 0, 1733356800, 5000000, 500000, 1, -1, 0, -750.383, -1601.63, 42.2152, -750.383, -1601.63, 42.2152, 55.1472, -747.543, -1590.46, 41.995, 50.3218, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(236, 0, '', 15, 0, 0, 0, 1733356800, 5000000, 500000, 1, -1, 0, -471.77, -1742.74, 41.2428, -471.77, -1742.74, 41.2428, 85.6428, -471.046, -1735.27, 41.0173, 51.4056, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(237, 0, '', 15, 0, 0, 0, 1753920000, 5000000, 500000, 1, -1, 0, -720.023, -1711.05, 42.2817, -720.023, -1711.05, 42.2817, 321.856, -730.069, -1728.91, 42.0483, 226.728, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(238, 0, '', 15, 0, 0, 0, 1736899200, 9000000, 900000, 3, -1, 0, -243.022, -1552.29, 40.7562, -243.083, -1551.98, 40.6836, 350.523, -236.041, -1551.74, 40.4251, 170.835, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(239, 0, '', 15, 0, 0, 0, 1735084800, 9000000, 900000, 3, -1, 0, -220.175, -1597.5, 40.9867, -219.909, -1597.46, 40.8155, 267.006, -212.542, -1601.41, 40.8096, 228.017, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(240, 0, '', 15, 0, 0, 0, 1735344000, 9000000, 900000, 3, -1, 0, -246.299, -1529.84, 40.603, -246.692, -1529.84, 40.4115, 79.7581, -248.629, -1508.12, 40.8328, 148.428, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(241, 0, '', 15, 0, 0, 0, 1733356800, 9000000, 900000, 3, -1, 0, -163.965, -1597.27, 41.2256, -163.936, -1596.91, 41.1122, 353.386, -158.741, -1592.76, 40.7066, 176.603, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(242, 0, '', 15, 0, 0, 0, 1737331200, 9000000, 900000, 3, -1, 0, -283.042, -1412.12, 40.7277, -283.293, -1412.47, 40.7236, 83.3605, -274.743, -1411.83, 40.3672, 348.067, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(243, 0, '', 15, 0, 0, 0, 1737331200, 9000000, 900000, 3, -1, 0, -261.085, -1413.12, 40.603, -261.479, -1412.94, 40.4688, 78.223, -266.458, -1411.18, 40.3832, 167.46, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(244, 0, '', 15, 0, 0, 0, 1733356800, 9000000, 900000, 3, -1, 0, -365.083, -1757.24, 41.5164, -365.083, -1757.24, 41.5164, 251.309, -371.075, -1761.15, 41.1734, 251.539, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(245, 0, '', 15, 0, 0, 0, 1733356800, 13000000, 1300000, 5, -1, 0, -441.489, -1779.77, 41.5541, -441.489, -1779.77, 41.5541, 354.282, -442.544, -1784.31, 40.998, 86.424, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(246, 0, '', 15, 0, 0, 0, 1737331200, 9000000, 900000, 3, -1, 0, -370.593, -1792.94, 41.1987, -370.588, -1792.93, 41.1989, 72.6053, -372.342, -1801.28, 41.0599, 74.6809, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(247, 0, '', 15, 0, 0, 0, 1733443200, 9000000, 900000, 3, -1, 0, -451.046, -1758.14, 41.31, -451.046, -1758.14, 41.31, 359.633, -445.423, -1760.37, 40.9203, 358.253, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(248, 0, '', 15, 0, 0, 0, 1733356800, 9000000, 900000, 3, -1, 0, -425.995, -1734.21, 41.5053, -425.995, -1734.21, 41.5053, 266.931, -432.981, -1732.92, 40.9396, 355.626, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(249, 0, '', 15, 0, 0, 0, 1733356800, 9000000, 900000, 3, -1, 0, -259.324, -1629.7, 40.8114, -259.311, -1629.62, 40.7836, 312.756, -253.299, -1622.58, 40.6626, 346.222, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(250, 0, '', 0, 0, 0, 0, 1721088000, 9000000, 900000, 3, -1, 0, 2524.48, -198.935, 3.71875, 2524.48, -198.935, 3.71875, 89.9857, 2530.82, -203.907, 3.2, 180.813, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(251, 0, '', 15, 0, 0, 0, 1733356800, 9000000, 900000, 3, -1, 0, -400.085, -1737.86, 41.2985, -400.085, -1737.88, 41.2981, 88.5223, -398.212, -1745.57, 41.0392, 166.188, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(252, 0, '', 15, 0, 0, 0, 1734998400, 9000000, 900000, 3, -1, 0, -307.244, -1741.96, 41.4441, -307.263, -1741.96, 41.444, 6.06744, -303.046, -1741.34, 41.0995, 357.336, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(253, 0, '', 15, 0, 0, 0, 1733356800, 9000000, 900000, 3, -1, 0, -238.545, -1716.16, 41.0488, -238.545, -1716.16, 41.0488, 76.281, -247.335, -1709.97, 40.688, 350.803, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(254, 0, '', 15, 0, 0, 0, 1733356800, 9000000, 900000, 3, -1, 0, -257.224, -1749.96, 41.2788, -257.224, -1749.96, 41.2788, 346.503, -242.576, -1755.99, 40.8581, 316.631, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(255, 0, '', 15, 0, 0, 0, 1740528000, 9000000, 900000, 3, -1, 0, -206.493, -1718.15, 41.4812, -206.493, -1718.15, 41.4812, 256.1, -214.574, -1722.83, 40.8753, 165.861, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(256, 0, '', 15, 0, 0, 0, 1733356800, 9000000, 900000, 3, -1, 0, -166.578, -1668.42, 41.358, -166.578, -1668.42, 41.358, 259.087, -170.723, -1674.5, 40.8008, 172.69, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(257, 0, '', 15, 0, 0, 0, 1734825600, 9000000, 900000, 3, -1, 0, -288.85, -1688.15, 41.1936, -288.85, -1688.15, 41.1936, 82.2878, -284.194, -1681.26, 40.5312, 330.688, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(258, 0, '', 15, 0, 0, 0, 1740441600, 9000000, 900000, 4, -1, 0, -289.579, -1651.23, 41.1755, -289.643, -1651.2, 41.1753, 115.67, -280.552, -1649.48, 40.6471, 24.9071, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(259, 0, '', 15, 0, 0, 0, 1735171200, 9000000, 900000, 4, -1, 0, -271.474, -1715.82, 40.9018, -271.474, -1715.82, 40.9018, 260.893, -273.251, -1709.47, 40.519, 343.613, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(260, 0, '', 15, 0, 0, 0, 1736899200, 9000000, 900000, 4, -1, 1, -344.338, -1709.55, 41.6804, -344.338, -1709.55, 41.6804, 350.442, -338.346, -1713.67, 41.0694, 119.973, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(261, 0, '', 15, 0, 0, 0, 1733356800, 9000000, 900000, 4, -1, 0, -344.866, -1741.19, 41.318, -344.866, -1741.19, 41.318, 338.494, -337.872, -1744.29, 41.0769, 316.895, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(262, 0, '', 15, 0, 0, 0, 1721347200, 9000000, 900000, 3, -1, 0, 2770.44, -290.37, 3.57812, 2770.44, -290.37, 3.57812, 92.3921, 2774.36, -293.51, 3.57812, 282.511, 435.628, 1319.34, 1615.53, 0, 0, 0, 0, 0, 0),
(263, 0, '', 15, 0, 0, 0, 1721174400, 9000000, 900000, 3, -1, 0, 2773.47, -254.051, 3.57033, 2773.47, -254.051, 3.57033, 86.5816, 2780.06, -261.052, 3.62246, 358.66, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(264, 0, '', 15, 0, 0, 0, 1721174400, 9000000, 900000, 3, -1, 0, 2750.04, -237.004, 3.57033, 2750.04, -237.004, 3.57033, 180.62, 2754.69, -234.174, 3.57812, 2.17637, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(265, 0, '', 15, 0, 0, 0, 1721433600, 9000000, 900000, 3, -1, 1, 2716.61, -230.886, 3.54258, 2716.61, -230.886, 3.54258, 179.343, 2713.29, -223.95, 3.38696, 265.43, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(266, 0, '', 0, 0, 0, 0, 1720915200, 9000000, 900000, 3, -1, 0, 2685.65, -231.572, 3.98125, 2685.65, -231.572, 3.98125, 179.281, 2688.96, -225.603, 3.88454, 91.665, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(267, 0, '', 0, 0, 0, 0, 1720051200, 9000000, 900000, 3, -1, 0, 2668.45, -246.069, 3.97777, 2668.49, -245.483, 3.97378, 180.351, 2666.88, -234.939, 4.10652, 81.5729, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `houses` (`id`, `owner_id`, `name`, `city`, `zone`, `miami`, `improvements`, `rent_time`, `price`, `rent_price`, `type`, `entrance`, `lock`, `x`, `y`, `z`, `exit_x`, `exit_y`, `exit_z`, `exit_angle`, `car_x`, `car_y`, `car_z`, `car_angle`, `store_x`, `store_y`, `store_z`, `eviction`, `store_metall`, `store_drugs`, `store_weapon`, `store_ammo`, `store_skin`) VALUES
(268, 0, '', 0, 0, 0, 0, 1721692800, 9000000, 900000, 3, -1, 0, 2627.69, -232.803, 3.98125, 2627.69, -232.803, 3.98125, 179.128, 2619.27, -226.281, 3.98184, 77.2641, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(269, 0, '', 0, 0, 0, 0, 1721260800, 9000000, 900000, 4, -1, 0, 2608.47, -201.014, 6.83391, 2608.47, -201.014, 6.83391, 270.72, 2603.05, -206.543, 5.99097, 177.14, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(270, 0, '', 0, 0, 0, 0, 1721260800, 9000000, 900000, 3, -1, 0, 2590.49, -230.935, 4.04502, 2590.49, -230.935, 4.04502, 180.351, 2595.83, -230.161, 3.97378, 336.677, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(271, 0, '', 0, 0, 0, 0, 1722556800, 9000000, 900000, 3, -1, 0, 2513.64, -230.507, 2.56719, 2513.64, -230.507, 2.56719, 178.225, 2509, -227.826, 2.446, 87.7036, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(272, 0, '', 0, 0, 0, 0, 1721433600, 9000000, 900000, 3, -1, 0, 2508.99, -263.715, 2.05474, 2508.99, -263.715, 2.05474, 270.177, 2503.44, -265.816, 1.64822, 255.192, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(273, 0, '', 0, 0, 0, 0, 1717113600, 9000000, 900000, 3, -1, 0, 2466.7, -201.202, 2.1375, 2466.7, -201.202, 2.1375, 1.46353, 2465.13, -210.332, 2.1375, 220.635, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(274, 0, '', 0, 0, 0, 0, 1721260800, 9000000, 900000, 3, -1, 0, 2454, -205.102, 2.26849, 2454, -205.102, 2.2685, 356.319, 2452.31, -210.983, 2.1375, 91.2749, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(275, 0, '', 0, 0, 0, 0, 1720569600, 9000000, 900000, 3, -1, 0, 2414.88, -230.624, 2.05938, 2414.88, -230.624, 2.05938, 175.322, 2410.63, -225.836, 2.17001, 356.878, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(276, 0, '', 0, 0, 0, 0, 1720051200, 9000000, 900000, 3, -1, 0, 2422.18, -206.156, 2.3574, 2422.18, -206.156, 2.3574, 358.297, 2423.11, -211.436, 2.1375, 93.9192, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(277, 0, '', 0, 0, 0, 0, 1720051200, 9000000, 900000, 3, -1, 0, 2381.84, -202.442, 2.83037, 2381.84, -202.442, 2.83037, 275.672, 2376.81, -209.306, 2.1375, 186.68, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(278, 0, '', 0, 0, 0, 0, 1721088000, 9000000, 900000, 3, -1, 0, 2356.44, -207.057, 2.1375, 2356.64, -207.059, 2.1375, 182.147, 2356.58, -216.048, 2.1375, 94.9895, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(279, 0, '', 0, 0, 0, 0, 1720656000, 9000000, 900000, 3, -1, 0, 2330.16, -205.211, 2.42344, 2330.39, -205.214, 2.42344, 178.685, 2328.98, -215.309, 2.1375, 81.4351, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(280, 0, '', 0, 0, 0, 0, 1720051200, 9000000, 900000, 3, -1, 0, 2285.14, -229.196, 2.06268, 2285.14, -229.196, 2.06268, 173.387, 2281.1, -225.191, 2.23217, 84.3947, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(281, 0, '', 0, 0, 0, 0, 1718928000, 9000000, 900000, 3, -1, 0, 2261.18, -230.619, 2.07752, 2261.18, -230.619, 2.07752, 176.904, 2261.32, -223.039, 2.38924, 103.202, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(282, 0, '', 0, 0, 0, 0, 1721433600, 9000000, 900000, 4, -1, 0, 2240.52, -197.039, 2.39238, 2240.52, -197.039, 2.39238, 92.1928, 2219.02, -207.021, 2.09063, 88.2172, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(283, 0, '', 0, 0, 0, 0, 1748649600, 9000000, 900000, 3, -1, 0, 2204.55, -231.38, 2.07619, 2204.55, -231.38, 2.07619, 181.743, 2207.42, -224.79, 2.79593, 95.5025, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(284, 0, '', 2, 0, 0, 0, 1740528000, 9000000, 900000, 3, -1, 0, -2356.25, 2586.21, 41.7824, -2356.15, 2584.3, 41.6941, 0.108352, -2357.41, 2595.34, 41.5345, 71.4549, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(285, 0, '', 2, 0, 0, 0, 1734912000, 9000000, 900000, 3, -1, 0, -2342.5, 2593.29, 42.0089, -2342.48, 2594.98, 42.0012, 174.776, -2354.54, 2601.54, 41.5631, 85.7006, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(286, 0, '', 2, 0, 0, 0, 1745020800, 9000000, 900000, 3, -1, 0, -2358.28, 2608.47, 42.1653, -2357.53, 2608.33, 41.9152, 91.43, -2358.25, 2602.54, 41.5089, 106.564, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(287, 0, '', 2, 0, 0, 0, 1750032000, 9000000, 900000, 3, -1, 0, -2361.72, 2556.92, 41.9111, -2361.83, 2558.15, 41.8646, 180.069, -2358.69, 2568.74, 41.8218, 84.1636, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(288, 0, '', 2, 0, 0, 0, 1741564800, 9000000, 900000, 3, -1, 0, -2344.78, 2556.34, 41.8839, -2346.41, 2555.92, 41.8761, 85.8695, -2356.61, 2564.37, 41.9308, 42.4129, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(289, 0, '', 15, 0, 0, 0, 1718323200, 9000000, 900000, 3, -1, 0, -304.362, 1320.52, 12.4121, -304.342, 1322.12, 12.4512, 179.77, -303.024, 1331.9, 12.6922, 257.625, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(290, 0, '', 15, 0, 0, 0, 1721260800, 9000000, 900000, 3, -1, 0, -316.009, 1350.34, 12.82, -316.085, 1348.57, 12.82, 0.64498, -312.856, 1344.68, 12.82, 204.872, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(291, 0, '', 15, 0, 0, 0, 1713744000, 9000000, 900000, 3, -1, 0, -299.812, 1350.34, 12.82, -299.818, 1348.4, 12.82, 358.592, -303.085, 1344.66, 12.82, 91.6665, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(292, 0, '', 15, 0, 0, 0, 1717372800, 9000000, 900000, 4, -1, 0, -348.194, 1360.94, 12.3034, -348.2, 1359.38, 12.2854, 359.781, -348.381, 1352.04, 12.4756, 184.201, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(293, 0, '', 15, 0, 0, 0, 1721347200, 9000000, 900000, 4, -1, 0, -354.443, 1387.75, 12.4146, -356.255, 1387.62, 12.4122, 269.841, -350.132, 1400.95, 12.7198, 268.219, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(294, 0, '', 15, 0, 0, 0, 1717977600, 9000000, 900000, 3, -1, 0, -328.99, 1392.36, 12.82, -329.203, 1393.83, 12.82, 188.657, -325.199, 1398.25, 12.82, 279.245, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(295, 0, '', 15, 0, 0, 0, 1715558400, 9000000, 900000, 3, -1, 0, -312.501, 1392.36, 12.82, -312.605, 1393.67, 12.82, 183.035, -312.237, 1398.46, 12.82, 341.728, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(296, 0, '', 15, 0, 0, 0, 1721260800, 9000000, 900000, 3, -1, 0, -289.202, 1389.38, 12.4643, -289.228, 1390.93, 12.5016, 179.361, -288.209, 1401.77, 12.7151, 258.514, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(297, 0, '', 15, 0, 0, 0, 1753574400, 20000000, 2000000, 6, -1, 0, 1999.66, -2895.89, 4.74569, 1999.26, -2896.96, 4.45071, 172.463, 1991.66, -2908.83, 4.02266, 261.45, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(298, 0, '', 15, 0, 0, 0, 1750032000, 20000000, 2000000, 6, -1, 0, 2089.35, -2901.68, 4.75493, 2089.43, -2902.37, 4.50493, 23.8019, 2080.12, -2905.38, 4.02266, 74.0099, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(299, 0, '', 15, 0, 0, 0, 1742256000, 20000000, 2000000, 6, -1, 0, 1887.77, -3096.25, 4.75493, 1888.56, -3096.21, 4.50493, 75.9141, 1894.28, -3095.67, 4.01864, 296.764, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(300, 0, '', 15, 0, 0, 0, 1755043200, 20000000, 2000000, 6, -1, 0, 2032.79, -3105.78, 4.62677, 2032.92, -3105.86, 4.63339, 193.239, 2053.43, -3105.98, 3.79108, 119.961, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(301, 0, '', 15, 0, 0, 0, 1742860800, 20000000, 2000000, 6, -1, 0, 2101.29, -3103.68, 4.74569, 2101.83, -3104.39, 4.74569, 189.077, 2099.12, -3110.91, 4.02836, 159.122, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(302, 0, '', 15, 0, 0, 0, 1722470400, 20000000, 2000000, 6, -1, 1, 2101.02, -3175.71, 4.75493, 2100.74, -3174.16, 4.02836, 187.325, 2103.3, -3168.15, 4.02836, 355.639, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(303, 0, '', 15, 0, 0, 0, 1750032000, 20000000, 2000000, 6, -1, 0, 2011.9, -3215.6, 4.80525, 2011.07, -3214.84, 4.80525, 355.427, 2024.44, -3195.18, 4.02836, 98.8283, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(304, 0, '', 15, 0, 0, 0, 1741737600, 20000000, 2000000, 6, -1, 0, 2151.79, -3094.2, 4.02836, 2151.96, -3095.88, 4.02836, 2.86136, 2151.78, -3106.06, 4.02836, 180.795, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(305, 0, '', 15, 0, 0, 0, 1736726400, 20000000, 2000000, 6, -1, 0, 2258.48, -3119.33, 4.74762, 2258.6, -3118.12, 4.74762, 14.7608, 2253.56, -3113.63, 4.02763, 49.5812, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(306, 0, '', 15, 0, 0, 0, 1721520000, 20000000, 2000000, 6, -1, 0, 2222.59, -3052.99, 4.31057, 2223.36, -3054.24, 4.31057, 26.9787, 2228.87, -3062.39, 4.02763, 217.993, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(307, 0, '', 15, 0, 0, 0, 1722556800, 20000000, 2000000, 6, -1, 1, 2324.05, -3049.54, 4.74762, 2324.45, -3050.77, 4.74762, 8.59567, 2319.7, -3060.76, 4.02763, 141.992, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(308, 0, '', 15, 0, 0, 0, 1733616000, 20000000, 2000000, 6, -1, 0, 2414.93, -3040.05, 4.85156, 2415.54, -3041.23, 4.85156, 113.955, 2415.21, -3050.22, 4.02763, 164.294, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(309, 0, '', 15, 0, 0, 0, 1722124800, 20000000, 2000000, 6, -1, 0, 2521.93, -3032.86, 4.75493, 2521.96, -3034.17, 4.25493, 350.758, 2519.68, -3040.24, 4.02763, 171.611, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(310, 0, '', 15, 0, 0, 0, 1721347200, 20000000, 2000000, 6, -1, 0, 2575.72, -3107.21, 4.74569, 2575.5, -3105.98, 4.3159, 182.775, 2574.46, -3100.84, 4.02303, 7.00328, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(311, 0, '', 15, 0, 0, 0, 1721520000, 20000000, 2000000, 6, -1, 0, 2616.3, -3010.29, 4.29856, 2617.12, -3010.9, 4.29856, 44.4146, 2620.27, -3015.52, 4.02895, 207.431, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(312, 0, '', 15, 0, 0, 0, 1734134400, 20000000, 2000000, 6, -1, 0, 2691.72, -3013.86, 4.81892, 2691.99, -3014.98, 4.81892, 359.209, 2693.86, -3022.67, 4.02895, 183.869, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(313, 0, '', 15, 0, 0, 0, 1721692800, 20000000, 2000000, 6, -1, 0, 2775.99, -3021.09, 4.02895, 2774.92, -3021.68, 4.02895, 295.072, 2767.25, -3023.94, 4.02895, 111.061, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(314, 0, '', 15, 0, 0, 0, 1721520000, 20000000, 2000000, 6, -1, 0, 2788.45, -3076.75, 4.74762, 2787.86, -3076.5, 4.74762, 190.661, 2781.14, -3073.72, 4.02895, 44.7608, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(315, 0, '', 15, 0, 0, 0, 1741824000, 20000000, 2000000, 6, -1, 0, 2709.76, -3094.89, 4.80525, 2709.92, -3093.7, 4.80525, 132.219, 2724.79, -3083.42, 4.02895, 305.937, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(316, 0, '', 15, 0, 0, 0, 1722124800, 20000000, 2000000, 6, -1, 0, 2792.85, -3141.37, 4.73977, 2791.81, -3140.72, 4.45071, 11.6398, 2780.92, -3137.24, 4.02895, 76.2295, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(317, 0, '', 15, 0, 0, 0, 1721779200, 20000000, 2000000, 6, -1, 0, 2719.64, -3209.37, 4.29856, 2718.87, -3208.66, 4.29856, 220.562, 2721.5, -3201.7, 4.02718, 338.284, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(318, 0, '', 15, 0, 0, 0, 1722211200, 20000000, 2000000, 6, -1, 0, 2661.56, -3257.77, 4.75493, 2660.79, -3257.21, 4.25493, 218.8, 2664.35, -3247.29, 4.02036, 340.197, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(319, 0, '', 15, 0, 0, 0, 1722124800, 20000000, 2000000, 6, -1, 0, 2611.04, -3221.85, 4.85156, 2611.98, -3223.13, 4.85156, 33.8259, 2611.27, -3232.2, 4.02036, 184.302, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(320, 0, '', 15, 0, 0, 0, 1721952000, 20000000, 2000000, 6, -1, 1, 2615.44, -3291.53, 4.02718, 2614.66, -3290, 4.02718, 206.558, 2614.21, -3283.76, 4.02718, 17.4662, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(321, 0, '', 15, 0, 0, 0, 1722297600, 20000000, 2000000, 6, -1, 0, 2528.99, -3278.91, 4.74762, 2530.19, -3278.1, 4.59918, 124.815, 2537.58, -3275.89, 4.02036, 285.237, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(322, 0, '', 15, 0, 0, 0, 1722384000, 20000000, 2000000, 6, -1, 0, 2473.12, -3131.39, 4.81892, 2473.04, -3132.84, 4.81892, 353.313, 2469.89, -3138.23, 4.02763, 150.275, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(323, 0, '', 15, 0, 0, 0, 1722297600, 20000000, 2000000, 6, -1, 0, 2451.27, -3220.44, 4.29856, 2452.56, -3221.02, 4.29856, 74.69, 2464.29, -3211.56, 4.02763, 303.672, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(324, 0, '', 15, 0, 0, 0, 1722124800, 20000000, 2000000, 6, -1, 0, 2394.99, -3159.25, 4.74569, 2395.29, -3160.48, 4.45071, 25.4925, 2399.69, -3164.83, 4.02763, 221.503, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(325, 0, '', 15, 0, 0, 0, 1722211200, 20000000, 2000000, 6, -1, 0, 2344.14, -3214.15, 4.81892, 2345.81, -3214.74, 4.81892, 67.2645, 2351.2, -3220.48, 4.02763, 235.145, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(326, 0, '', 15, 0, 0, 0, 1722297600, 20000000, 2000000, 6, -1, 0, 2342.67, -3328.98, 4.02835, 2344.21, -3328.36, 4.02835, 107.66, 2364.79, -3332.04, 4.02007, 303.431, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(327, 0, '', 15, 0, 0, 0, 1722556800, 20000000, 2000000, 6, -1, 0, 2410.63, -3337.97, 4.73977, 2409.66, -3338.4, 4.45071, 289.584, 2403.27, -3333.69, 4.02835, 59.1976, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(328, 0, '', 15, 0, 0, 0, 1721347200, 20000000, 2000000, 6, -1, 0, 2424.28, -3397.38, 4.75493, 2422.57, -3397.29, 4.02835, 258.763, 2416.62, -3393.81, 4.02835, 67.6172, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(329, 0, '', 15, 0, 0, 0, 1722297600, 20000000, 2000000, 6, -1, 0, 2361.2, -3446.57, 4.85156, 2360.19, -3445.15, 4.85156, 209.55, 2364.88, -3436.86, 4.02835, 309.327, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(330, 0, '', 15, 0, 0, 0, 1722124800, 20000000, 2000000, 6, -1, 0, 2303.87, -3406.34, 4.02216, 2304.85, -3408.5, 4.02269, 17.7678, 2305.1, -3416.7, 4.02479, 189.865, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(331, 0, '', 15, 0, 0, 0, 1722470400, 20000000, 2000000, 6, -1, 0, 2292.81, -3471.8, 4.62677, 2292.44, -3470.45, 4.62677, 191.545, 2291.58, -3462.79, 4.02835, 13.1549, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(332, 0, '', 15, 0, 0, 0, 1735084800, 20000000, 2000000, 6, -1, 0, 2166.54, -3489.89, 4.74762, 2166.27, -3488.51, 4.59918, 182.479, 2165.71, -3483.18, 4.02226, 21.6007, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(333, 0, '', 15, 0, 0, 0, 1722124800, 20000000, 2000000, 6, -1, 0, 2072.22, -3496.18, 4.74569, 2072.07, -3495.32, 4.59915, 180.832, 2074.21, -3484, 4.02226, 352.497, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(334, 0, '', 15, 0, 0, 0, 1740700800, 20000000, 2000000, 6, -1, 0, 2102.63, -3412.1, 4.29856, 2101.01, -3412.55, 4.29856, 288.199, 2097.11, -3411.27, 4.02226, 74.3519, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(335, 0, '', 15, 0, 0, 0, 1721865600, 20000000, 2000000, 6, -1, 0, 2048.29, -3335.68, 4.62677, 2049.93, -3335.57, 4.43146, 85.9312, 2056.22, -3341.82, 4.02226, 230.678, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(336, 0, '', 15, 0, 0, 0, 1722384000, 20000000, 2000000, 6, -1, 0, 2106.29, -3297.31, 4.02226, 2104.21, -3297.55, 4.02226, 271.59, 2100.41, -3292.41, 4.02226, 61.5265, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(337, 0, '', 15, 0, 0, 0, 1735862400, 20000000, 2000000, 6, -1, 0, 1963.17, -3137.38, 4.81892, 1965.04, -3136.73, 4.81892, 103.427, 1972.19, -3135.12, 4.02836, 267.741, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(338, 0, '', 15, 0, 0, 0, 1746057600, 20000000, 2000000, 6, -1, 0, 1957.5, -3267.1, 4.02836, 1959.2, -3267.03, 4.02836, 90.468, 1966.56, -3264.2, 4.02124, 273.723, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(339, 0, '', 15, 0, 0, 0, 1722470400, 20000000, 2000000, 6, -1, 0, 1929.85, -3359, 4.74569, 1930.75, -3359.74, 4.45071, 60.481, 1936.17, -3364.09, 4.01508, 244.037, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(340, 0, '', 15, 0, 0, 0, 1721347200, 20000000, 2000000, 6, -1, 0, 1988.93, -3499.67, 4.29856, 1988.77, -3498.25, 4.29856, 178.369, 1989.82, -3492.46, 4.02226, 347.223, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(341, 0, '', 15, 0, 0, 0, 1722124800, 20000000, 2000000, 6, -1, 0, 1973.11, -3431.88, 4.02226, 1972.96, -3433.3, 4.02226, 359.51, 1973.33, -3450.51, 4.02226, 179.39, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(342, 0, '', 15, 0, 0, 0, 1741651200, 20000000, 2000000, 6, -1, 0, 1894.83, -3513.27, 4.80525, 1895.09, -3511.61, 4.80525, 87.8622, 1898.98, -3492.61, 4.02662, 350.932, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(343, 0, '', 15, 0, 0, 0, 1750896000, 20000000, 2000000, 6, -1, 0, 1827.34, -3427.06, 4.74762, 1827.14, -3427.95, 4.74762, 351.671, 1821.51, -3435.94, 4.02662, 145.931, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(344, 0, '', 15, 0, 0, 0, 1721779200, 20000000, 2000000, 6, -1, 0, 1785.73, -3481.53, 4.02662, 1786.14, -3479.82, 4.02662, 160.07, 1792.62, -3469.34, 4.02662, 330.978, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(345, 0, '', 15, 0, 0, 0, 1721865600, 20000000, 2000000, 6, -1, 1, 1777.03, -3414.22, 4.85156, 1776.8, -3415.78, 4.85156, 344.29, 1763.85, -3413.55, 4.02662, 98.1324, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(346, 0, '', 15, 0, 0, 0, 1722556800, 20000000, 2000000, 6, -1, 0, 1702.75, -3457.09, 4.81892, 1703.5, -3455.47, 4.81892, 152.211, 1711.23, -3445.19, 4.02662, 316.957, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(347, 0, '', 15, 0, 0, 0, 1721692800, 20000000, 2000000, 6, -1, 0, 1644.32, -3396.39, 4.75493, 1644.86, -3395.51, 4.25493, 139.032, 1646.19, -3389.4, 4.02662, 338.718, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(348, 0, '', 15, 0, 0, 0, 1721952000, 20000000, 2000000, 6, -1, 0, 1637.82, -3296.52, 4.29856, 1637.24, -3298.1, 4.29856, 333.875, 1634.26, -3302.84, 4.02662, 153.647, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(349, 0, '', 15, 0, 0, 0, 1722297600, 20000000, 2000000, 6, -1, 1, 1560.03, -3350.27, 4.85156, 1561, -3349.1, 4.85156, 136.258, 1567.96, -3341.78, 4.02527, 319.922, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(350, 0, '', 15, 0, 0, 0, 1722470400, 20000000, 2000000, 6, -1, 0, 1523.65, -3247.26, 4.0187, 1522.89, -3248.87, 4.01909, 328.893, 1526.73, -3255.63, 4.02075, 191.929, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(351, 0, '', 15, 0, 0, 0, 1722470400, 20000000, 2000000, 6, -1, 0, 1482.89, -3291.41, 4.62677, 1483.74, -3290.16, 4.62677, 142.119, 1488.61, -3285.97, 4.02527, 316.378, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(352, 0, '', 15, 0, 0, 0, 1722297600, 20000000, 2000000, 6, -1, 0, 1419.95, -3245.07, 4.02527, 1420.75, -3243.83, 4.02527, 143.448, 1440.74, -3232.68, 4.02527, 319.329, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(353, 0, '', 15, 0, 0, 0, 1721779200, 20000000, 2000000, 6, -1, 0, 1366.08, -3200.99, 4.74569, 1366.72, -3200.06, 4.45071, 139.488, 1369.57, -3198.1, 4.02527, 313.964, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(354, 0, '', 15, 0, 0, 0, 1721606400, 20000000, 2000000, 6, -1, 0, 1538.52, -3124.7, 4.80525, 1537.57, -3123.97, 4.80525, 237.88, 1528.13, -3116.34, 4.00277, 52.4629, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(355, 0, '', 15, 0, 0, 0, 1722297600, 20000000, 2000000, 6, -1, 0, 1482.09, -3064.39, 4.85156, 1482.79, -3065.85, 4.85156, 52.8375, 1492.95, -3073.11, 4.00074, 237.906, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(356, 0, '', 15, 0, 0, 0, 1721692800, 20000000, 2000000, 6, -1, 0, 1563.63, -3012.61, 4.75493, 1564.14, -3014.03, 3.99569, 38.7342, 1563.9, -3022.15, 4.00277, 183.914, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(357, 0, '', 15, 0, 0, 0, 1722384000, 20000000, 2000000, 6, -1, 0, 1628.94, -3069.1, 4.81892, 1628.86, -3067.15, 4.81892, 177.761, 1628.58, -3056.64, 4.00009, 358.181, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(358, 0, '', 15, 0, 0, 0, 1722038400, 20000000, 2000000, 6, -1, 0, 1643.53, -2999.7, 4.00202, 1643.76, -3001.76, 4.00202, 1.72896, 1647.35, -3007.27, 4.00202, 198.064, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(359, 0, '', 15, 0, 0, 0, 1754870400, 20000000, 2000000, 6, -1, 0, 1720.68, -3039.74, 4.62677, 1719.23, -3040.63, 4.43146, 306.076, 1710.03, -3041.87, 4.00179, 100.444, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(360, 0, '', 15, 0, 0, 0, 1750032000, 20000000, 2000000, 6, -1, 0, 1742.86, -3131.5, 4.75493, 1742.33, -3130.95, 4.50493, 196.206, 1737.76, -3121.61, 4.00202, 30.4637, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(361, 0, '', 15, 0, 0, 0, 1722470400, 20000000, 2000000, 6, -1, 0, 2585.2, -3384.34, 4.81892, 2585.99, -3383.58, 4.81892, 122.911, 2593.91, -3377.82, 4.02036, 302.911, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(362, 0, '', 8, 0, 0, 0, 1750896000, 9000000, 900000, 4, -1, 0, 471.738, 1293.23, 5.37995, 471.307, 1290.96, 5.37995, 178.288, 461.478, 1286.85, 5.04271, 160.182, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(363, 0, '', 8, 0, 0, 0, 1744588800, 9000000, 900000, 4, -1, 0, 523.849, 1305.36, 5.62359, 524.083, 1304.47, 5.43609, 30.3317, 532.52, 1300.44, 4.90568, 301.905, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(364, 0, '', 8, 0, 0, 0, 1750032000, 9000000, 900000, 4, -1, 0, 536.101, 1275.03, 5.87911, 535.682, 1275.41, 5.87911, 211.733, 545.15, 1281.98, 5.04064, 299.187, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(365, 0, '', 8, 0, 0, 0, 1750032000, 9000000, 900000, 4, -1, 0, 562.177, 1338.2, 5.42772, 562.443, 1337.76, 5.42772, 40.0807, 560.687, 1333.81, 5.04621, 98.1791, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(366, 0, '', 8, 0, 0, 0, 1745020800, 9000000, 900000, 4, -1, 0, 612.205, 1311.37, 5.7804, 612.206, 1312.13, 5.17102, 187.824, 609.18, 1318.2, 5.04064, 17.4333, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(367, 0, '', 8, 0, 0, 0, 1745020800, 9000000, 900000, 4, -1, 0, 610.24, 1365.25, 5.87911, 610.954, 1364.74, 5.68262, 41.8887, 624.107, 1373.98, 5.04271, 245.659, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(368, 0, '', 15, 0, 0, 0, 1741478400, 9000000, 900000, 4, -1, 0, 644.615, 1403.48, 5.37995, 645.455, 1402.31, 5.37995, 33.8223, 647.349, 1395.53, 5.03491, 196.731, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(369, 0, '', 15, 0, 0, 0, 1722470400, 9000000, 900000, 4, -1, 0, 697.012, 1426.07, 5.41314, 697.87, 1424.92, 5.0412, 32.2989, 691.69, 1417.03, 5.0412, 131.968, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(370, 0, '', 15, 0, 0, 0, 1722556800, 9000000, 900000, 4, -1, 0, 701.148, 1380.1, 5.68165, 700.657, 1381.88, 5.22853, 189.459, 702.405, 1386.33, 5.04274, 344.584, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(371, 0, '', 15, 0, 0, 0, 1722211200, 9000000, 900000, 4, -1, 0, 745.168, 1401.54, 5.78704, 744.584, 1402.28, 5.17102, 211.679, 739.556, 1404.94, 5.04274, 70.3673, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(372, 0, '', 15, 0, 0, 0, 1739145600, 9000000, 900000, 4, -1, 0, 729.343, 1442.23, 5.68165, 730.156, 1440.98, 5.45509, 25.761, 738.277, 1442.84, 5.0412, 259.931, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(373, 0, '', 15, 0, 0, 0, 1721952000, 9000000, 900000, 4, -1, 0, 779.334, 1416.34, 5.45171, 778.133, 1416.27, 5.04274, 280.862, 769.421, 1420.84, 5.04274, 62.0418, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(374, 0, '', 15, 0, 0, 0, 1748390400, 9000000, 900000, 4, -1, 0, 777.384, 1469.6, 5.42772, 777.634, 1468.31, 5.04514, 22.6235, 772.626, 1462.08, 5.0412, 138.424, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(375, 0, '', 15, 0, 0, 0, 1721606400, 9000000, 900000, 4, -1, 1, 833.853, 1479.46, 5.37995, 833.657, 1478, 5.37995, 344.956, 821.403, 1471.73, 5.0412, 117.055, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(376, 0, '', 15, 0, 0, 0, 1722211200, 9000000, 900000, 4, -1, 0, 869.615, 1434.26, 5.7804, 869.006, 1433.99, 5.37415, 283.955, 864.038, 1431.73, 5.0412, 123.077, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(377, 0, '', 15, 0, 0, 0, 1721433600, 9000000, 900000, 4, -1, 0, 863.902, 1389.31, 5.68165, 863.083, 1389.7, 5.68738, 235.373, 853.48, 1384.76, 5.0412, 113.976, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(378, 0, '', 15, 0, 0, 0, 1722556800, 9000000, 900000, 4, -1, 0, 824.558, 1394.84, 5.37995, 825.667, 1393.81, 5.37995, 40.0058, 824.143, 1385.85, 5.04274, 179.132, 1606.23, -404.1, 1051, 0, 0, 0, 0, 0, 0),
(379, 0, '', 15, 0, 0, 0, 1722038400, 9000000, 900000, 4, -1, 1, 837.905, 1333.52, 5.41314, 836.473, 1333.94, 5.0412, 246.613, 833.105, 1339.4, 5.03431, 33.5226, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(380, 0, '', 15, 0, 0, 0, 1722470400, 9000000, 900000, 4, -1, 0, 798.908, 1349.96, 5.41314, 799.954, 1349.62, 5.04274, 68.3085, 801.101, 1340.99, 5.04274, 173.275, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(381, 0, '', 15, 0, 0, 0, 1734134400, 9000000, 900000, 4, -1, 0, 810.003, 1295.23, 5.62359, 810.245, 1296.05, 5.62359, 158.205, 798.036, 1301.24, 5.04064, 61.7792, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(382, 0, '', 15, 0, 0, 0, 1735257600, 9000000, 900000, 4, -1, 0, 760.776, 1345.35, 5.37995, 760.416, 1343.97, 5.37995, 2.5473, 754.128, 1341.09, 5.04274, 129.458, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(383, 0, '', 15, 0, 0, 0, 1721260800, 9000000, 900000, 4, -1, 0, 743.433, 1307.25, 5.78704, 743.407, 1308.26, 5.17102, 175.702, 741.138, 1314.01, 5.04064, 17.983, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(384, 0, '', 15, 0, 0, 0, 1722556800, 9000000, 900000, 4, -1, 0, 712.914, 1342.09, 5.87911, 713.127, 1341.18, 5.68262, 0.578783, 701.489, 1341.94, 5.04274, 79.3005, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(385, 0, '', 15, 0, 0, 0, 1721433600, 9000000, 900000, 4, -1, 0, 691.11, 1315.34, 5.41314, 691.424, 1316.58, 5.04064, 177.411, 696.337, 1318.71, 5.04064, 257.081, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(386, 0, '', 15, 0, 0, 0, 1734825600, 9000000, 900000, 4, -1, 0, 655.719, 1307.19, 5.62359, 655.897, 1307.62, 5.62359, 175.685, 650.448, 1312.25, 5.04064, 34.8289, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(387, 0, '', 15, 0, 0, 0, 1721433600, 9000000, 900000, 4, -1, 0, 670.511, 1344.39, 5.42772, 670.59, 1343.24, 5.04274, 1.16617, 667.571, 1342.87, 5.04274, 116.618, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(388, 0, '', 15, 0, 0, 0, 1741737600, 9000000, 900000, 4, -1, 0, 858.075, 1295.87, 5.7804, 857.487, 1295.58, 5.37415, 304.329, 856.628, 1292.71, 5.0412, 154.147, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(389, 0, '', 15, 0, 0, 0, 1748304000, 9000000, 900000, 4, -1, 0, 863.993, 1237.13, 5.87911, 862.962, 1237.18, 5.45724, 261.331, 859.322, 1224.86, 5.0412, 177.769, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(390, 0, '', 15, 0, 0, 0, 1741910400, 9000000, 900000, 4, -1, 0, 806.507, 1233.77, 5.38153, 806.477, 1232.8, 5.04064, 351.596, 803.292, 1229.93, 5.04064, 138.397, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(391, 0, '', 15, 0, 0, 0, 1756339200, 9000000, 900000, 4, -1, 0, 801.938, 1201.03, 5.87911, 802.078, 1201.45, 5.87911, 178.006, 804.012, 1204.98, 5.03996, 66.7459, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(392, 0, '', 15, 0, 0, 0, 1733184000, 9000000, 900000, 4, -1, 0, 781.982, 1242.48, 5.37995, 782.145, 1240.82, 5.37995, 0.961848, 781.565, 1237.41, 5.04064, 152.628, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(393, 0, '', 15, 0, 0, 0, 1722297600, 9000000, 900000, 4, -1, 0, 728.446, 1207.16, 5.62359, 728.336, 1208.22, 5.22817, 180.84, 729.092, 1215.15, 5.03996, 261.267, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(394, 0, '', 15, 0, 0, 0, 1721433600, 9000000, 900000, 4, -1, 0, 728.411, 1241.71, 5.68165, 728.676, 1240.11, 5.45509, 359.445, 728.254, 1240.25, 5.45509, 179.445, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(395, 0, '', 15, 0, 0, 0, 1722211200, 9000000, 900000, 4, -1, 0, 673.498, 1241.72, 5.42772, 673.68, 1240.67, 5.04064, 10.8119, 674.755, 1237.93, 5.04064, 190.812, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(396, 0, '', 15, 0, 0, 0, 1741651200, 9000000, 900000, 4, -1, 0, 664.973, 1196.08, 5.41314, 666.241, 1196.09, 5.03996, 92.4613, 668.89, 1193.91, 5.03996, 224.02, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(397, 0, '', 15, 0, 0, 0, 1753747200, 9000000, 900000, 4, -1, 0, 654.74, 1155.37, 5.7804, 655.474, 1155.39, 5.37415, 88.99, 658.362, 1156.2, 5.03996, 339.196, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(398, 0, '', 15, 0, 0, 0, 1721433600, 9000000, 900000, 4, -1, 0, 666.884, 1129.3, 5.68165, 667.659, 1130.51, 5.45509, 139.214, 669.56, 1132.26, 5.03996, 319.214, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(399, 0, '', 15, 0, 0, 0, 1750032000, 9000000, 900000, 4, -1, 0, 703.034, 1131.75, 5.87911, 702.576, 1132.67, 5.45724, 198.941, 700.648, 1136.88, 5.03214, 19.6011, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(400, 0, '', 15, 0, 0, 0, 1745020800, 9000000, 900000, 4, -1, 0, 720.005, 1157.37, 5.37995, 718.233, 1157.08, 5.37995, 275.954, 716.362, 1157.51, 5.18464, 68.4844, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(401, 0, '', 15, 0, 0, 0, 1734825600, 9000000, 900000, 4, -1, 0, 645.585, 1243.92, 5.68165, 645.491, 1242.77, 5.68738, 347.783, 643.48, 1241.3, 5.04064, 117.072, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(402, 0, '', 8, 0, 0, 0, 1738195200, 9000000, 900000, 4, -1, 0, 603.311, 1248.46, 5.37995, 603.027, 1247.2, 5.37995, 346.294, 601.458, 1245.25, 5.18464, 133.095, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(403, 0, '', 8, 0, 0, 0, 1741564800, 9000000, 900000, 4, -1, 0, 600.963, 1203.88, 5.62359, 599.671, 1204.01, 5.03996, 253.882, 597.587, 1191.23, 5.03996, 168.158, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(404, 0, '', 8, 0, 0, 0, 1733356800, 9000000, 900000, 4, -1, 0, 599.734, 1151.49, 5.42772, 599.018, 1151.42, 5.2246, 269.606, 597.369, 1154.49, 5.03996, 34.6791, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(405, 0, '', 8, 0, 0, 0, 1750982400, 9000000, 900000, 4, -1, 0, 551.278, 1144.57, 5.37995, 552.758, 1144.87, 5.37995, 98.9848, 557.778, 1144.42, 5.04271, 263.406, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(406, 0, '', 8, 0, 0, 0, 1743120000, 9000000, 900000, 4, -1, 0, 572.864, 1098.08, 5.87911, 573.735, 1098.36, 5.68262, 99.9674, 577.395, 1099.46, 5.04422, 269.362, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(407, 0, '', 8, 0, 0, 0, 1721433600, 9000000, 900000, 4, -1, 0, 617.25, 1103.34, 5.18657, 616.137, 1102.81, 5.03996, 296.086, 613.829, 1092.17, 5.04472, 164.527, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(408, 0, '', 7, 0, 0, 0, 1743120000, 9000000, 900000, 4, -1, 0, 596.434, 1053.06, 5.7804, 597.105, 1053.67, 5.17102, 128.38, 599.978, 1055.34, 5.04422, 310.206, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(409, 0, '', 7, 0, 0, 0, 1745020800, 9000000, 900000, 4, -1, 0, 648.792, 1073.81, 5.37995, 648.312, 1072.53, 5.37995, 331.463, 645.036, 1069.54, 5.03996, 139.993, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(410, 0, '', 7, 0, 0, 0, 1744156800, 9000000, 900000, 4, -1, 0, 625.472, 1028.73, 5.42772, 625.713, 1029.75, 5.04746, 160.013, 625.219, 1033.12, 4.54705, 147.978, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(411, 0, '', 7, 0, 0, 0, 1745020800, 9000000, 900000, 4, -1, 0, 688.056, 1017.36, 5.68165, 688.028, 1018.9, 5.45509, 170.376, 685.153, 1020.13, 5.04422, 61.518, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(412, 0, '', 7, 0, 0, 0, 1743120000, 9000000, 900000, 4, -1, 0, 723.703, 1020.85, 5.41314, 723.312, 1021.95, 5.04422, 194.846, 720.094, 1023.65, 5.04422, 72.0435, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(413, 0, '', 7, 0, 0, 0, 1721433600, 9000000, 900000, 4, -1, 1, 700.403, 1065.38, 5.62359, 700.69, 1064.57, 5.62359, 11.7268, 704.772, 1060.82, 5.03996, 165.242, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(414, 0, '', 7, 0, 0, 0, 1749945600, 9000000, 900000, 4, -1, 0, 770.403, 1051.17, 5.62359, 769.164, 1052.39, 5.04422, 211.303, 767.582, 1053.7, 5.04422, 48.9354, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(415, 0, '', 7, 0, 0, 0, 1743465600, 9000000, 900000, 4, -1, 0, 753.503, 1080.7, 5.68165, 754.478, 1079.77, 5.45509, 39.509, 758.484, 1079.08, 4.50518, 41.6155, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(416, 0, '', 7, 0, 0, 0, 1721865600, 9000000, 900000, 4, -1, 0, 803.301, 1077.76, 5.87911, 802.803, 1077.9, 5.87911, 230.329, 798.961, 1082.61, 4.5225, 251.38, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(417, 0, '', 15, 0, 0, 0, 1734998400, 9000000, 900000, 4, -1, 0, 788.503, 1123.13, 5.42772, 789.664, 1122.48, 5.04803, 57.7643, 793.365, 1120.58, 4.53889, 135.543, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(418, 0, '', 15, 0, 0, 0, 1721433600, 9000000, 900000, 4, -1, 0, 843.281, 1127.42, 5.7804, 842.567, 1127.73, 5.37415, 238.131, 841.242, 1129.78, 5.0369, 44.9306, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(419, 0, '', 15, 0, 0, 0, 1722470400, 9000000, 900000, 4, -1, 0, 801.282, 1163.1, 5.7804, 801.798, 1163.17, 5.57727, 75.8569, 805.034, 1162.15, 5.03996, 251.305, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(420, 0, '', 15, 0, 0, 0, 1722556800, 9000000, 900000, 4, -1, 0, 864.16, 1172.89, 5.37995, 862.639, 1173.4, 5.37995, 243.558, 855.544, 1176.42, 5.04422, 63.5584, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(421, 0, '', 15, 0, 0, 0, 1750291200, 13000000, 1300000, 5, -1, 0, 2614.63, 1767.44, 6.97437, 2614.74, 1769.65, 6.45875, 357.965, 2610.12, 1776.73, 2.58959, 344.178, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(422, 0, '', 15, 0, 0, 0, 1750032000, 9000000, 900000, 3, -1, 0, -2812.13, -670.441, 9.05513, -2812.21, -672.144, 9.05513, 181.684, -2811.65, -653.01, 8.05951, 69.3893, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(423, 0, '', 15, 0, 0, 0, 1743984000, 20000000, 2000000, 6, -1, 0, 6628, 10808.2, -96.729, 2330.6, 1542, 13.349, 2.86731, 2310.46, 1548.52, 11.2683, 40.0411, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(424, 0, '', 10, 0, 0, 0, 1750032000, 20000000, 2000000, 6, -1, 0, 1937.38, 2160.9, 15.6621, 1939.42, 2160.81, 15.7008, 270.558, 1947.29, 2167.84, 15.6843, 324.409, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(425, 0, '', 15, 0, 0, 0, 1722124800, 5000000, 500000, 1, -1, 0, 465.263, -1249.74, 41.8893, 466.367, -1245.89, 40.7311, 339.012, 460.36, -1248.76, 40.7907, 170.165, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(426, 0, '', 1, 0, 0, 0, 1703030400, 5000000, 500000, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(427, 0, '', 1, 0, 0, 0, 1702857600, 5000000, 500000, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(428, 0, '', 1, 0, 0, 0, 1721260800, 5000000, 500000, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(429, 0, '', 1, 0, 0, 0, 1703203200, 5000000, 500000, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(430, 0, '', 1, 0, 0, 0, 1703289600, 5000000, 500000, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(431, 0, '', 1, 0, 0, 0, 1721260800, 5000000, 500000, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(432, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(433, 0, '', 1, 0, 0, 0, 1702512000, 5000000, 500000, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(434, 0, '', 1, 0, 0, 0, 1702512000, 5000000, 500000, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(435, 0, '', 1, 0, 0, 0, 1703203200, 5000000, 500000, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(436, 0, '', 1, 0, 0, 0, 1703203200, 5000000, 500000, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(437, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(438, 0, '', 1, 0, 0, 0, 1702684800, 5000000, 500000, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(439, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(440, 0, '', 1, 0, 0, 0, 1701820800, 5000000, 500000, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(441, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(442, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(443, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(444, 0, '', 1, 0, 0, 0, 1701734400, 5000000, 500000, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(445, 0, '', 1, 0, 0, 0, 1701907200, 5000000, 500000, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(446, 0, '', 1, 0, 0, 0, 1703376000, 5000000, 500000, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(447, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(448, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(449, 0, '', 1, 0, 0, 0, 1702425600, 5000000, 500000, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(450, 0, '', 1, 0, 0, 0, 1701216000, 5000000, 500000, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(451, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(452, 0, '', 1, 0, 0, 0, 1702512000, 5000000, 500000, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(453, 0, '', 1, 0, 0, 0, 1701043200, 5000000, 500000, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(454, 0, '', 1, 0, 0, 0, 1703203200, 5000000, 500000, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(455, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(456, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(457, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(458, 0, '', 1, 0, 0, 0, 1700006400, 5000000, 500000, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(459, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(460, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(461, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(462, 0, '', 1, 0, 0, 0, 1700265600, 5000000, 500000, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(463, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(464, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(465, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(466, 0, '', 1, 0, 0, 0, 1703203200, 5000000, 500000, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(467, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(468, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(469, 0, '', 1, 0, 0, 0, 1702684800, 5000000, 500000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(470, 0, '', 1, 0, 0, 0, 1702512000, 5000000, 500000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(471, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(472, 0, '', 1, 0, 0, 0, 1702944000, 5000000, 500000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(473, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(474, 0, '', 1, 0, 0, 0, 1700006400, 5000000, 500000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(475, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(476, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(477, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(478, 0, '', 1, 0, 0, 0, 1700956800, 5000000, 500000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(479, 0, '', 1, 0, 0, 0, 1702684800, 5000000, 500000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(480, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(481, 0, '', 1, 0, 0, 0, 1700784000, 5000000, 500000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(482, 0, '', 1, 0, 0, 0, 1701043200, 5000000, 500000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(483, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(484, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(485, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(486, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(487, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(488, 0, '', 1, 0, 0, 0, 1701561600, 5000000, 500000, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(489, 0, '', 1, 0, 0, 0, 1703203200, 5000000, 500000, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(490, 0, '', 1, 0, 0, 0, 1703894400, 5000000, 500000, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(491, 0, '', 1, 0, 0, 0, 1703116800, 5000000, 500000, 1, 8, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(492, 0, '', 1, 0, 0, 0, 1703376000, 5000000, 500000, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(493, 0, '', 1, 0, 0, 0, 1703548800, 5000000, 500000, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(494, 0, '', 1, 0, 0, 0, 1703721600, 5000000, 500000, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(495, 0, '', 1, 0, 0, 0, 1703289600, 5000000, 500000, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(496, 0, '', 1, 0, 0, 0, 1703289600, 5000000, 500000, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(497, 0, '', 1, 0, 0, 0, 1703203200, 5000000, 500000, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(498, 0, '', 1, 0, 0, 0, 1703116800, 5000000, 500000, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(499, 0, '', 1, 0, 0, 0, 1702944000, 5000000, 500000, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(500, 0, '', 1, 0, 0, 0, 1703116800, 5000000, 500000, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(501, 0, '', 1, 0, 0, 0, 1703808000, 5000000, 500000, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(502, 0, '', 1, 0, 0, 0, 1702944000, 5000000, 500000, 1, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(503, 0, '', 1, 0, 0, 0, 1703894400, 5000000, 500000, 1, 7, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(504, 0, '', 1, 0, 0, 0, 1703721600, 5000000, 500000, 1, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(505, 0, '', 1, 0, 0, 0, 1702598400, 5000000, 500000, 1, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(506, 0, '', 1, 0, 0, 0, 1702598400, 5000000, 500000, 1, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(507, 0, '', 1, 0, 0, 0, 1702684800, 5000000, 500000, 1, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(508, 0, '', 1, 0, 0, 0, 1703116800, 5000000, 500000, 1, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(509, 0, '', 1, 0, 0, 0, 1702598400, 5000000, 500000, 1, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(510, 0, '', 1, 0, 0, 0, 1702512000, 5000000, 500000, 1, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(511, 0, '', 1, 0, 0, 0, 1703116800, 5000000, 500000, 1, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(512, 0, '', 1, 0, 0, 0, 1700352000, 5000000, 500000, 1, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(513, 0, '', 1, 0, 0, 0, 1700179200, 5000000, 500000, 1, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(514, 0, '', 1, 0, 0, 0, 1701216000, 5000000, 500000, 1, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(515, 0, '', 1, 0, 0, 0, 1701648000, 5000000, 500000, 1, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(516, 0, '', 1, 0, 0, 0, 1702684800, 5000000, 500000, 1, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(517, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(518, 0, '', 1, 0, 0, 0, 1702944000, 5000000, 500000, 1, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(519, 0, '', 1, 0, 0, 0, 1703116800, 5000000, 500000, 1, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(520, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(521, 0, '', 1, 0, 0, 0, 1701475200, 5000000, 500000, 1, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(522, 0, '', 1, 0, 0, 0, 1703289600, 5000000, 500000, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(523, 0, '', 1, 0, 0, 0, 1702857600, 5000000, 500000, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(524, 0, '', 1, 0, 0, 0, 1702512000, 5000000, 500000, 1, 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(525, 0, '', 1, 0, 0, 0, 1702857600, 5000000, 500000, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(526, 0, '', 1, 0, 0, 0, 1702684800, 5000000, 500000, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(527, 0, '', 1, 0, 0, 0, 1703116800, 5000000, 500000, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(528, 0, '', 1, 0, 0, 0, 1702684800, 5000000, 500000, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(529, 0, '', 1, 0, 0, 0, 1702512000, 5000000, 500000, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(530, 0, '', 1, 0, 0, 0, 1703203200, 5000000, 500000, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(531, 0, '', 1, 0, 0, 0, 1703030400, 5000000, 500000, 1, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(532, 0, '', 1, 0, 0, 0, 1700352000, 5000000, 500000, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(533, 0, '', 1, 0, 0, 0, 1701561600, 5000000, 500000, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(534, 0, '', 1, 0, 0, 0, 1702771200, 5000000, 500000, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(535, 0, '', 1, 0, 0, 0, 1702598400, 5000000, 500000, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(536, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(537, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(538, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(539, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(540, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(541, 0, '', 1, 0, 0, 0, 1703116800, 5000000, 500000, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(542, 0, '', 1, 0, 0, 0, 1699920000, 5000000, 500000, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(543, 0, '', 1, 0, 0, 0, 1701388800, 5000000, 500000, 1, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(544, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(545, 0, '', 1, 0, 0, 0, 1703116800, 5000000, 500000, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(546, 0, '', 1, 0, 0, 0, 1702857600, 5000000, 500000, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(547, 0, '', 1, 0, 0, 0, 1702771200, 5000000, 500000, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(548, 0, '', 1, 0, 0, 0, 1701907200, 5000000, 500000, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(549, 0, '', 1, 0, 0, 0, 1701993600, 5000000, 500000, 1, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(550, 0, '', 1, 0, 0, 0, 1703203200, 5000000, 500000, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(551, 0, '', 1, 0, 0, 0, 1703116800, 5000000, 500000, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(552, 0, '', 1, 0, 0, 0, 1702857600, 5000000, 500000, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(553, 0, '', 1, 0, 0, 0, 1702944000, 5000000, 500000, 1, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(554, 0, '', 1, 0, 0, 0, 1701648000, 5000000, 500000, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(555, 0, '', 1, 0, 0, 0, 1701907200, 5000000, 500000, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(556, 0, '', 1, 0, 0, 0, 1701734400, 5000000, 500000, 1, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(557, 0, '', 1, 0, 0, 0, 1702425600, 5000000, 500000, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(558, 0, '', 1, 0, 0, 0, 1701216000, 5000000, 500000, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(559, 0, '', 1, 0, 0, 0, 1702857600, 5000000, 500000, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(560, 0, '', 1, 0, 0, 0, 1700352000, 5000000, 500000, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(561, 0, '', 1, 0, 0, 0, 1700006400, 5000000, 500000, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(562, 0, '', 1, 0, 0, 0, 1702857600, 5000000, 500000, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(563, 0, '', 1, 0, 0, 0, 1702080000, 5000000, 500000, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(564, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(565, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(566, 0, '', 1, 0, 0, 0, 1702166400, 5000000, 500000, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(567, 0, '', 1, 0, 0, 0, 1702857600, 5000000, 500000, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(568, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(569, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(570, 0, '', 1, 0, 0, 0, 1701648000, 5000000, 500000, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(571, 0, '', 1, 0, 0, 0, 1702252800, 5000000, 500000, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(572, 0, '', 1, 0, 0, 0, 1702425600, 5000000, 500000, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(573, 0, '', 1, 0, 0, 0, 1699833600, 5000000, 500000, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(574, 0, '', 1, 0, 0, 0, 1701820800, 5000000, 500000, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(575, 0, '', 1, 0, 0, 0, 1701129600, 5000000, 500000, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(576, 0, '', 1, 0, 0, 0, 1701129600, 5000000, 500000, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(577, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(578, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(579, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(580, 0, '', 1, 0, 0, 0, 1698969600, 5000000, 500000, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(581, 0, '', 1, 0, 0, 0, 1702857600, 5000000, 500000, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(582, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(583, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(584, 0, '', 1, 0, 0, 0, 1702598400, 5000000, 500000, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(585, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(586, 0, '', 1, 0, 0, 0, 1699920000, 5000000, 500000, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(587, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
INSERT INTO `houses` (`id`, `owner_id`, `name`, `city`, `zone`, `miami`, `improvements`, `rent_time`, `price`, `rent_price`, `type`, `entrance`, `lock`, `x`, `y`, `z`, `exit_x`, `exit_y`, `exit_z`, `exit_angle`, `car_x`, `car_y`, `car_z`, `car_angle`, `store_x`, `store_y`, `store_z`, `eviction`, `store_metall`, `store_drugs`, `store_weapon`, `store_ammo`, `store_skin`) VALUES
(588, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(589, 0, '', 1, 0, 0, 0, 1702857600, 5000000, 500000, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(590, 0, '', 1, 0, 0, 0, 1702080000, 5000000, 500000, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(591, 0, '', 1, 0, 0, 0, 1701388800, 5000000, 500000, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(592, 0, '', 1, 0, 0, 0, 1700784000, 5000000, 500000, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(593, 0, '', 1, 0, 0, 0, 1700697600, 5000000, 500000, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(594, 0, '', 1, 0, 0, 0, 1702080000, 5000000, 500000, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(595, 0, '', 1, 0, 0, 0, 1700524800, 5000000, 500000, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(596, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(597, 0, '', 1, 0, 0, 0, 1701820800, 5000000, 500000, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(598, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(599, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(600, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(601, 0, '', 1, 0, 0, 0, 1702684800, 5000000, 500000, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(602, 0, '', 1, 0, 0, 0, 1702598400, 5000000, 500000, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(603, 0, '', 1, 0, 0, 0, 1702080000, 5000000, 500000, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(604, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(605, 0, '', 1, 0, 0, 0, 1700006400, 5000000, 500000, 1, 10, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(606, 0, '', 1, 0, 0, 0, 1701993600, 5000000, 500000, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(607, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(608, 0, '', 1, 0, 0, 0, 1699315200, 5000000, 500000, 1, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(609, 0, '', 1, 0, 0, 0, 1703289600, 5000000, 500000, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(610, 0, '', 1, 0, 0, 0, 1703376000, 5000000, 500000, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(611, 0, '', 1, 0, 0, 0, 1703376000, 5000000, 500000, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(612, 0, '', 1, 0, 0, 0, 1703289600, 5000000, 500000, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(613, 0, '', 1, 0, 0, 0, 1703289600, 5000000, 500000, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(614, 0, '', 1, 0, 0, 0, 1702684800, 5000000, 500000, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(615, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(616, 0, '', 1, 0, 0, 0, 1702166400, 5000000, 500000, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(617, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(618, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(619, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(620, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(621, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(622, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(623, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(624, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(625, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(626, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(627, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(628, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(629, 0, '', 1, 0, 0, 0, 1703116800, 5000000, 500000, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(630, 0, '', 1, 0, 0, 0, 1702857600, 5000000, 500000, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(631, 0, '', 1, 0, 0, 0, 1702857600, 5000000, 500000, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(632, 0, '', 1, 0, 0, 0, 1703289600, 5000000, 500000, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(633, 0, '', 1, 0, 0, 0, 1703289600, 5000000, 500000, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(634, 0, '', 1, 0, 0, 0, 1703203200, 5000000, 500000, 1, 8, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(635, 0, '', 1, 0, 0, 0, 1703289600, 5000000, 500000, 1, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(636, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(637, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(638, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(639, 0, '', 1, 0, 0, 0, 1699228800, 5000000, 500000, 1, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(640, 0, '', 1, 0, 0, 0, 1701388800, 5000000, 500000, 1, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(641, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(642, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(643, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(644, 0, '', 1, 0, 0, 0, 1701907200, 5000000, 500000, 1, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(645, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(646, 0, '', 1, 0, 0, 0, 1701907200, 5000000, 500000, 1, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(647, 0, '', 1, 0, 0, 0, 1701648000, 5000000, 500000, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(648, 0, '', 1, 0, 0, 0, 1703116800, 5000000, 500000, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(649, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(650, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(651, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(652, 0, '', 1, 0, 0, 0, 1702771200, 5000000, 500000, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(653, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(654, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(655, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(656, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(657, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(658, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(659, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(660, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(661, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(662, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(663, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(664, 0, '', 1, 0, 0, 0, 1702252800, 5000000, 500000, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(665, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(666, 0, '', 1, 0, 0, 0, 1701302400, 5000000, 500000, 1, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(667, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(668, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(669, 0, '', 1, 0, 0, 0, 1700438400, 5000000, 500000, 1, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(670, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(671, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(672, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(673, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(674, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(675, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(676, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(677, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(678, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(679, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(680, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(681, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(682, 0, '', 1, 0, 0, 0, 1702684800, 5000000, 500000, 1, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(683, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(684, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(685, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(686, 0, '', 1, 0, 0, 0, 1698537600, 5000000, 500000, 1, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(687, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(688, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(689, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(690, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(691, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(692, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(693, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(694, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(695, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(696, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(697, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(698, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(699, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(700, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(701, 0, '', 1, 0, 0, 0, 1698537600, 5000000, 500000, 1, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(702, 0, '', 1, 0, 0, 0, 1700784000, 5000000, 500000, 1, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(703, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(704, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(705, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(706, 0, '', 1, 0, 0, 0, 1700784000, 5000000, 500000, 1, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(707, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(708, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(709, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(710, 0, '', 1, 0, 0, 0, 1702684800, 5000000, 500000, 1, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(711, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(712, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(713, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(714, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(715, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(716, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(717, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(718, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(719, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(720, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(721, 0, '', 1, 0, 0, 0, 1700956800, 5000000, 500000, 1, 14, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(722, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(723, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(724, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(725, 0, '', 1, 0, 0, 0, 1701907200, 5000000, 500000, 1, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(726, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(727, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(728, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(729, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(730, 0, '', 1, 0, 0, 0, 1702339200, 5000000, 500000, 1, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(731, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(732, 0, '', 1, 0, 0, 0, 1700956800, 5000000, 500000, 1, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(733, 0, '', 1, 0, 0, 0, 0, 5000000, 500000, 1, 13, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(734, 0, '', 1, 0, 0, 0, 1750291200, 5000000, 500000, 1, -1, 0, 1912, 2266.13, 15.9241, 1912.1, 2264.64, 15.7637, 180.293, 1896.67, 2274.35, 15.8344, 87.8596, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(735, 0, '', 15, 0, 0, 0, 1734307200, 13000000, 1300000, 5, -1, 0, 2399.32, -2219.19, 22.2696, 2400.08, -2219.31, 22.2696, 266.379, 2408.36, -2222.27, 21.971, 210.46, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(736, 0, '', 15, 0, 0, 0, 1733616000, 13000000, 1300000, 5, -1, 0, 1894.87, 1186.52, 30.3239, 1892.85, 1187.32, 30.3239, 85.5871, 1886.53, 1182.71, 29.8425, 4.14908, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(737, 0, '', 15, 0, 0, 0, 1733616000, 13000000, 1300000, 5, -1, 0, 1879.92, 1170.9, 30.0086, 1879.83, 1168.91, 30.0101, 183.685, 1874.11, 1179.76, 30.0702, 220.658, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(738, 0, '', 7, 0, 0, 0, 1734998400, 666666666, 6666, 6, -1, 0, -286.827, 577.717, 12.8447, -286.589, 581.46, 12.114, 352.978, -286.589, 581.46, 12.114, 352.978, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(739, 0, '', 15, 0, 0, 0, 1736726400, 666666666, 666666, 6, -1, 0, -508.566, 854.29, 14.9199, -508.652, 855.886, 14.9199, 357.638, -508.148, 869.197, 12.5039, 355.444, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(740, 0, '', 15, 0, 0, 0, 1733011200, 1500000000, 50000, 6, -1, 0, -2887.89, 2170.18, 2.79494, -2886.38, 2169.12, 2.79494, 227.376, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(741, 0, '', 15, 0, 0, 0, 1733356800, 5000000, 10000, 1, -1, 0, -771.794, -1649.21, 42.8307, -771.756, -1649.14, 42.8304, 236.378, -772.941, -1661.9, 42.622, 234.54, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(742, 0, '', 15, 0, 0, 0, 0, 5000000, 10000, 1, -1, 0, -781.971, -1625.55, 42.8624, -781.971, -1625.55, 42.8624, 149.062, -786.298, -1622.15, 42.5391, 143.777, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(743, 0, '', 15, 0, 0, 0, 0, 5000000, 10000, 1, -1, 0, -779.841, -1601.02, 42.3631, -779.841, -1601.02, 42.3631, 145.286, -773.69, -1599.03, 41.8486, 225.939, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(744, 0, '', 15, 0, 0, 0, 0, 5000000, 10000, 1, -1, 0, -836.385, -1617.99, 42.9026, -836.385, -1617.99, 42.9026, 240.875, -820.787, -1603.76, 42.5952, 324.745, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(745, 0, '', 15, 0, 0, 0, 0, 5000000, 10000, 1, -1, 0, -815.689, -1633.88, 43.0601, -815.689, -1633.88, 43.0601, 52.9803, -811.424, -1639.71, 42.5283, 147.879, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(746, 0, '', 15, 0, 0, 0, 0, 5000000, 10000, 1, -1, 0, -802.417, -1677.04, 41.5496, -802.417, -1677.04, 41.5496, 142.004, -813.658, -1671.65, 40.8888, 131.894, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(747, 0, '', 15, 0, 0, 0, 1735084800, 5000000, 10000, 1, -1, 0, -833.365, -1655.32, 41.7025, -833.365, -1655.32, 41.7025, 240.58, -853.636, -1651.18, 41.0761, 153.328, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(748, 0, '', 15, 0, 0, 0, 1745539200, 5000000, 10000, 1, -1, 0, -873.677, -1583.38, 42.6736, -873.677, -1583.38, 42.6736, 52.2253, -852.433, -1590.78, 42.2748, 217.831, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(749, 0, '', 15, 0, 0, 0, 0, 5000000, 10000, 1, -1, 0, -857.022, -1550.09, 42.1611, -857.022, -1550.09, 42.1611, 235.295, -861.76, -1553.39, 41.6694, 225.414, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(750, 0, '', 15, 0, 0, 0, 1733443200, 5000000, 10000, 1, -1, 0, -832.829, -1541.36, 42.0578, -832.829, -1541.36, 42.0578, 317.326, -821.881, -1543.96, 41.8547, 315.488, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(751, 0, '', 15, 0, 0, 0, 1733529600, 5000000, 10000, 1, -1, 0, -799.079, -1563.72, 42.9756, -799.09, -1563.71, 42.9756, 330.589, -793.002, -1561.96, 42.2849, 325.074, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(752, 0, '', 15, 0, 0, 0, 0, 5000000, 10000, 1, -1, 0, -791.319, -1579.23, 42.482, -791.319, -1579.23, 42.482, 235, -771.813, -1587.07, 41.9715, 237.528, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(753, 0, '', 15, 0, 0, 0, 0, 5000000, 10000, 1, -1, 0, -768.841, -1428.32, 41.2488, -768.841, -1428.32, 41.2488, 127.364, -761.092, -1427.01, 40.7099, 41.2615, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(754, 0, '', 15, 0, 0, 0, 0, 5000000, 10000, 1, -1, 0, -752.244, -1407.68, 40.8216, -752.244, -1407.68, 40.8216, 40.5723, -754.566, -1413.69, 40.5659, 129.727, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(755, 0, '', 15, 0, 0, 0, 0, 5000000, 10000, 1, -1, 0, -708.953, -1380.62, 40.5985, -708.953, -1380.62, 40.5985, 31.1513, -702.781, -1388.84, 40.3712, 226.456, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(757, 0, '', 15, 0, 0, 0, 1733529600, 1500000000, 5000000, 4, -1, 0, 1.11182, -1552.16, 41.9425, -1.95831, -1555.13, 39.3998, 88.9009, -4.05044, -1546.44, 39.3351, 359.934, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(756, 0, '', 15, 0, 0, 0, 1734998400, 5000000, 10000, 1, -1, 0, -256.86, -1774.36, 41.287, -256.85, -1774.29, 41.2872, 79.0551, -256.668, -1762.19, 40.6801, 54.6985, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(758, 0, '', 15, 0, 0, 0, 1740787200, 250000000, 250000, 1, -1, 0, -478.896, -2044.86, 41.2387, -478.437, -2043.42, 41.2409, 343.108, -471.754, -2034.18, 41.3095, 85.7135, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(759, 0, '', 1, 0, 0, 0, 0, 10000000, 55000, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(760, 0, '', 1, 0, 0, 0, 0, 10000000, 55000, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(761, 0, '', 1, 0, 0, 0, 0, 10000000, 55000, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(762, 0, '', 1, 0, 0, 0, 0, 10000000, 55000, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(763, 0, '', 1, 0, 0, 0, 0, 10000000, 55000, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(764, 0, '', 1, 0, 0, 0, 0, 10000000, 55000, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(765, 0, '', 1, 0, 0, 0, 0, 10000000, 55000, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(766, 0, '', 1, 0, 0, 0, 0, 10000000, 55000, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(767, 0, '', 1, 0, 0, 0, 0, 10000000, 55000, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(768, 0, '', 1, 0, 0, 0, 0, 10000000, 55000, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(769, 0, '', 1, 0, 0, 0, 0, 10000000, 55000, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(770, 0, '', 1, 0, 0, 0, 0, 10000000, 55000, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Структура таблицы `houses_renters`
--

CREATE TABLE `houses_renters` (
  `id` int(11) NOT NULL,
  `owner_id` int(11) NOT NULL,
  `house_id` int(11) NOT NULL,
  `room_id` int(11) NOT NULL,
  `rent_time` int(11) NOT NULL,
  `time` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `items`
--

CREATE TABLE `items` (
  `id` int(11) NOT NULL,
  `get_id` int(11) NOT NULL,
  `owner_id` int(11) NOT NULL,
  `return_items` int(11) NOT NULL,
  `type` int(11) NOT NULL,
  `slots` int(11) NOT NULL DEFAULT -1,
  `item` int(11) NOT NULL,
  `count` int(11) NOT NULL,
  `number` varchar(32) NOT NULL,
  `region` varchar(32) NOT NULL,
  `typenumber` int(11) NOT NULL,
  `aks_id` int(11) NOT NULL,
  `typeacs` int(11) NOT NULL,
  `status` int(11) NOT NULL DEFAULT 0,
  `indx` int(11) NOT NULL,
  `foffset_x` float NOT NULL,
  `foffset_y` float NOT NULL,
  `foffset_z` float NOT NULL,
  `frot_x` float NOT NULL,
  `frot_y` float NOT NULL,
  `frot_z` float NOT NULL,
  `fscale_x` float NOT NULL,
  `fscale_y` float NOT NULL,
  `fscale_z` float NOT NULL,
  `skin_id` int(11) NOT NULL,
  `skin_iznos` int(11) NOT NULL,
  `shelf` int(11) NOT NULL DEFAULT -1,
  `sklad` int(11) NOT NULL DEFAULT -1,
  `car_id` int(11) NOT NULL DEFAULT 0,
  `bag` int(11) NOT NULL DEFAULT 0,
  `type_item` int(11) NOT NULL DEFAULT 0,
  `weapon` int(11) NOT NULL DEFAULT 0,
  `patron` int(11) NOT NULL DEFAULT 0,
  `slot_weapon` int(11) NOT NULL,
  `plate` int(11) NOT NULL DEFAULT -1,
  `skin_active` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `items_log`
--

CREATE TABLE `items_log` (
  `id` int(11) NOT NULL,
  `owner_id` int(11) NOT NULL,
  `items_text` varchar(94) NOT NULL,
  `text` varchar(150) NOT NULL,
  `time` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `jobs_player`
--

CREATE TABLE `jobs_player` (
  `id` int(11) NOT NULL,
  `uid` int(11) NOT NULL,
  `jobs` varchar(32) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `kiosk`
--

CREATE TABLE `kiosk` (
  `id` int(11) NOT NULL,
  `owner_id` int(11) NOT NULL,
  `name` varchar(33) NOT NULL DEFAULT 'Киоск',
  `improvements` int(11) NOT NULL DEFAULT 1,
  `rent_time` int(11) NOT NULL,
  `balance` int(11) NOT NULL,
  `lock` int(11) NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `rent_price` int(11) NOT NULL,
  `rent` int(11) NOT NULL,
  `min_price` int(11) NOT NULL,
  `price` int(11) NOT NULL DEFAULT 300000,
  `nalog` int(11) NOT NULL DEFAULT 1,
  `day` int(11) NOT NULL,
  `month` int(11) NOT NULL,
  `year` int(11) NOT NULL,
  `inter` int(11) NOT NULL,
  `x_inter` float NOT NULL,
  `y_inter` float NOT NULL,
  `angel_inter` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Дамп данных таблицы `kiosk`
--

INSERT INTO `kiosk` (`id`, `owner_id`, `name`, `improvements`, `rent_time`, `balance`, `lock`, `x`, `y`, `z`, `rent_price`, `rent`, `min_price`, `price`, `nalog`, `day`, `month`, `year`, `inter`, `x_inter`, `y_inter`, `angel_inter`) VALUES
(0, 0, 'Киоск', 1, 0, 0, 0, 1134, 2782, 1001, 12500, 0, 500, 500000, 1, 19, 7, 2024, 15932, 1131.59, 2785.19, 180),
(1, 0, 'Киоск', 1, 0, 0, 0, 1120.65, 2781.93, 1000.98, 12500, 0, 5000000, 500000, 25, 15, 7, 2024, 15931, 1118.29, 2785.2, 180),
(2, 0, 'Киоск', 1, 0, 0, 0, 1094, 2787, 1001, 12500, 0, 10000, 500000, 8, 14, 7, 2024, 15931, 1091.67, 2790.83, -180),
(3, 0, 'Киоск', 1, 0, 0, 0, 1072.53, 2785.4, 1000.98, 12500, 0, 1000000, 500000, 1, 18, 7, 2024, 15931, 1070.25, 2788.84, 180),
(4, 0, 'Киоск', 1, 0, 0, 0, 1060, 2785, 1001, 12500, 0, 3333333, 500000, 4, 9, 3, 2025, 15931, 1057.66, 2788.83, 180),
(5, 0, 'Киоск', 1, 0, 0, 0, 1039, 2787, 1001, 12500, 0, 1500000, 500000, 3, 10, 8, 2025, 15931, 1036.78, 2790.84, 180),
(6, 0, 'Киоск', 1, 0, 0, 0, 965.612, 2787.12, 1000.98, 12500, 0, 1000000, 500000, 5, 14, 12, 2024, 15931, 963.204, 2790.84, 180),
(7, 0, 'Киоск', 1, 0, 0, 0, 944.665, 2785.37, 1000.98, 12500, 0, 500, 500000, 1, 19, 7, 2024, 15933, 942.308, 2788.84, -180),
(8, 0, 'Киоск', 1, 0, 0, 0, 932, 2785, 1001, 12500, 0, 1000000, 500000, 14, 7, 7, 2024, 15931, 929.72, 2788.84, 180),
(9, 0, 'Киоск', 1, 0, 0, 0, 911, 2787, 1001, 12500, 0, 500000, 500000, 25, 16, 7, 2024, 15932, 908.302, 2790.84, 180),
(10, 0, 'Киоск', 1, 0, 0, 0, 884, 2782, 1001, 12500, 0, 1000000, 500000, 25, 18, 7, 2024, 15932, 881.673, 2785.18, 180),
(11, 0, 'Киоск', 1, 0, 0, 0, 871, 2782, 1001, 12500, 0, 1500000, 500000, 5, 18, 7, 2024, 15931, 868.378, 2785.19, -180),
(12, 0, 'Киоск', 1, 0, 0, 0, 866, 2819, 1001, 12500, 0, 1000000, 500000, 5, 3, 7, 2024, 15931, 868.406, 2815.43, 0),
(13, 0, 'Киоск', 1, 0, 0, 0, 879, 2819, 1001, 12500, 0, 2555555, 500000, 25, 12, 7, 2024, 15932, 881.699, 2815.44, 0),
(14, 0, 'Киоск', 1, 0, 0, 0, 906, 2813, 1001, 12500, 0, 50000, 500000, 25, 30, 6, 2024, 15931, 908.321, 2809.72, 0),
(15, 0, 'Киоск', 1, 0, 0, 0, 927, 2815, 1001, 12500, 0, 500000, 500000, 25, 15, 7, 2024, 15932, 929.754, 2811.9, 0),
(16, 0, 'Киоск', 1, 0, 0, 0, 940, 2815, 1001, 12500, 0, 1000000, 500000, 1, 24, 12, 2024, 15932, 942.348, 2811.9, 0),
(17, 0, 'Киоск', 1, 0, 0, 0, 961, 2813, 1001, 12500, 0, 1000000, 500000, 25, 29, 3, 2025, 15931, 963.236, 2809.75, 0),
(18, 0, 'Киоск', 1, 0, 0, 0, 1034.53, 2813.13, 1000.99, 12500, 0, 444444, 500000, 19, 1, 12, 2024, 15931, 1036.8, 2809.75, 0),
(19, 0, 'Киоск', 1, 0, 0, 0, 1055.4, 2815.36, 1000.98, 12500, 0, 10000, 500000, 1, 23, 12, 2024, 15931, 1057.69, 2811.89, 0),
(20, 0, 'Киоск', 1, 0, 0, 0, 1068, 2815, 1001, 12500, 0, 5000000, 500000, 25, 17, 7, 2024, 15933, 1070.28, 2811.89, 0),
(21, 0, 'Киоск', 1, 0, 0, 0, 1089.34, 2813.19, 1000.98, 12500, 0, 11111, 500000, 10, 13, 3, 2025, 15931, 1091.7, 2809.74, 0),
(22, 0, 'Киоск', 1, 0, 0, 0, 1116, 2819, 1001, 12500, 0, 1111111, 500000, 2, 19, 7, 2024, 15932, 1118.34, 2815.44, 0),
(23, 0, 'Киоск', 1, 0, 0, 0, 1129, 2819, 1001, 12500, 0, 1000000, 500000, 25, 11, 7, 2024, 15931, 1131.62, 2815.43, 0);

-- --------------------------------------------------------

--
-- Структура таблицы `kiosks_items`
--

CREATE TABLE `kiosks_items` (
  `id` int(11) NOT NULL,
  `kiosk_id` int(11) NOT NULL DEFAULT -1,
  `item_id` int(11) NOT NULL,
  `owner_id` int(11) NOT NULL,
  `name` varchar(32) NOT NULL,
  `count` int(11) NOT NULL,
  `price` int(11) NOT NULL,
  `number` varchar(32) NOT NULL,
  `region` varchar(32) NOT NULL,
  `typenumber` int(11) NOT NULL,
  `aks_id` int(11) NOT NULL,
  `typeacs` int(11) NOT NULL,
  `indx` int(11) NOT NULL,
  `skin_id` int(11) NOT NULL,
  `item_type` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `localban`
--

CREATE TABLE `localban` (
  `id` int(11) NOT NULL,
  `mid` int(11) NOT NULL,
  `by` varchar(111) NOT NULL,
  `dtime` varchar(111) NOT NULL,
  `reason` varchar(222) NOT NULL,
  `lid` int(111) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_unicode_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `marktplc`
--

CREATE TABLE `marktplc` (
  `id` int(11) NOT NULL,
  `owner_id` int(11) NOT NULL,
  `owner_name` varchar(32) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `owner_phone` int(11) NOT NULL,
  `r_name` varchar(32) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `type` int(11) NOT NULL,
  `category` int(11) NOT NULL,
  `updates` int(11) NOT NULL,
  `money` int(11) NOT NULL,
  `p_name` varchar(48) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `description` varchar(124) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `items` int(11) NOT NULL,
  `likes` int(11) NOT NULL,
  `views` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `money_log`
--

CREATE TABLE `money_log` (
  `id` int(11) NOT NULL,
  `uid` int(11) NOT NULL,
  `uip` varchar(16) NOT NULL DEFAULT '255.255.255.255',
  `time` datetime NOT NULL,
  `money` varchar(21) NOT NULL DEFAULT '0',
  `last_money` varchar(21) NOT NULL DEFAULT '-1',
  `description` varchar(64) NOT NULL DEFAULT 'None'
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `mutes`
--

CREATE TABLE `mutes` (
  `id` int(11) NOT NULL,
  `mid` int(111) NOT NULL,
  `pid` int(111) NOT NULL,
  `dtime` int(111) NOT NULL,
  `by` varchar(111) NOT NULL,
  `reason` varchar(111) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_unicode_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `mytplist`
--

CREATE TABLE `mytplist` (
  `id` int(11) NOT NULL,
  `owner_id` int(11) NOT NULL,
  `name` varchar(33) NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `neftenasos`
--

CREATE TABLE `neftenasos` (
  `id` int(11) NOT NULL,
  `owner_id` int(11) NOT NULL,
  `owner_name` varchar(33) NOT NULL,
  `price` int(11) NOT NULL,
  `rent_price` int(11) NOT NULL,
  `rent` int(11) NOT NULL,
  `neftfuels` int(11) NOT NULL,
  `balance` int(11) NOT NULL,
  `work` int(11) NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `rx` float NOT NULL,
  `ry` float NOT NULL,
  `rz` float NOT NULL,
  `improvements` int(11) NOT NULL,
  `create_type` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

--
-- Дамп данных таблицы `neftenasos`
--

INSERT INTO `neftenasos` (`id`, `owner_id`, `owner_name`, `price`, `rent_price`, `rent`, `neftfuels`, `balance`, `work`, `x`, `y`, `z`, `rx`, `ry`, `rz`, `improvements`, `create_type`) VALUES
(0, 0, 'None', 50000000, 5000000, 0, 0, 0, 0, 2252.55, -769.057, 13.2436, 0, 0, 0, 0, 0),
(1, 0, 'None', 50000000, 5000000, 0, 0, 0, 0, 1446.17, -1453.26, 12.9724, 0, 0, 0, 0, 0),
(2, 0, 'None', 50000000, 5000000, 0, 0, 0, 0, 5.29158, -2537.99, 34.5068, 0, 0, 0, 0, 0),
(3, 0, 'None', 50000000, 5000000, 0, 0, 0, 0, -1675.98, -356.099, 51.5194, 0, 0, 0, 0, 0),
(4, 0, 'None', 50000000, 5000000, 0, 0, 0, 0, -2343.02, -1061.15, 48.0063, 0, 0, 0, 0, 0),
(5, 0, 'None', 50000000, 5000000, 0, 0, 0, 0, -2360.39, -1054.68, 48.0063, 0, 0, 0, 0, 0),
(6, 0, 'None', 50000000, 5000000, 0, 0, 0, 0, -2502.59, -1510.42, 7.32294, 0, 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Структура таблицы `notification`
--

CREATE TABLE `notification` (
  `id` int(11) NOT NULL,
  `owner_id` int(11) NOT NULL,
  `text` varchar(64) NOT NULL,
  `note_text` varchar(255) NOT NULL,
  `time` timestamp NOT NULL,
  `status` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `orders`
--

CREATE TABLE `orders` (
  `id` int(11) NOT NULL,
  `type` int(11) NOT NULL,
  `company` int(11) NOT NULL,
  `amount` int(11) NOT NULL,
  `price` int(11) NOT NULL,
  `time` int(11) NOT NULL,
  `btype` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `ownable_cars`
--

CREATE TABLE `ownable_cars` (
  `id` int(11) NOT NULL,
  `owner_id` int(11) NOT NULL,
  `model_id` int(11) NOT NULL,
  `color_1` int(11) NOT NULL DEFAULT -1,
  `color_2` int(11) NOT NULL DEFAULT -1,
  `vinil` int(2) NOT NULL DEFAULT 3,
  `viniltype` int(11) NOT NULL DEFAULT 1,
  `pos_x` float NOT NULL,
  `pos_y` float NOT NULL,
  `pos_z` float NOT NULL,
  `angle` float NOT NULL,
  `status` int(11) NOT NULL,
  `alarm` int(11) NOT NULL,
  `key_in` int(11) NOT NULL,
  `diski` int(11) NOT NULL,
  `gidra` int(11) NOT NULL,
  `nitro` int(11) NOT NULL,
  `mileage` float NOT NULL,
  `create_time` int(11) NOT NULL,
  `health` float NOT NULL DEFAULT 1000,
  `rent` int(11) NOT NULL DEFAULT -1,
  `rentp` int(11) NOT NULL DEFAULT 0,
  `koleso_1` float NOT NULL DEFAULT 0,
  `koleso_2` float NOT NULL DEFAULT 0,
  `koleso_3` float NOT NULL DEFAULT 0,
  `koleso_4` float NOT NULL DEFAULT 0,
  `inter` int(11) NOT NULL DEFAULT 0,
  `world` int(11) NOT NULL DEFAULT 0,
  `toner` varchar(100) NOT NULL DEFAULT '-1',
  `toner1` int(11) NOT NULL DEFAULT -1,
  `toner2` int(11) NOT NULL DEFAULT 255,
  `toner3` int(11) NOT NULL DEFAULT -1,
  `number` varchar(10) NOT NULL DEFAULT '------',
  `region` varchar(10) NOT NULL,
  `typenumber` int(2) NOT NULL,
  `glass` int(2) NOT NULL DEFAULT -1,
  `procent` int(4) NOT NULL DEFAULT 0,
  `steklo_0` int(5) NOT NULL DEFAULT -1,
  `steklo_1` int(5) NOT NULL DEFAULT -1,
  `steklo_2` int(5) NOT NULL DEFAULT -1,
  `fuel` float NOT NULL DEFAULT 40,
  `colortoner` varchar(100) NOT NULL DEFAULT '-1',
  `obves` varchar(100) NOT NULL DEFAULT '-1',
  `statusts` int(11) NOT NULL,
  `no_key_dostup` int(11) NOT NULL,
  `vehicleid` int(44) NOT NULL DEFAULT -1,
  `famcar` int(44) NOT NULL,
  `famcarrank` int(44) NOT NULL,
  `sab` int(11) NOT NULL,
  `maslo` int(11) NOT NULL,
  `maslo_filter` int(11) NOT NULL,
  `filter` int(11) NOT NULL,
  `stoyanka` int(11) NOT NULL,
  `cutsprings` int(11) NOT NULL,
  `tonerinstall` int(11) NOT NULL,
  `stage` int(11) NOT NULL,
  `sab_pos` int(11) NOT NULL,
  `sab_x` int(11) NOT NULL,
  `sab_y` int(11) NOT NULL,
  `sab_z` int(11) NOT NULL,
  `wash` int(11) NOT NULL,
  `st1x` float NOT NULL,
  `st1y` float NOT NULL,
  `st1z` float NOT NULL,
  `st1rx` float NOT NULL,
  `st1ry` float NOT NULL,
  `st1rz` float NOT NULL,
  `st2x` float NOT NULL,
  `st2y` float NOT NULL,
  `st2z` float NOT NULL,
  `st2rx` float NOT NULL,
  `st2ry` float NOT NULL,
  `st2rz` float NOT NULL,
  `st3x` float NOT NULL,
  `st3y` float NOT NULL,
  `st3z` float NOT NULL,
  `st3rx` float NOT NULL,
  `st3ry` float NOT NULL,
  `st3rz` float NOT NULL,
  `st11x` float NOT NULL,
  `st11y` float NOT NULL,
  `st11z` float NOT NULL,
  `st11rx` float NOT NULL,
  `st11ry` float NOT NULL,
  `st11rz` float NOT NULL,
  `stage1` int(11) NOT NULL,
  `stage1_1` int(11) NOT NULL,
  `stage2` int(11) NOT NULL,
  `stage3` int(11) NOT NULL,
  `iznos` int(11) NOT NULL,
  `gryaz` float NOT NULL,
  `pselect` varchar(155) NOT NULL,
  `tcolor` varchar(155) NOT NULL,
  `tprocent` varchar(155) NOT NULL,
  `pnewma` int(11) NOT NULL,
  `pnewma_1` float NOT NULL,
  `pnewma_2` float NOT NULL,
  `engineacceleration` float NOT NULL,
  `maxgearvelocity` float NOT NULL,
  `number_status` int(11) NOT NULL,
  `horn` int(11) NOT NULL,
  `stage1_obj` int(11) NOT NULL,
  `stage1_1_obj` int(11) NOT NULL,
  `stage2_obj` int(11) NOT NULL,
  `stage3_obj` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `ownable_trailer`
--

CREATE TABLE `ownable_trailer` (
  `id` int(11) NOT NULL,
  `owner_id` int(11) NOT NULL,
  `model_id` float NOT NULL,
  `pos_x` float NOT NULL,
  `pos_y` float NOT NULL,
  `pos_z` float NOT NULL,
  `angle` float NOT NULL,
  `create_time` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `phone_books`
--

CREATE TABLE `phone_books` (
  `id` int(11) NOT NULL,
  `owner_id` int(11) NOT NULL,
  `name` varchar(21) DEFAULT NULL,
  `number` varchar(9) DEFAULT NULL,
  `time` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `player_bonus`
--

CREATE TABLE `player_bonus` (
  `id` int(11) NOT NULL,
  `owner_id` int(11) NOT NULL,
  `count` int(11) NOT NULL,
  `text` varchar(32) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `player_settings`
--

CREATE TABLE `player_settings` (
  `uid` int(11) NOT NULL,
  `player_settings_1` int(11) NOT NULL,
  `player_settings_2` int(11) NOT NULL,
  `player_settings_3` int(11) NOT NULL,
  `player_settings_4` int(11) NOT NULL,
  `player_settings_5` int(11) NOT NULL,
  `player_settings_6` int(11) NOT NULL,
  `player_settings_7` int(11) NOT NULL,
  `player_settings_8` int(11) NOT NULL,
  `player_settings_9` int(11) NOT NULL,
  `player_settings_10` int(11) NOT NULL,
  `player_settings_11` int(11) NOT NULL,
  `player_settings_12` int(11) NOT NULL,
  `player_settings_13` int(11) NOT NULL,
  `player_settings_14` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `police_tablet`
--

CREATE TABLE `police_tablet` (
  `id` int(11) NOT NULL,
  `event` int(11) NOT NULL,
  `name` varchar(64) NOT NULL,
  `place` varchar(64) NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `time` int(11) NOT NULL,
  `ownerid` int(11) NOT NULL,
  `reason` varchar(64) NOT NULL,
  `type` int(11) NOT NULL,
  `suspect` varchar(64) NOT NULL,
  `skin` int(11) NOT NULL,
  `cuffname` varchar(64) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `prizes`
--

CREATE TABLE `prizes` (
  `id` int(11) NOT NULL,
  `owner_id` int(11) NOT NULL,
  `name` varchar(34) NOT NULL,
  `size` int(11) NOT NULL,
  `item` int(11) NOT NULL,
  `type` int(11) NOT NULL,
  `count` int(11) NOT NULL,
  `indx` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `prizes_code`
--

CREATE TABLE `prizes_code` (
  `id` int(11) NOT NULL,
  `name` varchar(32) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `count_time` int(11) NOT NULL,
  `count_activation` int(11) NOT NULL,
  `type_code` int(11) NOT NULL,
  `type_prize_1` int(11) NOT NULL,
  `id_prize_1` int(11) NOT NULL,
  `count_prize_1` int(11) NOT NULL,
  `type_prize_2` int(11) NOT NULL,
  `id_prize_2` int(11) NOT NULL,
  `count_prize_2` int(11) NOT NULL,
  `type_prize_3` int(11) NOT NULL,
  `id_prize_3` int(11) NOT NULL,
  `count_prize_3` int(11) NOT NULL,
  `type_prize_4` int(11) NOT NULL,
  `id_prize_4` int(11) NOT NULL,
  `count_prize_4` int(11) NOT NULL,
  `type_prize_5` int(11) NOT NULL,
  `id_prize_5` int(11) NOT NULL,
  `count_prize_5` int(11) NOT NULL,
  `type_prize_6` int(11) NOT NULL,
  `id_prize_6` int(11) NOT NULL,
  `count_prize_6` int(11) NOT NULL,
  `yt_promo` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `promocode_activations`
--

CREATE TABLE `promocode_activations` (
  `id` int(11) NOT NULL,
  `owner_id` int(11) NOT NULL,
  `name` varchar(32) NOT NULL,
  `time` int(11) NOT NULL,
  `status` int(11) NOT NULL,
  `type` int(11) NOT NULL,
  `count` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `raffle_shop`
--

CREATE TABLE `raffle_shop` (
  `id` int(11) NOT NULL,
  `owner_id` int(11) NOT NULL,
  `type` int(11) NOT NULL,
  `ticket_id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `report_mesage`
--

CREATE TABLE `report_mesage` (
  `id` int(11) NOT NULL,
  `owner_id` int(11) NOT NULL,
  `report_id` int(11) NOT NULL,
  `name` varchar(50) NOT NULL,
  `text` varchar(150) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `data` varchar(25) NOT NULL,
  `status` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_unicode_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `report_ticket`
--

CREATE TABLE `report_ticket` (
  `id` int(11) NOT NULL,
  `owner_id` int(11) NOT NULL,
  `name` varchar(50) NOT NULL,
  `text` varchar(150) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `data` varchar(25) NOT NULL,
  `lock` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_unicode_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `repositories`
--

CREATE TABLE `repositories` (
  `id` int(11) NOT NULL,
  `type` int(11) NOT NULL,
  `action_id` int(11) NOT NULL,
  `amount` int(11) NOT NULL,
  `description` varchar(64) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

--
-- Дамп данных таблицы `repositories`
--

INSERT INTO `repositories` (`id`, `type`, `action_id`, `amount`, `description`) VALUES
(1, 6, 0, 871, '226'),
(2, 1, 1, 9928, '221'),
(3, 2, 0, 100000, '222'),
(4, 3, 1, 65164, '223'),
(5, 4, 1, 4, '224'),
(6, 5, 0, -112, '225'),
(7, 4, 0, 1, '224'),
(8, 2, 1, 22, '222'),
(9, 2, 2, 222, '222'),
(10, 1, 0, 9988, '221'),
(11, 1, 2, 10441, '221'),
(12, 3, 0, 98077, '223');

-- --------------------------------------------------------

--
-- Структура таблицы `server_config`
--

CREATE TABLE `server_config` (
  `id` int(11) NOT NULL,
  `x_bonus` int(11) NOT NULL,
  `test_status` int(11) NOT NULL,
  `time_battlepass` int(11) NOT NULL,
  `time_daily` int(11) NOT NULL,
  `id_raffleshopping_1` int(11) NOT NULL DEFAULT -1,
  `id_raffleshopping_2` int(11) NOT NULL DEFAULT -1,
  `time_raffleshopping_1` int(11) NOT NULL,
  `time_raffleshopping_2` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_unicode_ci;

--
-- Дамп данных таблицы `server_config`
--

INSERT INTO `server_config` (`id`, `x_bonus`, `test_status`, `time_battlepass`, `time_daily`, `id_raffleshopping_1`, `id_raffleshopping_2`, `time_raffleshopping_1`, `time_raffleshopping_2`) VALUES
(1, 1, 0, 1755660320, 1756753513, 22, 38, 1755322098, 1755322098);

-- --------------------------------------------------------

--
-- Структура таблицы `test_user`
--

CREATE TABLE `test_user` (
  `id` int(11) NOT NULL,
  `name` varchar(64) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_unicode_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `tickets`
--

CREATE TABLE `tickets` (
  `id` int(11) NOT NULL,
  `uid` int(11) NOT NULL,
  `amount` int(11) NOT NULL,
  `description` varchar(64) NOT NULL,
  `issuer` varchar(32) NOT NULL,
  `status` int(11) NOT NULL,
  `time` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

-- --------------------------------------------------------

--
-- Структура таблицы `tk_cars`
--

CREATE TABLE `tk_cars` (
  `id` int(11) NOT NULL,
  `owner_id` int(11) NOT NULL,
  `model_id` int(11) NOT NULL,
  `color_1` int(11) NOT NULL DEFAULT -1,
  `color_2` int(11) NOT NULL DEFAULT -1,
  `pos_x` float NOT NULL,
  `pos_y` float NOT NULL,
  `pos_z` float NOT NULL,
  `angle` float NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

--
-- Дамп данных таблицы `tk_cars`
--

INSERT INTO `tk_cars` (`id`, `owner_id`, `model_id`, `color_1`, `color_2`, `pos_x`, `pos_y`, `pos_z`, `angle`) VALUES
(1, 7, 535, 1, 1, 1387.11, -1184.72, 13.9019, 142.398),
(2, 7, 15206, 1, 1, -1621.73, -2510.05, 7.4877, 130.667),
(3, 1, 15622, 1, 1, 2220.02, -2569.51, 21.7242, 275.016),
(4, 1, 15140, 1, 1, -2750.95, -1415.64, 9.9549, 138.894),
(5, 1, 15140, 0, 0, 788.865, 538.677, 14.908, 0),
(6, 1, 15185, 1, 1, -2761.65, -1335.12, 9.927, 143.776),
(7, 1, 908, 0, 0, -2779.54, -1441.68, 9.9129, 310.633),
(8, 3, 535, 1, 1, 788.865, 538.677, 14.908, 0),
(9, 3, 432, 0, 0, 788.865, 538.677, 14.908, 0),
(10, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(11, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(12, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(13, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(14, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(15, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(16, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(17, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(18, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(19, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(20, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(21, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(22, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(23, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(24, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(25, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(26, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(27, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(28, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(29, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(30, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(31, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(32, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(33, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(34, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(35, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(36, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(37, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(38, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(39, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(40, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(41, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(42, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(43, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(44, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(45, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(46, 1, 400, 1, 1, 788.865, 538.677, 14.908, 0),
(48, 2, 15160, 1, 1, -1925.93, 2936.78, 6.191, 90),
(49, 1, 15071, 1, 1, -1925.93, 2936.78, 6.191, 90),
(50, 1, 400, 1, 1, -267.007, -1452.04, 40.972, 180),
(51, 1943, 15175, 0, 0, 788.865, 538.677, 14.908, 0),
(52, 2, 492, 4, 34, -382.418, 1041.61, 11.4772, 279.457),
(53, 2, 15074, 50, 0, -380.036, 1051.75, 11.6026, 11.2678),
(54, 2, 15669, 255, 0, 788.865, 538.677, 14.908, 0),
(55, 2, 15145, 0, 0, -425.848, 1019.63, 11.5971, 71.2786),
(56, 2, 503, 8, 0, -431.647, 604.087, 11.6185, 180.039),
(57, 2, 15151, 39, 0, 2178.71, -1837.9, 18.5692, 89.7445),
(58, 2, 400, 13, 1, 788.865, 538.677, 14.908, 0),
(59, 2, 579, 0, 0, 1882.36, 2820.49, 12.06, 90.257),
(60, 2, 558, 15, 0, 1903.24, 2832.22, 12.06, 269.568),
(61, 2, 15158, 34, 0, -419.119, 604.887, 11.6184, 180.358),
(62, 1943, 492, 0, 0, 788.865, 538.677, 14.908, 0),
(63, 2, 15080, 8, 9, 2174.41, -1829.94, 18.5958, 95.2939),
(64, 1, 15250, 1, 1, 788.865, 538.677, 14.908, 0),
(65, 1, 15085, 1, 1, 788.865, 538.677, 14.908, 0),
(66, 2, 15085, 0, 0, 1882.56, 2832.22, 12.06, 89.885),
(68, 97, 793, 1, 1, 788.865, 538.677, 14.908, 0),
(67, 6907, 15675, 0, 0, 2239.17, -2397.82, 51.4252, 181.73),
(69, 6907, 470, 0, 0, 788.865, 538.677, 14.908, 0),
(70, 8238, 15085, 1, 1, -2653.85, 169.338, 12.0889, 1.56913),
(71, 8238, 15284, 1, 1, -2655.25, 168.91, 12.5897, 359.999),
(72, 2, 15095, 0, 0, 1033.63, -1911.67, 34.446, 227.525);

-- --------------------------------------------------------

--
-- Структура таблицы `vorota`
--

CREATE TABLE `vorota` (
  `id` int(11) NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `z` float NOT NULL,
  `rz` float NOT NULL,
  `type` int(11) NOT NULL,
  `type_open` int(11) NOT NULL,
  `type_object` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

--
-- Дамп данных таблицы `vorota`
--

INSERT INTO `vorota` (`id`, `x`, `y`, `z`, `rz`, `type`, `type_open`, `type_object`) VALUES
(1, -2231.69, -1642.49, 7.67655, -55.8, 1, 0, 10919),
(2, -2228.15, -1647.73, 7.67655, 123.8, 2, 0, 10919),
(3, -2214.95, -1667.5, 7.66655, -57, 1, 0, 10919),
(4, -2211.43, -1672.75, 7.66435, 124.7, 2, 0, 10919),
(5, -2198.25, -1692.44, 7.74655, -58, 1, 0, 10919),
(6, -2194.78, -1697.72, 7.75431, 124.9, 2, 0, 10919),
(7, -2181.67, -1717.26, 7.79654, -55.1, 1, 0, 10919),
(8, -2178.15, -1722.48, 7.79655, 123.1, 2, 0, 10919),
(9, -2151.58, -1762.19, 7.669, -54.7, 1, 0, 10919),
(10, -2148.03, -1767.42, 7.679, 122.8, 2, 0, 10919),
(11, -2134.84, -1787.16, 7.729, -55.4, 1, 0, 10919),
(12, -2131.33, -1792.43, 7.739, 123, 2, 0, 10919),
(13, -2171.86, -1839.13, 7.669, 124.8, 1, 0, 10919),
(14, -2175.37, -1833.89, 7.669, -56.8, 2, 0, 10919),
(15, 3661.12, 4229, 7.14201, -139.5, 1, 0, 10900),
(16, 3657.38, 4225.69, 7.14526, 42.5, 2, 0, 10900),
(17, 3636.75, 4196.72, 7.10145, 67.1, 1, 0, 10900),
(18, 3638.72, 4201.27, 7.10144, -114.3, 2, 0, 10900),
(19, 3626.96, 4147.56, 7.15349, 84.2, 1, 0, 10900),
(20, 3627.58, 4152.54, 7.16143, -98.2001, 2, 0, 10900),
(23, 854.378, 1194.44, 4.09422, -113.4, 1, 0, 10900),
(24, 852.444, 1189.82, 4.11421, 66.8, 2, 0, 10900),
(25, 3690.95, 4249.38, 7.11143, 27.6, 1, 0, 10900),
(26, 3695.4, 4251.85, 7.10144, -150.1, 2, 0, 10900),
(27, 3881.4, 4326.11, 7.0509, 21.2, 1, 0, 10900),
(28, 3886.18, 4327.96, 7.05091, -159.7, 2, 0, 10900),
(29, 3848.1, 4313.06, 7.0609, 22.1, 1, 0, 10900),
(30, 3852.79, 4314.83, 7.0509, -161.1, 2, 0, 10900),
(31, 3801.94, 4295.03, 7.1009, 20.4001, 1, 0, 10900),
(32, 3806.55, 4296.82, 7.11476, -157.8, 2, 0, 10900),
(33, 3765.56, 4281.36, 7.0809, 20.3, 1, 0, 10900),
(34, 3770.29, 4283.17, 7.0709, -158.9, 2, 0, 10900),
(35, -2249.91, -1762.94, 7.66654, -56.7, 1, 0, 10919),
(36, -2246.45, -1768.22, 7.66435, 123.5, 2, 0, 10919),
(37, -2266.54, -1738.04, 7.73655, -55.2, 1, 0, 10919),
(38, -2262.97, -1743.26, 7.72654, 123.3, 2, 0, 10919),
(39, -2235.22, -1744.44, 7.74435, 124.9, 1, 0, 10919),
(40, -2238.76, -1739.2, 7.73435, -56.9, 2, 0, 10919),
(41, -2218.56, -1769.36, 7.66654, 124.9, 1, 0, 10919),
(42, -2222.11, -1764.15, 7.66655, -56.1, 2, 0, 10919),
(43, -2188.53, -1814.23, 7.679, 125.1, 1, 0, 10919),
(44, -2192.06, -1808.99, 7.67899, -57.2, 2, 0, 10919),
(45, -2218.87, -1809.35, 7.659, -55, 1, 0, 10919),
(46, -2215.35, -1814.59, 7.649, 122.6, 2, 0, 10919),
(47, -2185.45, -1859.28, 7.64899, -55.6, 1, 0, 10919),
(48, -2181.92, -1864.51, 7.679, 124.1, 2, 0, 10919),
(49, -2118.22, -1812, 7.66899, -54.6, 1, 0, 10919),
(50, -2114.63, -1817.19, 7.65144, 124.1, 2, 0, 10919),
(51, -2283.28, -1713.01, 7.66654, -55.7, 1, 0, 10919),
(52, -2279.72, -1718.23, 7.66655, 122.9, 2, 0, 10919),
(53, -2299.89, -1688.16, 7.64435, -55.6, 1, 0, 10919),
(54, -2296.33, -1693.37, 7.64436, 124.2, 2, 0, 10919),
(55, -2251.99, -1719.42, 7.64655, 123.9, 1, 0, 10919),
(56, -2255.52, -1714.18, 7.63655, -56.1, 2, 0, 10919),
(57, -2335.44, -1594.8, 7.64655, 125.6, 1, 0, 10919),
(58, -2338.95, -1589.56, 7.65655, -58.2, 2, 0, 10919),
(59, -2318.74, -1619.75, 7.62655, 124, 1, 0, 10919),
(60, -2322.19, -1614.48, 7.63654, -57.7, 2, 0, 10919),
(61, -2305.53, -1639.58, 7.68654, -56.8, 2, 0, 10919),
(62, -2301.96, -1644.77, 7.69655, 125.6, 1, 0, 10919),
(63, -2285.31, -1669.67, 7.63435, 124.8, 1, 0, 10919),
(64, -2288.83, -1664.43, 7.63655, -57.6, 2, 0, 10919),
(65, -2268.64, -1694.58, 7.67436, 125.5, 1, 0, 10919),
(66, -2272.21, -1689.38, 7.68435, -56.3, 2, 0, 10919),
(67, -2155.17, -1864.07, 7.60899, 126.2, 1, 0, 10919),
(68, -2158.72, -1858.85, 7.619, -58.1, 2, 0, 10919),
(69, -2097.96, -1842.23, 7.689, 123.7, 2, 0, 10919),
(70, -2101.49, -1836.99, 7.679, -55.3, 1, 0, 10919),
(71, -2084.72, -1862.01, 7.729, -56.1, 1, 0, 10919),
(72, -2081.18, -1867.23, 7.71899, 123.8, 2, 0, 10919),
(73, -2138.47, -1888.97, 7.599, 122, 1, 0, 10919),
(74, -2141.99, -1883.71, 7.589, -54.5, 2, 0, 10919),
(75, -2105.12, -1938.88, 7.679, 124.2, 1, 0, 10919),
(76, -2108.63, -1933.64, 7.689, -56.7, 2, 0, 10919),
(77, -2121.76, -1913.99, 7.659, 124.5, 1, 0, 10919),
(78, -2125.29, -1908.74, 7.65899, -56.9, 2, 0, 10919),
(79, -2076.28, -1971.24, 7.619, -110.6, 1, 0, 10919),
(80, -2078.48, -1977.07, 7.639, 68.8001, 2, 0, 10919),
(81, -2067.64, -1949.04, 7.65899, 67.8, 1, 0, 10919),
(82, -2065.36, -1943.16, 7.659, -110.5, 2, 0, 10919),
(83, -2056.83, -1921.13, 7.61899, 67.3, 1, 0, 10919),
(84, -2054.52, -1915.26, 7.629, -110.2, 2, 0, 10919),
(85, -2045.95, -1893.06, 7.629, 69.4001, 1, 0, 10919),
(86, -2043.67, -1887.19, 7.639, -112, 2, 0, 10919),
(87, -2045.78, -1878.88, 7.659, 123.8, 1, 0, 10919),
(88, -2049.31, -1873.65, 7.65669, -55.8, 2, 0, 10919),
(89, -2062.43, -1854.03, 7.639, 124.5, 1, 0, 10919),
(90, -2066.08, -1848.87, 7.629, -54.1, 2, 0, 10919),
(91, -2079.11, -1829.09, 7.66899, 125.4, 1, 0, 10919),
(92, -2082.66, -1823.86, 7.679, -56.9999, 2, 0, 10919),
(93, -2095.86, -1804.09, 7.659, 126.2, 1, 0, 10919),
(94, -2099.39, -1798.86, 7.68669, -57.8, 2, 0, 10919),
(95, -2112.56, -1779.15, 7.63669, 124.6, 1, 0, 10919),
(96, -2116.02, -1773.83, 7.639, -58.1, 2, 0, 10919),
(97, -2129.29, -1754.16, 7.669, 124.9, 1, 0, 10919),
(98, -2132.85, -1748.95, 7.66899, -56.2, 2, 0, 10919),
(99, -2145.9, -1729.33, 7.66655, 124.2, 1, 0, 10919),
(100, -2149.38, -1724.07, 7.66655, -57.8, 2, 0, 10919),
(101, -2202.05, -1834.37, 7.63899, -54.9, 1, 0, 10919),
(102, -2198.55, -1839.62, 7.63899, 122.4, 2, 0, 10919),
(103, 3665.61, 3982.75, 7.05372, 0, 1, 0, 10900),
(104, 3670.65, 3982.8, 7.06779, -180, 2, 0, 10900),
(105, 3711.14, 3982.57, 7.05672, 0, 1, 0, 10900),
(106, 3716.23, 3982.59, 7.07866, -179.7, 2, 0, 10900),
(107, 3745.79, 3982.57, 7.0549, 0, 1, 0, 10900),
(108, 3750.8, 3982.56, 7.06534, 179.4, 2, 0, 10900),
(109, 3645.08, 4001.05, 7.08681, 0, 1, 0, 10900),
(110, 3650.2, 4001.19, 7.07564, -177.9, 2, 0, 10900),
(111, 3702.18, 4001.86, 7.07898, 0, 1, 0, 10900),
(112, 3707.18, 4001.99, 7.07635, -177.4, 2, 0, 10900),
(113, 3761.53, 4001.72, 7.13347, 0, 1, 0, 10900),
(114, 3766.62, 4001.77, 7.13898, -178, 2, 0, 10900),
(115, 3806.91, 3986.74, 7.08449, 17.2, 1, 0, 10900),
(116, 3811.68, 3988.11, 7.09064, -165.5, 2, 0, 10900),
(117, 3807.69, 4007.72, 7.0955, 16.1, 1, 0, 10900),
(118, 3812.54, 4008.95, 7.09571, -167.4, 2, 0, 10900),
(119, 3855.98, 4001.38, 7.14064, 18.9, 1, 0, 10900),
(120, 3860.8, 4002.94, 7.13386, -163.1, 2, 0, 10900),
(121, 3847.12, 4018.96, 7.11667, 16, 1, 0, 10900),
(122, 3851.88, 4020.33, 7.07064, -164, 2, 0, 10900),
(123, 3798.99, 3920.91, 7.14064, -78.5, 1, 0, 10900),
(124, 3799.94, 3915.91, 7.13064, 99.6, 2, 0, 10900),
(125, 3811.46, 3865.12, 7.16064, -75.1999, 1, 0, 10900),
(126, 3812.69, 3860.21, 7.16064, 103.3, 2, 0, 10900),
(127, 3850.91, 3815.92, 7.13119, -7.99999, 1, 0, 10900),
(128, 3855.73, 3815.32, 7.12252, 173.2, 2, 0, 10900),
(129, 3918.38, 3851.38, 7.14064, 106.2, 1, 0, 10900),
(130, 3916.96, 3856.2, 7.14199, -74, 2, 0, 10900),
(131, 3938.98, 3848.95, 7.07032, 104.8, 1, 0, 10900),
(132, 3937.73, 3853.7, 7.07091, -75.7999, 2, 0, 10900),
(133, 3923.85, 3902.68, 7.13842, -72.4, 1, 0, 10900),
(134, 3925.31, 3897.89, 7.13558, 106.2, 2, 0, 10900),
(135, 3905.93, 3895.64, 7.08814, 107.6, 1, 0, 10900),
(136, 3904.53, 3900.38, 7.07041, -75.0999, 2, 0, 10900),
(137, 3895.16, 3932.65, 7.08032, 105.4, 1, 0, 10900),
(138, 3893.72, 3937.39, 7.0756, -72.2, 2, 0, 10900),
(139, 3907.74, 3955.21, 7.06064, -73.1, 1, 0, 10900),
(140, 3909.12, 3950.31, 7.0723, 105.5, 2, 0, 10900),
(141, 3895.03, 3997.12, 7.15064, -72.7999, 1, 0, 10900),
(142, 3896.52, 3992.35, 7.15064, 107.4, 2, 0, 10900),
(143, 4004.69, 3961.41, 7.11335, 104.2, 1, 0, 10900),
(144, 4003.33, 3966.3, 7.11992, -73.8, 2, 0, 10900),
(145, 3953.83, 4033.21, 7.11657, -161.7, 1, 0, 10900),
(146, 3949, 4031.55, 7.07574, 19.3, 2, 0, 10900),
(147, 3941.72, 4048.35, 7.11696, 15.6, 1, 0, 10900),
(148, 3946.51, 4049.84, 7.1305, -161.3, 2, 0, 10900),
(149, 3881.25, 4046.49, 7.06245, 109.5, 1, 0, 10900),
(150, 3879.69, 4051.19, 7.06064, -73.3, 2, 0, 10900),
(151, 3870.53, 4082.02, 7.0579, -72.6, 1, 0, 10900),
(152, 3871.96, 4077.2, 7.05063, 105.3, 2, 0, 10900),
(153, 3848.2, 4091.2, 7.07877, 107.4, 1, 0, 10900),
(154, 3846.8, 4096.05, 7.08744, -75.3, 2, 0, 10900),
(155, 3957.72, 4146.5, 7.11216, 93.1, 1, 0, 10900),
(156, 3957.23, 4151.5, 7.11636, -82.1, 2, 0, 10900),
(157, 3618.27, 4073.53, 7.13286, 82.1, 1, 0, 10900),
(158, 3619.1, 4078.5, 7.12541, -101.6, 2, 0, 10900),
(159, 3623.09, 4109.41, 7.07528, 84.3, 1, 0, 10900),
(160, 3623.52, 4114.31, 7.10018, -94.5, 2, 0, 10900),
(161, 3663.47, 4207.94, 7.135, 40.5, 1, 0, 10900),
(162, 3667.36, 4210.93, 7.1202, -145.7, 2, 0, 10900),
(163, 3722.85, 4243.43, 7.09217, 26.2, 1, 0, 10900),
(164, 3727.39, 4245.51, 7.09844, -154.4, 2, 0, 10900),
(165, 3722.57, 4264.98, 7.12176, 23.5, 1, 0, 10900),
(166, 3727.17, 4266.94, 7.12093, -158, 2, 0, 10900),
(167, 3827.24, 4285, 7.14341, 20.2, 1, 0, 10900),
(168, 3831.9, 4286.84, 7.14121, -157.2, 2, 0, 10900),
(169, 3856.33, 4296.19, 7.13122, 21.4, 1, 0, 10900),
(170, 3861.04, 4298, 7.14122, -159.3, 2, 0, 10900),
(171, 3906.48, 4314.96, 7.13341, -160.1, 1, 0, 10900),
(172, 3901.77, 4313.25, 7.13341, 19.8, 2, 0, 10900),
(173, 3946.5, 4246.8, 7.08788, 96.7, 1, 0, 10900),
(174, 3945.86, 4251.79, 7.07986, -82.6, 2, 0, 10900),
(175, 3953.09, 4194.62, 7.14063, 97.2999, 1, 0, 10900),
(176, 3952.56, 4199.54, 7.12122, -85.3999, 2, 0, 10900),
(177, 3799.42, 4258.89, 7.13764, 109.7, 1, 0, 10900),
(178, 3797.69, 4263.66, 7.13586, -70.4, 2, 0, 10900),
(179, 3831.37, 4217.03, 7.13341, -72.8, 1, 0, 10900),
(180, 3832.83, 4212.32, 7.09375, 106.9, 2, 0, 10900),
(181, 3814.82, 4207.56, 7.13122, -72.3999, 1, 0, 10900),
(182, 3816.3, 4202.86, 7.13122, 106.9, 2, 0, 10900),
(183, 3843.02, 4177.17, 7.09472, -74.4999, 1, 0, 10900),
(184, 3844.34, 4172.33, 7.09091, 104.4, 2, 0, 10900),
(185, 3832.6, 4148.77, 7.13122, 107.5, 1, 0, 10900),
(186, 3831.12, 4153.61, 7.14342, -73.4, 2, 0, 10900),
(187, 3750.06, 4103.36, 7.19342, 3.9, 1, 0, 10900),
(188, 3755.1, 4103.49, 7.19281, 179.1, 2, 0, 10900),
(189, 3749.38, 4124.42, 7.08339, 1.8, 1, 0, 10900),
(190, 3754.32, 4124.65, 7.09583, -176.6, 2, 0, 10900),
(191, 3719.37, 4103.13, 7.10635, -177.5, 1, 0, 10900),
(192, 3714.32, 4102.99, 7.11118, 0, 2, 0, 10900),
(193, 3717.02, 4123.32, 7.10144, 1.8, 1, 0, 10900),
(194, 3722.02, 4123.5, 7.10144, -177.8, 2, 0, 10900),
(195, 3659.15, 4101.98, 7.11679, 0, 1, 0, 10900),
(196, 3664.16, 4102.15, 7.11679, -177, 2, 0, 10900),
(197, 3662.73, 4120.74, 7.02818, 0, 1, 0, 10900),
(198, 3667.77, 4120.95, 7.01144, -175.5, 2, 0, 10900),
(199, 3855.1, 4135.01, 7.15341, 106.8, 1, 0, 10900),
(200, 3853.72, 4139.83, 7.15122, -73.8, 2, 0, 10900),
(201, 1996.88, -2916.46, 2.98496, -19, 1, 0, 16036),
(202, 2003.28, -2918.64, 2.97496, 160.9, 2, 0, 16036),
(203, 2234.17, -3078.31, 2.82763, 20, 1, 1, 16041),
(204, 736.46, 1317.36, 4.11248, -5.9, 1, 0, 10900),
(205, 741.455, 1316.94, 4.11251, 176.1, 2, 0, 10900),
(206, 2285.59, -3454.66, 2.92835, 9.9, 1, 1, 16040),
(207, 2698.58, -3038.99, 3.13114, 5, 1, 1, 16037),
(208, 2614.47, -3058.26, 3.02078, 15.6, 1, 1, 16039),
(209, 702.771, 1320.12, 4.11145, -4.4, 1, 0, 10900),
(210, 707.757, 1319.67, 4.1103, 174.4, 2, 0, 10900),
(211, 2564.94, -3091.47, 2.55008, -0.199999, 1, 0, 16036),
(212, 2571.73, -3091.45, 2.53869, 179.9, 2, 0, 16036),
(213, 2305.5, -3426.7, 2.82117, 13.7, 1, 1, 16037),
(214, 2375.27, -3424.08, 3.01248, 29.5, 1, 1, 16039),
(215, 2404.39, -3385.76, 2.5231, -100.8, 1, 0, 16036),
(216, 2403.16, -3392.4, 2.50363, 79.4001, 2, 0, 16036),
(217, 2394.71, -3335.95, 2.94138, 104.8, 1, 0, 16036),
(218, 2392.99, -3329.35, 2.93004, -76, 2, 0, 16036),
(219, 2359.96, -3228.86, 2.85763, 70.1, 1, 1, 16037),
(220, 2368.15, -3326.03, 2.98921, -70.1, 1, 1, 16041),
(221, 2417.6, -3197.07, 3.02763, 31.6, 1, 1, 16039),
(222, 2467.45, -3159.64, 3.09763, -3.2, 1, 1, 16037),
(223, 2414.79, -3171.89, 2.57763, -146.8, 1, 0, 16036),
(224, 2409.16, -3175.78, 2.57763, 35.8, 2, 0, 16036),
(225, 1621.23, -3042.19, 2.84327, 5.7, 1, 0, 16036),
(226, 1628.02, -3041.48, 2.83483, -174.3, 2, 0, 16036),
(227, 690.606, 1234.42, 4.09063, 1.8, 1, 0, 10900),
(228, 695.612, 1234.45, 4.09063, 178.6, 2, 0, 10900),
(229, 2509.33, -3051.75, 2.50044, -11.4, 1, 0, 16036),
(230, 2516.02, -3053.07, 2.50044, 168.4, 2, 0, 16036),
(231, 2412.51, -3061.43, 3.02763, 29.1, 1, 1, 16038),
(232, 692.376, 1339.17, 4.10632, -5.5, 1, 0, 10900),
(233, 697.306, 1338.81, 4.10631, 177, 2, 0, 10900),
(234, 2306.48, -3074.64, 3.00763, -9.9, 1, 1, 16039),
(235, 746.536, 1335.58, 4.11631, -4.8, 1, 0, 10900),
(236, 751.521, 1335.34, 4.11273, 179, 2, 0, 10900),
(237, 797.292, 1308.91, 4.11852, -19.3, 1, 0, 10900),
(238, 802.072, 1307.43, 4.11842, 164.5, 2, 0, 10900),
(239, 2242.66, -3098.31, 2.75763, 18, 1, 1, 16037),
(240, 797.292, 1308.91, 4.11852, -19.3, 1, 0, 10900),
(241, 802.072, 1307.43, 4.11842, 164.5, 2, 0, 10900),
(242, 2587.76, -3342.01, 3.06937, -59.6, 1, 1, 16037),
(243, 2601.34, -3276.46, 3.07718, 35.5, 1, 1, 16037),
(244, 680.365, 1132.91, 4.10632, -9.19999, 1, 0, 10900),
(245, 685.335, 1132.22, 4.10631, 172.1, 2, 0, 10900),
(246, 2615.9, -3239.31, 3.03036, 32.9, 1, 1, 16039),
(247, 2655.26, -3240.57, 2.45718, 34.5, 1, 0, 16036),
(248, 2660.78, -3236.6, 2.44718, -143.7, 2, 0, 16036),
(249, 2721.91, -3188.21, 3.13718, 40, 1, 1, 16039),
(250, 2767.66, -3131.44, 2.52114, -110.4, 1, 0, 16036),
(251, 2765.25, -3137.84, 2.51114, 68.4999, 2, 0, 16036),
(252, 1509.46, -3107.88, 2.9444, 55.3, 1, 0, 16036),
(253, 1513.29, -3102.24, 2.93456, -124.5, 2, 0, 16036),
(254, 2771.51, -3065.22, 3.23895, -80, 1, 1, 16038),
(255, 2757.96, -3043.79, 3.13527, -30.1, 1, 1, 16037),
(256, 676.327, 1179.98, 4.09995, 85.3001, 1, 0, 10900),
(257, 676.573, 1184.96, 4.09995, -91.2, 2, 0, 10900),
(258, 2747.91, -3068.59, 2.96853, 129.2, 1, 0, 16036),
(259, 2743.62, -3063.38, 2.95915, -50.8001, 2, 0, 16036),
(260, 1718.96, -3097.24, 2.40445, 22.1, 1, 0, 16036),
(261, 1725.32, -3094.79, 2.40434, -160.5, 2, 0, 16036),
(262, 2067.72, -3477.44, 2.57226, -1.5, 1, 0, 16036),
(263, 2074.53, -3477.58, 2.57226, 178.6, 2, 0, 16036),
(264, 1814.85, -3444.08, 3.03662, -15.2, 1, 1, 16038),
(265, 572.825, 1118.65, 4.1027, -72.4, 1, 0, 10900),
(266, 574.416, 1113.92, 4.10271, 109.2, 2, 0, 10900),
(267, 1531.41, -3272.2, 3.01527, -29.4, 1, 1, 16037),
(268, 825.016, 1377.41, 4.0963, 57.9, 1, 0, 10900),
(269, 827.725, 1381.59, 4.0963, -124, 2, 0, 10900),
(270, 833.985, 1352.82, 4.1663, -122.9, 1, 0, 10900),
(271, 831.344, 1348.61, 4.16629, 58.5, 2, 0, 10900),
(272, 848.528, 1289.67, 4.10631, -61.1, 1, 0, 10900),
(273, 850.922, 1285.27, 4.10631, 117.8, 2, 0, 10900),
(274, 856.624, 1222.92, 4.11631, -94, 1, 0, 10900),
(275, 856.251, 1217.96, 4.1212, 85.2, 2, 0, 10900),
(276, 848.528, 1289.67, 4.10631, -61.1, 1, 0, 10900),
(277, 850.922, 1285.27, 4.10631, 117.8, 2, 0, 10900),
(278, 856.624, 1222.92, 4.11631, -94, 1, 0, 10900),
(279, 856.251, 1217.96, 4.1212, 85.2, 2, 0, 10900),
(280, 2088.47, -3144.51, 2.54683, 3.7, 1, 0, 16036),
(281, 2095.25, -3144.56, 2.53705, 174.8, 2, 0, 16036),
(282, 832.799, 1132.78, 4.11421, -122.1, 1, 0, 10900),
(283, 830.17, 1128.51, 4.11422, 58.5, 2, 0, 10900),
(284, 752.418, 1044.64, 4.09852, -147.2, 1, 0, 10900),
(285, 748.162, 1042, 4.09631, 30.7, 2, 0, 10900),
(286, 785.66, 1067.31, 4.09852, 47.3, 1, 0, 10900),
(287, 788.99, 1071.05, 4.09689, -130.9, 2, 0, 10900),
(288, 1699.22, -3042.52, 2.93042, -47.3, 1, 1, 16040),
(289, 787.962, 1208.47, 4.10632, 172.8, 1, 0, 10900),
(290, 783.035, 1209.19, 4.10994, -9.60001, 2, 0, 10900),
(291, 826.255, 1223.54, 4.11063, -9.09999, 1, 0, 10900),
(292, 831.208, 1222.78, 4.11063, 171.4, 2, 0, 10900),
(293, 746.658, 1213.12, 4.11632, -5.3, 1, 0, 10900),
(294, 751.61, 1212.87, 4.11994, 179.5, 2, 0, 10900),
(295, 786.935, 1101.22, 4.09995, 50.3, 1, 0, 10900),
(296, 790.066, 1105.07, 4.09632, -128.7, 2, 0, 10900),
(297, 730.506, 1057.98, 4.12994, -155.5, 1, 0, 10900),
(298, 726.014, 1055.91, 4.12994, 24.9, 2, 0, 10900),
(299, 591.24, 1242.95, 4.11082, 166.1, 1, 0, 10900),
(300, 586.342, 1243.98, 4.11063, -10.2, 2, 0, 10900),
(301, 549.967, 1292.37, 4.11063, 27.8, 1, 0, 10900),
(302, 554.403, 1294.7, 4.11063, -152.6, 2, 0, 10900),
(303, 541.927, 1311.55, 4.10632, 30.3, 1, 0, 10900),
(304, 546.253, 1314.07, 4.10631, -149.901, 2, 0, 10900),
(305, 454.536, 1279.19, 4.11489, -8.69999, 1, 0, 10900),
(306, 459.483, 1278.39, 4.1127, 170.2, 2, 0, 10900),
(307, 550.52, 1316.92, 4.1227, 21.6, 1, 0, 10900),
(308, 555.098, 1318.88, 4.1227, -155.5, 2, 0, 10900),
(309, 1648.89, -3020.53, 2.36312, 176.4, 1, 0, 16036),
(310, 1642.09, -3020.08, 2.364, -4.7, 2, 0, 16036),
(311, 625.53, 1369.77, 4.11629, 39.4001, 1, 0, 10900),
(312, 629.335, 1373.01, 4.11271, -138.7, 2, 0, 10900),
(313, 639.357, 1381.91, 4.1127, 28.3, 1, 0, 10900),
(314, 643.774, 1384.27, 4.1127, -152.3, 2, 0, 10900),
(315, 689.636, 1407.02, 4.0885, 28.1, 1, 0, 10900),
(316, 694.095, 1409.29, 4.0985, -154, 2, 0, 10900),
(317, 742.059, 1439.06, 4.1112, 28, 1, 0, 10900),
(318, 746.431, 1441.43, 4.11119, -151.2, 2, 0, 10900),
(319, 763.673, 1451.51, 4.11119, 17.8, 1, 0, 10900),
(320, 768.374, 1453.15, 4.11119, -159.6, 2, 0, 10900),
(321, 814.035, 1465.97, 4.1063, -2.20001, 1, 0, 10900),
(322, 819.037, 1465.66, 4.10119, 175, 2, 0, 10900),
(323, 858.885, 1431.41, 4.1163, -82.9, 1, 0, 10900),
(324, 859.475, 1426.43, 4.1143, 96.3, 2, 0, 10900),
(325, 849.605, 1385.27, 4.1063, -117.9, 1, 0, 10900),
(326, 847.284, 1380.91, 4.1063, 61.6, 2, 0, 10900),
(327, 764.199, 1428.03, 4.10629, -158.5, 1, 0, 10900),
(328, 759.837, 1425.75, 4.0963, 33.3, 2, 0, 10900),
(329, 732.201, 1408.81, 4.13273, 33.2, 1, 0, 10900),
(330, 736.542, 1411.23, 4.13273, -155.1, 2, 0, 10900),
(331, 1561.39, -3036.88, 2.44257, 20.2, 1, 0, 16036),
(332, 1567.75, -3034.53, 2.43259, -160.3, 2, 0, 16036),
(333, 631.118, 1323.59, 4.12783, -1.2, 1, 0, 10900),
(334, 636.088, 1323.62, 4.12593, -178, 2, 0, 10900),
(335, 604.892, 1322.43, 4.09618, 5.99999, 1, 0, 10900),
(336, 609.878, 1322.93, 4.09654, -174.8, 2, 0, 10900),
(337, 651.097, 1340.84, 4.09632, -1.4, 1, 0, 10900),
(338, 656.058, 1340.61, 4.09273, 175.9, 2, 0, 10900),
(339, 742.799, 1232.82, 4.11063, -1.1, 1, 0, 10900),
(340, 747.811, 1232.55, 4.11631, 174.8, 2, 0, 10900),
(341, 673.705, 1026.93, 4.11421, -2.8, 1, 0, 10900),
(342, 678.671, 1026.61, 4.11421, 175.4, 2, 0, 10900),
(343, 643.711, 1034.58, 4.1169, -24.1, 1, 0, 10900),
(344, 648.265, 1032.63, 4.1169, 157.6, 2, 0, 10900),
(345, 601.524, 1064.84, 4.10632, -50.5, 1, 0, 10900),
(346, 604.71, 1060.96, 4.10632, 129.2, 2, 0, 10900),
(347, 613.219, 1079.76, 4.08632, -44.7, 1, 0, 10900),
(348, 616.687, 1076.23, 4.08994, 133.6, 2, 0, 10900),
(349, 628.245, 1067.97, 4.11995, -33.1, 1, 0, 10900),
(350, 632.455, 1065.28, 4.11213, 147.7, 2, 0, 10900),
(351, 768.06, 1081.18, 4.0822, 40.4001, 1, 0, 10900),
(352, 771.826, 1084.44, 4.06994, -138.9, 2, 0, 10900),
(353, 821.517, 1162.29, 4.11631, 76.7, 1, 0, 10900),
(354, 822.723, 1167.09, 4.11995, -104.9, 2, 0, 10900),
(355, 1503.02, -3076.4, 3.03039, 48.4, 1, 1, 16038),
(356, 707.543, 1146.2, 4.09631, -115.9, 1, 0, 10900),
(357, 705.172, 1141.85, 4.09631, 58.4999, 2, 0, 10900),
(358, 622.156, 1237.13, 4.09787, -6.6, 1, 0, 10900),
(359, 627.135, 1236.6, 4.09631, 174.2, 2, 0, 10900),
(360, 802.81, 1332.08, 4.1063, 67.0999, 1, 0, 10900),
(361, 804.848, 1336.59, 4.1063, -115.9, 2, 0, 10900),
(362, 700.283, 1391.68, 4.17273, 30.4, 1, 0, 10900),
(363, 704.608, 1394.12, 4.17273, -151.8, 2, 0, 10900),
(364, 1899.47, -3102.31, 2.53545, 58.6999, 1, 0, 16036),
(365, 1903.14, -3096.58, 2.53545, -124.7, 2, 0, 16036),
(366, 591.086, 1169.56, 4.11632, -96.2, 1, 0, 10900),
(367, 590.578, 1164.64, 4.11631, 84.2, 2, 0, 10900),
(368, 1445.9, -3227.74, 2.93527, -31.6001, 1, 1, 16041),
(369, 1380.11, -3190.68, 2.68527, 150.1, 1, 0, 16036),
(370, 1374.19, -3187.33, 2.68527, -29.7, 2, 0, 16036),
(371, 2544.21, -3264.48, 3.02718, -60.6, 1, 1, 16038),
(372, 568.695, 1136.61, 4.1227, -82.6, 1, 0, 10900),
(373, 569.232, 1131.63, 4.1227, 94.7999, 2, 0, 10900),
(374, 1493.56, -3271.81, 2.93527, -39.2, 1, 1, 16040),
(375, 1602.96, -3328.32, 3.01662, -39.2, 1, 1, 16038),
(376, 593.468, 1186.11, 4.09632, -102.3, 1, 0, 10900),
(377, 592.466, 1181.24, 4.09631, 78.8999, 2, 0, 10900),
(378, 1635.49, -3326.63, 3.01662, -40, 1, 1, 16039),
(379, 1658.88, -3378.35, 2.38663, -53, 1, 0, 16036),
(380, 1662.79, -3383.92, 2.38663, 122.6, 2, 0, 16036),
(381, 1725.39, -3413.8, 3.00025, -24.9, 1, 1, 16038),
(382, 2085.85, -3290.38, 2.95226, -90.2, 1, 1, 16037),
(383, 1730.53, -3438.87, 2.44662, 162, 1, 0, 16036),
(384, 1724.05, -3436.78, 2.44663, -18.4, 2, 0, 16036),
(385, 704.536, 1167.98, 4.11632, -56.8, 1, 0, 10900),
(386, 706.976, 1163.67, 4.11213, 115.7, 2, 0, 10900),
(387, 1794.36, -3461.02, 2.92663, -20.7, 1, 1, 16037),
(388, 1893.84, -3479.44, 2.92663, -6, 1, 0, 16036),
(389, 1900.68, -3480.13, 2.93663, 174.1, 2, 0, 16036),
(390, 1986.55, -3480.31, 3.01226, 0, 1, 1, 16039),
(391, 1951.32, -3362.85, 2.98509, -123.8, 1, 0, 16036),
(392, 1947.43, -3368.43, 2.96226, 53.6, 2, 0, 16036),
(393, 1967.87, -3459.86, 2.94226, 0, 1, 1, 16041),
(394, 1973.3, -3259.91, 2.70054, -88.3998, 1, 0, 16036),
(395, 1973.53, -3266.72, 2.69054, 91.6001, 2, 0, 16036),
(396, 1971.89, -3163.94, 2.37054, 46.3, 1, 0, 16036),
(397, 1976.6, -3159.04, 2.37456, -134.5, 2, 0, 16036),
(398, 2189.87, -3109.59, 2.90635, 45.1001, 1, 1, 16037),
(399, 2063, -3339.14, 2.91226, -94.9, 1, 1, 16040),
(400, 2095.21, -3121.65, 2.67836, 1.8, 1, 0, 16036),
(401, 2102, -3121.46, 2.67763, -179, 2, 0, 16036),
(402, 2043.34, -3124.87, 2.92983, 1, 1, 1, 16040),
(403, 2005.16, -3169.14, 2.98032, 10.2, 1, 0, 16036),
(404, 2011.93, -3167.85, 2.97031, -169.5, 2, 0, 16036),
(405, 735.276, 1037.82, 4.11632, -165.7, 1, 0, 10900),
(406, 730.474, 1036.6, 4.11631, 13.9, 2, 0, 10900),
(407, 2090.02, -2922.98, 2.72266, -71, 1, 0, 16036),
(408, 2092.14, -2929.03, 2.72266, 109, 2, 0, 16036),
(409, 766.981, 1230.95, 4.11063, -3.6, 1, 0, 10900),
(410, 771.963, 1230.59, 4.11063, 175.4, 2, 0, 10900),
(411, 2085.1, -3402.59, 3.01226, -89.9, 1, 1, 16039),
(412, 2148.27, -3473.3, 3.03852, 4.8, 1, 1, 16038),
(413, 666.293, 1160.75, 4.11995, -95.3, 1, 0, 10900),
(414, 665.951, 1155.78, 4.11632, 87.2, 2, 0, 10900),
(415, -3181.25, 827.027, 7.11221, 90.5, 1, 2, 14584),
(416, -3181.28, 831.927, 7.12193, -89.3999, 2, 2, 14584),
(417, 1947.06, -45.7163, 7.11109, 0, 1, 3, 14584),
(418, 1951.96, -45.7275, 7.09801, -179.9, 2, 3, 14584),
(419, 4008.4, 3858.81, 8.61118, -111.3, 1, 4, 14584),
(420, 4006.66, 3854.21, 8.61002, 69.1, 2, 4, 14584),
(421, 1990.29, 1305.66, 23.9003, 0, 1, 0, 10919),
(422, 1996.6, 1305.66, 24.1203, -180, 2, 0, 10919),
(423, 2013.04, 1264.84, 24.925, 0, 1, 0, 10919),
(424, 2019.38, 1264.84, 24.925, 179.6, 2, 0, 10919);

--
-- Индексы сохранённых таблиц
--

--
-- Индексы таблицы `accounts_canvasdev`
--
ALTER TABLE `accounts_canvasdev`
  ADD PRIMARY KEY (`id`),
  ADD KEY `name` (`name`),
  ADD KEY `email` (`email`),
  ADD KEY `phone` (`phone`);

--
-- Индексы таблицы `action_log`
--
ALTER TABLE `action_log`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `anticheat_settings`
--
ALTER TABLE `anticheat_settings`
  ADD UNIQUE KEY `ac_code` (`ac_code`);

--
-- Индексы таблицы `arenda_cars`
--
ALTER TABLE `arenda_cars`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `auction`
--
ALTER TABLE `auction`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `auction_bet`
--
ALTER TABLE `auction_bet`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `banip_list`
--
ALTER TABLE `banip_list`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `bank_accounts`
--
ALTER TABLE `bank_accounts`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `bank_accounts_log`
--
ALTER TABLE `bank_accounts_log`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `ban_list`
--
ALTER TABLE `ban_list`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `billboard`
--
ALTER TABLE `billboard`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `bugreport`
--
ALTER TABLE `bugreport`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `business`
--
ALTER TABLE `business`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `business_gps`
--
ALTER TABLE `business_gps`
  ADD PRIMARY KEY (`id`),
  ADD KEY `bid` (`bid`);

--
-- Индексы таблицы `business_profit`
--
ALTER TABLE `business_profit`
  ADD PRIMARY KEY (`id`),
  ADD KEY `fid` (`business_id`);

--
-- Индексы таблицы `carsharing_cars`
--
ALTER TABLE `carsharing_cars`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `cars_accessories`
--
ALTER TABLE `cars_accessories`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `car_market`
--
ALTER TABLE `car_market`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `change_names`
--
ALTER TABLE `change_names`
  ADD PRIMARY KEY (`id`),
  ADD KEY `owner_id` (`owner_id`);

--
-- Индексы таблицы `charity`
--
ALTER TABLE `charity`
  ADD PRIMARY KEY (`id`),
  ADD KEY `uid` (`uid`);

--
-- Индексы таблицы `create_objects`
--
ALTER TABLE `create_objects`
  ADD PRIMARY KEY (`Name`);

--
-- Индексы таблицы `daily_rewards_players`
--
ALTER TABLE `daily_rewards_players`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `decoration`
--
ALTER TABLE `decoration`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `donate_items`
--
ALTER TABLE `donate_items`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `donate_log`
--
ALTER TABLE `donate_log`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `donations`
--
ALTER TABLE `donations`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `entrances`
--
ALTER TABLE `entrances`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `family`
--
ALTER TABLE `family`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `family_cars`
--
ALTER TABLE `family_cars`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `family_log`
--
ALTER TABLE `family_log`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `fuel_orders`
--
ALTER TABLE `fuel_orders`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `gang_repositories`
--
ALTER TABLE `gang_repositories`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `gang_zones`
--
ALTER TABLE `gang_zones`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `garage`
--
ALTER TABLE `garage`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `gardens`
--
ALTER TABLE `gardens`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `hardware_bans`
--
ALTER TABLE `hardware_bans`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `hotels`
--
ALTER TABLE `hotels`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `houses`
--
ALTER TABLE `houses`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `houses_renters`
--
ALTER TABLE `houses_renters`
  ADD PRIMARY KEY (`id`),
  ADD KEY `owner_id` (`owner_id`),
  ADD KEY `house_id` (`house_id`);

--
-- Индексы таблицы `items`
--
ALTER TABLE `items`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `items_log`
--
ALTER TABLE `items_log`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `jobs_player`
--
ALTER TABLE `jobs_player`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `kiosk`
--
ALTER TABLE `kiosk`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `kiosks_items`
--
ALTER TABLE `kiosks_items`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `localban`
--
ALTER TABLE `localban`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `marktplc`
--
ALTER TABLE `marktplc`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `money_log`
--
ALTER TABLE `money_log`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `mutes`
--
ALTER TABLE `mutes`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `mytplist`
--
ALTER TABLE `mytplist`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `neftenasos`
--
ALTER TABLE `neftenasos`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `notification`
--
ALTER TABLE `notification`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `orders`
--
ALTER TABLE `orders`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `ownable_cars`
--
ALTER TABLE `ownable_cars`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `ownable_trailer`
--
ALTER TABLE `ownable_trailer`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `phone_books`
--
ALTER TABLE `phone_books`
  ADD PRIMARY KEY (`id`),
  ADD KEY `owner_id` (`owner_id`);

--
-- Индексы таблицы `player_bonus`
--
ALTER TABLE `player_bonus`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `player_settings`
--
ALTER TABLE `player_settings`
  ADD PRIMARY KEY (`uid`);

--
-- Индексы таблицы `police_tablet`
--
ALTER TABLE `police_tablet`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `prizes`
--
ALTER TABLE `prizes`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `prizes_code`
--
ALTER TABLE `prizes_code`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `promocode_activations`
--
ALTER TABLE `promocode_activations`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `raffle_shop`
--
ALTER TABLE `raffle_shop`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `report_mesage`
--
ALTER TABLE `report_mesage`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `report_ticket`
--
ALTER TABLE `report_ticket`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `repositories`
--
ALTER TABLE `repositories`
  ADD PRIMARY KEY (`id`),
  ADD KEY `type` (`type`,`action_id`);

--
-- Индексы таблицы `server_config`
--
ALTER TABLE `server_config`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `test_user`
--
ALTER TABLE `test_user`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `tickets`
--
ALTER TABLE `tickets`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `tk_cars`
--
ALTER TABLE `tk_cars`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `vorota`
--
ALTER TABLE `vorota`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT для сохранённых таблиц
--

--
-- AUTO_INCREMENT для таблицы `accounts_canvasdev`
--
ALTER TABLE `accounts_canvasdev`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `action_log`
--
ALTER TABLE `action_log`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `arenda_cars`
--
ALTER TABLE `arenda_cars`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `auction`
--
ALTER TABLE `auction`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=1999;

--
-- AUTO_INCREMENT для таблицы `auction_bet`
--
ALTER TABLE `auction_bet`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `banip_list`
--
ALTER TABLE `banip_list`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `bank_accounts`
--
ALTER TABLE `bank_accounts`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `bank_accounts_log`
--
ALTER TABLE `bank_accounts_log`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `ban_list`
--
ALTER TABLE `ban_list`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `billboard`
--
ALTER TABLE `billboard`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=10;

--
-- AUTO_INCREMENT для таблицы `bugreport`
--
ALTER TABLE `bugreport`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `business`
--
ALTER TABLE `business`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=140;

--
-- AUTO_INCREMENT для таблицы `business_gps`
--
ALTER TABLE `business_gps`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `business_profit`
--
ALTER TABLE `business_profit`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `carsharing_cars`
--
ALTER TABLE `carsharing_cars`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=115;

--
-- AUTO_INCREMENT для таблицы `cars_accessories`
--
ALTER TABLE `cars_accessories`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `car_market`
--
ALTER TABLE `car_market`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=343;

--
-- AUTO_INCREMENT для таблицы `change_names`
--
ALTER TABLE `change_names`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `charity`
--
ALTER TABLE `charity`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `daily_rewards_players`
--
ALTER TABLE `daily_rewards_players`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `decoration`
--
ALTER TABLE `decoration`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `donate_items`
--
ALTER TABLE `donate_items`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=387;

--
-- AUTO_INCREMENT для таблицы `donate_log`
--
ALTER TABLE `donate_log`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `donations`
--
ALTER TABLE `donations`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `entrances`
--
ALTER TABLE `entrances`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `family`
--
ALTER TABLE `family`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `family_cars`
--
ALTER TABLE `family_cars`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `family_log`
--
ALTER TABLE `family_log`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `fuel_orders`
--
ALTER TABLE `fuel_orders`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `gang_repositories`
--
ALTER TABLE `gang_repositories`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT для таблицы `gang_zones`
--
ALTER TABLE `gang_zones`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `garage`
--
ALTER TABLE `garage`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=289;

--
-- AUTO_INCREMENT для таблицы `gardens`
--
ALTER TABLE `gardens`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=339;

--
-- AUTO_INCREMENT для таблицы `hardware_bans`
--
ALTER TABLE `hardware_bans`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `hotels`
--
ALTER TABLE `hotels`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `houses`
--
ALTER TABLE `houses`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=771;

--
-- AUTO_INCREMENT для таблицы `houses_renters`
--
ALTER TABLE `houses_renters`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `items`
--
ALTER TABLE `items`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `items_log`
--
ALTER TABLE `items_log`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `jobs_player`
--
ALTER TABLE `jobs_player`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `kiosk`
--
ALTER TABLE `kiosk`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=34;

--
-- AUTO_INCREMENT для таблицы `kiosks_items`
--
ALTER TABLE `kiosks_items`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `localban`
--
ALTER TABLE `localban`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `marktplc`
--
ALTER TABLE `marktplc`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `money_log`
--
ALTER TABLE `money_log`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `mutes`
--
ALTER TABLE `mutes`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `mytplist`
--
ALTER TABLE `mytplist`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `neftenasos`
--
ALTER TABLE `neftenasos`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;

--
-- AUTO_INCREMENT для таблицы `notification`
--
ALTER TABLE `notification`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `orders`
--
ALTER TABLE `orders`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `ownable_cars`
--
ALTER TABLE `ownable_cars`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `ownable_trailer`
--
ALTER TABLE `ownable_trailer`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `phone_books`
--
ALTER TABLE `phone_books`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `player_bonus`
--
ALTER TABLE `player_bonus`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `player_settings`
--
ALTER TABLE `player_settings`
  MODIFY `uid` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `police_tablet`
--
ALTER TABLE `police_tablet`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `prizes`
--
ALTER TABLE `prizes`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `prizes_code`
--
ALTER TABLE `prizes_code`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `promocode_activations`
--
ALTER TABLE `promocode_activations`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `raffle_shop`
--
ALTER TABLE `raffle_shop`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `report_mesage`
--
ALTER TABLE `report_mesage`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `report_ticket`
--
ALTER TABLE `report_ticket`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `repositories`
--
ALTER TABLE `repositories`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=13;

--
-- AUTO_INCREMENT для таблицы `server_config`
--
ALTER TABLE `server_config`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT для таблицы `test_user`
--
ALTER TABLE `test_user`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `tickets`
--
ALTER TABLE `tickets`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT для таблицы `tk_cars`
--
ALTER TABLE `tk_cars`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=73;

--
-- AUTO_INCREMENT для таблицы `vorota`
--
ALTER TABLE `vorota`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=546;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
