/**
 * 
 */
package com.kingstargroup.conference.dao;

import java.util.List;

import org.apache.log4j.Logger;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.CONSTANT;

/**
 * @author hjw
 * 
 */
public class FuncListDAO extends BasicDAO {

	/**
	 * Description:singleton pattern
	 * 
	 * @return Modify History:
	 */
	public static FuncListDAO getInstance() {
		if (_instance == null) {
			_instance = new FuncListDAO();
		}
		return _instance;
	}

	/**
	 * Description:根据父功能号得到子功能号列表
	 * 
	 * @param funcCode
	 * @return Modify History:
	 */
	public List getChildList(String funcCode) {
		Session s = getSession();
		List list = null;
		try {
			StringBuffer buff = new StringBuffer();
			if ("db2".equals(CONSTANT.DB_CONFIG)) {
				buff
						.append(
								" from TFuncList as func where func.funcCode like :funcCode")
						.append(
								" order by integer(substr(func.funcCode, locate('.', func.funcCode) + 1)) asc");
				Query query = s.createQuery(buff.toString());
				query.setString("funcCode", funcCode + ".%");
				list = query.list();
			} else if ("oracle".equals(CONSTANT.DB_CONFIG)) {
				buff
						.append(
								" from TFuncList as func where func.funcCode like :funcCode")
						.append(" order by func.funcCode asc");
				Query query = s.createQuery(buff.toString());
				query.setString("funcCode", funcCode + ".%");
				list = query.list();
			} else {
				buff
						.append(
								" from TFuncList as func where func.funcCode like :funcCode")
						.append(" order by func.funcCode asc");
				Query query = s.createQuery(buff.toString());
				query.setString("funcCode", funcCode + ".%");
				list = query.list();
			}
			return list;
		} catch (HibernateException ex) {
			_log.error(ex);
			return null;
		}
	}

	/**
	 * Description:取得一级栏目列表
	 * 
	 * @return Modify History:
	 */
	public List getParentList() {
		Session s = getSession();
		List list = null;
		try {
			StringBuffer buff = new StringBuffer();
			if ("db2".equals(CONSTANT.DB_CONFIG)) {
				buff.append(" from TFuncList where locate('.', funcCode) = 0");
				Query q = s.createQuery(buff.toString());
				list = q.list();
			} else if ("oracle".equals(CONSTANT.DB_CONFIG)) {
				buff.append(" from TFuncList where func_url is null");
				Query q = s.createQuery(buff.toString());
				list = q.list();
			} else {
				buff.append(" from TFuncList where func_url is null");
				Query q = s.createQuery(buff.toString());
				list = q.list();
			}
			return list;
		} catch (HibernateException ex) {
			_log.error(ex);
			throw ex;
		}
	}

	/**
	 * File name: FuncListDAO.java<br>
	 * Description: <br>
	 * Return:
	 * 
	 * @throws HibernateException
	 *             <br>
	 *             Modify History: <br>
	 *             操作类型 操作人 操作时间 操作内容<br>
	 *             ======================================<br>
	 *             创建 何林青 2007-1-15 <br>
	 * @author 何林青
	 * @version
	 * @since 1.0
	 */
	public void deleteAllFuncList() throws HibernateException {
		Session s = getSession();
		try {
			Query q = s.createQuery("delete from TFuncList");
			q.executeUpdate();

		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}

	private static FuncListDAO _instance;

	private Logger _log = Logger.getLogger(FuncListDAO.class.getClass());
}
