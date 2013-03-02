package com.kingstargroup.ecard.portlet.card.service;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.postpone.EcardPostponeApply;
import com.kingstargroup.ecard.hibernate.util.ResultPage;

public interface PostponeService {

	/**
	 * Description:
	 * 
	 * @param reason
	 * @param customerId
	 * @param postponeTime
	 * @throws PortalException
	 *             Modify History:
	 */
	public void addPostpone(String reason, String customerId,
			String postponeTime) throws PortalException;

	/**
	 * Description:�������¿�����������Ϣ
	 * 
	 * @param customerIds
	 * @param status
	 * @throws PortalException
	 *             Modify History:
	 */
	public void updatePostpones(String[] ids, String status)
			throws PortalException;

	/**
	 * Description:��������ָ����һ��������Ϣ
	 * 
	 * @param customerId
	 * @param status
	 * @param checkResult
	 * @throws PortalException
	 *             Modify History:
	 */
	public void updatePostpone(String id, String status, String checkResult)
			throws PortalException;

	/**
	 * Description:
	 * 
	 * @param stuempNo
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public EcardPostponeApply getPostponeByStuempNo(String stuempNo)
			throws PortalException;

	/**
	 * Description:����ָ������������
	 * 
	 * @param applyId
	 * @throws PortalException
	 *             Modify History:
	 */
	public void cancelPostpone(String applyId) throws PortalException;

	public EcardPostponeApply getPostpone(String applyId)
			throws PortalException;

	/**
	 * Description:��ҳ�г������˵�������Ϣ
	 * 
	 * @param page
	 * @param size
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public ResultPage list(int page, int size) throws PortalException;

	public ResultPage list(String status, int page, int size)
			throws PortalException;

}
