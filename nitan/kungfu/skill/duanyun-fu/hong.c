//hongtianza.c ¶áÃüÈı¸«Ö®¡¸ºäÌìÔÒ¡¹
// Modified by Venus Oct.1997
#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
    string msg,*limbs;
    int i,size,damage;
    object weapon;
    object my_w,target_w;
    my_w=query_temp("weapon", me);
//    target_w = target->query_temp("weapon");
    if( !target ) target = offensive_target(me);

              if( !target || !me->is_fighting(target) )
                      return notify_fail("¡¸"HIM"¡¸ºäÌìÔÒ¡¹"NOR"¡¹Ö»ÄÜÔÚÕ½¶·ÖĞ¶Ô¶ÔÊÖÊ¹ÓÃ¡£\n");

              if( !objectp(weapon=query_temp("weapon", target)) )
                      return notify_fail("¶Ô·½Ã»ÓĞÊ¹ÓÃ±øÆ÷£¬ÄÑÒÔÊ©Õ¹¡¸ºäÌìÔÒ¡¹¡£\n");

    if( target->is_busy() )
    return notify_fail(target->name() + "Ä¿Ç°ÕıÃ£È»²»ÖªËù´ë£¬¼Ó½ô¹¥»÷°É¡£\n");
    if( (int)me->query_skill("duanyun-fu",1) < 50)
    return notify_fail("ÄãÄ¿Ç°¹¦Á¦»¹Ê¹²»³ö¡¸ºäÌìÔÒ¡¹¡£\n");
    if( query("neili", me)<100 )
    return notify_fail("ÄãµÄÄÚÁ¦²»¹»¡£\n");
    addn("neili", -60, me);
msg = CYN"$NÍ»È»±©ºğÒ»Éù£º¡°ÎÒÔÒ£¡ÎÒÔÒ£¡ÎÒÔÒÔÒÔÒ£¡¡±£¬ÊÖÖĞ¾Ş¸«¾¹È»ÔÒÏò$pÊÖÖĞ±øÈĞ£¡\n"NOR;
    target_w=query_temp("weapon", target);
    me->start_busy(1);

    if( query_temp("weapon", target) || 
   query_temp("secondary_weapon", target)){

    if( random(query("combat_exp", me)/100)>
      query("combat_exp", target)/300){
    if( target_w->weight() > 2 * random(my_w->weight()) ) {
msg+="½á¹û$pÊÖÖĞµÄ"+query("name", target_w)+"±»$PµÄºäÌìÔÒÔÒ¸öÕı×Å£¬ÔÙÒ²°ÑÎÕ²»×
×¡£¬Á¢¼´ÍÑÊÖ·É³ö£¡\n" NOR;
    target_w->unequip();
    target_w->move(environment(target));
    target->reset_action();
    target->start_busy( (int)me->query_skill("duanyun-fu") / 20 );
}
   msg += HIC
"Ö»¼û$nÊÖÖĞµÄ"+query("name", target_w)+"¾¹È»±»ÔÒ¶Ï×÷Êı¶Î£¬²¢ÇÒ
ÊÜµ½$NµÄ¾¢ÆøµÄ¼¤µ´¶øÏò$nÑ¸ËÙÉäÈ¥£¡\n"NOR;
    message_combatd(msg,me,target);
    target_w->unequip();
    target_w->move(environment(target));
    set("name",query("name",  target_w)+"µÄËéÆ¬", target_w);
    set("value",query("value",  target_w)/10, target_w);
    set("weapon_prop", 0, target_w);
    target->reset_action();
    target->start_busy( (int)me->query_skill("duanyun-fu") / 20 );
    limbs=query("limbs", target);
    me->start_busy(1);
    msg += "½á¹û$p´ôÁ¢µ±³¡£¬±»¹¥ÁË¸ö´ëÊÖ²»¼°£¡\n" NOR;
    size=(int)(me->query_skill("duanyun-fu")/10);
    damage=random(size)+size;
                                 damage=damage+me->query_str()/3+random(query_temp("apply/damage",me)); 
    for(i=0;i<=random(size);i++)
   {
   msg =HIB"¡°àÍ¡±£¬ËéÆ¬ÉäÈë$p"+limbs[random(sizeof(limbs))]+"£¡\n"NOR;
   message_combatd(msg,me,target);
   target->receive_damage("qi",damage,me);
   target->receive_wound("qi",damage/3,me);
   }
    COMBAT_D->report_status(target);
    } else {
    msg += "¿ÉÊÇ$p¼±Ã¦½«×Ô¼ºµÄ±øÈĞÉÁ¿ª£¬²¢Ã»ÓĞÈÃ$PµÄ¼ÆÄ±µÃ³Ñ¡£\n" NOR;
    }
    return 1;
    }
    return notify_fail(target->name() + "Ä¿Ç°ÊÇ¿ÕÊÖ£¬ÄãÏëÔÒÊ²Ã´£¿\n");
}
