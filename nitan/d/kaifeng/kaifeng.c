#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "���⸮");
        set("long", @LONG
���⸮ͳ�ܿ�����Ƭ�������εĿ��⸮������������������˽��
�������������������Σ�����Ϊ�����졣����һ��һ���ߴ�Ĺļ�
��״��ԩ�Ŀ����ڴ��ùġ�
LONG );
        set("objects", ([
                __DIR__"npc/zhaohu" : 1,
                __DIR__"npc/zhanglong" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"jiedao1",
                "west" : __DIR__"datang",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5050);
	set("coor/y", 2150);
	set("coor/z", 10);
	setup();
}

int valid_leave(object me, string dir)
{
        object ob;

        if (dir == "west")
        {
                if (objectp(ob = present("zhang long", this_object()))
                   && living(ob))
                        return notify_fail(CYN "����һ����ס�㣬�ȵ���������"
                                           "�أ����������˵���������\n" NOR);

                if (objectp(ob = present("zhao hu", this_object()))
                   && living(ob))
                        return notify_fail(CYN "�Ի�һ����ס�㣬�ȵ���������"
                                           "�أ����������˵���������\n" NOR);
        }
        return ::valid_leave(me, dir);
}