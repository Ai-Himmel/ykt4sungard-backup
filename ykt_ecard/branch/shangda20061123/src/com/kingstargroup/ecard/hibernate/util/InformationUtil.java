/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import javax.servlet.http.HttpServletRequest;

import org.hibernate.Transaction;


import com.kingstargroup.ecard.common.BasicUtil;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.information.EcardInformation;
import com.kingstargroup.ecard.hibernate.information.InformationPersistence;
import com.kingstargroup.ecard.hibernate.infotype.InfoType;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.util.StringUtil;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.
 * File name: InformationUtil.java
 * Description: ����һ����Ϣ���ݵĹ�����
 * Modify History: 
 * ��������   ������   ����ʱ��     ��������
 * ===================================
 *  ����    Xiao Qi  2005-9-5  
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class InformationUtil extends BasicUtil {

	
	/**
	 * Description:������ϴ��ļ�����Ϣ
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
		return add(title, content, attachments, type, creater, null, null, 0);
	}
	
	/**
	 * Description:�����Ϣ
	 * @param title ��Ϣ����
	 * @param content ��Ϣ����
	 * @param attachments ��Ϣ��������,�ָ��ϴ��ļ���ID
	 * @param type ��Ϣ����0-����֪ͨ 1-�ƶȹ��� 2-�ĵ����� 3-�豸�ֲ�ͼ 4-FAQ 5-�쿨���� 6-ʧ������ 7-����ָ�� 8-��ʧ��֪
	 * @param creater ������Ϣ�˵�ID
	 * @param req �û����ϴ�Action����
	 * @param uploadFieldNames �ϴ��ļ���������
	 * @param uploadType �ϴ����ļ�����,0-�ĵ�,1-ͼƬ
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static EcardInformation add(String title, 
									String content, 
									String attachments, 
									String type, 
									String creater, 
									HttpServletRequest req, 
									String[] uploadFieldNames, 
									int uploadType) 
						throws IOException, PortalException {
		InformationPersistence persistence = (InformationPersistence) getPersistence(InformationPersistence.class.getName());		
		EcardInformation info = new EcardInformation();
		info.setInfoTitle(title);
		info.setInfoContent(content);		
		info.setInfoType(type);
		info.setCreateDate(new Date());
		info.setCreater(creater);		
		Transaction t = beginTransaction();
		try {			
			//����д��ϴ����ļ�
			if (req != null) {
				attachments = UploadFileUtil.upload(req, uploadFieldNames, uploadType);
			}
			info.setAttachments(attachments);
			persistence.add(info);
			t.commit();			
		} catch (PortalException pe) {
			t.rollback();
			throw pe;
		}  catch (IOException ioe) {
			t.rollback();
			throw ioe;
		} finally {
			closeSession();
		}
		return info;
		
	}
	
	/**
	 * Description:������ϢID�õ���Ӧ����Ϣ����
	 * @param id �������ϢID
	 * @return
	 * Modify History:
	 */
	public static EcardInformation getInfoById(String id) throws PortalException {
		EcardInformation info = null;
		InformationPersistence persistence = (InformationPersistence) getPersistence(InformationPersistence.class.getName());
		Transaction t = beginTransaction();		
		try {
			info = persistence.getInfoById(id);
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
		return info;
	}
	
	public static void updateInfoById(String id, 
			String title, 
			String content, 
			String attachments) 
			throws IOException,PortalException {
		updateInfoById(id, title, content, attachments, null, null, EcardConstants.DOCUMENT_TYPE);
	}
	
	/**
	 * Description:
	 * @param id Ҫ���µ���ϢID
	 * @param title Ҫ���µ���Ϣ����
	 * @param content Ҫ���µ���Ϣ����
	 * @param attachments Ҫ���µ���Ϣ����ID
	 * @param req �û��ϴ��ļ���Action����
	 * @param uploadFieldNames �ϴ��ļ���������
	 * @param uploadType �ϴ�����
	 * @throws PortalException
	 * Modify History:
	 */
	public static void updateInfoById(String id, 
										String title, 
										String content, 
										String attachments, 
										HttpServletRequest req, 
										String[] uploadFieldNames, 
										int uploadType) 
					throws IOException, PortalException {		
		InformationPersistence persistence = (InformationPersistence) getPersistence(InformationPersistence.class.getName());
		Transaction t = beginTransaction();
		EcardInformation info = persistence.getInfoById(id);
		info.setInfoTitle(title);
		info.setInfoContent(content);
		info.setCreateDate(new Date());
		info.setAttachments(attachments);		
		try {
			if (req != null) {			
					UploadFileUtil.updateUpload(req, uploadFieldNames, uploadType, StringUtil.split(attachments));
			}
			persistence.update(info);
			t.commit();
		} catch (PortalException pe) {
			t.rollback();
			throw pe;
		}  catch (IOException ioe) {
			t.rollback();
			throw ioe;
		} finally {
			closeSession();
		}
	}
	
	public static ResultPage list(String infoType) throws PortalException {
		return list(0, infoType);
	}
	
	public static ResultPage list(int page, String infoType) throws PortalException {
		return list(page, infoType, EcardConstants.MAX_RESULT_SIZE);
	}
	
	/**
	 * Description:����Ҫ�����ҳ��ҳ��¼������Ϣ���Ͳ�ѯ��Ҫ����Ϣ����?
	 * @param page ҳ��?
	 * @param size һҳ��Ҫ�����ļ�¼��
	 * @param infoType Ҫȡ�õ���Ϣ����
	 * @throws PortalException
	 * @return
	 * Modify History:
	 */
	public static ResultPage list(int page, String infoType, int size) throws PortalException {
		return search(null, null, infoType, page, size);
	}
	
	/**
	 * Description:�����û��ṩ�Ĳ�ѯ���ѯ�������
	 * @param title ��ѯ����
	 * @param content ��ѯ����
	 * @param infoType ��ѯ��Ϣ����
	 * @param page ��Ҫ��ѯ��ҳ
	 * @throws PortalException
	 * @return
	 * Modify History:
	 */
	public static ResultPage search(String title, String content, String infoType, int page) throws PortalException {
		return search(title, content, infoType, page, EcardConstants.LIST_MORE_SIZE);
	}
	
	/**
	 * Description:�����û��ṩ�Ĳ�ѯ���ѯ�������
	 * @param title ��ѯ����
	 * @param content ��ѯ����
	 * @param infoType ��ѯ��Ϣ����
	 * @param page ��Ҫ��ѯ��ҳ
	 * @param size ָ��һҳ���ض��ټ�¼
	 * @throws PortalException
	 * @return
	 * Modify History:
	 */
	public static ResultPage search(String title, String content, String infoType, int page, int size) throws PortalException {
		InformationPersistence persistence = (InformationPersistence) getPersistence(InformationPersistence.class.getName());
		List subTypes = InfoTypeUtil.getChildList(String.valueOf(infoType)).getList();
		List typeIds = new ArrayList();
		for (int i = 0; i < subTypes.size(); i++ ) {
			InfoType type = (InfoType) subTypes.get(i);
			typeIds.add(type.getInfoType());
		}
		typeIds.add(infoType);
		Transaction t = beginTransaction();
		ResultPage result = null;
		try {
			result = persistence.search(title, content, typeIds, page, size);
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
		return result;
	}
	
	public static List search(String title) throws PortalException {
		InformationPersistence persistence = (InformationPersistence) getPersistence(InformationPersistence.class.getName());
		List results = null;
		try {
			results = persistence.search(title);
		} catch (DBSystemException e) {
			throw e;
		} finally {
			closeSession();
		}
		return results;
	}
	
	/**
	 * Description:���ݴ���Ҫɾ����ID����ɾ����Ӧ������
	 * @param ids Ҫɾ����ID����
	 * @throws PortalException
	 * Modify History:
	 */
	public static boolean deleteInfos(String[] ids) throws PortalException {
		InformationPersistence persistence = (InformationPersistence) getPersistence(InformationPersistence.class.getName());
		Transaction t = beginTransaction();
		boolean result = false;
		try {
			List delAttachIds = new ArrayList();
			for (int i = 0; i < ids.length; i++) {
				EcardInformation info = persistence.getInfoById(ids[i]);
				String[] tmpAttachId = StringUtil.split(info.getAttachments(), EcardConstants.DELIMITER);
				if (tmpAttachId.length != 0) {
					delAttachIds.add(tmpAttachId[0]);
				}
			}
			UploadFileUtil.deleteFile((String[]) delAttachIds.toArray(new String[delAttachIds.size()]));
			result = persistence.deleteInfosByIds(ids);
			t.commit();
		} catch (Exception e) {
			t.rollback();
			throw new PortalException(e);
		} finally {
			closeSession();
		}
		return result;
	}	

}
