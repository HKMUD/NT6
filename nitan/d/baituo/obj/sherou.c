// sherou.c …ﬂ»‚

inherit F_FOOD;
inherit ITEM;

void create()
{
        set_name("…ﬂ»‚", ({ "she rou", "rou" }) );
        set_weight(350);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "“ªÃı…’øæµ√œ„≈Á≈Áµƒ…ﬂ»‚°£\n");
                set("unit", "Ãı");
                set("value", 50);
                set("food_remaining", 3);
                set("food_supply", 20);
        }
    setup();
}
