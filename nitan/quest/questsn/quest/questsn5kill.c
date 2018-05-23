#include <ansi.h>

mapping *quest = ({
        ([
                "id":          "jian seng",
                "name":        "½£É®",
                "type":        "É±",
                "bonus":       72,
                "msg":        "",
                "object":      "/d/tulong/yitian/npc/18jingang-5jian.c",
        ]),
        ([
                "id":          "gongye qian",
                "name":        "¹«Ò±Ç¬",
                "type":        "É±",
                "bonus":       87,
                "msg":        "",
                "object":      "/d/yanziwu/npc/gongye.c",
        ]),
        ([
                "id":          "dao seng",
                "name":        "µ¶É®",
                "type":        "É±",
                "bonus":       74,
                "msg":        "",
                "object":      "/d/tulong/yitian/npc/18jingang-5dao.c",
        ]),
        ([
                "id":          "yu canghai",
                "name":        "Óà²×º£",
                "type":        "É±",
                "bonus":       105,
                "msg":        "",
                "object":      "/kungfu/class/qingcheng/yu.c",
        ]),
        ([
                "id":          "feng boe",
                "name":        "·ç²¨¶ñ",
                "type":        "É±",
                "bonus":       73,
                "msg":        "",
                "object":      "/d/yanziwu/npc/feng.c",
        ]),
        ([
                "id":          "zhao banshan",
                "name":        "ÕÔ°ëÉ½",
                "type":        "É±",
                "bonus":       105,
                "msg":        "",
                "object":      "/d/hangzhou/honghua/zhao.c",
        ]),
        ([
                "id":          "deng baichuan",
                "name":        "µË°Ù´¨",
                "type":        "É±",
                "bonus":       100,
                "msg":        "",
                "object":      "/d/yanziwu/npc/deng.c",
        ]),
        ([
                "id":          "bai zhen",
                "name":        "°×Õñ",
                "type":        "É±",
                "bonus":       70,
                "msg":        "",
                "object":      "/d/hangzhou/npc/baizhen.c",
        ]),
        ([
                "id":          "yuzhen zi",
                "name":        "ÓñÕæ×Ó",
                "type":        "É±",
                "bonus":       85,
                "msg":        "",
                "object":      "/d/guanwai/npc/yuzhenzi.c",
        ]),
        ([
        "id":          "fei bin",
                "name":        "·Ñ±ò",
                "type":        "É±",
                "bonus":       85,
                "msg":        "",
                "object":      "/kungfu/class/songshan/fei.c",
        ]),
        ([
                "id":          "bao butong",
                "name":        "°ü²»Í¬",
                "type":        "É±",
                "bonus":       80,
                "msg":        "",
                "object":      "/d/yanziwu/npc/bao.c",
        ]),
        ([
                "id":          "mu wanqing",
                "name":        "Ä¾ÍñÇå",
                "type":        "É±",
                "bonus":       80,
                "msg":        "",
                "object":      "/d/wanjiegu/npc/mu.c",
        ]),
        ([
                "id":          "nv lang",
                "name":        "ÃÉÃæÅ®ÀÉ",
                "type":        "É±",
                "bonus":       75,
                "msg":        "",
                "object":      "/d/lingjiu/npc/nvlang.c",
        ]),
        ([
                "id":          "lazhang huofo",
                "name":        "À­ÕÂ»î·ð",
                "type":        "É±",
                "bonus":       72,
                "msg":        "",
                "object":      "/kungfu/class/xueshan/lazhang.c",
        ]),
        ([
                "id":          "sheng di",
                "name":        "Ê¤ÚÐ",
                "type":        "É±",
                "bonus":       89,
                "msg":        "",
                "object":      "/kungfu/class/xuedao/shengdi.c",
        ]),
        ([
                "id":          "zhang danyue",
                "name":        "ÕÅµ­ÔÂ",
                "type":        "É±",
                "bonus":       82,
                "msg":        "",
                "object":      "/kungfu/class/shenlong/zhang.c",
        ]),
        ([
                "id":          "wugen daozhang",
                "name":        "ÎÞ¸ùµÀ³¤",
                "type":        "É±",
                "bonus":       97,
                "msg":        "",
                "object":      "/kungfu/class/shenlong/wugen.c",
        ]),
        ([
                "id":          "su quan",
                "name":        "ËÕÜõ",
                "type":        "É±",
                "bonus":       87,
                "msg":        "",
                "object":      "/kungfu/class/shenlong/su.c",
        ]),
        ([
                "id":          "yu hongxing",
                "name":        "ÓàºéÐË",
                "type":        "É±",
                "bonus":       80,
                "msg":        "",
                "object":      "/kungfu/class/gaibang/yu-hx.c",
        ]),
        ([
                "id":          "quan guanqing",
                "name":        "È«¹ÚÇå",
                "type":        "É±",
                "bonus":       75,
                "msg":        "",
                "object":      "/kungfu/class/gaibang/quan-gq.c",
        ]),
        ([
                "id":          "li sheng",
                "name":        "ÀèÉú",
                "type":        "É±",
                "bonus":       73,
                "msg":        "",
                "object":      "/kungfu/class/gaibang/li-sh.c",
        ]),
});
mapping query_questsn()
{
        int i;
        mapping the_quest,random_quest;
        string *quest_key;

        random_quest = quest[random(sizeof(quest))];
        the_quest = ([]);

        quest_key = keys(random_quest);
        for (i = 0;i < sizeof(quest_key);i++)
                the_quest[quest_key[i]] = random_quest[quest_key[i]];

        return the_quest;
}
