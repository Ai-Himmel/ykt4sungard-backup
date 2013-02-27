package com.kingstargroup.action.bgAnalysis;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: SerialLostAnalysisThread
 * Description: 流水缺失检查线程类
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期     操作者    操作内容简述
 * 创建  				2005-10-19   何林青    流水缺失检查线程
 * 修改					2006-7-17    何林青    整改，对查询的方式进行了修改
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
import com.kingstargroup.form.DeviceSerialLostResult;
import com.kingstargroup.form.DeviceSerialostRt;
import com.kingstargroup.form.MapAlertTable;
import com.kingstargroup.form.MapAnalysisPoint;
import com.kingstargroup.form.MapContactMonitorTable;
import com.kingstargroup.form.MapContactTable;
import com.kingstargroup.form.MapParamTable;
import com.kingstargroup.form.MapSerialostTable;
import com.kingstargroup.form.MapSerialostTableId;
import com.kingstargroup.form.TPosdtl;
import com.kingstargroup.utils.CheckLostSeriUitl;
import com.kingstargroup.utils.CommonSendMailUtil;
import com.kingstargroup.utils.CommonSendSMGUtil;
import com.kingstargroup.utils.DateUtil;
import com.kingstargroup.utils.GetApplicationResources;
import com.kingstargroup.utils.StringUtil;

public class SerialLostAnalysisThread extends Thread implements
		AnalyzeThreadInterface {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(SerialLostAnalysisThread.class);

	// flag of stop this thread
	private static boolean requestStop = false;

	// record analysis time
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
	}

	public void initParam() {
		if (logger.isInfoEnabled()) {
			logger.info("**************流水缺失分析线程初始化**************"); //$NON-NLS-1$
		}

		// TODO Auto-generated method stub
		try {
			Session session = HibernateSessionFactory.currentSession();
			Query queryTime = session
					.createQuery("from MapAnalysisPoint point where point.analysisname=:analysisName");
			queryTime.setString("analysisName", "SERI_LOSS");
			Iterator iterTime = queryTime.iterate();
			if (iterTime.hasNext()) {
				MapAnalysisPoint mapAnalysisPoint = (MapAnalysisPoint) iterTime
						.next();
				this.startTime = mapAnalysisPoint.getAnalysispoint();
			}
			Query queryCycle = session
					.createQuery("from MapParamTable param where param.parameter=:paramRefer");
			queryCycle.setString("paramRefer", "TradeLackCycle");
			Iterator iterParam = queryCycle.iterate();
			if (iterParam.hasNext()) {
				MapParamTable mapParamTable = (MapParamTable) iterParam.next();
				this.cycle = mapParamTable.getValue();
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
			logger.error("流水缺失分析线程初始化失败！", e); //$NON-NLS-1$

		} finally {
			HibernateSessionFactory.closeSession();
		}

		if (logger.isInfoEnabled()) {
			logger.info("**************流水缺失分析线程初始化成功**************"); //$NON-NLS-1$
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
				.createQuery("from MapAlertTable alert where alert.parameter='RecordLack'");
		Iterator iterOrNot = queryOrNot.iterate();
		if (iterOrNot.hasNext()) {
			MapAlertTable alertTable = (MapAlertTable) iterOrNot.next();
			if (0 == alertTable.getNote()) {
				recordOrNot = false;
			}
			if (1 == alertTable.getMailalert()) {
				mailOrNot = true;
			}
			if (1 == alertTable.getPhonealert()) {
				smgOrNot = true;
			}
		}

		Query queryCycle = session
				.createQuery("from MapParamTable param where param.parameter=:paramRefer");
		queryCycle.setString("paramRefer", "TradeLackCycle");
		Iterator iterParam = queryCycle.iterate();
		if (iterParam.hasNext()) {
			MapParamTable mapParamTable = (MapParamTable) iterParam.next();
			this.cycle = mapParamTable.getValue();
		}
		String s = String.valueOf(cycle * 3600);
		this.doubleCycle = Integer.parseInt(s.substring(0, s.indexOf('.')));

		// contact list
		Query queryContact = session
				.createQuery("from MapContactMonitorTable monitor where monitor.monitorno='SERI_LOSS'");
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
			logger.info("流水缺失分析线程开始分析任务"); //$NON-NLS-1$
		}

		Transaction tx = null;
		try {
			Session session = HibernateSessionFactory.currentSession();
			tx = session.beginTransaction();

			this.accelateParam = Integer
					.parseInt(BgMonitor.getIntance().SerialLostAnalysisThreadaccelateParam);
			endTime = DateUtil.getNewTime(endTime, accelateParam * 60);
			if (logger.isInfoEnabled()) {
				logger
						.info("流水缺失分析线程开始分析时间:" + DateUtil.getNow("yyyy/MM/dd/HH:mm:ss")); //$NON-NLS-1$
			}
			if (1 > DateUtil.checkTimeSequence(endTime, DateUtil.getNow())) {
				if (logger.isInfoEnabled()) {
					logger
							.info("流水缺失分析线程分析时间段：" + startTime + " -- "
									+ endTime);
				}
			} else {
				endTime = DateUtil.getNow();
				if (logger.isInfoEnabled()) {
					logger
							.info("流水缺失分析线程分析时间段：" + startTime + " -- "
									+ endTime);
				}
			}
			// get new parameter timely!
			getParameter(session);

			// analysis time record
			recordTime = DateUtil.getNow();
			// 状态报告
			BgMonitor
					.monitorThreadStatusReport(
							"com.kingstargroup.action.bgAnalysis.SerialLostAnalysisThread",
							"流水缺失分析线程", DateUtil.getNow("yyyy/MM/dd/HH:mm:ss"),
							String.valueOf(this.doubleCycle), "运行中...");

			// String dateTime = this.startTime.substring(0, 8);
			// String dateTime1 = this.endTime.substring(0, 8);
			String device_name = "";
			long serialNo = 0;
			long fSerialNo = 0;
			String dateRec = "00000000";

			Query firstquery = session
					.createSQLQuery(
							SqlStatementDictionary
									.getIntance()
									.getSQL(
											"com.kingstargroup.action.bgAnalysis.SerialLostAnalysisThread.getIntervalLostSerial"))
					.addEntity("serialost", DeviceSerialostRt.class);
			firstquery.setString("time1", startTime);
			firstquery.setString("time2", endTime);
			firstquery.setString("time3", startTime);
			firstquery
					.setString("time4", DateUtil.getNewTime(endTime, -259200));

			List firstlist = firstquery.list();
			Iterator firstIter = firstlist.iterator();

			while (firstIter.hasNext()) {
				dateRec = "00000000";
				DeviceSerialostRt rt = (DeviceSerialostRt) firstIter.next();
				device_name = DeviceNameDictionary.getInstance().get(
						rt.getDeviceId());
				List rtSerialNo = CheckLostSeriUitl.numberLostSerial(rt
						.getFirstNo(), rt.getLastNo());
				if ((rtSerialNo != null) && (rtSerialNo.size() < 50)) {// 假设五十条以上的都有问题，属于流水突变的范畴
					Iterator returnIter = rtSerialNo.iterator();
					while (returnIter.hasNext()) {
						serialNo = Long.parseLong(returnIter.next().toString());

						Query queryCheck = session
								.createSQLQuery(
										SqlStatementDictionary
												.getIntance()
												.getSQL(
														"com.kingstargroup.action.bgAnalysis.SerialLostAnalysisThread.checkSerial"))
								.addEntity("posdtl", TPosdtl.class);
						queryCheck.setLong("serialNo", serialNo);
						queryCheck.setString("deviceId", rt.getDeviceId());
						// 前3天的流水中查找
						queryCheck.setString("startTime", DateUtil.getNewTime(
								startTime, -259200));
						queryCheck.setString("endTime", endTime);
						List listCheck = queryCheck.list();
						if (listCheck.size() == 0) {
							// can not find this serial
							// the serial is lost really

							fSerialNo = serialNo + 1;
							Query queryFive = session
									.createSQLQuery(
											SqlStatementDictionary
													.getIntance()
													.getSQL(
															"com.kingstargroup.action.bgAnalysis.SerialLostAnalysisThread.getnextSerail"))
									.addEntity("posdtl", TPosdtl.class);
							queryFive.setLong("F_serialNo", fSerialNo);
							queryFive.setString("deviceId", rt.getDeviceId());
							queryFive.setString("startTime", DateUtil
									.getNewTime(startTime, -259200));
							queryFive.setString("endTime", endTime);
							List listFive = queryFive.list();
							Iterator iterTwo = listFive.iterator();
							if (iterTwo.hasNext()) {
								// insert into serialosttable
								TPosdtl rcvdtl = (TPosdtl) iterTwo.next();
								if (true == recordOrNot) {
									MapSerialostTable mapSerialost = new MapSerialostTable();
									MapSerialostTableId mapSerialostKey = new MapSerialostTableId();
									mapSerialostKey.setAnalysistime(recordTime);
									mapSerialostKey.setDeviceId(rt
											.getDeviceId().trim());
									mapSerialostKey
											.setSerialNo(Long.parseLong(String
													.valueOf(serialNo)));
									mapSerialost.setId(mapSerialostKey);
									mapSerialost.setTxDate(rcvdtl.getId()
											.getTransdate());
									dateRec = rcvdtl.getId().getTransdate();// 纪录流水时间
									mapSerialost.setTxTime(rcvdtl
											.getTranstime());
									mapSerialost.setContactname(contactName);
									mapSerialost.setSerialReason(Long
											.parseLong("7"));
									mapSerialost.setSerialStatus(Long
											.parseLong("0"));
									session.save(mapSerialost);
								}
								mailRecord++;
								if (!"".equals(mailList)) {
									buffer.append(StringUtil
											.seriallostStringGenerate(rt
													.getDeviceId(),
													device_name, serialNo,
													rcvdtl.getId()
															.getTransdate(),
													rcvdtl.getTranstime(),
													"SERI_LOSS"));
								}
							} else {
								// can not find or means no F_serialNo insert
								// directly with no detail info
								if (true == recordOrNot) {
									MapSerialostTable mapSerialost = new MapSerialostTable();
									MapSerialostTableId mapSerialostKey = new MapSerialostTableId();
									mapSerialostKey.setAnalysistime(recordTime);
									mapSerialostKey.setDeviceId(rt
											.getDeviceId().trim());
									mapSerialostKey.setSerialNo(serialNo);
									mapSerialost.setId(mapSerialostKey);
									mapSerialost.setTxDate(dateRec);

									mapSerialost.setTxTime("000000");
									mapSerialost.setContactname(contactName);
									mapSerialost.setSerialReason(Long
											.parseLong("7"));
									mapSerialost.setSerialStatus(Long
											.parseLong("0"));
									session.save(mapSerialost);
								}
								mailRecord++;
								if (!"".equals(mailList)) {
									buffer.append(StringUtil
											.seriallostStringGenerate(rt
													.getDeviceId(),
													device_name, serialNo,
													dateRec, "000000",
													"SERI_LOSS"));
								}
							}
						}
					}
				}
			}

			Query queryTen = session
					.createSQLQuery(
							SqlStatementDictionary
									.getIntance()
									.getSQL(
											"com.kingstargroup.action.bgAnalysis.SerialLostAnalysisThread.getinLostSerial2"))
					.addEntity("serialost", DeviceSerialLostResult.class);
			queryTen.setString("startTime", startTime);
			queryTen.setString("endTime", endTime);
			List listTen = queryTen.list();
			Iterator iterTen = listTen.iterator();

			while (iterTen.hasNext()) {
				dateRec = "00000000";
				DeviceSerialLostResult serialLost = (DeviceSerialLostResult) iterTen
						.next();
				device_name = DeviceNameDictionary.getInstance().get(
						serialLost.getDeviceId());

				// one srial is lost
				if (1 == serialLost.getDiff()) {
					serialNo = serialLost.getLogic() - serialLost.getTruth();
					Query queryCheck = session
							.createSQLQuery(
									SqlStatementDictionary
											.getIntance()
											.getSQL(
													"com.kingstargroup.action.bgAnalysis.SerialLostAnalysisThread.checkSerial"))
							.addEntity("posdtl", TPosdtl.class);
					queryCheck.setLong("serialNo", serialNo);
					queryCheck.setString("deviceId", serialLost.getDeviceId());
					queryCheck.setString("startTime", DateUtil.getNewTime(
							startTime, -259200));
					queryCheck.setString("endTime", endTime);
					List listCheck = queryCheck.list();
					if (listCheck.size() == 0) {
						// can not find this serial
						// the serial is lost really
						fSerialNo = serialNo + 1;
						Query queryOne = session
								.createSQLQuery(
										SqlStatementDictionary
												.getIntance()
												.getSQL(
														"com.kingstargroup.action.bgAnalysis.SerialLostAnalysisThread.getnextSerail"))
								.addEntity("posdtl", TPosdtl.class);
						queryOne.setLong("F_serialNo", fSerialNo);
						queryOne
								.setString("deviceId", serialLost.getDeviceId());
						queryOne.setString("startTime", DateUtil.getNewTime(
								startTime, -259200));
						queryOne.setString("endTime", endTime);
						List listOne = queryOne.list();
						Iterator iterOne = listOne.iterator();
						if (iterOne.hasNext()) {
							// insert into serialosttable
							TPosdtl rcvdtl = (TPosdtl) iterOne.next();
							if (true == recordOrNot) {
								MapSerialostTable mapSerialost = new MapSerialostTable();
								MapSerialostTableId mapSerialostKey = new MapSerialostTableId();
								mapSerialostKey.setAnalysistime(recordTime);
								mapSerialostKey.setDeviceId(rcvdtl.getId()
										.getDevphyid().trim());
								mapSerialostKey.setSerialNo(serialNo);
								mapSerialost.setId(mapSerialostKey);
								mapSerialost.setTxDate(rcvdtl.getId()
										.getTransdate());
								mapSerialost.setTxTime(rcvdtl.getTranstime());
								mapSerialost.setContactname(contactName);
								mapSerialost.setSerialReason(Long
										.parseLong("7"));
								mapSerialost.setSerialStatus(Long
										.parseLong("0"));
								session.save(mapSerialost);
							}
							mailRecord++;
							if (!"".equals(mailList)) {
								buffer.append(StringUtil
										.seriallostStringGenerate(serialLost
												.getDeviceId(), device_name,
												serialNo, rcvdtl.getId()
														.getTransdate(), rcvdtl
														.getTranstime(),
												"SERI_LOSS"));
							}
						}
					}

				} else if (serialLost.getDiff() <= 50) {
					// more than one lost serial use btree check
					Query queryTwo = session
							.createSQLQuery(
									SqlStatementDictionary
											.getIntance()
											.getSQL(
													"com.kingstargroup.action.bgAnalysis.SerialLostAnalysisThread.getAllSerialNo"))
							.addScalar("serialNo", Hibernate.INTEGER);
					queryTwo.setString("startTime", startTime);
					queryTwo.setString("endTime", endTime);
					queryTwo.setString("deviceId", serialLost.getDeviceId());
					List listTwo = queryTwo.list();
					List returnSerialNo = CheckLostSeriUitl
							.sequenceCheckLostSerial(listTwo);
					Iterator returnIter = returnSerialNo.iterator();
					while (returnIter.hasNext()) {
						serialNo = Long.parseLong(returnIter.next().toString());

						Query queryCheck = session
								.createSQLQuery(
										SqlStatementDictionary
												.getIntance()
												.getSQL(
														"com.kingstargroup.action.bgAnalysis.SerialLostAnalysisThread.checkSerial"))
								.addEntity("posdtl", TPosdtl.class);
						queryCheck.setLong("serialNo", serialNo);
						queryCheck.setString("deviceId", serialLost
								.getDeviceId().trim());
						queryCheck.setString("startTime", startTime);
						queryCheck.setString("endTime", endTime);
						List listCheck = queryCheck.list();
						if (listCheck.size() == 0) {// can not find this serial
							// the serial is lost really
							fSerialNo = serialNo + 1;
							Query queryOne = session
									.createSQLQuery(
											SqlStatementDictionary
													.getIntance()
													.getSQL(
															"com.kingstargroup.action.bgAnalysis.SerialLostAnalysisThread.getnextSerail"))
									.addEntity("posdtl", TPosdtl.class);
							queryOne.setLong("F_serialNo", fSerialNo);
							queryOne.setString("deviceId", serialLost
									.getDeviceId());
							queryOne.setString("startTime", DateUtil
									.getNewTime(startTime, -259200));
							queryOne.setString("endTime", endTime);
							List listOne = queryOne.list();
							Iterator iterOne = listOne.iterator();
							if (iterOne.hasNext()) {
								// insert into serialosttable
								TPosdtl rcvdtl = (TPosdtl) iterOne.next();
								if (true == recordOrNot) {
									MapSerialostTable mapSerialost = new MapSerialostTable();
									MapSerialostTableId mapSerialostKey = new MapSerialostTableId();
									mapSerialostKey.setAnalysistime(recordTime);
									mapSerialostKey.setDeviceId(rcvdtl.getId()
											.getDevphyid().trim());
									mapSerialostKey.setSerialNo(serialNo);
									mapSerialost.setId(mapSerialostKey);
									mapSerialost.setTxDate(rcvdtl.getId()
											.getTransdate());
									dateRec = rcvdtl.getId().getTransdate();// 纪录流水时间
									mapSerialost.setTxTime(rcvdtl
											.getTranstime());
									mapSerialost.setContactname(contactName);
									mapSerialost.setSerialReason(Long
											.parseLong("7"));
									mapSerialost.setSerialStatus(Long
											.parseLong("0"));
									session.save(mapSerialost);
								}
								mailRecord++;
								if (!"".equals(mailList)) {
									buffer.append(StringUtil
											.seriallostStringGenerate(
													serialLost.getDeviceId(),
													device_name, serialNo,
													rcvdtl.getId()
															.getTransdate(),
													rcvdtl.getTranstime(),
													"SERI_LOSS"));
								}
							} else {
								// can not find or means no fSerialNo insert
								// directly with no detail info
								if (true == recordOrNot) {
									MapSerialostTable mapSerialost = new MapSerialostTable();
									MapSerialostTableId mapSerialostKey = new MapSerialostTableId();
									mapSerialostKey.setAnalysistime(recordTime);
									mapSerialostKey.setDeviceId(serialLost
											.getDeviceId().trim());
									mapSerialostKey.setSerialNo(serialNo);
									mapSerialost.setId(mapSerialostKey);
									mapSerialost.setTxDate(dateRec);
									mapSerialost.setTxTime("000000");
									mapSerialost.setContactname(contactName);
									mapSerialost.setSerialReason(Long
											.parseLong("7"));
									mapSerialost.setSerialStatus(Long
											.parseLong("0"));
									session.save(mapSerialost);
								}
								mailRecord++;
								if (!"".equals(mailList)) {
									buffer.append(StringUtil
											.seriallostStringGenerate(
													serialLost.getDeviceId(),
													device_name, serialNo,
													dateRec, "000000",
													"SERI_LOSS"));

								}
							}
						}
					}// for
				}
			}
			session.flush();
			session.clear();

			// max serial_no is less than 65535

			Query query = session
					.createSQLQuery(
							SqlStatementDictionary
									.getIntance()
									.getSQL(
											"com.kingstargroup.action.bgAnalysis.SerialLostAnalysisThread.getinLostSerial1"))
					.addEntity("serialost", DeviceSerialLostResult.class);
			query.setString("startTime", startTime);
			query.setString("endTime", endTime);
			List list = query.list();
			Iterator iter = list.iterator();

			while (iter.hasNext()) {
				dateRec = "00000000";
				DeviceSerialLostResult serialLost = (DeviceSerialLostResult) iter
						.next();
				device_name = DeviceNameDictionary.getInstance().get(
						serialLost.getDeviceId());

				// one srial is lost
				if (1 == serialLost.getDiff()) {
					serialNo = serialLost.getLogic() - serialLost.getTruth();
					Query queryCheck = session
							.createSQLQuery(
									SqlStatementDictionary
											.getIntance()
											.getSQL(
													"com.kingstargroup.action.bgAnalysis.SerialLostAnalysisThread.checkSerial"))
							.addEntity("posdtl", TPosdtl.class);
					queryCheck.setLong("serialNo", serialNo);
					queryCheck.setString("deviceId", serialLost.getDeviceId());
					queryCheck.setString("startTime", DateUtil.getNewTime(
							startTime, -259200));
					queryCheck.setString("endTime", endTime);
					List listCheck = queryCheck.list();
					if (listCheck.size() == 0) {
						// can not find this serial
						// the serial is lost really
						fSerialNo = serialNo + 1;
						Query queryOne = session
								.createSQLQuery(
										SqlStatementDictionary
												.getIntance()
												.getSQL(
														"com.kingstargroup.action.bgAnalysis.SerialLostAnalysisThread.getnextSerail"))
								.addEntity("posdtl", TPosdtl.class);
						queryOne.setLong("F_serialNo", fSerialNo);
						queryOne
								.setString("deviceId", serialLost.getDeviceId().trim());
						queryOne.setString("startTime", DateUtil.getNewTime(
								startTime, -259200));
						queryOne.setString("endTime", endTime);
						List listOne = queryOne.list();
						Iterator iterOne = listOne.iterator();
						if (iterOne.hasNext()) {
							// insert into serialosttable
							TPosdtl rcvdtl = (TPosdtl) iterOne.next();
							if (true == recordOrNot) {
								MapSerialostTable mapSerialost = new MapSerialostTable();
								MapSerialostTableId mapSerialostKey = new MapSerialostTableId();
								mapSerialostKey.setAnalysistime(recordTime);
								mapSerialostKey.setDeviceId(rcvdtl.getId()
										.getDevphyid().trim());
								mapSerialostKey.setSerialNo(serialNo);
								mapSerialost.setId(mapSerialostKey);
								mapSerialost.setTxDate(rcvdtl.getId()
										.getTransdate());
								mapSerialost.setTxTime(rcvdtl.getTranstime());
								mapSerialost.setContactname(contactName);
								mapSerialost.setSerialReason(Long
										.parseLong("7"));
								mapSerialost.setSerialStatus(Long
										.parseLong("0"));
								session.save(mapSerialost);
							}
							mailRecord++;
							if (!"".equals(mailList)) {
								buffer.append(StringUtil
										.seriallostStringGenerate(serialLost
												.getDeviceId(), device_name,
												serialNo, rcvdtl.getId()
														.getTransdate(), rcvdtl
														.getTranstime(),
												"SERI_LOSS"));
							}
						}
					}

				} else if (serialLost.getDiff() <= 50) {
					// more than one lost serial use btree check
					Query queryTwo = session
							.createSQLQuery(
									SqlStatementDictionary
											.getIntance()
											.getSQL(
													"com.kingstargroup.action.bgAnalysis.SerialLostAnalysisThread.getAllSerialNo"))
							.addScalar("serialNo", Hibernate.INTEGER);
					queryTwo.setString("startTime", startTime);
					queryTwo.setString("endTime", endTime);
					queryTwo.setString("deviceId", serialLost.getDeviceId());
					List listTwo = queryTwo.list();
					List returnSerialNo = CheckLostSeriUitl
							.sequenceCheckLostSerial(listTwo);
					Iterator returnIter = returnSerialNo.iterator();
					while (returnIter.hasNext()) {
						serialNo = Long.parseLong(returnIter.next().toString());

						Query queryCheck = session
								.createSQLQuery(
										SqlStatementDictionary
												.getIntance()
												.getSQL(
														"com.kingstargroup.action.bgAnalysis.SerialLostAnalysisThread.checkSerial"))
								.addEntity("posdtl", TPosdtl.class);
						queryCheck.setLong("serialNo", serialNo);
						queryCheck.setString("deviceId", serialLost
								.getDeviceId());
						queryCheck.setString("startTime", startTime);
						queryCheck.setString("endTime", endTime);
						List listCheck = queryCheck.list();
						if (listCheck.size() == 0) {// can not find this serial
							// the serial is lost really
							fSerialNo = serialNo + 1;
							Query queryOne = session
									.createSQLQuery(
											SqlStatementDictionary
													.getIntance()
													.getSQL(
															"com.kingstargroup.action.bgAnalysis.SerialLostAnalysisThread.getnextSerail"))
									.addEntity("posdtl", TPosdtl.class);
							queryOne.setLong("F_serialNo", fSerialNo);
							queryOne.setString("deviceId", serialLost
									.getDeviceId());
							queryOne.setString("startTime", DateUtil
									.getNewTime(startTime, -259200));
							queryOne.setString("endTime", endTime);
							List listOne = queryOne.list();
							Iterator iterOne = listOne.iterator();
							if (iterOne.hasNext()) {
								// insert into serialosttable
								TPosdtl rcvdtl = (TPosdtl) iterOne.next();
								if (true == recordOrNot) {
									MapSerialostTable mapSerialost = new MapSerialostTable();
									MapSerialostTableId mapSerialostKey = new MapSerialostTableId();
									mapSerialostKey.setAnalysistime(recordTime);
									mapSerialostKey.setDeviceId(rcvdtl.getId()
											.getDevphyid().trim());
									mapSerialostKey.setSerialNo(serialNo);
									mapSerialost.setId(mapSerialostKey);
									mapSerialost.setTxDate(rcvdtl.getId()
											.getTransdate());
									dateRec = rcvdtl.getId().getTransdate();// 纪录流水时间
									mapSerialost.setTxTime(rcvdtl
											.getTranstime());
									mapSerialost.setContactname(contactName);
									mapSerialost.setSerialReason(Long
											.parseLong("7"));
									mapSerialost.setSerialStatus(Long
											.parseLong("0"));
									session.save(mapSerialost);
								}
								mailRecord++;
								if (!"".equals(mailList)) {
									buffer.append(StringUtil
											.seriallostStringGenerate(
													serialLost.getDeviceId(),
													device_name, serialNo,
													rcvdtl.getId()
															.getTransdate(),
													rcvdtl.getTranstime(),
													"SERI_LOSS"));
								}
							} else {
								// can not find or means no fSerialNo insert
								// directly with no detail info
								if (true == recordOrNot) {
									MapSerialostTable mapSerialost = new MapSerialostTable();
									MapSerialostTableId mapSerialostKey = new MapSerialostTableId();
									mapSerialostKey.setAnalysistime(recordTime);
									mapSerialostKey.setDeviceId(serialLost
											.getDeviceId().trim());
									mapSerialostKey.setSerialNo(serialNo);
									mapSerialost.setId(mapSerialostKey);
									mapSerialost.setTxDate(dateRec);
									mapSerialost.setTxTime("000000");
									mapSerialost.setContactname(contactName);
									mapSerialost.setSerialReason(Long
											.parseLong("7"));
									mapSerialost.setSerialStatus(Long
											.parseLong("0"));
									session.save(mapSerialost);
								}
								mailRecord++;
								if (!"".equals(mailList)) {
									buffer.append(StringUtil
											.seriallostStringGenerate(
													serialLost.getDeviceId(),
													device_name, serialNo,
													dateRec, "000000",
													"SERI_LOSS"));

								}
							}
						}
					}// for
				}
			}
			session.flush();
			session.clear();

			// max serial_no is 65535
			Query queryTwo = session
					.createSQLQuery(
							SqlStatementDictionary
									.getIntance()
									.getSQL(
											"com.kingstargroup.action.bgAnalysis.SerialLostAnalysisThread.getSpecialDevice"))
					.addScalar("deviceId", Hibernate.STRING);
			queryTwo.setString("startTime", startTime);
			queryTwo.setString("endTime", endTime);
			List listTwo = queryTwo.list();
			String deviceId = "00000000";
			String specialTime = "";
			for (int i = 0; i < listTwo.size(); i++) {
				dateRec = "00000000";
				deviceId = listTwo.get(i).toString().trim();
				device_name = DeviceNameDictionary.getInstance().get(deviceId);
				Query queryThree = session
						.createSQLQuery(
								SqlStatementDictionary
										.getIntance()
										.getSQL(
												"com.kingstargroup.action.bgAnalysis.SerialLostAnalysisThread.getcoltimestamp"))
						.addScalar("dateTime", Hibernate.STRING);
				queryThree.setString("startTime", startTime);
				queryThree.setString("endTime", endTime);
				queryThree.setString("deviceId", deviceId);
				List listThree = queryThree.list();
				if (listThree.size() > 0) {
					specialTime = listThree.get(0).toString();
				}
				// Query queryFour = session.getNamedQuery("DeviceSerialLost");
				Query queryFour = session
						.createSQLQuery(
								SqlStatementDictionary
										.getIntance()
										.getSQL(
												"com.kingstargroup.action.bgAnalysis.SerialLostAnalysisThread.getAllSerialNo"))
						.addScalar("serialNo", Hibernate.STRING);
				queryFour.setString("startTime", startTime);
				queryFour.setString("endTime", specialTime);
				queryFour.setString("deviceId", deviceId);
				List ListFour = queryFour.list();
				List returnSerialNo = CheckLostSeriUitl
						.sequenceCheckLostSerial(ListFour);
				if ((returnSerialNo != null) && (returnSerialNo.size() < 50)) {// 假设五十条以上的都有问题，属于流水突变的范畴
					Iterator returnIter = returnSerialNo.iterator();
					while (returnIter.hasNext()) {
						serialNo = Long.parseLong(returnIter.next().toString());

						Query queryCheck = session
								.createSQLQuery(
										SqlStatementDictionary
												.getIntance()
												.getSQL(
														"com.kingstargroup.action.bgAnalysis.SerialLostAnalysisThread.checkSerial"))
								.addEntity("posdtl", TPosdtl.class);
						queryCheck.setLong("serialNo", serialNo);
						queryCheck.setString("deviceId", deviceId);
						queryCheck.setString("startTime", DateUtil.getNewTime(
								startTime, -259200));
						queryCheck.setString("endTime", endTime);
						List listCheck = queryCheck.list();
						if (listCheck.size() == 0) {// can not find this serial
							// the serial is lost really

							fSerialNo = serialNo + 1;
							Query queryFive = session
									.createSQLQuery(
											SqlStatementDictionary
													.getIntance()
													.getSQL(
															"com.kingstargroup.action.bgAnalysis.SerialLostAnalysisThread.getnextSerail"))
									.addEntity("posdtl", TPosdtl.class);
							queryFive.setLong("F_serialNo", fSerialNo);
							queryFive.setString("deviceId", deviceId);
							queryFive.setString("startTime", DateUtil
									.getNewTime(startTime, -259200));
							queryFive.setString("endTime", endTime);
							List listFive = queryFive.list();
							Iterator iterTwo = listFive.iterator();
							if (iterTwo.hasNext()) {
								// insert into serialosttable
								TPosdtl rcvdtl = (TPosdtl) iterTwo.next();
								if (true == recordOrNot) {
									MapSerialostTable mapSerialost = new MapSerialostTable();
									MapSerialostTableId mapSerialostKey = new MapSerialostTableId();
									mapSerialostKey.setAnalysistime(recordTime);
									mapSerialostKey.setDeviceId(deviceId);
									mapSerialostKey.setSerialNo(serialNo);
									mapSerialost.setId(mapSerialostKey);
									mapSerialost.setTxDate(rcvdtl.getId()
											.getTransdate());
									dateRec = rcvdtl.getId().getTransdate();// 纪录流水时间
									mapSerialost.setTxTime(rcvdtl
											.getTranstime());
									mapSerialost.setContactname(contactName);
									mapSerialost.setSerialReason(Long
											.parseLong("7"));
									mapSerialost.setSerialStatus(Long
											.parseLong("0"));
									session.save(mapSerialost);
								}
								mailRecord++;
								if (!"".equals(mailList)) {
									buffer.append(StringUtil
											.seriallostStringGenerate(deviceId,
													device_name, serialNo,
													rcvdtl.getId()
															.getTransdate(),
													rcvdtl.getTranstime(),
													"SERI_LOSS"));
								}
							} else {
								// can not find or means no fSerialNo insert
								// directly with no detail info
								if (true == recordOrNot) {
									MapSerialostTable mapSerialost = new MapSerialostTable();
									MapSerialostTableId mapSerialostKey = new MapSerialostTableId();
									mapSerialostKey.setAnalysistime(recordTime);
									mapSerialostKey.setDeviceId(deviceId);
									mapSerialostKey.setSerialNo(serialNo);
									mapSerialost.setId(mapSerialostKey);
									mapSerialost.setTxDate(dateRec);

									mapSerialost.setTxTime("000000");
									mapSerialost.setContactname(contactName);
									mapSerialost.setSerialReason(Long
											.parseLong("7"));
									mapSerialost.setSerialStatus(Long
											.parseLong("0"));
									session.save(mapSerialost);
								}
								mailRecord++;
								if (!"".equals(mailList)) {
									buffer.append(StringUtil
											.seriallostStringGenerate(deviceId,
													device_name, serialNo,
													dateRec, "000000",
													"SERI_LOSS"));
								}
							}
						}
					}
				}

				// 后半段
				Query querySix = session
						.createSQLQuery(
								SqlStatementDictionary
										.getIntance()
										.getSQL(
												"com.kingstargroup.action.bgAnalysis.SerialLostAnalysisThread.getAllSerialNo"))
						.addScalar("serialNo", Hibernate.STRING);
				querySix.setString("startTime", specialTime);
				querySix.setString("endTime", endTime);
				querySix.setString("deviceId", deviceId);
				List ListSix = querySix.list();
				List returnSerialNo1 = CheckLostSeriUitl
						.sequenceCheckLostSerial(ListSix);
				if ((returnSerialNo1 != null) && (returnSerialNo1.size() < 50)) {// 假设五十条以上的都有问题，属于流水突变的范畴
					Iterator returnIter = returnSerialNo1.iterator();
					while (returnIter.hasNext()) {
						serialNo = Long.parseLong(returnIter.next().toString());

						Query queryCheck = session
								.createSQLQuery(
										SqlStatementDictionary
												.getIntance()
												.getSQL(
														"com.kingstargroup.action.bgAnalysis.SerialLostAnalysisThread.checkSerial"))
								.addEntity("posdtl", TPosdtl.class);
						queryCheck.setLong("serialNo", serialNo);
						queryCheck.setString("deviceId", deviceId);
						queryCheck.setString("startTime", DateUtil.getNewTime(
								startTime, -259200));
						queryCheck.setString("endTime", endTime);
						List listCheck = queryCheck.list();
						if (listCheck.size() == 0) {// can not find this serial
							// the serial is lost really

							fSerialNo = serialNo + 1;
							Query querySeven = session
									.createSQLQuery(
											SqlStatementDictionary
													.getIntance()
													.getSQL(
															"com.kingstargroup.action.bgAnalysis.SerialLostAnalysisThread.getnextSerail"))
									.addEntity("posdtl", TPosdtl.class);
							querySeven.setLong("F_serialNo", fSerialNo);
							querySeven.setString("deviceId", deviceId);
							querySeven.setString("startTime", DateUtil
									.getNewTime(startTime, -259200));
							querySeven.setString("endTime", endTime);
							List listSeven = querySeven.list();
							Iterator iterTwo = listSeven.iterator();
							if (iterTwo.hasNext()) {
								// insert into serialosttable
								TPosdtl rcvdtl = (TPosdtl) iterTwo.next();
								if (true == recordOrNot) {
									MapSerialostTable mapSerialost = new MapSerialostTable();
									MapSerialostTableId mapSerialostKey = new MapSerialostTableId();
									mapSerialostKey.setAnalysistime(recordTime);
									mapSerialostKey.setDeviceId(deviceId);
									mapSerialostKey.setSerialNo(serialNo);
									mapSerialost.setId(mapSerialostKey);
									mapSerialost.setTxDate(rcvdtl.getId()
											.getTransdate());
									dateRec = rcvdtl.getId().getTransdate();// 纪录流水时间
									mapSerialost.setTxTime(rcvdtl
											.getTranstime());
									mapSerialost.setContactname(contactName);
									mapSerialost.setSerialReason(Long
											.parseLong("7"));
									mapSerialost.setSerialStatus(Long
											.parseLong("0"));
									session.save(mapSerialost);
								}
								mailRecord++;
								if (!"".equals(mailList)) {
									buffer.append(StringUtil
											.seriallostStringGenerate(deviceId,
													device_name, serialNo,
													rcvdtl.getId()
															.getTransdate(),
													rcvdtl.getTranstime(),
													"SERI_LOSS"));
								}
							} else {
								// can not find or means no fSerialNo insert
								// directly with no detail info
								if (true == recordOrNot) {
									MapSerialostTable mapSerialost = new MapSerialostTable();
									MapSerialostTableId mapSerialostKey = new MapSerialostTableId();
									mapSerialostKey.setAnalysistime(recordTime);
									mapSerialostKey.setDeviceId(deviceId);
									mapSerialostKey.setSerialNo(serialNo);
									mapSerialost.setId(mapSerialostKey);
									mapSerialost.setTxDate(dateRec);

									mapSerialost.setTxTime("000000");
									mapSerialost.setContactname(contactName);
									mapSerialost.setSerialReason(Long
											.parseLong("7"));
									mapSerialost.setSerialStatus(Long
											.parseLong("0"));
									session.save(mapSerialost);
								}
								mailRecord++;
								if (!"".equals(mailList)) {
									buffer.append(StringUtil
											.seriallostStringGenerate(deviceId,
													device_name, serialNo,
													dateRec, "000000",
													"SERI_LOSS"));

								}
							}
						}
					}
				}
			}
			session.flush();
			session.clear();

			// record timepoint analysis
			Object tempAnalysis = session.get(MapAnalysisPoint.class,
					"SERI_LOSS");
			MapAnalysisPoint analysisPoint = null;
			if (tempAnalysis == null) {
				analysisPoint = new MapAnalysisPoint();
				analysisPoint.setAnalysisname("SERI_LOSS");
				analysisPoint.setAnalysispoint(endTime);
				session.save(analysisPoint);
			} else {
				analysisPoint = (MapAnalysisPoint) tempAnalysis;
				analysisPoint.setAnalysispoint(endTime);
				session.update(analysisPoint);
			}
			tx.commit();

		} catch (HibernateException e) {
			logger.error("流水缺失分析线程出现以下异常：", e); //$NON-NLS-1$

			if (tx != null) {
				try {
					tx.rollback();
				} catch (Exception e1) {
					// TODO: handle exception
					e1.printStackTrace();
				}
			}

		} catch (Exception e) {
			logger.error("流水缺失分析线程出现以下异常：", e); //$NON-NLS-1$
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

		try {
			// mail
			sendMail();
			// SMG
			sendSMG();
		} catch (Exception e) {
			// TODO: handle exception
			logger.error("流水缺失分析线程出现以下异常：", e); //$NON-NLS-1$
		}
		// sleep thread follows the setting
		try {
			long sleepTime = Long.parseLong(String.valueOf(doubleCycle * 1000))
					- DateUtil.getIntervalTime(DateUtil.getNow(), recordTime);
			if (logger.isInfoEnabled()) {
				logger
						.info("流水缺失分析线程结束进入休眠状态!"
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
			logger.error("流水缺失分析线程出现以下异常：可能被强行停止！ ", e); //$NON-NLS-1$
		} catch (Exception e) {
			logger.error("流水缺失分析线程出现以下异常：可能被强行停止！ ", e); //$NON-NLS-1$
		}
	}

	public void terminate() {
		// TODO Auto-generated method stub
		if (this.isAlive()) {
			logger.warn("流水缺失分析线程状态被请求，此时线程状态：活动线程!"); //$NON-NLS-1$
			requestStop = true;
		} else {
			logger.warn("流水缺失分析线程状态被请求，此时线程状态：死亡线程!"); //$NON-NLS-1$
			this.destroy();

		}
	}

	public boolean isTerminate() {
		// TODO Auto-generated method stub
		return this.isAlive();
	}

	public void sendMail() {

		if ((true == mailOrNot) && (!"".equals(mailList))
				&& (0 != buffer.size())) {
			if (logger.isInfoEnabled()) {
				logger.info("流水缺失分析线程发送邮件给联系人:" + contactName);
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
									.serialostMailGenerate(nameList[i],
											DateUtil.reFormatTime(recordTime),
											mailRecord, tmpStr, "SERI_LOSS"));
				}
			}
		}
	}

	public void sendSMG() {
		// TODO Auto-generated method stub
		if ((true == smgOrNot) && (!"".equals(phoneNumber)) && mailRecord > 0) {
			if (logger.isInfoEnabled()) {
				logger.info("流水缺失分析线程发送短信给联系人:" + contactName);
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
							"SERI_LOSS");
					CommonSendSMGUtil.sendSMG(tempList[i], SmgMessage);
				}
			}

		}
	}

}
