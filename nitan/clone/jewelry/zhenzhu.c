// zhenzhu.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(WHT"’‰÷È"NOR, ({ "zhen zhu", "zhu" }) );
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "“ª¡£¡˙—€¥Ûµƒ’‰÷È°£\n");
                set("unit", "¡£");
                set("value", 20000 );
        }

}
