#include <ansi.h>  
inherit TASK;
void create()
{
    set_name(HIC"Éú³½°Ë×Ö"NOR, ({ "scbz", "shengchen bazi" }) );  
    set_weight(1); 
    if( clonep() ) 
            destruct(this_object());  
    else { 
            set("unit", "ÕÅ");  
            set("material", "paper");
            set("long", "Éú³½°Ë×Ö¡£¡£¡£¡£¡£¡££¡\n"); 
        }
        set("owner", "ºìÄï");  
        setup(); 
}
