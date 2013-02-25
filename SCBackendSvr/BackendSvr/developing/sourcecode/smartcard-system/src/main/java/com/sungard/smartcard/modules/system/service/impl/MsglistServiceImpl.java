package com.sungard.smartcard.modules.system.service.impl;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import com.sungard.smartcard.domain.Msglist;
import com.sungard.smartcard.modules.system.dao.MsglistDao;
import com.sungard.smartcard.modules.system.service.MsglistService;
/**
 * 消息队列业务处理实现
 * 
 * @author chuxiong.long
 * @version v1.00
 * @since 2012-02-23
 */
@Service
@Transactional
public class MsglistServiceImpl implements MsglistService{

	@Autowired
	@Qualifier("msglistDaoImpl")
	private MsglistDao msglistDao;

	/**
	 * 根据条件查询
	 * */
	@Override
	public List<Msglist> listMsglist(Msglist msglist) {
		return this.msglistDao.listMsglist(msglist);
	}
	
	/**
	 * 根据msgid删除消息队列记录
	 * */
	@Override
	public int deleteMsglist(int msgid) {
		return this.msglistDao.deleteMsglist(msgid);
	}

	/**
	 * 根据msgid判断是否存在消息队列记录
	 * */
	@Override
	public boolean isExistMsglist(int msgid) {
		return this.msglistDao.isExistMsglist(msgid);
	}
	/**
	 * 根据msgid修改保存
	 * */
	@Override
	public int updateMsglist(Msglist msglist) {
		return this.msglistDao.updateMsglist(msglist);
	}
	
	
	
}
