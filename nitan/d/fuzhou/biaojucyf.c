// Room: /city/biaojucyf.c

inherit ROOM;

void create()
{
        set("short", "ǩѺ��");
           set("long", @LONG
�����Ǹ����ھ�ǩѺ�����ھֺ͹ٸ��������뽭���ϵ�ͬ����
Ҳ����Ҳ�ǹϸ����ء���Щ����������ϵ�ӭ�����������������к���
LONG
        );
        set("exits", ([
                "east" : __DIR__"biaojudy",
        ]));
        set("objects", ([
                __DIR__"npc/gao" : 1,
        ]));
	set("coor/x", -111);
	set("coor/y", -6171);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}