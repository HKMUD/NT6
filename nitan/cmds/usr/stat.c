// This program is a part of NT MudLIB

#include <ansi.h>

int main(object me, string arg)
{
        mapping buff_list,buff;
        string *lists, name;
        int i,time,warn_time,idx;
        object ob;
        
        mapping cont_list, vend_list;
        string *show_cont, color;
        mixed num;
        
        if( arg && wizardp(me) )
        {
                ob = present(arg, environment(me));
                if (!ob) ob = find_player(arg);
                if (!ob) ob = find_living(arg);
                if (!ob) return notify_fail("ÄãÒª²ì¿´Ë­µÄ×´Ì¬£¿\n");
        } else
                ob = me;
        
        buff_list = query_temp("buff", ob);
        cont_list = ob->query_condition();
        vend_list = query("vendetta", ob);
        
        tell_object(me, WHT"\t¡¡¡¡µ±Ç°×´Ì¬£º\n"NOR);
        tell_object(me, HIR BLK"©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤\n"NOR);

        if( (!mapp(buff_list) || !sizeof(buff_list)) && 
            (!mapp(cont_list) || !sizeof(cont_list)) && 
            (!mapp(vend_list) || !sizeof(vend_list)) ) {
                tell_object(me, "Ã»ÓÐÈÎºÎÒì³£×´Ì¬×÷ÓÃÖÐ¡£\n");
                tell_object(me, HIR BLK"©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤\n"NOR);
                return 1;
        }
        
        seteuid(getuid());
        if( mapp(buff_list) && sizeof(buff_list) )
        {       lists = keys(buff_list);
                for( i=0; i<sizeof(lists); i++ )
                {
                        if( !sscanf(lists[i],"%d", idx) ) continue;
                        buff = query_temp("buff/"+lists[i], ob);
                        color = "";
                        if( buff["att"] == "bless" )
                                color = CYN;
                        if( buff["att"] == "curse" )
                                color = MAG;
        
                        tell_object(me, color+buff["name"]+NOR);
        
                        time = buff["time"];
                        warn_time = time / 40;
                        if( warn_time < 15 )
                                warn_time = 15;
                        if( warn_time > time )
                                warn_time = 3;
                        time = time + query_temp("buff_time/"+lists[i], ob)-time();
                        if( time > warn_time )
                                color = YEL;
                        else
                                color = RED;
                        tell_object(me, color+"\t"+time+NOR" sec\n");
                }
        }
        
        if( mapp(cont_list) && sizeof(cont_list) )
        {
                write(HIR BLK"©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤\n"NOR);
                lists = keys(cont_list);
                num  = values(cont_list);
                for( i=0; i< sizeof(lists);i++ )
                {
                        num = cont_list[lists[i]];
                        if( !stringp(name = CONDITION_D(lists[i])->chinese_name()) )
                                name = CONDITION_D(lists[i])->name();
                        if( stringp(name) &&  num["remain"]>0 )
                        {
                                tell_object (me, sprintf(MAG"%-16s%3d ´Î\n", name, num["remain"]));
                        }       
                } 
        }       
        
        if( mapp(vend_list) && sizeof(vend_list) )
        {
                write(HIR BLK"©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤\n"NOR);
                lists = keys(vend_list);
                for (i=0; i< sizeof(lists);i++)
                {
                        if(lists[i] == "shaolin" && num[i])
                                tell_object (me, sprintf(HIB"%-16s%3d \n", "ÉÙÁÖ·Ë", num[i]));
                        else if(lists[i] == "authority" && num[i])
                                tell_object (me, sprintf(HIB"%-16s%3d \n", "¹Ù·Ë", num[i]));
                        else if(lists[i] == "demon" && num[i])
                                tell_object (me, sprintf(HIB"%-16s%3d \n", "Ä§½Ì·Ë", num[i]));
                                                        
                } 
        }       
         
        tell_object(me, HIR BLK"©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤\n"NOR);


        return 1;
}


int help(object me)
{
write(@HELP

[0;1;37m©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤[0m
[0;1;36mÖ¸Áî¸ñÊ½ :     stat [0m
[0;1;37m©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤[0m   

Õâ¸öÖ¸Áî¿ÉÒÔÈÃÄãÖªµÀÄãÄ¿Ç°ËùÓµÓÐµÄËùÓÐÒì³£×´Ì¬Óë³ÖÐøÊ±¼ä¡£

[0;1;37m©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤[0m  
HELP
    );
    return 1;
}
 
 
