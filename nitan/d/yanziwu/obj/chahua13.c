//chahua13.c
#include <ansi.h>;
#include <armor.h>;
inherit HEAD;

void create()
{
        set_name(HIW"�ۺ�"NOR, ({"cha hua", "hua"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", 
"һ��ѩ�׵Ĳ軨���������ˡ�\n");
                set("value", 50);
                set("material", "plant");
                set_weight(10);
                set("armor_prop/armor", 0);
                set("armor_prop/per", 3);
                set("wear_msg", "$N����ذ�һ��$n����ͷ�ϡ�\n");
                set("unequip_msg", "$N����ذ�$n��ͷ��ժ��������\n");
        }
        setup();
}