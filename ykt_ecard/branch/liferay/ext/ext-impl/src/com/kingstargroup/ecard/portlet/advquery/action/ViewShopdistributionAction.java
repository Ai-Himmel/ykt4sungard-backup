/**
 * 
 */
package com.kingstargroup.ecard.portlet.advquery.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.liferay.portal.struts.PortletAction;
/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name:ViewSavingSortStatAction.java
 * Description: 
 * Modify History����Change Log��: 
 * �������ͣ��������޸ĵȣ� ��������     ������    �������ݼ���
 * ����               2009-10-21  ������    
 * <p>
 * 
 * @author ������
 * @version 1.0
 * @since 1.0
 */
public class ViewShopdistributionAction extends PortletAction {
	/* (non-Javadoc)
	 * @see org.apache.struts.action.Action#execute(org.apache.struts.action.ActionMapping, org.apache.struts.action.ActionForm, javax.servlet.http.HttpServletRequest, javax.servlet.http.HttpServletResponse)
	 */
	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {		
		return mapping.findForward("portlet.advquery.shopdistribution.view");
	}
}
