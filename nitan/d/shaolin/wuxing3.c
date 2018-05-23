// Room: /d/shaolin/wuxing3.c
// Date: YZC 96/02/06

#include <ansi.h>

inherit ROOM;

string* dirs = ({"east", "south", "west", "north"});

void create()
{
        set("short", HIR "ÎåĞĞ¶´" NOR);
        set("long", @LONG
[1£»31mÕâÊÇÎåĞĞ¶´¡£½øÀ´¶Ù¾õÒ»¹ÉÈÈÀËÆËÃæ¶øÀ´£¬³åµÃÄã²îµãÔÎÁË¹ıÈ¥¡£
ËÄÖÜÒ»Æ¬Í¨ºì£¬µØÃæÉÏÃ°×ÅË¿Ë¿°×Æø£¬½Åµ×¾çÁÒµÄÖËÍ´Ê¹Äã¼¸ºõÁ¢½Å
²»×¡¡£ÈÈ·ç´ø×ÅÂ¡Â¡¾ŞÏì³å»÷×Å¶ú¹Ä£¬ÁîÄã¾õµÃÖÃÉíºéÂ¯Ö®ÖĞ£¬È«Éí
µÄË®·Ö¶¼ÔÚ±»Ò»µÎµÎµØ¿¾¸É¡£Ç½½ÇÉÏ¼¸¾ß¿İ²ñ°ãµÄ¸ÉÊ¬¾ÍÖ¤Ã÷ÁËÕâÒ»
µã¡£[2£»37£»0m
LONG );
        set("exits", ([
                "east" : __DIR__"wuxing1",
                "south" : __DIR__"wuxing2",
                "west" : __DIR__"wuxing0",
                "north" : __DIR__"wuxing4",
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
                if (dir == "north")
                {
//                        write("*»ğÉúÍÁ*\n");
                        count=query_temp("wuxing/ÍÁ", me);
                        count++;
                        set_temp("wuxing/ÍÁ", count, me);
                        if (check_out(me))
                        {
                                write("ÄãË³ÀûµØ×ß³öÁËÎåĞĞÃÔ¹¬¡£\n");
                                return 1;
                        }
                }
                else if (dir == "west")
                {
//                        write("*»ğ¿Ë½ğ*\n");
                        delete_temp("wuxing", me);
                        me->move(__DIR__"jianyu1");
                        write("Äãµô½ø»ú¹Ø£¬ÂäÈëÉ®¼à¡£\n");
                        return 1;
                }
        }
        return ::valid_leave(me, dir);
}
