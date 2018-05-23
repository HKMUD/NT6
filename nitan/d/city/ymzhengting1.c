#include <ansi.h>
inherit ROOM;
//void kf_same(object who,object me);

void create()
{
        set("short", "ÑÃÃÅÕýÌü");
        set("long", @LONG
    ÌÃÉÏ¶«Î÷ÓÐÁ½¸ùéº×¡£¬¹Ò×ÅÒ»·ù¶ÔÁª£¬µ«ÊÇÄãÎÞÐÄÏ¸¿´¡£Õý
Ç½ÉÏÐü¹ÒÒ»¸öºáØÒ£¬ÉÏÊéËÄ¸ö½ð¹âÉÁÉÁµÄ´ó×Ö¡£Öª¸®Õý×øÔÚÎÄ°¸ºóÅú
ÔÄÎÄÊé£¬Ê¦Ò¯ËæÊÌÔÚºó¡£´óÌÃÕýÖÐ¸ßÐüÒ»ØÒ£º[1£»31m               Ã÷   
 ¾µ    ¸ß    Ðü[2£»37£»0m
LONG );
        set("valid_startroom",1);
        set("no_steal", "1");
        set("no_magic", "1");
        set("no_fight", "1");
        set("exits", ([
           "east"  : "/d/city/dongting", 
                      "west"  : "/d/city/xiting", 
                      "north" : "/d/city/neizhai", 
                      "south" : "/d/city/yamen", 

        ]));
  

        set("objects", ([
                  "/d/city/npc/cheng" : 1, 
                  "/d/city/npc/shiye" : 1, 
        ]));
        setup();
}

void init ()
{
        add_action("do_work","work");
        add_action("do_finish","finish");
}

int do_work (string arg)
{
        object ob,ob1;
        int kf_npc,kf_whatnpc,worked_num;
        string kf_name,kf_name1,kf_where,titles;
        object me = this_player();
        if( query("kf_jiangli", me) )
                return notify_fail("³ÌÒ©·¢ËµµÀ£ºÉñ²¶´óÈË»¹Ã»½ø¾©ÃæÊ¥°¡£¿\n");

        if( !query("kaifengfu", me) )
                return notify_fail("Á½ÅÔÑÃÒÛ´óÉùºÈµÀ£º´óµ¨µóÃñ£¬²»µÃÅØÏø¹«ÌÃ£¡\n");
        if (!objectp(present("cheng yaofa", environment(me))))
                return notify_fail("·çÔÆÑÃÒÛÐ¦µÀ£º³ÌÒ©·¢ÒÑ¾­ÍËÌÃÁË£¬ÒªÏëÈÎÎñÃ÷ÈÕÇëÔçÁËÄú¡£\n");

        if( present("lingpai",me) || query("kf_working", me) )
                return notify_fail("³ÌÒ©·¢Á³É«Ò»³ÁµÀ£º±¾¹ÙÇ°ÈÕ½»ÓëÄãµÄ²îÊÂËÙÈ¥°ìÀí£¬²»µÃÄíÇáÅÂÖØ£¡\n");
        kf_npc = 1 + random(209);
        kf_whatnpc =1+random(8);
        set("kf_whatnpc", kf_whatnpc, me);
        ob = new("/d/city/obj/lingpai");        //50
        if(kf_whatnpc==1){ob1 = new("/d/city/npc/tufei1");}
        if(kf_whatnpc==2){ob1 = new("/d/city/npc/tufei2");}
        if(kf_whatnpc==3){ob1 = new("/d/city/npc/tufei3");}
        if(kf_whatnpc==4){ob1 = new("/d/city/npc/tufei4");}
        if(kf_whatnpc==5){ob1 = new("/d/city/npc/tufei5");}
        if(kf_whatnpc==6){ob1 = new("/d/city/npc/tufei6");}
        if(kf_whatnpc==7){ob1 = new("/d/city/npc/tufei7");}
        if(kf_whatnpc==8){ob1 = new("/d/city/npc/tufei8");}
        ob ->move(me);
        set_temp("kf_npc", kf_npc, me);
        if(kf_npc<210) kf_where = "Îäµ±¸½½ü";
        if(kf_npc<191) kf_where = "»ÆÉ½¸½½ü";
        if(kf_npc<166) kf_where = "åÐÒ£ÅÉ¸½½ü";
        if(kf_npc<152) kf_where = "ÐÇËÞÅÉ¸½½ü";
        if(kf_npc<141) kf_where = "Ì©É½¸½½ü";
        if(kf_npc<125) kf_where = "Ñ©É½¸½½ü";
        if(kf_npc<107) kf_where = "ÑïÖÝ¸½½ü";
        if(kf_npc<84) kf_where = "±±¾©³ÇÖÐ";
        if(kf_whatnpc==1){ kf_name = "ÃÉÃæ´óµÁ"; kf_name1 = "À¹Â·ÇÀ½Ù,É±ÈËÈçÂé";}
        if(kf_whatnpc==2){ kf_name = "ÎÞÓ°ÉñÍµ"; kf_name1 = "ËÄ´¦µÁÇÔ²ÆÎï";}
        if(kf_whatnpc==3){ kf_name = "¶ñÈËÅá·çÏô"; kf_name1 = "¾­³£½ÙÂÓÃñÅ®£¬ÎÞ¶ñ²»×ö";}
        if(kf_whatnpc==4){ kf_name = "Ä§½ÌÏ¸×÷"; kf_name1 = "ËÄ´¦»î¶¯";}
        if(kf_whatnpc==5){ kf_name = "Ìì×Ú¼éÏ¸"; kf_name1 = "ËÄ´¦ÔìÒ¥ÆÆ»µ";}
        if(kf_whatnpc==6){ kf_name = "ÉñÃØÈË"; kf_name1 = "´ÌÉ±³¯Í¢Ãü¹Ù";}
        if(kf_whatnpc==7){ kf_name = "ÀîÔª¿ü"; kf_name1 = "´ó¼Ò½ÙÉá";}
        if(kf_whatnpc==8){ kf_name = "¹ÅÒã"; kf_name1 = "ÉËÈËÎÞÊý";}

        set_temp("kf_whatnpc", kf_whatnpc, me);
        set_temp("kf_name", kf_name, me);
        set_temp("kf_where", kf_where, me);
        message_vision("³ÌÒ©·¢Ò»ÅÄ¾ªÌÃÄ¾Å­µÀ£º¾Ý²é½ñÓÐ"+kf_name+"ÔÚ"+kf_where+kf_name1+"£¬"+query("name", me)+"ËÙÈ¥ÆÆ°¸£¬²»µÃÓÐÎó¡£\n",me);
        set("kf_working", 1, me);
        return 1;
}
int do_finish (string arg)
{
        object ob;
        int kf_npc,kf_whatnpc,kf_exp,kf_qn;
        string kf_name,kf_name1,kf_where,titles;
        object me = this_player();
        ob= present("ling pai",me);
        kf_name=query_temp("kf_name", me);
        kf_where=query_temp("kf_where", me);
        
        if( !query("kaifengfu", me) )
                return notify_fail("Á½ÅÔµÄ·çÔÆÑÃÒÛ´óÉùºÈµÀ£º´óµ¨µóÃñ£¬²»µÃÅØÏø¹«ÌÃ£¡\n");
        if (!objectp(present("cheng yaofa", environment(me))))
                return notify_fail("·çÔÆÑÃÒÛÐ¦µÀ£º³Ì´óÈËÒÑ¾­ÍËÌÃÁË£¬ÒªÏë½»ÁîÃ÷ÈÕÇëÔçÁËÄú¡£\n");
        if( !query("kf_working", me) )
                return notify_fail("³ÌÒ©·¢Á³É«Ò»³ÁµÀ£º±¾¹ÙÊ²Ã´Ê±ºòÅÉ¹ýÄã²îÊÂ°¡£¿\n");
        if( !query_temp("kf_finish", me) )
                return notify_fail("³ÌÒ©·¢Á³É«Ò»³ÁµÀ£º±¾¸®½»ÄãµÄ²îÊ¹ÖÁ½ñ»¹Î´°ìÍ×£¬Äã»¹ÓÐÃæÄ¿À´¼ûÎÒ£¿\n");
        if (present("ling pai",me)){
                tell_object(me, "Äã¹§¹§¾´¾´µÄ½ÉÉÏÁîÅÆ¡£\n" NOR );
        destruct(present("ling pai",me));
        }        
        message_vision(WHT"³ÌÒ©·¢Î¢Î¢Ò»Ð¦µÀ£º"+query("name", me)+WHT"ÔÚ"+kf_where+WHT"ÆÆ»ñ"+kf_name+WHT"Ò»°¸£¬ÀÍ¿à¹¦¸ß£¬¸Ï¿ìÏÂÈ¥ÐÝÏ¢°É£¡\n"NOR,me);
        kf_exp = 2000+random(2000);
        kf_qn = 500+random(500);
        addn("combat_exp", kf_exp, me);
        addn("kf_worked", 1, me);
        addn("potential", kf_qn, me);
        addn("kf_worked", 1, me);
        set("kf_working", 0, me);
        delete_temp("kf_finish", me);
        tell_object(me, "Äã»ñµÃÁË" + chinese_number(kf_exp)+ "µã¾­Ñé¡£\n" NOR );
        tell_object(me, "Äã»ñµÃÁË" + chinese_number(kf_qn)+ "µãÇ±ÄÜ¡£\n" NOR );
        if( query("kf_worked", me) == 4800){
                set("kainame", 10, me);
                addn("shen", 3000, me);
                message_vision(HIC "$NµÄÕýÆøÌá¸ßÁË£¡\n" NOR,me);
                tell_object(me,"ÄãÏÖÔÚµÄÕýÆøÊÇ"+chinese_number((query("shen", me)))+"¡£\n"NOR);
                message_vision(WHT"³ÌÒ©·¢Î¢Ð¦×ÅËµµÀ£º"+query("name", me)+"Á¬ÆÆ´ó°¸£¬ÌìÏÂÎÅÃû£¬±¾¸®ÒÑ¾­×àÃ÷»ÊÉÏ¡£\n×òÈÕ³¯Ö¼ÒÑÏÂ£¬½±Äã»Æ½ðÎåÇ§Á½¡£Äã¿ÉÒÔµ½Ç®×¯ÁìÈ¡¡£"NOR,me);
                 addn("balance", 10000000, me);
               set("kf_jiangli", 1, me);

      }
        if( query("kf_worked", me) == 3200){
                addn("shen", 3000, me);
                set("kainame", 9, me);
                message_vision(HIC "$NµÄÕýÆøÌá¸ßÁË£¡\n" NOR,me);
                tell_object(me,"ÄãÏÖÔÚµÄÕýÆøÊÇ"+chinese_number((query("shen", me)))+"¡£\n"NOR);
                message_vision(WHT"³ÌÒ©·¢Î¢Ð¦×ÅËµµÀ£º"+query("name", me)+"Á¬ÆÆ´ó°¸£¬ÌìÏÂÎÅÃû,¼ÌÐø¼ÓÓÍ£¡£¡"NOR,me);
      }
        if( query("kf_worked", me) == 1600){
                set("kainame", 8, me);
                addn("shen", 1500, me);
                message_vision(HIC "$NµÄÕýÆøÌá¸ßÁË£¡\n" NOR,me);
                tell_object(me,"ÄãÏÖÔÚµÄÕýÆøÊÇ"+chinese_number((query("shen", me)))+"¡£\n"NOR);
      }
        if( query("kf_worked", me) == 800){
                set("kainame", 7, me);
                addn("shen", 1000, me);
                message_vision(HIC "$NµÄÕýÆøÌá¸ßÁË£¡\n" NOR,me);
                tell_object(me,"ÄãÏÖÔÚµÄÕýÆøÊÇ"+chinese_number((query("shen", me)))+"¡£\n"NOR);
        }
        if( query("kf_worked", me) == 400){
                set("kainame", 6, me);
                addn("shen", 800, me);
                message_vision(HIC "$NµÄÕýÆøÌá¸ßÁË£¡\n" NOR,me);
                tell_object(me,"ÄãÏÖÔÚµÄÕýÆøÊÇ"+chinese_number((query("shen", me)))+"¡£\n"NOR);
        }
        if( query("kf_worked", me) == 200){
                set("kainame", 5, me);
                addn("shen", 400, me);
                message_vision(HIC "$NµÄÕýÆøÌá¸ßÁË£¡\n" NOR,me);
                tell_object(me,"ÄãÏÖÔÚµÄÕýÆøÊÇ"+chinese_number((query("shen", me)))+"¡£\n"NOR);
        }
        if( query("kf_worked", me) == 100){
                set("kainame", 4, me);
                addn("shen", 200, me);
                message_vision(HIC "$NµÄÕýÆøÌá¸ßÁË£¡\n" NOR,me);
                tell_object(me,"ÄãÏÖÔÚµÄÕýÆøÊÇ"+chinese_number((query("shen", me)))+"¡£\n"NOR);
        }
        if( query("kf_worked", me) == 50){
                set("kainame", 3, me);
                addn("shen", 100, me);
                message_vision(HIC "$NµÄÕýÆøÌá¸ßÁË£¡\n" NOR,me);
                tell_object(me,"ÄãÏÖÔÚµÄÕýÆøÊÇ"+chinese_number((query("shen", me)))+"¡£\n"NOR);
        }
        if( query("kf_worked", me) == 20){
                set("kainame", 2, me);
        }
        me->save();
        return 1;
}
int valid_leave (object who, string dir)
{
        if(who->query_condition("kf_stop")<1){
                return ::valid_leave(who, dir);
        }
        else{
                message_vision ("$NÅÀÆðÀ´¾ÍÏëÍùÍâÅÜ¡£\n",who);
                return notify_fail(WHT"ÑÃÒÛËÀËÀ°ÑÄã°´ÔÚµØÉÏºÈµÀ£ºÀÏÊµµã£¡\n"NOR);
                return 1;
}
}
