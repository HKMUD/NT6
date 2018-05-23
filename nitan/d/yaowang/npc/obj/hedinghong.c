#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR"º×¶¥ºì"NOR, ({"he dinghong"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "µÎ");
                set("long", "ÕâÊÇÒ»µÎº×¶¥ºì£¬Ææ¶¾ÎÞ±È¡£\n");
                set("yaowang", 1);
                set("value", 1000);
                set("weight", 1000);
        }
        setup();
}
