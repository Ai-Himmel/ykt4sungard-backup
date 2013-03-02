package com.kingstargroup.ecard.portlet.shop.action;

import java.util.Locale;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.liferay.portal.kernel.util.DateUtil;
import com.liferay.portal.struts.PortletAction;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: ViewRuleAction.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型 操作人 操作时间 操作内容<br>
 * ===================================<br>
 * 创建 Xiao Qi 2005-9-21 <br>
 * 
 * @author Xiao Qi
 * @version
 * @since 1.0
 */
public class ViewShopPosDinnerReportAction extends PortletAction {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest req, HttpServletResponse res) throws Exception {
		String datetime = DateUtil.getCurrentDate("yyyy/MM/dd", Locale.CHINA);
		datetime = com.kingstargroup.ecard.util.DateUtil.getOtherDate(datetime,
				"yyyy/MM/dd", -1);
		req.setAttribute("shopposdinnerreport_begindate", datetime);
		req.setAttribute("shopposdinnerreport_enddate", datetime);
		return mapping.findForward("portlet.shopposdinnerreport.view");

	}
}
