//andao2.c                �Ĵ����š��ص�

inherit ROOM;

void create()
{
        set("short","�ص�");
        set("long",
"����,�������һ��,�����ʲô���������Ƶ���������,�㲻���뵽\n"
"���ƺ���ÿ�����䶼��������ɱ��,̫�ֲ������ܺ�����Ϣ���������һ\n"
"���붼����������\n"
);
        set("exits",([
                "north" : __DIR__"andao1",
                "west" : __DIR__"huayuan",
        ]));
        setup();
        replace_program(ROOM);
}