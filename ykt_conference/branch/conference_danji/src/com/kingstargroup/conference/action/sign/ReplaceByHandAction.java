package com.kingstargroup.conference.action.sign;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.ajaxanywhere.AAUtils;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.common.GetterUtil;
import com.kingstargroup.conference.common.ParamUtil;
import com.kingstargroup.conference.util.AttendeeUtil;
import com.kingstargroup.conference.util.GetDictionary;
import com.kingstargroup.conference.util.SignUtil;

/**
 * 替代签到
 * 
 * @author hjw
 * 
 */
public class ReplaceByHandAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		int confid = ParamUtil.getInteger(request, "confidA");
		String custnoA = ParamUtil.getString(request, "custnoA");
		String custnameA = ParamUtil.getString(request, "custnameA");
		String deptcodeA = ParamUtil.getString(request, "deptcodeA");
		String dutyA = ParamUtil.getString(request, "dutyA");
		String custnoB = ParamUtil.getString(request, "custnoB");
		String custnameB = ParamUtil.getString(request, "custnameB");
		String deptcodeB = ParamUtil.getString(request, "deptcodeB");
		String dutyB = ParamUtil.getString(request, "dutyB");		
		String flag = ParamUtil.getString(request, "flag");
		String custidA = ParamUtil.getString(request, "custidA");
		String custidB = ParamUtil.getString(request, "custidB");
		String username = GetterUtil.get((String) request.getSession()
				.getAttribute("username"), "");
		List confList = GetDictionary.getConfListBeforeMeeting(username);
		List deptList = GetDictionary.getDeptList();
		request.setAttribute("confList", confList);
		request.setAttribute("deptList", deptList);
		if ("A".equals(flag)) {
			if(confid==0){
				request.setAttribute("tipinfo", "请选择会议！");
				if (AAUtils.isAjaxRequest(request)) {
					AAUtils.addZonesToRefresh(request, "tipinfo");
				}
				return mapping.findForward("success");
			}
			
			request.setAttribute("resultA", AttendeeUtil.getCustListMaphandA(
					confid, custnoA, custnameA, dutyA, deptcodeA));
			if (AAUtils.isAjaxRequest(request)) {
				AAUtils.addZonesToRefresh(request, "alist");
			}
			return mapping.findForward("success");
		} else if ("B".equals(flag)) {
			if(confid==0){
				request.setAttribute("tipinfo", "请选择会议！");
				if (AAUtils.isAjaxRequest(request)) {
					AAUtils.addZonesToRefresh(request, "tipinfo");
				}
				return mapping.findForward("success");
			}

			request.setAttribute("resultB", AttendeeUtil.getCustListMaphandB(
					confid, custnoB, custnameB, dutyB, deptcodeB));
			if (AAUtils.isAjaxRequest(request)) {
				AAUtils.addZonesToRefresh(request, "blist");
			}
			return mapping.findForward("success");
		} else if ("all".equals(flag)) {
			try {
				if(confid==0){

					request.setAttribute("tipinfo", "请选择会议！");
					if (AAUtils.isAjaxRequest(request)) {
						AAUtils.addZonesToRefresh(request, "tipinfo");
					}
					return mapping.findForward("success");
				}
				if("".equals(custidA)){

					request.setAttribute("tipinfo", "请选择未到人员！");
					if (AAUtils.isAjaxRequest(request)) {
						AAUtils.addZonesToRefresh(request, "tipinfo");
					}
					return mapping.findForward("success");
				}
				if("".equals(custidB)){

					request.setAttribute("tipinfo", "请选择代签人员！");
					if (AAUtils.isAjaxRequest(request)) {
						AAUtils.addZonesToRefresh(request, "tipinfo");
					}
					return mapping.findForward("success");
				}
				if (SignUtil.attendeeReplacebyhand(confid, custidA, custidB)) {					

					request.setAttribute("resultA", AttendeeUtil
							.getCustListMaphandA(confid, custnoA, custnameA,
									dutyA, deptcodeA));
					request.setAttribute("resultB", AttendeeUtil
							.getCustListMaphandB(confid, custnoB, custnameB,
									dutyB, deptcodeB));
					if (AAUtils.isAjaxRequest(request)) {
						AAUtils.addZonesToRefresh(request, "alist,blist");
					}
					return mapping.findForward("success");
				} else {

					request.setAttribute("tipinfo", "代签失败，请检查原因！");
					return mapping.findForward("success");
				}

			} catch (Exception e) {

				request.setAttribute("tipinfo", "代签失败，请检查原因！");
				if (AAUtils.isAjaxRequest(request)) {
					AAUtils.addZonesToRefresh(request, "tipinfo");
				}
				return mapping.findForward("success");
			}
		} else {
			return mapping.findForward("success");
		}

	}

}
