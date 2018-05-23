// make.c

#include <ansi.h>
#include <medical.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object qm;
        object hob;
        string med;
        mapping make;
        mapping req;
        mapping herb;
        string *ks;
        object *hlist;
        string msg;
        int only_list;
        int i;

        if (! arg)
        {
                make=query("can_make", me);
                if (! mapp(make))
                        return notify_fail("�����ڲ������κ�ҩ�\n");

                ks = keys(make);
                msg = "�������Ѿ�����";
                if (sizeof(ks) >= 2)
                        msg += implode(ks[0..sizeof(ks) - 2], "��") +
                                "��" + ks[sizeof(ks) - 1] + "�ˡ�\n";
                else
                        msg += ks[0] + "�ˡ�\n";
                msg = sort_string(msg, 64);
                write(msg);
                return 1;
        }

        // only for list?
        only_list = sscanf(arg, "%s ?", arg);

        if( !stringp(med=query("can_make/"+arg, me)) )
                return notify_fail("�㻹����������ҩ����\n");

        // The player can only make the medicine under the /clone/medicine,
        // nothing, but for save memory.
        med = MEDICINE(med);
        if (file_size(med + ".c") < 0)
                return notify_fail("����ҩ�������Ѿ�ʧ���ˣ��㻹��������ʦ�ɡ�\n");

        if (! mapp(req = query("mixture", get_object(med))))
                return notify_fail(med->name() + "�����޷�����...\n");

        if (! mapp(herb = req["herb"]))
                return notify_fail(med->name() + "��Ҫʲôԭ����...\n");

        if (only_list)
        {
                // show herb
                write("����" + arg + "��Ҫ������Щҩ�ģ�\n");
                ks = keys(herb);
                for (i = 0; i < sizeof(ks); i++)
                {
                        write(chinese_number(herb[ks[i]]) + query("base_unit", get_object(HERB(ks[i]))) +
                              HERB(ks[i])->name() + "\n");
                }
                return 1;
        }

        if (me->is_fighting())
                return notify_fail("��ܵ�ʱ���㻹���й�����ҩ��\n");

        if (me->is_busy())
                return notify_fail("�����Ȱ���ͷ������æ��ɡ�\n");

        if( query("no_fight", environment(me)) && 0 )
                return notify_fail("����������ҩֻ��Ҫ���ŵ����ˡ�\n");

        qm=query_temp("handing", me);
        if (! qm)
                return notify_fail("����Ȱ��ܹ�ĥҩ���в���(hand)�����ϲ��С�\n");

        if (! qm->can_make_medicine())
                return notify_fail(qm->name() + "�����޷������в������ðɡ�\n");

        if (sizeof(all_inventory(qm)) > 0)
                return notify_fail("�㻹���Ȱ�" + qm->name() + "����Ķ����ó�����˵��\n");

        if( query("jing", me)<query("max_jing", me)*7/10 )
                return notify_fail("�����ھ������Լ��У��޷���ҩ��\n");

        ks = keys(req) - ({ "herb", "neili", "jing", "jingli", "min_level", "time" });

        // check skills
        for (i = 0; i < sizeof(ks); i++)
                if (me->query_skillo(ks[i], 1) < req[ks[i]])
                        return notify_fail("���" + to_chinese(ks[i]) +
                                           "ˮƽ���������޷�����" +
                                           med->name() + "��\n");

        // check herb
        ks = keys(herb);
        hlist = allocate(sizeof(ks));
        for (i = 0; i < sizeof(ks); i++)
        {
                hob = present("herb_" + ks[i], me);
                if (! hob || hob->query_amount() < herb[ks[i]])
                {
                        if (file_size(HERB(ks[i]) + ".c") < 0)
                        {
                                write("û��(" + ks[i] + ")����ҩ�İ���"
                                      "��ô���£�\n");
                                return 1;
                        }
                        return notify_fail("����˵�ҩ�ģ�����" +
                                           HERB(ks[i])->name() +
                                           "�ķ�����������\n");
                }
                hlist[i] = hob;
        }

        // decrease herb
        msg = "��ѡ��";
        for (i = 0; i < sizeof(ks); i++)
        {
                if (i) msg += "��";
                msg += chinese_number(herb[ks[i]]) +
                       query("base_unit", hlist[i])+
                       hlist[i]->name();
                hlist[i]->add_amount(-herb[ks[i]]);
        }
        msg += "��Ȼ��С�������İ����Ƿŵ�" + qm->name() + "���棬��ʼ��ҩ��\n";
        msg = sort_string(msg, 64);
        write(msg);
        message("vision", me->name() + "����������ŪŪ����֪���ڸ�ɶ��\n",
                environment(me), ({ me }));
        me->start_busy(bind((:call_other, __FILE__, "making" :), me),
                       bind((:call_other, __FILE__, "halt_make" :), me));
        me->set_short_desc("����ר����־������ҩ�");
        set_temp("pending/making", 0, me);
        set_temp("making/medicine", med, me);
        set_temp("making/time", req["time"], me);
        set_temp("making/require", req, me);
        set_temp("making/container", qm, me);
        return 1;
}

int stop_making(object me)
{
        delete_temp("making", me);
        delete_temp("pending/making", me);
        me->set_short_desc(0);
        return 0;
}

int making(object me)
{
        int step;
        mapping req;
        string msg_me, msg_out;
        string med;
        object ob;
        object qm;

        step=query_temp("pending/making", me);
        req=query_temp("making/require", me);
        med=query_temp("making/medicine", me);
        qm=query_temp("making/container", me);
        if( qm != query_temp("handing", me) )
        {
                write("�ţ��в���...���ҵ��в���\n");
                return stop_making(me);
        }

        switch (step)
        {
        default:
                step = 0;
                msg_me = "��������ƣ������ĵ���" + qm->name() + "�����ҩ�ġ�\n";
                msg_out = "$N������ƶ��۶��۵ĵ��ú��𾢡�\n";
                break;
        case 1:
                msg_me = "�������꣬ҩ���ۼ������һ���С��顣\n";
                msg_out = "$Nû��û�˵ĵ��ġ�\n";
                break;
        case 2:
                msg_me = "���������ĥ��ҩ�ģ�����Խ��Խϸ��\n";
                msg_out = "$N���ŵ�ĥ�Ŷ�����\n";
                break;
        case 3:
                msg_me = "����Ű���Щ�����Ĵ���һ���ҩ�ĵ��顣\n";
                msg_out = "$NͻȻ�ֶ��۶��۵ĵ�����ͣ��\n";
                break;
        case 4:
                msg_me = "��ϸϸ�Ľ����е�ҩ��ĥ���˷�ĩ��\n";
                msg_out = "$N���Ű���ĥ��ĥȥ��\n";
                break;
        case 5:
                msg_me = "������ĺ���" + qm->name() +
                         "��ĬĬ���������������������ҩ�ġ�\n";
                msg_out = "$N����" + qm->name() + "��˫�ֱ��ţ���֪���ڸ�ʲô��\n";
                break;
        case 6:
                if( query("jing", me)<req["jing"] )
                {
                        write("����þ��񲻼ã��������Լ���������" +
                              med->name() + "����\n");
                        return stop_making(me);
                }
                        
        
                if( query("neili", me)<req["neili"] )
                {
                        write("������������ã��������Լ���������" +
                              med->name() + "����\n");
                        return stop_making(me);
                }
        
                if( query("jingli", me)<req["jingli"] )
                {
                        write("����þ������ã��������Լ���������" +
                              med->name() + "����\n");
                        return stop_making(me);
                }
        
                me->receive_damage("jing", req["jing"]);
                addn("neili", -req["neili"], me);
                addn("jingli", -req["jingli"], me);

                if( me->add_temp("making/time",-1)>0 )
                {
                        // when time > 0, next busy stage will
                        // still at 6, becuase the step will be
                        // increase by 1 later, so I decrase it
                        // first
                        step--;
                }

                msg_me = random(2) ? "�����" + qm->name() + "������������������"
                                     "���������ҩ���ƺ��Ѿ��ڻ��ˡ�\n"
                                   : "�㲻�ϵĽ���������" + qm->name() + "������"
                                     "ʹ�����ҩ���ڻ���һ��\n";
                msg_out = random(2) ? "$N���Ϻ���һ����Ŀڤ���������\n"
                                    : "$N��������" + qm->name() + "û��û�˵�ת��תȥ��\n";

                break;
        case 7:
                msg_me = "����������������" + qm->name() + "ʹ�����ҩ�ĳ��׵��ںϡ�\n";
                msg_out = "$Nüë���˶������������Ϻ���һ����Ŀڤ���������\n";
                break;
        case 8:
                msg_me = "�㳤����һ�����������İ����ÿ�������" + qm->name() + "��\n";
                msg_out = "$N������һ�����������İ����ÿ�������" + qm->name() + "��\n";
                break;
        case 9:
                if ((random(me->query_skill("medical", 1) +
                     query("item_prop/medical", qm)) >= req["min_level"]) ||
                    (me->query_skillo("liandan-shu", 1) + query("item_prop/liandan-shu", qm)) >= req["liandan-shu"]+100 )
                {
                        ob = new(med);
                        ob->move(qm, 1);
                        msg_me = HIM "��ѡ�" + ob->name() + HIM "���ɹ����ƺ��ˣ�\n" NOR;
                        msg_out = HIM "$N" HIM "���¶��һ˿΢Ц��\n" NOR;
                        me->improve_skill("liandan-shu", me->query_int()*100+100); 
                }else if( !query("special_skill/lucky", me) || random(2) == 0 )
                {
                        msg_me = HIG "�����˾�ɥ����Ȼʧ���ˣ����ǿ�ϧ�ˡ�\n" NOR;
                        msg_out = HIG "$N" HIG "һ����ɥ����"
                                  "֪��������ʲô��ù�¡�\n" NOR;
                }else
                {
                        ob = new(med);
                        ob->move(qm, 1);
                        msg_me = HIM "��о��ƺ���ʲô�ط�û�����ԣ�Ȼ���������ʵ��̫���ˣ�\n��ѡ�" + ob->name() + HIM "���ɹ����ƺ��ˣ�\n" NOR;
                        msg_out = HIM "$N" HIM "���¶��һ˿΢Ц��\n" NOR;
                        me->improve_skill("liandan-shu", me->query_int()*10+10); 
                }
                break;
        }

        msg_out = replace_string(msg_out, "$N", me->name());
        message("vision", msg_me, me);
        message("vision", msg_out, environment(me), ({ me }));
        step++;
        if (step >= 10)
                // end of making
                return stop_making(me);

        set_temp("pending/making", step, me);
        return 1;
}

int halt_make(object me)
{
        message_vision("$N�����е��в�һ����������"
                       "ȫ�����˳�����\n", me);
        stop_making(me);
        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : make [<ҩƷ>] [?]

���ָ�������������ĳ��ҩƷ�����û��ָ��ҩƷ����г���ǰ
������Ƶ�ҩƷ�������ָ����ҩƷ��������һ��"?" ����г���
������ҩƷ��Ҫ�Ĳ��ϡ�

HELP );
    return 1;
}