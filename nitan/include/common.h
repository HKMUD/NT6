// common.h

// 噸宥麗瞳双燕

// weapon : 冷匂
// sword　: 州
// knife　: 悵遍
// axe　　: 見遊
// mace　 : 嬌
// club　 : 漉
// bow　　: 広
// javelin: 炎嚢
// spear　: 狸
// hammer : 憾

// equip　: 廾姥
// helmet : 遊据
// armor　: 擦遮
// shield : 芹
// gloves : 返耗
// boots　: 僖徨
// belt　 : 劈揮
// ring　 : 巡峺
// amulet : 擦憲
// charm　: 蔑麗 - 蒙寄, 寄侏, 弌侏
// other　: 凪麿

mapping common_list = ([
        "weapon" : ([   "sword" : ([ "short sword": "玉州", "scimitar" : "淀偽",
　　　　　　　　　　　　　　　　　 "sabre"　　　: "瀧偽", "fachion"　: "漕埖偽",
　　　　　　　　　　　　　　　　　 "long sword" : "海州", "war sword": "媾州",
　　　　　　　　　　　　　　　　　 "crystal sword"　: "邦唱州", "broad sword"　: "姓州",
　　　　　　　　　　　　　　　　　 "two-hand sword" : "褒返州", "claymore"　　 : "褒釆偽",
　　　　　　　　　　　　　　　　　 "giant sword"　　: "賞州",　 "bastard sword": "謎佩州",
　　　　　　　　　　　　　　　　　 "flamberge"　　　: "諮刎州", "great sword"　: "賞繁州", ]),

                        "knife" : ([ "dagger" : "玉州",　 "dirk"　: "悵遍",
　　　　　　　　　　　　　　　　　 "kris"　 : "敷釆州", "blade" : "偽",
　　　　　　　　　　　　　　　　　 "throwing knife" : "誘崟偽", "balanced knife" : "峠財偽", ]),

                        "axe"　 : ([ "hand exe"　 : "返見",　 "axe"　　　　　 : "見", 
　　　　　　　　　　　　　　　　　 "double exe" : "褒釆見", "military pick" : "媾娯",
　　　　　　　　　　　　　　　　　 "war axe"　　: "媾見",　 "large axe"　　 : "寄見",
　　　　　　　　　　　　　　　　　 "broad axe"　: "錐見",　 "battle axe"　　: "媾見",
　　　　　　　　　　　　　　　　　 "great axe"　: "賞見",　 "giant axe"　　 : "賞見", ]),

                        "mace"　: ([ "mace" : "嬌", "morning star" : "蛙佛嬌", "flail" : "銭赦", ]),
　　　　　　　　　　　
                        "club"　: ([ "club" : "漉", "spiked club"　: "兇漉", ]),
　　　　　　　　　　　
                        "bow"　 : ([ "short bow" : "玉広", "hunter's bow"　: "壮広",
                        "long bow"　: "海広", "composite bow" : "鹸栽広",
　　　　　　　　　　　　　　　　　 "short battle bow" : "玉媾広", "long battle bow" : "海媾広",
　　　　　　　　　　　　　　　　　 "short war bow"　　: "玉媾広", "long war bow"　　: "海媾広", ]),

                        "javelin" : ([ "javelin"　　　　: "炎嚢", "pilum"　: "嶷炎嚢",
　　　　　　　　　　　　　　　　　　 "short spear"　　: "玉狸", "glaive" : "瑚",
　　　　　　　　　　　　　　　　　　 "throwing spear" : "崟狸", ]),

                        "spear"　 : ([ "spear"　　　 : "狸",　 "trident" : "眉我螽",
　　　　　　　　　　　　　　　　　　 "brandistock" : "海狸", "spetum"　: "海狸",
　　　　　　　　　　　　　　　　　　 "pike"　　　　: "海嚢", ]), ]),

        "helmet" : ([ "cap"　　　 : "単徨",　 "skull cap"　: "遊据", "helm"　: "遊据", 
　　　　　　　        "full helm" : "畠遊据", "great helm" : "賞据", "crown" : "酵",
　　　　　　　　　　  "mask"　　　: "中醤",　 "bone helm"　: "糠据", ]),

　　　  "armor"　: ([ "quilted armor"　　　: "罷遮",　 "leather armor" : "討遮",
　　　　　　　　　    "hard leather armor" : "啣討遮", "studded armor" : "兇遮",
　　　　　　　　　　  "ring mail"　　　　　: "桟遮",　 "scale mail"　　: "想遮",
　　　　　　　　　　  "chain mail"　　　　 : "迄徨遮", "breast plate"　: "俟遮",
　　　　　　　　　    "splint mail"　　　　: "儲遮",　 "plate mail"　　: "菰医遮",
　　　　　　　　　　  "field plate"　　　　: "頭遮",　 "gothic plate"　: "悟蒙遮",
　　　　　　　　　　  "full plate mail"　　: "畠附遮", "ancient armor" : "症遮",
　　　　　　　　　　  "light plate"　　　　: "煤遮", ]),

        "shield" : ([ "buckler"　　　: "弌坩芹", "small shield"　: "弌芹",
　　　　　　　　　　  "large shield" : "寄芹",　 "kite shield"　 : "海芹",
　　　　　　　　　　  "tower shield" : "峠芹",　 "gothic shield" : "悟蒙芹",
　　　　　　　　　　  "bone shield"　: "糠芹",　 "spiked shield" : "兇芹", ]),

        "gloves" : ([ "leather gloves" : "討返耗", "heavy gloves"　　: "嶷返耗",
　　　　　　　　　　  "chain gloves"　 : "全返耗", "light gauntlets" : "煤鑓擦返",
　　　　　　　　　　  "gauntlets"　　　: "鑓擦返", ]),

        "boots"　: ([ "boots"　　　 : "僖徨",　 "heavy boots"　　　　: "嶷僖",
　　　　　　　　　　  "chain boots" : "迄徨僖", "light plated boots" : "煤鑓僖",
　　　　　　　　　　  "greaves"　　 : "擦誦遮", ]),

        "belt"　 : ([ "sash" : "劈揮", "light belt" : "煤劈揮",
　　　　　　　　　　  "belt" : "劈揮", "heavy belt" : "嶷劈揮",
　　　　　　　　　　  "plated belt" : "鑓劈揮", ]),

        "ring"　 : "巡峺",
        "amulet" : "擦附憲",

        "charm"　: ([ "grand charm" : "裟鯖蔑麗", "large charm" : "寄蔑麗",
　　　　　　　　　　  "small charm" : "弌蔑麗", ]),

        "potion" : ([ "healing"　: ([ "minor healing potion"　 : "弌伏凋匿",
　　　　　　　　　　　　　　　　　　  "light healing potion"　 : "煤伏凋匿",
　　　　　　　　　　　　　　　　　　  "healing potion"　　　　 : "煤伏凋匿",
　　　　　　　　　　　　　　　　　　  "greater healing potion" : "寄伏凋匿",
　　　　　　　　　　　　　　　　　　  "super healing potion"　 : "蒙雫伏凋匿", ]),
　　　　　　　　　　  "mana"　　 : ([ "minor mana potion"　 : "弌徴隈匿",
　　　　　　　　　　　　　　　　　　  "light mana potion"　 : "煤徴隈匿",
　　　　　　　　　　　　　　　　　　  "mana potion"　　　　 : "煤徴隈匿",
　　　　　　　　　　　　　　　　　　  "greater mana potion" : "寄徴隈匿",
　　　　　　　　　　　　　　　　　　  "super mana potion"　 : "蒙雫徴隈匿", ]),
　　　　　　　　　　  "antidote potion" : "盾蕎質",
　　　　　　　　　　  "thawing potion"　: "盾恭質", ]),

        "key"　 : "埒革",
        "jewel" : "帷右",
]);

// 麗瞳竃�峙勅限�
array common_rate_table = ({ "weapon", "potion", "armor", "helmet", "shield",
　　　　　　　　　　　　　　　 "key", "gloves", "boots", "belt", "ring", "amulet",
　　　　　　　　　　　　　　　 "charm", "jewel", });

static int max_rate;

int *common_rate_list = ({ 120, 100, 100, 80, 80, 70, 60, 60, 60, 20, 20, 20, 10, });
