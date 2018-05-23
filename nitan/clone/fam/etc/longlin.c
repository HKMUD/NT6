#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "ýˆÁÛ" NOR, ({ "dragon palta", "palta" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "Ò»Æ¬ýˆÁÛ£¬¹â²Ê¶áÄ¿¡£\n" NOR);
                set("unit", "Æ¬");
                set("value", 100000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}