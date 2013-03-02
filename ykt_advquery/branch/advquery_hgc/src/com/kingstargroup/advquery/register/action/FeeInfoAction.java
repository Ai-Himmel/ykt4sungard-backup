package com.kingstargroup.advquery.register.action;

import java.util.HashMap;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.advquery.hibernate.util.RegisterUtil;

public class FeeInfoAction extends Action {
	
	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest req, 
			HttpServletResponse res) throws Exception {
		String cmd = req.getParameter("cmd");
		
		String   stuempNo = req.getParameter("stuempNo");
		String   optDate = req.getParameter("optDate");
		String   optTime = req.getParameter("optTime");
		if("update".equals(cmd)){		
		String      comments = req.getParameter("comments");
		boolean flag = RegisterUtil.updateReserverByStuempNo(stuempNo,optDate,optTime,comments);
		req.setAttribute("flag",new Boolean(flag));
		}
		Map result = new HashMap();
		result = RegisterUtil.getReserverByStuempNo(stuempNo,optDate,optTime);
		req.setAttribute("result",result);
		
		return mapping.findForward("fee.reserver");
		
	}

}
