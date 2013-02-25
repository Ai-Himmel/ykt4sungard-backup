>pubdb.h
echo "#ifndef __DB_PUB_INCLUDE__" >>pubdb.h
echo "#define __DB_PUB_INCLUDE__" >>pubdb.h
echo "#include \"esqlc.h\" ">>pubdb.h
#echo "#include <sql.h>" >>pubdb.h
#echo "#include <sqlca.h>" >>pubdb.h

files=`ls *stru.h`
for i in $files
do
	echo "#include \"$i\"" >>pubdb.h
done
#echo "#include \"db_addition.h\"" >>pubdb.h
#awk '   BEGIN{print "extern int g_dbchkerr;"}
 #       /^int/&&!/;/  {print $0";"}
 #       /^char/&&!/;/ {print $0";"}
#        /^void/&&!/;/ {print $0";"}
#' pubdb.sqc >>pubdb.h
echo "#endif" >>pubdb.h
#cp esqlc.h $HOME/ykt/src/include
mv pubdb.h $HOME/ykt/src/include
