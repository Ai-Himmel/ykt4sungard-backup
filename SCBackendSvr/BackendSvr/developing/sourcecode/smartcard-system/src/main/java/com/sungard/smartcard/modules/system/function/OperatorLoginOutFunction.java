package com.sungard.smartcard.modules.system.function;

import java.util.List;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import com.sungard.smartcard.AbstractFunction;
import com.sungard.smartcard.annotation.SmartCardFunction;
import com.sungard.smartcard.bccsvr.BccServerThread;
import com.sungard.smartcard.bccsvr.Function;
import com.sungard.smartcard.domain.Functionality;
import com.sungard.smartcard.domain.Operator;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.modules.system.service.OperatorService;


@SmartCardFunction(infotype = 3, funcnum = 10001108, name = "操作员登出")
@Component
public class OperatorLoginOutFunction extends AbstractFunction {
	private static final Logger logger = LoggerFactory.getLogger(OperatorLoginOutFunction.class);
	
	@Autowired
	private OperatorService operatorService;
	public void setOperatorService(OperatorService operatorService) {
		this.operatorService = operatorService;
	}
	@Override
	/*
	 * 操作员登出
	 */
	public void other(Function function, BccServerThread session)
			throws FunctionException {
		Operator or = super.getParameter(Operator.class, session);
		logger.info("操作员[{}]登出",new Object[]{or.getOpername()});
		operatorService.operatorLoginOut(or);
	}
	
	

}
