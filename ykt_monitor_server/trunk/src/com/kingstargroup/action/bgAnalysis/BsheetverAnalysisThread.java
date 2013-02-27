package com.kingstargroup.action.bgAnalysis;

/**
 * <p>
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: BsheetverAnalysisThread.java
 * Description: 黑卡消费流水检查线程
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				2005-10-19   何林青    黑卡消费流水检查线程
 * 修改					2006-07-20   何林青    修改日志记录方式及报警方式           
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
import com.kingstargroup.form.MapParamTable;
import com.kingstargroup.form.MapSerialexceptTable;
import com.kingstargroup.form.MapSerialexceptTableId;
import com.kingstargroup.form.TPosdtl;
import com.kingstargroup.utils.CommonSendMailUtil;
import com.kingstargroup.utils.CommonSendSMGUtil;
import com.kingstargroup.utils.DateUtil;
import com.kingstargroup.utils.GetApplicationResources;
import com.kingstargroup.utils.StringUtil;

public class BsheetverAnalysisThread extends Thread implements
		AnalyzeThreadInterface {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(BsheetverAnalysisThread.class);

	private static boolean requestStop = false;

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
		logger.info("$$$$$$$$$$$$$$$$黑卡消费分析线程停止运行$$$$$$$$$$$$$$$$$$$$$"); //$NON-NLS-1$
	}

	public void initParam() {
		if (logger.isInfoEnabled()) {
			logger.info("**************黑卡消费分析线程初始化**************"); //$NON-NLS-1$
		}
		try {
			Session session = HibernateSessionFactory.currentSession();
			Query queryTime = session
					.createQuery("from MapAnalysisPoint  point where point.analysisname=:analysisName");
			queryTime.setString("analysisName", "BSHEETVER_EXCEPTION");
			Iterator iterTime = queryTime.iterate();
			if (iterTime.hasNext()) {
				MapAnalysisPoint mapAnalysisPoint = (MapAnalysisPoint) iterTime
						.next();
				this.startTime = mapAnalysisPoint.getAnalysispoint();
			}
			Query queryCycle = session
					.createQuery("from MapParamTable  param where param.parameter=:paramRefer");
			queryCycle.setString("paramRefer", "BlackCardCycle");
			Iterator iterParam = queryCycle.iterate();
			if (iterParam.hasNext()) {
				MapParamTable mapParamTable = (MapParamTable) iterParam.next();
				if ("BlackCardCycle".equals(mapParamTable.getParameter())) {
					this.cycle = mapParamTable.getValue();
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
			logger.error("黑卡消费分析线程初始化失败！", e); //$NON-NLS-1$

		} finally {
			HibernateSessionFactory.closeSession();
		}

		if (logger.isInfoEnabled()) {
			logger.info("**************黑卡消费分析线程初始化成功**************"); //$NON-NLS-1$
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
				.createQuery("from MapAlertTable alert where alert.parameter='BlackCardComsumption'");
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
				.createQuery("from MapContactMonitorTable monitor where monitor.monitorno='BSHEETVER_EXCEPTION'");
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
				.createQuery("from MapParamTable  param where param.parameter=:paramRefer");
		queryCycle.setString("paramRefer", "BlackCardCycle");
		Iterator iterParam = queryCycle.iterate();
		if (iterParam.hasNext()) {
			MapParamTable mapParamTable = (MapParamTable) iterParam.next();
			if ("BlackCardCycle".equals(mapParamTable.getParameter())) {
				this.cycle = mapParamTable.getValue();
			}

		}
		String s = String.valueOf(cycle * 3600);
		this.doubleCycle = Integer.parseInt(s.substring(0, s.indexOf('.')));
	}

	public void anaylize() {
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
						.info("黑卡消费分析线程开始分析时间:" + DateUtil.getNow("yyyy/MM/dd/HH:mm:ss")); //$NON-NLS-1$
			}
			if (1 != DateUtil.checkTimeSequence(endTime, DateUtil.getNow())) {
				if (logger.isInfoEnabled()) {
					logger
							.info("黑卡消费分析线程分析时间段：" + startTime + " -- "
									+ endTime);
				}

			} else {
				endTime = DateUtil.getNow();
				if (logger.isInfoEnabled()) {
					logger
							.info("黑卡消费分析线程分析时间段：" + startTime + " -- "
									+ endTime);
				}
			}

			getParameter(session);
			recordTime = DateUtil.getNow();
			// 黑卡继续消费
			Query query = session
					.createSQLQuery(
							SqlStatementDictionary
									.getIntance()
									.getSQL(
											"com.kingstargroup.action.bgAnalysis.BsheetverAnalysisThread.Analyze1"))
					.addEntity("posdtl", TPosdtl.class);
			query.setString("startTime", startTime);
			query.setString("endTime", endTime);
			List list = query.list();
			Iterator iter = list.iterator();
			while (iter.hasNext()) {
				TPosdtl rcvdtl = (TPosdtl) iter.next();
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
					seriExcept.setAbnormaltype(Long.parseLong("51"));
					session.save(seriExcept);
				}
				mailRecord++;
				if (!"".equals(mailList)) {
					String device_name = "";
					device_name = DeviceNameDictionary.getInstance().get(
							rcvdtl.getId().getDevphyid()).trim();
					Query queryCustomer = session
							.createSQLQuery(
									SqlStatementDictionary
											.getIntance()
											.getSQL(
													"com.kingstargroup.action.bgAnalysis.BsheetverAnalysisThread.getCutName"))
							.addScalar("cutName", Hibernate.STRING);
					queryCustomer.setLong("cardno", rcvdtl.getCardno());
					List listCust = queryCustomer.list();
					String cust_name = "";
					if (listCust.size() > 0) {
						cust_name = listCust.get(0).toString().trim();
					}
					buffer.append(StringUtil.solidStringGenerate(rcvdtl.getId()
							.getDevphyid(), device_name, rcvdtl.getCardno(),
							cust_name, rcvdtl.getId().getDevseqno(), rcvdtl
									.getId().getTransdate(), rcvdtl
									.getTranstime(),
							"BSHEETVER_EXCEPTION.BLACK_ERR"));
				}
			}
			session.flush();
			session.clear();

			// // 白卡不能消费
			// recordTime = DateUtil.getNow();
			// Query queryOne = session
			// .createSQLQuery(SqlStatementDictionary.getIntance().getSQL("com.kingstargroup.action.bgAnalysis.BsheetverAnalysisThread.Analyze2"))
			// .addEntity("posdtl", TTifRcvdtl.class);
			// queryOne.setString("startTime", startTime);
			// queryOne.setString("endTime", endTime);
			// List listOne = queryOne.list();
			// Iterator iterOne = listOne.iterator();
			// while (iterOne.hasNext()) {
			// TTifRcvdtl rcvdtl = (TTifRcvdtl) iterOne.next();
			// Query queryDiv = session
			// .createSQLQuery(
			// "select b.card_id as cardId "
			// + "from YKT_CUR.V_BLKLST b where b.is_ad=1 "
			// + "and b.card_id=:cardId and concat('20',b.volume)<=:txTime with
			// ur")
			// .addScalar("cardId", Hibernate.INTEGER);
			// queryDiv.setString("txTime", rcvdtl.getId().getTxDate()
			// + rcvdtl.getId().getTxTime());
			// queryDiv.setInteger("cardId", rcvdtl.getId().getCardNo()
			// .intValue());
			// List listDiv = queryDiv.list();
			// Iterator iterDiv = listDiv.iterator();
			// if (iterDiv.hasNext()) {
			// if (true == recordOrNot) {
			// MapSerialexceptTable seriExcept = new MapSerialexceptTable();
			// MapSerialexceptTableKey seriExptKey = new
			// MapSerialexceptTableKey();
			// seriExptKey.setAnalysisTime(recordTime);
			// seriExptKey.setTxDate(rcvdtl.getId().getTxDate());
			// seriExptKey.setTxTime(rcvdtl.getId().getTxTime());
			// seriExptKey.setCardNo(rcvdtl.getId().getCardNo());
			// seriExptKey.setDeviceId(rcvdtl.getId().getDeviceId());
			// seriExptKey.setSerialNo(rcvdtl.getId().getSerialNo());
			// seriExptKey.setTxCode(rcvdtl.getId().getTxCode());
			// seriExcept.setAmount(rcvdtl.getAmount());
			// seriExcept.setColTimestamp(rcvdtl.getColTimestamp());
			// seriExcept.setComuVer(rcvdtl.getComuVer());
			// seriExcept.setDealDate(rcvdtl.getDealDate());
			// seriExcept.setDealTime(rcvdtl.getDealTime());
			// seriExcept.setId(seriExptKey);
			// seriExcept.setInBala(rcvdtl.getInBala());
			// seriExcept.setOutBala(rcvdtl.getOutBala());
			// seriExcept.setPurseNo(rcvdtl.getPurseNo());
			// seriExcept.setRunReason(rcvdtl.getRunReason());
			// seriExcept.setStatus(rcvdtl.getStatus());
			// seriExcept.setSysId(rcvdtl.getSysId());
			// seriExcept.setTotalCnt(rcvdtl.getTotalCnt());
			// seriExcept.setTxMark(rcvdtl.getTxMark());
			// seriExcept.setContactname(contactName);
			// seriExcept.setAbnormaltype(Short.valueOf("52"));
			// session.save(seriExcept);
			// }
			// mailRecord++;
			// if (!"".equals(mailList)) {
			// String device_name = "";
			// device_name = DeviceNameDictionary.getInstance().get(
			// rcvdtl.getId().getDeviceId()).trim();
			// Query queryCustomer = session
			// .createSQLQuery(SqlStatementDictionary.getIntance().getSQL("com.kingstargroup.action.bgAnalysis.BsheetverAnalysisThread.getCutName"))
			// .addScalar("cutName", Hibernate.STRING);
			// queryCustomer.setInteger("cutId", rcvdtl.getId()
			// .getCardNo().intValue());
			// List listCust = queryCustomer.list();
			// String cust_name = "";
			// if (listCust.size() > 0) {
			// cust_name = listCust.get(0).toString().trim();
			// }
			// buffer.append(StringUtil.solidStringGenerate(rcvdtl
			// .getId().getDeviceId(), device_name, rcvdtl
			// .getId().getCardNo(), cust_name, rcvdtl.getId()
			// .getSerialNo().toString(), rcvdtl.getId()
			// .getTxDate(), rcvdtl.getId().getTxTime(),
			// "BSHEETVER_EXCEPTION.WHITE_ERR"));
			// }
			// }
			//
			// }
			// session.flush();
			// session.clear();

			// 黑卡标记消费
			recordTime = DateUtil.getNow();
			BgMonitor
			.monitorThreadStatusReport(
					"com.kingstargroup.action.bgAnalysis.BsheetverAnalysisThread",
					"黑卡消费分析线程", DateUtil.getNow("yyyy/MM/dd/HH:mm:ss"),
					String.valueOf(this.doubleCycle), "运行中...");
			
			
			Query queryOne = session
					.createSQLQuery(
							SqlStatementDictionary
									.getIntance()
									.getSQL(
											"com.kingstargroup.action.bgAnalysis.BsheetverAnalysisThread.Analyze2"))
					.addEntity("posdtl", TPosdtl.class);
			queryOne.setString("startTime", startTime);
			queryOne.setString("endTime", endTime);
			
			List listOne = queryOne.list();
			Iterator iterThree = listOne.iterator();
			while (iterThree.hasNext()) {
				TPosdtl rcvdtl = (TPosdtl) iterThree.next();
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
						seriExcept.setAbnormaltype(Long.parseLong("53"));
						session.save(seriExcept);
					}
					mailRecord++;
					
					if (!"".equals(mailList)) {
						String device_name = "";
						device_name = DeviceNameDictionary.getInstance().get(
								rcvdtl.getId().getDevphyid()).trim();
						Query queryCustomer = session
								.createSQLQuery(
										SqlStatementDictionary
												.getIntance()
												.getSQL(
														"com.kingstargroup.action.bgAnalysis.BsheetverAnalysisThread.getCutName"))
								.addScalar("cutName", Hibernate.STRING);
						queryCustomer.setLong("cardno", rcvdtl.getCardno());
						List listCust = queryCustomer.list();
						String cust_name = "";
						if (listCust.size() > 0) {
							cust_name = listCust.get(0).toString().trim();
						}
						buffer.append(StringUtil.solidStringGenerate(rcvdtl.getId()
								.getDevphyid(), device_name, rcvdtl.getCardno(),
								cust_name, rcvdtl.getId().getDevseqno(), rcvdtl
										.getId().getTransdate(), rcvdtl
										.getTranstime(),
								"BSHEETVER_EXCEPTION.FLAG_ERR"));
					}

			}
			session.flush();
			session.clear();

			// record timepoint analysis
			Object tempAnalysis = session.get(MapAnalysisPoint.class,
					"BSHEETVER_EXCEPTION");
			MapAnalysisPoint analysisPoint = null;
			if (tempAnalysis == null) {
				analysisPoint = new MapAnalysisPoint();
				analysisPoint.setAnalysisname("BSHEETVER_EXCEPTION");
				analysisPoint.setAnalysispoint(endTime);
				session.save(analysisPoint);
			} else {
				analysisPoint = (MapAnalysisPoint) tempAnalysis;
				analysisPoint.setAnalysispoint(endTime);
				session.update(analysisPoint);
			}

			tx.commit();

		} catch (HibernateException e) {
			logger.error("黑卡消费分析线程出现以下异常：", e); //$NON-NLS-1$
			if (tx != null) {
				try {
					tx.rollback();
				} catch (Exception e1) {
					// TODO: handle exception
					e1.printStackTrace();
				}
			}
		} catch (Exception e) {
			logger.error("黑卡消费分析线程出现以下异常：", e); //$NON-NLS-1$
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
			logger.error("黑卡消费分析线程出现以下异常：", e); //$NON-NLS-1$
		}

		// sleep thread follows the setting
		try {
			long sleepTime = Long.parseLong(String.valueOf(doubleCycle * 1000))
					- DateUtil.getIntervalTime(DateUtil.getNow(), recordTime);
			if (logger.isInfoEnabled()) {
				logger
						.info("黑卡消费线程分析结束进入休眠状态!"
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
			logger.error("黑卡消费分析线程出现以下异常：可能被强行停止！ ", e); //$NON-NLS-1$
		} catch (Exception e) {
			logger.error("黑卡消费分析线程出现以下异常：可能被强行停止！ ", e); //$NON-NLS-1$
		}
	}

	public void terminate() {
		// TODO Auto-generated method stub
		if (this.isAlive()) {
			logger.warn("黑卡消费分析线程状态被请求，此时线程状态：活动线程!"); //$NON-NLS-1$
			requestStop = true;
		} else {
			logger.warn("黑卡消费分析线程状态被请求，此时线程状态：死亡线程!"); //$NON-NLS-1$
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
				logger.info("黑卡消费分析线程发送邮件给联系人:" + contactName);
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
				if (!"".equals(tempList[i])) {
					CommonSendMailUtil.sendMail(GetApplicationResources
							.getInstance().getString(
									"com.kingstar.MonitorSys.SUBJECT_SERIAL"),
							nameList[i], tempList[i], StringUtil
									.wholeMailGenerate(nameList[i], DateUtil
											.reFormatTime(recordTime),
											mailRecord, tmpStr,
											"BSHEETVER_EXCEPTION"));
				}
			}
		}
	}

	public void sendSMG() {
		// TODO Auto-generated method stub
		if ((true == smgOrNot) && (!"".equals(phoneNumber)) && mailRecord > 0) {
			if (logger.isInfoEnabled()) {
				logger.info("黑卡消费分析线程发送短信给联系人:" + contactName);
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
							"BSHEETVER_EXCEPTION");
					CommonSendSMGUtil.sendSMG(tempList[i], SmgMessage);
				}
			}

		}
	}
}
