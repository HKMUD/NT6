//wuying-jian ÉÙÁÖÎŞÓ°½£
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$NÎÕ½ôÊÖÖĞ$wÒ»ÕĞ¡¸À´È¥×ÔÈç¡¹µãÏò$nµÄ$l",
        "force" : 50,
        "dodge" : 40,
        "damage" : 20,
        "lvl"    : 0,
        "skill_name" : "À´È¥×ÔÈç", 
        "damage_type" : "´ÌÉË"
]),
([      "action" : "$NÒ»ÕĞ¡¸ÈÕÔÂÎŞ¹â¡¹£¬ÎŞÊı$wÉÏÏÂ´Ì³ö£¬Ö±Ïò$n±ÆÈ¥",
        "force" : 70,
        "dodge" : 10,
        "damage" : 30,
        "lvl"    : 20,
        "skill_name" : "ÈÕÔÂÎŞ¹â",
        "damage_type" : "´ÌÉË"
]),
([      "action" : "$NÏòÇ°¿çÉÏÒ»²½£¬ÊÖÖĞ$wÊ¹³ö¡¸½£Æø·âºí¡¹Ö±´Ì$nµÄºí²¿",
        "force" : 90,
        "dodge" : 80,
        "damage" : 50,
        "lvl"    : 40,
        "skill_name" : "½£Æø·âºí",
        "damage_type" : "´ÌÉË"
]),
([      "action" : "$NĞé»ĞÒ»²½£¬Ê¹³ö¡¸ĞÄ¾³ÈçË®¡¹ÊÖÖĞ$wÖ±´Ì$nµÄÒªº¦",
        "force" : 90,
        "dodge" : 60,
        "damage" : 80,
        "lvl"    : 60,
        "skill_name" : "ĞÄ¾³ÈçË®",
        "damage_type" : "´ÌÉË"
]),
([      "action" : "Ö»¼û$NÂÕÆğÊÖÖĞµÄ$w£¬Ê¹³ö¡¸·ğ¹âÆÕÕÕ¡¹Íòµã½ğ¹âÖ±Éä$n",
        "force" : 90,
        "dodge" : 70,
        "damage" : 110,
        "lvl"    : 80,
        "skill_name" : "·ğ¹âÆÕÕÕ",
        "damage_type" : "´ÌÉË"
]),
([      "action" : "$NÂÕÆğÊÖÖĞµÄ$w£¬Ê¹³ö¡¸·çĞĞÒ¶Âä¡¹ÎŞÊı½£¹âÖ±Éä$n",
        "force" : 120,
        "dodge" : 60,
        "damage" : 120,
        "lvl"    : 100,
        "skill_name" : "·çĞĞÒ¶Âä", 
        "damage_type" : "´ÌÉË"
]),
([      "action" : "$NÊ¹³ö¡¸Éù¶«»÷Î÷¡¹£¬ÊÖÖĞ$wÈç¹ÎÆğ¿ñ·çÒ»°ãÉÁË¸²»¶¨£¬´ÌÏò$n",
        "force" : 200,
        "dodge" : 80,
        "damage" : 140,
        "lvl"    : 120,
        "skill_name" : "Éù¶«»÷Î÷",
        "damage_type" : "´ÌÉË"
]),
([      "action" : "$NËæÊÖÊ¹³ö½£·¨Ö®°ÂÒå¡¸ÎŞÓ°ÎŞ×Ù¡¹£¬ÊÖÖĞ$wÈç¹í÷ÈÒ»°ãÆÌÌì¸ÇµØµÄ´ÌÏò$n",
        "force" : 300,
        "dodge" : 90,
        "damage" : 250,
        "lvl"    : 150,
        "skill_name" : "¡¸ÎŞÓ°ÎŞ×Ù¡¹",
        "damage_type" : "´ÌÉË"
]),
([      "action" : HIY"$NÊ¹³öÎŞÓ°½£·¨Ö®×îÖÕ¾ø¼¼[1;36m¡¸òÔÁú³öË®¡¹[0m,[1;33mÊÖÖĞ$wÓÌÈçòÔÁúÒ»°ã´ÌÏò$n[0m"NOR,
        "force" : 400,
        "dodge" : 100,
        "damage" : 800,
        "lvl"    : 220,
        "skill_name" : "HIY¡¸½£ÆøºÏÒ»¡¹"NOR,
        "damage_type" : "´ÌÉË"
]),



});


int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }

int valid_learn(object me)
{
        if ((int)me->query_skill("hunyuan-yiqi", 1) < 150)
                return notify_fail("ÄãµÄ¡¸»ìÔªÒ»Æø¡¹»ğºò²»¹»£¬ÎŞ·¨Ñ§¡¸ÎŞÓ°½£·¨¡¹¡£\n");
        if( query("max_neili", me)<300 )
                return notify_fail("ÄãµÄÄÚÁ¦Ì«Èõ£¬ÎŞ·¨Á·¡¸ÎŞÓ°½£·¨¡¹¡£\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("wuying-jian",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/4)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("ÄãÊ¹ÓÃµÄÎäÆ÷²»¶Ô¡£\n");
        if( query("qi", me)<50 )
                return notify_fail("ÄãµÄÌåÁ¦²»¹»Á·¡¸ÎŞÓ°½£·¨¡¹¡£\n");
        if( query("neili", me)<50 )
                return notify_fail("ÄãµÄÄÚÁ¦²»¹»Á·¡¸ÎŞÓ°½£·¨¡¹¡£\n");
        me->receive_damage("qi", 40);
        addn("neili", -15, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"wuying-jian/" + action;
}
/*
mixed hit_ob(object me, object victim, int damage_bonus)
{
        if( damage_bonus < 100 ) return 0;

        if( random(damage_bonus/2) > victim->query_str() ) {
//                victim->add("qi", 1 - damage_bonus - 100 * 3 );
                victim->receive_wound("qi", (damage_bonus - 100) / 2 );
                return HIR "ÄãÌıµ½¡¸ßê¡¹Ò»ÉùÇáÏìÒ»µÀ°ÔÆøÆËÌì¶øÀ´£¬ºöÈ»¼ä$nÑªÃ°ÈıÕÉ£¬±»$N½£ÆøËùÉË£¡\n";
        }
}


*/