package com.kingstargroup.ecard.portlet.infotype.service;

import java.util.List;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.infotype.InfoType;
import com.kingstargroup.ecard.hibernate.util.ResultPage;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.kernel.util.StringUtil;

public class InfoTypeServiceImpl extends InfoTypeServiceBase{

	
	public  ResultPage getChildList(String id) throws PortalException {
		return getChildList(id, 0, EcardConstants.MAX_RESULT_SIZE);
	}

	public  ResultPage getChildList(String id, int page, int size)
			throws PortalException {
		return infoTypePersistence.search(id + ".", null, page, size);

	}

	
	/**
	 * Description: ����һ���µ������͵�ָ���ĸ���������
	 * 
	 * @param parentId
	 *            ������ID
	 * @param typeName
	 *            Ҫ���ӵ���������
	 * @throws PortalException
	 *             Modify History:
	 */
	public  void add(String parentId, String typeName)
			throws PortalException {
		/*
		 * ��ȡ����Ҫ�����������ID
		 */
		List childList = getChildList(parentId).getList();
		StringBuffer newTypeId = new StringBuffer(parentId);
		int maxTypeId = 0;
		for (int i = 0; i < childList.size(); i++) {
			InfoType tmp = (InfoType) childList.get(i);
			int tmpTypeId = Integer.parseInt(StringUtil.split(
					tmp.getInfoType(), ".")[1]);
			if (tmpTypeId > maxTypeId) {
				maxTypeId = tmpTypeId;
			}
		}
		newTypeId.append(".").append(maxTypeId + 1);
		InfoType type = new InfoType();
		type.setInfoName(typeName);
		type.setInfoType(newTypeId.toString());
		infoTypePersistence.saveOrUpdate(type);
	}

	/**
	 * Description:���¶�Ӧ�����Ͷ���
	 * 
	 * @param typeId
	 *            ����ID
	 * @param typeName
	 *            ��������
	 * @throws PortalException
	 *             Modify History:
	 */
	public void updateType(String typeId, String typeName)
			throws PortalException {

		InfoType type = infoTypePersistence.getTypeById(typeId);
		if (type != null) {
			type.setInfoName(typeName);
			infoTypePersistence.saveOrUpdate(type);
		}
	}

	/**
	 * Description:��������ID�õ����Ͷ���
	 * 
	 * @param typeId
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public InfoType getTypeById(String typeId) throws PortalException {

		return infoTypePersistence.getTypeById(typeId);
	}

	
	/**
	 * Description:ɾ��ָ������Ϣ����
	 * 
	 * @param ids
	 * @throws PortalException
	 *             Modify History:
	 */
	public void deleteTypes(String[] ids) throws PortalException {
		infoTypePersistence.deleteTypesByIds(ids);
	}
	

}
