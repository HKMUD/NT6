// Code of ShenZhou
// shegu.c �߹�
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "�߹��µ�");
        set("long", @LONG
�����Ѿ����߹ȵ���һ�ˣ�ɽ������ϴ����ϱ���һƬ���֣�
����������ʯ��᾵�ɽ�¡�
LONG );

        set("exits", ([ 
            "northup" : __DIR__"shegu_shanya",
            "southwest" : __DIR__"shegu18",
        ]));

        set("objects", ([
            __DIR__"npc/bt_snake" : 2,
        ]));

        set("cost", 2);
        set("outdoors","baituo");
        set("shegu", 1);
        set("coor/x", -49940);
        set("coor/y", 20190);
        set("coor/z", 20);
        setup();
}

#include "snake_room.h"