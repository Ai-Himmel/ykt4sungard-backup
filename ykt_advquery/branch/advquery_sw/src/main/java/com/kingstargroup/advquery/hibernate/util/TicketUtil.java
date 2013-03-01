/**
 * 
 */
package com.kingstargroup.advquery.hibernate.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import com.kingstargroup.advquery.hibernate.dao.TicketDAO;

public class TicketUtil extends BasicUtil {

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
	public static List getTicketFillDetail(
			String deptNo,
			String ticketNo,
			int ticketType,
			String stuempno,
			String beginDate,
			String endDate,
			int cutType) {
		TicketDAO dao = TicketDAO.getInstance();
		List result = new ArrayList();
		try {
			List ticket = dao.getTicketFillList(deptNo,ticketNo,ticketType,stuempno,beginDate,endDate,cutType);
			for (int i=0 ;i<ticket.size();i++){
				Object[] objects = (Object[])ticket.get(i);
				HashMap accMap = new HashMap();
				accMap.put("custno",objects[0]);
				accMap.put("custname",objects[1]);
				accMap.put("deptname",objects[2]);
				accMap.put("txdate",objects[3]);
				accMap.put("txtime",objects[4]);
				accMap.put("billno",objects[5]);
				accMap.put("amount",objects[6]);
				accMap.put("cuttype",objects[7]);
				result.add(accMap);
			}
			return result;
		} catch(Exception he) {
			he.printStackTrace();
			return null;		
		} finally {
			closeSession();
		}
	}
	public static List getFillType(){
		TicketDAO dao = TicketDAO.getInstance();
		try {
			return dao.getFillType();
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		}
	}
}
