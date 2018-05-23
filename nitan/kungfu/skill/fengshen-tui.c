#include <ansi.h>
inherit SKILL;
//By dream ¼òµ¥°æ£¬´ýÐÞ¸Ä

string *dodge_msg = ({
    "Ö»¼û$nÒ»ÕÐ[1;32m¡¸²¶·ç×½Ó°¡¹[2;37;0m£¬Éí»¯ÎÞÓ°£¬¿ìÈôÁ÷ÐÇµØ¶ã¹ýÁË$NÕâÒ»ÕÐ¡£\n",
    "$n¼±ÓÃÒ»ÕÐ[1;36m¡¸·çÖÐ¾¢²Ý¡¹[2;37;0m£¬Ïòºó×Ý³öÊýÕÉÖ®Ô¶£¬±Ü¿ªÁË$NµÄÁèÀ÷¹¥ÊÆ¡£\n",
    "$nÊ¹³ö[1;34m¡¸±©Óê¿ñ·ç¡¹[2;37;0m£¬ÃÍÁÒµÄÆøÊÆÑ¹µÄ$NÈ«²¿¹¥»÷²»×Ô¾õµØÂäÁË¿Õ¡£\n"
    "µ«ÊÇ$nÉíÓ°¿ìÈçÉÁµç£¬Ò»ÕÐ[1;31m¡¸À×À÷·çÐÐ¡¹[2;37;0m£¬ÇáËÉ¶ã¹ýÁË$NµÄ¹¥»÷¡£\n",
    "$nÉíËæÒâ×ª£¬Ò»ÕÐ[1;35m¡¸·ç¾íÂ¥²Ð¡¹[2;37;0m±Ü¹ýÁË$NÕâÒ»ÕÐ¡£\n",
    "$nÊ¹ÓÃÒ»ÕÐ[1;37m¡¸Éñ·çÅ­º¿¡¹[2;37;0m£¬¶ÙÊ±$NÁ¬$nµÄÉíÓ°¶¼¿´²»¼ûÁË¡£\n"
});

int valid_enable(string usage) 
{ 
        return usage == "dodge"; 
}

int valid_learn(object me)
{
        if ((int)me->query_skill("dodge", 1) < 100)
                return notify_fail("Äã»ù±¾Çá¹¦ÐÞÎªÓÐÏÞ£¬ÄÑÒÔÐÞÁ¶·çÉñÍÈ¡£\n");

        if ((int)me->query_skill("bingxin-jue", 1) < 80)
                return notify_fail("Äã±ùÐÄ¾öÐÞÎª²»¹»£¬ÄÑÒÔÐÞÁ¶·çÉñÍÈ¡£\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("ÄãÄÚÁ¦ÐÞÎªÌ«Ç³£¬ÄÑÒÔÐÞÁ¶·çÉñÍÈ¡£\n");
        return 1;
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("fengshen-tui", 1);
        if (lvl < 50)  return 0;
        if (lvl < 100) return 20;
        if (lvl < 150) return 30;
        if (lvl < 200) return 50;
        if (lvl < 250) return 70;
        return 80;
}

int practice_skill(object me)
{
        if( query("qi", me)<200 )
                return notify_fail("ÄãµÄÌåÁ¦Ì«²îÁË£¬²»ÄÜÁ··çÉñÍÈ¡£\n");

        if( query("neili", me)<200 )
                return notify_fail("ÄãµÄÄÚÁ¦Ì«²îÁË£¬²»ÄÜÁ·Ï°·çÉñÍÈ¡£\n");

        me->receive_damage("qi", 60);
        addn("neili", -60, me);
        return 1;
}
string perform_action_file(string action)
{
      return __DIR__"fengshen-tui/" + action;
}
