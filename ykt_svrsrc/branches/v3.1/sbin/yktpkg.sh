DATE=`date +%m%d%H%M`
tarfile="yktv3.1.$DATE.tar"
cd $HOME
#tar -T ./ykt/yktpkg.lst -cvf $tarfile 
tar -cvf $tarfile ./.bash_profile ./ykt/yktprofile ./ykt/bin/ykt_bu ./ykt/bin/dataclean ./ykt/bin/dayendbala ./ykt/bin/colposdtl ./ykt/bin/statdiffacc ./ykt/bin/posdtlacc ./ykt/bin/start ./ykt/bin/start.ini ./ykt/bin/ksmbcc ./ykt/bin/ksmbcc.ini ./ykt/bin/libbupub.so ./ykt/bin/libksshmtd.so ./ykt/bin/drtp ./ykt/bin/drtpdemo ./ykt/bin/drtp.ini ./ykt/bin/cpack.dat ./ykt/bin/sall ./ykt/bin/bu0/cpack.dat ./ykt/bin/bu0/ksbu.ini ./ykt/sbin/kall ./ykt/sbin/add_errcode ./ykt/sbin/dayendbala.sh ./ykt/sbin/dataclean.sh ./ykt/sql_update 
gzip $tarfile
