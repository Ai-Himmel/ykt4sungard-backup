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
 * @author 温晓刚
 */

public class CommonUtil {
//*****************************
public static int PageNumber = 1;//每页显示的记录树
private int[] maxDay = {
      31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  //	定义数据显示格式 yyyy-mm-dd
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
       //argue if 润年
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

//	定义数据显示格式（针对扣率或金额小数点后保留几位） yyyy-mm-dd HH:mm:ss
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
   //argue if 润年

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

//或得_前的string
  public static synchronized String getIdx(String TempStr) {
    int position = TempStr.indexOf("_");
    return TempStr.substring(0, position);
  }
//或得_后的索引值
  public static synchronized int getIndex(String TempStr) {
    int position = TempStr.indexOf("_");
    int tempIndex =
        Integer.parseInt(TempStr.substring(position + 1, TempStr.length()));
    return tempIndex;
  }
//或得_后的string
  public static synchronized String getIndexString(String TempStr) {
    int position = TempStr.indexOf("_");
    String tempIndex =
        TempStr.substring(position + 1, TempStr.length());
    return tempIndex;
  }
//检查是否int类型
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
//检查是否是double型
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

  //	定义数据显示格式（针对扣率或金额小数点后保留几位）
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
  public static String formatIntValue(int source, int num) {//使编码成为00xx的形式
    
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

//中文乱码解决
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
  //去除因为orcal里null字段而在页面上显示null
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
//把null字段变为0
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
//判断数字是否事负数
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
  //人民币转大写
  public static String changeToBig(double value){
    char[] hunit={'拾','佰','仟'};                                               //段内位置表示
    char[] vunit={'万','亿'};                                                     //段名表示
    char[] digit={'零','壹','贰','叁','肆','伍','陆','柒','捌','玖'};  //数字表示
   /* long midVal = (long)(value*100);                                      //转化成整形
    String valStr=String.valueOf(midVal);                                //转化成字符串
    */
    String midVal= formatDoubleValue(value*100,0);
    String valStr=midVal;
    String head=valStr.substring(0,valStr.length()-2);               //取整数部分
    String rail=valStr.substring(valStr.length()-2);                     //取小数部分

    String prefix="";                                                                 //整数部分转化的结果
    String suffix="";                                                                  //小数部分转化的结果
    //处理小数点后面的数
    if(rail.equals("00")){                                                            //如果小数部分为0
      suffix="整";
    } else{
      suffix=digit[rail.charAt(0)-'0']+"角"+digit[rail.charAt(1)-'0']+"分";        //否则把角分转化出来
    }
    //处理小数点前面的数
    char[] chDig=head.toCharArray();                                                         //把整数部分转化成字符数组
    char zero='0';                                                                                          //标志'0'表示出现过0
    byte zeroSerNum = 0;                                                                            //连续出现0的次数
    for(int i=0;i<chDig.length;i++){                                                               //循环处理每个数字
      int idx=(chDig.length-i-1)%4;                                                                //取段内位置
      int vidx=(chDig.length-i-1)/4;                                                                //取段位置
      if(chDig[i]=='0'){                                                                                  //如果当前字符是0
        zeroSerNum++;                                                                                 //连续0次数递增
        if(zero == '0'){                                                                                    //标志
          zero=digit[0];
        } else if(idx==0 && vidx >0 &&zeroSerNum < 4){
          prefix += vunit[vidx-1];
          zero='0';
        }
        continue;
      }
      zeroSerNum = 0;                                                                                    //连续0次数清零
      if(zero != '0') {                                                                                        //如果标志不为0,则加上,例如万,亿什么的
        prefix+=zero;
        zero='0';
      }
      prefix+=digit[chDig[i]-'0'];                                                                        //转化该数字表示
      if(idx > 0) prefix += hunit[idx-1];                  
      if(idx==0 && vidx>0){
        prefix+=vunit[vidx-1];                                                                             //段结束位置应该加上段名如万,亿
      }
    }

    if(prefix.length() > 0) prefix += '圆';                                                             //如果整数部分存在,则有圆的字样
    return prefix+suffix;                                                                                     //返回正确表示
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
