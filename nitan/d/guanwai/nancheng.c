// /guanwai/nancheng.c

inherit ROOM;

void create()
{
        set("short", "�ϳ�");
        set("long", @LONG
�������û����̾͵Ľֵ������ϵ����˲��࣬�����������塣ż���м�
������������ε������߹��������������壬����ľ���������һ���Ͱ�
���������ſڹ���һ��д�����ĵĻ��ӣ���������������㣬��������һ��
С���ݡ�
LONG );
        set("exits", ([
                "north" : __DIR__"jishi",
                "south" : __DIR__"muqiao",
                "west"  : __DIR__"rouguan",
                "southeast" : __DIR__"tulu",
        ]));
        set("objects", ([
                __DIR__"npc/tengyilei" : 1,
        ]));
        set("outdoors", "guanwai");
        set("coor/x", 3990);
	set("coor/y", 9230);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}