// Room: /d/gaochang/zoulange.c
// Last Modified by Winder on Jul. 15 2000


inherit ROOM;
string look_writing();


void create()
{
        set("short", "����");
        set("long", @LONG
�����Ǻ�����ȡ�����һ��֧������ĸ�ǽ�ϣ���һ�����뱱�߰�
���õ��ݶ�����������������̧����ȥ��������Ҳ�ò�������˸��ַ�
���ͼ�Σ�ÿ�����ƺ�������˵һ���渶��˵ķ𾭹��¡��ϱ�ǽ����
��һ����(writing)��
LONG
        );

        set("exits", ([
                "northwest" : __DIR__"zoulangc",
                "southwest" : __DIR__"eroom3",
        ]));
        set("item_desc",([
                "writing" : (: look_writing :),
        ]));
        set("no_clean_up", 0);
        setup();
}

string look_writing()
{
        return
        "\n"
"       ���������������������\n"
"       ������                  �������\n"
"       ������  ��������  �������\n"
"       ������  ��  ����  ��  �������\n"
"       ������  ���  ��  ���  �������\n"
"       ������  ����  ����  �������\n"
"       ������  ���  ��  ���  �������\n"
"       ������  ��  ����  ��  �������\n"
"       ������  ��������  �������\n"
"       �����  ����������  ��  ����\n"
"       ����  ������������  �����\n"
"       ���������������������\n"
"       ���������������������\n";

}

void init()
{
        add_action("do_study", "yanxi");
}


int do_study(string arg)
{
        object me = this_player();
        int cost=10;

        if ( !arg && ( arg != "qiang" ) && ( arg != "qiangbi" ) )
                return notify_fail("ʲô��\n");

        if ( (int)me->query_skill("literate", 1) < 1)
                return notify_fail("���Ǹ���ä����ѧ���Ļ�(literate)�ɡ�\n");

        if( query("jing", me)<30 )
                return notify_fail("�����ھ����޷����У�\n");

        me->receive_damage("jing", 10);

        message_vision("$N��ר���ж�ǽ���ϵĹŹ�ͼ�Ρ�\n", me);

        if ( (int)me->query_skill("dodge", 1) < 100)
        {
            if( query("jing", me)>cost )
              {
                 me->improve_skill("dodge",(query("int", me)/4));
                 write("�����ǽ����ĥ��һ�ض����ƺ��Ի����Ṧ�е��ĵá�\n");
                 set_temp("stone_learned", 1, me);
                 return 1;
                }
            else
               {
                cost=query("jing", me);
                write("�����ڹ���ƣ�룬�޷�ר�������ж������Ṧ��\n");
               } 
                            
        }

        if( !query_temp("stone_learned", me) )
        {
                write("�����ǽ����ĥ��һ�ض�������������˵��̫��ǳ�ԣ�������˵�Ѻ��������ˡ�\n");
        }
        return 1;
}