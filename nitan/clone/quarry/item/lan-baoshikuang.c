#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIC "À¶±¦Ê¯¿ó" NOR, ({ "lan baoshikuang", "lan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("base_unit", "¿é");
                set("unit", "¿é");
                set("base_value", 10000);
                set("base_weight", 600);
        }
        setup();
}
int query_autoload()
{
        return 1;
}