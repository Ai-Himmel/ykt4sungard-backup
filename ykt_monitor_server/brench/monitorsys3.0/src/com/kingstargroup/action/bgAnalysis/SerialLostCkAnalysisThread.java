package com.kingstargroup.action.bgAnalysis;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: SerialLostAnalysisThread
 * Description: ��ˮȱʧ����߳���
 * Modify History����Change Log��:  
 * �������ͣ��������޸ĵȣ�   ��������     ������    �������ݼ���
 * ����  				2005-10-19   ������    ��ˮȱʧ����߳�
 * �޸�					2006-7-17    ������    ���ģ��Բ�ѯ�ķ�ʽ�������޸�
 * <p>
 *
 * @author      ������
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

public class SerialLostCkAnalysisThread extends Thread implements
		AnalyzeThreadInterface {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(SerialLostCkAnalysisThread.class);

	// flag of stop this thread
	private static boolean requestStop = false;

	// record analysis time
	private String recordTime = "";

	// default analysis is to analysis all from
	public String startTime = "20050101000000";

	public String endTime = DateUtil.getNow();

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
			logger.info("**************��ˮȱʧ�ع�����̳߳�ʼ��**************"); //$NON-NLS-1$
		}

		// TODO Auto-generated method stub
		try {
			Session session = HibernateSessionFactory.currentSession();
			Query queryTime = session
					.createQuery("from MapAnalysisPoint as point where point.analysisname=:analysisName");
			queryTime.setString("analysisName", "SERI_LOSS");
			Iterator iterTime = queryTime.iterate();
			if (iterTime.hasNext()) {
				MapAnalysisPoint mapAnalysisPoint = (MapAnalysisPoint) iterTime
						.next();
				this.startTime = mapAnalysisPoint.getAnalysispoint();
			}
			Query queryCycle = session
					.createQuery("from MapParamTable as param where param.parameter=:paramRefer");
			queryCycle.setString("paramRefer", "TradeLackCkCycle");
			Iterator iterParam = queryCycle.iterate();
			if (iterParam.hasNext()) {
				MapParamTable mapParamTable = (MapParamTable) iterParam.next();
				this.cycle = mapParamTable.getValue();
			}
			String s = String.valueOf(cycle * 24 * 3600);
			this.doubleCycle = Integer.parseInt(s.substring(0, s.indexOf('.')));
			if (!"20050101000000".equals(this.startTime)) {
				this.endTime = DateUtil.getNewTime(startTime, doubleCycle);
			} else {
				this.endTime = DateUtil.getNow();
				this.startTime = DateUtil
						.getNewTime(this.endTime, -doubleCycle);
			}

		} catch (HibernateException e) {
			logger.error("��ˮȱʧ�ع�����̳߳�ʼ��ʧ�ܣ�", e); //$NON-NLS-1$

		} finally {
			HibernateSessionFactory.closeSession();
		}

		if (logger.isInfoEnabled()) {
			logger.info("**************��ˮȱʧ�ع�����̳߳�ʼ���ɹ�**************"); //$NON-NLS-1$
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
				.createQuery("from MapParamTable as param where param.parameter=:paramRefer");
		queryCycle.setString("paramRefer", "TradeLackCkCycle");
		Iterator iterParam = queryCycle.iterate();
		if (iterParam.hasNext()) {
			MapParamTable mapParamTable = (MapParamTable) iterParam.next();
			this.cycle = mapParamTable.getValue();
		}
		String s = String.valueOf(cycle * 24 * 3600);
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
			logger.info("��ˮȱʧ�ع�����߳̿�ʼ��������"); //$NON-NLS-1$
		}

		Transaction tx = null;
		try {
			Session session = HibernateSessionFactory.currentSession();
			tx = session.beginTransaction();

			this.accelateParam = Integer
					.parseInt(BgMonitor.getIntance().SerialLostAnalysisThreadaccelateParam);
			endTime = DateUtil.getNewTime(endTime, accelateParam * 24 * 3600);
			if (logger.isInfoEnabled()) {
				logger
						.info("��ˮȱʧ�ع�����߳̿�ʼ����ʱ��:" + DateUtil.getNow("yyyy/MM/dd/HH:mm:ss")); //$NON-NLS-1$
			}
			if (1 > DateUtil.checkTimeSequence(endTime, DateUtil.getNow())) {
				if (logger.isInfoEnabled()) {
					logger.info("��ˮȱʧ�ع�����̷߳���ʱ��Σ�" + startTime + " -- "
							+ endTime);
				}
			} else {
				endTime = DateUtil.getNow();
				if (logger.isInfoEnabled()) {
					logger.info("��ˮȱʧ�ع�����̷߳���ʱ��Σ�" + startTime + " -- "
							+ endTime);
				}
			}
			// get new parameter timely!
			getParameter(session);

			// analysis time record
			recordTime = DateUtil.getNow();
			// ״̬����
			BgMonitor
					.monitorThreadStatusReport(
							"com.kingstargroup.action.bgAnalysis.SerialLostAnalysisThread",
							"��ˮȱʧ�ع�����߳�", DateUtil
									.getNow("yyyy/MM/dd/HH:mm:ss"), String
									.valueOf(this.doubleCycle), "������...");

			// String dateTime = this.startTime.substring(0, 8);
			// String dateTime1 = this.endTime.substring(0, 8);

			// max serial_no is less than 65535

			Query query = session
					.createSQLQuery(
							SqlStatementDictionary
									.getIntance()
									.getSQL(
											"com.kingstargroup.action.bgAnalysis.SerialLostCkAnalysisThread.getCheckLostSerial"))
					.addEntity("serialost", DeviceSerialLostResult.class);
			query.setString("startTime", startTime);
			query.setString("endTime", endTime);
			query.setString("startDate", startTime.substring(0, 8));
			query.setString("endDate", endTime.substring(0, 8));
			List list = query.list();
			Iterator iter = list.iterator();
			String device_name = "";
			long serialNo = 0;
			long F_serialNo = 0;
			String dateRec = "00000000";
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
													"com.kingstargroup.action.bgAnalysis.SerialLostCkAnalysisThread.getdeviceSerial"))
							.addEntity("posdtl", TPosdtl.class);
					queryCheck.setLong("serialNo", serialNo);
					queryCheck.setString("deviceId", serialLost.getDeviceId());
					queryCheck.setString("startTime", startTime);
					queryCheck.setString("endTime", endTime);
					queryCheck
							.setString("startDate", startTime.substring(0, 8));
					queryCheck.setString("endDate", endTime.substring(0, 8));
					List listCheck = queryCheck.list();
					if (listCheck.size() == 0) {// can not find this serial
						// check whether it has found by another thread
						if (!CheckSerialost(session, serialLost.getDeviceId(),
								serialNo)) {
							// if not
							// a new lost serial has found
							// a serial is lost really
							F_serialNo = serialNo + 1;
							Query queryOne = session
									.createSQLQuery(
											SqlStatementDictionary
													.getIntance()
													.getSQL(
															"com.kingstargroup.action.bgAnalysis.SerialLostCkAnalysisThread.checklostornot"))
									.addEntity("posdtl", TPosdtl.class);
							queryOne.setLong("F_serialNo", F_serialNo);
							queryOne.setString("deviceId", serialLost
									.getDeviceId());
							queryOne.setString("startTime", startTime);
							queryOne.setString("endTime", endTime);
							queryOne.setString("startDate", startTime
									.substring(0, 8));
							queryOne.setString("endDate", endTime.substring(0,
									8));
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
											.getDevphyid());
									mapSerialostKey.setSerialNo(serialNo);
									mapSerialost.setId(mapSerialostKey);
									mapSerialost.setTxDate(rcvdtl.getId()
											.getTransdate());
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
													"com.kingstargroup.action.bgAnalysis.SerialLostCkAnalysisThread.getcerttimeserial"))
							.addScalar("serialNo", Hibernate.INTEGER);
					queryTwo.setString("startTime", startTime);
					queryTwo.setString("endTime", endTime);
					queryTwo.setString("startDate", startTime.substring(0, 8));
					queryTwo.setString("endDate", endTime.substring(0, 8));
					queryTwo.setString("deviceId", serialLost.getDeviceId());
					List listTwo = queryTwo.list();
					List returnSerialNo = CheckLostSeriUitl
							.sequenceCheckLostSerial(listTwo);
					Iterator returnIter = returnSerialNo.iterator();
					while (returnIter.hasNext()) {
						serialNo = Integer.parseInt(returnIter.next()
								.toString());

						Query queryCheck = session
								.createSQLQuery(
										SqlStatementDictionary
												.getIntance()
												.getSQL(
														"com.kingstargroup.action.bgAnalysis.SerialLostCkAnalysisThread.getdeviceSerial"))
								.addEntity("posdtl", TPosdtl.class);
						queryCheck.setLong("serialNo", serialNo);
						queryCheck.setString("deviceId", serialLost
								.getDeviceId());
						queryCheck.setString("startTime", startTime);
						queryCheck.setString("endTime", endTime);
						queryCheck.setString("startDate", startTime.substring(
								0, 8));
						queryCheck
								.setString("endDate", endTime.substring(0, 8));
						List listCheck = queryCheck.list();
						if (listCheck.size() == 0) {
							// can not find this serial
							// the serial is lost really
							if (!CheckSerialost(session, serialLost
									.getDeviceId(), serialNo)) {
								F_serialNo = serialNo + 1;
								Query queryOne = session
										.createSQLQuery(
												SqlStatementDictionary
														.getIntance()
														.getSQL(
																"com.kingstargroup.action.bgAnalysis.SerialLostCkAnalysisThread.checklostornot"))
										.addEntity("posdtl", TPosdtl.class);
								queryOne.setLong("F_serialNo", F_serialNo);
								queryOne.setString("deviceId", serialLost
										.getDeviceId());
								queryOne.setString("startTime", startTime);
								queryOne.setString("endTime", endTime);
								queryOne.setString("startDate", startTime
										.substring(0, 8));
								queryOne.setString("endDate", endTime
										.substring(0, 8));
								List listOne = queryOne.list();
								Iterator iterOne = listOne.iterator();
								if (iterOne.hasNext()) {
									// insert into serialosttable
									TPosdtl rcvdtl = (TPosdtl) iterOne.next();
									if (true == recordOrNot) {
										MapSerialostTable mapSerialost = new MapSerialostTable();
										MapSerialostTableId mapSerialostKey = new MapSerialostTableId();
										mapSerialostKey
												.setAnalysistime(recordTime);
										mapSerialostKey.setDeviceId(rcvdtl
												.getId().getDevphyid());
										mapSerialostKey.setSerialNo(serialNo);
										mapSerialost.setId(mapSerialostKey);
										mapSerialost.setTxDate(rcvdtl.getId()
												.getTransdate());
										dateRec = rcvdtl.getId().getTransdate();// ��¼��ˮʱ��
										mapSerialost.setTxTime(rcvdtl
												.getTranstime());
										mapSerialost
												.setContactname(contactName);
										mapSerialost.setSerialReason(Long
												.parseLong("7"));
										mapSerialost.setSerialStatus(Long
												.parseLong("0"));
										session.save(mapSerialost);
									}
									mailRecord++;
									if (!"".equals(mailList)) {
										buffer
												.append(StringUtil
														.seriallostStringGenerate(
																serialLost
																		.getDeviceId(),
																device_name,
																serialNo,
																rcvdtl
																		.getId()
																		.getTransdate(),
																rcvdtl
																		.getTranstime(),
																"SERI_LOSS"));
									}
								} else {
									// can not find or means no F_serialNo
									// insert
									// directly with no detail info
									if (true == recordOrNot) {
										MapSerialostTable mapSerialost = new MapSerialostTable();
										MapSerialostTableId mapSerialostKey = new MapSerialostTableId();
										mapSerialostKey
												.setAnalysistime(recordTime);
										mapSerialostKey.setDeviceId(serialLost
												.getDeviceId());
										mapSerialostKey.setSerialNo(serialNo);
										mapSerialost.setId(mapSerialostKey);
										mapSerialost.setTxDate(dateRec);
										mapSerialost.setTxTime("000000");
										mapSerialost
												.setContactname(contactName);
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
														serialLost
																.getDeviceId(),
														device_name, serialNo,
														dateRec, "000000",
														"SERI_LOSS"));

									}
								}
							}

						}
					}// for
				} else {

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
											"com.kingstargroup.action.bgAnalysis.SerialLostCkAnalysisThread.getspedeviceid"))
					.addScalar("deviceId", Hibernate.STRING);

			queryTwo.setString("startTime", startTime);
			queryTwo.setString("endTime", endTime);
			queryTwo.setString("startDate", startTime.substring(0, 8));
			queryTwo.setString("endDate", endTime.substring(0, 8));
			List listTwo = queryTwo.list();
			String deviceId = "00000000";
			String specialTime = "";
			for (int i = 0; i < listTwo.size(); i++) {
				dateRec = "00000000";
				deviceId = listTwo.get(i).toString();
				device_name = DeviceNameDictionary.getInstance().get(deviceId);
				Query queryThree = session
						.createSQLQuery(
								SqlStatementDictionary
										.getIntance()
										.getSQL(
												"com.kingstargroup.action.bgAnalysis.SerialLostCkAnalysisThread.getspedeviceidserial"))
						.addScalar("dateTime", Hibernate.STRING);
				queryThree.setString("startTime", startTime);
				queryThree.setString("endTime", endTime);
				queryThree.setString("startDate", startTime.substring(0, 8));
				queryThree.setString("endDate", endTime.substring(0, 8));
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
												"com.kingstargroup.action.bgAnalysis.SerialLostCkAnalysisThread.getspedeviceidserialno"))
						.addScalar("serialNo", Hibernate.STRING);
				queryFour.setString("startTime", startTime);
				queryFour.setString("endTime", specialTime);
				queryFour.setString("startDate", startTime.substring(0, 8));
				queryFour.setString("endDate", specialTime.substring(0, 8));
				queryFour.setString("deviceId", deviceId);
				List ListFour = queryFour.list();
				List returnSerialNo = CheckLostSeriUitl
						.sequenceCheckLostSerial(ListFour);
				if ((returnSerialNo != null) && (returnSerialNo.size() < 50)) {// ������ʮ�����ϵĶ������⣬������ˮͻ��ķ���
					Iterator returnIter = returnSerialNo.iterator();
					while (returnIter.hasNext()) {
						serialNo = Integer.parseInt(returnIter.next()
								.toString());

						Query queryCheck = session
								.createSQLQuery(
										SqlStatementDictionary
												.getIntance()
												.getSQL(
														"com.kingstargroup.action.bgAnalysis.SerialLostCkAnalysisThread.getdeviceSerial"))
								.addEntity("posdtl", TPosdtl.class);
						queryCheck.setLong("serialNo", serialNo);
						queryCheck.setString("deviceId", deviceId);
						queryCheck.setString("startTime", startTime);
						queryCheck.setString("endTime", endTime);
						queryCheck.setString("startDate", startTime.substring(
								0, 8));
						queryCheck
								.setString("endDate", endTime.substring(0, 8));
						List listCheck = queryCheck.list();
						if (listCheck.size() == 0) {// can not find this serial
							// the serial is lost really
							if (!CheckSerialost(session, deviceId, serialNo)) {
								F_serialNo = serialNo + 1;
								Query queryFive = session
										.createSQLQuery(
												SqlStatementDictionary
														.getIntance()
														.getSQL(
																"com.kingstargroup.action.bgAnalysis.SerialLostCkAnalysisThread.checklostornot"))
										.addEntity("posdtl", TPosdtl.class);
								queryFive.setLong("F_serialNo", F_serialNo);
								queryFive.setString("deviceId", deviceId);
								queryFive.setString("startTime", startTime);
								queryFive.setString("endTime", endTime);
								queryFive.setString("startDate", startTime
										.substring(0, 8));
								queryFive.setString("endDate", endTime
										.substring(0, 8));
								List listFive = queryFive.list();
								Iterator iterTwo = listFive.iterator();
								if (iterTwo.hasNext()) {
									// insert into serialosttable
									TPosdtl rcvdtl = (TPosdtl) iterTwo.next();
									if (true == recordOrNot) {
										MapSerialostTable mapSerialost = new MapSerialostTable();
										MapSerialostTableId mapSerialostKey = new MapSerialostTableId();
										mapSerialostKey
												.setAnalysistime(recordTime);
										mapSerialostKey.setDeviceId(deviceId);
										mapSerialostKey.setSerialNo(serialNo);
										mapSerialost.setId(mapSerialostKey);
										mapSerialost.setTxDate(rcvdtl.getId()
												.getTransdate());
										dateRec = rcvdtl.getId().getTransdate();// ��¼��ˮʱ��
										mapSerialost.setTxTime(rcvdtl
												.getTranstime());
										mapSerialost
												.setContactname(contactName);
										mapSerialost.setSerialReason(Long
												.parseLong("7"));
										mapSerialost.setSerialStatus(Long
												.parseLong("0"));
										session.save(mapSerialost);
									}
									mailRecord++;
									if (!"".equals(mailList)) {
										buffer
												.append(StringUtil
														.seriallostStringGenerate(
																deviceId,
																device_name,
																serialNo,
																rcvdtl
																		.getId()
																		.getTransdate(),
																rcvdtl
																		.getTranstime(),
																"SERI_LOSS"));
									}
								} else {
									// can not find or means no F_serialNo
									// insert
									// directly with no detail info
									if (true == recordOrNot) {
										MapSerialostTable mapSerialost = new MapSerialostTable();
										MapSerialostTableId mapSerialostKey = new MapSerialostTableId();
										mapSerialostKey
												.setAnalysistime(recordTime);
										mapSerialostKey.setDeviceId(deviceId);
										mapSerialostKey.setSerialNo(serialNo);
										mapSerialost.setId(mapSerialostKey);
										mapSerialost.setTxDate(dateRec);

										mapSerialost.setTxTime("000000");
										mapSerialost
												.setContactname(contactName);
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
														deviceId, device_name,
														serialNo, dateRec,
														"000000", "SERI_LOSS"));
									}
								}
							}

						}
					}
				}

				// ����
				Query querySix = session
						.createSQLQuery(
								SqlStatementDictionary
										.getIntance()
										.getSQL(
												"com.kingstargroup.action.bgAnalysis.SerialLostCkAnalysisThread.getcerttimeserial"))
						.addScalar("serialNo", Hibernate.STRING);
				querySix.setString("startTime", specialTime);
				querySix.setString("endTime", endTime);
				querySix.setString("startDate", specialTime.substring(0, 8));
				querySix.setString("endDate", endTime.substring(0, 8));
				querySix.setString("deviceId", deviceId);
				List ListSix = querySix.list();
				List returnSerialNo1 = CheckLostSeriUitl
						.sequenceCheckLostSerial(ListSix);
				if ((returnSerialNo1 != null) && (returnSerialNo1.size() < 50)) {// ������ʮ�����ϵĶ������⣬������ˮͻ��ķ���
					Iterator returnIter = returnSerialNo1.iterator();
					while (returnIter.hasNext()) {
						serialNo = Integer.parseInt(returnIter.next()
								.toString());

						Query queryCheck = session
								.createSQLQuery(
										SqlStatementDictionary
												.getIntance()
												.getSQL(
														"com.kingstargroup.action.bgAnalysis.SerialLostCkAnalysisThread.getdeviceSerial"))
								.addEntity("posdtl", TPosdtl.class);
						queryCheck.setLong("serialNo", serialNo);
						queryCheck.setString("deviceId", deviceId);
						queryCheck.setString("startTime", startTime);
						queryCheck.setString("endTime", endTime);
						queryCheck.setString("startDate", startTime.substring(
								0, 8));
						queryCheck
								.setString("endDate", endTime.substring(0, 8));
						List listCheck = queryCheck.list();
						if (listCheck.size() == 0) {// can not find this serial
							// the serial is lost really
							if (!CheckSerialost(session, deviceId, serialNo)) {
								F_serialNo = serialNo + 1;
								Query querySeven = session
										.createSQLQuery(
												SqlStatementDictionary
														.getIntance()
														.getSQL(
																"com.kingstargroup.action.bgAnalysis.SerialLostCkAnalysisThread.checklostornot"))
										.addEntity("posdtl", TPosdtl.class);
								querySeven.setLong("F_serialNo", F_serialNo);
								querySeven.setString("deviceId", deviceId);
								querySeven.setString("startTime", startTime);
								querySeven.setString("endTime", endTime);
								querySeven.setString("startDate", startTime
										.substring(0, 8));
								querySeven.setString("endDate", endTime
										.substring(0, 8));
								List listSeven = querySeven.list();
								Iterator iterTwo = listSeven.iterator();
								if (iterTwo.hasNext()) {
									// insert into serialosttable
									TPosdtl rcvdtl = (TPosdtl) iterTwo.next();
									if (true == recordOrNot) {
										MapSerialostTable mapSerialost = new MapSerialostTable();
										MapSerialostTableId mapSerialostKey = new MapSerialostTableId();
										mapSerialostKey
												.setAnalysistime(recordTime);
										mapSerialostKey.setDeviceId(deviceId);
										mapSerialostKey.setSerialNo(serialNo);
										mapSerialost.setId(mapSerialostKey);
										mapSerialost.setTxDate(rcvdtl.getId()
												.getTransdate());
										dateRec = rcvdtl.getId().getTransdate();// ��¼��ˮʱ��
										mapSerialost.setTxTime(rcvdtl
												.getTranstime());
										mapSerialost
												.setContactname(contactName);
										mapSerialost.setSerialReason(Long
												.parseLong("7"));
										mapSerialost.setSerialStatus(Long
												.parseLong("0"));
										session.save(mapSerialost);
									}
									mailRecord++;
									if (!"".equals(mailList)) {
										buffer
												.append(StringUtil
														.seriallostStringGenerate(
																deviceId,
																device_name,
																serialNo,
																rcvdtl
																		.getId()
																		.getTransdate(),
																rcvdtl
																		.getTranstime(),
																"SERI_LOSS"));
									}
								} else {
									// can not find or means no F_serialNo
									// insert
									// directly with no detail info
									if (true == recordOrNot) {
										MapSerialostTable mapSerialost = new MapSerialostTable();
										MapSerialostTableId mapSerialostKey = new MapSerialostTableId();
										mapSerialostKey
												.setAnalysistime(recordTime);
										mapSerialostKey.setDeviceId(deviceId);
										mapSerialostKey.setSerialNo(serialNo);
										mapSerialost.setId(mapSerialostKey);
										mapSerialost.setTxDate(dateRec);

										mapSerialost.setTxTime("000000");
										mapSerialost
												.setContactname(contactName);
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
														deviceId, device_name,
														serialNo, dateRec,
														"000000", "SERI_LOSS"));

									}
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
					"SERI_LOSS_CK");
			MapAnalysisPoint analysisPoint = null;
			if (tempAnalysis == null) {
				analysisPoint = new MapAnalysisPoint();
				analysisPoint.setAnalysisname("SERI_LOSS_CK");
				analysisPoint.setAnalysispoint(endTime);
				session.save(analysisPoint);
			} else {
				analysisPoint = (MapAnalysisPoint) tempAnalysis;
				analysisPoint.setAnalysispoint(endTime);
				session.update(analysisPoint);
			}
			tx.commit();

		} catch (HibernateException e) {
			logger.error("��ˮȱʧ�ع�����̳߳��������쳣��", e); //$NON-NLS-1$

			if (tx != null) {
				try {
					tx.rollback();
				} catch (Exception e1) {
					// TODO: handle exception
					e1.printStackTrace();
				}
			}

		} catch (Exception e) {
			logger.error("��ˮȱʧ�ع�����̳߳��������쳣��", e); //$NON-NLS-1$
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
			logger.error("��ˮȱʧ�ع�����̳߳��������쳣��", e); //$NON-NLS-1$
		}

		// sleep thread follows the setting
		try {
			long sleepTime = Long.parseLong(String.valueOf(doubleCycle * 1000))
					- DateUtil.getIntervalTime(DateUtil.getNow(), recordTime);
			if (logger.isInfoEnabled()) {
				logger
						.info("��ˮȱʧ�ع�����߳̽�����������״̬!"
								+ " ���߿�ʼʱ��:" + DateUtil.getNow("yyyy/MM/dd/HH:mm:ss") + ", ����ʱ��:" + sleepTime + " ����"); //$NON-NLS-1$
			}
			this.startTime = this.endTime;
			this.endTime = DateUtil.getNewTime(this.endTime, doubleCycle);
			if (sleepTime <= 0) {
				sleep(600000);
			} else {
				sleep(sleepTime);
			}
		} catch (InterruptedException e) {
			logger.error("��ˮȱʧ�ع�����̳߳��������쳣�����ܱ�ǿ��ֹͣ�� ", e); //$NON-NLS-1$
		} catch (Exception e) {
			logger.error("��ˮȱʧ�ع�����̳߳��������쳣�����ܱ�ǿ��ֹͣ�� ", e); //$NON-NLS-1$
		}
	}

	private boolean CheckSerialost(Session session, String deviceId,
			long serialNo) {
		boolean ret = false;
		try {
			Query queryHasFound = session
					.createSQLQuery(
							"select {a.*} from ykt_mon.map_serialost_table a "
									+ "where a.device_id=:deviceId and a.serial_no=:serialNo "
									+ "and a.serial_reason=7 and a.serial_status=0 ")
					.addEntity("a", MapSerialostTable.class);
			queryHasFound.setString("deviceId", deviceId);
			queryHasFound.setLong("serialNo", serialNo);
			List list = queryHasFound.list();
			if (list.size() > 0) {
				ret = true;
			}
		} catch (HibernateException e) {
			logger.error("��ˮȱʧ�ع�����̳߳��������쳣��", e); //$NON-NLS-1$
			e.printStackTrace();
		} catch (Exception e) {
			logger.error("��ˮȱʧ�ع�����̳߳��������쳣��", e); //$NON-NLS-1$
			e.printStackTrace();
		}
		return ret;
	}

	public void terminate() {
		// TODO Auto-generated method stub
		if (this.isAlive()) {
			logger.warn("��ˮȱʧ�ع�����߳�״̬�����󣬴�ʱ�߳�״̬����߳�!"); //$NON-NLS-1$
			requestStop = true;
		} else {
			logger.warn("��ˮȱʧ�ع�����߳�״̬�����󣬴�ʱ�߳�״̬�������߳�!"); //$NON-NLS-1$
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
				logger.info("��ˮȱʧ�ع�����̷߳����ʼ�����ϵ��:" + contactName);
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
				logger.info("��ˮȱʧ�ع�����̷߳��Ͷ��Ÿ���ϵ��:" + contactName);
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
