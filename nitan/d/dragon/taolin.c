inherit ROOM;
#include <ansi.h> 
void create()
{
        set("short", "ÌÒÁÖ");
        set("long",
"[1;32mÕâÊÇÆ¬Ã¯ÃÜµÄÌÒÁÖ(peachtree)£¬ÁÖÖĞ·¼²İÏÊÃÀ£¬ÂäÓ¢çÍ·×£¬\n"
"Ò»²ãµ­µ­µÄ±¡Îí£¬»ìºÏ×ÅÇàÇàµÄ²İÏã£¬ÃÖÂşÔÚ¿ÕÆøÖ®ÖĞ¡£Å¼¶ûµÄÒ»Á½ÉùÄñ\n"
"Ãù£¬Óú·¢µØÏÔ³öÓÄ¾²À´¡£ÕâÀïµÄĞ¡Â·ÒÑ±»Âä»¨ÆÌÂú£¬ÔçÒÑ±æ²»³öºÛ¼£À´¡£\n"
"[2;37;0m\n"
);
        set("exits", ([ /* sizeof() == 4 */
  "south" : __DIR__"lake1",
]));

        set("item_desc", ([
            "ÌÒÊ÷": "·ÛÔÆ²ÊÏ¼°ãµÄÌÒ»¨£¬ÈÈÈÈÄÖÄÖµØ¿ªÂúÁËÖ¦Í·¡£\n",
            "peach tree": "·ÛÔÆ²ÊÏ¼°ãµÄÌÒ»¨£¬ÈÈÈÈÄÖÄÖµØ¿ªÂúÁËÖ¦Í·£¬ÈÃÈËÈÌ²»×¡ÏëÕª(pick)Ò»Ö¦ÌÒÖ¦(taozhi)ÏÂÀ´¡£\n",
        ]) );

        set("no_magic", 1);
        setup();
}

void init() 
{
   add_action("do_pick", "pick");
}

int do_pick(string arg)
{
   object me, where, zhi;

   me = this_player(); 
        where=environment(me); 
   if(!arg || arg != "taozhi" && arg != "ÌÒÖ¦") return 0;       
   if( query_temp("marks/taozhi", where)){
      tell_object(me, "\nÔÙÕªÌÒÊ÷¾ÍÍºÁË! \n");  
      return 1;
   }    
   zhi = new("/quest/tulong/obj/taozhi");
   zhi->move(me);
   set_temp("marks/taozhi", 1, where);
   message_vision("\n$NÉìÊÖÕªÁËÒ»Ö¦ÌÒ»¨ÏÂÀ´¡£\n", me);
        
   return 1;    
}
