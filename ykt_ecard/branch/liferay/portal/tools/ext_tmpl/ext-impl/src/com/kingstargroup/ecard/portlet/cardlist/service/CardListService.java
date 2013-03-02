package com.kingstargroup.ecard.portlet.cardlist.service;

import java.io.IOException;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.information.EcardInformation;

public interface CardListService {

	/**
	 * Description:增加一条卡名单
	 * 
	 * @param title
	 * @param content
	 * @param attachments
	 * @param type
	 * @param creater
	 * @return
	 * @throws IOException
	 * @throws PortalException
	 *             Modify History:
	 */
	public EcardInformation add(String title, String content,
			String attachments, String type, String creater)
			throws IOException, PortalException;

	/**
	 * Description:更新指定卡名单
	 * 
	 * @param id
	 * @param title
	 * @param content
	 * @param attachments
	 * @throws IOException
	 * @throws PortalException
	 *             Modify History:
	 */
	public void updateInfoById(String id, String title, String content,
			String attachments) throws IOException, PortalException;

	/**
	 * Description:根据信息ID得到对应的信息对象
	 * 
	 * @param id
	 *            传入的信息ID
	 * @return Modify History:
	 */
	public EcardInformation getInfoById(String id) throws PortalException;

}
