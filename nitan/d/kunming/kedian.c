#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "��ջ");
        set("long", @LONG
����һ�Ҽۼ�ª��ջ��������Ȼ��������ȴ����������
�������˶�ϲ��ѡ��������ţ���Ϊ����ĵ���ʶ��һЩ����
���ˣ����Ժ������˻��������¡����е�С��æǰæ��ͣ��
�к��ſ��ˣ���������Ҳ������Ц�ݵ�����˵�û������˾���
�й�ҵĸо�һ�㡣
LONG);
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("no_sleep_room", 1);
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
                __DIR__"npc/laoban" : 1,
        ]));
        set("exits", ([
                "west" : __DIR__"majiu",
                "east" : __DIR__"nandajie2",
                "westup" : __DIR__"kedian1",
        ]));
	set("coor/x", -16850);
	set("coor/y", -7230);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{

        if (! me->query_temp("rent_paid") && dir == "westup" )
        return notify_fail(CYN "Ԫ�ƶ�����Ц������λ�͹٣���������"
                           "����Ǯ����¥ס�ꡣ\n" NOR);
        return ::valid_leave(me, dir);
}