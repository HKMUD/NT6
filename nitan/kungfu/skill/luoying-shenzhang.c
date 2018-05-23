#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$NË«ÊÖÆ½Éì£¬ÏòÍâÂÓ³ö£¬Ò»Ê½"GRN"¡¸´ºÔÆÕ§Õ¹¡¹"NOR"£¬Ö¸¼âÇáÓ¯Æ¯¶¯£¬ÇáÇá·´µã$nµÄ$l",
        "lvl" : 10,
        "skill_name" : "´ºÔÆÕ§Õ¹"
]),
([        "action" : "$NÓÒÊÖÎåÖ¸»º»ºÒ»ÊÕ£¬Ò»Ê½"HIG"¡¸»Ø·ç·÷Áø¡¹"NOR"£¬ÎåÖ¸ºöÈ»Ò£Ò£·÷Ïò$n£¬$nÖ»¾õµÃÎå¹É¼²·çÏ®Ïò×Ô¼ºÎå´¦´óÑ¨",
        "lvl" : 0,
        "skill_name" : "»Ø·ç·÷Áø"
]),
([        "action" : "$NÍ»È»×İÉíÔ¾Èë°ë¿Õ£¬Ò»¸öÇáÇÉ×ªÉí£¬µ¥ÕÆÅüÂä£¬Ò»Ê½"MAG "¡¸½­³Ç·É»¨¡¹"NOR"£¬ÅÄÏò$nµÄÍ·¶¥",
        "lvl" : 10,
        "skill_name" : "½­³Ç·É»¨"
]),
([        "action" : "$NÍ»È»Ô¾Æğ£¬Ë«ÊÖÁ¬»·£¬ÔËÕÆÈç½££¬ÊÆÈç¼²·çµçÉÁ£¬Ò»Ê½"HIM "¡¸Óê¼±·ç¿ñ¡¹"NOR"£¬¹¥Ïò$nµÄÈ«Éí",
        "lvl" : 10,
        "skill_name" : "Óê¼±·ç¿ñ"
]),
([        "action" : "$N×óÊÖ»ÓÆğ£¬ÕÆĞÄ³¯Ìì£¬Éì³öÓÒÊÖ²¢Â£Ê³Ö¸ÖĞÖ¸£¬Äí¸ö½£¾ö£¬Ò»Ê½"CYN"¡¸ĞÇºÓÔÚÌì¡¹"NOR"£¬Ö±Ö¸$nµÄÖĞÅÌ",
        "lvl" : 20,
        "skill_name" : "ĞÇºÓÔÚÌì"
]),
([        "action" : "$NÍ»È»³éÉí¶øÍË£¬½Ó×ÅÒ»Ê½"HIW"¡¸Á÷»ª·×·É¡¹"NOR"£¬Æ½Éí·ÉÆğ£¬Ë«ÕÆÏò$nµÄºóÄÔÁ¬ÅÄÊıÕÆ",
        "lvl" : 30,
        "skill_name" : "Á÷»ª·×·É"
]),
([        "action" : "$NÍ»È»³éÉíÔ¾Æğ£¬×óÕÆĞ®×Å¾¢·çĞÚÓ¿ÅÄ³ö£¬½Ó×ÅÓÒÕÆ×Ô×óÕÆºóÍ»µØÉì³ö£¬Ò»Ê½"HIR"¡¸²ÊÔÆ×·ÔÂ¡¹"NOR"ÇÀÔÚ×óÕÆÇ°Ïò$nµÄ$lÅÄÈ¥",
        "lvl" : 30,
        "skill_name" : "²ÊÔÆ×·ÔÂ"
]),
([        "action" : "$NÊ¹Ò»Ê½"HIC"¡¸ÌìÈçñ·Â®¡¹"NOR"£¬È«ÉíÍ»È»·ÉËÙĞı×ª£¬Ë«ÕÆºöÇ°ºöºó£¬ÃÍµØÅÄÏò$nµÄĞØ¿Ú",
        "lvl" : 40,
        "skill_name" : "ÌìÈçñ·Â®"
]),
([        "action" : "$NÇ°ºóÒ»Èà£¬Ò»Ê½"HIB"¡¸³¯ÔÆºá¶È¡¹"NOR"£¬»¯ÕÆÈç½££¬Ò»¹ÉÁèÀ÷½£ÆøÏ®Ïò$nµÄÏÂÅÌ",
        "lvl" : 50,
        "skill_name" : "³¯ÔÆºá¶È"
]),
([        "action" : "$NÊ¹Ò»Ê½"HIW"¡¸°×ºç¾­Ìì¡¹"NOR"£¬Ë«ÕÆÎè³öÎŞÊıÈ¦¾¢Æø£¬Ò»»·»·Ïò$nµÄ$lí½È¥",
        "lvl" : 70,
        "skill_name" : "°×ºç¾­Ìì"
]),
([        "action" : "$NË«ÊÖÊ³Ö¸ºÍÖĞÖ¸Ò»ºÍ£¬Ò»Ê½"HIM"¡¸×ÏÆø¶«À´¡¹"NOR"£¬Ò»¹ÉÇ¿ÁÒµÄÆøÁ÷Ó¿Ïò$nµÄÈ«Éí",
        "lvl" : 60,
        "skill_name" : "×ÏÆø¶«À´"
]),
([        "action" : "$NÒ»Ê½"HIC"¡¸ÂäÓ¢ÂşÌì¡¹"NOR"£¬Ë«ÕÆÔÚÉíÇ°¼²×ª£¬ÕÆ»¨·ÉÎè£¬ÆÌÌì¸ÇµØÖ±Ö¸Ïò$n¡£$nÖ»¼ûÂşÌìÕÆ»¨£¬ÑÛ»¨çÔÂÒ¡£",
        "lvl" : 99,
        "skill_name" : "ÂäÓ¢ÂşÌì"
])
});
/*
mapping *action = ({
([      "action" : "$NÓÒÊÖÎåÖ¸»º»ºÒ»ÊÕ£¬Ò»Ê½¡¸»Ø·ç·÷Áø¡¹£¬ÎåÖ¸ºöÈ»·÷Ïò$nÎå´¦´óÑ¨",
        "force"  : 80,
        "attack" : 14,
        "dodge"  : 7,
        "parry"  : 8,
        "damage" : 5,
        "lvl"    : 0,
        "damage_type" : "ÄÚÉË",
        "skill_name"  : "»Ø·ç·÷Áø"
]),
([      "action" : "$N¶¸È»Ò»¸öÇáÇÉ×ªÉí£¬µ¥ÕÆÅüÂä£¬Ò»Ê½¡¸½­³Ç·É»¨¡¹£¬ÅÄÏò$nµÄÍ·¶¥",
        "force"  : 91,
        "attack" : 17,
        "dodge"  : 10,
        "parry"  : 13,
        "damage" : 9,
        "lvl"    : 20,
        "damage_type" : "ğöÉË",
        "skill_name"  : "½­³Ç·É»¨"
]),
([      "action" : "$NÍ»È»Ô¾Æğ£¬Ë«ÊÖÁ¬»·£¬ÔËÕÆÈç½££¬Ò»Ê½¡¸Óê¼±·ç¿ñ¡¹£¬¹¥Ïò$nµÄÈ«Éí",
        "force"  : 108,
        "attack" : 22,
        "dodge"  : 17,
        "parry"  : 15,
        "damage" : 12,
        "lvl"    : 40,
        "damage_type" : "ğöÉË",
        "skill_name"  : "Óê¼±·ç¿ñ"
]),
([      "action" : "$NÍ»È»³éÉí¶øÍË£¬Ò»Ê½¡¸Á÷»ª·×·É¡¹£¬Æ½Éí·ÉÆğ£¬Ë«ÕÆÏò$nÁ¬ÅÄÊıÕÆ",
        "force"  : 180,
        "attack" : 33,
        "dodge"  : 13,
        "parry"  : 16,
        "damage" : 28,
        "lvl"    : 60,
        "damage_type" : "ğöÉË",
        "skill_name"  : "Á÷»ª·×·É"
]),
([      "action" : "$NÍ»È»³éÉíÔ¾Æğ£¬ÓÒÕÆ·­¹ö£¬Ò»Ê½¡¸²ÊÔÆ×·ÔÂ¡¹ÇÀÔÚ×óÕÆÇ°Ïò$nµÄ$lÅÄÈ¥",
        "force"  : 210,
        "attack" : 38,
        "dodge"  : 30,
        "parry"  : 25,
        "damage" : 33,
        "lvl"    : 80,
        "damage_type" : "ğöÉË",
        "skill_name"  : "²ÊÔÆ×·ÔÂ"
]),
([      "action" : "$NÊ¹Ò»Ê½¡¸°×ºç¾­Ìì¡¹£¬Ë«ÕÆÎè³öÎŞÊıÈ¦¾¢Æø£¬Ò»»·»·Ïò$nµÄ$lí½È¥",
        "force"  : 310,
        "attack" : 72,
        "dodge"  : 41,
        "parry"  : 55,
        "damage" : 68,
        "lvl"    : 100,
        "damage_type" : "ÄÚÉË",
        "skill_name"  : "°×ºç¾­Ìì"
]),
([      "action" : "$NÒ»Ê½¡¸ÂäÓ¢ÂşÌì¡¹£¬Ë«ÕÆÔÚÉíÇ°¼²×ª£¬ÕÆ»¨·ÉÎè£¬ÆÌÌì¸ÇµØÖ±Ö¸Ïò$n",
        "force"  : 378,
        "attack" : 84,
        "dodge"  : 41,
        "parry"  : 65,
        "damage" : 103,
        "lvl"    : 120,
        "damage_type" : "ğöÉË",
        "skill_name"  : "ÂäÓ¢ÂşÌì"
]),
//ĞÂÔöÈıÕĞ
([      "action" : "[1;32m$NÒ»Ê½¡¸Áø¼ªÏé¡¹£¬Ë«ÕÆÈçÁøĞõ°ãÔÚĞØÇ°°Ú¶¯£¬¶ÙÊ±Ò»µÀµÀ°µ¾¢¿ìËÙ³åÏò$n[2;37;0m",
        "force"  : 400,
        "attack" : 200,
        "dodge"  : 200,
        "parry"  : 200,
        "damage" : 250,
        "lvl"    : 300,
        "damage_type" : "ÄÚÉË",
        "skill_name"  : "[1;32mÁø¼ªÏé[2;37;0m"
]),
([      "action" : "[1;37m$NµÄÂäÓ¢ÉñÕÆÒÑĞŞÁ¶ÖÁ´ó³É£¬Ò»ÕĞ¡¸»¡ÔÂÕ¶¡¹£¬ÃÍÈ»Áè¿Õ·ÉÆğ£¬µ±Í·Ïò$nÕ¶È¥[2;37;0m",
        "force"  : 500,
        "attack" : 300,
        "dodge"  : 300,
        "parry"  : 300,
        "damage" : 350,
        "lvl"    : 350,
        "damage_type" : "ÄÚÉË",
        "skill_name"  : "[1;37m»¡ÔÂÕ¶[2;37;0m"
]),
([      "action" : "[1;36m$NµÄÂäÓ¢ÉñÕÆÒÑÈë·µè±¹éÕæ¾³½ç£¬ÔËÆğÈ«ÉíÄÚÁ¦£¬Ò»ÕĞ¡¸±ÌÌÎËÌ¡¹£¬Èçº£ÀË°ãµÄ

ÄÚÁ¦Ïò$nÓ¿È¥£¬¶ÙÊ±ÈıÕÉ·¶Î§ÄÚÉ³Ê¯·ÉĞı£¬ÑÛ¼û$nÒÑÎŞ´¦¿ÉÌÓ[2;37;0m",
        "force"  : 850,
        "attack" : 500,
        "dodge"  : 500,
        "parry"  : 500,
        "damage" : 750,
        "lvl"    : 400,
        "damage_type" : "ÄÚÉË",
        "skill_name"  : "[1;36m±ÌÌÎËÌ[2;37;0m"
])
});
*/
int valid_enable(string usage)
{
        return usage == "strike" || usage == "parry";
}

int valid_combine(string combo)
{
        return combo == "xuanfeng-tui";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("Á·ÂäÓ¢Éñ½£ÕÆ±ØĞë¿ÕÊÖ¡£\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("ÄãµÄ»ù±¾ÄÚ¹¦»ğºò²»¹»£¬ÎŞ·¨Ñ§ÂäÓ¢Éñ½£ÕÆ¡£\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("ÄãµÄÄÚÁ¦Ì«Èõ£¬ÎŞ·¨Á·ÂäÓ¢Éñ½£ÕÆ¡£\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("luoying-shenzhang", 1))
                return notify_fail("ÄãµÄ»ù±¾ÕÆ·¨Ë®Æ½ÓĞÏŞ£¬ÎŞ·¨Áì»á¸ü¸ßÉîµÄÂäÓ¢Éñ½£ÕÆ¡£\n");

        /*
        if( query("character", me) == "ÒõÏÕ¼éÕ©" )
                return notify_fail("Ñ§Ï°ÂäÓ¢Éñ½£ÕÆĞèÒª²©´óµÄĞØ»³£¬Ã»ÓĞ´ËµÈĞØ»³ÊÇÎŞ·¨ÁìÎòµÄ¡£\n");
        */

        if( query("str", me)<22 )
                return notify_fail("ÄãÏÈÌì±ÛÁ¦²»×ã£¬ÎŞ·¨ĞŞÁ¶ÂäÓ¢Éñ½£ÕÆ¡£\n");

        if ((int)me->query_skill("strike", 1) < 200)
                return notify_fail("ÄãµÄ»ù±¾ÕÆ·¨²»¹»æµÊì£¬ÎŞ·¨ĞŞÁ¶ÂäÓ¢Éñ½£ÕÆ¡£\n");

        if ((int)me->query_skill("strike", 1) < 200)
                return notify_fail("ÄãµÄ»ù±¾ÕÆ·¨²»¹»æµÊì£¬ÎŞ·¨ĞŞÁ¶ÂäÓ¢Éñ½£ÕÆ¡£\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -35;
        int d_e2 = -15;
        int p_e1 = -45;
        int p_e2 = -35;
        int f_e1 = 180;
        int f_e2 = 280;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("luoying-shenzhang", 1);
        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* »ñµÃÕĞÊıĞòºÅÉÏÏŞ */
                        break;
                }
        seq = random(seq);       /* Ñ¡Ôñ³öÊÖÕĞÊıĞòºÅ */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "ÄÚÉË" : "ğöÉË",
        ]);
}

int practice_skill(object me)
{
        if( query("qi", me)<300 )
                return notify_fail("ÄãµÄÌåÁ¦Ì«µÍÁË¡£\n");

        if( query("neili", me)<100 )
                return notify_fail("ÄãµÄÄÚÁ¦²»¹»Á·ÂäÓ¢Éñ½£ÕÆ¡£\n");

        me->receive_damage("qi", 45);
        addn("neili", -40, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"luoying-shenzhang/" + action;
}

int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\nÂäÓ¢Éñ½£ÕÆ£º"NOR"\n");
        write(@HELP

    ÂäÓ¢Éñ½£ÕÆÍÑÌ¥ÓÚÂäÓ¢Éñ½££¬ÒÔÕÆ´ú½££¬ÍşÁ¦²»Ñ·¡£
    ¿ÉÓëĞı·çÉ¨Ò¶ÍÈ»¥±¸¡£

        Ñ§Ï°ÒªÇó£º
                ±Ì²¨Éñ¹¦15¼¶
                ÄÚÁ¦100
HELP
        );
        return 1;
}
