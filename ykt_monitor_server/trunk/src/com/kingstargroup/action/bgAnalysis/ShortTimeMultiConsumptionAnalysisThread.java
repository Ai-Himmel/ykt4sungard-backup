package com.kingstargroup.action.bgAnalysis;

/**
 * <p>
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: ShortTimeMultiConsumptionAnalysisThread.java
 * Description: ���ڶ����ˮ����߳���
 * Modify History����Change Log��:  
 * �������ͣ��������޸ĵȣ�   ��������       ������             �������ݼ���
 * ���� 					 2005-10-31    ������ <br>       ���ڶ����ˮ����߳���
 * �޸�  				 2006-7-20     ������             
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
import com.kingstargroup.form.MapAlertTable;
import com.kingstargroup.form.MapAnalysisPoint;
import com.kingstargroup.form.MapContactMonitorTable;
import com.kingstargroup.form.MapContactTable;
import com.kingstargroup.form.MapParamTable;
import com.kingstargroup.form.MapSerialexceptTable;
import com.kingstargroup.form.MapSerialexceptTableId;
import com.kingstargroup.form.TPosdtl;
import com.kingstargroup.utils.CommonSendMailUtil;
import com.kingstargroup.utils.CommonSendSMGUtil;
import com.kingstargroup.utils.DateUtil;
import com.kingstargroup.utils.GetApplicationResources;
import com.kingstargroup.utils.StringUtil;

public class ShortTimeMultiConsumptionAnalysisThread extends Thread implements
		AnalyzeThreadInterface {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(ShortTimeMultiConsumptionAnalysisThread.class);

	// flag of stop this thread
	private static boolean requestStop = false;

	// record analysis time
	private String recordTime = "";

	// default analysis is to analysis all from
	private String startTime = "20050101000000";

	// default analysis's end time to now
	private String endTime = DateUtil.getNow();

	// default analysis cycle is one hour
	private double cycle = 1.0;

	// money limit
	private double timeLimit = 5.0;

	// money limit
	private double countLimit = 3.0;

	// inteval param
	private int doubleCycle = 0;

	// limit param
	private int tLimit = 0;

	// count param
	private int cLimit = 0;

	// // split time
	// private String splitTime1 = "";
	//
	// private String splitTime2 = "";

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

	/*
	 * (non-Javadoc)
	 * 
	 * @see com.kingstargroup.commons.AnalyzeThreadInterface#initParam()
	 */
	public void initParam() {
		if (logger.isInfoEnabled()) {
			logger.info("**************���ڶ�����ѷ����̳߳�ʼ��**************"); //$NON-NLS-1$
		}

		// TODO Auto-generated method stub
		try {
			Session session = HibernateSessionFactory.currentSession();
			Query queryTime = session
					.createQuery("from MapAnalysisPoint point where point.analysisname=:analysisName");
			queryTime.setString("analysisName", "SHORTTIME_MUTI_COMSUMPTION");
			Iterator iterTime = queryTime.iterate();
			if (iterTime.hasNext()) {
				MapAnalysisPoint mapAnalysisPoint = (MapAnalysisPoint) iterTime
						.next();
				this.startTime = mapAnalysisPoint.getAnalysispoint();
			}

			Query queryCycle = session
					.createQuery("from MapParamTable param where "
							+ "param.parameter=:paramRefer or param.parameter=:paramRefer1 "
							+ "or param.parameter=:paramRefer2");
			queryCycle.setString("paramRefer", "ShortTimeMCCycle");
			queryCycle.setString("paramRefer1", "ShortTimeLimit");
			queryCycle.setString("paramRefer2", "CountLimit");
			List list  = queryCycle.list();
			Iterator iterParam = list.iterator();
			while (iterParam.hasNext()) {
				MapParamTable mapParamTable = (MapParamTable) iterParam.next();
				if ("ShortTimeMCCycle".equals(mapParamTable.getParameter())) {
					this.cycle = mapParamTable.getValue();
				} else if ("ShortTimeLimit"
						.equals(mapParamTable.getParameter())) {
					this.timeLimit = mapParamTable.getValue();
				} else if ("CountLimit".equals(mapParamTable.getParameter())) {
					this.countLimit = mapParamTable.getValue();
				}
			}

			String s = String.valueOf(cycle * 3600);
			int position = s.indexOf('.');
			this.doubleCycle = Integer.parseInt(s.substring(0, position));
			String v = String.valueOf(timeLimit * 60);
			position = v.indexOf('.');
			this.tLimit = Integer.parseInt(v.substring(0, position));
			String c = String.valueOf(countLimit);
			position = c.indexOf('.');
			this.cLimit = Integer.parseInt(c.substring(0, position));
			if (!"20050101000000".equals(this.startTime)) {
				// Analysis lattest hours
				this.endTime = DateUtil.getNewTime(this.startTime, doubleCycle);
			} else {
				this.endTime = DateUtil.getNow();
				this.startTime = DateUtil
						.getNewTime(this.endTime, -doubleCycle);
			}
			//
			// this.splitTime1 = DateUtil.getNewTimes("240000", -doubleCycle
			// - tLimit, "HHmmss");
			// this.splitTime2 = DateUtil.getNewTimes("240000", doubleCycle
			// + tLimit, "HHmmss");

		} catch (HibernateException e) {
			logger.error("���ڶ�����ѷ����̳߳�ʼ��ʧ�ܣ�", e); //$NON-NLS-1$
		} finally {
			HibernateSessionFactory.closeSession();
		}
		if (logger.isInfoEnabled()) {
			logger.info("**************���ڶ�����ѷ����̳߳�ʼ���ɹ�**************"); //$NON-NLS-1$
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
				.createQuery("from MapAlertTable alert where alert.parameter='ShortTimeMulti'");
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
				.createQuery("from MapParamTable as param where "
						+ "param.parameter=:paramRefer or param.parameter=:paramRefer1 "
						+ "or param.parameter=:paramRefer2");
		queryCycle.setString("paramRefer", "ShortTimeMCCycle");
		queryCycle.setString("paramRefer1", "ShortTimeLimit");
		queryCycle.setString("paramRefer2", "CountLimit");
		Iterator iterParam = queryCycle.iterate();
		if (iterParam.hasNext()) {
			MapParamTable mapParamTable = (MapParamTable) iterParam.next();
			if ("ShortTimeMCCycle".equals(mapParamTable.getParameter())) {
				this.cycle = mapParamTable.getValue();
			} else if ("ShortTimeLimit".equals(mapParamTable.getParameter())) {
				this.timeLimit = mapParamTable.getValue();
			} else if ("CountLimit".equals(mapParamTable.getParameter())) {
				this.countLimit = mapParamTable.getValue();
			}
		}

		String s = String.valueOf(cycle * 3600);
		int position = s.indexOf('.');
		this.doubleCycle = Integer.parseInt(s.substring(0, position));
		String v = String.valueOf(timeLimit * 60);
		position = v.indexOf('.');
		this.tLimit = Integer.parseInt(v.substring(0, position));
		String c = String.valueOf(countLimit);
		position = c.indexOf('.');
		this.cLimit = Integer.parseInt(c.substring(0, position));

		// contact list
		Query queryContact = session
				.createQuery("from MapContactMonitorTable monitor where monitor.monitorno='SHORTTIME_MUTI_COMSUMPTION'");
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
			logger.info("���ڶ�����ѷ����߳̿�ʼ��������"); //$NON-NLS-1$
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
						.info("���ڶ�����ѷ����߳̿�ʼ����ʱ��:" + DateUtil.getNow("yyyy/MM/dd/HH:mm:ss")); //$NON-NLS-1$
			}
			if (1 > DateUtil.checkTimeSequence(endTime, DateUtil.getNow())) {
				if (logger.isInfoEnabled()) {
					logger.info("���ڶ�����ѷ����̷߳���ʱ��Σ�" + startTime + " -- "
							+ endTime);
				}
			} else {
				endTime = DateUtil.getNow();
				if (logger.isInfoEnabled()) {
					logger.info("���ڶ�����ѷ����̷߳���ʱ��Σ�" + startTime + " -- "
							+ endTime);
				}
			}
			getParameter(session);
			// analysis time record
			recordTime = DateUtil.getNow();
			BgMonitor
					.monitorThreadStatusReport(
							"com.kingstargroup.action.bgAnalysis.ShortTimeMultiConsumptionAnalysisThread",
							"���ڶ�����ѷ����߳�", DateUtil
									.getNow("yyyy/MM/dd/HH:mm:ss"), String
									.valueOf(this.doubleCycle), "������...");
			String txDate = "";
			String txDate1 = "";
			String txTime = "";
			String txTime1 = "";
			String tempTime = DateUtil.getNewTime(startTime, -tLimit / 2);
			String tempTime1 = DateUtil.getNewTime(startTime, tLimit / 2);

			// method1
			String cardNo = "";
			while (DateUtil.checkTimeSequence(tempTime, endTime) < 0) {
				tempTime1 = DateUtil.getNewTime(tempTime, tLimit);
				txDate = tempTime.substring(0, 8);
				txDate1 = tempTime1.substring(0, 8);
				txTime = tempTime.substring(8);
				txTime1 = tempTime1.substring(8);
				Query query = session
						.createSQLQuery(SqlStatementDictionary.getIntance().getSQL("com.kingstargroup.action.bgAnalysis.ShortTimeMultiConsumptionAnalysisThread.getstCardno"))
						.addScalar("cardNo", Hibernate.INTEGER);
				query.setString("txDate", txDate);
				query.setString("txDate1", txDate1);
				query.setString("txTime", txTime);
				query.setString("txTime1", txTime1);
				query.setInteger("countLimit", cLimit);
				List list = query.list();
				for (int i = 0; i < list.size(); i++) {
					cardNo = list.get(i).toString();
					Query queryOne = session
							.createSQLQuery(SqlStatementDictionary.getIntance().getSQL("com.kingstargroup.action.bgAnalysis.ShortTimeMultiConsumptionAnalysisThread.getstCardserial"))
							.addEntity("posdtl", TPosdtl.class);
					queryOne.setString("txDate", txDate);
					queryOne.setString("txDate1", txDate1);
					queryOne.setString("txTime", txTime);
					queryOne.setString("txTime1", txTime1);
					queryOne.setInteger("cardNo", Integer.parseInt(cardNo));
					List listOne = queryOne.list();
					Iterator iterOne = listOne.iterator();
					while (iterOne.hasNext()) {
						TPosdtl rcvdtl = (TPosdtl) iterOne.next();
						if (true == recordOrNot) {
							MapSerialexceptTable seriExcept = new MapSerialexceptTable();
							MapSerialexceptTableId seriExptKey = new MapSerialexceptTableId();
							
							seriExptKey.setAnalysistime(recordTime);
							seriExptKey.setTransdate(rcvdtl.getId().getTransdate());
							seriExptKey.setDevphyid(rcvdtl.getId().getDevphyid());
							seriExptKey.setDevseqno(rcvdtl.getId().getDevseqno());
							seriExcept.setAccdate(rcvdtl.getAccdate());
							seriExcept.setAcctime(rcvdtl.getAcctime());

							seriExcept.setAmount(rcvdtl.getAmount());
							seriExcept.setBatchno(rcvdtl.getBatchno());
							seriExcept.setCardaftbal(rcvdtl.getCardaftbal());
							seriExcept.setCardbefbal(rcvdtl.getCardbefbal());
							seriExcept.setCardcnt(rcvdtl.getCardcnt());
							seriExcept.setCardno(rcvdtl.getCardno());
							seriExcept.setColdate(rcvdtl.getColdate());
							seriExcept.setColtime(rcvdtl.getColtime());

							seriExcept.setDelflag(rcvdtl.getDelflag());
							seriExcept.setErrcode(rcvdtl.getErrcode());
							seriExcept.setErrmsg(rcvdtl.getErrmsg());
							seriExcept.setId(seriExptKey);
							seriExcept.setManagefee(rcvdtl.getManagefee());
							seriExcept.setPurseno(rcvdtl.getPurseno());
							seriExcept.setShopid(rcvdtl.getShopid());
							seriExcept.setStatus(rcvdtl.getStatus());
							seriExcept.setSubsidyno(rcvdtl.getSubsidyno());
							seriExcept.setSysid(rcvdtl.getSysid());
							seriExcept.setTranscode(rcvdtl.getTranscode());
							seriExcept.setTransmark(rcvdtl.getTransmark());
							seriExcept.setTranstime(rcvdtl.getTranstime());

							seriExcept.setContactname(contactName);
							seriExcept.setAbnormaltype(Long.parseLong("14"));
							session.save(seriExcept);
						}
						mailRecord++;
						if (!"".equals(mailList)) {
							String device_name = "";
							device_name = DeviceNameDictionary.getInstance().get(
									rcvdtl.getId().getDevphyid()).trim();
							Query queryCustomer = session
									.createSQLQuery(SqlStatementDictionary.getIntance().getSQL("com.kingstargroup.action.bgAnalysis.ShortTimeMultiConsumptionAnalysisThread.getCutName"))
									.addScalar("cutName", Hibernate.STRING);
							queryCustomer.setLong("cardno", rcvdtl.getCardno());
							List listCust = queryCustomer.list();
							String cust_name = "";
							if (listCust.size() > 0) {
								cust_name = listCust.get(0).toString().trim();
							}
							
							buffer.append(StringUtil.largeExceptStringGenerate(
									rcvdtl.getId().getDevphyid(), device_name,
									rcvdtl.getCardno(), cust_name, rcvdtl.getId().getDevseqno(),
									rcvdtl.getAmount(), rcvdtl.getId().getTransdate(), rcvdtl.getTranstime(),
									"SHORTTIME_MUTI_COMSUMPTION"));

						}
					}
				}
				tempTime = DateUtil.getNewTime(tempTime, tLimit);
			}

			// record timepoint analysis
			Object tempAnalysis = session.get(MapAnalysisPoint.class,
					"SHORTTIME_MUTI_COMSUMPTION");
			MapAnalysisPoint analysisPoint = null;
			if (tempAnalysis == null) {
				analysisPoint = new MapAnalysisPoint();
				analysisPoint.setAnalysisname("SHORTTIME_MUTI_COMSUMPTION");
				analysisPoint.setAnalysispoint(endTime);
				session.save(analysisPoint);
			} else {
				analysisPoint = (MapAnalysisPoint) tempAnalysis;
				analysisPoint.setAnalysispoint(endTime);
				session.update(analysisPoint);
			}
			tx.commit();
		} catch (HibernateException e) {
			logger.error("���ڶ�����ѷ����̳߳��������쳣��", e); //$NON-NLS-1$

			if (tx != null) {
				try {
					tx.rollback();
				} catch (Exception e1) {
					// TODO: handle exception
					e1.printStackTrace();
				}
			}

		} catch (Exception e) {
			logger.error("���ڶ�����ѷ����̳߳��������쳣��", e); //$NON-NLS-1$
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
			logger.error("���ڶ�����ѷ����̳߳��������쳣��", e); //$NON-NLS-1$
		}
		// sleep thread follows the setting
		try {
			long sleepTime = Long.parseLong(String.valueOf(doubleCycle * 1000))
					- DateUtil.getIntervalTime(DateUtil.getNow(), recordTime);
			if (logger.isInfoEnabled()) {
				logger
						.info("���ڶ�������̷߳���������������״̬!"
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
			logger.error("���ڶ�����ѷ����̳߳��������쳣�����ܱ�ǿ��ֹͣ�� ", e); //$NON-NLS-1$

		} catch (Exception e) {
			logger.error("���ڶ�����ѷ����̳߳��������쳣�����ܱ�ǿ��ֹͣ�� ", e); //$NON-NLS-1$
		}

	}

	public void terminate() {
		// TODO Auto-generated method stub
		if (this.isAlive()) {
			logger.warn("���ڶ�����ѷ����߳�״̬�����󣬴�ʱ�߳�״̬����߳�!"); //$NON-NLS-1$
			requestStop = true;
		} else {
			logger.warn("���ڶ�����ѷ����߳�״̬�����󣬴�ʱ�߳�״̬�������߳�!"); //$NON-NLS-1$
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
				logger.info("���ڶ�����ѷ����̷߳����ʼ�����ϵ��:" + contactName);
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
									.largeExceptMailGenerate(nameList[i],
											DateUtil.reFormatTime(recordTime),
											mailRecord, tmpStr,
											"SHORTTIME_MUTI_COMSUMPTION"));
				}
			}
		}
		if (logger.isDebugEnabled()) {
			logger.debug("sendMail() - end");
		}
	}

	public void sendSMG() {
		// TODO Auto-generated method stub
		if ((true == smgOrNot) && (!"".equals(phoneNumber)) && mailRecord > 0) {
			if (logger.isInfoEnabled()) {
				logger.info("���ڶ�����ѷ����̷߳��Ͷ��Ÿ���ϵ��:" + contactName);
			}
			String[] tempList = null;
			String[] nameList = null;
			tempList = phoneNumber.split(";");
			nameList = phoneName.split(";");
			for (int i = 0; i < tempList.length; i++) {
				if (!"".equals(tempList[i])) {
					SmgMessage = StringUtil.wholeSMGGenerate(nameList[i],
							DateUtil.reFormatTime(recordTime), mailRecord,
							"SHORTTIME_MUTI_COMSUMPTION");
					CommonSendSMGUtil.sendSMG(tempList[i], SmgMessage);
				}
			}
		}
	}
}
