
#include <armor.h>
#include <ansi.h>

inherit ARMOR;

void create()
{
        set_name(HIR "ÆÆÌì¼×" NOR, ({ "potian jia" }) );
        set_weight(1000);
                set("long", HIW "ÕâÊÇÒ»ÕÅÆÕÆÕÍ¨Í¨µÄ»¤¼×£¬»¤¼×ÖÜÎ§É¢·¢³öµ­µ­µÄÎíÆø½«ÆäÖÜÉíÁıÕÖ"
                        "Ê²Ã´Ò²¿´²»Çå¡£\n" HIC
                    HIC "ÓĞĞ§ÕĞ¼ÜĞŞÕı£º+ 100        ÓĞĞ§Çá¹¦ĞŞÕı£º+ 100\n" NOR
                    HIC "¿¹¶¾Ğ§¹ûĞŞÕı£º+ 20%        ·ÀÓùĞ§¹ûµÈ¼¶£º  300\n" NOR
                    HIC "¿¹¶¾»Ø±ÜĞŞÕı£º+ 40%\n" NOR);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "¼ş");
                set("material", "steel");
                                set("value", 800000);
                set("armor_prop/armor", 300);
                        set("armor_prop/dodge", 100);
                                set("armor_prop/parry", 100);
                        set("armor_prop/reduce_poison", 20);
                                set("armor_prop/avoid_poison", 40);
                }
                set("material", "tian jing");
                set("wear_msg", HIR "ÆÆÌì¼×ÆÆ¿Õ¶øÏì£¬ÕóÕóÎíÆøËæÖ®¶ø³ö£¬È´ÔçÒÑÓë$N" HIC "ºÏ¶øÎªÒ»¡£[2;37;0m\n" NOR);
                set("remove_msg", HIR "$N" HIC "ÑöÌì³¤Ğ¥£¬ÆÆÌì¼×¶£ßÊ×öÏì£¬É²ÄÇ¼äÖÜÎ§ÎíÆø½¥É¢£¬µ«ÆÆÌì¼×ÔçÒÑ"
                                                        "ÏûÊ§ÓÚÌì¼Ê¡£\n" NOR);

        setup();
}

int query_autoload()
{
        return 1;
}
/*
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;
        int cost;  

        if ((int)me->query_skill("force", 1) < 260
           || (int)me->query("neili") < 500
           || ! living(me) || random(4) != 1)
                return;

        cost = damage / 2;

        if (cost > 300) cost = 300;

        ap = ob->query_skill("force") * 12 + ob->query("max_neili");
        dp = me->query_skill("force") * 12 + me->query("neili");

        if (ap / 2 + random(ap) < dp)
        {
                me->add("neili", -cost);
                result = ([ "damage": -damage ]);

                switch (random(4))
                {
                case 0:
                        result += (["msg" : HIR "$n" HIR "Æ½¾²µØ¿´×Å$N" HIR "£¬$N" HIR "ÄÔ"
                                            "×ÓÒ»Æ¬Ã£È»£¬ĞÄÏë£ºÄÑµÀÕâĞ¡×ÓÊÇÀÏÇ§£¿\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIR "$n" HIR "Æ½¾²µØ¿´×Å$N" HIR "£¬$N" HIR "ÄÔ"
                                            "×ÓÒ»Æ¬Ã£È»£¬ĞÄÏë£ºÄÑµÀÕâĞ¡×ÓÊÇÀÏÇ§£¿\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIR "$n" HIR "Æ½¾²µØ¿´×Å$N" HIR "£¬$N" HIR "ÄÔ"
                                            "×ÓÒ»Æ¬Ã£È»£¬ĞÄÏë£ºÄÑµÀÕâĞ¡×ÓÊÇÀÏÇ§£¿\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIR "$n" HIR "Æ½¾²µØ¿´×Å$N" HIR "£¬$N" HIR "ÄÔ"
                                            "×ÓÒ»Æ¬Ã£È»£¬ĞÄÏë£ºÄÑµÀÕâĞ¡×ÓÊÇÀÏÇ§£¿\n" NOR]);
                        break;
                }
                return result;
        }
}
*/