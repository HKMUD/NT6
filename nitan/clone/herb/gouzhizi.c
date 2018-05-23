#include "herb.h"

void create()
{
        set_name(HIR"èÛè××Ó"NOR, ({"gouzhi zi","gouzhi","zi"}));
        if (clonep())
                set_default_object(__FILE__);
        else 
        {
                set("long","èÛè××Ó£¬Î¶¸Ê£¬É«ºì£¬²¹ÑªÁ¼Ò©¡£\n");
                set("base_unit", "Á£");
                set("base_value", 4000);
                set("base_weight", 60);
                set("cure_s",5);
                set("cure_d",0);
                set("cure_n",0);                
        }
        setup();
}