package com.sungard.smartcard.modules.system.function;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import com.sungard.smartcard.AbstractFunction;
import com.sungard.smartcard.annotation.SmartCardFunction;
import com.sungard.smartcard.bccsvr.BccServerThread;
import com.sungard.smartcard.bccsvr.Function;
import com.sungard.smartcard.domain.Operator;
import com.sungard.smartcard.domain.Opersite;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.modules.system.service.OperatorService;

/**
 * 操作员登陆站点维护
 * @author HongYi.Wang
 *
 */
@SmartCardFunction(infotype = 3, funcnum = 10001105, name = "操作员登陆站点维护")
@Component
public class OperatorSiteFunction extends AbstractFunction {
	private static final Logger logger = LoggerFactory.getLogger(OperatorSiteFunction.class);

    @Autowired
    private OperatorService operatorService;
	public void setOperatorService(OperatorService operatorService) {
		this.operatorService = operatorService;
	}

	@Override
	/*
	 * 增加操作员维护站点
	 */
	public void add(Function function, BccServerThread session)
			throws FunctionException {
		Opersite os = super.getParameter(Opersite.class, session);
		operatorService.addOperatorSite(os);
	}

	@Override
	/*
	 * 删除操作员站点关系
	 */
	public void delete(Function function, BccServerThread session)
			throws FunctionException {
		Opersite os = super.getParameter(Opersite.class, session);
		operatorService.delOperatorSite(os);
	}

	@Override
	public void query(Function function, BccServerThread session)
			throws FunctionException {
		// TODO Auto-generated method stub
		super.query(function, session);
	}
	
	
}
