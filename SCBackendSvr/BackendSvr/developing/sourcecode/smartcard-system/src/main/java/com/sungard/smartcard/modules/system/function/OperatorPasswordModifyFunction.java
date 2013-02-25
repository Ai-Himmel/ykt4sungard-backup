package com.sungard.smartcard.modules.system.function;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;

import com.sungard.smartcard.AbstractFunction;
import com.sungard.smartcard.annotation.SmartCardFunction;
import com.sungard.smartcard.bccsvr.BccServerThread;
import com.sungard.smartcard.bccsvr.Function;
import com.sungard.smartcard.domain.Site;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.modules.system.service.OperatorService;

@SmartCardFunction(infotype = 3, funcnum = 10001106, name = "修改操作员密码/重置操作员密码")
public class OperatorPasswordModifyFunction extends AbstractFunction {
	private static final Logger logger = LoggerFactory.getLogger(OperatorPasswordModifyFunction.class);
    @Autowired
    private OperatorService operatorService;
	public void setOperatorService(OperatorService operatorService) {
		this.operatorService = operatorService;
	}

	@Override
	/*
	 * 修改操作员密码
	 */
	public void add(Function function, BccServerThread session)
			throws FunctionException {
		/**s.getIp()用来存放密码 s.getSitename()用来存放操作员号s.getMachinecode()存放操作员原密码;*/
		logger.info("--------------修改操作员密码-------------------");
		Site s = super.getParameter(Site.class, session);
		logger.debug("当前修改密码的操作员为："+s.getSitename());
		operatorService.modifyOperatorPW(s);
	}

	@Override
	/*
	 * 重置操作员密码
	 */
	public void update(Function function, BccServerThread session)
			throws FunctionException {
		logger.info("--------------重置操作员密码-------------------");
		/**s.getIp()用来存放密码 s.getSitename()用来存放操作员号s.getMachinecode()存放操作员原密码;*/
		Site s = super.getParameter(Site.class, session);
		logger.debug("当前修改密码的操作员为："+s.getSitename());
		operatorService.resetOperatorPW(s);
	}
	
}
