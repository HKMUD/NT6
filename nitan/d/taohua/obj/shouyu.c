//Cracked by Kafei
// 
inherit ITEM;

void create()
{
        set_name("ª∆“© ¶ ÷⁄Õ", ({"shou yu", "yu", "letter"}));
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "∑‚");
                set("long","\n
=================================
|                                |
|                ◊÷                |
|                ⁄Õ                |
|                ¡È                |
|                ∑Á                |
|                Œ·                |
|                ÕΩ                |
|                                |
|                        Ã“        |
|                        ª®        |
|                        ª∆        |
|                                |
|                        ºÍ        |
|                                |
=================================\n");
                set("material", "paper");
        }
}