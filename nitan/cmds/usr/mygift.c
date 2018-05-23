
#include <ansi.h>
#ifndef MYGIFT_D
#define MYGIFT_D    "/adm/daemons/mygiftd.c"
#endif

int main(object me, string arg)
{
	return MYGIFT_D->mygift(me, arg);
}

