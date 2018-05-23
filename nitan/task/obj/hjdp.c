#include <ansi.h>  
inherit TASK;  
void create()  
{ 
    set_name(HIW"ºú¼Òµ¶Æ×"NOR, ({ "daopu" }) );  
    set_weight(10);
       if( clonep() ) 
            destruct(this_object());  
    else { 
            set("unit", "±¾");
            set("material", "book");  
            set("long", "ºú¼Òµ¶Æ×¶ªÊ§µôµÄÒ»Ò³¡£\n");
        }
       set("owner", "ºúì³"); 
        setup();  
}
