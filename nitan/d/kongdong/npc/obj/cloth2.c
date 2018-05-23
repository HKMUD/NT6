#include <armor.h>
inherit CLOTH;


void create()
{
        set_name("»ÒÉ«µÀÅÛ", ({ "dao pao","pao" }) );
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "¼þ");
                set("material", "cloth");
                set("armor_prop/armor", 3);
        }
        setup();
}
