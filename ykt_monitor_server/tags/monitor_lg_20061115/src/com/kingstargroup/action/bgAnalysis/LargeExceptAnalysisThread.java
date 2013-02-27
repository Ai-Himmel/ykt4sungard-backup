package com.kingstargroup.action.bgAnalysis;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: LargeExceptAnalysisThread
 * Description: 大额不正常流水检查线程类
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期     操作者    操作内容简述
 * 创建  				2005-10-19   何林青    大额不正常流水检查线程
 * 修改					2006-07-20   何林青    修改日志记录方式
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
import java.util.Iterator;
import java.util.List;
import com.kingstargroup.commons.AnalyzeThreadInterface;
import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.form.MapAlertTable;
import com.kingstargroup.form.MapAnalysisPoint;
import com.kingstargroup.form.MapContactMonitorTable;
import com.kingstargroup.form.MapContactTable;
import com.kingstargroup.form.MapParamTable;
import com.kingstargroup.form.MapSerialexceptTable;
import com.kingstargroup.form.MapSerialexceptTableKey;
import com.kingstargroup.form.RcvdtlCardResult;
import com.kingstargroup.form.TTifRcvdtl;
import com.kingstargroup.utils.CommonSendMailUtil;
import com.kingstargroup.utils.CommonSendSMGUtil;
import com.kingstargroup.utils.DateUtil;
import com.kingstargroup.utils.GetApplicationResources;
import com.kingstargroup.utils.StringUtil;

public class LargeExceptAnalysisThread extends Thread implements
		AnalyzeThreadInterface {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(LargeExceptAnalysisThread.class);

	// flag of stop this thread
	private boolean requestStop = false;

	// record analysis time
	private String recordTime = "";

	// default analysis is to analysis all from
	public String startTime = "20050101000000";

	// default analysis is to analysis to now
	public String endTime = DateUtil.getNow();

	// default analysis cycle is one hour
	private double cycle = 1.0;

	// money limit
	private double limit = 100;

	// single money limit
	private double singleLimit = 19;

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
			logger.info("**************大额不正常流水分析线程初始化**************"); //$NON-NLS-1$
		}
		try {
			Session session = HibernateSessionFactory.currentSession();
			Query queryTime = session
					.createQuery("from MapAnalysisPoint as point where point.analysisname=:analysisName");
			queryTime.setString("analysisName", "LARGE_EXCEPTION");
			Iterator iterTime = queryTime.iterate();
			if (iterTime.hasNext()) {
				MapAnalysisPoint mapAnalysisPoint = (MapAnalysisPoint) iterTime
						.next();
				this.startTime = mapAnalysisPoint.getAnalysispoint();
			}
			Query queryCycle = session
					.createQuery("from MapParamTable as param where param.parameter=:paramRefer "
							+ "or param.parameter=:paramRefer1 or param.parameter=:paramRefer2");
			queryCycle.setString("paramRefer", "LargeAmountCycle");
			queryCycle.setString("paramRefer1", "LargeAmountLimit");
			queryCycle.setString("paramRefer2", "SingleAmountLimit");
			List listParam = queryCycle.list();
			Iterator iterParam = listParam.iterator();
			while (iterParam.hasNext()) {
				MapParamTable mapParamTable = (MapParamTable) iterParam.next();
				if ("LargeAmountCycle".equals(mapParamTable.getParameter())) {
					this.cycle = mapParamTable.getValue().doubleValue();
				}
				if ("LargeAmountLimit".equals(mapParamTable.getParameter())) {
					this.limit = mapParamTable.getValue().doubleValue();
				}
				if ("SingleAmountLimit".equals(mapParamTable.getParameter())) {
					this.singleLimit = mapParamTable.getValue().doubleValue();
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
			logger.error("大额不正常流水分析线程初始化失败！", e); //$NON-NLS-1$
		} finally {
			HibernateSessionFactory.closeSession();
		}
		if (logger.isInfoEnabled()) {
			logger.info("**************大额不正常流水分析线程初始化成功**************"); //$NON-NLS-1$
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
				.createQuery("from MapAlertTable alert where alert.parameter='LargeAmountRecord'");
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
				.createQuery("from MapContactMonitorTable monitor where monitor.monitorno='LARGE_EXCEPTION'");
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
		Query queryCycle = session
				.createQuery("from MapParamTable as param where param.parameter=:paramRefer "
						+ "or param.parameter=:paramRefer1 or param.parameter=:paramRefer2");
		queryCycle.setString("paramRefer", "LargeAmountCycle");
		queryCycle.setString("paramRefer1", "LargeAmountLimit");
		queryCycle.setString("paramRefer2", "SingleAmountLimit");
		List listParam = queryCycle.list();
		Iterator iterParam = listParam.iterator();
		while (iterParam.hasNext()) {
			MapParamTable mapParamTable = (MapParamTable) iterParam.next();
			if ("LargeAmountCycle".equals(mapParamTable.getParameter())) {
				this.cycle = mapParamTable.getValue().doubleValue();
			}
			if ("LargeAmountLimit".equals(mapParamTable.getParameter())) {
				this.limit = mapParamTable.getValue().doubleValue();
			}
			if ("SingleAmountLimit".equals(mapParamTable.getParameter())) {
				this.singleLimit = mapParamTable.getValue().doubleValue();
			}

		}
		String s = String.valueOf(cycle * 3600);
		this.doubleCycle = Integer.parseInt(s.substring(0, s.indexOf('.')));
	}

	public void anaylize() {
		if (logger.isInfoEnabled()) {
			logger.info("大额不正常流水分析线程开始分析任务"); //$NON-NLS-1$
		}
		Transaction tx = null;
		try {
			Session session = HibernateSessionFactory.currentSession();
			tx = session.beginTransaction();

			if (logger.isInfoEnabled()) {
				logger
						.info("大额不正常流水分析线程开始分析时间:" + DateUtil.getNow("yyyy/MM/dd/HH:mm:ss")); //$NON-NLS-1$
			}
			if (1 > DateUtil.checkTimeSequence(endTime, DateUtil.getNow())) {
				if (logger.isInfoEnabled()) {
					logger.info("大额不正常流水分析线程分析时间段：" + startTime + " -- "
							+ endTime);
				}
			} else {
				endTime = DateUtil.getNow();
				if (logger.isInfoEnabled()) {
					logger.info("大额不正常流水分析线程分析时间段：" + startTime + " -- "
							+ endTime);
				}
			}
			getParameter(session);
			// analysis time record
			recordTime = DateUtil.getNow();
			StringBuffer queryStr = new StringBuffer();
			queryStr
					.append(
							"select new com.kingstargroup.form.RcvdtlCardResult(a.id.cardNo,a.id.txDate,sum(a.amount))")
					.append("from TTifRcvdtl as a where a.id.txCode=930031 ")
					.append(
							"and a.colTimestamp>=:startTime and a.colTimestamp<:endTime ")
					.append("group by a.id.cardNo,a.id.txDate ").append(
							"having sum(a.amount)>=" + limit * 100 + " ");
			Query query = session.createQuery(queryStr.toString());

			// Query query = session
			// .createSQLQuery(
			// "select rcvdtl.card_no as {cardRt.cardNo}, rcvdtl.tx_date as
			// {cardRt.txDate}, "
			// + "sum(rcvdtl.amount) as {cardRt.amount} from
			// ykt_cur.t_tif_rcvdtl as rcvdtl "
			// + "where rcvdtl.tx_code=930031 "
			// + "and rcvdtl.col_timestamp>=:startTime "
			// + "and rcvdtl.col_timestamp<:endTime "
			// + " group by rcvdtl.card_no,rcvdtl.tx_date "
			// + "having sum(rcvdtl.amount)>=" + limit
			// * 100 + " with ur").addEntity("cardRt",
			// RcvdtlCardResult.class);

			query.setString("startTime", startTime);
			query.setString("endTime", endTime);
			List list = query.list();
			Iterator iter = list.iterator();
			while (iter.hasNext()) {
				RcvdtlCardResult cardResult = (RcvdtlCardResult) iter.next();
				Query queryOne = session
						.createSQLQuery(
								"select {rcvdtl.*} from ykt_cur.t_tif_rcvdtl as rcvdtl "
										+ "where rcvdtl.tx_code=930031 and rcvdtl.tx_mark=153 "// 只是消费流水
										+ "and rcvdtl.card_no=:cardNo and rcvdtl.tx_date=:txDate with ur")
						.addEntity("rcvdtl", TTifRcvdtl.class);
				queryOne
						.setInteger("cardNo", cardResult.getCardNo().intValue());
				queryOne.setString("txDate", cardResult.getTxDate());
				Query queryCustomer = session
						.createSQLQuery(
								"select a.cut_name as cutName "
										+ "from YKT_CUR.T_CIF_CUSTOMER a,YKT_CUR.T_PIF_CARD b "
										+ "where a.cut_id=b.COSUMER_ID and b.CARD_ID=:cutId with ur")
						.addScalar("cutName", Hibernate.STRING);
				queryCustomer.setInteger("cutId", cardResult.getCardNo()
						.intValue());
				List listCust = queryCustomer.list();
				String cust_name = "";
				if (listCust.size() > 0) {
					cust_name = listCust.get(0).toString().trim();
				}
				List listOne = queryOne.list();
				Iterator iterOne = listOne.iterator();
				while (iterOne.hasNext()) {
					TTifRcvdtl rcvdtl = (TTifRcvdtl) iterOne.next();
					if (true == recordOrNot) {
						MapSerialexceptTable seriExcept = new MapSerialexceptTable();
						MapSerialexceptTableKey seriExptKey = new MapSerialexceptTableKey();
						seriExptKey.setAnalysisTime(recordTime);
						seriExptKey.setTxDate(rcvdtl.getId().getTxDate());
						seriExptKey.setTxTime(rcvdtl.getId().getTxTime());
						seriExptKey.setCardNo(rcvdtl.getId().getCardNo());
						seriExptKey.setDeviceId(rcvdtl.getId().getDeviceId());
						seriExptKey.setSerialNo(rcvdtl.getId().getSerialNo());
						seriExptKey.setTxCode(rcvdtl.getId().getTxCode());
						seriExcept.setAmount(rcvdtl.getAmount());
						seriExcept.setColTimestamp(rcvdtl.getColTimestamp());
						seriExcept.setComuVer(rcvdtl.getComuVer());
						seriExcept.setDealDate(rcvdtl.getDealDate());
						seriExcept.setDealTime(rcvdtl.getDealTime());
						seriExcept.setId(seriExptKey);
						seriExcept.setInBala(rcvdtl.getInBala());
						seriExcept.setOutBala(rcvdtl.getOutBala());
						seriExcept.setPurseNo(rcvdtl.getPurseNo());
						seriExcept.setRunReason(rcvdtl.getRunReason());
						seriExcept.setStatus(rcvdtl.getStatus());
						seriExcept.setSysId(rcvdtl.getSysId());
						seriExcept.setTotalCnt(rcvdtl.getTotalCnt());
						seriExcept.setTxMark(rcvdtl.getTxMark());
						seriExcept.setContactname(contactName);
						seriExcept.setAbnormaltype(Short.valueOf("3"));
						session.save(seriExcept);
					}
					mailRecord++;
					if (!"".equals(mailList)) {
						String device_name = "";
						device_name = DeviceNameDictionary.getInstance().get(
								rcvdtl.getId().getDeviceId()).trim();

						buffer.append(StringUtil.largeExceptStringGenerate(
								rcvdtl.getId().getDeviceId(), device_name,
								rcvdtl.getId().getCardNo(), cust_name, rcvdtl
										.getId().getSerialNo().toString(),
								rcvdtl.getAmount().floatValue() / 100, rcvdtl
										.getId().getTxDate(), rcvdtl.getId()
										.getTxTime(),
								"LARGE_EXCEPTION.DAYTIME_ERR"));
					}
				}
			}

			// 单笔超额

			recordTime = DateUtil.getNewTime(DateUtil.getNow(), 10);
			BgMonitor
					.monitorThreadStatusReport(
							"com.kingstargroup.action.bgAnalysis.LargeExceptAnalysisThread",
							"大额不正常流水分析线程", DateUtil
									.getNow("yyyy/MM/dd/HH:mm:ss"), String
									.valueOf(this.doubleCycle), "运行中...");
			Query querySingle = session.createSQLQuery(
					"select {rcvdtl.*} from ykt_cur.t_tif_rcvdtl as rcvdtl "
							+ "where rcvdtl.tx_code=930031 "
							+ "and rcvdtl.col_timestamp>=:startTime "
							+ "and rcvdtl.col_timestamp<:endTime "
							+ "and rcvdtl.amount>" + singleLimit * 100
							+ " with ur ")
					.addEntity("rcvdtl", TTifRcvdtl.class);

			querySingle.setString("startTime", startTime);
			querySingle.setString("endTime", endTime);

			List listSingle = querySingle.list();
			Iterator iterSingle = listSingle.iterator();
			while (iterSingle.hasNext()) {
				TTifRcvdtl rcvdtl = (TTifRcvdtl) iterSingle.next();
				if (true == recordOrNot) {
					MapSerialexceptTable seriExcept = new MapSerialexceptTable();
					MapSerialexceptTableKey seriExptKey = new MapSerialexceptTableKey();
					seriExptKey.setAnalysisTime(recordTime);
					seriExptKey.setTxDate(rcvdtl.getId().getTxDate());
					seriExptKey.setTxTime(rcvdtl.getId().getTxTime());
					seriExptKey.setCardNo(rcvdtl.getId().getCardNo());
					seriExptKey.setDeviceId(rcvdtl.getId().getDeviceId());
					seriExptKey.setSerialNo(rcvdtl.getId().getSerialNo());
					seriExptKey.setTxCode(rcvdtl.getId().getTxCode());
					seriExcept.setAmount(rcvdtl.getAmount());
					seriExcept.setColTimestamp(rcvdtl.getColTimestamp());
					seriExcept.setComuVer(rcvdtl.getComuVer());
					seriExcept.setDealDate(rcvdtl.getDealDate());
					seriExcept.setDealTime(rcvdtl.getDealTime());
					seriExcept.setId(seriExptKey);
					seriExcept.setInBala(rcvdtl.getInBala());
					seriExcept.setOutBala(rcvdtl.getOutBala());
					seriExcept.setPurseNo(rcvdtl.getPurseNo());
					seriExcept.setRunReason(rcvdtl.getRunReason());
					seriExcept.setStatus(rcvdtl.getStatus());
					seriExcept.setSysId(rcvdtl.getSysId());
					seriExcept.setTotalCnt(rcvdtl.getTotalCnt());
					seriExcept.setTxMark(rcvdtl.getTxMark());
					seriExcept.setContactname(contactName);
					seriExcept.setAbnormaltype(Short.valueOf("15"));
					session.save(seriExcept);
				}
				mailRecord++;
				if (!"".equals(mailList)) {
					String device_name = "";
					device_name = DeviceNameDictionary.getInstance().get(
							rcvdtl.getId().getDeviceId()).trim();
					Query queryCustomer = session
							.createSQLQuery(
									"select a.cut_name as cutName "
											+ "from YKT_CUR.T_CIF_CUSTOMER a,YKT_CUR.T_PIF_CARD b "
											+ "where a.cut_id=b.COSUMER_ID and b.CARD_ID=:cutId with ur")
							.addScalar("cutName", Hibernate.STRING);
					queryCustomer.setInteger("cutId", rcvdtl.getId()
							.getCardNo().intValue());
					List listCust = queryCustomer.list();
					String cust_name = "";
					if (listCust.size() > 0) {
						cust_name = listCust.get(0).toString().trim();
					}
					buffer.append(StringUtil.largeExceptStringGenerate(rcvdtl
							.getId().getDeviceId(), device_name, rcvdtl.getId()
							.getCardNo(), cust_name, rcvdtl.getId()
							.getSerialNo().toString(), rcvdtl.getAmount()
							.floatValue() / 100, rcvdtl.getId().getTxDate(),
							rcvdtl.getId().getTxTime(),
							"LARGE_EXCEPTION.ONETIME_ERR"));
				}

			}

			// record timepoint analysis
			Object tempAnalysis = session.get(MapAnalysisPoint.class,
					"LARGE_EXCEPTION");
			MapAnalysisPoint analysisPoint = null;
			if (tempAnalysis == null) {
				analysisPoint = new MapAnalysisPoint();
				analysisPoint.setAnalysisname("LARGE_EXCEPTION");
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
			logger.error("大额不正常流水分析线程出现以下异常：", e); //$NON-NLS-1$

			if (tx != null) {
				tx.rollback();
			}
		} catch (Exception e) {
			logger.error("大额不正常流水分析线程出现以下异常：", e); //$NON-NLS-1$
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
						.info("大额不正常流水分析线程结束进入休眠状态!"
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
			logger.error("大额不正常流水分析线程出现以下异常：可能被强行停止！ ", e); //$NON-NLS-1$
		} catch (Exception e) {
			logger.error("大额不正常流水分析线程出现以下异常：可能被强行停止！ ", e); //$NON-NLS-1$
		}
	}

	public void terminate() {
		if (this.isAlive()) {
			logger.warn("大额不正常流水分析线程状态被请求，此时线程状态：活动线程!"); //$NON-NLS-1$
			this.requestStop = true;
		} else {
			logger.warn("大额不正常流水分析线程状态被请求，此时线程状态：死亡线程!"); //$NON-NLS-1$
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
				logger.info("大额不正常流水分析线程发送邮件给联系人:" + contactName);
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
							contactName, tempList[i], StringUtil
									.largeExceptMailGenerate(nameList[i],
											DateUtil.reFormatTime(recordTime),
											mailRecord, tmpStr,
											"LARGE_EXCEPTION"));
				}
			}
		}
	}

	public void sendSMG() {
		if ((true == smgOrNot) && (!"".equals(phoneNumber)) && mailRecord > 0) {
			if (logger.isInfoEnabled()) {
				logger.info("大额不正常流水分析线程发送短信给联系人:" + contactName);
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
							"LARGE_EXCEPTION");
					CommonSendSMGUtil.sendSMG(tempList[i], SmgMessage);
				}
			}
		}
	}

}
