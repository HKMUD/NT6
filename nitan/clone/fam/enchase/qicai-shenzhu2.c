inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIR "∆ﬂ"HIY"≤ "HIC"…Ò"HIG"÷È" NOR, ({"qicai shenshi"}));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "¡£");
                set("value", 500000);
                set("enchase/name", "∆ﬂ≤ …Ò÷È");
                set("enchase/point", 1);
                set("enchase/type", "neck");
                                set("enchase/cur_firm", 90);
                                set("nine_object", 1); // æ≈ø◊œ‚«∂ŒÔ∆∑±Íº«
                                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}

