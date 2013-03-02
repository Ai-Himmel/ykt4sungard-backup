package com.kingstargroup.ecard.portlet.card.service;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.picdelay.EcardPicDelay;
import com.kingstargroup.ecard.hibernate.picdelay.PostponeFiles;
import com.kingstargroup.ecard.hibernate.util.ResultPage;

public class PicDelayServiceUtil {
	
	/**
	 * Description:
	 * @param oldStuempNo
	 * @param newStuempNo
	 * @throws PortalException
	 * Modify History:
	 */
	public static void add(String oldStuempNo, String newStuempNo) throws PortalException {
			PicDelayService picDelayService = PicDelayServiceFactory.getService();
			picDelayService.add(oldStuempNo, newStuempNo);
	}
	
	/**
	 * Description:更新所有未被处理的照片延用信息
	 * @throws PortalException
	 * Modify History:
	 */
	public static byte[] updateDelays() throws PortalException {
		PicDelayService picDelayService = PicDelayServiceFactory.getService();
		return picDelayService.updateDelays();
	}
	
	/**
	 * Description:
	 * @param id
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static PostponeFiles getPostponeFile(int id) throws PortalException {
		PicDelayService picDelayService = PicDelayServiceFactory.getService();
		return  picDelayService.getPostponeFile(id);		
	}
	
	public static ResultPage list(int page) throws PortalException {
		PicDelayService picDelayService = PicDelayServiceFactory.getService();
		return picDelayService.list(page);
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
		PicDelayService picDelayService = PicDelayServiceFactory.getService();
		return picDelayService.list(page, size);

	}
	
	/**
	 * Description:
	 * @param curStuempId
	 * @return
	 * @throws DBSystemException
	 * Modify History:
	 */
	public static EcardPicDelay getDelayById(String curStuempId) throws PortalException {
		PicDelayService picDelayService = PicDelayServiceFactory.getService();
		return picDelayService.getDelayById(curStuempId);
	}
	
	public static int countUnprocessedDelays() throws PortalException {
		PicDelayService picDelayService = PicDelayServiceFactory.getService();
		return picDelayService.countUnprocessedDelays();
	}
	
	/**
	 * Description:取消
	 * @param curStuempNo
	 * @throws PortalException
	 * Modify History:
	 */
	public static void cancelPicDelay(String curStuempNo) throws PortalException {
		PicDelayService picDelayService = PicDelayServiceFactory.getService();
		picDelayService.cancelPicDelay(curStuempNo);
	}
}
