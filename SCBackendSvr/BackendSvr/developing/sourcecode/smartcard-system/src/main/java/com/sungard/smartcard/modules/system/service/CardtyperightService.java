/*
 * CardtyperightService.java  v1.00  2012-2-22
 * Peoject	smartcard-system
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	CardtyperightService.java  v1.00 2012-2-22
 * Project	: 	smartcard-system
 * Copyight	:	Copyright (c) 2012 Sungard.China.HE
 */
package com.sungard.smartcard.modules.system.service;

import java.util.List;

import com.sungard.smartcard.domain.Cardtyperight;
import com.sungard.smartcard.exception.FunctionException;

/**
 * [TODO 发卡权限维护.]
 * 
 * @author <a href=mailto:xinxing.cheng@sungard.com.cn">程新兴</a>
 * @version v1.00
 * @since 1.00 2012-2-22
 * 
 */
public interface CardtyperightService {
	public int addCardtyperight(Cardtyperight cardtyperight) throws FunctionException;
	public int deleteCardtyperight(Cardtyperight cardtyperight) throws FunctionException;
	public List<Cardtyperight> queryCardtyperight(Cardtyperight cardtyperight) throws FunctionException;
}
