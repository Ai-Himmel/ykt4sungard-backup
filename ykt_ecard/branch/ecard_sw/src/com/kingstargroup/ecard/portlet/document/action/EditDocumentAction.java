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
import com.liferay.util.servlet.SessionErrors;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.
 * File name: EditDocumentAction.java
 * Description: 
 * Modify History: 
 * ��������   ������   ����ʱ��     ��������
 * ===================================
 *  ����    Xiao Qi  2005-9-14  
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class EditDocumentAction extends PortletAction {

	/* (non-Javadoc)
	 * @see org.apache.struts.action.Action#execute(org.apache.struts.action.ActionMapping, org.apache.struts.action.ActionForm, javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)
	 */
	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {
		String docId = req.getParameter("id");
		String title = req.getParameter("title");
		String attachments = req.getParameter("attachments");
		try {
			if (isTokenValid(req)) {
				
				InformationUtil.updateInfoById(docId, 
												title, 
												"", 
												attachments, 
												req, 
												new String[]{"file_location"}, 
												EcardConstants.DOCUMENT_TYPE);
				resetToken(req);
			}
			SessionErrors.add(req, EcardConstants.EDIT_INFO_SUCCESS);
			return mapping.findForward("portlet.ecarddoc.admin");			
		}
		catch (PortalException e) {
			if (e != null && 
					e instanceof FileSizeException || 
					e instanceof FileNameException) {
					SessionErrors.add(req, e.getClass().getName());
					return mapping.findForward("portlet.ecarddoc.edit");
				} else if (e != null && 
							e instanceof DBSystemException) {
					req.setAttribute(PageContext.EXCEPTION, e);
					return mapping.findForward(Constants.COMMON_ERROR);
				}
		}
		return null;
	}

}
