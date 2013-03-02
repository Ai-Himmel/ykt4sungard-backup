package com.kingstargroup.fdykt.trade;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionError;
import org.apache.struts.action.ActionErrors;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.KSConstant;
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.DB2SysParaDAO;
import com.kingstargroup.fdykt.dao.DB2TradeSerialDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.BlackSheetDTO;
import com.kingstargroup.fdykt.dto.CardDTO;
import com.kingstargroup.fdykt.dto.MesListDTO;
import com.kingstargroup.fdykt.dto.SysParaDTO;
import com.kingstargroup.fdykt.dto.TradeSerialDTO;

public class CancelLossAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(CancelLossAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		ActionForward forward = mapping.findForward("error");
		try {
		DB2CardDAO carddao = new DB2CardDAO();
		String cardno = request.getParameter("cardno");
		request.setAttribute("cardno",cardno);
		CardDTO card = carddao.getCardInfoByCardNo(cardno);
		if (card == null) {
			return mapping.findForward("msg");
		}
		String cardId = card.getCardId();
		String cutid = card.getCosumerId();
		
		
		KSDaoSessionFactory.createSession();
		
	
			if (doUnloss(mapping, request,cardId,cutid)) {
				forward = mapping.findForward("success");
				KSDaoSessionFactory.commit();
			} else {
				request.setAttribute("msg","��ҿ�ʧ��");
				forward = mapping.findForward("failure");
				KSDaoSessionFactory.rollback();
			}
		} catch (Exception e) {
			e.printStackTrace();
			logger.error("����ʧ��:��ҿ�ʧ��");
		}
		return forward;
	}

	private boolean doUnloss(ActionMapping mapping, HttpServletRequest request,String  cardid,String cutid) {
		DB2CardDAO carddao = new DB2CardDAO();
		CardDTO card = new CardDTO();
		DB2SysParaDAO sysParadao = new DB2SysParaDAO();
	
		// ȡ��ϵͳ����ʱ��
		try {
			String sysdate = new DB2SysParaDAO().getDBDateTime();
			String systime = sysdate.substring(8);
			sysdate = sysdate.substring(0, 8);
			card = carddao.getCardInfo(cardid);
			String state = card.getStateId();
			
			SysParaDTO sysPara = sysParadao.getSysPara(KSConstant.DICT_MAINKEY);//�豸��Ȩ��Կ
			request.setAttribute("paramKey",sysPara.getValue());
			
			if (state == null || state.length() != 4)
				return false;
			char[] stateAry = state.toCharArray();
			if (KSConstant.BOOLEAN_TRUE == stateAry[KSConstant.CARDSTAT_TYPE_FREEZE]) {
				ActionErrors errors = new ActionErrors();
				errors.add("100561", new ActionError("errors.100561"));
				if (!errors.isEmpty()) {
					saveErrors(request, errors);
				}
				return false;
			}
			// ��鿨״̬�Ƿ�Ϊ��ʧ
			int flag = carddao.isCancel(cutid, cardid);
			if (flag != 0) {
				// �����ظ���� modify by ���� 2005-05-15
				/*
				 * if (flag == 100559) { ActionErrors errors = new
				 * ActionErrors(); errors.add("100559", new
				 * ActionError("errors.100559")); if (!errors.isEmpty()) {
				 * saveErrors(request, errors); }
				 * //System.out.println("-------------2-----------"); return
				 * mapping.findForward("failure"); } else
				 */
				if (flag == KSConstant.MAINCARD_UNLOSSED) {
					ActionErrors errors = new ActionErrors();
					errors.add("100560", new ActionError("errors.100560"));
					if (!errors.isEmpty()) {
						saveErrors(request, errors);
					}
					//logger.info("���п�δ��ʧ,����Ҫ�ȹ�ʧ,custno[" + cutid + "]");
					return false;
				}
			}
			// �ظ����Ҫ���´�����			
			// ����ÿ��ű�����,���ʧʱ�Ժ�����������
			if (KSConstant.BOOLEAN_FALSE == stateAry[KSConstant.CARDSTAT_TYPE_FREEZE]) {
				// ״̬��Ϊ����������Ч״̬,����Ϊ��״̬
				carddao.updateLossState(sysdate, cardid);
				// �޸�ԭ���ĺ�������״̬��־Ϊ��Ч
				// �����������
				BlackSheetDTO blacksheet = new BlackSheetDTO();
				blacksheet.setCardId(cardid);
				blacksheet.setIsAd("1");
				blacksheet.setOperateDate(sysdate);
				blacksheet.setOperateTime(systime);
				blacksheet.setStateId("1");
				blacksheet.setValiddate("501230121212");
				blacksheet.setVolume(sysdate.substring(2, 8) + systime);
				carddao.createBlackSheet(blacksheet);
				// �㲥������
				MesListDTO meslist = new MesListDTO();
				String incontent = "<CARDID>" + cardid + "</CARDID>"
						+ "<VERNUM>" + blacksheet.getVolume() + "</VERNUM>"
						+ "<ADDDELSIGN>" + blacksheet.getIsAd()
						+ "</ADDDELSIGN>";
				meslist.setIncontent(incontent);
				meslist.setFunId("930005");
				meslist.setLevel("1");
				meslist.setEcode("9999");
				meslist.setStateId("1");
				meslist.setIndt(sysdate + systime);
				request.setAttribute("blkversion", blacksheet.getVolume());
				carddao.createMesList(meslist);
				// �޸Ŀ�״̬Ϊ���״̬

				stateAry[KSConstant.CARDSTAT_TYPE_LOST] = KSConstant.BOOLEAN_FALSE;
				carddao.updateCardState(cardid, String.valueOf(stateAry));
				// ׼�����ݲ��뽻����ˮ��
				TradeSerialDTO tradeserial = new TradeSerialDTO();
				tradeserial.setOperate_Date(sysdate);
				tradeserial.setOperate_time(systime);
				tradeserial.setCollect_Date(sysdate);
				tradeserial.setCollect_time(systime);
				tradeserial.setEnterAct_time(systime);
				tradeserial.setSerial_type("930002");
				tradeserial.setSerial_state(9);
				tradeserial.setCustomer_id((new Integer(cutid)).longValue());
				tradeserial.setCard_id((new Integer(cardid)).longValue());
				DB2TradeSerialDAO tradeserialdao = new DB2TradeSerialDAO();
				tradeserialdao.createTradeSerial(tradeserial);
				return true;
			}
			return false;
		} catch (Exception e) {
			logger.error("��ҿ�ʧ��:" + e.getMessage());
			return false;
		}
	}

}
