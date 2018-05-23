// Room: /d/shaolin/bagua.h
// Date: YZC 96/01/19

string* dirs = ({
        "¿²", "À¤", "Àë", "Ç¬",
        "ôÞ", "Õð", "Ùã", "¶Ò"
        });

int check_dirs(object me, string dir)
{
        int i, bc, count;
        if (member_array(dir, dirs) != -1)
        {
                bc=query_temp("bagua/count", me);

                switch (dir)
                {
                case "¿²":
                        if (bc == 0 || bc == 13 || bc == 17) {
                                set_temp("bagua/count", bc+1, me);
                                me->receive_damage("jing",50); }                        
                        else
                                delete_temp("bagua/count", me);
                        break;
                case "À¤":
                        delete_temp("bagua/count", me);
                        break;
                case "Àë":
                        if (bc == 1 || bc == 12 ) {
                                set_temp("bagua/count", bc+1, me);
                                addn("neili", -50, me);}
                        else
                                delete_temp("bagua/count", me);
                        break;
                case "Ç¬":
                        if (bc == 8 ) {
                                set_temp("bagua/count", bc+1, me);
                                me->receive_damage("qi", 50); }
                        else
                                delete_temp("bagua/count", me);
                        break;
                case "ôÞ":
                        if (bc == 3 || bc == 4 || bc == 15) {
                                set_temp("bagua/count", bc+1, me);
                                addn("combat_exp", -50, me);}
                        else
                                delete_temp("bagua/count", me);
                        break;
                case "Õð":
                        if (bc == 2 || bc == 7 || bc == 9 ) {
                                set_temp("bagua/count", bc+1, me);
                                me->unconcious(); }
                        else
                                delete_temp("bagua/count", me);
                        break;
                case "Ùã":
                        if (bc == 6 || bc == 11 ) {
                                set_temp("bagua/count", bc+1, me);
                                me->receive_wound("qi", 50); }
                        else
                                delete_temp("bagua/count", me);
                        break;
                case "¶Ò":
                        if (bc == 5 || bc == 10 || bc == 14 || bc == 16) {
                                set_temp("bagua/count", bc+1, me);
                                me->receive_wound("jing", 50); }
                        else
                                delete_temp("bagua/count", me);
                        break;
                default:
                        delete_temp("bagua/count", me);
                        break;
                }

                if (dir == "À¤")
                {
                        delete_temp("bagua", me);
                }
                else
                {
                        count=query_temp("bagua/"+dir, me);
                        count++;
                        set_temp("bagua/"+dir, count, me);
                        if (count > 13)
                        {
                                delete_temp("bagua", me);
                                me->move(__DIR__"jianyu");
                                return (1);
                        }
                }
        }

/*
        write("*"+query_temp("bagua/northwest", me));
        write(""+query_temp("bagua/north", me));
        write(""+query_temp("bagua/northeast", me)+"\n");
        
        write("*"+query_temp("bagua/west", me));
        write(""+query_temp("bagua/count", me));
        write(""+query_temp("bagua/east", me)+"\n");
        
        write("*"+query_temp("bagua/southwest", me));
        write(""+query_temp("bagua/south", me));
        write(""+query_temp("bagua/southeast", me)+"\n");
*/
        return (0);
}