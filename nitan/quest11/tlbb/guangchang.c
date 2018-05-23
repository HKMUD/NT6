// Room: /d/shaolin/guangchang1.c
// Date: YZC 96/01/19

#include <ansi.h>
#include <wanted.h>

inherit ROOM;

void init();
int do_open();
string look_gate();
#define QUESTDIR3 "quest/ÌìÁú°Ë²¿/Ïô·åÉíÊÀÆª/"
#define QUESTDIR5 "quest/ÌìÁú°Ë²¿/¸´ĞËÌìÏÂÆª/"

void create()
{
	set("short", "¹ã³¡");
	set("long", @LONG
ÕâÀïÊÇÉÙÁÖËÂÇ°µÄ¹ã³¡£¬Õû¸ö¹ã³¡ÓÉ´ó¿éµÄÇàÊ¯ÆÌ³É£¬¼«ÎªÆ½Ì¹¡£µ«ÒòÄê
´ú¾ÃÔ¶£¬¶¼ÓĞĞ©ÆÆËğ¡£´Ô´ÔĞ¡²İ´ÓÊ¯°åµÄ·ìÏ¶ÖĞ³¤ÁË³öÀ´¡£¹ã³¡ÖÜÎ§¶¼ÊÇÃÜÃÜ
µÄËÉÊ÷ÁÖ£¬ËÄ½ÇÉÏ¸÷·ÅÁË¼¸¿éÊ¯±®£¬×Ö¼£¶¼ÉõÎªÄ£ºı¡£ÕıÇ°·½»ÆÇ½±ÌÍß£¬·ÉéÜ
ÇÌéİ£¬ÕıÖĞÒ»µÀ¶şÕÉÀ´¿í£¬ÈıÕÉÀ´¸ßµÄÖìºìÉ¼Ä¾°üÍ­´óÃÅ(gate)¡£ÉÏ·½Ò»¿é´ó
ØÒ£¬Áú·É·ïÎèµØÊé×Å¡º[1;33mÉÙÁÖËÂ[0;37;0m¡»Èı¸ö´ó×Ö¡£ËÂÇ°ÈıÈıÁ½Á½µÄÕ¾×Å¼¸¸öÉ®ÈË¡£
LONG
    );

	set("exits", ([
		"east" : __DIR__"gchange",
		"south" : __DIR__"shifang",
		"west" : __DIR__"gchangw",
	]));

	set("outdoors", "shaolin");
	set("item_desc",([
		"gate"        :    (: look_gate :),
	]));

	set("objects",([
		CLASS_D("shaolin") + "/qing-fa" : 1,
	]));

	setup();
	"/clone/board/shaolin_b"->foo();
}

void init()
{
	object me;
  me = this_player();
  if(!me->query_condition("killer") && me->query(QUESTDIR3+"bad") && me->query_temp(QUESTDIR5+"zhangxing") && !me->query_temp(QUESTDIR5+"dagouzhen"))
  {
   tell_object(me,HIC"\nÄã×ÜËã×ß³öÉÙÁÖËÂ£¬À´µ½É½ÃÅµî¹ã³¡¡£Í»È»ÄãÓÖÓĞÒ»ÖÖ²»ÃîµÄÔ¤¸Ğ¡£\n"NOR); 
   message_vision(WHT"É½ÏÂ´Ò´Ò×ßÀ´Ò»¸öÈË£¬Ïò$NÒ»¹°ÊÖµÀ£º¡°ºÙºÙ£¬Ê©Ö÷Èç´ËĞ×ºİ£¬»¹ÊÇÁôÔÚÉÙÁÖÇ±ĞŞ·ğ·¨µÃºÃ°¢¡£¡±\n"NOR,me);
   me->move("/d/gb/dagouzhen");
   tell_object(me,HIR"ÄãÒÉ»óÁËÒ»ÏÂ£¬È´·¢ÏÖËÄÖÜÎ§ÉÏÒ»È¦ÈË£¬ËÆºõÊÇØ¤°ï´ò¹·Õó·¨¡£\n"NOR);
   log_file("quest/TLBB", sprintf("%s(%s)±»¹Ø½ø´ò¹·Õó¡£¾­Ñé£º%d¡£\n", me->name(1),me->query("id"), me->query("combat_exp")) );
   return;
  }
	add_action("do_knock", "knock");
}

int close_gate()
{
	object room;

	if(!( room = find_object(__DIR__"smdian")) )
		room = load_object(__DIR__"smdian");
	if(objectp(room)) {
	delete("exits/north");
	message("vision", "Æ¹µØÒ»Éù£¬ÀïÃæÓĞÈË°Ñ´óÃÅ¹ØÉÏÁË¡£\n", this_object());
	room->delete("exits/south");
	if (objectp(present("qingfa biqiu", room)))
		message("vision", "Çå·¨±ÈÇğÉÏÇ°°Ñ´óÃÅ¹ØÁËÆğÀ´¡£\n", room);
	else
		message("vision", "×³ÄêÉ®ÈËÉÏÇ°°Ñ´óÃÅ¹ØÁËÆğÀ´¡£\n", room);
	}
	else message("vision", "ERROR: gate not found(close).\n", room);
}

int do_knock(string arg)
{
	object room;

	if (query("exits/north"))
		return notify_fail("´óÃÅÒÑ¾­ÊÇ¿ª×ÅÁË¡£\n");

	if (!arg || (arg != "gate" && arg != "north"))
		return notify_fail("ÄãÒªÇÃÊ²Ã´£¿\n");

	if(!( room = find_object(__DIR__"smdian")) )
		room = load_object(__DIR__"smdian");

	if(objectp(room)) {
		set("exits/north", __DIR__"smdian");
		message_vision("$NÇáÇáµØÇÃÁËÇÃÃÅ£¬Ö»ÌıÖ¨µØÒ»Éù£¬Ò»Î»×³ÄêÉ®ÈËÓ¦Éù´ò¿ª´óÃÅ£¬\n"
				"ËûÓÃÈñÀûµÄÄ¿¹âÉÏÉÏÏÂÏÂ´òÁ¿×Å$N¡£\n",this_player());
		room->set("exits/south", __FILE__);
		message("vision", "ÍâÃæ´«À´Ò»ÕóÇÃÃÅÉù£¬×³ÄêÉ®ÈËÓ¦ÉùÉÏÇ°°Ñ´óÃÅ¿ª¡£\n", room);
		remove_call_out("close_gate");
		call_out("close_gate", 10);
	}
	return 1;
}

int valid_leave(object me, string dir)
{
	if ( dir != "north" )
	return ::valid_leave(me, dir);

	if (is_wanted(me))
		return 0;
	if ( me->query("family/family_name") == "ÉÙÁÖÅÉ" ) {
		if ( me->query("guilty") == 0
		 && me->query("K_record") == ( me->query("PKS") + me->query("MKS"))) {
			message_vision("×³ÄêÉ®ÈË²àÉíÈÃ¿ª£¬ËµµÀ£ºÊ¦ĞÖĞÁ¿àÁË£¬Çë½ø¡£\n", me);
			return 1;
		}
		else {
			if((int)me->query("guilty") == 0) {
				int shen = me->query("shen");
				if((int)me->query("shen_record") > shen)
					me->set("guilty", 1);
				else
					me->set("guilty", 2);
				me->set("K_record", me->query("PKS") + me->query("MKS"));
				if (shen > 0 && shen > me->query("combat_exp")) shen = me->query("combat_exp");
				if (shen < 0 && -shen > me->query("combat_exp")) shen = -me->query("combat_exp");
				if (shen < 0) shen += shen / 9;
				else shen -= shen / 9;
				me->set("shen_record", shen);
			}
			write("×³ÄêÉ®ÈË³ÁÏÂÁ³À´£¬ËµµÀ£º½äÂÉÔºÖ÷³ÖĞş¼Å´óÊ¦ÇëÊ¦ĞÖ»ğËÙÈ¥½äÂÉÔº³ÂÊö´ËĞĞ¹ı·¸¡£\n");
			return 1;
		}
	}
	else if( present("yingxiong ling", me)){
		message_vision("×³ÄêÉ®ÈËºÏÊ®ÎªÀñ£¬²àÉíÈÃ¿ª£¬ËµµÀ£ºÔ­À´ÊÇ¹ó¿Í¼İµ½£¬Çë½øÇë½ø£¡\n", me);
		return 1;
	}
	else if (me->query("luohan_winner")) {
		message_vision(HIY "×³ÄêÉ®ÈË¶Ô$NºÏÊ®ÎªÀñ£¬²àÉíÈÃ¿ª£¬ËµµÀ£ºÔ­À´ÊÇ´³¹ıÂŞººÕóµÄ´óÓ¢ĞÛ¼İµ½£¬Çë½øÇë½ø£¡\n" NOR, me);
		return 1;
	}
	if (me->query("shen") >= 0) {
		if (me->query("gender") == "Å®ĞÔ") {
			return notify_fail("×³ÄêÉ®ÈËËµµÀ£ºÕâÎ»Å®Ê©Ö÷»¹ÊÇÇë»Ø°Õ£¬±¾ËÂ´Ó²»½Ó´ıÅ®¿Í¡£\n");
		}
		else {
			return notify_fail("×³ÄêÉ®ÈËËµµÀ£ºÕâÎ»Ê©Ö÷Çë»Ø°Õ£¬±¾ËÂ²»½Ó´ıË×ÈË¡£\n");
		}
	}
	return notify_fail("×³ÄêÉ®ÈËÁ¢Ê±´ÓÉíÅÏÖ¿³öÒ»°ÑÑ©ÁÁµÄ½äµ¶À´£¬°ÑÃ÷»Î»ÎµÄ\n"
			"µ¶¼â¶Ô×¼ÄãµÄĞØ¿Ú£¬ºáÃ¼Å­Ä¿µØËµµÀ£ºÄãµÈĞ°Ä§ÍâµÀ£¬»¹²»¸øÎÒ¹ö¿ª£¡\n"
			"ÒÔºóÔÙ¸Ò×ß½üÉÙÁÖÒ»²½£¬ÎÒÁ¢Ê±¾ÍÕ¶¶ÏÄãÃÇµÄ¹·ÍÈ£¡\n");

	if(me->query("no_quest"))
		return notify_fail("\n");
}

string look_gate()
{
	return "Ò»µÀÈıÕÉÀ´¸ßµÄÖìºìÉ¼Ä¾°üÍ­´óÃÅ¡£\n";
}
