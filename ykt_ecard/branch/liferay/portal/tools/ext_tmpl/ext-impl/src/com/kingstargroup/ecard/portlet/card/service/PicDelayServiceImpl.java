package com.kingstargroup.ecard.portlet.card.service;

import java.util.Date;
import java.util.List;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.picdelay.EcardPicDelay;
import com.kingstargroup.ecard.hibernate.picdelay.PostponeFiles;
import com.kingstargroup.ecard.hibernate.util.ResultPage;
import com.kingstargroup.ecard.util.EcardConstants;


public class PicDelayServiceImpl extends PicDelayServiceBase {

	/**
	 * Description:
	 * @param oldStuempNo
	 * @param newStuempNo
	 * @throws PortalException
	 * Modify History:
	 */
	public  void add(String oldStuempNo, String newStuempNo) throws PortalException {
			EcardPicDelay delay = new EcardPicDelay();
			delay.setCurStuempNo(newStuempNo);
			delay.setOldStuempNo(oldStuempNo);
			delay.setStatus(EcardConstants.POSTPONE_STATUS_UNACCEPTED);
			picDelayPersistence.saveOrUpdate(delay);
	}
	
	/**
	 * Description:��������δ���������Ƭ������Ϣ
	 * @throws PortalException
	 * Modify History:
	 */
	public  byte[] updateDelays() throws PortalException {
		byte[] bytes = null;
			List unprocessedItems = picDelayPersistence.getDelays(EcardConstants.POSTPONE_STATUS_UNACCEPTED);			
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
				picDelayPersistence.addPostponeFile(file);			
				for (int i = 0; i < unprocessedItems.size(); i++) {
					EcardPicDelay delay = (EcardPicDelay) unprocessedItems.get(i);
					delay.setStatus(EcardConstants.POSTPONE_STATUS_ACCEPTED);
					picDelayPersistence.saveOrUpdate(delay);
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
	public  PostponeFiles getPostponeFile(int id) throws PortalException {
		return picDelayPersistence.getPostponeFile(id);			
	}
	
	public  ResultPage list(int page) throws PortalException {
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
	public  ResultPage list(int page, int size) throws PortalException {
			return picDelayPersistence.getPostponeFiles(page, size);

	}
	
	/**
	 * Description:
	 * @param curStuempId
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public  EcardPicDelay getDelayById(String curStuempId) throws PortalException {
			return picDelayPersistence.getDelayById(curStuempId);
	}
	
	public  int countUnprocessedDelays() throws PortalException {
			return picDelayPersistence.getDelays(EcardConstants.POSTPONE_STATUS_UNACCEPTED).size();

	}
	
	/**
	 * Description:ȡ��
	 * @param curStuempNo
	 * @throws PortalException
	 * Modify History:
	 */
	public  void cancelPicDelay(String curStuempNo) throws PortalException {
		picDelayPersistence.deleteDelayById(curStuempNo);
	}
	
	/**
	 * Description:������Ƭ������Ϣ��ӳ������
	 * @param delayList
	 * @return
	 * Modify History:
	 */
	 String createMappingTxt(List delayList){		
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
}
