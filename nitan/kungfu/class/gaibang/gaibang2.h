// gaibang.h for fight and get ������

int accept_object(object ob, object obj)
{
        object me = this_object();

        mappingmy_fam=query("family", me);
        mappingob_fam=query("family", ob);

        if (!ob_fam || (ob_fam["family_name"] != "ؤ��"))
        {
                command("say ���������������\n");
                return 0;
        }

        if( query_temp("have_cloth", ob) || present("pobu",ob) )
        {
                command("say �㲻���Ѿ����Ʋ�ô?");
                return 0;
        }

        if( ((query("beggarlvl", ob) == 0) && 
                (query("combat_exp", ob) <= 500)) || 
                ((query("beggarlvl", ob) == 1) && 
                (query("combat_exp", ob) <= 1000)) || 
                ((query("beggarlvl", ob) == 2) && 
                (query("combat_exp", ob) <= 3000)) || 
                ((query("beggarlvl", ob) == 3) && 
                (query("combat_exp", ob) <= 5000)) || 
                ((query("beggarlvl", ob) == 4) && 
                (query("combat_exp", ob) <= 10000)) || 
                ((query("beggarlvl", ob) == 5) && 
                (query("combat_exp", ob) <= 15000)) || 
                ((query("beggarlvl", ob) == 6) && 
                (query("combat_exp", ob) <= 20000)) || 
                ((query("beggarlvl", ob) >= 7) && 
                (query("combat_exp", ob) <= 30000)) )
        {
                command("say �����ǵ�ŧˮ���ҿ������˰ɡ�\n");
                return 1;
        }
        if( ((query("beggarlvl", ob) == 0) && 
                (query("beggarlvl", me) == 1)) || 
                ((query("beggarlvl", ob) == 1) && 
                (query("beggarlvl", me) == 2)) || 
                ((query("beggarlvl", ob) == 2) && 
                (query("beggarlvl", me) == 3)) || 
                ((query("beggarlvl", ob) == 3) && 
                (query("beggarlvl", me) == 4)) || 
                ((query("beggarlvl", ob) == 4) && 
                (query("beggarlvl", me) == 5)) || 
                ((query("beggarlvl", ob) == 5) && 
                (query("beggarlvl", me) == 6)) || 
                ((query("beggarlvl", ob) == 6) && 
                (query("beggarlvl", me) == 7)) || 
                ((query("beggarlvl", ob) == 7) && 
                (query("beggarlvl", me) == 8)) || 
                ((query("beggarlvl", ob) == 8) && 
                (query("beggarlvl", me) == 9)) )
        {
                if( (query("id", obj) == "qingzhuling") && !query_temp("have_cloth", ob) )
                {
                        set_temp("fight_ok",query("beggarlvl",  me), ob);
                        command("say �ã���Ȼ����������ǾͿ���������ˡ�\n");
                        remove_call_out("destroying");
                        call_out("destroying", 1, me, obj);
                        return 1;
                }
        }
        command("smile");
        command("say ������Ȼֻ������������Ҳ�ǲ��еġ�\n");
        command("say �ⶫ�����㻹���Լ����Űɡ�\n");
        command("give"+query("id", obj)+"to"+query("id", me));
        return 0;
}

void destroying(object me, object obj)
{
        destruct(obj);
        return;
}

int accept_fight(object ob)
{
        object me = this_object();
        if( query("family/family_name", ob) != "ؤ��")return 0;
        if( query_temp("fight_ok", ob) != query("beggarlvl", me) )
        {
                command("say���Ǳ���"+chinese_number(query("beggarlvlk", ob))+"������������ս��\n");
                return 0;
        }

        remove_call_out("checking");
        call_out("checking", 1, me, ob);
        delete_temp("fight_ok", ob);
        return 1;
}

int checking(object me, object ob)
{
        object obj;
        int my_max_qi, his_max_qi;

        my_max_qi=query("max_qi", me);
        his_max_qi=query("max_qi", ob);

        if (me->is_fighting())
        {
                call_out("checking",2, me, ob);
                return 1;
        }

        if ( !present(ob, environment()) ) return 1;

        if( (query("qi", me)*100/my_max_qi) <= 50 )
        {
                command("say ��ү��������ã�����������������Ʋ��Ҽ���ȥ��\n");
                message_vision("$N����$nһ���Ʋ���\n", me, ob);
                set_temp("have_cloth", 1, ob);
                obj=new(__DIR__"obj/po-bu");
                obj->move(ob);
                return 1;
        }

        if( (query("qi", ob)*100/his_max_qi)<50 )
        {
                command("say ����" + RANK_D->query_respect(ob) + "��������Ҳ�����������ԼҵĽ�����\n");
                return 1;
        }
        return 1;
}