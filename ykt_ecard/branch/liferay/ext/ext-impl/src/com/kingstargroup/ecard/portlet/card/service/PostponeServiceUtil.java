package com.kingstargroup.ecard.portlet.card.service;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.postpone.EcardPostponeApply;
import com.kingstargroup.ecard.hibernate.util.ResultPage;

public class PostponeServiceUtil {
	
	/**
	 * Description:
	 * @param reason
	 * @param customerId
	 * @param postponeTime
	 * @throws PortalException
	 * Modify History:
	 */
	public static void addPostpone(String reason, 
								String customerId, 
								String postponeTime) throws PortalException {
			PostponeService postponeService = PostponeServiceFactory.getService();
			postponeService.addPostpone(reason, customerId, postponeTime);
	}
	
	/**
	 * Description:�������¿�����������Ϣ
	 * @param customerIds
	 * @param status
	 * @throws PortalException
	 * Modify History:
	 */
	public static void updatePostpones(String[] ids, String status) throws PortalException {
		PostponeService postponeService = PostponeServiceFactory.getService();
		postponeService.updatePostpones(ids, status);		
	}
	
	/**
	 * Description:��������ָ����һ��������Ϣ
	 * @param customerId
	 * @param status
	 * @param checkResult
	 * @throws PortalException
	 * Modify History:
	 */
	public static void updatePostpone(String id, String status, String checkResult) throws PortalException {
		PostponeService postponeService = PostponeServiceFactory.getService();
		postponeService.updatePostpone(id, status, checkResult);
	}
	/**
	 * Description:
	 * @param stuempNo
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static EcardPostponeApply getPostponeByStuempNo(String stuempNo) throws PortalException {
		PostponeService postponeService = PostponeServiceFactory.getService();
		return postponeService.getPostponeByStuempNo(stuempNo);
	}	
	
	/**
	 * Description:����ָ������������
	 * @param applyId
	 * @throws PortalException
	 * Modify History:
	 */
	public static void cancelPostpone(String applyId) throws PortalException {
		PostponeService postponeService = PostponeServiceFactory.getService();
		postponeService.cancelPostpone(applyId);
	}
	
	public static EcardPostponeApply getPostpone(String applyId) throws PortalException {
		PostponeService postponeService = PostponeServiceFactory.getService();
		return postponeService.getPostpone(applyId);
	}
	
	/**
	 * Description:��ҳ�г������˵�������Ϣ
	 * @param page
	 * @param size
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static ResultPage list(int page, int size) throws PortalException {
		return list("", page, size);
	}
	
	public static ResultPage list(String status, int page, int size) throws PortalException {
		PostponeService postponeService = PostponeServiceFactory.getService();
		return postponeService.list(status, page, size);

	}

}
