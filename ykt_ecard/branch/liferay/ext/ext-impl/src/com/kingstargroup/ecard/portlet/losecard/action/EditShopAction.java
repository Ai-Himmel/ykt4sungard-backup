package com.kingstargroup.ecard.portlet.losecard.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.losecard.TLosscardshop;
import com.kingstargroup.ecard.portlet.losecard.service.LoseCardServiceUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.util.servlet.SessionErrors;

public class EditShopAction extends Action {

	/**
	 * 遗失卡管理，修改登陆商户信息
	 */
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		response.setCharacterEncoding("UTF-8");
		DynaActionForm shopInfoForm = (DynaActionForm)form;
		String shopCode = shopInfoForm.getString("shopCode");
		String shopName = shopInfoForm.getString("shopName");
		String addr = shopInfoForm.getString("addr");
		String tel = shopInfoForm.getString("tel");
		String getCardPlace = shopInfoForm.getString("getCardPlace");
		//根据商户登录号查找表中是否存在该商户，不存在则添加，存在则提取商户相关的信息
		try{
			LoseCardServiceUtil.update(shopCode, shopName, addr, tel, getCardPlace);
			TLosscardshop lossCardShop = LoseCardServiceUtil.getInfoByShopCode(shopCode); 
			request.setAttribute("lossCardShop", lossCardShop);
			SessionErrors.add(request, EcardConstants.EDIT_INFO_SUCCESS);	
		}catch (PortalException pe){
			request.setAttribute(PageContext.EXCEPTION, pe);
			return mapping.findForward(ActionConstants.COMMON_ERROR);
		}
		
		return mapping.findForward("portlet.losecard.shop.view");
	}

}
