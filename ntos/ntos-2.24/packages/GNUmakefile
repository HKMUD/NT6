
SRC=uids.c arith_operator.c db.c compress.c database.c math.c develop.c ansi.c mappingbase.c external.c contrib.c moon.c lonely.c sockets.c async.c chinese.c 
OBJ=uids.$(O) arith_operator.$(O) db.$(O) compress.$(O) database.$(O) math.$(O) develop.$(O) ansi.$(O) mappingbase.$(O) external.$(O) contrib.$(O) moon.$(O) lonely.$(O) sockets.$(O) async.$(O) chinese.$(O) 

OBJ=$(addprefix $(OBJDIR)/,$(subst .c,.o,$(SRC)))

$(OBJDIR)/%.o: %.c
	$(CC) -I$(OBJDIR) -I.. $(CFLAGS) -o $@ -c $<

all: $(OBJ)
	ar rcu packages.$(A) $(OBJ)
	$(RANLIB) packages.$(A)

$(OBJDIR)/db.o: db.c
	$(CC) -I$(OBJDIR) -I.. -I/usr/include/mysql $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.$(O)
	rm -f packages.$(A)
