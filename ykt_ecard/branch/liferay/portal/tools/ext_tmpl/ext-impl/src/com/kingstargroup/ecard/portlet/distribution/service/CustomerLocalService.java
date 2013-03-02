package com.kingstargroup.ecard.portlet.distribution.service;

import java.util.HashMap;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.customer.TCustomer;

public interface CustomerLocalService {

	/**
	 * Description: 通过传入的客户号得到对应客户对象
	 * 
	 * @param customerId
	 *            传入客户号
	 * @return 客户对象 Modify History:
	 */
	public TCustomer getCustomerById(String customerId)
			throws PortalException;

	/**
	 * Description:根据学工号得到对应客户对象
	 * 
	 * @param stuempNo
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public TCustomer getCustomerByStuempNo(String stuempNo)
			throws PortalException;

	/**
	 * Description:根据用学/工号得到和客户相关的一些信息（卡信息等）
	 * 
	 * @param stuempNo
	 * @return
	 * @throws PortalException
	 *             Modify History: 2005-10-18 更换客户号为学工号
	 */
	public HashMap getRelatedCustomerInfo(String stuempNo)
			throws PortalException;

	public HashMap getRelatedCustomerInfo(String customerId, Long cardId)
			throws PortalException;
}
