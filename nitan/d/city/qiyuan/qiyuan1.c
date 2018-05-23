//ÆåÔ·

#include <ansi.h>
inherit  ROOM;

string look_string();

void  create  ()
{
    set  ("short",  "ÆåÔ·");
        set("long", @LONG
ÆåÔ·¹²·ÖËÄ¸ö´ó¼ä£¬ÊÇÊÖÌ¸ĞİÆÜµÄºÃµØ·½¡£ÕâÀïµÄÄÏ±±ºÍÎ÷Èı¸ö
·½Ïò¸÷ÓĞÒ»¼äÆåÊÒ£¬ÔÚÃ¿¸öÆåÊÒµÄÃÅÍâ¶¼Ìù×Å[1£»33mÇëÎğ´òÈÅÆå¾Ö[2£»37£»0mµÄÅÆ×Ó£¬
ÔÚ·¿¼äÖĞÑëµÄÖù×ÓÉÏ»¹Ìù×ÅÒ»ÕÅÏÂÆåÖ¸ÄÏ(help)¡£
LONG );

  set("no_dazuo",1);set("no_kill",1);set("no_fight",1);
         set("no_steal",1);
         set("pingan",1);
         set("no_beg",1);         
    set("item_desc", ([
    "help" : ( : look_string : ),
    ]));

    set("exits",  ([
    "east"  :  __DIR__"qiyuan2",
    "south"  :  __DIR__"qiyuan3",
    "north"  :  __DIR__"qiyuan4",
    "west" : "/d/pingan/nan2",
    ]));

     set("objects",  ([
    __DIR__"cch"  :  1,
    ]));
   setup();
}

string look_string()
{
        string  msg  =  "»¶Ó­µ½ÆåÔ·À´ÏÂÆå£¡\n"  +
"
ÔÚÕâÀïÄú¿ÉÒÔÏÂÎ§Æå»òÎå×ÓÆå£¬ÒÔÏÂÊÇÏÂÆåµÄ²½Öè£º
Ò»¡¢ÏÈÕÒºÃ¶ÔÊÖ£¬È»ºó·Ö±ğÓÃ  sit black  ºÍ  sit white  Èë×ù£»
¶ş¡¢Ê¹ÓÃ new ¿ªÊ¼Ò»ÅÌĞÂµÄÆå¾Ö£ºnew [-5] [-b(numbers)] [-h(numbers)]
    ÆäÖĞ -5  ´ú±íÏÂÎå×ÓÆå£¬²»Ñ¡¼´ÎªÏÂÎ§Æå£»
      ¡¡ -b  Ö¸¶¨ËùÓÃÆåÅÌµÄ´óĞ¡£»
         -h  Ö¸¶¨ÈÃ×ÓµÄÊıÄ¿£»
¡¡¡¡ÀıÈç£º
¡¡¡¡Î§Æå new
    ÈÃ¾Å×ÓÎ§Æå£ºnew -h9
    Ê®Îå³ËÊ®ÎåµÄÎå×ÓÆå£ºnew -5 -b15
Èı¡¢Ê¹ÓÃ play ÂÖÁ÷×ßÆå
    ÀıÈç play d4 µÈµÈ¡£
ËÄ¡¢Ê¹ÓÃ refresh ¹Û¿´ÆåÅÌ¡£
Îå¡¢Ê¹ÓÃ leave Àë¿ªÆåÅÌ¡£
Áù¡¢Ê¹ÓÃ pass Æú×ÓÈÏÊä¡£
Æß¡¢Ê¹ÓÃ undo »ÚÆå¡£Ä¿Ç°Ö»Ìá¹©Îå×ÓÆåµÄ»ÚÆå¹¦ÄÜ¡£

";
        return  msg;
}

int valid_leave(object me, string dir)
{
        object room;
        mapping exit;

        exit=query("exits", environment(me));

        if ( dir == "south" || dir == "north" || dir == "west" ) {
                if( !( room = find_object(exit[dir])) )
                       room = load_object(exit[dir]);
                if( query_temp("action", room) == 1 )
                       return notify_fail("ÄÇ¼äÆåÊÒÒÑ¾­ÓĞÈË¿ªÊ¼ÏÂÆåÁË£¬ÇëÎğ´òÈÅ\n");
                }

        return ::valid_leave(me, dir);
}