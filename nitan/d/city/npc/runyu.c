// runyu.c

inherit NPC;
inherit F_DEALER;
#include <ansi.h>;
int do_send(string arg);
void create()
{
        set_name( WHT"ÈóÓñ"NOR , ({ "run yu", "yu" }) );
        set("title", MAG"Âô»¨¹ÃÄï"NOR );
        set("gender", "Å®ÐÔ" );
        set("age",16);
        set("per",23);
        set("combat_exp", 1500);
        set("attitude", "friendly");

        set("vendor_goods", ({
                __DIR__"obj/red_rose",
                __DIR__"obj/yellow_rose",
                __DIR__"obj/yujinxiang",
                __DIR__"obj/kangnaixin",
                "/d/luoyang/npc/obj/chahua",
                "/d/luoyang/npc/obj/lanhua",
                "/d/luoyang/npc/obj/mudan",
                "/d/luoyang/npc/obj/chahua",
                "/d/luoyang/npc/obj/chahua",
        }));

        setup();
        carry_object("/clone/cloth/female-cloth")->wear();
}

void init()
{
        object ob;
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment( this_object() ) )
        return;

        if( query("gender", ob) == "Å®ÐÔ" )
        {
                if( query("age", ob)<30 )
                {
                        message_vision("Âô»¨¹ÃÄï³å$PÌðÌðÒ»Ð¦£º¹ÃÄï²»Âò¶äÓô½ðÏãÂð£¿\n",ob);
                        return;
                }
        }
        else
        {
                if( query("couple", ob) )
                {
                        message_vision("Âô»¨¹ÃÄï³å×Å$PÐ¦×Å£º²»¸øÄúµÄÆÞ×ÓÂòÊø»¨Âð£¿\n",ob);
                        return;
                }
                else
                {
                        message_vision("Âô»¨¹ÃÄï³å×Å$PÐ¦×Å£º²»¸øÐÄÉÏÈËÂòÊøºìÃµ¹åÂð£¿\n",ob);
                        return;
                }
        }
        return;
}
