// white_silk °×É´È¹
// 01/08/03
// Code by April

#include <armor.h>
#include <ansi.h>
inherit CLOTH;

void create()
{
        set_name("°×É´È¹", ({ "white skirt","skirt" }) );
                //set_color("$HIW$");
        set_weight(800);
        
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "¼þ");
                        set("long", "Ò»¼þ½à°×µÄÉ´È¹¡£\n");
            set("material", "cloth");
            set("value", 0);
            set("armor_prop/armor", 8);
            set("armor_prop/per", 5);
            set("female_only", 1);
        }

        setup();
}
