package com.kingstargroup.conference.action.nocardimp;



import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.util.AnalyseUtil;

public class NocardConfListNextAction  extends Action{

	public ActionForward execute(
			ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		try{
         String  confid = request.getParameter("confid");
         if(confid == null || "".equals(confid)){
        	 request.setAttribute("tipinfo",NoCardConstant.SELECTCONF);
        	 return mapping.findForward("error");
         }
        if(AnalyseUtil.isConferenceOver(confid)){
        	 request.setAttribute("tipinfo",NoCardConstant.CONFERENCEOVER);
        	 return mapping.findForward("error");
        }
        	
         
         request.getSession().setAttribute("confid", confid);
         
		 return mapping.findForward("findexcel");
		}catch (Exception e) {
			e.printStackTrace();
			return mapping.findForward("error");
		}
	}

}
