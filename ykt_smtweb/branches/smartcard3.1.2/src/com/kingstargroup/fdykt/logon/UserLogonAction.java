package com.kingstargroup.fdykt.logon;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionError;
import org.apache.struts.action.ActionErrors;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.KSConstant;
import com.kingstargroup.fdykt.Util;
import com.kingstargroup.fdykt.dao.DB2AccountDAO;
import com.kingstargroup.fdykt.dao.DB2CustomerDAO;
import com.kingstargroup.fdykt.dao.DB2DeviceDAO;
import com.kingstargroup.fdykt.dao.DB2TradeCodeDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.AccountDTO;
import com.kingstargroup.fdykt.dto.CustomerDTO;

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
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(UserLogonAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {

		KSDaoSessionFactory.createSession();
		ActionForward forward = doLogin(mapping, request);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			logger.error("提交事务失败");
			e.printStackTrace();
		}
		return forward;
	}
	
	private ActionForward doLogin(ActionMapping mapping, HttpServletRequest request) {

    /**@todo: complete the business logic here, this is just a skeleton.*/
    String stuempno = request.getParameter("stuempno");
    String password = request.getParameter("password");
    String cardphytype = request.getParameter("cardphytype");
    DB2CustomerDAO customerdao = new DB2CustomerDAO();
    DB2DeviceDAO devicedao = new DB2DeviceDAO();
    DB2TradeCodeDAO tradecodedao = new DB2TradeCodeDAO();
   
    try {
    	ArrayList list = customerdao.getAvailCardPhytype();
		request.setAttribute("cardphytypeList", list);
      if (stuempno.equals("") || password.equals("")) {
        ActionErrors errors = new ActionErrors();
        errors.add("login", new ActionError("errors.empty"));
        if (!errors.isEmpty()) {
          saveErrors(request, errors);
        }
        return mapping.findForward("failure");
      }
     
      
     stuempno = stuempno.toUpperCase();
     String ciphered=Util.DESEnc(password);
     String existsql = "select * from ykt_cur.t_customer cus " +
     "join  ykt_cur.t_card card on cus.custid=card.custid " +
     "where upper(cus.stuempno)='" + stuempno +"' ";
	if(!"0".equals(cardphytype)){
		existsql +=" and card.cardphytype="+cardphytype;
	}
	
	 ArrayList existcustomers = customerdao.RetriveCustomer(existsql);
	  if (existcustomers.size() == 0) {
		  ActionErrors errors = new ActionErrors();
		  errors.add("login", new ActionError(
					"back.error", "您尚未开通此类卡。"));
			saveErrors(request, errors);
	        return mapping.findForward("failure");
	  }

     String sql ="select * from ykt_cur.t_customer cus " +
                "join  ykt_cur.t_card card on cus.custid=card.custid " +
                "where upper(cus.stuempno)='" + stuempno +"' and card.cardpwd='" + ciphered +"'";
     if(!"0".equals(cardphytype)){
    	 sql +=" and card.cardphytype="+cardphytype;
     }

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
        CustomerDTO custDTO = (CustomerDTO) customers.get(0);
		long custid = custDTO.getCustid();
		String custname = custDTO.getCustname();
        session.setAttribute("name",custname);
        session.setAttribute("cutid",String.valueOf(custid));
        session.setAttribute("stuempno", stuempno);
        session.setAttribute("password", password);
        session.setAttribute("device", device);
        session.setAttribute("trademsg", trademsg);
        DB2AccountDAO accountdao = new DB2AccountDAO();
		ArrayList accounts = accountdao.getAccountInfo(stuempno,cardphytype);
		if (accounts.size() == 0) {
			ArrayList lossaccounts = accountdao.getLossAccountInfo(stuempno,cardphytype);
			if(lossaccounts.size()>0){
				AccountDTO acc = (AccountDTO)lossaccounts.get(0);
				request.setAttribute("card_id",String.valueOf(acc.getCardno()));
				request.setAttribute("state",String.valueOf(acc.getCardstatus()));
				request.setAttribute("cardphytype", cardphytype);
			}
			return (mapping.findForward("isnull"));
		}
		Iterator i = accounts.iterator();
		while (i.hasNext()) {
			AccountDTO account = (AccountDTO) i.next();
			String state = account.getCardstatus();
			// 只有正常卡与写卡失败的卡可以挂失
			if (KSConstant.CARDSTAT_NORMAL.equals(state)
					|| KSConstant.CARDSTAT_WFAIL.equals(state)) {
				session.setAttribute("card_id", String.valueOf(account.getCardno()));
				session.setAttribute("account", account);
				return (mapping.findForward("success"));
			}else if(KSConstant.CARDSTAT_LOST.equals(state)){
				request.setAttribute("card_id", String.valueOf(account.getCardno()));
				request.setAttribute("state", state);
//				session.setAttribute("account", account);
				return (mapping.findForward("isnull"));
			}
		}
		return (mapping.findForward("isnull"));
      }
    }catch (Exception e) {
      e.printStackTrace();
      ActionErrors errors = new ActionErrors();
      errors.add("login", new ActionError("errors.login"));
      if (!errors.isEmpty()) {
        saveErrors(request, errors);
      }
      return mapping.findForward("failure");
    }
  }
}

