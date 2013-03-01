/**
 * 
 */
package com.kingstargroup.advquery.hibernate.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import com.kingstargroup.advquery.common.DateUtilExtend;
import com.kingstargroup.advquery.hibernate.dao.ReportOperDAO;
import com.kingstargroup.advquery.util.WebKeys;

public class ReportOperUtil extends BasicUtil {

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AccountUtil个人消费明细<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-5-15  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public static List posSavingCompareStat(String beginDate,String endDate,String statType){
		ReportOperDAO dao = ReportOperDAO.getInstance();
		List result = new ArrayList();
		try {
			List pos = dao.posSavingCompareStat(beginDate,endDate,statType);
			if ("bydate".equals(statType)){
				for (int i=0 ;i<pos.size();i++){
					Object[] objects = (Object[])pos.get(i);
					HashMap accMap = new HashMap();
					accMap.put("balance_date",objects[0]);
					accMap.put("hdamt",objects[1]);
					accMap.put("flamt",objects[2]);
					accMap.put("zjamt",objects[3]);
					accMap.put("hdnum",objects[4]);
					accMap.put("flnum",objects[5]);
					accMap.put("zjnum",objects[6]);
					accMap.put("week",DateUtilExtend.getWeekByDate(objects[0].toString()));
					accMap.put("sysdate",new Integer((int)DateUtilExtend.diffDate(WebKeys.sysBeginDate,objects[0].toString())+1));
					result.add(accMap);
				}
			}else {
				for (int i=0 ;i<pos.size();i++){
					Object[] objects = (Object[])pos.get(i);
					HashMap accMap = new HashMap();
					accMap.put("balance_date",objects[0]);
					accMap.put("hdamt",objects[1]);
					accMap.put("flamt",objects[2]);
					accMap.put("zjamt",objects[3]);
					accMap.put("hdnum",objects[4]);
					accMap.put("flnum",objects[5]);
					accMap.put("zjnum",objects[6]);
					result.add(accMap);
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
	
}
