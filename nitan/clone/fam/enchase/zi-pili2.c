inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(MAG "×ÏÅùö¨" NOR, ({"zi pili"}));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "Á£");
                set("value", 500000);
                set("enchase/name", "×ÏÅùö¨");
                set("enchase/point", 1);
                set("enchase/type", "wrists");
                                set("enchase/cur_firm", 100);
                                set("nine_object", 1); // ¾Å¿×ÏâÇ¶ÎïÆ·±ê¼Ç
                                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}

