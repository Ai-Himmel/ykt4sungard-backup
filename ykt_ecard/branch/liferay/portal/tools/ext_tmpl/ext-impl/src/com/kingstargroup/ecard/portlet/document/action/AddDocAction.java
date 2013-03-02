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
import org.apache.struts.action.DynaActionForm;
import org.apache.struts.upload.FormFile;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.FileNameException;
import com.kingstargroup.ecard.exceptions.FileSizeException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.portlet.information.service.EcardInformationServiceUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.UploadServletRequest;

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

			UpLoadForm upLoadForm = (UpLoadForm)form;
//			String title = req.getParameter("title");
//			String cmd = req.getParameter("cmd");
			String title = upLoadForm.getTitle();
			String cmd = upLoadForm.getCmd();
			String creater = GetterUtil.get((String)req.getSession().getAttribute("j_username"), StringPool.BLANK);
//			String creater = GetterUtil.get((String)req.getSession().getAttribute(WebKeys.USER_ID), StringPool.BLANK);
			//添加此条文档信息
//			if (isTokenValid(req)) {
//				
				EcardInformationServiceUtil.add(title, 
						"", 
						"", 
						String.valueOf(EcardConstants.INFORMATION_DOCUMENT_TYPE), 
						creater, 
						upLoadForm,
						EcardConstants.DOCUMENT_TYPE);
//				resetToken(req);
//			}			
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
				return mapping.findForward(ActionConstants.COMMON_ERROR);
			}
		}
		return null;
	}
}
