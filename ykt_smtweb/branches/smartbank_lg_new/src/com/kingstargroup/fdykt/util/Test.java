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
		   //DESPlus des = new DESPlus();//Ĭ����Կ   
		   
		   DesUtil des = new DesUtil("87906576");//�Զ�����Կ   
		   byte[] arrB ={-108,-39,-87,-6,60,-45,-71,-64,-51,61,-125,-35,-100,31,-85,-27};
		   String cc = des.byteArr2HexStr(arrB);
		   System.out.println("���ܺ���ַ�"+des.decrypt(cc));
		  
		   DesUtil des2 = new DesUtil(", *-.$*.");
		   System.out.println("���ܺ���ַ���"+des2.encrypt(test)); */
		   
		 /*  System.out.println("����ǰ���ַ���"+test);   
		   System.out.println("���ܺ���ַ���"+des.encrypt(test));   
		   System.out.println("���ܺ���ַ���"+des.decrypt(des.encrypt(test))); */  
			 System.out.println("02905".getBytes());
			
			 System.out.println(new String("02905".getBytes(),0,5)); 
			 
		  } catch (Exception e) {   
		   // TODO: handle exception   
		   e.printStackTrace();   
		  }    
		 }   


}
