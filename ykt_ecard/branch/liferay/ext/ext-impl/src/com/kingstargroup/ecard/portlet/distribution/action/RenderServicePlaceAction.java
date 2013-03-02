/**
 * 
 */
package com.kingstargroup.ecard.portlet.distribution.action;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.hibernate.util.ResultPage;
import com.kingstargroup.ecard.portlet.information.service.EcardInformationServiceUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.struts.PortletAction;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: RenderEditMapAction.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-10-28  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class RenderServicePlaceAction extends PortletAction {

	/* (non-Javadoc)
	 * @see org.apache.struts.action.Action#execute(org.apache.struts.action.ActionMapping, org.apache.struts.action.ActionForm, javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)
	 */
	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {
		saveToken(req);
		ResultPage result = EcardInformationServiceUtil.list(EcardConstants.INFORMATION_DISTRIBUTION_TYPE);
		List list = result.getList();
		if(list!=null&&list.size()>0){
			return mapping.findForward("portlet.serviceplace.edit");
		}else{
			return mapping.findForward("portlet.serviceplace.add");
		}
		
	}

}
