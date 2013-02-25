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
import com.sungard.smartcard.domain.Dictionary;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.modules.system.service.DictionaryService;

/**
 * [TODO 数据字典维护]
 * 
 * @author bo.chen 
 * @version v1.00
 * @since 1.00 2012-2-22
 */
@SmartCardFunction(infotype = 3, funcnum = 10004100, name = "数据字典维护")
@Component
public class DictionaryFunction extends AbstractFunction {
	
	@SuppressWarnings("unused")
	private static final Logger logger = LoggerFactory
			.getLogger(DictionaryFunction.class);
	
	@Autowired
	@Qualifier("dictionaryServiceImpl")
	private DictionaryService dictionaryService;

	public void setDictionaryService(DictionaryService dictionaryService) {
		this.dictionaryService = dictionaryService;
	}

	@Override
	public void add(Function function, BccServerThread session)
			throws FunctionException {
		Dictionary param = super.getParameter(Dictionary.class, session);
		dictionaryService.addDictionary(param);
	}

	@Override
	public void query(Function function, BccServerThread session)
			throws FunctionException {
		Dictionary param = super.getParameter(Dictionary.class, session);
		super.outPack(dictionaryService.queryByParam(param), Dictionary.class, session);

	}

	@Override
	public void update(Function function, BccServerThread session)
			throws FunctionException {
		Dictionary param = super.getParameter(Dictionary.class, session);
		if (dictionaryService.updateDictionary(param) < 0) {
			throw new FunctionException(RetCode.SYSTEM_EXCEPTION, "数据字典修改失败");
		}
	}

	@Override
	public void delete(Function function, BccServerThread session)
			throws FunctionException {
		Dictionary param = super.getParameter(Dictionary.class, session);
		if (dictionaryService.removeDictionary(param) < 0) {
			throw new FunctionException(RetCode.SYSTEM_EXCEPTION, "数据字典删除失败");
		}
	}
}
