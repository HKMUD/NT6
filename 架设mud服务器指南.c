查看linux版本
lsb_release -a
cat /etc/issue
cat /etc/redhat-release



显示中文
系统中文显示
vi /etc/profile 结尾加上
export LANG=zh_CN

安装mysql
yum install mysql
yum install mysql-devel
yum install mysql-server

setup开启系统mysql服务，关闭防火墙


定时备份mud
vi /etc/crontab加入
10 6 * * * root /home/nitan/bin/mysql.sh >>/dev/null 2>&1
15 6 * * * root /home/nitan/bin/backup.sh >>/dev/null 2>&1


创建mud数据库 
mysql
create database nitan;
grant all on nitan.* to lonely@localhost identified by 'nt150867';
exit
mysql -ulonely -pnt150867 nitan < /home/nitan/mud_db.sql

运行mud
./run.sh

********************************
以下安装为可选部分
********************************

安装 mrtg
配置snmpd

安装编译环境用来编译fluffos
安装gcc-4.8.1.tar.bz2
yum install gcc gcc-c++ kernel-devel
安装flex，bison：执行yum install flex; yum install bison; 如果不安装编译会遇到问题
yun install qt
安装libevent-2.0.21-stable.tar.gz
./configure --prefix=/usr && make && make install
ldconfig
ldd ./driver

cp /root/gcc-build-4.8.1/x86_64-unknown-linux-gnu/libstdc++-v3/src/.libs/libstdc++.so.6 /usr/lib64/
