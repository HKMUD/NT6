// huanu.c

inherit NPC;

void create()
{
    set_name("����Ů",({ "yanghua nv", "girl" }) );
        set("gender", "Ů��" );
        set("age", 17);
        set("long", "һλ������Ů����ÿ������չ�����Ҳ������Ĳ軨��\n");
         set_temp("apply/defense", 5);
        set("combat_exp", 7000);
//        set("shen", 100);
        set("shen_type", 1);
        set("per", 28);
        set("str", 14);
        set("dex", 15);
        set("con", 16);
        set("int", 15);
        set("attitude", "friendly");
        setup();
        carry_object("/d/dali/npc/obj/wchangqun")->wear();
}