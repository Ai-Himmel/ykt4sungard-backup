package com.kingstargroup.ecard.portlet.information.service;

import java.io.IOException;
import java.util.List;

import javax.servlet.http.HttpServletRequest;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.information.EcardInformation;
import com.kingstargroup.ecard.hibernate.util.ResultPage;
import com.kingstargroup.ecard.portlet.document.action.UpLoadForm;
import com.kingstargroup.ecard.util.EcardConstants;

public class EcardInformationServiceUtil {

	public static ResultPage list(String infoType) throws PortalException {
		return list(0, infoType);
	}

	public static ResultPage list(int page, String infoType)
			throws PortalException {
		return list(page, infoType, EcardConstants.MAX_RESULT_SIZE);
	}

	public static ResultPage list(int page, String infoType, int size)
			throws PortalException {
		EcardInformationService ecardInformationService = EcardInformationServiceFactory
				.getService();
		return ecardInformationService.list(page, infoType, size);
	}

	public static ResultPage search(String title, String content,
			String infoType, int page, int size) throws PortalException {
		EcardInformationService ecardInformationService = EcardInformationServiceFactory
				.getService();
		return ecardInformationService.search(title, content, infoType, page,
				size);

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
	public static ResultPage search(String title, String content,
			String infoType, int page) throws PortalException {
		return search(title, content, infoType, page,
				EcardConstants.LIST_MORE_SIZE);
	}

	public static EcardInformation getInfoById(String id)
			throws PortalException {
		EcardInformationService ecardInformationService = EcardInformationServiceFactory
				.getService();
		return ecardInformationService.getInfoById(id);

	}

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
	public static EcardInformation add(String title, String content,
			String attachments, String type, String creater)
			throws IOException, PortalException {
		EcardInformationService ecardInformationService = EcardInformationServiceFactory
				.getService();
		return ecardInformationService.add(title, content, attachments, type,
				creater);
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
	public static EcardInformation add(String title, String content,
			String attachments, String type, String creater,
			HttpServletRequest req, String[] uploadFieldNames, int uploadType)
			throws IOException, PortalException {
		EcardInformationService ecardInformationService = EcardInformationServiceFactory
				.getService();
		return ecardInformationService.add(title, content, attachments, type,
				creater, req, uploadFieldNames, uploadType);
	}
	
	public static EcardInformation add(String title, String content,
			String attachments, String type, String creater,UpLoadForm upLoadForm, int uploadType)
			throws IOException, PortalException {
		EcardInformationService ecardInformationService = EcardInformationServiceFactory
				.getService();
		return ecardInformationService.add(title, content, attachments, type,
				creater,upLoadForm, uploadType);
	}

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
	public static void updateInfoById(String id, String title, String content,
			String attachments) throws IOException, PortalException {
		EcardInformationService ecardInformationService = EcardInformationServiceFactory
				.getService();
		ecardInformationService.updateInfoById(id, title, content, attachments);
	}

	/**
	 * Description:ɾ��������
	 * 
	 * @param ids
	 * @throws PortalException
	 *             Modify History:
	 */
	public static void deleteInfomations(String[] ids) throws PortalException {
		EcardInformationService ecardInformationService = EcardInformationServiceFactory
				.getService();
		ecardInformationService.deleteInfomations(ids);
	}

	public static void updateInfoById(String id, String title, String content,
			String attachments, HttpServletRequest req,
			String[] uploadFieldNames, int uploadType) throws IOException,
			PortalException {
		EcardInformationService ecardInformationService = EcardInformationServiceFactory
				.getService();
		ecardInformationService.updateInfoById(id, title, content, attachments,
				req, uploadFieldNames, uploadType);
	}
	
	public static void updateInfoById(String id, String title, String content,
			String attachments, UpLoadForm upLoadForm, int uploadType) throws IOException,
			PortalException {
		EcardInformationService ecardInformationService = EcardInformationServiceFactory
				.getService();
		ecardInformationService.updateInfoById(id, title, content, attachments,
				upLoadForm, uploadType);
	}

	public static List search(String title) throws PortalException {
		EcardInformationService ecardInformationService = EcardInformationServiceFactory
				.getService();
		return ecardInformationService.search(title);
	}

	/**
	 * Description:���ݴ���Ҫɾ����ID����ɾ����Ӧ������
	 * 
	 * @param ids
	 *            Ҫɾ����ID����
	 * @throws PortalException
	 *             Modify History:
	 */
	public static boolean deleteInfos(String[] ids) throws PortalException {
		EcardInformationService ecardInformationService = EcardInformationServiceFactory
				.getService();
		return ecardInformationService.deleteInfos(ids);
	}

}
