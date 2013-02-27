package com.kingstargroup.action.bgAnalysis;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: ExceptSerilAnalysisThread.java
 * Description: 异常流水检查线程类
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				 2005-10-19    何林青             异常流水检查线程类
 * 修改					2006-07-20     何林青    			 修改日志记录方式
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

import com.kingstargroup.commons.AnalyzeThreadInterface;
import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.form.DupliSerialResult;
import com.kingstargroup.form.MapAlertTable;
import com.kingstargroup.form.MapAnalysisPoint;
import com.kingstargroup.form.MapContactMonitorTable;
import com.kingstargroup.form.MapContactTable;
import com.kingstargroup.form.MapParamTable;
import com.kingstargroup.form.MapSerialexceptTable;
import com.kingstargroup.form.MapSerialexceptTableKey;
import com.kingstargroup.form.TTifRcvdtl;
import com.kingstargroup.utils.CommonSendMailUtil;
import com.kingstargroup.utils.CommonSendSMGUtil;
import com.kingstargroup.utils.DB2TimeUtil;
import com.kingstargroup.utils.DateUtil;
import com.kingstargroup.utils.GetApplicationResources;
import com.kingstargroup.utils.OracleTimeUtil;
import com.kingstargroup.utils.StringUtil;

public class ExceptSerilAnalysisThread extends Thread implements
		AnalyzeThreadInterface {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(ExceptSerilAnalysisThread.class);

	// flag of stop this thread
	private boolean requestStop = false;

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
			logger.info("**************异常流水分析线程初始化**************"); //$NON-NLS-1$
		}
		try {
			Session session = HibernateSessionFactory.currentSession();
			Query queryTime = session
					.createQuery("from MapAnalysisPoint point where point.analysisname=:analysisName");
			queryTime.setString("analysisName", "SERI_EXCEPTION");
			Iterator iterTime = queryTime.iterate();
			if (iterTime.hasNext()) {
				MapAnalysisPoint mapAnalysisPoint = (MapAnalysisPoint) iterTime
						.next();
				this.startTime = mapAnalysisPoint.getAnalysispoint();
			}
			Query queryCycle = session
					.createQuery("from MapParamTable param where param.parameter=:paramRefer");
			queryCycle.setString("paramRefer", "MutationCycle");
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
			logger.error("异常流水分析线程初始化失败！", e); //$NON-NLS-1$
		} finally {
			HibernateSessionFactory.closeSession();
		}
		if (logger.isInfoEnabled()) {
			logger.info("**************异常流水分析线程初始化成功**************"); //$NON-NLS-1$
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
				.createQuery("from MapAlertTable alert where alert.parameter='ChangedRecord'");
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
				.createQuery("from MapContactMonitorTable monitor where monitor.monitorno='SERI_EXCEPTION'");
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
				.createQuery("from MapParamTable param where param.parameter=:paramRefer");
		queryCycle.setString("paramRefer", "MutationCycle");
		Iterator iterParam = queryCycle.iterate();
		if (iterParam.hasNext()) {
			MapParamTable mapParamTable = (MapParamTable) iterParam.next();
			this.cycle = mapParamTable.getValue().doubleValue();
		}
		String s = String.valueOf(cycle * 3600);
		this.doubleCycle = Integer.parseInt(s.substring(0, s.indexOf('.')));
	}

	public void anaylize() {
		if (logger.isInfoEnabled()) {
			logger.info("异常流水分析线程开始分析任务"); //$NON-NLS-1$
		}
		Transaction tx = null;
		try {
			Session session = HibernateSessionFactory.currentSession();
			tx = session.beginTransaction();
			if (logger.isInfoEnabled()) {
				logger
						.info("异常流水分析线程开始分析时间:" + DateUtil.getNow("yyyy/MM/dd/HH:mm:ss")); //$NON-NLS-1$
			}
			if (1 > DateUtil.checkTimeSequence(endTime, DateUtil.getNow())) {
				if (logger.isInfoEnabled()) {
					logger
							.info("异常流水分析线程分析时间段：" + startTime + " -- "
									+ endTime);
				}
			} else {
				endTime = DateUtil.getNow();
				if (logger.isInfoEnabled()) {
					logger
							.info("异常流水分析线程分析时间段：" + startTime + " -- "
									+ endTime);
				}
			}
			getParameter(session);
			recordTime = DateUtil.getNow();
			Query query = session
					.createSQLQuery(
							"select {rcvdtl.*} from ykt_cur.t_tif_rcvdtl rcvdtl "
									+ "where (concat(rcvdtl.tx_date,rcvdtl.tx_time)>:curDate "
									+ "or rcvdtl.tx_date<='20050101' "
									+ "or substr(rcvdtl.tx_date,5,2)>='13' "
									+ "or substr(rcvdtl.tx_date,7,2)>'31') "
									+ "and rcvdtl.col_timestamp>=:startTime "
									+ "and rcvdtl.col_timestamp<:endTime ")
					.addEntity("rcvdtl", TTifRcvdtl.class);

			query.setString("curDate", OracleTimeUtil.getSysDate(0));
			query.setString("startTime", startTime);
			query.setString("endTime", endTime);
			List list = query.list();
			Iterator iter = list.iterator();
			while (iter.hasNext()) {
				TTifRcvdtl rcvdtl = (TTifRcvdtl) iter.next();
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
					seriExcept.setAbnormaltype(Short.valueOf("201"));
					session.save(seriExcept);
				}
				mailRecord++;
				if (!"".equals(mailList)) {
					String device_name = "";
					device_name = DeviceNameDictionary.getInstance().get(
							rcvdtl.getId().getDeviceId()).trim();
					Query queryCustomer = session
							.createSQLQuery(
									"select a.cut_name cutName "
											+ "from YKT_CUR.T_CIF_CUSTOMER a,YKT_CUR.T_PIF_CARD b "
											+ "where a.cut_id=b.COSUMER_ID and b.CARD_ID=:cutId ")
							.addScalar("cutName", Hibernate.STRING);
					queryCustomer.setInteger("cutId", rcvdtl.getId()
							.getCardNo().intValue());
					List listCust = queryCustomer.list();
					String cust_name = "";
					if (listCust.size() > 0) {
						cust_name = listCust.get(0).toString().trim();
					}
					buffer.append(StringUtil.solidStringGenerate(rcvdtl.getId()
							.getDeviceId(), device_name, rcvdtl.getId()
							.getCardNo(), cust_name, rcvdtl.getId()
							.getSerialNo().toString(), rcvdtl.getId()
							.getTxDate(), rcvdtl.getId().getTxTime(),
							"SERI_EXCEPTION.TIME_ERR"));
				}
			}
			session.flush();
			session.clear();
			// 流水出入卡金额突变
			recordTime = DateUtil.getNow();
			Query queryFour = session
					.createSQLQuery(
							"select {a.*} from YKT_CUR.T_TIF_RCVDTL a,"
									+ "YKT_CUR.T_TIF_RCVDTL b "
									+ "where a.total_cnt=b.total_cnt-1 and a.card_no=b.card_no "
									+ "and a.col_timestamp>:startTime and a.col_timestamp<=:endTime "
									+ "and b.col_timestamp>:startTime and b.col_timestamp<=:endTime "
									+ "and (a.tx_code=930031 or a.tx_code=930034) "// 交易、冲正、充值流水
									+ "and (b.tx_code=930031 or b.tx_code=930034) "
									+ "and a.out_bala<>b.in_bala "
									+ "order by a.card_no,a.total_cnt ")
					.addEntity("a", TTifRcvdtl.class);
			queryFour.setString("startTime", startTime);
			queryFour.setString("endTime", endTime);
			List listFour = queryFour.list();
			Iterator iterFour = listFour.iterator();
			while (iterFour.hasNext()) {
				TTifRcvdtl rcvdtl = (TTifRcvdtl) iterFour.next();
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
					seriExcept.setAbnormaltype(Short.valueOf("203"));
					session.save(seriExcept);
				}
				mailRecord++;
				if (!"".equals(mailList)) {
					String device_name = "";
					device_name = DeviceNameDictionary.getInstance().get(
							rcvdtl.getId().getDeviceId()).trim();
					Query queryCustomer = session
							.createSQLQuery(
									"select a.cut_name cutName "
											+ "from YKT_CUR.T_CIF_CUSTOMER a,YKT_CUR.T_PIF_CARD b "
											+ "where a.cut_id=b.COSUMER_ID and b.CARD_ID=:cutId ")
							.addScalar("cutName", Hibernate.STRING);
					queryCustomer.setInteger("cutId", rcvdtl.getId()
							.getCardNo().intValue());
					List listCust = queryCustomer.list();
					String cust_name = "";
					if (listCust.size() > 0) {
						cust_name = listCust.get(0).toString().trim();
					}
					buffer.append(StringUtil.solidStringGenerate(rcvdtl.getId()
							.getDeviceId(), device_name, rcvdtl.getId()
							.getCardNo(), cust_name, rcvdtl.getId()
							.getSerialNo().toString(), rcvdtl.getId()
							.getTxDate(), rcvdtl.getId().getTxTime(),
							"SERI_EXCEPTION.MONEY_ERR"));
				}
			}
			session.flush();
			session.clear();
			// 设备号不存在
			recordTime = DateUtil.getNow();
			Query queryOne = session.createSQLQuery(
					"select {rcvdtl.*} from ykt_cur.t_tif_rcvdtl rcvdtl "
							+ "where rcvdtl.col_timestamp>:startTime "
							+ "and rcvdtl.col_timestamp<=:endTime "
							+ "and rcvdtl.err_code=100172 ").addEntity(
					"rcvdtl", TTifRcvdtl.class);
			queryOne.setString("startTime", startTime);
			queryOne.setString("endTime", endTime);
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
					seriExcept.setAbnormaltype(Short.valueOf("204"));
					session.save(seriExcept);
				}
				mailRecord++;
				if (!"".equals(mailList)) {
					String device_name = "";
					device_name = DeviceNameDictionary.getInstance().get(
							rcvdtl.getId().getDeviceId()).trim();
					Query queryCustomer = session
							.createSQLQuery(
									"select a.cut_name cutName "
											+ "from YKT_CUR.T_CIF_CUSTOMER a,YKT_CUR.T_PIF_CARD b "
											+ "where a.cut_id=b.COSUMER_ID and b.CARD_ID=:cutId ")
							.addScalar("cutName", Hibernate.STRING);
					queryCustomer.setInteger("cutId", rcvdtl.getId()
							.getCardNo().intValue());
					List listCust = queryCustomer.list();
					String cust_name = "";
					if (listCust.size() > 0) {
						cust_name = listCust.get(0).toString().trim();
					}
					buffer.append(StringUtil.solidStringGenerate(rcvdtl.getId()
							.getDeviceId(), device_name, rcvdtl.getId()
							.getCardNo(), cust_name, rcvdtl.getId()
							.getSerialNo().toString(), rcvdtl.getId()
							.getTxDate(), rcvdtl.getId().getTxTime(),
							"SERI_EXCEPTION.DEV_ERR"));
				}
			}
			session.flush();
			session.clear();
			// 重复流水
			recordTime = DateUtil.getNow();
			BgMonitor
					.monitorThreadStatusReport(
							"com.kingstargroup.action.bgAnalysis.ExceptSerilAnalysisThread",
							"异常流水分析线程", DateUtil.getNow("yyyy/MM/dd/HH:mm:ss"),
							String.valueOf(this.doubleCycle), "运行中...");
			StringBuffer queryStr2 = new StringBuffer();
			queryStr2
					.append(
							"select new com.kingstargroup.form.DupliSerialResult(a.id.serialNo,a.id.deviceId,a.id.cardNo) ")
					.append(
							"from TTifRcvdtl a where a.colTimestamp>=:startTime ")
					.append("and a.colTimestamp<:endTime ")
					.append("group by a.id.deviceId,a.id.cardNo,a.id.serialNo ")
					.append("having count(a.id.serialNo)>1  ");
			Query queryTwo = session.createQuery(queryStr2.toString());
			queryTwo.setString("startTime", startTime);
			queryTwo.setString("endTime", endTime);
			List listTwo = queryTwo.list();
			Iterator iterTwo = listTwo.iterator();
			while (iterTwo.hasNext()) {
				DupliSerialResult serialResult = (DupliSerialResult) iterTwo
						.next();
				Query queryThree = session.createSQLQuery(
						"select {a.*} from ykt_cur.t_tif_rcvdtl a "
								+ "where a.device_id=:deviceId "
								+ "and a.serial_no=:serialNo "
								+ "and a.card_no=:cardNo "
								+ "and a.col_timestamp>=:startTime "
								+ "and a.col_timestamp<:endTime ")
						.addEntity("a", TTifRcvdtl.class);
				queryThree.setString("deviceId", serialResult.getDeviceId());
				queryThree.setInteger("serialNo", serialResult.getSerialNo()
						.intValue());
				queryThree.setInteger("cardNo", serialResult.getCardNo()
						.intValue());
				queryThree.setString("startTime", startTime);
				queryThree.setString("endTime", endTime);
				List listThree = queryThree.list();
				Iterator iterThree = listThree.iterator();
				while (iterThree.hasNext()) {
					TTifRcvdtl rcvdtl = (TTifRcvdtl) iterThree.next();
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
						seriExcept.setAbnormaltype(Short.valueOf("205"));
						session.save(seriExcept);
					}
					mailRecord++;
					if (!"".equals(mailList)) {
						String device_name = "";
						device_name = DeviceNameDictionary.getInstance().get(
								rcvdtl.getId().getDeviceId()).trim();
						Query queryCustomer = session
								.createSQLQuery(
										"select a.cut_name cutName "
												+ "from YKT_CUR.T_CIF_CUSTOMER a,YKT_CUR.T_PIF_CARD b "
												+ "where a.cut_id=b.COSUMER_ID and b.CARD_ID=:cutId ")
								.addScalar("cutName", Hibernate.STRING);
						queryCustomer.setInteger("cutId", rcvdtl.getId()
								.getCardNo().intValue());
						List listCust = queryCustomer.list();
						String cust_name = "";
						if (listCust.size() > 0) {
							cust_name = listCust.get(0).toString().trim();
						}
						buffer.append(StringUtil.solidStringGenerate(rcvdtl
								.getId().getDeviceId(), device_name, rcvdtl
								.getId().getCardNo(), cust_name, rcvdtl.getId()
								.getSerialNo().toString(), rcvdtl.getId()
								.getTxDate(), rcvdtl.getId().getTxTime(),
								"SERI_EXCEPTION.DUP_ERR"));
					}
				}
			}
			session.flush();
			session.clear();

			Object tempAnalysis = session.get(MapAnalysisPoint.class,
					"SERI_EXCEPTION");
			MapAnalysisPoint analysisPoint = null;
			if (tempAnalysis == null) {
				analysisPoint = new MapAnalysisPoint();
				analysisPoint.setAnalysisname("SERI_EXCEPTION");
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
			logger.error("异常流水分析线程出现以下异常：", e); //$NON-NLS-1$

			if (tx != null) {
				tx.rollback();
			}
		} catch (Exception e) {
			logger.error("异常流水分析线程出现以下异常：", e); //$NON-NLS-1$
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
						.info("异常流水分析线程结束进入休眠状态!"
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
			logger.error("异常流水分析线程出现以下异常：可能被强行停止！ ", e); //$NON-NLS-1$
		} catch (Exception e) {
			logger.error("异常流水分析线程出现以下异常：可能被强行停止！ ", e); //$NON-NLS-1$
		}
	}

	public void terminate() {
		if (this.isAlive()) {
			logger.warn("异常流水分析线程状态被请求，此时线程状态：活动线程!"); //$NON-NLS-1$
			this.requestStop = true;
		} else {
			logger.warn("异常流水分析线程状态被请求，此时线程状态：死亡线程!"); //$NON-NLS-1$
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
				logger.info("异常流水分析线程发送邮件给联系人:" + contactName);
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
									.wholeMailGenerate(nameList[i], DateUtil
											.reFormatTime(recordTime),
											mailRecord, tmpStr,
											"SERI_EXCEPTION"));
				}
			}
		}
	}

	public void sendSMG() {
		if ((true == smgOrNot) && (!"".equals(phoneNumber)) && mailRecord > 0) {
			if (logger.isInfoEnabled()) {
				logger.info("异常流水分析线程发送短信给联系人:" + contactName);
			}

			String[] tempList = null;
			String[] nameList = null;
			tempList = phoneNumber.split(";");
			nameList = phoneName.split(";");
			for (int i = 0; i < tempList.length; i++) {
				if (!"".equals(tempList[i])) {
					SmgMessage = StringUtil.wholeSMGGenerate(nameList[i],
							DateUtil.reFormatTime(recordTime), mailRecord,
							"SERI_EXCEPTION");
					CommonSendSMGUtil.sendSMG(tempList[i], SmgMessage);
				}
			}
		}
	}

}
