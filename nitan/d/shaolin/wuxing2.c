// Room: /d/shaolin/wuxing2.c
// Date: YZC 96/02/06

#include <ansi.h>

inherit ROOM;

string* dirs = ({"east", "south", "west", "north"});

void create()
{
        set("short", HIB "ÎåĞĞ¶´" NOR);
        set("long", @LONG
[1£»34mÕâÊÇÎåĞĞ¶´¡£Ò»½øÕâÀï£¬Äã¾ÍÏİÔÚÆëÑüÉîµÄË®Àï£¬½Åµ×ÊÇºñºñµÄ
ÓÙÄà£¬Ò»²ÈÉÏÈ¥¾ÍËÉËÉµØÉ¢¿ª£¬»¹´ø³öÒ»´ó´®ÆøÅİÃ°³öË®Ãæ¡£×î¿É²À
µÄÊÇË®ÃæÉÏ²»Ê±Æ®¹ıÀ´Ò»Á½¾ß½şµÃ·¢Ö×µÄ¸¡Ê¬£¬¼¸Ö»ÀÏÊóÔÚÉÏÃæÅÀÉÏ
ÅÀÏÂ£¬°ÑÊ¬ÌåÒ§µÃÃæÄ¾È«·Ç¡£ËÄ±ÚÓÃ´Ö²ÚµÄÆ¬ÑÒÀİ¶â¶ø³É£¬Ò»¿Å¿ÅË®
ÖéÑØ×ÅÇ½±Ú¹öÏÂÀ´£¬½¦ÔÚË®ÖĞ£®[2£»37£»0m
LONG );
        set("exits", ([
                "east" : __DIR__"wuxing1",
                "south" : __DIR__"wuxing4",
                "west" : __DIR__"wuxing0",
                "north" : __DIR__"wuxing3",
        ]));
        set("no_clean_up", 0);
        setup();
}

int check_out(object me)
{
        int metal, wood, water, fire, earth;

        metal=query_temp("wuxing/½ğ", me);
        wood=query_temp("wuxing/Ä¾", me);
        water=query_temp("wuxing/Ë®", me);
        fire=query_temp("wuxing/»ğ", me);
        earth=query_temp("wuxing/ÍÁ", me);

        if ( metal > 0 &&
                metal == wood && metal == water &&
                metal == fire && metal == earth )
        {
                delete_temp("wuxing", me);
                me->move(__DIR__"andao2");
                return (1);
        }
        return (0);
}

int valid_leave(object me, string dir)
{
        int count;

        if (member_array(dir, dirs) != -1)
        {
                if (dir == "east")
                {
//                        write("*Ë®ÉúÄ¾*\n");
                        count=query_temp("wuxing/Ä¾", me);
                        count++;
                        set_temp("wuxing/Ä¾", count, me);
                        if (check_out(me))
                        {
                                write("ÄãË³ÀûµØ×ß³öÁËÎåĞĞÃÔ¹¬¡£\n");
                                return 1;
                        }
                }
                else if (dir == "north")
                {
//                        write("*Ë®¿Ë»ğ*\n");
                        delete_temp("wuxing", me);
                        me->move(__DIR__"jianyu1");
                        write("Äãµô½ø»ú¹Ø£¬ÂäÈëÉ®¼à¡£\n");
                        return 1;
                }
        }
        return ::valid_leave(me, dir);
}
