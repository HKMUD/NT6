// This program is a part of NT MudLIB
// party_questd.c

#pragma optimize
#pragma save_binary

inherit F_DBASE;

#include <ansi.h>
#include <command.h>
#include <npc/name.h>
#include <npc/chinese.c>
#include <npc/japanese.c>
#include <npc/european.c>
#include <npc/masia.c>
#include <npc/indian.c>

#define MIN_IDLE        30              // ɱ��������Сʱ����
#define MAX_MOVED       5               // NPC����߶��ķ�Χ
#define WAIT_TIME       600             // ������ʱ��
#define HEARTBEAT       10              // ����ϵͳ����
#define QUEST_NUM       5               // ÿ�������б�����������

// �����е���Ʒֱ�ӵ�����ʦ�������Ʒ�б�
#define QUEST_GOOD_OBJ(x)     ("/quest/questdg/quest/questdg" + x)
#define QUEST_BAD_OBJ(x)      ("/quest/questkh/quest/questkh" + x)

mapping *bunch_zs = ({});

mapping bunch_city_quest = ([
        "bje" : ({ }),
        "bjw" : ({ }),
        "yz"  : ({ }),
        "ca"  : ({ }),
        "cd"  : ({ }),
        "sz"  : ({ }),
        "hz"  : ({ }),
        "xy"  : ({ }),
        "dl"  : ({ }),
]);

string *need_send_msg = ({
        "���պڵ�����Ҫ�д�ٶ�����ú�׼��׼����",
        "ע��һ�»�ɽ�ɵ��ӵľٶ���",
        "ע��һ�º�ɽ�ɵ��ӵľٶ���",
        "ע��һ�������ɵ��ӵľٶ���",
        "ע��һ�¶��ϻ�����ӵľٶ���",
        "ע��һ��Ľ�����ҵľٶ���",
        "ע��һ�¹�����ҵľٶ���",
        "��̽һ�º�������������",
        "ע��һ���һ������ӵľٶ���",
        "�׵����˵��ж������е����أ���úù۲졣",
});

string *bad_msg1 = ({
        "name���Ǹ����Ǻڵ����ԣ�",
        "������׵�name���α�����ˣ�",
        "��Ϳ�name����һﲻ˳�ۣ�",
        "name�ϴ�ɱ������һ���ڵ��ֵ���������",
        "name˫��մ�������Ǻڵ��ֵܵ���Ѫ��",
        "�Դ�name�����������ֵܣ�һֱ���Ų�¶�棬",
        "nameΥ�����ϵĹ�أ�",
        "��˵��name�����ֵܵ�����ɣ�",
        "�ǵ�ȥ��nameͶ���׵�������ɣ�",
        "name�����ν���˾���ɱ�������Ǻܶ���֣�",
        "����ڰ׵���������������������name����ͷ��������",
        "����ڵ�����ƣ�����ý�name����ͷ��������ʿ����",
        "����name�����Ǻڵ����������Բ�ѷ��",
        "name���վ�Ȼ����Ҫ��ƽ���Ǻڵ��ܶ棬",
        "name���С��������Ϊ���������Ǻڵ�������",
        "�ܶ�����С���Ÿ�name�������ˣ�",
});

string *bad_msg2 = ({
        "�����Ǳ����placeһ����",
        "�е��������place�����������ټ���",
        "�������˿�������place��û��",
        "����������place��һ�ҿ͵���֣�",
        "�����峿����place���Ż�����У�",
        "�������͵�����place�����ܻ�δ���ߣ�",
        "place��һ�ҿ͵��������һ���������",
        "������װ��������place��",
        "place���˸�İ���˾�ֹ���죬",
        "place���е��ָ�����һ��۸��ˣ�",
        "place�ڵ��ֵ�˵ǰ��������һ���һ��������",
        "������ܿ�����placeһ����",
        "��������ǰ��placeһ����",
        "����һ��������place����������ȥ�����������",
        "place����һ�������ѵ㣬��֪�����Ƿ�Ǳ�������",
        "�������еط����������ˣ�ֻʣ��place��ûȫ��������",
});

string *bad_msg3 = ({
        "�����ǸϿ�ȥ�������ˡ�",
        "������ȥ�������������Ͳ�Ҫ�������顣",
        "��Ҫ�����ټ��������̫����",
        "���������������������ˡ�",
        "������Ѫ�������Ǻڵ�������ɡ�",
        "������֪������ô���˰ɣ�",
        "�ҵ�����ɱ���⣡",
        "ֻҪ�ҵ�������ɱ���ۣ�",
});

string *good_msg1 = ({
        "name�����ˣ�",
        "��������name��������ˣ�",
        "��name���ħ���ǰ׵���ʿ��ȥ̫�����˵㣬",
        "name�ϴ�ɱ������һ��ͬ����������",
        "name˫��մ��������������ʿ����Ѫ��",
        "�Դ�name�����������ֵܣ�һֱ���Ų�¶�棬",
        "nameΥ������������ʿ������׼��",
        "��˵��name�����ֵܵ�����ɣ�",
        "�ǵ�ȥ��nameͶ��ħ�̵�����ɣ�",
        "name���ɫ��Ϊ�������Ѿã�",
        "����ڰ׵��������𣬲�ȡ��name����ͷ�����Ժ���������",
        "�������������ʿ�������ڵ���ѹ��name����ͷ������������ʿ����",
        "����name���������ɳ��Բ�ѷ��",
        "name���վ�Ȼ����Ҫ��ƽ���ǰ׵��ܲ���",
        "name���С��������Ϊ����������������ʿ������",
        "name�Ժ��ζģ��޶�����",
});

string *good_msg2 = ({
        "�����Ǳ����placeһ����",
        "�е��������place�����������ټ���",
        "�������˿�������place��û��",
        "����������place��һ�Ҷĳ����֣�",
        "�����峿����place���Ż�����У�",
        "�������͵�����place�����ܻ�δ���ߣ�",
        "place��һ�ҿ͵��������һ��İ���ˣ�",
        "������װ��������place��",
        "place���˸�İ���˾�ֹ���죬",
        "place���е��ָ�����һ��۸��ˣ�",
        "place���ֵ�˵ǰ��������һ���һ��������",
        "������ܿ�����placeһ����",
        "��������ǰ��placeһ����",
        "����һ��С���place����������������",
        "place����һ�������ѵ㣬��֪�����Ƿ�Ǳ�������",
        "�������еط����������ˣ�ֻʣ��place��ûȫ��������",
});

string *good_msg3 = ({
        "�����ǸϿ�ȥ���������ˡ�",
        "������ȥ�������������Ͳ�Ҫ�������顣",
        "��Ҫ������Ϊ�������ˡ�",
        "���������������������ˡ�",
        "������Ѫ����а�����һ�����档",
        "������֪������ô���˰ɣ�",
        "�ҵ�����ɱ���⣡",
        "ֻҪ�ҵ�������ɱ���ۣ�",
});

string *search_msg = ({
        "����������̽���ֵ�������",
        "���ǵļ������������Ϣ��",
        "ͨ���ķ�������",
        "���ǵ��ֵ�����������ҹ����׷�飬",
        "�����ķ�������������Ϣ��",
        "���ֵܴ�ؤ���׵�����Ϣ��",
        "����Ϣ��ͨ��ʿ͸¶��",
});

mapping levels = ([
//      combat_exp   skill_level
        10000      : 45,               // level 1
        16000      : 55,               // level 2
        27000      : 65,               // level 3
        41000      : 75,               // level 4
        60000      : 85,               // level 5
        84000      : 95,               // level 6
        120000     : 105,              // level 7
        150000     : 115,              // level 8
        190000     : 125,              // level 9
        240000     : 135,              // level 10
        300000     : 145,              // level 11
        370000     : 155,              // level 12
        440000     : 165,              // level 13
        530000     : 175,              // level 14
]);

nosave mapping city = ([
        "bje" : "��������",
        "bjw" : "��������",
        "yz"  : "���ݳ�",
        "ca"  : "������",
        "cd"  : "�ɶ���",
        "sz"  : "���ݳ�",
        "hz"  : "���ݳ�",
        "xy"  : "������",
        "dl"  : "����һ��",
]);

nosave mapping static_npc = ([
        "bje"     : ([
                        "/d/beijing/caishi.c"   :  "ju min",
                        "/d/beijing/caishi.c"   :  "cai fan",
                        "/d/beijing/cagc_s.c"   :  "shuahou ren",
                        "/d/beijing/cagc_s.c"   :  "xian ren",
                        "/d/beijing/zhuang8.c"  :  "dizi",
                        "/d/beijing/chaoyang_dao1.c"    :  "tang zi",
                        "/d/beijing/chaoyang_dao2.c"    :  "tiao fu",
                        "/d/beijing/ximenkou.c" :  "old man",
                        "/d/beijing/ximenkou.c" :  "tang zi",
                        "/d/beijing/ximenkou.c" :  "tiao fu",
                        "/d/beijing/tiepu.c"    :  "huoji",
                        "/d/beijing/tiepu.c"    :  "tie jiang",
                        "/d/beijing/yongdingdao.c"      :  "kid",
                        "/d/beijing/yongdingdao.c"      :  "tiao fu",
                        "/d/beijing/yongdingdao.c"      :  "tang zi",
                        "/d/beijing/guandao_1.c"        :  "tang zi",
                        "/d/beijing/qingmu_dating.c"    :  "chen jinnan",
                        "/d/beijing/road9.c"    :  "tangzi shou",
                        "/d/beijing/road4.c"    :  "jian ke",
                        "/d/beijing/road1.c"    :  "tiao fu",
                        "/d/beijing/road5.c"    :  "seng ren",
                        "/d/beijing/road2.c"    :  "tangzi shou",
                        "/d/beijing/road3.c"    :  "shu sheng",
                        "/d/beijing/road7.c"    :  "jianghu haoke",
                        "/d/beijing/qingmu_dayuan.c"    :  "xuan zhen",
                        "/d/beijing/di_dajie2.c"        :  "di pi",
                        "/d/beijing/di_dajie2.c"        :  "tiao fu",
                        "/d/beijing/di_donggc.c"        :  "kid",
                        "/d/beijing/di_donggc.c"        :  "shao fu",
                        "/d/beijing/di_donggc.c"        :  "liu mang",
                        "/d/beijing/dianmen.c"  :  "old man",
                        "/d/beijing/dianmen.c"  :  "kid",
                        "/d/beijing/di_xigc.c"  :  "hun hun",
                        "/d/beijing/di_xigc.c"  :  "xian ren",
                        "/d/beijing/dong_3.c"   :  "shu sheng",
                        "/d/beijing/di_4.c"     :  "boy",
                        "/d/beijing/di_1.c"     :  "you ren",
                        "/d/beijing/di_3.c"     :  "di pi",
                        "/d/beijing/di_1.c"     :  "kid",
                        "/d/beijing/di_3.c"     :  "tiao fu",
                        "/d/beijing/di_1.c"     :  "xiu cai",
                        "/d/beijing/cagc_e.c"   :  "shu sheng",
                        "/d/beijing/cagc_e.c"   :  "xian ren",
                        "/d/beijing/caroad_e2.c"        :  "old woman",
                        "/d/beijing/caroad_e1.c"        :  "girl",
                        "/d/beijing/caroad_e2.c"        :  "hun hun",
                        "/d/beijing/caroad_e1.c"        :  "ju min",
                        "/d/beijing/haigang.c"          :  "lao chuanfu",
                        "/d/beijing/tianqiao.c"         :  "boy",
                        "/d/beijing/tianqiao.c"  :  "old woman",
                        "/d/beijing/tianqiao.c"  :  "xiao fan",
                        "/d/beijing/tianqiao.c"  :  "xian ren",
                        "/d/beijing/tianqiao.c"  :  "maiyi ren",
                        "/d/beijing/gaosheng.c"  :  "cha ke",
                        "/d/beijing/gaosheng.c"  :  "cha boshi",
                        "/d/beijing/gaosheng.c"  :  "old man",
                        "/d/beijing/gaosheng.c"  :  "chapu huoji",
                        "/d/beijing/guozijian.c" :  "shu sheng",
                        "/d/beijing/duchang.c"  :  "liu mang",
                        "/d/beijing/duchang.c"  :  "di pi",
                        "/d/beijing/duchang.c"  :  "du ke",
                        "/d/beijing/duchang.c"  :  "jianghu haoke",
                        "/d/beijing/fu_2.c"  :  "jianghu haoke",
                        "/d/beijing/fu_2.c"  :  "shao fu",
                        "/d/beijing/huichuntang.c"  :  "kid",
                        "/d/beijing/huichuntang.c"  :  "old man",
                        "/d/beijing/huichuntang.c"  :  "yaopu huoji",
                        "/d/beijing/huiying.c"  :  "xiao er",
                        "/d/beijing/huiyingup.c"  :  "qian erbai",
                        "/d/beijing/huiyingup.c"  :  "zhao min",
                        "/d/beijing/huiyingup.c"  :  "zhao yishang",
                        "/d/beijing/qiao.c"  :  "xiao fan",
                        "/d/beijing/kedian.c"  :  "chen laotou",
                        "/d/beijing/kedian.c"  :  "you ren",
                        "/d/beijing/niaoshi.c"  :  "xiu cai",
                        "/d/beijing/niaoshi.c"  :  "fujia dizi",
                        "/d/beijing/qingmu_fang3.c"  :  "fan gang",
                        "/d/beijing/qingmu_fang3.c"  :  "qi biaoqing",
                        "/d/beijing/qingmu_fang2.c"  :  "guan anji",
                        "/d/beijing/qingmu_fang3.c"  :  "feng jizhong",
                        "/d/beijing/qingmu_fang2.c"  :  "jia laoliu",
                        "/d/beijing/qingmu_fang2.c"  :  "qian laoben",
                        "/d/beijing/qingmu_fang1.c"  :  "xu tianchuan",
                        "/d/beijing/huangling.c"  :  "you ren",
                        "/d/beijing/minju_y.c"  :  "ju min",
                        "/d/beijing/tiananmen.c"  :  "kid",
                        "/d/beijing/tiananmen.c"  :  "maiyi ren",
                        "/d/beijing/tiananmen.c"  :  "old man",
                        "/d/beijing/tiantan.c"  :  "you ren",
                        "/d/beijing/tiantan_n.c"  :  "shao fu",
                        "/d/beijing/cagc_w.c"  :  "shao fu",
                        "/d/beijing/cagc_w.c"  :  "xiu cai",
                        "/d/beijing/cagc_w.c"  :  "girl",
                        "/d/beijing/caroad_w1.c"  :  "kid",
                        "/d/beijing/caroad_w2.c"  :  "shu sheng",
                        "/d/beijing/caroad_w2.c"  :  "fujia dizi",
                        "/d/beijing/caroad_w1.c"  :  "jianghu haoke",
                        "/d/beijing/caroad_w2.c"  :  "boy",
                        "/d/beijing/xi_2.c"  :  "man",
                        "/d/beijing/xi_2.c"  :  "shao fu",
                        "/d/beijing/xi_1.c"  :  "tiao fu",
                        "/d/beijing/xi_1.c"  :  "boy",
                        "/d/beijing/xi_2.c"  :  "xiao fan",
                        "/d/beijing/bei_1.c"  :  "you ren",
                        "/d/beijing/bei_3.c"  :  "girl",
                        "/d/beijing/bei_4.c"  :  "you ren",
                        "/d/beijing/shi_2.c"  :  "boy",
                        "/d/beijing/shi_1.c"  :  "liu mang",
                        "/d/beijing/huadian.c"  :  "shao nv",
                        "/d/beijing/road10.c"  :  "tiao fu",
                        "/d/beijing/zhuang9.c"  :  "san furen",
                        "/d/beijing/zhuang1.c"  :  "seng ren",
                        "/d/beijing/xiaotan.c"  :  "youke",
                        "/d/beijing/xiaotan.c"  :  "xiao er",
                        "/d/beijing/yancao.c"  :  "old man",
                        "/d/beijing/yangliu1.c"  :  "old woman",
                        "/d/beijing/liandan_yaoshi.c"  :  "yao chun",
                        "/d/beijing/yong_1.c"  :  "di pi",
                        "/d/beijing/yong_1.c"  :  "boy",
                    ]),
        "bjw"     : ([
                        "/d/beijing/caishi.c"  :  "ju min",
                        "/d/beijing/caishi.c"  :  "cai fan",
                        "/d/beijing/cagc_s.c"  :  "shuahou ren",
                        "/d/beijing/cagc_s.c"  :  "xian ren",
                        "/d/beijing/zhuang8.c"  :  "dizi",
                        "/d/beijing/chaoyang_dao1.c"  :  "tang zi",
                        "/d/beijing/chaoyang_dao2.c"  :  "tiao fu",
                        "/d/beijing/ximenkou.c"  :  "old man",
                        "/d/beijing/ximenkou.c"  :  "tang zi",
                        "/d/beijing/ximenkou.c"  :  "tiao fu",
                        "/d/beijing/tiepu.c"  :  "huoji",
                        "/d/beijing/tiepu.c"  :  "tie jiang",
                        "/d/beijing/yongdingdao.c"  :  "kid",
                        "/d/beijing/yongdingdao.c"  :  "tiao fu",
                        "/d/beijing/yongdingdao.c"  :  "tang zi",
                        "/d/beijing/guandao_1.c"  :  "tang zi",
                        "/d/beijing/qingmu_dating.c"  :  "chen jinnan",
                        "/d/beijing/road9.c"  :  "tangzi shou",
                        "/d/beijing/road4.c"  :  "jian ke",
                        "/d/beijing/road1.c"  :  "tiao fu",
                        "/d/beijing/road5.c"  :  "seng ren",
                        "/d/beijing/road2.c"  :  "tangzi shou",
                        "/d/beijing/road3.c"  :  "shu sheng",
                        "/d/beijing/road7.c"  :  "jianghu haoke",
                        "/d/beijing/qingmu_dayuan.c"  :  "xuan zhen",
                        "/d/beijing/di_dajie2.c"  :  "di pi",
                        "/d/beijing/di_dajie2.c"  :  "tiao fu",
                        "/d/beijing/di_donggc.c"  :  "kid",
                        "/d/beijing/di_donggc.c"  :  "shao fu",
                        "/d/beijing/di_donggc.c"  :  "liu mang",
                        "/d/beijing/dianmen.c"  :  "old man",
                        "/d/beijing/dianmen.c"  :  "kid",
                        "/d/beijing/di_xigc.c"  :  "hun hun",
                        "/d/beijing/di_xigc.c"  :  "xian ren",
                        "/d/beijing/dong_3.c"  :  "shu sheng",
                        "/d/beijing/di_4.c"  :  "boy",
                        "/d/beijing/di_1.c"  :  "you ren",
                        "/d/beijing/di_3.c"  :  "di pi",
                        "/d/beijing/di_1.c"  :  "kid",
                        "/d/beijing/di_3.c"  :  "tiao fu",
                        "/d/beijing/di_1.c"  :  "xiu cai",
                        "/d/beijing/cagc_e.c"  :  "shu sheng",
                        "/d/beijing/cagc_e.c"  :  "xian ren",
                        "/d/beijing/caroad_e2.c"  :  "old woman",
                        "/d/beijing/caroad_e1.c"  :  "girl",
                        "/d/beijing/caroad_e2.c"  :  "hun hun",
                        "/d/beijing/caroad_e1.c"  :  "ju min",
                        "/d/beijing/haigang.c"  :  "lao chuanfu",
                        "/d/beijing/tianqiao.c"  :  "boy",
                        "/d/beijing/tianqiao.c"  :  "old woman",
                        "/d/beijing/tianqiao.c"  :  "xiao fan",
                        "/d/beijing/tianqiao.c"  :  "xian ren",
                        "/d/beijing/tianqiao.c"  :  "maiyi ren",
                        "/d/beijing/gaosheng.c"  :  "cha ke",
                        "/d/beijing/gaosheng.c"  :  "cha boshi",
                        "/d/beijing/gaosheng.c"  :  "old man",
                        "/d/beijing/gaosheng.c"  :  "chapu huoji",
                        "/d/beijing/guozijian.c"  :  "shu sheng",
                        "/d/beijing/duchang.c"  :  "liu mang",
                        "/d/beijing/duchang.c"  :  "di pi",
                        "/d/beijing/duchang.c"  :  "du ke",
                        "/d/beijing/duchang.c"  :  "jianghu haoke",
                        "/d/beijing/fu_2.c"  :  "jianghu haoke",
                        "/d/beijing/fu_2.c"  :  "shao fu",
                        "/d/beijing/huichuntang.c"  :  "kid",
                        "/d/beijing/huichuntang.c"  :  "old man",
                        "/d/beijing/huichuntang.c"  :  "yaopu huoji",
                        "/d/beijing/huiying.c"  :  "xiao er",
                        "/d/beijing/huiyingup.c"  :  "qian erbai",
                        "/d/beijing/huiyingup.c"  :  "zhao min",
                        "/d/beijing/huiyingup.c"  :  "zhao yishang",
                        "/d/beijing/qiao.c"  :  "xiao fan",
                        "/d/beijing/kedian.c"  :  "chen laotou",
                        "/d/beijing/kedian.c"  :  "you ren",
                        "/d/beijing/niaoshi.c"  :  "xiu cai",
                        "/d/beijing/niaoshi.c"  :  "fujia dizi",
                        "/d/beijing/qingmu_fang3.c"  :  "fan gang",
                        "/d/beijing/qingmu_fang3.c"  :  "qi biaoqing",
                        "/d/beijing/qingmu_fang2.c"  :  "guan anji",
                        "/d/beijing/qingmu_fang3.c"  :  "feng jizhong",
                        "/d/beijing/qingmu_fang2.c"  :  "jia laoliu",
                        "/d/beijing/qingmu_fang2.c"  :  "qian laoben",
                        "/d/beijing/qingmu_fang1.c"  :  "xu tianchuan",
                        "/d/beijing/huangling.c"  :  "you ren",
                        "/d/beijing/minju_y.c"  :  "ju min",
                        "/d/beijing/tiananmen.c"  :  "kid",
                        "/d/beijing/tiananmen.c"  :  "maiyi ren",
                        "/d/beijing/tiananmen.c"  :  "old man",
                        "/d/beijing/tiantan.c"  :  "you ren",
                        "/d/beijing/tiantan_n.c"  :  "shao fu",
                        "/d/beijing/cagc_w.c"  :  "shao fu",
                        "/d/beijing/cagc_w.c"  :  "xiu cai",
                        "/d/beijing/cagc_w.c"  :  "girl",
                        "/d/beijing/caroad_w1.c"  :  "kid",
                        "/d/beijing/caroad_w2.c"  :  "shu sheng",
                        "/d/beijing/caroad_w2.c"  :  "fujia dizi",
                        "/d/beijing/caroad_w1.c"  :  "jianghu haoke",
                        "/d/beijing/caroad_w2.c"  :  "boy",
                        "/d/beijing/xi_2.c"  :  "man",
                        "/d/beijing/xi_2.c"  :  "shao fu",
                        "/d/beijing/xi_1.c"  :  "tiao fu",
                        "/d/beijing/xi_1.c"  :  "boy",
                        "/d/beijing/xi_2.c"  :  "xiao fan",
                        "/d/beijing/bei_1.c"  :  "you ren",
                        "/d/beijing/bei_3.c"  :  "girl",
                        "/d/beijing/bei_4.c"  :  "you ren",
                        "/d/beijing/shi_2.c"  :  "boy",
                        "/d/beijing/shi_1.c"  :  "liu mang",
                        "/d/beijing/huadian.c"  :  "shao nv",
                        "/d/beijing/road10.c"  :  "tiao fu",
                        "/d/beijing/zhuang9.c"  :  "san furen",
                        "/d/beijing/zhuang1.c"  :  "seng ren",
                        "/d/beijing/xiaotan.c"  :  "youke",
                        "/d/beijing/xiaotan.c"  :  "xiao er",
                        "/d/beijing/yancao.c"  :  "old man",
                        "/d/beijing/yangliu1.c"  :  "old woman",
                        "/d/beijing/liandan_yaoshi.c"  :  "yao chun",
                        "/d/beijing/yong_1.c"  :  "di pi",
                        "/d/beijing/yong_1.c"  :  "boy",
                    ]),
        "ca"      : ([
                        "/d/changan/baozipu"  :  "huo ji",
                        "/d/changan/baoxiangsi"  :  "monk",
                        "/d/changan/weapon-shop"  :  "murong hao",
                        "/d/changan/tea-shop"  :  "waiter",
                        "/d/changan/tea-shop"  :  "shuoshu laoren",
                        "/d/changan/miao"  :  "keeper",
                        "/d/changan/baodian"  :  "xiang ke",
                        "/d/changan/duchang"  :  "zhuang jia",
                        "/d/changan/fangzhangshi"  :  "huitong chanshi",
                        "/d/changan/guozijian"  :  "li boyuan",
                        "/d/changan/biaoju-dating"  :  "wang yuanba",
                        "/d/changan/huadian"  :  "maihua guniang",
                        "/d/changan/yaopu"  :  "shi jiugong",
                        "/d/changan/huiwenge"  :  "shu chi",
                        "/d/changan/mianguan"  :  "lao zhang",
                        "/d/changan/piandian"  :  "jing ming",
                        "/d/changan/piandian"  :  "jing xuan",
                        "/d/changan/xiaojia-pianting"  :  "yahuan",
                        "/d/changan/shoushi-dian"  :  "chen laoban",
                        "/d/changan/fruit-shop"  :  "zhang lanxiang",
                        "/d/changan/bank"  :  "tie gongji",
                        "/d/changan/tuchangguan"  :  "ji nu",
                        "/d/changan/jiulou"  :  "xiaoer",
                        "/d/changan/jiulou2"  :  "yang laoban",
                        "/d/changan/xiyuan"  :  "xi zi",
                        "/d/changan/dangpu"  :  "xiao wanxi",
                        "/d/changan/xiaojiuguan"  :  "ru hua",
                        "/d/changan/xunbufang"  :  "bu tou",
                        "/d/changan/kezhan"  :  "xiaoer",
                        "/d/changan/zahuopu"  :  "liu laoshi",
                        "/d/changan/zhubaohang"  :  "jin fuhuan",
                     ]),
        "yz"      :  ([
                        "/d/city/beidajie1"  :  "ouyang ke",
                        "/d/city/beimen"  :  "ma chaoxing",
                        "/d/city/dayuan"  :  "guan jia",
                        "/d/city/dayuan"  :  "jia ding",
                        "/d/city/dongxiang"  :  "hong niang",
                        "/d/city/houyuan"  :  "cui yuanwai",
                        "/d/city/xixiang"  :  "cui yingying",
                        "/d/city/garments"  :  "zeng rou",
                        "/d/city/chaguan"  :  "aqing sao",
                        "/d/city/datiepu"  :  "tie jiang",
                        "/d/city/dangpu"  :  "tang nan",
                        "/d/city/duchang"  :  "pang toutuo",
                        "/d/city/huadian"  :  "zi yin",
                        "/d/city/lichunyuan"  :  "mao shiba",
                        "/d/city/lichunyuan"  :  "wei chunfang",
                        "/d/city/lichunyuan"  :  "kong kong",
                        "/d/city/lichunyuan2"  :  "gui gong",
                        "/d/city/neizhai"  :  "cheng yuhuan",
                        "/d/city/nandajie1"  :  "liumang tou",
                        "/d/city/nandajie2"  :  "tuobo seng",
                        "/d/city/nandajie1"  :  "xiao hunhun",
                        "/d/city/nandajie1"  :  "liu mang",
                        "/d/city/nanmen"  :  "shi song",
                        "/d/city/qianzhuang"  :  "qian yankai",
                        "/d/city/shuyuan"  :  "zhu xi",
                        "/d/city/xidajie2"  :  "youfang daoren",
                        "/d/city/ximen"  :  "feng gongying",
                        "/d/city/ximenroad"  :  "boy",
                        "/d/city/yamen"  :  "ya yi",
                        "/d/city/wuguan"  :  "chen youde",
                        "/d/city/yaopu"  :  "ping yizhi",
                        "/d/city/zahuopu"  :  "Yang yongfu",
                        "/d/city/zuixianlou"  :  "xiao er",
                        "/d/city/zuixianlou2"  :  "xian laoban",
                        "/d/city/zuixianlou2"  :  "wang wu",
                     ]),
        "sz"      :  ([
                        "/d/suzhou/bailianchi"  :  "girl",
                        "/d/suzhou/baodaiqiao"  :  "seller",
                        "/d/suzhou/dangpu"  :  "wang heji",
                        "/d/suzhou/chaguan"  :  "girl",
                        "/d/suzhou/jiudian"  :  "xiao er",
                        "/d/suzhou/datiepu"  :  "tie jiang",
                        "/d/suzhou/dongdajie1"  :  "kid",
                        "/d/suzhou/hutong2"  :  "liu mang",
                        "/d/suzhou/hutong2"  :  "liumang tou",
                        "/d/suzhou/jubaozhai"  :  "sun baopi",
                        "/d/suzhou/kedian"  :  "xiao er",
                        "/d/suzhou/yaopu"  :  "yaopu huoji",
                        "/d/suzhou/liuyuan"  :  "girl",
                        "/d/suzhou/shijianshi"  :  "jian ke",
                        "/d/suzhou/shuchang"  :  "gongzi",
                        "/d/suzhou/shuyuan"  :  "lao fuzi",
                        "/d/suzhou/toumenshan"  :  "jian ke",
                        "/d/suzhou/wanjing"  :  "dao ke",
                        "/d/suzhou/wenmeige"  :  "bi nu",
                        "/d/suzhou/xiyuan"  :  "piao you",
                        "/d/suzhou/yanyutang"  :  "ya huan",
                        "/d/suzhou/yingbin-lou1"  :  "xiao er",
                        "/d/suzhou/zhenshi"  :  "seng ren",
                        "/d/suzhou/zhishuang"  :  "girl",
                     ]),
        "cd"      :    ([
                        "/d/chengdu/northroad3"  :  "jianghu haoke",
                        "/d/chengdu/northroad3"  :  "jian ke",
                        "/d/chengdu/bingqidian"  :  "tang huai",
                        "/d/chengdu/eastroad2"  :  "liumang tou",
                        "/d/chengdu/eastroad2"  :  "liu mang",
                        "/d/chengdu/eastroad1"  :  "xiao zei",
                        "/d/chengdu/yaodian"  :  "yaodian huoji",
                        "/d/chengdu/kedian"  :  "xiao er",
                        "/d/chengdu/chufang"  :  "chu niang",
                        "/d/chengdu/southroad3"  :  "dao ke",
                        "/d/chengdu/southroad3"  :  "jian ke",
                        "/d/chengdu/jiudian"  :  "tang",
                        "/d/chengdu/jiudian"  :  "xiao er",
                        "/d/chengdu/westroad1"  :  "seller",
                        "/d/chengdu/westroad1"  :  "liu mang",
                        "/d/chengdu/westroad2"  :  "tangzi shou",
                        "/d/chengdu/westroad3"  :  "jianghu haoke",
                     ]),
        "hz"      :  ([
                        "/d/hangzhou/dalu1"  :  "hong hua",
                        "/d/hangzhou/dalu1"  :  "tiao fu",
                        "/d/hangzhou/duanqiao"  :  "poor man",
                        "/d/hangzhou/faxisi"  :  "lao heshang",
                        "/d/hangzhou/yaodian"  :  "hu qingyu",
                        "/d/hangzhou/jujingyuan"  :  "hong hua",
                        "/d/hangzhou/jujingyuan"  :  "jian ke",
                        "/d/hangzhou/lingyinsi"  :  "lao heshang",
                        "/d/hangzhou/liuzhuang"  :  "guan jia",
                        "/d/hangzhou/liuzhuang"  :  "jia ding",
                        "/d/hangzhou/jiulou"  :  "xiao er",
                        "/d/hangzhou/maojiabu"  :  "old woman",
                        "/d/hangzhou/maojiabu"  :  "boy",
                        "/d/hangzhou/qiantang"  :  "jian ke",
                        "/d/hangzhou/road17"  :  "chu yuan",
                        "/d/hangzhou/road14"  :  "luo bing",
                        "/d/hangzhou/road6"  :  "liumang tou",
                        "/d/hangzhou/road12"  :  "qing bing",
                        "/d/hangzhou/road7"  :  "youfang daoren",
                        "/d/hangzhou/road6"  :  "liu mang",
                        "/d/hangzhou/road19"  :  "dao ke",
                        "/d/hangzhou/road12"  :  "li kexiu",
                        "/d/hangzhou/road14"  :  "wen tailai",
                        "/d/hangzhou/road5"  :  "tiao fu",
                        "/d/hangzhou/road2"  :  "xianghuo daoren",
                        "/d/hangzhou/road19"  :  "long jun",
                        "/d/hangzhou/road5"  :  "hong hua",
                        "/d/hangzhou/road16"  :  "bai zhen",
                        "/d/hangzhou/qingbomen"  :  "girl",
                        "/d/hangzhou/suti4"  :  "li yuanzhi",
                        "/d/hangzhou/suti7"  :  "shu sheng",
                        "/d/hangzhou/kedian"  :  "xiao er",
                        "/d/hangzhou/tiejiangpu"  :  "tiejiang",
                        "/d/hangzhou/tulu1"  :  "boy",
                        "/d/hangzhou/yuquan"  :  "youke",
                        "/d/hangzhou/yuquan"  :  "yue nv",
                     ]),
        "xy"      :  ([
                        "/d/xiangyang/tiejiangpu"  :  "tiejiang",
                        "/d/xiangyang/caodi4"  :  "cheng lingsu",
                        "/d/xiangyang/caodi1"  :  "tuo lei",
                        "/d/xiangyang/juyichufang"  :  "shaofan shifu",
                        "/d/xiangyang/jiekou2"  :  "kid",
                        "/d/xiangyang/jiekou2"  :  "seller",
                        "/d/xiangyang/juyiyuan"  :  "zhu ziliu",
                        "/d/xiangyang/dangpu"  :  "qiu hang",
                        "/d/xiangyang/biaoju"  :  "biao tou",
                        "/d/wuguan/guofu_gate"  :  "wu dunru",
                        "/d/wuguan/guofu_gate"  :  "jia ding",
                        "/d/wuguan/guofu_dayuan2" :  "yelv qi",
                        "/d/wuguan/guofu_dating"  :  "guo jing",
                        "/d/wuguan/guofu_huayuan" :  "huang rong",
                        "/d/xiangyang/xiaorong2"  :  "boy",
                        "/d/xiangyang/xiaorong2"  :  "girl",
                        "/d/xiangyang/xiaorong1"  :  "kid",
                        "/d/xiangyang/juyihuayuan"  :  "guo fu",
                        "/d/xiangyang/jiedao"  :  "poor man",
                        "/d/xiangyang/nixianglou"  :  "xiao er",
                        "/d/xiangyang/mujiang"  :  "mu jiang",
                        "/d/xiangyang/southjie2"  :  "liu mang",
                        "/d/xiangyang/qianzhuang"  :  "huang zhen",
                        "/d/xiangyang/shudian"  :  "shudian laoban",
                        "/d/xiangyang/juyiwupin"  :  "wu xiuwen",
                        "/d/xiangyang/westjie1"  :  "poor man",
                        "/d/xiangyang/westjie2"  :  "wu santong",
                        "/d/xiangyang/kedian"  :  "wu dunru",
                        "/d/xiangyang/xinluofang"  :  "gaoli shang",
                        "/d/xiangyang/xuetang"  :  "lao xiansheng",
                        "/d/xiangyang/yaopu"  :  "yaopu huoji",
                     ]),
        "dl"      :  ([
                        "/d/dali/atoubu"  :  "lie ren",
                        "/d/dali/baiyiminju"  :  "oldman",
                        "/d/dali/baiyiminju"  :  "girl",
                        "/d/dali/banshan"  :  "kanzhu ren",
                        "/d/dali/bijishan"  :  "youke",
                        "/d/dali/biluoshan"  :  "nong fu",
                        "/d/dali/buxiongbu"  :  "shang fan",
                        "/d/dali/cangshanlu1"  :  "lie ren",
                        "/d/dali/chahua2"  :  "yanghua nu",
                        "/d/dali/chahua9"  :  "mu wanqing",
                        "/d/dali/changlang"  :  "duan wuwei",
                        "/d/dali/caopo"  :  "muyang ren",
                        "/d/dali/yanan1"  :  "cun fu",
                        "/d/dali/feilihusouth"  :  "yu fu",
                        "/d/dali/langan3"  :  "yangcan nu",
                        "/d/dali/langan2"  :  "kid",
                        "/d/dali/langan4"  :  "fangsha nu",
                        "/d/dali/dalangan2"  :  "lao jisi",
                        "/d/dali/gelucheng"  :  "muyang ren",
                        "/d/dali/road3"  :  "girl",
                        "/d/dali/guibingshi2"  :  "daizu shouling",
                        "/d/dali/hebian"  :  "shang fan",
                        "/d/dali/hexi"  :  "shang fan",
                        "/d/dali/jisidawu1"  :  "lao jisi",
                        "/d/dali/zhulou5"  :  "ji si",
                        "/d/dali/jianchuan"  :  "lie ren",
                        "/d/dali/jianchuan"  :  "pihuo shang",
                        "/d/dali/jinzhihe"  :  "seng ren",
                        "/d/dali/kedian"  :  "xiao er",
                        "/d/dali/shanjian"  :  "caisun ren",
                        "/d/dali/luwang"  :  "shang fan",
                        "/d/dali/minadian"  :  "shao nu",
                        "/d/dali/nianhuasi"  :  "po chen",
                        "/d/dali/nianhuasi"  :  "po yi",
                        "/d/dali/nongtian1"  :  "nong fu",
                        "/d/dali/paifang"  :  "hu yizhi",
                        "/d/dali/qingzhulin"  :  "caisun ren",
                        "/d/dali/qingxi"  :  "biao tou",
                        "/d/dali/yulin"  :  "lie ren",
                        "/d/dali/sanglin"  :  "caisang nu",
                        "/d/dali/sheguta"  :  "kid",
                        "/d/dali/stoneshop"  :  "shi jiang",
                        "/d/dali/shuitian"  :  "nong fu",
                        "/d/dali/taiheju"  :  "xiao er",
                        "/d/dali/tusifu"  :  "da tusi",
                        "/d/dali/tusifu"  :  "shi cong",
                        "/d/dali/wunong"  :  "shang fan",
                        "/d/dali/wuyiminju1"  :  "muyang nu",
                        "/d/dali/wuyiminju4"  :  "kid",
                        "/d/dali/wuyiminju2"  :  "lie ren",
                        "/d/dali/wuding"  :  "gu niang",
                        "/d/dali/xizhou"  :  "ke shang",
                        "/d/dali/xiaguan"  :  "shang fan",
                        "/d/dali/xiaguan"  :  "shang fan",
                        "/d/dali/garments"  :  "xue laoban",
                        "/d/dali/yangzong"  :  "shang fan",
                        "/d/dali/yangcanfang"  :  "yangcan nu",
                        "/d/dali/yaoshop"  :  "he hongyao",
                        "/d/dali/zhulou4"  :  "zu zhang",
                        "/d/dali/tusiyishi"  :  "da tusi",
                        "/d/dali/tusiyishi"  :  "zu touren",
                        "/d/dali/yixibu"  :  "shao nu",
                        "/d/dali/yujia"  :  "fu nu",
                        "/d/dali/yuxiashan"  :  "youke",
                        "/d/dali/yuxuguan"  :  "dao baifeng",
                        "/d/dali/yuxuguanqian"  :  "xiao daogu",
                        "/d/dali/zhenxiong"  :  "muyang nu",
                        "/d/dali/zhenxiong"  :  "shang fan",
                        "/d/dali/center"  :  "jianghu yiren",
                     ]),
]);

nosave mapping place = ([
        "��������": ({
                        "/d/beijing/cagc_e","/d/beijing/caroad_e1",
                        "/d/beijing/caroad_e2","/d/beijing/zahuo",
                        "/d/beijing/yancao","/d/beijing/xingchang",
                        "/d/beijing/wang_4","/d/beijing/chaoyang_dao1",
                        "/d/beijing/chaoyang_dao2","/d/beijing/chaoyangmen",
                        "/d/beijing/wang_6","/d/beijing/wang_8",
                        "/d/beijing/xiyuan","/d/beijing/xiyuanup",
                        "/d/beijing/wang_10","/d/beijing/wang_9",
                        "/d/beijing/wang_1","/d/beijing/wang_3",
                        "/d/beijing/wang_5","/d/beijing/wang_7",
                        "/d/beijing/wang_8","/d/beijing/quanjude",
                        "/d/beijing/quanjudeup","/d/beijing/dong_1",
                        "/d/beijing/dong_3","/d/beijing/dongchang_men",
                        "/d/beijing/dongchang","/d/beijing/xiaochang",
                        "/d/beijing/weifu_men","/d/beijing/weifu_zoulang1",
                        "/d/beijing/weifu_dayuan","/d/beijing/weifu_zoulang2",
                        "/d/beijing/weifu_dating","/d/beijing/weifu_shufang",
                        "/d/beijing/dong_2","/d/beijing/guozijian",
                        "/d/beijing/wang_2",
                     }),
        "��������" : ({
                        "/d/beijing/niaoshi","/d/beijing/xi_1",
                        "/d/beijing/caroad_w1","/d/beijing/yangliu1",
                        "/d/beijing/yangliu2","/d/beijing/yangliu3",
                        "/d/beijing/qingmu_men","/d/beijing/qingmu_dayuan",
                        "/d/beijing/qingmu_fang3","/d/beijing/qingmu_fang1",
                        "/d/beijing/caroad_w1","/d/beijing/caroad_w2",
                        "/d/beijing/cagc_w","/d/beijing/tiananmen",
                        "/d/beijing/cagc_s","/d/beijing/tianqiao",
                        "/d/beijing/yong_1","/d/beijing/duchang",
                        "/d/beijing/huiying","/d/beijing/huiyingup",
                        "/d/beijing/yong_2","/d/beijing/tiepu",
                        "/d/beijing/yong_3","/d/beijing/fu_2",
                        "/d/beijing/fukedian","/d/beijing/kediandayuan",
                        "/d/beijing/hai_men","/d/beijing/hai_dayuan",
                        "/d/beijing/hai_fang","/d/beijing/hai_huating",
                        "/d/beijing/hai_dating","/d/beijing/hai_houyuan",
                        "/d/beijing/mianguan","/d/beijing/fu_1",
                        "/d/beijing/tiantan_n","/d/beijing/tiantan",
                        "/d/beijing/yongdingdao","/d/beijing/yongdingmen",
                        "/d/beijing/qiao","/d/beijing/hgmen_s",
                        "/d/beijing/gaosheng","/d/beijing/xi_2",
                        "/d/beijing/huichuntang","/d/beijing/bei_2",
                        "/d/beijing/kangfu_men","/d/beijing/kangfu_dayuan",
                        "/d/beijing/kangfu_zoulang1","/d/beijing/kangfu_dating",
                        "/d/beijing/kangfu_zoulang2","/d/beijing/kangfu_xifang",
                        "/d/beijing/kangfu_dongfang","/d/beijing/kangfu_shufang",
                        "/d/beijing/bei_2","/d/beijing/bei_4",
                        "/d/beijing/di_1","/d/beijing/di_3",
                        "/d/beijing/di_4","/d/beijing/aofu_men",
                        "/d/beijing/caishi","/d/beijing/ximenkou",
                        "/d/beijing/shi_1","/d/beijing/guandao_1",
                        "/d/beijing/guandao_2","/d/beijing/huangling",
                        "/d/beijing/shi_3","/d/beijing/di_xigc",
                        "/d/beijing/di_2","/d/beijing/dianmen",
                        "/d/beijing/di_dajie1","/d/beijing/di_5",
                        "/d/beijing/di_dajie2","/d/beijing/di_anmen",
                        "/d/beijing/qingmu_dating",
                     }),
        "���ݳ�"   : ({
                        "/d/city/zuixianlou2","/d/city/zuixianlou3",
                        "/d/city/zuixianlou","/d/city/beidajie2",
                        "/d/city/beimen","/d/city/beidajie1",
                        "/d/city/qianzhuang","/d/city/guangchang",
                        "/d/city/xidajie1","/d/city/yamen",
                        "/d/city/xidajie2","/d/city/wuguan",
                        "/d/city/ximen","/d/city/dongdajie1",
                        "/d/city/zahuopu","/d/city/dongdajie2",
                        "/d/city/yaopu","/d/city/datiepu",
                        "/d/city/dongmen",
                     }),
         "������"   : ({
                        "/d/changan/huanggong","/d/changan/bridge1",
                        "/d/changan/baihu2","/d/changan/beian-dadao",
                        "/d/changan/beian-daokou","/d/changan/bingying1",
                        "/d/changan/bingying2","/d/changan/bei-chengmen",
                        "/d/changan/qixiang3","/d/changan/qixiang2",
                        "/d/changan/tea-shop","/d/changan/fruit-shop",
                        "/d/changan/qixiang1","/d/changan/jiulou",
                        "/d/changan/jiulou2","/d/changan/yongtai-beikou",
                        "/d/changan/zhubaohang","/d/changan/yongtai-dadao1",
                        "/d/changan/yongtai-dadao2","/d/changan/yongtai-dadao3",
                        "/d/changan/huiwenge","/d/changan/xian-daokou",
                        "/d/changan/xi-chengmen","/d/changan/bingying3",
                        "/d/changan/yongtai-dadao4","/d/changan/miao",
                        "/d/changan/yongtai-dadao5","/d/changan/yongtai-nankou",
                        "/d/changan/baozipu","/d/changan/huarui1",
                        "/d/changan/nanan-daokou","/d/changan/huarui2",
                        "/d/changan/mianguan","/d/changan/huarui3",
                        "/d/changan/huadian","/d/changan/bingying5",
                        "/d/changan/bingying4","/d/changan/nan-chengmen",
                        "/d/changan/huarui4","/d/changan/xiaojinghu",
                        "/d/changan/huarui4","/d/changan/huarui5",
                        "/d/changan/zahuopu","/d/changan/huarui5",
                        "/d/changan/huarui6","/d/changan/tuchangguan",
                        "/d/changan/liande-nankou","/d/changan/xiaojiuguan",
                        "/d/changan/liande-dadao5","/d/changan/xiaojia-qianyuan",
                        "/d/changan/liande-dadao4","/d/changan/dongan-daokou",
                        "/d/changan/dong-chengmen","/d/changan/bingying6",
                        "/d/changan/liande-dadao3","/d/changan/liande-dadao2",
                        "/d/changan/liande-dadao1","/d/changan/liande-beikou",
                        "/d/changan/xiyuan","/d/changan/qixiang6",
                        "/d/changan/yaopu","/d/changan/weapon-shop",
                        "/d/changan/qixiang5","/d/changan/shoushi-dian",
                        "/d/changan/biaoju-damen","/d/changan/qixiang4",
                        "/d/changan/bank","/d/changan/qunyulou",
                        "/d/changan/baihu1","/d/changan/fufeng1",
                        "/d/changan/fufeng2","/d/changan/fufeng3",
                        "/d/changan/fufeng4","/d/changan/xian-dadao",
                        "/d/changan/fufeng5","/d/changan/qinglong1",
                        "/d/changan/baoxiangsi","/d/changan/qinglong2",
                        "/d/changan/bridge2","/d/changan/qinglong2",
                        "/d/changan/nanan-dadao","/d/changan/qinglong3",
                        "/d/changan/yamen","/d/changan/fengxu5",
                        "/d/changan/fengxu4","/d/changan/lingyange",
                        "/d/changan/fengxu3","/d/changan/fengxu2",
                        "/d/changan/dongan-dadao","/d/changan/fengxu1",
                        "/d/changan/baihu3","/d/changan/guozijian",
                     }),
        "�ɶ���"   : ({
                        "/d/chengdu/guangchang","/d/chengdu/tidugate",
                        "/d/chengdu/shuduroad2","/d/chengdu/shuduroad1",
                        "/d/chengdu/eastroad2","/d/chengdu/eastroad1",
                        "/d/chengdu/northroad3","/d/chengdu/northroad2",
                        "/d/chengdu/northgate","/d/chengdu/northroad1",
                        "/d/chengdu/bingqidian","/d/chengdu/westroad3",
                        "/d/chengdu/yaodian","/d/chengdu/westroad2",
                        "/d/chengdu/westgate","/d/chengdu/westroad1",
                        "/d/chengdu/qingyanggong","/d/chengdu/southroad3",
                        "/d/chengdu/wuhoucigate","/d/chengdu/liubeidian",
                        "/d/chengdu/wuhouci","/d/chengdu/southroad2",
                        "/d/chengdu/southgate","/d/chengdu/tiduroad",
                        "/d/chengdu/southroad1","/d/chengdu/eastroad3",
                        "/d/chengdu/wangjianglou","/d/chengdu/eastroad2",
                        "/d/chengdu/eastroad1","/d/chengdu/jiudian",
                        "/d/chengdu/wuguan",
                     }),
        "���ݳ�"   : ({
                        "/d/suzhou/beimen","/d/suzhou/beidajie2",
                        "/d/suzhou/zijinan","/d/suzhou/jiudian",
                        "/d/suzhou/beidajie1","/d/suzhou/xiyuan",
                        "/d/suzhou/canlangting","/d/suzhou/dongdajie1",
                        "/d/suzhou/hutong1","/d/suzhou/leitai",
                        "/d/suzhou/hutong2","/d/suzhou/hutong3",
                        "/d/suzhou/dongdajie2","/d/suzhou/dongmen",
                        "/d/suzhou/yaopu","/d/suzhou/datiepu",
                        "/d/suzhou/baodaiqiao","/d/suzhou/nandajie1",
                        "/d/suzhou/jubaozhai","/d/suzhou/shizilin",
                        "/d/suzhou/yanyutang","/d/suzhou/zhenquting",
                        "/d/suzhou/wenmeige","/d/suzhou/lixuetang",
                        "/d/suzhou/zhipoxuan","/d/suzhou/shuyuan",
                        "/d/suzhou/chaguan","/d/suzhou/nandajie2",
                        "/d/suzhou/liuyuan","/d/suzhou/hehuating",
                        "/d/suzhou/gumujiaohe","/d/suzhou/chitang",
                        "/d/suzhou/nanmen","/d/suzhou/tingyu",
                        "/d/suzhou/xidajie1","/d/suzhou/bingying",
                        "/d/suzhou/xidajie2",
                        "/d/suzhou/xuanmiao","/d/suzhou/shuchang",
                        "/d/suzhou/ximen",
                     }),
        "���ݳ�"   : ({
                        "/d/hangzhou/suti2", "/d/hangzhou/jujingyuan",
                        "/d/hangzhou/liuzhuang", "/d/hangzhou/road19",
                        "/d/hangzhou/huangniling", "/d/hangzhou/qinglindong",
                        "/d/hangzhou/road5","/d/hangzhou/liuhe2",
                        "/d/hangzhou/dadao1","/d/hangzhou/xilingqiao",
                        "/d/hangzhou/road9","/d/hangzhou/baoshishan",
                        "/d/hangzhou/yuelang",
                        "/d/hangzhou/huagang","/d/hangzhou/hupaoquan",
                        "/d/hangzhou/yuhuangsd","/d/hangzhou/yuhuangshan",
                        "/d/hangzhou/shanlu6","/d/hangzhou/shanlu7",
                        "/d/hangzhou/yuhuangsj","/d/hangzhou/road18",
                        "/d/hangzhou/road20","/d/hangzhou/suti7",
                        "/d/hangzhou/suti7","/d/hangzhou/suti6",
                        "/d/hangzhou/suti5","/d/hangzhou/suti4",
                        "/d/hangzhou/suti3","/d/hangzhou/suti2",
                        "/d/hangzhou/road7","/d/hangzhou/road8",
                        "/d/hangzhou/road9","/d/hangzhou/road10",
                        "/d/hangzhou/road11","/d/hangzhou/road12",
                        "/d/hangzhou/road13","/d/hangzhou/road14",
                        "/d/hangzhou/road15","/d/hangzhou/road16",
                        "/d/hangzhou/xizhaoshan","/d/hangzhou/road17",
                        "/d/hangzhou/road18","/d/hangzhou/qingbomen",
                        "/d/hangzhou/jujingyuan","/d/hangzhou/liulangqiao",
                        "/d/hangzhou/qiantang","/d/hangzhou/liuheta",
                        "/d/hangzhou/yuquan","/d/hangzhou/dadao1",
                        "/d/hangzhou/dadao2","/d/hangzhou/dalu1",
                        "/d/hangzhou/liuzhuang",
                        "/d/hangzhou/road1", "/d/hangzhou/road2",
                        "/d/hangzhou/road4", "/d/hangzhou/road3",
                        "/d/hangzhou/hongchunqiao","/d/hangzhou/jiulou",
                        "/d/hangzhou/duanqiao","/d/hangzhou/baiti",
                        "/d/hangzhou/pinghuqiuyue","/d/hangzhou/fangheting",
                        "/d/hangzhou/gushan","/d/hangzhou/gushanpingtai",
                        "/d/meizhuang/shijie","/d/meizhuang/xiaolu",
                        "/d/meizhuang/gate","/d/hangzhou/shanlu8",
                        "/d/hangzhou/tiejiangpu",
                        "/d/hangzhou/yaodian","/d/hangzhou/jingcisi",
                        "/d/hangzhou/jingci","/d/hangzhou/shanlu1",
                        "/d/hangzhou/shanlu2","/d/hangzhou/shanlu3",
                        "/d/hangzhou/fajingsi","/d/hangzhou/fajinsi",
                        "/d/hangzhou/faxisi","/d/hangzhou/shanlu4",
                        "/d/hangzhou/shanlu5","/d/hangzhou/shanlu6",
                        "/d/hangzhou/shanlu7","/d/hangzhou/tulu1",
                        "/d/hangzhou/yanxiadong","/d/hangzhou/maojiabu",
                        "/d/hangzhou/maojiabu","/d/hangzhou/huangniling",
                        "/d/hangzhou/shuiledong","/d/hangzhou/manjuelong",
                     }),
        "������"   : ({
                        "/d/xiangyang/westjie2", "/d/xiangyang/southjie2",
                        "/d/xiangyang/xiaorong1", "/d/xiangyang/zhonglie",
                        "/d/xiangyang/guangchang", "/d/xiangyang/dingzi",
                        "/d/xiangyang/westgate2","/d/xiangyang/northgate1",
                        "/d/xiangyang/eastgate1","/d/xiangyang/southgate2",
                        "/d/xiangyang/walls2","/d/xiangyang/walle3",
                        "/d/xiangyang/walln4","/d/xiangyang/juyilang",
                        "/d/xiangyang/northgate2","/d/xiangyang/northjie",
                        "/d/xiangyang/bingying1","/d/xiangyang/chaguan",
                        "/d/xiangyang/northroad2","/d/xiangyang/xiaorong2",
                        "/d/xiangyang/xiaorong1","/d/xiangyang/jiekou2",
                        "/d/xiangyang/eastroad2","/d/xiangyang/eastroad1",
                        "/d/xiangyang/biaoju","/d/xiangyang/eastjie2",
                        "/d/xiangyang/eastjie3","/d/xiangyang/bingying2",
                        "/d/xiangyang/eastgate2","/d/xiangyang/walle1",
                        "/d/xiangyang/walle5","/d/xiangyang/walle7",
                        "/d/xiangyang/walle2","/d/xiangyang/walle4",
                        "/d/xiangyang/walle6","/d/xiangyang/walle8",
                        "/d/xiangyang/mujiang","/d/xiangyang/eastjie2",
                        "/d/xiangyang/eastjie3","/d/xiangyang/jiedao",
                        "/d/xiangyang/minju2","/d/xiangyang/eastjie1",
                        "/d/xiangyang/jiangjungate","/d/xiangyang/yaopu",
                        "/d/xiangyang/anfugate","/d/xiangyang/anfupailou",
                        "/d/xiangyang/southjie1","/d/xiangyang/southjie2",
                        "/d/xiangyang/southjie3","/d/xiangyang/xuetang",
                        "/d/xiangyang/qianzhuang","/d/xiangyang/southgate1",
                        "/d/xiangyang/nixianglou","/d/xiangyang/duchang",
                        "/d/xiangyang/tiejiangpu","/d/xiangyang/bingying3",
                        "/d/xiangyang/walls1","/d/xiangyang/walls3",
                        "/d/xiangyang/walls5","/d/xiangyang/walls7",
                        "/d/xiangyang/walls4","/d/xiangyang/walls6",
                        "/d/xiangyang/walls8","/d/xiangyang/westjie1",
                        "/d/xiangyang/westjie2","/d/xiangyang/westjie3",
                        "/d/wuguan/guofu_gate","/d/wuguan/guofu_dayuan",
                        "/d/wuguan/guofu_dating","/d/wuguan/guofu_huayuan",
                        "/d/wuguan/guofu_kefang","/d/wuguan/guofu_woshi1",
                        "/d/wuguan/guofu_shufang","/d/xiangyang/dangpu",
                        "/d/xiangyang/juyiyuan","/d/xiangyang/juyilianwu2",
                        "/d/xiangyang/juyilianwu1","/d/xiangyang/juyilang",
                        "/d/xiangyang/juyihuayuan","/d/xiangyang/juyimale",
                        "/d/xiangyang/juyifemale","/d/xiangyang/juyichufang",
                        "/d/xiangyang/juyiwupin","/d/xiangyang/dajiaochang",
                        "/d/xiangyang/bingying4","/d/xiangyang/westgate1",
                        "/d/xiangyang/wallw1","/d/xiangyang/wallw2",
                        "/d/xiangyang/wallw3","/d/xiangyang/wallw4",
                        "/d/xiangyang/wallw5","/d/xiangyang/wallw6",
                        "/d/xiangyang/wallw7","/d/xiangyang/wallw8",
                        "/d/xiangyang/westroad1","/d/xiangyang/westroad2",
                        "/d/xiangyang/shudian","/d/xiangyang/hutong1",
                        "/d/xiangyang/hutong2","/d/xiangyang/xinluofang",
                        "/d/xiangyang/jiekou1","/d/xiangyang/northgate2",
                        "/d/xiangyang/walln1","/d/xiangyang/walln2",
                        "/d/xiangyang/walln3","/d/xiangyang/walln5",
                        "/d/xiangyang/walln6","/d/xiangyang/walln7",
                        "/d/xiangyang/walln8",
                     }),
        "����һ��" : ({
                        "/d/dali/northgate", "/d/dali/southgate",
                        "/d/dali/shanlu2", "/d/dali/buxiongbu",
                        "/d/dali/jinzhihe", "/d/dali/xiaodao1",
                        "/d/dali/tianweijing", "/d/dali/wuding",
                        "/d/dali/luwang", "/d/dali/gudao",
                        "/d/dali/biluoxueshan", "/d/dali/zhenxiong",
                        "/d/dali/yixibu", "/d/dali/cangshanzhong",
                        "/d/dali/wumeng", "/d/dali/hongsheng",
                        "/d/dali/tusifu","/d/dali/tusimentang",
                        "/d/dali/tusiyishi","/d/dali/dahejiewest",
                        "/d/dali/dahejieeast","/d/dali/baiyiziguan",
                        "/d/dali/baiyiminju","/d/dali/center",
                        "/d/dali/taihejiekou","/d/dali/sheguta",
                        "/d/dali/qingchi","/d/dali/taiheeast",
                        "/d/dali/stoneshop","/d/dali/garments",
                        "/d/dali/yaoshop","/d/dali/paifang",
                        "/d/dali/yujie","/d/dali/gongmen",
                        "/d/dali/qiandian","/d/dali/yuhuayuan",
                        "/d/dali/hualang","/d/dali/yushanfang",
                        "/d/dali/piandian","/d/dali/chahuashan1",
                        "/d/dali/chahuashan2","/d/dali/chahuashan3",
                        "/d/dali/chahuashan4","/d/dali/chahuashan5",
                        "/d/dali/chahuashan6","/d/dali/dadieshui",
                        "/d/dali/qingxi","/d/dali/xiaodao1",
                        "/d/dali/hudiequan","/d/dali/yuxuguanqian",
                     }),
]);

varargs mixed query_city_quest(string arg, string bh);
varargs mixed query_zhuisha_quest(string type, string bh);
void ready_to_start();
object create_npc(mixed me);
void init_npc_skill(object ob, int lvl);
void start_quest();
int get_bianhao(string arg);
varargs void place_npc(object ob, string *not_place);
void random_move(object ob);
int not_wizard(object ob);
int check_level(object ob);
string check_difficult(int lvl);
string check_reward(int lvl);
string bad_zhuisha_msg(string name, string place, string difficult);
string good_zhuisha_msg(string name, string place, string difficult);
void check_xuncheng();
void check_city_quest();
int is_the_bunch(mapping arg, string type);
varargs mixed create_quest(string the_city, string bunch_type, object player);
varargs void delete_city_quest(string arg, string type, string bh);

// ��ѯָ�����е������б���ʹ�ò���bh�򷵻ر��Ϊbh������
varargs mixed query_city_quest(string arg, string type, string bh)
{
        int i;
        mapping *bunch_quest;

        if (! arg) return bunch_city_quest;

        bunch_quest = bunch_city_quest[arg];

        if (type)
                bunch_quest = filter_array(bunch_quest,(: is_the_bunch($1, $2) :), type);

        if (bh)
        {
                for (i = 0;i < sizeof(bunch_quest);i++)
                        if (bunch_quest[i]["id"] == bh)
                                return bunch_quest[i];
                return 0;
        }

        return bunch_quest;
}

// ��ѯ׷ɱ�����б���ʹ�ò���BHΪ���ر��Ϊbh������
varargs mixed query_zhuisha_quest(string type, string bh)
{
        int i;
        mapping *bunch_quest = ({});
        bunch_quest = bunch_zs;

        if (type)
                bunch_quest = filter_array(bunch_quest,(: is_the_bunch($1, $2) :), type);

        if (! bh) return bunch_quest;

        for (i = 0;i < sizeof(bunch_quest);i++)
                if (bunch_quest[i]["id"] == bh)
                        return bunch_quest[i];

        return 0;
}

// ���ڲ��������ض����񣬸��������԰���֪ͨ����ʽ���͸����
// ���������Ϊ����
// ��һ�֣�ֻ���͸�һ����ң�ֻ�ܸ����ȥ���
// �ڶ��֣����͸����е���ң�˭�������˭�õ�����
void ready_to_start()
{
        int num;
        object *all_user;
        remove_call_out("start_quest");
        all_user = users();
        all_user = filter_array(all_user, (: interactive($1) &&
                                !wizardp($1) &&
                                query("combat_exp", $1) >= $2 &&
                                query("combat_exp", $1) <= $3 &&
                                environment($1) &&
                                !$1->is_ghost() &&
                                !$1->in_prison() &&
                               bunchp($1) :), 10000, 270000000);

        num = 300 - sizeof(all_user);        // �������������Խ�࣬��������������ٶ�Խ��
        if (num < MIN_IDLE) num = MIN_IDLE;
        call_out("start_quest", num);
}

int clean_up()
{
        return 1;
}

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "������");
        CHANNEL_D->do_channel( this_object(), "sys", "�������ϵͳ�Ѿ�������");
        ready_to_start();
        set_heart_beat(2);
}

void heart_beat()
{
        int i;

        // ���׷ɱ�������Ŀ���Ѿ����ڣ��ʹ�׷ɱ�����б���ȥ��
        if (sizeof(bunch_zs))
                for (i = 0;i < sizeof(bunch_zs);i++)
                        if (! objectp(bunch_zs[i]["ob"]))
                                bunch_zs[i] = 0;
        bunch_zs -= ({ 0 });

        // ���Ѳ������
        remove_call_out("check_xuncheng");
        call_out("check_xuncheng", 0);

        // ���������е�����
        remove_call_out("check_city_quest");
        call_out("check_city_quest", 0);

        set_heart_beat(HEARTBEAT);
}

object create_npc(mixed me)
{
        int lvl,exp;
        object ob;

        ob = new(CLASS_D("generate") + "/party_npc");

        if (objectp(me))
                ob->set_from_me(me,0);
        else
                init_npc_skill(ob,random(sizeof(levels))+1);
        lvl = check_level(ob);
        if (lvl < 1) lvl = 1;
        if (lvl >= sizeof(levels)) lvl = sizeof(levels) - 1;
        exp = sort_array(keys(levels), 1)[lvl - 1];
        set("lvl", lvl, ob);
        set("bonus", (levels[exp]*3/2)*10, ob);
        return ob;
}

// set the the level of the npc's skill
void init_npc_skill(object ob, int lvl)
{
        int sk_lvl;
        string *ks;
        int i;
        int exp;
        mixed my;

        if (lvl < 1) lvl = 1;
        if (lvl >= sizeof(levels)) lvl = sizeof(levels) - 1;

        exp = sort_array(keys(levels), 1)[lvl - 1];
        my = ob->query_entire_dbase();
        set("combat_exp", exp, ob);
        sk_lvl = levels[exp];
        my["jing"] = my["eff_jing"] = my["max_jing"] = sk_lvl * 3;
        my["qi"] = my["eff_qi"] = my["max_qi"] = sk_lvl * 6;
        my["jingli"] = my["max_jingli"] = sk_lvl * 2;
        my["neili"] = my["max_neili"] = sk_lvl * 4;
        if (! ob->query_skills())
                return;
        ks = keys(ob->query_skills());
        for (i = 0; i < sizeof(ks); i++)
                ob->set_skill(ks[i], sk_lvl);
}

void start_quest()
{
        object *all_user, ob;
        string the_nation, the_enemy;
        mapping bunch_quest;
        int i, num;

        ready_to_start();
        all_user = users();
        // �ٴ�ȷ������з��������������Ŀ
        all_user = filter_array(all_user,(: interactive($1) &&
                                ! wizardp($1) &&
                                query("combat_exp", $1) >= $2 &&
                                query("combat_exp", $1) <= $3 &&
                                environment($1) &&
                                ! $1->is_ghost() &&
                                ! $1->in_prison() &&
                               bunchp($1) :), 10000, 270000000);

        num = sizeof(all_user);
        //���û��������ң�����ֹ�������
        if (! num) return;

        CHANNEL_D->do_channel( this_object(), "sys", "�������ϵͳ��ʼ����׷ɱ����");

        ob = create_npc(1);
        bunch_quest = ([]);
        place_npc(ob);
        random_move(ob);
        random_move(ob);
        random_move(ob);

        bunch_quest["type"] = "׷ɱ";
        bunch_quest["ob"] = ob;
        bunch_quest["bonus"]=query("bonus", ob)*2;
        bunch_quest["name"] = ob->name();
        bunch_quest["place"]=query("place", ob);
        bunch_quest["difficult"]=check_difficult(query("lvl", ob));
        bunch_quest["reward"]=check_reward(query("lvl", ob));

        if (random(2))        //�ڵ�׷ɱ
        {
                set("shen", 20000, ob);
                bunch_quest["bunch_type"] = "bad";
                bunch_quest["msg"] = bad_zhuisha_msg(bunch_quest["name"], bunch_quest["place"], bunch_quest["difficult"]);
                all_user = filter_array(all_user,(: bad_bunch($1) :));
                if (sizeof(all_user))
                        for (i = 0;i < sizeof(all_user);i++)
                        {
                                tell_object(all_user[i],HIB"ӭ�漱������һλ��"+query("bunch/bunch_name", all_user[i])+
                                            "���ֵܳ��㼱��ææ��˵�����ڵ�ͬ�˷���׷ɱ���ˣ�\n" NOR +
                                            bunch_quest["msg"] + "��\n");
                                tell_object(all_user[i], "˵������һ��ȭ�������ֵܻ���Ҫ�����������и�ǣ�\n");
                        }
                else destruct(ob);
        }
        else                //�׵�׷ɱ
        {
                set("shen", -20000, ob);
                bunch_quest["bunch_type"] = "good";
                bunch_quest["msg"]=good_zhuisha_msg(bunch_quest["name"],bunch_quest["place"],bunch_quest["difficult"]);
                all_user = filter_array(all_user,(: good_bunch($1) :));
                if (sizeof(all_user))
                        for (i = 0;i < sizeof(all_user);i++)
                        {
                                tell_object(all_user[i],HIW"ӭ�汼��һλ��"+query("bunch/bunch_name", all_user[i])+
                                            "�����ֳ��������ֲ����������ĺ�ˮ�����������׵�����"+
                                            "����ͨ��������\n"NOR+
                                            bunch_quest["msg"] + "��\n");
                                tell_object(all_user[i],"˵������һ��ȭ���������»���Ҫ�����������и�ǣ�\n");
                        }
                else destruct(ob);
        }
        if (ob)
        {
                //ÿ�����񶼱������Լ�����ˮ�ţ�ʹ��get_bianhao()��������ȡͳһ����ˮ��
                bunch_quest["num"] = get_bianhao("zhuisha");
                bunch_quest["id"] = "zs" + (string)bunch_quest["num"];
                bunch_zs += ({ bunch_quest });
                set("bunch_quest", bunch_quest, ob);
        }
        return;
}

int get_bianhao(string arg)
{
        int i,have_it,bh;
        have_it = 0;
        bh = 1;

        switch(arg)
        {
                case "zhuisha":
                        for (;;)
                        {
                                if (!sizeof(bunch_zs)) break;
                                for (i = 0; i < sizeof(bunch_zs); i++)
                                        if (bunch_zs[i]["num"] == bh)
                                                have_it = 1;
                                if (have_it)
                                {
                                        have_it = 0;
                                        bh++;
                                        continue;
                                } else break;
                        }
                        break;
                default:
                        for (;;)
                        {
                                if (!sizeof(bunch_city_quest[arg])) break;
                                for (i = 0;i < sizeof(bunch_city_quest[arg]);i++)
                                {
                                        if (!sizeof(bunch_city_quest[arg][i])) break;
                                        if (bunch_city_quest[arg][i]["num"] == bh)
                                                have_it = 1;
                                }
                                if (have_it)
                                {
                                        have_it = 0;
                                        bh++;
                                        continue;
                                } else break;
                        }
                        break;
        }
        return bh;
}

// random move
void random_move(object ob)
{
        mapping exits;
        string *moved;
        string dir;
        string *dirs;
        int i;

        moved=query_temp("moved", ob);
        if (! moved) moved = ({ });
        if (sizeof(moved) >= MAX_MOVED)
        {
                // out of range, move back
                dir = GO_CMD->query_reverse(moved[sizeof(moved) - 1]);
        } else
        {
                exits=query("exits", environment(ob));
                dirs = keys(exits);
                for (i = 0; i < 12; i++)
                {
                        if (! sizeof(dirs))
                                return;
                        dir = dirs[random(sizeof(dirs))];
                        if (stringp(GO_CMD->query_reverse(dir)) &&
                            get_object(exits[dir]) &&
                           !query("room_id", get_object(exits[dir])) &&
                           !query("no_fight", get_object(exits[dir])) )
                                break;
                        dirs -= ({ dir });
                }
        }

        if (sizeof(moved) &&
            GO_CMD->query_reverse(dir) == moved[sizeof(moved) - 1])
        {
                // move back
                moved = moved[0..<2];
        } else
                moved += ({ dir });
        set_temp("moved", moved, ob);

        GO_CMD->main(ob, dir);
}

// place npc
varargs void place_npc(object ob, string *not_place)
{
        string *kp;
        string p;
        string startroom;
        object pos;

        kp = keys(place);
        if (arrayp(not_place))
                kp -= not_place;
        for (;;)
        {
                p = kp[random(sizeof(kp))];
                startroom = place[p][random(sizeof(place[p]))];
                if (! objectp(pos = get_object(startroom)))
                {
                        log_file("log", sprintf("party_questd error to place npc to %s:%s\n",
                                                p, startroom));
                        continue;
                }
                break;
        }

        ob->move(pos);
        set("place", p, ob);
        set("startroom", startroom, ob);
        set_temp("moved", ({}), ob);
        message_vision("$N���˹�����\n", ob);
}

int check_level(object ob)
{
        int *exp;
        int i;

        exp = sort_array(keys(levels), 1);
        for (i = 0; i < sizeof(exp); i++)
                if( query("combat_exp", ob)<exp[i])break;
        return i;
}

string check_difficult(int lvl)
{
        string difficult;

        switch(lvl)
        {
                case 1:
                case 2:
                        difficult = "������";
                        break;
                case 3:
                case 4:
                        difficult = "����";
                        break;
                case 5:
                case 6:
                        difficult = "������";
                        break;
                case 7:
                case 8:
                        difficult = "�е�";
                        break;
                case 9:
                case 10:
                        difficult = "������";
                        break;
                case 11:
                case 12:
                        difficult = "����";
                        break;
                default:
                        difficult = "������";
                        break;
        }
        return difficult;
}

string check_reward(int lvl)
{
        string reward;

        switch(lvl)
        {
                case 1:
                case 2:
                        reward = "����";
                        break;
                case 3:
                case 4:
                        reward = "��";
                        break;
                case 5:
                case 6:
                        reward = "����";
                        break;
                case 7:
                case 8:
                        reward = "�е�";
                        break;
                case 9:
                case 10:
                        reward = "�ϸ�";
                        break;
                case 11:
                case 12:
                        reward = "��";
                        break;
                default:
                        reward = "�ܸ�";
                        break;
        }
        return reward;
}

string bad_zhuisha_msg(string name,string place,string difficult)
{
        string msg1,msg2,msg3,msg4,msg5;
        msg1 = replace_string(bad_msg1[random(sizeof(bad_msg1))],"name",name);
        msg2 = search_msg[random(sizeof(search_msg))];
        msg3 = replace_string(bad_msg2[random(sizeof(bad_msg2))],"place",place);
        msg4 = bad_msg3[random(sizeof(bad_msg3))];
        msg5 = "��������ѶȾ������ֵ�˵��" + difficult + "�������������Ļ��ᰡ��";
        return msg1 + msg2 + "\n" + msg3 + msg4 + "\n" + msg5;
}

string good_zhuisha_msg(string name,string place,string difficult)
{
        string msg1,msg2,msg3,msg4,msg5;
        msg1 = replace_string(good_msg1[random(sizeof(good_msg1))],"name",name);
        msg2 = search_msg[random(sizeof(search_msg))];
        msg3 = replace_string(good_msg2[random(sizeof(good_msg2))],"place",place);
        msg4 = good_msg3[random(sizeof(good_msg3))];
        msg5 = "��������ѶȾ�����ͬ��˵��" + difficult + "�����Լ����Ű죡";
        return msg1 + msg2 + "\n" + msg3 + msg4 + "\n" + msg5;
}

void check_xuncheng()
{
        int i,j,xc_num,bonus,have_it = 0;
        string *city_id, *xc_map, *all_map;
        string the_place, data;
        string bunch_id;
        mapping *bunch_quest,xc_quest;
        string date;

        date = NATURE_D->game_time();
        sscanf(date, "%s��%*s��", date);

        city_id = keys(city);
        for (i=0;i < sizeof(city_id);i++)
        {
                bunch_quest = bunch_city_quest[city_id[i]];

                //���������û�б仯������Ѳ�������Ѿ����ڣ��Ͳ�����
                if (sizeof(bunch_quest))
                {
                        for (j = 0;j<sizeof(bunch_quest);j++)
                                if (bunch_quest[j]["id"] == "xc")
                                        //�������Ѳ�����������ڣ�������ڱ仯����ɾ��������
                                        if (bunch_quest[j]["date"] == date)
                                                have_it = 1;
                                        else
                                                bunch_quest[j] = 0;
                        if (have_it) return;
                }
                bunch_quest -= ({ 0 });

                xc_map=({});
                all_map=place[city[city_id[i]]];

                //Ѳ�ǵĽ������ݳ��а����ĵط���С��ȷ����
                bonus = sizeof(all_map);
                if (bonus<40) bonus=40;
                if (bonus>70) bonus=70;

                //�Ӹó��е�ͼ�����ѡ��10��20���ص���ΪѲ������
                xc_num=10+random(10);
                bonus += xc_num;
                bonus += random(bonus)*2;
                bonus *= 10;

                for (j=0;j<xc_num;j++)
                {
                        the_place = all_map[random(sizeof(all_map))];
                        xc_map += ({ the_place });
                        all_map -= ({ the_place });
                }

                xc_quest = ([]);

                xc_quest["id"]="xc";
                xc_quest["time"]=time();
                xc_quest["name"]="Ѳ" + city[city_id[i]];
                xc_quest["type"]="Ѳ��";
                xc_quest["bunch_type"]="bad";
                xc_quest["bonus"]=bonus;
                xc_quest["enable"]=1;
                xc_quest["place"]=xc_map;
                xc_quest["date"]=date;
                xc_quest["num"] = get_bianhao(city_id[i]);
                xc_quest["difficult"]="����";
                xc_quest["reward"]="�ϸ�";
                xc_quest["msg"] = "����ҪѲ�����µ�����\n";
                for (j=0;j<sizeof(xc_quest["place"]);j++)
                        xc_quest["msg"] += get_object(xc_quest["place"][j])->short() + "\n";
                bunch_quest += ({ xc_quest });
                bunch_city_quest[city_id[i]] = bunch_quest;
        }
        return;
}

void check_city_quest()
{
        int i,j,new_num;
        string *city_id;
        mapping *bunch_quest,*bunch_quest_good,*bunch_quest_bad;
        mixed new_quest;

        city_id = keys(city);
        for (i = 0;i < sizeof(city_id);i++)
        {
                bunch_quest = bunch_city_quest[city_id[i]];

                bunch_quest -= ({ 0 });

               //�������״�������������
                if (sizeof(bunch_quest))
                        for (j=0;j<sizeof(bunch_quest);j++)
                                if (time() - bunch_quest[j]["time"] > WAIT_TIME ||
                                    (bunch_quest[j]["type"] == "�������" && !objectp(bunch_quest[j]["ob"])) ||
                                    (bunch_quest[j]["type"] == "�������" && !objectp(bunch_quest[j]["ob"])))
                                {
                                        if ((bunch_quest[j]["type"] == "�������" || bunch_quest[j]["type"] == "�������") &&
                                            objectp(bunch_quest[j]["ob"]))
                                                bunch_quest[j]["ob"]->destruct_me();
                                        bunch_quest[j]=0;
                                }

                bunch_quest -= ({ 0 });

                //������������Ƿ����
                bunch_quest_good = filter_array(bunch_quest,(: is_the_bunch($1,"good") :));

                //��������֮��û����������ͳ�����������
                if (sizeof(bunch_quest_good))
                        new_num = QUEST_NUM - sizeof(bunch_quest_good);
                else new_num = QUEST_NUM;

                //�����񱣳���QUEST_NUM�����ң�׷ɱ����������
                if (new_num > 0)
                        for (j = 0;j < new_num;j++)
                        {
                                reset_eval_cost();
                                new_quest = create_quest(city_id[i],"good");
                                {
                                        bunch_quest += ({ new_quest });
                                        //�������ó��������б�
                                        bunch_city_quest[city_id[i]] = bunch_quest;
                                }
                        }

                //���ڵ������Ƿ����
                bunch_quest_bad = filter_array(bunch_quest,(: is_the_bunch($1,"bad") :));

                //��������֮��û����������ͳ�����������
                if (sizeof(bunch_quest_bad))
                        new_num = QUEST_NUM - sizeof(bunch_quest_bad);
                else new_num = QUEST_NUM;

                //�����񱣳���QUEST_NUM�����ң�׷ɱ����������
                if (new_num > 0)
                        for (j = 0;j < new_num;j++)
                        {
                                new_quest = create_quest(city_id[i],"bad");
                                if (mapp(new_quest))
                                {
                                        bunch_quest += ({ new_quest });
                                        //�������ó��������б�
                                        bunch_city_quest[city_id[i]] = bunch_quest;
                                }
                        }

        }
        return;
}

int is_the_bunch(mapping arg, string type)
{
        if (!mapp(arg) || !stringp(type))
                return 0;

        if (undefinedp(arg["bunch_type"]))
                return 0;

        if (arg["bunch_type"] == type)
                return 1;

        return 0;
}

varargs mixed create_quest(string the_city,string bunch_type,object player)
{
        string room,*env_rooms,obj_name,*all_city,other_city;
        mapping new_quest,obj_mapp;
        mapping all_static_npc;
        object the_room,the_npc,env,npc,jiufen_npc;
        int i,j,control,bh;

        control = 0;                //���������������ѭ��
        if (bunch_type == "good")
        {
                switch(random(4))
                {
                        case 0:
                                all_static_npc = static_npc[the_city];
                                env_rooms = keys(all_static_npc);
                                for (;;)
                                {
                                        if (control > 50) break;        //ѭ������50���ж�
                                        room = env_rooms[random(sizeof(env_rooms))];
                                        env = get_object(room);
                                        if (!env)
                                                log_file("static/party_quest",sprintf("������������¼��%s\n",room));
                                        if (! objectp(npc = present(all_static_npc[room], env)) ||
                                                      query("shen", npc)<0 )
                                        {
                                                control ++;
                                                continue;
                                        } else break;
                                }
                                if (objectp(npc))
                                {
                                        new_quest = ([]);
                                        new_quest["target"]=base_name(npc);
                                        new_quest["bunch_type"]="good";
                                        new_quest["time"]=time();
                                        new_quest["num"]=get_bianhao(the_city);
                                        new_quest["id"]=the_city+(string)new_quest["num"];
                                        new_quest["type"] = "Ѱ����Ʒ";
                                        switch(random(3))
                                        {
                                                case 0:
                                                        obj_mapp = QUEST_GOOD_OBJ("0find")->query_questdg();
                                                        new_quest["obj_name"] = obj_mapp["name"];
                                                        new_quest["bonus"] = 500;
                                                        new_quest["difficult"] = "����";
                                                        new_quest["reward"] = "��";
                                                        break;
                                                case 2:
                                                        obj_mapp = QUEST_GOOD_OBJ("1find")->query_questdg();
                                                        new_quest["obj_name"] = obj_mapp["name"];
                                                        new_quest["bonus"] = 800;
                                                        new_quest["difficult"] = "�е�";
                                                        new_quest["reward"] = "�е�";
                                                        break;
                                                case 1:
                                                        obj_mapp = QUEST_GOOD_OBJ("2find")->query_questdg();
                                                        new_quest["obj_name"] = obj_mapp["name"];
                                                        new_quest["bonus"] = 1100;
                                                        new_quest["difficult"] = "����";
                                                        new_quest["reward"] = "��";
                                                        break;
                                        }
                                        new_quest["name"]="��" + room->short() + "��" + npc->name() +
                                                          "�ҵ�" + new_quest["obj_name"];
                                        new_quest["msg"]=room->short() + "��" + npc->name() +
                                                          "��Ҫ" + new_quest["obj_name"] +
                                                          "����ȥ�����ҵ����͹�ȥ��";
                                        return new_quest;
                                } else return 0;
                                break;
                        case 1:
                                if (objectp(player))
                                        npc = create_npc(player);
                                else
                                        npc = create_npc(1);

                                env_rooms = place[city[the_city]];
                                room = env_rooms[random(sizeof(env_rooms))];
                                env = get_object(room);
                                if (!env)
                                        log_file("static/party_quest",sprintf("������������¼��%s\n",room));
                                npc->move(env);
                                set("place", env->short(), npc);
                                set("startroom", room, npc);
                                set_temp("moved", ({}), npc);
                                message_vision("$N���˹�����\n", npc);
                                random_move(npc);
                                random_move(npc);
                                random_move(npc);
                                set("shen", -20000, npc);

                                new_quest = ([]);

                                new_quest["type"]="�������";
                                new_quest["ob"]=npc;
                                new_quest["time"]=time();
                                new_quest["bunch_type"]="good";
                                new_quest["num"]=get_bianhao(the_city);
                                new_quest["id"]=the_city+(string)new_quest["num"];
                                new_quest["bonus"]=query("bonus", npc);
                                new_quest["name"]="����������" + city[the_city] +
                                                  "�����" + npc->name();
                                new_quest["place"]=query("place", npc);
                                new_quest["difficult"]=check_difficult(query("lvl", npc));
                                new_quest["reward"]=check_reward(query("lvl", npc));
                                new_quest["msg"]=npc->name() + "Σ�������վã���������������" +
                                                 city[the_city] + "�ؽ磬��֪����ͼ��Ϊ��\n��������" +
                                                 "����ʲô���µģ�����������Ϣ����" + new_quest["place"] +
                                                 "�������֡�\n�ҵ����������������ˣ�";
                                return new_quest;
                                break;
                        case 2:
                                all_city = keys(city);
                                all_city -= ({ the_city });
                                other_city = all_city[random(sizeof(all_city))];
                                all_static_npc = static_npc[other_city];
                                env_rooms = keys(all_static_npc);
                                for (;;)
                                {
                                        if (control > 50) break;        //ѭ������50���ж�
                                        room = env_rooms[random(sizeof(env_rooms))];
                                        env = get_object(room);
                                        if (!env)
                                                log_file("static/party_quest",sprintf("������������¼��%s\n",room));
                                        if (! objectp(npc = present(all_static_npc[room], env)) ||
                                                      query("shen", npc)<0 )
                                        {
                                                control ++;
                                                continue;
                                        } else break;
                                }
                                if (objectp(npc))
                                {
                                        new_quest = ([]);
                                        new_quest["target"]=base_name(npc);
                                        new_quest["bunch_type"]="good";
                                        new_quest["time"]=time();
                                        new_quest["num"]=get_bianhao(the_city);
                                        new_quest["id"]=the_city+(string)new_quest["num"];
                                        new_quest["type"] = "Ѱ����Ʒ";
                                        switch(random(3))
                                        {
                                                case 0:
                                                        obj_mapp = QUEST_GOOD_OBJ("0find")->query_questdg();
                                                        new_quest["obj_name"] = obj_mapp["name"];
                                                        new_quest["bonus"] = 500;
                                                        new_quest["difficult"] = "����";
                                                        new_quest["reward"] = "��";
                                                        break;
                                                case 2:
                                                        obj_mapp = QUEST_GOOD_OBJ("1find")->query_questdg();
                                                        new_quest["obj_name"] = obj_mapp["name"];
                                                        new_quest["bonus"] = 900;
                                                        new_quest["difficult"] = "�е�";
                                                        new_quest["reward"] = "�е�";
                                                        break;
                                                case 1:
                                                        obj_mapp = QUEST_GOOD_OBJ("2find")->query_questdg();
                                                        new_quest["obj_name"] = obj_mapp["name"];
                                                        new_quest["bonus"] = 1300;
                                                        new_quest["difficult"] = "����";
                                                        new_quest["reward"] = "��";
                                                        break;
                                        }

                                        new_quest["name"]="��" + city[other_city]+ room->short() +
                                                          "��" + npc->name() +
                                                          "�ҵ�" + new_quest["obj_name"];

                                        new_quest["msg"]=city[other_city] + room->short() +
                                                          "��" + npc->name() +
                                                          "��Ҫ" + new_quest["obj_name"] +
                                                          "����ȥ�����ҵ����͹�ȥ��";
                                        return new_quest;
                                } else return 0;
                                break;
                        case 3:
                                all_static_npc = static_npc[the_city];
                                env_rooms = keys(all_static_npc);
                                for (;;)
                                {
                                        if (control > 50) break;        //ѭ������50���ж�
                                        room = env_rooms[random(sizeof(env_rooms))];
                                        env = get_object(room);
                                        if (!env)
                                                log_file("static/party_quest",sprintf("������������¼��%s\n",room));
                                        if (! objectp(npc = present(all_static_npc[room], env)) ||
                                                      query("shen", npc)<0 )
                                        {
                                                control ++;
                                                continue;
                                        } else break;
                                }
                                if (objectp(npc))
                                {
                                        new_quest = ([]);
                                        new_quest["bunch_type"]="good";
                                        new_quest["time"]=time();
                                        new_quest["num"]=get_bianhao(the_city);
                                        new_quest["id"]=the_city+(string)new_quest["num"];
                                        new_quest["type"] = "�������";
                                        switch(random(3))
                                        {
                                                case 0:
                                                        obj_mapp = QUEST_GOOD_OBJ("0find")->query_questdg();
                                                        new_quest["obj_name"] = obj_mapp["name"];
                                                        new_quest["bonus"] = 600;
                                                        new_quest["difficult"] = "����";
                                                        new_quest["reward"] = "��";
                                                        break;
                                                case 2:
                                                        obj_mapp = QUEST_GOOD_OBJ("1find")->query_questdg();
                                                        new_quest["obj_name"] = obj_mapp["name"];
                                                        new_quest["bonus"] = 1000;
                                                        new_quest["difficult"] = "�е�";
                                                        new_quest["reward"] = "�е�";
                                                        break;
                                                case 1:
                                                        obj_mapp = QUEST_GOOD_OBJ("2find")->query_questdg();
                                                        new_quest["obj_name"] = obj_mapp["name"];
                                                        new_quest["bonus"] = 1400;
                                                        new_quest["difficult"] = "����";
                                                        new_quest["reward"] = "��";
                                                        break;
                                        }
                                        jiufen_npc = new(CLASS_D("generate") + "/jiufen_npc");
                                        NPC_D->generate_cn_name(jiufen_npc);
                                        jiufen_npc->move(env);
                                        message_vision("$N���˹���������$n����ϲ��ŭ��ԭ����������ﰡ��\n",jiufen_npc,npc);
                                        jiufen_npc->set_leader(npc);
                                        jiufen_npc->set_jiufen_object(npc);
                                        jiufen_npc->set_quest_ob(new_quest["obj_name"]);
                                        jiufen_npc->set("inquiry/����","TNND,"+npc->name()+
                                                    "ȥ���������������" + new_quest["obj_name"] +
                                                    "�����ڻ�û�л����ң�");
                                        new_quest["ob"]=jiufen_npc;
                                        new_quest["name"]="��" + room->short() + "��" + npc->name() +
                                                          "�������";
                                        new_quest["msg"]=room->short() + "��" + npc->name() +
                                                          "��" + jiufen_npc->name() + "�����˾��ף���ȥ" +
                                                          "�����ǵ���һ�°ɡ�";
                                        return new_quest;
                                } else return 0;
                                break;
                }
        } else
        {
                switch(random(4))
                {
                        case 0:
                                all_static_npc = static_npc[the_city];
                                env_rooms = keys(all_static_npc);
                                for (;;)
                                {
                                        if (control > 50) break;        //ѭ������50���ж�
                                        room = env_rooms[random(sizeof(env_rooms))];
                                        env = get_object(room);
                                        if (!env)
                                                log_file("static/party_quest",sprintf("������������¼��%s\n",room));
                                        if (! objectp(npc = present(all_static_npc[room], env)) ||
                                                      query("shen", npc)>0 )
                                        {
                                                control ++;
                                                continue;
                                        } else break;
                                }
                                if (objectp(npc))
                                {
                                        new_quest = ([]);
                                        new_quest["target"]=base_name(npc);
                                        new_quest["bunch_type"]="bad";
                                        new_quest["time"]=time();
                                        new_quest["num"]=get_bianhao(the_city);
                                        new_quest["id"]=the_city+(string)new_quest["num"];
                                        new_quest["type"] = "Ѱ����Ʒ";
                                        switch(random(3))
                                        {
                                                case 0:
                                                        obj_mapp = QUEST_BAD_OBJ("0find")->query_questkh();
                                                        new_quest["obj_name"] = obj_mapp["name"];
                                                        new_quest["bonus"] = 500;
                                                        new_quest["difficult"] = "����";
                                                        new_quest["reward"] = "��";
                                                        break;
                                                case 2:
                                                        obj_mapp = QUEST_BAD_OBJ("1find")->query_questkh();
                                                        new_quest["obj_name"] = obj_mapp["name"];
                                                        new_quest["bonus"] = 800;
                                                        new_quest["difficult"] = "�е�";
                                                        new_quest["reward"] = "�е�";
                                                        break;
                                                case 1:
                                                        obj_mapp = QUEST_BAD_OBJ("2find")->query_questkh();
                                                        new_quest["obj_name"] = obj_mapp["name"];
                                                        new_quest["bonus"] = 1100;
                                                        new_quest["difficult"] = "����";
                                                        new_quest["reward"] = "��";
                                                        break;
                                        }
                                        new_quest["name"]="��" + room->short() + "��" + npc->name() +
                                                          "�ҵ�" + new_quest["obj_name"];
                                        new_quest["msg"]=room->short() + "��" + npc->name() +
                                                          "��Ҫ" + new_quest["obj_name"] +
                                                          "����ȥ�����ҵ����͹�ȥ��";
                                        return new_quest;
                                } else return 0;
                                break;
                        case 1:
                                if (objectp(player))
                                        npc = create_npc(player);
                                else
                                        npc = create_npc(1);

                                env_rooms = place[city[the_city]];
                                room = env_rooms[random(sizeof(env_rooms))];
                                env = get_object(room);
                                if (!env)
                                        log_file("static/party_quest",sprintf("������������¼��%s\n",room));
                                npc->move(env);
                                set("place", env->short(), npc);
                                set("startroom", room, npc);
                                set_temp("moved", ({}), npc);
                                message_vision("$N���˹�����\n", npc);
                                random_move(npc);
                                random_move(npc);
                                random_move(npc);
                                set("shen", 20000, npc);

                                new_quest = ([]);

                                new_quest["type"]="�������";
                                new_quest["ob"]=npc;
                                new_quest["time"]=time();
                                new_quest["bunch_type"]="bad";
                                new_quest["num"]=get_bianhao(the_city);
                                new_quest["id"]=the_city+(string)new_quest["num"];
                                new_quest["bonus"]=query("bonus", npc);
                                new_quest["name"]="����������" + city[the_city] +
                                                  "���Ƶ�" + npc->name();
                                new_quest["place"]=query("place", npc);
                                new_quest["difficult"]=check_difficult(query("lvl", npc));
                                new_quest["reward"]=check_reward(query("lvl", npc));
                                new_quest["msg"]=npc->name() + "��Ȼ����������ʿ�����Ǹ����Ǻڵ�����"+
                                                 "���ԣ���������������" + city[the_city] +
                                                 "�ؽ硣\n����ֺ����������ӣ����߲��ƣ�"+
                                                 "����������Ϣ������" + new_quest["place"] +
                                                 "�������֡�\n�ҵ��������������ˣ�";
                                return new_quest;
                                break;
                        case 2:
                                all_city = keys(city);
                                all_city -= ({ the_city });
                                other_city = all_city[random(sizeof(all_city))];
                                all_static_npc = static_npc[other_city];
                                env_rooms = keys(all_static_npc);
                                for (;;)
                                {
                                        if (control > 50) break;        //ѭ������50���ж�
                                        room = env_rooms[random(sizeof(env_rooms))];
                                        env = get_object(room);
                                        if (!env)
                                                log_file("static/party_quest",sprintf("������������¼��%s\n",room));
                                        if (! objectp(npc = present(all_static_npc[room], env)) ||
                                                      query("shen", npc)>0 )
                                        {
                                                control ++;
                                                continue;
                                        } else break;
                                }
                                if (objectp(npc))
                                {
                                        new_quest = ([]);
                                        new_quest["bonus"]=600;
                                        new_quest["difficult"]="����";
                                        new_quest["reward"]="��";
                                        new_quest["target"]=base_name(npc);
                                        new_quest["bunch_type"]="bad";
                                        new_quest["time"]=time();
                                        new_quest["num"]=get_bianhao(the_city);
                                        new_quest["id"]=the_city+(string)new_quest["num"];
                                        new_quest["type"] = "������";
                                        new_quest["send_msg"] = need_send_msg[random(sizeof(need_send_msg ))];
                                        new_quest["name"]="��" + city[other_city]+ room->short() +
                                                          "��" + npc->name() +
                                                          "��һ������";

                                        new_quest["msg"]=city[other_city] + room->short() +
                                                          "��" + npc->name() +
                                                          "Ҳ�����Ǻڵ����ֵܣ�������Ҫ�㴫�����Ÿ�" +
                                                          ((query("gender", npc) == "Ů��")?"��":"��")+
                                                          "��\n�����ǣ�" + new_quest["send_msg"];
                                        return new_quest;
                                } else return 0;
                                break;
                        case 3:
                                all_static_npc = static_npc[the_city];
                                env_rooms = keys(all_static_npc);
                                for (;;)
                                {
                                        if (control > 50) break;        //ѭ������50���ж�
                                        room = env_rooms[random(sizeof(env_rooms))];
                                        env = get_object(room);
                                        if (!env)
                                                log_file("static/party_quest",sprintf("������������¼��%s\n",room));
                                        if (! objectp(npc = present(all_static_npc[room], env)) ||
                                                      query("shen", npc)>0 )
                                        {
                                                control ++;
                                                continue;
                                        } else break;
                                }
                                if (objectp(npc))
                                {
                                        new_quest = ([]);
                                        new_quest["bunch_type"]="bad";
                                        new_quest["time"]=time();
                                        new_quest["num"]=get_bianhao(the_city);
                                        new_quest["id"]=the_city+(string)new_quest["num"];
                                        new_quest["type"] = "�������";
                                        switch(random(3))
                                        {
                                                case 0:
                                                        obj_mapp = QUEST_GOOD_OBJ("0find")->query_questdg();
                                                        new_quest["obj_name"] = obj_mapp["name"];
                                                        new_quest["bonus"] = 600;
                                                        new_quest["difficult"] = "����";
                                                        new_quest["reward"] = "��";
                                                        break;
                                                case 2:
                                                        obj_mapp = QUEST_GOOD_OBJ("1find")->query_questdg();
                                                        new_quest["obj_name"] = obj_mapp["name"];
                                                        new_quest["bonus"] = 900;
                                                        new_quest["difficult"] = "�е�";
                                                        new_quest["reward"] = "�е�";
                                                        break;
                                                case 1:
                                                        obj_mapp = QUEST_GOOD_OBJ("2find")->query_questdg();
                                                        new_quest["obj_name"] = obj_mapp["name"];
                                                        new_quest["bonus"] = 1300;
                                                        new_quest["difficult"] = "����";
                                                        new_quest["reward"] = "��";
                                                        break;
                                        }
                                        jiufen_npc = new(CLASS_D("generate") + "/jiufen_npc");
                                        NPC_D->generate_cn_name(jiufen_npc);
                                        jiufen_npc->move(env);
                                        message_vision("$N���˹���������$n����ϲ��ŭ��ԭ����������ﰡ��\n",jiufen_npc,npc);
                                        jiufen_npc->set_leader(npc);
                                        jiufen_npc->set_jiufen_object(npc);
                                        jiufen_npc->set_quest_ob(new_quest["obj_name"]);
                                        jiufen_npc->set("inquiry/����","��������,"+npc->name()+
                                                    "ȥ���������������" + new_quest["obj_name"] +
                                                    "�����ڻ�û�л����ң�");
                                        new_quest["ob"]=jiufen_npc;
                                        new_quest["name"]="��" + room->short() + "��" + npc->name() +
                                                          "�������";
                                        new_quest["msg"]=room->short() + "��" + npc->name() +
                                                          "��" + jiufen_npc->name() + "�����˾��ף���ȥ" +
                                                          "�����ǵ���һ�°ɡ�";
                                        return new_quest;
                                } else return 0;
                                break;
                }
        }
        return 0;
}

//���������ڲ��ҵص��б��Ĵ���
void check_all_place()
{
        int i,j;
        string *all_city, *the_place;
        object env;

        all_city = keys(city);
        for (i = 0;i < sizeof(all_city);i++)
        {
                the_place = place[city[all_city[i]]];
                for (j = 0;j<sizeof(the_place);j++)
                        if (!objectp(env = get_object(the_place[j])))
                                log_file("static/party_quest",sprintf("������������¼��%s\n",the_place[j]));
        }
}

varargs void delete_city_quest(string arg,string type,string bh)
{
        int i;
        mapping *bunch_quest;
        if (!arg)
        {
                bunch_city_quest = ([]);
                return;
        }
        bunch_quest = bunch_city_quest[arg];

        if (!sizeof(bunch_quest)) return;

        if (bh)
        {
                if (bh == "xc")
                {
                        for (i = 0;i < sizeof(bunch_quest);i++)
                                if (bunch_quest[i]["id"] == "xc")
                                        bunch_quest[i]["enable"] = 0;
                } else
                {
                        for (i = 0;i < sizeof(bunch_quest);i++)
                                if (bunch_quest[i]["id"] == bh)
                                        bunch_quest[i] = 0;
                }
        } else if (type)
        {
                for (i = 0;i < sizeof(bunch_quest);i++)
                        if (bunch_quest[i]["bunch_type"] == type)
                                if (bunch_quest[i]["id"] == "xc")
                                        bunch_quest[i]["enable"] = 0;
                                else
                                        bunch_quest[i] = 0;
        } else bunch_quest = ({});
        bunch_quest -= ({ 0 });
        bunch_city_quest[arg] = bunch_quest;
        return;
}