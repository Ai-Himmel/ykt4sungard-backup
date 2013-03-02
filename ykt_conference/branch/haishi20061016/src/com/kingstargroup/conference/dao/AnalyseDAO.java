/**
 * 
 */
package com.kingstargroup.conference.dao;

import java.util.List;

import org.apache.log4j.Logger;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.SQLQuery;
import org.hibernate.Session;


/**
 * @author 王莹
 *
 */
public class AnalyseDAO extends BasicDAO {

	private Logger errlog = Logger.getLogger("Errlog");
	private static AnalyseDAO _instance;
	public static AnalyseDAO getInstance() {
		if (_instance == null) {
			_instance = new AnalyseDAO();
		}
		return _instance;
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AnalyseDAO 返回所有未删除的已发生会议列表<br>
	 * @author 王莹
	 * @return List
	 * @throws HibernateException
	 */
	public List getAllConference() throws HibernateException {
		Session s = getSession();
		try {
			Query q = s.createQuery("select c from TConference c where c.status<>'9' " +
					" and c.conId in (select distinct a.id.conId from TAttendeeList a)");
			return q.list();			
		} catch(HibernateException ex) {
			ex.printStackTrace();
			errlog.error(ex);
			throw ex;
		}
	}


	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AnalyseDAO返回未删除的会议信息<br>
	 * @author 王莹
	 * @param enddate 
	 * @param begindate 
	 * @return List
	 * @throws HibernateException
	 */
	public List getConference(Integer conId, String conType, String begindate, String enddate) {
		Session s = getSession();
		try {
			StringBuffer sqlStr = new StringBuffer();
			boolean begin = false;
			boolean end = false;
			if(!"".equals(begindate)) {
				begin = true;
			}
			if(!"".equals(enddate)) {
				end = true;
			}
			
			sqlStr.append(" from TConference a where a.status<>'9' ");
			if (null != conId) {
				sqlStr.append(" and a.conId=" + conId);
			}
			if (!"".equals(conType)) {
				sqlStr.append(" and a.typeName='" + conType + "' ");
			}
			if (begin && end) {
				sqlStr.append(" and (a.conBegindate>='" + begindate + "' and a.conEnddate<='" + enddate + "' ) ");
			} else if(begin) {
				sqlStr.append(" and a.conBegindate>='" + begindate + "'  ");
			} else if(end) {
				sqlStr.append(" and a.conEnddate<='" + enddate + "'  ");
			}
			Query q = s.createQuery(sqlStr.toString());			
			return q.list();			
		} catch(HibernateException ex) {
			ex.printStackTrace();
			errlog.error(ex);
			throw ex;
		}
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AnalyseDAO 返回未删除的会议信息, 与会者签到统计专用<br>
	 * @author 王莹
	 * @param enddate 
	 * @param begindate 
	 * @return List
	 * @throws HibernateException
	 */
	public List getConferenceBySign(Integer conId, String duty, String sign) {
		Session s = getSession();
		try {
			StringBuffer sqlStr = new StringBuffer();
			boolean ifduty = false;
			boolean ifsign = false; 
			
			if(!"".equals(duty)) {
				ifduty = true;
			}
			if((!"".equals(sign)) && (null != sign)) {
				ifsign = true;
			}
			
			sqlStr.append(" from TConference c where c.status<>'9' ")
				.append(" and c.conId in (select a.id.conId from TAttendeeList a where 1=1 ");
			if(ifsign) {
				sqlStr.append(" and a.attendSign='" + sign + "' ");
			}
			if(ifduty) {
				sqlStr.append(" and a.id.custId in (select cus.cutId from TCifCustomer cus ")
					.append(" where cus.dutyName='" + duty + "') ");
			}
			sqlStr.append(" ) ");
						
			if(!"".equals(conId)) {
				sqlStr.append(" and c.conId=" + conId);
			}
			
			Query q = s.createQuery(sqlStr.toString());			
			return q.list();			
		} catch(HibernateException ex) {
			ex.printStackTrace();
			errlog.error(ex);
			throw ex;
		}
	}
	

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AnalyseDAO 返回与会者统计人数<br>
	 * @author 王莹
	 * @return int
	 * @throws HibernateException
	 */ 
	public int getAtteCountById(Integer conId, String sign) {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select count(*) from TAttendeeList a where a.id.conId=" + conId);
		if(null != sign) {
			sqlStr.append(" and a.attendSign='" + sign + "' ");
		}
		try {			
			Query q = s.createQuery(sqlStr.toString());
			int count = 0;			
			count = ((Integer) q.uniqueResult()).intValue();
			return count;			
		} catch(HibernateException ex) {
			ex.printStackTrace();
			errlog.error(ex);
			throw ex;
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AnalyseDAO 返回与会者统计数<br>
	 * @author 王莹
	 * @return int
	 * @throws HibernateException
	 */
	public int getAtteCountByType(Integer conId, String conType, String sign, String begindate, String enddate) {
		Session s = getSession();
		boolean begin = false;
		boolean end = false;
		if(!"".equals(begindate)) {
			begin = true;
		}
		if(!"".equals(enddate)) {
			end = true;
		}
		
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select count(*) from TAttendeeList a where a.id.conId in ")
			.append(" (select c.conId from TConference c where 1=1 ");
		if (null != conId) {
			sqlStr.append(" and c.conId=" + conId);
		}
		if (!"".equals(conType)) {
			sqlStr.append(" and c.typeName='" + conType + "' ");
		}
		if (begin && end) {
			sqlStr.append(" and (c.conBegindate>='" + begindate + "' and c.conEnddate<='" + enddate + "') ");
		} else if(begin) {
			sqlStr.append(" and c.conBegindate>='" + begindate + "' ");
		} else if(end) {
			sqlStr.append(" and c.conEnddate<='" + enddate + "' ");
		}
		if(null != sign) {
			sqlStr.append(" ) and a.attendSign='" + sign + "' ");
		} else {
			sqlStr.append(" )");
		}
		
		try {			
			Query q = s.createQuery(sqlStr.toString());
			int count = 0;			
			count = ((Integer) q.uniqueResult()).intValue();
			return count;			
		} catch(HibernateException ex) {
			ex.printStackTrace();
			errlog.error(ex);
			throw ex;
		}
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AnalyseDAO 返回与会者统计数, 与会者签到统计专用<br>
	 * @author 王莹
	 * @return int
	 * @throws HibernateException
	 */
	public int getAtteCountBySign(Integer conId, String duty, String sign) {
		Session s = getSession();	
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select count(*) from TAttendeeList a where a.id.conId in ")
			.append(" (select c.conId from TConference c where c.status<>'9') ");
		if(!"".equals(conId)) {
			sqlStr.append(" and a.id.conId=" + conId);
		}
		if(!"".equals(sign) && null != sign) {
			sqlStr.append(" and a.attendSign='" + sign + "' ");
		}
		if(!"".equals(duty)) {
			sqlStr.append(" and a.id.custId in (select cus.cutId from TCifCustomer cus ")
				.append(" where cus.dutyName='" + duty + "') ");
		}
		
		try {			
			Query q = s.createQuery(sqlStr.toString());
			int count = 0;			
			count = ((Integer) q.uniqueResult()).intValue();
			return count;			
		} catch(HibernateException ex) {
			ex.printStackTrace();
			errlog.error(ex);
			throw ex;
		}
	}

	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AnalyseDAO 返回与会者列表 
	 * 				签到标志：0-未签到；1-正常；2-请假；3-无卡；4-代替；5-迟到；9-其它；<br>
	 * @author 王莹
	 * @return List
	 * @throws HibernateException
	 */
	public List getAttendeeList(Integer conId, String sign) {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select ")
			.append(" c.cut_name as cutName,")
			.append(" d.dept_name as deptName,")
			.append(" duty.duty as dutyName, c.tel as tel,")
			.append(" a.send_sign as sendSign,")
			.append(" l.inform_sign as informSign,")
			.append(" a.attend_Sign as attendSign,")
			.append(" a.attend_Time as attendTime")
			.append(" from ykt_conf.t_attendee_list a")
			.append(" join ykt_cur.t_cif_customer c on a.cust_Id=c.cut_Id")
			.append(" join ykt_conf.t_inform_list l on a.cust_Id=l.cust_Id and a.con_Id=l.con_id")
			.append(" left join  ykt_cur.t_cif_dept d on c.classdept_No=d.dept_Code")
			.append(" left join YKT_CONF.T_DUTY duty on c.stuemp_No=duty.stuemp_No")
			.append(" ")
			.append(" where a.con_Id=" + conId);
		if("0".equals(sign)) {	// 取出席人员列表
			sqlStr.append(" and a.attend_Sign in ('1', '3', '4','5')");
		}
		if("1".equals(sign)) {	// 取迟到人员列表
			sqlStr.append(" and a.attend_Sign='5'");
		}
		if("2".equals(sign)) {	// 取请假人员列表
			sqlStr.append(" and a.attend_Sign='2'");
		}
		if("3".equals(sign)) {	// 缺席人员列表
			sqlStr.append(" and a.attend_Sign='0'");
		}
		if ("4".equals(sign)){
			sqlStr.append(" and a.attend_Sign in ('0','1','2','3','4','5','9')");
		}
		if("9".equals(sign)) {	// 取所有未正常出席人员列表
			sqlStr.append(" and a.attend_Sign in ('2', '5', '0')");
		}
		sqlStr.append(" order by c.cut_name ");
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutName",Hibernate.STRING);
			q.addScalar("deptName",Hibernate.STRING);
			q.addScalar("dutyName",Hibernate.STRING);
			q.addScalar("tel",Hibernate.STRING);
			q.addScalar("sendSign",Hibernate.STRING);
			q.addScalar("informSign",Hibernate.STRING);	
			q.addScalar("attendSign",Hibernate.STRING);
			q.addScalar("attendTime",Hibernate.STRING);
			return q.list();			
		} catch(HibernateException ex) {
			ex.printStackTrace();
			errlog.error(ex);
			throw ex;
		}
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AnalyseDAO 返回与会者列表<br>
	 * @author 王莹
	 * @return List
	 * @throws HibernateException
	 */
	public List getAttendeeList(Integer conId, String sign, String duty) {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select ")
		.append(" c.cut_name as cutName,")
		.append(" d.dept_name as deptName,")
		.append(" duty.duty as dutyName, c.tel as tel,")
		.append(" a.send_sign as sendSign,")
		.append(" l.inform_sign as informSign,")
		.append(" a.attend_Sign as attendSign,")
		.append(" a.attend_Time as attendTime")
		.append(" from ykt_conf.t_attendee_list a")
		.append(" join ykt_cur.t_cif_customer c on a.cust_Id=c.cut_Id")		
		.append(" join ykt_conf.t_inform_list l on a.cust_Id=l.cust_Id and a.con_Id=l.con_id")
		.append(" left join  ykt_cur.t_cif_dept d on c.classdept_No=d.dept_Code")
		.append(" left join YKT_CONF.T_DUTY duty on c.stuemp_No=duty.stuemp_No")
		.append(" where a.con_Id=" + conId);
		if((!"".equals(sign)) && (null != sign)) {	// 取所有人员列表
			sqlStr.append(" and a.attend_Sign='" + sign + "' ");
		} 
		if(!"".equals(duty)) {
			sqlStr.append(" and duty.duty='" + duty + "' ");
		}
		sqlStr.append(" order by c.cut_name ");
		
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutName",Hibernate.STRING);
			q.addScalar("deptName",Hibernate.STRING);
			q.addScalar("dutyName",Hibernate.STRING);
			q.addScalar("tel",Hibernate.STRING);
			q.addScalar("sendSign",Hibernate.STRING);
			q.addScalar("informSign",Hibernate.STRING);
			q.addScalar("attendSign",Hibernate.STRING);
			q.addScalar("attendTime",Hibernate.STRING);
			return q.list();			
		} catch(HibernateException ex) {
			ex.printStackTrace();
			errlog.error(ex);
			throw ex;
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AnalyseDAO 返回会议类型列表<br>
	 * @author 王莹
	 * @return List
	 * @throws HibernateException
	 */
	public List getConfType() throws HibernateException{
		Session s = getSession();
		String sql = "select c.typeName from TConference c " +
				" where c.conId in (select distinct a.id.conId from TAttendeeList a) ";
		try {
			Query q = s.createQuery(sql);
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}		
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AnalyseDAO 返回会议签到状态列表<br>
	 * @author 王莹
	 * @return List
	 * @throws HibernateException
	 */
	public List getAllSignStatus() {
		Session s = getSession();
		String sql = " from TPifDictionary d where d.id.dictNo=79 ";
		try {
			Query q = s.createQuery(sql);
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}

	

	

	

	
	
}
