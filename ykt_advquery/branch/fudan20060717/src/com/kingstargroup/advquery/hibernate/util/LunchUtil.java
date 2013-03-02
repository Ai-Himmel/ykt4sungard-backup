package com.kingstargroup.advquery.hibernate.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.kingstargroup.advquery.hibernate.dao.LunchDAO;


public class LunchUtil extends BasicUtil {
	/**
	 * 根据人员类型查找
	 * @param params
	 * @return
	 */
	public static List getLunchDetail(Map params) {
		LunchDAO dao = LunchDAO.getInstance();
		List result = new ArrayList();
		try {
			List rows = dao.getLunchDetail(params);
			if(rows!=null && rows.size()>0){
				String feeType = "";
				int meal = 0;
				double amount = 0.00d;
				int subtotalMeal = 0;
				double subtotalAmount = 0.00d;
				int totalMeal = 0;
				double totalAmount = 0.00d;
				
				for(int i=0;i<rows.size();i++){
					//stuemp_no,cut_name,fee_type,fee_name,type_name,meal,amount,period
					Object[] objects = (Object[])rows.get(i);
					meal = objects[5]==null?0:Integer.parseInt(objects[5].toString());
					amount = objects[6]==null?0:Double.parseDouble(objects[6].toString());
					String currentFeeType = objects[2]==null?"":objects[2].toString();
					
					//当当前feeType与上一条记录的feeType不相等并且当前记录不是第一条记录时，为之前的所有记录做小计
					if(i!=0 && !currentFeeType.equals(feeType)){
						Map subtotalMap = new HashMap();
						subtotalMap.put("custName", "小计");
						subtotalMap.put("meal", String.valueOf(subtotalMeal));
						subtotalMap.put("amount", String.valueOf(subtotalAmount));
						result.add(subtotalMap);
						subtotalMeal=0;
						subtotalAmount=0.00d;
					}
					
					HashMap row = new HashMap();
					row.put("stuempNo", objects[0]);
					row.put("custName", objects[1]);
					row.put("feeName", objects[3]);
					row.put("meal", String.valueOf(meal));
					row.put("amount", String.valueOf(amount));
					row.put("period", objects[7]);
					
					result.add(row);
					feeType = currentFeeType;
					
					subtotalMeal += meal;
					subtotalAmount += amount;
					totalMeal += meal;
					totalAmount += amount;
				}
				
				//为最后一类feeType做小计
				Map subtotalMap = new HashMap();
				subtotalMap.put("custName", "小计");
				subtotalMap.put("meal", String.valueOf(subtotalMeal));
				subtotalMap.put("amount", String.valueOf(subtotalAmount));
				result.add(subtotalMap);
				
				//总计
				Map totalMap = new HashMap();
				totalMap.put("feeName", "总计");
				totalMap.put("meal",String.valueOf(totalMeal));
				totalMap.put("amount",String.valueOf(totalAmount));
				result.add(totalMap);
			}
			
			return result;
		} catch(Exception he) {
			he.printStackTrace();
			return null;		
		} finally {
			closeSession();
		}
	}
	
	/**
	 * 查找贫困生
	 * @param params
	 * @return
	 */
	public static List getLunchPerson(Map params) {
		LunchDAO dao = LunchDAO.getInstance();
		List result = new ArrayList();
		try {
			List rows = dao.getLunchPerson(params);
			if(rows!=null && rows.size()>0){
				for(int i=0;i<rows.size();i++){
					//stuemp_no,cut_name,fee_type,fee_name,type_name,totalMeal,totalAmount,totalDay,peroid
					Object[] objects = (Object[])rows.get(i);
					HashMap row = new HashMap();
					row.put("stuempNo", objects[0]);
					row.put("custName", objects[1]);
					row.put("feeName", objects[3]);
					row.put("totalMeal", objects[5]);
					row.put("totalAmount", objects[6]);
					row.put("totalDay", objects[7]);
					row.put("period", objects[8]);
					
					result.add(row);
				}
			}
			return result;
		} catch(Exception he) {
			he.printStackTrace();
			return null;		
		} finally {
			closeSession();
		}
	}
	
	public static List getFeeType(){
		LunchDAO dao = LunchDAO.getInstance();
		List result = new ArrayList();
		try {
			List feeTypeList = dao.getFeeType();
			for (int i=0 ;i<feeTypeList.size();i++){
				Object[] objects = (Object[])feeTypeList.get(i);
				HashMap row = new HashMap();
				row.put("feeType",objects[0]);
				row.put("feeName",objects[1]);
				result.add(row);
			}
			return result;
		} catch(Exception he) {
			he.printStackTrace();
			return null;		
		} finally {
			closeSession();
		}
	}
}
