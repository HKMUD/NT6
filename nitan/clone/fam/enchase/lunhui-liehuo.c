inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIM "ÂÖ»Ø¡¤ÁÒ»ğ" NOR, ({"lunhui liehuo","lunhui","liehuo" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                 set("long", HIM "ÂÖ»ØÖ®¿à¡¤ÁÒ»ğ·ÙÉí¡£\n" NOR);
                set("unit", "¿é");
                set("value", 5000);
                set("enchase/name", "ÂÖ»Ø¡¤ÁÒ»ğ");
                set("enchase/point", 100);
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

