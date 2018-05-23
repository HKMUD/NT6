
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name( WHT "Éß¶¾" NOR , ({"she du"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "Ò»µÎ×Ç°×É«µÄÉß¶¾¡£\n");
                set("unit", "µÎ");
                set("yaowang", 1);
                set("value", 1000);
                set("weight", 1000);
        }
}
