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

/**
 * ÎÞ¿¨Ç©µ½
 * @author hjw
 *
 */
public class ReplaceByHandQueryAAction extends Action{

	public ActionForward execute(
			ActionMapping mapping, 
			ActionForm from, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
			int confid = ParamUtil.getInteger(request,"confidA");
			String custno = ParamUtil.getString(request,"custnoA");
			String custname = ParamUtil.getString(request,"custnameA");
			String deptcode = ParamUtil.getString(request,"deptcodeA");
			String duty = ParamUtil.getString(request,"dutyA");
			String username = GetterUtil.get((String) request.getSession()
					.getAttribute("username"), "");			
			List confList = GetDictionary.getConfList(username);
			List deptList = GetDictionary.getDeptList();
			request.setAttribute("confList", confList);
			request.setAttribute("deptList", deptList);
			request.setAttribute("resultA",AttendeeUtil.getCustListMaphandA(confid,custno,custname,duty,deptcode));
			if (AAUtils.isAjaxRequest(request)) {
				AAUtils.addZonesToRefresh(request, "alist");
			}
			
			return mapping.findForward("success");
			
	}

}
