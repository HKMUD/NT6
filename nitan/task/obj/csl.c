#include <ansi.h>
inherit TASK;
void create()
{
    set_name(HIR"´ÌÉ±Áî" NOR, ({ "csl" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "¿é");
            set("material", "stone");
            set("long", "Ò»¿éÑª¼£°ß°ßµÄÁîÅÆ¡£\n");
    }
    set("owner", "È«¹ÚÇå");
    setup();
}
