package com.kingstargroup.fdykt.logon;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;


import org.apache.log4j.Logger;
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

import java.sql.SQLException;
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
     String sql="select cus.* from ykt_cur.t_cif_customer as cus " +
                "join  ykt_cur.T_PIF_Card as card on cus.Cut_id=card.Cosumer_id " +
                "where cus.StuEmp_no='" + stuempno +"' and card.password='" + ciphered +"' with ur";
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
        int cutid = ((CustomerDTO) customers.get(0)).getCut_id();
        session.setAttribute("cutid",new Integer(cutid));
        session.setAttribute("stuempno", stuempno);
        session.setAttribute("device", device);
        session.setAttribute("trademsg", trademsg);       
		
		DB2AccountDAO accountdao = new DB2AccountDAO();
		ArrayList accounts = accountdao.getAccountInfo(stuempno);
		if (accounts.size() == 0) {
			return (mapping.findForward("isnull"));
		}
		Iterator i = accounts.iterator();
		while (i.hasNext()) {
			AccountDTO account = (AccountDTO) i.next();
			String state = account.getState_id();
			// 只有正常卡与写卡失败的卡可以挂失
			if (KSConstant.CARDSTAT_NORMAL.equals(state)
					|| KSConstant.CARDSTAT_WFAIL.equals(state)) {
				session.setAttribute("card_id", new Long(account
						.getCard_id()));
				session.setAttribute("account", account);
			}
		}
		
//		 try {
//				DB2SubsysLogDAO subsyslogdao = new DB2SubsysLogDAO();
//				TSubsysLogDTO syslogdto = new TSubsysLogDTO();
//				syslogdto.setCustId(cutid);
//				String sysdate = new DB2SysParaDAO().getDBDateTime();
//				String systime = sysdate.substring(8);
//				sysdate = sysdate.substring(0, 8);
//				syslogdto.setLogDate(sysdate);
//				syslogdto.setLogTime(systime);
//				syslogdto.setFlag(0);
//				syslogdto.setLoginName("");
//				syslogdto.setSussysId(2001);
//				syslogdto.setComments("["+cutid+":"+sysdate+systime+"]成功登陆多媒体查询系统");
//				subsyslogdao.createLogInfo(syslogdto);
//			} catch (Exception e) {
//				// TODO: handle exception
//				e.printStackTrace();
//				logger.error(e.getMessage());
//				return (mapping.findForward("index"));
//			}
        
        return (mapping.findForward("success"));
      }
    }
    catch (Exception e) {
      return (mapping.findForward("index"));
    }
  }
}

