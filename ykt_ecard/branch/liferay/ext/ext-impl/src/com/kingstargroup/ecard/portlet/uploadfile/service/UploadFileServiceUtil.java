package com.kingstargroup.ecard.portlet.uploadfile.service;

import java.io.IOException;

import javax.servlet.http.HttpServletRequest;

import com.kingstargroup.ecard.exceptions.FileNameException;
import com.kingstargroup.ecard.exceptions.FileSizeException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.upload.UploadFiles;
import com.kingstargroup.ecard.portlet.document.action.UpLoadForm;

public class UploadFileServiceUtil {
	
	public synchronized static String upload(UpLoadForm upLoadForm, int uploadType) 
	throws IOException, PortalException {
	UploadFileService uploadFileService = UploadFileServiceFactory.getService();
	return uploadFileService.upload(upLoadForm, uploadType);
}
	
		/**
	 * Description: 上传用户请求的文件
	 * @param req 用户的http请求对象
	 * @param uploadFieldNames 上传的文件在html中的域名
	 * @param uploadType 上传的文件类型,0-文档,1-图片
	 * @return String "attachId1,attachId2,..."这样格式的上传文件ID字符串
	 * @throws IOException
	 * @throws FileNameException 扩展名不在允许上传文件扩展名列表内
	 * @throws FileSizeException 上传文件大小不在允许大小范围内
	 * Modify History:
	 */
	public synchronized static String upload(HttpServletRequest req, String[] uploadFieldNames, int uploadType) 
		throws IOException, PortalException {
		UploadFileService uploadFileService = UploadFileServiceFactory.getService();
		return uploadFileService.upload(req, uploadFieldNames, uploadType);
	}
	
	/**
	 * Description: 上传用户请求的文件
	 * @param req 用户的http请求对象
	 * @param uploadFieldNames 上传的文件在html中的域名
	 * @param uploadType 上传的文件类型,0-文档,1-图片
	 * @throws IOException
	 * @throws FileNameException 扩展名不在允许上传文件扩展名列表内
	 * @throws FileSizeException 上传文件大小不在允许大小范围内
	 * Modify History:
	 */
	public synchronized static void updateUpload(HttpServletRequest req, 
												String[] uploadFieldNames, 
												int uploadType, 
												String[] attachIds) 
		throws IOException, PortalException {
		UploadFileService uploadFileService = UploadFileServiceFactory.getService();
		uploadFileService.updateUpload(req, uploadFieldNames, uploadType, attachIds);
		
	}
	
	public synchronized static void updateUpload(UpLoadForm upLoadForm, 
			int uploadType, 
			String[] attachIds) 
throws IOException, PortalException {
UploadFileService uploadFileService = UploadFileServiceFactory.getService();
uploadFileService.updateUpload(upLoadForm, uploadType, attachIds);

}
	
	/**
	 * Description:根据传入的文件ID得到下载文件的字节数据
	 * @param fileId  传入的文件ID
	 * @return String 文件字节数据
	 * @throws IOException
	 * Modify History:
	 */
	public static byte[] downloadFile(String fileId) throws IOException, PortalException {
		UploadFileService uploadFileService = UploadFileServiceFactory.getService();
		return uploadFileService.downloadFile(fileId);
	}
	
	/**
	 * Description: 根据传入的文件ID删除对应的上传文件
	 * @param fileIds 要删除的附件
	 * @throws PortalException
	 * Modify History:
	 */
	public static void deleteFile(String[] fileIds) throws PortalException {
		UploadFileService uploadFileService = UploadFileServiceFactory.getService();
		uploadFileService.deleteFile(fileIds);
	}
	
	/**
	 * Description:根据文件ID得到对应的原始文件名称
	 * @param fileId 文件ID
	 * @return 文件名称
	 * Modify History:
	 */
	public static String getFileName(String fileId) throws PortalException {		
		return getFileById(fileId).getOldFilename();
	}
	
	/**
	 * Description: 根据传入的附件ID得到对应的附件对象
	 * @param fileId 传入的附件ID
	 * @return
	 * Modify History:
	 */
	public static UploadFiles getFileById(String fileId) throws PortalException {
		UploadFileService uploadFileService = UploadFileServiceFactory.getService();
		return uploadFileService.getFileById(fileId);
	}	


}
