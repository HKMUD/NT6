// kuai.c 快剑

#include <ansi.h>

inherit F_SSERVER;
#define PNAME "「快剑」"
int perform(object me, object target)
{
        object weapon;
        int dodge, parry, sword, busy_time;
        int flag;
        string fskill,sskill,bskill,pfname,pskill;

        sskill = explode(__FILE__,"/")[<2];
        pfname = explode(__FILE__,"/")[<1][0..<3];
  if (userp(me) && !wizardp(me) &&
   !query("perform/"+pfname, me) && 
   !query("can_perform/"+sskill+"/"+pfname, me) && 
   !query_temp("murong/xingyi", me) && 
   !SCBORN_D->valid_perform(me,sskill,pfname))
   return notify_fail("你所使用的外功中没有这种功能。\n");

        if( !objectp(target) ) {flag =1;target = offensive_target(me);}
        
        if( !target || !target->is_character() || target == me ||        
                  !me->is_fighting(target) ||
          !living(target) || query_temp("noliving", target) )
                return notify_fail(PNAME"只能对战斗中的对手使用。\n");
                
        if( query_temp("pfm-target/xunlei-kuai", target) )
                return notify_fail("对手已被昆仑「快剑」心法所困。\n");        

        weapon=query_temp("weapon", me);

        if( !objectp(weapon) || query("skill_type", weapon) != "sword" )
                return notify_fail("你手中无剑，怎能运用「快剑」心法？！\n");

        fskill = "xuantian-wuji";
        bskill = "sword";
        if (SCBORN_D->valid_perform(me,sskill,pfname))
                fskill = me->query_skill_mapped("force");
        if( query_temp("murong/xingyi", me) )
        {
                sskill = "douzhuan-xingyi";
                fskill = "shenyuan-gong";
                bskill = "parry";
        }

        if( (int)me->query_skill(fskill, 1) < 120 )
                return notify_fail("你的"+to_chinese(fskill)+"修为火候未到，施展"+PNAME+"只会伤及自身。\n");

        if( (int)me->query_skill(sskill, 1) < 120 )
                return notify_fail("你的"+to_chinese(sskill)+"修为还不够，还未领悟"+PNAME+"。\n");

        if( me->query_skill_mapped("force") != fskill)
                return notify_fail("你所用内功与「快剑」心法相悖！\n");

        if( query("max_neili", me) <= 1500 )
                return notify_fail("你的内力修为不足，劲力不足以施展「快剑」！\n");

        if( query("neili", me) <= 700 )
                return notify_fail("你的内力不够，劲力不足以施展「快剑」！\n");

        if( query("qi", me) <= 200 )
                return notify_fail("你的气血有限，不足以施展「快剑」！\n");
        
        dodge = target->query_skill("dodge", 1)/3;
        parry = target->query_skill("parry", 1)/3;
        sword = me->query_skill(bskill, 1)/3;
        busy_time = me->query_skill(bskill, 1)/30;        
        
        message_combatd(HIW"$N飘身而起，使出昆仑绝技「快剑」心法，顿时剑意空灵飘逸，似万千柳絮飞舞，\n" NOR, me, target);
        
        if( random(query("combat_exp", me))>query("combat_exp", target)/5 )
        { 
                message_combatd(HIW"又如和风阵阵拂过。$n"HIW"眼花缭乱，被攻了个措手不及！\n" NOR, me, target);
                addn_temp("apply/dodge", -dodge, target);
                addn_temp("apply/parry", -parry, target);
                addn_temp("apply/attack", -sword, target);
                target->start_busy(busy_time);
                set_temp("pfm-target/xunlei-kuai", 1, target);
                addn("neili", -300, me);
                addn("qi", -100, me);
                target->start_call_out( (: call_other, __FILE__, "remove_effect",me,target, dodge, parry,  sword :), sword/3);
        }
        else
        {
                message_combatd(HIW"可$n"HIW"镇定自若，丝毫不为所动！\n"NOR, me, target);
                me->start_busy(1);
                addn("neili", -200, me);
                addn("qi", -100, me);
        }
        return 1;
}

void remove_effect(object me,object victim, int dodge, int parry, int sword)
{
        if (objectp(victim))
        {
                delete_temp("pfm-target/xunlei-kuai", victim);
                addn_temp("apply/dodge", dodge, victim);
                addn_temp("apply/parry", parry, victim);
                addn_temp("apply/attack", sword, victim);
        }
        
        if (objectp(me) && objectp(victim) && victim->is_fighting(me))
        {
                message_combatd(HIY "\n\n$N"HIY"渐渐适应了$n"HIY"的剑路，攻守自如多了。\n" NOR, victim, me);
        }
}
string name() {return replace_string(replace_string(PNAME,"「",""),"」","");}

int help(object me)
{
        write(WHT"\n"+to_chinese(explode(__FILE__,"/")[<2])+"之"+name()+WHT"："NOR"\n");
        write(@HELP

        使用功效：
                损害对方攻防
                迟滞对方出手

        出手要求：
                玄天无极功120级
                迅雷十六剑120级
                内力1500
                气血200
HELP
        );
        return 1;
}
