/**
 * 
 */
package com.kingstargroup.ecard.portlet.document.action;


import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.FileNameException;
import com.kingstargroup.ecard.exceptions.FileSizeException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.util.InformationUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.GetterUtil;
import com.liferay.util.StringPool;
import com.liferay.util.servlet.SessionErrors;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: AddDocAction.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-9-21  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class AddDocAction extends PortletAction {
	/* (non-Javadoc)
	 * @see org.apache.struts.action.Action#execute(org.apache.struts.action.ActionMapping, org.apache.struts.action.ActionForm, javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)
	 */
	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {
		try {			
			String title = req.getParameter("title");
			String cmd = req.getParameter("cmd");
			String creater = GetterUtil.get((String)req.getSession().getAttribute(WebKeys.USER_ID), StringPool.BLANK);
			String[] uploadFieldNames = new String[]{"file_location"};
			//添加此条文档信息
			if (isTokenValid(req)) {
				
				InformationUtil.add(title, 
						"", 
						"", 
						String.valueOf(EcardConstants.INFORMATION_DOCUMENT_TYPE), 
						creater, 
						req, 
						uploadFieldNames, 
						EcardConstants.DOCUMENT_TYPE);
				resetToken(req);
			}			
			if (cmd.equals("saveandnext")) {
				if (mapping.getAttribute() != null) {
					if ("request".equals(mapping.getScope())) {					
						req.removeAttribute(mapping.getAttribute());					
					} else {
						req.getSession().removeAttribute(mapping.getAttribute());
					}
				}
				saveToken(req);
				SessionErrors.add(req, EcardConstants.ADD_INFO_SUCCEED);
				return mapping.findForward("portlet.ecarddoc.add");
			} else {
				return mapping.findForward("portlet.ecarddoc.admin");
			}
		} catch (PortalException e) {
			if (e != null && 
				e instanceof FileSizeException || 
				e instanceof FileNameException) {
				SessionErrors.add(req, e.getClass().getName());
				return mapping.findForward("portlet.ecarddoc.add");
			} else if (e != null && 
						e instanceof DBSystemException) {
				req.setAttribute(PageContext.EXCEPTION, e);
				return mapping.findForward(Constants.COMMON_ERROR);
			}
		}
		return null;
	}
}
