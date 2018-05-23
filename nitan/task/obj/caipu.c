#include <ansi.h>
inherit TASK;
void create()
{
    set_name(HIC"×íÏÉÂ¥²ËÆ×" NOR, ({ "cai pu" }) );
    set_weight(1);
    if( clonep() )
            destruct(this_object());
    else {
            set("unit", "±¾");
            set("material", "stone");
            set("long", "Ò»±¾×íÏÉÂ¥²ËÆ×\n");
          }
    set("owner", "ÙşÀÏ°å");
    setup();
}
