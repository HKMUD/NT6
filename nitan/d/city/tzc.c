#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY+BLINK"ÌôÕ½ÀŞÌ¨"NOR);
        set("long", @LONG
[1£»36mÕâÀïÊÇ×¨ÃÅÉèÀ´½ÓÊÜÍâ¹úÌôÕ½µÄÀŞÌ¨¡£
LONG );
        set("no_drift", 1);
        set("no_clean_up", 0);
        set("exits",([
                "down" : "/d/city/guangchang",
        ]));

        setup();
        replace_program(ROOM);
}
