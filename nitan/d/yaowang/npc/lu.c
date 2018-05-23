#include <ansi.h>
inherit NPC;

void create()
{
        set_name(YEL"÷��¹"NOR, ({ "meihua lu", "lu" }) );
        set("race", "Ұ��");
        set("age", 2);
        set("long", "һֻ�ɰ���÷��¹������Ѫ�Ǵ�֮�\n");
        set("attitude", "peaceful");
 
        set("str", 30);
        set("cor", 26);

        set("limbs", ({ "ͷ��", "����", "צ��", "β��" }) );
        set("verbs", ({ "bite" }) );
 
        set("combat_exp", 3000);

        set_temp("apply/attack", 50);
        set_temp("apply/damage", 10);
        set_temp("apply/defence",30);
        set_temp("apply/armor",10);

        set("yaowang_zhuo",1);
        setup();
}

void die()
{
        object ob1, ob2, ob3;
        message_vision(HIR"$N����һ�ţ�$N���ˡ�\n"NOR, this_object());
        
        if(random(10)>8)
        {
        
        ob1 = new(__DIR__"obj/luxue");
        ob2 = new(__DIR__"obj/lurong");
        ob3 = new(__DIR__"obj/lurong");
        ob1->move(environment(this_object()));
        ob2->move(environment(this_object()));
        ob3->move(environment(this_object()));
        } else 
        {
        ob1 = new(__DIR__"obj/luxue");
        ob1->move(environment(this_object()));
        }
        destruct(this_object());
}