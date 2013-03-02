/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import java.util.Date;
import java.util.List;

import org.hibernate.Transaction;

import com.kingstargroup.ecard.common.BasicUtil;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.picdelay.EcardPicDelay;
import com.kingstargroup.ecard.hibernate.picdelay.PicDelayPersistence;
import com.kingstargroup.ecard.hibernate.picdelay.PostponeFiles;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.util.lang.FastStringBuffer;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: PicDelayUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-9-28  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class PicDelayUtil extends BasicUtil {

	/**
	 * Description:
	 * @param oldStuempNo
	 * @param newStuempNo
	 * @throws PortalException
	 * Modify History:
	 */
	public static void add(String oldStuempNo, String newStuempNo) throws PortalException {
		PicDelayPersistence persistence = (PicDelayPersistence) getPersistence(PicDelayPersistence.class.getName());
		Transaction t = beginTransaction();
		try {
			EcardPicDelay delay = new EcardPicDelay();
			delay.setCurStuempNo(newStuempNo);
			delay.setOldStuempNo(oldStuempNo);
			delay.setStatus(EcardConstants.POSTPONE_STATUS_UNACCEPTED);
			persistence.saveOrUpdate(delay);
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
	}
	
	/**
	 * Description:更新所有未被处理的照片延用信息
	 * @throws PortalException
	 * Modify History:
	 */
	public static byte[] updateDelays() throws PortalException {
		PicDelayPersistence persistence = (PicDelayPersistence) getPersistence(PicDelayPersistence.class.getName());
		Transaction t = beginTransaction();
		byte[] bytes = null;
		try {
			List unprocessedItems = persistence.getDelays(EcardConstants.POSTPONE_STATUS_UNACCEPTED);			
			/*
			 * 记录批量处理的照片延用信息
			 */
			String delayContent = createMappingTxt(unprocessedItems);
			bytes = delayContent.getBytes();
			/*
			 * 如果没有可处理的申请
			 */
			if (unprocessedItems.size() != 0) {
				PostponeFiles file = new PostponeFiles();
				file.setGenerateDate(new Date());
				file.setFileContent(delayContent);
				persistence.addPostponeFile(file);			
				for (int i = 0; i < unprocessedItems.size(); i++) {
					EcardPicDelay delay = (EcardPicDelay) unprocessedItems.get(i);
					delay.setStatus(EcardConstants.POSTPONE_STATUS_ACCEPTED);
					persistence.saveOrUpdate(delay);
				}
			}
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
		return bytes;
	}
	
	/**
	 * Description:
	 * @param id
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static PostponeFiles getPostponeFile(int id) throws PortalException {
		PicDelayPersistence persistence = (PicDelayPersistence) getPersistence(PicDelayPersistence.class.getName());		
		PostponeFiles file = null;
		Transaction t = beginTransaction();
		try {
			file = persistence.getPostponeFile(id);			
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
		return file;
	}
	
	public static ResultPage list(int page) throws PortalException {
		return list(page, EcardConstants.LIST_MORE_SIZE);
	}
	
	/**
	 * Description:分页查询照片延用的导出信息
	 * @param page
	 * @param size
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static ResultPage list(int page, int size) throws PortalException {
		PicDelayPersistence persistence = (PicDelayPersistence) getPersistence(PicDelayPersistence.class.getName());		
		ResultPage result = null;
		Transaction t = beginTransaction();
		try {
			result = persistence.getPostponeFiles(page, size);
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
		return result;
	}
	
	/**
	 * Description:
	 * @param curStuempId
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public static EcardPicDelay getDelayById(String curStuempId) throws PortalException {
		PicDelayPersistence persistence = (PicDelayPersistence) getPersistence(PicDelayPersistence.class.getName());
		Transaction t = beginTransaction();
		EcardPicDelay delay = null;		
		try {
			delay = persistence.getDelayById(curStuempId);
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
		return delay;
	}
	
	public static int countUnprocessedDelays() throws PortalException {
		PicDelayPersistence persistence = (PicDelayPersistence) getPersistence(PicDelayPersistence.class.getName());
		Transaction t = beginTransaction();
		int count = 0;
		try {
			count = persistence.getDelays(EcardConstants.POSTPONE_STATUS_UNACCEPTED).size();
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
		return count;
	}
	
	/**
	 * Description:取消
	 * @param curStuempNo
	 * @throws PortalException
	 * Modify History:
	 */
	public static void cancelPicDelay(String curStuempNo) throws PortalException {
		PicDelayPersistence persistence = (PicDelayPersistence) getPersistence(PicDelayPersistence.class.getName());
		Transaction t = beginTransaction();
		try {
			persistence.deleteDelayById(curStuempNo);
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
	}
	
	/**
	 * Description:生成照片延用信息的映射内容
	 * @param delayList
	 * @return
	 * Modify History:
	 */
	static String createMappingTxt(List delayList){		
		FastStringBuffer buff = new FastStringBuffer();
		for (int i = 0; i < delayList.size(); i++) {
			EcardPicDelay delay = (EcardPicDelay) delayList.get(i);
			buff.append(delay.getCurStuempNo())
				.append("    ")
				.append(delay.getOldStuempNo())
				.append(EcardConstants.LINE_SEPARATOR);
		}		
		return buff.toString();
	}

}
