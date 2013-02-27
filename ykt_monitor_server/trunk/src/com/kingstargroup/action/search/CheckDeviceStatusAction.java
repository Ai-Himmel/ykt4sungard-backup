package com.kingstargroup.action.search;

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

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name:CheckDeviceStatusAction.java
 * Description :设备状态分析结果 
 * Modify History（或Change Log）: 
 * 操作类型（创建、修改等） 操作日期     操作者    操作内容简述
 * 创建               2009-9-18  何林青    
 * <p>
 * 
 * @author 何林青
 * @version 1.0
 * @since 1.0
 */
public class CheckDeviceStatusAction extends BaseAction {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(CheckDeviceStatusAction.class);

	/**
	 * Method name: deviceList<br>
	 * Description: 设备信息列表<br>
	 * Return: ActionForward<br>
	 * Args:
	 * 
	 * @param mapping
	 *            Args:
	 * @param form
	 *            Args:
	 * @param request
	 *            Args:
	 * @param response
	 *            Args:
	 * @return Args:
	 * @throws Exception
	 *             Modify History: <br>
	 *             操作类型 操作人 操作时间 操作内容<br>
	 *             ======================================<br>
	 *             创建 何林青 Aug 15, 2007 <br>
	 * @author 何林青
	 * @version
	 * @since 1.0
	 */
	public ActionForward deviceList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		HttpSession httpSession = request.getSession();
		// 判断信息
		if (httpSession.getAttribute("userLogin") != null) {

			try {
				// MessageResources msgResources = (MessageResources) this
				// .getServlet().getServletContext().getAttribute(
				// Globals.MESSAGES_KEY);
				request.setCharacterEncoding("GBK");

				StringBuffer sqlBuff = new StringBuffer();

				sqlBuff
						.append(
								"from Devicestatus device where (devstatus=1 or devstatus=2 or devstatus=3) order by errlasttime desc,deviceid desc ");
				Session session = HibernateSessionFactory.currentSession();
				String xmlOut = "";
				Query query = session.createQuery(sqlBuff.toString());
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
