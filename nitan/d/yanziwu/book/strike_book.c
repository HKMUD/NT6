// strike_book.c
#include <ansi.h>
inherit ITEM;
int do_study(string arg);
void init()
{
        add_action("do_study","kan");
}
void create()
{
        set_name(HIM"Ľ������"HIY"�״�ƪ"HIC"����"NOR, ({"strike book","book"}));
        set_weight(500);
        set("unit", "��");
        set("long","����Ľ�����ҵĲ����е�"HIG"�״�ƪ"NOR"֮"HIC"����"NOR"���������������������ɵ��Ʒ���Ҫ��\n���޾����书���ͺúÿ�(kan)�ɡ�\n");
        set("value", 1);
        set("material", "paper");
        setup();
}
int do_study(string arg)
{
        object me = this_player();
        int level = me->query_skill("strike",1);
        if (me->query_skill("shenyuan-gong",1) < 20)
                return notify_fail("�����Ԫ��δ���ţ��޷�������ѧ��ʲô��\n");
        if ( (arg != "book") && (arg != "strike book"))
                return notify_fail("��Ҫѧʲô��\n");
        if (level >= 150)
                return notify_fail("���ж���һ��������Ƿ���������˵�Ķ�����Զ�̫ǳ�ˣ�û��ѧ���κζ�����\n");
        if (level <= 50)
                return notify_fail("���ж���һ��������Ƿ���������˵�Ķ�����Զ�̫����ˣ������ջ�\n");
        if( query("combat_exp", me)<(level*level*level/10) )
                return notify_fail("���ʵս���鲻�㣬����ô��Ҳû�á�\n");
        if( query("jing", me)<25 )
                return notify_fail("�����ڹ���ƣ�룬�޷�ר�������ж���֪��\n");
        me->receive_damage("jing", 25);
        me->improve_skill("strike", (int)me->query_skill("literate",1)/5+1); 
        write("���ж����йػ����Ʒ��ļ��ɣ��ƺ��е��ĵá�\n");
        return 1;
}