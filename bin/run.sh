

#!/bin/sh

workdir=/home/nitan

########################################
logdir=$workdir/nitan/log
logs="debug.log catch runtime log"
logfile=$logdir/driver.log

bindir=$workdir/bin
driver=$bindir/driver
config=$bindir/config.nt6

ulimit -n 16384
ulimit -c unlimited
echo 655360 > /proc/sys/vm/max_map_count

touch $workdir/mud.out
nice $bindir/addr_server 3990 >>$workdir/mud.out &

while true; do

cd $bindir

for f in $logs
do mv -f $logdir/$f $logdir/$f.`date +%m%d` > $workdir/mud.out 2>&1
done

date > $logfile
$driver $config >> $logfile 2>&1

sleep 10

done

