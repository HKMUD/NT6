#include <ansi.h>
//¹ûÀàÒ©²Ä

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
([     "name":     "èÛè½",
       "id":       "gou qi",
       "yaoxing":  10,
]),
([     "name":     "ÂÞºº¹û",
       "id":       "luohan guo",
       "yaoxing":  20,
]),
([     "name":     "´©ÐÄÁ«",
       "id":       "chuanxin lian",
       "yaoxing":  30,
]),
([     "name":     "³ÂÆ¤",
       "id":       "chen pi",
       "yaoxing":  40,
]),
([     "name":     "¶¹Þ¢",
       "id":       "dou kou",
       "yaoxing":  50,
]),
([     "name":     "°Í¶¹",
       "id":       "ba dou",
       "yaoxing":  60,
]),
([     "name":     "É½é«",
       "id":       "shan zha",
       "yaoxing":  70,
]),
([     "name":     "ÜîÏã",
       "id":       "hui xiang",
       "yaoxing":  80,
]),
([     "name":     "è×Êµ",
       "id":       "zhi shi",
       "yaoxing":  90,
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
         set("unit", "¿Å");                        
        }

   set("yaoxing",yaoxing);
   set("yao",1);
   setup();
  }

