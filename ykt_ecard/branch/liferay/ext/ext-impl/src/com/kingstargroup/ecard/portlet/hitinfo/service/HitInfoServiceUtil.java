package com.kingstargroup.ecard.portlet.hitinfo.service;

import java.util.List;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.hitinfo.EcardHitInfo;
import com.kingstargroup.ecard.hibernate.util.ResultPage;

public class HitInfoServiceUtil {
	

	/**
	 * Description:添加一条滚动新闻
	 * 
	 * @param title
	 * @param mapInfoId
	 * @throws PortalException
	 *             Modify History:
	 */
	public static void add(String title, int mapInfoId) throws PortalException {
		HitInfoService hitInfoService = HitInfoServiceFactory.getService();
		hitInfoService.add(title, mapInfoId);
	}

	public static void update(int id, String title, int mapInfoId)
			throws PortalException {
		HitInfoService hitInfoService = HitInfoServiceFactory.getService();
		hitInfoService.update(id, title, mapInfoId);
	}

	public static void delete(String[] ids) throws PortalException {
		HitInfoService hitInfoService = HitInfoServiceFactory.getService();
		hitInfoService.delete(ids);
	}

	/**
	 * Description:返回需要显示的滚动新闻列表
	 * 
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public static ResultPage getHitInfos(int page) throws PortalException {
		HitInfoService hitInfoService = HitInfoServiceFactory.getService();
		return hitInfoService.getHitInfos(page);
	}
	
	public static ResultPage getHitInfos(int page, int size) throws PortalException {
		HitInfoService hitInfoService = HitInfoServiceFactory.getService();
		return hitInfoService.getHitInfos(page, size);
	}

	public static ResultPage search(String title, int page, int size)
			throws PortalException {
		HitInfoService hitInfoService = HitInfoServiceFactory.getService();
		return hitInfoService.search(title, page, size);
	}

	public static EcardHitInfo getHitInfo(String id) throws PortalException {
		HitInfoService hitInfoService = HitInfoServiceFactory.getService();
		return hitInfoService.getHitInfo(id);
	}
}
