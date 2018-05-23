// This program is a part of NT MudLIB

#include <ansi.h>

inherit BOSS;

void check_weapon();
void check_friend();

void create()
{
        set_name(HIM "��һ��" NOR, ({ "hu yidao"}) );
        set("title", HIR "��������" NOR);
        set("long", HIC "����һ���⺷����ı����󺺣�˫�۾�������\n"
                        "��˵���ĵ���������˫��\n" NOR);

        set("gender", "����");
        set("age", 39);

        set("str", 500);
        set("int", 500);
        set("con", 500);
        set("dex", 500);

        set("shen", 8000000);

        set_temp("apply/attack", 1000000);
        set_temp("apply/unarmed_damage", 100000);
        set_temp("apply/damage", 100000);
        set_temp("apply/armor", 60000);
        set_temp("apply/qy", 50);  // ����
        set_temp("apply/fy", 50);  // ��Ե

        set("reborn/times", 1);

        set("max_qi", 2100000000);
        set("eff_qi", 2100000000);
        set("qi", 2100000000);

        set("max_jing", 1000000000);
        set("jing", 1000000000);
        set("eff_jing", 1000000000);
        set("max_jingli", 1000000000);
        set("jingli", 1000000000);

        set("neili", 200000000);
        set("max_neili", 1000000);
        set("jiali", 50000);
        set("combat_exp", 2100000000);

        set_skill("unarmed", 3500);
        set_skill("finger", 3500);
        set_skill("claw", 3500);
        set_skill("strike", 3500);
        set_skill("hand", 3500);
        set_skill("cuff", 3500);
        set_skill("parry", 3500);
        set_skill("dodge", 3500);
        set_skill("force", 3500);
        set_skill("sword", 3500);
        set_skill("blade", 3500);
        set_skill("zuoyou-hubo", 2500);

        set_skill("daojian-guizhen", 4000);
        set_skill("jiuyang-shengong", 4000);
        set_skill("yinyang-shiertian", 4500);
        set_skill("qiankun-danuoyi", 4000);
        set_skill("martial-cognize", 5000);
        set_skill("qiankun-danuoyi", 4000);
        set_skill("lingbo-weibu", 4000);
        set_skill("literate", 4000);
        set_skill("huajia-su", 800);

        set_skill("jingluo-xue", 4000);

        set("no_nuoyi", 1); // ����Ų��Ӱ��

        map_skill("parry", "qiankun-danuoyi");
        map_skill("force", "yinyang-shiertian");
        map_skill("dodge", "lingbo-weibu");
        map_skill("unarmed", "yinyang-shiertian");
        map_skill("finger", "yinyang-shiertian");
        map_skill("strike", "yinyang-shiertian");
        map_skill("hand", "yinyang-shiertian");
        map_skill("cuff", "yinyang-shiertian");
        map_skill("claw", "yinyang-shiertian");
        map_skill("sword", "daojian-guizhen");
        map_skill("blade", "daojian-guizhen");

        prepare_skill("finger", "yinyang-shiertian");
        prepare_skill("unarmed", "yinyang-shiertian");

        // yun perform
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
              //
              (: command("perform sword.ben twice") :),
              (: command("perform sword.ben and sword.tian") :),
              // ����12t
              (: command("perform finger.tian twice") :),
              (: command("perform finger.zhen and finger.jiu") :),

              //(: exert_function, "roar" :),
              (: exert_function, "powerup" :),
              (: exert_function, "shield" :),
              (: exert_function, "recover" :),
              (: exert_function, "dispel" :),
              (: check_weapon :),

        }));

        set("my_life", 1); // ����Ѫ����10%��ʱ����һ�Σ����øò���Ϊ0

        //set("auto_perform", 1);
        //set("clear_fuben", 1);
        set("end_time", 1800);  // ����ս��������1800�������
        set("rewards", ([
                "exp"   : 30000,
                "pot"   : 10000,
                "mar"   : 5000,
                "weiwang"   : 500,
                "score"   : 500,
                "gold"   : 50,
        ]));
        set("drops", ([
                "FI&/clone/armor/daojian/kuangfeng"         : 10,
                "FI&/clone/armor/daojian/kuangfeng2"        : 10,
                "FI&/clone/armor/daojian/kuangfeng3"        : 1,
                "FI&/clone/armor/daojian/lengyue"           : 10,
                "FI&/clone/armor/daojian/lengyue2"          : 10,
                "FI&/clone/armor/daojian/lengyue3"          : 1,
                "FI&/clone/armor/daojian/xingshi"           : 10,
                "FI&/clone/armor/daojian/xingshi2"          : 10,
                "FI&/clone/armor/daojian/xingshi3"          : 1,
                "FI&/clone/armor/daojian/xingshi4"          : 1,
                "FI&/clone/tongren/tongren"+(1+random(2))   : 10,
                "FI&/clone/armor/daojian/renpiyi"           : 1,
        ]));
        set_temp("apply/reduce_damage", 70);
        set_temp("apply/reduce_busy", 36);
        set_temp("apply/add_busy", 15);

        setup();

        // �·�
        carry_object("/clone/cloth/bupao")->wear();

        // ����
        carry_object("/clone/weapon/anyue-dao")->wield();
}

void heart_beat()
{
        object ob;

        if( !clonep(this_object()) ) return;
        // �������perform yun������
        if (random(3) == 1)
        {
                delete_temp("no_perform");
                delete_temp("no_exert");
        }

        if (random(2) == 1)check_weapon();

        // ���ͬ���״̬
        check_friend();

        return ::heart_beat();
}

void check_friend()
{
        string friend_id;
        object ob, *obs, me, env;
        int i;

        friend_id = "miao renfeng";
        me = this_object();

        if( !(env = environment(me)) ) return;

        ob = present(friend_id, env);
        if (! ob) return;

        me->clean_up_enemy();
        ob->clean_up_enemy();

        // �Һ�ͬ�鲻�������ɱ
        me->remove_enemy(ob);
        me->remove_killer(ob);
        ob->remove_enemy(me);
        ob->remove_killer(me);

        // ���δ��ս���У��鿴ͬ���Ƿ���ս���У�����ڵĻ�����������ͬ��ĵ���
        if (! me->is_fighting() && ob->is_fighting())
        {
                ob->clean_up_enemy();
                obs = ob->query_enemy();
                if (me->is_busy()) me->interrupt_busy(me, 1000);
                if (me->is_busy()) me->interrupt_busy(me);
                if (sizeof(obs))
                {
                        message_vision(HIG "\n$N" HIG "���һ���������֣�С�ģ�һ����Ҳ����\n\n" NOR, me);
                        for(i = 0; i < sizeof(obs); i ++)
                        {
                                me->kill_ob(obs[i]);
                        }
                }
        }

        // ���ͬ���HPС��20%,���ҵ�HP����60%�򱣻��Է�
        if( query("eff_qi", ob) <= query("max_qi", ob)/10 && 
            query("eff_qi", me) >= query("max_qi", me)/5*3 )
        {
                if (query_temp("guardfor", me))return;
                if (me->is_busy())me->interrupt_busy(me, 1000);
                if (me->is_busy())me->interrupt_busy(me);
                command("guard " + friend_id);
        }
}

// �������
void check_weapon()
{
        object me, ob;

        me = this_object();

        // ͬʱ��������
        set("neili", query("max_neili"));

        if (me->is_busy())me->interrupt_busy(me, 1000);

        if (me->is_busy())me->interrupt_me(me);

        if( !query_temp("weapon", me) )
        {
                if( !objectp(ob = present("anyue dao", environment(me))) )
                ob = new("/clone/weapon/anyue-dao");
                ob->move(me);
                "/cmds/std/wield"->main(me, "anyue dao");
        }
        if( !query_temp("secondary_weapon", me) )
        {
                if( !objectp(ob = present("fengshen jian", environment(me))) )
                ob = new("/clone/weapon/fengshen-jian");
                ob->move(me);
                "/cmds/std/wield"->main(me, "fengshen jian");
        }

        if (random(5) == 1)
        {
                delete_temp("no_perform", me);
                delete_temp("no_exert", me);

                addn_temp("apply/damage", 50000, me);
                if (random(3) == 1)
                        command("perform sword.ben twice");
                else
                        command("perform sword.ben and sword.tian");
                addn_temp("apply/damage", -50000, me);

                if (random(2))
                {
                        delete_temp("eff/jiuyin-shengong/xin", me);
                }
        }

        if (random(10) == 1)
        {
                me->clear_condition();
        }

        // ��С���ʻָ���Ѫ
        if (random(1000) == 1)
        {
                if (query("eff_qi") < query("max_qi") / 3) addn("eff_qi", query("max_qi") / 5);
                if (query("qi") < query("max_qi") / 3) addn("qi", query("max_qi") / 5);
        }

        if (me->is_busy())me->interrupt_busy(me);

        if (! me->is_fighting() || random(5) == 1)
        {
                command("yun powerup");
        }

        return;
}

int accept_hit(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

int accept_fight(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

int accept_kill(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

void new_life()
{
        object me = this_object();

        full_self(); // ������Ѫ

        delete_temp("no_perform");
        delete_temp("no_exert");

        me->clear_condition();

        me->interrupt_me(this_object());

        set_temp("apply/attack", 1200000);
        set_temp("apply/unarmed_damage", 150000);
        set_temp("apply/damage", 150000);
        set_temp("apply/armor", 100000);
        set_temp("apply/qy", 70);  // ����
        set_temp("apply/fy", 70);  // ��Ե
        delete("my_life", me);

        message_vision(HIG "\n$N" HIG "���һ����Ŀ���ʱ����ɱ�⣡\n\n" NOR, me);

        return;
}

int receive_damage(string type, int damage, object who)
{
        object ob;

        object me = this_object();

        if( !query("my_life", me))return ::receive_damage(type,damage,who);

        if( query("qi", me)<query("max_qi", me)/10 )
        {
                new_life(); // ����һ��
                return 0;
        }

        return ::receive_damage(type, damage, who);
}

varargs void die(object killer)
{
        object ob;

        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") )
        {
                full_self();
                return;
        }

        // �����δ������������һ��
        if (query("my_life"))
        {
                new_life();
                return;
        }

        if( time() < query_temp("end_time") ) // ʱ��û�е�����������
        {
                addn("jing", query("max_jing") / 10);
                if( query("jing") > query("max_jing") ) set("jing", query("max_jing"));
                addn("eff_jing", query("max_jing") / 10);
                if( query("eff_jing") > query("max_jing") ) set("eff_jing", query("max_jing"));
                addn("qi", query("max_qi") / 10);
                if( query("qi") > query("max_qi") ) set("qi", query("max_qi"));
                addn("eff_qi", query("max_qi") / 10);
                if( query("eff_qi") > query("max_qi") ) set("eff_qi", query("max_qi"));
                message_vision(HIR "\n$N" HIR "���һ���������ط�����Ѫ����������\n\n" NOR, this_object());
                return;
        }

        if( !objectp(present("miao renfeng", environment(this_object()))) )
                set("clear_fuben", 1);

        message_vision(HIR "\n$N" HIR "��̾һ������ʧ��ɽ��֮�� ����\n\n" NOR, this_object());

        return ::die(killer);
}

varargs void unconcious(object defeater)
{
        object ob;

        //if( query("end_boss") || query("fight_boss") )
        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") ) {
                full_self();
                return;
        }
        die(defeater);
        return;
}