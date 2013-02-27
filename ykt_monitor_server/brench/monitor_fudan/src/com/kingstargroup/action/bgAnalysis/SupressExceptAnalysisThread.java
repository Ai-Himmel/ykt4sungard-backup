package com.kingstargroup.action.bgAnalysis;

/**
 * <p>
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: SupressExceptAnalysisThread.java
 * Description: 压数流水检查线程类
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				 2005-10-19    何林青             压数流水检查线程类
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */
import org.apache.log4j.Logger;
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
import com.kingstargroup.form.MapContactMonitorTable;
import com.kingstargroup.form.MapContactTable;
import com.kingstargroup.form.MapParamTable;
import com.kingstargroup.form.MapSerialostTable;
import com.kingstargroup.form.MapSerialostTableKey;
import com.kingstargroup.form.TTifRcvdtl;
import com.kingstargroup.utils.CommonSendMailUtil;
import com.kingstargroup.utils.CommonSendSMGUtil;
import com.kingstargroup.utils.DateUtil;
import com.kingstargroup.utils.GetApplicationResources;
import com.kingstargroup.utils.StringUtil;

import java.util.Iterator;
import java.util.List;

public class SupressExceptAnalysisThread extends Thread implements
		AnalyzeThreadInterface {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(SupressExceptAnalysisThread.class);

	// flag of stop this thread
	private boolean requestStop = false;

	// record analysis time
	private String recordTime = "";

	// default analysis is to analysis all from
	private String startTime = "20050101000000";

	// default analysis is to analysis to now
	private String endTime = DateUtil.getNow();

	// default analysis cycle is one hour
	private double cycle = 1.0;

	// money limit
	private double timeLimit = 24.0;

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
			logger.info("**************流水压数分析线程初始化**************"); //$NON-NLS-1$
		}
		try {
			Session session = HibernateSessionFactory.currentSession();
			Query queryTime = session
					.createQuery("from MapAnalysisPoint as point where point.analysisname=:analysisName");
			queryTime.setString("analysisName", "SUPRESS_EXCEPTION");
			List listTime = queryTime.list();
			Iterator iterTime = listTime.iterator();
			if (iterTime.hasNext()) {
				MapAnalysisPoint mapAnalysisPoint = (MapAnalysisPoint) iterTime
						.next();
				this.startTime = mapAnalysisPoint.getAnalysispoint();
			}
			Query queryCycle = session
					.createQuery("from MapParamTable as param where param.parameter=:paramRefer or param.parameter=:paramRefer1");
			queryCycle.setString("paramRefer", "SuppressCycle");
			queryCycle.setString("paramRefer1", "SuppressTime");
			List listParam = queryCycle.list();
			Iterator iterParam = listParam.iterator();
			while (iterParam.hasNext()) {
				MapParamTable mapParamTable = (MapParamTable) iterParam.next();
				if ("SuppressCycle".equals(mapParamTable.getParameter())) {
					this.cycle = mapParamTable.getValue().doubleValue();
				}
				if ("SuppressTime".equals(mapParamTable.getParameter())) {
					this.timeLimit = mapParamTable.getValue().doubleValue();
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
			logger.error("流水压数分析线程初始化失败！", e); //$NON-NLS-1$
		} finally {
			HibernateSessionFactory.closeSession();
		}

		if (logger.isInfoEnabled()) {
			logger.info("**************流水压数分析线程初始化成功**************"); //$NON-NLS-1$
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
				.createQuery("from MapAlertTable alert where alert.parameter='SuppressMonitor'");
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
		queryCycle.setString("paramRefer", "SuppressCycle");
		queryCycle.setString("paramRefer1", "SuppressTime");
		List listParam = queryCycle.list();
		Iterator iterParam = listParam.iterator();
		while (iterParam.hasNext()) {
			MapParamTable mapParamTable = (MapParamTable) iterParam.next();
			if ("SuppressCycle".equals(mapParamTable.getParameter())) {
				this.cycle = mapParamTable.getValue().doubleValue();
			}
			if ("SuppressTime".equals(mapParamTable.getParameter())) {
				this.timeLimit = mapParamTable.getValue().doubleValue();
			}

		}
		String s = String.valueOf(cycle * 3600);
		this.doubleCycle = Integer.parseInt(s.substring(0, s.indexOf('.')));

		// contact list
		Query queryContact = session
				.createQuery("from MapContactMonitorTable monitor where monitor.monitorno='SUPRESS_EXCEPTION'");
		List listContact = queryContact.list();
		Iterator iterContact = listContact.iterator();
		while (iterContact.hasNext()) {
			MapContactMonitorTable contactMonitor = (MapContactMonitorTable) iterContact
					.next();
			String nowDayTime = DateUtil.getNow("HHmmss");

			Query queryPhone = session
					.createQuery("from MapContactTable a where a.contactname=:contactName and a.starttime<=:starttime and a.endtime>=:endtime");
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
			logger.info("流水压数分析线程开始分析任务"); //$NON-NLS-1$
		}
		// TODO Auto-generated method stub
		Transaction tx = null;
		try {
			Session session = HibernateSessionFactory.currentSession();
			tx = session.beginTransaction();
			this.accelateParam = Integer
					.parseInt(BgMonitor.getIntance().accelateParam);
			endTime = DateUtil.getNewTime(endTime, accelateParam * 60);
			if (logger.isInfoEnabled()) {
				logger
						.info("流水压数分析线程开始分析时间:" + DateUtil.getNow("yyyy/MM/dd/HH:mm:ss")); //$NON-NLS-1$
			}
			if (1 > DateUtil.checkTimeSequence(endTime, DateUtil.getNow())) {
				if (logger.isInfoEnabled()) {
					logger
							.info("流水压数分析线程分析时间段：" + startTime + " -- "
									+ endTime);
				}
			} else {
				endTime = DateUtil.getNow();
				if (logger.isInfoEnabled()) {
					logger
							.info("流水压数分析线程分析时间段：" + startTime + " -- "
									+ endTime);
				}
			}
			getParameter(session);
			// analysis time record
			recordTime = DateUtil.getNow();

			BgMonitor
					.monitorThreadStatusReport(
							"com.kingstargroup.action.bgAnalysis.SupressExceptAnalysisThread",
							"流水压数分析线程", DateUtil.getNow("yyyy/MM/dd/HH:mm:ss"),
							String.valueOf(this.doubleCycle), "运行中...");

			// select distinct b.device_id from YKT_CUR.T_TIF_RCVDTL b where
			// b.col_timestamp>'20060707103000'
			// and b.col_timestamp<='20060707133000'
			// and b.device_id not in (select distinct c.device_id from
			// YKT_CUR.T_TIF_RCVDTL c
			// where c.col_timestamp>'20060707133000' and
			// c.col_timestamp<='20060708133000');
			Query query = session
					.createSQLQuery(
							"select distinct a.device_id as deviceId from YKT_CUR.T_TIF_RCVDTL a "
									+ "where a.col_timestamp>:startTime and a.col_timestamp<=:time "
									+ "and a.device_id not in (select distinct b.device_id from YKT_CUR.T_TIF_RCVDTL b "
									+ " where b.col_timestamp>:time and b.col_timestamp<=:endTime) with ur")
					.addScalar("deviceId", Hibernate.STRING);
			// session.getNamedQuery("SupressDevice");
			String temp = String.valueOf(this.timeLimit);
			int intTemp = Integer
					.parseInt(temp.substring(0, temp.indexOf(".")));
			intTemp *= (-1 * 3600);
			query.setString("startTime", DateUtil
					.getNewTime(startTime, intTemp));
			query.setString("endTime", endTime);
			query.setString("time", DateUtil.getNewTime(endTime, intTemp));
			List list = query.list();
			String device_id = "";
			for (int i = 0; i < list.size(); i++) {
				device_id = list.get(i).toString();
				Query queryOne = session
						.createSQLQuery(
								"select {rcvdtl.*} from YKT_CUR.T_TIF_RCVDTL as rcvdtl where rcvdtl.device_id=:deviceId "
										+ " and rcvdtl.col_timestamp>:startTime and not rcvdtl.col_timestamp>:endTime "
										+ " Order by rcvdtl.tx_date desc,rcvdtl.tx_time desc with ur")
						.addEntity("rcvdtl", TTifRcvdtl.class);

				queryOne.setString("deviceId", device_id);
				queryOne.setString("startTime", DateUtil.getNewTime(startTime,
						intTemp));
				queryOne.setString("endTime", endTime);
				List listOne = queryOne.list();
				Iterator iterOne = listOne.iterator();
				if (iterOne.hasNext()) {
					// insert into serialosttable
					TTifRcvdtl rcvdtl = (TTifRcvdtl) iterOne.next();
					if (true == recordOrNot) {
						MapSerialostTable mapSerialost = new MapSerialostTable();
						MapSerialostTableKey mapSerialostKey = new MapSerialostTableKey();
						mapSerialostKey.setAnalysistime(recordTime);
						mapSerialostKey.setDeviceId(rcvdtl.getId()
								.getDeviceId());
						mapSerialostKey.setSerialNo(rcvdtl.getId()
								.getSerialNo());
						mapSerialost.setId(mapSerialostKey);
						mapSerialost.setTxDate(rcvdtl.getId().getTxDate());
						mapSerialost.setTxTime(rcvdtl.getId().getTxTime());
						mapSerialost.setContactname(contactName);
						mapSerialost.setSerialReason(Short.valueOf("8"));
						mapSerialost.setSerialStatus(Short.valueOf("0"));
						session.save(mapSerialost);
					}
					mailRecord++;
					if (!"".equals(mailList)) {
						String device_name = "";
						device_name = DeviceNameDictionary.getInstance().get(
								rcvdtl.getId().getDeviceId()).trim();
						buffer.append(StringUtil.suppressExceptStringGenerate(
								rcvdtl.getId().getDeviceId(), device_name,
								rcvdtl.getId().getTxDate(), rcvdtl.getId()
										.getTxTime(), recordTime, rcvdtl
										.getId().getSerialNo().toString(),
								"SUPRESS_EXCEPTION"));
					}
				} else {
					// can not find or means no F_serialNo insert
					// directly with no detail info
					if (true == recordOrNot) {
						MapSerialostTable mapSerialost = new MapSerialostTable();
						MapSerialostTableKey mapSerialostKey = new MapSerialostTableKey();
						mapSerialostKey.setAnalysistime(recordTime);
						mapSerialostKey.setDeviceId(device_id);
						mapSerialostKey.setSerialNo(Integer.valueOf("0"));
						mapSerialost.setId(mapSerialostKey);
						mapSerialost.setTxDate("00000000");
						mapSerialost.setTxTime("000000");
						mapSerialost.setContactname(contactName);
						mapSerialost.setSerialReason(Short.valueOf("8"));
						mapSerialost.setSerialStatus(Short.valueOf("0"));
						session.save(mapSerialost);
					}
					mailRecord++;
					if (!"".equals(mailList)) {
						String device_name = "";
						device_name = DeviceNameDictionary.getInstance().get(
								device_id).trim();
						buffer.append(StringUtil.suppressExceptStringGenerate(
								device_id, device_name, "00000000", "000000",
								recordTime, "", "SUPRESS_EXCEPTION"));
					}

				}
			}

			// record timepoint analysis
			Object tempAnalysis = session.get(MapAnalysisPoint.class,
					"SUPRESS_EXCEPTION");
			MapAnalysisPoint analysisPoint = null;
			if (tempAnalysis == null) {
				analysisPoint = new MapAnalysisPoint();
				analysisPoint.setAnalysisname("SUPRESS_EXCEPTION");
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
			logger.error("流水压数分析线程出现以下异常：", e); //$NON-NLS-1$

			if (tx != null) {
				tx.rollback();
			}
		} catch (Exception e) {
			logger.error("流水压数分析线程出现以下异常：", e); //$NON-NLS-1$
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
						.info("流水压数分析线程结束进入休眠状态!"
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
			logger.error("流水压数分析线程出现以下异常：可能被强行停止！ ", e); //$NON-NLS-1$
		} catch (Exception e) {
			logger.error("流水压数分析线程出现以下异常：可能被强行停止！ ", e); //$NON-NLS-1$
		}
	}

	public void terminate() {
		if (this.isAlive()) {
			logger.warn("流水压数分析线程状态被请求，此时线程状态：活动线程!"); //$NON-NLS-1$
			this.requestStop = true;
		} else {
			logger.warn("流水压数分析线程状态被请求，此时线程状态：死亡线程!"); //$NON-NLS-1$
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
				logger.info("流水压数分析线程发送邮件给联系人:" + contactName);
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
									"com.kingstar.MonitorSys.SUBJECT_SERIAL"),
									nameList[i], tempList[i], StringUtil
									.suppressExceptMailGenerate(nameList[i],
											DateUtil.reFormatTime(recordTime),
											mailRecord, tmpStr,
											"SUPRESS_EXCEPTION"));
				}
			}
		}
	}

	public void sendSMG() {
		if ((true == smgOrNot) && (!"".equals(phoneNumber)) && mailRecord > 0) {
			if (logger.isInfoEnabled()) {
				logger.info("流水压数分析线程发送短信给联系人:" + contactName);
			}

			String[] tempList = null;
			String[] nameList = null;
			tempList = phoneNumber.split(";");
			nameList = phoneName.split(";");
			for (int i = 0; i < tempList.length; i++) {
				if (!"".equals(tempList[i])) {
					SmgMessage = StringUtil.wholeSMGGenerate(nameList[i],
							DateUtil.reFormatTime(recordTime), mailRecord,
							"SUPRESS_EXCEPTION");
					CommonSendSMGUtil.sendSMG(tempList[i], SmgMessage);
				}
			}
		}
	}
}
