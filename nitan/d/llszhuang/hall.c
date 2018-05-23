#include <ansi.h>
inherit ROOM;
string *s1 = ({ "ÎÊ","²Ô","Ã£","´ó","µØ","Ë­","Ö÷","³Á","¸¡","Êı","·ç","Á÷",
                "ÈË","Îï","»¹","¿´","½ñ","³¯","½­","É½","Èç","´Ë","¶à","½¿"});
void create()
{
        set("short", YEL"É½×¯ÕıÌü"NOR);
        set("long",
"ÄãÈËÉĞÎ´µ½£¬Ò»Ë¿µ­µ­µÄÇåÏãÒÑ×ÔÇßÈëÄãµÄĞÄÆ¢¡£×ß½ø´óÌü£¬Ó­ÃæÊÇ\n"
"Ò»·ù¼«´óµÄÆÃÄ«É½Ë®£¬Ä«¼£×İºáÁÜÀì£¬±Ê·æá¿áÉÓĞÖÂ¡£»­ÃæÉÏ»æµÄÊÇÉ½ºÓ\n"
"Éçğ¢Í¼£¬¶«ÆğÃ£Ã£´óº££¬Î÷ÖÁ°¨°¨Ñ©É½£¬ÆøÊÆ²»·²£¬ÁîÈË¶ÙÉúÑöÖ¹Ö®¸Ğ£¬\n"
"ÅÔ±ßÊÇÒ»·ù¶ÔÁª£º¡¸ÎÊ²ÔÃ£´óµØË­Ö÷³Á¸¡[2;37;0mÊı·çÁ÷ÈËÎï»¹¿´½ñ³¯\n"
"¡¹[2;37;0m[2;37;0mºáÅú£º½­É½Èç´Ë¶à½¿[2;37;0mÕû×ù´óÌüËäÈ»¸»Àö\n"
"ÌÃ»Ê£¬ÆøÊÆ»Öºê£¬¿ÉÊÇÄã×Ü¸Ğ¾õÓĞµã²»Ì«Ğ­µ÷µÄµØ·½¡£ËÆºõºÍÄãÒ»Â·Ëù¼û\n"
"ËùÎÅ²»Ì«ÏàÏó¡£ÄãÊÇ²»ÊÇÓ¦¸ÃºÃºÃ(think)ÄØ£¬È»ºóÔÙ½øÈ¥£¿\n"
);

        set("exits", ([ /* sizeof() == 2 */
          "south" : __DIR__"dynamic/jiuqu16",
          "north" : __DIR__"neishi",
        ]));
        set("no_magic", "1");

        setup();
}

int init()
{
        add_action("do_think","think");
        add_action("do_uncover","uncover");
}

int do_think(string arg)
{
        object me;

        me = this_player();
        if( random(query("int", me))<20 )
        {
                write("ÄãÏë°¡Ïë£¬½á¹ûÏëÆÆÁËÄÔ´ü£¬°×°×µÄÄÔ½¬Á÷ÁËÒ»µØ¡£\n");
                me->receive_damage("jing",100);
        }
        else
        {
                write("ÄãÃÆÍ·¿àË¼£¬Í»È»·¢ÏÖµØÉÏÓĞÒ»¿é·½×©(brick)ËÆºõ±ßÔµÌØ±ğµÄ¹â
»¬¡£ºÃÏó¿ÉÒÔ(uncover)\n");
                set_temp("marks/xanadu_hall1", 1, me);
        }
        return 1;
}

int do_uncover(string arg)
{
          object me;
        int i,j,k,l;

        me = this_player();
        if( !arg || arg != "brick" || !query_temp("marks/xanadu_hall1", me))// || wizardp(me) )
                return 0;
        message_vision(GRN"$NĞ¡ĞÄÒíÒíµØ°ÑµØ°å×©½Ò¿ª£¬Ö»Ìı¡°¶£¡±µÄÒ»ÉùÇáÏì...\n"NOR,me);
       if( random(10) > 5 ) {
        message_vision(RED"Ò»ÅîÅ£Ã«Ï¸ÕëÏò$NÉäÀ´£¬ÕıºÃÃüÖĞ£¬Ö»ÌıÄãÒ»Éù²Òº¿£¬Ï¸ÕëÒÑÔÚÄãĞØÇ°¶Ô´©¶ø¹ı¡£\n"NOR,me);
                me->receive_wound("qi",random(query("kar", me))*50);
                COMBAT_D->report_status(me,me,1);
         }
        else
         message_vision(RED"Ò»ÅîÅ£Ã«Ï¸ÕëÏò$NÉäÀ´£¬$NÇáËÉµÄ¶ãÁË¿ªÈ¥¡£\n"NOR,me);
         if( query("qi", me)>100 )
                {
                        delete_temp("marks/xanadu_hall1", me);
                        i=random(9);
                        j=random(9);
                        k=random(6);
                        l=random(6);
                        set_temp("marks/xanadu_hall2", l*1000+k*100+j*10+i, me);
 write("Äã¾ª»ê¸¦¶¨£¬·¢ÏÖµØ°å·­ÆğÀ´µÄ±³Ãæ¿Ì×ÅÒ»ĞĞĞ¡×Ö£º"+s1[i]+s1[9+j]+s1[18+k]+s1[18+l]+"\n");


                }
        return 1;
}
