// Updated by Lonely
// xingxiu-duzhang.c, based on xianglong-zhang.c
// by yucao
// Ryu, 12/4/96.
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N����¶�������Ц�ݣ�����������ɫ��˫��ɨ��$n��$l",
        "dodge": -30,
        "force": 280,
//      "poison": 80,
        "damage_type": "����"
]),
([      "action": "$NͻȻ������ת��������$n��˫�Ʒ���������$n��$l",
        "dodge": -10,
        "force": 200,
//      "poison": 60,
        "damage_type": "����"
]),
([        "action": "$N�������������֣�һ�С���ʬ���������ޱȵ�ץ��$n��$l",
        "dodge": -20,
        "force": 450,
        "damage": 65,
//      "poison": 100,
        "damage_type": "����"
]),
([        "action": "$N˫��Ю��һ���ȳ�֮������$n��$l",
        "dodge": -10,
        "force": 350,
        "damage": 60,
//      "poison": 80
        "damage_type": "����"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }
int valid_combine(string combo) { return combo=="sanyin-zhua"; }
mapping query_action(object me)
{
        mapping a_action;
        int i, level;
        level = (int) me->query_skill("xingxiu-duzhang",1);
        if (random(me->query_skill("strike")) > 60 &&
            me->query_skill("force") > 50 &&
            query("neili", me)>100){
                addn("neili", -100, me);
                return ([
                "action":BLU "$Nҧ����⣬������Ѫ���ۼ�ȫ������������$n"NOR,
                "force": 480,
                "attack": 300,
                "parry" :-300,
                "dodge" :-300,
                "damage": 80,
                "damage_type": "����"]);
        }
        for( i = sizeof(action); i > 0; i-- )
                if( level > action[i-1]["lvl"] )
                {
                        a_action = action[NewRandom(i, 20, level/5)];
                        break;
                }
        a_action["dodge"] -= level / 10;
        a_action["parry"] = level / 10;
        a_action["force"] += level / 10;
        a_action["damage"] += level / 10;
        return a_action;
}

int valid_learn(object me)
{
        int  nb,  nh;
        nb = (int)me->query_skill("poison", 1);
        nh = (int)me->query_skill("xingxiu-duzhang", 1);

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("�����޶��Ʊ�����֡�\n");
        if ((int)me->query_skill("huagong-dafa", 1) < 10)
                return notify_fail("��Ļ����󷨻�򲻹����޷������޶��ơ�\n");
        if ( nb < 100 && nb <= nh )
                return notify_fail("��Ķ�����Ϊ�������޷�������޶��ơ�\n");

        if( query("max_neili", me)<60 )
                return notify_fail("�������̫�����޷������޶���");
        return 1;
}


int practice_skill(object me)
{
        int  nb,  nh;
        nb = (int)me->query_skill("poison", 1);
        nh = (int)me->query_skill("xingxiu-duzhang", 1);

        if( query("jingli", me)<30 )
                return notify_fail("��ľ���̫���ˡ�\n");
        if( query("neili", me)<8 )
                return notify_fail("����������������޶��ơ�\n");
        if ( nb < 100 && nb <= nh )
                return notify_fail("��Ķ�����Ϊ�������޷�������޶��ơ�\n");

        if (me->query_skill("xingxiu-duzhang", 1) < 50)
                me->receive_damage("jingli", 20);
        else
                me->receive_damage("jingli", 30);
        addn("neili", -5, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        if( random(me->query_skill("xingxiu-duzhang", 1)) > 30 ) {
                victim->apply_condition("xx_poison", 
                random(me->query_skill("xingxiu-duzhang", 1)/2) + victim->query_condition("xx_poison"));
        }
}
string perform_action_file(string action)
{
        if ( this_player()->query_skill("xingxiu-duzhang", 1) >= 30 )
                return __DIR__"xingxiu-duzhang/" + action;
}