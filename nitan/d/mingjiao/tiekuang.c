// Code of JHSH
// Room: /d/mingjiao/luanshidui.c
// Zhangchi 3/00

#include <ansi.h>
inherit ROOM;

int start_wa(object me);
int check_busy(object me);

void create()
{
        set("short",HIR "Ìú¿ó" NOR);
        set("long", @LONG
[1£»37mÕâÀïÊÇÒ»¸ö¹âÍºÍºµÄĞ¡É½Çğ£¬ËÄÖÜÊ²Ã´»¨²İÊ÷Ä¾Ò²Ã»ÓĞ¡£×ĞÏ¸Ò»
¿´£¬·¢ÏÖÉ½ÇğÖÜÎ§ÓĞĞ©ºÚ÷î÷îµÄ´óÊ¯Í·£¬Õâ¾ÍÊÇ¹âÃ÷¶¥Ê¢²úµÄÎÚ½ğÌú
¿óÊ¯¡£Ã÷½Ì½ÌÖÚÓÃµÄ±øÆ÷¶¼ÊÇÓÃÕâÖÖ¿óÊ¯ÖıÔì¶ø³É£¬±ÈÖ®Ñ°³£¾«ÌúÖı
ÔìµÄ±øÆ÷¸üÎª¼á¹Ì£¬·æÀû¡£[2£»37£»0m
LONG );
        set("exits", ([ /* sizeof() == 1 */
          "east" : __DIR__"rjqmenlou1",
        ]));

        set("invalid_startroom", 1);
        set("wa_times",15);
        setup();

}

void init()
{
        add_action("do_save", "save");
        add_action("do_wa", "excavate");
        add_action("do_wa", "dig");
}

int do_save(string arg)
{
        write("ÕâÀï²¢·ÇÒ»°ãµØ·½,²»ÄÜÔÚÕâÀï¼ÍÂ¼¡£\n");
        return 1;
}

int do_wa(string arg)
{
        object qiao,me;

        me = this_player();

        if( me->is_busy() || query_temp("pending/job_busy", me) )
                return notify_fail("ÄãÕıÃ¦×ÅÄØ¡£\n");

        if( query("mingjiao/job", me) != "jin_caikuang")
                return notify_fail("ÕâÀï²»ÄÜËæ±ãÂÒÍÚ£¡\n");

        if( present("wujin kuangshi", me) )
                return notify_fail("ÄãÒÑ¾­ÓĞÒ»¿é¿óÊ¯£¬ÊµÔÚ±§²»¶¯µÚ¶ş¿éÁË¡£\n");

        if( !objectp(qiao = present("tie qiao", me)) )
                 return notify_fail("ÄãÃ»ÓĞ³ÃÊÖµÄ¹¤¾ß£¬ÎŞ·¨¿ª²ÉÌú¿ó\n");

        if( query("jing", me) < 50 || query("qi", me) < 30 )
                return notify_fail("ÄãÒÑ¾­¾«Æ£Á¦½ßÁË£¡\n");

        if( query("wa_times") > 0 )
        {
                message_vision("$N½«ÌúÇÂÄÃÔÚÊÖÉÏ£¬¿´×¼ÁËÒ»¿éºÚ÷î÷îµÄÎÚ½ğÌú¿óÊ¯£¬ÓÃÁ¦ÏòÏÂÍÚÈ¥¡£\n",me);
                set_temp("pending/job_busy", 1, me);
                call_out("start_wa", 10, me);
                me->start_busy( (: check_busy :) );
        }
        else
                tell_object(me,"¿óÊ¯ËÆºõ¶¼±»ÍÚ¹âÁË¡£\n");

        return 1;

}

int check_busy(object me)
{
        if (query_temp("pending/job_busy", me)) return 1;
        return 0;
}

int start_wa(object me)
{
        object kuangshi;

        if(query("jingli", me)>90 && random(3)==1)
        {
                message_vision("$N½«Ò»Ğ¡¿é"+HIB"ÎÚ½ğ¿óÊ¯"NOR+"ÍÚÁË³öÀ´·ÅÔÚÉíÉÏ¡£\n",me);
                addn("wa_times",-1);
                kuangshi=new(__DIR__"obj/kuangshi");
                if (! kuangshi->move(me))
                        kuangshi->move(environment(me));
                addn("jing",-20, me);
                addn("qi",-30, me);
        }
        else
        {
                tell_object(me,HIR"ÄãÍ»È»¾õµÃÆøÁ¦²»¼Ã£¬ÔõÑùÒ²ÎŞ·¨½«ÄÇ¿é¿óÊ¯ÍÚ³ö¡£\n"NOR);
                addn("jing",-20, me);
                addn("qi",-30, me);
        }

        delete_temp("pending/job_busy", me);
        return 1;

}

int valid_leave(object me, string dir)
{
        object ob;

        if (dir == "northeast" && query_temp("job_busy", me) )
               return notify_fail("ÄãÕıÃ¦×ÅÍÚ¿óÄØ£¡\n");

        return ::valid_leave(me, dir);
}