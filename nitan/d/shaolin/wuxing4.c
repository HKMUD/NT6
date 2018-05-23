// Room: /d/shaolin/wuxing4.c
// Date: YZC 96/02/06

#include <ansi.h>

inherit ROOM;

string* dirs = ({"east", "south", "west", "north"});

void create()
{
        set("short", HIW "ÎåĞĞ¶´" NOR);
        set("long", @LONG
[1£»37mÕâÊÇÎåĞĞ¶´¡£µØÃæÊÇÄàÍİµØ£¬²ÈÉÏÈ¥°¼Í¹²»Æ½¡£ËÄ±ÚÒ²¶¼ÊÇÍÁÇ½
Öş³É£¬ÃşÉÏÈ¥Ïàµ±¸ÉÔï£¬Ê±¶ø»¹»áµôÏÂÒ»´ó¿é»ÒÍÁÀ´¡£´ÓÇ½½Ç»¹ÄÜ¿´
µ½Ò»Ğ©ÀÏÊó¶´¡£µØÃæÓĞÊ±»áÂ¡ÆğÒ»³¤Ìõ£¬ËÆºõÓĞÊ²Ã´¶«Î÷´ÓÍÁÏÂ×êÁË
¹ıÈ¥¡£[2£»37£»0m
LONG );
        set("exits", ([
                "east" : __DIR__"wuxing1",
                "south" : __DIR__"wuxing3",
                "west" : __DIR__"wuxing0",
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
                return (1);
        }
        return (0);
}

int valid_leave(object me, string dir)
{
        int count;

        if (member_array(dir, dirs) != -1)
        {
                if (dir == "west")
                {
//                        write("*ÍÁÉú½ğ*\n");
                        count=query_temp("wuxing/½ğ", me);
                        count++;
                        set_temp("wuxing/½ğ", count, me);
                        if (check_out(me))
                        {
                                write("ÄãË³ÀûµØ×ß³öÁËÎåĞĞÃÔ¹¬¡£\n");
                                return 1;
                        }
                }
                else if (dir == "north")
                {
//                        write("*ÍÁ¿ËË®*\n");
                        delete_temp("wuxing", me);
                        me->move(__DIR__"jianyu1");
                        write("Äãµô½ø»ú¹Ø£¬ÂäÈëÉ®¼à¡£\n");
                        return 1;
                }
        }
        return ::valid_leave(me, dir);
}
