package com.kingstargroup.fdykt.cfgfee;

import java.sql.SQLException;
import java.util.HashMap;

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
import org.apache.struts.action.ActionMessages;

import com.kingstar.itemconfig.ConfigProcess;
import com.kingstar.itemconfig.ConfigPropertyvalue;
import com.kingstar.itemconfig.Configitem;
import com.kingstargroup.BusinessProcessor;
import com.kingstargroup.BusinessProcessorImpl;
import com.kingstargroup.fdykt.ConfigItemInit;
import com.kingstargroup.fdykt.Util;
import com.kingstargroup.fdykt.dao.DB2AccountDAO;
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.DB2CustomerDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;
import com.kingstargroup.fdykt.dto.CustomerDTO;

public class CfgfeeThirdCheckAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(CfgfeeThirdCheckAction.class);

	/**
	 * Logger for this class
	 */

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = doPutin(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			logger
					.error(
							"execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doPutin(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		DB2AccountDAO accdao = new DB2AccountDAO();
		ActionErrors errors = new ActionErrors();
		HttpSession session = request.getSession();
		String cardphyid = request.getParameter("cardphyid");
		String gid = request.getParameter("gid");
		String cardBala = request.getParameter("cardBala");
		String txCnt = request.getParameter("txCnt");
		String fee = request.getParameter("fee");
		String password = request.getParameter("password");

		request.setAttribute("cardphyid", cardphyid);
		request.setAttribute("gid", gid);
		request.setAttribute("cfgitem", ConfigItemInit.getConfigItembyGid(gid));
		request.setAttribute("cardBala", cardBala);
		request.setAttribute("txCnt", txCnt);
		request.setAttribute("fee", fee);
		String reqip = request.getRemoteAddr();
		// reqip = "10.49.188.50";
		int deviceid = -2;
		try {
			deviceid = accdao.getdevidFromip(reqip);
			if (deviceid < 0) {
				errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
						"deviceid.notregister"));
				saveErrors(request, errors);
				return mapping.findForward("failure");
			}
		} catch (Exception e1) {
			logger
					.error(
							"doPutin(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e1); //$NON-NLS-1$

			e1.printStackTrace();
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
					"deviceid.notregister"));
			saveErrors(request, errors);
			return mapping.findForward("failure");
		}

		DB2CardDAO carddao = new DB2CardDAO();
		DB2CustomerDAO custdao = new DB2CustomerDAO();
		CardDTO card = new CardDTO();
		CustomerDTO custdto = new CustomerDTO();
		try {

			String ciphered = Util.DESEnc(password);
			card = carddao.getCardInfoByIdPwd(cardphyid, ciphered);
			if (card == null) {
				errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("errors.password"));
				saveErrors(request, errors);
				return mapping.findForward("failure");
			}
			custdto = custdao.getCustomer(card.getCustid());
		} catch (Exception e) {
			// TODO: handle exception
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
					"back.error", "卡信息读取失败"));
			saveErrors(request, errors);
			return mapping.findForward("failure");
		}

		/**
		 * 处理第三方配置业务
		 * 
		 */

		Configitem cfgitem = ConfigItemInit.getConfigItembyGid(gid);
		ConfigProcess cfgpress = cfgitem.getBusinessProcessor();

		ConfigPropertyvalue[] cfgpvArr = cfgpress.getParamArray();
		HashMap args = new HashMap();
		if (cfgpvArr != null && cfgpvArr.length > 0) {
			for (int i = 0; i < cfgpvArr.length; i++) {
				ConfigPropertyvalue cfgpv = cfgpvArr[i];
				String property = cfgpv.getProperty();
				String value = cfgpv.getValue();
				args.put(property, value);
			}
		}

		String classname = cfgpress.getClassname();
		Class c = null;
		try {
			if (null != classname && !"".equals(classname)) {
				c = Class.forName(classname);
				if (c.newInstance() instanceof BusinessProcessor) {
					BusinessProcessor businessProcessor = (BusinessProcessor) c
							.newInstance();
					boolean ret = businessProcessor.checkThirdpart(session,
							custdto.getStuempno(), custdto.getCustname(), fee,
							args);
					if (ret == true) {
						//调用第三方信息返回
						HashMap thirdpartinfo = businessProcessor.getThirdpartInfo(session, custdto.getStuempno(), custdto.getCustname(), fee,
							args);
						request.setAttribute("thirdpartinfo", thirdpartinfo);
						return mapping.findForward("success");
					} else {
						String errmsg = businessProcessor.getProcessMessage(session)==null?"":businessProcessor.getProcessMessage(session);
						errors.add(ActionMessages.GLOBAL_MESSAGE,
								new ActionError("back.error",
										errmsg == null ? "第三方系统未知错误" : errmsg));
						saveErrors(request, errors);
						return mapping.findForward("failure");
					}
				} else {
					BusinessProcessor businessProcessor = new BusinessProcessorImpl();
					boolean ret = businessProcessor.checkThirdpart(session,
							custdto.getStuempno(), custdto.getCustname(), fee,
							args);
					if (ret == true) {
						//调用第三方信息返回
						HashMap thirdpartinfo = businessProcessor.getThirdpartInfo(session, custdto.getStuempno(), custdto.getCustname(), fee,
							args);
						request.setAttribute("thirdpartinfo", thirdpartinfo);
						return mapping.findForward("success");
					} else {
						String errmsg =businessProcessor.getProcessMessage(session)==null?"":businessProcessor.getProcessMessage(session);
						errors.add(ActionMessages.GLOBAL_MESSAGE,
								new ActionError("back.error",
										errmsg == null ? "第三方系统未知错误" : errmsg));
						saveErrors(request, errors);
						return mapping.findForward("failure");
					}

				}
			} else {

				BusinessProcessor businessProcessor = new BusinessProcessorImpl();
				boolean ret = businessProcessor.checkThirdpart(session, custdto
						.getStuempno(), custdto.getCustname(), fee, args);
				if (ret == true) {
					//调用第三方信息返回
					HashMap thirdpartinfo = businessProcessor.getThirdpartInfo(session, custdto.getStuempno(), custdto.getCustname(), fee,
						args);
					request.setAttribute("thirdpartinfo", thirdpartinfo);
					return mapping.findForward("success");
				} else {
					String errmsg = businessProcessor.getProcessMessage(session)==null?"":businessProcessor.getProcessMessage(session);
					errors.add(ActionMessages.GLOBAL_MESSAGE,
							new ActionError("back.error",
									errmsg == null ? "第三方系统未知错误" : errmsg));
					saveErrors(request, errors);
					return mapping.findForward("failure");
				}

			}

		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		} catch (IllegalAccessException e) {
			e.printStackTrace();
		} catch (InstantiationException e) {
			e.printStackTrace();
		}
		errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("back.error",
				"系统配置出错，此功能暂时无法使用"));
		saveErrors(request, errors);
		return mapping.findForward("failure");

	}
}
