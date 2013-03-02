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
	 * 初始化可上传文档和图片扩展名
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
		// 设置上传路径
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
	 * Description: 上传用户请求的文件
	 * 
	 * @param req
	 *            用户的http请求对象
	 * @param uploadFieldNames
	 *            上传的文件在html中的域名
	 * @param uploadType
	 *            上传的文件类型,0-文档,1-图片
	 * @return String "attachId1,attachId2,..."这样格式的上传文件ID字符串
	 * @throws IOException
	 * @throws FileNameException
	 *             扩展名不在允许上传文件扩展名列表内
	 * @throws FileSizeException
	 *             上传文件大小不在允许大小范围内 Modify History:
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
			// 设置上传路径
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
	 * Description: 上传用户请求的文件
	 * 
	 * @param req
	 *            用户的http请求对象
	 * @param uploadFieldNames
	 *            上传的文件在html中的域名
	 * @param uploadType
	 *            上传的文件类型,0-文档,1-图片
	 * @throws IOException
	 * @throws FileNameException
	 *             扩展名不在允许上传文件扩展名列表内
	 * @throws FileSizeException
	 *             上传文件大小不在允许大小范围内 Modify History:
	 */
	public synchronized void updateUpload(HttpServletRequest req,
			String[] uploadFieldNames, int uploadType, String[] attachIds)
			throws IOException, PortalException {
		UploadServletRequest uploadReq = getUploadServletRequest(req);
		for (int i = 0; i < uploadFieldNames.length; i++) {
			File tmpFile = uploadReq.getFile(uploadFieldNames[i]);
			// 如果没有替换原有的上传文件
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
			// 删除原有文件
			UploadFiles file = uploadFilePersistence.getUploadFileById(Integer
					.parseInt(attachIds[i]));
			File ioFile = new File(file.getStoreFilename());
			ioFile.delete();
			String storeFileName = path
					+ String.valueOf(System.currentTimeMillis())
					+ tmpFileName.substring(tmpFileName.lastIndexOf("."));
			writeToDisk(uploadType, storeFileName, bytes);
			// 更新数据库中的上传文件信息
			uploadFilePersistence.updateFile(Integer.parseInt(attachIds[i]),
					tmpFileName, storeFileName);
		}
	}

	public synchronized void updateUpload(UpLoadForm upLoadForm,
			int uploadType, String[] attachIds) throws IOException,
			PortalException {
		FormFile tmpFile = upLoadForm.getTheFile();
		// 如果没有替换原有的上传文件
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
		// 删除原有文件
		UploadFiles file = uploadFilePersistence.getUploadFileById(Integer
				.parseInt(attachIds[0]));
		File ioFile = new File(file.getStoreFilename());
		ioFile.delete();
		String storeFileName = path
				+ String.valueOf(System.currentTimeMillis())
				+ tmpFileName.substring(tmpFileName.lastIndexOf("."));
		writeToDisk(uploadType, storeFileName, bytes);
		// 更新数据库中的上传文件信息
		uploadFilePersistence.updateFile(Integer.parseInt(attachIds[0]),
				tmpFileName, storeFileName);
	}

	/**
	 * Description:根据传入的文件ID得到下载文件的字节数据
	 * 
	 * @param fileId
	 *            传入的文件ID
	 * @return String 文件字节数据
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
	 * Description: 根据传入的文件ID删除对应的上传文件
	 * 
	 * @param fileIds
	 *            要删除的附件
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
	 * Description:根据文件ID得到对应的原始文件名称
	 * 
	 * @param fileId
	 *            文件ID
	 * @return 文件名称 Modify History:
	 */
	public String getFileName(String fileId) throws PortalException {
		return getFileById(fileId).getOldFilename();
	}

	/**
	 * Description: 根据传入的附件ID得到对应的附件对象
	 * 
	 * @param fileId
	 *            传入的附件ID
	 * @return Modify History:
	 */
	public UploadFiles getFileById(String fileId) throws PortalException {
		return uploadFilePersistence
				.getUploadFileById(Integer.parseInt(fileId));
	}

	/**
	 * Description: 初始化允许上传的扩展名列表
	 * 
	 * @param extensionString
	 *            未解析过的扩展名字符串,格式为(.xxx,.xxx)
	 * @param container
	 *            需要初始化的扩展名列表 Modify History:
	 */
	static void initExtensions(String extensionString, List container) {
		StringTokenizer token = new StringTokenizer(extensionString,
				EcardConstants.DELIMITER);
		while (token.hasMoreTokens()) {
			container.add(token.nextToken());
		}
	}

	/**
	 * Description: 检查上传文件的扩展名是否在上传文件扩展名允许列表内
	 * 
	 * @param uploadType
	 *            上传的文件类型,0-文档,1-图片
	 * @param extension
	 *            要检查的扩展名
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
	 * Description:检查上传文件的大小是否在允许范围内
	 * 
	 * @param uploadType
	 *            上传的文件类型,0-文档,1-图片
	 * @param size
	 *            要检查的文件大小
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
	 * Description:将要保存的上传文件数据写入磁盘
	 * 
	 * @param uploadType
	 *            上传的文件类型,0-文档,1-图片
	 * @param fileName
	 *            要保存的文件名
	 * @param bytes
	 *            要保存的文件数据
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
