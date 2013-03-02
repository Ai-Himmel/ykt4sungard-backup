/**
 * 
 */
package com.kingstargroup.conference.action.analyse;


import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.common.DateUtilExtend;
import com.kingstargroup.conference.common.ParamUtil;
import com.kingstargroup.conference.common.SessionErrors;
import com.kingstargroup.conference.util.AnalyseUtil;

/**
 * @author Õı”®
 *
 */
public class SignPerAnalyseAction extends Action {

	public ActionForward execute(
			ActionMapping mapping,
			ActionForm form,
			HttpServletRequest request,
			HttpServletResponse response) {
		String conId = ParamUtil.getString(request, "conId");
		String conType = ParamUtil.getString(request, "conType");
		String begindate = ParamUtil.getString(request, "begindate");
		String enddate = ParamUtil.getString(request, "enddate");
		boolean begin = false;
		boolean end = false;
		Integer conid;
		if(!"".equals(begindate)) {
			begin = true;
		}
		if(!"".equals(enddate)) {
			end = true;
		}
		if("".equals(conId)) {
			conid = null;
		} else  {
			conid = Integer.valueOf(conId);
		}		
		
		try {
			request.setAttribute("conflist", AnalyseUtil.getAllConfenece());	
			request.setAttribute("conftype", AnalyseUtil.getAllConfType());
			
			if(begin && end) {
				long i = DateUtilExtend.diffDate(begindate, enddate);
				if(i<0) {
					SessionErrors.add(request, "analyse.failed.date");
					return mapping.getInputForward();
				}			
			}
			
			if((null != conid) || (!"".equals(conType)) || begin || end) {
				request.setAttribute("conference", AnalyseUtil.getConference(conid, conType, begindate, enddate));	
				request.setAttribute("concount", AnalyseUtil.getAtteCount(conid, conType, begindate, enddate));
			}
		} catch(Exception e) {
			return mapping.findForward("error");
		}
		return mapping.findForward("querysignper");
	}
}
