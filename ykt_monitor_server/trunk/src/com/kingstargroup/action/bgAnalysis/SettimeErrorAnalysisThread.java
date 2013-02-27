package com.kingstargroup.action.bgAnalysis;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: SettimeErrorAnalysisThread.java
 * Description: 设备时钟错误检查类
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				 2005-10-19     何林青             设备时钟错误检查类
 * 修改					2006-07-20   	何林青    		  修改日志记录方式
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
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;
import org.hibernate.Transaction;

import com.kingstargroup.SqlStatementDictionary;
import com.kingstargroup.commons.AnalyzeThreadInterface;
import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.form.MapAlertTable;
import com.kingstargroup.form.MapAnalysisPoint;
import com.kingstargroup.form.MapContactMonitorTable;
import com.kingstargroup.form.MapContactTable;
import com.kingstargroup.form.MapDeviceTable;
import com.kingstargroup.form.MapDeviceTableId;
import com.kingstargroup.form.MapParamTable;
import com.kingstargroup.form.TDevice;
import com.kingstargroup.form.TDevmonitor;
import com.kingstargroup.utils.CommonSendMailUtil;
import com.kingstargroup.utils.CommonSendSMGUtil;
import com.kingstargroup.utils.DateUtil;
import com.kingstargroup.utils.GetApplicationResources;
import com.kingstargroup.utils.StringUtil;

public class SettimeErrorAnalysisThread extends Thread implements
		AnalyzeThreadInterface {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(SettimeErrorAnalysisThread.class);

	// flag of stop this thread
	private static boolean requestStop = false;

	// record analysis time
	private String recordTime = "";

	// default analysis is to analysis all from
	private String startTime = "20050101000000";

	// default analysis is to analysis to now
	private String endTime = DateUtil.getNow();

	// default analysis cycle is one hour
	private double cycle = 1.0;

	// money limit
	private double timeLimit = 10.0;

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
	}

	public void initParam() {
		if (logger.isInfoEnabled()) {
			logger.info("**************设备时钟错误分析线程初始化**************"); //$NON-NLS-1$
		}
		try {
			Session session = HibernateSessionFactory.currentSession();
			Query queryTime = session
					.createQuery("from MapAnalysisPoint point where point.analysisname=:analysisName");
			queryTime.setString("analysisName", "SETTIME_ERROR");
			Iterator iterTime = queryTime.iterate();
			if (iterTime.hasNext()) {
				MapAnalysisPoint mapAnalysisPoint = (MapAnalysisPoint) iterTime
						.next();
				this.startTime = mapAnalysisPoint.getAnalysispoint();
			}

			Query queryCycle = session
					.createQuery("from MapParamTable param where param.parameter=:paramRefer "
							+ "or param.parameter=:paramRefer1");
			queryCycle.setString("paramRefer", "ClockErrorCycle");
			queryCycle.setString("paramRefer1", "ClockErrortimeLimit");
			List listParam = queryCycle.list();
			Iterator iterParam = listParam.iterator();
			while (iterParam.hasNext()) {
				MapParamTable mapParamTable = (MapParamTable) iterParam.next();
				if ("ClockErrorCycle".equals(mapParamTable.getParameter())) {
					this.cycle = mapParamTable.getValue();
				}
				if ("ClockErrortimeLimit".equals(mapParamTable.getParameter())) {
					this.timeLimit = mapParamTable.getValue();
				}

			}
			String s = String.valueOf(cycle * 3600);
			this.doubleCycle = Integer.parseInt(s.substring(0, s.indexOf('.')));

			if (!"20050101000000".equals(this.startTime)) {
				this.endTime = DateUtil.getNewTime(startTime, doubleCycle);
			} else {
				this.endTime = DateUtil.getNow();
				this.startTime = DateUtil
						.getNewTime(this.endTime, -doubleCycle);
			}

		} catch (HibernateException e) {
			logger.error("设备时钟错误分析线程初始化失败！", e); //$NON-NLS-1$
		} finally {
			HibernateSessionFactory.closeSession();
		}
		if (logger.isInfoEnabled()) {
			logger.info("**************设备时钟错误分析线程初始化成功**************"); //$NON-NLS-1$
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
				.createQuery("from MapAlertTable alert where alert.parameter='ClockError'");
		Iterator iterOrNot = queryOrNot.iterate();
		if (iterOrNot.hasNext()) {
			MapAlertTable alertTable = (MapAlertTable) iterOrNot.next();
			if (0==alertTable.getNote()) {
				recordOrNot = false;
			}
			if (1==alertTable.getMailalert()) {
				mailOrNot = true;
			}
			if (1==alertTable.getPhonealert()) {
				smgOrNot = true;
			}
		}
		Query queryCycle = session
				.createQuery("from MapParamTable as param where param.parameter=:paramRefer "
						+ "or param.parameter=:paramRefer1");
		queryCycle.setString("paramRefer", "ClockErrorCycle");
		queryCycle.setString("paramRefer1", "ClockErrortimeLimit");
		List listParam = queryCycle.list();
		Iterator iterParam = listParam.iterator();
		while (iterParam.hasNext()) {
			MapParamTable mapParamTable = (MapParamTable) iterParam.next();
			if ("ClockErrorCycle".equals(mapParamTable.getParameter())) {
				this.cycle = mapParamTable.getValue();
			}
			if ("ClockErrortimeLimit".equals(mapParamTable.getParameter())) {
				this.timeLimit = mapParamTable.getValue();
			}

		}
		String s = String.valueOf(cycle * 3600);
		this.doubleCycle = Integer.parseInt(s.substring(0, s.indexOf('.')));

		// contact list
		Query queryContact = session
				.createQuery("from MapContactMonitorTable monitor where monitor.monitorno='SETTIME_ERROR'");
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
		if (logger.isInfoEnabled()) {
			logger.info("设备时钟错误分析线程开始分析任务"); //$NON-NLS-1$
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
						.info("设备时钟错误分析线程开始分析时间:" + DateUtil.getNow("yyyy/MM/dd/HH:mm:ss")); //$NON-NLS-1$
			}
			if (1 > DateUtil.checkTimeSequence(endTime, DateUtil.getNow())) {
				if (logger.isInfoEnabled()) {
					logger.info("设备时钟错误分析线程分析时间段：" + startTime + " -- "
							+ endTime);
				}
			} else {
				endTime = DateUtil.getNow();
				if (logger.isInfoEnabled()) {
					logger.info("设备时钟错误分析线程分析时间段：" + startTime + " -- "
							+ endTime);
				}
			}
			getParameter(session);
			// analysis time record
			recordTime = DateUtil.getNow();
			BgMonitor
					.monitorThreadStatusReport(
							"com.kingstargroup.action.bgAnalysis.SettimeErrorAnalysisThread",
							"设备时钟错误分析线程", DateUtil
									.getNow("yyyy/MM/dd/HH:mm:ss"), String
									.valueOf(this.doubleCycle), "运行中...");

			Query query = session.createSQLQuery(SqlStatementDictionary.getIntance().getSQL("com.kingstargroup.action.bgAnalysis.SettimeErrorAnalysisThread.getdevmonitor")).addEntity("a",
					TDevmonitor.class);// filter
			List list = query.list();
			Iterator iter = list.iterator();
			String serverTime = "";
			String serverTime1 = "";
			String temp = String.valueOf(this.timeLimit);
			int intTemp = Integer
					.parseInt(temp.substring(0, temp.indexOf("."))) * 60;
			int intTemp1 = intTemp * -1;
			while (iter.hasNext()) {
				TDevmonitor devMonitor = (TDevmonitor) iter.next();
				serverTime = DateUtil.getNewTime(devMonitor.getOptime()
						.substring(0, 14), intTemp);
				serverTime1 = DateUtil.getNewTime(devMonitor.getOptime()
						.substring(0, 14), intTemp1);
				if ((0 > DateUtil.checkTimeSequence(serverTime, devMonitor
						.getDevtime()))
						|| (0 < DateUtil.checkTimeSequence(serverTime1,
								devMonitor.getDevtime()))) {
					Query queryOne = session
							.createSQLQuery(SqlStatementDictionary.getIntance().getSQL("com.kingstargroup.action.bgAnalysis.SettimeErrorAnalysisThread.getdevice"))
							.addEntity("a", TDevice.class);
					queryOne.setLong("deviceId", devMonitor.getDeviceid());
					List listOne = queryOne.list();
					Iterator iterOne = listOne.iterator();
					if (iterOne.hasNext()) {
						TDevice device = (TDevice) iterOne.next();
						if (true == recordOrNot) {
							MapDeviceTable mapDeviceTable = new MapDeviceTable();
							MapDeviceTableId deviceTableKey = new MapDeviceTableId();
							deviceTableKey.setAnalysistime(recordTime);
							deviceTableKey.setDeviceid(device.getDeviceid());
							
							Query devquery = session.createSQLQuery(
									"select dev.devphyid devphy999Id from YKT_CUR.T_DEVICE dev "
											+ "where dev.deviceid="
											+ device.getFdeviceid()).addScalar(
									"devphy999Id", Hibernate.STRING);
							List devList = devquery.list();
							Iterator devIter = devList.iterator();
							String fdevphyId = "";
							if (devIter.hasNext()) {
								fdevphyId = devIter.next().toString();
							}
							mapDeviceTable.setAreacode(device.getAreacode());
							mapDeviceTable.setCardverno(device.getCardverno());
							mapDeviceTable.setContactName(contactName);
							mapDeviceTable.setCpu(Long.parseLong("0"));
							mapDeviceTable.setDevicetime(devMonitor
									.getDevtime());
							mapDeviceTable
									.setServertime(devMonitor.getOptime());
							mapDeviceTable
									.setDevicename(device.getDevicename());
							mapDeviceTable.setDevtypecode(device.getDevtypecode());
							mapDeviceTable.setDevphyid(device.getDevphyid());
							mapDeviceTable.setErrorReason(Long.parseLong("12"));
							mapDeviceTable.setFdevphyid(fdevphyId);
							mapDeviceTable.setHarddisk(Long.parseLong("0"));
							mapDeviceTable.setId(deviceTableKey);
							mapDeviceTable.setMemory(Long.parseLong("0"));
							mapDeviceTable.setSysid(device.getSysid());
							session.save(mapDeviceTable);

//							TTifMeslist mesList = new TTifMeslist();
//							mesList.setCardNo(Integer.valueOf("0"));
//							mesList.setDelFlag("0");
//							mesList.setDeviceId(device.getSubsystemId());
//							mesList.setDevphy999Id(device.getDev999Id());
//							mesList.setFunid(Integer.valueOf("930001"));
//							mesList.setIncontent("<CLOCK>"
//									+ DB2TimeUtil.getSysDate(0).substring(2)
//									+ "</CLOCK>");
//							mesList.setEcode(Integer.valueOf("9999"));
//							mesList.setIndt(DB2TimeUtil.getSysDate(0));
//							mesList.setLevel(Integer.valueOf("2"));
//							mesList.setMaxSendCnt(Integer.valueOf("3"));
//							mesList.setPfunid(Integer.valueOf("0"));
//							mesList.setSendcount(Integer.valueOf("0"));
//							mesList.setStateid(Integer.valueOf("1"));
//							session.save(mesList);
						}
						mailRecord++;
						if (!"".equals(mailList)) {
							buffer.append(StringUtil.devtimeStringGenerate(
									device.getDevphyid(), device
											.getDevicename(), devMonitor
											.getDevtime(), devMonitor
											.getOptime(), "SETTIME_ERROR"));
						}
					}
				}
			}

			// record timepoint analysis
			Object tempAnalysis = session.get(MapAnalysisPoint.class,
					"SETTIME_ERROR");
			MapAnalysisPoint analysisPoint = null;
			if (tempAnalysis == null) {
				analysisPoint = new MapAnalysisPoint();
				analysisPoint.setAnalysisname("SETTIME_ERROR");
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
			logger.error("设备时钟错误分析线程出现以下异常：", e); //$NON-NLS-1$

			if (tx != null) {
				try {
					tx.rollback();
				} catch (Exception e1) {
					// TODO: handle exception
					e1.printStackTrace();
				}
			}
		} catch (Exception e) {
			logger.error("设备时钟错误分析线程出现以下异常：", e); //$NON-NLS-1$
			if (tx != null) {
				try {
					tx.rollback();
				} catch (Exception e1) {
					// TODO: handle exception
					e1.printStackTrace();
				}
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
						.info("设备时钟错误分析线程结束进入休眠状态!"
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
			logger.error("设备时钟错误分析线程出现以下异常：可能被强行停止！ ", e); //$NON-NLS-1$
		} catch (Exception e) {
			logger.error("设备时钟错误分析线程出现以下异常：可能被强行停止！ ", e); //$NON-NLS-1$
		}
	}

	public void terminate() {
		if (this.isAlive()) {
			logger.warn("设备时钟错误分析线程状态被请求，此时线程状态：活动线程!"); //$NON-NLS-1$
			requestStop = true;
		} else {
			logger.warn("设备时钟错误分析线程状态被请求，此时线程状态：死亡线程!"); //$NON-NLS-1$
			this.destroy();

		}
	}

	public boolean isTerminate() {
		return this.isAlive();
	}

	public void sendMail() {
		if ((true == mailOrNot) && (!"".equals(mailList))
				&& (0 != buffer.size())) {
			if (logger.isInfoEnabled()) {
				logger.info("设备时钟错误分析线程发送邮件给联系人:" + contactName);
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
				if (!"".equals(tempList)) {
					CommonSendMailUtil.sendMail(GetApplicationResources
							.getInstance().getString(
									"com.kingstar.MonitorSys.SUBJECT_DEVICE"),
									nameList[i], tempList[i],
							StringUtil.devTimeMailGenerate(nameList[i],
									DateUtil.reFormatTime(recordTime),
									mailRecord, tmpStr, "SETTIME_ERROR"));
				}
			}
		}
	}

	public void sendSMG() {
		if ((true == smgOrNot) && (!"".equals(phoneNumber)) && mailRecord > 0) {
			if (logger.isInfoEnabled()) {
				logger.info("设备时钟错误分析线程发送短信给联系人:" + contactName);
			}
			String[] tempList = null;
			String[] nameList = null;
			tempList = phoneNumber.split(";");
			nameList = phoneName.split(";");
			for (int i = 0; i < tempList.length; i++) {
				if (!"".equals(tempList[i])) {
					SmgMessage = StringUtil.wholeSMGGenerate(nameList[i],
							DateUtil.reFormatTime(recordTime), mailRecord,
							"SETTIME_ERROR");
					CommonSendSMGUtil.sendSMG(tempList[i], SmgMessage);
				}
			}
		}
	}

}
