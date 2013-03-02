/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import java.util.Date;

import org.hibernate.Transaction;

import com.kingstargroup.ecard.common.BasicUtil;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.postpone.EcardPostponeApply;
import com.kingstargroup.ecard.hibernate.postpone.PostponePersistence;
import com.kingstargroup.ecard.util.EcardConstants;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: PostponeUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-9-28  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class PostponeUtil extends BasicUtil {

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
		PostponePersistence persistence = (PostponePersistence) getPersistence(PostponePersistence.class.getName());
		Transaction t = beginTransaction();
		try {
			EcardPostponeApply apply = new EcardPostponeApply();
			apply.setStuempno(customerId);
			apply.setApplyTime(new Date());
			apply.setPostponeTime(postponeTime);
			apply.setReason(reason);
			apply.setCheckResult("");
			apply.setStatus(EcardConstants.POSTPONE_STATUS_UNACCEPTED);
			persistence.saveOrUpdate(apply);
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
	}
	
	/**
	 * Description:批量更新卡延期申请信息
	 * @param customerIds
	 * @param status
	 * @throws PortalException
	 * Modify History:
	 */
	public static void updatePostpones(String[] ids, String status) throws PortalException {
		PostponePersistence persistence = (PostponePersistence) getPersistence(PostponePersistence.class.getName());
		Transaction t = beginTransaction();
		try {
			for (int i = 0; i < ids.length; i++) {
				EcardPostponeApply apply = persistence.getPostpone(ids[i]);
				apply.setStatus(status);
				persistence.saveOrUpdate(apply);
			}			
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
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
	public static void updatePostpone(String id, String status, String checkResult) throws PortalException {
		PostponePersistence persistence = (PostponePersistence) getPersistence(PostponePersistence.class.getName());
		Transaction t = beginTransaction();
		try {
			EcardPostponeApply apply = persistence.getPostpone(id);
			apply.setCheckResult(checkResult);
			apply.setStatus(status);
			persistence.saveOrUpdate(apply);
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
	}
	/**
	 * Description:
	 * @param stuempNo
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static EcardPostponeApply getPostponeByStuempNo(String stuempNo) throws PortalException {
		PostponePersistence persistence = (PostponePersistence) getPersistence(PostponePersistence.class.getName());
		Transaction t = beginTransaction();
		EcardPostponeApply apply = null;		
		try {
			apply = persistence.getPostponeByStuempNo(stuempNo);
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
		return apply;
	}	
	
	/**
	 * Description:撤销指定卡延期申请
	 * @param applyId
	 * @throws PortalException
	 * Modify History:
	 */
	public static void cancelPostpone(String applyId) throws PortalException {
		PostponePersistence persistence = (PostponePersistence) getPersistence(PostponePersistence.class.getName());
		Transaction t = beginTransaction();
		try {
			persistence.delete(applyId);
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
	}
	
	public static EcardPostponeApply getPostpone(String applyId) throws PortalException {
		PostponePersistence persistence = (PostponePersistence) getPersistence(PostponePersistence.class.getName());
		Transaction t = beginTransaction();
		EcardPostponeApply apply = null;
		try {
			apply = persistence.getPostpone(applyId);
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
		return apply;
	}
	
	/**
	 * Description:分页列出所有人的申请信息
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
		PostponePersistence persistence = (PostponePersistence) getPersistence(PostponePersistence.class.getName());
		Transaction t = beginTransaction();
		ResultPage result = null;		
		try {
			result = persistence.search(status, page, size);
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
		return result;
	}
}
