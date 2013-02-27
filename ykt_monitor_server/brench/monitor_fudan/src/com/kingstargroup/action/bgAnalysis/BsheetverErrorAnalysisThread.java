package com.kingstargroup.action.bgAnalysis;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: BsheetverErrorAnalysisThread.java
 * Description: 黑名单版本号错误检查线程类
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				 2005-10-19    何林青             黑名单版本号错误检查线程类
 * 修改					 2006-07-20    何林青    			 修改日志记录方式        
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

import com.kingstargroup.commons.AnalyzeThreadInterface;
import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.form.MapAlertTable;
import com.kingstargroup.form.MapAnalysisPoint;
import com.kingstargroup.form.MapContactMonitorTable;
import com.kingstargroup.form.MapContactTable;
import com.kingstargroup.form.MapDeviceTable;
import com.kingstargroup.form.MapDeviceTableKey;
import com.kingstargroup.form.MapParamTable;
import com.kingstargroup.form.TPifDevice;
import com.kingstargroup.utils.CommonSendMailUtil;
import com.kingstargroup.utils.CommonSendSMGUtil;
import com.kingstargroup.utils.DateUtil;
import com.kingstargroup.utils.GetApplicationResources;
import com.kingstargroup.utils.StringUtil;

public class BsheetverErrorAnalysisThread extends Thread implements
		AnalyzeThreadInterface {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(BsheetverErrorAnalysisThread.class);

	// flag of stop this thread
	private boolean requestStop = false;

	private String recordTime = "";

	// default analysis is to analysis all from
	private String startTime = "20050101000000";

	private String endTime = DateUtil.getNow();

	// default analysis cycle is one hour
	private double cycle = 1.0;

	// time limit
	private double timeLimit = 24;

	// inteval param
	private int doubleCycle = 0;

	// alarm contact
	private String contactName = "";

	// blk list
	private String blackSheet = "";

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
			logger.info("**************黑名单版本错误分析线程初始化**************"); //$NON-NLS-1$
		}
		try {
			Session session = HibernateSessionFactory.currentSession();
			Query queryTime = session
					.createQuery("from MapAnalysisPoint as point where point.analysisname=:analysisName");
			queryTime.setString("analysisName", "BSHEETVER_ERROR");
			Iterator iterTime = queryTime.iterate();
			if (iterTime.hasNext()) {
				MapAnalysisPoint mapAnalysisPoint = (MapAnalysisPoint) iterTime
						.next();
				this.startTime = mapAnalysisPoint.getAnalysispoint();
			}
			Query queryCycle = session
					.createQuery("from MapParamTable as param where param.parameter=:paramRefer "
							+ "or param.parameter=:paramRefer1");
			queryCycle.setString("paramRefer", "BlackListDistrCycle");
			queryCycle.setString("paramRefer1", "BlackListDistrTime");
			List listParam = queryCycle.list();
			Iterator iterParam = listParam.iterator();
			while (iterParam.hasNext()) {
				MapParamTable mapParamTable = (MapParamTable) iterParam.next();
				if ("BlackListDistrCycle".equals(mapParamTable.getParameter())) {
					this.cycle = mapParamTable.getValue().doubleValue();
				}
				if ("BlackListDistrTime".equals(mapParamTable.getParameter())) {
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
			logger.error("黑名单版本错误分析线程初始化失败！", e); //$NON-NLS-1$
		} finally {
			HibernateSessionFactory.closeSession();
		}
		if (logger.isInfoEnabled()) {
			logger.info("**************黑名单版本错误分析线程初始化成功**************"); //$NON-NLS-1$
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
				.createQuery("from MapAlertTable alert where alert.parameter='BlackListDiff'");
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

		// contact list
		Query queryContact = session
				.createQuery("from MapContactMonitorTable monitor where monitor.monitorno='BSHEETVER_ERROR'");
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

		Query queryCycle = session
				.createQuery("from MapParamTable as param where param.parameter=:paramRefer "
						+ "or param.parameter=:paramRefer1");
		queryCycle.setString("paramRefer", "BlackListDistrCycle");
		queryCycle.setString("paramRefer1", "BlackListDistrTime");
		List listParam = queryCycle.list();
		Iterator iterParam = listParam.iterator();
		while (iterParam.hasNext()) {
			MapParamTable mapParamTable = (MapParamTable) iterParam.next();
			if ("BlackListDistrCycle".equals(mapParamTable.getParameter())) {
				this.cycle = mapParamTable.getValue().doubleValue();
			}
			if ("BlackListDistrTime".equals(mapParamTable.getParameter())) {
				this.timeLimit = mapParamTable.getValue().doubleValue();
			}
		}
		String s = String.valueOf(cycle * 3600);
		this.doubleCycle = Integer.parseInt(s.substring(0, s.indexOf('.')));
	}

	public void anaylize() {
		if (logger.isInfoEnabled()) {
			logger.info("黑名单版本错误分析线程开始分析任务"); //$NON-NLS-1$
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
						.info("黑名单版本错误分析线程开始分析时间:" + DateUtil.getNow("yyyy/MM/dd/HH:mm:ss")); //$NON-NLS-1$
			}
			if (1 > DateUtil.checkTimeSequence(endTime, DateUtil.getNow())) {
				if (logger.isInfoEnabled()) {
					logger.info("黑名单版本错误分析线程分析时间段：" + startTime + " -- "
							+ endTime);
				}
			} else {
				endTime = DateUtil.getNow();
				if (logger.isInfoEnabled()) {
					logger.info("黑名单版本错误分析线程分析时间段：" + startTime + " -- "
							+ endTime);
				}
			}
			getParameter(session);
			recordTime = DateUtil.getNow();
			BgMonitor
					.monitorThreadStatusReport(
							"com.kingstargroup.action.bgAnalysis.BsheetverErrorAnalysisThread",
							"黑名单版本错误分析线程", DateUtil
									.getNow("yyyy/MM/dd/HH:mm:ss"), String
									.valueOf(this.doubleCycle), "运行中...");
			String blackSheetTmp = "";
			Query queryTime = session
					.createQuery("select max(volume)as maxVolume from TTifBlackSheet ");
			Iterator iterTime = queryTime.iterate();
			if (iterTime.hasNext()) {
				blackSheetTmp = iterTime.next().toString();
				String temp = String.valueOf(this.timeLimit);
				int intTemp = Integer.parseInt(temp.substring(0, temp
						.indexOf(".")));
				intTemp *= (-1 * 3600);
				blackSheet = DateUtil.getSpecialNewTime(blackSheetTmp, intTemp);
			}
			// Query query = session.getNamedQuery("BsverError1");
			Query query = session
					.createSQLQuery(
							"select {a.*} from YKT_CUR.T_PIF_DEVICE as a "
									+ "where (a.bsheetver<=:blackSheet) and a.state_id<>5 "
									+ "and (a.devtype='0226' or a.devtype='0201' or a.devtype='0232') "
									+ "and a.bsheetver<>'' and a.bsheetver<>'000000000000' order by a.bsheetver with ur ")
					.addEntity("a", TPifDevice.class);
			query.setString("blackSheet", blackSheet);
			List list = query.list();
			Iterator iter = list.iterator();
			while (iter.hasNext()) {
				TPifDevice device = (TPifDevice) iter.next();
				if (true == recordOrNot) {
					MapDeviceTable mapDeviceTable = new MapDeviceTable();
					MapDeviceTableKey deviceTableKey = new MapDeviceTableKey();
					deviceTableKey.setAnalysisTime(recordTime);
					deviceTableKey.setDeviceId(device.getDeviceId());
					mapDeviceTable.setArea(device.getArea());
					mapDeviceTable.setBsheetver(device.getBsheetver());
					mapDeviceTable.setContactName(contactName);
					mapDeviceTable.setCpu(Float.valueOf("0"));
					mapDeviceTable.setDevicetime("");
					mapDeviceTable.setDeviceName(device.getDeviceName());
					mapDeviceTable.setDeviceType(device.getDevtype());
					mapDeviceTable.setDevphy999Id(device.getDev999Id());
					mapDeviceTable.setErrorReason(Short.valueOf("11"));
					mapDeviceTable.setFdevphyId(device.getFdevphyId());
					mapDeviceTable.setHarddisk(Float.valueOf("0"));
					mapDeviceTable.setId(deviceTableKey);
					mapDeviceTable.setMemory(Float.valueOf("0"));
					mapDeviceTable.setSubsystemId(device.getSubsystemId());
					session.save(mapDeviceTable);
				}
				mailRecord++;
				if (!"".equals(mailList)) {
					buffer.append(StringUtil.blksheetStringGenerate(device
							.getDev999Id(), device.getDeviceName(), device
							.getBsheetver(), blackSheetTmp, "BSHEETVER_ERROR"));
				}
			}
			// 门禁的黑名单版本错误
			recordTime = DateUtil.getNow();
			Query query1 = session
					.createSQLQuery(
							"select {dev.*} from ykt_cur.t_pif_device dev where dev.device_id in(select distinct d.device_id "
									+ "from ykt_cur.t_door_device_cardlist c,"
									+ "ykt_cur.v_blklst a,ykt_cur.t_pif_device d "
									+ "where c.card_no=a.card_id and c.device_id=d.dev999_id  "
									+ "and ((c.status='1' and a.is_ad=0) or ( c.status='0')) "
									+ "and a.volume<=:blackSheet and a.volume>d.bsheetver "
									+ "and d.state_id<>5 "
									+ "and d.devtype='0121' and d.BSHEETVER<=:blackSheet "
									+ "and d.BSHEETVER<>'000000000000') order by dev.bsheetver with ur")
					.addEntity("dev", TPifDevice.class);
			query1.setString("blackSheet", blackSheet);
			List list1 = query1.list();
			Iterator iter1 = list1.iterator();
			while (iter1.hasNext()) {
				TPifDevice device = (TPifDevice) iter1.next();
				if (true == recordOrNot) {
					MapDeviceTable mapDeviceTable = new MapDeviceTable();
					MapDeviceTableKey deviceTableKey = new MapDeviceTableKey();
					deviceTableKey.setAnalysisTime(recordTime);
					deviceTableKey.setDeviceId(device.getDeviceId());
					mapDeviceTable.setArea(device.getArea());
					mapDeviceTable.setBsheetver(device.getBsheetver());
					mapDeviceTable.setContactName(contactName);
					mapDeviceTable.setCpu(Float.valueOf("0"));
					mapDeviceTable.setDevicetime("");
					mapDeviceTable.setDeviceName(device.getDeviceName());
					mapDeviceTable.setDeviceType(device.getDevtype());
					mapDeviceTable.setDevphy999Id(device.getDev999Id());
					mapDeviceTable.setErrorReason(Short.valueOf("11"));
					mapDeviceTable.setFdevphyId(device.getFdevphyId());
					mapDeviceTable.setHarddisk(Float.valueOf("0"));
					mapDeviceTable.setId(deviceTableKey);
					mapDeviceTable.setMemory(Float.valueOf("0"));
					mapDeviceTable.setSubsystemId(device.getSubsystemId());
					session.save(mapDeviceTable);
				}
				mailRecord++;
				if (!"".equals(mailList)) {
					buffer.append(StringUtil.blksheetStringGenerate(device
							.getDev999Id(), device.getDeviceName(), device
							.getBsheetver(), blackSheetTmp, "BSHEETVER_ERROR"));
				}
			}

			// record timepoint analysis
			Object tempAnalysis = session.get(MapAnalysisPoint.class,
					"BSHEETVER_ERROR");
			MapAnalysisPoint analysisPoint = null;
			if (tempAnalysis == null) {
				analysisPoint = new MapAnalysisPoint();
				analysisPoint.setAnalysisname("BSHEETVER_ERROR");
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
			logger.error("黑名单版本错误分析线程出现以下异常：", e); //$NON-NLS-1$

			if (tx != null) {
				tx.rollback();
			}
		} catch (Exception e) {
			logger.error("黑名单版本错误分析线程出现以下异常：", e); //$NON-NLS-1$
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
						.info("黑名单版本错误分析线程结束进入休眠状态!"
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
			logger.error("黑名单版本错误分析线程出现以下异常：可能被强行停止！ ", e); //$NON-NLS-1$
		} catch (Exception e) {
			logger.error("黑名单版本错误分析线程出现以下异常：可能被强行停止！ ", e); //$NON-NLS-1$
		}
	}

	public void terminate() {
		if (this.isAlive()) {
			logger.warn("黑名单版本错误分析线程状态被请求，此时线程状态：活动线程!"); //$NON-NLS-1$
			this.requestStop = true;
		} else {
			logger.warn("黑名单版本错误分析线程状态被请求，此时线程状态：死亡线程!"); //$NON-NLS-1$
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
				logger.info("黑名单版本错误分析线程发送邮件给联系人:" + contactName);
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
									nameList[i], tempList[i], StringUtil
									.blksheetMailGenerate(nameList[i], DateUtil
											.reFormatTime(recordTime),
											mailRecord, tmpStr,
											"BSHEETVER_ERROR"));
				}
			}
		}
	}

	public void sendSMG() {
		// TODO Auto-generated method stub
		if ((true == smgOrNot) && (!"".equals(phoneNumber)) && mailRecord > 0) {
			if (logger.isInfoEnabled()) {
				logger.info("黑名单版本错误分析线程发送短信给联系人:" + contactName);
			}
			String[] tempList = null;
			String[] nameList = null;
			tempList = phoneNumber.split(";");
			nameList = phoneName.split(";");
			for (int i = 0; i < tempList.length; i++) {
				if (!"".equals(tempList[i])) {
					SmgMessage = StringUtil.wholeSMGGenerate(nameList[i],
							DateUtil.reFormatTime(recordTime), mailRecord,
							"BSHEETVER_ERROR");
					CommonSendSMGUtil.sendSMG(tempList[i], SmgMessage);
				}
			}
		}
	}

}
