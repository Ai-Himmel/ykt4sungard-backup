/**
 * 
 */
package com.kingstargroup.advquery.hibernate.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.hibernate.HibernateException;

import com.kingstargroup.advquery.common.DateUtil;
import com.kingstargroup.advquery.hibernate.dao.ShopDAO;
import com.kingstargroup.advquery.shop.TCifShop;
/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: ShopUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-11-13  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class ShopUtil extends BasicUtil {

	public synchronized static List createShopJSList(String rootId) {
		
		List shopJSList = new ArrayList();
		try {
			nodeId = 1;
			shopJSList = _createShopJSList(rootId, "");
		} catch (HibernateException he) {
			
		} finally {
			closeSession();
		}
		return shopJSList;
	}
	
	public static List getShopTrade(String stuempNo,String name,String begindate,String endDate,String posid,String postids){
		ShopDAO dao = ShopDAO.getInstance();
		List tradeList = new ArrayList();
		try{
			if(!"".equals(begindate)){
			 begindate = DateUtil.reFormatTime(begindate);
			}
			if(!"".equals(endDate)){
			 endDate = DateUtil.reFormatTime(endDate);
			}
			List list = dao.getShopTrade(stuempNo,name,begindate,endDate,posid,postids);
			if(list != null){
				for(int i=0;i<list.size();i++){
					Map temp = new HashMap();
				    Object[] obj = (Object[]) list.get(i);
				    temp.put("optDate",obj[0]);
				    temp.put("optTime",obj[1]);
				    temp.put("devName",obj[2]);
				    temp.put("name",obj[3]);
				    temp.put("stuNo",obj[4]);
				    temp.put("tradCount",obj[5]);
				    temp.put("opfee",obj[6]);
				    tradeList.add(temp);
				}
			}
			return tradeList;
        } catch (HibernateException he) {
        	 throw he;
		} finally {
			closeSession();
		}
	//	return tradeList;
	}
	
	private static List _createShopJSList(String parentId, String nodeParentId) {
		ShopDAO dao = ShopDAO.getInstance();
		List shopJSList = new ArrayList();
		try {
			List childList = dao.getChildList(parentId);
			for (int i = 0; i < childList.size(); i++) {
				TCifShop shop = (TCifShop) childList.get(i);
				StringBuffer nodeBuff = new StringBuffer();
				nodeBuff.append(nodeId)//nodeId
						.append("|")
						.append(nodeParentId)
						.append("|");//parentId
				if (i == childList.size() - 1){//ls
					nodeBuff.append("1|");
				} else {
					nodeBuff.append("0|");
				}
				nodeBuff.append("|");//path
				nodeBuff.append(shop.getShopName())
						.append("|");//name
				nodeBuff.append("|");//image
				nodeBuff.append(shop.getShopId());//href
				shopJSList.add(nodeBuff.toString());//add to list	
				int parentNode = nodeId;
				nodeId ++;				
				/*
				 * process child list
				 */
				shopJSList.addAll(_createShopJSList(shop.getShopId().toString(), String.valueOf(parentNode)));
			}
		} catch (HibernateException he) {
			throw he;
		}
		return shopJSList;
	}
	
	private static int nodeId = 1;
}
