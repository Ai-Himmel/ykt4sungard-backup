package com.kingstargroup.fdykt.register.fee;

import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.KSConstant;
import com.kingstargroup.fdykt.dao.DB2SysParaDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.SysParaDTO;
public class RegisterFeeAction extends Action {

	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(RegisterFeeAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
       
		KSDaoSessionFactory.createSession();
		ActionForward forward = checklogin(mapping, request);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			logger.error("提交事务失败");
			e.printStackTrace();
		} catch(Exception e){
			
		}
		return forward;
	}

	private ActionForward checklogin(ActionMapping mapping, HttpServletRequest request) {
		HttpSession session = request.getSession();
		/*String cardno = (String) session.getAttribute("cardno");				
		if (cardno == null || "".equals(cardno))
			return mapping.findForward("logon");		
		request.setAttribute("cardno", cardno);*/
		DB2SysParaDAO sysParadao = new DB2SysParaDAO();
		try{
		SysParaDTO sysPara = sysParadao.getSysPara(KSConstant.DICT_MAINKEY);//设备授权密钥
		session.setAttribute("paramKey", sysPara.getValue());//设备授权密钥
		
		
		return (mapping.findForward("success"));
		}catch(Exception e){
			logger.error("读取参数失败");
			request.setAttribute("errmsg","系统暂时无法更新，稍后再试");
			e.printStackTrace();
			return (mapping.findForward("failure"));
		}
		
		
	}
}
