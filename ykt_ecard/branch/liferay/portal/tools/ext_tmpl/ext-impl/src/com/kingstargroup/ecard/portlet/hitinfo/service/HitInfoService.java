package com.kingstargroup.ecard.portlet.hitinfo.service;

import java.util.List;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.hitinfo.EcardHitInfo;
import com.kingstargroup.ecard.hibernate.util.ResultPage;

public interface HitInfoService {

	/**
	 * Description:���һ����������
	 * 
	 * @param title
	 * @param mapInfoId
	 * @throws PortalException
	 *             Modify History:
	 */
	public void add(String title, int mapInfoId) throws PortalException;

	public void update(int id, String title, int mapInfoId)
			throws PortalException;

	public void delete(String[] ids) throws PortalException;

	/**
	 * Description:������Ҫ��ʾ�Ĺ��������б�
	 * 
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public List getHitInfos() throws PortalException;

	public ResultPage search(String title, int page, int size)
			throws PortalException;

	public EcardHitInfo getHitInfo(String id) throws PortalException;
}
