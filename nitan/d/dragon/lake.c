inherit ROOM; 
#include <ansi.h> 
void create()
{
        set("short", "ÈıÇåºş");
        set("long",
"[1;32mºşË®Çå³ºÍ¸Ã÷£¬²»Ê±¿ÉÒÔ¿´µ½¼¸Î²ÓãÌøÉÏË®Ãæ¡£ºşË®¾¡Í·ÊÇ\n"
"Ò»¸ö´óÆÙ²¼¡£ÔÚÕâÀï¿ÉÒÔÌıµ½ÆÙ²¼´ÓÉ½ÉÏÖ±³å¶øÏÂ£¬·¢³öµÄºäºäÀ×Éù¡£ºş\n"
"±ßÒ»¿é¾ŞÊ¯£¬ÉÏĞ´£¢ÈıÇåºş£¢£¬ºşÖĞÓĞÒ»Ò¶±âÖÛ¡£\n"
);
        set("exits", ([ 
  "north" : __DIR__"village",
  "east" : __DIR__"lake1",
]));
        set("resource/water",1);
         set("no_magic", 1);
        setup();
}
void init()
{
    add_action("do_yell", "yell");
}

void check_trigger()
{
    object room;

    if(!query("exits/enter") ) {
        if( !(room = find_object(__DIR__"duchuan")) )
            room = load_object(__DIR__"duchuan");
        if( room = find_object(__DIR__"duchuan") ) {
            if( query("yell_trigger", room) == 0){
                set("yell_trigger", 1, room);
                set("exits/enter", __DIR__"duchuan");
                set("exits/out", __FILE__, room);
                message("vision", "Ò»Ò¶±âÖÛ»º»ºµØÊ»ÁË¹ıÀ´£¬ô¹¹«½«Ò»¿éÌ¤½Å"
                    "°å´îÉÏµÌ°¶£¬ÒÔ±ã³Ë¿Í\nÉÏÏÂ¡£\n", this_object() );
                message("vision", "ô¹¹«½«Ò»¿éÌ¤½Å°å´îÉÏµÌ°¶£¬ĞÎ³ÉÒ»¸öÏòÉÏ"
                    "µÄ½×Ìİ¡£\n", room);
                remove_call_out("on_board");
                call_out("on_board", 15);
            }
            else
                message("vision", "Ö»ÌıµÃºşÃæÉÏÒşÒş´«À´£º¡°±ğ¼±Âï£¬"
                    "Õâ¶ùÕıÃ¦×ÅÄÅ¡­¡­¡±\n",this_object() );
        }
        else
            message("vision", "ERROR: boat not found\n", this_object() );
    }
    else 
        message("vision", "°¶±ßÒ»Ö»¶É´¬ÉÏµÄÀÏô¹¹«ËµµÀ£ºÕıµÈ×ÅÄãÄØ£¬ÉÏÀ´°É¡£\n",
            this_object() );
}
void on_board()
{
    object room;

    if( !query("exits/enter") ) return;

    message("vision", "ô¹¹«°ÑÌ¤½Å°åÊÕÁËÆğÀ´£¬Öñ¸İÒ»µã£¬±âÖÛÏòºşĞÄÊ»È¥¡£\n",
        this_object() );

    if( room = find_object(__DIR__"duchuan") )
    {
        delete("exits/out", room);
        message("vision", "ô¹¹«°ÑÌ¤½Å°åÊÕÆğÀ´£¬ËµÁËÒ»Éù¡°×øÎÈà¶¡±£¬"
            "Öñ¸İÒ»µã£¬±âÖÛÏò\nºşĞÄÊ»È¥¡£\n", room );
    }
    delete("exits/enter");

    remove_call_out("arrive");
    call_out("arrive", 20);
}
void arrive()
{
    object room;
    if( room = find_object(__DIR__"duchuan") )
    {
        set("exits/out", __DIR__"spirit9", room);
        message("vision", "ô¹¹«Ëµ¡°µ½À²£¬ÉÏ°¶°É¡±£¬Ëæ¼´°ÑÒ»¿éÌ¤½Å°å"
            "´îÉÏµÌ°¶¡£\n",room );
    }
    remove_call_out("close_passage");
    call_out("close_passage", 20);
}

void close_passage()
{
    object room;
    if( room = find_object(__DIR__"duchuan") ) {
        delete("exits/out", room);
        message("vision","ô¹¹«°ÑÌ¤½Å°åÊÕÆğÀ´£¬°Ñ±âÖÛÊ»ÏòºşĞÄ¡£\n", room);
        delete("yell_trigger", room);
    }
}
int do_yell(string arg)
{
    string dir;

    if( !arg || arg=="" ) return 0;

    if( arg=="boat" ) arg = "´¬¼Ò";
    if( query("age", this_player())<16 )
        message_vision("$NÊ¹³ö³ÔÄÌµÄÁ¦Æøº°ÁËÒ»Éù£º¡°" + arg + "¡±\n",
            this_player());
    else if( query("neili", this_player())>500 )
        message_vision("$NÎüÁË¿ÚÆø£¬Ò»Éù¡°" + arg + "¡±£¬ÉùÒôÖĞÕıÆ½ºÍµØÔ¶Ô¶´«"
            "ÁË³öÈ¥¡£\n", this_player());
    else
        message_vision("$N¹Ä×ãÖĞÆø£¬³¤Ğ¥Ò»Éù£º¡°" + arg + "£¡¡±\n",
            this_player());
    if( arg=="´¬¼Ò")
    { 
     if( !query_temp("m_success/³õ¼¶", this_player()))return notify_fail("ÄãÊÇÔõÃ´À´µÄ£¿Î×Ê¦×¥µÄ£¿ÄÇ¿É²»ºÃ¡£\n");

     if( !query_temp("m_success/»ÃÓ°", this_player()))return notify_fail("ÄãÃ»ÄÜÇ×Á¦½â¿ª·âÓ¡£¬²»ÄÜ¶ÉÄã¹ıÈ¥ÄØ¡£\n");

     if( !query_temp("m_success/ÄõÁú", this_player()))return notify_fail("Äã²Î¼ÓÍÀÁúÁËÂğ£¿»òÕßÄãÃ»Ç×ÊÖÉ±ÁËËü£¿ÕâÑùÊÇ²»ĞĞµÄ¡£\n");
        check_trigger();
        return 1;
    }
    else
        message_vision("ºşÃæÉÏÔ¶Ô¶´«À´Ò»Õó»ØÉù£º¡°" + arg +
            "¡«¡«¡«¡±\n", this_player());
    return 1;
}

void reset()
{
    object room;

    ::reset();
    if( room = find_object(__DIR__"duchuan") )
        delete("yell_trigger", room);
}

