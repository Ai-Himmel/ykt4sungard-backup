/**
 * 
 */
package com.kingstargroup.ecard.hibernate.tradedetail;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.hibernate.util.ResultPage;
import com.kingstargroup.ecard.util.DateUtil;
import com.liferay.portal.service.persistence.BasePersistence;

/**
 * @author hjw
 * 
 */
public class GateHisTradeDetailPersistence extends BasePersistence {

	/**
	 * Description
	 * 
	 * @param cardId
	 * @param beginDate
	 * @param endDate
	 * @param page
	 * @param size
	 * @return
	 * @throws DBSystemException
	 */
	public ResultPage getGateHisTradeDetailsByDate(
			String cardId, 
			String beginDate,
			String endDate, 
			int page, 
			int size)
			throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			// accId = "1000000000326835";
			Query query = null;
			Query countQuery = null;
			/*
			 * 
			 */
			query = s.getNamedQuery("GateHisTradelogSQL");
			countQuery = s.getNamedQuery("GateHisTradelogCountSQL");
			query.setInteger("cardNo", Integer.parseInt(cardId));
			query.setString("startDate", beginDate);
			query.setString("endDate", endDate);

			countQuery.setInteger("cardNo", Integer.parseInt(cardId));
			countQuery.setString("startDate", beginDate);
			countQuery.setString("endDate", endDate);
			ResultPage result = new ResultPage(query, page, size);
			int totalRecords = ((Integer) countQuery.uniqueResult()).intValue();
			int quotient = totalRecords / size;
			int remainder = totalRecords % size;
			if (remainder == 0 && quotient != 0) {
				result.setTotalPage(quotient);
			} else {
				result.setTotalPage(quotient + 1);
			}
			return result;
			// return new ResultPage(query, page, size);
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}finally{
			closeSession(s);
		}
	}

	/**
	 * Method name: getCKHisTradeDetailsByDate<br>
	 * Description: 海事考勤<br>
	 * Return: ResultPage<br>
	 * Args:
	 * 
	 * @param stuempNo
	 *            Args:
	 * @param beginDate
	 *            Args:
	 * @param endDate
	 *            Args:
	 * @param page
	 *            Args:
	 * @param size
	 *            Args:
	 * @return Args:
	 * @throws DBSystemException
	 *             Modify History: <br>
	 *             操作类型 操作人 操作时间 操作内容<br>
	 *             ======================================<br>
	 *             创建 何林青 Mar 12, 2008 <br>
	 * @author 何林青
	 * @version
	 * @since 1.0
	 */
	public ResultPage getCKHisTradeDetailsByDate(String stuempNo,
			String beginDate, String endDate, int page, int size)
			throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			// accId = "1000000000326835";
			Query query = null;
			Query countQuery = null;
			/*
			 * 
			 */
			query = s.getNamedQuery("CheckTTLogSQL");
			countQuery = s.getNamedQuery("CheckTTLogCountSQL");
			query.setString("stuempNo", stuempNo);
			query.setString("startDate", beginDate);
			query.setString("endDate", endDate);

			countQuery.setString("stuempNo", stuempNo);
			countQuery.setString("startDate", beginDate);
			countQuery.setString("endDate", endDate);
			ResultPage result = new ResultPage(query, page, size);
			int totalRecords = ((Integer) countQuery.uniqueResult()).intValue();
			int quotient = totalRecords / size;
			int remainder = totalRecords % size;
			if (remainder == 0 && quotient != 0) {
				result.setTotalPage(quotient);
			} else {
				result.setTotalPage(quotient + 1);
			}
			return result;
			// return new ResultPage(query, page, size);
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally {
			closeSession(s);
		}
	}

	public int getCKHisTradeDetailsSizeByDate(String stuempNo,
			String beginDate, String endDate) throws DBSystemException {
		Session s = null;
		try {
			// accId = "1000000000326835";
			s = openSession();
			Query countQuery = null;

			countQuery = s.getNamedQuery("CheckTTLogCountSQL");
			countQuery.setString("stuempNo", stuempNo);
			countQuery.setString("startDate", beginDate);
			countQuery.setString("endDate", endDate);
			int totalRecords = ((Integer) countQuery.uniqueResult()).intValue();

			return totalRecords;
			// return new ResultPage(query, page, size);
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally {
			closeSession(s);
		}
	}
	public List getCheckAttSerial(String beginDate,String endDate,int cardid) throws DBSystemException {	
		
		Session session = null;		
		try {
			session = openSession();
			StringBuffer hsql = new StringBuffer();			
			hsql.append(" select deviceid,devicename,custid,custname,transdate,transtime from (")
				.append(" select seri.deviceid,dev.devicename,seri.custid,cust.custname,seri.transdate,seri.transtime ")
				.append(" from ykt_cur.t_doordtl seri,ykt_cur.t_customer cust,ykt_cur.t_device dev where seri.custid=cust.custid")
				.append(" and seri.deviceid=dev.deviceid")
				.append(" and dev.devusage=1004 and seri.cardno=:cardid and seri.transdate>=:begindate and seri.transdate<=:enddate)")
                    .append(" order by transdate desc,transtime desc")
                    ;
			SQLQuery q = session.createSQLQuery(hsql.toString());
			System.out.println("chkquery---"+hsql.toString());
			
			q.setInteger("cardid", cardid);		
			q.setString("begindate", beginDate);
			q.setString("enddate", endDate);
			
			q.addScalar("deviceid",Hibernate.INTEGER);
			q.addScalar("devicename",Hibernate.STRING);
			q.addScalar("custid",Hibernate.INTEGER);
			q.addScalar("custname",Hibernate.STRING);
			q.addScalar("transdate",Hibernate.STRING);
			q.addScalar("transtime",Hibernate.STRING);
			
			List seriinfo = q.list();
			List result = new ArrayList();
			if (seriinfo!=null){
				for (int i = 0; i < seriinfo.size(); i++) {
					Object[] objects = (Object[]) seriinfo.get(i);
					HashMap serialMap = new HashMap();
					serialMap.put("devid", objects[0]);
					serialMap.put("devname", objects[1]);
					serialMap.put("custid", objects[2]);
					serialMap.put("custname", objects[3]);
					serialMap.put("attdate", objects[4]);
					serialMap.put("atttime", objects[5]);
					result.add(serialMap);
				}
				return result;				
			}else{
				return null;
			}
		} catch (HibernateException ex) {			
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		}finally{			
			closeSession(session);
		}
	}
	
public List getTdquerystat(String begindate,String enddate,String classno,String stuempno,String custname) throws DBSystemException {	
/**
 * Session session = null;		
		try {
			session = openSession();
			StringBuffer hsql = new StringBuffer();			
			hsql.append("select dp.deptname as classname,seri.stuempno,seri.custname,count(distinct seri.transdate) as count ")
				.append("from ykt_cur.t_doordtl seri,ykt_cur.t_device dev,ykt_cur.t_customer cust left join ykt_cur.t_dept dp on cust.deptcode=dp.deptcode ")
				.append("where seri.deviceid=dev.deviceid and dev.devusage=1005 and seri.custid=cust.custid ");
				if(!"".equals(begindate)){
					hsql.append("and seri.transdate>=:begindate ");
				}
				if(!"".equals(enddate)){
					hsql.append("and seri.transdate<=:enddate ");
				}
				if(!"".equals(classno)){
					hsql.append("and dp.deptname like :classno ");
				}
				if(!"".equals(stuempno)){
					hsql.append("and seri.stuempno like :stuempno ");
				}
				if(!"".equals(custname)){
					hsql.append("and seri.custname like :custname ");
				}
			
				hsql.append("group by dp.deptname,seri.stuempno,seri.custname order by dp.deptname,seri.stuempno");
				
			SQLQuery q = session.createSQLQuery(hsql.toString());
			System.out.println("chkquerystat_td---"+hsql.toString());
			
			if(!"".equals(begindate)){
				q.setString("begindate", begindate);	
			}
			if(!"".equals(enddate)){
				q.setString("enddate", enddate);	
			}
			if(!"".equals(classno)){
				q.setString("classno", "%"+classno+"%");	
			}
			if(!"".equals(stuempno)){
				q.setString("stuempno", "%"+stuempno+"%");	
			}
			if(!"".equals(custname)){
				q.setString("custname", "%"+custname+"%");	
			}

			
			q.addScalar("classname",Hibernate.STRING);
			q.addScalar("stuempno",Hibernate.STRING);
			q.addScalar("custname",Hibernate.STRING);
			q.addScalar("count",Hibernate.INTEGER);
			
			List seriinfo = q.list();
			
			List result = new ArrayList();
			if (seriinfo!=null){
				for (int i = 0; i < seriinfo.size(); i++) {
					Object[] objects = (Object[]) seriinfo.get(i);
					HashMap serialMap = new HashMap();
					serialMap.put("classname", objects[0]);
					serialMap.put("stuempno", objects[1]);
					serialMap.put("custname", objects[2]);
					serialMap.put("count", objects[3]);
					result.add(serialMap);
				}
				return result;				
			}else{
				return null;
			}				
		} catch (HibernateException ex) {			
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		}finally{			
			closeSession(session);
		}
 * 
 */
	
	Session session = null;		
	try {
		session = openSession();
		StringBuffer hsql = new StringBuffer();			
		hsql.append("select cust.classname,seri.stuempno,seri.custname,seri.transdate,seri.transtime,seri.deviceid,dev.devusage,dev.areacode,cust.sex ")
		.append("from ykt_cur.t_doordtl seri,ykt_cur.t_device dev,ykt_cur.t_customer cust ")
		.append("where seri.deviceid=dev.deviceid and (dev.devusage=1005 or dev.devusage=1006) and seri.custid=cust.custid ");
		if(!"".equals(begindate)){
			hsql.append("and seri.transdate>=:begindate ");
		}
		if(!"".equals(enddate)){
			hsql.append("and seri.transdate<=:enddate ");
		}
		if(!"".equals(classno)){
			hsql.append("and cust.classname like :classno ");
		}
		if(!"".equals(stuempno)){
			hsql.append("and seri.stuempno like :stuempno ");
		}
		if(!"".equals(custname)){
			hsql.append("and seri.custname like :custname ");
		}
	
		hsql.append("order by cust.classname,seri.stuempno,seri.transdate,dev.devusage,seri.transtime");
		
	SQLQuery q = session.createSQLQuery(hsql.toString());
	System.out.println("chkquerystat_td---"+hsql.toString());
	
	if(!"".equals(begindate)){
		q.setString("begindate", begindate);	
	}
	if(!"".equals(enddate)){
		q.setString("enddate", enddate);	
	}
	if(!"".equals(classno)){
		q.setString("classno", "%"+classno+"%");	
	}
	if(!"".equals(stuempno)){
		q.setString("stuempno", "%"+stuempno+"%");	
	}
	if(!"".equals(custname)){
		q.setString("custname", "%"+custname+"%");	
	}

	q.addScalar("classname",Hibernate.STRING);
	q.addScalar("stuempno",Hibernate.STRING);
	q.addScalar("custname",Hibernate.STRING);
	q.addScalar("transdate",Hibernate.STRING);
	q.addScalar("transtime",Hibernate.STRING);
	q.addScalar("deviceid",Hibernate.INTEGER);
	q.addScalar("devusage",Hibernate.INTEGER);
	q.addScalar("areacode",Hibernate.STRING);
	q.addScalar("sex",Hibernate.INTEGER);
	
	List seriinfo = q.list();
	List result = new ArrayList();
	
	Object curClassname = null;
	Object curStuempno = null;
	Object curCustname = null;
	Object transdate = null;
	String sex = null;
	
	int count=0;
	int valiCount=0;
	String startTime = null;
	String endTime = null;
	
	Object areaCode = null;
	Boolean isSameArea = true; 
	
	if (seriinfo!=null){
		for (int i = 0; i < seriinfo.size(); i++) {
			Object[] objects = (Object[]) seriinfo.get(i);
			if(!objects[1].equals(curStuempno)){
				if(i>0){
					//将统计好的数据存入MAP中
					HashMap serialMap = new HashMap();
					serialMap.put("classname", curClassname);
					serialMap.put("stuempno", curStuempno);
					serialMap.put("custname", curCustname);
					serialMap.put("count", count);
					serialMap.put("valiCount", valiCount);
					result.add(serialMap);
					
					//重新初始化相关参数
					count=0;
				    valiCount=0;
					startTime = null;
					endTime = null;
					areaCode = null;
					isSameArea = true; 
				}
				//提取当前体锻流水中有用的参数
				count++;
				curClassname = objects[0];
				curStuempno = objects[1];
				curCustname =  objects[2];
				transdate = objects[3];
				areaCode = objects[7];
				sex = objects[8].toString();
				
				//当前流水如果在设备体锻-起始考勤机上刷卡，则为体锻起始时间
				if((objects[6]+"").equals("1005")){
					startTime = objects[4]+"";
				}
				//当前流水如果在设备体锻-结束考勤机上刷卡，则为体锻结束时间
				if((objects[6]+"").equals("1006")){
					endTime = objects[4]+"";
				}
			}else {
				if(objects[3].equals(transdate)){
					
					//取当天体锻-起始考勤机上最后一次刷卡时间为起始时间
					//取当天体锻-结束考勤机上第一次刷卡时间为结束时间
					if((objects[7]+"").equals(areaCode)){
						if((objects[6]+"").equals("1005")){
							startTime = objects[4]+"";
						}
						if((objects[6]+"").equals("1006") && endTime==null){
							endTime = objects[4]+"";
						}
					}else {
						isSameArea = false;
					}
					
				}else {
					//计算有效体锻次数
					if(startTime!=null && endTime!=null && isSameArea && isValidity(startTime,endTime,sex,null)){
						valiCount++;
					}
					
					//从新初始化起始、结束刷卡时间
					startTime = null;
					endTime = null;
					
					count++;
					transdate = objects[3];
					//当前流水如果在设备体锻-起始考勤机上刷卡，则为体锻起始时间
					if((objects[6]+"").equals("1005")){
						startTime = objects[4]+"";
					}
					//当前流水如果在设备体锻-结束考勤机上刷卡，则为体锻结束时间
					if((objects[6]+"").equals("1006")){
						endTime = objects[4]+"";
					}
				}
				
			}
			
		}
		//将最后统计好的数据存入MAP中
		HashMap serialMap = new HashMap();
		serialMap.put("classname", curClassname);
		serialMap.put("stuempno", curStuempno);
		serialMap.put("custname", curCustname);
		serialMap.put("count", count);
		serialMap.put("valiCount", valiCount);
		result.add(serialMap);
		
			return result;				
		}else{
			return null;
		}				
	} catch (HibernateException ex) {			
		_log.error(ex);			
		throw new DBSystemException(ex.getMessage());
	}finally{			
		closeSession(session);
	}
}

public List getCheckAttSerial_td(String beginDate,String endDate,int cardid) throws DBSystemException {	
	
	Session session = null;		
	try {
		session = openSession();
		StringBuffer hsql = new StringBuffer();			
		hsql.append("select seri.transdate,seri.transtime,seri.deviceid,dev.devusage,dev.areacode,cust.sex ")
			.append("from ykt_cur.t_doordtl seri,ykt_cur.t_device dev,ykt_cur.t_card card,ykt_cur.t_customer cust ")
			.append("where seri.deviceid=dev.deviceid and (dev.devusage=1005 or dev.devusage=1006) and seri.custid=card.custid and seri.custid=cust.custid ")
			.append("and card.cardno=:cardid and seri.transdate>=:begindate and seri.transdate<=:enddate " )
			.append("order by seri.transdate,dev.devusage,seri.transtime");
		SQLQuery q = session.createSQLQuery(hsql.toString());
		System.out.println("chkquery_td---"+hsql.toString());
		
		q.setInteger("cardid", cardid);		
		q.setString("begindate", beginDate);
		q.setString("enddate", endDate);
		
		q.addScalar("transdate",Hibernate.STRING);
		q.addScalar("transtime",Hibernate.STRING);
		q.addScalar("deviceid",Hibernate.INTEGER);
		q.addScalar("devusage",Hibernate.INTEGER);
		q.addScalar("areacode",Hibernate.STRING);
		q.addScalar("sex",Hibernate.INTEGER);
		
		List seriinfo = q.list();
		List result = new ArrayList();
		
		String sex = null;
		String transdate = null;
		
		String squtime = "——";
		String isValidity = "无效"; 
		String startTime = null;
		String endTime = null;
		
		String areaCode = null;
		Boolean isSameArea = true; 
		
		if (seriinfo!=null){
			for (int i = 0; i < seriinfo.size(); i++) {
				Object[] objects = (Object[]) seriinfo.get(i);
				sex = objects[5]+"";
				if(!(objects[0]+"").equals(transdate)){
					if(i>0){
						HashMap serialMap = new HashMap();
						serialMap.put("squtime", squtime);
						serialMap.put("transtime", DateUtil.formatStr2Str(startTime)+" - "+DateUtil.formatStr2Str(endTime));
						if(startTime!=null && endTime!=null && isSameArea){
							if(isValidity(startTime,endTime,sex,serialMap)){
								isValidity = "有效";
							}
						}
						serialMap.put("transdate", DateUtil.String2Date(transdate,"yyyyMMdd"));
						serialMap.put("isValidate", isValidity);
						result.add(serialMap);
						
						 squtime = "——";
						 isValidity = "无效";
						 startTime = null;
						 endTime = null;
						 areaCode = null;
						 isSameArea = true; 
					}
					
					areaCode = objects[4]+"";
					transdate = objects[0]+"";
					
					if((objects[3]+"").equals("1005")){
						startTime = objects[1]+"";
					}
					if((objects[3]+"").equals("1006")){
						endTime = objects[1]+"";
					}
					
				}else {
					if((objects[4]+"").equals(areaCode)){
						if((objects[3]+"").equals("1005")){
							startTime = objects[1]+"";
						}
						if((objects[3]+"").equals("1006") && endTime==null){
							endTime = objects[1]+"";
						}
					}else {
						isSameArea = false;
					}
					
				}
				
			}
			
			HashMap serialMap = new HashMap();
			serialMap.put("squtime", squtime);
			serialMap.put("transtime", DateUtil.formatStr2Str(startTime)+" - "+DateUtil.formatStr2Str(endTime));
			if(startTime!=null && endTime!=null && isSameArea){
				if(isValidity(startTime,endTime,sex,serialMap)){
					isValidity = "有效";
				}
			}
			serialMap.put("transdate", DateUtil.String2Date(transdate,"yyyyMMdd"));
			serialMap.put("isValidate", isValidity);
			result.add(serialMap);
			return result;				
		}else{
			return null;
		}
	} catch (HibernateException ex) {			
		_log.error(ex);			
		throw new DBSystemException(ex.getMessage());
	}finally{			
		closeSession(session);
	}
}


private Boolean isValidity(String startTime, String endTime, String sex,HashMap serialMap) {
	 SimpleDateFormat df = new SimpleDateFormat("HHmmss");
	 try {
		 Date start = df.parse(startTime);
		   Date end =df.parse(endTime);
		   long l=end.getTime()-start.getTime();
		   long min=((l/(60*1000)));
		   long s=(l/1000-min*60);
		   if(min>=0 && s>=0){
			   if(serialMap!=null){
				   serialMap.put("squtime", min+"分"+s+"秒");
			   }
			   long spuS = min*60+s;
			   if(sex.equals("1") && spuS<=300){
				   return true;
			   }
			   if(sex.equals("2") && spuS<=330){
				   return true;
			   }
		   }else{
			   return false;
		   }
			   
	 } catch (Exception e) {
		 return false;
	}
	 return false;
}

	private static final Log _log = LogFactory
			.getLog(GateHisTradeDetailPersistence.class);
}
