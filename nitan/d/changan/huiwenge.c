//Room: huiwenge.c

#include <ansi.h>

inherit ROOM;

void create ()
{
        set ("short", "»ãÎÄ¸ó");
        set("long", @LONG
ÕâÊÇÒ»¼ÒÊé¾Ö¡£´óÌÃÀï°ÚÁËÒ»ÅÅÅÅµÄÊé¹ñ£¬Êé¼ÜÉÏÕûÕûÆëÆëµØ·Å
×ÅÒ»Ğ©¾íÖá£¬ÌÃÄÚ»¹Ğü¹Ò×Å¼¸Åè»¨»¨²İ²İ£¬ºìÂÌÏà¼ä£¬ÊèÃÜÓĞÖÂ£¬Áî
ÈËÉÍĞÄÔÃÄ¿¡£½øÀ´¾Í¿ÉÒÔ¿´µ½Ò»¶îºáØÒ£º[1£»34m         ÊéÉ½ÓĞ¾¶ÇÚÎªÂ· 
        Ñ§º£ÎŞÑÄ¿à×öÖÛ[2£»37£»0m
LONG );

        set("exits", 
        ([ //sizeof() == 1
                "west" : "/d/changan/yongtai-dadao3",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/shuchi" : 1,
        ]));

        set("no_clean_up", 0);
        set("coor/x", -10750);
	set("coor/y", 1930);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}