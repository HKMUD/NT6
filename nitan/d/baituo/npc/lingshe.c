// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// lingshe ��������

#include <ansi.h>
inherit SNAKE;

void create()
{
        set_name("����", ({ "ling she", "she", "snake" }) );
        set("race", "Ұ��");
        set("age", 4);
        set("long", "һ������������С�ߣ��������򣬼�Ϊ������\n");
        set("attitude", "peaceful");

        set("msg_fail", "$n��$N˻��һ����ͷ");
        set("msg_succ", "$n˻˻���죬��ͷ����$N���ֶ�������");
        set("msg_trained","$n������Ϣ���ε�$N�Ľ��²�����");
        set("auto_follow",0);
        set("wildness", 90);

        set("str", 30);
        set("cor", 30);
        set("dex", 35);

        set("combat_exp", 100000);

        set_temp("apply/attack", 55);
        set_temp("apply/damage", 56);
        set_temp("apply/armor", 52);

        setup();
}

/*
void init()
{
        object ob;
        ::init();
        add_action("convert","bian");
        if (interactive(ob = this_player()) &&
            query("family/family_name", ob) != "ŷ������" && 
                ! present("xiong huang", environment(ob))) {
                        remove_call_out("kill_ob");
                        call_out("kill_ob", 1, ob); 
        }
}

void unconcious()
{        
        write("�����µ�һ���ӵ��ˡ�\n");
        destruct(this_object());
}
void die()
{
        object ob;
        ob = new("/d/baituo/npc/obj/shedan");
        ob->move(environment(this_object()));
        destruct(this_object());
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        victim->apply_condition("bt_poison",10+query("snake_poison", me)+
                victim->query_condition("bt_poison"));
        if( query("bite_busy", me))victim->start_busy(2);
}
*/

int convert(string arg)
{
        object me = this_player();
        object ob;

        if (arg != "ling she") return 0;
        if( query("family/family_name", me) != "ŷ������" )
                return notify_fail("�㲻�ܻ���Ϊ�ȡ�\n");
        if (me->query_skill("training",1) < 70 + random(70)) {
                kill_ob(me);
                return 1;
        }
        message_vision("$N���ְ�ס���ߵ�ͷ�������ḧ���ߴ磬���������дʣ�Ƭ�̼佫�߻�Ϊһ�����ȡ�\n",
                me,);
                ob = new("/d/baituo/obj/lingshezhang");
        ob->move(environment(this_object()));
        set("poison_applied", me->query_skill("poison",1)/2, ob);
        destruct(this_object());
        return 1;    
}