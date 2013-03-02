package com.kingstargroup.fdykt.cfgfee;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionError;
import org.apache.struts.action.ActionErrors;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessages;

import com.kingstar.itemconfig.Configitem;
import com.kingstargroup.fdykt.ConfigItemInit;

public class CfgfeePutinAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(CfgfeePutinAction.class);

	/**
	 * Logger for this class
	 */

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		ActionErrors errors = new ActionErrors();
		String gid = request.getParameter("gid");

		if (null == gid) {
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
					"back.error", "没有选择收费科目"));
			saveErrors(request, errors);
			return mapping.findForward("failure");
		}

		// 找出配置
		Configitem cfgitem = ConfigItemInit.getConfigItembyGid(gid);
		if (cfgitem != null) {
			request.setAttribute("gid", gid);
			request.setAttribute("cfgitem", cfgitem);
			return mapping.findForward("success");
		} else {
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
					"back.error", "没有找到相应的配置信息"));
			saveErrors(request, errors);
			return mapping.findForward("failure");
		}
	}

}
