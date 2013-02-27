package com.kingstargroup.business.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.form.DeviceStatusResult;
import com.kingstargroup.form.Devicefilter;
import com.kingstargroup.form.Deviceservice;
import com.kingstargroup.form.Devicestatus;
import com.kingstargroup.form.MapStateDic;
import com.kingstargroup.form.MapSysDictionary;
import com.kingstargroup.utils.DateUtil;

public class DeviceStatusUtil {

	public static List getDeviceStatus(String devicename, String errreason,
			String devstatus, String errlasttime) {

		Session session = HibernateSessionFactory.currentSession();
		List result_svr = new ArrayList();
		List result_dev = new ArrayList();
		try {

			HashMap dicmap = new HashMap();
			StringBuffer dic = new StringBuffer();
			dic
					.append("from MapSysDictionary a where a.id.dictNo=1 and a.id.dictValue>101 and a.id.dictValue<120");
			Query querydic = session.createQuery(dic.toString());
			List listdic = querydic.list();
			for (int i = 0; i < listdic.size(); i++) {
				MapSysDictionary sysdic = (MapSysDictionary) listdic.get(i);
				dicmap.put(sysdic.getId().getDictValue(), sysdic
						.getDictCaption());
			}

			StringBuffer dicstat = new StringBuffer();
			dicstat.append("from MapStateDic a where a.errornot=1");
			Query querystat = session.createQuery(dicstat.toString());
			List liststat = querystat.list();
			for (int i = 0; i < liststat.size(); i++) {
				MapStateDic statdic = (MapStateDic) liststat.get(i);
				dicmap.put(statdic.getTagcode(), statdic.getStatename());
			}

			StringBuffer str_svr = new StringBuffer("");
			str_svr
					.append(
							" select * from (select t.id as {devstatusresult.id}, t.deviceid as {devstatusresult.deviceid}, t.devicename as {devstatusresult.devicename}, t.devphyid as {devstatusresult.devphyid},")
					.append(
							" t.fdevceid as {devstatusresult.fdevceid}, t.devtypecode as {devstatusresult.devtypecode}, t.ip as {devstatusresult.ip}, t.errstarttime as {devstatusresult.errstarttime},t.errendtime as {devstatusresult.errendtime}, t.errlasttime as {devstatusresult.errlasttime}, '' as {devstatusresult.errlastdate},")
					.append(
							" t.contactname as {devstatusresult.contactname},t.errreason as {devstatusresult.errreason},t.devstatus as {devstatusresult.devstatus},'' as {devstatusresult.statename},s.rcvman as {devstatusresult.rcvman} ")

					.append(
							" from ykt_mon.devicestatus t left join ykt_mon.deviceservice s on t.id=s.devicestatusid and s.dealstatus=1 ")

					.append(" where t.devtypecode='0000' ");

			if (null != devicename && !"".equals(devicename)) {
				str_svr.append("and t.devicename like :devicename ");
			}
			if (null != errreason && !"".equals(errreason)) {
				str_svr.append("and t.errreason=:errreason ");
			}
			if (null != devstatus && !"".equals(devstatus)) {
				str_svr.append("and t.devstatus in (").append(devstatus)
						.append(") ");
			} else {
				str_svr.append("and t.devstatus in (1,2) ");
			}
			str_svr
					.append("and t.errlasttime >:errlasttime and  rownum<1000 order by t.errlasttime desc) a ");
			
			str_svr.append("union all ");
			
			str_svr
			.append(
					" select * from (select t.id as {devstatusresult.id}, t.deviceid as {devstatusresult.deviceid}, t.devicename as {devstatusresult.devicename}, t.devphyid as {devstatusresult.devphyid},")
			.append(
					" t.fdevceid as {devstatusresult.fdevceid}, t.devtypecode as {devstatusresult.devtypecode}, t.ip as {devstatusresult.ip}, t.errstarttime as {devstatusresult.errstarttime},t.errendtime as {devstatusresult.errendtime}, t.errlasttime as {devstatusresult.errlasttime}, '' as {devstatusresult.errlastdate},")
			.append(
					" t.contactname as {devstatusresult.contactname},t.errreason as {devstatusresult.errreason},t.devstatus as {devstatusresult.devstatus},'' as {devstatusresult.statename},s.rcvman as {devstatusresult.rcvman} ")

			.append(
					" from ykt_mon.devicestatus t left join ykt_mon.deviceservice s on t.id=s.devicestatusid and s.dealstatus=1 ")

			.append(" where t.devtypecode<>'0000' ");
		
			if (null != devicename && !"".equals(devicename)) {
				str_svr.append("and t.devicename like :devicename ");
			}
			if (null != errreason && !"".equals(errreason)) {
				str_svr.append("and t.errreason=:errreason ");
			}
			if (null != devstatus && !"".equals(devstatus)) {
				str_svr.append("and t.devstatus in (").append(devstatus)
						.append(") ");
			} else {
				str_svr.append("and t.devstatus in (1,2) ");
			}
			str_svr
					.append("and t.errlasttime >:errlasttime and  rownum<1000 order by t.errlasttime desc) b");
			
			Query query = session.createSQLQuery(str_svr.toString()).addEntity(
					"devstatusresult", DeviceStatusResult.class);
			if (null != devicename && !"".equals(devicename)) {
				query.setString("devicename", "%" + devicename + "%");
			}
			if (null != errreason && !"".equals(errreason)) {
				query.setInteger("errreason", Integer.parseInt(errreason));
			}
			query.setString("errlasttime", errlasttime);
			result_svr = query.list();
			if (result_svr != null && result_svr.size() > 0) {
				for (int i = 0; i < result_svr.size(); i++) {
					DeviceStatusResult m = (DeviceStatusResult) result_svr
							.get(i);
					long lasttime = m.getErrlasttime();
					String errstarttime = m.getErrstarttime();
					String errendtime = m.getErrendtime();
					String statename = String.valueOf(m.getErrreason());
					m.setErrlastdate(DateUtil.FormatSecond(lasttime));
					m.setErrstarttime(DateUtil.FormatTime(errstarttime));
					m.setErrendtime(DateUtil.FormatTime(errendtime));
					m.setStatename((String) dicmap.get(statename));
				}
			}

		} catch (HibernateException e) {
			e.printStackTrace();
		} finally {
			HibernateSessionFactory.closeSession();
		}
		return result_svr;
	}

	public static DeviceStatusResult getDeviceById(String id) {

		Session session = HibernateSessionFactory.currentSession();
		DeviceStatusResult result = null;
		try {

			HashMap dicmap = new HashMap();
			StringBuffer dic = new StringBuffer();
			dic
					.append("from MapSysDictionary a where a.id.dictNo=1 and a.id.dictValue>101 and a.id.dictValue<120");
			Query querydic = session.createQuery(dic.toString());
			List listdic = querydic.list();
			for (int i = 0; i < listdic.size(); i++) {
				MapSysDictionary sysdic = (MapSysDictionary) listdic.get(i);
				dicmap.put(sysdic.getId().getDictValue(), sysdic
						.getDictCaption());
			}

			StringBuffer dicstat = new StringBuffer();
			dicstat.append("from MapStateDic a where a.errornot=1");
			Query querystat = session.createQuery(dicstat.toString());
			List liststat = querystat.list();
			for (int i = 0; i < liststat.size(); i++) {
				MapStateDic statdic = (MapStateDic) liststat.get(i);
				dicmap.put(statdic.getTagcode(), statdic.getStatename());
			}

			StringBuffer str = new StringBuffer("");
			str
					.append(
							" select t.id as {devstatusresult.id}, t.deviceid as {devstatusresult.deviceid}, t.devicename as {devstatusresult.devicename}, t.devphyid as {devstatusresult.devphyid},")
					.append(
							" t.fdevceid as {devstatusresult.fdevceid}, t.devtypecode as {devstatusresult.devtypecode}, t.ip as {devstatusresult.ip}, t.errstarttime as {devstatusresult.errstarttime},t.errendtime as {devstatusresult.errendtime}, t.errlasttime as {devstatusresult.errlasttime}, '' as {devstatusresult.errlastdate},")
					.append(
							" t.contactname as {devstatusresult.contactname},t.errreason as {devstatusresult.errreason},t.devstatus as {devstatusresult.devstatus},'' as {devstatusresult.statename},s.rcvman as {devstatusresult.rcvman} ")

					.append(
							" from ykt_mon.devicestatus t left join ykt_mon.deviceservice s on t.id=s.devicestatusid  and s.dealstatus=1 ")

					.append(" where t.id=:id");
			Query query = session.createSQLQuery(str.toString()).addEntity(
					"devstatusresult", DeviceStatusResult.class);
			;
			query.setString("id", id);
			List list = query.list();
			result = (DeviceStatusResult) list.get(0);

			long lasttime = result.getErrlasttime();
			String errstarttime = result.getErrstarttime();
			String errendtime = result.getErrendtime();
			String statename = String.valueOf(result.getErrreason());
			result.setErrlastdate(DateUtil.FormatSecond(lasttime));
			result.setErrstarttime(DateUtil.FormatTime(errstarttime));
			result.setErrendtime(DateUtil.FormatTime(errendtime));
			result.setStatename((String) dicmap.get(statename));

		} catch (HibernateException e) {
			e.printStackTrace();
		} finally {
			HibernateSessionFactory.closeSession();
		}
		return result;
	}

	public static boolean updateDeviceStatus(String id, long status, String time) {
		Session session = HibernateSessionFactory.currentSession();
		boolean flag = false;
		try {
			Devicestatus dev = (Devicestatus) session.get(Devicestatus.class,
					id);
			dev.setDevstatus(status);
			dev.setErrendtime(time);
			session.update(dev);
			session.flush();
			flag = true;
		} catch (HibernateException e) {
			e.printStackTrace();
		} finally {
			HibernateSessionFactory.closeSession();
		}
		return flag;
	}

	public static boolean saveDeviceFilter(String loginUserName,
			String canceltime, String cancelreason, long deviceid) {
		Session session = HibernateSessionFactory.currentSession();
		boolean flag = false;
		try {
			Devicefilter fliter = new Devicefilter();
			fliter.setDeviceid(deviceid);
			fliter.setFiltertotime(canceltime);
			fliter.setUserid(loginUserName);//
			fliter.setRemark(cancelreason);
			session.save(fliter);
			session.flush();
			flag = true;
		} catch (HibernateException e) {
			e.printStackTrace();
		} finally {
			HibernateSessionFactory.closeSession();
		}
		return flag;
	}

	public static List getServiceList(String id) {
		Session session = HibernateSessionFactory.currentSession();
		List list = null;

		try {
			Query query = session
					.createQuery("from Deviceservice a where a.devicestatusid=:devicestatusid");
			query.setString("devicestatusid", id);
			list = query.list();
			if (list != null) {
				for (int i = 0; i < list.size(); i++) {
					Deviceservice deviceservice = (Deviceservice) list.get(i);
					deviceservice.setRcvtime(DateUtil.FormatTime(deviceservice
							.getRcvtime()));
				}
			}
		} catch (HibernateException e) {
			e.printStackTrace();
		} finally {
			HibernateSessionFactory.closeSession();
		}

		return list;
	}

	public static List stateDictList() {
		Session session = HibernateSessionFactory.currentSession();
		List list = null;

		try {
			Query query = session
					.createQuery("select distinct new com.kingstargroup.form.DeviceResult(101||a.errorcode,a.statename) from MapStateDic a where a.errornot=1 order by 101||a.errorcode");
			list = query.list();
			Query querydic = session
					.createQuery("select distinct new com.kingstargroup.form.DeviceResult(a.id.dictValue,a.dictCaption) from MapSysDictionary a where a.id.dictNo=1 and a.id.dictValue>101 and a.id.dictValue<120 order by a.id.dictValue");
			List listdic = querydic.list();
			list.addAll(listdic);
		} catch (HibernateException e) {
			e.printStackTrace();
		} finally {
			HibernateSessionFactory.closeSession();
		}

		return list;
	}

	public static void saveDeviceService(Deviceservice deviceservice) {
		Session session = HibernateSessionFactory.currentSession();
		try {
			session.save(deviceservice);
			session.flush();
		} catch (HibernateException e) {
			e.printStackTrace();
		} finally {
			HibernateSessionFactory.closeSession();
		}

	}

}
