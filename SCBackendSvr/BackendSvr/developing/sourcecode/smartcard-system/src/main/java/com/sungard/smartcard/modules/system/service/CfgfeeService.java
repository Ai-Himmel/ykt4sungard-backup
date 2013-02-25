/*
 * CfgfeeService.java  v1.00  2012-2-21
 * Peoject	smartcard-system
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	CfgfeeService.java  v1.00 2012-2-21
 * Project	: 	smartcard-system
 * Copyight	:	Copyright (c) 2012 Sungard.China.HE
 */
package com.sungard.smartcard.modules.system.service;

import java.util.List;

import com.sungard.smartcard.domain.Cfgfee;
import com.sungard.smartcard.exception.FunctionException;

/**
 * [TODO 交易收费信息维护.]
 * 
 * @author <a href=mailto:xinxing.cheng@sungard.com.cn">程新兴</a>
 * @version v1.00
 * @since 1.00 2012-2-21
 * 
 */
public interface CfgfeeService {
	public List<Cfgfee> findCfgfee(Cfgfee cfgfee);
	public Cfgfee getCfgfee(Integer feetype,Integer transcode,Integer cardtype,Integer transtype) throws FunctionException;
	public boolean update(Cfgfee cfgfee,String opercode) throws FunctionException;
	public boolean delete(Cfgfee cfgfee,String opercode) throws FunctionException;
	public boolean add(Cfgfee cfgfee,String opercode) throws FunctionException;
}
