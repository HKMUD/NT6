inherit ROOM;

void create()
{
        set("short", "����¥����");
        set("long", @LONG
����������������ѧʿ������������ʫ��������������Ҳ������߳�
�ȱ������ס�����Ҳ�ǳ���ٰ�ϲ�����ѳ�������վ��¥��������ֻ��
���Ŀ�������������һ�غ�ˮ���̲��������������ǳ�ɽ���룬�����ۻ룬
Ρ��׳�ۡ�
LONG);

        set("no_clean_up", 0);
        set("exits", ([
                  "up" : __DIR__"zuixianlou3",
                  "down" : __DIR__"zuixianlou",
        ]));
        set("objects", ([
                "/d/kaifeng/npc/shike" : 2,
        ]));
	set("coor/x", -6980);
	set("coor/y", 2190);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}