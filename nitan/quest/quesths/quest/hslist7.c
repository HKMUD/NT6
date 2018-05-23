#include <ansi.h>

mapping *quest = ({
        ([
                "id" :    "yue er",
                "name" :  "ÔÂ¶ù",
                "bonus":  75,
                "type":   "É±",
        ]),
        ([
                "id" :    "cloth",
                "name" :  "²¼ÒÂ",
                "bonus":  50,
                "type":   "Ñ°",
        ]),
        ([
                "id" :    "cloth",
                "name" :  "²¼ÒÂ",
                "bonus":  60,
                "type":   "Õ÷",
                "object": "/d/city/obj/cloth.c",
        ]),
        ([
                "id" :    "cloth",
                "name" :  "²¼ÒÂ",
                "bonus":  60,
                "type":   "ËÍ",
                "object": "/d/city/obj/cloth.c",
        ]),
});

mapping query_quest()
{
        return quest[random(sizeof(quest))];
}
