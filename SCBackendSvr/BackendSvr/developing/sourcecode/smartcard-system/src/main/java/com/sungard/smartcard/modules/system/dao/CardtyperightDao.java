/*
 * CardtyperightDao.java  v1.00  2012-2-22
 * Peoject	smartcard-system
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	CardtyperightDao.java  v1.00 2012-2-22
 * Project	: 	smartcard-system
 * Copyight	:	Copyright (c) 2012 Sungard.China.HE
 */
package com.sungard.smartcard.modules.system.dao;

import java.util.List;

import com.sungard.smartcard.domain.Cardtyperight;

/**
 * [TODO 发卡权限.]
 * 
 * @author <a href=mailto:xinxing.cheng@sungard.com.cn">程新兴</a>
 * @version v1.00
 * @since 1.00 2012-2-22
 * 
 */
public interface CardtyperightDao {
	public List<Cardtyperight> findall();
	public List<Cardtyperight> findByparam(String sql,Object[] arg);
	public List<Cardtyperight> findCardtyperight(Cardtyperight cardtyperight);
	public Cardtyperight getCardtyperight(Integer cardtype,Integer feetype);
	public int delete(Integer cardtype,Integer feetype);
	public int update(Cardtyperight cardtyperight);
	public int add(Cardtyperight cardtyperight);
}
