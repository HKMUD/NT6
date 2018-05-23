inherit SKILL;

mapping *action = ({
([      "action": "$Nһ�С�������������$w���������$n���������Σ�����������仯����",
        "force" : 40,
        "attack": 10,
        "dodge" : 10,
        "parry" : 5,
        "lvl"   : 0,
        "damage": 5,
        "skill_name"  : "��������",
        "damage_type" : "����"
]),
([      "action": "$Nһ�С���ˮǧɽ����������һǰһ��$w����������$n��$lնȥ",
        "force" : 90,
        "attack": 20,
        "dodge" : 10,
        "parry" : 8,
        "damage": 5,
        "lvl"   : 10,
        "skill_name"  : "��ˮǧɽ",
        "damage_type" : "����"
]),
([      "action":  "$N����Ծ�䣬һ�С���ɨǧ���$w���ż������һ������$n��ɨ��ȥ",
        "force" : 140,
        "attack": 25,
        "dodge" : 5,
        "parry" : 12,
        "damage": 15,
        "lvl"   : 30,
        "skill_name"  : "��ɨǧ��",
        "damage_type" : "����"
]),
([      "action": "$Nһ�С����ҿ�������$w�󿪴��أ����Ҳ���������������$n�����翳��",
        "force" : 190,
        "attack": 30,
        "dodge" : 5,
        "parry" : 15,
        "damage": 25,
        "lvl"   : 50,
        "skill_name"  : "���ҿ���",
        "damage_type" : "����"
]),
([      "action": "$N����$w���϶��£�һ�С����ɷ��١�������к�����ٲ��㿳��$n��ͷ��",
        "force" : 240,
        "attack": 35,
        "dodge" : 10,
        "parry" : 25,
        "damage": 30,
        "lvl"   : 80,
        "skill_name"  : "���ɷ���",
        "damage_type" : "����"
]),
([      "action": "$Nʹ��һ�С�ֱ�����������������ã����ҿ�����ǧ������������$n",
        "force" : 280,
        "attack": 40,
        "dodge" : 15,
        "parry" : 32,
        "damage": 35,
        "lvl"   : 100,
        "skill_name"  : "ֱ������",
        "damage_type" : "����"
]),
([      "action": "$N���õ��羢����һ�С�������������ת������������$n��$l����ȥ",
        "force" : 290,
        "attack": 45,
        "dodge" : 5,
        "parry" : 35,
        "damage": 50,
        "lvl"   : 120,
        "skill_name"  : "��������",
        "damage_type" : "����"
]),
([      "action": "$Nһ�С��ϲ���ɽ����$wֱֱ��������һƬ�����ĵ�Ӱ��$n��ȫ����ȥ",
        "force" : 320,
        "attack": 50,
        "dodge" : 20,
        "parry" : 45,
        "damage": 60,
        "lvl"   : 150,
        "skill_name"  : "�ϲ���ɽ",
        "damage_type" : "����"
]),
});

int valid_enable(string usage)
{
        return usage == "blade" || usage == "parry";
}

int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("���������Ϊ����������������Ѫ������\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("����ڹ���򲻹�������������Ѫ������\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("tiexue-dao", 1))
                return notify_fail("��Ļ�������ˮƽ���ޣ��޷������������Ѫ������\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("tiexue-dao", 1);
        for(i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("qi", me)<60 )
                return notify_fail("���������������Ѫ������\n");

        if( query("neili", me)<60 )
                return notify_fail("���������������Ѫ������\n");

        me->receive_damage("qi", 55);
        addn("neili", -58, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tiexue-dao/" + action;
}