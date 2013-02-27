package com.kingstargroup.action.bgAnalysis;

/**
 * <p>
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: ServiceAnalysisThread.java
 * Description: 服务检查线程
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				2006-11-10   何林青    服务检查线程
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */
import java.util.Iterator;
import java.util.List;

import org.apache.log4j.Logger;
import org.apache.xml.utils.FastStringBuffer;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;
import org.hibernate.Transaction;

import com.kingstargroup.action.serverAnalysis.MonitorDBUtils;
import com.kingstargroup.action.serverAnalysis.MonitorHttpUtils;
import com.kingstargroup.commons.AnalyzeThreadInterface;
import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.form.MapAlertTable;
import com.kingstargroup.form.MapAnalysisPoint;
import com.kingstargroup.form.MapContactMonitorTable;
import com.kingstargroup.form.MapContactTable;
import com.kingstargroup.form.MapFathersetsTable;
import com.kingstargroup.form.MapParamTable;
import com.kingstargroup.form.MapServiceException;
import com.kingstargroup.form.MapServiceExceptionKey;
import com.kingstargroup.form.MapServiceTable;
import com.kingstargroup.form.Monitors;
import com.kingstargroup.utils.CommonSendMailUtil;
import com.kingstargroup.utils.CommonSendSMGUtil;
import com.kingstargroup.utils.DateUtil;
import com.kingstargroup.utils.GetApplicationResources;
import com.kingstargroup.utils.StringUtil;

public class ServiceAnalysisThread extends Thread implements
		AnalyzeThreadInterface {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(ServiceAnalysisThread.class);

	private boolean requestStop = false;

	private String recordTime = "";

	// default analysis is to analysis all from
	private String startTime = "20050101000000";

	private String endTime = DateUtil.getNow();

	// default analysis cycle is one hour
	private double cycle = 1.0;

	// inteval param
	private int doubleCycle = 0;

	// alarm contact
	private String contactName = "";

	// record the record of analysis result
	private int mailRecord = 0;

	// whether to record
	private boolean recordOrNot = true;

	// whether to mail
	private boolean mailOrNot = false;

	// whether to SMG
	private boolean smgOrNot = false;

	// mail content' bufferString
	private FastStringBuffer buffer = null;

	// SMG content's Sting
	private String SmgMessage = "";

	// phone number list with delimeter ";"
	private String phoneNumber = "";

	// phone contact name list with delimeter ";"

	private String phoneName = "";

	// mail address list with delimeter ";"
	private String mailList = "";

	// mail contact name list with delimeter ";"
	private String mailName = "";

	private int accelateParam = 0;

	/*
	 * (non-Javadoc)
	 * 
	 * @see java.lang.Runnable#run()
	 */
	public void run() {
		while (!requestStop) {
			buffer = new FastStringBuffer(100);
			mailRecord = 0;
			anaylize();
		}
		logger.info("$$$$$$$$$$$$$$$$服务分析线程停止运行$$$$$$$$$$$$$$$$$$$$$"); //$NON-NLS-1$
	}

	public void initParam() {
		if (logger.isInfoEnabled()) {
			logger.info("**************服务分析线程初始化**************"); //$NON-NLS-1$
		}
		try {
			Session session = HibernateSessionFactory.currentSession();
			Query queryTime = session
					.createQuery("from MapAnalysisPoint as point where point.analysisname=:analysisName");
			queryTime.setString("analysisName", "SERVICE_EXCEPTION");
			Iterator iterTime = queryTime.iterate();
			if (iterTime.hasNext()) {
				MapAnalysisPoint mapAnalysisPoint = (MapAnalysisPoint) iterTime
						.next();
				this.startTime = mapAnalysisPoint.getAnalysispoint();
			}

			Query queryCycle = session
					.createQuery("from MapParamTable as param where param.parameter=:paramRefer");
			queryCycle.setString("paramRefer", "ServiceExceptionCycle");
			List listParam = queryCycle.list();
			Iterator iterParam = listParam.iterator();
			if (iterParam.hasNext()) {
				MapParamTable mapParamTable = (MapParamTable) iterParam.next();
				if ("ServiceExceptionCycle"
						.equals(mapParamTable.getParameter())) {
					this.cycle = mapParamTable.getValue().doubleValue();
				}

			}
			String s = String.valueOf(cycle * 60);
			this.doubleCycle = Integer.parseInt(s.substring(0, s.indexOf('.')));

			if (!"20050101000000".equals(this.startTime)) {
				this.endTime = DateUtil.getNewTime(startTime, doubleCycle);
			} else {
				this.endTime = DateUtil.getNow();
				this.startTime = DateUtil
						.getNewTime(this.endTime, -doubleCycle);
			}

		} catch (HibernateException e) {
			logger.error("服务分析线程初始化失败！", e); //$NON-NLS-1$

		} finally {
			HibernateSessionFactory.closeSession();
		}

		if (logger.isInfoEnabled()) {
			logger.info("**************服务分析线程初始化成功**************"); //$NON-NLS-1$
		}
	}

	/**
	 * @param session
	 */
	private void getParameter(Session session) {
		phoneNumber = "";
		phoneName = "";
		mailList = "";
		contactName = "";
		recordOrNot = true;
		mailOrNot = false;
		smgOrNot = false;
		// monitor param
		Query queryOrNot = session
				.createQuery("from MapAlertTable alert where alert.parameter='ServiceException'");
		Iterator iterOrNot = queryOrNot.iterate();
		if (iterOrNot.hasNext()) {
			MapAlertTable alertTable = (MapAlertTable) iterOrNot.next();
			if ("0".equals(alertTable.getNote().toString())) {
				recordOrNot = false;
			}
			if ("1".equals(alertTable.getMailalert().toString())) {
				mailOrNot = true;
			}
			if ("1".equals(alertTable.getPhonealert().toString())) {
				smgOrNot = true;
			}
		}
		Query queryCycle = session
				.createQuery("from MapParamTable as param where param.parameter=:paramRefer");
		queryCycle.setString("paramRefer", "ServiceExceptionCycle");
		List listParam = queryCycle.list();
		Iterator iterParam = listParam.iterator();
		if (iterParam.hasNext()) {
			MapParamTable mapParamTable = (MapParamTable) iterParam.next();
			if ("ServiceExceptionCycle".equals(mapParamTable.getParameter())) {
				this.cycle = mapParamTable.getValue().doubleValue();
			}

		}
		String s = String.valueOf(cycle * 60);
		this.doubleCycle = Integer.parseInt(s.substring(0, s.indexOf('.')));
		// contact list
		Query queryContact = session
				.createQuery("from MapContactMonitorTable monitor where monitor.monitorno='SERVICE_EXCEPTION'");
		List listContact = queryContact.list();
		Iterator iterContact = listContact.iterator();
		while (iterContact.hasNext()) {
			MapContactMonitorTable contactMonitor = (MapContactMonitorTable) iterContact
					.next();
			String nowDayTime = DateUtil.getNow("HHmmss");

			Query queryPhone = session
					.createQuery("from MapContactTable a where a.contactname=:contactName "
							+ "and a.starttime<=:starttime and a.endtime>=:endtime");
			queryPhone
					.setString("contactName", contactMonitor.getContactname());
			queryPhone.setString("starttime", nowDayTime);
			queryPhone.setString("endtime", nowDayTime);
			Iterator iterPhone = queryPhone.iterate();
			if (iterPhone.hasNext()) {
				MapContactTable contactTable = (MapContactTable) iterPhone
						.next();
				int dayofWeek = DateUtil.getDayofWeek();
				if ((1 == dayofWeek)
						&& ("1".equals(contactTable.getWeekdays().substring(6,
								7)))) {
					if (!"".equals(contactTable.getCellphone())) {
						phoneNumber += contactTable.getCellphone() + ";";
						phoneName += contactTable.getContactname() + ";";
					}
					if (!"".equals(contactTable.getEmail())) {
						mailList += contactTable.getEmail() + ";";
						mailName += contactMonitor.getContactname() + ";";
					}
					if (!"".equals(contactMonitor.getContactname())) {
						contactName += contactMonitor.getContactname() + ",";
					}
				} else if ("1".equals(contactTable.getWeekdays().substring(
						dayofWeek - 2, dayofWeek - 1))) {
					if (!"".equals(contactTable.getCellphone())) {
						phoneNumber += contactTable.getCellphone() + ";";
						phoneName += contactTable.getContactname() + ";";
					}
					if (!"".equals(contactTable.getEmail())) {
						mailList += contactTable.getEmail() + ";";
						mailName += contactMonitor.getContactname() + ";";
					}
					if (!"".equals(contactMonitor.getContactname())) {
						contactName += contactMonitor.getContactname() + ",";
					}
				}
			}
		}
		if (!"".equals(contactName)) {
			contactName = contactName
					.substring(0, contactName.lastIndexOf(","));
		}
	}

	public void anaylize() {
		Transaction tx = null;
		try {
			Session session = HibernateSessionFactory.currentSession();
			tx = session.beginTransaction();
			this.accelateParam = Integer
					.parseInt(BgMonitor.getIntance().accelateParam);
			endTime = DateUtil.getNewTime(endTime, accelateParam * 60);
			if (logger.isInfoEnabled()) {
				logger
						.info("服务分析线程开始分析时间:" + DateUtil.getNow("yyyy/MM/dd/HH:mm:ss")); //$NON-NLS-1$
			}
			if (1 != DateUtil.checkTimeSequence(endTime, DateUtil.getNow())) {
				if (logger.isInfoEnabled()) {
					logger.info("服务分析线程分析时间段：" + startTime + " -- " + endTime);
				}

			} else {
				endTime = DateUtil.getNow();
				if (logger.isInfoEnabled()) {
					logger.info("服务分析线程分析时间段：" + startTime + " -- " + endTime);
				}
			}

			getParameter(session);
			recordTime = DateUtil.getNow();
			Query query = session
					.createSQLQuery(
							"select {service.*} from ykt_mon.map_service_table as service with ur")
					.addEntity("service", MapServiceTable.class);
			List list = query.list();
			Iterator iter = list.iterator();
			while (iter.hasNext()) {
				MapServiceTable service = (MapServiceTable) iter.next();
				// 是否down机
				if ("web".equals(service.getServiceType())) {
					// web服务
					if (!MonitorHttpUtils.checkHttpClient(service.getUrl())) {
						// down
						if (true == recordOrNot) {
							MapServiceException mapservice = new MapServiceException();
							MapServiceExceptionKey mapservicekey = new MapServiceExceptionKey();
							mapservicekey.setAnalysistime(recordTime);
							mapservicekey.setServiceId(service.getServiceId());
							mapservice.setId(mapservicekey);
							mapservice.setServerId(service.getServerId());
							mapservice.setServerName(service.getServerName());
							mapservice.setServiceType(service.getServiceType());
							mapservice.setStatus("down");
							mapservice.setContactname(contactName);
							mapservice.setErrorcode(Short.valueOf("108"));
							session.save(mapservice);
						}
					}
				} else if (service.getServiceType().startsWith("db")) {
					// db服务器
					String db = service.getServiceType().substring(
							service.getServiceType().indexOf(":") + 1);
					String ip = service.getIp();
					String port = service.getPort().toString();
					String dbname = service.getDbname();
					String username = service.getUsername();
					String password = service.getPassword();
					if (!MonitorDBUtils.checkDBstatus(db, ip, port, dbname,
							username, password)) {
						MapServiceException mapservice = new MapServiceException();
						MapServiceExceptionKey mapservicekey = new MapServiceExceptionKey();
						mapservicekey.setAnalysistime(recordTime);
						mapservicekey.setServiceId(service.getServiceId());
						mapservice.setId(mapservicekey);
						mapservice.setServerId(service.getServerId());
						mapservice.setServerName(service.getServerName());
						mapservice.setServiceType(service.getServiceType());
						mapservice.setStatus("down");
						mapservice.setContactname(contactName);
						mapservice.setErrorcode(Short.valueOf("109"));
						session.save(mapservice);
					}

				} else if ("drtp".equals(service.getServiceType())) {
					// drtp服务器
					String ip = service.getIp();
					Query nameQuery = session
							.createQuery("from MapFathersetsTable a where a.ip=:ip ");
					nameQuery.setString("ip", ip);
					List listname = nameQuery.list();
					Iterator itername = listname.iterator();
					if (itername.hasNext()) {
						MapFathersetsTable set = (MapFathersetsTable) itername
								.next();
						String hostname = set.getHostname();
						Query statusQuery = session
								.createQuery("from Monitors a where a.host=:hostname and category='APP' and entry='drtp'");
						statusQuery.setString("hostname", hostname);
						List listStatus = statusQuery.list();
						Iterator iterStatus = listStatus.iterator();
						if (iterStatus.hasNext()) {
							Monitors monitor = (Monitors) iterStatus.next();
							if (!"......ok".equals(monitor.getValuestr())) {
								MapServiceException mapservice = new MapServiceException();
								MapServiceExceptionKey mapservicekey = new MapServiceExceptionKey();
								mapservicekey.setAnalysistime(recordTime);
								mapservicekey.setServiceId(service
										.getServiceId());
								mapservice.setId(mapservicekey);
								mapservice.setServerId(service.getServerId());
								mapservice.setServerName(service
										.getServerName());
								mapservice.setServiceType(service
										.getServiceType());
								mapservice.setStatus("down");
								mapservice.setContactname(contactName);
								mapservice.setErrorcode(Short.valueOf("110"));
								session.save(mapservice);
							}
						}
					}

				} else if ("".equals(service.getServiceType())) {
					// 其他 有待扩充
				}

				// mailRecord++;
				// if (!"".equals(mailList)) {
				// String device_name = "";
				// device_name = DeviceNameDictionary.getInstance().get(
				// rcvdtl.getId().getDeviceId()).trim();
				// Query queryCustomer = session
				// .createSQLQuery(
				// "select a.cut_name as cutName "
				// + "from YKT_CUR.T_CIF_CUSTOMER a,YKT_CUR.T_PIF_CARD b "
				// + "where a.cut_id=b.COSUMER_ID and b.CARD_ID=:cutId with ur")
				// .addScalar("cutName", Hibernate.STRING);
				// queryCustomer.setInteger("cutId", rcvdtl.getId()
				// .getCardNo().intValue());
				// List listCust = queryCustomer.list();
				// String cust_name = "";
				// if (listCust.size() > 0) {
				// cust_name = listCust.get(0).toString().trim();
				// }
				// buffer.append(StringUtil.solidStringGenerate(rcvdtl.getId()
				// .getDeviceId(), device_name, rcvdtl.getId()
				// .getCardNo(), cust_name, rcvdtl.getId()
				// .getSerialNo().toString(), rcvdtl.getId()
				// .getTxDate(), rcvdtl.getId().getTxTime(),
				// "SERVICE_EXCEPTION.BLACK_ERR"));
				// }
			}
			session.flush();
			session.clear();

			// record timepoint analysis
			Object tempAnalysis = session.get(MapAnalysisPoint.class,
					"SERVICE_EXCEPTION");
			MapAnalysisPoint analysisPoint = null;
			if (tempAnalysis == null) {
				analysisPoint = new MapAnalysisPoint();
				analysisPoint.setAnalysisname("SERVICE_EXCEPTION");
				analysisPoint.setAnalysispoint(endTime);
				session.save(analysisPoint);
			} else {
				analysisPoint = (MapAnalysisPoint) tempAnalysis;
				analysisPoint.setAnalysispoint(endTime);
				session.update(analysisPoint);
			}

			tx.commit();
			// mail
			sendMail();
			// SMG
			sendSMG();

		} catch (HibernateException e) {
			logger.error("服务分析线程出现以下异常：", e); //$NON-NLS-1$
			if (tx != null) {
				tx.rollback();
			}
		} catch (Exception e) {
			logger.error("服务分析线程出现以下异常：", e); //$NON-NLS-1$
			if (tx != null) {
				tx.rollback();
			}
		} finally {
			HibernateSessionFactory.closeSession();
		}

		// sleep thread follows the setting
		try {
			long sleepTime = Long.parseLong(String.valueOf(doubleCycle * 1000))
					- DateUtil.getIntervalTime(DateUtil.getNow(), recordTime);
			if (logger.isInfoEnabled()) {
				logger
						.info("服务线程分析结束进入休眠状态!"
								+ " 休眠开始时间:" + DateUtil.getNow("yyyy/MM/dd/HH:mm:ss") + ", 休眠时间:" + sleepTime + " 毫秒"); //$NON-NLS-1$
			}
			this.startTime = this.endTime;
			this.endTime = DateUtil.getNewTime(this.endTime, doubleCycle);
			if (sleepTime <= 0) {
				sleep(600000);
			} else {
				sleep(sleepTime);
			}
		} catch (InterruptedException e) {
			logger.error("服务分析线程出现以下异常：可能被强行停止！ ", e); //$NON-NLS-1$
		} catch (Exception e) {
			logger.error("服务分析线程出现以下异常：可能被强行停止！ ", e); //$NON-NLS-1$
		}
	}

	public void terminate() {
		// TODO Auto-generated method stub
		if (this.isAlive()) {
			logger.warn("服务分析线程状态被请求，此时线程状态：活动线程!"); //$NON-NLS-1$
			this.requestStop = true;
		} else {
			logger.warn("服务分析线程状态被请求，此时线程状态：死亡线程!"); //$NON-NLS-1$
			this.destroy();

		}
	}

	public boolean isTerminate() {
		// TODO Auto-generated method stub
		return this.isAlive();
	}

	public void sendMail() {
		// TODO Auto-generated method stub
		if ((true == mailOrNot) && (!"".equals(mailList))
				&& (0 != buffer.size())) {
			if (logger.isInfoEnabled()) {
				logger.info("服务分析线程发送邮件给联系人:" + contactName);
			}
			String tmpStr = "";
			if (buffer.size() > 5000) {
				tmpStr = buffer.getString(0, 5000);
			}
			tmpStr = buffer.toString();

			String[] tempList = null;
			String[] nameList = null;
			tempList = mailList.split(";");
			nameList = mailName.split(";");
			for (int i = 0; i < tempList.length; i++) {
				if (!"".equals(tempList[i])) {
					CommonSendMailUtil.sendMail(GetApplicationResources
							.getInstance().getString(
									"com.kingstar.MonitorSys.SUBJECT_SERIAL"),
									nameList[i], tempList[i], StringUtil
									.wholeMailGenerate(nameList[i], DateUtil
											.reFormatTime(recordTime),
											mailRecord, tmpStr,
											"SERVICE_EXCEPTION"));
				}
			}
		}
	}

	public void sendSMG() {
		// TODO Auto-generated method stub
		if ((true == smgOrNot) && (!"".equals(phoneNumber)) && mailRecord > 0) {
			if (logger.isInfoEnabled()) {
				logger.info("服务分析线程发送短信给联系人:" + contactName);
			}

			String[] tempList = null;
			String[] nameList = null;
			tempList = phoneNumber.split(";");
			nameList = phoneName.split(";");
			// String tempPhone = phoneNumber.substring(0, phoneNumber
			// .lastIndexOf(";"));
			for (int i = 0; i < tempList.length; i++) {
				if (!"".equals(tempList[i])) {
					SmgMessage = StringUtil.wholeSMGGenerate(nameList[i],
							DateUtil.reFormatTime(recordTime), mailRecord,
							"SERVICE_EXCEPTION");
					CommonSendSMGUtil.sendSMG(tempList[i], SmgMessage);
				}
			}

		}
	}
}
