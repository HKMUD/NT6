#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR "»ð·ï»ËÖ®½î" NOR, ({ "phoenix vein", "vein" }));
        set_weight(4000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "Ò»¸ù»ð·ï»ËµÄ½î£¬¾§Ó¨Í¸ÁÁ¡£\n" NOR);
                set("unit", "¸ù");
                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
