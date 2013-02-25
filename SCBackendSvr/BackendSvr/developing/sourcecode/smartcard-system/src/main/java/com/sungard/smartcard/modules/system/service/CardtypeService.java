/*
 * CardtypeService.java  v1.00  2012-2-22
 * Peoject	smartcard-system
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	CardtypeService.java  v1.00 2012-2-22
 * Project	: 	smartcard-system
 * Copyight	:	Copyright (c) 2012 Sungard.China.HE
 */
package com.sungard.smartcard.modules.system.service;

import java.util.List;

import com.sungard.smartcard.domain.Cardtype;
import com.sungard.smartcard.exception.FunctionException;

/**
 * [TODO 类功能说明、代码引用实例.]
 * 
 * @author <a href=mailto:xinxing.cheng@sungard.com.cn">程新兴</a>
 * @version v1.00
 * @since 1.00 2012-2-22
 * 
 */
public interface CardtypeService {
	public boolean add(Cardtype cardtype) throws FunctionException;
	public boolean delete(int cardtype) throws FunctionException;
	public boolean update(Cardtype cardtype) throws FunctionException;
	public List<Cardtype> query(Cardtype cardtype) throws FunctionException; 
}
