inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
���������������������ҵط��ż������ţ���λ�䵱��������ϥ
�������������
LONG );
        set("exits", ([
                "west" : __DIR__"donglang2",
        ]));
        set("objects", ([
                "/d/village/obj/zhujian" : 3
        ]));
        set("coor/x", -340);
        set("coor/y", -300);
        set("coor/z", 90);
        setup();
}