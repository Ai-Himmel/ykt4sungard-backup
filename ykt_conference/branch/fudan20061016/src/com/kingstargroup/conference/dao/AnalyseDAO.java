/**
 * 
 */
package com.kingstargroup.conference.dao;

import java.util.HashMap;
import java.util.List;

import org.apache.log4j.Logger;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

import com.kingstargroup.conference.hibernate.form.TCifPhoto;


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
	private static HashMap photohash = new HashMap();
	
	
	
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
	
	/***
	 *   其他到场人员统计
	 */
	
	public int getAtteCountByNoInform(Integer conId,String sign){
		Session s = getSession();
		
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append(" select count(*) from TRecordhis r where r.confid ="+conId)
		      .append(" and r.attendSign='"+sign+"'");
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
			sqlStr.append(" and a.attend_Sign in ('11','12','13','21','22','23')");
		}
		if("1".equals(sign)) {	// 取迟到人员列表
			sqlStr.append(" and a.attend_Sign in ('21','22','23')");
		}
		if("2".equals(sign)) {	// 取请假人员列表
			sqlStr.append(" and a.attend_Sign='30'");
		}
		if("3".equals(sign)) {	// 缺席人员列表
			sqlStr.append(" and a.attend_Sign='00'");
		}
		if ("4".equals(sign)){
			sqlStr.append(" and a.attend_Sign in ('00','11','12','13','21','22','23','30')");
		}
		if("9".equals(sign)) {	// 取所有未正常出席人员列表
			sqlStr.append(" and a.attend_Sign in ('00','21','22','23','30')");
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
	public List getPicAttendeeList(String conId,String attendeetime, String flag) {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select ")
			.append(" a.cust_id as custId,")
			.append(" a.cut_name as cutName,")
			.append(" a.dept_name as deptName,")
			.append(" '' as dutyName, a.stuemp_no as stuempNo,")
			.append(" a.attend_Time as attendTime")			
			.append(" from ykt_conf.t_attendee_list a")
			.append(" where a.con_Id=" + conId);
			sqlStr.append(" and a.attend_Sign in ('11','12','13','21','22','23') ");
			if("0".equals(flag)){
				//第一个人
				if(!"".equals(attendeetime)){
					sqlStr.append(" and a.attend_time>'");
					sqlStr.append(attendeetime);
					sqlStr.append("' order by a.attend_Time");
				}else{
					sqlStr.append(" order by a.attend_Time desc");
				}
				
			}else{
				if(!"".equals(attendeetime)){
					sqlStr.append(" and a.attend_time<='");
					sqlStr.append(attendeetime);
					sqlStr.append("' order by a.attend_Time desc");
				}else{
					sqlStr.append(" order by a.attend_Time desc");
				}
			}
			sqlStr.append(" with ur");
			
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("custId",Hibernate.INTEGER);
			q.addScalar("cutName",Hibernate.STRING);
			q.addScalar("deptName",Hibernate.STRING);
			q.addScalar("dutyName",Hibernate.STRING);
			q.addScalar("stuempNo",Hibernate.STRING);
			q.addScalar("attendTime",Hibernate.STRING);
			return q.list();			
		} catch(HibernateException ex) {
			ex.printStackTrace();
			errlog.error(ex);
			throw ex;
		}
	}
	
	public List getPicAttendeeListTest(String conId,String attendeetime, String flag) {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select ")
			.append(" a.cust_id as custId,")
			.append(" a.attend_Time as attendTime")
			.append(" from ykt_conf.t_attendee_list a")
			.append(" where a.con_Id=" + conId);
			sqlStr.append(" and a.attend_Sign in ('11','12','13','21','22','23') ");
			if("0".equals(flag)){
				//第一个人
				if(!"".equals(attendeetime)){
					sqlStr.append(" and a.attend_time>'");
					sqlStr.append(attendeetime);
					sqlStr.append("' order by a.attend_Time");
				}else{
					sqlStr.append(" order by a.attend_Time desc");
				}
				
			}else{
				if(!"".equals(attendeetime)){
					sqlStr.append(" and a.attend_time<='");
					sqlStr.append(attendeetime);
					sqlStr.append("' order by a.attend_Time desc");
				}else{
					sqlStr.append(" order by a.attend_Time desc");
				}
			}
			
			sqlStr.append(" with ur");
			
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("custId",Hibernate.INTEGER);
			q.addScalar("attendTime",Hibernate.STRING);
			return q.list();			
		} catch(HibernateException ex) {
			ex.printStackTrace();
			errlog.error(ex);
			throw ex;
		}
	}
	
	public List getTTAttendeeList(Integer conId, String sign) {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select ")
			.append(" COALESCE(c.cut_name,a.cut_name) as cutName,")
			.append(" COALESCE(d.dept_name,a.dept_name) as deptName,")
			.append(" COALESCE(duty.duty,replacer_duty) as dutyName, c.tel as tel,")
			.append(" a.send_sign as sendSign,")
			.append(" COALESCE(l.inform_sign,'0')  as informSign,")
			.append(" a.attend_Sign as attendSign,")
			.append(" a.attend_Time as attendTime")
			.append(" from ykt_conf.t_attendee_list a")
			.append(" left outer join ykt_cur.t_cif_customer c on a.cust_Id=c.cut_Id")
			.append(" left join ykt_conf.t_inform_list l on a.cust_Id=l.cust_Id and a.con_Id=l.con_id")
			.append(" left join  ykt_cur.t_cif_dept d on c.classdept_No=d.dept_Code")
			.append(" left join YKT_CONF.T_DUTY duty on c.stuemp_No=duty.stuemp_No")
			.append(" ")
			.append(" where a.con_Id=" + conId);		
		if("1".equals(sign)) {	
			sqlStr.append(" and a.attend_Sign in ('00','11','12','13','21','22','23','30')");			
		}
		if("2".equals(sign)) {	
			sqlStr.append(" and a.attend_Sign in ('11','12','13','21','22','23')");
		}
		if("3".equals(sign)) {	
			sqlStr.append(" and a.attend_Sign='30'");
		}
		if ("4".equals(sign)){
			sqlStr.append(" and a.attend_Sign='00'");
		}
		if("5".equals(sign)) {	
			sqlStr.append(" and a.attend_Sign='11'");
		}
		if("6".equals(sign)) {	
			sqlStr.append(" and a.attend_Sign='12'");
		}
		if("7".equals(sign)) {	
			sqlStr.append(" and a.attend_Sign='13'");
		}
		if ("8".equals(sign)){
			sqlStr.append(" and a.attend_Sign='21'");
		}
		if("9".equals(sign)) {	
			sqlStr.append(" and a.attend_Sign='22'");
		}
		if("10".equals(sign)) {
			sqlStr.append(" and a.attend_Sign='23'");
		}
		if("11".equals(sign)||"12".equals(sign)){
		  return 	getNoInfoSignList(conId,sign);
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
	
	public   List  getNoInfoSignList(Integer  conId,String sign) throws HibernateException {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select ")
		      .append(" cust.cut_name as cutName ,  d.dept_name  as deptName  ,duty.duty as  dutyName , cust.tel as tel," )
		      .append(" 0 as sendSign ,0 as informSign ,ATTEND_SIGN as attendSign , CHECKTIME as attendTime ,  DEALORNOT ")
              .append(" from YKT_CONF.T_RECORDHIS  r ") 
	          .append(" inner join YKT_CUR.T_PIF_CARD c on r.physical_no=c.physical_no and r.confid="+conId )
	          .append(" inner join  ykt_cur.t_cif_customer  cust on  cust.cut_id = c.cosumer_id ")
		      .append(" left join  ykt_cur.t_cif_dept d  on cust.classdept_No=d.dept_Code ")
		      .append(" left join YKT_CONF.T_DUTY duty on cust.stuemp_No=duty.stuemp_No ")
		      .append("  where r.ATTEND_SIGN='"+sign+"'")
		      .append(" order by ID");
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
			q.addScalar("DEALORNOT",Hibernate.STRING);
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
		String sql = "select distinct c.typeName from TConference c " +
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

	public TCifPhoto getCifPhoto(Integer custId){
		Session s = getSession();
		String sql = " from TCifPhoto cif where cif.cutId= "+custId +"";
		try {
			Query q = s.createQuery(sql);
			List list = q.list();
			if(list!=null&&list.size()>0){
				return (TCifPhoto)list.get(0);
			}else{
				return null;
			}
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
		
	}
	
	public TCifPhoto getfudanCifPhoto(String stuempNo){
//		if(photohash.size()>=50){
//			photohash.clear();
//		}
//		if(photohash!=null && photohash.get(stuempNo)!=null){
//			TCifPhoto aaa = (TCifPhoto)photohash.get(stuempNo);
//			if(aaa.getPhoto()==null){
//				System.out.println("omg  that's it lob is empty");
//			}
//			return aaa;
//		}else{
			Session s = getSession();
			String sql = " from TCifPhoto cif where cif.stuempNo= '"+stuempNo+"'";
			try {
				Query q = s.createQuery(sql);
				List list = q.list();
				if(list!=null&&list.size()>0){
					return (TCifPhoto)list.get(0);
				}else{
					return null;
				}
			} catch (HibernateException he) {
				errlog.error(he);
				throw he;
			}
//		}
		
	}

	

	

	
	
}
