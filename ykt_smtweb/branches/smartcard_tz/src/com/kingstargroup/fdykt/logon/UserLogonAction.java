package com.kingstargroup.fdykt.logon;

import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;


import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionErrors;
import org.apache.struts.action.ActionError;

import com.kingstargroup.fdykt.dao.*;
import com.kingstargroup.fdykt.dto.*;
import com.kingstargroup.fdykt.KSConstant;
import com.kingstargroup.fdykt.Util;
import java.util.*;

/**
 * <p>Title:Test</p>
 * <p>Description: </p>
 * <p>Copyright: Copyright (c) 2004</p>
 * <p>Company: kingstargroup</p>
 * @author
 * @version 1.0
 */

public class UserLogonAction
    extends Action {


  public ActionForward execute(ActionMapping mapping,
                               ActionForm form,
                               HttpServletRequest request,
                               HttpServletResponse response) {
    /**@todo: complete the business logic here, this is just a skeleton.*/
	String areano = request.getParameter("school");
    String stuempno = request.getParameter("stuempno");
    String password = request.getParameter("password");
    DB2CustomerDAO customerdao = new DB2CustomerDAO();
    DB2DeviceDAO devicedao = new DB2DeviceDAO();
    DB2TradeCodeDAO tradecodedao = new DB2TradeCodeDAO();
    try {
      if (stuempno.equals("") || password.equals("")) {
        ActionErrors errors = new ActionErrors();
        errors.add("login", new ActionError("errors.empty"));
        if (!errors.isEmpty()) {
          saveErrors(request, errors);
        }
        return mapping.findForward("failure");
      }
     String ciphered=Util.DESEnc(password);
     System.out.println("password:" + ciphered);
     String sql="select * from ykt_cur.t_cif_customer as cus " +
                "join  ykt_cur.T_PIF_Card as card on cus.Cut_id=card.Cosumer_id " +
                "where cus.StuEmp_no='" + stuempno +"' and cus.area="+areano+" and card.password='" + ciphered +"' ";
      ArrayList customers = customerdao.RetriveCustomer(sql);
      if (customers.size() == 0) {
        ActionErrors errors = new ActionErrors();
        errors.add("login", new ActionError("errors.login"));
        if (!errors.isEmpty()) {
          saveErrors(request, errors);
        }
        return mapping.findForward("failure");
      }else {
        HttpSession session = request.getSession(true);
        HashMap device = devicedao.RetriveDevice();
        HashMap trademsg = tradecodedao.RetriveTradeMsgs();
        session.setAttribute("name",
                             ( (CustomerDTO) customers.get(0)).getCut_name());
        session.setAttribute("cutid",new Integer(((CustomerDTO) customers.get(0)).getCut_id()));
        session.setAttribute("stuempno", stuempno);
        session.setAttribute("device", device);
        session.setAttribute("trademsg", trademsg);
        Cookie clintcookie = new Cookie("school",areano);
        response.addCookie(clintcookie);
        DB2AccountDAO accountdao = new DB2AccountDAO();
		ArrayList accounts = accountdao.getAccountInfo(stuempno);
		if (accounts.size() == 0) {
			return (mapping.findForward("isnull"));
		}
		Iterator i = accounts.iterator();
		while (i.hasNext()) {
			AccountDTO account = (AccountDTO) i.next();
			String state = account.getState_id();
			// ֻ����������д��ʧ�ܵĿ����Թ�ʧ
			if (KSConstant.CARDSTAT_NORMAL.equals(state)
					|| KSConstant.CARDSTAT_WFAIL.equals(state)) {
				session.setAttribute("card_id", new Long(account
						.getCard_id()));
				session.setAttribute("account", account);
				return (mapping.findForward("success"));
			}
		}
		return (mapping.findForward("isnull"));
      }
    }
    catch (Exception e) {
      return (mapping.findForward("index"));
    }
  }
}

