package com.kingstargroup.action.search;
/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name:CheckContactAction.java
 * Description: 报警联系人查询
 * Modify History（或Change Log）: 
 * 操作类型（创建、修改等） 操作日期     操作者    操作内容简述
 * 创建                2005-10-10   何林青   查询报警联系人
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
import com.kingstargroup.utils.XMLGenerateUtil;

public class CheckContactAction extends BaseAction {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(CheckContactAction.class);

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

			String contactName = request.getParameter("ContactName");
			String exceptionType = request.getParameter("ExceptionType");
			String startTime = request.getParameter("StartTime");
			String endTime = request.getParameter("EndTime");


			StringBuffer sqlBuff = new StringBuffer();
			sqlBuff.append("from MapContactTable as contact, MapContactMonitorTable ")
			.append("as monitor where contact.contactname = monitor.contactname ");
			if (!"".equals(contactName)&&null!=contactName) {
				sqlBuff.append("and contact.contactname like :contactName ");
			}		
			if (!"".equals(exceptionType)&&null!=exceptionType&&!"-".equals(exceptionType)) {
				sqlBuff.append("and monitor.monitoritem = :exceptionType ");
			}

			if (!"".equals(startTime)&&null!=startTime) {
				sqlBuff.append("and contact.starttime <= :startTime ");
			}
			if (!"".equals(endTime)&&null!=endTime) {
				sqlBuff.append("and contact.endtime >= :endTime ");
			}


			try {
//				MessageResources msgResources = (MessageResources) this
//						.getServlet().getServletContext().getAttribute(
//								Globals.MESSAGES_KEY);
				Session session = HibernateSessionFactory.currentSession();
				String xmlOut = "";
				Query query = session.createQuery(sqlBuff.toString());
				if (!"".equals(contactName)&&null!=contactName) {
					contactName = "%"+contactName+"%";
					query.setString("contactName",contactName);
				}		
				if (!"".equals(exceptionType)&&null!=exceptionType&&!"-".equals(exceptionType)) {
					query.setString("exceptionType",exceptionType);
				}

				if (!"".equals(startTime)&&null!=startTime) {
					query.setString("startTime",contactName);
				}
				if (!"".equals(endTime)&&null!=endTime) {
					query.setString("endTime",endTime);

				}
				
				List list = query.list();
				// user exist
				xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
						.valueOf(list.size()), list);

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
