// liuyun-jian.c
// 	nerd     Dec 9,1996 create

inherit SKILL;

mapping	* action=({
	([	"action":
        "$N π“ª’–°∏œ…»Àπ∞ ÷°π£¨ ÷÷–$wª√“ªÃıº≤π‚¥ÃœÚ$nµƒ$l",
        "lian" :
        "$N π“ª’–°∏œ…»Àπ∞ ÷°π£¨ ÷÷–$wª√“ªÃıº≤π‚¥ÃœÚ◊Û«∞∑Ω......",
                "jibie":7,
                "zhaoshi":"°∏œ…»Àπ∞ ÷°π",
                "sen"  :8  ,
		"dodge":		20  ,
		"damage":		40   ,
		"damage_type":	"¥Ã…À"
	]),
	([	"action":
        "$N“ª’–°∏»’‘¬ª‘ªÕ°π£¨◊›…Ì∆Æø™ ˝≥ﬂ£¨ ÷÷–$w’∂œÚ$nµƒ$l",
                "lian":
        "$N“ª’–°∏»’‘¬ª‘ªÕ°π£¨◊›…Ì∆Æø™ ˝≥ﬂ£¨ ÷÷–$w¥Ûø™¥Û„⁄£¨ª”»˜∆Æ“›......",
                "jiebie":30,
                "zhaoshi":"°∏»’‘¬ª‘ªÕ°π",
                "sen" : 10,
		"dodge":		30,
		"damage":		50 ,
		"damage_type":	"∏Ó…À"
	]),
	([	"action":
        "$N ÷÷–$w÷–π¨÷±Ω¯£¨“ª Ω°∏∞◊…ﬂÕ¬–≈°π∂‘◊º$nµƒºÁæÆ—®¥Ã≥ˆ“ªΩ£",
                "lian":
        "$N ÷÷–$w÷–π¨÷±Ω¯£¨“ª Ω°∏∞◊…ﬂÕ¬–≈°π∂‘◊º◊Û«∞∑Ω–±¥Ã“ªΩ£......",
                "jibie":40,
                "limb":"ºÁÕ∑",
                "zhaoshi":"∞◊…ﬂÕ¬–≈",
                "sen": 12,
		"dodge":30 ,
                "damage":50,
		"damage_type":	"¥Ã…À"
	]),
	([	"action":
        "$Nµƒ$w∆æø’“ª÷∏£¨“ª’–°∏Ω’Î÷∏ƒœ°π£¨$wÃ¯∂Ø◊≈¥ÃœÚ$nµƒæ±≤ø.......",
                "lian":
        "$Nµƒ$w∆æø’“ª÷∏£¨“ª’–°∏Ω’Î÷∏ƒœ°π£¨$wÃ¯∂Ø◊≈¥ÃœÚ…œ∑Ω.......",
                "jibie":62,
                "zhaoshi":"°∏Ω’Î÷∏ƒœ°π",
                "sen": 10,
                "limb":"æ±≤ø",
		"dodge":		20,
		"damage":		70,
		"damage_type":	"¥Ã…À"
	]),
    ([  "action":"$N◊Û ÷ƒÛ¡À∏ˆΩ£æ˜£¨”“ ÷“ª’–°∏∂˛¿…µ£…Ω°π£¨ ÷÷–$w∂‘◊º$n“ªµ„",
        "lian"  :"$N◊Û ÷ƒÛ¡À∏ˆΩ£æ˜£¨”“ ÷“ª’–°∏∂˛¿…µ£…Ω°π£¨ ÷÷–$w«·«·“ªµ„°£",
        "sen"   :4,
        "jibie" :20,
        "dodge" :40,
        "parry" :30,
        "zhaoshi":"°∏∂˛¿…µ£…Ω°π",
        "damage":5,
        "damage_type":"¥Ã…À"    ]),
    ([  "action":"÷ªº˚$Nπ≠≤Ω…œ«∞£¨À´ ÷ΩÙŒ’$w£¨“ª’–°∏∑ÔªÀ’π“Ì°π£¨œÚ$nµƒÕ∑≤ø”…œ¬∂¯…œ“ª¡√",
        "lian"  :"$N“ª∏ˆπ≠≤Ω£¨ π≥ˆ“ª’–°∏∑ÔªÀ’π“Ì°π£¨ ÷÷–$wÕ˘…œ“ª¡√°£",
        "sen"   :5,
        "jibie" :30,
        "dodge" :30,
        "parry" :30,
        "zhaoshi":"°∏∑ÔªÀ’π“Ì°π",
        "damage":50,
        "damage_type":"∏Ó…À"    ]),
    ([  "action":"$N ÷ƒ√$w£¨“ª’–°∏√Õª¢∞⁄Œ≤°π£¨œÚ$nµƒ$l∑…ÀŸ“ªª˜",
        "lian"  :"$N ÷ƒ√$w£¨“ª’–°∏√Õª¢∞⁄Œ≤°π£¨øÏÀŸª˜≥ˆ°£",
        "sen"   :5,
        "jibie" :40,
        "dodge" :10,
        "parry" :10,
        "zhaoshi":"°∏√Õª¢∞⁄Œ≤°π",
        "damage":60,
        "damage_type":"∏Ó…À"    ]),
});

string *parry_msg = ({
    "$n π≥ˆ“ª’–°∏À≥∑Á…®“∂°π£¨ ÷÷–µƒ$vªØ◊˜“ªÃı≥§∫Á£¨øƒø™¡À$Nµƒ$w°£\n",
    "$n π≥ˆ“ª’–°∏◊Û”“Ã·¬Ø°π£¨ ÷÷–µƒ$vªØ◊ˆ¬˛ÃÏ—©”∞£¨µ¥ø™¡À$Nµƒ$w°£\n",
    "$n ÷÷–µƒ$v“ª∂∂£¨“ª’–°∏‘∆»∏∑…ø’°π£¨œÚ$Nƒ√$wµƒ ÷ÕÛœ˜»•°£\n",
    "$n π≥ˆ“ª’–°∏πÚÃ¯∆Àª¢°π£¨$w÷±¥Ã$NµƒÀ´ ÷°£\n",
});

string *unarmed_parry_msg = ({
    "$nÀ´ ÷ŒËµ√√‹≤ªÕ∏∑Á£¨ π≥ˆ°∏À≥∑Á…®“∂°π£¨∑‚◊°¡À$Nµƒπ• ∆°£\n",
    "$n∑¥ ÷“ª’–°∏◊Û”“Ã·¬Ø°°π£¨±‹ø™¡À$Nµƒ’‚“ª’–°£\n",
    "$n π≥ˆ“ª’–°∏‘∆»∏∑…ø’°π£¨º‹◊°¡À$Nµƒπ• ∆°£\n",
    "µ´º˚$n“ª’–°∏πÚÃ¯∆Àª¢°π£¨∆»µ√$N¡¨¡¨∫ÛÕÀ°£\n",
});

int valid_learn(object me)
{
    return 1;
}

int valid_lian( object me )
{   
    object ob = me->query_temp("weapon");
    if ( !ob || (string)ob->query("weapon_type") != "sword" )
    {   
        write("ƒ„±ÿ–Îœ»’““ª∞—Ω£≤≈ƒ‹¡∑Ω£∑®°£\n");
        return 0;
    }
    return 1;
}

mapping query_action(int jibie)
{
	int i, size;

	size = sizeof( action );
	for ( i = 0; i < sizeof( action ); i++ )
		if ( action[ i ][ "jibie" ] > jibie )
		{
			size = i;
			break;
		}
    return action[ random( size ) ];
}

string query_parry_msg(object weapon)
{   
    if ( weapon )
        return parry_msg[random(sizeof(parry_msg))];
    else
        return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
}

string query_xiuwei_type() { return "sword"; }      
string query_weapon_type() { return "sword"; }

int query_dengji() { return 2; }

int query_youxiao_jibie() { return 9; }

int query_parry_ratio() { return 12; }
