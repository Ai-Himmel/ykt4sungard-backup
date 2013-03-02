package com.kingstargroup.ecard.portlet.cardlist.service;

import java.io.IOException;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.information.EcardInformation;

public class CardListServiceUtil {
	
	/**
	 * Description:增加一条卡名单
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
	 * Description:更新指定卡名单
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
	 * Description:根据信息ID得到对应的信息对象
	 * @param id 传入的信息ID
	 * @return
	 * Modify History:
	 */
	public static EcardInformation getInfoById(String id) throws PortalException {
		CardListService cardListService = CardListServiceFactory.getService();
		return cardListService.getInfoById(id);
		
	}
	

}
