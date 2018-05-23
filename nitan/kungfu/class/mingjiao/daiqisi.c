// This program is a part of NT MudLIB
// dai.c ���˿

#include <ansi.h>
#include "mingjiao.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
string ask_fan();

void create()
{
        set_name("���˿",({"dai qisi","dai","qisi"}));
        set("title", HIG "����" MAG "��������" NOR);
        set("gender","Ů��");
        set("long",  "�������̵��Ĵ󻤷�֮һ������������\n"+
                     "�������������ǵ������̵ĵ�һ��Ů��\n"+
                     "�������Ѹߣ��Բ���ɫ�Բ������ꡣ\n");
        set("age", 45);
        set("attitude", "peaceful");
        set("shen", -10000);
        set("str", 24);
        set("int", 40);
        set("con", 26);
        set("dex", 30);
        set("max_qi", 2800);
        set("max_jing", 2200);
        set("eff_jingli", 2000);
        set("jiali", 10);
        set("combat_exp", 1100000);
        set("level", 30);

        set_skill("throwing",280);
        set_skill("dodge",240);
        set_skill("force", 240);
        set_skill("staff", 280);
        set_skill("cuff", 240);
        set_skill("parry", 240);
        set_skill("claw", 240);
        set_skill("pili-quan", 240);
        set_skill("duoming-jinhua",280);
        set_skill("yinhu-zhang", 280);
            set_skill("shenghuo-xinfa", 240);
              set_skill("shenghuo-bu", 240);
        set_skill("literate", 230);
        set_skill("martial-cognize", 200);

        map_skill("force", "shenghuo-xinfa");
            map_skill("dodge", "shenghuo-bu");
            map_skill("parry", "yinfeng-dao");
            map_skill("throwing", "duoming-jinhua");
        map_skill("cuff", "pili-quan");
            map_skill("staff", "yinhu-zhang");

        prepare_skill("cuff", "pili-quan");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: command("perform staff.lao") :),
                (: command("perform cuff.jin") :),
        }) );

        set("inquiry", ([
                "лѷ"   : (: ask_fan :),
                "������" : (: ask_fan :),
                "����" : (: ask_fan :),
        ]) );

        create_family("����", 35, "��������");
        set("master_ob",4);
        setup();

        carry_object("/d/mingjiao/obj/yel-cloth")->wear();
        carry_object("/d/mingjiao/obj/luopan");
        carry_object("/d/mingjiao/obj/jinhua")->wield();
}

void attempt_apprentice(object ob)
{
        mapping fam=query("family", ob);

        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<5000 )
        {
                command("say ����������������û�������������ذɡ�");
                return;
        }

        if (! fam || fam["family_name"] != "����")
        {
                command("say "+RANK_D->query_respect(ob) + "�뱾��������������֪�˻��Ӻ�̸��");
                return;
        }

        /*
        if( query("gender", ob) != "Ů��"){
                command("say "+RANK_D->query_respect(ob)+"���ǻ�ȥ�ɣ�����ֻ��Ů���ӡ�");
                return;
        }

        if ((int)ob->query_skill("shenghuo-shengong", 1) < 100)
        {
                command("say Ҫѧ��Ϊ������书�������и�����ڹ���Ϊ��");
                command("say " + RANK_D->query_respect(ob) + "�Ƿ�Ӧ����ʥ�����϶��µ㹦��");
                return;
        }
        */

        if ((int)ob->query_int() < 28)
        {
                command("say ��ѧ�ҵĽ𻨰����������ܹ��۹��ķ��������˷���");
                command("say ���������Է��棬"+RANK_D->query_respect(ob)+"�Ƿ��Ӳ��˵㣿");
                return;
        }
        command("say �ţ����㻹�Ǹ�ѧ����ϣ������Ҿ�������ɣ�");
        command("say ��л������ӣ����������ֵ�һ���ģ�Ϊ�������壬�������̷�����ɡ�");
        command("recruit "+query("id", ob));
        set("title",query("title",  this_object())+"���½���", ob);
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "������" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yinhu-zhang/lao",
                           "name"    : "������",
                           "sk1"     : "yinhu-zhang",
                           "lv1"     : 100,
                           "force"   : 260,
                           "neili"   : 2000,
                           "gongxian": 750,
                           "shen"    : 70000, ]));
                break;
        case "����ɻ�" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/duoming-jinhua/fei",
                           "name"    : "����ɻ�",
                           "sk1"     : "duoming-jinhua",
                           "lv1"     : 140,
                           "neili"   : 2000,
                           "gongxian": 800,
                           "shen"    : 100000, ]));
                break;

        default:
                return 0;
        }
}
string ask_fan()
{
        mapping fam;
        object *allob,env,ob,me=this_player();
        string *sname;
        int i, count, here = 0;

        if( !(fam=query("family", me)) || fam["family_name"] != "����" )
                return RANK_D->query_respect(me) +
                "�뱾��������������֪�˻��Ӻ�̸��";

        addn("fan",-1);
        ob = new("/d/binghuo/obj/fan");
        ob->move(me);
        message_vision("$N���һ�淫����\n",me);

        return "�ðɣ����ϼ��գ�����һ�鷫�������Լ�ȥ��л����ɡ�";

}