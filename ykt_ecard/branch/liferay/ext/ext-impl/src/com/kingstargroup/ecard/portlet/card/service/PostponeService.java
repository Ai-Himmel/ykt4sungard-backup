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
	 * Description:批量更新卡延期申请信息
	 * 
	 * @param customerIds
	 * @param status
	 * @throws PortalException
	 *             Modify History:
	 */
	public void updatePostpones(String[] ids, String status)
			throws PortalException;

	/**
	 * Description:单独更新指定的一个申请信息
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
	 * Description:撤销指定卡延期申请
	 * 
	 * @param applyId
	 * @throws PortalException
	 *             Modify History:
	 */
	public void cancelPostpone(String applyId) throws PortalException;

	public EcardPostponeApply getPostpone(String applyId)
			throws PortalException;

	/**
	 * Description:分页列出所有人的申请信息
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
