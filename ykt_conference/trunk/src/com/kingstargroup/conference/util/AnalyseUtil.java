/**
 * 
 */
package com.kingstargroup.conference.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import org.hibernate.HibernateException;

import com.kingstargroup.conference.dao.AnalyseDAO;
import com.kingstargroup.conference.dao.DictionaryDAO;
import com.kingstargroup.conference.hibernate.form.TConference;

public class AnalyseUtil extends BasicUtil {
	
	public static List getAllSignStatus() {
		AnalyseDAO dao = AnalyseDAO.getInstance();
		try {
			return dao.getAllSignStatus();
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		}finally{
			closeSession();
		}
	}

	/* 
	 * 取得已发生会议
	 */
	public static List getAllConfenece() {
		AnalyseDAO dao = AnalyseDAO.getInstance();
		try {
			return dao.getAllConference();
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		}finally{
			closeSession();
		}
	}

	/*
	 * 按主键取得会议信息
	 */ 
	public static TConference getConference(Integer conId) {
		AnalyseDAO dao = AnalyseDAO.getInstance();		
		try {
			return (TConference) dao.findByPrimaryKey(TConference.class, conId);
		} catch(HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}
	
	/*
	 * 按主键取得会议信息
	 */
	public static List getConference(Integer conId, String conType, String begindate, String enddate) {
		AnalyseDAO dao = AnalyseDAO.getInstance();		
		try {			
			return dao.getConference(conId, conType, begindate, enddate);
		} catch(HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}
	
	/*
	 * 按主键取得会议信息
	 */
	public static List getConferenceBySign(Integer conId, String duty, String sign) {
		AnalyseDAO dao = AnalyseDAO.getInstance();		
		try {			
			return dao.getConferenceBySign(conId, duty, sign);
		} catch(HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}

	/* 
	 * 按主键取得会议统计人数
	 */
	public static ArrayList getAtteCount(Integer conId) {
		AnalyseDAO dao = AnalyseDAO.getInstance();	
		ArrayList list = new ArrayList();
		int count = 0;
		try {
			/* 应出席 */
			count = dao.getAtteCountById(conId, null);
			list.add(0,new Integer(count));
			
			/* 实出席 */
			count = dao.getAtteCountById(conId, "1");
			count += dao.getAtteCountById(conId, "3");
			count += dao.getAtteCountById(conId, "4");
			count += dao.getAtteCountById(conId, "5");
			list.add(1,new Integer(count));
		
			/* 迟到 */
			count = dao.getAtteCountById(conId, "5");
			list.add(2,new Integer(count));
			
			/* 代签 */
			count = dao.getAtteCountById(conId, "4");
			list.add(3,new Integer(count));
			
			/* 请假 */
			count = dao.getAtteCountById(conId, "2");
			list.add(4,new Integer(count));		
		
			return list;
		} catch(HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}		
	/* 
	 * 按会议类型取得会议统计人数
	 */
	public static ArrayList getAtteCount(Integer conId, String conType, String begindate, String enddate) {
		AnalyseDAO dao = AnalyseDAO.getInstance();	
		ArrayList list = new ArrayList();
		int count = 0;
		try {			
			/* 应出席 */
			count = dao.getAtteCountByType(conId, conType, null, begindate, enddate);
			list.add(0,new Integer(count));
			
			/* 实出席 */
			count = dao.getAtteCountByType(conId, conType, "1", begindate, enddate);
			count += dao.getAtteCountByType(conId, conType, "3", begindate, enddate);
			count += dao.getAtteCountByType(conId, conType, "4", begindate, enddate);
			count += dao.getAtteCountByType(conId, conType, "5", begindate, enddate);
			list.add(1,new Integer(count));
			
			/* 迟到 */
			count = dao.getAtteCountByType(conId, conType, "5", begindate, enddate);
			list.add(2,new Integer(count));
			
			/* 代签 */
			count = dao.getAtteCountByType(conId, conType, "4", begindate, enddate);
			list.add(3,new Integer(count));
			
			/* 请假 */
			count = dao.getAtteCountByType(conId, conType, "2", begindate, enddate);
			list.add(4,new Integer(count));
			
			return list;
		} catch(HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}
	/* 
	 * 取得会议统计人数，与会者签到专用
	 */
	public static ArrayList getAtteCount(Integer conId, String duty, String sign) {
		AnalyseDAO dao = AnalyseDAO.getInstance();	
		ArrayList list = new ArrayList();
		int count = 0;
		try {	
			/* 应出席 */
			count = dao.getAtteCountBySign(conId, duty, null);						
			list.add(0,new Integer(count));
			count = 0;
			
			/* 实出席 */
			count = dao.getAtteCountBySign(conId, duty, "1");
			count += dao.getAtteCountBySign(conId, duty, "3");
			count += dao.getAtteCountBySign(conId, duty, "4");
			count += dao.getAtteCountBySign(conId, duty, "5");
			list.add(1,new Integer(count));
			count = 0;
			
			/* 迟到 */
			count = dao.getAtteCountBySign(conId, duty, "5");
			list.add(2,new Integer(count));
			count = 0;
			
			/* 代签 */
			count = dao.getAtteCountBySign(conId, duty, "4");
			list.add(3,new Integer(count));
			count = 0;
			
			/* 请假 */
			count = dao.getAtteCountBySign(conId, duty, "2");
			list.add(4,new Integer(count));
			count = 0;
			
			/* 选中状态 */
			count = dao.getAtteCountBySign(conId, duty, sign);
			list.add(5,new Integer(count));
			
			return list;
			
		} catch(HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}
	
	/* 
	 * 取得与会人员列表
	 */
	public static List getAttendeeList(Integer conId, String sign) {
		AnalyseDAO dao = AnalyseDAO.getInstance();	
		DictionaryDAO dictdao = DictionaryDAO.getInstance();
		List result = new ArrayList();
		List list = null;
		try {
			list = dao.getAttendeeList(conId, sign);
			for (int i=0, l=list.size();i<l;i++){
				Object[] objects = (Object[]) list.get(i);
				HashMap map = new HashMap();
				map.put("cutName",convent(objects[0]));
				map.put("deptName", convent(objects[1]));
				map.put("dutyName", convent(objects[2]));
				map.put("tel", convent(objects[3]));				
				map.put("sendSign", eqwith(objects[4]));
				map.put("informSign", eqwith(objects[5]));
				map.put("attendSign",dictdao.getAttendeeStatus(convent(objects[6])));
				map.put("attendTime",objects[7]);
				result.add(map);
			}
			return result;
		} catch(HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}
	/* 
	 * 取得与会人员列表
	 */
	public static List getAttendeeList(Integer conId, String duty, String sign) {
		AnalyseDAO dao = AnalyseDAO.getInstance();	
		DictionaryDAO dictdao = DictionaryDAO.getInstance();
		List result = new ArrayList();
		List list = null;
		try {
			list = dao.getAttendeeList(conId, sign, duty);
			for (int i=0, l=list.size();i<l;i++){
				Object[] objects = (Object[]) list.get(i);
				HashMap map = new HashMap();				
				map.put("cutName",convent(objects[0]));
				map.put("deptName", convent(objects[1]));
				map.put("dutyName", convent(objects[2]));
				map.put("tel", convent(objects[3]));				
				map.put("sendSign", eqwith(objects[4]));
				map.put("informSign", eqwith(objects[5]));
				map.put("attendSign",dictdao.getAttendeeStatus(convent(objects[6])));
				map.put("attendTime",objects[7]);
				result.add(map);
			}
			return result;
		} catch(HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}

	/* 
	 * 取得所有已发生会议类型
	 */
	public static List getAllConfType(){
		AnalyseDAO dao = AnalyseDAO.getInstance();
		List typeList = new ArrayList();
		try {
			typeList = dao.getConfType();
		} catch (HibernateException he) {
			he.printStackTrace();
		}finally{
			closeSession();
		}
		return typeList;
	}

	private static String convent (Object ss){
		if (null==ss){
			return "";
		}else{
			return ss.toString();
		}
	}
	
	/* 
	 * 为会议人员列表设计
	 * 判断是否下发通知
	 */
	private static String eqwith(Object ss) {
		String yes = "是";
		String no = "否";
		if (null==ss){
			return "";
		}else{
			int temp = Integer.parseInt(ss.toString());
			if(temp==0) {
				return no;
			} else if(temp==1) {			
				return yes;
			}
			return "";
		}
	}

		

	
}
