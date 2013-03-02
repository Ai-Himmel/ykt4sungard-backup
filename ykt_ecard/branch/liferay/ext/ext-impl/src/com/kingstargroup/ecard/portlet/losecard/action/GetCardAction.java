package com.kingstargroup.ecard.portlet.losecard.action;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.jgroups.protocols.LOSS;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.portlet.losecard.service.LoseCardServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.model.User;
import com.liferay.portal.service.UserServiceUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.util.servlet.SessionErrors;

public class GetCardAction extends Action {

	/**
	 * 遗失卡管理
	 */
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {	
		
		String shopCode = null;
		try{
			long userId = PortalUtil.getUserId(request);
			if (userId==0){
				SessionErrors.add(request, EcardConstants.LOSECARD_NOLOGIN);
				return mapping.findForward("portlet.losecard.shop.view");
			}
			
			User user = null;
			user = UserServiceUtil.getUserById(userId);
			shopCode = user.getScreenName();
		}catch (Exception e){
			throw new PortalException(e);
		}
		List cardType = LoseCardServiceUtil.getCardType();
		request.setAttribute("cardType", cardType);
		String cardNo = request.getParameter("cardno").toString();
		//根据卡号和商户号查找是否有正常状态的卡，没有找到这返回错误信息
		int haveCard = LoseCardServiceUtil.haveCard(shopCode, new Integer(cardNo));
		if (haveCard==0){
			SessionErrors.add(request, EcardConstants.LOSECARD_CARDSTATUSERROR);
			String endDate = DateUtil.getNow("yyyyMMdd");
			String beginDate = DateUtil.getOtherDate(endDate,-30);
			request.setAttribute("beginDate", beginDate);
			request.setAttribute("endDate", endDate);
			return mapping.findForward("portlet.losecard.getcard.view");
		}
		request.setAttribute("cardNo", cardNo);
		return mapping.findForward("portlet.losecard.getcard.get");
	}

}
