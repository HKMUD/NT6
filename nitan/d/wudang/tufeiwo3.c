inherit ROOM;

void create()
{
        set("short", "����С·");
        set("long", @LONG
������һ��Ƨ��������С·�ϣ���������ɭɭ�����֡�ֻ������
ǰ�󣬵�����������ǵص������֡���ʮ�ɸߵĴ���������һ�飬��
ʵ��֦Ҷ��һ�����ɡ��������գ��������ڵ�˿��Ҳ�ޡ���˵����
���������˳�û�����ɾ�����
LONG );
        set("outdoors", "sanbuguan");
        set("no_sleep_room", 1);
        set("exits", ([
                "west" : __DIR__"tufeiwo2",
        ]));
        set("objects", ([
                __DIR__"npc/tufei1" : 2 ,
                __DIR__"npc/tufeitou" : 1, 
        ]));
        set("coor/x", -310);
        set("coor/y", -200);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}