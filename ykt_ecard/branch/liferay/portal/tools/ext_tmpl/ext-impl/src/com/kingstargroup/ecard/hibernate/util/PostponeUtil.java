/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import java.util.Date;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.postpone.EcardPostponeApply;
import com.kingstargroup.ecard.hibernate.postpone.PostponePersistence;
import com.kingstargroup.ecard.util.EcardConstants;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: PostponeUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * ��������   ������   ����ʱ��     ��������<br>
 * ===================================<br>
 *  ����    Xiao Qi  2005-9-28  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class PostponeUtil {

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
			EcardPostponeApply apply = new EcardPostponeApply();
			apply.setStuempno(customerId);
			apply.setApplyTime(new Date());
			apply.setPostponeTime(postponeTime);
			apply.setReason(reason);
			apply.setCheckResult("");
			apply.setStatus(EcardConstants.POSTPONE_STATUS_UNACCEPTED);
			getPersistence().saveOrUpdate(apply);
	}
	
	/**
	 * Description:�������¿�����������Ϣ
	 * @param customerIds
	 * @param status
	 * @throws PortalException
	 * Modify History:
	 */
	public static void updatePostpones(String[] ids, String status) throws PortalException {
			for (int i = 0; i < ids.length; i++) {
				EcardPostponeApply apply = getPersistence().getPostpone(ids[i]);
				apply.setStatus(status);
				getPersistence().saveOrUpdate(apply);
			}			
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

			EcardPostponeApply apply = getPersistence().getPostpone(id);
			apply.setCheckResult(checkResult);
			apply.setStatus(status);
			getPersistence().saveOrUpdate(apply);
	}
	/**
	 * Description:
	 * @param stuempNo
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static EcardPostponeApply getPostponeByStuempNo(String stuempNo) throws PortalException {
			return getPersistence().getPostponeByStuempNo(stuempNo);
	}	
	
	/**
	 * Description:����ָ������������
	 * @param applyId
	 * @throws PortalException
	 * Modify History:
	 */
	public static void cancelPostpone(String applyId) throws PortalException {
		getPersistence().delete(applyId);
	}
	
	public static EcardPostponeApply getPostpone(String applyId) throws PortalException {
			return getPersistence().getPostpone(applyId);

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
			return getPersistence().search(status, page, size);

	}
	
	
	public static PostponePersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(PostponePersistence persistence) {
		_persistence = persistence;
	}

	private static PostponeUtil _getUtil() {
		if (_util == null) {
			_util = (PostponeUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = PostponeUtil.class.getName();
	private static PostponeUtil _util;
	private PostponePersistence _persistence;
}
