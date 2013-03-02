package com.kingstargroup.ecard.util;

import java.text.Collator;
import java.util.Comparator;
import java.util.HashMap;

/**
 * 对查询结果进行指定列排序
 * @author Administrator
 *
 */
public class SortListByResult  implements Comparator{
	
	private String keyName;
	
	public SortListByResult(String keyName){
		this.keyName = keyName;
	}
	 public int compare(Object o1, Object o2){
		 if(null == o1 || null == o2)
			 throw new RuntimeException("compare error!");
		 if((o1 instanceof HashMap) && (o2 instanceof HashMap)){
			 HashMap srcMap = (HashMap)o1;
			 HashMap destMap = (HashMap)o2;
			 String srcValue = (String)srcMap.get(keyName);
			 String destValue = (String)destMap.get(keyName);
			 if(null == srcValue && null == destValue)
				 return 0;
			 if(null == srcValue)
				 return -1;
			 if(null == destValue)
				 return 1;
			 return Collator.getInstance().compare(srcValue,destValue);
		 }
		 throw new RuntimeException("compare error!");
	 }
	 public boolean equals(Object obj){
		 return (obj instanceof SortListByResult);
	 }

}
