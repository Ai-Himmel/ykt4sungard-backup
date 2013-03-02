package com.kingstargroup.fdykt.transfer;

import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.kingstargroup.fdykt.dao.*;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.logon.LogonAction;

public class CheckTransferAction  extends Action {
	
	private static final Logger logger = Logger.getLogger(LogonAction.class);
	
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {


	    saveToken(request);
		String money  = request.getParameter("money");
		request.setAttribute("money",money);
	
	
	return mapping.findForward("success");
	}

}
