// finit.h
#include <ansi.h>
#define A_TIME 60

string * weapon_msg = ({
        "/d/city/task2/obj/anqi",
        "/d/city/task2/obj/anqi",
        "/d/city/task2/obj/anqi",
        "/d/city/task2/obj/anqi",
        "/d/city/task2/obj/anqi",
        "/d/city/task2/obj/anqi",
        "/d/city/task2/obj/chuidutong",
        "/d/city/task2/obj/sheerkou",
});

void init()
{
        remove_call_out("do_check");
        call_out("do_check",1);
        remove_call_out("do_wait");
        call_out("do_wait",A_TIME);
}

void do_check()
{
        object me = this_object();
        object ob;

        remove_call_out("do_check");
        if (! living(me) || me->fighting() )
        {
                call_out("do_check",1);
        }
        else
        {
                if( !ob = present("biao tou",environment(me)))
                {
                        call_out("do_check",1);
                }
                else
                {
                        command("shot"+query("id", ob));
                        addn("combat_num", 1, ob);
                        message_vision(HIW"\n$N�󺰵������ڵ������ӣ��������ɣ�\n"NOR,me);
                        remove_call_out("do_sha");
                        call_out("do_sha",1);
                }
        }
}

void do_wait()
{
        object ob;
        object me = this_object();

        remove_call_out("do_wait"); 
        if (me->is_fighting() || !living(me) )
        {
                call_out("do_wait",A_TIME);
        }
        else
        {
                message_vision("$N˵����������������ү�����ˣ�\n$Nһ�����Զ�����˿�ȥ��\n",this_object());
                destruct(me);
        }
}

void do_sha()
{
        object me = this_object();
        object cart,ob, weapon;
        string wmsg;

        remove_call_out("do_sha");
        if (! living(me) || me->fighting() )
        {
                message_vision("$Nҧ���гݵض�����մ�У��������죡��\n",me);

                call_out("do_sha",1);
        }
        else
        {
                if( ob = present("biao tou",environment(me)))
                {
                        wmsg = weapon_msg[random(sizeof(weapon_msg))];
                        weapon = new(wmsg);
                        weapon->move(me);
                        message_vision(HIW"\n$N����$n�󺰵����㻹�����������ҵ��ֶΣ�\n"NOR,me, ob);
                        command("shot"+query("id", ob));
                        addn("combat_num", 1, ob);
                        call_out("do_sha",1);
                }
                else
                {
                        message_vision("$N˵�����󹦸�ɣ���ү�����ˣ�\n$Nһ������Զ���ɳ۶�ȥ��\n",me);
                        if ( cart = present("cart",environment(me)))
                        destruct(cart);
                        destruct(me);
                }
        }
}
