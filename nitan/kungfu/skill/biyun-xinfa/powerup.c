#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("��ֻ���ñ����ķ��������Լ���ս������\n");

        if( query("neili", me)<80 )
                return notify_fail("�������������\n");

        if( query_temp("powerup", me) )
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("force", 1);
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        message_combatd(
                HIR "$N����Ϣ������������ķ�����߾��磬ֻ��һ����������������\n" NOR, me);

        addn_temp("apply/attack", skill/3, me);
        addn_temp("apply/defense", skill/3, me);
        set_temp("powerup", 1, me);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill/3 :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        addn_temp("apply/attack", -amount, me);
        addn_temp("apply/defense", -amount, me);
        delete_temp("powerup", me);
        tell_object(me, "��ı����ķ�������ϣ��������ջص��\n");
}