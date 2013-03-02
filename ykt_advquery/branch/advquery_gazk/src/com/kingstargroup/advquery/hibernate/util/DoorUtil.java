package com.kingstargroup.advquery.hibernate.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import com.kingstargroup.advquery.hibernate.dao.DoorDAO;

public class DoorUtil extends BasicUtil{
	
	public static List getDoorDetailByCust(String custno,String begingdate,String enddate) {
		DoorDAO dao = new DoorDAO();
		List result = new ArrayList();
		try{
		   List  doors =	dao.getDoorDetailByCust(custno,begingdate,enddate);
		   for (int i=0 ;i<doors.size();i++){
			  Object[] obj  = (Object[])doors.get(i);
			  HashMap temp = new HashMap();
			  temp.put("deviceId",obj[0]);
			  temp.put("deviceName",obj[1]);
			  temp.put("txDate",obj[2]);
			  temp.put("txTime",obj[3]);
			  temp.put("custId",obj[4]);
			  
			  result.add(temp);
		   }
		   return result;
		}catch(Exception e){
			e.printStackTrace();
			return null;			
	  }finally {
		closeSession();
	  }
	}
	

}
