// xuedao-book.c

inherit BOOK;

void create()
{
        set_name("��絶���ؼ�", ({ "kuangfeng book", "book" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long","����һ��������С���ӣ�����д�ſ�絶���ؼ��ĸ�С�֡�\n");
                set("no_sell", 1);
                set("material", "silk");
                set("skill", ([
                        "name": "kuangfeng-blade",      //name of the skill
                        "exp_required": 100000, //minimum combat experience required
                        "jing_cost": 50,        // jing cost every time study this
                        "difficulty": 32,       // the base int to learn this skill
                        "max_skill": 180,       // the maximum level you can learn
                ]) );
        }
}