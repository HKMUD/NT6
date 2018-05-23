// xieyan.c

#include <ansi.h>

inherit NPC;

mixed ask_me(); 
void greeting(object ob);

void create()
{
        seteuid(getuid());
        set_name("л�̿�", ({ "xie yanke", "xie" }));
        set("long", @LONG
Ħ���ʿл�̿������µ�һ���ˣ��书��ǿ������ɢ��
��������ö�����Կ�������ӵ�д���������κ�Ը����
LONG );
        set("nickname", HIG "Ħ���ʿ" NOR);
        set("gender", "����");
        set("age", 71);
        set("shen_type", 1);
        set("attitude", "friendly");

        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);

        set("qi", 5000);
        set("max_qi", 5000);
        set("jing", 2500);
        set("max_jing", 2500);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 150);

        set("combat_exp", 2500000);

        set_skill("force", 260);
        set_skill("unarmed", 250);
        set_skill("dodge", 250);
        set_skill("parry", 250);
        set_skill("strike", 260);
        set_skill("yijinjing", 260);
        set_skill("shexing-lifan", 250);
        set_skill("bizhen-qingzhang", 260);

        map_skill("force", "yijinjing");
        map_skill("dodge", "shexing-lifan");
        map_skill("strike", "bizhen-qingzhang");
        map_skill("parry", "bizhen-qingzhang");

        prepare_skill("strike", "bizhen-qingzhang");

        set("inquiry", ([
                "��������" : (: ask_me :),
                "����"     : (: ask_me :),
                "����"     : (: ask_me :),
                "����"     : (: ask_me :),
                "������"   : "��ö���������Ѿ��ջء�",
                "ʯ����"   : "�������Ǹ��׳ջ�û��ô��",
        ]));

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}

int accept_object(object me, object ob)
{
        if( query("id", ob) != "xuantie ling" )
        {
                command("say ��������ֶ�����ʲô��");
                return 0;
        } else
        {
                command("say �ܺã��ܺã�");
                command("say ��������һ�ױ������ƣ��������괴�µľ�ѧ�����Դ������㡣");
                set("can_learn/xieyanke/bizhen-qingzhang", 1, me);
                destruct(ob);
                return -1;
        }
}

int recognize_apprentice(object ob, string skill)
{
        if( !query("can_learn/xieyanke/bizhen-qingzhang", ob) )
        {
                command("say ����ʲô���������ҹ�����\n");
                return -1; 

        }

        if (skill != "bizhen-qingzhang")
        {
                command("killair");
                command("say ��˵��ֻ�����������Ʒ����㲻ѧ�����ˡ�");
                return -1;
        }

        if (ob->query_skill("bizhen-qingzhang", 1) > 100)
        {
                command("say ���ˣ�ʣ�µ��Լ�ȥ����");
                return -1;
        }
        return 1;
}

mixed ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/bizhen-qingzhang/pengpai", me) )
                return "�̵ܽ��Ѿ������ˣ��������Ҹ��";

        if( !query("can_learn/xieyanke/bizhen-qingzhang", me) )
                return "���ҹ�������������ǰ���£�";

        if (me->query_skill("bizhen-qingzhang", 1) < 180)
                return "��ı�������������̶Ⱦ����ʾ��У�";

        message_vision(HIW "$n" HIW "��Цһ����˫�ƶ�Ȼ����"
                       "��һ����Ȧ�����ƶ�������ʱһ����ӿ��"
                       "�ȵľ����粨��һ����" HIW "ӿ����\n$N"
                       HIW "�󺧣�Ӳ������һ�У�ֻ����Ϣ����"
                       "��ȫ��������Ҫɢ��һ�㡣ͻȻĿ��һ��"
                       "���ƺ�������ʲô��\n" NOR,
                       me, this_object());

        command("grin");
        command("say ���̵ܽ��Ѿ������ˣ��Ժ��Ҹ��߸���·��");

        tell_object(me, HIC "��ѧ���˱������ơ����ȡ���һ�С�\n" NOR);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 300000);
        set("can_perform/bizhen-qingzhang/pengpai", 1, me);
        return 1;
}