#include <ansi.h>

inherit SMITH;

void create()
{
        set_name("Ìú½³", ({ "tiejiang", "smith" }));
        set("title", "¼×ëÐµêÀÏ°å");
        set("shen_type", 1);
        set("gender", "ÄÐÐÔ" );
        set("age", 33);
        set("long", "Ìú½³ÕýÓÃÌúÇ¯¼Ð×¡Ò»¿éºìÈÈµÄÌú¿é·Å½øÂ¯ÖÐ¡£\n");

        set("combat_exp", 400);
        set("attitude", "friendly");
        set("vendor_goods",({
                   __DIR__"obj/armor",
                   __DIR__"obj/beixin",
                   "/d/city/npc/obj/jinsijia",
        }));

        setup();

        carry_object("/clone/misc/cloth")->wear();
}