//Room: jiulou2.c

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "ÍûĞÇÂ¥¶şÂ¥");
        set("long", @LONG
¶şÂ¥ÊÇ¾ÆÂ¥µÄÑÅ×ù¡£ÔÚÕâÀïµÄ¿ÍÈËÃÇ¶¼µÍÑÔÂıÓï£¬²»ÏóÂ¥ÏÂµÄ¿Í
ÈËÄÇ°ã¿ñºôºÀÒû¡£¶şÂ¥ÂôµÄ¾Æ²ËÒ²ÊÇÍûĞÇÂ¥ÕÆ³ø×îÄÃÊÖµÄ¡£Á½ÅÔ¹Ò×Å
³¤ÁªÖ±¹áÎİ½Ç£º[1£»31m       ¾ı¼´Òû´Ëõü£¬¶Ô¾Æ¸ß¸è£¬ÈË×íÂ¥Í·£¬´ıÁõÁæÍ¬
ÀÖ£»       ÓàÒàõ¸Ò»ÃÎ£¬ÁÙ·ç°ÑÕµ£¬ÔÆºá½­ÉÏ£¬ÓëÍõôÓÏú³î¡£[2£»37£»0m
LONG );


        set("exits", ([
                "down" : "/d/changan/jiulou",
        ]));
        set("objects", ([
                "/d/changan/npc/yang-laoban" : 1,
        ]));

        set("coor/x", -10750);
	set("coor/y", 1970);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}