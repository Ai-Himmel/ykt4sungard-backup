/**
 * 
 */
package com.kingstargroup.advquery.hibernate.dao;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

import com.kingstargroup.advquery.hibernate.user.TLeadqueryOperator;
import com.kingstargroup.advquery.util.WebKeys;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: UserDAO.java<br>
 * Description: <br>
 * Modify History: <br>
 * ��������   ������   ����ʱ��     ��������<br>
 * ===================================<br>
 *  ����    Xiao Qi  2005-11-9  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class UserDAO extends BasicDAO {
	/**
	 * Description:singleton pattern
	 * @return
	 * Modify History:
	 */
	public static UserDAO getInstance() {
		if (_instance == null) {
			_instance = new UserDAO();
		}
		return _instance;
	}
	
	
	public  List queryUsers(String userId,String username){
		Session s = getSession();
		try{
			StringBuffer buff = new StringBuffer();		
			buff.append("select t.oper_code operCode,t.oper_name operName ,t.is_shop_owner  isShop from ykt_query.T_LEADQUERY_OPERATOR  t where 1=1 ");
			
			if(userId !=null && !userId.equals("") ){
				buff.append(" and  t.oper_code like '%").append(userId).append("%'");
			}
			if(username !=null && !username.equals("")){
				buff.append(" and  t.oper_name like '%").append(username).append("%'");
			}
			
			SQLQuery q = s.createSQLQuery(buff.toString());
			q.addScalar("operCode", Hibernate.STRING);
			q.addScalar("operName", Hibernate.STRING);
			q.addScalar("isShop", Hibernate.STRING);
			
			List list = q.list();
			List temp = new ArrayList();
			
			if(list !=null && list.size()>0){
				for(int i=0;i<list.size();i++){
					Object[] obj = (Object[])list.get(i);
					TLeadqueryOperator ope = new TLeadqueryOperator();
					ope.setOperCode((String)obj[0]);
					ope.setOperName((String)obj[1]);
					ope.setIsShopOwner((String)obj[2]);
                    temp.add(ope);					
				}
			}
			return temp;
				
		}catch (HibernateException ex) {
			_log.error(ex);
			throw ex;
		}
		
	}
	
	
	public void deleteUsers(String userIds[]) throws HibernateException {
		Session s = getSession();
		try {
			for (int i = 0; i < userIds.length; i++) {
				s.delete(s.get(TLeadqueryOperator.class, userIds[i]));
			}			
		} catch (HibernateException ex) {
			_log.error(ex);
			throw ex;
		}
	}
	
	public List getUsers() throws HibernateException{
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TLeadqueryOperator where operCode <> 'admin'");
			return q.list();
		} catch (HibernateException ex) {
			_log.error(ex);
			throw ex;
		}
	}
	
	public List getUserParentFuncList(String userId) throws HibernateException {
		Session s = getSession();
		try {
			StringBuffer buff = new StringBuffer();			
			buff.append(" from TLeadqueryFunclist where funcCode in")
				.append(" (select distinct(substr(id.funcCode, 1, 1)) from TLeadqueryOperlimit")
				.append(" where id.operCode = :userId) order by funcCode asc");
			Query q = s.createQuery(buff.toString());
			//System.out.println(buff.toString());
			q.setString("userId", userId);
			return q.list();
		} catch (HibernateException ex) {
			_log.error(ex);
			throw ex;
		}
	}
	
	public List getUserChildFuncList(String userId, String parentId) throws HibernateException {
		Session s = getSession();
		try {
			StringBuffer buff = new StringBuffer();		
			if ("ORACLE".equals(WebKeys.DATABASE)){
				buff.append(" from TLeadqueryFunclist where funcCode in")
				.append(" (select id.funcCode from TLeadqueryOperlimit")
				.append(" where id.operCode = :userId and id.funcCode like :funcCode)")
				.append(" order by to_number(substr(funcCode, instr('.', funcCode) + 1)) asc");
			}else if ("DB2".equals(WebKeys.DATABASE)){
				buff.append(" from TLeadqueryFunclist where funcCode in")
				.append(" (select id.funcCode from TLeadqueryOperlimit")
				.append(" where id.operCode = :userId and id.funcCode like :funcCode)")
				.append(" order by integer(substr(funcCode, locate('.', funcCode) + 1)) asc");
			}

			Query q = s.createQuery(buff.toString());
			q.setString("userId", userId);
			q.setString("funcCode", parentId + ".%");
			return q.list();
		} catch (HibernateException ex) {
			_log.error(ex);
			throw ex;
		}
	}
	
	public boolean checkUserRight(String userId, String funcURL) throws HibernateException {
		Session s = getSession();
		try {
			StringBuffer buff = new StringBuffer();
			buff.append(" from TLeadqueryFunclist func, TLeadqueryOperlimit limit")
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
			_log.error(ex);
			throw ex;
		}
	}
	private static UserDAO _instance;
	private Log _log = LogFactory.getLog(UserDAO.class.getClass());
}
