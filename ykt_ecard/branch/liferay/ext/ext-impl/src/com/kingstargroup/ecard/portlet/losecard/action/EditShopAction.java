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
	 * ��ʧ�������޸ĵ�½�̻���Ϣ
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
		//�����̻���¼�Ų��ұ����Ƿ���ڸ��̻�������������ӣ���������ȡ�̻���ص���Ϣ
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
