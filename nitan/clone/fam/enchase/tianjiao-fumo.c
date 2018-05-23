inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIG "Ìì½Î¡¤·üÄ§" NOR, ({"tianjiao fumo", "fumo" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "¿é");
                set("value", 50000);
                set("enchase/name", "Ìì½Î¡¤·üÄ§");
                set("enchase/point", 70);
                set("enchase/type", "all");
                set("enchase/cur_firm", 80);
                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}

