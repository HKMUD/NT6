// Room: /d/suzhou/fengqiao.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
�µı�����һ���ſ׳ʰ�Բ�ĵ���ʯ��--���ţ��������˺ӵķ���
�塣�ŵĶ���������أ�����׻��أ�����أ��ϳ��������ء�
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "enter" : __DIR__"hanshidian",
                "north" : __DIR__"tielingguan",
        ]));
	set("coor/x", 1050);
	set("coor/y", -1050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}