package com.kingstargroup.ecard.portlet.infotype.service;

import java.util.List;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.infotype.InfoType;
import com.kingstargroup.ecard.hibernate.util.ResultPage;
import com.liferay.portal.kernel.util.StringUtil;

public interface InfoTypeService {
	
	public ResultPage getChildList(String id) throws PortalException;
	
	public  ResultPage getChildList(String id, int page, int size)
	throws PortalException;
	
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
			throws PortalException;
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
	public  void updateType(String typeId, String typeName)
			throws PortalException ;

	/**
	 * Description:��������ID�õ����Ͷ���
	 * 
	 * @param typeId
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public  InfoType getTypeById(String typeId) throws PortalException ;
	
	
	/**
	 * Description:ɾ��ָ������Ϣ����
	 * 
	 * @param ids
	 * @throws PortalException
	 *             Modify History:
	 */
	public void deleteTypes(String[] ids) throws PortalException;
}
