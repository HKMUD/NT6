//Room: /d/dali/road3.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","�ٵ�");
        set("long", @LONG
������һ����ʯ�ٵ��ϣ������Ѿ�����گ�����ˣ�·��ʱʱ����
������ɫ�����������������������ﲻ����·��վ��Щ�����λ��޵�
����Ů�ӣ�����һ���������µ��Եø�����������ȥ���ϼ��Ǵ�����
���ؿ�̫�ͳǣ��عٵ��򶫱��ɴ���ԭ��
LONG );
        set("objects", ([
           "/d/dali/npc/girl": 1,
        ]));
        set("outdoors", "dalin");
        set("exits",([ /* sizeof() == 1 */
            "northeast"  : "/d/dali/road2",
            "south"      : "/d/dali/dehuabei",
            "northwest"  : "/d/wanjiegu/riverside2",
        ]));
	set("coor/x", -19160);
	set("coor/y", -6820);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}