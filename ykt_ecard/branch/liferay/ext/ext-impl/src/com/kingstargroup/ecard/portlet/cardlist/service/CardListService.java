package com.kingstargroup.ecard.portlet.cardlist.service;

import java.io.IOException;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.information.EcardInformation;

public interface CardListService {

	/**
	 * Description:����һ��������
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
	 * Description:����ָ��������
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
	 * Description:������ϢID�õ���Ӧ����Ϣ����
	 * 
	 * @param id
	 *            �������ϢID
	 * @return Modify History:
	 */
	public EcardInformation getInfoById(String id) throws PortalException;

}
