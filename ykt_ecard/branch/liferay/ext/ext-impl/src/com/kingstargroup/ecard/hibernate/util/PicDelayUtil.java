/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import java.util.Date;
import java.util.List;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.picdelay.EcardPicDelay;
import com.kingstargroup.ecard.hibernate.picdelay.PicDelayPersistence;
import com.kingstargroup.ecard.hibernate.picdelay.PostponeFiles;
import com.kingstargroup.ecard.util.EcardConstants;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: PicDelayUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * ��������   ������   ����ʱ��     ��������<br>
 * ===================================<br>
 *  ����    Xiao Qi  2005-9-28  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class PicDelayUtil{

	/**
	 * Description:
	 * @param oldStuempNo
	 * @param newStuempNo
	 * @throws PortalException
	 * Modify History:
	 */
	public static void add(String oldStuempNo, String newStuempNo) throws PortalException {
			EcardPicDelay delay = new EcardPicDelay();
			delay.setCurStuempNo(newStuempNo);
			delay.setOldStuempNo(oldStuempNo);
			delay.setStatus(EcardConstants.POSTPONE_STATUS_UNACCEPTED);
			getPersistence().saveOrUpdate(delay);
	}
	
	/**
	 * Description:��������δ���������Ƭ������Ϣ
	 * @throws PortalException
	 * Modify History:
	 */
	public static byte[] updateDelays() throws PortalException {
		byte[] bytes = null;
			List unprocessedItems = getPersistence().getDelays(EcardConstants.POSTPONE_STATUS_UNACCEPTED);			
			/*
			 * ��¼�����������Ƭ������Ϣ
			 */
			String delayContent = createMappingTxt(unprocessedItems);
			bytes = delayContent.getBytes();
			/*
			 * ���û�пɴ��������
			 */
			if (unprocessedItems.size() != 0) {
				PostponeFiles file = new PostponeFiles();
				file.setGenerateDate(new Date());
				file.setFileContent(delayContent);
				getPersistence().addPostponeFile(file);			
				for (int i = 0; i < unprocessedItems.size(); i++) {
					EcardPicDelay delay = (EcardPicDelay) unprocessedItems.get(i);
					delay.setStatus(EcardConstants.POSTPONE_STATUS_ACCEPTED);
					getPersistence().saveOrUpdate(delay);
				}
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
		return getPersistence().getPostponeFile(id);			
	}
	
	public static ResultPage list(int page) throws PortalException {
		return list(page, EcardConstants.LIST_MORE_SIZE);
	}
	
	/**
	 * Description:��ҳ��ѯ��Ƭ���õĵ�����Ϣ
	 * @param page
	 * @param size
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static ResultPage list(int page, int size) throws PortalException {
			return getPersistence().getPostponeFiles(page, size);

	}
	
	/**
	 * Description:
	 * @param curStuempId
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public static EcardPicDelay getDelayById(String curStuempId) throws PortalException {
			return getPersistence().getDelayById(curStuempId);
	}
	
	public static int countUnprocessedDelays() throws PortalException {
			return getPersistence().getDelays(EcardConstants.POSTPONE_STATUS_UNACCEPTED).size();

	}
	
	/**
	 * Description:ȡ��
	 * @param curStuempNo
	 * @throws PortalException
	 * Modify History:
	 */
	public static void cancelPicDelay(String curStuempNo) throws PortalException {
			getPersistence().deleteDelayById(curStuempNo);
	}
	
	/**
	 * Description:������Ƭ������Ϣ��ӳ������
	 * @param delayList
	 * @return
	 * Modify History:
	 */
	static String createMappingTxt(List delayList){		
		StringBuffer buff = new StringBuffer();
		for (int i = 0; i < delayList.size(); i++) {
			EcardPicDelay delay = (EcardPicDelay) delayList.get(i);
			buff.append(delay.getCurStuempNo())
				.append("    ")
				.append(delay.getOldStuempNo())
				.append(EcardConstants.LINE_SEPARATOR);
		}		
		return buff.toString();
	}
	
	public static PicDelayPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(PicDelayPersistence persistence) {
		_persistence = persistence;
	}

	private static PicDelayUtil _getUtil() {
		if (_util == null) {
			_util = (PicDelayUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = PicDelayUtil.class.getName();
	private static PicDelayUtil _util;
	private PicDelayPersistence _persistence;

}
