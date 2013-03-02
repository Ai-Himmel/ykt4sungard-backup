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
	 * Description:���ݸ����ܺŵõ��ӹ��ܺ��б�
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
	 * Description:ȡ��һ����Ŀ�б�
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
	 *             �������� ������ ����ʱ�� ��������<br>
	 *             ======================================<br>
	 *             ���� ������ 2007-1-15 <br>
	 * @author ������
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
