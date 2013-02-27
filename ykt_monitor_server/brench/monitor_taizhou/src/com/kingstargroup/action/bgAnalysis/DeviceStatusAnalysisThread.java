package com.kingstargroup.action.bgAnalysis;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: DeviceStatusAnalysisThread.java
 * Description: 设备状态监控
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				 2005-10-31    何林青             设备状态监控
 * 修改					2006-07-20     何林青    			修改日志记录方式
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */
import org.apache.log4j.Logger;
import java.util.Iterator;
import java.util.List;
import org.apache.xml.utils.FastStringBuffer;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;
import org.hibernate.Transaction;

import com.kingstargroup.commons.AnalyzeThreadInterface;
import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.form.MapAlertTable;
import com.kingstargroup.form.MapAnalysisPoint;
import com.kingstargroup.form.MapDeviceTable;
import com.kingstargroup.form.MapDeviceTableKey;
import com.kingstargroup.form.MapParamTable;
import com.kingstargroup.form.TMifDevmonitor;
import com.kingstargroup.form.TPifDevice;

import com.kingstargroup.utils.CommonSendMailUtil;
import com.kingstargroup.utils.CommonSendSMGUtil;
import com.kingstargroup.utils.DB2TimeUtil;
import com.kingstargroup.utils.DateUtil;
import com.kingstargroup.utils.GetApplicationResources;
import com.kingstargroup.utils.StringUtil;

public class DeviceStatusAnalysisThread extends Thread implements
		AnalyzeThreadInterface {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(DeviceStatusAnalysisThread.class);

	// flag of stop this thread
	private boolean requestStop = false;

	// record analysis time
	private String recordTime = "";

	// default analysis is to analysis all from
	public String startTime = "20050101000000";

	// default analysis is to analysis to now
	public String endTime = DateUtil.getNow();

	// default analysis cycle is one hour
	private double cycle = 10.0;

	// inteval param
	private int doubleCycle = 0;

	private double difftime = 5.5;

	private int diffCycle = 330;

	String systemTime = "";

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
	}

	public void initParam() {
		if (logger.isInfoEnabled()) {
			logger.info("**************设备状态分析线程初始化**************"); //$NON-NLS-1$
		}
		try {
			Session session = HibernateSessionFactory.currentSession();
			Query queryTime = session
					.createQuery("from MapAnalysisPoint as point where point.analysisname=:analysisName");
			queryTime.setString("analysisName", "DEVICE_EXCEPTION");
			Iterator iterTime = queryTime.iterate();
			if (iterTime.hasNext()) {
				MapAnalysisPoint mapAnalysisPoint = (MapAnalysisPoint) iterTime
						.next();
				this.startTime = mapAnalysisPoint.getAnalysispoint();
			}
			Query queryCycle = session
					.createQuery("from MapParamTable as param where param.parameter=:paramRefer or param.parameter=:paramRefer1");
			queryCycle.setString("paramRefer", "HeartInterval");
			queryCycle.setString("paramRefer1", "TimeInterval");
			Iterator iterParam = queryCycle.iterate();
			while (iterParam.hasNext()) {
				MapParamTable mapParamTable = (MapParamTable) iterParam.next();
				if ("HeartInterval".equals(mapParamTable.getParameter())) {
					this.cycle = mapParamTable.getValue().doubleValue();
				}
				if ("TimeInterval".equals(mapParamTable.getParameter())) {
					this.difftime = mapParamTable.getValue().doubleValue();
				}

			}
			String s = String.valueOf(cycle * 60);
			this.doubleCycle = Integer.parseInt(s.substring(0, s.indexOf('.')));
			String d = String.valueOf(difftime * 60);
			this.diffCycle = Integer.parseInt(d.substring(0, d.indexOf('.')));
			if (!"20050101000000".equals(this.startTime)) {
				this.endTime = DateUtil.getNow();
				this.startTime = DateUtil.getNewTime(endTime, -1 * doubleCycle);
			}

		} catch (HibernateException e) {
			logger.error("设备状态分析线程初始化失败！", e); //$NON-NLS-1$
		} finally {
			HibernateSessionFactory.closeSession();
		}
		if (logger.isInfoEnabled()) {
			logger.info("**************设备状态分析线程初始化成功**************"); //$NON-NLS-1$
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
				.createQuery("from MapAlertTable alert where alert.parameter='DeviceAbnormal'");
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
				.createQuery("from MapParamTable as param where param.parameter=:paramRefer or param.parameter=:paramRefer1");
		queryCycle.setString("paramRefer", "HeartInterval");
		queryCycle.setString("paramRefer1", "TimeInterval");
		Iterator iterParam = queryCycle.iterate();
		while (iterParam.hasNext()) {
			MapParamTable mapParamTable = (MapParamTable) iterParam.next();
			if ("HeartInterval".equals(mapParamTable.getParameter())) {
				this.cycle = mapParamTable.getValue().doubleValue();
			}
			if ("TimeInterval".equals(mapParamTable.getParameter())) {
				this.difftime = mapParamTable.getValue().doubleValue();
			}

		}
		String s = String.valueOf(cycle * 60);
		this.doubleCycle = Integer.parseInt(s.substring(0, s.indexOf('.')));
		String d = String.valueOf(difftime * 60);
		this.diffCycle = Integer.parseInt(d.substring(0, d.indexOf('.')));

		// // contact list
		// Query queryContact = session
		// .createQuery("from MapContactMonitorTable monitor where
		// monitor.monitorno='DEVICE_EXCEPTION'");
		// Iterator iterContact = queryContact.iterate();
		// while (iterContact.hasNext()) {
		// MapContactMonitorTable contactMonitor = (MapContactMonitorTable)
		// iterContact
		// .next();
		// String nowDayTime = DateUtil.getNow("HHmmss");
		//
		// Query queryPhone = session
		// .createQuery("from MapContactTable a where
		// a.contactname=:contactName and a.starttime<=:starttime and
		// a.endtime>=:endtime");
		// queryPhone.setString("contactName", contactMonitor
		// .getContactname());
		// queryPhone.setString("starttime", nowDayTime);
		// queryPhone.setString("endtime", nowDayTime);
		// Iterator iterPhone = queryPhone.iterate();
		// if (iterPhone.hasNext()) {
		// MapContactTable contactTable = (MapContactTable) iterPhone
		// .next();
		// int dayofWeek = DateUtil.getDayofWeek();
		// if ((1 == dayofWeek)
		// && ("1".equals(contactTable.getWeekdays()
		// .substring(6, 7)))) {
		// phoneNumber += contactTable.getCellphone() + ";";
		// mailList += contactTable.getEmail() + ";";
		// contactName += contactMonitor.getContactname() + ",";
		// } else if ("1".equals(contactTable.getWeekdays().substring(
		// dayofWeek - 2, dayofWeek - 1))) {
		// phoneNumber += contactTable.getCellphone() + ";";
		// mailList += contactTable.getEmail() + ";";
		// contactName += contactMonitor.getContactname() + ",";
		// }
		// }
		// }
	}

	public void anaylize() {
		if (logger.isInfoEnabled()) {
			logger.info("设备状态分析线程开始分析任务"); //$NON-NLS-1$
		}
		Transaction tx = null;
		try {
			Session session = HibernateSessionFactory.currentSession();
			tx = session.beginTransaction();
			this.accelateParam = Integer
					.parseInt(BgMonitor.getIntance().accelateParam);
			endTime = DateUtil.getNewTime(endTime, accelateParam * 60);
			if (logger.isInfoEnabled()) {
				logger
						.info("设备状态分析线程开始分析时间:" + DateUtil.getNow("yyyy/MM/dd/HH:mm:ss")); //$NON-NLS-1$
			}
			if (1 > DateUtil.checkTimeSequence(endTime, DateUtil.getNow())) {
				if (logger.isInfoEnabled()) {
					logger
							.info("设备状态分析线程分析时间段：" + startTime + " -- "
									+ endTime);
				}
			} else {
				endTime = DateUtil.getNow();
				if (logger.isInfoEnabled()) {
					logger
							.info("设备状态分析线程分析时间段：" + startTime + " -- "
									+ endTime);
				}
			}
			getParameter(session);
			// analysis time record
			recordTime = DateUtil.getNow();
			BgMonitor
					.monitorThreadStatusReport(
							"com.kingstargroup.action.bgAnalysis.DeviceStatusAnalysisThread",
							"设备状态分析线程", DateUtil.getNow("yyyy/MM/dd/HH:mm:ss"),
							String.valueOf(this.doubleCycle), "运行中...");
			// Query query = session.getNamedQuery("AbDeviceResult");
			systemTime = DB2TimeUtil.getSysDate(0);
			systemTime = DateUtil.getNewTime(systemTime, -diffCycle);
			Query query = session
					.createSQLQuery(
							"select {dev.*} from YKT_CUR.T_PIF_DEVICE dev,YKT_CUR.T_MIF_DEVMONITOR a "
									+ "where a.device_id=dev.device_id and dev.state_id<>5 and "
									+ "(a.beatstate<>0 or a.op_time<:sysTime) with ur ")
					.addEntity("dev", TPifDevice.class);
			query.setString("sysTime", systemTime);
			List list = query.list();
			Iterator iter = list.iterator();
			while (iter.hasNext()) {
				TPifDevice device = (TPifDevice) iter.next();
				if (true == recordOrNot) {
					TMifDevmonitor devMonitor = (TMifDevmonitor) session.get(
							TMifDevmonitor.class, device.getDeviceId());
					MapDeviceTable mapDeviceTable = new MapDeviceTable();
					MapDeviceTableKey deviceTableKey = new MapDeviceTableKey();
					deviceTableKey.setAnalysisTime(recordTime);
					deviceTableKey.setDeviceId(device.getDeviceId());
					mapDeviceTable.setArea(device.getArea());
					mapDeviceTable.setBsheetver(device.getBsheetver());
					Query devquery = session.createSQLQuery(
							"select dev.DEVPHY999_ID as devphy999Id from YKT_CUR.T_PIF_DEVICE as dev "
									+ "where dev.device_id="
									+ device.getFdevId()).addScalar(
							"devphy999Id", Hibernate.STRING);
					List devList = devquery.list();
					Iterator devIter = devList.iterator();// devquery.iterate();
					String fdevphyId = "";
					if (devIter.hasNext()) {
						fdevphyId = devIter.next().toString();
					}
					Query queryContact = session
							.createQuery("select a.contactname from MapContactMonitorTable a "
									+ "where a.monitorno= :monitorNo");
					queryContact.setString("monitorNo", fdevphyId);
					List listContact = queryContact.list();
					contactName = "";
					for (int i = 0; i < listContact.size(); i++) {
						contactName += listContact.get(i).toString() + ",";
					}
					if (!"".equals(contactName)) {
						contactName = contactName.substring(0, contactName
								.lastIndexOf(","));
					}
					mapDeviceTable.setContactName(contactName);// to get
					// contact
					// according to
					// fdevphy_id
					mapDeviceTable.setCpu(Float.valueOf("0"));
					mapDeviceTable.setDevicetime(devMonitor.getDevtime());
					mapDeviceTable.setServertime(devMonitor.getOpTime());
					mapDeviceTable.setDeviceName(device.getDeviceName());
					mapDeviceTable.setDeviceType(device.getDevtype());
					mapDeviceTable.setDevphy999Id(device.getDev999Id());
					mapDeviceTable.setErrorReason(Short.valueOf("101"));
					mapDeviceTable.setFdevphyId(device.getFdevId().toString());
					mapDeviceTable.setHarddisk(Float.valueOf("0"));
					mapDeviceTable.setId(deviceTableKey);
					mapDeviceTable.setMemory(Float.valueOf("0"));
					mapDeviceTable.setSubsystemId(device.getSubsystemId());
					session.save(mapDeviceTable);
				}
				mailRecord++;
			}

			// record timepoint analysis
			Object tempAnalysis = session.get(MapAnalysisPoint.class,
					"DEVICE_EXCEPTION");
			MapAnalysisPoint analysisPoint = null;
			if (tempAnalysis == null) {
				analysisPoint = new MapAnalysisPoint();
				analysisPoint.setAnalysisname("DEVICE_EXCEPTION");
				analysisPoint.setAnalysispoint(endTime);
				session.save(analysisPoint);
			} else {
				analysisPoint = (MapAnalysisPoint) tempAnalysis;
				analysisPoint.setAnalysispoint(endTime);
				session.update(analysisPoint);
			}
			tx.commit();

		} catch (HibernateException e) {
			logger.error("设备状态分析线程出现以下异常：", e); //$NON-NLS-1$

			if (tx != null) {
				tx.rollback();
			}
		} catch (Exception e) {
			logger.error("设备状态分析线程出现以下异常：", e); //$NON-NLS-1$
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
						.info("设备状态分析线程结束进入休眠状态!"
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
			logger.error("设备状态分析线程出现以下异常：可能被强行停止！ ", e); //$NON-NLS-1$
		} catch (Exception e) {
			logger.error("设备状态分析线程出现以下异常：可能被强行停止！ ", e); //$NON-NLS-1$
		}
	}

	public void terminate() {
		if (this.isAlive()) {
			logger.warn("设备状态分析线程状态被请求，此时线程状态：活动线程!"); //$NON-NLS-1$
			this.requestStop = true;
		} else {
			logger.warn("设备状态分析线程状态被请求，此时线程状态：死亡线程!"); //$NON-NLS-1$
			this.destroy();

		}
	}

	public boolean isTerminate() {
		return this.isAlive();
	}

	public void sendMail() {
		// TODO Auto-generated method stub
		if ((true == mailOrNot) && (!"".equals(mailList))
				&& (0 != buffer.size())) {
			if (logger.isInfoEnabled()) {
				logger.info("设备状态分析线程发送邮件给联系人:" + contactName);
			}
			String tmpStr = "";
			if (buffer.size() > 5000) {
				tmpStr = buffer.getString(0, 5000);
			}
			tmpStr = buffer.toString();

			String[] tempList = null;
			tempList = mailList.split(";");
			for (int i = 0; i < tempList.length; i++) {
				if (!"".equals(tempList)) {
					CommonSendMailUtil.sendMail(GetApplicationResources
							.getInstance().getString(
									"com.kingstar.MonitorSys.SUBJECT_SERIAL"),
							contactName, tempList[i], StringUtil
									.wholeMailGenerate(contactName, DateUtil
											.reFormatTime(recordTime),
											mailRecord, tmpStr,
											"DEVICE_EXCEPTION"));
				}
			}
		}
	}

	public void sendSMG() {
		if ((true == smgOrNot) && (!"".equals(phoneNumber)) && mailRecord > 0) {
			if (logger.isInfoEnabled()) {
				logger.info("设备状态分析线程发送短信给联系人:" + contactName);
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
							"DEVICE_EXCEPTION");
					CommonSendSMGUtil.sendSMG(tempList[i], SmgMessage);
				}
			}
		}
	}

}
