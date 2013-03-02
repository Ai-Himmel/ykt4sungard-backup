package com.kingstargroup.fdykt.util;

import java.security.SecureRandom;

import javax.crypto.Cipher;
import javax.crypto.SecretKey;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.DESKeySpec;

public class Test {
	

	
	public static void main(String[] args) {   
		  // TODO Auto-generated method stub   
		  try {   
			  
		/*   String test = "170800  ";   
		   //DESPlus des = new DESPlus();//默认密钥   
		   
		   DesUtil des = new DesUtil("87906576");//自定义密钥   
		   byte[] arrB ={-108,-39,-87,-6,60,-45,-71,-64,-51,61,-125,-35,-100,31,-85,-27};
		   String cc = des.byteArr2HexStr(arrB);
		   System.out.println("解密后的字符"+des.decrypt(cc));
		  
		   DesUtil des2 = new DesUtil(", *-.$*.");
		   System.out.println("加密后的字符："+des2.encrypt(test)); */
		   
		 /*  System.out.println("加密前的字符："+test);   
		   System.out.println("加密后的字符："+des.encrypt(test));   
		   System.out.println("解密后的字符："+des.decrypt(des.encrypt(test))); */  
			 System.out.println("02905".getBytes());
			
			 System.out.println(new String("02905".getBytes(),0,5)); 
			 
		  } catch (Exception e) {   
		   // TODO: handle exception   
		   e.printStackTrace();   
		  }    
		 }   


}
