package com.kingstargroup.action.search;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name:CheckUnbalanceAction.java
 * Description: xml返会不平的流水记录
 * Modify History（或Change Log）: 
 * 操作类型（创建、修改等） 操作日期     操作者    操作内容简述
 * 创建                2005-09-28   何林青    返回卡库不平的流水记录
 * <p>
 * 
 * @author 何林青
 * @version 1.0
 * @since 1.0
 */

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.log4j.Logger;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;
import com.kingstargroup.action.user.ErrorCode;
import com.kingstargroup.commons.BaseAction;
import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.utils.DateUtil;
import com.kingstargroup.utils.XMLGenerateUtil;

public class CheckUnbalanceAction extends BaseAction {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(CheckUnbalanceAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		HttpSession httpSession = request.getSession();
		// 判断信息
		if (httpSession.getAttribute("userLogin") != null) {
			request.setCharacterEncoding("GBK");
			
			String accountNO = request.getParameter("AccountNO");
			String studentNO = request.getParameter("StudentNO");
			String costomerName = request.getParameter("CostomerName");
			String startTime = request.getParameter("StartTime");
			String endTime = request.getParameter("EndTime");
			String lastFlag = request.getParameter("lastanalysis");
			String startCount = request.getParameter("StartCount");

			StringBuffer sqlBuff = new StringBuffer();
			sqlBuff.append("from MapCaunbalanceTable unbalance where 1=1 ");
			if (!"".equals(accountNO) && null != accountNO) {
				sqlBuff.append(" and unbalance.id.accountId = :accountNO ");
			}
			if (!"".equals(studentNO) && null != studentNO) {
				sqlBuff.append(" and unbalance.stuempNo = :studentNO ");
			}
			if (!"".equals(costomerName) && null != costomerName) {
				sqlBuff.append(" and unbalance.cutName like :cutName ");
			}
			
			if (!"".equals(lastFlag) && null != lastFlag) {
				if ("1".equals(lastFlag)) {
					// ToDo:checked----to get the last version of result
					sqlBuff.append(" and unbalance.id.analysisTime >= :startTime ");
					sqlBuff.append(" and unbalance.id.analysisTime <= :endTime ");
				} else {
					// ToDo:unchecked
					if (!"".equals(startTime) && null != startTime) {
						sqlBuff.append(" and unbalance.id.analysisTime >= :startTime ");
					}
					if (!"".equals(endTime) && null != endTime) {
						sqlBuff.append(" and unbalance.id.analysisTime <= :endTime ");
					}
				}
			}
						
			try {
				// MessageResources msgResources = (MessageResources) this
				// .getServlet().getServletContext().getAttribute(
				// Globals.MESSAGES_KEY);
				Session session = HibernateSessionFactory.currentSession();
				
				Query queryTime = session.createQuery("select a.value from MapParamTable a,MapSysDictionary b where a.parameter=b.dictCode and b.id.dictNo=:dictNo and b.id.dictValue=:dictValue");
				queryTime.setInteger("dictNo",2);
				queryTime.setString("dictValue","13");				
				List listTime = queryTime.list();
				String dateTime = DateUtil.getNow();
				int intevalTime = 0;
				if(listTime.size()>0){
					intevalTime = (int)(Float.parseFloat(listTime.get(0).toString())*60*60*-1);
				}else{
					intevalTime = -12*60*60;
				}	
				
				String xmlOut = "";
				Query query = session.createQuery(sqlBuff.toString());

				if (!"".equals(accountNO) && null != accountNO) {
					query.setString("accountNO", accountNO);
				}
				if (!"".equals(studentNO) && null != studentNO) {
					query.setString("studentNO", studentNO);
				}

				if (!"".equals(costomerName)) {
					costomerName = "%" + costomerName + "%";
					query.setString("cutName", costomerName);
				}

				if (!"".equals(lastFlag) && null != lastFlag) {
					if ("1".equals(lastFlag)) {
						// ToDo:checked----to get the last version of result
						query.setString("startTime", DateUtil.getNewTime(dateTime,intevalTime));
						query.setString("endTime", dateTime);
					} else {
						// ToDo:unchecked
						if (!"".equals(startTime) && null != startTime) {
							query.setString("startTime", startTime);
						}
						if (!"".equals(endTime) && null != endTime) {
							query.setString("endTime", dateTime);
						}
					}
				}
				
				if ("".equals(startCount) || null == startCount) {
					query.setFirstResult(0);
					query.setMaxResults(200);
				} else {
					query.setFirstResult(Integer.parseInt(startCount));
					query.setMaxResults(200);
				}

				List list = null;
				list = query.list();
				// user exist
				if (200 == list.size()) {
					xmlOut = XMLGenerateUtil.XMLGenerateWithFlag(
							ErrorCode.SUCCESS, String.valueOf(list.size()),
							list, "1");
				} else {
					xmlOut = XMLGenerateUtil.XMLGenerateWithFlag(
							ErrorCode.SUCCESS, String.valueOf(list.size()),
							list, "0");
				}

				XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

			} catch (HibernateException e) {
				logger
						.error(
								"execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

				e.printStackTrace();
			} finally {
				HibernateSessionFactory.closeSession();
			}

			if (logger.isDebugEnabled()) {
				logger
						.debug("execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
			}
		}
		return null;
	}
}
