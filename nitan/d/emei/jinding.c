inherit ROOM;

void create()
{
              set("short", "��");
        set("long", @LONG
����Ƕ���ɽ������𶥡��˷�������أ������Ʊ�����������
׳�������������������ڤ���쿪���ʴ��ɻ��������Ͻ𶥣���Ұ��
Ȼ���ʣ��񿴽��£�����Ⱥ��ӿ�̵��䣬������˿���������Զ����
�����ѩɽ��ب��ʣ�����ɽֱ���񷡣
LONG );
        set("no_sleep_room",1);
              set("outdoors", "emei");

              set("objects", ([
                   CLASS_D("emei") + "/fengling" : 1,
              ]));
              set("exits",([
                  "northdown" : __DIR__"wanxingan",
                  "southwest" : __DIR__"woyunan", 
                  "southeast" : __DIR__"huacangan",
              ]));

              set("no_clean_up", 0);
              set("coor/x", -570);
        set("coor/y", -310);
        set("coor/z", 220);
        setup();
}