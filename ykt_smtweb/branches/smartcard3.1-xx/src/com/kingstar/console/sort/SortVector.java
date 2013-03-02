package com.kingstar.console.sort;

import java.util.Iterator;
import java.util.Vector;

public class SortVector extends Vector {
	


	private static final long serialVersionUID = 1L;
	
private Compare compare; 
  
//引用比较接口
  public SortVector(Compare comp) {
    compare = comp;
  }
  //设置比较接口
  public void setCompare(Compare compare) {
	this.compare = compare;
}
public void sort() {
    quickSort(0, size() - 1);
  }
  
  //快速的排序
  private void quickSort(int left, int right) {
    if(right > left) {
      Object o1 = elementAt(right);
      int i = left - 1;
      int j = right;
      while(true) {
        while(compare.lessThan(
              elementAt(++i), o1))
          ;
        while(j > 0)
          if(compare.lessThanOrEqual(
             elementAt(--j), o1))
            break; // out of while
        if(i >= j) break;
        swap(i, j);
      }
      swap(i , right);
      quickSort(left, i-1);
      quickSort(i+1, right);
    }
  }
  private void swap(int loc1, int loc2) {
    Object tmp = elementAt(loc1);
    setElementAt(elementAt(loc2), loc1);
    setElementAt(tmp, loc2);
  }
  public void debug(){
	  Iterator i=this.iterator();
	  while(i.hasNext()){
		  System.out.println("object:"+i.next());
		  
	  }
	  
	  
  }

}