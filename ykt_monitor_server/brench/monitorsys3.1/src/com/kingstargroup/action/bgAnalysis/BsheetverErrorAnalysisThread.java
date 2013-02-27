package com.kingstargroup.action.bgAnalysis;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: BsheetverErrorAnalysisThread.java
 * Description: �������汾�Ŵ������߳���
 * Modify History����Change Log��:  
 * �������ͣ��������޸ĵȣ�   ��������       ������             �������ݼ���
 * ����  				 2005-10-19    ������             �������汾�Ŵ������߳���
 * �޸�					 2006-07-20    ������    			 �޸���־��¼��ʽ        
 * <p>
 *
 * @author      ������
 * @version     1.0
 * @since       1.0
 */
import java.util.Iterator;
import java.util.List;

import org.apache.commons.beanutils.BeanUtils;
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
	private static boolean requestStop = false;

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
	
	private String preAnalysisTime = "";

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

	/* (non-Javadoc)
	 * @see com.kingstargroup.commons.AnalyzeThreadInterface#initParam()
	 */
	public void initParam() {
		if (logger.isInfoEnabled()) {
			logger.info("**************�������汾��������̳߳�ʼ��**************"); //$NON-NLS-1$
		}
		try {
			Session session = HibernateSessionFactory.currentSession();
			Query queryTime = session
					.createQuery("from MapAnalysisPoint  point where point.analysisname=:analysisName");
			queryTime.setString("analysisName", "BSHEETVER_ERROR");
			Iterator iterTime = queryTime.iterate();
			if (iterTime.hasNext()) {
				MapAnalysisPoint mapAnalysisPoint = (MapAnalysisPoint) iterTime
						.next();
				this.startTime = mapAnalysisPoint.getAnalysispoint();
			}
			Query queryCycle = session
					.createQuery("from MapParamTable  param where param.parameter=:paramRefer "
							+ "or param.parameter=:paramRefer1");
			queryCycle.setString("paramRefer", "BlackListDistrCycle");
			queryCycle.setString("paramRefer1", "BlackListDistrTime");
			List listParam = queryCycle.list();
			Iterator iterParam = listParam.iterator();
			while (iterParam.hasNext()) {
				MapParamTable mapParamTable = (MapParamTable) iterParam.next();
				if ("BlackListDistrCycle".equals(mapParamTable.getParameter())) {
					this.cycle = mapParamTable.getValue();
				}
				if ("BlackListDistrTime".equals(mapParamTable.getParameter())) {
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
			logger.error("�������汾��������̳߳�ʼ��ʧ�ܣ�", e); //$NON-NLS-1$
		} finally {
			HibernateSessionFactory.closeSession();
		}
		if (logger.isInfoEnabled()) {
			logger.info("**************�������汾��������̳߳�ʼ���ɹ�**************"); //$NON-NLS-1$
		}
	}

	/**
	 * @param session
	 */
	
	/**
			* Method name: getParameter<br>
			* Description: �����ݿ����³�ʼ��һЩ�����õĲ���<br>
			* Return: void<br>
			* Args: @param session
			* Modify History: <br>
			* ��������    ������     ����ʱ��       ��������<br>
			* ======================================<br>
			*  ����      ������    Aug 11, 2007  <br>
			* @author   ������
			* @version 
			* @since 1.0
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
				.createQuery("from MapParamTable  param where param.parameter=:paramRefer "
						+ "or param.parameter=:paramRefer1");
		queryCycle.setString("paramRefer", "BlackListDistrCycle");
		queryCycle.setString("paramRefer1", "BlackListDistrTime");
		List listParam = queryCycle.list();
		Iterator iterParam = listParam.iterator();
		while (iterParam.hasNext()) {
			MapParamTable mapParamTable = (MapParamTable) iterParam.next();
			if ("BlackListDistrCycle".equals(mapParamTable.getParameter())) {
				this.cycle = mapParamTable.getValue();
			}
			if ("BlackListDistrTime".equals(mapParamTable.getParameter())) {
				this.timeLimit = mapParamTable.getValue();
			}
		}
		String s = String.valueOf(cycle * 3600);
		this.doubleCycle = Integer.parseInt(s.substring(0, s.indexOf('.')));
	}

	public void anaylize() {
		if (logger.isInfoEnabled()) {
			logger.info("�������汾��������߳̿�ʼ��������"); //$NON-NLS-1$
		}
		Transaction tx = null;
		try{
		try {
			Session session = HibernateSessionFactory.currentSession();
			tx = session.beginTransaction();
			this.accelateParam = Integer
					.parseInt(BgMonitor.getIntance().accelateParam);
			endTime = DateUtil.getNewTime(endTime, accelateParam * 60);
			if (logger.isInfoEnabled()) {
				logger
						.info("�������汾��������߳̿�ʼ����ʱ��:" + DateUtil.getNow("yyyy/MM/dd/HH:mm:ss")); //$NON-NLS-1$
			}
			if (1 > DateUtil.checkTimeSequence(endTime, DateUtil.getNow())) {
				if (logger.isInfoEnabled()) {
					logger.info("�������汾��������̷߳���ʱ��Σ�" + startTime + " -- "
							+ endTime);
				}
			} else {
				endTime = DateUtil.getNow();
				if (logger.isInfoEnabled()) {
					logger.info("�������汾��������̷߳���ʱ��Σ�" + startTime + " -- "
							+ endTime);
				}
			}
			getParameter(session);
			
			// record prev record time
			preAnalysisTime = recordTime;
			String devid_t = "";
			
			
			recordTime = DateUtil.getNow();
			BgMonitor
					.monitorThreadStatusReport(
							"com.kingstargroup.action.bgAnalysis.BsheetverErrorAnalysisThread",
							"�������汾��������߳�", DateUtil
									.getNow("yyyy/MM/dd/HH:mm:ss"), String
									.valueOf(this.doubleCycle), "������...");
			String blackSheetTmp = "";

			Query queryTime = session
					.createQuery("select max(cardverno) as maxVolume from TCardver ");
			List listTime = queryTime.list();
			Iterator iterTime = listTime.iterator();
			if (iterTime.hasNext()) {
				blackSheetTmp = iterTime.next().toString();
				
				
				String temp = String.valueOf(this.timeLimit);
				int intTemp = Integer.parseInt(temp.substring(0, temp
						.indexOf(".")));
//				intTemp *= (-1 * 3600);
//				blackSheet = DateUtil.getSpecialNewTime(blackSheetTmp, intTemp);
				blackSheet = DateUtil.getSpecialCardver(blackSheetTmp, intTemp);
			}
			// Query query = session.getNamedQuery("BsverError1");
			Query query = session
					.createSQLQuery(SqlStatementDictionary.getIntance().getSQL("com.kingstargroup.action.bgAnalysis.BsheetverErrorAnalysisThread.BsverError1"))
					.addEntity("a", TDevice.class);
			query.setString("blackSheet", blackSheet);
			List list = query.list();
			Iterator iter = list.iterator();
			while (iter.hasNext()) {
				TDevice device = (TDevice) iter.next();
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
					mapDeviceTable.setCpu(Double.parseDouble("0"));
					mapDeviceTable.setDevicename(device.getDevicename());
					mapDeviceTable.setDeviceno(device.getDeviceno());
					mapDeviceTable.setDevicetime("");
					mapDeviceTable.setDevphyid(device.getDevphyid());
					mapDeviceTable.setDevtypecode(device.getDevtypecode());
					mapDeviceTable.setDevusage(device.getDevusage());
					mapDeviceTable.setErrorReason(Long.parseLong("11"));
					mapDeviceTable.setFdevphyid(fdevphyId);			
					mapDeviceTable.setHarddisk(Double.parseDouble("0"));
					mapDeviceTable.setId(deviceTableKey);
					mapDeviceTable.setIp(device.getIp());
					mapDeviceTable.setMemory(Double.parseDouble("0"));
					mapDeviceTable.setRunstatus(device.getRunstatus());
					mapDeviceTable.setServertime("");
					mapDeviceTable.setStatus(device.getStatus());
					mapDeviceTable.setSysid(device.getSysid());
					session.save(mapDeviceTable);
				}
				devid_t+=device.getDeviceid()+",";
				mailRecord++;
				if (!"".equals(mailList)) {
					buffer.append(StringUtil.blksheetStringGenerate(device
							.getDevphyid(), device.getDevicename(), device
							.getCardverno(), blackSheetTmp, "BSHEETVER_ERROR"));
				}
			}
			// �Ž��ĺ������汾����
//			recordTime = DateUtil.getNow();
//			Query query1 = session
//					.createSQLQuery(SqlStatementDictionary.getIntance().getSQL("com.kingstargroup.action.bgAnalysis.BsheetverErrorAnalysisThread.getMJBsverError"))
//					.addEntity("dev", TDevice.class);
//			query1.setString("blackSheet", blackSheet);
//			List list1 = query1.list();
//			Iterator iter1 = list1.iterator();
//			while (iter1.hasNext()) {
//				TDevice device = (TDevice) iter1.next();
//				if (true == recordOrNot) {
//					MapDeviceTable mapDeviceTable = new MapDeviceTable();
//					MapDeviceTableId deviceTableKey = new MapDeviceTableId();
//					
//					deviceTableKey.setAnalysistime(recordTime);
//					deviceTableKey.setDeviceid(device.getDeviceid());
//					
//					Query devquery = session.createSQLQuery(
//							"select dev.devphyid devphy999Id from YKT_CUR.T_DEVICE dev "
//									+ "where dev.deviceid="
//									+ device.getFdeviceid()).addScalar(
//							"devphy999Id", Hibernate.STRING);
//					List devList = devquery.list();
//					Iterator devIter = devList.iterator();
//					String fdevphyId = "";
//					if (devIter.hasNext()) {
//						fdevphyId = devIter.next().toString();
//					}
//
//					mapDeviceTable.setContactName(contactName);// to get
//					
//					mapDeviceTable.setAreacode(device.getAreacode());
//					mapDeviceTable.setCardverno(device.getCardverno());
//					mapDeviceTable.setCpu(Double.parseDouble("0"));
//					mapDeviceTable.setDevicename(device.getDevicename());
//					mapDeviceTable.setDeviceno(device.getDeviceno());
//					mapDeviceTable.setDevicetime("");
//					mapDeviceTable.setDevphyid(device.getDevphyid());
//					mapDeviceTable.setDevtypecode(device.getDevtypecode());
//					mapDeviceTable.setDevusage(device.getDevusage());
//					mapDeviceTable.setErrorReason(Long.parseLong("11"));
//					mapDeviceTable.setFdevphyid(fdevphyId);
//					mapDeviceTable.setHarddisk(Double.parseDouble("0"));
//					mapDeviceTable.setId(deviceTableKey);
//					mapDeviceTable.setIp(device.getIp());
//					mapDeviceTable.setMemory(Double.parseDouble("0"));
//					mapDeviceTable.setRunstatus(device.getRunstatus());
//					mapDeviceTable.setServertime("");
//					mapDeviceTable.setStatus(device.getStatus());
//					mapDeviceTable.setSysid(device.getSysid());
//	
//					session.save(mapDeviceTable);
//				}
//				devid_t+=device.getDeviceid()+",";
//				mailRecord++;
//				if (!"".equals(mailList)) {
//					buffer.append(StringUtil.blksheetStringGenerate(device
//							.getDevphyid(), device.getDevicename(), device
//							.getCardverno(), blackSheetTmp, "BSHEETVER_ERROR"));
//				}
//			}
			
			
			// analysis time record
			if (!"".equals(preAnalysisTime)) {
				Query queryPrev = session
						.createSQLQuery(
								SqlStatementDictionary
										.getIntance()
										.getSQL(
												"com.kingstargroup.action.bgAnalysis.BsheetverErrorAnalysisThread.PreBsverErrorResult"))
						.addEntity("a", MapDeviceTable.class);
				queryPrev.setString("analysisTime", preAnalysisTime);
				List listpre = queryPrev.list();
				Iterator iterPre = listpre.iterator();
				while (iterPre.hasNext()) {
					MapDeviceTable device = (MapDeviceTable) iterPre.next();
					if (devid_t.indexOf(String.valueOf(device.getId().getDeviceid())) == -1) {
						
						MapDeviceTable newdevice =new MapDeviceTable();
						// ԭ���ĺ���
						BeanUtils.copyProperties(newdevice, device);
						newdevice.getId().setAnalysistime(recordTime);
						newdevice.setErrorReason(Long.parseLong("161"));
						session.save(newdevice);
					}
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


		} catch (HibernateException e) {
			logger.error("�������汾��������̳߳��������쳣��", e); //$NON-NLS-1$

			if (tx != null) {
				try {
					tx.rollback();
				} catch (Exception e1) {
					// TODO: handle exception
					e1.printStackTrace();
				}
				
			}
		} catch (Exception e) {
			logger.error("�������汾��������̳߳��������쳣��", e); //$NON-NLS-1$
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
		
		}catch (Exception e) {
			e.printStackTrace();
		}
		
		try {
			// mail
			sendMail();
			// SMG
			sendSMG();
		} catch (Exception e) {
			// TODO: handle exception
			logger.error("�������汾��������̳߳��������쳣��", e); //$NON-NLS-1$
		}

		// sleep thread follows the setting
		try {
			long sleepTime = Long.parseLong(String.valueOf(doubleCycle * 1000))
					- DateUtil.getIntervalTime(DateUtil.getNow(), recordTime);
			if (logger.isInfoEnabled()) {
				logger
						.info("�������汾��������߳̽�����������״̬!"
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
			logger.error("�������汾��������̳߳��������쳣�����ܱ�ǿ��ֹͣ�� ", e); //$NON-NLS-1$
		} catch (Exception e) {
			logger.error("�������汾��������̳߳��������쳣�����ܱ�ǿ��ֹͣ�� ", e); //$NON-NLS-1$
		}
	}

	public void terminate() {
		if (this.isAlive()) {
			logger.warn("�������汾��������߳�״̬�����󣬴�ʱ�߳�״̬����߳�!"); //$NON-NLS-1$
			requestStop = true;
		} else {
			logger.warn("�������汾��������߳�״̬�����󣬴�ʱ�߳�״̬�������߳�!"); //$NON-NLS-1$
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
				logger.info("�������汾��������̷߳����ʼ�����ϵ��:" + contactName);
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
				logger.info("�������汾��������̷߳��Ͷ��Ÿ���ϵ��:" + contactName);
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
