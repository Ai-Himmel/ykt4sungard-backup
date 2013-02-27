/**
 * 
 */
package com.kingstargroup.action.bgDeal;

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
import com.kingstargroup.action.bgAnalysis.BgMonitor;
import com.kingstargroup.action.bgAnalysis.DeviceNameDictionary;
import com.kingstargroup.commons.AnalyzeThreadInterface;
import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.form.MapAlertTable;
import com.kingstargroup.form.MapAnalysisPoint;
import com.kingstargroup.form.MapContactMonitorTable;
import com.kingstargroup.form.MapContactTable;
import com.kingstargroup.form.MapParamTable;
import com.kingstargroup.form.MapSerialostTable;
import com.kingstargroup.form.TMsglist;
import com.kingstargroup.utils.CommonSendMailUtil;
import com.kingstargroup.utils.CommonSendSMGUtil;
import com.kingstargroup.utils.DateUtil;
import com.kingstargroup.utils.GetApplicationResources;
import com.kingstargroup.utils.OracleTimeUtil;
import com.kingstargroup.utils.StringUtil;

/**
 * <br>
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. <br>
 * File name: SerialLostDealThread.java<br>
 * Description: <br>
 * Modify History（或Change Log）: <br>
 * 操作类型（创建、修改等） 操作日期 操作者 操作内容简述<br>
 * 创建 2005-11-1 何林青 <br>
 * <p>
 * 
 * @author 何林青
 * @version 1.0
 * @since 1.0
 */
public class SerialLostDealThread extends Thread implements
		AnalyzeThreadInterface {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(SerialLostDealThread.class);

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
	private int doubleCycle = 1;

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

	/**
	 * 
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
			logger.info("**************流水缺失处理线程初始化**************"); //$NON-NLS-1$
		}
		try {
			Session session = HibernateSessionFactory.currentSession();
			Query queryTime = session
					.createQuery("from MapAnalysisPoint point where point.analysisname=:analysisName");
			queryTime.setString("analysisName", "SERI_LOSS_DEAL");
			Iterator iterTime = queryTime.iterate();
			if (iterTime.hasNext()) {
				MapAnalysisPoint mapAnalysisPoint = (MapAnalysisPoint) iterTime
						.next();
				this.startTime = mapAnalysisPoint.getAnalysispoint();
			}
			Query queryCycle = session
					.createQuery("from MapParamTable param where param.parameter=:paramRefer");
			queryCycle.setString("paramRefer", "TradeLackDealCycle");
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

			// monitor param
			Query queryOrNot = session
					.createQuery("from MapAlertTable alert where alert.parameter='RecordLack'");
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
				queryPhone.setString("contactName", contactMonitor
						.getContactname());
				queryPhone.setString("starttime", nowDayTime);
				queryPhone.setString("endtime", nowDayTime);
				Iterator iterPhone = queryPhone.iterate();
				if (iterPhone.hasNext()) {
					MapContactTable contactTable = (MapContactTable) iterPhone
							.next();
					int dayofWeek = DateUtil.getDayofWeek();
					if ((1 == dayofWeek)
							&& ("1".equals(contactTable.getWeekdays()
									.substring(6, 7)))) {
						if (!"".equals(contactTable.getCellphone())) {
							phoneNumber += contactTable.getCellphone() + ";";
							phoneName += contactTable.getContactname() + ";";
						}
						if (!"".equals(contactTable.getEmail())) {
							mailList += contactTable.getEmail() + ";";
							mailName += contactMonitor.getContactname() + ";";
						}
						if (!"".equals(contactMonitor.getContactname())) {
							contactName += contactMonitor.getContactname()
									+ ",";
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
							contactName += contactMonitor.getContactname()
									+ ",";
						}
					}
				}
			}
			if (!"".equals(contactName)) {
				contactName = contactName.substring(0, contactName
						.lastIndexOf(","));
			}
		} catch (HibernateException e) {
			logger.error("流水缺失处理线程初始化失败！", e); //$NON-NLS-1$

		} finally {
			HibernateSessionFactory.closeSession();
		}

		if (logger.isInfoEnabled()) {
			logger.info("**************流水缺失处理线程初始化成功**************"); //$NON-NLS-1$
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
				.createQuery("from MapParamTable as param where param.parameter=:paramRefer");
		queryCycle.setString("paramRefer", "TradeLackDealCycle");
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
			logger.info("流水缺失处理线程开始分析任务"); //$NON-NLS-1$
		}

		Transaction tx = null;
		try {
			Session session = HibernateSessionFactory.currentSession();
			tx = session.beginTransaction();
			// specialInitParameter(session);
			this.accelateParam = Integer
					.parseInt(BgMonitor.getIntance().SerialLostAnalysisThreadaccelateParam);
			// this.endTime = DateUtil.getNewTime(startTime, doubleCycle);
			endTime = DateUtil.getNewTime(endTime, accelateParam * 60);

			if (logger.isInfoEnabled()) {
				logger
						.info("流水缺失处理线程开始分析时间:" + DateUtil.getNow("yyyy/MM/dd/HH:mm:ss")); //$NON-NLS-1$
			}
			if (1 > DateUtil.checkTimeSequence(endTime, DateUtil.getNow())) {
				if (logger.isInfoEnabled()) {
					logger
							.info("流水缺失处理线程分析时间段：" + startTime + " -- "
									+ endTime);
				}
			} else {
				endTime = DateUtil.getNow();
				if (logger.isInfoEnabled()) {
					logger
							.info("流水缺失处理线程分析时间段：" + startTime + " -- "
									+ endTime);
				}
			}

			// get new parameter timely!
			getParameter(session);

			recordTime = DateUtil.getNow();

			BgMonitor.monitorThreadStatusReport(
					"com.kingstargroup.action.bgAnalysis.SerialLostDealThread",
					"流水缺失处理线程", DateUtil.getNow("yyyy/MM/dd/HH:mm:ss"), String
							.valueOf(this.doubleCycle), "运行中...");

			Query query = session
					.createQuery(SqlStatementDictionary.getIntance().getSQL("com.kingstargroup.action.bgDeal.SerialLostDealThread.getLostserial"));
			query.setString("startTime", startTime);
			query.setString("endTime", endTime);
			List list = query.list();
			Iterator iter = list.iterator();
			while (iter.hasNext()) {
				MapSerialostTable mapSerialostTable = (MapSerialostTable) iter
						.next();
				// Query queryTwo = session
				// .createQuery("from TTifRcvdtl a where a.id.serialNo=:seialno
				// and a.id.txDate=:txdate and a.id.deviceId=:deviceId and
				// a.id.txCode=930031 ");
				Query queryTwo = session.createSQLQuery(SqlStatementDictionary.getIntance().getSQL("com.kingstargroup.action.bgDeal.SerialLostDealThread.checkLostserial"))
						.addScalar("serialNo", Hibernate.INTEGER);

				queryTwo.setLong("serialno", mapSerialostTable.getId()
						.getSerialNo());
				queryTwo.setString("txdate1", DateUtil.getOtherDate(mapSerialostTable.getTxDate(),1));
				queryTwo.setString("txdate2", mapSerialostTable.getTxDate());
				queryTwo.setString("txdate3", DateUtil.getOtherDate(mapSerialostTable.getTxDate(),-1));
				queryTwo.setString("deviceId", mapSerialostTable.getId()
						.getDeviceId().trim());
				List listTwo = queryTwo.list();
				if (listTwo.size() > 0) {
					// serial has uploaded
					mapSerialostTable.setSerialStatus(Long.parseLong("1"));
					session.update(mapSerialostTable);
					session.flush();
				} else {
					// serial has not uploaded. distribution command to fetch it
					// .
					TMsglist mesList = new TMsglist();
					Query queryOne = session.createSQLQuery(SqlStatementDictionary.getIntance().getSQL("com.kingstargroup.action.bgDeal.SerialLostDealThread.getsubsystem"))
							.addScalar("subsystemId", Hibernate.STRING);
					queryOne.setString("devId", mapSerialostTable.getId()
							.getDeviceId().trim());
					List listOne = queryOne.list();
					if (listOne.size() > 0) {
						if("0201".equals(DeviceNameDictionary.getInstance().getType(mapSerialostTable.getId().getDeviceId()))){
							//增值机				
							mesList.setCardno(Long.parseLong("0"));
							mesList.setDelflag("0");
							mesList.setDeviceid(Long.parseLong(listOne.get(0)
									.toString()));
							Query devquery = session
									.createSQLQuery(SqlStatementDictionary.getIntance().getSQL("com.kingstargroup.action.bgDeal.SerialLostDealThread.getdeviceid"))
									.addScalar("deviceId", Hibernate.STRING);
							devquery.setString("dev999Id", mapSerialostTable
									.getId().getDeviceId().trim());
							List devList = devquery.list();
							Iterator devIter = devList.iterator();
							long devId = Long.parseLong("0");
							if (devIter.hasNext()) {
								devId = Long.parseLong(devIter.next().toString());
							}
							mesList.setSysid(devId);
							mesList.setFuncno(Long.parseLong("930018"));
							mesList.setReqdata("<STARTNUM>"
									+ mapSerialostTable.getId().getSerialNo()
									+ "</STARTNUM><ENDNUM>"
									+ mapSerialostTable.getId().getSerialNo()
									+ "</ENDNUM>");
							mesList.setErrcode(Long.parseLong("9999"));
							mesList.setCreatedtime(OracleTimeUtil.getSysDate(0));
							mesList.setMsglevel(Long.parseLong("1"));
							mesList.setMaxsendcnt(Long.parseLong("100"));
							mesList.setPfuncno(Long.parseLong("930018"));
							mesList.setSendcnt(Long.parseLong("0"));
							mesList.setDelflag("0");
							mesList.setStatus("3");
							session.save(mesList);
							
						}else{
							mesList.setCardno(Long.parseLong("0"));
							mesList.setDelflag("0");
							mesList.setDeviceid(Long.parseLong(listOne.get(0)
									.toString()));
							Query devquery = session
									.createSQLQuery(SqlStatementDictionary.getIntance().getSQL("com.kingstargroup.action.bgDeal.SerialLostDealThread.getdeviceid"))
									.addScalar("deviceId", Hibernate.STRING);
							devquery.setString("dev999Id", mapSerialostTable
									.getId().getDeviceId().trim());
							List devList = devquery.list();
							Iterator devIter = devList.iterator();
							long devId = Long.parseLong("0");
							if (devIter.hasNext()) {
								devId = Long.parseLong(devIter.next().toString());
							}
							
							mesList.setSysid(devId);
							mesList.setFuncno(Long.parseLong("930016"));
							mesList.setReqdata("<STARTNUM>"
									+ mapSerialostTable.getId().getSerialNo()
									+ "</STARTNUM><ENDNUM>"
									+ mapSerialostTable.getId().getSerialNo()
									+ "</ENDNUM>");
							mesList.setErrcode(Long.parseLong("9999"));
							mesList.setCreatedtime(OracleTimeUtil.getSysDate(0));
							mesList.setMsglevel(Long.parseLong("1"));
							mesList.setMaxsendcnt(Long.parseLong("100"));
							mesList.setPfuncno(Long.parseLong("930016"));
							mesList.setSendcnt(Long.parseLong("0"));
							mesList.setDelflag("0");
							mesList.setStatus("3");
							session.save(mesList);
						}
						
					}
				}

			}

			// todo:check today's serials whether upload?
			Query queryOne = session
					.createQuery(SqlStatementDictionary.getIntance().getSQL("com.kingstargroup.action.bgDeal.SerialLostDealThread.checkunretainserial"));
			queryOne.setString("startTime", startTime);
			queryOne.setString("txDate", DateUtil.getNewTime(startTime,
					-7776000).substring(0, 8));
			List listOne = queryOne.list();
			Iterator iterOne = listOne.iterator();
			while (iterOne.hasNext()) {
				MapSerialostTable mapSerialostTable = (MapSerialostTable) iterOne
						.next();
				// Query queryThree = session
				// .createQuery("from TTifRcvdtl a where a.id.serialNo=:seialno
				// " +
				// "and a.id.txDate=:txdate and a.id.deviceId=:deviceId and
				// a.id.txCode=930031 ");
				Query queryThree = session.createSQLQuery(SqlStatementDictionary.getIntance().getSQL("com.kingstargroup.action.bgDeal.SerialLostDealThread.getserailno"))
						.addScalar("serialNo", Hibernate.INTEGER);
				queryThree.setLong("serialno", mapSerialostTable.getId().getSerialNo());
				queryThree.setString("txdate", mapSerialostTable.getTxDate());
				queryThree.setString("deviceId", mapSerialostTable.getId()
						.getDeviceId().trim());
				List listThree = queryThree.list();
				if (listThree.size() > 0) {
					// serial has uploaded
					mapSerialostTable.setSerialStatus(Long.parseLong("1"));
					session.update(mapSerialostTable);
					session.flush();
				} else {
					// hasn't uploaded
					// TODO: record it as email or SMS
					mailRecord++;
					if (!"".equals(mailList)) {
						String device_name = "";
						device_name = DeviceNameDictionary.getInstance().get(
								mapSerialostTable.getId().getDeviceId().trim());
						buffer
								.append(StringUtil
										.seriallostStringGenerate(
												mapSerialostTable.getId()
														.getDeviceId().trim(),
												device_name, mapSerialostTable
														.getId().getSerialNo(),
												mapSerialostTable.getTxDate(),
												mapSerialostTable.getTxTime(),
												"SERI_LOSS_DEAL"));
					}
				}

			}

			// record timepoint analysis
			Object tempAnalysis = session.get(MapAnalysisPoint.class,
					"SERI_LOSS_DEAL");
			MapAnalysisPoint analysisPoint = null;
			if (tempAnalysis == null) {
				analysisPoint = new MapAnalysisPoint();
				analysisPoint.setAnalysisname("SERI_LOSS_DEAL");
				analysisPoint.setAnalysispoint(endTime);
				session.save(analysisPoint);
			} else {
				analysisPoint = (MapAnalysisPoint) tempAnalysis;
				analysisPoint.setAnalysispoint(endTime);
				session.update(analysisPoint);
			}

			tx.commit();


		} catch (HibernateException e) {
			logger.error("流水缺失处理线程出现以下异常：", e); //$NON-NLS-1$
//			e.printStackTrace();
			if (tx != null) {
				tx.rollback();
			}

		} catch (Exception e) {
			logger.error("流水缺失处理线程出现以下异常：", e); //$NON-NLS-1$
			if (tx != null) {
				tx.rollback();
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
			logger.error("流水缺失处理线程出现以下异常：", e); //$NON-NLS-1$
		}
		// sleep thread follows the setting
		try {
			long sleepTime = Long.parseLong(String.valueOf(doubleCycle * 1000))
					- DateUtil.getIntervalTime(DateUtil.getNow(), recordTime);
			if (logger.isInfoEnabled()) {
				logger
						.info("流水缺失处理线程结束进入休眠状态!"
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
			logger.error("流水缺失处理线程出现以下异常：可能被强行停止！ ", e); //$NON-NLS-1$
		} catch (Exception e) {
			logger.error("流水缺失处理线程出现以下异常：可能被强行停止！ ", e); //$NON-NLS-1$
		}
	}

	public void terminate() {
		// TODO Auto-generated method stub
		if (this.isAlive()) {
			logger.warn("流水缺失处理线程状态被请求，此时线程状态：活动线程!"); //$NON-NLS-1$
			requestStop = true;
		} else {
			logger.warn("流水缺失处理线程状态被请求，此时线程状态：死亡线程!"); //$NON-NLS-1$
			this.terminate();

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
				logger.info("流水缺失处理线程发送邮件给联系人:" + contactName);
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
											mailRecord, tmpStr,
											"SERI_LOSS_DEAL"));
				}
			}
		}

	}

	public void sendSMG() {
		// TODO Auto-generated method stub
		if ((true == smgOrNot) && (!"".equals(phoneNumber)) && mailRecord > 0) {
			if (logger.isInfoEnabled()) {
				logger.info("流水缺失处理线程发送短信给联系人:" + contactName);
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
							"SERI_LOSS_DEAL");
					CommonSendSMGUtil.sendSMG(tempList[i], SmgMessage);
				}
			}
		}
	}

}

