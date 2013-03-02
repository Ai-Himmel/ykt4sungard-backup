package com.kingstargroup.ecard.portlet.card.service;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.picdelay.EcardPicDelay;
import com.kingstargroup.ecard.hibernate.picdelay.PostponeFiles;
import com.kingstargroup.ecard.hibernate.util.ResultPage;

public interface PicDelayService {

	/**
	 * Description:
	 * @param oldStuempNo
	 * @param newStuempNo
	 * @throws PortalException
	 * Modify History:
	 */
	public  void add(String oldStuempNo, String newStuempNo) throws PortalException ;
	
	/**
	 * Description:更新所有未被处理的照片延用信息
	 * @throws PortalException
	 * Modify History:
	 */
	public  byte[] updateDelays() throws PortalException ;
	
	/**
	 * Description:
	 * @param id
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public  PostponeFiles getPostponeFile(int id) throws PortalException;
	
	public  ResultPage list(int page) throws PortalException ;
	/**
	 * Description:分页查询照片延用的导出信息
	 * @param page
	 * @param size
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public  ResultPage list(int page, int size) throws PortalException ;
	
	/**
	 * Description:
	 * @param curStuempId
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public  EcardPicDelay getDelayById(String curStuempId) throws PortalException ;
	
	public  int countUnprocessedDelays() throws PortalException ;
	
	/**
	 * Description:取消
	 * @param curStuempNo
	 * @throws PortalException
	 * Modify History:
	 */
	public  void cancelPicDelay(String curStuempNo) throws PortalException ;
	
}
