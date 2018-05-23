#include <ansi.h>

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("÷Ï“˚", ({ "zhu yin", "zhu", "yin" }));
        set("gender", "ƒ––‘");
        set("title", "Œ‰∆˜µÍ¿œ∞Â");
        set("age", 45);
        set_skill("dodge", 80);
        set_skill("force", 80);
        set_skill("parry", 80);
        set_skill("claw", 80);
        set_skill("hand", 80);
        set_skill("strike", 80);
        set_skill("finger", 80);
        set_skill("cuff", 80);
        set_skill("blade", 80);
        set_skill("club", 80);
        set_skill("staff", 80);
        set_skill("sword", 80);
        set_skill("throwing", 80);
        set_temp("apply/attack", 80);
        set_temp("apply/defense", 80);
        set_temp("apply/damage", 20);

        set("combat_exp", 400000);
        set("shen_type", 1);
        setup();
        set("vendor_goods",({
                "/clone/weapon/changjian",
                "/clone/weapon/hammer",
                "/clone/weapon/tudao",
                "/clone/weapon/dagger",
                "/clone/weapon/tiegun",
                "/clone/weapon/gangdao",
                "/clone/weapon/arrow",
                "/clone/weapon/wolfarrow",
                "/clone/weapon/bow",
                "/clone/weapon/longbow",
        }));
        carry_object("/d/luoyang/npc/obj/sword1");
        carry_object("/d/luoyang/npc/obj/blade1");
}

void init()
{
        add_action("do_buy", "buy");
        add_action("do_list", "list");
}
