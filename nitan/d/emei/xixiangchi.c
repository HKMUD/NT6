#include <ansi.h>
inherit ROOM;

string look_pool();

void create()
{
      set("short", "ϴ���");
        set("long", @LONG
ϴ���ԭֻ��һͤ��ͤǰ��һ��ʯ����С��(pool)���ر߲�Զ��
��Σ�ҡ�ϴ���Ԣ��һƬ��ɼ���У��������������ɽ��������
�����������̿������������ʱ�����������ţ�������ޣ�����
�����칬�����������������������ġ���س�ҹ�����ɴ��������ʣ�
�����׶�ƺ������������ʯ��
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "eastdown"  : __DIR__"ztpo2",
          "southup"   : __DIR__"lingyunti",
      ]));
      set("item_desc", ([
          "pool" : (: look_pool :),
      ]));
      set("no_clean_up", 0);
        set("coor/x", -560);
        set("coor/y", -240);
        set("coor/z", 160);
        setup();
}

string look_pool()
{
    return WHT "\n����һ��ʯ��������С�أ���˵���ͳ�����"
           "�ˣ������ڴ˳���\nԡ���󣬶���������𶥣���"
           "Ϊ��ϴ��ء���\n" NOR;
}