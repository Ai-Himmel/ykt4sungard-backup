package com.kingstargroup.ecard.portlet.maintain.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.equipment.Maintain;
import com.kingstargroup.ecard.hibernate.util.MaintainUtil;
import com.kingstargroup.ecard.hibernate.util.WebDictionaryUtil;
import com.kingstargroup.ecard.hibernate.web.WebDictionary;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;


public class UserMaintainDetailAction extends PortletAction{

	public ActionForward execute(    
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {
		try {
			String id = req.getParameter("id");
			Maintain maintain =MaintainUtil.getMaintainById(id);
			String school = maintain.getSchoolArea();
			WebDictionary  webservice= WebDictionaryUtil.getDictionary("009",school);
			String schoolArea = webservice.getDicCaption();
			req.getSession().setAttribute("schoolArea",schoolArea);
			req.getSession().setAttribute("Maintain", maintain);
			req.getSession().setAttribute("TypeList", MaintainUtil.getDictionaryByMaintain(new Integer(id)));
			req.getSession().setAttribute("id", id);
			return mapping.findForward("portlet.maintain.userdetail");		
		} catch (PortalException pe) {
			req.setAttribute(PageContext.EXCEPTION, pe);
			return mapping.findForward(Constants.COMMON_ERROR);
		}
	}

}
