//Room: /d/dali/jinzhihe.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","��֭����");
        set("long", @LONG
����λ����֭���ϣ�ԭ������һ���ز��£������Ժ��ϡ�Ψ��
һ��ʯ�̾���(jingzhuang)�������С��˴�Ϊ��׶״���߲�ʯ�񡣸�
Լ����ߣ�����Ϊ�˽��ε���ʯ�����Ͽ��������������֮���н�ʯ��
���Ǳ���֮���ܣ������ϲ�֮��ʯ��
LONG );
        set("item_desc", ([
           "jingzhuang" : "���Ǹ�ϡ����������ȥ����Ҳ������\n",
        ]));
        set("objects", ([
           "/d/dali/npc/seng": 2,
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "east"  : "/d/dali/yanchi1",
            "west"  : "/d/dali/xiaojing",
            "enter" : "/d/dali/jingzhuang1",
        ]));
	set("coor/x", -19090);
	set("coor/y", -6870);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}