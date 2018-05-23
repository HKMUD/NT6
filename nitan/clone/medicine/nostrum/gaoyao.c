// gaoyao.c

inherit ITEM;
#include <ansi.h>

void setup()
{}

void init()
{
        add_action("do_tie", "tie");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(YEL"��Ƥ��ҩ"NOR, ({"goupi gaoyao", "goupi", "gaoyao"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ��������ʿ����(tie)�Ĺ�Ƥ��ҩ��\n");
                set("value", 5000);
        }
        set("pour_type", "1");
        setup();
}

int do_tie(string arg)
{
        object me = this_player();

        if (!id(arg)) return notify_fail("��Ҫ��ʲôҩ��\n");
        if (!present(this_object(), this_player()))
                return notify_fail("��Ҫ��ʲôҩ��\n");
        if (me->is_busy() )
                return notify_fail("������û������Ƥ��ҩ�ˡ�\n");

        if( query("eff_qi", me) == query("max_qi", me) )
                return notify_fail("�����ڲ���Ҫ�ù�Ƥ��ҩ��\n");
        else {
                me->receive_curing("qi", 50);
                message_vision("$Nž��һ�����˿�������һ����Ƥ��ҩ����ɫ�������ö��ˡ�\n", me);
                me->start_busy(2);
                destruct(this_object());
                return 1;
        }
}