
/*
 * Îï¼ş£º ³ÇÊĞ¾«Áé(City Maker) V1.0
 * ×÷Õß£º ±ùºÓ (Glacier@£ÛÑ©Óò£®ºÚ³±£İ)
 * ÈÕÆÚ£º 2001/01/11
 * ±¸×¢£º ES_Base_Code
 * ĞŞ¸Ä£º ¹¦ÄÜÄ£¿éĞŞ¸Ä³ÉÏòµ¼·½Ê½£¬¼ÓÈëµØÍ¼µµ´íÎóÅĞ¶Ï¡£
 *        ÈÎºÎÊ±ºòÊäÈëµã "."£¬¶¼¿ÉÒÔ·ÅÆú±à¼­¡£
 *                            Glacier -- 2001.2.20
 *
 * ĞŞ¸Ä£º ¼ÓÈë×Ô¼ºÉè¶¨ÎÄ¼şÃû¹¦ÄÜ¡£ÎÄ¼şÃûµ¼³ö¸ñÊ½Îª£º³ÇÊĞÃû_·¿¼äÃû.c
 *        ÆäÖĞ³ÇÊĞÃûÎªµØÍ¼ÎÄ¼şµÄÃû³Æ£¬·¿¼äÃûÔÚµØÍ¼ÎÄ¼şµÚÒ»ĞĞÉè¶¨¡£
 *                            Lonely -- 2001.3.12 
 */
#pragma save_binary
inherit ITEM;
inherit F_AUTOLOAD;

#include <mudlib.h>
//#define _check_map
#define _show_map

mixed maps, icons, icons1;
mapping room_short = ([]),room_filename = ([]);
string city,current_path;
string *outdoors_room;
string outdoors;
int _Mrow, _Mcol, _size;
int set_path(string arg);
int set_outdoors_room(string arg);
int save_file(string yn, string file_name, string file);
int confirm_make(string yn);
void create()
{
        set_name("³ÇÊĞ¾«Áé V1.1", ({ "citymaker", "maker" }) );
        set_weight(2000);
        set("unit", "¸ö" );
        set("long", @LONG
    Õâ¸öÊÇÒ»¸ö·½±ãÎ×Ê¦¹¤×÷µÄ¹¤¾ß£¬¿ÉÒÔ¿ìËÙ½¨Á¢ÍêÕûµÄÇøÓò½á¹¹¡£
ÇëÊ¹ÓÃ help citymaker »ñµÃÏêÏ¸°ïÖú¡£
LONG
        );
        setup();
}

void init()
{
        if( wizardp(environment()) ) {
                seteuid(getuid(environment()));
                add_action("do_makecity", "make");
                add_action("do_help", "help");
        }
}

int process_map(string file)
{
        string input,*line;
        int i,j,v;
        int _Trow, _Tcol;
        if(file_size(file)>0)
        {
            input=read_file(file);
//´¦Àí line
            line=explode(input,"\n");
            icons1=explode(line[0]," ");
            for(i=0;i<sizeof(icons1);i++)
            {
                j=i+1;
                if (strsrch(icons1[i],"\t")!=-1 || strsrch(icons1[i],".")==-1)
                {
                write("[ Citymaker ]£º·¿¼ä±êÊ¶Î»´íÎó£¬Çë¼ì²éµØÍ¼µÚÒ»ĞĞ±êÊ¶Î»[ "+ j +" == "+icons1[i]+" ]´¦¡£\n");
                write("[ Citymaker ]£ºº¬ÓĞÖÆ±í·û»òÕß<·¿¼ä±êÊ¶.·¿¼äÃû³Æ>Ö®¼ä²»º¬·Ö¸î·û\".\"¡£\n");
                return 0;
                }            
            }
            icons=allocate(sizeof(icons1));
            for(i=0;i<sizeof(icons1);i++)
            {
                //icons[i]=allocate(2);
                icons[i]=allocate(3);
                icons[i]=explode(icons1[i],".");
            }
            for(i=0;i<sizeof(icons1);i++)
            {
                room_short[icons[i][0]] = icons[i][1];
                room_filename[icons[i][0]] = icons[i][2];
            }
//´¦Àí mapping room_short
            _Trow=sizeof(line);
            _Mrow=_Trow-1;
            _size=_Trow;
            for(i=1;i<(sizeof(line));i++)
            {
                _Tcol=sizeof(line[i]);
                if (_Mcol<_Tcol) {_Mcol=_Tcol;}
            }
            if (_size<_Mcol) {_size=_Mcol;}
//´¦Àí³É¾ØÕó
            for(i=1;i<(sizeof(line));i++)
            {
                j=i+1;
                if (strsrch(line[i],"\t")!=-1)
                {
                write("[ Citymaker ]£º·¿¼ä±êÊ¶Î»´íÎó£¬Çë¼ì²éµØÍ¼µÚ["+j+"]ĞĞ[ "+line[i]+" ]´¦¡£\n");
                write("[ Citymaker ]£ºº¬ÓĞÖÆ±í·û¡£\n");
                return 0;
                }               
                for (_Tcol=sizeof(line[i]);_Tcol<_Mcol;_Tcol++)
                 {
                        line[i]+= " " ;
                 }
            }
                maps = allocate(_size);
//´¦Àí maps
                for(v=1;v<(sizeof(line));v++)
            {
            maps[v-1]=allocate(_size);
            maps[v-1]=explode(line[v],"");
            }
            return 1;
        } else return 0;
}



int makeroom(int _row, int _col)
{
        int i;
        string file_name,file,*exit_key,room;
        mapping exit=([]);
        room=maps[_row][_col];
                write("[ Citymaker ]£ºroom("+_row+","+_col+") == "+room+" ");
  if (_row>1)                       {if (maps[_row-1][_col] == "|"   && maps[_row-2][_col]!=" ")     {exit["north"]=room_filename[maps[_row-2][_col]];}}
  if (_row>1 && _col<_Mcol-1)       {if (maps[_row-1][_col+1] == "/" && maps[_row-2][_col+2]!=" ")   {exit["northeast"]=room_filename[maps[_row-2][_col+2]];}}
  if (_col<_Mcol-1)                 {if (maps[_row][_col+1] == "-"   && maps[_row][_col+2]!=" ")     {exit["east"]=room_filename[maps[_row][_col+2]];}}
  if (_row<_Mrow-1 && _col<_Mcol-1) {if (maps[_row+1][_col+1] == "\\"&& maps[_row+2][_col+2]!=" ")   {exit["southeast"]=room_filename[maps[_row+2][_col+2]];}}
  if (_row<_Mrow-1)                 {if (maps[_row+1][_col] == "|"   && maps[_row+2][_col]!=" ")     {exit["south"]=room_filename[maps[_row+2][_col]];}}
  if (_row<_Mrow-1 && _col>1)       {if (maps[_row+1][_col-1] == "/" && maps[_row+2][_col-2]!=" ")   {exit["southwest"]=room_filename[maps[_row+2][_col-2]];}}
  if (_col>1)                       {if (maps[_row][_col-1] == "-"   && maps[_row][_col-2]!=" ")      {exit["west"]=room_filename[maps[_row][_col-2]];}}
  if (_row>1 && _col>1)             {if (maps[_row-1][_col-1] == "\\"&& maps[_row-2][_col-2]!=" ")   {exit["northwest"]=room_filename[maps[_row-2][_col-2]];}}
  //file_name=current_path++"_"+room_filename[maps[_row][_col]]+".c";
  file_name=current_path+room_filename[maps[_row][_col]]+".c";
  file=sprintf("/*\n * ÎÄ¼ş    : %s (%s)\n",room_short[maps[_row][_col]],room_filename[maps[_row][_col]]);
        file+=sprintf(" * ×÷Õß    : %s(%s@%s)\n * ´´½¨    : %s\n",this_player()->query("name"),this_player()->query("id"),MUD_NAME,ctime(time()));
        file+=@FILE_HEAD
 * ¹¤¾ß    : Build with Citymaker@Glacier
 * ĞŞ¸Ä    : Changed By Lonely@ÄàÌ¶
 */
#include <ansi.h>
inherit ROOM;
void create()
{
FILE_HEAD
;
        file+=sprintf("\tset(\"short\", \"%s\");\n",room_short[maps[_row][_col]]);
file+=@FILE_LONG
        set("long", @LONG
Ò¹.²´.ÇØ.»´.¾Ó.Ë­.¼Ò£¿

LONG
);
        set("objects",([
        ]));
        set("exits",([
FILE_LONG;
;
        exit_key=keys(exit);
        for(i=0;i<sizeof(exit_key);i++) {
                file=sprintf("%s\t\"%s\" : __DIR__\"%s\",\n",file,exit_key[i],exit[exit_key[i]]);
        }
        file+=@FILE_2
        ]));
FILE_2
;
  if (member_array(lower_case(maps[_row][_col]),outdoors_room)==-1 )
{
        file+=@FILE_3
        setup();
//      replace_program(ROOM);
}
FILE_3
;
}
else {
        file+=sprintf("\tset(\"outdoors\",\"%s\");\n",city);
        file+=@FILE_3
        setup();
//      replace_program(ROOM);
}
FILE_3
;
}

return save_file("y", file_name, file);
}

int do_makecity(string arg)
{
        int _row,_col;
        string file,room;
        if (!arg) return notify_fail ("[ Citymaker ]£ºmakecity <µØÍ¼µµ°¸Ãû>\n");
        if (strsrch(arg,".")!=-1 || strsrch(arg," ")!=-1) 
        {
        write("[ Citymaker ]£º´íÎóµØÍ¼µµÃû£¬µØÍ¼µµÖĞ²»ÔÊĞí³öÏÖ\".\"»òÕß\" \"£¬\n ");
        write("              ÇëÖ±½ÓÊ¹ÓÃÄãÏë½¨Á¢µÄ³ÇÊĞÃûÎªµØÍ¼µµÃû¡£\n");
        return 1;
        }
        else
        {
        
                //city=;
                file=resolve_path(this_player()->query("cwd"), arg);
                if(process_map(file))
                {
                        write("[ Citymaker ]£ºÕıÔÚÔØÈëµØÍ¼µµ[ "+file+" ]...\n");
#ifdef _check_map
                        for(_row=0;_row<sizeof(maps);_row++)
                        {
                                for(_col=0;_col<sizeof(maps[_row]);_col++)
                                {
                                room=maps[_row][_col];
                                write("room("+_row+","+_col+") == "+room + "\n");
                                }
                        }
#endif
#ifdef _show_map
                        for(_row=0;_row<sizeof(maps);_row++)
                        {
                                for(_col=0;_col<sizeof(maps[_row]);_col++)
                                {
                                room=maps[_row][_col];
                                write(""+room + "");
                                }
                         write("\n");
                        }
                        write("[ Citymaker ]£º_Mrow = "+_Mrow+" _Mcol = "+_Mcol+"\n");
#endif
                        write("[ Citymaker ]£ºµØÍ¼µµ[ "+file+" ]ÔØÈëÍê³É!!\n");
                }
                else
                {
                        return notify_fail("[ Citymaker ]£ºµØÍ¼µµ[ "+file+" ]ÔØÈëÊ§°Ü¡£\n");
                }
        }       
          write("[ Citymaker ]£ºÇëÉè¶¨´æ´¢µµ°¸Ä¿Â¼(Ä¬ÈÏÎªµ±Ç°Ä¿Â¼)£º");
          input_to ( "set_path" );

        return 1;
}

int save_file(string yn, string file_name, string file)
{
        if( strlen(yn)<1 || yn[0]!='y' ) return 1;
        
      if(file_name[0..2]!="/u/") return 0;
//Ö»ÔÊĞíÔÚ/u/Ä¿Â¼ÏÂÃæ½¨Á¢ÎÄ¼ş
        rm(file_name);
        write(" ½¨Á¢ " + file_name + "....");
        
        if( write_file(file_name, file,1)==1 ) {
                write("OK!\n");
                return 1;
        } else
                write("ÄãÃ»ÓĞĞ´ÈëÕâ¸öµµ°¸(" + file_name + ")µÄÈ¨Àû¡£\n");
                return 0;
}

int set_path(string arg)
{
        string dir;
        if (arg == ".") { write ("[ Citymaker ]£º·ÅÆú±¾´Î²Ù×÷¡£\n"); return 1; }
        if (strsrch(arg," ")!=-1) 
        {
        write("[ Citymaker ]£º´íÎóµÄÂ·¾¶£¬ÇëÉè¶¨´æ´¢µµ°¸Ä¿Â¼(Ä¬ÈÏÎªµ±Ç°Ä¿Â¼)£º");
        input_to ( "set_path" );        
        return 1;
        }
        if(!arg)
        {
                if(dir = this_player()->query("cwd"))
                {
                        current_path=dir;
                        write("[ Citymaker ]£º×Ô¶¯Éè¶¨´æ´¢µµ°¸Ä¿Â¼Îªµ±Ç°Ä¿Â¼[ "+current_path+" ]¡£\n");
                        write("[ Citymaker ]£ºÇëÉè¶¨»§Íâ·¿¼äÀàĞÍ(ÀıÈç£ºc,g ÔòµØÍ¼Îª c¡¢g µÄ·¿¼ä½«±»Éè¶¨Îª»§Íâ)£º");
                        input_to("set_outdoors_room");
                        return 1;
                } else return notify_fail("[ Citymaker ]£ºÎŞ·¨×Ô¶¯Éè¶¨Ä¿Â¼£¬·ÅÆú²Ù×÷¡£\n");
        }
        else
        {
                dir = resolve_path(this_player()->query("cwd"), arg);
                if(file_size(dir)!=-2) { write("[ Citymaker ]£ºÃ»ÓĞÕâ¸öÄ¿Â¼£¬·ÅÆú²Ù×÷¡£\n"); return 1; }                 
                if(dir[strlen(dir)-1]!='/') dir += "/";
                current_path=dir;
                write("[ Citymaker ]£ºÉè¶¨´æ´¢µµ°¸Ä¿Â¼Îª[ "+current_path+" ]¡£\n");
                write("[ Citymaker ]£ºÇëÉè¶¨»§Íâ·¿¼äÀàĞÍ(ÀıÈç£ºc,g ÔòµØÍ¼Îª c¡¢g µÄ·¿¼ä½«±»Éè¶¨Îª»§Íâ)£º");
                input_to("set_outdoors_room");                
        }
                return 1;        
}
int set_outdoors_room(string arg)
{
        int  i;
        string *tmp,test,argt;
        argt=lower_case(arg);
        if (arg == ".") { write ("[ Citymaker ]£º·ÅÆú±¾´Î²Ù×÷¡£\n"); return 1; }     
        if (strsrch(argt," ")!=-1 )
        {
        write("[ Citymaker ]£º»§Íâ·¿¼äÀàĞÍÉè¶¨´íÎó£¬²»ÔÊĞí³öÏÖ\" \"¡£\n");
        write("[ Citymaker ]£ºÇëÉè¶¨»§Íâ·¿¼äÀàĞÍ(ÀıÈç£ºc,g ÔòµØÍ¼Îª c¡¢g µÄ·¿¼ä½«±»Éè¶¨Îª»§Íâ)£º");      
        input_to ( "set_outdoors_room" );       
        return 1;
        }
        tmp=(explode(lower_case(arg),","));
        for (i=0;i<sizeof(tmp);i++)
        {
        test=tmp[i];
        if (strlen(test)>1) {
                write("[ Citymaker ]£º»§Íâ·¿¼äÉè¶¨´íÎó£¬·¿¼ä±êÊ¶³¤¶ÈÓ¦Îªµ¥¸ö×Ö·û¡£\n");
                write("[ Citymaker ]£ºÇëÉè¶¨»§Íâ·¿¼äÀàĞÍ(ÀıÈç£ºc,g ÔòµØÍ¼Îª c¡¢g µÄ·¿¼ä½«±»Éè¶¨Îª»§Íâ)£º");
                input_to ( "set_outdoors_room" );       
                return 1;               
                }
        }
        if(!arg) 
        {
        write ("[ Citymaker ]£ºÉè¶¨ËùÓĞ·¿¼äÎª»§Íâ...OK¡£\n");
        }
        outdoors_room=(explode(lower_case(arg),","));
        for (i=0;i<sizeof(outdoors_room);i++)
        {
        outdoors=outdoors_room[i];
        write("[ Citymaker ]£ºÉè¶¨·¿¼ä[ "+outdoors+" ]Îª»§Íâ...OK¡£\n");
        }
        write("[ Citymaker ]£ºÉè¶¨Íê³É£¬Citymaker ½«»áÉú³É³ÇÊĞµµ°¸£¬ÇëÈ·ÈÏ(y/n)£º");
        input_to("confirm_make");   
        return 1;
}
int confirm_make(string arg)
{
        int  _row,_col;
        int count=0;
        if( arg=="" ) 
        {
        write("[ Citymaker ]£ºĞèÒªÈ·ÈÏ£¬ÄúÈ·¶¨Âğ(y/n)£¿");
        input_to("confirm_make");
        return 1;
        }       
        if( arg[0]!='y' && arg[0]!='Y' ) {write ("[ Citymaker ]£º·ÅÆú±¾´Î²Ù×÷¡£\n"); return 1;}
        write("[ Citymaker ]£ºÕıÔÚ½¨Á¢³ÇÊĞ ... ...\n");    
        for(_row=0;_row<sizeof(maps);_row++)
        {
        for(_col=0;_col<sizeof(maps[_row]);_col++)
        {
                if (maps[_row][_col]!=" "
                 && maps[_row][_col]!="|"
                 && maps[_row][_col]!="/"
                 && maps[_row][_col]!="\\"
                 && maps[_row][_col]!="-" )
                {
                        makeroom(_row,_col);
                        count++;
                }
                }
        }
        write("[ Citymaker ]£º²Ù×÷±¨¸æ£¬¹²¼Æ[ " + count +" ]¸ö·¿¼ä£¡\n");   
        return 1;
}

int do_help(string arg)
{
        if(arg=="citymaker" ||arg== "maker")
        {
                write(@HELP_LONG
³ÇÊĞ¾«Áé V1.1 ( 2001.2)            - By Glacier@£ÛÑ©Óò£®ºÚ³±£İ
                                     Email:wizard@game.com.cn
                                     
Õâ¸öÊÇÒ»¸öÎª·½±ãÎ×Ê¦¹¤×÷µÄ³ÇÊĞ¹¤¾ß£¬¿ÉÒÔ¿ìËÙ½¨Á¢ÍêÕûµÄÇøÓò½á¹¹¡£

1.±à¼­µØÍ¼µµ, ·¶ÀıÈçÏÂ£º
-----------------------------------------------------------------
a.¿Í·¿.kefang b.Ïá·¿.xiangfang c.×ßÀÈ.zoulang d.´óÌü.dating
e.³ø·¿.chufang f.»¨Ô°.huayuan g.´óÃÅ.damen h.ÄÚÊÒ.neishi
(×¢Òâ£ºÉÏÁ½ĞĞÓ¦ºÏ²¢ÎªÒ»ĞĞ£¬ÓÉÓÚ¹ı¿í£¬ÎªÁË±ãÓÚÏÔÊ¾£¬ËùÒÔÔÚÕâÀï·ÖÎªÁ½ĞĞ)
  g   b
  |  / \
b-c-b   b
  |  \ /
a-d-a b
  |
h-f-e
------------------------------------------------------------------
µØÍ¼ËµÃ÷£º   ±¾µØÍ¼µµËù¼Ó±ß¿ò(---)£¬Îª½âÊÍµØÍ¼ËùÓÃ£¬Êµ¼ÊµØÍ¼ÖĞÃ»ÓĞ¡£
             µØÍ¼µÚÒ»ĞĞÎªÍ¼Àı£¬²ÉÓÃ<·¿¼ä±êÊ¶.·¿¼äÃû³Æ.·¿¼äÎÄ¼şÃû>µÄ
             ·½Ê½£¬¼´a´ú±í¿Í·¿£¬µØÍ¼ÖĞËùÓĞa¾ù±»´¦Àí³É¿Í·¿¡£ ·¿¼ä±ê
             Ê¶¡¢·¿¼äÃû³ÆºÍ·¿¼äÎÄ¼şÃûÖ®¼äÓÃ£¢.£¢·Ö¸î¡£
             ÓÃ£¢-¡¢\¡¢/¡¢|£¢À´±íÊ¾³£ÓÃµÄµÄ°ËÖĞÍ¨Â·(²»¿¼ÂÇµØĞÎ)¼´£º
             west¡¢east¡¢northwest¡¢southeast¡¢northeast¡¢southwest
             north¡¢south¡£
×¢ÒâÊÂÏî£º   ËùÓĞ·¿¼ä¾ùÓ¦ÔÚµÚÒ»ĞĞÓĞÍ¼ÀıËµÃ÷£¬·ñÔò½«ÎŞ·¨Õı³£Éú³É·¿¼ä¡£
             µØÍ¼ÖĞËùÓĞ×Ö·û¾ùÎª°ë½Ç×Ö·û£¬Ö»ÔÊĞí³öÏÖ¿Õ¸ñ£¢ £¢£¬²»ÔÊĞí
             ³öÏÖÖÆ±í·û \t ¡£Îª±ÜÃâ³ö´íÇëÑÏ¸ñ°´Ôì±¾µØÍ¼µµ½¨Á¢¡£
2. Ö¸Áî¸ñÊ½£ºmake <µØÍ¼µµ>  ( ×îºÃ°Ñ³ÇÊĞÃû×÷ÎªµØÍ¼µµÃû³Æ£¬ ÕâÊÇÒòÎª
             Citymaker ÔÚÉèÖÃoutdoors·¿¼äµÄÊ±ºòÊ¹ÓÃµØÍ¼µµÃû×÷Îª·¿¼ä
             µÄËùÊô³ÇÊĞ¡£)
3. Citymaker ĞèÒªÉè¶¨´æ·Åµµ°¸µÄÂ·¾¶£º <Ä¿Â¼Ãû> (Ä¬ÈÏÎªµ±Ç°ËùÔÚÄ¿Â¼)¡£
4. Citymaker ĞèÒªÉè¶¨»§ÍâµÄ·¿¼ä£º<»§Íâ·¿¼ä±êÊ¶,»§Íâ·¿¼ä±êÊ¶,...
             ËùÉè¶¨µÄ·¿¼ä½«±»Éè¶¨Îª»§Íâ(Ä¬ÈÏÎªÊÒÄÚ)¡£       
5. Èç¹ûÒÔÉÏÉè¶¨ÎŞÎó£¬È·ÈÏºó Citymaker »áÅúÁ¿Éú³É³ÇÊĞµµ°¸¡£(È·ÈÏºó±¾³
             Ğò½«Ö±½Ó¸ÄĞ´ÖØÃûÎÄ¼ş£¬ËùÒÔÇë×¢ÒâÄãËùÕßÉèÖÃµÄ´æ´¢Ä¿Â¼¡£
6. ±¾³ÌĞò»¶Ó­ĞŞ¸Ä£¬µ«Çë±£ÁôÔ­×÷ÕßÃû¡£       

HELP_LONG);
                return 1;
        }
        return 0;
}

string query_autoload() { return "";}

void autoload(string param)
{return ;}

