// regiser: yanluodian.c
// by Doing

#include <ansi.h>
#include <login.h>
#include <command.h>

inherit ROOM;

int is_chat_room() { return 1; }

int do_wash(string arg);
int do_born(string arg);

mapping born = ([
        "��������" : "/d/guanwai/kedian",
        "��������" : "/d/beijing/kedian",
        "��³����" : "/d/taishan/kedian",
        "�ؽ�����" : "/d/changan/kezhan",
        "�ɹ�����" : 0,
        "��ԭ����" : "/d/shaolin/kedian1",
        "��������" : "/d/xingxiu/kedian",
        "��������" : "/d/xiangyang/kedian",
        "��������" : "/d/city/kedian",
        "��������" : "/d/suzhou/kedian",
        "��������" : "/d/hangzhou/kedian",
        "��������" : "/d/fuzhou/kedian",
        "��������" : "/d/city3/kedian",
        "��������" : "/d/dali/kedian",
        "ǭ������" : 0,
        "��������" : "/d/foshan/beidimiao",
        "ŷ������" : ([ "born"      : "��������",
                        "surname"   : "ŷ��",
                        "startroom" : "/d/baituo/dating",
                     ]),
        "�������" : ([ "born"      : "��������",
                        "surname"   : "��",
                        "startroom" : "/d/guanwai/xiaowu",
                     ]),
        "���ϻ���" : ([ "born"      : "��������",
                        "surname"   : "��",
                        "startroom" : "/d/dali/wangfugate",
                     ]),
        "Ľ������" : ([ "born"      : "��������",
                        "surname"   : "Ľ��",
                        "startroom" : "/d/yanziwu/cuixia",
                     ]),
]);

void create()
{
        int i, k;
        string desc;
        string *position;

        set("short", HIR "���޵�" NOR);
        set("long", @LONG
��������ֲ������˸о���һ����ĺ��⣬��������ţͷ���棬ڤ
�����䣬�����������¡�ʮ�����ޣ������ڴˣ��ز������ڴ���֮�ϣ�
��ŭ����������ȽŲ�������Щ���ˡ�
    ��������һ��ʯͷ���ɵĳ��ӣ�����ˮ�峺ȴ�����ף���֪����
�����ж��
    �Ա���һ������(paizi)����Ҳ��Ӧ����ϸ������
LONG );
        set("no_fight", 1);
        set("item_desc", ([
                "paizi" : "Ͷ̥���������£��мǲ��ɲ��ʣ�ѡ�÷��򣬾�����born <����>��\n"
        ]));

        set("objects", ([
                __DIR__"npc/dizangwang" : 1,
        ]));

        set("no_say", "���޵�����ɭ�ֲ������������˵����\n");

        desc = query("item_desc/paizi");
        position = keys(born);

        for (i = 0, k = 1; i < sizeof(position); i++)
        {
                if (! stringp(born[position[i]]))
                        continue;

                desc += sprintf("%2d. " HIW "%s" NOR "\n", k++, position[i]);
        }

        for (i = 0; i < sizeof(position); i++)
        {
                if (! mapp(born[position[i]]))
                        continue;

                desc += sprintf("%2d. " HIC "%s" NOR "\n", k++, position[i]);
        }
        set("item_desc/paizi", desc);

        setup();
}

void init()
{
        add_action("do_wash", "wash");
        add_action("do_born", "born");
}

int do_wash(string arg)
{
        int i;
        int points;
        int tmpstr, tmpint, tmpcon, tmpdex;
        object me;
        mapping my;

        if (! objectp(me = this_player()) ||
            ! userp(me))
                return 1;

        write(HIC "���������ǳأ���ʱ��һ�ɼ������˽�ȥ��\n" NOR, me);

        tmpstr = tmpint = tmpcon = tmpdex = 13;

        switch(query("type", me) )
        {
        case "��ʿ��":
                tmpstr = 20;
                break;

        case "�ǻ���":
                tmpint = 20;
                break;

        case "������":
                tmpcon = 20;
                break;

        case "������":
                tmpdex = 20;
                break;

        default:
                break;
        }

        points = 80 - (tmpstr + tmpint + tmpcon + tmpdex);
        for (i = 0; i < points; i++) {
                switch (random(4)) {
                case 0: if (tmpstr < 30) tmpstr++; else i--; break;
                case 1: if (tmpint < 30) tmpint++; else i--; break;
                case 2: if (tmpcon < 30) tmpcon++; else i--; break;
                case 3: if (tmpdex < 30) tmpdex++; else i--; break;
                }
        }

        my = me->query_entire_dbase();

        my["str"] = tmpstr;
        my["int"] = tmpint;
        my["con"] = tmpcon;
        my["dex"] = tmpdex;
        my["kar"] = 10 + random(21);
        my["per"] = 10 + random(21);

        write(HIC "��ž����һ�����㱻ʪ���������˳�����\n" NOR, me);
        write(sprintf(HIY "\n����λ�õ����������츳�ֱ��ǣ�\n"
                          "�������� " HIG "%d" HIY " �� "
                          "���ԣ��� " HIG "%d" HIY " �� "
                          "���ǣ��� " HIG "%d" HIY " �� "
                          "�������� " HIG "%d" HIY " ��\n"
                          "��������⣬��ȥͶ̥(born)�ɣ�\n\n" NOR,
                      tmpstr, tmpint, tmpcon, tmpdex));
        set_temp("washed", 1, me);

        return 1;
}

int do_born(string arg)
{
        object me;
        object obj;
        object item;
        mixed dest;
        string new_name;
        string msg;

        if (! objectp(me = this_player()) ||
            ! userp(me))
                return 1;

        if( !query_temp("washed", me) )
                return notify_fail("���������ǳ���ϴһ��(wash)��ѡ����츳����Ͷ̥Ҳ���ٰ���\n");

        if (arg && arg[0] < 160)
                return notify_fail("������������ĵ���������born �������ϣ�������born ŷ�������Ա���Ͷ��̥��\n");

        new_name = 0;
        if (arg) sscanf(arg, "%s %s", arg, new_name);

        if (! arg || (! stringp(dest = born[arg]) && ! mapp(dest)))
        {
                message_vision("ţͷ��ݺݵĶ�$N˵����Ҫ��ʲô��Ͷ̥ȥ���\n", me);
                return 1;
        }

        if (mapp(dest) && stringp(dest["notice"]))
                return notify_fail(dest["notice"]);

        if (stringp(dest))
        {
                if (! objectp(obj = find_object(dest)))
                        obj = load_object(dest);
                set("startroom", dest, me);
                set("born", arg, me);
                set("born_family", "û��", me);
        } else
        {
                if (! objectp(obj = find_object(dest["startroom"])))
                        obj = load_object(dest["startroom"]);

                if (new_name)
                {
                        if (! sscanf(new_name, dest["surname"] + "%*s"))
                                new_name = dest["surname"] + new_name;

                        if (strlen(new_name) > 8)
                                return notify_fail("�������̫���ˡ�\n");

                        if (strlen(new_name) < 4)
                                return notify_fail("�������̫���ˡ�\n");

                        if (! is_chinese(new_name))
                                return notify_fail("���������������֡�\n");
                }

                if( query("surname", me) != dest["surname"] )
                {
                        // ������Ҫ�仯
                        NAME_D->remove_name(me->name(1),query("id", me));
                        if( !new_name)new_name=dest["surname"]+query("purename", me);
                        if (stringp(msg = NAME_D->invalid_new_name(new_name)))
                        {
                                write(msg);
                                write("����Կ�����Ͷ�����ҵ�ʱ������ѡ�����֣�born <����> <����>\n");
                                return 1;
                        }
                        set("surname", dest["surname"], me);
                        set("purename", new_name[strlen(dest["surname"])..<1], me);
                        me->set_name();
                        NAME_D->map_name(me->name(1),query("id", me));
                }

                set("startroom", dest["startroom"], me);
                set("born", dest["born"], me);
                set("born_family", arg, me);

                if (mapp(dest["family"]))
                {
                        set("family", dest["family"], me);
                        me->assign_apprentice(dest["family"]["title"], 0);
                }
        }
        if (! objectp(obj))
        {
                message_vision("ţͷһ����ɦɦͷ˵����ô����������...\n", me);
                return 1;
        }

        message_vision("ţͷ����һ�ţ���$N���˳�ȥ��\n", me);
        
        foreach (item in all_inventory(me))
                if( !query("armor_type", item) )
                {
                        message_vision("$N������$n��\n", me, item);
                        if( item->is_character() || query("value", item) )
                                item->move(environment(me));
                        else
                                destruct(item);
                }

        // ѡ�����⼼��
        UPDATE_D->born_player(me);

        me->move(obj);
        set("mud_age", 0, me);
        set("age", 14, me);
        me->save();
        HELP_CMD->main(me, "rules");
        message_vision("$N�����۾�����㯵��������İ�������硣\n", me);

        return 1;
}