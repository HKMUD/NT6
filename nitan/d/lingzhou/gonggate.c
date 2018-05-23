// Room: /lingzhou/gonggate.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "�ʹ�����");
        set("long", @LONG
����������Ļʹ����ţ����ȿ����������ţ��������ȭͷ���
ͭ�����ŵ�����վ�������¼���������ʿ���䱸���ϡ�
LONG );
        set("exits", ([
                "north"  : __DIR__"gongsquare",
                "south"  : __DIR__"beidajie",
        ]));
        set("outdoors", "lingzhou");
        set("objects", ([
                __DIR__"npc/gongweishi" : 2,
        ]));
        set("coor/x", -6265);
        set("coor/y", 2945);
        set("coor/z", 0);
        setup();
        create_door("north" , "���Ṭ��", "south" , DOOR_CLOSED);
}

int valid_leave(object me, string dir)
{
        if (dir == "north" && 
            objectp(present("wei shi", environment(me))))
           return notify_fail("��ʿ������һ�����������ǲ������ܽ�ȥ�ĵط���\n");

        return ::valid_leave(me, dir);
}