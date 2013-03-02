package com.kingstargroup.ecard.portlet.information.service;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import javax.servlet.http.HttpServletRequest;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.information.EcardInformation;
import com.kingstargroup.ecard.hibernate.infotype.InfoType;
import com.kingstargroup.ecard.hibernate.util.ResultPage;
import com.kingstargroup.ecard.portlet.document.action.UpLoadForm;
import com.kingstargroup.ecard.portlet.infotype.service.InfoTypeServiceUtil;
import com.kingstargroup.ecard.portlet.uploadfile.service.UploadFileServiceUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.kingstargroup.ecard.util.EcardInformationPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.util.PropsUtil;

public class EcardInformationServiceImpl extends EcardInformationServiceBase {

	private static String cardlistDir = PropsUtil.get("info.cardlist.dir");

	/**
	 * Description:������ϴ��ļ�����Ϣ
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
	public  EcardInformation add(String title, String content,
			String attachments, String type, String creater)
			throws IOException, PortalException {
		return add(title, content, attachments, type, creater, null, null, 0);
	}

	/**
	 * Description:�����Ϣ
	 * 
	 * @param title
	 *            ��Ϣ����
	 * @param content
	 *            ��Ϣ����
	 * @param attachments
	 *            ��Ϣ��������,�ָ��ϴ��ļ���ID
	 * @param type
	 *            ��Ϣ����0-����֪ͨ 1-�ƶȹ��� 2-�ĵ����� 3-�豸�ֲ�ͼ 4-FAQ 5-�쿨���� 6-ʧ������ 7-����ָ��
	 *            8-��ʧ��֪
	 * @param creater
	 *            ������Ϣ�˵�ID
	 * @param req
	 *            �û����ϴ�Action����
	 * @param uploadFieldNames
	 *            �ϴ��ļ���������
	 * @param uploadType
	 *            �ϴ����ļ�����,0-�ĵ�,1-ͼƬ
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public  EcardInformation add(String title, String content,
			String attachments, String type, String creater,
			HttpServletRequest req, String[] uploadFieldNames, int uploadType)
			throws IOException, PortalException {
		EcardInformation info = new EcardInformation();
		info.setInfoTitle(title);
		info.setInfoContent(content);
		info.setInfoType(type);
		info.setCreateDate(new Date());
		info.setCreater(creater);
		try {
			// ����д��ϴ����ļ�
			if (req != null) {
				attachments = UploadFileServiceUtil.upload(req, uploadFieldNames,
						uploadType);
			}
			info.setAttachments(attachments);
			informationPersistence.add(info);
		} catch (PortalException pe) {
			throw pe;
		} catch (IOException ioe) {
			throw ioe;
		}
		return info;

	}
	
	public  EcardInformation add(String title, String content,
			String attachments, String type, String creater,UpLoadForm upLoadForm,int uploadType)
			throws IOException, PortalException {
		EcardInformation info = new EcardInformation();
		info.setInfoTitle(title);
		info.setInfoContent(content);
		info.setInfoType(type);
		info.setCreateDate(new Date());
		info.setCreater(creater);
		try {
			// ����д��ϴ����ļ�
			if (upLoadForm != null) {
				attachments = UploadFileServiceUtil.upload(upLoadForm,uploadType);
			}
			info.setAttachments(attachments);
			informationPersistence.add(info);
		} catch (PortalException pe) {
			throw pe;
		} catch (IOException ioe) {
			throw ioe;
		}
		return info;

	}

	/**
	 * Description:������ϢID�õ���Ӧ����Ϣ����
	 * 
	 * @param id
	 *            �������ϢID
	 * @return Modify History:
	 */
	public  EcardInformation getInfoById(String id)
			throws PortalException {
		EcardInformation info = null;

		try {
			info =informationPersistence.getInfoById(id);
		} catch (DBSystemException e) {
			throw e;
		}
		return info;
	}

	public  void updateInfoById(String id, String title, String content,
			String attachments) throws IOException, PortalException {
		updateInfoById(id, title, content, attachments, null, null,
				EcardConstants.DOCUMENT_TYPE);
	}

	/**
	 * Description:
	 * 
	 * @param id
	 *            Ҫ���µ���ϢID
	 * @param title
	 *            Ҫ���µ���Ϣ����
	 * @param content
	 *            Ҫ���µ���Ϣ����
	 * @param attachments
	 *            Ҫ���µ���Ϣ����ID
	 * @param req
	 *            �û��ϴ��ļ���Action����
	 * @param uploadFieldNames
	 *            �ϴ��ļ���������
	 * @param uploadType
	 *            �ϴ�����
	 * @throws PortalException
	 *             Modify History:
	 */
	public  void updateInfoById(String id, String title, String content,
			String attachments, HttpServletRequest req,
			String[] uploadFieldNames, int uploadType) throws IOException,
			PortalException {
		EcardInformation info = informationPersistence.getInfoById(id);
		info.setInfoTitle(title);
		info.setInfoContent(content);
		info.setCreateDate(new Date());
		info.setAttachments(attachments);
		try {
			if (req != null) {
				UploadFileServiceUtil.updateUpload(req, uploadFieldNames, uploadType,
						com.liferay.portal.kernel.util.StringUtil.split(attachments));
			}
			informationPersistence.update(info);

		} catch (PortalException pe) {

			throw pe;
		} catch (IOException ioe) {
			throw ioe;
		}
	}
	
	public  void updateInfoById(String id, String title, String content,
			String attachments, UpLoadForm upLoadForm, int uploadType) throws IOException,
			PortalException {
		EcardInformation info = informationPersistence.getInfoById(id);
		info.setInfoTitle(title);
		info.setInfoContent(content);
		info.setCreateDate(new Date());
		info.setAttachments(attachments);
		try {
			if (upLoadForm != null) {
				UploadFileServiceUtil.updateUpload(upLoadForm, uploadType,
						com.liferay.portal.kernel.util.StringUtil.split(attachments));
			}
			informationPersistence.update(info);

		} catch (PortalException pe) {

			throw pe;
		} catch (IOException ioe) {
			throw ioe;
		}
	}

	public  ResultPage list(String infoType) throws PortalException {
		return list(0, infoType);
	}

	public  ResultPage list(int page, String infoType)
			throws PortalException {
		return list(page, infoType, EcardConstants.MAX_RESULT_SIZE);
	}

	/**
	 * Description:����Ҫ�����ҳ��ҳ��¼������Ϣ���Ͳ�ѯ��Ҫ����Ϣ����?
	 * 
	 * @param page
	 *            ҳ��?
	 * @param size
	 *            һҳ��Ҫ�����ļ�¼��
	 * @param infoType
	 *            Ҫȡ�õ���Ϣ����
	 * @throws PortalException
	 * @return Modify History:
	 */
	public  ResultPage list(int page, String infoType, int size)
			throws PortalException {
		return search(null, null, infoType, page, size);
	}

	/**
	 * Description:�����û��ṩ�Ĳ�ѯ���ѯ�������
	 * 
	 * @param title
	 *            ��ѯ����
	 * @param content
	 *            ��ѯ����
	 * @param infoType
	 *            ��ѯ��Ϣ����
	 * @param page
	 *            ��Ҫ��ѯ��ҳ
	 * @throws PortalException
	 * @return Modify History:
	 */
	public  ResultPage search(String title, String content,
			String infoType, int page) throws PortalException {
		return search(title, content, infoType, page,
				EcardConstants.LIST_MORE_SIZE);
	}

	/**
	 * Description:�����û��ṩ�Ĳ�ѯ���ѯ�������
	 * 
	 * @param title
	 *            ��ѯ����
	 * @param content
	 *            ��ѯ����
	 * @param infoType
	 *            ��ѯ��Ϣ����
	 * @param page
	 *            ��Ҫ��ѯ��ҳ
	 * @param size
	 *            ָ��һҳ���ض��ټ�¼
	 * @throws PortalException
	 * @return Modify History:
	 */
	public  ResultPage search(String title, String content,
			String infoType, int page, int size) throws PortalException {
		List subTypes = InfoTypeServiceUtil.getChildList(String.valueOf(infoType))
				.getList();
		List typeIds = new ArrayList();
		for (int i = 0; i < subTypes.size(); i++) {
			InfoType type = (InfoType) subTypes.get(i);
			typeIds.add(type.getInfoType());
		}
		typeIds.add(infoType);
		ResultPage result = null;
		try {
			result = informationPersistence.search(title, content, typeIds, page,
					size);
		} catch (DBSystemException e) {
			throw e;
		}
		return result;
	}

	public  List search(String title) throws PortalException {
		List results = null;
		try {
			results = informationPersistence.search(title);
		} catch (DBSystemException e) {
			throw e;
		}
		return results;
	}

	/**
	 * Description:���ݴ���Ҫɾ����ID����ɾ����Ӧ������
	 * 
	 * @param ids
	 *            Ҫɾ����ID����
	 * @throws PortalException
	 *             Modify History:
	 */
	public  boolean deleteInfos(String[] ids) throws PortalException {
		boolean result = false;
		try {
			List delAttachIds = new ArrayList();
			for (int i = 0; i < ids.length; i++) {
				EcardInformation info = informationPersistence.getInfoById(ids[i]);
				String[] tmpAttachId = StringUtil.split(info.getAttachments(),
						EcardConstants.DELIMITER);
				if (tmpAttachId.length != 0) {
					delAttachIds.add(tmpAttachId[0]);
				}
			}
			UploadFileServiceUtil.deleteFile((String[]) delAttachIds
					.toArray(new String[delAttachIds.size()]));
			result = informationPersistence.deleteInfosByIds(ids);
		} catch (Exception e) {
			throw new PortalException(e);
		}
		return result;
	}
	
	
	/**
	 * Description:ɾ��������
	 * @param ids
	 * @throws PortalException
	 * Modify History:
	 */
	public  void deleteInfomations(String[] ids) throws PortalException {
		try {
			for (int i = 0; i < ids.length; i++) {				
				EcardInformation info = informationPersistence.getInfoById(ids[i]);
				File ioFile = new File(cardlistDir + info.getAttachments());
				ioFile.delete();
				EcardInformationPool.remove(ids[i]);//update cache pool
			}
			informationPersistence.deleteInfosByIds(ids);			
		} catch (Exception e) {
			throw new PortalException(e);
		} 
	}

}
