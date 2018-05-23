// Room: /d/shaolin/wuxing0.c
// Date: YZC 96/02/06

#include <ansi.h>

inherit ROOM;

string* dirs = ({"east", "south", "west", "north"});

void create()
{
        set("short",HIY "ÎåĞĞ¶´" NOR);
        set("long", @LONG
[1£»33mÕâÊÇÎåĞĞ¶´¡£ËÄÖÜÒ»Æ¬ÁÁ¾§¾§µÄ£¬¶¨¾¦Ï¸¿´£¬È´ÊÇÎŞÊı·æÀûµÄµ¶
¼â´ÓÇ½ÉÏ£¬µØÉÏ£¬¶¥ÉÏ£¬ËÄÃæ°Ë·½ÏòÄãÉì¹ıÀ´£¬ÉÔ²»ÁôÉñ¾Í»á×Ô¼º×²
µ½µ¶¼âÉÏÈ¥¡£µ¶¹âÑ£Ä¿£¬¸üÌí³¹¹Çº®Òâ¡£¼¸¾ßÑªÁÜÁÜµÄ¶ÏÖ«²Ğº¡¹ÒÔÚ
µ¶¼âÉÏ£¬¿´À´ÒÑ¾­ÓĞĞ©Ê±ÈÕÁË¡£Ç½±ÚºÚºõºõµÄ£¬ËÆÊÇ¸ÖÌúÖı³É¡£[2£»37£»0m
LONG );
        set("exits", ([
                "east" : __DIR__"wuxing4",
                "south" : __DIR__"wuxing3",
                "west" : __DIR__"wuxing1",
                "north" : __DIR__"wuxing2",
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
                return 1;
        }
        return 0;
}

int valid_leave(object me, string dir)
{
        int count;

        if (member_array(dir, dirs) != -1)
        {
                if (dir == "north")
                {
//                        write("*½ğÉúË®*\n");
                        count=query_temp("wuxing/Ë®", me);
                        count++;
                        set_temp("wuxing/Ë®", count, me);
                        if (check_out(me))
                        {
                                write("ÄãË³ÀûµØ×ß³öÁËÎåĞĞÃÔ¹¬¡£\n");
                                return 1;
                        }
                }
                else if (dir == "west")
                {
//                        write("*½ğ¿ËÄ¾*\n");
                        delete_temp("wuxing", me);
                        me->move(__DIR__"jianyu1");
                        write("Äãµô½ø»ú¹Ø£¬ÂäÈëÉ®¼à¡£\n");
                        return 1;
                }
        }
        return ::valid_leave(me, dir);
}
