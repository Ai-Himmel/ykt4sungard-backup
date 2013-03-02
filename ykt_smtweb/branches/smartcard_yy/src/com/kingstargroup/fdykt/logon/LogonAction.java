package com.kingstargroup.fdykt.logon;

import org.apache.log4j.Logger;

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

public class LogonAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(LogonAction.class);

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
		String cardno = request.getParameter("cardno");
		String password = request.getParameter("password");
		DB2CustomerDAO customerdao = new DB2CustomerDAO();
		DB2CardDAO carddao = new DB2CardDAO();
		DB2DeviceDAO devicedao = new DB2DeviceDAO();
		DB2TradeCodeDAO tradecodedao = new DB2TradeCodeDAO();
		DB2SysParaDAO sysParadao = new DB2SysParaDAO();
		try {
			if (null == password || "".equals(password)) {
				ActionErrors errors = new ActionErrors();
				errors.add("login", new ActionError("errors.emptypwd"));
				if (!errors.isEmpty()) {
					saveErrors(request, errors);
				}
				return mapping.getInputForward();
			}
			String hexcardno = Integer.toHexString(Integer.parseInt(cardno))
					.toUpperCase();
			for (int i = hexcardno.length(); i < 8; i++) {
				hexcardno = "0" + hexcardno;//pad left
			}
			logger.debug("physical cardno:" + hexcardno);
			String ciphered = Util.DESEnc(password);
			logger.debug("password:" + ciphered);
			 
			// 查询出唯一的卡
			CardDTO card = carddao.getCardInfoByIdPwd(hexcardno, ciphered);

			if (card == null) {
				ActionErrors errors = new ActionErrors();
				errors.add("login", new ActionError("errors.password"));
				if (!errors.isEmpty()) {
					saveErrors(request, errors);
				}
				return mapping.findForward("failure");
			} else {
				String sql = "select * from ykt_cur.t_cif_customer cus "
						+ "where cus.Cut_id= " + card.getCosumerId();
				ArrayList customers = customerdao.RetriveCustomer(sql);
				HttpSession session = request.getSession(true);
				HashMap device = devicedao.RetriveDevice();
				HashMap trademsg = tradecodedao.RetriveTradeMsgs();
				SysParaDTO sysPara = sysParadao.getSysPara(KSConstant.DICT_MAINKEY);//设备授权密钥
				
				if (customers.size() > 0) {
					int cutid = ((CustomerDTO) customers.get(0)).getCut_id();
					session.setAttribute("name", ((CustomerDTO) customers
							.get(0)).getCut_name());
					session.setAttribute("cutid", new Integer(
							((CustomerDTO) customers.get(0)).getCut_id()));
					session.setAttribute("stuempno", ((CustomerDTO) customers
							.get(0)).getStuemp_no());
					
					try {
						DB2SubsysLogDAO subsyslogdao = new DB2SubsysLogDAO();
						TSubsysLogDTO syslogdto = new TSubsysLogDTO();
						syslogdto.setCustId(cutid);
						String sysdate = new DB2SysParaDAO().getDBDateTime();
						String systime = sysdate.substring(8);
						sysdate = sysdate.substring(0, 8);
						syslogdto.setLogDate(sysdate);
						syslogdto.setLogTime(systime);
						syslogdto.setFlag(0);
						syslogdto.setLoginName("");
						syslogdto.setSussysId(2001);
						syslogdto.setComments("["+cutid+":"+sysdate+systime+"]成功登陆多媒体查询系统");
						subsyslogdao.createLogInfo(syslogdto);
					} catch (Exception e) {
						// TODO: handle exception
						e.printStackTrace();
						logger.error(e.getMessage());
					}
				}
				session.setAttribute("cardid", card.getCardId());
				session.setAttribute("device", device);
				session.setAttribute("trademsg", trademsg);
				session.setAttribute("paramKey", sysPara.getValue());//设备授权密钥
				session.setAttribute("cardPhysicalNo", hexcardno);
				session.setAttribute("cardno", cardno);
				
				
				
				return (mapping.findForward("success"));
			}
		} catch (Exception e) {
			logger.error(e.getMessage());
			e.printStackTrace();
			return (mapping.findForward("failure"));
		}
	}
}
