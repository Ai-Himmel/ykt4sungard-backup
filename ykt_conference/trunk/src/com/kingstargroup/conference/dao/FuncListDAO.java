/**
 * 
 */
package com.kingstargroup.conference.dao;

import java.util.List;

import org.apache.log4j.Logger;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

/**
 * @author hjw
 *
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
			buff.append(" from TFuncList as func where func.funcCode like :funcCode")
				.append(" order by integer(substr(func.funcCode, locate('.', func.funcCode) + 1)) asc");
			Query query = s.createQuery(buff.toString());
			query.setString("funcCode", funcCode + ".%");
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
			buff.append(" from TFuncList where locate('.', funcCode) = 0");
			Query q = s.createQuery(buff.toString());
			return q.list();
		} catch (HibernateException ex) {
			_log.error(ex);	
			throw ex;
		}
	}
	
	
	
	private static FuncListDAO _instance;
	private Logger _log = Logger.getLogger(FuncListDAO.class.getClass());
}
