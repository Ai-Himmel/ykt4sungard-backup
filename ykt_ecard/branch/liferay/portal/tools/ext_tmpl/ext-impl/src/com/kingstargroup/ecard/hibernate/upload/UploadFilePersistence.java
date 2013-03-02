/**
 * 
 */
package com.kingstargroup.ecard.hibernate.upload;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Session;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.liferay.portal.service.persistence.BasePersistence;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. File name:
 * UploadFilePersistence.java Description: �ϴ��ļ��ĳ־ö�������� Modify History: �������� ������
 * ����ʱ�� �������� =================================== ���� Xiao Qi 2005-9-13
 * 
 * @author Xiao Qi
 * @version
 * @since 1.0
 */
public class UploadFilePersistence extends BasePersistence {

	/**
	 * Description: ���ݴ�����ļ���������Ӧ�����ݿ�����Ӷ�Ӧ��¼
	 * 
	 * @param oldFileName
	 *            �ϴ��ļ���ʵ���ļ���
	 * @param storeFileName
	 *            �ϴ��ļ��洢�ڴ��̵�ʵ���ļ���
	 * @param fileType
	 *            �ϴ��ļ����� 0-�ĵ� 1-ͼƬ Modify History:
	 */
	public UploadFiles addFile(String oldFileName, String storeFileName)
			throws DBSystemException {
		Session s = null;
		UploadFiles file = new UploadFiles();
		file.setOldFilename(oldFileName);
		file.setStoreFilename(storeFileName);
		try {
			s = openSession();
			s.save(file);
			return file;
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally {
			closeSession(s);
		}
	}

	/**
	 * Description: �������ݿ��е��ϴ��ļ��־ö���
	 * 
	 * @param id
	 *            Ҫ���µ��ϴ��ļ�ID
	 * @param oldFileName
	 *            �ϴ��ļ���ԭʼ�ļ���
	 * @param storeFileName
	 *            �ϴ��ļ��Ĵ洢�ļ���
	 * @throws DBSystemException
	 *             Modify History:
	 */
	public void updateFile(int id, String oldFileName, String storeFileName)
			throws DBSystemException {
		Session s = null;
		UploadFiles file = getUploadFileById(id);
		file.setOldFilename(oldFileName);
		file.setStoreFilename(storeFileName);
		try {
			s = openSession();
			s.update(file);
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally {
			closeSession(s);
		}
	}

	/**
	 * Description: ���ݸ���IDɾ�����ݿ����ĸ����־ö���
	 * 
	 * @param fileId
	 *            ����id
	 * @throws DBSystemException
	 *             Modify History:
	 */
	public void deleteFileById(int fileId) throws DBSystemException {
		Session s = null;
		UploadFiles file = getUploadFileById(fileId);
		try {
			s = openSession();
			s.delete(file);
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally {
			closeSession(s);
		}
	}

	/**
	 * Description: ���ݴ�����ϴ��ļ�ID�õ���Ӧ���ϴ��ļ�����
	 * 
	 * @param id
	 *            Ҫȡ�õ��ϴ��ļ�ID
	 * @return
	 * @throws DBSystemException
	 *             Modify History:
	 */
	public UploadFiles getUploadFileById(int id) throws DBSystemException {
		Session s = null;
		UploadFiles file = null;
		try {
			s = openSession();
			file = (UploadFiles) s.get(UploadFiles.class, new Integer(id));
			return file;
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally {
			closeSession(s);
		}
	}

	private static final Log _log = LogFactory
			.getLog(UploadFilePersistence.class);
}
