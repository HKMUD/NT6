// Code of ShenZhou
// xuesang.c  
// By Haowen 1/14/98

#include <ansi.h>

inherit ITEM;


void create()
{
        set_name("Ñ©É£",({"xue sang","sang"}));
        set_weight(900000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "ÕâÊÇÒ»¿ÃÌìÉ½ÌØÓĞµÄÉú³¤ÔÚÑ©·åµÄÑ©É£Ê÷¡£
´«ËµÓĞÒ»ÖÖÑ©²Ï×îÏ²»¶Éú³¤ÔÚÕâÑ©É£Ö®ÉÏ£¬¾­³£ÓĞÈËÀ´Ñ°ÕÒ(xunzhao)¡ \n");
                set("unit", "¿Ã");
                set("value", 8);
                set("no_get", 1);
                set("leaves",20);
       }
       
        setup();
}

void init()
{
        add_action("do_search", "search");
        add_action("do_search", "xunzhao");
        add_action("do_feed", "fed");
        add_action("do_look", "look");
        add_action("do_look", "l");
}

int do_search()
{
object obj=this_object(),me=this_player();

if( query_temp("find_can", me) )
        return notify_fail("Ñ©²ÏÒÑ¾­ÔÚÑ©É£ÉÏÁË£¬Äã»¹ÕÒÊ²Ã´Ñ½£¿\n");

if( random(query("kar", me))>15 )
        {
        tell_object(me,HIG"Äã×ĞÏ¸µÄ·­¶¯Ñ©É£Ò¶£¬µ½´¦Ñ°ÕÒÆğÀ´¡£\n" NOR);
        if(random(10)>5)
                {
                tell_object(me,HIR"ÄãºöÈ»ÑÛÇ°Ò»ÁÁ£¬Ò»Ìõ¾§Ó¨Ñ©°×µÄÑ©²Ï(can)ÕıÎÔÔÚÒ»Æ¬Ñ©É£Ò¶ÉÏ£¡\n"NOR);
                set_temp("find_can", 1, me);
                }
        addn("neili", -10, me);
        return 1;
        }
else    {
        addn("neili", -10, me);
        return notify_fail("ÄãÕÒÁË°ëÌìÊ²Ã´Ò²Ã»ÕÒµ½£¡\n");
        }
}

int do_feed(string arg)
{
object ob,obj=this_object(),me=this_player();
string what;

//message_vision(arg);
if (!arg || sscanf(arg,"%s",what)!=1)
        return notify_fail("ÄãÒªÎ¹Ê²Ã´£¿\n");

if (what!="can")
        return notify_fail("ÕâÀïµÄÑ©É£Ò¶Ö»ÓĞÌìÉ½Ñ©²Ï°®³Ô£¡\n");

if( !query_temp("find_can", me) )
        return notify_fail("ÕâÑ©É£ÉÏÊ²Ã´Ò²Ã»ÓĞ£¬ÄãÒªÎ¹Ê²Ã´£¿\n");

if( query_temp("get_si", me) )
        return notify_fail("Ñ©²Ï¸ÕÍÂ¹ıË¿£¬¿ÖÅÂÏÖÔÚ²»»áÔÙÍÂÁË£¡\n");

if( query("leaves", obj)>1 )
        {
        tell_object(me,HIY "ÄãÕªÁËÒ»Æ¬Ñ©É£Ò¶Î¹¸øÑ©²Ï³Ô¡£Ñ©²Ï×ĞÏ¸µÄ³ÔÁËÆğÀ´¡£\n" NOR);
        set("leaves",query("leaves",  obj)-1, obj);
                if (random(10)>5)
                        {
                        tell_object(me,HIY "Ñ©²Ï³ÔÍêÁËÉ£Ò¶£¬Í·Ò»°º£¬ÍÂ³öÒ»¸ù²ÏË¿£¬Äã¸Ï½ôÓÃÊÖ½Ó×¡¡£\n" NOR);
                        set_temp("get_si", 1, me);
                        ob=new("/d/xingxiu/obj/xuecan-si");
                        ob->move(me);
                        }
        return 1;}
else 
        {
        call_out("grow",200,obj);
        return notify_fail("Ñ©É£ÉÏµÄÒ¶×Ó¶¼ÕªÍêÁË£¬µÈÂıÂı³¤³öÀ´ÔÙÀ´Î¹°É£¡\n");
        }
}

int do_look(string arg)
{
        object ob,me=this_player();
        string what;
        ob=this_object();
 
        if( !arg || arg == "" || sscanf(arg,"%s",what)!=1) return 0;

        
        if(what=="sang" || what=="xue sang")
                {        
                if( query_temp("find_can", me) )
                        tell_object(me,query("long", ob)+"ÏÖÔÚÉÏÃæÓĞÒ»Ö»Ñ©²Ï(can)£¡ºÃÏóÕıÔÚµÈÄãÎ¹(fed)Ëü¡£\n");
                else tell_object(me,query("long", ob));
                return 1;
                }

return 0;

}

int grow(object ob)
{
        message_vision(HIG "Ñ©É£ÉÏµÄÉ£Ò¶ÓÖ³¤³öÀ´ÁË£¡\n");
        set("leaves", 20, ob);
}