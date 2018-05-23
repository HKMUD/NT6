// This program is a part of NITAN MudLIB
// luowang-club.c ½ôÄÇÂŞÍõ¹÷

#include <ansi.h> 
#include <combat.h>

inherit SKILL; 

mapping *action = ({ 
([      "action" :
       "$NÊÖÖĞµÄ¹÷ÉÒÓÉÏÂÍùÉÏÒ»ÁÃ,½ô½Ó×ÅÒ»ÕĞ[Ë³·ç´òÆì],ÄÇ¹÷Î²Ö± Íù$nµÄ$l´òÈ¥",     
       "force"  : 350, 
       "attack" : 220, 
       "dodge"  : -10, 
       "parry"  : -100, 
       "damage" : 230, 
       "damage_type": "ÓÙÉË" 
]), 
([      "action" :"$Nµ¥ÍÈµãµØ£¬ÏòÉÏ°Î³öÕÉÓà£¬$w·ÉÎè»Ã³öÎŞÊı»ÃÓ°½«
$nÕÖ×¡£¬¿ÚÖĞ´óºÈÒ»Éù[Ñ©»¨¸Ç¶¥]£¬Ö»Ìı¹÷´ø·çÉùÎØÎØ×÷ÏìÏò$nµÄ$1ÅüÈ¥",     
       "force"  : 380, 
       "attack" : 200, 
       "dodge"  : -5, 
       "parry"  : -80, 
       "damage" : 250, 
       "damage_type": "ÓÙÉË" 
]), 
([      "action" : "$N°Ñ$wÒ»¼Ü£¬µ²×¡ÁË$nµÄÈ¥Â·£¬$NÊÖÖĞµÄ$wÒ»Õñ£¬´øÆğÁËÍòÕÉ½ğ¹â£¬
¡¡¡¡¡¡´ÓÕâÆ¬¹âÃ¢ÖĞ³å³öÒ»µÀÇåÑÌ£¬Ö±Ïò$nµÄ$1±¼È¥£¬ÕıÊÇÒ»ÕĞ£Û²¦ÔÆ¼ûÈÕ£İ",
       "force"  : 400, 
       "attack" : 200, 
       "dodge"  : -40, 
       "parry"  : -105, 
       "damage" : 280, 
       "damage_type": "´ÌÉË" 
]), 
([      "action" :       "$NÊÖÖĞµÄ$wÒ»Õñ£¬ÒÔ¹÷ĞĞµ¶Ê½£¬´ó¿ª´óãØ,       
       $w»¯×öÁùµÀºÚÓ°Ïò$nµÄ$1¼¯ÖĞÅüÈ¥",      
       "force"  : 420, 
       "attack" : 180, 
       "dodge"  : -15, 
       "parry"  : -80, 
       "damage" : 280, 
       "damage_type": "ÓÙÉË" 
]), 
([      "action" : "$NÉíÌåÏòºóÒ»×ª,´óºÈ:[ÎÚÁú°ÚÎ²],$w»¯×öÊıµÀ»ÃÓ°É¨Ïò$nµÄÑü²¿", 
       "force"  : 420, 
       "attack" : 190, 
       "dodge"  : -10, 
       "parry"  : -100, 
       "damage" : 290, 
       "damage_type": "ÕğÉË"
]), 
([     "action" : "$NÉíĞĞÒ»Õ¹,»¯Îª[Ñà×Ó´©ÁÖ]Ê½,ÊÖÖĞµÄ$w¿ìÈçÉÁµçµØ´ÌÏò$nµÄµÄ$l",
       "force"  : 450,
       "attack" : 150,
       "dodge"  : -20,
       "parry"  : -120,
       "damage" : 310,
       "damage_type": "´ÌÉË"
]), 
([     "action" : "$NÉíÌåÍùºóÒ»¶Ù,»»ÒÔÎÕÇ¹µÄÊÖ·¨,Ò»Ê½[òÔÁú³öË®],ÊÖÖĞµÄ$wÍù$nµÄ$l´ÌÈ¥",
       "force"  : 520, 
       "force" : 460, 
       "attack" : 160, 
       "dodge"  : -40, 
       "parry"  : -100, 
       "damage" : 90, 
       "damage_type": "´ÌÉË" 
]), 
([      "action" : "$NÊÖÖĞµÄ$wÎèÁË¸ö¹÷»¨£¬µ¥ÍÈ¶ÀÁ¢£¬$wÏòºóÒ»´ø£¬¿ÚÖĞ´óºÈÒ»Éù
¡¡¡¡¡¡¡¡[¶ÀÅü»ªÉ½]£¬Ö»Ìı$w´øÒ»ÉùºôĞ¥Ïò$nµÄ$1ÅüÈ¥",
       "force"  : 490, 
       "attack" : 220, 
       "dodge"  : -10, 
       "parry"  : -75, 
       "damage" : 320, 
       "damage_type": "ÓÙÉË" 
]), 
([      "action" : "$NÑüÒ»°Ú£¬Ë«ÍÈË³ÊÆÅÌÍÈ×øÏÂ£¬ÊÖÖĞ$wÒ»¶¶£¬Ò»Ê½£ÛÏ¬Å£ÍûÔÂ],
       ÊÖÖĞµÄ$wÊÆÈç³¤ºç£¬ÓÉÏÂÍù$nµÄ$1´ÌÈ¥",    
       "force"  : 500, 
       "attack" : 150, 
       "dodge"  : -30, 
       "parry"  : -110, 
       "damage" : 340, 
       "damage_type": "´ÌÉË" 
]), 
([      "action" : "$NÊÖÖĞµÄ$w×óÓÒÀ¹É¨£¬Ò»°Ñ°Ñ$nÈ¦×¡,½ô½Ó×Å£¬$NÓÃ$w°Ñ$nÒ»Ìô£       
        ³¤Ğ¥Ò»Éù:[ÂŞºº²«»¢],¹÷ÉÒ¾¶Ö±Ïò$nµÄ$1ÅüÈ¥",           
       "dodge"  : -25, 
       "force"  : 500, 
       "attack" : 170, 
       "dodge"  : -70, 
       "parry"  : -55, 
       "damage" : 350, 
       "damage_type": "ÓÙÉË" 
]), 
([      "action" : "$NÊ¹³öÒ»ÕĞ[ÌìÂíĞĞ¿Õ],ÊÖÖĞµÄ$wÇáÓ¯×ÔÈçµØ»ÓÈ÷£¬Ïò$nµÄ$1µã»÷¹ıÈ¥",
       "force" : 510, 
       "attack" : 185, 
       "dodge"  : -30, 
       "parry"  : -100, 
       "damage" : 410, 
       "damage_type": "ÓÙÉË" 
]), 
([      "action" :        "$NÒ»Éù³¤Ò÷£¬$wÏòÍâÒ»²¦ÉíÌåË³ÊÆ¼±×ª£¬Í»È»¼±Í£Ïò
        $nµÄÉíÇ°Ô¾È¥£¬¿ÚÖĞ³¤Ğ¥¡¸·ï»ËÕ¹³á¡¹¹÷ÉÒºáÉ¨$nµÄ$l",    
       "force"  : 510, 
       "attack" : 180, 
       "dodge"  : -50, 
       "parry"  : -110, 
       "damage" : 410, 
       "damage_type": "ÓÙÉË" 
]), 
([       "action" : "$NË«Ä¿¾«¹â±©³¤£¬ÉñÇéÅ­²»¿É¶ô£¬Ò»Ê½[ºáÉ¨Ç§¾ü]´ø¶¯
       ÎŞÊıµÀºÚÓ°,$wÖ±»÷$nµÄ$l²»´ı$n×ö³ö·´Ó¦£¬$w¾¹È»ºÁÎŞÕÂ·¨ËÆµÄÏò$nÈ«Éí
       ÂÒÅü¹ıÈ¥,ËÙ¶È¼«¿ì$nÖ»¾õÑÛÇ°¾¡ÊÇ¹÷Ó°¶ø²»¼ûÈË",     
       "force"  : 560, 
       "attack" : 170, 
       "dodge"  : -65, 
       "parry"  : -120, 
       "damage" : 500, 
       "damage_type": "ÓÙÉË" 
]), 
}); 

string main_skill() { return "luowang-club"; } 

mapping sub_skills = ([ 
       "shunfeng-daqi"         : 120,        // 1 
       "xuehua-gaiding"        : 120,        // 2 
       "boyun-jianri"          : 120,        // 3
       "liuding-kaishan"       : 120,        // 4
       "wulong-baiwei"         : 120,        // 5
       "yanzi-chuanlin"        : 120,        // 6
       "jiaolong-chushui"      : 120,        // 7
       "dupi-huashan"          : 120,        // 8
       "xiniu-wangyue"         : 120,        // 9
       "luohan-bohu"           : 120,        // 10
       "tianma-xingkong"       : 120,        // 11
       "fenghuang-zhanchi"     : 120,        // 12
       "hengsao-qianjun"       : 120,        // 13
]); 

int get_ready(object me) 
{ 
       return 1; 
} 

int get_finish(object me) 
{ 
       if( query("str", me)<25 || me->query_str()<45 )
       { 
               tell_object(me, "ÄãÑİÁ·Íê±Ï£¬Õû¸öÉíÌå¼¸ºõÍêÈ«ĞéÍÑÁË£¬ÈíÃàÃàµÄÌá²»ÆğÒ»µã¾¢¡£\n"); 
               return 0; 
       } 

       if( query("con", me)<25 || me->query_con()<45 )
       { 
               tell_object(me, "ÄãÑİÁ·Íê±Ï£¬¾Í¾õµÃÑÛÇ°½ğĞÇÂÒÃ°£¬Ì«ÑôÑ¨Í»Í»µÄÌø¡£\n"); 
               return 0; 
       } 

       if ((int)me->query_skill("force") < 200) 
       { 
               tell_object(me, "ÄãÑİÁ·Íê±Ï£¬¼¸ºõĞéÍÑ£¬×Ô¼ºµÄÄÚ¹¦Ë®Æ½¿´À´»¹ÓĞ´ıÌá¸ß¡£\n"); 
               return 0; 
       } 

       if( query("max_neili", me)<1500 )
       { 
               tell_object(me, "ÄãÑİÁ·Íê±Ï£¬µ¤ÌïÌá²»Æğ°ëµãÁ¦À´£¬¿´À´Ó¦¸Ã¼ÌĞø¶ÍÁ¶ÄÚÁ¦¡£\n"); 
               return 0; 
       } 

       if (random(10) < 5) 
       { 
               tell_object(me, "Äã¶Ô½ôÄÇÂŞÍõ¹÷µÄ°ÂÃîÆÄÓĞÁìÎò£¬»òĞíÔÙÑİÁ·Ò»´Î¾ÍÄÜ¹»ÈÚ»á¹áÍ¨¡£\n"); 
               return 0; 
       } 

       tell_object(me, HIY "ÄãÒ»ÆøºÇ³É£¬½«½ôÄÇÂŞÍõ¹÷´ÓÍ·µ½Î²ÑİÁ·ÁËÒ»±ä£¬ĞÄÖĞ¶ÙÎò£¬Í¨\n" 
                           "ÏşÁËµÄ½ôÄÇÂŞÍõ¹÷°ÂÃî¾«Ëè£¬ÈÚ»á¹áÍ¨ÁË¹÷·¨µÄ¾«Î¢Ö®´¦£¬\n" 
                           "ÔÙÒ²²»ÊÇ²ğ¿ªÊ¹ÓÃÄÇÃ´ÄÇÃ´¼òµ¥¡£\n" NOR); 
       return 1; 
} 

mapping query_sub_skills() 
{ 
       return sub_skills; 
} 

int valid_enable(string usage) { return usage=="club" ||  usage=="parry"; }   

int valid_learn(object me) 
{  
        object weapon;
        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "club" )
                return notify_fail("ÄãÊÖÖĞÎŞ¹÷ÔõÃ´Ñ§Ï°°¡¡£\n");
       if( query("str", me)<25 && 
           query("con", me)<25 )
               return notify_fail("¾ÍÄãÕâÉí×Ó¹Ç»¹Á·½ôÄÇÂŞÍõ¹÷£¿Ğ¡ĞÄÉíÌå³Ô²»Ïû°¡¡£\n"); 
       if( query("int", me)<20 )
               return notify_fail("ËãÁË°É£¬ÄãÏÈÌìÎòĞÔ²»ºÃ£¬ÔõÃ´ÄÜÀí½âÄØ¡£\n"); 
       if ((int)me->query_skill("force") < 200) 
               return notify_fail("ÄãµÄÄÚ¹¦»ğºò²»¹»£¬ÎŞ·¨Ñ§Ï°½ôÄÇÂŞÍõ¹÷¡£\n"); 
       if ((int)me->query_skill("hunyuan-yiqi") < 200) 
               return notify_fail("ÄãµÄ»ìÔªÒ»Æø¹¦»ğºò²»¹»£¬ÎŞ·¨Ñ§Ï°½ôÄÇÂŞÍõ¹÷¡£\n");
       if((int)me->query_skill("zui-gun") < 200) 
               return notify_fail("ÄãµÄ×í¹÷»ğºò²»¹»£¬ÎŞ·¨Ñ§Ï°½ôÄÇÂŞÍõ¹÷¡£\n"); 
       if ((int)me->query_skill("buddhism") < 200) 
               return notify_fail("ÄãµÄìø×ÚĞÄ·¨»ğºò²»¹»£¬ÎŞ·¨Ñ§Ï°ÓÚìø×ÚÏ¢Ï¢Ïà¹Ø½ôÄÇÂŞÍõ¹÷¡£\n"); 
       if( query("max_neili", me)<2000 )
               return notify_fail("ÄãµÄÄÚÁ¦ÕâÃ´²î£¬ÔõÄÜÈÚ»á¹áÍ¨½ôÄÇÂŞÍõ¹÷£¿\n"); 

       if ((int)me->query_skill("club", 1) < 200) 
               return notify_fail("ÄãµÄ»ù±¾¹÷·¨»ğºò²»¹»£¬ÎŞ·¨Ñ§Ï°½ôÄÇÂŞÍõ¹÷¡£\n"); 
       if ((int)me->query_skill("club", 1) < (int)me->query_skill("luowang-club", 1)) 
       return
   notify_fail("ÄãµÄ»ù±¾¹÷·¨Ë®Æ½ÓĞÏŞ£¬ÎŞ·¨Áì»á¸ü¸ßÉîµÄ½ôÄÇÂŞÍõ¹÷¡£\n"); 

       return 1; 
} 

mapping query_action(object me, object weapon) 
{ 
       mapping a_action;
       int level;

       level = (int)me->query_skill("luowang-club", 1);
       a_action = action[random(sizeof(action))]; 
       a_action["dodge"] -= level / 10;
       a_action["parry"] -= level / 10;
       a_action["attack"] += level / 10;
       a_action["force"] += level / 10;
       a_action["damage"] += level / 10;
       if( query_temp("action_flag", me) )
                set_temp("action_msg", "½ô¸ú×Å", me);
       return a_action;
} 

int practice_skill(object me) 
{ 
        object weapon;
        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "club" )
                return notify_fail("ÄãÊÖÖĞÎŞ¹÷ÔõÃ´Á·°¡¡£\n");
     if( query("qi", me)<150 )
               return notify_fail("ÄãµÄÌåÁ¦Ì«µÍÁË¡£\n"); 
       if( query("neili", me)<100 )
               return notify_fail("ÄãµÄÄÚÁ¦²»¹»Á·½ôÄÇÂŞÍõ¹÷¡£\n"); 

       me->receive_damage("qi", 120); 
       addn("neili", -50, me);
       return 1; 
} 

mixed hit_ob(object me, object victim, int damage_bonus) 
{ 
        if (random(10) >= 1)
       { 
               victim->receive_wound("qi", damage_bonus); 
               victim->receive_wound("jing", damage_bonus); 
               return HIR "Ëæ×ÅÒ»Éù³ÁÃÆµÄºßÉù´«À´£¬$nµÄ¿ÚÖĞ¿È³öÁË¼¸¿ÚÏÊÑª£¡\n" NOR; 
       } 
} 

string perform_action_file(string action) 
{ 
       return __DIR__"luowang-club/" + action; 
} 

void skill_improved(object me) 
{ 
       int i; 
       string *sub_skillnames; 

       sub_skillnames = keys(sub_skills); 
       for (i = 0; i < sizeof(sub_skillnames); i++) 
               me->delete_skill(sub_skillnames); 
} 
void do_interlink(object me, object victim)
{
        int skill, i, j;
        object *enemy;
        object weapon;
    
        skill = me->query_skill("luowang-club", 1);
        if( skill>120 && !objectp(weapon=query_temp("weapon", me)) )
        {
                enemy=me->query_enemy();
                if (! sizeof(enemy)) return;
                for (i=0;i<sizeof(enemy);i++)
                {
                        for (j=0;j<(skill/(60*sizeof(enemy)));j++)
                        if( (me->is_fighting(enemy[i]) || enemy[i]->is_fighting(me)) && query("qi", enemy[i])>0 )
                        {
                                if (environment(me) == environment(enemy[i]))
                                {
                                        addn_temp("str", skill/10, me);
                                        addn_temp("dex", skill/10, me);
                                        COMBAT_D->do_attack(me,enemy[i],query_temp("weapon", me),TYPE_REGULAR);
                                }
                        } else break;
                }
                delete_temp("str", me);
                delete_temp("dex", me);
        }
}

