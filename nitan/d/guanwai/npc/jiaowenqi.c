// /jiaowenqi.c

#include <ansi.h>
inherit NPC;

void create()
{
        set_name("������", ({ "jiao wenqi", "jiao" }));
        set("long",@LONG
���ǹ�����ħ�е���ħ�����ڡ�����һ�������ã����������ټ������ű�����
LONG );
        set("nickname", HIC "������ħ" NOR);
        set("gender", "����");
        set("age", 36);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 50);
        set("int", 20);
        set("con", 30);
        set("dex", 20);
        set("max_qi", 1200);
        set("max_jing", 500);
        set("neili", 1200);
        set("max_neili", 1200);
        set("jiali", 100);
        set("combat_exp", 170000);
        set("score", 20000);

        set_skill("force", 80);
        set_skill("xiaowuxiang", 50);
        set_skill("dodge", 50);
        set_skill("shenkong-xing", 60);
        set_skill("unarmed", 90);
        set_skill("yujiamu-quan", 40);
        set_skill("parry", 60);
        set_skill("hammer", 100);
        set_skill("riyue-lun", 100);

        map_skill("force", "xiaowuxiang");
        map_skill("dodge", "shenkong-xing");
        map_skill("unarmed", "yujiamu-quan");
        map_skill("parry", "riyue-lun");
        map_skill("hammer", "riyue-lun");

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object(__DIR__"obj/tiepipa")->wield();
        add_money("silver",40);
}