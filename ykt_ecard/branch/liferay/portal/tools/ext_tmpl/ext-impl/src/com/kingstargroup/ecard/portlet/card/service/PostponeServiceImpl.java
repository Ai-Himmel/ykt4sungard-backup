package com.kingstargroup.ecard.portlet.card.service;

import java.util.Date;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.postpone.EcardPostponeApply;
import com.kingstargroup.ecard.hibernate.util.ResultPage;
import com.kingstargroup.ecard.util.EcardConstants;

public class PostponeServiceImpl extends PostponeServiceBase {

	/**
	 * Description:
	 * @param reason
	 * @param customerId
	 * @param postponeTime
	 * @throws PortalException
	 * Modify History:
	 */
	public  void addPostpone(String reason, 
								String customerId, 
								String postponeTime) throws PortalException {
			EcardPostponeApply apply = new EcardPostponeApply();
			apply.setStuempno(customerId);
			apply.setApplyTime(new Date());
			apply.setPostponeTime(postponeTime);
			apply.setReason(reason);
			apply.setCheckResult("");
			apply.setStatus(EcardConstants.POSTPONE_STATUS_UNACCEPTED);
			postponePersistence.saveOrUpdate(apply);
	}
	
	/**
	 * Description:批量更新卡延期申请信息
	 * @param customerIds
	 * @param status
	 * @throws PortalException
	 * Modify History:
	 */
	public  void updatePostpones(String[] ids, String status) throws PortalException {
			for (int i = 0; i < ids.length; i++) {
				EcardPostponeApply apply =postponePersistence.getPostpone(ids[i]);
				apply.setStatus(status);
				postponePersistence.saveOrUpdate(apply);
			}			
	}
	
	/**
	 * Description:单独更新指定的一个申请信息
	 * @param customerId
	 * @param status
	 * @param checkResult
	 * @throws PortalException
	 * Modify History:
	 */
	public  void updatePostpone(String id, String status, String checkResult) throws PortalException {

			EcardPostponeApply apply = postponePersistence.getPostpone(id);
			apply.setCheckResult(checkResult);
			apply.setStatus(status);
			postponePersistence.saveOrUpdate(apply);
	}
	/**
	 * Description:
	 * @param stuempNo
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public  EcardPostponeApply getPostponeByStuempNo(String stuempNo) throws PortalException {
			return postponePersistence.getPostponeByStuempNo(stuempNo);
	}	
	
	/**
	 * Description:撤销指定卡延期申请
	 * @param applyId
	 * @throws PortalException
	 * Modify History:
	 */
	public  void cancelPostpone(String applyId) throws PortalException {
		postponePersistence.delete(applyId);
	}
	
	public  EcardPostponeApply getPostpone(String applyId) throws PortalException {
			return postponePersistence.getPostpone(applyId);

	}
	
	/**
	 * Description:分页列出所有人的申请信息
	 * @param page
	 * @param size
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public  ResultPage list(int page, int size) throws PortalException {
		return list("", page, size);
	}
	
	public  ResultPage list(String status, int page, int size) throws PortalException {
			return postponePersistence.search(status, page, size);

	}
}
