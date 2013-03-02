package com.kingstargroup.ecard.portlet.losecard.action;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.portlet.losecard.service.LoseCardServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;

public class ViewQueryAction extends Action {

	/**
	 * “≈ ßø®π‹¿Ì
	 */
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String endDate = DateUtil.getNow("yyyyMMdd");
		String beginDate = DateUtil.getOtherDate(endDate,-30);
		request.setAttribute("beginDate", beginDate);
		request.setAttribute("endDate", endDate);
		List lossCardStatus = LoseCardServiceUtil.getDictListBy(160);
		request.setAttribute("lossCardStatus", lossCardStatus);
		request.setAttribute("custName", "");
		request.setAttribute("stuempNO", "");
		//request.setAttribute("lossCardStatus", lossCardStatus);
		request.setAttribute("cardShowNo", "");
		return mapping.findForward("portlet.losecard.query.view");
	}

}
