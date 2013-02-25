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
import com.sungard.smartcard.domain.Waterrate;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.modules.system.service.WaterrateService;

/**
 * [TODO 脱机水价维护]
 * 
 * @author bo.chen 
 * @version v1.00
 * @since 1.00 2012-2-22
 */
@SmartCardFunction(infotype = 3, funcnum = 10004103, name = "脱机水价维护")
@Component
public class WaterrateFunction extends AbstractFunction {
	
	@SuppressWarnings("unused")
	private static final Logger logger = LoggerFactory
			.getLogger(WaterrateFunction.class);
	
	@Autowired
	@Qualifier("waterrateServiceImpl")
	private WaterrateService waterrateService;


	public void setWaterrateService(WaterrateService waterrateService) {
		this.waterrateService = waterrateService;
	}

	@Override
	public void add(Function function, BccServerThread session)
			throws FunctionException {
		Waterrate param = super.getParameter(Waterrate.class, session);
		waterrateService.addWaterrate(param);
	}

	@Override
	public void query(Function function, BccServerThread session)
			throws FunctionException {
		Waterrate param = super.getParameter(Waterrate.class, session);
		super.outPack(waterrateService.queryByParam(param), Waterrate.class, session);

	}

	@Override
	public void update(Function function, BccServerThread session)
			throws FunctionException {
		Waterrate param = super.getParameter(Waterrate.class, session);
		if (waterrateService.updateWaterrate(param) < 0) {
			throw new FunctionException(RetCode.SYSTEM_EXCEPTION, "脱机水价修改失败");
		}
	}

	@Override
	public void delete(Function function, BccServerThread session)
			throws FunctionException {
		Waterrate param = super.getParameter(Waterrate.class, session);
		if (waterrateService.removeWaterrate(param) < 0) {
			throw new FunctionException(RetCode.SYSTEM_EXCEPTION, "脱机水价删除失败");
		}
	}
}
