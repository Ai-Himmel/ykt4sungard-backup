package com.kingstargroup.ecard.portlet.losecard.action;

import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;

import com.kingstargroup.ecard.hibernate.losecard.TLosscardshop;
import com.kingstargroup.ecard.portlet.card.service.CardServiceUtil;
import com.kingstargroup.ecard.portlet.losecard.service.LoseCardServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.model.User;
import com.liferay.portal.service.UserServiceUtil;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.util.servlet.SessionErrors;

public class ViewRegAction extends Action {

	/**
	 * ��ʧ������
	 * pagesign,1 ��ҳ�棬2������3����
	 */
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		DynaActionForm reginfo = (DynaActionForm)form;
		String shopCode = null;
		//String shopName = null;
		try{
			long userId = PortalUtil.getUserId(request);
			if (userId==0){
				SessionErrors.add(request, EcardConstants.LOSECARD_NOLOGIN);
				return mapping.findForward("portlet.losecard.reg");
			}
			
			User user = null;
			user = UserServiceUtil.getUserById(userId);
			shopCode = user.getScreenName();
		}catch (Exception e){
			request.setAttribute(PageContext.EXCEPTION, e);
			return mapping.findForward(ActionConstants.COMMON_ERROR);
		}
		TLosscardshop lossCardShop = null;
		lossCardShop = LoseCardServiceUtil.getInfoByShopCode(shopCode); 
		//request.setAttribute("lossCardShop", lossCardShop);
		request.setAttribute("regDate", DateUtil.getNow("yyyyMMdd"));
		request.setAttribute("getCardPlace", lossCardShop.getGetcardplace());
		request.setAttribute("tel", lossCardShop.getTel());
		request.setAttribute("addr", lossCardShop.getAddr());
		
		String pagesign;
		try{
			pagesign = reginfo.getString("pagesign");
		}catch(Exception e){
			pagesign = "2";
		}
				
		if (("2".equals(pagesign))||("3".equals(pagesign))){
			String cardPhyId = reginfo.getString("cardphyid");
			String readPhyId = reginfo.getString("readPhyId");
			String hexcardno = "";
			if ("2".equals(pagesign)){
				hexcardno = Integer.toHexString(Integer.parseInt(readPhyId)).toUpperCase();
			}else{
				hexcardno = cardPhyId;
			}
			String getCardPlace = reginfo.getString("getcardplace");
			String tel = reginfo.getString("tel");
			String addr = reginfo.getString("addr");
			String regDate= reginfo.getString("regdate");
			Map  stuempInfo= LoseCardServiceUtil.getStuempInfo(hexcardno);
			/*
			if (stuempInfo==null){
				SessionErrors.add(request, EcardConstants.LOSECARD_NOCARD);
				return mapping.findForward("portlet.losecard.reg.view");
			}
			*/
			request.setAttribute("stuempInfo", stuempInfo);
			request.setAttribute("getCardPlace", getCardPlace);
			request.setAttribute("tel", tel);
			request.setAttribute("addr", addr);
			request.setAttribute("regDate", regDate);
			if ("3".equals(pagesign)){
				//�жϿ�״̬������Ѿ�ע��������ʾ�������ʧ��������Ϣ
				String cardStatus = LoseCardServiceUtil.cardStatusString(cardPhyId);
				if ("2".equals(cardStatus)){
					SessionErrors.add(request, EcardConstants.CARD_DESTORY);
				}else{
					String cardId = reginfo.getString("cardno");
					//��ʧ
					CardServiceUtil.processLostCard("", cardId); 
					//������Ϣ
					//����Ѿ����ڣ�ֻ�ܸ����̻������Ϣ�����Բ�ͬ���̻�����ʱ��ʾ�ÿ��Ѿ�����
					if (LoseCardServiceUtil.getLossCardBy(shopCode, new Integer(cardId))!=null){
						SessionErrors.add(request, EcardConstants.LOSECARD_RECORDEXIST);
						return mapping.findForward("portlet.losecard.reg");
					}
					LoseCardServiceUtil.saveLossCardInfo(shopCode, Integer.parseInt(cardId), hexcardno, getCardPlace, addr, tel);
					SessionErrors.add(request, EcardConstants.LOSECARD_SAVESUCC);
				}
			}
			return mapping.findForward("portlet.losecard.reg");
		}
		return mapping.findForward("portlet.losecard.reg");

	}
}