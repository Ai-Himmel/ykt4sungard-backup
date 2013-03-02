/**
 * 
 */
package com.kingstargroup.ecard.hibernate.upload;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Session;

import com.kingstargroup.ecard.common.BasicPersistence;
import com.kingstargroup.ecard.exceptions.DBSystemException;


/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.
 * File name: UploadFilePersistence.java
 * Description: 上传文件的持久对象管理类
 * Modify History: 
 * 操作类型   操作人   操作时间     操作内容
 * ===================================
 *  创建    Xiao Qi  2005-9-13  
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class UploadFilePersistence extends BasicPersistence {


	/**
	 * Description: 根据传入的文件名参数相应在数据库中添加对应记录
	 * @param oldFileName 上传文件的实际文件名
	 * @param storeFileName 上传文件存储在磁盘的实际文件名
	 * @param fileType 上传文件类型 0-文档 1-图片
	 * Modify History:
	 */
	public UploadFiles addFile(String oldFileName, String storeFileName) throws DBSystemException {
		Session s = getSession();
		UploadFiles file = new UploadFiles();
		file.setOldFilename(oldFileName);
		file.setStoreFilename(storeFileName);
		try {			
			s.save(file);
			return file;
		} catch (HibernateException ex) {
			_log.error(ex);						
			throw new DBSystemException(ex.getMessage());			
		}		
	}	
	
	/**
	 * Description: 更新数据库中的上传文件持久对象
	 * @param id 要更新的上传文件ID
	 * @param oldFileName 上传文件的原始文件名
	 * @param storeFileName 上传文件的存储文件名
	 * @throws DBSystemException
	 * Modify History:
	 */
	public void updateFile(int id, String oldFileName, String storeFileName) throws DBSystemException {
		Session s = getSession();
		UploadFiles file = getUploadFileById(id);
		file.setOldFilename(oldFileName);
		file.setStoreFilename(storeFileName);
		try {			
			s.update(file);						
		} catch (HibernateException ex) {			
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}		
	}
		
	/**
	 * Description: 根据附件ID删除数据库对象的附件持久对象
	 * @param fileId 附件id
	 * @throws DBSystemException
	 * Modify History:
	 */
	public void deleteFileById(int fileId) throws DBSystemException {
		Session s = getSession();
		UploadFiles file = getUploadFileById(fileId);
		try {			
			s.delete(file);
		} catch (HibernateException ex) {
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());
		}
	}
	
	/**
	 * Description: 根据传入的上传文件ID得到对应的上传文件对象
	 * @param id 要取得的上传文件ID
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public UploadFiles getUploadFileById(int id) throws DBSystemException {
		Session s = getSession();
		UploadFiles file = null;
		try {
			file = (UploadFiles) s.get(UploadFiles.class, new Integer(id));
			return file;
		} catch (HibernateException ex) {
			_log.error(ex);			
			throw new DBSystemException(ex.getMessage());			
		}		
	}
	
	private static final Log _log = LogFactory.getLog(UploadFilePersistence.class);
}
