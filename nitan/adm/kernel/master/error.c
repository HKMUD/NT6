// This program is a part of NT MudLIB

#define TRACE_DETAIL_LENGTH_LIMIT       300
#define SPRINTF_OVERFLOW                65535

// ´¦Àí´íÎóÑ¶Ï¢µÄº¯Ê½
string tracert_error(mapping error, int caught)
{
        int count;
        string err_msg;
        mapping trace;

        err_msg = "\n"+sprintf(@ERR
©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤<Bugs Report>©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤
[ ´íÎóÊ±¼ä ]: %-s
[ ´íÎóÄÚÈİ ]: %-s[m
[ ´íÎóµµ°¸ ]: %-s
[ ´íÎóĞĞÊı ]: %-d[m
[ ×ÊÁÏ»ØËİ ]:
ERR,
        ctime(time()),
        replace_string(error["error"], "\n", " "),
        error["file"],
        error["line"]);

        foreach( trace in error["trace"] )
        {
                count++;
                err_msg +=sprintf(@ERR
    -- µÚ %|3d ±Ê --
        [ ´¥¶¯Îï¼ş ]: %O
        [ ³ÌÊ½µµ°¸ ]: %s
        [ º¯Ê½Ãû³Æ ]: %s(%s)
        [ ºô½ĞĞĞÊı ]: %s
ERR,
                count,
                trace["object"],
                trace["program"]||"",
                trace["function"]||"",
                trace["arguments"] ? implode(map(trace["arguments"], (:typeof($1):)), ", ") : "",
                (trace["line"] || "Î´Öª")+"");

                if( trace["arguments"] )
                {
                        err_msg += "        [ ´«Èë²ÎÊı ]:\n";
                        err_msg += implode(map(trace["arguments"], (: "                   ** ("+typeof($1)+")"+implode(explode(sprintf("%."+TRACE_DETAIL_LENGTH_LIMIT+"O\n", $1)+(strlen(sprintf("%O", $1)) > TRACE_DETAIL_LENGTH_LIMIT ? "... Ñ¶Ï¢¹ı³¤Ê¡ÂÔ\n" : ""), "\n"),"\n                      ") :)), "\n")+"\n";
                }
                if( trace["locals"] )
                {
                        err_msg += "        [ ³ÌÊ½±äÊı ]:\n";
                        err_msg += implode(map(trace["locals"], (: "                   ** ("+typeof($1)+")"+implode(explode(sprintf("%."+TRACE_DETAIL_LENGTH_LIMIT+"O\n", $1)+(strlen(sprintf("%O", $1)) > TRACE_DETAIL_LENGTH_LIMIT ? "... Ñ¶Ï¢¹ı³¤Ê¡ÂÔ\n" : ""), "\n"),"\n                      ") :)), "\n")+"\n";
                }
        }
        err_msg += "©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤<Bugs Report>©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤\n\n";
        return err_msg;
}

// simulate the old behavior of the driver
string standard_trace(mapping error, int caught)
{
        int i, s;
        string res;
        object me;
        mixed *cmds;

        /* keep track of number of errors per object...if you're into that */

        res = (caught) ? "´íÎóÑ¶Ï¢±»À¹½Ø£º" : "";
        res = sprintf("%s\nÖ´ĞĞÊ±¶Î´íÎó£º%s\n³ÌÊ½£º%s µÚ %i ĞĞ\nÎï¼ş£º%s\n",
                      res, error["error"],
                      error["program"], error["line"],
                      error["object"] ? file_name(error["object"]) : "0");

        if( !error["object"] && (me = this_player()) ) {
                res += sprintf("µ±Ç°Íæ¼Ò£º%s(%s) - %O  ËùÔÚ»·¾³£º%O\n",
                               me->name(1), query("id", me), me, environment(me));
                cmds = me->query_commands();
                res += me->name(1) + "ÉíÉÏ¼°ËÄÖÜµÄÎïÆ·ÓëËùÔÚµÄ»·¾³Ìá¹©ÒÔÏÂÖ¸Áî£º\n";
                for(i = 0; i<sizeof(cmds); i++)
                        res += sprintf("%-15s  %2d %O\n",
                                       cmds[i][0], cmds[i][1], cmds[i][2]);

                res += sprintf("µ±Ç°µÄÃüÁî£º%O\n", me->query_last_input());
        }

        i = 0;
        s = sizeof(error["trace"]);
        if( !this_player(1) && this_player() ) {
                // filter error trace of messaged & chat command
                for (; i < s; i++)
                {
                        string prog;
                        prog = "/" + error["trace"][i]["program"];
                        if( prog != MESSAGE_D + ".c" &&
                            ! sscanf(prog, "/cmds/chat/%*s") &&
                            prog != "/clone/user/chatter.c" &&
                            prog != F_COMMAND )
                                break;
                }
        }

        for (; i < s; i++)
        {
                res = sprintf("%sºô½ĞÀ´×Ô£º%s µÄ %s() µÚ %i ĞĞ£¬Îï¼ş£º %O\n",
                              res,
                              error["trace"][i]["program"],
                              error["trace"][i]["function"],
                              error["trace"][i]["line"],
                              error["trace"][i]["object"]);
        }
        return res;
}

void error_handler(mapping error, int caught)
{
        string msg;
        object user;

        /*
        user = this_player(1);
        if( !objectp(user) ) user = this_player();
        if( !objectp(user) ) user = previous_object();
        */
        user = this_interactive() || this_player() || previous_object();

        efun::write_file(LOG_DIR + "debug.log", standard_trace(error, caught));

        // ±ÜÃâÏİÈëÎŞÏŞ´íÎó»Ø±¨»ØÈ¦
        if( previous_object() == this_object() )
        {
                if( find_object(CHANNEL_D) )
                        CHANNEL_D->channel_broadcast("debug", "Master object ·¢ÉúÎŞÏŞ´íÎó»ØÈ¦£¬"+error["file"]+" µÚ "+error["line"]+" ĞĞ£¬´íÎó£º"+error["error"]+"£¬ÒÑÇ¿ÖÆÖĞÖ¹¡£");
                return;
        }

        msg = tracert_error(error, caught);
        efun::write_file(LOG_DIR + "debug.full", msg);

        if( objectp(user) && userp(user) )
        {
                if( strlen(msg) >= SPRINTF_OVERFLOW-50000 ) msg = msg[0..SPRINTF_OVERFLOW-50000] + "\n\n[Ñ¶Ï¢¹ı³¤Ê¡ÂÔ...]\n";
                user->set_temp("bug_msg", msg);

                if( !wizardp(user) )
                {
                        tell_object(user, "[1;5;33mWARNING[m ÕâÀï·¢ÏÖÁË³ô³æ£¬ÇëÓÃ bug Ö¸Áî½«ÏêÏ¸Çé¿ö±¨¸æ¸øÎ×Ê¦»òÏà¹ØÈËÔ±...\n");

                        if( find_object(CHANNEL_D) )
                        {
                                CHANNEL_D->channel_broadcast("debug", user->query_idname()+"Ö´ĞĞÊ±¶Î´íÎó"+(caught ? "(Catch)" : "")+"£º"+error["file"]+" µÚ "+error["line"]+" ĞĞ¡£");
                                CHANNEL_D->channel_broadcast("debug", "´íÎó£º"+replace_string(error["error"],"\n", " ")+"¡£");
                        }
                }
                else
                        tell_object(user, "[1;33mÖ´ĞĞÊ±¶Î´íÎó[m£ºÇëÖ´ĞĞ bug ¼ì²éÏêÏ¸´íÎó»ØËİ¡£\n"+
                                "[1;33m........µµ°¸[m£º"+error["file"]+"\n[1;33m........ĞĞÊı[m£ºµÚ "+error["line"]+" ĞĞ\n[1;33m........´íÎó[m£º"+replace_string(error["error"],"\n", " ")+"\n");
        }
        else
        {
                if( find_object(CHANNEL_D) )
                {
                        CHANNEL_D->channel_broadcast("debug", (objectp(user) ? base_name(user)+" " : "")+"Ö´ĞĞÊ±¶Î´íÎó"+(caught ? "(Catch)" : "")+"£º"+error["file"]+" µÚ "+error["line"]+" ĞĞ¡£");
                        CHANNEL_D->channel_broadcast("debug", "´íÎó£º"+replace_string(error["error"],"\n", " ")+"¡£");
                }
        }

        return;
}


// Write an error message into a log file. The error occured in the object
// 'file', giving the error message 'message'.
// ¼ÍÂ¼ÏÔÊ¾±àÒë´íÎóÖ®Ñ¶Ï¢
void log_error(string file, string message)
{
        string error_type;
        string name, home;
        object user;


        /*
        user = this_player(1);
        if( !objectp(user) ) user = this_player();
        if( !objectp(user) ) user = previous_object();
        */
        user = this_interactive() || this_player() || previous_object();

        error_type = strsrch(message, "Warning") == -1 ? "´íÎó" : "¾¯¸æ";

        if( objectp(user) && userp(user) )
        {
                if( !wizardp(user) )
                {
                        if( find_object(CHANNEL_D) )
                                CHANNEL_D->channel_broadcast("debug", user->query_idname()+"±àÒëÊ±¶Î"+error_type+"£º"+message);
                }
                tell_object(user, "\n±àÒëÊ±¶Î"+error_type+"£º" + message);
        }
        else
        {
                if( find_object(CHANNEL_D) )
                        CHANNEL_D->channel_broadcast("debug", (objectp(user) ? base_name(user)+" " : "")+"±àÒëÊ±¶Î"+error_type+"£º"+message);
        }
        efun::write_file(LOG_DIR + "log", message);
}

