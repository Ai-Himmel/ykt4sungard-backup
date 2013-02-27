package com.kingstargroup.utils;
/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: MD5encoding.java
 * Description: ��Ҫ���ڶ��ַ�������MD5���ܹ��ܡ�
 * Modify History����Change Log��:  
 * �������ͣ��������޸ĵȣ�   ��������     ������    �������ݼ���
 * ����  				2005-9-28    ������    ����MD5encoding����
 * <p>
 *
 * @author      ������
 * @version     1.0
 * @since       1.0
 */
import java.security.MessageDigest; 

public class MD5encoding {
  private final static String[] hexDigits = { 
      "0", "1", "2", "3", "4", "5", "6", "7", 
      "8", "9", "a", "b", "c", "d", "e", "f"}; 

  /** 
   * ת���ֽ�����Ϊ16�����ִ� 
   * @param b �ֽ����� 
   * @return 16�����ִ� 
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
