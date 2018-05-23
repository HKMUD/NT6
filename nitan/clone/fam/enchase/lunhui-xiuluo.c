inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIM "ÂÖ»Ø¡¤ÐÞÂÞ" NOR, ({"lunhui xiuluo","lunhui","xiuluo" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                 set("long", HIM "ÂÖ»ØÖ®¿à¡¤ÐÞÂÞÃðÖ®¡£\n" NOR);
                set("unit", "¿é");
                set("value", 5000);
                set("enchase/name", "ÂÖ»Ø¡¤ÐÞÂÞ");
                set("enchase/point", 95);
                  set("enchase/type", "all");
                set("enchase/cur_firm", 85);
                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}

