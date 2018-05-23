#include <room.h>
inherit ROOM;

void create()
{
        set("short", "ÇàÄ¾ÌÃ");
        set("long", @LONG
ÉÐÎ´¿ª·Å¡£
LONG );
        set("exits", ([
                "north" : "/d/beijing/yangliu3",
        ]));
        replace_program(ROOM);
}
