package com.kingstargroup.ecard.portlet.distribution.service;

import java.util.HashMap;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.customer.TCustomer;

public interface CustomerLocalService {

	/**
	 * Description: ͨ������Ŀͻ��ŵõ���Ӧ�ͻ�����
	 * 
	 * @param customerId
	 *            ����ͻ���
	 * @return �ͻ����� Modify History:
	 */
	public TCustomer getCustomerById(String customerId)
			throws PortalException;

	/**
	 * Description:����ѧ���ŵõ���Ӧ�ͻ�����
	 * 
	 * @param stuempNo
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public TCustomer getCustomerByStuempNo(String stuempNo)
			throws PortalException;

	/**
	 * Description:������ѧ/���ŵõ��Ϳͻ���ص�һЩ��Ϣ������Ϣ�ȣ�
	 * 
	 * @param stuempNo
	 * @return
	 * @throws PortalException
	 *             Modify History: 2005-10-18 �����ͻ���Ϊѧ����
	 */
	public HashMap getRelatedCustomerInfo(String stuempNo)
			throws PortalException;

	public HashMap getRelatedCustomerInfo(String customerId, Long cardId)
			throws PortalException;
}
