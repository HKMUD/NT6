inherit DEMONROOM;

void create()
{
        set("short", "�ձ�������");
        set("long",@LONG
���а�����9��18�±�����������ʿ��Ϊ���ǵ�Ӣ�۱���ɣ�
LONG);

	set("exits", ([
		"east"   : __DIR__"japan2",
		"west"   : __DIR__"japan0",

	]));

		set("n_time", 30); 
		set("n_npc", 5); 
		set("n_max_npc", 15);
		set("s_npc", "/clone/dream_npc/japangame/japannpc01");

        setup();
}