// chabei.c
// Last Modified by winder on May. 29 2001

inherit ITEM;
inherit F_LIQUID;

void create()
{
        set_name("²è±­",({"cha bei", "cha", "bei"}));
        set_weight(120);
        if (clonep())
                 set_default_object(__FILE__);
        else {
                 set("long", "Ò»±­ÐÂÆãµÄ²è£¬ÓÆÓÆµØÃ°×ÅÏãÆø~~~~~~\n");
                set("unit", "±­");
                set("value", 20);
                set("remaining",10);
                set("drink_supply", 20);
        }
        set("liquid", ([
                "type": "tea",
                "name": "²è",
                "remaining": 15,
                "drunk_apply": 3,
        ]));
}
