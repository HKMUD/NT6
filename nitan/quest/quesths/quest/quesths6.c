#include <ansi.h>
#define QUESTHS_D(x)      ("/quest/quesths/quest/quesths" + x)

mapping query_quesths() 
{
        mapping quesths = ([]);
        if (random(50) == 25)
                quesths = QUESTHS_D("7find")->query_quesths();
        else if (random(2) == 1)
                quesths = QUESTHS_D("6find")->query_quesths();
        else
        quesths = QUESTHS_D("6kill")->query_quesths();
        if (quesths["type"] == "Ñ°") 
        {
                if (random(5) == 3)
                {
                        quesths["type"] = "ËÍ";
                        quesths["name"] = "»ØÖ´";
                } else 
                if (random(5) == 2)
                {
                        quesths["type"] = "Õ÷";
                }
        } 
        return quesths;
}
