inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIM "�ֻء�����" NOR, ({"lunhui egui","lunhui","egui" }));
        set_weight(900);
        if (clonep())
                set_default_object(__FILE__);
        else {
                 set("long", HIM "�ֻ�֮�ࡤ����������\n" NOR);
                set("unit", "��");
                set("value", 5000);
                set("enchase/name", "�ֻء��þ�");
                set("enchase/point", 95);
                  set("enchase/type", "all");
                set("enchase/cur_firm", 85);
                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}

