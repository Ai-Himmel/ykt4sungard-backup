package com.kingstargroup.action.systemreffer;
/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name:AddContactAction.java
 * Description: 添加报警联系人
 * Modify History（或Change Log）: 
 * 操作类型（创建、修改等） 操作日期     操作者    操作内容简述
 * 创建                2005-10-10   何林青   管理员添加报警联系人
 * <p>
 * 
 * @author 何林青
 * @version 1.0
 * @since 1.0
 */

import org.apache.log4j.Logger;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name:AddContactAction.java
 * Description: 管理员添加报警联系人
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期     操作者    操作内容简述
 * 创建  				2005-10-10    何林青    添加联系人方法
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.Globals;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.util.MessageResources;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;
import org.hibernate.Transaction;

import com.kingstargroup.action.user.ErrorCode;
import com.kingstargroup.commons.BaseAction;
import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.form.MapContactTable;
import com.kingstargroup.utils.XMLGenerateUtil;

public class AddContactAction extends BaseAction {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(AddContactAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		HttpSession httpSession = request.getSession();
		if (httpSession.getAttribute("userLogin") != null) {
			Transaction tx = null;
			request.setCharacterEncoding("GBK");

			String contactName = request.getParameter("ContactName");
			String contactGender = request.getParameter("ContactGender");
			String contactCompany = request.getParameter("ContactCompany");
			String weekdays = request.getParameter("Weekdays");
			String startTime = request.getParameter("StartTime");
			String endTime = request.getParameter("EndTime");
			String email = request.getParameter("Email");
			String cellphone = request.getParameter("Cellphone");

			try {
				MessageResources msgResources = (MessageResources) this
						.getServlet().getServletContext().getAttribute(
								Globals.MESSAGES_KEY);
				Session session = HibernateSessionFactory.currentSession();
				String xmlOut = "";
				Query query = session
						.createQuery("from MapContactTable  contact where contact.contactname=?");
				query.setString(0, contactName);
				if (query.iterate().hasNext()) {
					// user exist
					xmlOut = XMLGenerateUtil
							.XMLGenerate(
									ErrorCode.CONTACT_EXIST,
									msgResources
											.getMessage("com.kingstargroup.acton.systemreffer.CONTACT_EXIST"),
									null);
				} else {
					// add user
					tx = session.beginTransaction();
					MapContactTable mapContactTable = new MapContactTable();
					mapContactTable.setContactname(contactName);
					mapContactTable.setContactgender(contactGender);
					mapContactTable.setContactcompany(contactCompany);
					mapContactTable.setWeekdays(weekdays);
					mapContactTable.setStarttime(startTime);
					mapContactTable.setEndtime(endTime);
					mapContactTable.setEmail(email);
					mapContactTable.setCellphone(cellphone);
					session.save(mapContactTable);
					tx.commit();
					xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS,
							msgResources
									.getMessage("com.kingstargroup.acton.systemreffer.CONTACT_ADD_SUCCESS"),
							null);
				}
				XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

			} catch (HibernateException e) {
				logger
						.error(
								"execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

				if (tx != null) {
					tx.rollback();
				}

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
