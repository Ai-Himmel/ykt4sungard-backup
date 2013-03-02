package com.kingstargroup.ecard.portlet.cardlist.service;

import java.io.IOException;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.information.EcardInformation;

public class CardListServiceUtil {
	
	/**
	 * Description:����һ��������
	 * @param title
	 * @param content
	 * @param attachments
	 * @param type
	 * @param creater
	 * @return
	 * @throws IOException
	 * @throws PortalException
	 * Modify History:
	 */
	public static EcardInformation add(String title, 
			String content, 
			String attachments, 
			String type, 
			String creater)
	throws IOException, PortalException {		
		CardListService cardListService = CardListServiceFactory.getService();
		return cardListService.add(title, content, attachments, type, creater);
	}
	
	/**
	 * Description:����ָ��������
	 * @param id
	 * @param title
	 * @param content
	 * @param attachments
	 * @throws IOException
	 * @throws PortalException
	 * Modify History:
	 */
	public static void updateInfoById(String id, 
			String title, 
			String content, 
			String attachments) 
			throws IOException,PortalException {		
		CardListService cardListService = CardListServiceFactory.getService();
		cardListService.updateInfoById(id, title, content, attachments);
	}
	
	/**
	 * Description:������ϢID�õ���Ӧ����Ϣ����
	 * @param id �������ϢID
	 * @return
	 * Modify History:
	 */
	public static EcardInformation getInfoById(String id) throws PortalException {
		CardListService cardListService = CardListServiceFactory.getService();
		return cardListService.getInfoById(id);
		
	}
	

}
