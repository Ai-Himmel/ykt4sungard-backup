package org.king.utils;

import java.util.Locale;

import com.ibm.icu.text.Collator;

public class CollatorTest {

	public static void swap(String a,String b){
		String temp ="";
		temp = a;
		a=b;
		b=temp;
	}
	/**
	 * Description: TODO
	 *@param args
	 * @return Modify History: 2006-7-5 jackey create
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String [] s = new String [5];
		s[0]="中文";
		s[1]="英文";
		s[2]="法文";
		s[3]="意大利文";
		s[4]="汉语";
		
		Collator coll = Collator.getInstance(Locale.CHINA); 
	    for (int i = s.length - 1; i >= 1; i --) {
	        for (int j=0; j<i; j++) {
	            if (coll.compare(s[j], s[j+1]) == 1) {
	            	String temp = s[j];
	                s[j]=s[j+1];
	                s[j+1]=temp;
	            }
	        }
	    }
	    
	    System.out.println(s[0]+s[1]+s[2]+s[3]+s[4]);

	}

}
