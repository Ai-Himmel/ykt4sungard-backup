/*
 * FeetypeService.java  v1.00  2012-2-20
 * Peoject	smartcard-system
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	FeetypeService.java  v1.00 2012-2-20
 * Project	: 	smartcard-system
 * Copyight	:	Copyright (c) 2012 Sungard.China.HE
 */
package com.sungard.smartcard.modules.system.service;

import java.util.List;

import com.sungard.smartcard.domain.Feetype;
import com.sungard.smartcard.exception.FunctionException;

/**
 * [TODO 收费类型维护.]
 * 
 * @author <a href=mailto:xinxing.cheng@sungard.com.cn">程新兴</a>
 * @version v1.00
 * @since 1.00 2012-2-20
 * 
 */
public interface FeetypeService {
	public List<Feetype> queryAll();
	public List<Feetype> queryByParam(Feetype feetype);
	public Feetype queryByFeetype(String feetype) throws FunctionException;
	public int addFeetype(Feetype feetype) throws FunctionException; 
	public int updateFeetype(Feetype feetype) throws FunctionException;
	public int removeFeetype(String feetype) throws FunctionException;
}
