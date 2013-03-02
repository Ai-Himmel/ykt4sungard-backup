/**
 * 
 */
package com.kingstargroup.advquery.hibernate.util;

import java.util.ArrayList;
import java.util.List;

import org.hibernate.HibernateException;

import com.kingstargroup.advquery.hibernate.dao.FuncListDAO;
import com.kingstargroup.advquery.hibernate.user.TLeadqueryFunclist;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: FuncListUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-11-13  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class FuncListUtil extends BasicUtil {
	public static String getFuncName(String funcCode) {
		FuncListDAO dao = FuncListDAO.getInstance();
		String funcName = "";
		try {
			funcName = ((TLeadqueryFunclist)dao.findByPrimaryKey(TLeadqueryFunclist.class, funcCode)).getFuncName();
		} catch(HibernateException he) {
			
		} finally {
			closeSession();
		}
		return funcName;
	}
	
	public static List createJSTree() {
		FuncListDAO dao = FuncListDAO.getInstance();
		List moduleJSList = new ArrayList();
		try {			
			int nodeId = 2;
			List parentList = dao.getParentList();
			for (int i = 0; i < parentList.size(); i++) {
				TLeadqueryFunclist func = (TLeadqueryFunclist) parentList.get(i);
				StringBuffer nodeBuff = new StringBuffer();
				nodeBuff.append(nodeId)//nodeId
						.append("|1|");//parentId
				if (i == parentList.size() - 1){//ls
					nodeBuff.append("1|");
				} else {
					nodeBuff.append("0|");
				}
				nodeBuff.append("|");//path
				nodeBuff.append(func.getFuncName())
						.append("|");//name
				nodeBuff.append("|");//image
				nodeBuff.append(func.getFuncCode());//href
				moduleJSList.add(nodeBuff.toString());//add to list
				int parentNode = nodeId;
				nodeId++;				
				/*
				 * process child list
				 */
				List childList = dao.getChildList(func.getFuncCode());
				for (int j = 0; j < childList.size(); j++) {
					TLeadqueryFunclist child = (TLeadqueryFunclist) childList.get(j);
					StringBuffer childBuff = new StringBuffer();
					childBuff.append(nodeId)//nodeId
							.append("|")
							.append(parentNode)
							.append("|");//parentId
					if (j == childList.size() - 1){//ls
						childBuff.append("1|");
					} else {
						childBuff.append("0|");
					}
					childBuff.append("|");//path
					childBuff.append(child.getFuncName())
							.append("|");//name
					childBuff.append("|");//image
					childBuff.append(child.getFuncCode());//href
					moduleJSList.add(childBuff.toString());//add to list
					nodeId++;
				}
			}
		} catch (HibernateException he) {
			
		} finally {
			closeSession();
		}
		return moduleJSList;
	}
}
