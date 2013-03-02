package com.kingstargroup.ecard.portlet.msgboard.service;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.msgboard.EcardMsgboard;
import com.kingstargroup.ecard.hibernate.util.ResultPage;
import com.kingstargroup.ecard.util.EcardConstants;

public class MsgBoardServiceUtil {
	

	/**
	 * Description:
	 * 
	 * @param id
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public static EcardMsgboard getMsg(int id) throws PortalException {
		MsgBoardService msgBoardService = MsgBoardServiceFactory.getService();
		return msgBoardService.getMsg(id);

	}

	/**
	 * Description:����һ���µ�������Ϣ
	 * 
	 * @param title
	 * @param postContent
	 * @param poster
	 * @throws PortalException
	 *             Modify History:
	 */
	public static void addMsg(String title, String postContent, String poster)
			throws PortalException {
		MsgBoardService msgBoardService = MsgBoardServiceFactory.getService();
		msgBoardService.addMsg(title, postContent, poster);

	}

	/**
	 * Description:�ظ�����
	 * 
	 * @param id
	 * @param replyContent
	 * @param replyer
	 * @throws PortalException
	 *             Modify History:
	 */
	public static void replyMsg(int id, String replyContent, String replyer)
			throws PortalException {
		MsgBoardService msgBoardService = MsgBoardServiceFactory.getService();
		msgBoardService.replyMsg(id, replyContent, replyer);
	}

	/**
	 * Description:
	 * 
	 * @param ids
	 * @throws PortalException
	 *             Modify History:
	 */
	public static void deleteMsgs(int ids[]) throws PortalException {
		MsgBoardService msgBoardService = MsgBoardServiceFactory.getService();
		msgBoardService.deleteMsgs(ids);
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
	 * Description:���ݲ�ѯ��õ��������������Լ�¼
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
		MsgBoardService msgBoardService = MsgBoardServiceFactory.getService();
		return msgBoardService.list(title, content, page, size);
	}
}
