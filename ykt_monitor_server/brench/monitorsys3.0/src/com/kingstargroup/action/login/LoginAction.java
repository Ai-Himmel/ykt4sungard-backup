package com.kingstargroup.action.login;

import java.util.ArrayList;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessage;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.actions.DispatchAction;
import org.hibernate.engine.Mapping;

import com.kingstargroup.action.user.ErrorCode;
import com.kingstargroup.action.user.LoginCheck;
import com.kingstargroup.business.util.DeviceStatusUtil;
import com.kingstargroup.business.util.ParaUtil;
import com.kingstargroup.form.Devicestatus;
import com.kingstargroup.form.MapParamTable;
import com.kingstargroup.utils.MD5encoding;

public class LoginAction extends DispatchAction {
	
	public ActionForward login(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		HttpSession session = request.getSession();
		ActionMessages errors = new ActionMessages();
		try {

			String userName = request.getParameter("UserName");
			String password = request.getParameter("PassWord");
			String retCode = LoginCheck.logindbCheck(userName, MD5encoding.MD5Encode(password));
			
			
			if (ErrorCode.NO_USER.equals(retCode)) {
				errors.add("login", new ActionMessage("user.loginServlet.NO_USER"));
				if (!errors.isEmpty()) {
					saveErrors(request, errors);
				}
				return mapping.findForward("failure");
			} else if (ErrorCode.PWD_ERROR.equals(retCode)) {
				errors.add("login", new ActionMessage("user.loginServlet.PWD_ERROR"));
				if (!errors.isEmpty()) {
					saveErrors(request, errors);
				}
				return mapping.findForward("failure");
			} else if (ErrorCode.USER_STOPED.equals(retCode)) {
				errors.add("login", new ActionMessage("user.loginServlet.USER_STOPED"));
				if (!errors.isEmpty()) {
					saveErrors(request, errors);
				}
				return mapping.findForward("failure");
			} else {
				List list  = DeviceStatusUtil.stateDictList();
				request.setAttribute("stateDict", list);
				List result = new ArrayList();
			    MapParamTable param = ParaUtil.getPara("HeartLostTime"); 
			    double  timeInterval =param.getValue();
			    result = DeviceStatusUtil.getDeviceStatus("","","1,2",String.valueOf(timeInterval));
			    request.setAttribute("result", result);
			    
			    session.setAttribute("loginUserName", userName);
				return mapping.findForward("success");
				
			}

		} catch (Exception e) {
			e.printStackTrace();
			errors.add("login", new ActionMessage("user.loginServlet.PWD_ERROR"));
			if (!errors.isEmpty()) {
				saveErrors(request, errors);
			}
			return mapping.findForward("failure");
		}

	
	}
	
	public ActionForward loginout(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
	throws Exception {
		request.getSession().invalidate();
		return mapping.findForward("failure");	
	}

}
