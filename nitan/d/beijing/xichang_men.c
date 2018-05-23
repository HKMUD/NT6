inherit ROOM;
#include <ansi.h>

void create()
{
        set("short",RED"Î÷³§´óÃÅ"NOR);
        set("long", @LONG
ÕâÀï¾ÍÊÇ¾©³ÇµÄÌØÎñ»ú¹¹¡ª¡ªÎ÷³§µÄ´óÃÅ¡£ÕâÀï¾¯±¸ÉîÑÏ£¬²»Ê±
ÓĞ´©×ÅÖÆ·şµÄÎ÷³§¹Ù±ø½ø½ø³ö³ö£¬Íû´óÃÅÀïÍûÈ¥£¬¿ÉÒÔÍû¼û´óÃÅÀïÃæ
ÓĞĞí¶àÌ«¼à¡£´óÃÅÁ½ÅÔµÄÎ÷³§¹Ù±øÕıÈçÀÇËÆ»¢µÄ¶¢×ÅÄã¿´£¬Èç¹ûÄã²»
ÏëÕÒËÀµÄ»°£¬×îºÃ»¹ÊÇ¸Ï¿ìÀë¿ªµÄºÃ¡£[2£»37£»0m
LONG );
        set("exits", ([
                "south" : "/d/beijing/xichang",
                "north" : "/d/beijing/di_2",
        ]));
        set("objects", ([
                "/d/beijing/npc/bing3" : 2,
                "/d/beijing/npc/taijian" : 1,
        ]));
        set("no_fight", 0);
	set("coor/x", -2810);
	set("coor/y", 7700);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (objectp(present("guan bing", environment(me))) && dir == "south")
                return notify_fail("Î÷³§¹Ù±øÉìÊÖ½«ÄãÀ¹×¡¡£\n\n");
        return ::valid_leave(me, dir);
}