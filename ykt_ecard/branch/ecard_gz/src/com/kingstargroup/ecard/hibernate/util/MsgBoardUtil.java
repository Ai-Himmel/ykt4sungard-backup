/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import java.util.Date;

import org.hibernate.Transaction;

import com.kingstargroup.ecard.common.BasicUtil;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.msgboard.EcardMsgboard;
import com.kingstargroup.ecard.hibernate.msgboard.MsgBoardPersistence;
import com.kingstargroup.ecard.util.EcardConstants;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: MsgBoardUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-10-11  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class MsgBoardUtil extends BasicUtil {

	/**
	 * Description:
	 * @param id
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static EcardMsgboard getMsg(int id) throws PortalException {
		MsgBoardPersistence persistence = (MsgBoardPersistence) getPersistence(MsgBoardPersistence.class.getName());
		Transaction t = beginTransaction();
		EcardMsgboard msg = null;
		
		try {
			msg = persistence.getMsg(id);
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
		return msg;
	}
	
	/**
	 * Description:增加一条新的留言信息
	 * @param title
	 * @param postContent
	 * @param poster
	 * @throws PortalException
	 * Modify History:
	 */
	public static void addMsg(String title, 
							String postContent, 
							String poster) throws PortalException {
		MsgBoardPersistence persistence = 
						(MsgBoardPersistence) getPersistence(MsgBoardPersistence.class.getName());
		Transaction t = beginTransaction();
		try {
			EcardMsgboard msg = new EcardMsgboard();
			msg.setMsgTitle(title);
			msg.setPostContent(postContent);
			msg.setPoster(poster);
			msg.setStatus(EcardConstants.MSG_NO_REPLY);
			msg.setPostTime(new Date());
			msg.setReplyContent("");
			msg.setReplyer("");
			msg.setReplyTime(new Date());
			persistence.saveOrUpdate(msg);
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
	}
	
	/**
	 * Description:回复留言
	 * @param id
	 * @param replyContent
	 * @param replyer
	 * @throws PortalException
	 * Modify History:
	 */
	public static void replyMsg(int id, String replyContent, String replyer) throws PortalException {
		MsgBoardPersistence persistence = 
			(MsgBoardPersistence) getPersistence(MsgBoardPersistence.class.getName());
		Transaction t = beginTransaction();
		try {
			EcardMsgboard msg = persistence.getMsg(id);
			msg.setReplyContent(replyContent);
			msg.setReplyer(replyer);
			msg.setReplyTime(new Date());
			msg.setStatus(EcardConstants.MSG_REPLIED);			
			persistence.saveOrUpdate(msg);
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
	 * @param ids
	 * @throws PortalException
	 * Modify History:
	 */
	public static void deleteMsgs(int ids[]) throws PortalException {		
		MsgBoardPersistence persistence = 
			(MsgBoardPersistence) getPersistence(MsgBoardPersistence.class.getName());
		Transaction t = beginTransaction();
		try {			
			persistence.deleteMsgs(ids);
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
	}
	
	public static ResultPage list() throws PortalException {
		return list(0);
	}
	
	public static ResultPage list(int page) throws PortalException {
		return list(page, EcardConstants.DEFAULT_RESULT_SIZE);
	}
	
	public static ResultPage list(int page, int size) throws PortalException {
		return list(null, null, page, size);
	}
	
	/**
	 * Description:根据查询项得到符合条件的留言记录
	 * @param title
	 * @param content
	 * @param page
	 * @param size
	 * @return
	 * @throws PortalException
	 * Modify History:
	 */
	public static ResultPage list(String title, String content, int page, int size) throws PortalException {
		MsgBoardPersistence persistence = 
			(MsgBoardPersistence) getPersistence(MsgBoardPersistence.class.getName());
		Transaction t = beginTransaction();
		ResultPage result = null;		
		try {
			result = persistence.search(title, content, page, size);
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
