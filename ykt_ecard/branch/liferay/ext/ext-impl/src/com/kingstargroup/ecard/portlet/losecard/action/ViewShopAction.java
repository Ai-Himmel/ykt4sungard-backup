package com.kingstargroup.ecard.portlet.losecard.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.losecard.TLosscardshop;
import com.kingstargroup.ecard.portlet.losecard.service.LoseCardServiceUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.model.User;
import com.liferay.portal.service.UserServiceUtil;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.util.servlet.SessionErrors;

public class ViewShopAction extends Action {

	/**
	 * 遗失卡管理，修改登陆商户信息
	 */
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String shopCode = null;
		String shopName = null;
		try{
			long userId = PortalUtil.getUserId(request);
			if (userId==0){
				SessionErrors.add(request, EcardConstants.LOSECARD_NOLOGIN);
				return mapping.findForward("portlet.losecard.shop.view");
			}
			
			User user = null;
			user = UserServiceUtil.getUserById(userId);
			shopCode = user.getScreenName();
			shopName = user.getFirstName();
		}catch (Exception e){
			throw new PortalException(e);
		}
		//根据商户登录号查找表中是否存在该商户，不存在则添加，存在则提取商户相关的信息
		TLosscardshop lossCardShop = null;
		try{
			lossCardShop = LoseCardServiceUtil.getInfoByShopCode(shopCode); 
			if (lossCardShop==null){
				//添加信息
				LoseCardServiceUtil.add(shopCode,shopName);
				lossCardShop = LoseCardServiceUtil.getInfoByShopCode(shopCode); 
			}
			request.setAttribute("lossCardShop", lossCardShop);
			
		}catch (PortalException pe){
			request.setAttribute(PageContext.EXCEPTION, pe);
			return mapping.findForward(ActionConstants.COMMON_ERROR);
		}
		//request.setAttribute("mytest", );
		return mapping.findForward("portlet.losecard.shop.view");
	}

}
