#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR + YEL "¹ê¼×" NOR, ({ "gui jia", "gui", "jia" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + YEL "ÎÚ¹êµÄ¼×¿Ç£¬²»´íµÄÖıÔì²ÄÁÏ¡£\n" NOR);
                set("base_unit", "¿é");
                set("unit", "¿é");
                set("base_value", 10000);
                set("base_weight", 1000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}