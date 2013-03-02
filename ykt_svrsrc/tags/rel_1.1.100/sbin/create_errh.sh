TMPFILE=err$$
ERRFILE=$HOME/fdykt/src/include/errdef.h
awk  '$1~/^#define/&&/\/\//&&($2!~/999_0X/)' $ERRFILE |sort >$TMPFILE
awk  'BEGIN{
	cnt=100000;
	printf"#ifndef  __ERRDEF_H_\n";
	printf"#define  __ERRDEF_H_\n\n";
	printf"%s %-30s %d\t%s\n","#define","E_999_0X00",390000,"//�ڿ�����";
	printf"%s %-30s %d\t%s\n","#define","E_999_0X01",390001,"//�Ƿ���";
	printf"%s %-30s %d\t%s\n","#define","E_999_0X02",390002,"//��;�ο�";
	printf"%s %-30s %d\t%s\n","#define","E_999_0X03",390003,"//Ǯ����ʽ��";
	printf"%s %-30s %d\t%s\n","#define","E_999_0X05",390005,"//�޷�д��";
	printf"%s %-30s %d\t%s\n","#define","E_999_0X10",390016,"//�������";
	printf"%s %-30s %d\t%s\n","#define","E_999_0XA0",390160,"//����ʱ����ڴ�";
	printf"%s %-30s %d\t%s\n","#define","E_999_0XA1",390161,"//��������";
	printf"%s %-30s %d\t%s\n","#define","E_999_0XA2",390162,"//ʱ��������";
	printf"%s %-30s %d\t%s\n","#define","E_999_0XFA",390250,"//��ֵ����";
	printf"%s %-30s %d\t%s\n","#define","E_999_0XFE",390254,"//��������";
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
