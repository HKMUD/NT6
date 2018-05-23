#!/bin/sh
rq=`date +%y%m%d` 
mysqldump -ulonely -pnt150867 nitan --quick --default-character-set=latin1 > /home/nitan/backup/mud_db$rq.sql 
