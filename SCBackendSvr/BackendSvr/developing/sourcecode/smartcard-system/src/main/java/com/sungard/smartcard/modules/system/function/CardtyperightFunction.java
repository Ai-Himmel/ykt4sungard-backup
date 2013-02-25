/*
 * CardtyperightFunction.java  v1.00  2012-2-22
 * Peoject	smartcard-system
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	CardtyperightFunction.java  v1.00 2012-2-22
 * Project	: 	smartcard-system
 * Copyight	:	Copyright (c) 2012 Sungard.China.HE
 */
package com.sungard.smartcard.modules.system.function;

import java.util.List;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Component;

import com.sungard.smartcard.AbstractFunction;
import com.sungard.smartcard.annotation.SmartCardFunction;
import com.sungard.smartcard.bccsvr.BccServerThread;
import com.sungard.smartcard.bccsvr.Function;
import com.sungard.smartcard.domain.Cardtyperight;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.modules.system.service.CardtyperightService;

/**
 * [TODO 发卡权限维护.]
 * 
 * @author <a href=mailto:xinxing.cheng@sungard.com.cn">程新兴</a>
 * @version v1.00
 * @since 1.00 2012-2-22
 * 
 */
@SmartCardFunction(infotype = 3, funcnum = 10004107, name = "发卡权限维护")
@Component
public class CardtyperightFunction extends AbstractFunction {
	private static final Logger logger = LoggerFactory.getLogger(CardtyperightFunction.class);
	@Autowired
	@Qualifier("cardtyperightServiceImpl")
	private CardtyperightService cardtyperightService;
	
	public void setCardtyperightService(CardtyperightService cardtyperightService) {
		this.cardtyperightService = cardtyperightService;
	}
	@Override
	public void add(Function function, BccServerThread session)
			throws FunctionException {
		Cardtyperight cardtyperight = super.getParameter(Cardtyperight.class, session);
		this.cardtyperightService.addCardtyperight(cardtyperight);
	}
	@Override
	public void query(Function function, BccServerThread session)
			throws FunctionException {
		Cardtyperight cardtyperight = super.getParameter(Cardtyperight.class, session);
		List<Cardtyperight> l = this.cardtyperightService.queryCardtyperight(cardtyperight);
		super.outPack(l, Cardtyperight.class, session);
	}
	@Override
	public void delete(Function function, BccServerThread session)
			throws FunctionException {
		Cardtyperight cardtyperight = super.getParameter(Cardtyperight.class, session);
		this.cardtyperightService.deleteCardtyperight(cardtyperight);
	}
}
