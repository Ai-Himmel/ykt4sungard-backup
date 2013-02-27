package com.kingstargroup.business.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.form.Devicefilter;
import com.kingstargroup.form.Devicestatus;
import com.kingstargroup.utils.DateUtil;

public class DeviceStatusUtil {

	public static List getDeviceStatus(String devstatus, String errlasttime) {

 		Session session = HibernateSessionFactory.currentSession();
		List tempresult = new ArrayList();
		List result = new ArrayList();
		try {
			StringBuffer str = new StringBuffer("");
			str
					.append(
							" select  new Map( t.id as id , t.deviceid as deviceid , t.devicename as devicename , t.devphyid as  devphyid ,")
					.append(
							" t.fdevceid as fdevceid  , t.devtype as devtype , t.ip as ip , t.errstarttime as errstarttime , t.errlasttime as errlasttime ,")
					.append(
							" t.contactname as contactname ,t.errreason  as errreason ,t.devstatus as devstatus ,m.statename  as statename ) ")
							
					.append(" from Devicestatus t ,MapStateDic m ")
					
					.append(" where  t.errreason = m.tagcode and   t.devstatus=:devstatus  and    t.errlasttime >:errlasttime ");
			Query query = session.createQuery(str.toString());
			query.setInteger("devstatus", Integer.parseInt(devstatus));
			query.setString("errlasttime", errlasttime);
			tempresult = query.list();
			if (tempresult != null && tempresult.size() > 0) {
				for (int i = 0; i < tempresult.size(); i++) {
					Map m = (Map) tempresult.get(i);
					long lasttime = ((Long) m.get("errlasttime")).longValue();
					m.put("errlasttime", DateUtil.FormatSecond(lasttime));
					m.put("errstarttime", DateUtil.FormatTime((String) m.get("errstarttime")));
					result.add(m);
				}
			}
		} catch (HibernateException e) {
			e.printStackTrace();
		} finally {
			HibernateSessionFactory.closeSession();
		}
		return result;
	}

	public static Map getDeviceById(String id) {
		
		Session session = HibernateSessionFactory.currentSession();
		Map  result = new HashMap();
		try{
			StringBuffer str = new StringBuffer("");
			str.append(" select new Map( t.id as id , t.deviceid as deviceid , t.devicename as devicename , t.devphyid as  devphyid ,")
					.append(
							" t.fdevceid as fdevceid  , t.devtype as devtype , t.ip as ip , t.errstarttime as errstarttime , t.errlasttime as errlasttime ,")
					.append(
							" t.contactname as contactname ,t.errreason  as errreason ,t.devstatus as devstatus ,m.statename  as statename ) ")
							
					.append(" from Devicestatus t ,MapStateDic m ")
					
					.append(" where  t.errreason = m.tagcode  and    t.id=:id");
			Query query = session.createQuery(str.toString());
			      query.setString("id", id);
			List list = query.list();      
			result = (Map)list.get(0);
			long lasttime = ((Long) result.get("errlasttime")).longValue();
			result.put("errlasttime", DateUtil.FormatSecond(lasttime));
			result.put("errstarttime", DateUtil.FormatTime((String) result.get("errstarttime")));
		}catch(HibernateException e){
			e.printStackTrace();
		}finally{
			HibernateSessionFactory.closeSession();
		}
		return result;
	}
	
	public static boolean updateDeviceStatus(String id,long status){
		Session session = HibernateSessionFactory.currentSession();
		boolean flag=false;
		try{
			Devicestatus dev =	(Devicestatus)session.get(Devicestatus.class, id);
			dev.setDevstatus(status);
			session.update(dev);
			session.flush();
			flag = true;
		}catch(HibernateException e){
			e.printStackTrace();
		}finally{
			HibernateSessionFactory.closeSession();
		}
		return flag;
	}
	
	public static boolean updateDevice(String canceltime,String  cancelreason,long deviceid){
		Session session = HibernateSessionFactory.currentSession();
		boolean flag=false;
		try{
			Devicefilter fliter = new Devicefilter();
			fliter.setDeviceid(deviceid);
			fliter.setFiltertotime(canceltime);
			fliter.setUserid("");//
			fliter.setRemark(cancelreason);
			session.save(fliter);
			session.flush();
			flag=true;
		}catch(HibernateException e){
			e.printStackTrace();
		}finally{
			HibernateSessionFactory.closeSession();
		}
		return flag;
	}
	
	
	
	
}
