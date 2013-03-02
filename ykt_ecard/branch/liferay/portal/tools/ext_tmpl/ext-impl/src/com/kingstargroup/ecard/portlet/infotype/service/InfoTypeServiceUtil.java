package com.kingstargroup.ecard.portlet.infotype.service;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.infotype.InfoType;
import com.kingstargroup.ecard.hibernate.util.ResultPage;

public class InfoTypeServiceUtil {
	
	public static  ResultPage getChildList(String id) throws PortalException{
		
		InfoTypeService infoTypeService = InfoTypeServiceFactory.getService();
		return infoTypeService.getChildList(id);
	}
	
	public static  ResultPage getChildList(String id, int page, int size)
	throws PortalException {
		InfoTypeService infoTypeService = InfoTypeServiceFactory.getService();
		return infoTypeService.getChildList(id, page, size);	
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
	public static void add(String parentId, String typeName)
			throws PortalException {
		InfoTypeService infoTypeService = InfoTypeServiceFactory.getService();
		infoTypeService.add(parentId, typeName);
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
	public static void updateType(String typeId, String typeName)
			throws PortalException {
		InfoTypeService infoTypeService = InfoTypeServiceFactory.getService();
		infoTypeService.updateType(typeId, typeName);
	}

	/**
	 * Description:��������ID�õ����Ͷ���
	 * 
	 * @param typeId
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public static InfoType getTypeById(String typeId) throws PortalException {
		InfoTypeService infoTypeService = InfoTypeServiceFactory.getService();
		return infoTypeService.getTypeById(typeId);
	}
	
	
	
	/**
	 * Description:ɾ��ָ������Ϣ����
	 * 
	 * @param ids
	 * @throws PortalException
	 *             Modify History:
	 */
	public static void deleteTypes(String[] ids) throws PortalException {
		InfoTypeService infoTypeService = InfoTypeServiceFactory.getService();
		infoTypeService.deleteTypes(ids);
		
	}
}
