inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(" Ï≈£»‚", ({"niu rou", "rou"}));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "“ªøÈœ„≈Á≈Áµƒ Ï≈£»‚°£\n");
                set("unit", "÷ª");
                set("value", 150);
                set("food_remaining", 3);
                set("food_supply", 60);
        }
}