#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(BLU"∂œ≥¶≤›"NOR, ({"duanchang cao", "duanchang"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "÷Í");
                set("long", "’‚ «“ª÷Í∂œ≥¶≤›£¨∆Ê∂æŒﬁ±»°£\n");
                set("yaowang", 1);
                set("dig", 1);
                set("value", 1000);
                set("weight", 1000);
        }
        setup();
}
