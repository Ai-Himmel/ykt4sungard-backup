/*
 * CfgfeeFunction.java  v1.00  2012-2-22
 * Peoject	smartcard-system
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	CfgfeeFunction.java  v1.00 2012-2-22
 * Project	: 	smartcard-system
 * Copyight	:	Copyright (c) 2012 Sungard.China.HE
 */
package com.sungard.smartcard.modules.system.function;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Component;

import com.sungard.smartcard.AbstractFunction;
import com.sungard.smartcard.annotation.SmartCardFunction;
import com.sungard.smartcard.annotation.TransfersNodeType;
import com.sungard.smartcard.bccsvr.BccServerThread;
import com.sungard.smartcard.bccsvr.Function;
import com.sungard.smartcard.domain.Cfgfee;
import com.sungard.smartcard.domain.Feetype;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.modules.system.service.CardtyperightService;
import com.sungard.smartcard.modules.system.service.CfgfeeService;

/**
 * [TODO 交易收费配置.]
 * 
 * @author <a href=mailto:xinxing.cheng@sungard.com.cn">程新兴</a>
 * @version v1.00
 * @since 1.00 2012-2-22
 * 
 */
@SmartCardFunction(infotype = 3, funcnum = 10004104, name = "交易收费配置")
@Component
public class CfgfeeFunction extends AbstractFunction {
	private static final Logger logger = LoggerFactory.getLogger(CfgfeeFunction.class);
	@Autowired
	@Qualifier("cfgfeeServiceImpl")
	private CfgfeeService cfgfeeService;
	
	public void setCfgfeeService(CfgfeeService cfgfeeService) {
		cfgfeeService = cfgfeeService;
	}
	@Override
	public void add(Function function, BccServerThread session)
			throws FunctionException {
		String opercode = session.GetStringFieldByName(0, TransfersNodeType.semp.getName());
		Cfgfee cfgfee = super.getParameter(Cfgfee.class, session);
		cfgfeeService.add(cfgfee, opercode);
	}
	@Override
	public void query(Function function, BccServerThread session)
			throws FunctionException {
		Cfgfee cfgfee = super.getParameter(Cfgfee.class, session);
		super.outPack(cfgfeeService.findCfgfee(cfgfee), Cfgfee.class, session);
	}
	@Override
	public void delete(Function function, BccServerThread session)
			throws FunctionException {
		Cfgfee cfgfee = super.getParameter(Cfgfee.class, session);
		String opercode = session.GetStringFieldByName(0, TransfersNodeType.semp.getName());
		cfgfeeService.delete(cfgfee, opercode);
	}
	@Override
	public void update(Function function, BccServerThread session)
			throws FunctionException {
		String opercode = session.GetStringFieldByName(0, TransfersNodeType.semp.getName());
		Cfgfee cfgfee = super.getParameter(Cfgfee.class, session);
		cfgfeeService.update(cfgfee, opercode);
	}
}
