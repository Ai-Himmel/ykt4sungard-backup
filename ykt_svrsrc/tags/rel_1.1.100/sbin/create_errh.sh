TMPFILE=err$$
ERRFILE=$HOME/fdykt/src/include/errdef.h
awk  '$1~/^#define/&&/\/\//&&($2!~/999_0X/)' $ERRFILE |sort >$TMPFILE
awk  'BEGIN{
	cnt=100000;
	printf"#ifndef  __ERRDEF_H_\n";
	printf"#define  __ERRDEF_H_\n\n";
	printf"%s %-30s %d\t%s\n","#define","E_999_0X00",390000,"//黑卡交易";
	printf"%s %-30s %d\t%s\n","#define","E_999_0X01",390001,"//非法卡";
	printf"%s %-30s %d\t%s\n","#define","E_999_0X02",390002,"//中途拔卡";
	printf"%s %-30s %d\t%s\n","#define","E_999_0X03",390003,"//钱包格式错";
	printf"%s %-30s %d\t%s\n","#define","E_999_0X05",390005,"//无法写卡";
	printf"%s %-30s %d\t%s\n","#define","E_999_0X10",390016,"//密码错误";
	printf"%s %-30s %d\t%s\n","#define","E_999_0XA0",390160,"//不在时间段内打卡";
	printf"%s %-30s %d\t%s\n","#define","E_999_0XA1",390161,"//次数超出";
	printf"%s %-30s %d\t%s\n","#define","E_999_0XA2",390162,"//时间间隔不够";
	printf"%s %-30s %d\t%s\n","#define","E_999_0XFA",390250,"//充值交易";
	printf"%s %-30s %d\t%s\n","#define","E_999_0XFE",390254,"//冲正交易";
	printf"\n";
	}
	$1~/^#define/&&/\/\//&&($2!~/999_0X/) {	n=index($0,$4);
						msg=substr($0,n);
						if($2~/_N$/)
							printf("%s %-30s  %d\t%s\n",$1,$2,cnt++,msg);
						else
							printf("%s %-30s  %d\t%s\n",$1,$2,cnt++,msg)
					      }
					      END {
							printf"\n#endif\n";
					          } '  $TMPFILE
rm -f $TMPFILE
