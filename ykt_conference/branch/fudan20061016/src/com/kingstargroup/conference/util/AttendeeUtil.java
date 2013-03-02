package com.kingstargroup.conference.util;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.apache.log4j.Logger;
import org.hibernate.HibernateException;
import org.hibernate.Transaction;

import com.kingstargroup.conference.common.DateUtilExtend;
import com.kingstargroup.conference.common.SortListColl;
import com.kingstargroup.conference.common.StringUtil;
import com.kingstargroup.conference.dao.AttendeeDAO;
import com.kingstargroup.conference.dao.AttendeeGroupDAO;
import com.kingstargroup.conference.dao.ConferenceDAO;
import com.kingstargroup.conference.dao.DictionaryDAO;
import com.kingstargroup.conference.hibernate.form.TAttendeeGroup;
import com.kingstargroup.conference.hibernate.form.TAttendeeGroupKey;
import com.kingstargroup.conference.hibernate.form.TAttendeeList;
import com.kingstargroup.conference.hibernate.form.TAttendeeListKey;
import com.kingstargroup.conference.hibernate.form.TCifCustomer;
import com.kingstargroup.conference.hibernate.form.TConference;
import com.kingstargroup.conference.hibernate.form.TDelegate;
import com.kingstargroup.conference.hibernate.form.TDevConference;
import com.kingstargroup.conference.hibernate.form.TDevConferenceKey;
import com.kingstargroup.conference.hibernate.form.TInformList;
import com.kingstargroup.conference.hibernate.form.TInformListKey;
import com.kingstargroup.conference.hibernate.form.TPifCard;
import com.kingstargroup.conference.hibernate.form.TPifDevice;
import com.kingstargroup.conference.hibernate.form.TPifDictionary;
import com.kingstargroup.conference.hibernate.form.TTifMeslist;

public class AttendeeUtil extends BasicUtil {
	static Logger log = Logger.getLogger("Businesslog");
	
	
	public static boolean addNoCardNoInfo(int confid,String name,String sex ,String duty ,String dept){
		AttendeeDAO dao = AttendeeDAO.getInstance();
		return dao.addNoCardNoInfo(confid,name,sex,duty,dept);
	}
	
	
	public static  List  findNocardNoInfoByName(String confid ,String   name){
		AttendeeDAO dao = AttendeeDAO.getInstance();
		List result = new ArrayList();
		if ( confid!=null && !"".equals(confid)){
		  result = 	dao.findNocardNoInfoByName(Integer.parseInt(confid),name);
		}
		return result;
	}
	
	
	
	public static void  deleteImpList(String   confid,String custids){
		AttendeeDAO dao = AttendeeDAO.getInstance();
		if ( confid!=null && !"".equals(confid)){
		    	dao.deleteExcelDate(Integer.parseInt(confid),custids);
		}
	
	}
	
	
	
	public static List getImpList(String confid){
		AttendeeDAO dao = AttendeeDAO.getInstance();
		List result  = new ArrayList();
		if ( confid!=null && !"".equals(confid)){
			result =   dao.getImpattend(confid);
		}
		return result;
		
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: GetDictionary根据条件查询人员分组信息<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-6 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public static List getCustList(String custno, String custname, String duty,
			String dept, int confid, List custAllotList) {
		AttendeeGroupDAO dao = AttendeeGroupDAO.getInstance();
		List custList = null;
		List result = new ArrayList();
		try {
			if ("".equals(custno)) {
				custList = dao.getCustInfo("", custname, duty, dept, confid,
						custAllotList);
				
				for (int i = 0, l = custList.size(); i < l; i++) {
					Object[] objects = (Object[]) custList.get(i);
					String dutyName = convent(objects[5]);
					if (i + 1 < l) {
						Object[] objects1 = (Object[]) custList.get(i + 1);
						if (convent(objects[0]).equals(convent(objects1[0]))) {
							// dutyName += ","+convent(objects1[5]);
							i++;
							for (int j = i + 1; j < l; j++) {
								objects1 = (Object[]) custList.get(j);
								if (convent(objects[0]).equals(
										convent(objects1[0]))) {
									// dutyName += ","+convent(objects1[5]);
									i++;
									continue;
								} else {
									break;
								}
							}
						}
					}	

					HashMap confMap = new HashMap();
					confMap.put("cutId", new Integer(convent(objects[0])));
					confMap.put("cutName", convent(objects[1]));
					confMap.put("stuempNo", convent(objects[2]));
					confMap.put("dutyName", convent(objects[3]));
					confMap.put("deptName", convent(objects[4]));
					confMap.put("duty", dutyName);
					// confMap.put("pym",GetCh2Spell.getBeginCharacter(convent(objects[4])));
					confMap.put("pym", convent(objects[1]));
					result.add(confMap);
				}
				
				
			} else {
				String[] custid = custno.split("\r\n");
				for (int j = 0; j < custid.length; j++) {
					if (!"".equals(custid[j].trim())) {
						custList = dao.getCustInfo(custid[j], custname, duty,
								dept, confid, custAllotList);
						for (int i = 0; i < custList.size(); i++) {
							Object[] objects = (Object[]) custList.get(i);
							HashMap confMap = new HashMap();
							confMap.put("cutId", new Integer(
									convent(objects[0])));
							confMap.put("cutName", convent(objects[1]));
							confMap.put("stuempNo", convent(objects[2]));
							confMap.put("dutyName", convent(objects[3]));
							confMap.put("deptName", convent(objects[4]));
							confMap.put("duty", convent(objects[5]));
							// confMap.put("pym",GetCh2Spell.getBeginCharacter(convent(objects[4])));
							confMap.put("pym", convent(objects[1]));
							result.add(confMap);
						}

					}
				}
				
			}

		} catch (HibernateException he) {
			he.printStackTrace();
		} finally {
			closeSession();
		}
		Collections.sort(result, new SortListColl());
		return result;
	}

	public static List getAttendeeList(String physicalno,int con_id ,HashMap timemap) {
		AttendeeGroupDAO dao = AttendeeGroupDAO.getInstance();
		List custList = null;
		List result = new ArrayList();
		try {
			if ("".equals(physicalno)) {
				HashMap confMap = new HashMap();
				result.add(confMap);
			} else {
				String[] physicalno_arr = physicalno.split("\r\n");
				String physicalno_rem = "";
				for (int j = 0; j < physicalno_arr.length; j++) {
					if ((!"".equals(physicalno_arr[j].trim()))&&(physicalno_rem.indexOf(physicalno_arr[j].trim())==-1)) {
						physicalno_rem += physicalno_arr[j].trim()+",";
						custList = dao.getCustInfo(physicalno_arr[j].trim());
						
						for (int i = 0; i < custList.size(); i++) {
							Object[] objects = (Object[]) custList.get(i);
							HashMap confMap = new HashMap();
                            //必须增加判断，如果在会议中已经签到了，则不再显示文本中需要签到的人员信息--gejinfeng,20080624--
							if(SignUtil
							.getSignedOrNot(con_id, new Integer(
									convent(objects[0])).intValue())){
								continue;
							}
									
							confMap.put("cutId", new Integer(
									convent(objects[0])));
							confMap.put("cutType", new Integer(
									convent(objects[1])));
							confMap.put("typeName", convent(objects[2]));
							confMap.put("cutName", convent(objects[3]));
							confMap.put("stuempNo",convent(objects[4]));
							confMap.put("deptNo", convent(objects[5]));
							confMap.put("deptName", convent(objects[6]));
							confMap.put("sCode", convent(objects[7]));
							confMap.put("sName", convent(objects[8]));
							confMap.put("sex", convent(objects[9]));
							confMap.put("dictCaption", convent(objects[10]));
							confMap.put("asignTime", timemap.get(physicalno_arr[j].trim()));
							result.add(confMap);
						}

					}
				}
			}

		} catch (HibernateException he) {
			he.printStackTrace();
		} finally {
			closeSession();
		}
		return result;
	}
	
	public static HashMap gettiemMap(String physicalno,HashMap timemap) {
		
		AttendeeGroupDAO dao = AttendeeGroupDAO.getInstance();
		HashMap newtimemap = new HashMap();
		try {
			if (!"".equals(physicalno)) {
				String[] physicalno_arr = physicalno.split("\r\n");
				String physicalno_rem = "";
				for (int j = 0; j < physicalno_arr.length; j++) {
					if ((!"".equals(physicalno_arr[j].trim()))&&(physicalno_rem.indexOf(physicalno_arr[j].trim())==-1)) {
						physicalno_rem += physicalno_arr[j].trim()+",";
						List custList = dao.getCustInfo(physicalno_arr[j].trim());
						for (int i = 0; i < custList.size(); i++) {
							Object[] objects = (Object[]) custList.get(i);
							newtimemap.put(convent(objects[0]), timemap.get(physicalno_arr[j].trim()));
						}

					}
				}
			}

		} catch (HibernateException he) {
			he.printStackTrace();
		} finally {
			closeSession();
		}
		return newtimemap;
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeUtil取得客户信息放入map<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-17 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public static List getCustListMap(int confid, String custno,
			String custname, String duty, String dept) {
		AttendeeGroupDAO dao = AttendeeGroupDAO.getInstance();
		List custList = null;
		List result = new ArrayList();
		try {
			custList = dao.getCustInfo(confid, custno, custname, duty, dept);
			for (int i = 0, l = custList.size(); i < custList.size(); i++) {
				Object[] objects = (Object[]) custList.get(i);
				String dutyName = convent(objects[3]);
				if (i + 1 < l) {
					Object[] objects1 = (Object[]) custList.get(i + 1);
					if (convent(objects[0]).equals(convent(objects1[0]))) {
						dutyName += "," + convent(objects1[3]);
						i++;
						for (int j = i + 1; j < l; j++) {
							objects1 = (Object[]) custList.get(j);
							if (convent(objects[0])
									.equals(convent(objects1[0]))) {
								dutyName += "," + convent(objects1[3]);
								i++;
								continue;
							} else {
								break;
							}
						}
					}
				}
				HashMap confMap = new HashMap();
				confMap.put("cutId", new Integer(convent(objects[0])));
				confMap.put("cutName", convent(objects[1]));
				confMap.put("stuempNo", convent(objects[2]));
				confMap.put("dutyName", dutyName);
				confMap.put("deptName", convent(objects[4]));
				confMap.put("attendSign", GetDictionary
						.getAttendeeStatus(convent(objects[5])));
				result.add(confMap);
			}
			return result;
		} catch (Exception he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}

	public static List getCustListReplaceMap(int confid, String custno,
			String custname, String duty, String dept) {
		AttendeeGroupDAO dao = AttendeeGroupDAO.getInstance();
		List custList = null;
		List result = new ArrayList();
		try {
			custList = dao.getReplaceCustInfo(confid, custno, custname, duty,
					dept);
			for (int i = 0, l = custList.size(); i < custList.size(); i++) {
				Object[] objects = (Object[]) custList.get(i);
				String dutyName = convent(objects[3]);
				if (i + 1 < l) {
					Object[] objects1 = (Object[]) custList.get(i + 1);
					if (convent(objects[0]).equals(convent(objects1[0]))) {
						dutyName += "," + convent(objects1[3]);
						i++;
						for (int j = i + 1; j < l; j++) {
							objects1 = (Object[]) custList.get(j);
							if (convent(objects[0])
									.equals(convent(objects1[0]))) {
								dutyName += "," + convent(objects1[3]);
								i++;
								continue;
							} else {
								break;
							}
						}
					}
				}
				HashMap confMap = new HashMap();
				confMap.put("cutId", new Integer(convent(objects[0])));
				confMap.put("cutName", convent(objects[1]));
				confMap.put("stuempNo", convent(objects[2]));
				confMap.put("dutyName", dutyName);
				confMap.put("deptName", convent(objects[4]));
				confMap.put("attendSign", GetDictionary
						.getAttendeeStatus(convent(objects[5])));
				result.add(confMap);
			}
			return result;
		} catch (Exception he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}

	public static List getCustListLeaveMap(int confid, String custno,
			String custname, String duty, String dept) {
		AttendeeGroupDAO dao = AttendeeGroupDAO.getInstance();
		List custList = null;
		List result = new ArrayList();
		try {
			custList = dao.getLeaveCustInfo(confid, custno, custname, duty,
					dept);
			for (int i = 0, l = custList.size(); i < custList.size(); i++) {
				Object[] objects = (Object[]) custList.get(i);
				String dutyName = convent(objects[3]);
				if (i + 1 < l) {
					Object[] objects1 = (Object[]) custList.get(i + 1);
					if (convent(objects[0]).equals(convent(objects1[0]))) {
						dutyName += "," + convent(objects1[3]);
						i++;
						for (int j = i + 1; j < l; j++) {
							objects1 = (Object[]) custList.get(j);
							if (convent(objects[0])
									.equals(convent(objects1[0]))) {
								dutyName += "," + convent(objects1[3]);
								i++;
								continue;
							} else {
								break;
							}
						}
					}
				}
				HashMap confMap = new HashMap();
				confMap.put("cutId", new Integer(convent(objects[0])));
				confMap.put("cutName", convent(objects[1]));
				confMap.put("stuempNo", convent(objects[2]));
				confMap.put("dutyName", dutyName);
				confMap.put("deptName", convent(objects[4]));
				confMap.put("attendSign", GetDictionary
						.getAttendeeStatus(convent(objects[5])));
				result.add(confMap);
			}
			return result;
		} catch (Exception he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}

	public static List getCustListMapSPE(int confid, String custno,
			String custname, String duty, String dept, String dlgt) {
		AttendeeGroupDAO dao = AttendeeGroupDAO.getInstance();
		List custList = null;
		List result = new ArrayList();
		try {
			custList = dao.getCustInfoSPE(confid, custno, custname, duty, dept,
					dlgt);
			for (int i = 0, l = custList.size(); i < custList.size(); i++) {
				Object[] objects = (Object[]) custList.get(i);
				String dutyName = convent(objects[3]);
				if (i + 1 < l) {
					Object[] objects1 = (Object[]) custList.get(i + 1);
					if (convent(objects[0]).equals(convent(objects1[0]))) {
						dutyName += "," + convent(objects1[3]);
						i++;
						for (int j = i + 1; j < l; j++) {
							objects1 = (Object[]) custList.get(j);
							if (convent(objects[0])
									.equals(convent(objects1[0]))) {
								dutyName += "," + convent(objects1[3]);
								i++;
								continue;
							} else {
								break;
							}
						}
					}
				}
				HashMap confMap = new HashMap();
				confMap.put("cutId", new Integer(convent(objects[0])));
				confMap.put("cutName", convent(objects[1]));
				confMap.put("stuempNo", convent(objects[2]));
				confMap.put("dutyName", dutyName);
				confMap.put("deptName", convent(objects[4]));
				confMap.put("attendSign", GetDictionary
						.getAttendeeStatus(convent(objects[5])));
				result.add(confMap);
			}
			return result;
		} catch (Exception he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}

	public static List getCustListMaphandA(int confid, String custno,
			String custname, String duty, String dept) {
		AttendeeGroupDAO dao = AttendeeGroupDAO.getInstance();
		List custList = null;
		List result = new ArrayList();
		try {
			custList = dao.getCustInfohandA(confid, custno, custname, duty,
					dept);
			for (int i = 0; i < custList.size(); i++) {
				Object[] objects = (Object[]) custList.get(i);
				HashMap confMap = new HashMap();
				confMap.put("cutId", new Integer(convent(objects[0])));
				confMap.put("cutName", convent(objects[1]));
				confMap.put("stuempNo", convent(objects[2]));
				confMap.put("dutyName", convent(objects[3]));
				confMap.put("deptName", convent(objects[4]));
				confMap.put("attendSign", GetDictionary
						.getAttendeeStatus(convent(objects[5])));
				result.add(confMap);
			}
			return result;
		} catch (Exception he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}

	public static List getCustListMaphandB(int confid, String custno,
			String custname, String duty, String dept) {
		AttendeeGroupDAO dao = AttendeeGroupDAO.getInstance();
		List custList = null;
		List result = new ArrayList();
		try {
			custList = dao.getCustInfohandB(confid, custno, custname, duty,
					dept);
			for (int i = 0; i < custList.size(); i++) {
				Object[] objects = (Object[]) custList.get(i);
				HashMap confMap = new HashMap();
				confMap.put("cutId", new Integer(convent(objects[0])));
				confMap.put("cutName", convent(objects[1]));
				confMap.put("stuempNo", convent(objects[2]));
				confMap.put("dutyName", convent(objects[3]));
				confMap.put("deptName", convent(objects[4]));
				confMap.put("attendSign", GetDictionary
						.getAttendeeStatus(convent(objects[5])));
				result.add(confMap);
			}
			return result;
		} catch (Exception he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}

	/**
	 * 根据选择的人员列表显示要出席会议人员名单 2006-6-12 hjw
	 * 
	 * @param
	 * @return
	 */
	public static List getAttendeeAllotList(List custList) {
		AttendeeDAO dao = AttendeeDAO.getInstance();
		StringBuffer custIds = new StringBuffer();
		for (int i = 0; i < custList.size(); i++) {
			Map custMap = (Map) custList.get(i);
			if (i == custList.size() - 1) {
				custIds.append(custMap.get("custId"));
			} else {
				custIds.append(custMap.get("custId") + ",");
			}
		}
		List custLists = null;
		List result = new ArrayList();
		try {
			custLists = dao.getAttendeeAllotList(custIds.toString());
			for (int i = 0; i < custLists.size(); i++) {
				Object[] objects = (Object[]) custLists.get(i);
				HashMap confMap = new HashMap();
				confMap.put("cutId", new Integer(convent(objects[0])));
				confMap.put("cutName", convent(objects[1]));
				confMap.put("stuempNo", convent(objects[2]));
				confMap.put("dutyName", convent(objects[3]));
				confMap.put("deptName", convent(objects[4]));
				result.add(confMap);
			}
			return result;
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeUtil把指定的人员分组<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-7 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public static boolean attendeeGroup(String groupname, String ids) {
		AttendeeGroupDAO dao = AttendeeGroupDAO.getInstance();
		Transaction t = beginTransaction();
		String[] custids = StringUtil.split(ids, ",");
		try {
			for (int i = 0; i < custids.length; i++) {
				if (dao.existsAttendeeGroup(Integer.parseInt(groupname),
						Integer.parseInt(custids[i]))) {
					continue;
				}
				TAttendeeGroupKey key = new TAttendeeGroupKey();
				key.setCustId(new Integer(custids[i]));
				key.setGroupId(new Integer(groupname));
				TAttendeeGroup group = new TAttendeeGroup(key);
				dao.save(group);
			}
			t.commit();
			return true;
		} catch (HibernateException he) {
			he.printStackTrace();
			t.rollback();
			return false;
		} finally {
			closeSession();
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeUtil根据组编号得到该组的人员列表<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-7 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public static List getCustListByGroupId(int groupid) {
		AttendeeGroupDAO dao = AttendeeGroupDAO.getInstance();
		List custList = null;
		List result = new ArrayList();
		try {
			custList = dao.getCustGroupList(groupid);
			for (int i = 0, l = custList.size(); i < l; i++) {

				Object[] objects = (Object[]) custList.get(i);
				String dutyName = convent(objects[3]);
				if (i + 1 < l) {
					Object[] objects1 = (Object[]) custList.get(i + 1);
					if (convent(objects[0]).equals(convent(objects1[0]))) {
						dutyName += "," + convent(objects1[3]);
						i++;
						for (int j = i + 1; j < l; j++) {
							objects1 = (Object[]) custList.get(j);
							if (convent(objects[0])
									.equals(convent(objects1[0]))) {
								dutyName += "," + convent(objects1[3]);
								i++;
								continue;
							} else {
								break;
							}
						}
					}
				}

				HashMap confMap = new HashMap();
				confMap.put("cutId", new Integer(convent(objects[0])));
				confMap.put("cutName", convent(objects[1]));
				confMap.put("stuempNo", convent(objects[2]));
				confMap.put("duty", dutyName);
				confMap.put("deptName", convent(objects[4]));
				confMap.put("sex", convertgender(objects[5]));
				confMap.put("pym", convent(objects[1]));
				result.add(confMap);
			}
			Collections.sort(result, new SortListColl());
			return result;
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}

	public static List getCustListByGroupIdOnlyOne(int groupid) {
		AttendeeGroupDAO dao = AttendeeGroupDAO.getInstance();
		List custList = null;
		List result = new ArrayList();
		try {
			custList = dao.getCustGroupListOnlyOne(groupid);
			for (int i = 0; i < custList.size(); i++) {
				Object[] objects = (Object[]) custList.get(i);
				HashMap confMap = new HashMap();
				confMap.put("cutId", new Integer(convent(objects[0])));
				confMap.put("cutName", convent(objects[1]));
				confMap.put("stuempNo", convent(objects[2]));
				confMap.put("duty", "");
				confMap.put("deptName", convent(objects[3]));
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

	public static List getCustListByGroupId(int confid, int groupid,
			List attendedList) {
		AttendeeGroupDAO dao = AttendeeGroupDAO.getInstance();
		List custList = null;
		List result = new ArrayList();
		try {
			custList = dao.getCustGroupList(confid, groupid, attendedList);
			for (int i = 0; i < custList.size(); i++) {
				Object[] objects = (Object[]) custList.get(i);
				HashMap confMap = new HashMap();
				confMap.put("cutId", new Integer(convent(objects[0])));
				confMap.put("cutName", convent(objects[1]));
				confMap.put("stuempNo", convent(objects[2]));
				confMap.put("duty", convent(objects[3]));
				confMap.put("deptName", convent(objects[4]));
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

	public static List getCustListByGroupIdExcept(int confid, int groupid,
			String custIds) {
		AttendeeGroupDAO dao = AttendeeGroupDAO.getInstance();
		List custList = null;
		List result = new ArrayList();
		try {
			custList = dao.getCustGroupListExcept(confid, groupid, custIds);
			for (int i = 0, l = custList.size(); i < l; i++) {

				Object[] objects = (Object[]) custList.get(i);
				String dutyName = convent(objects[3]);
				if (i + 1 < l) {
					Object[] objects1 = (Object[]) custList.get(i + 1);
					if (convent(objects[0]).equals(convent(objects1[0]))) {
						// dutyName += ","+convent(objects1[3]);
						i++;
						for (int j = i + 1; j < l; j++) {
							objects1 = (Object[]) custList.get(j);
							if (convent(objects[0])
									.equals(convent(objects1[0]))) {
								// dutyName += ","+convent(objects1[3]);
								i++;
								continue;
							} else {
								break;
							}
						}
					}
				}
				HashMap confMap = new HashMap();
				confMap.put("cutId", new Integer(convent(objects[0])));
				confMap.put("cutName", convent(objects[1]));
				confMap.put("stuempNo", convent(objects[2]));
				confMap.put("duty", dutyName);
				confMap.put("deptName", convent(objects[4]));
				confMap.put("pym", convent(objects[1]));
				result.add(confMap);
			}
			Collections.sort(result, new SortListColl());
			return result;
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}

	/**
	 * 已分配过的人员名单列表
	 * 
	 * @param confId
	 * @param attendedList
	 * @return
	 */
	public static List getAttendedList(int confId, List attendedList) {
		AttendeeGroupDAO dao = AttendeeGroupDAO.getInstance();
		List custList = null;
		List result = new ArrayList();
		try {
			custList = dao.getAttendedList(confId, attendedList);
			for (int i = 0; i < custList.size(); i++) {
				Object[] objects = (Object[]) custList.get(i);
				HashMap confMap = new HashMap();
				confMap.put("cutId", new Integer(convent(objects[0])));
				confMap.put("cutName", convent(objects[1]));
				confMap.put("stuempNo", convent(objects[2]));
				confMap.put("duty", convent(objects[3]));
				confMap.put("deptName", convent(objects[4]));
				confMap.put("pym", convent(objects[1]));
				result.add(confMap);
			}
			Collections.sort(result, new SortListColl());
			return result;
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}

	/**
	 * 已分配过的人员名单列表
	 * 
	 * @param confId
	 * @param attendedList
	 * @return
	 */
	public static List getAllAttendedList(int confId, List attendedList) {
		AttendeeGroupDAO dao = AttendeeGroupDAO.getInstance();
		List custList = null;
		List result = new ArrayList();
		try {
			custList = dao.getAllAttendedList(confId, attendedList);
			for (int i = 0, l = custList.size(); i < l; i++) {
				Object[] objects = (Object[]) custList.get(i);
				String dutyName = convent(objects[3]);
				if (i + 1 < l) {
					Object[] objects1 = (Object[]) custList.get(i + 1);
					if (convent(objects[0]).equals(convent(objects1[0]))) {
						dutyName += "," + convent(objects1[3]);
						i++;
						for (int j = i + 1; j < l; j++) {
							objects1 = (Object[]) custList.get(j);
							if (convent(objects[0])
									.equals(convent(objects1[0]))) {
								dutyName += "," + convent(objects1[3]);
								i++;
								continue;
							} else {
								break;
							}
						}
					}
				}

				HashMap confMap = new HashMap();
				String cutId = convent(objects[0]);
				confMap.put("cutId", cutId);
				confMap.put("cutName", convent(objects[1]));
				confMap.put("stuempNo", convent(objects[2]));
				confMap.put("duty", convent(objects[3]));
				confMap.put("deptName", convent(objects[4]));
				confMap.put("pym", convent(objects[1]));
				if ("".equals(convent(objects[5]))) {
					for (int j = 0; j < attendedList.size(); j++) {
						HashMap map = (HashMap) attendedList.get(j);
						if (map.get("custId").toString().equals(cutId)) {
							if (!"".equals(map.get("delegray").toString())) {
								TDelegate dlg = GetDictionary.getDlgt(map.get(
										"delegray").toString());
								if (null != dlg) {
									confMap.put("delegray", dlg.getDlgtId());
									confMap.put("dlgtName", dlg.getDlgtName());
								} else {
									confMap.put("delegray", "0");
									confMap.put("dlgtName", "");
								}
								TPifDictionary dic = GetDictionary
										.getCustType(map.get("custType")
												.toString());
								if (null != dic) {
									confMap.put("attendeeType", dic.getId()
											.getDictValue());
									confMap.put("dictCaption", dic
											.getDictCaption());
								}
							}
							break;
						}
					}
				} else {
					confMap.put("delegray", convent(objects[5]));
					confMap.put("dlgtName", convent(objects[6]));
					confMap.put("attendeeType", convent(objects[7]));
					confMap.put("dictCaption", convent(objects[8]));
				}
				result.add(confMap);
			}
			Collections.sort(result, new SortListColl());
			return result;
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}

	public static List getFirstAttendedList(int confId) {
		AttendeeGroupDAO dao = AttendeeGroupDAO.getInstance();
		List custList = null;
		List result = new ArrayList();
		try {
			custList = dao.getFirstAttendedList(confId);
			for (int i = 0, l = custList.size(); i < l; i++) {
				Object[] objects = (Object[]) custList.get(i);
				String dutyName = convent(objects[3]);
				if (i + 1 < l) {
					Object[] objects1 = (Object[]) custList.get(i + 1);
					if (convent(objects[0]).equals(convent(objects1[0]))) {
						// dutyName += ","+convent(objects1[3]);
						i++;
						for (int j = i + 1; j < l; j++) {
							objects1 = (Object[]) custList.get(j);
							if (convent(objects[0])
									.equals(convent(objects1[0]))) {
								// dutyName += ","+convent(objects1[3]);
								i++;
								continue;
							} else {
								break;
							}
						}
					}
				}
				HashMap confMap = new HashMap();
				confMap.put("cutId", new Integer(convent(objects[0])));
				confMap.put("cutName", convent(objects[1]));
				confMap.put("stuempNo", convent(objects[2]));
				confMap.put("duty", dutyName);
				confMap.put("deptName", convent(objects[4]));
				confMap.put("delegray", convent(objects[5]));
				confMap.put("dlgtName", convent(objects[6]));
				confMap.put("attendeeType", convent(objects[7]));
				confMap.put("dictCaption", convent(objects[8]));
				confMap.put("pym", convent(objects[1]));
				result.add(confMap);
			}
			Collections.sort(result, new SortListColl());
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
	 * Description: AttendeeUtil从组中删除人员名单<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-7 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public static boolean deleteCustGroup(int groupid, String custids) {
		AttendeeGroupDAO dao = AttendeeGroupDAO.getInstance();
		Transaction t = beginTransaction();
		String[] custs = StringUtil.split(custids, ",");
		try {
			for (int i = 0; i < custs.length; i++) {
				dao.deleteCustGroup(groupid, Integer.parseInt(custs[i]));
			}
			t.commit();
			return true;
		} catch (HibernateException he) {
			he.printStackTrace();
			t.rollback();
			return false;
		} finally {
			closeSession();
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeUtil把人员和设备绑定到会议中，并向通知表中写入人员数据<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-11 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public static boolean attendeeAllot(int confid, String[] deviceids,
			List custList) {
		AttendeeDAO dao = AttendeeDAO.getInstance();
		ConferenceDAO confdao = ConferenceDAO.getInstance();
		// String[] devids = StringUtil.split(deviceids, ",");
		// 会议编号
		Integer conid = new Integer(confid);
		String getDate = DateUtilExtend.getNowDate2();
		String getTime = DateUtilExtend.getNowTime2();
		Transaction t = beginTransaction();
		String custids = "";
		try {
			TConference conf = (TConference) confdao.findByPrimaryKey(
					TConference.class, new Integer(confid));
			// 保存分组人员分配信息
			for (int i = 0; i < custList.size(); i++) {
				Map custMap = (Map) custList.get(i);
				if (i == custList.size() - 1) {
					custids += custMap.get("custId").toString();
				} else {
					custids += custMap.get("custId").toString() + ",";
				}
			}
			dao.deleteAllAttendeeList(confid, custids);
			for (int i = 0; i < custList.size(); i++) {
				Map custMap = (Map) custList.get(i);
				Integer custid = Integer.valueOf(custMap.get("custId")
						.toString());
				Integer delegray = Integer.valueOf("0");
				if (!custMap.get("delegray").equals("")) {
					delegray = Integer.valueOf(custMap.get("delegray")
							.toString());
				}

				String custType = (String) custMap.get("custType");
				if (dao.existAttendee(Integer.parseInt(custid.toString()),
						confid)) {
					continue;
				}
				// 根据客户号取得该客户的卡号
				TPifCard card = dao.getCardNoByCustId(Integer.parseInt(custid
						.toString()));
				TCifCustomer customer = dao.getCustomer(custid);
				TAttendeeListKey key = new TAttendeeListKey();
				key.setConId(conid);
				key.setCustId(custid);
				TAttendeeList attendee = new TAttendeeList(key);
				if (null != card) {
					attendee.setCardNo(card.getCardId());
				} else {
					attendee.setCardNo(new Integer(0));
				}
				attendee.setSendSign("0");// 是否下发，0未下发，1下发
				attendee.setDelSign("0");
				attendee.setAttendSign("00");
				attendee.setAllotDate(getDate);
				attendee.setAllotTime(getTime);
				attendee.setDelegray(delegray);
				attendee.setAttendeeType(custType);
				attendee.setCutName(customer.getCutName());
				attendee.setStuempNo(customer.getStuempNo());
				attendee.setSex(customer.getSex());
				attendee.setDeptName(DictionaryDAO.getInstance().getDeptName(
						customer.getClassdeptNo()));
				dao.save(attendee);
			}
			for (int i = 0; i < custList.size(); i++) {
				Map custMap = (Map) custList.get(i);

				Integer custid = Integer.valueOf(custMap.get("custId")
						.toString());
				if (dao
						.existInform(Integer.parseInt(custid.toString()),
								confid)) {
					continue;
				}
				TInformListKey informkey = new TInformListKey();
				informkey.setConId(conid);
				informkey.setCustId(custid);
				TInformList inform = new TInformList(informkey);
				inform.setInformDate(getDate);
				inform.setInformTime(getTime);
				inform.setInformSign("0");// 是否通知，0未通知，1通知
				dao.save(inform);

			}
			dao.delDevConf(confid);
			for (int j = 0; j < deviceids.length; j++) {
				if (dao.existDevice(Integer.parseInt(deviceids[j].toString()),
						confid)) {
					continue;
				}
				TDevConferenceKey key = new TDevConferenceKey();
				key.setConId(conid);
				key.setDeviceId(new Integer(deviceids[j]));
				TDevConference devconf = new TDevConference(key);
				devconf.setConBegindate(conf.getConBegindate());
				devconf.setConSigntime(conf.getConSigntime());
				devconf.setConBegintime(conf.getConBegintime());
				devconf.setConEndtime(conf.getConEndtime());
				dao.save(devconf);
			}
			t.commit();
			return true;
		} catch (HibernateException he) {
			he.printStackTrace();
			t.rollback();
			return false;
		} catch (Exception e) {
			e.printStackTrace();
			t.rollback();
			return false;
		} finally {
			closeSession();
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeUtil根据会议编号得到通知表里所有参与该会议的人员名单<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-12 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public static List getAttendeeListByConfId(int confid) {
		AttendeeDAO dao = AttendeeDAO.getInstance();
		// List custList = new ArrayList();
		List custList = null;
		List result = new ArrayList();
		try {
			custList = dao.getAttendeeListByConfId(confid);
			// custList = dao.getCustGroupList(groupid);
			for (int i = 0; i < custList.size(); i++) {
				Object[] objects = (Object[]) custList.get(i);
				HashMap confMap = new HashMap();
				confMap.put("cutId", new Integer(convent(objects[0])));
				confMap.put("cutName", convent(objects[1]));
				confMap.put("stuempNo", convent(objects[2]));
				confMap.put("duty_Name", convent(objects[3]));
				confMap.put("deptName", convent(objects[4]));
				confMap.put("pym", convent(objects[1]));
				result.add(confMap);
			}
		
			Collections.sort(result, new SortListColl());
			return result;
		} catch (HibernateException he) {
			he.printStackTrace();
		} finally {
			closeSession();
		}
		return custList;
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeUtil根据会议编号取得该会议分配的设备<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-27 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public static List getDevListByConfId(int confid) {
		AttendeeDAO dao = AttendeeDAO.getInstance();
		List devList = new ArrayList();
		try {
			devList = dao.getDevListByConfid(confid);
		} catch (HibernateException he) {
			he.printStackTrace();
		} finally {
			closeSession();
		}
		return devList;
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeUtil<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-13 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public static boolean attendeeInform(int confid, List custList,
			String informcotents) {
		AttendeeDAO dao = AttendeeDAO.getInstance();
		// 组人员选择的编号列表
		// String[] custids = StringUtil.split(idsgroup + idsquery, ",");
		// 会议编号
		Integer conid = new Integer(confid);
		String getDate = DateUtilExtend.getNowDate2();
		String getTime = DateUtilExtend.getNowTime();
		Transaction t = beginTransaction();
		try {
			// 把要通知的人员名单下发到人员名单列表中去
			for (int i = 0; i < custList.size(); i++) {
				Map custMap = (Map) custList.get(0);
				Integer custid = Integer.valueOf(custMap.get("custId")
						.toString());
				if (dao
						.existInform(Integer.parseInt(custid.toString()),
								confid)) {
					continue;
				}
				TInformListKey informkey = new TInformListKey();
				informkey.setConId(conid);
				informkey.setCustId(custid);
				TInformList inform = new TInformList(informkey);
				inform.setInformDate(getDate);
				inform.setInformTime(getTime);
				inform.setInformSign("0");// 是否通知，0未通知，1通知
				dao.save(inform);
			}
			// 在此处调用和OA通知的接口，把通知内容下发到OA账号中去
			// {通知接口}
			Iterator iter = dao.getAttendeeByConfId(confid).iterator();
			while (iter.hasNext()) {
				TInformList row = (TInformList) iter.next();
				row.setInformSign("1");
				dao.saveOrUpdate(row);
			}

			TConference conf = (TConference) dao.findByPrimaryKey(
					TConference.class, conid);
			conf.setContent(informcotents);
			dao.saveOrUpdate(conf);
			t.commit();
			// new MailSender().run(dao.getAttendeeByConfId(confid));

			return true;
		} catch (HibernateException he) {
			he.printStackTrace();
			t.rollback();
			return false;
		} finally {
			closeSession();
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeUtil向消息队列表插入消息<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-20 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public static boolean addMesListByConfId(int confid) {
		AttendeeDAO dao = AttendeeDAO.getInstance();
		DictionaryDAO dictdao = DictionaryDAO.getInstance();
		StringBuffer datetime = new StringBuffer();
		datetime.append(DateUtilExtend.getNowDate2()).append(
				DateUtilExtend.getNowTime());
		Transaction t = beginTransaction();
		try {
			// 删除已经存在的名单列表
			for (int i = 0; i < 3; i++) {
				deleteMesList(dictdao, dao, confid, datetime.toString());
			}

			// 获取设备列表
			Iterator devIter = dictdao.getDeviceListByConfid(confid).iterator();
			while (devIter.hasNext()) {
				TPifDevice dev = (TPifDevice) devIter.next();
				String devId = dev.getDevphy999Id();

				// 循环5次下发时间段
				for (int i = 0; i < 5; i++) {
					sendTime(dao, confid, datetime.toString(), dev, devId);
				}
				// 添加下发名单消息队列
				for (int i = 0; i < 3; i++) {
					addMesList(dao, confid, dev, devId, datetime.toString());
				}
			}
			Iterator attIter1 = dao.getAttListByConfId(confid).iterator();
			while (attIter1.hasNext()) {
				TAttendeeList attendee = (TAttendeeList) attIter1.next();
				attendee.setSendSign("1");
				dao.save(attendee);
			}
			t.commit();
			return true;
		} catch (Exception e) {
			e.printStackTrace();
			t.rollback();
			return false;
		} finally {
			closeSession();
		}
	}

	private static void deleteMesList(DictionaryDAO dictdao, AttendeeDAO dao,
			int confid, String datetime) throws Exception {
		StringBuffer delMesContent = new StringBuffer();
		// 加入删除已经存在的白名单队列
		delMesContent.append("<CARDID>").append(0).append("</CARDID>").append(
				"<FTFLAG>").append(2).append("</FTFLAG>");
		// 获取设备列表
		Iterator devIter = dictdao.getDeviceListByConfid(confid).iterator();
		while (devIter.hasNext()) {
			TTifMeslist delMesList = new TTifMeslist();
			TPifDevice dev = (TPifDevice) devIter.next();
			String devId = dev.getDevphy999Id();
			// BeanUtils.copyProperties(delMesList, mesList);
			delMesList.setFunid(new Integer(930117));
			delMesList.setLevel(new Integer(1));
			delMesList.setSendcount(new Integer(0));
			delMesList.setMaxSendCnt(new Integer(1));
			delMesList.setDelFlag("0");
			delMesList.setEcode(new Integer(9999));
			delMesList.setStateid(new Integer(1));
			delMesList.setIndt(datetime.toString());
			delMesList.setStartdt("");
			delMesList.setEnddt("");
			delMesList.setEmsg("");
			delMesList.setOutcontent("");
			delMesList.setCardNo(new Integer(0));
			delMesList.setIncontent(delMesContent.toString());
			delMesList.setDeviceId(dev.getSubsystemId());
			delMesList.setDevphy999Id(devId);
			dao.save(delMesList);
		}

	}

	private static void addMesList(AttendeeDAO dao, int confid, TPifDevice dev,
			String devId, String datetime) throws Exception {
		// 获取名单列表
		Iterator attIter1 = dao.getAttListByConfId(confid).iterator();
		while (attIter1.hasNext()) {
			TAttendeeList attendee = (TAttendeeList) attIter1.next();
			TTifMeslist addMesList = new TTifMeslist();
			StringBuffer addMesContent = new StringBuffer();
			if ("0".equals(attendee.getCardNo().toString())) {
				continue;
			}
			addMesContent.append("<CARDID>").append(attendee.getCardNo())
					.append("</CARDID>").append("<FTFLAG>").append(0).append(
							"</FTFLAG>");
			addMesList.setFunid(new Integer(930117));
			addMesList.setLevel(new Integer(2));
			addMesList.setSendcount(new Integer(0));
			addMesList.setMaxSendCnt(new Integer(20));
			addMesList.setDelFlag("0");
			addMesList.setEcode(new Integer(9999));
			addMesList.setStateid(new Integer(1));
			addMesList.setIndt(datetime);
			addMesList.setStartdt("");
			addMesList.setEnddt("");
			addMesList.setEmsg("");
			addMesList.setOutcontent("");
			// BeanUtils.copyProperties(addMesList, mesList);
			addMesList.setIncontent(addMesContent.toString());
			addMesList.setDeviceId(dev.getSubsystemId());
			addMesList.setCardNo(attendee.getCardNo());
			addMesList.setDevphy999Id(devId);
			dao.save(addMesList);
		}

	}

	private static void sendTime(AttendeeDAO dao, int confid, String datetime,
			TPifDevice dev, String dev999id) {
		// 为设备下发时间段
		ConferenceDAO confdao = ConferenceDAO.getInstance();
		TConference conf = (TConference) confdao.findByPrimaryKey(
				TConference.class, new Integer(confid));
		String week = DateUtilExtend.getWeekByDate(conf.getConBegindate()
				.toString());
		String begintime = conf.getConSigntime();
		String endtime = conf.getConEndtime().substring(0, 4);
		TTifMeslist weekMesList = new TTifMeslist();
		StringBuffer weekCont = new StringBuffer();
		weekCont
				.append("<WEEKNO>")
				.append(week)
				.append("</WEEKNO><OUTNUM>1</OUTNUM><T1>")
				.append(begintime)
				.append(endtime)
				.append("FFFFFFFF")
				.append(
						"</T1><T2></T2><T3></T3><T4></T4><T5></T5><T6></T6><T7></T7><T8></T8>");
		weekMesList.setFunid(new Integer(930105));
		weekMesList.setLevel(new Integer(2));
		weekMesList.setSendcount(new Integer(0));
		weekMesList.setMaxSendCnt(new Integer(20));
		weekMesList.setDelFlag("0");
		weekMesList.setEcode(new Integer(9999));
		weekMesList.setStateid(new Integer(1));
		weekMesList.setIndt(datetime.toString());
		weekMesList.setStartdt("");
		weekMesList.setEnddt("");
		weekMesList.setEmsg("");
		weekMesList.setOutcontent("");
		weekMesList.setCardNo(new Integer(0));
		weekMesList.setIncontent(weekCont.toString());
		weekMesList.setDeviceId(dev.getSubsystemId());
		weekMesList.setDevphy999Id(dev999id);
		dao.save(weekMesList);

	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeUtil<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-21 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public static List getAttendeeListBy(int confid, String custno,
			String custname, String dept, String duty) {
		AttendeeDAO dao = AttendeeDAO.getInstance();
		List custList = null;
		List result = new ArrayList();
		try {
			custList = dao.getAttendeeListBy(confid, custno, custname, dept,
					duty);
			for (int i = 0; i < custList.size(); i++) {
				Object[] objects = (Object[]) custList.get(i);
				HashMap confMap = new HashMap();
				confMap.put("cutId", new Integer(convent(objects[0])));
				confMap.put("cutName", convent(objects[1]));
				confMap.put("stuempNo", convent(objects[2]));
				confMap.put("dutyName", convent(objects[3]));
				confMap.put("deptName", convent(objects[4]));
				confMap.put("pym", convent(objects[1]));
				result.add(confMap);
			}
		Collections.sort(result, new SortListColl());
			return result;
		} catch (HibernateException he) {
			return null;
		} finally {
			closeSession();
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeUtil<br>
	 * Return: String<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-5-9 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public static String getUsedDevList(int confid) {
		AttendeeDAO dao = AttendeeDAO.getInstance();
		ConferenceDAO confdao = ConferenceDAO.getInstance();
		StringBuffer devstr = new StringBuffer();
		try {
			TConference conf = (TConference) confdao.findByPrimaryKey(
					TConference.class, new Integer(confid));
			String beginDate = conf.getConBegindate();
			String signTime = conf.getConSigntime();
			String endTime = conf.getConEndtime();
			List devlist = dao.usedDevIdList(beginDate);
			Iterator iter = devlist.iterator();
			while (iter.hasNext()) {
				Object[] dev = (Object[]) iter.next();
				String devsignTime = dev[4].toString();
				String devendTime = dev[3].toString();
				// 判断双双时间是否在对方之间
				if (((DateUtilExtend.timeDiff2(signTime, devsignTime) < 0) && (DateUtilExtend
						.timeDiff2(signTime, devendTime) > 0))
						|| ((DateUtilExtend.timeDiff2(endTime, devsignTime) < 0) && (DateUtilExtend
								.timeDiff2(endTime, devendTime) > 0))) {
					devstr.append(GetDictionary.getDev999IdByDevId(Integer
							.parseInt(dev[0].toString()))
							+ ",");
					continue;
				}
				if (((DateUtilExtend.timeDiff2(devsignTime, signTime) < 0) && (DateUtilExtend
						.timeDiff2(devendTime, signTime) > 0))
						|| ((DateUtilExtend.timeDiff2(devsignTime, endTime) < 0) && (DateUtilExtend
								.timeDiff2(devendTime, endTime) > 0))) {
					devstr.append(GetDictionary.getDev999IdByDevId(Integer
							.parseInt(dev[0].toString()))
							+ ",");
					continue;
				}
			}
			return devstr.toString();
		} catch (Exception he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}

	/**
	 * 判断是否存在有未下发成功的流水，true为存在有未下发成功的流水，false为没有 2006-6-7 hjw
	 * 
	 * @param
	 * @return
	 */
	public static boolean getMesListIfSucceed(int confid) {
		AttendeeDAO attdao = AttendeeDAO.getInstance();
		ConferenceDAO confdao = ConferenceDAO.getInstance();
		String beginDate = "";
		try {
			TConference conf = (TConference) confdao.findByPrimaryKey(
					TConference.class, new Integer(confid));
			beginDate = conf.getConBegindate();
			if ("0".equals(attdao.getMesListIfSucceed(confid, beginDate))) {
				return false;
			} else {
				return true;
			}
		} catch (HibernateException he) {
			he.printStackTrace();
			return false;
		} finally {
			closeSession();
		}
	}

	public static boolean ifSendBySucceed(int confid) {
		AttendeeDAO dao = AttendeeDAO.getInstance();
		try {
			if ("0".equals(dao.ifSendBySucceed(confid))) {
				return false;
			} else {
				return true;
			}
		} catch (Exception e) {
			return false;
		} finally {
			closeSession();
		}
	}

	public static List getCustListByConfId(int confid) {
		AttendeeDAO dao = AttendeeDAO.getInstance();
		try {
			return dao.getCustListByConfId(confid);
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
			return ss.toString().trim();
		}
	}

	public static String convertgender(Object ss) {
		if (null == ss) {
			return "";
		} else {
			if ("1".equals(convent(ss))) {
				return "男";
			} else if ("2".equals(convent(ss))) {
				return "女";
			} else {
				return "";
			}

		}
	}
	
	public static String sexchange(Object ss) {
		if (null == ss) {
			return "";
		} else {
			if ("男".equals(convent(ss))) {
				return "1";
			} else if ("女".equals(convent(ss))) {
				return "2";
			} else {
				return "";
			}

		}
	}
	
	public static synchronized   boolean ImpExcelDate(List list,int confid,String cmd){
		AttendeeDAO dao = AttendeeDAO.getInstance();
		ConferenceDAO confdao = ConferenceDAO.getInstance();
		// String[] devids = StringUtil.split(deviceids, ",");
		// 会议编号
		Integer conid = new Integer(confid);
		String getDate = DateUtilExtend.getNowDate2();
		String getTime = DateUtilExtend.getNowTime2();
		Transaction t = beginTransaction();
		try {
			if("del".equals(cmd)){
			dao.deleteExcelDate(confid,"all");
			for(int i=1;i<list.size();i++){
				String[]  row = (String[])list.get(i);
				TAttendeeListKey key = new TAttendeeListKey();
				key.setConId(conid);
				key.setCustId(new Integer(-(i)));
				TAttendeeList attendee = new TAttendeeList(key);
				attendee.setSendSign("0");// 是否下发，0未下发，1下发
				attendee.setDelSign("0");
				attendee.setAttendSign("00");
				attendee.setAllotDate(getDate);
				attendee.setAllotTime(getTime);
				attendee.setCutName(row[0]);
				attendee.setReplacerDuty(row[2]);
				attendee.setSex(sexchange(row[1]));
				attendee.setDeptName(row[3]);
				dao.save(attendee);
			 }
			}
			if("add".endsWith(cmd)){
			  int minNo =	dao.findMinDate(confid);
			  for(int i=1;i<list.size();i++){
					String[]  row = (String[])list.get(i);
					TAttendeeListKey key = new TAttendeeListKey();
					key.setConId(conid);
					key.setCustId(new Integer(-(i)+minNo));
					TAttendeeList attendee = new TAttendeeList(key);
					attendee.setSendSign("0");// 是否下发，0未下发，1下发
					attendee.setDelSign("0");
					attendee.setAttendSign("00");
					attendee.setAllotDate(getDate);
					attendee.setAllotTime(getTime);
					attendee.setCutName(row[0]);
					attendee.setReplacerDuty(row[2]);
					attendee.setSex(sexchange(row[1]));
					attendee.setDeptName(row[3]);
					dao.save(attendee);
				 }
			}
			t.commit();
			return true;
	} catch (HibernateException he) {
		he.printStackTrace();
		t.rollback();
		return false;
	} catch (Exception e) {
		e.printStackTrace();
		t.rollback();
		return false;
	} finally {
		closeSession();
	}
	}

}
