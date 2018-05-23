//yanhuo.c 焰火

inherit ITEM;
#include <ansi.h>
int fire(object me, object ob);

void create()
{
    set_name(HIM "烟花" NOR, ({"yan hua","yanhua"}));
    set("unit", "个");
    set("long", "这是还未点燃的烟花。\n");
    set("value",1000000);
    setup();
}

int fire(object me, object ob)
{
    object obj=this_object();

    message_vision("$N用" + ob->name() + "点燃了" + name() +"。\n", me);

    message_vision("一道火光冲天而起，“砰”的一声散开，化作满天美丽的图案....\n",me,ob);
    switch(random(15))
    {
        case 0:
        tell_room(environment(me),BLINK+HIM@TEXT

　　　　　　　　|愛|↘ ㊣◥ 〖ILOVEYOU〗◤㊣ ↙ |永|
　　　　　　　　|妳|≈● ☆╓══╦══╖☆ ○≈|遠|
　　　　　　　　|之| /█\╭╩╮ぬ‖め╭╩╮/█\ |不|
　　　　　　　　|心|★∏※╲╱ ぁΨん ╲╱※∏★|變|

TEXT NOR);
        break;

        case 1:
        tell_room(environment(me),BLINK+HIY@TEXT

　　　　　　　　　　　　　　　\\\|///
　　　　　　　　　　　　　　\\　.-.-　//
　　　　　　　　.　　　　　　(　.@.@　)
　　　　　　　　+-------oOOo-----(_)-----oOOo---------+
　　　　　　　　|　　　 　　　　　　　　　　　　　　　|
　　　　　　　　|　    　祝   你   快  乐！！！ 　  　|
　　　　　　　　|　　　　　　　　　　　　　　　　 　　|
　　　　　　　　+---------------------Oooo------------+

TEXT NOR);
        break;

        case 2:
        tell_room(environment(me),BLINK+HIC@TEXT

　　　　　　　　︵︵︵oοΟミ ╱╲╱╲ ミΟοo︵︵︵
  　　　　　　　　〔云淡⿰〕  ╲封╲╱  〔⿰心如〕
  　　　　　　　　〔⿰风轻〕  ╱╲心╲  〔止水⿰〕
　　　　　　　　    ︶︶╭☆╯╲╱╲╱╰☆╮

TEXT NOR);
        break;

        case 3:
        tell_room(environment(me),BLINK+HIG@TEXT

　　　　　　　　　︵︵︵oοΟミ┏永┓ミΟοo︵︵︵
　　　　　　　　〔愛妳⿰〕 oO天║遠║地0o 〔永不..〕
　　　　　　　　〔..一生〕 0o為║愛║證o0 〔⿰後悔〕
　　　　　　　　  ︶︶︶╭☆╯ ┗妳┛ ╰☆╮

TEXT NOR);
        break;

        case 4:
        tell_room(environment(me),BLINK+HIR@TEXT

　　　　　　　　◢◣◢◣ 我現在最  ╓══╦══╖
　　　　　　　　████ 大的願望╭╩╮我‖好╭╩╮
　　　　　　　　◥██◤ 就是想妳 ╲╱ 是‖愛 ╲╱
　　　　　　　　  ◥◤   陪著我!!    ★好愛妳★

TEXT NOR);
        break;

        case 5:
        tell_room(environment(me),BLINK+HIC@TEXT

　　　　　　　　::∴★∵**☆．∴★∵**☆．
　　　　　　　　  █████．☆．∵★∵∴☆．
　　　　　　　　  █田█田█．*☆．∴★∵．
　　　　　　　　  █田█田█．★∵∴☆．★∵∴．
　　　　　　　　  █田█田█．同一个星空下★..**．
　　　　　　　　  █田█田█．望著天空的星星雨**☆．
　　　　　　　　  █████．
　　　　　　　　◢██□██◣．~~~~~*^_^* 

TEXT NOR);
        break;

        case 6:
        tell_room(environment(me),BLINK+HIM@TEXT


　　　　　　　　         ★★ ★★       ★★  ★★
　　　　　　　　▲    ★ ☆☆★☆☆★  ★☆☆★☆☆ ★    
　　　　　　　　■■■■■■■■■■■■■■■■■■■■■〓→   
　　　　　　　　▲       ★  ☆ ★      ★  .☆  ★
　　　　　　　　           ★  ★          ★  ★
　　　　　　　　             ★              ★

TEXT NOR);
        break;

        case 7:
        tell_room(environment(me),BLINK+HIR@TEXT

                    * *   * *   *    * *
                  *     *     *   *      *
               <========      *==        *==<<<<<<
                    *       *          *
                      *   *     *    *      
                        *         *

TEXT NOR);
        break;

        case 8:
        tell_room(environment(me),BLINK+HIB@TEXT

　　　　　　　　记得我们的星空吗？好美！
　　　　　　　　　　　　   . ☆   .   ?  .  ?     .  ? .
　　　　　　　　　　  　     **    .   ?       〇    ? 
　　　　　　　　 　　　　 ? ***N   .       ? ｏ    ?  . 
　　　　　　　　 　　  　? *i****     ?  .  o    ?       ?
　　　　　　　　    　　　X***J***         ＿＿П   ＼ ／＼
　　　　　　　　   　　　**X*****o*     ／＼　Ц＼ 

TEXT NOR);
        break;

        case 9:
        tell_room(environment(me),BLINK+HIB@TEXT

　　　　　　　　∴°★．☆° ．★·°∴°★．° ．·。∴°
　　　　　　　　☆ ．·°∴° ☆．．·°∴°．☆°★°∴°
　　　　　　　　°∴ 那怕星际无垠 ☆° ．·★°∴°．°°
　　　　　　　　∴°．°★ ．·°∴°．°∴°．★☆° ．·
　　　　　　　　°．☆° ．★·我也要追到你 °．°°．★
　　　　　　　　．·°∴★°．°∴°．☆° ．·°∴°．°
　　　　　　　　．·°∴°★．°．∴·°°并永远爱你∴☆°

TEXT NOR);
        break;

        case 10:
        tell_room(environment(me),BLINK+HIY@TEXT

　　　　　　　　    ☆☆ ☆☆  ☆☆ ☆☆
　　　　　　　　  ★★       ★      ★★
　　　　　　　　 ☆☆     祝你快乐    ☆☆
　　　　　　　　  ★★               ★★
　　　　　　　　   ☆☆             ☆☆
　　　　　　　　     ★★         ★★
　　　　　　　　       ☆☆     ☆☆
　　　　　　　　         ★★  ★★
　　　　　　　　            ☆☆

TEXT NOR);
        break;

        case 11:
        tell_room(environment(me),BLINK+HIC@TEXT

　　　　　　　　█◤☆◥◤☆◥█ 送星星千百颗...
　　　　　　　　█☆☆☆☆☆☆█ 
　　　　　　　　█◣☆☆☆☆◢█ 生命活的精彩灿烂...
　　　　　　　　██◣☆☆◢██ 
　　　　　　　　███◣◢███ 愿你快乐  ^_^

TEXT NOR);
        break;

        case 12:
        tell_room(environment(me),BLINK+HIG@TEXT

　　　　　　　　@* .☆ / ＊/　.　/ * . ☆/ ＊。
　　　　　　　　   ◢◣。       ◢◣。
　　　　　　　　  ◢★◣。     ◢★◣。
　　　　　　　　 ◢■■◣。   ◢■■◣。
　　　　　　　　◢■■■◣。 ◢■■■◣。
　　　　　　　　︸︸||︸︸ !!︸︸||︸︸
　　　　　　　　愿您有快乐的每一天

TEXT NOR);
        break;

        case 13:
        tell_room(environment(me),BLINK+HIW@TEXT

　　　　　　　　::.--.-.::
　　　　　　　　:( (    ):::::  东边日出西边雨 
　　　　　　　　(_,  \ ) ,_)::  道是无晴却有情       |
　　　　　　　　:::-'--`--:::::::: ~~|     ,       \ _ /
　　　　　　　　::::::::::::::::::: ,|`-._/|   -==  (_)  ==-
　　　　　　　　::::::::^^::::::::.' |   /||\      /   \
　　　　　　　　::::::^^::::::::.'   | ./ ||`\       |
　　　　　　　　:::::::::::::::/ `-. |/._ ||  \
　　　　　　　　::::::::::::::|      ||   ||   \
　　　　　　　　 ~~=~_~^~ =~ \~~~~~~~'~~~~'~~~~/~~`` ~=~^~
　　　　　　　　~^^~~-=~^~ ^ `--------------'~^~=~^~_~^=~^~

TEXT NOR);
        break;

        case 14:
        tell_room(environment(me),BLINK+HIW@TEXT

　　　　　　　　　★　　 ◢◣　
　　　　　　　　　　　　　　　　　　　　　◢◢◣　　　☆　
　　　　　　　　　　　　　 /○\ ●　　　 ◢◢◣◣　　　 ┌────┐　
　　　　　　　　　　　　　 /■\/■\　　◢◢◢◣◣◣　　 │两情相悦│　
　　　　　　　　　 ╪═╪　 <|　||　　═╪═╪═╪═╪　└┬──┬┘

TEXT NOR);
        break;
    }
    me->start_busy(1);
    destruct(obj);
    return 1;
}
