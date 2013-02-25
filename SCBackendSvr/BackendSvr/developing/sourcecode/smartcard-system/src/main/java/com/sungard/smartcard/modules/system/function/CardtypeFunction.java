/*
 * CardtypeFunction.java  v1.00  2012-2-22
 * Peoject	smartcard-system
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	CardtypeFunction.java  v1.00 2012-2-22
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
import com.sungard.smartcard.annotation.TransfersNodeType;
import com.sungard.smartcard.bccsvr.BccServerThread;
import com.sungard.smartcard.bccsvr.Function;
import com.sungard.smartcard.domain.Cardtype;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.modules.system.service.CardtypeService;

/**
 * [TODO 卡类别维护.]
 * 
 * @author <a href=mailto:xinxing.cheng@sungard.com.cn">程新兴</a>
 * @version v1.00
 * @since 1.00 2012-2-22
 * 
 */
@SmartCardFunction(infotype = 3, funcnum = 10004106, name = "卡类别维护")
@Component
public class CardtypeFunction  extends AbstractFunction {
	private static final Logger logger = LoggerFactory.getLogger(CardtypeFunction.class);
	@Autowired
	@Qualifier("cardtypeServiceImpl")
	private CardtypeService cardtypeService;
	
	public void setCardtypeService(CardtypeService cardtypeService) {
		this.cardtypeService = cardtypeService;
	}
	
	@Override
	public void add(Function function, BccServerThread session)
			throws FunctionException {
		Cardtype cardtype = super.getParameter(Cardtype.class, session);
		this.cardtypeService.add(cardtype);
	}
	@Override
	public void delete(Function function, BccServerThread session)
			throws FunctionException {
		Integer cardtype = session.GetIntFieldByName(0,TransfersNodeType.lvol0.getName());
		this.cardtypeService.delete(cardtype);
	}
	@Override
	public void update(Function function, BccServerThread session)
			throws FunctionException {
		Cardtype cardtype = super.getParameter(Cardtype.class, session);
		this.cardtypeService.update(cardtype);
	}
	@Override
	public void query(Function function, BccServerThread session)
			throws FunctionException {
		Cardtype cardtype = super.getParameter(Cardtype.class, session);
		List<Cardtype> l = this.cardtypeService.query(cardtype);
		super.outPack(l, Cardtype.class, session);
	}
}
