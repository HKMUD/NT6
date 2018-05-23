inherit ROOM;
#include <ansi.h> 
void create()
{
        set("short", "ÁúÌ¶");
        set("long",
"[1;31mÕâÀï¾ÍÊÇÁúÌ¶£¬Ò»Ö»¾ŞÁúÅÌ¾áÔÚÕâÀï£¬¿´¼ûÓĞÈË½øÀ´£¬·¢³ö\n"
"Ò»ÉùÕğÌì¾Şºğ£¬È»ºó±ã·¢ÆğÁË¹¥»÷¡£ÌıËµËüÊØ»¤×Å¾«ÁéÍõÁôÏÂÀ´µÄ±¦²Ø¡£\n"
"ÓĞ¿ÕµÄ»°£¬ËÑË÷(search)Ò»ÏÂ»òĞí»áÓĞÊÕ»ñ¡£\n"
);
        set("exits", ([ 
              // "south" : __DIR__"spirit6", 
           ]));
        set("objects", ([ 
             "/quest/tulong/npc/dragon" : 1,
          ]));
        set("book_count", 7);

        set("no_magic", 1);
        setup();
} 

void init()
{
  add_action ("do_search","search"); 
  add_action ("do_quit","train");}

int do_quit(string arg){
        write(query("name", this_player())+"£¬ÁúÒ²ÊÇ¿ÉÒÔÑ±µÄÃ´£¿£¡\n");
        return 1;
} 
int do_search (string arg)
{
  object who = this_player ();
  object where = this_object ();
  object book;

 if (query("book_count") < 1) 
  {
    message_vision ("$NËÄ´¦ËÑË÷ÁËÒ»·¬£¬Ê²Ã´Ò²Ã»ÓĞÕÒµ½¡£\n",who);  
    message_vision ("Ò²ĞíÊÇ±»ÄÃ¹âÁË¡£\n",who);  
    return 1;
  }
        if (  present("night's diary", who) ) {
                return notify_fail("Äã¶¼ÓĞÕâ±¾ÊéÁË£¬»¹ÒªÕÒÊ²Ã´¡£\n");
          }
 if( query_temp("mark/diary", who) )
   {
    message_vision ("$NËÄ´¦ËÑË÷ÁËÒ»·¬£¬Ê²Ã´Ò²Ã»ÓĞÕÒµ½¡£\n",who);  
    message_vision ("¿´Ñù×ÓÊÇ²»ÄÜ¶àÄÃµÄ¡£\n",who);  
    return 1;
  }

  if (random(10))
  {
    message_vision ("$NËÄ´¦ËÑË÷ÁËÒ»·¬£¬Ê²Ã´Ò²Ã»ÓĞÕÒµ½¡£\n",who);  
  }
  else
  {
    book = new ("/quest/tulong/obj/diary");
    message_vision ("$N¾¹´Ó¿İÊ÷Ò¶¼äÕÒ³öÒ»±¾"+YEL"Ò¹³½ÈÕ¼Ç"NOR+"£¡\n",who,book);
     set_temp("mark/diary", 1, who);
    book->move(who);  
message("channel:rumor",HIR"¡¾¾«ÁéÉñ½ç¡¿Ä³ÈË£º"+query("name", this_player())+"ÕÒµ½Ò¹³½ÈÕ¼ÇÀ²¡£\n"NOR,users());
   addn("book_count", -1);
  }
  return 1;
}

void reset()
{
        ::reset();
        delete("exits/north");
}