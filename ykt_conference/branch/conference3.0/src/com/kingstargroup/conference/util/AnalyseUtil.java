/**
 * 
 */
package com.kingstargroup.conference.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import org.hibernate.HibernateException;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

import com.kingstargroup.conference.dao.AnalyseDAO;
import com.kingstargroup.conference.dao.DictionaryDAO;
import com.kingstargroup.conference.hibernate.form.TConference;
import com.kingstargroup.conference.hibernate.form.TPhoto;

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
	 * ȡ���ѷ�������
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
	 * ������ȡ�û�����Ϣ
	 */ 
	public static TConference getConference(Long conId) {
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
	 * ������ȡ�û�����Ϣ
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
	 * ������ȡ�û�����Ϣ
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
	 * ������ȡ�û���ͳ������
	 */
	public static ArrayList getAtteCount(Integer conId) {
		AnalyseDAO dao = AnalyseDAO.getInstance();	
		ArrayList list = new ArrayList();
		int count = 0;
		try {
			/* Ӧ��ϯ */
			count = dao.getAtteCountById(conId, null);
			list.add(0,new Integer(count));
			
			/* ʵ��ϯ */
			count = dao.getAtteCountById(conId, "11");
			count += dao.getAtteCountById(conId, "12");
			count += dao.getAtteCountById(conId, "13");
			count += dao.getAtteCountById(conId, "21");
			count += dao.getAtteCountById(conId, "22");
			count += dao.getAtteCountById(conId, "23");
			list.add(1,new Integer(count));
		
			/* �ٵ� */
			count = dao.getAtteCountById(conId, "21");
			count += dao.getAtteCountById(conId, "22");
			count += dao.getAtteCountById(conId, "23");
			list.add(2,new Integer(count));
			
			/* ��ǩ */
			count = dao.getAtteCountById(conId, "13");
			count += dao.getAtteCountById(conId, "23");
			list.add(3,new Integer(count));
			
			/* ��� */
			count = dao.getAtteCountById(conId, "30");
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
	 * ����������ȡ�û���ͳ������
	 */
	public static ArrayList getAtteCount(Integer conId, String conType, String begindate, String enddate) {
		AnalyseDAO dao = AnalyseDAO.getInstance();	
		ArrayList list = new ArrayList();
		int count = 0;
		try {			
			/* Ӧ��ϯ */
			count = dao.getAtteCountByType(conId, conType, null, begindate, enddate);
			list.add(0,new Integer(count));
			
			/* ʵ��ϯ */
			count = dao.getAtteCountByType(conId, conType, "11", begindate, enddate);
			count += dao.getAtteCountByType(conId, conType, "12", begindate, enddate);
			count += dao.getAtteCountByType(conId, conType, "13", begindate, enddate);
			count += dao.getAtteCountByType(conId, conType, "21", begindate, enddate);
			count += dao.getAtteCountByType(conId, conType, "22", begindate, enddate);
			count += dao.getAtteCountByType(conId, conType, "23", begindate, enddate);
			list.add(1,new Integer(count));					
			
			/* ��� */
			count = dao.getAtteCountByType(conId, conType, "30", begindate, enddate);
			list.add(2,new Integer(count));
			
			/* ȱϯ */
			count = dao.getAtteCountByType(conId, conType, "00", begindate, enddate);
			list.add(3,new Integer(count));
			
			
			/*
			����ǩ�����ֿ�ǩ����
			 */
			count = dao.getAtteCountByType(conId, conType, "11", begindate, enddate);
			list.add(4,new Integer(count));
			/*
			�޿�ǩ��
			 */
			count = dao.getAtteCountByType(conId, conType, "12", begindate, enddate);
			list.add(5,new Integer(count));
			/*
			����ǩ��
			 */
			count = dao.getAtteCountByType(conId, conType, "13", begindate, enddate);
			list.add(6,new Integer(count));
			/*
			�ֿ�ǩ�����ٵ���
			 */
			count = dao.getAtteCountByType(conId, conType, "21", begindate, enddate);
			list.add(7,new Integer(count));
			/*
			�޿�ǩ�����ٵ���
			 */
			count = dao.getAtteCountByType(conId, conType, "22", begindate, enddate);
			list.add(8,new Integer(count));
			/*
			����ǩ�����ٵ���
			 */
			count = dao.getAtteCountByType(conId, conType, "23", begindate, enddate);
			list.add(9,new Integer(count));
			
			/* �ٵ� */
			count = dao.getAtteCountByType(conId, conType, "21", begindate, enddate);
			count += dao.getAtteCountByType(conId, conType, "22", begindate, enddate);
			count += dao.getAtteCountByType(conId, conType, "23", begindate, enddate);
			list.add(10,new Integer(count));
			
			
			return list;
		} catch(HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}
	/* 
	 * ȡ�û���ͳ�������������ǩ��ר��
	 */
	public static ArrayList getAtteCount(Integer conId, String duty, String sign) {
		AnalyseDAO dao = AnalyseDAO.getInstance();	
		ArrayList list = new ArrayList();
		int count = 0;
		try {	
			/* Ӧ��ϯ */
			count = dao.getAtteCountBySign(conId, duty, null);						
			list.add(0,new Integer(count));
			count = 0;
			
			/* ʵ��ϯ */
			count = dao.getAtteCountBySign(conId, duty, "11");
			count += dao.getAtteCountBySign(conId, duty, "12");
			count += dao.getAtteCountBySign(conId, duty, "13");
			count += dao.getAtteCountBySign(conId, duty, "21");
			count += dao.getAtteCountBySign(conId, duty, "22");
			count += dao.getAtteCountBySign(conId, duty, "23");
			list.add(1,new Integer(count));
			count = 0;
			
			/* �ٵ� */
			count = dao.getAtteCountBySign(conId, duty, "21");
			count += dao.getAtteCountBySign(conId, duty, "22");
			count += dao.getAtteCountBySign(conId, duty, "23");
			list.add(2,new Integer(count));
			count = 0;
			
			/* ��ǩ */
			count = dao.getAtteCountBySign(conId, duty, "13");
			count += dao.getAtteCountBySign(conId, duty, "23");
			list.add(3,new Integer(count));
			count = 0;
			
			/* ��� */
			count = dao.getAtteCountBySign(conId, duty, "30");
			list.add(4,new Integer(count));
			count = 0;
			
			/* ѡ��״̬ */
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
	 * ȡ�������Ա�б�
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
	
	/**
		* File name: AnalyseUtil.java<br>
		* Description: <br>
		* Return: @param conId
		* Return: @param sign
		* Return: @param attendeetime
		* Return: @return<br>
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-5-15  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public static List getPicAttendeeList(String conId, String attendeetime,String flag) {
		AnalyseDAO dao = AnalyseDAO.getInstance();
		List result = new ArrayList();
		List list = null;
		try {
			list = dao.getPicAttendeeList(conId, attendeetime,flag);
			for (int i=0, l=list.size();i<l;i++){
				Object[] objects = (Object[]) list.get(i);
				String dutyName = convent(objects[3]);
				if(i+1<l){
					Object[] objects1 = (Object[]) list.get(i+1);
					if(convent(objects[0]).equals(convent(objects1[0]))){
						dutyName += ", "+convent(objects1[3]);
						i++;
						for(int j=i+1;j<l;j++){
							objects1 = (Object[]) list.get(j);
							if(convent(objects[0]).equals(convent(objects1[0]))){
								dutyName += ","+convent(objects1[3]);
								i++;
								continue;
							}else{
								break;
							}
						}						
					}
				}
				
				
				HashMap map = new HashMap();
				map.put("custId",convent(objects[0]));
				map.put("cutName",convent(objects[1]));
				map.put("deptName", convent(objects[2]));
				map.put("dutyName", dutyName);
				map.put("stuempNo", convent(objects[4]));				
				map.put("attendTime",convent(objects[5]));
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
	
	/**
		* File name: AnalyseUtil.java<br>
		* Description: <br>
		* Return: @param conId
		* Return: @param attendeetime
		* Return: @param flag
		* Return: @return<br>
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-5-21  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public static List getPicAttendeeListTest(String conId, String attendeetime,String flag) {
		AnalyseDAO dao = AnalyseDAO.getInstance();
		List result = new ArrayList();
		List list = null;
		try {
			list = dao.getPicAttendeeListTest(conId, attendeetime,flag);
			for (int i=0, l=list.size();i<l;i++){
				Object[] objects = (Object[]) list.get(i);
				HashMap map = new HashMap();
				map.put("custId",convent(objects[0]));			
				map.put("attendTime",convent(objects[1]));
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
	
	
	public static List getTTAttendeeList(Integer conId, String sign) {
		return getAttendeeListByDept(conId,sign,null);
	}
	
	/**
	 * ����deptcode��û�����Ա�б�
	 * @param conId
	 * @param sign
	 * @param deptcode
	 * @return
	 */
	public static List getAttendeeListByDept(Integer conId, String sign,String deptcode) {
		AnalyseDAO dao = AnalyseDAO.getInstance();	
		DictionaryDAO dictdao = DictionaryDAO.getInstance();
		List result = new ArrayList();
		List list = null;
		try {
			list = dao.getTTAttendeeListByDept(conId, sign,deptcode);
			for (int i=0, l=list.size();i<l;i++){
				Object[] objects = (Object[]) list.get(i);
				
				String dutyName = convent(objects[3]);
				if(i+1<l){
					Object[] objects1 = (Object[]) list.get(i+1);
					if(convent(objects[1]).equals(convent(objects1[1]))){
						dutyName += ", "+convent(objects1[3]);
						i++;
						for(int j=i+1;j<l;j++){
							objects1 = (Object[]) list.get(j);
							if(convent(objects[1]).equals(convent(objects1[1]))){
								dutyName += ","+convent(objects1[3]);
								i++;
								continue;
							}else{
								break;
							}
						}						
					}
				}
				
				HashMap map = new HashMap();
				map.put("stuempNo",convent(objects[0]));
				map.put("cutName",convent(objects[1]));
				map.put("deptName", convent(objects[2]));
				map.put("dutyName", dutyName);
				map.put("tel", convent(objects[4]));		
				map.put("sendSign", eqwith(objects[5]));
				map.put("informSign", eqwith(objects[6]));
				map.put("attendSign",dictdao.getAttendeeStatus(convent(objects[7])));
				map.put("attendTime",objects[8]);
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
	 * ȡ�������Ա�б�
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
				map.put("stuempNo",convent(objects[0]));
				map.put("cutName",convent(objects[1]));
				map.put("deptName", convent(objects[2]));
				map.put("dutyName", convent(objects[3]));
				map.put("tel", convent(objects[4]));				
				map.put("sendSign", eqwith(objects[5]));
				map.put("informSign", eqwith(objects[6]));
				map.put("attendSign",dictdao.getAttendeeStatus(convent(objects[7])));
				map.put("attendTime",objects[8]);
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
	
	public static TPhoto getPhoto(Long custId){
		AnalyseDAO dao = AnalyseDAO.getInstance();	
		try {
			TPhoto photo = dao.getPhoto(custId);
			return photo;
		} catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
			return null;
		}
	}
	
	public static TPhoto getfudanPhoto(String stuempNo){
		AnalyseDAO dao = AnalyseDAO.getInstance();	
		try {
			TPhoto photo = dao.getfudanPhoto(stuempNo);
			return photo;
		} catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
			return null;
		}
	}

	/* 
	 * ȡ�������ѷ�����������
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
	 * Ϊ������Ա�б����
	 * �ж��Ƿ��·�֪ͨ
	 */
	private static String eqwith(Object ss) {
		String yes = "��";
		String no = "��";
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

	/**
	 * ����Ա����ͳ�Ƴ�ϯ���
	 * @param conId
	 * @return
	 */
	public static List getDeptCount(Integer conId) {
		AnalyseDAO dao = AnalyseDAO.getInstance();	
		List result = new ArrayList();
		List list = null;
		try {
			list = dao.getDeptCount(conId);
			for (int i=0;i<list.size();i++){
				Object[] objects = (Object[]) list.get(i);
				HashMap map = new HashMap();
				map.put("deptCode",convent(objects[0]));
				map.put("deptName", convent(objects[1]));
				map.put("planattendNum", convent(objects[2]));
				map.put("presentedNum", convent(objects[3]));				
				map.put("dayoffNum", convent(objects[4]));
				map.put("absentNum", convent(objects[5]));
				map.put("checkinNum",convent(objects[6]));
				map.put("nocardsignNum",convent(objects[7]));
				map.put("replacerNum",convent(objects[8]));
				map.put("checkinlateNum",convent(objects[9]));
				map.put("nocardsignlateNum",convent(objects[10]));
				map.put("replacerlateNum",convent(objects[11]));
				//ʵ�ʳ�ϯ
				Integer presented = Integer.valueOf(convent(objects[3]));
				//�ƻ���ϯ
				Integer planttend = Integer.valueOf(convent(objects[2]));
				float presentRate = planttend.intValue()==0?0:presented.intValue() *10000 /planttend.intValue() /100.00f;
				map.put("presentRate", String.valueOf(presentRate)+"%");
        		
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
	
	
}
