inherit ROOM;

void create()
{
        set("short", "��");
        set("long", @LONG
����һ�䰫С���߷���ƽʱ��Ϊ�ѷ��������á������ﲼ
�����������������ǻҳ����������Ѿ��ܾ�û���˴�ɨ�ˡ���
����һ��б���ż����ɲ�
LONG);
        set("exits", ([
                  "north" : __DIR__"miaojia_dayuan",
        ]));
        set("no_clean_up", 0);
        set("objects", ([
                "/clone/misc/ganchai" : 2,
        ]));
        set("coor/x", -9020);
	set("coor/y", -970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}