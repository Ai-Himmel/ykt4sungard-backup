package com.kingstargroup.conference.dao;

import java.util.Iterator;
import java.util.List;

import org.apache.commons.lang.StringUtils;
import org.apache.log4j.Logger;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

import com.kingstargroup.conference.common.DateUtilExtend;
import com.kingstargroup.conference.hibernate.form.TDictionary;

public class DictionaryDAO extends BasicDAO{
	static Logger log = Logger.getLogger("Errlog");
	public static DictionaryDAO getInstance() {
		if (_instance == null) {
			_instance = new DictionaryDAO();
		}
		return _instance;
	}
		/**
		 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
		 * File name: .java<br>
		 * Description: DictionaryDAO取得会议室列表<br>
		 * Return: List<br>
		 * Modify History: <br>
		 * 操作类型    操作人     操作时间       操作内容<br>
		 * ======================================<br>
		 *  创建      韩纪伟     2006-4-3  <br>
		 * @author   韩纪伟
		 * @version 
		 * @since 1.0
		 */
	public List getAssimblyRoom() throws HibernateException{
		Session s = getSession();
		List getList = null;
		try {
			Query q = s.createQuery(" from TAssemblyRoom");
			getList = q.list();
		} catch (HibernateException ex) {
			ex.printStackTrace();
			log.error(ex);
			throw ex;
		}	
		return getList;
	}
		/**
		 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
		 * File name: .java<br>
		 * Description: DictionaryDAO取得会议类型列表<br>
		 * Return: List<br>
		 * Modify History: <br>
		 * 操作类型    操作人     操作时间       操作内容<br>
		 * ======================================<br>
		 *  创建      韩纪伟     2006-4-3  <br>
		 * @author   韩纪伟
		 * @version 
		 * @since 1.0
		 */
	public List getConfType() throws HibernateException{
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TConferenceType");
			List getlist = q.list();
			return getlist;
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
		
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: DictionaryDAO获得一级单位列表<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-4  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public List getDeptList() throws HibernateException{
		Session s = getSession();
		try {
			SQLQuery q = s.createSQLQuery("select deptcode,deptname from ykt_cur.T_Dept where deptlevel=2");
			q.addScalar("deptcode",Hibernate.STRING);
			q.addScalar("deptname",Hibernate.STRING);
			return q.list();
		} catch (HibernateException he) {
			he.printStackTrace();
			errlog.equals(he);
			throw he;
		}
	}
	
	public List getDeptList(String operCode) throws HibernateException{
		Session s = getSession();
		try {
			String sql = "select deptcode, deptname from ykt_cur.T_Dept d, ykt_conf.t_dept_limit dl where d.deptcode = dl.dept_id and d.deptlevel = 2";
			//此处不判断operCode是否为空，当其为空时证明session已失效
			sql += " and dl.oper_code='"+operCode+"' ";
			SQLQuery q = s.createSQLQuery(sql);
			q.addScalar("deptcode",Hibernate.STRING);
			q.addScalar("deptname",Hibernate.STRING);
			return q.list();
		} catch (HibernateException he) {
			he.printStackTrace();
			errlog.equals(he);
			throw he;
		}
	}
	
	public String getDeptName(String dept_code) throws HibernateException{
		Session s = getSession();
		String deptName = "";
		try {
			
			Query q = s.createQuery("select deptname from TDept where deptcode='"+dept_code+"'");
			List list = q.list();
			if(list!=null&&list.size()>0){
				deptName = list.get(0).toString();
			}
			return deptName;
		} catch (HibernateException he) {
			he.printStackTrace();
			errlog.equals(he);
			throw he;
		}
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: DictionaryDAO根据操作员取得该操作员具有权限的会议列表<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-5  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public List getConfList(String username)throws HibernateException{
		Session s= getSession();
		StringBuffer sqlStr = new StringBuffer();
		String beginDate = DateUtilExtend.getNowDate2();
		//sqlStr.append(" from TConference where organigerId")
		//.append(" in(select deptId from TDeptLimit where operCode=:opercode) and beginDate>=:begindate");
		sqlStr.append(" from TConference where organigerId")
		.append(" in(select id.deptId from TDeptLimit where id.operCode='"+username+"')")
		.append(" and status!='9' and conBegindate>='"+beginDate+"'");
		try {
			Query q = s.createQuery(sqlStr.toString());
			///q.setString("begindate",beginDate);
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
	
	/**
		* File name: DictionaryDAO.java<br>
		* Description: <br> 本部门以前的会议
		* Return: @param username
		* Return: @return
		* Return: @throws HibernateException<br>
		* Modify History: <br>
		* 操作类型    操作人     操作时间       操作内容<br>
		* ======================================<br>
		*  创建      何林青    2007-3-29  <br>
		* @author   何林青
		* @version 
		* @since 1.0
		*/
	public List getConfListBeforeMeeting(String username)throws HibernateException{
		Session s= getSession();
		StringBuffer sqlStr = new StringBuffer();
		String beginDate = DateUtilExtend.getNowDate2();
		//sqlStr.append(" from TConference where organigerId")
		//.append(" in(select deptId from TDeptLimit where operCode=:opercode) and beginDate>=:begindate");
		sqlStr.append(" from TConference where organigerId")
		.append(" in(select id.deptId from TDeptLimit where id.operCode='"+username+"')")
		.append(" and status!='9' and conBegindate<='"+beginDate+"' order by conBegindate desc,conBegintime desc");
		try {
			Query q = s.createQuery(sqlStr.toString());
			///q.setString("begindate",beginDate);
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: DictionaryDAO从客户表中取得职务列表<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-6  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public List getDutyList()throws HibernateException{
		Session s = getSession();
		try {
			Query q = s.createQuery("select distinct dutyname from TCustomer");
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: DictionaryDAO根据登录操作员号取得该操作员所定义的组<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-6  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public List getGroupListByOper(String username)throws HibernateException{
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TGroup where operId='"+username+"' order by groupId");
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: DictionaryDAO根据操作员编号得到分组列表中的所有人员<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-11  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public List getAttendeeGroupListByOper(String username)throws HibernateException{
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select cust.cut_Id as cutId,cust.cut_Name as cutName,cust.stuemp_No as stuempNo,")
		.append(" cust.duty_Name as dutyName,dept.dept_Name as deptName,group.GROUP_ID as groupId ")
		.append(" from ykt_cur.T_CUSTOMER cust left join YKT_CUR.T_Dept dept")
		.append(" on cust.deptcode=dept.deptcode left join ykt_conf.T_ATTENDEE_GROUP group ")
		.append(" on group.CUST_ID=cust.custid where ")
		.append(" group.group_Id in(select group_Id from ykt_conf.T_Group where oper_Id='"+username+"')");
		try {
			//where id.groupId in(select groupId from TGroup where operId='"+Constants.USER_KEY+"')");
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId",Hibernate.INTEGER);
			q.addScalar("cutName",Hibernate.STRING);
			q.addScalar("stuempNo",Hibernate.STRING);
			q.addScalar("dutyName",Hibernate.STRING);
			q.addScalar("deptName",Hibernate.STRING);
			q.addScalar("groupId",Hibernate.INTEGER);
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: DictionaryDAO会议状态<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-11  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public String getConfStatus(String typeid)throws HibernateException{
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TDictionary where id.dicttype=80 and id.dictval='"+typeid+"'");
			return ((TDictionary)q.list().get(0)).getDictcaption();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: DictionaryDAO与会人员状态<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-11  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public String getAttendeeStatus(String statusid)throws HibernateException{
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TDictionary where id.dicttype=79 and id.dictval='"+statusid+"'");
			return ((TDictionary)q.list().get(0)).getDictcaption();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: DictionaryDAO人员类别<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-11  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public List getCustTypeList()throws HibernateException{
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TDictionary where id.dicttype=78");
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
	
	public TDictionary getCustType(String dictValue)throws HibernateException{
		Session s = getSession();
		TDictionary dic = null;
		try {
			Query q = s.createQuery(" from TDictionary where id.dicttype=78 and id.dictval='"+dictValue+"'");
			List list = q.list();
			Iterator iter = list.iterator();
			if (iter.hasNext()) {
				dic = (TDictionary) iter.next();
			}
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
		return dic;
	}
	
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: DictionaryDAO取得计时宝设备的列表<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-11  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public List getDeviceList()throws HibernateException{
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append(" from TDevice where devtypecode='0121' and devusage=1003");
		try {
			Query q = s.createQuery(sqlStr.toString());
			return q.list();
		} catch (HibernateException he) {
			he.printStackTrace();
			errlog.error(he);
			throw he;
		}
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: DictionaryDAO根据会议编号取得该会议所分配的设备列表<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-19  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public List getDeviceListByConfid(int confid)throws HibernateException{
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append(" from TDevice where devtypecode='0121' and deviceid in ")
		.append("(select id.deviceId from TDevConference where id.conId="+confid+")");
		try {
			Query q = s.createQuery(sqlStr.toString());
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
		
	}
	
	private Logger errlog = Logger.getLogger("Errlog");

	private static DictionaryDAO _instance;
}
