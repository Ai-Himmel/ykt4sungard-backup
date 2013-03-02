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
import com.kingstargroup.ecard.hibernate.util.InfoTypeUtil;
import com.kingstargroup.ecard.hibernate.util.ResultPage;
import com.kingstargroup.ecard.hibernate.util.UploadFileUtil;
import com.kingstargroup.ecard.portlet.document.action.UpLoadForm;
import com.kingstargroup.ecard.util.EcardConstants;
import com.kingstargroup.ecard.util.EcardInformationPool;
import com.liferay.portal.kernel.util.StringUtil;

public interface EcardInformationService {
	
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
	public EcardInformation add(String title, String content,
			String attachments, String type, String creater)
			throws IOException, PortalException ;

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
	public EcardInformation add(String title, String content,
			String attachments, String type, String creater,
			HttpServletRequest req, String[] uploadFieldNames, int uploadType)
			throws IOException, PortalException ;
	
	public EcardInformation add(String title, String content,
			String attachments, String type, String creater,UpLoadForm upLoadForm, int uploadType)
			throws IOException, PortalException ;

	/**
	 * Description:������ϢID�õ���Ӧ����Ϣ����
	 * 
	 * @param id
	 *            �������ϢID
	 * @return Modify History:
	 */
	public EcardInformation getInfoById(String id)throws PortalException ;
	
	
	public void updateInfoById(String id, String title, String content,
			String attachments) throws IOException, PortalException;
	

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
	public void updateInfoById(String id, String title, String content,
			String attachments, HttpServletRequest req,
			String[] uploadFieldNames, int uploadType) throws IOException,
			PortalException ;
	public void updateInfoById(String id, String title, String content,
			String attachments, UpLoadForm upLoadForm, int uploadType) throws IOException,
			PortalException ;

	public ResultPage list(String infoType) throws PortalException ;

	public ResultPage list(int page, String infoType)
			throws PortalException ;

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
	public ResultPage list(int page, String infoType, int size)
			throws PortalException;

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
	public ResultPage search(String title, String content,
			String infoType, int page) throws PortalException ;

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
	public ResultPage search(String title, String content,
			String infoType, int page, int size) throws PortalException ;

	public List search(String title) throws PortalException ;

	/**
	 * Description:���ݴ���Ҫɾ����ID����ɾ����Ӧ������
	 * 
	 * @param ids
	 *            Ҫɾ����ID����
	 * @throws PortalException
	 *             Modify History:
	 */
	public boolean deleteInfos(String[] ids) throws PortalException ;
	
	
	/**
	 * Description:ɾ��������
	 * @param ids
	 * @throws PortalException
	 * Modify History:
	 */
	public void deleteInfomations(String[] ids) throws PortalException ;
	
}
