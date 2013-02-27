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
import com.kingstargroup.form.MapSerialostTableKey;
import com.kingstargroup.form.TTifRcvdtl;
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
	private boolean requestStop = false;

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
			logger.info("**************��ˮȱʧ�����̳߳�ʼ��**************"); //$NON-NLS-1$
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
				this.cycle = mapParamTable.getValue().doubleValue();
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
			logger.error("��ˮȱʧ�����̳߳�ʼ��ʧ�ܣ�", e); //$NON-NLS-1$

		} finally {
			HibernateSessionFactory.closeSession();
		}

		if (logger.isInfoEnabled()) {
			logger.info("**************��ˮȱʧ�����̳߳�ʼ���ɹ�**************"); //$NON-NLS-1$
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
				.createQuery("from MapParamTable param where param.parameter=:paramRefer");
		queryCycle.setString("paramRefer", "TradeLackCycle");
		Iterator iterParam = queryCycle.iterate();
		if (iterParam.hasNext()) {
			MapParamTable mapParamTable = (MapParamTable) iterParam.next();
			this.cycle = mapParamTable.getValue().doubleValue();
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
			logger.info("��ˮȱʧ�����߳̿�ʼ��������"); //$NON-NLS-1$
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
						.info("��ˮȱʧ�����߳̿�ʼ����ʱ��:" + DateUtil.getNow("yyyy/MM/dd/HH:mm:ss")); //$NON-NLS-1$
			}
			if (1 > DateUtil.checkTimeSequence(endTime, DateUtil.getNow())) {
				if (logger.isInfoEnabled()) {
					logger
							.info("��ˮȱʧ�����̷߳���ʱ��Σ�" + startTime + " -- "
									+ endTime);
				}
			} else {
				endTime = DateUtil.getNow();
				if (logger.isInfoEnabled()) {
					logger
							.info("��ˮȱʧ�����̷߳���ʱ��Σ�" + startTime + " -- "
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
							"��ˮȱʧ�����߳�", DateUtil.getNow("yyyy/MM/dd/HH:mm:ss"),
							String.valueOf(this.doubleCycle), "������...");

			// String dateTime = this.startTime.substring(0, 8);
			// String dateTime1 = this.endTime.substring(0, 8);
			String device_name = "";
			int serialNo = 0;
			int F_serialNo = 0;
			String dateRec = "00000000";

			Query firstquery = session
					.createSQLQuery(
							"select t.device_id as {serialost.deviceId},"
									+ "v.lastno as {serialost.lastNo},t.firstno as {serialost.firstNo} from "
									+ "(select device_id,min(serial_no) as firstno from YKT_CUR.T_TIF_RCVDTL n "
									+ "where col_timestamp>=:time1 "
									+ "and col_timestamp<=:time2 group by device_id) t,"
									+ "(select a.device_id,serial_no as lastno from YKT_CUR.T_TIF_RCVDTL a "
									+ "join (select device_id,max(col_timestamp) as col_timestamp from YKT_CUR.T_TIF_RCVDTL c "
									+ "where col_timestamp<=:time3 and col_timestamp>=:time4 "
									+ "group by device_id) b "
									+ "on a.device_id=b.device_id and a.col_timestamp=b.col_timestamp) v "
									+ "where t.device_id=v.device_id and t.firstno-v.lastno>1 and t.firstno-v.lastno<=50")
					.addEntity("serialost", DeviceSerialostRt.class);
			firstquery.setString("time1", startTime);
			firstquery.setString("time2", endTime);
			firstquery.setString("time3", startTime);
			firstquery.setString("time4", DateUtil
					.getNewTime(endTime, -2592000));

			List firstlist = firstquery.list();
			Iterator firstIter = firstlist.iterator();

			while (firstIter.hasNext()) {
				dateRec = "00000000";
				DeviceSerialostRt rt = (DeviceSerialostRt) firstIter.next();
				List rtSerialNo = CheckLostSeriUitl.numberLostSerial(rt
						.getFirstNo().intValue(), rt.getLastNo().intValue());
				if ((rtSerialNo != null) && (rtSerialNo.size() < 50)) {// ������ʮ�����ϵĶ������⣬������ˮͻ��ķ���
					Iterator returnIter = rtSerialNo.iterator();
					while (returnIter.hasNext()) {
						serialNo = Integer.parseInt(returnIter.next()
								.toString());

						Query queryCheck = session
								.createSQLQuery(
										"select {rcvdtl.*} from ykt_cur.t_tif_rcvdtl rcvdtl "
												+ "where rcvdtl.serial_no=:serialNo "
												+ "and rcvdtl.device_id=:deviceId "
												+ "and rcvdtl.COL_TIMESTAMP>=:startTime "
												+ "and rcvdtl.COL_TIMESTAMP<=:endTime "
												+ "order by rcvdtl.tx_date desc,rcvdtl.tx_time desc with ur")
								.addEntity("rcvdtl", TTifRcvdtl.class);
						queryCheck.setInteger("serialNo", serialNo);
						queryCheck.setString("deviceId", rt.getDeviceId());
						queryCheck.setString("startTime", startTime);
						queryCheck.setString("endTime", endTime);
						List listCheck = queryCheck.list();
						if (listCheck.size() == 0) {// can not find this serial
							// the serial is lost really

							F_serialNo = serialNo + 1;
							Query queryFive = session
									.createSQLQuery(
											"select {rcvdtl.*} from ykt_cur.t_tif_rcvdtl rcvdtl "
													+ "where rcvdtl.serial_no=:F_serialNo "
													+ "and rcvdtl.device_id=:deviceId "
													+ "and rcvdtl.COL_TIMESTAMP>=:startTime "
													+ "and rcvdtl.COL_TIMESTAMP<=:endTime "
													+ "order by rcvdtl.tx_date desc,rcvdtl.tx_time desc with ur")
									.addEntity("rcvdtl", TTifRcvdtl.class);
							queryFive.setInteger("F_serialNo", F_serialNo);
							queryFive.setString("deviceId", rt.getDeviceId());
							queryFive.setString("startTime", startTime);
							queryFive.setString("endTime", endTime);
							List listFive = queryFive.list();
							Iterator iterTwo = listFive.iterator();
							if (iterTwo.hasNext()) {
								// insert into serialosttable
								TTifRcvdtl rcvdtl = (TTifRcvdtl) iterTwo.next();
								if (true == recordOrNot) {
									MapSerialostTable mapSerialost = new MapSerialostTable();
									MapSerialostTableKey mapSerialostKey = new MapSerialostTableKey();
									mapSerialostKey.setAnalysistime(recordTime);
									mapSerialostKey.setDeviceId(rt
											.getDeviceId());
									mapSerialostKey.setSerialNo(Integer
											.valueOf(String.valueOf(serialNo)));
									mapSerialost.setId(mapSerialostKey);
									mapSerialost.setTxDate(rcvdtl.getId()
											.getTxDate());
									dateRec = rcvdtl.getId().getTxDate();// ��¼��ˮʱ��
									mapSerialost.setTxTime(rcvdtl.getId()
											.getTxTime());
									mapSerialost.setContactname(contactName);
									mapSerialost.setSerialReason(Short
											.valueOf("7"));
									mapSerialost.setSerialStatus(Short
											.valueOf("0"));
									session.save(mapSerialost);
								}
								mailRecord++;
								if (!"".equals(mailList)) {
									buffer.append(StringUtil
											.seriallostStringGenerate(rt
													.getDeviceId(),
													device_name, String
															.valueOf(serialNo),
													rcvdtl.getId().getTxDate(),
													rcvdtl.getId().getTxTime(),
													"SERI_LOSS"));
								}
							} else {
								// can not find or means no F_serialNo insert
								// directly with no detail info
								if (true == recordOrNot) {
									MapSerialostTable mapSerialost = new MapSerialostTable();
									MapSerialostTableKey mapSerialostKey = new MapSerialostTableKey();
									mapSerialostKey.setAnalysistime(recordTime);
									mapSerialostKey.setDeviceId(rt
											.getDeviceId());
									mapSerialostKey.setSerialNo(Integer
											.valueOf(String.valueOf(serialNo)));
									mapSerialost.setId(mapSerialostKey);
									mapSerialost.setTxDate(dateRec);

									mapSerialost.setTxTime("000000");
									mapSerialost.setContactname(contactName);
									mapSerialost.setSerialReason(Short
											.valueOf("7"));
									mapSerialost.setSerialStatus(Short
											.valueOf("0"));
									session.save(mapSerialost);
								}
								mailRecord++;
								if (!"".equals(mailList)) {
									buffer.append(StringUtil
											.seriallostStringGenerate(rt
													.getDeviceId(),
													device_name, String
															.valueOf(serialNo),
													dateRec, "000000",
													"SERI_LOSS"));
								}
							}
						}
					}
				}
			}

			// max serial_no is less than 65535

			Query query = session
					.createSQLQuery(
							" Select a.device_id as {serialost.deviceId},"
									+ "sum(double(a.serial_no)) as {serialost.truth},"
									+ "(((max(double(a.serial_no))+min(double(a.serial_no)))*(max(double(a.serial_no))-min(double(a.serial_no))+1))/2) as {serialost.logic}, "
									+ "count(a.serial_no) as {serialost.countserial}, "
									+ "(max(a.serial_no)-min(a.serial_no)+1) as {serialost.logicserial},"
									+ "((max(a.serial_no)-min(a.serial_no)+1)-count(a.serial_no)) as {serialost.diff} "
									+ "from YKT_CUR.T_TIF_RCVDTL a, ykt_cur.T_PIF_DEVICE b "
									+ "where a.COL_TIMESTAMP>=:startTime and a.COL_TIMESTAMP<=:endTime "
									+ "and a.device_id=b.dev999_id "
									+ "and b.state_id <> 5 "
									+ "group by a.device_id "
									+ "having (sum(double(a.serial_no))<>(((max(double(a.serial_no))+min(double(a.serial_no)))*(max(double(a.serial_no))-min(double(a.serial_no))+1))/2)) "
									+ "and (max(double(a.serial_no))<65535) "
									+ "and ((max(a.serial_no)-min(a.serial_no)+1)-count(a.serial_no))>0 order by {serialost.diff} with ur")
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
				if ("1".equals(serialLost.getDiff().toString())) {
					serialNo = Integer.parseInt(serialLost.getLogic()
							.toString())
							- Integer
									.parseInt(serialLost.getTruth().toString());
					Query queryCheck = session
							.createSQLQuery(
									"select {rcvdtl.*} from ykt_cur.t_tif_rcvdtl rcvdtl "
											+ "where rcvdtl.serial_no=:serialNo "
											+ "and rcvdtl.device_id=:deviceId "
											+ "and rcvdtl.COL_TIMESTAMP>=:startTime "
											+ "and rcvdtl.COL_TIMESTAMP<=:endTime "
											+ "order by rcvdtl.tx_date desc,rcvdtl.tx_time desc with ur")
							.addEntity("rcvdtl", TTifRcvdtl.class);
					queryCheck.setInteger("serialNo", serialNo);
					queryCheck.setString("deviceId", serialLost.getDeviceId());
					queryCheck.setString("startTime", startTime);
					queryCheck.setString("endTime", endTime);
					List listCheck = queryCheck.list();
					if (listCheck.size() == 0) {
						// can not find this serial
						// the serial is lost really
						F_serialNo = serialNo + 1;
						Query queryOne = session
								.createSQLQuery(
										"select {rcvdtl.*} from ykt_cur.t_tif_rcvdtl rcvdtl "
												+ "where rcvdtl.serial_no=:F_serialNo "
												+ "and rcvdtl.device_id=:deviceId "
												+ "and rcvdtl.COL_TIMESTAMP>=:startTime "
												+ "and rcvdtl.COL_TIMESTAMP<=:endTime "
												+ "order by rcvdtl.tx_date desc,rcvdtl.tx_time desc with ur")
								.addEntity("rcvdtl", TTifRcvdtl.class);
						queryOne.setInteger("F_serialNo", F_serialNo);
						queryOne
								.setString("deviceId", serialLost.getDeviceId());
						queryOne.setString("startTime", startTime);
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
								mapSerialostKey.setSerialNo(Integer
										.valueOf(String.valueOf(serialNo)));
								mapSerialost.setId(mapSerialostKey);
								mapSerialost.setTxDate(rcvdtl.getId()
										.getTxDate());
								mapSerialost.setTxTime(rcvdtl.getId()
										.getTxTime());
								mapSerialost.setContactname(contactName);
								mapSerialost
										.setSerialReason(Short.valueOf("7"));
								mapSerialost
										.setSerialStatus(Short.valueOf("0"));
								session.save(mapSerialost);
							}
							mailRecord++;
							if (!"".equals(mailList)) {
								buffer.append(StringUtil
										.seriallostStringGenerate(serialLost
												.getDeviceId(), device_name,
												String.valueOf(serialNo),
												rcvdtl.getId().getTxDate(),
												rcvdtl.getId().getTxTime(),
												"SERI_LOSS"));
							}
						}
					}

				} else if (serialLost.getDiff().intValue() <= 50) {
					// more than one lost serial use btree check
					Query queryTwo = session
							.createSQLQuery(
									"select a.serial_no as serialNo "
											+ "from YKT_CUR.T_TIF_RCVDTL a "
											+ "where a.COL_TIMESTAMP>=:startTime and a.COL_TIMESTAMP<=:endTime "
											+ "and a.device_id=:deviceId order by a.serial_no desc with ur")
							.addScalar("serialNo", Hibernate.INTEGER);
					queryTwo.setString("startTime", startTime);
					queryTwo.setString("endTime", endTime);
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
										"select {rcvdtl.*} from ykt_cur.t_tif_rcvdtl rcvdtl "
												+ "where rcvdtl.serial_no=:serialNo "
												+ "and rcvdtl.device_id=:deviceId  "
												+ "and rcvdtl.COL_TIMESTAMP>=:startTime "
												+ "and rcvdtl.COL_TIMESTAMP<=:endTime "
												+ "order by rcvdtl.tx_date desc,rcvdtl.tx_time desc with ur")
								.addEntity("rcvdtl", TTifRcvdtl.class);
						queryCheck.setInteger("serialNo", serialNo);
						queryCheck.setString("deviceId", serialLost
								.getDeviceId());
						queryCheck.setString("startTime", startTime);
						queryCheck.setString("endTime", endTime);
						List listCheck = queryCheck.list();
						if (listCheck.size() == 0) {// can not find this serial
							// the serial is lost really
							F_serialNo = serialNo + 1;
							Query queryOne = session
									.createSQLQuery(
											"select {rcvdtl.*} from ykt_cur.t_tif_rcvdtl rcvdtl "
													+ "where rcvdtl.serial_no=:F_serialNo "
													+ "and rcvdtl.device_id=:deviceId "
													+ "and rcvdtl.COL_TIMESTAMP>=:startTime "
													+ "and rcvdtl.COL_TIMESTAMP<=:endTime "
													+ "order by rcvdtl.tx_date desc,rcvdtl.tx_time desc with ur")
									.addEntity("rcvdtl", TTifRcvdtl.class);
							queryOne.setInteger("F_serialNo", F_serialNo);
							queryOne.setString("deviceId", serialLost
									.getDeviceId());
							queryOne.setString("startTime", startTime);
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
									mapSerialostKey.setSerialNo(Integer
											.valueOf(String.valueOf(serialNo)));
									mapSerialost.setId(mapSerialostKey);
									mapSerialost.setTxDate(rcvdtl.getId()
											.getTxDate());
									dateRec = rcvdtl.getId().getTxDate();// ��¼��ˮʱ��
									mapSerialost.setTxTime(rcvdtl.getId()
											.getTxTime());
									mapSerialost.setContactname(contactName);
									mapSerialost.setSerialReason(Short
											.valueOf("7"));
									mapSerialost.setSerialStatus(Short
											.valueOf("0"));
									session.save(mapSerialost);
								}
								mailRecord++;
								if (!"".equals(mailList)) {
									buffer.append(StringUtil
											.seriallostStringGenerate(
													serialLost.getDeviceId(),
													device_name, String
															.valueOf(serialNo),
													rcvdtl.getId().getTxDate(),
													rcvdtl.getId().getTxTime(),
													"SERI_LOSS"));
								}
							} else {
								// can not find or means no F_serialNo insert
								// directly with no detail info
								if (true == recordOrNot) {
									MapSerialostTable mapSerialost = new MapSerialostTable();
									MapSerialostTableKey mapSerialostKey = new MapSerialostTableKey();
									mapSerialostKey.setAnalysistime(recordTime);
									mapSerialostKey.setDeviceId(serialLost
											.getDeviceId());
									mapSerialostKey.setSerialNo(Integer
											.valueOf(String.valueOf(serialNo)));
									mapSerialost.setId(mapSerialostKey);
									mapSerialost.setTxDate(dateRec);
									mapSerialost.setTxTime("000000");
									mapSerialost.setContactname(contactName);
									mapSerialost.setSerialReason(Short
											.valueOf("7"));
									mapSerialost.setSerialStatus(Short
											.valueOf("0"));
									session.save(mapSerialost);
								}
								mailRecord++;
								if (!"".equals(mailList)) {
									buffer.append(StringUtil
											.seriallostStringGenerate(
													serialLost.getDeviceId(),
													device_name, String
															.valueOf(serialNo),
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
							"Select a.device_id as deviceId from YKT_CUR.T_TIF_RCVDTL a "
									+ "where a.COL_TIMESTAMP>=:startTime "
									+ "and a.COL_TIMESTAMP<=:endTime "
									+ "group by a.device_id having max(a.serial_no)=65535 with ur")
					.addScalar("deviceId", Hibernate.STRING);

			queryTwo.setString("startTime", startTime);
			queryTwo.setString("endTime", endTime);
			List listTwo = queryTwo.list();
			String deviceId = "00000000";
			String specialTime = "";
			for (int i = 0; i < listTwo.size(); i++) {
				dateRec = "00000000";
				deviceId = listTwo.get(i).toString();
				device_name = DeviceNameDictionary.getInstance().get(deviceId);
				Query queryThree = session.createSQLQuery(
						"select COL_TIMESTAMP dateTime "
								+ "from YKT_CUR.T_TIF_RCVDTL a "
								+ "where a.COL_TIMESTAMP>=:startTime "
								+ "and a.COL_TIMESTAMP<=:endTime "
								+ "and a.device_id=:deviceId "
								+ "and a.serial_no=65535 with ur").addScalar(
						"dateTime", Hibernate.STRING);
				queryThree.setString("startTime", startTime);
				queryThree.setString("endTime", endTime);
				queryThree.setString("deviceId", deviceId);
				List listThree = queryThree.list();
				if (listThree.size() > 0) {
					specialTime = listThree.get(0).toString();
				}
				// Query queryFour = session.getNamedQuery("DeviceSerialLost");
				Query queryFour = session.createSQLQuery(
						"select a.serial_no serialNo from YKT_CUR.T_TIF_RCVDTL a "
								+ "where a.COL_TIMESTAMP>=:startTime "
								+ "and a.COL_TIMESTAMP<=:endTime "
								+ "and a.device_id=:deviceId "
								+ "order by a.serial_no desc with ur")
						.addScalar("serialNo", Hibernate.STRING);
				queryFour.setString("startTime", startTime);
				queryFour.setString("endTime", specialTime);
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
										"select {rcvdtl.*} from ykt_cur.t_tif_rcvdtl rcvdtl "
												+ "where rcvdtl.serial_no=:serialNo "
												+ "and rcvdtl.device_id=:deviceId "
												+ "and rcvdtl.COL_TIMESTAMP>=:startTime "
												+ "and rcvdtl.COL_TIMESTAMP<=:endTime "
												+ "order by rcvdtl.tx_date desc,rcvdtl.tx_time desc with ur")
								.addEntity("rcvdtl", TTifRcvdtl.class);
						queryCheck.setInteger("serialNo", serialNo);
						queryCheck.setString("deviceId", deviceId);
						queryCheck.setString("startTime", startTime);
						queryCheck.setString("endTime", endTime);
						List listCheck = queryCheck.list();
						if (listCheck.size() == 0) {// can not find this serial
							// the serial is lost really

							F_serialNo = serialNo + 1;
							Query queryFive = session
									.createSQLQuery(
											"select {rcvdtl.*} from ykt_cur.t_tif_rcvdtl rcvdtl "
													+ "where rcvdtl.serial_no=:F_serialNo "
													+ "and rcvdtl.device_id=:deviceId "
													+ "and rcvdtl.COL_TIMESTAMP>=:startTime "
													+ "and rcvdtl.COL_TIMESTAMP<=:endTime "
													+ "order by rcvdtl.tx_date desc,rcvdtl.tx_time desc with ur")
									.addEntity("rcvdtl", TTifRcvdtl.class);
							queryFive.setInteger("F_serialNo", F_serialNo);
							queryFive.setString("deviceId", deviceId);
							queryFive.setString("startTime", startTime);
							queryFive.setString("endTime", endTime);
							List listFive = queryFive.list();
							Iterator iterTwo = listFive.iterator();
							if (iterTwo.hasNext()) {
								// insert into serialosttable
								TTifRcvdtl rcvdtl = (TTifRcvdtl) iterTwo.next();
								if (true == recordOrNot) {
									MapSerialostTable mapSerialost = new MapSerialostTable();
									MapSerialostTableKey mapSerialostKey = new MapSerialostTableKey();
									mapSerialostKey.setAnalysistime(recordTime);
									mapSerialostKey.setDeviceId(deviceId);
									mapSerialostKey.setSerialNo(Integer
											.valueOf(String.valueOf(serialNo)));
									mapSerialost.setId(mapSerialostKey);
									mapSerialost.setTxDate(rcvdtl.getId()
											.getTxDate());
									dateRec = rcvdtl.getId().getTxDate();// ��¼��ˮʱ��
									mapSerialost.setTxTime(rcvdtl.getId()
											.getTxTime());
									mapSerialost.setContactname(contactName);
									mapSerialost.setSerialReason(Short
											.valueOf("7"));
									mapSerialost.setSerialStatus(Short
											.valueOf("0"));
									session.save(mapSerialost);
								}
								mailRecord++;
								if (!"".equals(mailList)) {
									buffer.append(StringUtil
											.seriallostStringGenerate(deviceId,
													device_name, String
															.valueOf(serialNo),
													rcvdtl.getId().getTxDate(),
													rcvdtl.getId().getTxTime(),
													"SERI_LOSS"));
								}
							} else {
								// can not find or means no F_serialNo insert
								// directly with no detail info
								if (true == recordOrNot) {
									MapSerialostTable mapSerialost = new MapSerialostTable();
									MapSerialostTableKey mapSerialostKey = new MapSerialostTableKey();
									mapSerialostKey.setAnalysistime(recordTime);
									mapSerialostKey.setDeviceId(deviceId);
									mapSerialostKey.setSerialNo(Integer
											.valueOf(String.valueOf(serialNo)));
									mapSerialost.setId(mapSerialostKey);
									mapSerialost.setTxDate(dateRec);

									mapSerialost.setTxTime("000000");
									mapSerialost.setContactname(contactName);
									mapSerialost.setSerialReason(Short
											.valueOf("7"));
									mapSerialost.setSerialStatus(Short
											.valueOf("0"));
									session.save(mapSerialost);
								}
								mailRecord++;
								if (!"".equals(mailList)) {
									buffer.append(StringUtil
											.seriallostStringGenerate(deviceId,
													device_name, String
															.valueOf(serialNo),
													dateRec, "000000",
													"SERI_LOSS"));
								}
							}
						}
					}
				}

				// ����
				Query querySix = session.createSQLQuery(
						"select a.serial_no as serialNo from YKT_CUR.T_TIF_RCVDTL a "
								+ "where a.COL_TIMESTAMP>:startTime "
								+ "and a.COL_TIMESTAMP<=:endTime "
								+ "and a.device_id=:deviceId "
								+ "order by a.serial_no desc with ur")
						.addScalar("serialNo", Hibernate.STRING);
				querySix.setString("startTime", specialTime);
				querySix.setString("endTime", endTime);
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
										"select {rcvdtl.*} from ykt_cur.t_tif_rcvdtl rcvdtl "
												+ "where rcvdtl.serial_no=:serialNo "
												+ "and rcvdtl.device_id=:deviceId "
												+ "and rcvdtl.COL_TIMESTAMP>=:startTime "
												+ "and rcvdtl.COL_TIMESTAMP<=:endTime "
												+ "order by rcvdtl.tx_date desc,rcvdtl.tx_time desc with ur")
								.addEntity("rcvdtl", TTifRcvdtl.class);
						queryCheck.setInteger("serialNo", serialNo);
						queryCheck.setString("deviceId", deviceId);
						queryCheck.setString("startTime", startTime);
						queryCheck.setString("endTime", endTime);
						List listCheck = queryCheck.list();
						if (listCheck.size() == 0) {// can not find this serial
							// the serial is lost really

							F_serialNo = serialNo + 1;
							Query querySeven = session
									.createSQLQuery(
											"select {rcvdtl.*} from ykt_cur.t_tif_rcvdtl rcvdtl "
													+ "where rcvdtl.serial_no=:F_serialNo "
													+ "and rcvdtl.device_id=:deviceId "
													+ "and rcvdtl.COL_TIMESTAMP>=:startTime "
													+ "and rcvdtl.COL_TIMESTAMP<=:endTime "
													+ "order by rcvdtl.tx_date desc,rcvdtl.tx_time desc with ur")
									.addEntity("rcvdtl", TTifRcvdtl.class);
							querySeven.setInteger("F_serialNo", F_serialNo);
							querySeven.setString("deviceId", deviceId);
							querySeven.setString("startTime", startTime);
							querySeven.setString("endTime", endTime);
							List listSeven = querySeven.list();
							Iterator iterTwo = listSeven.iterator();
							if (iterTwo.hasNext()) {
								// insert into serialosttable
								TTifRcvdtl rcvdtl = (TTifRcvdtl) iterTwo.next();
								if (true == recordOrNot) {
									MapSerialostTable mapSerialost = new MapSerialostTable();
									MapSerialostTableKey mapSerialostKey = new MapSerialostTableKey();
									mapSerialostKey.setAnalysistime(recordTime);
									mapSerialostKey.setDeviceId(deviceId);
									mapSerialostKey.setSerialNo(Integer
											.valueOf(String.valueOf(serialNo)));
									mapSerialost.setId(mapSerialostKey);
									mapSerialost.setTxDate(rcvdtl.getId()
											.getTxDate());
									dateRec = rcvdtl.getId().getTxDate();// ��¼��ˮʱ��
									mapSerialost.setTxTime(rcvdtl.getId()
											.getTxTime());
									mapSerialost.setContactname(contactName);
									mapSerialost.setSerialReason(Short
											.valueOf("7"));
									mapSerialost.setSerialStatus(Short
											.valueOf("0"));
									session.save(mapSerialost);
								}
								mailRecord++;
								if (!"".equals(mailList)) {
									buffer.append(StringUtil
											.seriallostStringGenerate(deviceId,
													device_name, String
															.valueOf(serialNo),
													rcvdtl.getId().getTxDate(),
													rcvdtl.getId().getTxTime(),
													"SERI_LOSS"));
								}
							} else {
								// can not find or means no F_serialNo insert
								// directly with no detail info
								if (true == recordOrNot) {
									MapSerialostTable mapSerialost = new MapSerialostTable();
									MapSerialostTableKey mapSerialostKey = new MapSerialostTableKey();
									mapSerialostKey.setAnalysistime(recordTime);
									mapSerialostKey.setDeviceId(deviceId);
									mapSerialostKey.setSerialNo(Integer
											.valueOf(String.valueOf(serialNo)));
									mapSerialost.setId(mapSerialostKey);
									mapSerialost.setTxDate(dateRec);

									mapSerialost.setTxTime("000000");
									mapSerialost.setContactname(contactName);
									mapSerialost.setSerialReason(Short
											.valueOf("7"));
									mapSerialost.setSerialStatus(Short
											.valueOf("0"));
									session.save(mapSerialost);
								}
								mailRecord++;
								if (!"".equals(mailList)) {
									buffer.append(StringUtil
											.seriallostStringGenerate(deviceId,
													device_name, String
															.valueOf(serialNo),
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

			// mail
			sendMail();
			// SMS
			sendSMG();

		} catch (HibernateException e) {
			logger.error("��ˮȱʧ�����̳߳��������쳣��", e); //$NON-NLS-1$

			if (tx != null) {
				tx.rollback();
			}

		} catch (Exception e) {
			logger.error("��ˮȱʧ�����̳߳��������쳣��", e); //$NON-NLS-1$
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
						.info("��ˮȱʧ�����߳̽�����������״̬!"
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
			logger.error("��ˮȱʧ�����̳߳��������쳣�����ܱ�ǿ��ֹͣ�� ", e); //$NON-NLS-1$
		} catch (Exception e) {
			logger.error("��ˮȱʧ�����̳߳��������쳣�����ܱ�ǿ��ֹͣ�� ", e); //$NON-NLS-1$
		}
	}

	public void terminate() {
		// TODO Auto-generated method stub
		if (this.isAlive()) {
			logger.warn("��ˮȱʧ�����߳�״̬�����󣬴�ʱ�߳�״̬����߳�!"); //$NON-NLS-1$
			this.requestStop = true;
		} else {
			logger.warn("��ˮȱʧ�����߳�״̬�����󣬴�ʱ�߳�״̬�������߳�!"); //$NON-NLS-1$
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
				logger.info("��ˮȱʧ�����̷߳����ʼ�����ϵ��:" + contactName);
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
				logger.info("��ˮȱʧ�����̷߳��Ͷ��Ÿ���ϵ��:" + contactName);
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
