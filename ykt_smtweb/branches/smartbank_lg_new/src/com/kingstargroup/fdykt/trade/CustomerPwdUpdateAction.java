// Created by Xslt generator for Eclipse.
// XSL :  not found (java.io.FileNotFoundException:  (Bad file descriptor))
// Default XSL used : easystruts.jar$org.easystruts.xslgen.JavaClass.xsl

package com.kingstargroup.fdykt.trade;

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
import com.kingstargroup.fdykt.Util;
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.DB2SysParaDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;
import com.kingstargroup.fdykt.dto.SysParaDTO;

/**
 * AccountSearchAction.java created by EasyStruts - XsltGen.
 * http://easystruts.sf.net
 * created on 01-18-2005
 *
 * XDoclet definition:
 * @struts:action path="/accountSearch" name="accountsearchForm" attribute="accountSearchForm" input="/accountSearch.jsp" validate="true"
 * @struts:action-forward name="/accountResult.jsp" path="/accountResult.jsp"
 */
public class CustomerPwdUpdateAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(CustomerPwdUpdateAction.class);

	// --------------------------------------------------------- Instance Variables

	// --------------------------------------------------------- Methods

	/**
	 * Method execute
	 * @param ActionMapping mapping
	 * @param ActionForm form
	 * @param HttpServletRequest request
	 * @param HttpServletResponse response
	 * @return ActionForward
	 * @throws Exception
	 */
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		DB2CardDAO carddao = new DB2CardDAO();
		try {
		//HttpSession session = request.getSession();
		String cardno = request.getParameter("cardno");
		request.setAttribute("cardno",cardno);
		CardDTO card = carddao.getCardInfoByCardNo(cardno);
		DB2SysParaDAO sysParadao = new DB2SysParaDAO();
		
		if (card == null) {
			return mapping.findForward("msg");
		}
		
		SysParaDTO sysPara = sysParadao.getSysPara(KSConstant.DICT_MAINKEY);//设备授权密钥
		request.setAttribute("paramKey",sysPara.getValue());
		
		String cardId = card.getCardId();
		
		KSDaoSessionFactory.createSession();
		String  stateId = card.getStateId();
		
		if("1100".equals(stateId)){
			request.setAttribute("msg","卡已挂失,不能修改密码");
			return mapping.findForward("failure");
		}else if("1010".equals(stateId)) {
			request.setAttribute("msg","卡已冻结,不能修改密码");
			return mapping.findForward("failure");
		}
		
		 /* if(!oldPwd(mapping, form, request, cardId)){
			 request.setAttribute("msg","原密码错误");
			return  mapping.findForward("failure");
		  }*/

		  if(doUpdatePswd(mapping, form, request,cardId)){	
				KSDaoSessionFactory.commit();
				request.setAttribute("msg","密码修改成功");
				return mapping.findForward("success");
			}
			else{
				KSDaoSessionFactory.rollback();
				request.setAttribute("msg","密码修改失败，重新修改");
				return mapping.findForward("failure");
			}
		} catch (SQLException e) {
			logger.error("更新卡密码失败",e);
			e.printStackTrace();
		}
		return mapping.findForward("failure");
	}

	private boolean doUpdatePswd(ActionMapping mapping, ActionForm form, HttpServletRequest request,String cardId) {
		//HttpSession session = request.getSession();
		DB2CardDAO carddao = new DB2CardDAO();
		CustomerPwdUpdateForm customerPwdUpdateform = (CustomerPwdUpdateForm) form;
		
		//String cardId = (String)session.getAttribute("cardid");
		String newpwd = customerPwdUpdateform.getNewPwd();
		try {
			String ciphered = Util.DESEnc(newpwd);
			carddao.updateCardPassword(Integer.parseInt(cardId), ciphered);
			logger.debug(cardId + ":" + ciphered);
			request.setAttribute("newpwd", newpwd);
			return true;
		} catch (Exception e) {
			return false;
		}
	}
	
	private boolean oldPwd(ActionMapping mapping, ActionForm form, HttpServletRequest request,String cardId){
		//HttpSession session = request.getSession();
		//String cardId = (String)session.getAttribute("cardid");
		String pwd = request.getParameter("pwd")==null?"":request.getParameter("pwd");
		
		DB2CardDAO carddao = new DB2CardDAO();
		try{
		  String ciphered = Util.DESEnc(pwd);
		  CardDTO card = carddao.getCardInfo(cardId);
		  if(ciphered.equals(card.getPassword())){
			  return true;
		  }
		  return false;
		}catch(Exception e){
			return false;
		}
		
	}
	
}
