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
	 * Description:��������δ���������Ƭ������Ϣ
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
	 * Description:��ҳ��ѯ��Ƭ���õĵ�����Ϣ
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
	 * Description:ȡ��
	 * @param curStuempNo
	 * @throws PortalException
	 * Modify History:
	 */
	public  void cancelPicDelay(String curStuempNo) throws PortalException ;
	
}
