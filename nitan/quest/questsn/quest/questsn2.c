#include <ansi.h>
#define QUESTSN_D(x)      ("/quest/questsn/quest/questsn" + x)

mapping query_quest() 
{
        mapping questsn;
        if (random(50) == 25)
                questsn = QUESTSN_D("7find")->query_questsn();
        else if (random(2) == 1)
                questsn = QUESTSN_D("2find")->query_questsn();
        else
        questsn = QUESTSN_D("2kill")->query_questsn();
        if (questsn["type"] == "—∞") 
        {
                if (random(5) == 3)
                {
                        questsn["type"] = "ÀÕ";
                        questsn["name"] = "ªÿ÷¥";
                }
        } 
        return questsn;
}
