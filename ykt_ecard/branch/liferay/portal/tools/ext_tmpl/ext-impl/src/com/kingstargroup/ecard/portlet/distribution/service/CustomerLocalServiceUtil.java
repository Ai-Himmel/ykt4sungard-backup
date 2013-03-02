package com.kingstargroup.ecard.portlet.distribution.service;

import java.util.HashMap;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.customer.TCustomer;

public class CustomerLocalServiceUtil {
	
	/**
	 * Description: ͨ������Ŀͻ��ŵõ���Ӧ�ͻ�����
	 * @param customerId ����ͻ���
	 * @return �ͻ�����
	 * Modify History:
	 */
	public static TCustomer getCustomerById(String customerId) throws PortalException {
		CustomerLocalService customerLocalService = CustomerLocalServiceFactory.getService();
		return customerLocalService.getCustomerById(customerId);

	}
	
	/**
	 * Description:����ѧ���ŵõ���Ӧ�ͻ�����
	 * @param stuempNo
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static TCustomer getCustomerByStuempno(String stuempno) throws PortalException {
		CustomerLocalService customerLocalService = CustomerLocalServiceFactory.getService();
		return customerLocalService.getCustomerByStuempNo(stuempno);
	}
	
	/**
	 * Description:������ѧ/���ŵõ��Ϳͻ���ص�һЩ��Ϣ������Ϣ�ȣ�
	 * @param stuempNo
	 * @return
	 * @throws PortalException
	 * Modify History:
	 * 2005-10-18 �����ͻ���Ϊѧ����
	 */
	public static HashMap getRelatedCustomerInfo(String stuempNo) throws PortalException {
		CustomerLocalService customerLocalService = CustomerLocalServiceFactory.getService();
		return customerLocalService.getRelatedCustomerInfo(stuempNo);
	}
	
	public static HashMap getRelatedCustomerInfo(String customerId, Long cardno) throws PortalException {
		CustomerLocalService customerLocalService = CustomerLocalServiceFactory.getService();
		return customerLocalService.getRelatedCustomerInfo(customerId, cardno);
	}

}
