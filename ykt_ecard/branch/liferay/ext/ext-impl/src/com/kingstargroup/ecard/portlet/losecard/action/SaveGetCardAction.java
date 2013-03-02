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
	 * ��ʧ������,�쿨����
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
		//ȡ��������
		String cardPhyId = LoseCardServiceUtil.getCardPhyId(new Integer(cardNo));
		String hexcardno = Integer.toHexString(Integer.parseInt(readPhyId)).toUpperCase();
		List cardType = LoseCardServiceUtil.getCardType();
		request.setAttribute("cardType", cardType);
		if (!cardPhyId.equals(hexcardno)){
			//��ʾ����ͬһ�ſ���������Ƭ������ȡ
			SessionErrors.add(request, EcardConstants.LOSECARD_NOTSAMECARD);
			return mapping.findForward("portlet.losecard.getcard.get");
		}

		//�쿨����������֤���ش򿪣��������֤�������֤ͨ��������ʾ����֤ͨ�����쿨��������Ϣ
		String idType = request.getParameter("cardType").toString();
		String idNo = request.getParameter("idNo").toString();
		String reMark = request.getParameter("reMark").toString();
		Map idInfo = LoseCardServiceUtil.getIdInfo(new Integer(cardNo));
		int sign= Integer.parseInt(KSConfiguration.getInstance().getProperty("valid_sign", "0"));
		if (sign==1){
			//��֤ͨ��������ʾ��Ϣ
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
