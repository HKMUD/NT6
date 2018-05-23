// Room: /city/kedian4.c
// SMALLFISH 1995/12/04

#include <ansi.h>
#include <room.h>

inherit ROOM;

int is_chat_room() { return 1; }

void create() 
{
        set("short", "ÌìÁúµî");
        set("long", @LONG
[1£»33m   ÓÀ  ºÚ  ³¤  ¾Þ  Ëû  ¹Å  Ëü  ¹Å  Ëü  Ò£  Ëü  Ò£   ÓÀ  
ÑÛ  ³É  Áú  ÃÇ  ÀÏ  µÄ  ÀÏ  µÄ  Ô¶  µÄ  Ô¶   Ô¶  ¾¦  ÒÔ  ½Å 
 È«  µÄ  Ãû  µÄ  Ãû  µÄ  Ãû  µÄ   Ô¶  ºÚ  ºó  µ×  ¶¼  ¶«  ×Ö
  ¶«  ×Ö  ¶«  ×Ö  ¶«   ÊÇ  Í·  ÊÇ  ÏÂ  ÊÇ  ·½  ¾Í  ·½  ¾Í  ·½
  ¾Í  ·½   Áú  ·¢  Áú  ÎÒ  Áú  ÓÐ  ½Ð  ÓÐ  ½Ð  ÓÐ  ½Ð  ÓÐ   
µÄ  »Æ  µÄ  ³É  µÄ  Ò»  ÖÐ  Ò»  »Æ  Ò»  ³¤  Ò»   ´«  Æ¤  ´« 
 ³¤  ´«  Èº  ¹ú  Ìõ  ºÓ  Ìõ  ½­  Ìõ   ÈË  ·ô  ÈË      ÈË  ÈË
      Áú      ºÓ      ½­[2£»37£»0m
LONG );

        set("no_fight", 1);
        set("no_steal", 1);
        set("valid_startroom", 1);
        set("no_sleep_room",1);

        set("exits", ([
                "up"   : "/d/city/kedian",
        ]));

        setup();

        "/clone/board/kedian_b"->foo();
}