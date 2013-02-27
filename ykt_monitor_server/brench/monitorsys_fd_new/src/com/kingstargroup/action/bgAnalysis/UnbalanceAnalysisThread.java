package com.kingstargroup.action.bgAnalysis;

/**
 * <p>
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: UnbalanceAnalysisThread.java
 * Description: 卡库不平检查类
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				 2006-7-20     何林青             卡库不平检查类
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
import com.kingstargroup.form.MapCaunbalanceTable;
import com.kingstargroup.form.MapCaunbalanceTableKey;
import com.kingstargroup.form.MapContactMonitorTable;
import com.kingstargroup.form.MapContactTable;
import com.kingstargroup.form.MapParamTable;
import com.kingstargroup.form.TAifAccount;
import com.kingstargroup.utils.CommonSendMailUtil;
import com.kingstargroup.utils.CommonSendSMGUtil;
import com.kingstargroup.utils.DateUtil;
import com.kingstargroup.utils.GetApplicationResources;
import com.kingstargroup.utils.StringUtil;

public class UnbalanceAnalysisThread extends Thread implements
		AnalyzeThreadInterface {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(UnbalanceAnalysisThread.class);

	// flag of stop this thread
	private boolean requestStop = false;

	// record analysis time
	private String recordTime = "";

	// default analysis is to analysis all from
	private String startTime = "20050101000000";

	private String endTime = DateUtil.getNow();

	// default analysis cycle is one hour
	private double cycle = 12.0;

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
			logger.info("**************卡库不平分析线程初始化**************"); //$NON-NLS-1$
		}
		try {
			Session session = HibernateSessionFactory.currentSession();
			Query queryTime = session
					.createQuery("from MapAnalysisPoint point where point.analysisname=:analysisName");
			queryTime.setString("analysisName", "UNBALANCE_ERROR");
			Iterator iterTime = queryTime.iterate();
			if (iterTime.hasNext()) {
				MapAnalysisPoint mapAnalysisPoint = (MapAnalysisPoint) iterTime
						.next();
				this.startTime = mapAnalysisPoint.getAnalysispoint();
			}
			Query queryCycle = session
					.createQuery("from MapParamTable param where param.parameter=:paramRefer");
			queryCycle.setString("paramRefer", "CAUnbalanceCycle");
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
			logger.error("卡库不平分析线程初始化失败！", e); //$NON-NLS-1$
		} finally {
			HibernateSessionFactory.closeSession();
		}
		if (logger.isInfoEnabled()) {
			logger.info("**************卡库不平分析线程初始化成功**************"); //$NON-NLS-1$
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
				.createQuery("from MapAlertTable alert where alert.parameter='CAUnbalance'");
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
				.createQuery("from MapParamTable as param where param.parameter=:paramRefer");
		queryCycle.setString("paramRefer", "CAUnbalanceCycle");
		Iterator iterParam = queryCycle.iterate();
		if (iterParam.hasNext()) {
			MapParamTable mapParamTable = (MapParamTable) iterParam.next();
			this.cycle = mapParamTable.getValue().doubleValue();
		}
		String s = String.valueOf(cycle * 3600);
		this.doubleCycle = Integer.parseInt(s.substring(0, s.indexOf('.')));

		// contact list
		Query queryContact = session
				.createQuery("from MapContactMonitorTable monitor where monitor.monitorno='UNBALANCE_ERROR'");
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
			logger.info("卡库不平分析线程开始分析任务"); //$NON-NLS-1$
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
						.info("卡库不平分析线程开始分析时间:" + DateUtil.getNow("yyyy/MM/dd/HH:mm:ss")); //$NON-NLS-1$
			}
			if (1 > DateUtil.checkTimeSequence(endTime, DateUtil.getNow())) {
				if (logger.isInfoEnabled()) {
					logger
							.info("卡库不平分析线程分析时间段：" + startTime + " -- "
									+ endTime);
				}
			} else {
				endTime = DateUtil.getNow();
				if (logger.isInfoEnabled()) {
					logger
							.info("卡库不平分析线程分析时间段：" + startTime + " -- "
									+ endTime);
				}
			}
			getParameter(session);
			// analysis time record
			recordTime = DateUtil.getNow();
			BgMonitor
					.monitorThreadStatusReport(
							"com.kingstargroup.action.bgAnalysis.UnbalanceAnalysisThread",
							"卡库不平分析线程", DateUtil.getNow("yyyy/MM/dd/HH:mm:ss"),
							String.valueOf(this.doubleCycle), "运行中...");
			Query query = session
					.createSQLQuery(
							"select {a.*} from ykt_cur.t_aif_account a "
									+ "where a.cur_freebala<>a.card_balance "
									+ "and a.current_state=1 and (a.act_type=1 or a.act_type=3) "
									+ "order by a.account_id with ur ")
					.addEntity("a", TAifAccount.class);
			List list = query.list();
			Iterator iter = list.iterator();
			while (iter.hasNext()) {
				TAifAccount account = (TAifAccount) iter.next();
				if (true == recordOrNot) {
					MapCaunbalanceTable caUnbalance = new MapCaunbalanceTable();
					MapCaunbalanceTableKey unbalanceKey = new MapCaunbalanceTableKey();
					unbalanceKey.setAccountId(account.getAccountId());
					unbalanceKey.setAnalysisTime(recordTime);
					caUnbalance.setActType(account.getActType());
					caUnbalance.setCardBalance(account.getCardBalance());
					caUnbalance.setCardId(account.getCardId());
					caUnbalance.setCardType(account.getCardType());
					caUnbalance.setConsumeCount(account.getConsumeCount());
					caUnbalance.setCurBala(account.getCurBala());
					caUnbalance.setCurFreebala(account.getCurFreebala());
					caUnbalance.setCurFrozebala(account.getCurFrozebala());
					caUnbalance.setCurrentState(account.getCurrentState());
					caUnbalance.setCustomerId(account.getCustomerId());
					caUnbalance.setCutName(account.getCutName());
					caUnbalance.setCutType(account.getCutType());
					caUnbalance.setId(unbalanceKey);
					caUnbalance.setInBala(account.getInBala());
					caUnbalance.setInCount(account.getInCount());
					caUnbalance.setLastBala(account.getLastBala());
					caUnbalance.setLastFreebala(account.getLastFreebala());
					caUnbalance.setLastFrozebala(account.getLastFrozebala());
					caUnbalance.setOutBala(account.getOutBala());
					caUnbalance.setOutCount(account.getOutCount());
					caUnbalance.setPurseId(account.getPurseId());
					caUnbalance.setStuempNo(account.getStuempNo());
					caUnbalance.setSubno(account.getSubno());
					session.save(caUnbalance);
				}
				mailRecord++;
				if (!"".equals(mailList)) {
					// buffer.append(StringUtil.solidStringGenerate(account.getCardId().toString(),account.getCutName(),account.getStuempNo(),
					// "UNBALANCE_ERROR"));
				}
			}

			// record timepoint analysis
			Object tempAnalysis = session.get(MapAnalysisPoint.class,
					"UNBALANCE_ERROR");
			MapAnalysisPoint analysisPoint = null;
			if (tempAnalysis == null) {
				analysisPoint = new MapAnalysisPoint();
				analysisPoint.setAnalysisname("UNBALANCE_ERROR");
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
			logger.error("卡库不平分析线程出现以下异常：", e); //$NON-NLS-1$

			if (tx != null) {
				tx.rollback();
			}
		} catch (Exception e) {
			logger.error("卡库不平分析线程出现以下异常：", e); //$NON-NLS-1$
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
						.info("卡库不平分析线程结束进入休眠状态!"
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
			logger.error("卡库不平分析线程出现以下异常：可能被强行停止！ ", e); //$NON-NLS-1$
		} catch (Exception e) {
			logger.error("卡库不平分析线程出现以下异常：可能被强行停止！ ", e); //$NON-NLS-1$
		}
	}

	public void terminate() {
		if (this.isAlive()) {
			logger.warn("卡库不平分析线程状态被请求，此时线程状态：活动线程!"); //$NON-NLS-1$
			this.requestStop = true;
		} else {
			logger.warn("卡库不平分析线程状态被请求，此时线程状态：死亡线程!"); //$NON-NLS-1$
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
				logger.info("卡库不平分析线程发送邮件给联系人:" + contactName);
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
									.wholeMailGenerate(nameList[i], DateUtil
											.reFormatTime(recordTime),
											mailRecord, tmpStr,
											"UNBALANCE_ERROR"));
				}
			}
		}
	}

	public void sendSMG() {
		// TODO Auto-generated method stub
		if ((true == smgOrNot) && (!"".equals(phoneNumber)) && mailRecord > 0) {
			if (logger.isInfoEnabled()) {
				logger.info("卡库不平分析线程发送短信给联系人:" + contactName);
			}
			String[] tempList = null;
			String[] nameList = null;
			tempList = phoneNumber.split(";");
			nameList = phoneName.split(";");
			for (int i = 0; i < tempList.length; i++) {
				if (!"".equals(tempList[i])) {
					SmgMessage = StringUtil.wholeSMGGenerate(nameList[i],
							DateUtil.reFormatTime(recordTime), mailRecord,
							"UNBALANCE_ERROR");
					CommonSendSMGUtil.sendSMG(tempList[i], SmgMessage);
				}
			}
		}
	}
}
