/*
 * CardtypeDao.java  v1.00  2012-2-22
 * Peoject	smartcard-system
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	CardtypeDao.java  v1.00 2012-2-22
 * Project	: 	smartcard-system
 * Copyight	:	Copyright (c) 2012 Sungard.China.HE
 */
package com.sungard.smartcard.modules.system.dao;

import java.util.List;

import com.sungard.smartcard.domain.Cardtype;

/**
 * [TODO 卡类别.]
 * 
 * @author <a href=mailto:xinxing.cheng@sungard.com.cn">程新兴</a>
 * @version v1.00
 * @since 1.00 2012-2-22
 * 
 */
public interface CardtypeDao {
	public List<Cardtype> findAll();
	public List<Cardtype> findbyparam(String sql,Object[] arg);
	public List<Cardtype> findCardtype(Cardtype cardtype);
	public Cardtype getCardtype(String cardtype);
	public int delete(String cardtype);
	public int update(Cardtype cardtype);
	public int add(Cardtype cardtype);
	public int getNetCardtype();
}
