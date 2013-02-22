package org.king.utils;

import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;

/**
 * Copyright: Copyright (c) 2004
 * Company: kingstar
 * @author ������
 */

public class CommonUtil {
//*****************************
public static int PageNumber = 1;//ÿҳ��ʾ�ļ�¼��
private int[] maxDay = {
      31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  //	����������ʾ��ʽ yyyy-mm-dd
   public static boolean isDateFormat(String Date) {
     boolean flag = false;
     int month = 0;
     int day = 0;
     int year = 0;
     double Checktempyear = 0;
     double CheckHuntempyear = 0;
     CommonUtil util = new CommonUtil();
     if (Date.matches("\\d+{1,4}-\\d{1,2}-\\d{1,2}")) {
       flag = true;
     }
     if (flag) {
       //get now year
       year = Integer.parseInt(Date.substring(0, getFirst_ByDate(Date)));
       Checktempyear = year % 4;
       CheckHuntempyear = year % 400;
       //argue if ����
       if (year%100 == 0) {
         if(CheckHuntempyear==0)
           util.maxDay[1] = 29;
          else
            util.maxDay[1] = 28;
       }
       else {
         if(Checktempyear==0)
           util.maxDay[1] = 29;
         else {
             util.maxDay[1] = 28;
         }

       }

       //get now monthth
       month = Integer.parseInt(Date.substring(getFirst_ByDate(Date) + 1,
                                               getLast_ByDate(Date)));
       if (month < 1 || month > 12) {
         flag = false;
       }
       else {
         //get now day
         day = Integer.parseInt(Date.substring(getLast_ByDate(Date) + 1,
                                               Date.length()));
         //check day about month
         if (day < 1 || day > util.maxDay[month - 1]) {
           flag = false;
         }
       }

     }
     return flag;
   }

//	����������ʾ��ʽ����Կ��ʻ���С���������λ�� yyyy-mm-dd HH:mm:ss
public static boolean isDateHiResFormat(String Date) {
 boolean flag = false;
 int month = 0;
 int day = 0;
 int year = 0;
 double Checktempyear = 0;
 double CheckHuntempyear = 0;
 CommonUtil util = new CommonUtil();

 if (Date.matches("\\d+{1,4}-\\d{1,2}-\\d{1,2} \\d{1,2}:\\d{1,2}:\\d{1,2}")) {
   flag = true;
 }
 if (flag) {
   //get now year
   year = Integer.parseInt(Date.substring(0, getFirst_ByDate(Date)));
   Checktempyear = year % 4;
   CheckHuntempyear = year % 400;
   //argue if ����

   if (year%100 == 0) {
         if(CheckHuntempyear==0)
           util.maxDay[1] = 29;
          else
            util.maxDay[1] = 28;
       }
       else {
         if(Checktempyear==0)
           util.maxDay[1] = 29;
         else {
             util.maxDay[1] = 28;
         }

       }


   //get now monthth
   month = Integer.parseInt(Date.substring(getFirst_ByDate(Date) + 1,
                                           getLast_ByDate(Date)));
   if (month < 1 || month > 12) {
     flag = false;
   }
   else {
     //get now day
     day = Integer.parseInt(Date.substring(getLast_ByDate(Date) + 1,
                                           getSpaceByDate(Date)));
     //check day about month
     if (day < 1 || day > util.maxDay[month - 1]) {
       flag = false;
     }
   }

 }

 return flag;
}

private static int getFirst_ByDate(String Date) {
 int pos = 0;
 pos = Date.indexOf("-");
 return pos;
}

private static int getLast_ByDate(String Date) {
 int pos = 0;
 pos = Date.lastIndexOf("-");
 return pos;
}

private static int getSpaceByDate(String Date) {
 int pos = 0;
 pos = Date.indexOf(" ");
 return pos;
}
//*********************************************

//���_ǰ��string
  public static synchronized String getIdx(String TempStr) {
    int position = TempStr.indexOf("_");
    return TempStr.substring(0, position);
  }
//���_�������ֵ
  public static synchronized int getIndex(String TempStr) {
    int position = TempStr.indexOf("_");
    int tempIndex =
        Integer.parseInt(TempStr.substring(position + 1, TempStr.length()));
    return tempIndex;
  }
//���_���string
  public static synchronized String getIndexString(String TempStr) {
    int position = TempStr.indexOf("_");
    String tempIndex =
        TempStr.substring(position + 1, TempStr.length());
    return tempIndex;
  }
//����Ƿ�int����
  public static synchronized boolean checkIsInt(String str) {
    boolean flag = false;
    try {
      Integer.parseInt(str);
      flag = true;
    }
    catch (NumberFormatException ne) {
      flag = false;
    }
    return flag;
  }
//����Ƿ���double��
  public static synchronized boolean checkIsDouble(String str) {
    boolean flag = false;
    try {
      Double.parseDouble(str);
      flag = true;
    }
    catch (NumberFormatException ne) {
      flag = false;
    }
    return flag;
  }

  //	����������ʾ��ʽ����Կ��ʻ���С���������λ��
  public static String formatDoubleValue(double source, int num) {
    
  	String myformat = "";
    if (num == 0) {
      myformat = "###";
    }
    else {
      myformat = "###.";
      for (int i = 0; i < num; i++) {
        myformat = myformat + "0";
      }
    }
    DecimalFormat formatter = new DecimalFormat(myformat);

    String returnvalue = "";
    try {
      if (source < 1 && source >= 0) {
        returnvalue = "0" + formatter.format(source);
      }
      else {
        returnvalue = formatter.format(source);
      }
    }
    catch (Exception e) {
      returnvalue = "";
    }
    return returnvalue;
  } 
  public static String formatIntValue(int source, int num) {//ʹ�����Ϊ00xx����ʽ
    
  	String myformat = "";
    if (num == 4) {
      if(source>=0&&source<=9){
      	myformat = "000"+ String.valueOf(source);
      }
      if(source>=10&&source<=99){
      	myformat = "00"+ String.valueOf(source);
      }
      if(source>=100&&source<=999){
      	myformat = "0"+ String.valueOf(source);
      }
      if(source>=1000&&source<=9999){
      	myformat = String.valueOf(source);
      }
      if(source>=10000){
      	myformat = "0000";
      }
    }
    if (num == 3) {
        if(source>=0&&source<=9){
        	myformat = "00"+ String.valueOf(source);
        }
        if(source>=10&&source<=99){
        	myformat = "0"+ String.valueOf(source);
        }
        if(source>=100&&source<=999){
        	myformat = String.valueOf(source);
        }
        if(source>=1000){
        	myformat = "000";
        }
      }
    if (num == 5) {
        if(source>=0&&source<=9){
        	myformat = "0000"+ String.valueOf(source);
        }
        if(source>=10&&source<=99){
        	myformat = "000"+ String.valueOf(source);
        }
        if(source>=100&&source<=999){
        	myformat = "00"+ String.valueOf(source);
        }
        if(source>=1000&&source<=9999){
        	myformat = "0"+ String.valueOf(source);
        }
        if(source>=10000&&source<=99999){
        	myformat = String.valueOf(source);
        }
        if(source>=100000){
        	myformat = "00000";
        }
      }
    return myformat;
  }
  
  public static int rebackFormat(String newCode){
  	int count = newCode.length();
  	int oldCode = 0;

  	for(int i=0;i<count;i++){
  		if(newCode.charAt(i)!='0'){
  			oldCode = Integer.parseInt(newCode.substring(i));
  			break;
  		}
  	}
  	return oldCode;
  }

//����������
  public static String getStr(String str){
    try{
      String temp_p=str;
      byte[] temp_t=temp_p.getBytes("ISO8859-1");
//      String temp=new String(temp_t,"gb2312");
      String temp=new String(temp_t);
      return temp;
    }catch(Exception e){
      System.out.println("error=commonutil");
      return null;
    }
  }
  //ȥ����Ϊorcal��null�ֶζ���ҳ������ʾnull
  public static String killnull(String str){
    try{
      String strTemp="";
      if(str==null||str.equals("null")){
        return strTemp;
      }else{
        return str;
      }

    }catch(Exception e){
      System.out.println("error=commonutil");
      return str;
    }
  }
//��null�ֶα�Ϊ0
public static String null20(String str){
    try{
      String strTemp="0";
      if(str==null||str.equals("")||str.equals("null")){
        return strTemp;
      }else{
        return str;
      }

    }catch(Exception e){
      System.out.println("error=commonutil");
      return str;
    }
  }
//�ж������Ƿ��¸���
  public static boolean checkIsNotNegative(String num) {
    boolean flag = true;
    if (checkIsDouble(num)) {
      if(Double.parseDouble(num)<0){
        flag=false;
      }
    }
    return flag;
  }
  public static ArrayList GoToPage(int valPage,List source){

    int start = (valPage-1)*PageNumber;
    if(start<0)
      start =0;
    int end = start+PageNumber;
    int total = source.size();
    if(end>total)
        end = total;
    ArrayList ret = new ArrayList();
    for(int i=start;i<end;i++){
        ret.add(source.get(i));
    }
    return ret;
}
  //�����ת��д
  public static String changeToBig(double value){
    char[] hunit={'ʰ','��','Ǫ'};                                               //����λ�ñ�ʾ
    char[] vunit={'��','��'};                                                     //������ʾ
    char[] digit={'��','Ҽ','��','��','��','��','½','��','��','��'};  //���ֱ�ʾ
   /* long midVal = (long)(value*100);                                      //ת��������
    String valStr=String.valueOf(midVal);                                //ת�����ַ���
    */
    String midVal= formatDoubleValue(value*100,0);
    String valStr=midVal;
    String head=valStr.substring(0,valStr.length()-2);               //ȡ��������
    String rail=valStr.substring(valStr.length()-2);                     //ȡС������

    String prefix="";                                                                 //��������ת���Ľ��
    String suffix="";                                                                  //С������ת���Ľ��
    //����С����������
    if(rail.equals("00")){                                                            //���С������Ϊ0
      suffix="��";
    } else{
      suffix=digit[rail.charAt(0)-'0']+"��"+digit[rail.charAt(1)-'0']+"��";        //����ѽǷ�ת������
    }
    //����С����ǰ�����
    char[] chDig=head.toCharArray();                                                         //����������ת�����ַ�����
    char zero='0';                                                                                          //��־'0'��ʾ���ֹ�0
    byte zeroSerNum = 0;                                                                            //��������0�Ĵ���
    for(int i=0;i<chDig.length;i++){                                                               //ѭ������ÿ������
      int idx=(chDig.length-i-1)%4;                                                                //ȡ����λ��
      int vidx=(chDig.length-i-1)/4;                                                                //ȡ��λ��
      if(chDig[i]=='0'){                                                                                  //�����ǰ�ַ���0
        zeroSerNum++;                                                                                 //����0��������
        if(zero == '0'){                                                                                    //��־
          zero=digit[0];
        } else if(idx==0 && vidx >0 &&zeroSerNum < 4){
          prefix += vunit[vidx-1];
          zero='0';
        }
        continue;
      }
      zeroSerNum = 0;                                                                                    //����0��������
      if(zero != '0') {                                                                                        //�����־��Ϊ0,�����,������,��ʲô��
        prefix+=zero;
        zero='0';
      }
      prefix+=digit[chDig[i]-'0'];                                                                        //ת�������ֱ�ʾ
      if(idx > 0) prefix += hunit[idx-1];                  
      if(idx==0 && vidx>0){
        prefix+=vunit[vidx-1];                                                                             //�ν���λ��Ӧ�ü��϶�������,��
      }
    }

    if(prefix.length() > 0) prefix += 'Բ';                                                             //����������ִ���,����Բ������
    return prefix+suffix;                                                                                     //������ȷ��ʾ
  }
  public static Map getWrappedParameter(HttpServletRequest request){
		Map wrappedMap = new HashMap();
		Enumeration names = request.getParameterNames();
		while (names.hasMoreElements()){
			String name = names.nextElement().toString();
			String[] values = request.getParameterValues(name);
			wrappedMap.put(name,wrapValues(values));
		}
		return wrappedMap;
	}
	
	public static Object wrapValues(String[] values){
		if(values== null) return null;
		if (values.length==1) return values[0];
		else {
			
			return Arrays.asList(values);
		}
	}

}
