package com.kingstargroup.advquery.hibernate.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.kingstargroup.advquery.customer.TCifCustomer;
import com.kingstargroup.advquery.hibernate.dao.CustomerDAO;

public class CustomerUtil extends BasicUtil {
	
	public static TCifCustomer   getCustomerByStuempno(String stuempno){
		try {
		CustomerDAO dao = new CustomerDAO();
	    return 	dao.getCustomerByStuempno(stuempno);
		
		}catch(Exception he) {
			he.printStackTrace();
			return null;		
		} finally {
				 closeSession();
		 }
	  }
	
	public List getCustomerBymanId(String manId){
		try{
			CustomerDAO dao = new CustomerDAO();
			List list  = dao.getCustomerBymanId(manId);
			List result = new ArrayList();
			for(int i=0;i<list.size();i++){
				Map temp = new HashMap();
                Object[] obj	=(Object[])list.get(i);
				temp.put("cutId", obj[0]);
				temp.put("showId", obj[1]);
				temp.put("name", obj[2]);
				result.add(temp);
			}
			return result;
		}catch(Exception e){
			e.printStackTrace();
			return null;
		}finally{
			closeSession();
		}
	}
	
	public static  String getStateByCustId(String custId){
		try{
			CustomerDAO dao = new CustomerDAO();
			String  state  = dao.getStateByCustId(custId);
			return state;
		}catch(Exception e){
			e.printStackTrace();
			return null;
		}finally{
			closeSession();
		}
	}
}


