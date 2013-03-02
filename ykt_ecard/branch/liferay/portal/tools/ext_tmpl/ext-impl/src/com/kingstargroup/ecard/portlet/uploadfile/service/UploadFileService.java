package com.kingstargroup.ecard.portlet.uploadfile.service;

import java.io.IOException;

import javax.servlet.http.HttpServletRequest;

import com.kingstargroup.ecard.exceptions.FileNameException;
import com.kingstargroup.ecard.exceptions.FileSizeException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.upload.UploadFiles;
import com.kingstargroup.ecard.portlet.document.action.UpLoadForm;

public interface UploadFileService {
	public String upload(UpLoadForm upLoadForm,
			int uploadType) throws IOException, PortalException;
	/**
	 * Description: �ϴ��û�������ļ�
	 * 
	 * @param req
	 *            �û���http�������
	 * @param uploadFieldNames
	 *            �ϴ����ļ���html�е�����
	 * @param uploadType
	 *            �ϴ����ļ�����,0-�ĵ�,1-ͼƬ
	 * @return String "attachId1,attachId2,..."������ʽ���ϴ��ļ�ID�ַ���
	 * @throws IOException
	 * @throws FileNameException
	 *             ��չ�����������ϴ��ļ���չ���б���
	 * @throws FileSizeException
	 *             �ϴ��ļ���С���������С��Χ�� Modify History:
	 */
	public String upload(HttpServletRequest req, String[] uploadFieldNames,
			int uploadType) throws IOException, PortalException;

	/**
	 * Description: �ϴ��û�������ļ�
	 * 
	 * @param req
	 *            �û���http�������
	 * @param uploadFieldNames
	 *            �ϴ����ļ���html�е�����
	 * @param uploadType
	 *            �ϴ����ļ�����,0-�ĵ�,1-ͼƬ
	 * @throws IOException
	 * @throws FileNameException
	 *             ��չ�����������ϴ��ļ���չ���б���
	 * @throws FileSizeException
	 *             �ϴ��ļ���С���������С��Χ�� Modify History:
	 */
	public void updateUpload(HttpServletRequest req, String[] uploadFieldNames,
			int uploadType, String[] attachIds) throws IOException,
			PortalException;
	
	public void updateUpload(UpLoadForm upLoadForm,
			int uploadType, String[] attachIds) throws IOException,
			PortalException;

	/**
	 * Description:���ݴ�����ļ�ID�õ������ļ����ֽ�����
	 * 
	 * @param fileId
	 *            ������ļ�ID
	 * @return String �ļ��ֽ�����
	 * @throws IOException
	 *             Modify History:
	 */
	public byte[] downloadFile(String fileId) throws IOException,
			PortalException;

	/**
	 * Description: ���ݴ�����ļ�IDɾ����Ӧ���ϴ��ļ�
	 * 
	 * @param fileIds
	 *            Ҫɾ���ĸ���
	 * @throws PortalException
	 *             Modify History:
	 */
	public void deleteFile(String[] fileIds) throws PortalException;

	/**
	 * Description:�����ļ�ID�õ���Ӧ��ԭʼ�ļ�����
	 * 
	 * @param fileId
	 *            �ļ�ID
	 * @return �ļ����� Modify History:
	 */
	public String getFileName(String fileId) throws PortalException;

	/**
	 * Description: ���ݴ���ĸ���ID�õ���Ӧ�ĸ�������
	 * 
	 * @param fileId
	 *            ����ĸ���ID
	 * @return Modify History:
	 */
	public UploadFiles getFileById(String fileId) throws PortalException;

}
