package com.kingstargroup.conference.common;

import java.text.Collator;
import java.util.Comparator;
import java.util.HashMap;

/**
 * ʵ�������б������
 * @author Administrator
 *
 */

public class SortListColl implements Comparator{
	
	 public int compare(Object o1, Object o2){
		 if(null == o1 || null == o2)
			 throw new RuntimeException("û��Ҫ����Ķ���!");
		 if((o1 instanceof HashMap) && (o2 instanceof HashMap)){
			 HashMap a = (HashMap)o1;
			 HashMap b = (HashMap)o2;
			 String a1 = a.get("pym").toString();
			 String b1 = b.get("pym").toString();
			 if(null == a1 && null == b1){
				 return 0;
			 }else if(null == a1){
				 return -1;
			 }else if(null == b1){
				 return 1;
			 }else{
				 return Collator.getInstance(java.util.Locale.CHINA).compare(a1,b1);
			 }
			 //Comparator cmp = Collator.getInstance(java.util.Locale.CHINA);
			 
		 }
		 System.out.println(RuntimeException.class.toString());
		 throw new RuntimeException("����ʧ��!");
		 //Collections.sort(list,new SortListColl());
	 }
	 public boolean equals(Object obj){
		 return (obj instanceof SortListColl);
	 }

}
