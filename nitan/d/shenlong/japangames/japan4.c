inherit DEMONROOM;

void create()
{
        set("short", "�ձ�������");
        set("long",@LONG
���а�����9��18�±�����������ʿ��Ϊ���ǵ�Ӣ�۱���ɣ�
LONG);

	set("exits", ([
		"west"   : __DIR__"japan3",
		"east"   : __DIR__"changqi1",
		"north"  : __DIR__"daban1",
	    "south"  : __DIR__"siguo1",

	]));

		set("n_time", 30); 
		set("n_npc", 5); 
		set("n_max_npc", 15);
		set("s_npc", "/clone/dream_npc/japangame/japannpc01");

        setup();
}