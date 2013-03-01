package com.kingstargroup.advquery.struts.actions;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.advquery.hibernate.util.LunchUtil;

public class DelePersonAction extends Action {
	
	public ActionForward execute(
            ActionMapping mapping,
            ActionForm form,
            HttpServletRequest request,
            HttpServletResponse response) throws Exception {
		   
		  
		   String cutids = request.getParameter("cutids");
		   String[] cutId = cutids.split(",");
		   if( LunchUtil.delePerson(cutId)){
			   request.setAttribute("errorcont", "É¾³ý³É¹¦");
			   return mapping.findForward("errortest");
		   }else{
			   request.setAttribute("errorcont", "É¾³ýÊ§°Ü");
	           return mapping.findForward("errortest");
		   }
		
	}

}
