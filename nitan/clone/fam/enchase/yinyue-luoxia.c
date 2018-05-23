inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIM "ÒõÔÂ¡¤ÂäÏ¼" NOR, ({"yinyue luoxia", "luoxia" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "¿é");
                set("value", 50000);
                set("enchase/name", "ÒõÔÂ¡¤ÂäÏ¼");
                set("enchase/point", 95);
                set("enchase/type", "all");
                set("enchase/cur_firm", 100);
                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}

