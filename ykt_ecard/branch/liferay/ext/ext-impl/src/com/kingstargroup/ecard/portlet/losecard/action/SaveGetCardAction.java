package com.kingstargroup.ecard.portlet.losecard.action;

import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.KSConfiguration;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.portlet.losecard.service.LoseCardServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.model.User;
import com.liferay.portal.service.UserServiceUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.util.servlet.SessionErrors;

public class SaveGetCardAction extends Action {

	/**
	 * 遗失卡管理,领卡保存
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
		String cardNo = request.getParameter("cardNo").toString();
		request.setAttribute("cardNo", cardNo);
		String readPhyId = request.getParameter("cardPhyId").toString();
		//取得物理卡号
		String cardPhyId = LoseCardServiceUtil.getCardPhyId(new Integer(cardNo));
		String hexcardno = Integer.toHexString(Integer.parseInt(readPhyId)).toUpperCase();
		List cardType = LoseCardServiceUtil.getCardType();
		request.setAttribute("cardType", cardType);
		if (!cardPhyId.equals(hexcardno)){
			//提示不是同一张卡，更换卡片重新领取
			SessionErrors.add(request, EcardConstants.LOSECARD_NOTSAMECARD);
			return mapping.findForward("portlet.losecard.getcard.get");
		}

		//领卡，如果身份验证开关打开，则进行验证，如果验证通不过，提示，验证通过后领卡，更新信息
		String idType = request.getParameter("cardType").toString();
		String idNo = request.getParameter("idNo").toString();
		String reMark = request.getParameter("reMark").toString();
		Map idInfo = LoseCardServiceUtil.getIdInfo(new Integer(cardNo));
		int sign= Integer.parseInt(KSConfiguration.getInstance().getProperty("valid_sign", "0"));
		if (sign==1){
			//验证通不过，提示信息
			if (idInfo!=null){
				String dbIdNo = idInfo.get("idno").toString();
				if (!idNo.equals(dbIdNo)){
					SessionErrors.add(request, EcardConstants.LOSECARD_INFONOTSAME);
					return mapping.findForward("portlet.losecard.getcard.get");
				}
			}else{
				SessionErrors.add(request, EcardConstants.LOSECARD_INFONOTSAME);
				return mapping.findForward("portlet.losecard.getcard.get");
			}
		}
		LoseCardServiceUtil.updateLossCardInfo(shopCode, new Integer(cardNo), idType, idNo, reMark);		
		String endDate = DateUtil.getNow("yyyyMMdd");
		String beginDate = DateUtil.getOtherDate(endDate,-30);
		request.setAttribute("beginDate", beginDate);
		request.setAttribute("endDate", endDate);
		SessionErrors.add(request, EcardConstants.LOSECARD_GETCARDSUCC);
		return mapping.findForward("portlet.losecard.getcard.view");
	}

}
