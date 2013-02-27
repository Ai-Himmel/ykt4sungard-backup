package com.kingstargroup.utils;
/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: MD5encoding.java
 * Description: 主要用于对字符串进行MD5加密功能。
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期     操作者    操作内容简述
 * 创建  				2005-9-28    何林青    创建MD5encoding方法
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */
import java.security.MessageDigest; 

public class MD5encoding {
  private final static String[] hexDigits = { 
      "0", "1", "2", "3", "4", "5", "6", "7", 
      "8", "9", "a", "b", "c", "d", "e", "f"}; 

  /** 
   * 转换字节数组为16进制字串 
   * @param b 字节数组 
   * @return 16进制字串 
   */ 

  public static String byteArrayToHexString(byte[] b) { 
    StringBuffer resultSb = new StringBuffer(); 
    for (int i = 0; i < b.length; i++) {
    	resultSb.append(byteToHexString(b[i]));
      //resultSb.append(Integer.toHexString((int)b[i]).substring()); 
    } 
    return resultSb.toString(); 
  } 

  private static String byteToHexString(byte b) { 
    int n = b; 
    if (n < 0) 
      n = 256 + n; 
    int d1 = n / 16; 
    int d2 = n % 16; 
    return hexDigits[d1] + hexDigits[d2]; 
  } 

  public static String MD5Encode(String origin) { 
    String resultString = null; 

    try { 
      resultString=new String(origin); 
      MessageDigest md = MessageDigest.getInstance("MD5"); 
      resultString=byteArrayToHexString(md.digest(resultString.getBytes())); 
    } 
    catch (Exception ex) { 

    } 
    return resultString; 
  } 

}
