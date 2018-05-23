#include <ansi.h>
inherit ITEM;

void create()
{
        set_name( HIR "Â¹Ñª" NOR , ({"lu xue", "xue"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "Ò»µÎÃ·»¨Â¹Ñª¡£\n");
                set("unit", "µÎ");
                set("yaowang", 1);
                set("value", 1000);
                set("weight", 1000);
        }
}
