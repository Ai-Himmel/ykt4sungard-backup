package com.kingstargroup.conference.action.nocardimp;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.util.AttendeeUtil;
 
public class QryImpAttend extends Action{
	
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		try{
			String confid = request.getParameter("confid");
			if(confid==null || "".equals(confid)){
				 request.setAttribute("tipinfo",NoCardConstant.SELECTCONF);
	        	 return mapping.findForward("error");
			}
		    request.setAttribute("result",AttendeeUtil.getImpList(confid));
		    request.setAttribute("confid",confid);
		    return mapping.findForward("qryImpAttend");
		}catch(Exception e){
			return mapping.findForward("error");
		}
	}
	
}