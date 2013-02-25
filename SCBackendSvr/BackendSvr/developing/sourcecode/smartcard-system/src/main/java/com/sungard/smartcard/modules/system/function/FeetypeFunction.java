/*
 * FeetypeFunction.java  v1.00  2012-2-20
 * Peoject	smartcard-system
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	FeetypeFunction.java  v1.00 2012-2-20
 * Project	: 	smartcard-system
 * Copyight	:	Copyright (c) 2012 Sungard.China.HE
 */
package com.sungard.smartcard.modules.system.function;

import java.util.List;
import java.util.Map;

import org.apache.commons.lang.StringUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Component;

import com.sungard.smartcard.AbstractFunction;
import com.sungard.smartcard.RetCode;
import com.sungard.smartcard.annotation.SmartCardFunction;
import com.sungard.smartcard.annotation.TransfersNodeType;
import com.sungard.smartcard.bccsvr.BccServerThread;
import com.sungard.smartcard.bccsvr.Function;
import com.sungard.smartcard.domain.Feetype;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.modules.system.service.FeetypeService;

/**
 * [TODO 收费类型维护.]
 * 
 * @author <a href=mailto:xinxing.cheng@sungard.com.cn">程新兴</a>
 * @version v1.00
 * @since 1.00 2012-2-20
 * 
 */
@SmartCardFunction(infotype = 3, funcnum = 10004102, name = "收费类型维护")
@Component
public class FeetypeFunction extends AbstractFunction {
	private static final Logger logger = LoggerFactory.getLogger(FeetypeFunction.class);
	@Autowired
	@Qualifier("feetypeServiceImpl")
	private FeetypeService feetypeService;

	public void setFeetypeService(FeetypeService feetypeService) {
		this.feetypeService = feetypeService;
	}

	@Override
	public void add(Function function, BccServerThread session)
			throws FunctionException {
		Feetype param = super.getParameter(Feetype.class, session);
		feetypeService.addFeetype(param);
	}

	@Override
	public void query(Function function, BccServerThread session)
			throws FunctionException {
		Feetype param = super.getParameter(Feetype.class, session);
		super.outPack(feetypeService.queryByParam(param), Feetype.class, session);

	}

	@Override
	public void update(Function function, BccServerThread session)
			throws FunctionException {
		Feetype param = super.getParameter(Feetype.class, session);
		if (feetypeService.updateFeetype(param) <= 0) {
			throw new FunctionException(RetCode.SYSTEM_EXCEPTION, "收费类型修改失败");
		}
	}

	@Override
	public void delete(Function function, BccServerThread session)
			throws FunctionException {
		Integer feetypeid = session.GetIntFieldByName(0,TransfersNodeType.lvol1.getName());
		if (feetypeid==0||feetypeService.removeFeetype("" + feetypeid) <= 0) {
			throw new FunctionException(RetCode.SYSTEM_EXCEPTION, "收费类型删除 失败");
		}
	}
}
