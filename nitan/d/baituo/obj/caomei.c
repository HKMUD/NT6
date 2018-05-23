#include <ansi.h> 

inherit F_FOOD;
inherit ITEM;

void create()
{
        set_name("≤››Æ", ({ "cao mei", "cao", "mei" }));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", RED "’‚ «“ªø≈œ ∫ÏÀ∂¥Ûµƒ≤››Æ°£\n" NOR);
                set("unit", "ø≈");
                set("value", 10);
                set("food_remaining", 2);
                set("food_supply", 20);
        }
        setup();
}