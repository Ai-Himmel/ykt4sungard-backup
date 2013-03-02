package com.kingstargroup.ecard.portlet.msgboard.service;

import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.msgboard.EcardMsgboard;
import com.kingstargroup.ecard.hibernate.util.ResultPage;

public interface MsgBoardService {

	/**
	 * Description:
	 * 
	 * @param id
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public EcardMsgboard getMsg(int id) throws PortalException;

	/**
	 * Description:增加一条新的留言信息
	 * 
	 * @param title
	 * @param postContent
	 * @param poster
	 * @throws PortalException
	 *             Modify History:
	 */
	public void addMsg(String title, String postContent, String poster)
			throws PortalException;

	/**
	 * Description:回复留言
	 * 
	 * @param id
	 * @param replyContent
	 * @param replyer
	 * @throws PortalException
	 *             Modify History:
	 */
	public void replyMsg(int id, String replyContent, String replyer)
			throws PortalException;

	/**
	 * Description:
	 * 
	 * @param ids
	 * @throws PortalException
	 *             Modify History:
	 */
	public void deleteMsgs(int ids[]) throws PortalException;

	public ResultPage list() throws PortalException;

	public ResultPage list(int page) throws PortalException;

	public ResultPage list(int page, int size) throws PortalException;

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
	public ResultPage list(String title, String content, int page, int size)
			throws PortalException;

}
