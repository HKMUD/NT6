#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "¼«¸ßÃ÷Ì¨");
        set("long", @LONG
ÕâÀïÊÇ¸£ÑÏËÂ×î¸ß´¦¡£ÌÆÚşºîÀîÃÚÊÖÊé¡¸[1£»37m¼«¸ßÃ÷[2£»37£»0m¡¹Èı¸ö´ó×ÖÓÚ´Ë£¬
Òâ¼´·ğÏà¼«¸ß(¸ßÎŞ¼û¶¥Ïà)£¬·ğ¹â¼«Ã÷(Ã÷²»½èËû¹â)£¬·ğÊÇÖÁ¸ßÎŞÉÏ
µÄ£¬¹ÊÔ»¼«¸ßÃ÷Ì¨¡£
LONG );
        set("exits", ([ 
               "northdown"  : __DIR__"sansheng",
        ]));

        set("objects", ([
                __DIR__"npc/youke" : 4,
        ]));    

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6950);
	set("coor/y", -5580);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}