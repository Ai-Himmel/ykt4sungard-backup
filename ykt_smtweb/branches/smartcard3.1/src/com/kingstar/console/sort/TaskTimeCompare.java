package com.kingstar.console.sort;

 
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

import com.kingstar.basetask.bean.Task;

public class TaskTimeCompare extends Task {

	
	private static final long serialVersionUID = 8960083492449008419L;
	public boolean lessThan(Object lhs, Object rhs) {
			
		Date d1=null;
		Date d2=null;
		boolean r=false;
		try {
			SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
			if(((Task)lhs).getRuntimedata().equals(null)||((Task)rhs).getRuntimedata().equals(null)
					||((Task)lhs).getRuntimedata().equals("")||((Task)rhs).getRuntimedata().equals("")){	
				return false;
	
			}else{
			 d1=format.parse(((Task)lhs).getRuntimedata());
			 d2=format.parse(((Task)rhs).getRuntimedata());
			 r=d1.compareTo(d2) < 0;
			}
		} catch (ParseException e) {
			e.printStackTrace();
		}
		return r;
		
	//	return ((Task) lhs).getPriority().compareTo(((Task) rhs).getPriority()) < 0;
	}

	public boolean lessThanOrEqual(Object lhs, Object rhs) {


		Date d1=null;
		Date d2=null;
		boolean r=false;
		try {
			SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
			if(((Task)lhs).getRuntimedata().equals(null)||((Task)rhs).getRuntimedata().equals(null)
					||((Task)lhs).getRuntimedata().equals("")||((Task)rhs).getRuntimedata().equals("")){	
				return false;
	
			}else{
			 d1=format.parse(((Task)lhs).getRuntimedata());
			 d2=format.parse(((Task)rhs).getRuntimedata());
			 r=d1.compareTo(d2) < 0;
			}
		} catch (ParseException e) {
			e.printStackTrace();
		}
		return r;
	//	return ((Task) lhs).getPriority().compareTo(((Task) rhs).getPriority()) <= 0;
	}
	public static void main(String[] args) throws ParseException {
//		SimpleDateFormat  format = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
//		String s="2008-05-09 14:00:10";
//		String s2="2008-05-09 13:00:10";
//		String s3="2008-05-09 15:00:10";
//		Date date =  format.parse(s); 
//		Date date2 =  format.parse(s2); 
//		Date date3 =  format.parse(s3); 
//
//		TaskTimeCompare t=new TaskTimeCompare();
//		//t.lessThan(s,s2);
	}


}
