#include <ansi.h>
//²ÝÀàÒ©²Ä

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
([     "name":     "ÓãÐÈ²Ý",
       "id":       "yuxing cao",
       "yaoxing":  10000,
]),
([     "name":     "ÒæÄ¸²Ý",
       "id":       "yimu cao",
       "yaoxing":  20000,
]),
([     "name":     "Þ½Ïã",
       "id":       "huo xiang",
       "yaoxing":  30000,
]),
([     "name":     "²ÝÉºº÷",
       "id":       "cao shanhu",
       "yaoxing":  40000,
]),
([     "name":     "´©ÐÄÁ«",
       "id":       "chuanxin lian",
       "yaoxing":  50000,
]),
([     "name":     "ÔóÀ¼",
       "id":       "ze lan",
       "yaoxing":  60000,
]),
([     "name":     "½Ê¹ÉÀ¶",
       "id":       "jiaogu lan",
       "yaoxing":  70000,
]),
([     "name":     "»¢¶ú²Ý",
       "id":       "huer cao",
       "yaoxing":  80000,
]),
([     "name":     "½ðÇ®²Ý",
       "id":       "jinqian cao",
       "yaoxing":  90000,
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
         set("unit", "Öê");                        
        }

   set("yaoxing",yaoxing);
   set("yao",1);
  set("setdbase", 1);
  set("autoload", 1);
   setup();
  }

