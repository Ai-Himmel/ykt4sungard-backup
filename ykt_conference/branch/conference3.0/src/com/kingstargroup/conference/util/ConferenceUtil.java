package com.kingstargroup.conference.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import org.hibernate.HibernateException;
import org.hibernate.Transaction;

import com.kingstargroup.conference.common.DateUtilExtend;
import com.kingstargroup.conference.dao.ConferenceDAO;
import com.kingstargroup.conference.hibernate.form.DeptCustForm;
import com.kingstargroup.conference.hibernate.form.TConference;

public class ConferenceUtil extends BasicUtil {

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ConferenceUtil创建会议<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-3 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public static boolean createConference(String confName, String open,
			String roomId, String typeName, String signTime, String beginDate,
			String beginTime, String endDate, String endTime, String compere,
			String orgId, String ifSerecy, String explan, String comments,
			String username) {
		ConferenceDAO dao = ConferenceDAO.getInstance();
		Transaction t = beginTransaction();
		try {
			TConference conf = new TConference();
			conf.setConName(confName);
			conf.setPreplan1(open);
			conf.setRoomId(roomId);
			conf.setTypeName(typeName);
			conf.setConSigntime(signTime);
			conf.setConBegindate(beginDate);
			conf.setConEnddate(endDate);
			conf.setConBegintime(beginTime);
			conf.setConEndtime(endTime);
			conf.setCompere(compere);
			conf.setOrganigerId(orgId);
			conf.setIfSerecy(ifSerecy);
			conf.setConExplain(explan.trim());
			conf.setComments(comments.trim());
			conf.setStatus("0");
			conf.setPreplan2(username);
			dao.save(conf);
			t.commit();
		} catch (HibernateException e) {
			e.printStackTrace();
			t.rollback();
			return false;
		} finally {
			closeSession();
		}
		return true;
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ConferenceUtil返回日期大约当天的所有会议<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-4 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public static List getAllConference(String username) {
		ConferenceDAO dao = ConferenceDAO.getInstance();
		List result = new ArrayList();
		List confList = null;
		try {
			confList = dao.getConference(username);
			for (int i = 0; i < confList.size(); i++) {
				Object[] objects = (Object[]) confList.get(i);
				HashMap confMap = new HashMap();
				confMap.put("conId", new Integer(convent(objects[0])));
				confMap.put("conName", convent(objects[1]));
				confMap.put("roomId", convent(objects[2]));
				confMap.put("roomName", convent(objects[3]));
				confMap.put("address", convent(objects[4]));
				confMap.put("typeName", convent(objects[5]));
				confMap.put("confTime", convent(objects[6]));
				confMap.put("beginDate", convent(objects[7]));
				confMap.put("beginTime", convent(objects[8]));
				confMap.put("endDate", convent(objects[9]));
				confMap.put("endTime", convent(objects[10]));
				confMap.put("deptName", convent(objects[11]));
				confMap.put("orgId", convent(objects[12]));
				confMap.put("compere", convent(objects[13]));

				confMap.put("explain", convent(objects[14]));
				confMap.put("content", convent(objects[15]));
				confMap.put("status", GetDictionary
						.getConfStatus(convent(objects[16])));
				confMap.put("content", convent(objects[17]));
				confMap.put("comments", convent(objects[18]));
				result.add(confMap);
			}

			return result;
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ConferenceUtil删除会议，设置其状态为9<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-4 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public static boolean deleteConference(String ids[]) {
		ConferenceDAO dao = ConferenceDAO.getInstance();
		Transaction t = beginTransaction();
		try {
			for (int i = 0; i < ids.length; i++) {
				TConference conf = (TConference) dao.findByPrimaryKey(
						TConference.class, new Long(ids[i]));
				conf.setStatus("9");
				dao.saveOrUpdate(conf);
			}
			t.commit();
		} catch (HibernateException he) {
			he.printStackTrace();
			t.rollback();
			return false;
		} finally {
			closeSession();
		}
		return true;
	}

	public static boolean canbedeleteofconference(String ids[]) {

		ConferenceDAO dao = ConferenceDAO.getInstance();
		Transaction t = beginTransaction();
		String date = DateUtilExtend.getNowDate2();
		String time = DateUtilExtend.getNowTime2();
		boolean ret = true;
		try {
			for (int i = 0; i < ids.length; i++) {
				TConference conf = (TConference) dao.findByPrimaryKey(
						TConference.class, new Long(ids[i]));
				if (conf.getConBegindate().compareTo(date) <= 0
						&& conf.getConSigntime().compareTo(time) <= 0) {
					// 已经开始了不能删
					ret = false;
					break;
				}
			}
		} catch (HibernateException he) {
			he.printStackTrace();
			t.rollback();
			return false;
		} finally {
			closeSession();
		}
		return ret;

	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ConferenceUtil会议修改<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-5 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public static boolean editConference(Long confId, String confName,
			String open, String roomId, String typeName, String signTime,
			String beginDate, String beginTime, String endDate, String endTime,
			String compere, String orgId, String ifSerecy, String explan,
			String comments) {
		ConferenceDAO dao = ConferenceDAO.getInstance();

		Transaction t = beginTransaction();
		try {
			TConference conf = (TConference) dao.findByPrimaryKey(
					TConference.class, confId);
			conf.setConName(confName);
			conf.setPreplan1(open);
			conf.setRoomId(roomId);
			conf.setTypeName(typeName);
			conf.setConSigntime(signTime);
			conf.setConBegindate(beginDate);
			conf.setConEnddate(endDate);
			conf.setConBegintime(beginTime);
			conf.setConEndtime(endTime);
			conf.setCompere(compere);
			conf.setOrganigerId(orgId);
			conf.setIfSerecy(ifSerecy);
			conf.setConExplain(explan.trim());
			conf.setComments(comments.trim());
			conf.setStatus("1");
			dao.save(conf);

			t.commit();
		} catch (HibernateException he) {
			he.printStackTrace();
			t.rollback();
			return false;
		} finally {
			closeSession();
		}
		return true;
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ConferenceUtil返回会议查询记录集<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-5 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public static List getConfListByQuery(String confName, String confType,
			String confRoom, String confDept, String beginDate, String endDate,
			String compere, String username) {
		ConferenceDAO dao = ConferenceDAO.getInstance();
		List result = new ArrayList();
		List confList = null;
		try {
			confList = dao.getConferenceByQuery(confName, confType, confRoom,
					confDept, beginDate, endDate, compere, username);
			for (int i = 0; i < confList.size(); i++) {
				Object[] objects = (Object[]) confList.get(i);
				HashMap confMap = new HashMap();
				confMap.put("conId", new Integer(convent(objects[0])));
				confMap.put("conName", convent(objects[1]));
				confMap.put("roomId", convent(objects[2]));
				confMap.put("roomName", convent(objects[3]));
				confMap.put("address", convent(objects[4]));
				confMap.put("typeName", convent(objects[5]));
				confMap.put("beginDate", convent(objects[6]));
				confMap.put("beginTime", convent(objects[7]));
				confMap.put("endDate", convent(objects[8]));
				confMap.put("endTime", convent(objects[9]));
				confMap.put("deptName", convent(objects[10]));
				confMap.put("orgId", convent(objects[11]));
				confMap.put("compere", convent(objects[12]));
				confMap.put("explain", convent(objects[13]));
				confMap.put("content", convent(objects[14]));
				confMap.put("status", GetDictionary
						.getConfStatus(convent(objects[15])));
				confMap.put("content", convent(objects[16]));
				confMap.put("comments", convent(objects[17]));
				result.add(confMap);
			}

			return result;
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}

	public static List getConfList1(String custno, String custname,
			String deptCode, String type, String begindate, String enddate,
			String username) {
		ConferenceDAO dao = ConferenceDAO.getInstance();
		List result = new ArrayList();
		List confList = null;
		try {
			confList = dao.getConferenceByQuery1(custno,custname,deptCode,type,begindate,enddate,username);
			for (int i = 0; i < confList.size(); i++) {
				Object[] objects = (Object[]) confList.get(i);
				HashMap confMap = new HashMap();
				confMap.put("conId", new Integer(convent(objects[0])));
				confMap.put("conName", convent(objects[1]));
				confMap.put("typeName", convent(objects[2]));
				confMap.put("beginDate", convent(objects[3]));
				confMap.put("beginTime", convent(objects[4]));
				confMap.put("endDate", convent(objects[5]));
				confMap.put("endTime", convent(objects[6]));				
				confMap.put("custId", new Integer(convent(objects[7])));
				confMap.put("cutName", convent(objects[8]));
				confMap.put("stuempNo", convent(objects[9]));
				confMap.put("classdeptNo", convent(objects[10]));
				confMap.put("deptName", convent(objects[11]));
				confMap.put("attendSign", convent(objects[12]));
				result.add(confMap);
			}

			return result;
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}
	
	public static List getConfList2(String custno, String custname,
			String deptCode, String type, String begindate, String enddate,
			String username) {
		ConferenceDAO dao = ConferenceDAO.getInstance();
		List result = new ArrayList();
		List confList = null;
		try {
			confList = dao.getConferenceByQuery2(custno,custname,deptCode,type,begindate,enddate,username);
			for (int i = 0; i < confList.size(); i++) {
				Object[] objects = (Object[]) confList.get(i);
				HashMap confMap = new HashMap();			
				confMap.put("custId", new Integer(convent(objects[0])));
				confMap.put("allcount", new Integer(convent(objects[1])));
				confMap.put("shouldcount", new Integer(convent(objects[2])));
				result.add(confMap);
			}

			return result;
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}
	
	public static List getConfList3(String custno, String custname,
			String deptCode, String type, String begindate, String enddate,
			String username) {
		ConferenceDAO dao = ConferenceDAO.getInstance();
		List result = new ArrayList();
		List confList = null;
		try {
			confList = dao.getConferenceByQuery3(custno,custname,deptCode,type,begindate,enddate,username);
			for (int i = 0; i < confList.size(); i++) {
				Object[] objects = (Object[]) confList.get(i);
				HashMap confMap = new HashMap();
				confMap.put("classdeptNo", convent(objects[0]));
				confMap.put("conId", convent(objects[1]));
				confMap.put("allcount", new Integer(convent(objects[2])));
				confMap.put("shouldcount", new Integer(convent(objects[3])));
				result.add(confMap);
			}

			return result;
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}
	
	public static List getConfList4(String custno, String custname,
			String deptCode, String type, String begindate, String enddate,
			String username) {
		ConferenceDAO dao = ConferenceDAO.getInstance();
		List result = new ArrayList();
		List confList = null;
		try {
			confList = dao.getConferenceByQuery4(custno,custname,deptCode,type,begindate,enddate,username);
			for (int i = 0; i < confList.size(); i++) {
				Object[] objects = (Object[]) confList.get(i);
				HashMap confMap = new HashMap();
				confMap.put("conId", new Integer(convent(objects[0])));
				confMap.put("allcount",  new Integer(convent(objects[1])));
				confMap.put("shouldcount",  new Integer(convent(objects[2])));
				confMap.put("latecount",  new Integer(convent(objects[3])));
				result.add(confMap);
			}

			return result;
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}
	
	public static List getConfList5(String custno, String custname,
			String deptCode, String type, String begindate, String enddate,
			String username) {
		ConferenceDAO dao = ConferenceDAO.getInstance();
//		List result = new ArrayList();
		List confList = null;
		try {
			confList = dao.getConferenceByQuery5(custno,custname,deptCode,type,begindate,enddate,username);
//			for (int i = 0; i < confList.size(); i++) {
//				Object[] objects = (Object[]) confList.get(i);
//				HashMap confMap = new HashMap();
//				confMap.put("conId", new Integer(convent(objects[0])));
//				confMap.put("conName", convent(objects[1]));
//				result.add(confMap);
//			}

			return confList;
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
		
	}
	
	public static List getConfList6(String custno, String custname,
			String deptCode, String type, String begindate, String enddate,
			String username) {
		ConferenceDAO dao = ConferenceDAO.getInstance();
//		List result = new ArrayList();
		List deptList = null;
		try {
			deptList = dao.getConferenceByQuery6(custno,custname,deptCode,type,begindate,enddate,username);
			String tempdeptcode ="";
			int count =0;
			if(deptList !=null){
			for (int i = 0; i < deptList.size(); i++) {
				DeptCustForm dc = (DeptCustForm)deptList.get(i);
				if(i>0){
					if(i<deptList.size()-1){
						if(tempdeptcode.equals(dc.getDeptCode())){
							count++;
						}else{
							DeptCustForm tt = new DeptCustForm();
							tt.setDeptCode("count"+tempdeptcode);
							tt.setDeptName("部门出勤率");
							tt.setCustName(String.valueOf(count)+"人");
							deptList.add(i,tt);
							tempdeptcode = dc.getDeptCode();
							count=0;
						}
					}else{
						if(tempdeptcode.equals(dc.getDeptCode())){
							count++;
							DeptCustForm tt = new DeptCustForm();
							tt.setDeptCode("count"+tempdeptcode);
							tt.setDeptName("部门出勤率");
							tt.setCustName(String.valueOf(count)+"人");
							deptList.add(i+1,tt);
							break;
						}else{
							count++;
							DeptCustForm tt = new DeptCustForm();
							tt.setDeptCode("count"+tempdeptcode);
							tt.setDeptName("部门出勤率");
							tt.setCustName(String.valueOf(count)+"人");
							deptList.add(i,tt);
							
							DeptCustForm tt1 = new DeptCustForm();
							tt1.setDeptCode("count"+dc.getDeptCode());
							tt1.setDeptName("部门出勤率");
							tt1.setCustName(String.valueOf(1)+"人");
							deptList.add(i+2,tt1);
							break;
						}
					}
					
				}else{
					if(i!=deptList.size()-1){
						tempdeptcode = dc.getDeptCode();
						count=1;
					}else{
						tempdeptcode = dc.getDeptCode();
						count=1;
						DeptCustForm tt1 = new DeptCustForm();
						tt1.setDeptCode("count"+dc.getDeptCode());
						tt1.setDeptName("部门出勤率");
						tt1.setCustName(String.valueOf(1)+"人");
						deptList.add(i+1,tt1);
						break;
					}
					
				}
			}
			}
			
//			for (int i = 0; i < confList.size(); i++) {
//				Object[] objects = (Object[]) confList.get(i);
//				HashMap confMap = new HashMap();
//				confMap.put("classdeptNo", convent(objects[0]));
//				confMap.put("deptName", convent(objects[1]));
//				result.add(confMap);
//			}

			return deptList;
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
		
	}
	
	public static List getConfList7(String custno, String custname,
			String deptCode, String type, String begindate, String enddate,
			String username) {
		ConferenceDAO dao = ConferenceDAO.getInstance();
		List result = new ArrayList();
		List confList = null;
		try {
			confList = dao.getConferenceByQuery7(custno,custname,deptCode,type,begindate,enddate,username);
			for (int i = 0; i < confList.size(); i++) {
				Object[] objects = (Object[]) confList.get(i);
				HashMap confMap = new HashMap();
				confMap.put("classdeptNo", convent(objects[0]));
				confMap.put("custId", new Integer(convent(objects[1])));
				confMap.put("cutName", convent(objects[2]));
				result.add(confMap);
			}

			return result;
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
		
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ConferenceUtil根据会议编号得到会议内容<br>
	 * Return: TConference<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-5 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public static TConference getConfById(Long confId) {
		ConferenceDAO dao = ConferenceDAO.getInstance();
		try {
			return (TConference) dao
					.findByPrimaryKey(TConference.class, confId);
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}

	/**
	 * 
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ConferenceUtil根据当前日期取得要下发名单的会议<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-5-29 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public static List getAllotAttendeeConfByDate() {
		ConferenceDAO dao = ConferenceDAO.getInstance();
		try {
			return dao.getAllotAttendeeConfByDate();
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}

	private static String convent(Object ss) {
		if (null == ss) {
			return "";
		} else {
			return ss.toString();
		}
	}

	public static List getConfList() {
		ConferenceDAO dao = ConferenceDAO.getInstance();
		return dao.getConfList();
	}
	
	public static List getAvailableConfByUser(String username) {
		ConferenceDAO dao = ConferenceDAO.getInstance();
		List confList = null;
		try {
			confList = dao.getAvailableConfByUser(username);
			return confList;
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}
}
