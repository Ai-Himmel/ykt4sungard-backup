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
	 * Description:更新所有未被处理的照片延用信息
	 * @throws PortalException
	 * Modify History:
	 */
	public  byte[] updateDelays() throws PortalException {
		byte[] bytes = null;
			List unprocessedItems = picDelayPersistence.getDelays(EcardConstants.POSTPONE_STATUS_UNACCEPTED);			
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
	 * Description:分页查询照片延用的导出信息
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
	 * Description:取消
	 * @param curStuempNo
	 * @throws PortalException
	 * Modify History:
	 */
	public  void cancelPicDelay(String curStuempNo) throws PortalException {
		picDelayPersistence.deleteDelayById(curStuempNo);
	}
	
	/**
	 * Description:生成照片延用信息的映射内容
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
