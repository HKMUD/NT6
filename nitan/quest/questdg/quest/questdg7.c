#include <ansi.h>
#define QUESTDG_D(x)      ("/quest/questdg/quest/questdg" + x)

mapping query_questdg() 
{
        mapping questdg = ([]);

        if (random(10) == 5)
                questdg = QUESTDG_D("7find")->query_questdg();
        else if (random(1) == 1)
                questdg = QUESTDG_D("7find")->query_questdg();
        else
        questdg = QUESTDG_D("7kill")->query_questdg();
        if (questdg["type"] == "—∞") 
        {
                if (random(5) == 3)
                {
                        questdg["type"] = "ÀÕ";
                        questdg["name"] = "ªÿ÷¥";
                }
        } 
        if (questdg["type"] == "…±") 
        {
                if (random(3) == 2)
                {
                        questdg["type"] = "«‹";
                }
        } 
        return questdg;
}
