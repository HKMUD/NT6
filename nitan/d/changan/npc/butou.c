//butou.c

inherit NPC;

void create()
{
        set_name("��ͷ", ({ "bu tou"}));
        set("age", 40);
        set("gender", "����");
        set("long","����Ѳ��ͷ��\n");
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 20);
        set("combat_exp", 100000);
        set("max_qi", 600);
        set("max_jing", 600);
        set("max_neili", 500);
        set("neili", 500);
        set("jiali", 30);
        set_skill("unarmed", 40);
        set_skill("dodge", 40);
        set_skill("parry", 40);
        set_skill("blade", 40);
        set_skill("force", 40);

        setup();
        carry_object("/d/changan/npc/obj/gangdao")->wield();
        carry_object("/d/changan/npc/obj/cloth")->wear();
        carry_object("/d/changan/npc/obj/laofang-key");
}