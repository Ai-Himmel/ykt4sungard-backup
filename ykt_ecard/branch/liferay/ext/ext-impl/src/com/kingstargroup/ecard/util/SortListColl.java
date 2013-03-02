package com.kingstargroup.ecard.util;

import java.text.Collator;
import java.util.Comparator;

/**
 * 实现下拉列表框排序
 * @author Administrator
 *
 */

public class SortListColl implements Comparator{
	
	 public int compare(Object o1, Object o2){
		 if(null == o1 || null == o2)
			 throw new RuntimeException("compare error!");
		 if((o1 instanceof Object[]) && (o2 instanceof Object[])){
			 Object[] a = (Object[])o1;
			 Object[] b = (Object[])o2;
			 String a1 = (String)a[1];
			 String b1 = (String)b[1];
			 if(null == a1 && null == b1)
				 return 0;
			 if(null == a1)
				 return -1;
			 if(null == b1)
				 return 1;
			 return Collator.getInstance().compare(a1,b1);
		 }
		 throw new RuntimeException("compare error!");
	 }
	 public boolean equals(Object obj){
		 return (obj instanceof SortListColl);
	 }

}
