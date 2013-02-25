package com.sungard.smartcard.modules.system.dao;

import java.util.List;

import com.sungard.smartcard.domain.Msglist;

/**
 * 消息队列数据库操作类接口
 *
 * @author chuxiong.long
 * @version v1.00
 * @since 2012-02-23
 */
public interface MsglistDao {

	/**
	 * 根据msgid删除消息队列记录
	 * */
	public int deleteMsglist(int msgid);
	
	/**
	 * 根据msgid判断是否存在消息队列记录
	 * */
	public boolean isExistMsglist(int msgid);
	
	/**
	 * 根据条件查询
	 * */
	public List<Msglist> listMsglist(Msglist msglist );
	
	/**
	 * 根据msgid更新修改
	 * */
	public int updateMsglist(Msglist msglist);
}
