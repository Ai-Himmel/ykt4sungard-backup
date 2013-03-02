/**
 * 
 */
package com.kingstargroup.conference.dao;

import java.util.HashMap;
import java.util.Iterator;
import java.util.List;

import org.apache.log4j.Logger;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.conference.hibernate.form.TOperator;

/**
 * @author ��Ө
 * 
 */
public class OperatorDAO extends BasicDAO {
	private static OperatorDAO _instance;

	Logger errlog = Logger.getLogger("Errlog");
	Logger bizlog=Logger.getLogger("Businesslog");

	public static OperatorDAO getInstance() {
		if (_instance == null) {
			_instance = new OperatorDAO();
		}
		return _instance;
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: OperatorDAO�������еĲ���Ա�б�<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-14 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public List getAllOperatorList() throws HibernateException {
		Session s = getSession();
		HashMap map = new HashMap();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select new map(oper.operCode as operCode,oper.operName as operName,dept.deptName as deptName)")
		.append(" from TOperator oper,TCifDept dept where oper.deptId=dept.deptCode");
		try {
			Query q = s.createQuery(sqlStr.toString());
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: OperatorDAO���ݸ�����ŵõ����еĲ�������<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-13 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public List getDeptChildList(String pid) throws HibernateException {
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TCifDeptfull where parentdeptCode='"
					+ pid + "' and deptLevel in(0,1) order by dwglm");
			q.setCacheable(true);
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: OperatorDAO�����û����ȡ�ø��û���Ȩ���б�<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-14 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public List getFuncList(String userId) throws HibernateException {
		Session s = getSession();
		try {
			Query query = s
					.createQuery(" select id.funcCode from TOperLimit where id.operCode = :userId");
			query.setString("userId", userId);
			return query.list();
		} catch (HibernateException ex) {
			ex.printStackTrace();
			errlog.error(ex);
			throw ex;
		}
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: OperatorDAO���ݲ���Ա���ȡ�������еĲ���Ȩ��<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-17  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public List getDeptList(String userId) throws HibernateException {
		Session s = getSession();
		try {
			Query query = s.createQuery(" select id.deptId from TDeptLimit where id.operCode = :userId");			
			query.setString("userId", userId);
			return query.list();
		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: OperatorDAO�����û����ɾ�����û�������Ȩ��<br>
	 * Return: void<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-14 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public void deleteFuncList(String userId) throws HibernateException {
		Session s = getSession();
		try {
			Query query = s
					.createQuery(" from TOperLimit where id.operCode = :userId");

			query.setString("userId", userId);
			Iterator it = query.iterate();
			while (it.hasNext()) {
				s.delete(it.next());
			}
		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: OperatorDAO�����û����ɾ�����û�������Ȩ��<br>
	 * Return: void<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-14 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public void deleteFuncList(String userIds[]) throws HibernateException {
		try {
			for (int i = 0; i < userIds.length; i++) {
				deleteFuncList(userIds[i]);
			}
		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: OperatorDAOɾ��һ���û��Ĳ��Ų���Ȩ��<br>
	 * Return: void<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-17  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public void deleteDeptList(String userId) throws HibernateException {
		Session s = getSession();
		try {
			Query query = s.createQuery(" from TDeptLimit where id.operCode = :userId");
			
			query.setString("userId", userId);			
			Iterator it = query.iterate();
			while (it.hasNext()) {
				s.delete(it.next());
			}			
		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: OperatorDAO����ɾ������Ա�Ĳ��Ų���Ȩ��<br>
	 * Return: void<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-17  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public void deleteDeptList(String userIds[]) throws HibernateException {		
		try {
			for (int i = 0; i < userIds.length; i++) {
				deleteDeptList(userIds[i]);
			}
		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: OperatorDAO���ݲ���Ա���ɾ������Ա<br>
	 * Return: void<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-17  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public void deleteUser(String opercode){
		Session s = getSession();
		try {
			s.delete(s.get(TOperator.class,opercode));
		} catch (HibernateException he) {
			he.printStackTrace();
			errlog.error(he);
			throw he;
		}
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: OperatorDAO�����û����ȡ���û��ĸ��б�Ȩ��<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-14 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public List getUserParentFuncList(String userId) throws HibernateException {
		Session s = getSession();
		try {
			StringBuffer buff = new StringBuffer();
			buff
					.append(" from TFuncList where funcCode in")
					.append(" (select distinct(substr(id.funcCode, 1, 1)) from TOperLimit")
					.append(" where id.operCode = :userId) order by funcCode asc");
			Query q = s.createQuery(buff.toString());
			q.setString("userId", userId);
			return q.list();
		} catch (HibernateException ex) {
			ex.printStackTrace();
			errlog.error(ex);
			throw ex;
		}
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: OperatorDAO�����û��ź͸��˵���ȡ���Ӳ˵�<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-20  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public List getUserChildFuncList(String userId, String parentId) throws HibernateException {
		Session s = getSession();
		try {
			StringBuffer buff = new StringBuffer();			
			buff.append(" from TFuncList where funcCode in")
				.append(" (select id.funcCode from TOperLimit")
				.append(" where id.operCode = :userId and id.funcCode like :funcCode)")
				.append(" order by integer(substr(funcCode, locate('.', funcCode) + 1)) asc");
			Query q = s.createQuery(buff.toString());
			q.setString("userId", userId);
			q.setString("funcCode", parentId + ".%");
			return q.list();
		} catch (HibernateException ex) {
			ex.printStackTrace();
			errlog.error(ex);
			throw ex;
		}
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: OperatorDAO����û���¼Ȩ��<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-24  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public boolean checkUserRight(String userId, String funcURL) throws HibernateException {
		Session s = getSession();
		try {
			StringBuffer buff = new StringBuffer();
			buff.append(" from TFuncList func, TOperLimit limit")
				.append(" where func.funcCode = limit.id.funcCode and limit.id.operCode = :userId")
				.append(" and func.funcUrl = :funcURL");
			Query q = s.createQuery(buff.toString());
			q.setString("userId", userId);
			q.setString("funcURL", funcURL);
			if (q.list().size() > 0) {
				return true;
			} else {
				return false;
			}
			
		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}

}
