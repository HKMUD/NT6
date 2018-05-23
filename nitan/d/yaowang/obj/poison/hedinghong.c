// hedinghong.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(RED"º×¶¥ºì"NOR, ({"heding hong", "hong"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "Ò»Æ¿¾ç¶¾µÄ¶¾Ò©, Èç¹ûÓÃÀ´Á¶°µÆ÷ÓÐ¼ûÑª·âºíÖ®Ð§. \n");
                set("unit", "Æ¿");
                set("value", 20000);
                set("base_weight", 10);
                set("poison_type", "yaowang_poison");
                set("can_pour", 1);
                set("can_daub", 1);
                set("can_drug", 1);
                set("poison", ([
                        "level" : 220,
                        "id"    : "yaowang",
                        "name"  : "¾ç¶¾",
                        "duration" : 18,
                ]));
                set("no_sell", 1);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        message_vision("$NÑöÍ·¹¾à½¹¾à½¹àÏÂÒ»Æ¿" + name() + "¡£\n", me);
        set_temp("die_reason", "ºÈÁËº×¶¥ºì£¬ÖÐ¶¾ËÀÁË", me);
        me->die();
        destruct(this_object());
        return 1;
}
