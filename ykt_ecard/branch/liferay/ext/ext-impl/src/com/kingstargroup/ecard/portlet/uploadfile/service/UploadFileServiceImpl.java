package com.kingstargroup.ecard.portlet.uploadfile.service;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.List;
import java.util.StringTokenizer;

import javax.servlet.http.HttpServletRequest;

import org.apache.struts.upload.FormFile;

import com.kingstargroup.ecard.exceptions.FileNameException;
import com.kingstargroup.ecard.exceptions.FileSizeException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.upload.UploadFiles;
import com.kingstargroup.ecard.portlet.document.action.UpLoadForm;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.util.FileUtil;
import com.liferay.util.servlet.UploadServletRequest;

public class UploadFileServiceImpl extends UploadFileServiceBase {

	/**
	 * ��ʼ�����ϴ��ĵ���ͼƬ��չ��
	 */
	static {
		String docExtensions = PropsUtil.get("info.upload.document.extension");
		String imageExtensions = PropsUtil.get("info.upload.image.extension");
		initExtensions(docExtensions, EcardConstants.DOC_EXTENSION_LIST);
		initExtensions(imageExtensions, EcardConstants.IMAGE_EXTENSION_LIST);
	}

	public synchronized String upload(UpLoadForm upLoadForm, int uploadType)
			throws IOException, PortalException {
		StringBuffer attachBuff = new StringBuffer();
		/**/

		FormFile tmpFile = upLoadForm.getTheFile();
		String tmpFileName = tmpFile.getFileName();

		if (tmpFileName.indexOf(".") == -1
				|| !checkExtension(uploadType, tmpFileName
						.substring(tmpFileName.lastIndexOf(".")))) {
			throw new FileNameException();
		}
		if (!checkFormFileMaxSize(uploadType, tmpFile)) {
			throw new FileSizeException(tmpFileName);
		}
		byte[] bytes = tmpFile.getFileData();
		String path = null;
		// �����ϴ�·��
		if (uploadType == 0) {
			path = EcardConstants.DOC_ROOT;
		} else if (uploadType == 1) {
			path = EcardConstants.IMAGE_ROOT;
		}
		String storeFileName = path
				+ String.valueOf(System.currentTimeMillis())
				+ tmpFileName.substring(tmpFileName.lastIndexOf("."));
		writeToDisk(uploadType, storeFileName, bytes);
		UploadFiles file = uploadFilePersistence.addFile(tmpFileName,
				storeFileName);
		attachBuff.append(file.getId()).append(",");

		return attachBuff.deleteCharAt(attachBuff.length() - 1).toString();
	}

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
	public synchronized String upload(HttpServletRequest req,
			String[] uploadFieldNames, int uploadType) throws IOException,
			PortalException {
		UploadServletRequest uploadReq = getUploadServletRequest(req);
		StringBuffer attachBuff = new StringBuffer();
		/**/
		for (int i = 0; i < uploadFieldNames.length; i++) {
			File tmpFile = uploadReq.getFile(uploadFieldNames[i]);
			String tmpFileName = uploadReq.getFileName(uploadFieldNames[i]);

			if (tmpFileName.indexOf(".") == -1
					|| !checkExtension(uploadType, tmpFileName
							.substring(tmpFileName.lastIndexOf(".")))) {
				throw new FileNameException();
			}
			if (!checkMaxSize(uploadType, tmpFile)) {
				throw new FileSizeException(tmpFileName);
			}
			byte[] bytes = FileUtil.getBytes(tmpFile);
			String path = null;
			// �����ϴ�·��
			if (uploadType == 0) {
				path = EcardConstants.DOC_ROOT;
			} else if (uploadType == 1) {
				path = EcardConstants.IMAGE_ROOT;
			}
			String storeFileName = path
					+ String.valueOf(System.currentTimeMillis())
					+ tmpFileName.substring(tmpFileName.lastIndexOf("."));
			writeToDisk(uploadType, storeFileName, bytes);
			UploadFiles file = uploadFilePersistence.addFile(tmpFileName,
					storeFileName);
			attachBuff.append(file.getId()).append(",");
		}
		return attachBuff.deleteCharAt(attachBuff.length() - 1).toString();
	}

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
	public synchronized void updateUpload(HttpServletRequest req,
			String[] uploadFieldNames, int uploadType, String[] attachIds)
			throws IOException, PortalException {
		UploadServletRequest uploadReq = getUploadServletRequest(req);
		for (int i = 0; i < uploadFieldNames.length; i++) {
			File tmpFile = uploadReq.getFile(uploadFieldNames[i]);
			// ���û���滻ԭ�е��ϴ��ļ�
			String tmpFileName = uploadReq.getFileName(uploadFieldNames[i]);
			if (tmpFileName.equals("")) {
				continue;
			}
			if (tmpFileName.indexOf(".") == -1
					|| !checkExtension(uploadType, tmpFileName
							.substring(tmpFileName.lastIndexOf(".")))) {
				throw new FileNameException();
			}
			if (!checkMaxSize(uploadType, tmpFile)) {
				throw new FileSizeException(tmpFileName);
			}
			byte[] bytes = FileUtil.getBytes(tmpFile);
			String path = null;
			if (uploadType == 0) {
				path = EcardConstants.DOC_ROOT;
			} else if (uploadType == 1) {
				path = EcardConstants.IMAGE_ROOT;
			}
			// ɾ��ԭ���ļ�
			UploadFiles file = uploadFilePersistence.getUploadFileById(Integer
					.parseInt(attachIds[i]));
			File ioFile = new File(file.getStoreFilename());
			ioFile.delete();
			String storeFileName = path
					+ String.valueOf(System.currentTimeMillis())
					+ tmpFileName.substring(tmpFileName.lastIndexOf("."));
			writeToDisk(uploadType, storeFileName, bytes);
			// �������ݿ��е��ϴ��ļ���Ϣ
			uploadFilePersistence.updateFile(Integer.parseInt(attachIds[i]),
					tmpFileName, storeFileName);
		}
	}

	public synchronized void updateUpload(UpLoadForm upLoadForm,
			int uploadType, String[] attachIds) throws IOException,
			PortalException {
		FormFile tmpFile = upLoadForm.getTheFile();
		// ���û���滻ԭ�е��ϴ��ļ�
		String tmpFileName = tmpFile.getFileName();
		if ("".equals(tmpFileName)) {
			throw new FileNameException();
		}
		if (tmpFileName.indexOf(".") == -1
				|| !checkExtension(uploadType, tmpFileName
						.substring(tmpFileName.lastIndexOf(".")))) {
			throw new FileNameException();
		}
		if (!checkFormFileMaxSize(uploadType, tmpFile)) {
			throw new FileSizeException(tmpFileName);
		}
		byte[] bytes = tmpFile.getFileData();
		String path = null;
		if (uploadType == 0) {
			path = EcardConstants.DOC_ROOT;
		} else if (uploadType == 1) {
			path = EcardConstants.IMAGE_ROOT;
		}
		// ɾ��ԭ���ļ�
		UploadFiles file = uploadFilePersistence.getUploadFileById(Integer
				.parseInt(attachIds[0]));
		File ioFile = new File(file.getStoreFilename());
		ioFile.delete();
		String storeFileName = path
				+ String.valueOf(System.currentTimeMillis())
				+ tmpFileName.substring(tmpFileName.lastIndexOf("."));
		writeToDisk(uploadType, storeFileName, bytes);
		// �������ݿ��е��ϴ��ļ���Ϣ
		uploadFilePersistence.updateFile(Integer.parseInt(attachIds[0]),
				tmpFileName, storeFileName);
	}

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
			PortalException {
		byte[] bytes = null;
		UploadFiles file = uploadFilePersistence.getUploadFileById(Integer
				.parseInt(fileId));
		File outFile = new File(file.getStoreFilename());
		bytes = FileUtil.getBytes(outFile);
		return bytes;
	}

	/**
	 * Description: ���ݴ�����ļ�IDɾ����Ӧ���ϴ��ļ�
	 * 
	 * @param fileIds
	 *            Ҫɾ���ĸ���
	 * @throws PortalException
	 *             Modify History:
	 */
	public void deleteFile(String[] fileIds) throws PortalException {
		for (int i = 0; i < fileIds.length; i++) {
			UploadFiles file = uploadFilePersistence.getUploadFileById(Integer
					.parseInt(fileIds[i]));
			File ioFile = new File(file.getStoreFilename());
			ioFile.delete();
			uploadFilePersistence.deleteFileById(Integer.parseInt(fileIds[i]));
		}
	}

	/**
	 * Description:�����ļ�ID�õ���Ӧ��ԭʼ�ļ�����
	 * 
	 * @param fileId
	 *            �ļ�ID
	 * @return �ļ����� Modify History:
	 */
	public String getFileName(String fileId) throws PortalException {
		return getFileById(fileId).getOldFilename();
	}

	/**
	 * Description: ���ݴ���ĸ���ID�õ���Ӧ�ĸ�������
	 * 
	 * @param fileId
	 *            ����ĸ���ID
	 * @return Modify History:
	 */
	public UploadFiles getFileById(String fileId) throws PortalException {
		return uploadFilePersistence
				.getUploadFileById(Integer.parseInt(fileId));
	}

	/**
	 * Description: ��ʼ�������ϴ�����չ���б�
	 * 
	 * @param extensionString
	 *            δ����������չ���ַ���,��ʽΪ(.xxx,.xxx)
	 * @param container
	 *            ��Ҫ��ʼ������չ���б� Modify History:
	 */
	static void initExtensions(String extensionString, List container) {
		StringTokenizer token = new StringTokenizer(extensionString,
				EcardConstants.DELIMITER);
		while (token.hasMoreTokens()) {
			container.add(token.nextToken());
		}
	}

	/**
	 * Description: ����ϴ��ļ�����չ���Ƿ����ϴ��ļ���չ�������б���
	 * 
	 * @param uploadType
	 *            �ϴ����ļ�����,0-�ĵ�,1-ͼƬ
	 * @param extension
	 *            Ҫ������չ��
	 * @return Modify History:
	 */
	static boolean checkExtension(int uploadType, String extension) {
		if (uploadType == 0) {
			return EcardConstants.DOC_EXTENSION_LIST.contains(extension
					.toLowerCase());
		} else if (uploadType == 1) {
			return EcardConstants.IMAGE_EXTENSION_LIST.contains(extension
					.toLowerCase());
		}
		return true;
	}

	/**
	 * Description:����ϴ��ļ��Ĵ�С�Ƿ�������Χ��
	 * 
	 * @param uploadType
	 *            �ϴ����ļ�����,0-�ĵ�,1-ͼƬ
	 * @param size
	 *            Ҫ�����ļ���С
	 * @return Modify History:
	 */
	static boolean checkMaxSize(int uploadType, File file) {
		try {
			byte bytes[] = null;
			if (file == null) {
				return false;
			}
			if (uploadType == 0) {
				bytes = new byte[EcardConstants.DOC_MAX_SIZE + 1];
			} else if (uploadType == 1) {
				bytes = new byte[EcardConstants.IMAGE_MAX_SIZE + 1];
			}
			FileInputStream fis = new FileInputStream(file);
			int readBytes = fis.read(bytes, 0, bytes.length);
			if (readBytes < bytes.length) {
				return true;
			}
			return false;
		} catch (IOException ioe) {
			return false;
		}
	}

	static boolean checkFormFileMaxSize(int uploadType, FormFile file) {
		if (file == null) {
			return false;
		}
		int maxsize = 0;
		if (uploadType == 0) {
			maxsize = EcardConstants.DOC_MAX_SIZE + 1;
		} else if (uploadType == 1) {
			maxsize = EcardConstants.IMAGE_MAX_SIZE + 1;
		}

		if (maxsize > file.getFileSize()) {
			return true;
		}
		return false;
	}

	/**
	 * Description:��Ҫ������ϴ��ļ�����д�����
	 * 
	 * @param uploadType
	 *            �ϴ����ļ�����,0-�ĵ�,1-ͼƬ
	 * @param fileName
	 *            Ҫ������ļ���
	 * @param bytes
	 *            Ҫ������ļ�����
	 * @throws IOException
	 *             Modify History:
	 */
	static void writeToDisk(int uploadType, String fileName, byte[] bytes)
			throws IOException {
		File f = new File(fileName);
		if (f.getParent() != null) {
			FileUtil.mkdirs(f.getParent());
		}
		OutputStream os = new FileOutputStream(f);
		os.write(bytes);
		os.flush();
	}

	static UploadServletRequest getUploadServletRequest(HttpServletRequest req)
			throws IOException {
		// DynamicServletRequest dsr = (DynamicServletRequest) req;
		// return (UploadServletRequest) dsr.getRequest();
		UploadServletRequest uploadReq = PortalUtil.getUploadServletRequest(req);
		return uploadReq;

	}

}
