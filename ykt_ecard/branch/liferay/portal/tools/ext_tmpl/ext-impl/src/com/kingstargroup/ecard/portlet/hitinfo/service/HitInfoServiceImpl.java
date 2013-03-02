package com.kingstargroup.ecard.portlet.hitinfo.service;

import java.util.List;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.hitinfo.EcardHitInfo;
import com.kingstargroup.ecard.hibernate.util.ResultPage;
import com.kingstargroup.ecard.util.EcardConstants;

public class HitInfoServiceImpl extends HitInfoServiceBase {

	/**
	 * Description:添加一条滚动新闻
	 * 
	 * @param title
	 * @param mapInfoId
	 * @throws PortalException
	 *             Modify History:
	 */
	public void add(String title, int mapInfoId) throws PortalException {
		EcardHitInfo info = new EcardHitInfo();
		info.setInfoId(new Integer(mapInfoId));
		info.setTitle(title);
		hitInfoPersistence.save(info);
	}

	public void update(int id, String title, int mapInfoId)
			throws PortalException {
		EcardHitInfo info = (EcardHitInfo) hitInfoPersistence.findByPrimaryKey(
				EcardHitInfo.class, new Integer(id));
		if (info != null) {
			info.setInfoId(new Integer(mapInfoId));
			info.setTitle(title);
			hitInfoPersistence.saveOrUpdate(info);
		}
	}

	public void delete(String[] ids) throws PortalException {
		try {
			hitInfoPersistence.delete(ids);
		} catch (DBSystemException ex) {
			ex.printStackTrace();
			throw ex;
		}
	}

	/**
	 * Description:返回需要显示的滚动新闻列表
	 * 
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public List getHitInfos() throws PortalException {
		return hitInfoPersistence.search("", 0, EcardConstants.HIT_INFO_SIZE)
				.getList();
	}

	public ResultPage search(String title, int page, int size)
			throws PortalException {
		return hitInfoPersistence.search(title, page, size);
	}

	public EcardHitInfo getHitInfo(String id) throws PortalException {
		return (EcardHitInfo) hitInfoPersistence.findByPrimaryKey(
				EcardHitInfo.class, Integer.valueOf(id));
	}

}
