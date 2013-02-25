/*
 * TcfgfeeDao.java  v1.00  2012-2-21
 * Peoject	smartcard-system
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	TcfgfeeDao.java  v1.00 2012-2-21
 * Project	: 	smartcard-system
 * Copyight	:	Copyright (c) 2012 Sungard.China.HE
 */
package com.sungard.smartcard.modules.system.dao;

import java.util.List;

import com.sungard.smartcard.domain.Cfgfee;
import com.sungard.smartcard.domain.Transtype;

/**
 * [TODO 交易信息维护.]
 * 
 * @author <a href=mailto:xinxing.cheng@sungard.com.cn">程新兴</a>
 * @version v1.00
 * @since 1.00 2012-2-21
 * 
 */
public interface CfgfeeDao {
	public List<Cfgfee> findCfgfee();
	public  List<Cfgfee> findCfgfee(String sql,Object[] args);
	public List<Cfgfee> findCfgfee(Cfgfee cfgfee);
	public int add(Cfgfee cfgfee);
	public int update(Cfgfee cfgfee);
	public int delete(String sql,Object[] args);
	public int delete(Integer feetype,Integer transcode,Integer cardtype,Integer transtype);
	public int update(String sql,Object[] args);
	public Cfgfee getCfgfee(Integer feetype,Integer transcode,Integer cardtype,Integer transtype);
	public Transtype getTranstype(int transtype);
}
