/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.Date;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.information.EcardInformation;
import com.kingstargroup.ecard.util.EcardInformationPool;
import com.liferay.portal.util.PropsUtil;
import com.liferay.util.FileUtil;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: CardListUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * ��������   ������   ����ʱ��     ��������<br>
 * ===================================<br>
 *  ����    Xiao Qi  2005-11-8  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class CardListUtil{
	/**
	 * Description:����һ��������
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
	 * Description:����ָ��������
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
	 * Description:������ϢID�õ���Ӧ����Ϣ����
	 * @param id �������ϢID
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
	 * Description:��ָ���ļ�д�������
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
