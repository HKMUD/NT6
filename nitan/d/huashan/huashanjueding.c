#include <ansi.h>
inherit ROOM;
string look_notice();

void create()
{
        set("short", "»ªÉ½¾ø¶¥");
        set("long", @LONG
[1£»37m                                                   ÎäÁÖ´ó
»á¹ã³¡                                                      
  µÇÉÏ´Ë´¦£¬Ö»¾õÑÛÇ°ÊÇÒ»·½Ô²ÊıÊ®ÕÉµÄÆ½Ì¨£¬ÖĞÑëÓĞÒ»Í¹ÆğÔ¼ÕÉ¸ß
µÄÊ¯Ì¨£¬ÑÒÊ¯ÉÏ¿Ì×ÅÀú½ç»ªÉ½ÂÛ½£µÄÅÅĞĞ°ñ(notice)£»¿ÕÆºµÄ¶«²àÁ¢
ÓĞÒ»ÕÉĞí¸ßµÄ×ÏÌ´Ä¾¼Ü£¬¼Ü×ÅÒ»ÃæÑªºìÉ«µÄ´ó¹Ä£¬±ÈÎä¿ªÊ¼ºó£¬Ì¨ÉÏ
»áµİ³öÒ»¿éÅÆ×Ó(paizi)£¬ÏòÄãÕ¹Ê¾µ±Ç°±ÈÎäµÄÈü³Ì£»·å¶¥ËÄÖÜÔÆÎíÆ®
Ãì£¬·Â·ğÖÃÉí´óº££¬ÖÚÉ½ÓÌÈçº£ÖĞĞ¡µº£¬»·ÈÆ×ÅÖ÷·å£¬·ÂÈçÒ»¶äÊ¢¿ª
µÄÁ«»¨¡£[2£»37£»0m
LONG );
        set("item_desc", ([ /* sizeof() == 1 */
                "´ó¹Ä" : "ÕâÊÇÒ»Ö»Å£Æ¤ÖÆ³ÉµÄ¾Ş¹Ä£¬ÎäÁÖÈËÊ¿ÔÚ»ªÉ½ÂÛ½£Ê±ÇÃÏì(knock)Ëü¿ªÊ¼±ÈÎä¡£",
                "notice" : (: look_notice :),
        ]));
        set("exits", ([ /* sizeof() == 2 */
                "southdown" : "/d/huashan/houzhiwangyu",
        ]));
        
        set("outdoors", "huashan" );

        set("no_fight", 1);
        set("no_quit", 1);
        set("objects", ([
                // "/clone/misc/drum2" : 1,
        ]));
        setup();
}
void init()
{
        object me = this_player();
        add_action("get_weapon", ({ "na", "qu", })); 
        add_action("discmds", ({
                "respitate", "exert", "array", "ansuan", "touxi", "persuade", 
                "teach", "exert", "exercise", "study", "learn", "sleep", "kill",
                "steal", "cast", "conjure", "expell", "fight", "hit", "perform", 
                "prcatice", "scribe", "surrender", "sha", "recall", "quit", "exit"}));
        call_out("do_recover", 1, me);
}
void do_recover(object me)
{
        if (! me || environment(me) != this_object()) return;
                delete("no_get", me);
        if (! living(me)) me->revive();
        set("eff_jing",query("max_jing",  me), me);
        set("jing",query("max_jing",  me), me);
        set("eff_qi",query("max_qi",  me), me);
        set("qi",query("max_qi",  me), me);
        if( query("neili", me)<query("max_neili", me) )
                set("neili",query("max_neili",  me), me);
        if( query("jingli", me)<query("max_jingli", me) )
                set("jingli",query("max_jingli",  me), me);
        me->clear_condition();
        set("food", me->max_food_capacity(), me);
        set("water", me->max_water_capacity(), me);
        me->start_busy(0);
}
int discmds()
{
        tell_object(this_player(), "ÏÖÔÚÄã»¹ÊÇ×¨ĞÄ¿´±ÈÎä°É£¡\n");

        return 1;
}
int get_weapon(string arg)
{
        object me, ob;
        
        me = this_player();
        
        if (! arg) return notify_fail("ÄãÒªÄÃÈ¡Ê²Ã´ÎïÆ·£¿\n");
        
        switch (arg) 
        {
        case "cloth":
                ob = new("/clone/cloth/cloth");
                break;
        case "sword":
                ob = new("/clone/weapon/changjian");
                break;
        case "blade":
                ob = new("/clone/weapon/blade");
                break;
        case "staff":
                ob = new("/clone/weapon/zhubang");
                break;
        case "whip":
                ob = new("/clone/weapon/changbian");
                break;
        case "hammer":
                ob = new("/clone/weapon/hammer");
                break;
        default:  
                return notify_fail("ÄãÒªÄÃÈ¡Ê²Ã´ÎïÆ·£¿\n"); 
                break;
        }
        
        ob->move(me);
        
        tell_object(me, "Äã´Ó¼ÜÉÏÄÃÏÂÁËÄãĞèÒªµÄÎïÆ·¡£\n");
        return 1;
}
        
string look_notice()
{
        object who;
        string *name_list, file;
        int i, j = 0, k;
        
        who = this_player();
        file = read_file("/log/static/lunjian");
        if (! file)
                return "Ä¿Ç°Ã»ÓĞÈÎºÎ±ÈÎä¼ÇÂ¼¡£\n";
        name_list = explode(file,"\n");
        for (i = 0; i < sizeof(name_list); i++) 
        {
                if (name_list[i] == "seperator") 
                {
                        j++;
                        k = 0;
                        printf("\nµÚ" + chinese_number(j) + "½ì»ªÉ½ÂÛ½£½á¹û£º\n");
                        continue;
                }
                k++;
                printf(GRN "µÚ" + chinese_number(k) + "Ãû£º%-50s\n" NOR, name_list[i]);
        }
        return "\n";
}
