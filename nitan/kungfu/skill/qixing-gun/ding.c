// ding.c ȫ�潣-������

#include <ansi.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( (int)me->query_skill("quanzhen-jianfa", 1) < 40 )
                return notify_fail("���ȫ�潣��������죬����ʹ�ö����롣\n");

        if( (int)me->query_skill("quanzhen-xinfa", 1) < 40 &&
            (int)me->query_skill("yunv-xinfa", 1) < 40 )
                return notify_fail("��ı����ڹ�������죬����ʹ�ö����롣\n");

        if( query("neili", me)<150 )
                return notify_fail("����������̫��������ʹ�ö����롣\n");

        msg = HIC "$N�������Ҽ�����������������������һʽ�������롹бб�̳���\n"NOR;

        //if( !target->is_killing(me) ) target->kill_ob(me);

        if (random(me->query_skill("force")) > target->query_skill("force")/2 )
        {
                me->start_busy(2);

                damage = (int)me->query_skill("quanzhen-jianfa", 1) + (int)me->query_skill("force",1);
                //(ȫ�潣������+�����ڹ�)

                damage = damage/2 + random(damage/2);

                target->receive_damage("qi", damage);
                target->start_busy(4);
                addn("neili", -100, me);

                msg += HIR"$n����$N������ǧ����һ��������֪����мܣ�\n"NOR;

        }
        else
        {
                me->start_busy(3);
                msg += CYN"����$p������$P����ͼ��бԾ�ܿ���\n"NOR;
        }
        message_vision(msg, me, target);

        return 1;
}