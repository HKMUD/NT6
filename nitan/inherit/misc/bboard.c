// This program is a part of NT MudLIB
// bboard.c

#include <ansi.h>

inherit ITEM;
inherit F_SAVE;

#define NOTICE                  RED" Ôø¾­²×º£ÄÑÎªË®£¬³ýÈ¥Î×É½²»ÊÇÔÆ" NOR

// ×î¶àÈÝÄÉ 100 ¸öÌù×Ó
#define MAX_PLAN                1000

// ¼ÙÈçÌù×Ó³¬¹ýÁË MAX_PLAN£¬É¾µôÇ° 20 ¸ö
#define DEL_TO                  20

// ÊÇ·ñ±£´æËùÓÐÔ­À´µÄÌù×Ó£¬ÊÇÔòÉèÎª0£¬·ñÔòÉèÎª 1
#define SAVE_ALL_OLD_PLAN       0

// Èç¹ûÐèÒªÏÔÊ¾ÕûÀíÇé¿ö£¨ºÜ³¤ºÜ³¤£©£¬Çë£º
#define DEBUG                   1

// ×î´óµÄ±êÌâ³¤¶È
#define MAX_TITLE_LEN           30

// ·¢±íÎÄÕÂÐèÒªµÄÄÜÁ¦
#define NEED_EXP                10000
#define NEED_AGE                15

// ·µ»Ønote[num]µÄÄÚÈÝºÍ»ØÎÄÄÚÈÝ
string content(mapping *notes, int num);
string makeup_space(string s, int max);

void setup()
{
        string loc;
        string my_long, my_id;

        if( stringp(loc = query("location")) )
                move(loc);

        my_long = query("long");
        my_id = query("board_id");

        restore();

        set("no_get", 1);
        set("long", my_long);
        set("id", "board");
        set("location", loc);
}

void init()
{
        add_action("do_post", "post");
        add_action("do_followup", "re");
        add_action("do_followup", "followup");
        add_action("do_read", "read");
        add_action("do_discard", "delete");
        add_action("do_discard", "discard");
        add_action("do_banzhu", "banzhu");
        add_action("do_hold", "hold");
        add_action("do_mark", "mark");
        add_action("do_from", "from");
        add_action("do_search", "search");
}

string query_save_file()
{
        string id;

        if( !stringp(id = query("board_id")) ) return 0;
        return DATA_DIR + "board/" + id;
}

string short()
{
        mapping *notes;
        int i, unread, last_read_time;

        notes = query("notes");
        if( !pointerp(notes) || !sizeof(notes) )
                return ::short() + " [ Ã»ÓÐÈÎºÎÌù×Ó ]";

        if( this_player() )
        {
                last_read_time = (int)query("board_last_read/" +
                                 (string)query("board_id"), this_player());
                for (unread = 0, i = sizeof(notes) - 1; i >= 0; i--, unread ++)
                        if( notes[i]["time"] <= last_read_time ) break;
        }
        if( unread )
                return sprintf( HIC "%s" NOR " [ " HIW "%d" NOR " ¸öÌù×Ó£¬" HIR "%d" NOR " ÆªÎ´¶Á ]",
                                ::short(), sizeof(notes), unread);
        else
                return sprintf("%s [ " HIW "%d" NOR " ¸öÌù×Ó ]", ::short(), sizeof(notes));
}

string long()
{
        mapping *notes;
        int i, last_time_read;
        string msg;

        msg = query("long");
        if( msg[<1] != '\n' )
                msg += "\n";

        notes = query("notes");
        if( !pointerp(notes) || !sizeof(notes) )
                return msg + "\nÁôÑÔ°æµÄÊ¹ÓÃ·½·¨Çë¼û help board¡£\n" ;

        msg += (query("banzhu") ? ("Õâ¸ö°æµÄµÄ°æÖ÷ÊÇ " WHT + query("banzhu") + NOR "¡£\n") : "") +
               "©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤\n";

        last_time_read = query("board_last_read/" + (string)query("board_id"), this_player());

        for (i = 0; i < sizeof(notes); i++)
        {
                msg += sprintf("%s[" WHT "%3d" NOR "]" NOR "  %-30s  %12s (%s)\n",
                        (notes[i]["time"] > last_time_read ? HIY: ""),
                        i + 1, notes[i]["title"], notes[i]["author"],
                        TIME_D->replace_ctime(notes[i]["time"]) );
        }

        msg += "©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤\n";
        return msg;
}

int do_from(string arg)
{
        mapping *notes;
        int i,j,last_time_read;
        string msg;

        notes = query("notes");
        msg = query("long");
        if( msg[<1] != '\n' )
                msg += "\n";
        if( !pointerp(notes) || !sizeof(notes) )
                return notify_fail(msg + "\nÁôÑÔ°æµÄÊ¹ÓÃ·½·¨Çë¼û help board¡£\n");

        if( !arg ) i = 0;
        else i = atoi(arg) - 1;

        if( i < 0 ) i = 0;
        if( i > sizeof(notes) )
                return notify_fail(msg + "\nÁôÑÔ°æµÄÊ¹ÓÃ·½·¨Çë¼û help board¡£\n");

        msg += (query("banzhu") ? ("Õâ¸ö°æµÄµÄ°æÖ÷ÊÇ " WHT + query("banzhu") + NOR "¡£\n") : "") +
               "©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤\n";
        last_time_read = query("board_last_read/" + (string)query("board_id"), this_player());

        j = 0;
        for (; i < sizeof(notes); i++)
        {
                msg += sprintf("%s[" WHT "%3d" NOR "]" NOR "  %-30s  %12s (%s)\n",
                        (notes[i]["time"] > last_time_read ? HIY: ""),
                        i + 1, notes[i]["title"], notes[i]["author"],
                        TIME_D->replace_ctime(notes[i]["time"]) );
                j ++;
                if( j > 1000 ) break;
        }

        msg += "©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤\n";
        this_player()->start_more(msg);
        return 1;
}

void done_post(object me, mapping note, int n, string text)
{
        int i, j;
        int pl;
        string sign;
        string pure;
        mapping *notes;
        string *lines;
        string msg = "";

        if( !stringp(text) )
                return;

        if( strlen(text) > 64 * 2048 )
        {
                tell_object(me, "ÄãµÄÁôÑÔÌ«³¤ÁË£¬ÇëÂÔÈ¥Ò»Ð©²»±ØÒªµÄ¡£\n");
                return;
        }

        lines = explode(text, "\n");
        i = sizeof(lines);
        if( i > 2000 )
        {
                tell_object(me, "ÄãµÄÁôÑÔÌ«³¤ÁË£¬ÇëÂÔÈ¥Ò»Ð©²»±ØÒªµÄ¡£\n");
                return;
        }

        if( i > 20 && strlen(text) / i < 10 )
        {
                tell_object(me, "ÄãµÄÁôÑÔÖÐ¶Ì¾äÌ«¶àÁË£¬Çëµ÷ÕûÒ»ÏÂÒÔ±ãËûÈËÔÄ¶Á¡£\n");
                return;
        }

        while (i--)
        {
                // scan all lines
                if( strlen(lines[i]) > 200 )
                {
                        tell_object(me, "ÄãÁôÑÔÖÐÓÐÐ©ÐÐÌ«³¤ÁË£¬Çë·ÖÐÐÒÔ±ãËûÈËÔÄ¶Á¡£\n");
                        return;
                }
        }

        if( !n ) n = query("env/default_sign", me);
        if( !stringp(sign = query(sprintf("env/sign%d", n), me)) )
        {
                // auto select the first none null sign
                for (i = 1; i <= 4; i++)
                {
                        sign = query(sprintf("env/sign%d", i), me);
                        if( stringp(sign) ) break;
                }
        }

        if( stringp(sign) )
        {
                sign = replace_string(sign, "~", "\"");
                sign = replace_string(sign, "", "\\");
                sign = replace_string(sign, "\\n", "\n");
                sign = trans_color(sign, 1);
                pure = filter_color(sign);
                if( strlen(pure) >= 1 &&
                    pure[strlen(pure) - 1] != '\n')
                        sign += "\n";

                pure = filter_color(text);
                pl = strlen(pure);
                if( pl >= 1 && pure[pl - 1] != '\n')
                        text += "\n\n" + sign;
                else
                if( pl >= 2 && pure[pl - 2] != '\n')
                        text += "\n" + sign;
                else
                        text += sign;
        }

        text = trans_color(text, 3);
        note["msg"] = text;
        notes = query("notes");
        if( !pointerp(notes) || !sizeof(notes) )
                notes = ({ note });
        else
        {
                i = sizeof(notes) - 1;
                if( note["time"] <= notes[i]["time"] )
                        note["time"] = notes[i]["time"] + 1;
                notes += ({ note });
        }

        set("notes", notes);
        tell_object(me, HIW "ÐÂÌù×ÓÍê³É¡£\n" NOR);
        save();

        if( sizeof(query("notes")) > MAX_PLAN )
        {
                // DEL_TO ÒÔÇ°µÄÌù×Ó½«±£´æµ½ /data/board/ÕâÀïµÄboard_id ÎÄ¼þÖÐ
                // É¾³ýÄ¿Ç° board ÀïµÄ DEL_TO ÒÔÇ°µÄÌù×Ó
                // Ðè¶ÔmarkÎÄÕÂ±£Áô
                i = 0;
                j = 0;
                while (i<sizeof(notes))
                {
                        if( notes[i]["mark"] != "M" )
                        {
                                msg = content(notes, i);
                                write_file(DATA_DIR + "board/" + query("board_id") + ".old", msg, SAVE_ALL_OLD_PLAN);
                                //notes = notes[0..i-1] + notes[i+1..<1];
                                notes[i] = 0;
                                j ++;
                        }
                        //else  i ++;
                        i ++;

                        if( j == DEL_TO ) break;
                }
                notes -= ({ 0 });
                set("notes", notes);
                save();
                tell_object(me, HIR"¡­¡­ÕûÀíÍê±Ï£¬É¾³ý "HIW+(DEL_TO+1)+HIR" ºÅÒÔÇ°µÄÌù×Ó¡£\n"NOR);
        }
        return;
}

int do_post(string arg, int n)
{
        mapping note, fam;
        int noname_board;
        string poster_lvl, family;
        object me = this_player();
        string holded;

        poster_lvl = query("poster_level");

        if( !stringp(poster_lvl) )
                poster_lvl = "(player)";

        // write("Board Restricted to " + poster_lvl + " and above.\n");

        if( (int)SECURITY_D->check_wiz_level(me, poster_lvl) < 0 )
                return notify_fail("±¾°å²»½ÓÊÜÄãµÄÍ¶¸å¡£\n");

        if( stringp(holded = query("hold")) &&
            strsrch(holded, "*"+query("id", me)+"*") >= 0 && !wizardp(me) )
                return notify_fail("ÄãÔÚ±¾°æµÄÈ¨ÏÞÒÑ¾­±»·âÁË¡£\n");

        family = query("poster_family");
        fam = query("family", me);
        noname_board = query("noname_board");

        // write("Board Restricted to " + family + " players only.\n");

        if( stringp(family )
                && (int)SECURITY_D->check_wiz_level(me, "(immortal)") < 0
                && (!mapp(fam) || fam["family_name"] != family) )
                return notify_fail("·Ç±¾ÅÉµÜ×Ó²»µÃÏò±¾°åÂÒÍ¿ÂÒÐ´¡£\n");

        if( query("avoid_flood")
                && query("combat_exp", me) < NEED_EXP
                && query("age", me) < NEED_AGE )
                return notify_fail("ÄãÔÝÊ±»¹Ã»ÓÐÈ¨Á¦ÔÚÕâÀï·¢±íÎÄÕÂ£¬ÐèÒª " WHT +
                                   NEED_EXP + NOR " µã¾­ÑéÖµ»òÕß " WHT + NEED_AGE + NOR " ËêµÄÄêÁä¡£\n");

        if( !arg ) return notify_fail("ÐÂÌù×ÓÇëÖ¸¶¨Ò»¸ö±êÌâ¡£\n");

        if( sscanf(arg, "%s with %d", arg, n) != 2 )
                n = 0;

        if( replace_string(arg, " ", "") == "")
                arg = "ÎÞ±êÌâ";
        /*
        else
                arg = trans_color(arg, 3);
        */
        if( strlen(arg) > MAX_TITLE_LEN )
                return notify_fail("Õâ¸ö±êÌâÌ«³¤ÁË£¬Çë»»Ò»¸ö¼ò½àÒ»µãµÄ¡£\n");

        note = allocate_mapping(5);
        note["title"] = arg;

        if( noname_board )
        {
                note["owner"] = "NULL";
                note["author"] = "ÄäÃû";
        }
        else
        {
                note["owner"] = query("id", me);
                note["author"] = me->name(1);
        }
        note["time"] = time();
        me->edit((: done_post, me, note, n :));
        return 1;
}

int do_followup(string arg)
{
        int n, num, noname_board;
        string title, file, msg = "";
        mapping note, *notes, fam;
        string poster_lvl, family;
        object me = this_player();
        string holded;

        poster_lvl = query("poster_level");

        if( !stringp(poster_lvl) )
                poster_lvl = "(player)";

        // write("Board Restricted to " + poster_lvl + " and above.\n");

        if( (int)SECURITY_D->check_wiz_level(me, poster_lvl) < 0)
                return notify_fail("±¾°å²»½ÓÊÜÄãµÄÍ¶¸å¡£\n");

        if( stringp(holded = query("hold")) &&
            strsrch(holded, "*"+query("id", me)+"*") >= 0 && !wizardp(me) )
                return notify_fail("ÄãÔÚ±¾°æµÄÈ¨ÏÞÒÑ¾­±»·âÁË¡£\n");

        family = query("poster_family");
        fam = query("family", me);
        noname_board = query("noname_board");

        // write("Board Restricted to " + family + " players only.\n");

        if( stringp(family)
                && (int)SECURITY_D->check_wiz_level(me, "(immortal)") < 0
                && (!mapp(fam) || fam["family_name"] != family) )
                return notify_fail("·Ç±¾ÅÉµÜ×Ó²»µÃÏò±¾°åÂÒÍ¿ÂÒÐ´¡£\n");

        if( query("avoid_flood")
                && query("combat_exp", me) < NEED_EXP
                && query("age", me) < NEED_AGE )
                return notify_fail("ÄãÔÝÊ±»¹Ã»ÓÐÈ¨Á¦ÔÚÕâÀï·¢±íÎÄÕÂ£¬ÐèÒª " WHT +
                                   NEED_EXP + NOR " µã¾­ÑéÖµ»òÕß " WHT + NEED_AGE + NOR " ËêµÄÄêÁä¡£\n");

        if( !arg )
                return notify_fail("ÇëÊäÈëÓû»Ø¸´µÄÎÄÕÂ±àºÅ»ò last »Ø¸´×îºóÒ»ÆªÎÄÕÂ¡£\n");

        notes = query("notes");

        if( arg == "last" ) num = sizeof(notes);
        else
        if( sscanf(arg, "%d %s", num, title) < 1 )
                return notify_fail("ÇëÊäÈëÓû»Ø¸´µÄÎÄÕÂ±àºÅ¡£\n");

        if( sscanf(arg, "%d %s with %d", num, title, n) != 3
                && sscanf(arg, "%d with %d", num, n) != 2 )
                n = 0;

        if( !arrayp(notes) || num < 1 || num > sizeof(notes) )
                return notify_fail("Ã»ÓÐÕâÕÅÁôÑÔ¡£\n");

        if( title && strlen(title) > MAX_TITLE_LEN )
                return notify_fail("Õâ¸ö±êÌâÌ«³¤ÁË£¬Çë»»Ò»¸ö¼ò½àÒ»µãµÄ¡£\n");

        num--;
        file = notes[num]["msg"];

        foreach( string word in explode( file, "\n" ) )
        {
                if( word == "" || word[0..7]=="[1;30m>" ) continue;
                else if( word[0..5] == "[33m>" ) msg += "[1;30m> "+word[5..]+"\n";
                else if( word[0..5] == "[36m>" ) msg += "[33m> "+word[5..]+"\n";
                else msg += "[36m> "+word+"\n";
        }

        if( msg[0..5] == "[36m>" )
                msg = "[36m> ¡ò" + notes[num]["author"] + " ÔÚ " + TIME_D->replace_ctime(notes[num]["time"]) + " ÁôÏÂÕâÆªÁôÑÔ£º\n" + msg;

        msg += "\n¡ò" + me->query_idname() + " ÔÚ " + TIME_D->replace_ctime(notes[num]["time"]) + " ÁôÏÂÕâÆªÁôÑÔ£º\n";

        note = allocate_mapping(5);
        if( !title )
                title = (notes[num]["title"][0..5] != "»Ø¸´£º" ? "»Ø¸´£º" : "") + notes[num]["title"];

        note["title"] = title;
        if( noname_board )
        {
                note["owner"] = "NULL";
                note["author"] = "ÄäÃû";
        }
        else
        {
                note["owner"] = query("id", me);
                note["author"] = me->name(1);
        }
        note["time"] = time();
        me->edit((: done_post, me, note, n :), msg);
        return 1;
}

int do_read(string arg)
{
        int num, rep, last_read_time, i, last, arc, private_board;
        mapping *notes, fam;
        string myid, msg, file;
        string family;
        object me = this_player();
        int len = 0;

        last_read_time = query("board_last_read/" + query("board_id"), me);
        myid    = query("board_id");
        notes   = query("notes");
        arc = query("wizard_only");
        private_board = query("private_board");

        if( arc && !wizardp(me) )
                return notify_fail("Î×Ê¦ÄÚ²¿½»Á÷²»µÃ¿úÊÓ¡£\n");

        family = query("poster_family");
        fam = query("family", me);

        //write("Board Restricted to " + family + " players only.\n");

        if( stringp(family)
                && !wizardp(me)
                && (!mapp(fam) || fam["family_name"] != family) )
                return notify_fail("·Ç±¾ÅÉµÜ×Ó²»µÃ¿úÊÓ±¾ÅÉÄÚ²¿½»Á÷¡£\n");

        if( !pointerp(notes) || !sizeof(notes) )
                return notify_fail("°å×ÓÉÏÄ¿Ç°Ã»ÓÐÈÎºÎÌù×Ó¡£\n");

        if( !arg ) return notify_fail("Ö¸Áî¸ñÊ½£ºread <Ìù×Ó±àºÅ>|new|next|old\n");

        // ÏÔÊ¾ÒÔÇ°±¸·ÝµÄ¾ÉÌù×Ó
        if( arg == "old" )
        {
                file = DATA_DIR + "board/" + query("board_id") + ".old";
                if( file_size(file) <= 0 )
                        return notify_fail("¶Ô²»Æð£¬Ä¿Ç°±¾°æÃ»ÓÐ±£´æµÄ¾ÉÌù¡£\n");
                else
                {
                        if( private_board && !wizardp(me) )
                                return notify_fail("¶Ô²»Æð£¬ÓÉÓÚ¾ÉÌùÉæ¼°µ½Ò»Ð©¸öÈËÒþË½£¬¹Ê²»¿ª·ÅÔÄ¶Á¡£\n");

                        msg = read_file(file);
                        me->start_more(msg);
                        return 1;
                }
        }
        // ÏÔÊ¾Î´¶ÁµÄÌù×Ó
        if( arg == "new" || arg == "next" )
        {
                if( !intp(last_read_time) || undefinedp(last_read_time) )
                        num = 1;
                else
                        for (num = 1; num <= sizeof(notes); num++)
                        {
                                if( notes[num-1]["time"] > last_read_time )
                                {
                                        if( private_board )
                                        {
                                                if( wizardp(me) ) break;
                                                else if( !strcmp(query("id", me), notes[num - 1]["owner"]) ) break;
                                        } else break;
                                }
                        }

        } else
        if( !sscanf(arg, "%d", num) )
                return notify_fail("ÄãÒª¶ÁµÚ¼¸¸öÌù×Ó£¿\n");

        if( num < 1 || num > sizeof(notes) )
                return notify_fail("Ã»ÓÐÕâ¸öÌù×Ó¡£\n");
        num--;

        if( !wizardp(me) && private_board && strcmp(query("id", me), notes[num]["owner"]) )
                return notify_fail("Õâ¸öÌû×Ó²»ÊÇÄãÁôµÄ£¬ËùÒÔÄã²»ÄÜÔÄ¶Á¡£\n");

        msg = sprintf(  CYN "----------------------------------------------------------------------\n"
                        BWHT BLU " ±ê Ìâ " BBLU WHT " %-62s\n"
                        BWHT BLU " ×÷ Õß " BBLU WHT " %-19s   ¨q¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨r\n"
                        BWHT BLU " Æª Êý " BBLU WHT " %-11d           ¨U"HIR"ÇëÎÄÃ÷Ê¹ÓÃ£¬·ñÔò"HIY"Äã"HIR"»ò"HIY"Ìû×Ó"HIR"¿ÉÄÜ»á±»É¾³ý"NOR BBLU WHT"¨U\n"
                        BWHT BLU " Ê± ¼ä " BBLU WHT " %-19s   ¨t¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨T¨s\n" NOR
                        CYN "----------------------------------------------------------------------\n\n" NOR "%s\n",
                        notes[num]["title"], notes[num]["author"] + "(" + notes[num]["owner"] + ")", num + 1, TIME_D->replace_ctime(notes[num]["time"]),
                        notes[num]["msg"]);

#ifndef LONELY_IMPROVED
        len = color_len(NOTICE);
#endif
        msg +=sprintf(  CYN "----------------------------------------------------------------------\n"
                        CYN "|" NOR "%|"+(68+len)+"s" NOR CYN "|\n" NOR
                        CYN "----------------------------------------------------------------------\n" NOR, NOTICE);

        me->start_more(msg);

        if( notes[num]["time"] > last_read_time )
                me->set("board_last_read/" + query("board_id"),
                        notes[num]["time"]);

        return 1;
}

int do_banzhu(string arg)
{
        string opt;

        if( !arg ) return notify_fail("Ö¸Áî¸ñÊ½£º banzhu +|- <°æÖ÷id>\n");

        if( sscanf(arg, "%s %s", opt, arg) != 2 || opt != "+" && opt != "-" )
                return notify_fail("Ö¸Áî¸ñÊ½£º banzhu +|- <°æÖ÷id>\n");

        if( !wizardp(this_player(1)) && query("owner_id") != query("id", this_player()) )
                return notify_fail("Äã²»ÊÇÎ×Ê¦£¬²»¿ÉÒÔÈÎÃü°æÖ÷¡£\n");

        if( !stringp(arg) || strlen(arg) < 3 )
                return notify_fail("Ã»ÓÐÕâ¸öÈË¡£\n");

        if( opt == "+" )
        {
                if( query("banzhu") == arg )
                        return notify_fail("Ä¿Ç°µÄ°æÖ÷¾ÍÊÇ " + arg + "£¬²»ÐèÒªÈÎÃü¡£\n");

                set("banzhu", arg);
                save();
                write("ÈÎÃü " HIY + arg + NOR " Îª" + name() + "°æÖ÷³É¹¦¡£\n");
        }
        else
        {
                if( !query("banzhu") )
                        return notify_fail("Ä¿Ç°Ã»ÓÐ°æÖ÷£¬²»ÐèÒª³·»»¡£\n");

                if( query("banzhu") != arg )
                        return notify_fail("Ä¿Ç°µÄ°æÖ÷²»ÊÇ " + arg + "£¬²»ÄÜ³·»»¡£\n");

                delete("banzhu");
                save();
                write("³·»» " HIY + arg + NOR " " + name() + "°æÖ÷Ö°Î»³É¹¦¡£\n");
        }
        return 1;
}

int do_hold(string arg)
{
        string opt, holded;

        if( !arg ) return notify_fail("Ö¸Áî¸ñÊ½£º hold +|- <id>\n");

        if( sscanf(arg, "%s %s", opt, arg) != 2 || opt != "+" && opt != "-" )
                return notify_fail("Ö¸Áî¸ñÊ½£º hold +|- <id>\n");

        if( !stringp(arg) || strlen(arg) < 3 )
                return notify_fail("Ã»ÓÐÕâ¸öÈË¡£\n");

        if( !wizardp(this_player(1)) &&
            query("banzhu") != query("id", this_player(1)) )
                return notify_fail("Äã²»ÊÇ°æÖ÷£¬²»¿ÉÒÔ·âÍæ¼ÒÈ¨ÏÞ¡£\n");

        if( !query("hold") ) holded = "0";
        else holded = query("hold");

        if( opt == "+" )
        {
                if( strsrch(holded, "*"+arg+"*") >= 0 )
                        return notify_fail(arg + "ÒÑ¾­±»·â£¬²»ÐèÒªÔÙ·Ñ¾¢ÁË¡£\n");

                set("hold", query("hold")+"*"+arg+"*");
                save();
                write("·âÉ± "HIY + arg + NOR" È¨ÏÞ³É¹¦¡£\n");
        }
        else
        {
                if( holded == "0" )
                        return notify_fail("Ä¿Ç°Ã»·â¹ýÈË£¬²»ÐèÒª½â·â¡£\n");

                if( !strsrch(holded, "*"+arg+"*") >= 0 )
                        return notify_fail(arg+"Ã»±»·âÈ¨ÏÞ£¬²»ÐèÒª½â·â¡£\n");

                holded = replace_string(holded, "*"+arg+"*", "");

                set("hold", holded);
                save();
                write("½â·â "HIY+arg+NOR" È¨ÏÞ³É¹¦¡£\n");
        }
        return 1;
}

int do_discard(string arg)
{
        mapping *notes;
        int num;

        if( !arg || sscanf(arg, "%d", num) != 1 )
                return notify_fail("Ö¸Áî¸ñÊ½£ºdelete <Ìù×Ó±àºÅ>\n");

        notes = query("notes");
        if( !arrayp(notes)|| num < 1 || num > sizeof(notes) )
                return notify_fail("Ã»ÓÐÕâÕÅÌù×Ó¡£\n");

        else
        {
                num--;
                if( notes[num]["owner"] != (string)query("id", this_player(1))
                        && query("banzhu") != query("id", this_player(1))
                        && !wizardp(this_player(1)) )
                        return notify_fail("Õâ¸öÌù×Ó²»ÊÇÄãÐ´µÄ£¬ÄãÓÖ²»ÊÇ°æÖ÷¡£\n");

                notes = notes[0..num-1] + notes[num+1..sizeof(notes)-1];
                set("notes", notes);
                write("É¾³ýµÚ " + (num + 1) + " ºÅÌù×Ó....Ok¡£\n");
                save();
                return 1;
        }
}

int do_mark(string arg)
{
        mapping *notes;
        int num;

        if( !arg || sscanf(arg, "%d",num) != 1 )
                return notify_fail("Ö¸Áî¸ñÊ½£ºmark <Ìù×Ó±àºÅ>\n");

        notes = query("notes");
        if( !arrayp(notes)|| num <1 || num > sizeof(notes) )
                return notify_fail("Ã»ÓÐÕâÕÅÌù×Ó¡£\n");

        num--;
        if( query("banzhu") != query("id", this_player(1)) &&
            !wizardp(this_player(1)) )
                return notify_fail("Äã²»ÊÇ°æÖ÷£¬ÎÞ·¨±£ÁôÎÄÕÂ¡£\n");

        if( notes[num]["mark"] == "M" )
        {
                notes[num]["mark"] = " ";
                write("È¥³ýµÚ " + (num+1) + " ºÅÌù×ÓµÄ±£Áô±êÖ¾³É¹¦¡£\n");
        }
        else
        {
                notes[num]["mark"] = "M";
                write("±£ÁôµÚ " + (num+1) + " ºÅÌù×Ó³É¹¦¡£\n");
        }
        save();
        return 1;
}

string content(mapping *notes, int num)
{
        string msg;

        msg = sprintf("[" WHT "%3d" NOR "]  %-30s  %18s (" WHT "%s" NOR ")\n"
                      "©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤\n%s\n",
                      num + 1,
                      notes[num]["title"],
                      notes[num]["author"] + "(" + notes[num]["owner"] + ")",
                      TIME_D->replace_ctime(notes[num]["time"])[0..9],
                      notes[num]["msg"]);
        return msg;
}

string makeup_space(string s, int max)
{
        string *ansi_char = ({
                BLK,   RED,   GRN,   YEL,   BLU,   MAG,   CYN,   WHT,
                BBLK,  BRED,  BGRN,  BYEL,  BBLU,  BMAG,  BCYN,
                       HIR,   HIG,   HIY,   HIB,   HIM,   HIC,   HIW,
                       HBRED, HBGRN, HBYEL, HBBLU, HBMAG, HBCYN, HBWHT,
                NOR
        });

        string space = s;
        int i, space_count;

        for (i = 0; i < sizeof(ansi_char); i ++)
                space = replace_string(space, ansi_char[i], "", 0);

        space_count = sizeof(s) - sizeof(space);
        if( sizeof(s) >= max )
                space_count = max - sizeof(space);

        space = "";

        for (i = 0; i < space_count; i ++) space += " ";
        return space;
}

int do_search(string arg)
{
        mapping *notes;
        int i, last_time_read, j = 0;
        string msg, topic, note;
        object me = this_player();

        notes = query("notes");
        if( !pointerp(notes) || !sizeof(notes) )
        {
                tell_object(me, "Ä¿Ç°Ã»ÓÐÈÎºÎÌû×Ó¡£\n");
                return 1;
        }

        if( !arg )
        {
                tell_object(me, "ÄãÏëËÑË÷ÄÇÒ»ÌõÌû×Ó£¿\n");
                return 1;
        }

        if( sscanf(arg, "%s %s", topic, arg) != 2 )
        {
                tell_object(me, "ÄãÖ»ÄÜËÑË÷±êÌâ(title)¡¢×÷Õß(author)¡¢ÄÚÈÝ(document)¡£\n");
                return 1;
        } else
        {
                if( topic == "title" ) note = "±êÌâ";
                else if( topic == "author" ) note = "×÷Õß";
                else if( topic == "document" ) note = "ÄÚÈÝ";
                else
                {
                        tell_object(me, "ÄãÖ»ÄÜËÑË÷±êÌâ(title)¡¢×÷Õß(author)¡¢ÄÚÈÝ(document)¡£\n");
                        return 1;
                }
        }

        last_time_read = query("board_last_read/" + (string)query("board_id"), this_player());
        i = sizeof(notes);

        msg = sprintf("¸ù¾Ý " HIY "%s" NOR " ËÑË÷ " HIY "%s" NOR " µÃµ½ÈçÏÂ·ûºÏÌõ¼þÌû×Ó£º\n"
                      "©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤\n" NOR,
                      arg, note);

        while (i--)
        {
                if( topic == "document" )
                {
                        if( strsrch(notes[i]["msg"], arg) == -1 )
                                continue;
                } else
                {
                        if( strsrch(notes[i][topic], arg) == -1 )
                                continue;
                }
                msg += sprintf("%s[" WHT "%3d" NOR "]" NOR "  %-30s  %12s (%s)\n",
                               (notes[i]["time"] > last_time_read ? HIY: ""),
                               i + 1, notes[i]["title"], notes[i]["author"],
                               TIME_D->replace_ctime(notes[i]["time"]) );

                j ++;
                if( j > 19 ) break;
        }

        msg += "©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤\n";

        if( j == 0 )
        {
                tell_object(me, "¸ù¾Ý " HIY + arg + NOR " ËÑË÷ " HIY + note + NOR " Ã»ÓÐÕÒµ½·ûºÏÌõ¼þµÄÌû×Ó¡£\n");
                return 1;
        }

        if( j > 19 )
                msg += "ÓÉÓÚËÑË÷µ½µÄ½á¹ûÌ«¶à£¬Òò´ËÖ»ÏÔÊ¾¶þÊ®ÌõÁôÑÔ£¬ÇëÊ¹ÓÃ¸üÃ÷È·µÄ¹Ø¼ü×Ö|´Ê¡£\n";

        me->start_more(msg);
        return 1;
}
