/*********************************************************
   ±¾ÎÄ¼şÖ»±» hj_room1.c Ê¹ÓÃ¡£

   ±¾·¿¼äÃèÊö´øÓĞÍ¼Æ¬£¬½¨ÒéĞ§¹û£¨¼´ÄÎºÎËùÊ¹ÓÃÉèÖÃ£©£º
   zmud4.62 32bit ºº»¯°æ£¬ ËÎÌå£¬Ğ¡ËÄ(12)»òĞ¡Îå(10) ²é¿´£¬
   ¿ÉµÃ×î¼ÑĞ§¹û¡£

   ±¾·¿¼äÖ§³ÖÁ½¸ö JOB¡£

   ÆäÒ»£¬É±ÁË¸÷×åµÄ×å³¤Ê±£¬¿ÉËæ»úµÃµ½¸Ã×åµÄÈ¨ÕÈ£¬ËÑ¼¯ËùÓĞ
         ×åµÄÈ¨ÕÈ£¬ÔÙ»ØÀ´ÕâÀï·¢´ô JOB1_NEED_IDLE Ãë£¬¼´¿É
         µÃµ½´óÁ¿½±Àø¡£

   Æä¶ş£¬ÔÚ´Ë·¢´ô JOB2_NEED_IDLE Ãë£¬¼´µÃµ½ ÓÄÁéÎäÊ¿ JOB¡£
         É±ÁËËü¿ÉÒÔµÃµ½¶îÍâµÄ½±Àø¡£Èô±»ÆäËûÈËÉ±È¥£¬ÓëÆÕÍ¨
         ¸÷×åµÄNPCĞ§¹ûÒ»Ñù¡£±¾ÈËÉ±ÁËÓÄÁé×åÎäÊ¿Ê±£¬¿ÉµÃµ½
         ¼¼ÄÜÌáÉıÓëÓÎÏ·µÃ·Ö¡£

   JOB1 µÄ·¢´ôÉúĞ§Ê±¼ä±ØĞë±È JOB2 µÄ¶Ì¡£¾ßÌå¿´ÏÂ±ßµÄÉèÖÃ¡£

   ÁíÍâ£¬ÔÚ´Ë·¿¼äÍ£Áô£¬»áËæ»úËğÊ§ hp £¬ÖÁËÀ·½Ğİ£¡ 

   int query_idle( object target ) ·µ»Ø·¢´ôÖµ :)

   naihe 23:43 03-10-20
**********************************************************/


#include    "npc_obj/hj_settings/room_amount_hj.h"


#define        JOB1_NEED_IDLE       20
#define        JOB2_NEED_IDLE       31
#define        JOB1_AWARD           800
#define        JOB2_AWARD           80
#define        JOB2_AWARD_SKILLS    2

void full_all( object me );

int me_ok( object me )
{
    if( !me || !environment(me) || environment(me) != this_object()
       || query_temp("huanjing", me) != "start" || query_temp("hj_hp", me)<1 )
        return 0;

    return 1;
}


void create()
{
    set("j1_time", JOB1_NEED_IDLE );
    set("j2_time", JOB2_NEED_IDLE );

    set("room_mark",mark);
    set("short",MAG"»Ã¾³"NOR+GRN"¡¤ÃÔÊ§Ö®±¦ÎïÒşÄäÖ®ÁÖ"NOR);

    set("long", "Äã¸Õ×ß¹ıÀ´£¬È´·¢ÏÖÕâÀïÊÇÒ»Ğ¡·½Ë®Ì¶£¬Ë®Ì¶Ö®Ë®ÇåÓÄÆ½¾²£¬Ì¶±ßÁ¢×ÅÒ»¸ö
Ğ¡Í¤(ting)¡£ÄãÖ»¼ûÔÂÉ«Çå·ç£¬ôÔ¹âÉÁË¸£¬¶ËµÄÊÇÊæĞÄ³©»³£¬ÇåÑÅÎŞ±È¡£ÄãËÆºõ
ÒÑÍüÁËÃÜÁÖÖĞµÄĞ×É±Ë»º°£¬¸Õ²ÅµÄ½ôÆÈ¾ÍËÆÒÑÀëÄã¶øÈ¥¡£
                                                           [1;33m¡ñ[37;0m       
                                                                    
                                            [1;32m.. .[37;0m      [1;34mI[37;0m       [1;32m..[37;0m    
                                            [1;32m..[37;0m      [1;34m,'.`.[37;0m           
                                              [1;34m.__,-'.:::.`-.__,[37;0m  [1;32m.[37;0m  
                                               [1;34m~-------------~[37;0m      ");

    // string to long, Òª·Ö¿ªÀ´ set, 5555555
    set("long", query("long") + "
                                                 [1;31m_|=|___|=|_[37;0m        
                                           [1;34m.__,-'.:::::::::.`-.__,[37;0m  
                               [37m[37;0m             [1;34m~-------------------~[37;0m   
                               [37m |[37;0m              [1;31m_|_|_|___|_|_|_[37;0m      
                               [37m###################################[37;0m  
[42m     [30m¨y¨z¨{¨|¨}¨~¨}¨|¨{¨|¨}¨|¨{¨z¨y¨x¨y¨z¨{¨|¨}¨~¨€¨~¨}¨|¨{¨z¨y¨x   [37;0m
        \n");

    // ÄÎºÎ×¢£º´ËÍ¼¸´ÖÆ×Ô¹ş¹¤´óBBS£¬ÑÕÉ«ÉèÖÃÓëÆä²¢ÎŞ¶şÖÂ¡£Í¤Íâ°¶±ßµÄÒ»ÊúÊÇÎÒ¼ÓÉÏµÄ£¬
    // ÎªÁËÒ»Ğ©ÆäËûµÄĞ§¹û¡£
    // Íü¼ÇÔ­×÷ÊÇË­ÁË£¬ÔÚ HJ ºÁÎŞÉÌÒµÓÃÍ¾Ö®Ê±£¬Õâ¸öÍ¼½«±£Áô¡£
    // ±¾Í¼ÒàÊÇÄÎºÎµÄµ¥»úÉÏµÄ welcome Í¼£¬HOHO¡£¿ÉÏ§ÎÒ¶Ô»­Õâ¸ö¶«Î÷
    // ºÁÎŞ¸Ğ¾õ£¬¿´Õâ»­µÄÊÇ¶àÃÀ¡­¡­½¨ÒéĞ§¹û£º
    // zmud4.62 32bit ºº»¯°æ£¬ ËÎÌå£¬Ğ¡ËÄ£¨12£© ²é¿´£¬¿ÉµÃ×î¼ÑĞ§¹û¡£
    // naihe 23:25 03-10-20

    set("item_desc",([
        "Í¤"   : "ÕâÊÇÒ»¸öĞ¡Í¤×Ó£¬¾«ÖÂ·çÑÅ¡£Í¤Íâ°¶±ßÁ¢×ÅÒ»±úÈ¨ÕÈ(zhang)£¬Ê®·Ö´Ö´ó¡£\n",
        "Ğ¡Í¤" : "ÕâÊÇÒ»¸öĞ¡Í¤×Ó£¬¾«ÖÂ·çÑÅ¡£Í¤Íâ°¶±ßÁ¢×ÅÒ»±úÈ¨ÕÈ(zhang)£¬Ê®·Ö´Ö´ó¡£\n",
        "ting" : "ÕâÊÇÒ»¸öĞ¡Í¤×Ó£¬¾«ÖÂ·çÑÅ¡£Í¤Íâ°¶±ßÁ¢×ÅÒ»±úÈ¨ÕÈ(zhang)£¬Ê®·Ö´Ö´ó¡£\n",
        "ÕÈ"   : "ÕâÊÇÒ»±úÈ¨ÕÈ£¬ËÆºõÉ¢·¢×ÅÒ»¹É¹îÒìµÄÆøÏ¢¡£ËüÉÏ±ß¿ÌÓĞÒ»Ğ©Ğ¡×Ö(zi)¡£\n",
        "È¨ÕÈ" : "ÕâÊÇÒ»±úÈ¨ÕÈ£¬ËÆºõÉ¢·¢×ÅÒ»¹É¹îÒìµÄÆøÏ¢¡£ËüÉÏ±ß¿ÌÓĞÒ»Ğ©Ğ¡×Ö(zi)¡£\n",
        "zhang": "ÕâÊÇÒ»±úÈ¨ÕÈ£¬ËÆºõÉ¢·¢×ÅÒ»¹É¹îÒìµÄÆøÏ¢¡£ËüÉÏ±ß¿ÌÓĞÒ»Ğ©Ğ¡×Ö(zi)¡£\n",
        "×Ö"   : "¡¸ÓÄÁéÖ®×åÈ¨ÕÈ -- ÓÄÁéµÄÎäÊ¿½«ÓÉ´Ë½µÁÙ£¬°µÒ¹µÄÃÜÁÖ¼´½«Õ¹¿ª¼¤Õ½¡¹\n",
        "Ğ¡×Ö" : "¡¸ÓÄÁéÖ®×åÈ¨ÕÈ -- ÓÄÁéµÄÎäÊ¿½«ÓÉ´Ë½µÁÙ£¬°µÒ¹µÄÃÜÁÖ¼´½«Õ¹¿ª¼¤Õ½¡¹\n",
        "zi"   : "¡¸ÓÄÁéÖ®×åÈ¨ÕÈ -- ÓÄÁéµÄÎäÊ¿½«ÓÉ´Ë½µÁÙ£¬°µÒ¹µÄÃÜÁÖ¼´½«Õ¹¿ª¼¤Õ½¡¹\n",
        ]) );

    set("no_fight", "1");
    set("no_steal", "1");
    set("no_sleep_room", "1");
    set("invalid_startroom",1);

    set("exits",([
        "east" : __DIR__"hj_room2", 
        "south" : __DIR__"hj_room11",
        "southeast" : __DIR__"hj_room12",
        ]) );

    setup();
}

void init()
{
    // ËùÓĞµÄ¹²ÓĞ¶¯×÷(¼´ all_room_info_hj.h ¼° 1_room_info_special.h ¹²ÓĞ)
#include "all_common_init.h"

    // Éı¼¶¹¦ÄÜ£¡£¡£¡
    add_action("do_lvup", ({ "levelup", "lvup" }) );
    // npc ½øÈë´ËµØ£¬²»¹ÜÊÇÊ²Ã´ÈË£¬Á¢¿ÌÀë¿ª
    if( query("hj_game/npc", me) )
        call_out("npc_out", 1, me);
    // Æô¶¯¼ì²â me µÄ³ÌĞò
    if( query_temp("huanjing", me) == "start" )
        call_out("start_check",2,me,query("id", me));
}

// ËùÓĞµÄ¹²ÓĞº¯Êı(¼´ all_room_info_hj.h ¼° 1_room_info_special.h ¹²ÓĞ)
#include "all_common_func.h"

void npc_out( object me )
{
    object outroom;
    int or;

    if( !me ) return;
    if( !environment(me) || environment(me) != this_object() )
        return;

    message_vision("$N×óÓÒ¿´ÁËÒ»ÏÂ£¬¼±¼±Ã¦Ã¦µØÀë¿ªÁË¡£\n", me);
    if( random(2) ) or = 2;
    else if( random(2) ) or = 11;
    else or = 12;

    outroom = find_object( __DIR__"hj_room"+or );
    if( !outroom ) outroom = load_object( __DIR__"hj_room" + or );
    me->move( outroom );
    message_vision("$N¼±¼±Ã¦Ã¦µØ×ßÁË¹ıÀ´¡£\n", me);
}

void start_check( object me, string id )
{
    if( !me_ok(me) )
    {
        delete("checking_job1_"+ id );
        delete("checking_job2_"+ id );
        delete("checking_lost_hp_"+ id );
        return;
    }

    // ¿ªÊ¼Ö´ĞĞ´ËÈËµÄ·¢´ôÅĞ¶Ï¼°¿ÛÑª³ÌĞò

    // ²¢Î´ÔÚÖ´ĞĞ checking ´ËÈËµÄ job1 º¯Êı£¬¿ÉÒÔ½øĞĞ
    if( !query("checking_job1_"+ id ) )
    {
        set("checking_job1_"+ id, 1);
        call_out( "checking_job1", 5 + random(6), me, id);
    }
    // Í¬ÉÏ
    if( !query("checking_job2_"+ id ) )
    {
        if( !query_temp("hj_youling_job", me) )
        {
            set("checking_job2_"+id, 1);
            call_out( "checking_job2", 5 + random(6) , me, id );
        }
    }
    // Í¬ÉÏ¼°ÉÏÉÏ
    if( !query("checking_lost_hp_"+id) )
    {
        set("checking_lost_hp_"+ id, 1);
        call_out( "lost_hp", 1, me, id );
    }
}

// ÔÚÕâ¸öµØµãÍ£Áô£¬»á²»¶ÏµØµôHP£¬Ö±µ½ËÀÎªÖ¹¡£
void lost_hp( object me, string id )
{
    if( !me || !me_ok(me) )
    {
        delete("checking_lost_hp_"+ id );
        return;
    }

    // Ëæ»ú lost hp.
    if( random(3) )
    {
        call_out("lost_hp", 5+random(6), me, id );
        return;
    }

    write(HIB"ÄãºöµØ¸Ğµ½Ò»ÕóÇ¿ÁÒµÄ¹îÒìÆøÏ¢²»Öª´ÓÄÄ¶ùÉ¢·¢³öÀ´£¬Ö»¾õµÃĞÄ·³ÆøÃÆ£¬¾¹ËÆÁé»êÕıÔÚÓë×Ô¼ºÔ¶ÀëÒ»°ã£¡\n"NOR);
    addn_temp("hj_hp", -(5+random(16)), me);
    call_out("lost_hp", 5+random(6), me, id);
}

// ÕâÊÇËÑ¼¯¸÷×åÈ¨ÕÈµÄ JOB¡£
void checking_job1( object me, string id )
{
    string *job1_ids;
    string msg;
    object *job1_obj_list, temp;
    int i, award_score;

    // ¶ÏÏßµÄÍæ¼Òµ÷ÓÃ query_idle() »á³ö bug
    if( !me || !me_ok(me) || !interactive(me) )
    {
        delete("checking_job1_"+ id );
        return;
    }
    if( query_idle(me) < JOB1_NEED_IDLE )
    {
        call_out("checking_job1", 5+random(6), me, id);
        return;
    }

    // ·¢´ôÊ±¼äµ½
    job1_ids = ({ "manye quanzhang", "mengli quanzhang", "aiyao quanzhang",
            "shanguai quanzhang", "juren quanzhang", });

    job1_obj_list = ({ });

    // ²é¿´ÆäÊÇ·ñÓĞÈ«Ì×È¨ÕÈ
    for( i=0;i<sizeof( job1_ids ); i++ )
    {
        temp = present( job1_ids[i] , me );

        // ·¢ÏÖÈÎºÎÒ»¸ö²»¹»£¬ÍË³ö¼ì²â³ÌĞò¡£
        if( !temp )
        {
            delete("checking_job1_" + id );
            return;
        }
        job1_obj_list += ({ temp });
    }
    // ºÃµÄ£¡»ñµÃ½±Àø¡£
    message_vision( HIY"$N"HIY"ÕıÔÚÄıÉñÏ¸Ë¼£¬ºöµØ×Ô¼ºËù´øÈ¨ÕÈ¶¼·¢³öÁËÒ«ÑÛ¹âÃ¢£¬²»Ô¼¶øÍ¬µØÖ¸ÏòÓÄÁé×åµÄÈ¨ÕÈ£¡\n"NOR,me);
    msg = HIY + "";
    // È¨ÕÈÃ»ÓĞÑÕÉ«µÄÉèÖÃ£¬ËùÒÔ¶ÙºÅÕâÀïÒ²²»ÓÃĞ´ÑÕÉ«ÁË¡£
    for( i=0; i<sizeof( job1_obj_list ); i++ )
    {
        if( i == 0 )
            msg += job1_obj_list[i] -> name(1);
        else msg += sprintf( "¡¢%s", job1_obj_list[i] -> name(1) );
        destruct( job1_obj_list[i] );
    }

    message_vision( msg +"¡­¡­\nÖ»¼û¸÷¸öÈ¨ÕÈ½ÓÁ¬·É³ö£¬ÓÌÈç·É¶êÆË»ğ°ã×²ÏòÓÄÁé×åÈ¨ÕÈ£¬¾¹È«²¿ÏûÊ§²»¼ûÁË£¡\n$N"HIY"ÑÛ¿´´Ë¾°£¬ÆæÒìÄªÃû£¬Ö»¾ªµÃËµ²»³ö»°À´¡£\n"NOR, me );

    delete("checking_job1_"+ id );
    award_score = JOB1_AWARD + random( JOB1_AWARD / 10 );
    addn_temp("hj_score", award_score, me);
    tell_object( me, HIR"ÓÎÏ·ÌáÊ¾£ºÄãµÄµÃ·ÖÔö¼ÓÁË "+award_score+" µã£¡\n"NOR );
    return;
}

// ÕâÊÇÈ¥É±ÓÄÁé×åÎäÊ¿µÄJOB¡£
void checking_job2( object me, string id )
{
    object kill_npc, rooms, ling;
    int random_room, yeah = 0;

    // Èç¹û me ²»·ûºÏÌõ¼ş£¬»òÕß me ÒÑ¾­ÓĞ JOB ÔÚÉíÁË£¬½áÊø¼ì²âº¯Êı¡£
    // Õâ¸ö JOB ±ê¼ÇÊÇ object ĞÍµÄ£¬µ±NPC±»±ğÈËÉ±ÁË£¬JOB»á×Ô¶¯½áÊø :)
    if( !me || !me_ok(me) || query_temp("hj_youling_job", me) || !interactive(me) )
    {
        delete("checking_job2_"+ id );
        return;
    }
    // ÕâÊÇÒ»¸öÌØ±ğÅĞ¶Ï¡£µ±Íæ¼Ò³É¹¦´Ó³¼Ãñ´¦µÃµ½±¦ÎïµÄÖØÒª×éºÏ²¿·ÖÊ±£¬
    // ½«¿ÉµÃµ½Ò»¸ö¡°ÓÄÁéÖ®Áî¡±£¬ÓĞ´ËÁîÔÚÉíÕß£¬½«¿ÉÒÔ¼Ó±¶ËÙ¶ÈµÃµ½ÎäÊ¿JOB¡£
    // ´ËÁî±ØĞëÊÇÊôÓÚ¸ÃÍæ¼ÒµÄ¡£ÈçÍæ¼ÒÉíÉÏĞ¯´ø¹ı¶àµÄÁî¶øÓÖ·¢ÉúÁîÅÆÎ´Ö´ĞĞ
    // ×Ô»Ù³ÌĞòµÄÇé¿ö£¬Ôò»á²úÉúÁîÅÆÎŞĞ§µÄ·ÇBUGÀà´íÎó¡£
    ling = present( "youling ling", me);
    if( ling && query("my_master", ling) == me
         && query("this_time_mark", ling) == query_temp("this_time_mark", me) )
    {
        yeah = 1;
        if( query_idle(me) < JOB2_NEED_IDLE/2 )
        {
            call_out("checking_job2", 5+random(6), me, id);
            return;
        }
    }
    if( !yeah && query_idle(me) < JOB2_NEED_IDLE )
    {
        call_out("checking_job2", 5+random(6), me, id);
        return;
    }

    if( yeah && ling )
        message_vision( HIB"$N"HIB"ÉíÉÏµÄ$n"HIB"ºöÈ»·¢³öÒ»Õó¹í÷ÈÖ®Éù£¬ÖÜÎ§ÖèµØÀ÷ÉùËÄÆğ£¬ËÆÊÇÏìÆğÁËÒ»Æ¬ºôÓ¦£¡\n"NOR, me, ling);

    // ³É¹¦£¡·¢·ÅJOB¡£
    delete("checking_job2_"+id);
    kill_npc = new( __DIR__"npc_obj/hj_npc_kill" );
    kill_npc->setme( 88 );  // ÌØÊâµÄ set.

    set("job_master_obj", me, kill_npc);
    set("job_award_score", JOB2_AWARD*9/10+random(JOB2_AWARD/5), kill_npc);
    switch( random(10) )
    {
        // Õâ¸öÊÇËæ»ú½±Àø me µÄÄ³Ïî¼¼ÄÜÌáÉı¶àÉÙ¼¶
        case 0..1 :set("job_award_skills", JOB2_AWARD_SKILLS + random(2), kill_npc );
            break;
        // »òÕß½±ÀøÒ»µãÁ¦Á¿£¬ÒòÎªÁ¦Á¿ÖµºÜÖØÒª£¬ËùÒÔ²»¿É¶à½±
        case 8 :set("job_award_power", 1, kill_npc );
            break;
    }
    // ÉèÖÃÒ»Ğ©ÃèÊö£¬²¢ÇÒÒ²¿ÉÒÔÒÔ´ËÎªÒÀ¾İ£¬ÅĞ¶ÏÊÇ·ñ×Ô¼ºµÄNPC£¬²»Òª°×´ò£¨ºÜÄÑ´ò£¡£©¡£
    set("gender",query("gender",  me), kill_npc);
    set("long",query("long",  kill_npc)+"ÕâÈË¿´ÆğÀ´¾¹Óë"+query("name", me)+"Ò»Ä£Ò»Ñù£¡\n", kill_npc);
    set("per",query("per",  me), kill_npc);

    random_room = 2 + random( HJ_ROOM_AMOUNT -1 );
    rooms = find_object( __DIR__"hj_room" + random_room );
    if( !rooms ) rooms = load_object( __DIR__"hj_room" + random_room );
    kill_npc->move( rooms );
    message_vision( BLU"ºöµØÒ»ÕóÒõ·çÂÓÆğ£¬$N"NOR+BLU"ÖèÈ»ÏÖÉí£¬¹îÒìÖ®¼«¡£\n"NOR, kill_npc);
    // JOB ½±ÀøÓÉ¸Ã npc ÊµÏÖ¡£

    set_temp("hj_youling_job", kill_npc, me);
    // ¸ø me ÉèÖÃ±ê¼Ç£¬²»»á¼ÌĞø·¢·ÅJOB¡£
    // ÒÔ object ĞÍÀ´ÉèÖÃJOB£¬µ±¸ÃNPCËÀµô(destruct)Ê±£¬JOB×ÔÈ»½áÊø¡£

    message_vision( BLU"\n$N"NOR+BLU"ÕıÔÚÄıÉñÏ¸Ë¼£¬ºöÈ»¼äÖ»ÌıµÃÓÄÁéÖ®×åÈ¨ÕÈ·¢³öÒ»ÕóèÉ½ĞÖ®Éù£¡\n"
        "Ò»¸öÄ£ºıµÄÓ°×Ó´ÓÈ¨ÕÈÖĞ¼¤Éä¶ø³ö£¬¾¹È»´©¹ı$N"NOR+BLU"µÄÉíÌå£¬ÍùÍâ±ß¼±³å¶øÈ¥£¡\n"
        "$N"NOR+BLU"¾ª»êÎ´¶¨£¬ËÆÒÑ´ô×¡£¬»Ğã±ÖĞ¼ûµÃÓ°×ÓËÆºõÊÇÍù "HIR"\""+random_room+"\""NOR+BLU" È¥ÁË¡£\n\n"NOR, me);
    me->start_busy(3);
    // ok,finish.
}

// ·Ç³£ÄÑµÄÉı¼¶ÖÆ¶È
// naihe 05-9-3 18:18 °´£ººÃÏóÓÖ²»ÊÇºÜÄÑ¡£ÎÒ5Ìì³åµ½ lv6, lv6 ÊÇÊ²Ã´¸ÅÄî£¿¡­¡­ºÜÇ¿º·ÁË
// Ìá¸ßÉı¼¶ÄÑ¶È¡£
int do_lvup(string arg)
{
    object me = this_player(), rooms;
    int next_lv, score_need, skills_need, power_need, f_sks_need, y_sks_need, l_sks_need, d_sks_need, heal_sks_need, dh_sks_need, fh_sks_need, gs_sks_need;
    string msg;

    int t;

    if( !me_ok(me) ) return 0;

    if( me->is_busy() || query_temp("hj_need_waiting", me) )
        return notify_fail("Äã»¹Ã¦×ÅÄØ£¬ÄÇÃ´ÖØÒªµÄÊÂÇé»¹ÊÇµÈÓĞ¿ÕµÄÊ±ºòÔÙËµ°É¡£\n");

    next_lv=query("huanjing2003/lv", me)+1;
    if( next_lv > 9 ) return notify_fail("ÄãÏÖÔÚÒÑ¾­ÊÇ×î¸ßµÄµÈ¼¶ÁË£¡\n");

    rooms = find_object( __DIR__"room_door_hj" );
    if( !rooms ) rooms = load_object( __DIR__"room_door_hj" );
    if( !rooms ) return notify_fail("ÏÖÔÚË­¶¼²»ÄÜÉı¼¶¡£\n");

    switch( next_lv )
    {
// ######################################################
// ´ËÊ±£¬ÎŞÈÎºÎ×Ô¶¯±£³Ö£¬ËùÒÔÈİÒ×Éı

        case 1: msg = "1001µãµÃ·Ö"; score_need = 1001;
            break;


// ######################################################
// ´ËÊ±£¬sks ÒÑ¿É×Ô¶¯±£³Ö 5 lv
// ÔçÆÚµÄ power ºÜÈİÒ×ÉıÉÏÈ¥£¬ËùÒÔ power Æğµã¶¨Îª21µã¡£

        case 2: msg = "1001µãµÃ·Ö£¬·ç¡¢Óê¡¢À×¡¢µç¼¼ÄÜ¸÷31¼¶£¬21µãÁ¦Á¿";
                score_need = 1001; t = 31; power_need = 21;

                f_sks_need=t;y_sks_need=t;l_sks_need=t;d_sks_need=t;
            break;


// ######################################################
// ´ËÊ±£¬sks ÒÑ¿É×Ô¶¯±£³Ö 10 lv

        case 3: msg = "1001µãµÃ·Ö£¬·ç¡¢Óê¡¢À×¡¢µç¼¼ÄÜ¸÷41¼¶£¬26µãÁ¦Á¿";
                score_need = 1001; t = 41; power_need = 26;

                f_sks_need=t;y_sks_need=t;l_sks_need=t;d_sks_need=t;
            break;


// ######################################################
// ´ËÊ±£¬sks ÒÑ¿É×Ô¶¯±£³Ö 15 lv
// ÕâÊÇÒ»¸ö¹Ø¼üµã£¬ÉıÁË±¾¼¶ºó£¬sks lv ¿É±£³Ö 20£¬¼´¿ÉÒÔ
// Ê¹ÓÃ yun ÌØÊâ¼¼¡£ËùÒÔ£¬ÒªÇó¸ßĞ©

        case 4: msg = "999 µãµÃ·Ö£¬·ç¡¢Óê¡¢À×¡¢µç¡¢»Ö¸´¡¢¶á»ê¡¢·É»ğ¡¢"
                        "¹öÊ¯¼¼ÄÜ¸÷41¼¶£¬31µãÁ¦Á¿";
                score_need = 999; t = 41; power_need = 31;

                f_sks_need=t;y_sks_need=t;l_sks_need=t;d_sks_need=t;
                heal_sks_need=t;dh_sks_need=t;fh_sks_need=t;gs_sks_need=t;
            break;


// ######################################################
// ´ËÊ±£¬sks ÒÑ¿É×Ô¶¯±£³Ö 20 lv

        case 5: msg = "1001µãµÃ·Ö£¬·ç¡¢Óê¡¢À×¡¢µç¡¢»Ö¸´¡¢¶á»ê¡¢·É»ğ¡¢"
                        "¹öÊ¯¼¼ÄÜ¸÷51¼¶£¬31µãÁ¦Á¿";
                score_need = 1001; t = 51; power_need = 31;

                f_sks_need=t;y_sks_need=t;l_sks_need=t;d_sks_need=t;
                heal_sks_need=t;dh_sks_need=t;fh_sks_need=t;gs_sks_need=t;
            break;


// ######################################################
// ´ËÊ±£¬sks ÒÑ¿É×Ô¶¯±£³Ö 25 lv
// Õâ¸öÉı¼¶Ìõ¼şºÍ lv 5 Ò»Ñù£¬µ«ÊÇÏà¶ÔÈİÒ×Ğ©ÁË

        case 6: msg = "1001µãµÃ·Ö£¬·ç¡¢Óê¡¢À×¡¢µç¡¢»Ö¸´¡¢¶á»ê¡¢·É»ğ¡¢"
                        "¹öÊ¯¼¼ÄÜ¸÷51¼¶£¬31µãÁ¦Á¿";
                score_need = 1001; t = 51; power_need = 31;

                f_sks_need=t;y_sks_need=t;l_sks_need=t;d_sks_need=t;
                heal_sks_need=t;dh_sks_need=t;fh_sks_need=t;gs_sks_need=t;
            break;


// ######################################################
// ´ËÊ±£¬sks ÒÑ¿É×Ô¶¯±£³Ö 30 lv

        case 7: msg = "1001µãµÃ·Ö£¬·ç¡¢Óê¡¢À×¡¢µç¡¢»Ö¸´¡¢¶á»ê¡¢·É»ğ¡¢"
                        "¹öÊ¯¼¼ÄÜ¸÷61¼¶£¬36µãÁ¦Á¿";
                score_need = 1001; t = 61; power_need = 36;

                f_sks_need=t;y_sks_need=t;l_sks_need=t;d_sks_need=t;
                heal_sks_need=t;dh_sks_need=t;fh_sks_need=t;gs_sks_need=t;
            break;


// ######################################################
// ´ËÊ±£¬sks ÒÑ¿É×Ô¶¯±£³Ö 35 lv
// ÕâÓÖÊÇÒ»¸ö¹Ø¼üµã£¬up lv ºó£¬½«¿É±£³Ö sks 40, ¼´¿ÉÒÔ pfm.
// ÌØ±ğÄÑ£¡
        case 8:msg = "88µãµÃ·Ö£¬·ç¡¢Óê¡¢À×¡¢µç¡¢»Ö¸´¡¢¶á»ê¡¢·É»ğ¡¢"
                        "¹öÊ¯¼¼ÄÜ¸÷88¼¶£¬41µãÁ¦Á¿";
                score_need = 88; t = 88; power_need = 41;

                f_sks_need=t;y_sks_need=t;l_sks_need=t;d_sks_need=t;
                heal_sks_need=t;dh_sks_need=t;fh_sks_need=t;gs_sks_need=t;
            break;


// ######################################################
// ´ËÊ±£¬sks ÒÑ¿É×Ô¶¯±£³Ö 40 lv
// ÕâÊÇ×îºóµÄÒ»¼¶£¬Èç¹ûÓĞÈËÅäºÏ£¬ÄÇµ¹²»ËãÍ¦ÄÑ :)
// ÒòÎªÁ¦Á¿µÄÒªÇó½µµÍÁË
// sks µÄÒªÇóºÜÈİÒ×´ïµ½µÄ£¬hoho

        case 9:msg = "1888µãµÃ·Ö£¬·ç¡¢Óê¡¢À×¡¢µç¡¢»Ö¸´¡¢¶á»ê¡¢·É»ğ¡¢"
                        "¹öÊ¯¼¼ÄÜ¸÷66¼¶£¬31µãÁ¦Á¿£¬\n"
                "²¢ÇÒÔÚÉı¼¶ºó£¬ÄãËùÓĞµÄ¼¼ÄÜ¡¢Á¦Á¿¶¼½«±»Çå³ı£¡";
                score_need = 1888; t = 66; power_need = 31;

                f_sks_need=t;y_sks_need=t;l_sks_need=t;d_sks_need=t;
                heal_sks_need=t;dh_sks_need=t;fh_sks_need=t;gs_sks_need=t;
            break;
    }

// ######################################################
// ######################################################
// ######################################################


    write( "Äã½«Éıµ½µÚ "+next_lv+" ¼¶£¬ĞèÒª "+msg+" ¡£\n");
    if( !arg || arg != "now")
        return notify_fail("ÈçÈ·ÊµÏëÉı¼¶£¬ÇëÊäÈë <levelup now> ¡£Éı¼¶ºó£¬½«»á¶ÔÓ¦ËùĞèÌõ¼ş¶ÔÄãµÄ¸÷ÏîÄÜÁ¦½øĞĞÏ÷¼õ¡£\n");

// ¿ªÊ¼Éı¼¶

    if( score_need && query_temp("hj_score", me)<score_need )
        return notify_fail("ÄãÃ»ÓĞ×ã¹»µÄµÃ·Ö¡£\n");

    if( power_need && query_temp("hj_game_mepower", me)<power_need )
        return notify_fail("ÄãÃ»ÓĞ×ã¹»µÄÁ¦Á¿¡£\n");

    if( f_sks_need && (!query_temp("hj_game_skills/hfzj", me )
               || query_temp("hj_game_damages/hfzj", me)<f_sks_need) )
        return notify_fail("ÄãµÄ¡¸ºô·çÖ®¼¼¡¹µÈ¼¶²»¹»¡£\n");

    if( y_sks_need && (!query_temp("hj_game_skills/hyzj", me )
               || query_temp("hj_game_damages/hyzj", me)<y_sks_need) )
        return notify_fail("ÄãµÄ¡¸»½ÓêÖ®¼¼¡¹µÈ¼¶²»¹»¡£\n");

    if( l_sks_need && (!query_temp("hj_game_skills/llzj", me )
               || query_temp("hj_game_damages/llzj", me)<l_sks_need) )
        return notify_fail("ÄãµÄ¡¸ÂäÀ×Ö®¼¼¡¹µÈ¼¶²»¹»¡£\n");

    if( d_sks_need && (!query_temp("hj_game_skills/ydzj", me )
               || query_temp("hj_game_damages/ydzj", me)<d_sks_need) )
        return notify_fail("ÄãµÄ¡¸ÒıµçÖ®¼¼¡¹µÈ¼¶²»¹»¡£\n");

    if( heal_sks_need && (!query_temp("hj_game_skills/heal", me )
               || query_temp("hj_game_damages/heal", me)<heal_sks_need) )
        return notify_fail("ÄãµÄ¡¸»Ö¸´Ö®¼¼¡¹µÈ¼¶²»¹»¡£\n");

    if( dh_sks_need && (!query_temp("hj_game_skills/dhzj", me )
               || query_temp("hj_game_damages/dhzj", me)<dh_sks_need) )
        return notify_fail("ÄãµÄ¡¸¶á»êÖ®¼¼¡¹µÈ¼¶²»¹»¡£\n");

    if( fh_sks_need && (!query_temp("hj_game_skills/fhzj", me )
               || query_temp("hj_game_damages/fhzj", me)<fh_sks_need) )
        return notify_fail("ÄãµÄ¡¸·É»ğÖ®¼¼¡¹µÈ¼¶²»¹»¡£\n");

    if( gs_sks_need && (!query_temp("hj_game_skills/gszj", me )
               || query_temp("hj_game_damages/gszj", me)<gs_sks_need) )
        return notify_fail("ÄãµÄ¡¸¹öÊ¯Ö®¼¼¡¹µÈ¼¶²»¹»¡£\n");

// all ok now!

    set("huanjing2003/lv", next_lv, me);
    if( score_need)addn_temp("hj_score", -(score_need-1), me);
    if( power_need)addn_temp("hj_game_mepower", -(power_need-1), me);
    if( f_sks_need)addn_temp("hj_game_damages/hfzj", -(f_sks_need-1), me);
    if( y_sks_need)addn_temp("hj_game_damages/hyzj", -(y_sks_need-1), me);
    if( l_sks_need)addn_temp("hj_game_damages/llzj", -(l_sks_need-1), me);
    if( d_sks_need)addn_temp("hj_game_damages/ydzj", -(d_sks_need-1), me);
    if( heal_sks_need)addn_temp("hj_game_damages/heal", -(heal_sks_need-1), me);
    if( dh_sks_need)addn_temp("hj_game_damages/dhzj", -(dh_sks_need-1), me);
    if( fh_sks_need)addn_temp("hj_game_damages/fhzj", -(fh_sks_need-1), me);
    if( gs_sks_need)addn_temp("hj_game_damages/gszj", -(gs_sks_need-1), me);

    if( query_temp("hj_game_mepower", me)<5 )
        set_temp("hj_game_mepower", 5, me);
    set("huanjing2003/last_power",query_temp("hj_game_mepower",  me), me);
    set("huanjing2003/last_skills_lv",query_temp("hj_game_damages",  me), me);

// 9¼¶½«Çå³ıËùÓĞÀÛ»ı£¬µ«ÀÛ»ı´ÎÊı»¹ÓĞĞ§
    if( next_lv == 9 )
    {
        delete("huanjing2003/last_power", me);
        delete("huanjing2003/last_skills_name", me);
        delete("huanjing2003/last_skills_lv", me);
        delete("huanjing2003/last_hp_max", me);
        delete_temp("hj_game_skills", me);
        delete_temp("hj_game_damages", me);
        set_temp("hj_game_mepower", 10, me);
        set_temp("hj_hp_max", 700, me);
        set_temp("hj_game_skills/heal", "»Ö¸´Ö®¼¼", me);
        set_temp("hj_game_damages/heal", 3+random(8), me);
    }

    me->save();
    me->start_busy(5);

    message_vision( HIW"\n\n$N"HIW"´óºÈÒ»Éù£¬ÄîÖäÎÄµÀ£º¡°¸¡ÔÆÇå·ç£¬¾¡ÄÉÎÒ»³£¬ÓÄÁéÔÙÏÖ£¬ÓèÎÒÁ¦Á¿£¡¡±\n\n"
        "Ö»¼û$N"HIW"È«ÉíÒø¹âÉÁÒ«£¬ÄÜÁ¦ĞŞÎªÃ÷ÏÔµØÉÏÁËÒ»¸ö²ã´Î£¡\n\n\n"NOR, me);

    rooms->save_player_level(query("name", me),query("id", me),query("huanjing2003/lv", me),time());
    return 1;
}
