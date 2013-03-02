/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.Date;

import org.hibernate.Transaction;

import com.kingstargroup.ecard.common.BasicUtil;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.information.EcardInformation;
import com.kingstargroup.ecard.hibernate.information.InformationPersistence;
import com.kingstargroup.ecard.util.EcardInformationPool;
import com.liferay.portal.util.PropsUtil;
import com.liferay.util.FileUtil;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: CardListUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-11-8  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class CardListUtil extends BasicUtil {
	/**
	 * Description:增加一条卡名单
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
		String fileName = cardlistDir + attachments;
		writeToDisk(fileName, content.getBytes("UTF-8"));		
		return InformationUtil.add(title,
				"",
				attachments,
				type,
				creater);
	}
	
	/**
	 * Description:更新指定卡名单
	 * @param id
	 * @param title
	 * @param content
	 * @param attachments
	 * @throws IOException
	 * @throws PortalException
	 * Modify History:
	 */
	public static void updateInfoById(String id, 
			String title, 
			String content, 
			String attachments) 
			throws IOException,PortalException {		
		EcardInformation info = InformationUtil.getInfoById(id);
		String fileName = cardlistDir + info.getAttachments();
		writeToDisk(fileName, content.getBytes("UTF-8"));
		InformationUtil.updateInfoById(id, title, "", info.getAttachments());
		/*
		 * update cache object
		 */
		info.setInfoContent(content);
		info.setInfoTitle(title);
		info.setCreateDate(new Date());
		EcardInformationPool.put(id, info);
	}
	
	/**
	 * Description:根据信息ID得到对应的信息对象
	 * @param id 传入的信息ID
	 * @return
	 * Modify History:
	 */
	public static EcardInformation getInfoById(String id) throws PortalException {
		/*
		 * cache process
		 */
		EcardInformation info = EcardInformationPool.get(id);
		if (info != null) {
			return info;
		}
		info = InformationUtil.getInfoById(id);
		File outFile = new File(cardlistDir + info.getAttachments());
		try {
			byte bytes[] = FileUtil.getBytes(outFile);
			info.setInfoContent(new String(bytes, "UTF-8"));
		} catch(IOException ioe) {
			info.setInfoContent("");
		}
		EcardInformationPool.put(id, info);
		return info;
		
	}
	
	/**
	 * Description:删除卡名单
	 * @param ids
	 * @throws PortalException
	 * Modify History:
	 */
	public static void deleteInfos(String[] ids) throws PortalException {
		InformationPersistence persistence = (InformationPersistence) getPersistence(InformationPersistence.class.getName());
		Transaction t = beginTransaction();
		try {
			for (int i = 0; i < ids.length; i++) {				
				EcardInformation info = persistence.getInfoById(ids[i]);
				File ioFile = new File(cardlistDir + info.getAttachments());
				ioFile.delete();
				EcardInformationPool.remove(ids[i]);//update cache pool
			}
			persistence.deleteInfosByIds(ids);			
			t.commit();
		} catch (Exception e) {
			t.rollback();
		} finally {
			closeSession();
		}
	}
	/**
	 * Description:把指定文件写入磁盘中
	 * @param fileName
	 * @param bytes
	 * @throws IOException
	 * Modify History:
	 */
	static void writeToDisk(String fileName, byte[] bytes) throws IOException {
		File f = new File(fileName);
		if (f.getParent() != null) {
			FileUtil.mkdirs(f.getParent());
		}
		OutputStream os = new FileOutputStream(f);
		os.write(bytes);
		os.flush();
	}
	
	private static String cardlistDir = PropsUtil.get("info.cardlist.dir");
}
