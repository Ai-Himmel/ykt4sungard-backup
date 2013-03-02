/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import java.util.Date;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.msgboard.EcardMsgboard;
import com.kingstargroup.ecard.hibernate.msgboard.MsgBoardPersistence;
import com.kingstargroup.ecard.util.EcardConstants;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: MsgBoardUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型 操作人 操作时间 操作内容<br>
 * ===================================<br>
 * 创建 Xiao Qi 2005-10-11 <br>
 * 
 * @author Xiao Qi
 * @version
 * @since 1.0
 */
public class MsgBoardUtil {

	/**
	 * Description:
	 * 
	 * @param id
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public static EcardMsgboard getMsg(int id) throws PortalException {

		return getPersistence().getMsg(id);

	}

	/**
	 * Description:增加一条新的留言信息
	 * 
	 * @param title
	 * @param postContent
	 * @param poster
	 * @throws PortalException
	 *             Modify History:
	 */
	public static void addMsg(String title, String postContent, String poster)
			throws PortalException {

		EcardMsgboard msg = new EcardMsgboard();
		msg.setMsgTitle(title);
		msg.setPostContent(postContent);
		msg.setPoster(poster);
		msg.setStatus(EcardConstants.MSG_NO_REPLY);
		msg.setPostTime(new Date());
		msg.setReplyContent("");
		msg.setReplyer("");
		msg.setReplyTime(new Date());
		getPersistence().saveOrUpdate(msg);

	}

	/**
	 * Description:回复留言
	 * 
	 * @param id
	 * @param replyContent
	 * @param replyer
	 * @throws PortalException
	 *             Modify History:
	 */
	public static void replyMsg(int id, String replyContent, String replyer)
			throws PortalException {
		EcardMsgboard msg = getPersistence().getMsg(id);
		if (msg != null) {
			msg.setReplyContent(replyContent);
			msg.setReplyer(replyer);
			msg.setReplyTime(new Date());
			msg.setStatus(EcardConstants.MSG_REPLIED);
			getPersistence().saveOrUpdate(msg);
		}
	}

	/**
	 * Description:
	 * 
	 * @param ids
	 * @throws PortalException
	 *             Modify History:
	 */
	public static void deleteMsgs(int ids[]) throws PortalException {
			getPersistence().deleteMsgs(ids);

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
	 * 
	 * @param title
	 * @param content
	 * @param page
	 * @param size
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public static ResultPage list(String title, String content, int page,
			int size) throws PortalException {
		return getPersistence().search(title, content, page, size);
	}

	public static MsgBoardPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(MsgBoardPersistence persistence) {
		_persistence = persistence;
	}

	private static MsgBoardUtil _getUtil() {
		if (_util == null) {
			_util = (MsgBoardUtil) com.liferay.portal.kernel.bean.BeanLocatorUtil
					.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = MsgBoardUtil.class.getName();
	private static MsgBoardUtil _util;
	private MsgBoardPersistence _persistence;
}
