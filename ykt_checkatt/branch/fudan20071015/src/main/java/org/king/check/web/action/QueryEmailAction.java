package org.king.check.web.action;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.king.check.service.LeaveInfoService;
import org.king.framework.web.action.BaseAction;

public class QueryEmailAction extends BaseAction {
	private LeaveInfoService leaveInfoService;
	
	public void setLeaveInfoService(LeaveInfoService leaveInfoService) {
		this.leaveInfoService = leaveInfoService;
	}
	
	public ActionForward goEmailQuery(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		    
		  List addressList = leaveInfoService.QueryEmail("001");
          List emailList = leaveInfoService.QueryEmail("002");
          List userList = leaveInfoService.QueryEmail("003");
          List pwdList = leaveInfoService.QueryEmail("004");
          List titList =leaveInfoService.QueryEmail("005");
		  request.setAttribute("addressList", addressList);
		  request.setAttribute("emailList", emailList);
		  request.setAttribute("userList", userList);
		  request.setAttribute("pwdList", pwdList);
		  request.setAttribute("titList", titList);
		  
		  return mapping.findForward("goEmailQuery");
	}
}
