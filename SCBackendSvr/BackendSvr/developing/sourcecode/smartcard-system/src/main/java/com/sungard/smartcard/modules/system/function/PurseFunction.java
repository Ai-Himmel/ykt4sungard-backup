package com.sungard.smartcard.modules.system.function;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Component;

import com.sungard.smartcard.AbstractFunction;
import com.sungard.smartcard.RetCode;
import com.sungard.smartcard.annotation.SmartCardFunction;
import com.sungard.smartcard.bccsvr.BccServerThread;
import com.sungard.smartcard.bccsvr.Function;
import com.sungard.smartcard.domain.Purse;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.modules.system.service.PurseService;

/**
 * [TODO 钱包信息维护]
 * 
 * @author bo.chen 
 * @version v1.00
 * @since 1.00 2012-2-22
 */
@SmartCardFunction(infotype = 3, funcnum = 10004108, name = "钱包信息维护")
@Component
public class PurseFunction extends AbstractFunction {
	
	@SuppressWarnings("unused")
	private static final Logger logger = LoggerFactory
			.getLogger(PurseFunction.class);
	
	@Autowired
	@Qualifier("purseServiceImpl")
	private PurseService purseService;


	public void setPurseService(PurseService purseService) {
		this.purseService = purseService;
	}

	@Override
	public void add(Function function, BccServerThread session)
			throws FunctionException {
		Purse param = super.getParameter(Purse.class, session);
		purseService.addPurse(param);
	}

	@Override
	public void query(Function function, BccServerThread session)
			throws FunctionException {
		Purse param = super.getParameter(Purse.class, session);
		super.outPack(purseService.queryByParam(param), Purse.class, session);

	}

	@Override
	public void update(Function function, BccServerThread session)
			throws FunctionException {
		Purse param = super.getParameter(Purse.class, session);
		if (purseService.updatePurse(param) < 0) {
			throw new FunctionException(RetCode.SYSTEM_EXCEPTION, "钱包信息修改失败");
		}
	}

	@Override
	public void delete(Function function, BccServerThread session)
			throws FunctionException {
		Purse param = super.getParameter(Purse.class, session);
		if (purseService.removePurse(param) < 0) {
			throw new FunctionException(RetCode.SYSTEM_EXCEPTION, "钱包信息删除失败");
		}
	}
}
