#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "¹ú×Ó¼à");
        set("long", @LONG
ÕâÀï¾ÍÊÇ¾©³ÇµÄ¹ú×Ó¼à¡£¹ú×Ó¼àÊÇ³¯Í¢ÅàÑøÈË²ÅµÄµØ·½¡£¸ß¸ßµÍ
µÍµÄ×À×ÓÅÅÁËÁ½ÅÅ¡£ÔÚÕâÀï²»Ê±¿ÉÒÔ¿´µ½ÈıÈıÁ½Á½µÄÑ§ÉúÄ£ÑùµÄÈË´ó
ÉùÕù±ç×ÅÊ²Ã´ÎÊÌâ£¬»¹ÓĞÒ»Ğ©ÀÏÏÈÉúÃÇõ¾×ÅÃ¼Í·´Ò´ÒµÄ×ß¹ı£¬ÏóÊÇÔÚ
Ë¼¿¼×ÅÊ²Ã´ÎÊÌâ¡£[2£»37£»0m
LONG );
        set("exits", ([
                "south" : "/d/beijing/dong_2",
        ]));
        set("objects", ([
                "/d/beijing/npc/shusheng1" : 3,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2790);
	set("coor/y", 7740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}