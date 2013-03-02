package com.kingstargroup.ecard.portlet.msgboard.service;

import java.util.Date;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.msgboard.EcardMsgboard;
import com.kingstargroup.ecard.hibernate.util.ResultPage;
import com.kingstargroup.ecard.util.EcardConstants;

public class MsgBoardServiceImpl extends MsgBoardServiceBase{


	/**
	 * Description:
	 * 
	 * @param id
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public  EcardMsgboard getMsg(int id) throws PortalException {

		return msgBoardPersistence.getMsg(id);

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
	public  void addMsg(String title, String postContent, String poster)
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
		msgBoardPersistence.saveOrUpdate(msg);

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
	public  void replyMsg(int id, String replyContent, String replyer)
			throws PortalException {
		EcardMsgboard msg = msgBoardPersistence.getMsg(id);
		if (msg != null) {
			msg.setReplyContent(replyContent);
			msg.setReplyer(replyer);
			msg.setReplyTime(new Date());
			msg.setStatus(EcardConstants.MSG_REPLIED);
			msgBoardPersistence.saveOrUpdate(msg);
		}
	}

	/**
	 * Description:
	 * 
	 * @param ids
	 * @throws PortalException
	 *             Modify History:
	 */
	public  void deleteMsgs(int ids[]) throws PortalException {
		msgBoardPersistence.deleteMsgs(ids);

	}

	public  ResultPage list() throws PortalException {
		return list(0);
	}

	public  ResultPage list(int page) throws PortalException {
		return list(page, EcardConstants.DEFAULT_RESULT_SIZE);
	}

	public  ResultPage list(int page, int size) throws PortalException {
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
	public  ResultPage list(String title, String content, int page,
			int size) throws PortalException {
		return msgBoardPersistence.search(title, content, page, size);
	}
	

}
