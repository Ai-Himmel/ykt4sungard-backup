package com.kingstargroup.ecard.portlet.losecard.service;

import java.util.List;
import java.util.Map;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.losecard.TLosscardshop;

public class LoseCardServiceUtil {

	public static TLosscardshop getInfoByShopCode(String shopCode)throws PortalException {
		LoseCardService loseCardService = LoseCardServiceFactory.getService();
		return loseCardService.getInfoByShopCode(shopCode);
	}
	
	public static void add(String shopCode,String shopName)throws PortalException{
		LoseCardService loseCardService = LoseCardServiceFactory.getService();
		loseCardService.add(shopCode,shopName);
	}
	
	public static boolean update(String shopCode, String shopName, String addr,
			String tel, String getCardPlace)throws PortalException{
		LoseCardService loseCardService = LoseCardServiceFactory.getService();
		return loseCardService.update(shopCode, shopName, addr, tel, getCardPlace);
	}

	public static Map getStuempInfo(String cardPhyId)throws PortalException{
		LoseCardService loseCardService = LoseCardServiceFactory.getService();
		return loseCardService.getStuempInfo(cardPhyId);
	}

	public static String cardStatusString (String cardPhyId)throws PortalException{
		LoseCardService loseCardService = LoseCardServiceFactory.getService();
		return loseCardService.cardStatus(cardPhyId);
	}
	
	public static void saveLossCardInfo(String shopcode,int cardno,String cardphyid,String getcardplace,
			String addr,String tel) throws PortalException {
		LoseCardService loseCardService = LoseCardServiceFactory.getService();
		loseCardService.addLossCardInfo(shopcode, cardno, cardphyid, getcardplace, addr, tel);
	}

	public static List getLossCardBy(String shopCode,Integer cardNo) throws PortalException {
		LoseCardService loseCardService = LoseCardServiceFactory.getService();
		return loseCardService.getLossCardBy(shopCode, cardNo);
	}
	
	public static List getLossCardInfo(String shopCode, String bDate, String eDate,
			Integer cardNo, String showCardNo, String StuempNo, String custName,String cardStatus)
			throws PortalException {
		LoseCardService loseCardService = LoseCardServiceFactory.getService();
		return loseCardService.getLossCardInfo(shopCode, bDate, eDate, cardNo, showCardNo, StuempNo, custName,cardStatus);
	}
	
	public static List getCardType()throws PortalException {
		LoseCardService loseCardService = LoseCardServiceFactory.getService();
		return loseCardService.getCardType();
	}
	
	public static String getCardPhyId(Integer cardNo) throws PortalException {
		LoseCardService loseCardService = LoseCardServiceFactory.getService();
		return loseCardService.getCardPhyId(cardNo);
	}
	
	//���ݿ���ȡ�������Ϣ
	public static Map getIdInfo(Integer cardNo) throws PortalException {
		LoseCardService loseCardService = LoseCardServiceFactory.getService();
		return loseCardService.getIdNo(cardNo);
	}
	
	//�Ƿ��������״̬�Ŀ�
	public static int haveCard(String shopCode, Integer cardNo) throws PortalException {
		LoseCardService loseCardService = LoseCardServiceFactory.getService();
		return loseCardService.haveCard(shopCode, cardNo);
	}
	
	//������ʧ����Ϣ
	public static void updateLossCardInfo(String shopcode,int cardno,String idType,
			String idNo,String reMark) throws PortalException {
		LoseCardService loseCardService = LoseCardServiceFactory.getService();
		loseCardService.updateLossCardInfo(shopcode, cardno, idType, idNo, reMark);
	}
	
	//�����ֵ��ȡ���ֵ��б�
	public static List getDictListBy(Integer dictNo) throws PortalException {
		LoseCardService loseCardService = LoseCardServiceFactory.getService();
		return loseCardService.getDictListBy(dictNo);
	}
	
	//ͳ����ʧ����Ϣ
	public static List getLossStatList(String beginDate, String endDate,
			String shopCode) throws PortalException {
		LoseCardService loseCardService = LoseCardServiceFactory.getService();
		return loseCardService.getLossStatList(beginDate, endDate, shopCode);
	}
	
	//���ݿ���ȡ��ȡ���ĵ�ַ���绰����Ϣ
	public static Map getGetCardInfo(String cardNo) throws PortalException {
		LoseCardService loseCardService = LoseCardServiceFactory.getService();
		return loseCardService.getGetCardInfo(cardNo);
	}
}
