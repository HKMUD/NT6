// This program is a part of NT MudLIB

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        mapping riddle;
        string *list, attr;
        object ob;
        int i,j, *num;

        if( wizardp(me) && stringp(arg) )       
        {
                ob = LOGIN_D->find_body(arg);
                if (!ob) return notify_fail("ﬂ◊... ”–’‚∏ˆ»À¬?\n");
        } else
                ob = me;

        riddle = query("riddle", ob);    
        
        write(WHT"\t°°°°                " + ob->name()+ "’˝‘⁄Ω‚µƒ√’Ã‚\n"NOR);
        write(HIR BLK"©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§\n"NOR);

        if( !riddle )   write (HIR "Œﬁ\n"NOR);
        else
        {
                list = keys(riddle);
                i = 0;                                  // deal with the problem of setting riddle=0
                for( j=0; j<sizeof(list); j++ )
                {
                        if (riddle[list[j]])
                        {
                                if(i%5!=4) 
                                        write(sprintf(YEL"%-16s"NOR,list[j]));
                                else 
                                        write(YEL + list[j] + "\n"NOR);   
                                i++;
                        }
                }
        }
        write(HIR BLK"\n©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§\n"NOR);
    
 
        riddle = query("m_success", ob);

        write(WHT"\t°°°°            "+ob->name()+ "“—æ≠Ω‚ø™µƒ√’Ã‚\n"NOR);
        write(HIR BLK"©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§\n"NOR);

        if( !riddle )        write (HIR "Œﬁ\n"NOR,16);
        else
        {
                list = keys(riddle);
                for( i=0; i<sizeof(list); i++ )
                {
                        if(i%5!=4) 
                                write(sprintf(CYN"%-16s"NOR,list[i]));
                        else
                                write(CYN + list[i] + "\n"NOR);   
                }
        }
        write(HIR BLK"\n©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§\n"NOR);


        riddle = query("imbue", ob);

        write(WHT"\t°°°°            " + ob->name()+ "Ω‚√’‘ˆº”µƒ Ù–‘\n"NOR);
        write(HIR BLK"©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§\n"NOR);

        if( !riddle )        write (HIR "Œﬁ\n"NOR);
        else
        {
                list = keys(riddle);
                num = values(riddle);
                for( i=0; i<sizeof(list); i++ )
                {
                        switch (list[i])
                        {
                        case "dex": attr = "√ÙΩ›"; break;
                        case "int": attr = "≤≈÷«"; break;
                        case "con": attr = "ÃÂ÷ "; break;
                        case "str": attr = "¡¶¡ø"; break;
                        case "cps": attr = "∂®¡¶"; break;
                        case "kar": attr = "‘À∆¯"; break;
                        default: attr = "";
                        }           
            
                        if (sizeof (attr)>0)
                                write(HIR + attr +" +" + num[i] + "\t"NOR);   
                }
        }
        write(HIR BLK"\n©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§\n"NOR);

        return 1;
}
int help(object me)
{
        write(@HELP

[0;1;37m©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§[0m
[0;1;36m÷∏¡Ó∏Ò Ω :     riddle            [0m
[0;1;37m©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§[0m   

’‚∏ˆ÷∏¡Óø…“‘»√ƒ„÷™µ¿ƒ„ƒø«∞“—æ≠Ω‚ø™µƒ√’Ã‚£¨“‘º∞“ÚΩ‚√‹‘ˆº”µƒ Ù–‘

[0;1;37m©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§©§[0m  
HELP
        );
        return 1;
}


