// smith.c

inherit SMITH;

void create()
{
        set_name("Ìú½³", ({ "tie jiang", "smith" }));
        set("title", "Ìú½³ÆÌÀÏ°å");
        set("shen_type", 1);

        set("gender", "ÄĞĞÔ" );
        set("age", 33);
        set("long", "Ìú½³ÕıÓÃÌúÇ¯¼Ğ×¡Ò»¿éºìÈÈµÄÌú¿é·Å½øÂ¯ÖĞ¡£\n");

        set("combat_exp", 400);
        set("attitude", "friendly");
        set("vendor_goods",({
                "/d/city/obj/changjian",
                "/d/city/obj/hammer",
                "/d/beijing/obj/tudao",
                "/d/city/obj/dagger",
                "/d/xingxiu/obj/tiegun",
                "/d/city/obj/gangdao",
        }));

        setup();
        carry_object("/clone/misc/cloth")->wear();
}
