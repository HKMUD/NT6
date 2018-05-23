// tiejia.c Ìú¼×
//

#include <armor.h>
#include <ansi.h>

inherit ARMOR;

void create()
{
        set_name(NOR + WHT "¸ÖÌúîø" NOR, ({ "gangtie kai", "gangtie", "kai" }) );
        set_weight(30000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "¼ş");
                set("material", "steel");
                set("value", 300000);
                set("armor_prop/armor", 300);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
