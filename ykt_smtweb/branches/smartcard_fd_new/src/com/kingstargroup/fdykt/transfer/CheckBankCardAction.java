package com.kingstargroup.fdykt.transfer;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.kingstargroup.fdykt.util.BankUtil;
import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;

public class CheckBankCardAction extends Action {
	
	private static final Logger logger = Logger.getLogger(CheckBankCardAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		KSDaoSessionFactory.createSession();
		try {
			
			saveToken(request);
			
	        String bankno = request.getParameter("bankno");
	        
	        String cmd = request.getParameter("cmd");
            if(!new BankUtil().checkBankCardHead(bankno)){
				
				request.setAttribute("msg","请刷指定银行卡,请返回重新操作");
				
				return mapping.findForward("failure");
			}
	        
			if(!new BankUtil().checkBankCardLength(bankno)){
				
				request.setAttribute("msg","非指定银行卡,请返回重新操作");
				
				return mapping.findForward("failure");
			}
           
			
			KSDaoSessionFactory.commit();
			
			request.getSession().setAttribute("bankno",bankno);
			
			
			return mapping.findForward(cmd);
		} catch (Exception e) {
			e.printStackTrace();
			return mapping.findForward("index");
		}
		
	}


}
