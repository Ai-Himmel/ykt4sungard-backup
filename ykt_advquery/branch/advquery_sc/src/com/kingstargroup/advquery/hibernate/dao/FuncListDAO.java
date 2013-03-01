/**
 * 
 */
package com.kingstargroup.advquery.hibernate.dao;

import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.advquery.util.WebKeys;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: FunListDAO.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-11-9  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class FuncListDAO extends BasicDAO {

	/**
	 * Description:singleton pattern
	 * @return
	 * Modify History:
	 */
	public static FuncListDAO getInstance() {
		if (_instance == null) {
			_instance = new FuncListDAO();
		}
		return _instance;
	}
	
	/**
	 * Description:根据父功能号得到子功能号列表
	 * @param funcCode
	 * @return
	 * Modify History:
	 */
	public List getChildList(String funcCode) {
		Session s = getSession();
		try {
			StringBuffer buff = new StringBuffer();
			if ("ORACLE".equals(WebKeys.DATABASE)){
				buff.append(" from TLeadqueryFunclist func where func.funcCode like :funcCode")
				.append(" order by to_number(substr(func.funcCode, instr('.', func.funcCode) + 1)) asc");
			}else if ("DB2".equals(WebKeys.DATABASE)){
				buff.append(" from TLeadqueryFunclist func where func.funcCode like :funcCode")
				.append(" order by integer(substr(func.funcCode, locate('.', func.funcCode) + 1)) asc");
			}
			Query query = s.createQuery(buff.toString());
			query.setString("funcCode", "'"+funcCode + ".%'");
			return query.list();
		} catch (HibernateException ex) {
			_log.error(ex);
			return null;
		}
	}
	
	/**
	 * Description:取得一级栏目列表
	 * @return
	 * Modify History:
	 */
	public List getParentList() {		
		Session s = getSession();
		try {
			StringBuffer buff = new StringBuffer();
			if ("ORACLE".equals(WebKeys.DATABASE)){
				buff.append(" from TLeadqueryFunclist where instr('.', funcCode) = 0");
			}else if ("DB2".equals(WebKeys.DATABASE)){
				buff.append(" from TLeadqueryFunclist where locate('.', funcCode) = 0");
			}
			Query q = s.createQuery(buff.toString());
			return q.list();
		} catch (HibernateException ex) {
			_log.error(ex);	
			throw ex;
		}
	}
	
	
	
	private static FuncListDAO _instance;
	private Log _log = LogFactory.getLog(FuncListDAO.class.getClass());
}
