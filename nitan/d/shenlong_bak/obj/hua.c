//hua.c ���㻨
//
inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name(HIG"���㻨"NOR, ({"hua", "baixiang"}));
        set("unit", "��");
        set("long", "����һ�����޵Ļ�������Ũ���쳣��\n");
        setup();
}

int do_eat(string arg)
{
        int force_limit, neili_limit, force_skill, add_skill, improve;
        object me = this_player();
        force_limit = me->query_skill("force")*10;
        neili_limit=query("max_neili", me);
        force_skill = me->query_skill("force", 1);

        if(!id(arg)) return notify_fail("��Ҫ��ʲô��\n");
        if(!present(this_object(), me))
                return notify_fail("��Ҫ��ʲô��\n");
        if( me->is_busy() )
                return notify_fail("�𼱣������ԣ�С�ı�ҭ���ˡ�\n");
        if ( neili_limit <= force_limit  )
                addn("max_neili", 1, me);
        me->unconcious();
        destruct(this_object());
        return 1;
}