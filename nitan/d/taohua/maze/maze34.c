// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

#include "maze.h"

void create()
{
        set("short", "ʯ��");
        set("long", @LONG
����һ����ԼĪ���˶�ߵĴ�ʯ�鹹�ɵ���ʯ�󣬹�ģ�ƺ����󣬵�
̧����ȥ�����ܾ������ص�������Ᾱ�ʯ����ȫ��������·ͨ��ʯ��֮�⣬
��֮���г�������������������������ͷ����ʯ������һ��б����ʯ��(s
hibei)�������ڸ����С�
LONG );

        set("exits", ([
                "east"  : __DIR__"maze16",
                "south" : __DIR__"maze9",
                "north" : __DIR__"maze14",
        ]));

        set("item_desc", ([
                "shibei" : "
������׳�����ꡣ
�������ţ�׳��ֺ�����ף����ڡ�
�����Ŷ����꼪��
����������С����׳���������裬������ ���򴥷�������ǡ�
�������ģ��꼪����������������׳�ڴ���֮����
�������壺ɥ�����ף��޻ڡ�
�������������򴥷��������ˣ������죬�����������򼪡�
��  �� �� �� ��
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 34, me);
        check_count(me, 34);
        return;
}