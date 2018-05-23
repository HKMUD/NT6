inherit NPC;


void create()
{
	set_name("ÏÄĞÇÄ»",({"xia xingmu","xia","xingmu"}) );
    set("title","áÇá¼ÅÉÈıÊ¦ĞÖ");
    set("gender", "ÄĞĞÔ" );
    set("class","taoist");
    set("age",22);
    create_family("áÇá¼ÅÉ", 2, "µÜ×Ó");
    set_wugong("unarmed",100,100);
    set_wugong("shizi-zhan",80,80,1);
    set_wugong("dahong-quan",50,45,1);
	set_xiuwei_by_type("unarmed",560);
    set_wugong("jiben-qinggong",100,95);
    set_wugong("nieyun-bufa",80,76,1);
	set_xiuwei_by_type("dodge",450);
    set_wugong("sword",100,100);
    set_wugong("fengyun-jian",40,34,1);
    set_xiuwei_by_type("sword",300);
    set("social_exp",200);
    set("combat_exp",10000);
    set("positive_score",1000);
    set("class_score/áÇá¼ÅÉ",450);
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
