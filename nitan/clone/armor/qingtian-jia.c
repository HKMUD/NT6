
#include <armor.h>
#include <ansi.h>

inherit ARMOR;

void create()
{
        set_name(HIC "ÇàÌì¼×" NOR, ({ "qingtian jia" }) );
        set_weight(1000);
                set("long", HIW "ÕâÊÇÒ»ÕÅÆÕÆÕÍ¨Í¨µÄ»¤¼×£¬»¤¼×ÖÜÎ§É¢·¢³öµ­µ­µÄÎíÆø½«ÆäÖÜÉíÁıÕÖ"
                        "Ê²Ã´Ò²¿´²»Çå¡£\n" HIC
                    HIC "ÓĞĞ§ÕĞ¼ÜĞŞÕı£º+ 100        ÓĞĞ§Çá¹¦ĞŞÕı£º+ 100\n" NOR
                    HIC "¿¹¶¾Ğ§¹ûĞŞÕı£º+ 30%        ·ÀÓùĞ§¹ûµÈ¼¶£º  300\n" NOR
                    HIC "¿¹¶¾»Ø±ÜĞŞÕı£º+ 30%\n" NOR);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "¼ş");
                set("material", "steel");
                                set("value", 800000);
                set("armor_prop/armor", 300);
                        set("armor_prop/dodge", 100);
                                set("armor_prop/parry", 100);
                        set("armor_prop/reduce_poison", 30);
                                set("armor_prop/avoid_poison", 30);
                }
                set("material", "tian jing");
                set("wear_msg", HIC "ÇàÌì¼×ÆÆ¿Õ¶øÏì£¬ÕóÕóÎíÆøËæÖ®¶ø³ö£¬È´ÔçÒÑÓë$N" HIC "ºÏ¶øÎªÒ»¡£[2;37;0m\n" NOR);
                set("remove_msg", HIC "$N" HIC "ÑöÌì³¤Ğ¥£¬ÇàÌì¼×¶£ßÊ×öÏì£¬É²ÄÇ¼äÖÜÎ§ÎíÆø½¥É¢£¬µ«ÇàÌì¼×ÔçÒÑ"
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
                        result += (["msg" : HIR "$n" HIR "ÇáÇáÒ»Ì¾£¬ÉíÉÏ" HIC "ÇàÌì¼×" HIR "¶£ßÊ"
                                            "×öÏì£¬$N" HIR "Ö»¾õĞÄÍ·Ò»ÕóÆà¿à¡£ÕâÒ»ÕĞ¾ÓÈ»´ò²»ÏÂÈ¥¡£\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIM "Ö»¼û$n" HIM "ÉíÉÏ" HIC "ÇàÌì¼×" HIM "Ò»²ü£¬ÓĞ"
                                            "ÈôÁúÒ÷¡£" HIM "$N" HIM "ÄãÖ»¸ĞÍ·ÔÎÄ¿Ñ££¬¾ÓÈ»Ò»ÕĞ´òÔÚ¿Õ´¦¡£\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIW "$N" HIW "Ò»ÕĞ´òÖĞ$n" HIW "£¬¶Ù¾õºÁ²»ÊÜÁ¦¡£¶¨¾¦Ò»¿´£¬Ô­À´ÊÇ"
                                            "µÄ" HIC "ÇàÌì¼×" HIW "»Ã»¯³öÀ´µÄ»ÃÏó¡£\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIY "$n" HIY "ÉíÉÏ" HIC "ÇàÌì¼×" HIY "Ò»Õó½ğ¹âÉÁ¹ı£¬$N" HIY "ÕâÒ»"
                                            "ÕĞ±»½ğ¹âÀÎÀÎµ²×¡£¬ÉË²»ÁË$n" HIY "·ÖºÁ¡£\n" NOR]);
                        break;
                }
                return result;
        }
}
*/