#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{
    set("short", "��������");
        set("long", @LONG
����������µĴ������ڣ�������¥���Ĳ㣬�º��һ��ʮ����������
��Զ����������������ⲻʱ���ױ�������Ѳ�Ӳ쿴���䱸����ɭ�ϡ�
LONG );

    set("exits", ([
        "enter" : "/d/tulong/yitian/was_dayuan",
        "south" : "/d/tulong/yitian/road3",
    ]));

    set("objects", ([
        "/d/tulong/yitian/npc/bing1" : 4,
        "/d/tulong/yitian/npc/bing2" : 1,
    ]));
    setup();
}

int valid_leave(object me,string dir)
{
        object ob;

        if ( dir == "enter" && ob = present("qianfu zhang"))
        {
                ob->command("tnnd"+query("id", me));
                message_vision(CYN "$N�ȵ����ҵ����ӣ�����������Ұ��ȥ���ɣ�\n" NOR,ob,me);
                ob->kill_ob(me);
                ob=present("guan bing 1");
                if (objectp(ob)) ob->kill_ob(me);
                ob=present("guan bing 2");
                if (objectp(ob)) ob->kill_ob(me);
                ob=present("guan bing 3");
                if (objectp(ob)) ob->kill_ob(me);
                ob=present("guan bing 4");
                if (objectp(ob)) ob->kill_ob(me);
                return notify_fail("���ű��ɹű���ס�ˡ�\n");
        }
        return 1;
}
void init()
{
        object sword, me;
        me = this_player();
        if ((objectp(sword = present("yitian sword", me))))
        {
                remove_call_out("yixiao_rob");
                call_out("yixiao_rob", 1, me, sword);
        }
}

void yixiao_rob(object me, object sword)
{
        message_vision(HIC "\nֻ��һ������ĳ�Ц��һ����Ӱ��$N" HIC
                       "ֱ�˶������㶨��һ����ԭ���������Ĵ�"
                       "�̷���֮һ�ġ�" NOR+HIB 
                       "��\n������" NOR+HIC
                       "��ΤһЦ��\n\n" NOR,  me);

        if ((int)me->query_skill("parry") < 400)
        {
                message_vision(HIW "$N" HIW "ֻ���Է�������ӿ����æ�����ֵ���"
                           "��ʱֻ������һ�ᣬ���콣�ѱ�ΤһЦ"
                           "���˹�ȥ��\n\n" NOR, me);
                sword->move(environment(me));
                destruct(sword);
                shout(HIR "\n������������" NOR+WHT "ΤһЦ���ٺ٣���л�㽫���콣ȡ�أ����Ǻ�����ڡ�\n" NOR );
        }
        else {
                message_vision(HIW "$N" HIW "���Է�������ӿ����������Ծ�𣬰�"
                           "���аγ����콣������һ�������ĺ�âֱ��Τһ"
                           "Ц��ֻ��Τ\nһЦһ���Һ���" NOR+HIR 
                           "��Ѫ" NOR+HIW 
                           "�ɽ���\n\n", me);
        }
        write(HIC "ΤһЦ��Хһ����ʩչ�����Ṧ������ƮȻ��������һ·��"
              "�����Ѳ�������Ӱ......\n" NOR);
}