/**
 * 
 */
package com.kingstargroup.action.search;

import org.apache.log4j.Logger;

import java.util.List;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.utils.DateUtil;

/**
 * <br>
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. <br>
 * File name: GetAreaCodeTimelyAction.java<br>
 * Description: <br>
 * Modify History（或Change Log）: <br>
 * 操作类型（创建、修改等） 操作日期 操作者 操作内容简述<br>
 * 创建 2005-11-3 何林青 <br>
 * <p>
 * 
 * @author 何林青
 * @version 1.0
 * @since 1.0
 */
public class GetAreaCodeTimelyAction {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(GetAreaCodeTimelyAction.class);

	private int LIGONG = 11;

	private String time1 = "";


	private List listOne = null;



	private static GetAreaCodeTimelyAction instance = null;

	private static Object mutex = new Object();

	/**
	 * 
	 */
	private GetAreaCodeTimelyAction() {
		super();
		// TODO Auto-generated constructor stub
		time1 = DateUtil.getNow();
		listOne = AreaAnalysis(1);

//		time3 = DateUtil.getNow();
//		listThree = AreaAnalysis(3);
		// time4 = DateUtil.getNow();
		// listFour = AreaAnalysis(4);
	}

	static public GetAreaCodeTimelyAction getInstance() {
		synchronized (mutex) {
			if (null == instance) {
				//
				instance = new GetAreaCodeTimelyAction();
			}
		}
		return instance;
	}

	public List returnListAfterCheckTime(int i) {
		if (logger.isDebugEnabled()) {
			logger.debug("returnListAfterCheckTime(int) - start"); //$NON-NLS-1$
		}

		List list = null;
		switch (i) {
		case 1:
			if (DateUtil.checkIntervalTime(time1, DateUtil.getNow(), 24 * 3600) > 0) {// time
				// pass
				// 24hourss
				list = listOne;
			} else {
				list = AreaAnalysis(1);
			}
			break;

		}

		if (logger.isDebugEnabled()) {
			logger.debug("returnListAfterCheckTime(int) - end"); //$NON-NLS-1$
		}
		return list;
	}

	private List AreaAnalysis(int i) {
		if (logger.isDebugEnabled()) {
			logger.debug("AreaAnalysis(int) - start"); //$NON-NLS-1$
		}

		try {
			Session session = HibernateSessionFactory.currentSession();
			/*
			 * select area_no from ykt_cur.t_pif_area where area_no=2 or
			 * father_area_no=2 or father_area_no in(select area_no from
			 * ykt_cur.t_pif_area where father_area_no=2) or father_area_no
			 * in(select area_no from ykt_cur.t_pif_area where father_area_no in
			 * (select area_no from ykt_cur.t_pif_area where father_area_no=2))
			 */
			List returnList = null;
			switch (i) {
			case 1:
				Query queryOne = session
						.createQuery("select a.areaNo from TPifArea a where a.areaNo="
								+ LIGONG
								+ " or a.fatherAreaNo="
								+ LIGONG
								+ " or a.fatherAreaNo in(select b.areaNo from TPifArea b where b.fatherAreaNo="
								+ LIGONG
								+ ") or a.fatherAreaNo in(select c.areaNo from TPifArea c where c.fatherAreaNo in"
								+ "(select d.areaNo from TPifArea d where d.fatherAreaNo="
								+ LIGONG + "))");
				List listOne = queryOne.list();
				returnList = listOne;
				break;
			}

			if (logger.isDebugEnabled()) {
				logger.debug("AreaAnalysis(int) - end"); //$NON-NLS-1$
			}
			return returnList;

		} catch (HibernateException e) {
			logger.error("AreaAnalysis(int)", e); //$NON-NLS-1$

		} finally {
			HibernateSessionFactory.closeSession();
		}

		if (logger.isDebugEnabled()) {
			logger.debug("AreaAnalysis(int) - end"); //$NON-NLS-1$
		}
		return null;
	}

}
