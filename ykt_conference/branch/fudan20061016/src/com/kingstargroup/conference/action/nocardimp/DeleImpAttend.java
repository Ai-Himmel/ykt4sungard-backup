package com.kingstargroup.conference.action.nocardimp;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.util.AnalyseUtil;
import com.kingstargroup.conference.util.AttendeeUtil;

public class DeleImpAttend extends Action{

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		try{
		    String confid =	request.getParameter("confid");
		    String custids = request.getParameter("custids");
		    if(confid==null || "".equals(confid)){
				 request.setAttribute("tipinfo",NoCardConstant.SELECTCONF);
	        	 return mapping.findForward("error");
			}
		    if(AnalyseUtil.isConferenceOver(confid)){
	        	 request.setAttribute("tipinfo",NoCardConstant.CONFERENCEOVER);
	        	 return mapping.findForward("error");
	        }
		    AttendeeUtil.deleteImpList(confid,custids);
		    request.setAttribute("tipinfo",NoCardConstant.DELETESUCCESS);
		    return mapping.findForward("success");
		}catch(Exception e){
			request.setAttribute("tipinfo",NoCardConstant.DELETEFAIL);
			return mapping.findForward("error");
		}
	}

}
