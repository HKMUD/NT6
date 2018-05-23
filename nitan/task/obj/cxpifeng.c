#include <ansi.h>
#include <armor.h>
inherit TASK;
void create()
{
        set_name(HIR"²ÊÏ¼Åû·ç"NOR, ({ "cxpifeng" }) );
        set_weight(3000);
        if( clonep() )
            destruct(this_object());
        else {
                set("unit", "¼þ");
                set("material", "cloth");
                set("armor_prop/armor", 2);
                set("armor_prop/spells", 3);
        }
        set("owner", "ÈÎÓ¯Ó¯");
        setup();
}
