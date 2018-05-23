inherit NPC;


void create()
{
    set_name("ËÎ»¶³¼", ({ "song huanchen","chen","song" }) );
    set("title","áÇá¼ÅÉ¶şÊ¦ĞÖ");
    set("gender", "ÄĞĞÔ" );
    set("class","taoist");
    set("age",23);
    create_family("áÇá¼ÅÉ", 2, "µÜ×Ó");
    set("social_exp",2000);
    set("combat_exp",10000);
	set_wugong("shizi-zhan", 50,50,1);
	set_wugong("luofeng", 70,70,1);
	set_xiuwei("dodge", 500);
	set_xiuwei("unarmed", 600);
        set("force",200);
        set("max_force",200);
        set("force_factor",10);
	set("chat_chance", 5);
        set("chat_msg", ({
(: random_move :)
 }));
        setup();
        carry_object(__DIR__"obj/cloth1")->wear();
}
