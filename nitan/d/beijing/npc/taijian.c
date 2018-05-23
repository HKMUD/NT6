inherit NPC;

void create()
{
        set_name("Ì«¼à", ({ "tai jian", "tai", "jian" }) );
        set("gender", "ÎŞĞÔ" );
        set("age", 32);

        set("combat_exp", 5000);
        set("shen_type", 0);

        set_skill("unarmed", 30);
        set_skill("blade", 40);
        set_skill("parry", 30);
        set_skill("dodge", 30);

        set_temp("apply/attack", 15);
        set_temp("apply/defense", 15);
        set_temp("apply/damage", 20);
        set("attitude", "peaceful");

        setup();
        carry_object("/d/beijing/npc/obj/cloth")->wear();
}
