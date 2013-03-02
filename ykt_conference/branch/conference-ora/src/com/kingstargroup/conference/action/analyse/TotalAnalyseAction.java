/**
 * 
 */
package com.kingstargroup.conference.action.analyse;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.ajaxanywhere.AAUtils;
import org.apache.commons.lang.StringUtils;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.common.GetterUtil;
import com.kingstargroup.conference.common.ParamUtil;
import com.kingstargroup.conference.util.AnalyseUtil;

public class TotalAnalyseAction extends Action {

	public ActionForward execute(
			ActionMapping mapping,
			ActionForm form,
			HttpServletRequest request,
			HttpServletResponse response) {
		String conId = ParamUtil.getString(request, "conId");

		String flag = ParamUtil.getString(request, "flag");
		String printflag = ParamUtil.getString(request, "printflag");
		String groupId = ParamUtil.getString(request, "groupId");
		Integer conid;

		if("".equals(conId)) {
			conid = null;
		} else  {
			conid = Integer.valueOf(conId);
		}		
		try {
			request.setAttribute("conflist", AnalyseUtil.getAllConfenece());	
			request.setAttribute("conftype", AnalyseUtil.getAllConfType());
			request.setAttribute("groupCountList", AnalyseUtil.getGroupCount(conid));
			if(null==flag||"".equals(flag)){
				if((null != conid)) {
					request.setAttribute("conference", AnalyseUtil.getConference(conid, "", "", ""));	
					request.setAttribute("concount", AnalyseUtil.getAtteCount(conid, "", "", ""));
				}
			}else{		
				if((null != conid)) {
					request.setAttribute("conference", AnalyseUtil.getConference(conid, "", "", ""));	
					request.setAttribute("concount", AnalyseUtil.getAtteCount(conid, "", "", ""));
					if(StringUtils.isNotBlank(groupId)){
						request.setAttribute("result", AnalyseUtil.getAttendeeListByGroup(conid,flag,groupId));
					} else {
						request.setAttribute("result", AnalyseUtil.getTTAttendeeList(conid,flag));
					}
					if (AAUtils.isAjaxRequest(request)) {
						AAUtils.addZonesToRefresh(request, "alist");
					}	
				}						
			}		
		} catch(Exception e) {
			return mapping.findForward("error");
		}
		if("print".equals(printflag)){
			return mapping.findForward("totalreportforprint");
		}else{
			return mapping.findForward("totalreport");
		}
		
	}
}