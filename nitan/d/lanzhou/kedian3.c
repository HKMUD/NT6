// /d/lanzhou/kedian3.c

inherit ROOM;

void create()
{
        set("short", "�͵��¥");
        set("long", @LONG
����һ��ܴ�Ŀͷ�������ʮ�ּ�ª����ǽ����ʮ����Сľ������
�ٿ��������¶��ԣ������Ӷ��Ǻ����Ĵ������������Ŵ��ǿյģ���
������ŵ����˹�ȥ��
LONG );
        set("sleep_room", "1");
        set("no_fight", "1");
        set("hotel",1);
        set("no_clean_up", 0);
        set("exits", ([
                "out" : __DIR__"kedian2",
        ]));
	set("coor/x", -15741);
	set("coor/y", 3799);
	set("coor/z", 9);
	setup();
}

int valid_leave(object me, string dir)
{
        if( dir == "out")delete_temp("rent_paid", me);

        return ::valid_leave(me, dir);
}