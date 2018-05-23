// This program is a part of NT MudLIB

#include <ansi.h>
#ifndef F_ABILITY;
#define F_ABILITY        "/feature/ability"
#endif

inherit F_ABILITY;
int main(object me, string arg)
{
        string *lists,temp,id;
        int ab;
        int i, a_num, learned_ability;
        object ob;
        string arg1, myclass;

        MYGIFT_D->check_mygift(me, "newbie_mygift/ability");
        if( wizardp(me) )
        {
                if( arg && sscanf(arg, "-%s", id) == 1 )
                {
                        ob = present(id, environment(me));
                        if (!ob) ob = find_player(id);
                        if (!ob) ob = find_living(id);
                        if (!ob) return notify_fail("ÄãÒª²ì¿´Ë­µÄÄÜÁ¦£¿\n");
                } else
                        ob = me;
        } else
                ob = me;

        ab = query("ability", ob);

        learned_ability=query("learned_ability", ob);

        if( arg && ob == me )
        {
                if( !sscanf(arg, "+ %d", a_num) )
                        return notify_fail("Ìá¸ßÄÜÁ¦µÄ¸ñÊ½£ºability + ÄÜÁ¦Ãû³Æ \n");
                        
                if( a_num < 1 || a_num > 25 )
                        return notify_fail("Ã»ÓĞ´Ë´úÂëµÄÄÜÁ¦£¨ÇëÊäÈë1-20£©\n");

                if( a_num < 21 )
                {
                        arg1 = bas_ability[a_num-1];

                        if( !valid_ability_improve(ob, arg1, 0) )
                                return notify_fail("ÄãµÄ¾­ÑéµÈ¼¶»¹²»×ãÒÔÕÆÎÕ¸ü¸ßµÄ¸ÃÏîÄÜÁ¦¡£\n");
                                
                        if( !do_ability_cost(ob, arg1, 0) )
                                return notify_fail("ÄãÃ»ÓĞ×ã¹»µÄÄÜÁ¦µã´¢ĞîÀ´Ìá¸ß´ËÏîÄÜÁ¦¡£\n");
                                
                        improve_ability( ob, arg1, 0);
                        tell_object(ob, "¸ÃµÚ"+ (a_num) + "ÄÜÁ¦Ìá¸ßÍê±Ï¡£\n");
                        return 1;
                }

                if( !stringp(myclass=query("family/family_name", ob)) )
                        return notify_fail("ÄãÎŞÃÅÎŞÅÉ£¬ÈçºÎÄÜ¹»Áì»áÃÅÅÉÎä¹¦µÄ¾«Ëè£¿\n");

                if( !arrayp(fam_ability[myclass]) )
                {
                        return notify_fail("OOPS£¬ÄãËùÔÚµÄÃÅÅÉµÄÌØÉ«»¹Ã»Ğ´ºÃÒ®¡£\n");
                } else
                {
                        arg1 = fam_ability[myclass][a_num-21];
                        if( !valid_ability_improve(ob, arg1, 1) )
                                return notify_fail("ÄãµÄ¾­ÑéµÈ¼¶»¹²»×ãÒÔÕÆÎÕ¸ü¸ßµÄ¸ÃÏîÄÜÁ¦¡£\n");
                                
                        if( !do_ability_cost(ob, arg1, 1) )
                                return notify_fail("ÄãÃ»ÓĞ×ã¹»µÄÄÜÁ¦µã´¢ĞîÀ´Ìá¸ß´ËÏîÄÜÁ¦¡£\n");
                                
                        improve_ability(ob, arg1, 1);
                        tell_object(ob, "¸ÃµÚ"+ (a_num) + "ÄÜÁ¦Ìá¸ßÍê±Ï¡£\n");
                }

                return 1;
        }

        
        write("\n");
        write(HIC    "ĞòºÅ              ¹¦Ğ§                      µÈ¼¶          Éı¼¶µãÊı\n"NOR);
        write(HIG "¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª\n" NOR);
        write(HIC"»ù±¾ÄÜÁ¦½ø½×£º\n\n"NOR);

        for(i=0; i<sizeof(bas_ability); i++)
                write(sprintf(WHT"("WHT"%3d"WHT")", (i+1)) + HIC"\t"+ get_ability_info(ob, bas_ability[i], 0) + NOR);
        write("\n");
     
        write(HIG "¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª\n" NOR);
        write(HIC"ÃÅÅÉÄÜÁ¦½ø½×£º\n\n"NOR);

        if( !stringp(myclass=query("family/family_name", ob)) )       
                write("ÎŞÃÅÎŞÅÉÎŞÌØÉ«¡£\n");
        /*
        else if( query("betrayer", ob) )
                write("ÄãÓĞÅÑÊ¦Ç°¿Æ£¬ÎŞ·¨Áì»áĞÂÃÅÅÉµÄ¾«Ëè¡£\n");
        */
        else if( !arrayp(fam_ability[myclass]) )
                write("OOPS£¬ÄãËùÔÚµÄÃÅÅÉµÄÌØÉ«»¹Ã»Ğ´ºÃÒ®¡£\n");
        else
                for( i=0; i<5; i++ )
                        write(sprintf(WHT"("WHT"%3d"WHT")", (i+21)) + HIC"\t"+ get_ability_info(ob, fam_ability[myclass][i],1) + NOR);

        write("\n");
        write(HIG "¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª\n" NOR);

        write(HIW"ÄãÏÖÔÚ×Ü¹²»ñµÃ "HIC + ab + NOR+HIW" µãÄÜÁ¦¡£\n" NOR);
        write(HIW"ÄãÒÑ¾­ÓÃÈ¥ÁË " RED+ learned_ability +NOR+HIW" µãÄÜÁ¦£¬»¹Ê£ÏÂ "HIG+ (ab-learned_ability) + NOR+HIW" µã¿É¹©·ÖÅä¡£\n" NOR);
        //write(HIG "¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª\n" NOR);
        write("\n\n");
        return 1;
}


int help(object me)
{
write(@HELP

[0;1;37m©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤[0m
[0;1;36mÖ¸Áî¸ñÊ½ :     ability [0m
[0;1;37m©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤[0m

ability         ÈÃÄãÖªµÀÄãÄ¿Ç°ËùÑ§¹ıµÄÒ»ÇĞÄÜÁ¦£¬
ability + n     Ìá¸ßµÚ£îÏîÄÜÁ¦µÄµÈ¼¶¡£

ÄÜÁ¦ÊÇÄàÌ¶ÓÎÏ·ÖĞ³ı¾­ÑéÖµ¡¢¼¼ÄÜÖµÒÔÍâÌá¸ß×ÔÉíµÄÒ»¸öÖØÒªÍ¾¾¶¡£
ÏàÍ¬¾­ÑéµÈ¼¶µÄ£¬ÄÜÁ¦¸ßµÄÈË»áÓĞ¸ü¶àµÄÆøÑª£¬Ôì³É¸ü´óµÄÉËº¦Á¦£¬
»òÕß¿ÉÒÔÓĞ¸ü¸ßµÄÑ§Ï°Ğ§ÂÊ¡£ÈçºÎºÏÀí·ÖÅäÄÜÁ¦µãÊÇ³ÉÎª¸ßÊÖµÄÒ»
´ó»ù±¾ÒªÇó¡£

µ±ÄãµÄÈËÎïµÈ¼¶Éı¼¶¶ø»ñµÃÄÜÁ¦µã£¬¾Í¿ÉÒÔÌá¸ß×ÔÉíµÄ¸÷ÏîÄÜÁ¦ÁË£¡
ÊäÈë£á£â£é£ì£é£ô£ù¾Í¿ÉÒÔ¿´µ½Ò»¸öÇåÎúµÄÁĞ±í¡£·ÖÁ½´óÀà£¬µÚÒ»
Àà¹²ÓĞ£²£°Ïî£¬ËùÓĞÃÅÅÉ¶¼¿ÉÒÔĞŞÏ°£¬´ó¶àÊÇÌá¸ß»ù±¾ÊôĞÔµÄ£»µÚ
¶şÀàÓĞÎåÏî£¬ÊôÓÚÃÅÅÉÎä¹¦µÄ¾«ËèËùÔÚ£¬²»Í¬ÃÅÅÉ¸÷ÓĞÌØÉ«¡£

Ã¿ÏîÄÜÁ¦¹²·ÖÊ®¼¶£¬Ã¿¼¶µÄ¹¦Ğ§¶¼ÓĞÏêÏ¸ËµÃ÷¡£

¸ÃĞŞÏ°Ê²Ã´ÄØ£¿Õâ¾ÍÊÇÓÉ¸÷¸ö²»Í¬ÃÅÅÉµÄÌØµã»òÕß¸öÈËÏ²ºÃËù¾ö¶¨
ÁË¡£Èç¹ûÄãÏëÔÚÕ½¶·ÖĞ³Ö¾Ã£¬¾Í¶àÌá¸ßĞ©Ôö³¤¾«ÆøÉñµÄÄÜÁ¦£¬Èç¹û
ÄãÒªÌá¸ßÉ±ÉËÁ¦£¬¾ÍÌá¸ßĞ©Á¦Á¿¡£¡£¡£¡£



ÄÜÁ¦µãÖØÖÃ£º
    Íæ¼Ò¿ÉÒÔÔÚÄàÌ¶ÉÌ³Ç´¦¹ºÂòÁú¾§¿ÉÓÃÀ´ÖØÖÃÒÑ¾­·ÖÅäºÃµÄÄÜÁ¦µã¡£
ÖØÖÃºó£¬ËùÓĞÄÜÁ¦½ø½×»¹Ô­ÎªÄÜÁ¦µã¡£µÚÒ»´ÎÖØÖÃÄÜÁ¦»áÏûºÄÒ»¸öÁú
¾§£»Ö®ºóÃ¿ÖØÖÃÒ»´Î£¬»áÔÙ¶îÍâÏûºÄÒ»¸öÁú¾§£»µÚ25´Î¼°Ö®ºóµÄÖØÖÃ
½«²»»áÔÙ¶îÍâÔö¼ÓÏûºÄ£¬¹Ì¶¨Ã¿´Î25¸öÁú¾§¡£

[0;1;37m©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤[0m
HELP
    );

        MYGIFT_D->check_mygift(me, "newbie_mygift/ability");
        return 1;
}
