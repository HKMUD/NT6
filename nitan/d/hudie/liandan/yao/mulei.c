#include <ansi.h>
//ƒæ¿‡“©≤ƒ

inherit ITEM; 
mapping *ansi= ({
([     "yanse":    HIC,]),
([     "yanse":    HIG,]),
([     "yanse":    HIR,]),
([     "yanse":    HIB,]),
([     "yanse":    HIM,]),
([     "yanse":    HIY,]),
([     "yanse":    RED,]),
([     "yanse":    YEL,]), 
([     "yanse":    MAG,]),
([     "yanse":    CYN,]),

});
mapping *yao= ({
([     "name":     "∂≈÷Ÿ",
       "id":       "du zhong",
       "yaoxing":  1000,
]),
([     "name":     "Œ⁄ËÍ",
       "id":       "wu jiu",
       "yaoxing":  2000,
]),
([     "name":     "’¡ƒæ",
       "id":       "zhang mu",
       "yaoxing":  3000,
]),
([     "name":     "∫Ò∆”",
       "id":       "hou pu",
       "yaoxing":  4000,
]),
([     "name":     "À’ƒæ",
       "id":       "su mu",
       "yaoxing":  5000,
]),
([     "name":     "≥¡œ„",
       "id":       "chen xiang",
       "yaoxing":  6000,
]),
([     "name":     "ø‡ƒæ",
       "id":       "ku mu",
       "yaoxing":  7000,
]),
([     "name":     "Ã¥œ„",
       "id":       "tan xiang",
       "yaoxing":  8000,
]),
([     "name":     "ª∆∞ÿ",
       "id":       "huang bai",
       "yaoxing":  9000,
]),
});
void create()
{
    string name,id;
    int yaoxing,yaoo,yanse;

    yanse = random(sizeof(ansi));

    yaoo = random(sizeof(yao)); 

    name = yao[yaoo]["name"];

    id = yao[yaoo]["id"]; 

    yaoxing = yao[yaoo]["yaoxing"]; 

     //set_name(ansi[yanse]["yanse"]+name+NOR,({id}) );  
     set_name(name,({id}) );  

    set_weight(100);
    if( clonep() )
    set_default_object(__FILE__);
    else {
         set("unit", "÷Í");                        
        }

   set("yaoxing",yaoxing);
   set("yao",1);
   setup();
  }

