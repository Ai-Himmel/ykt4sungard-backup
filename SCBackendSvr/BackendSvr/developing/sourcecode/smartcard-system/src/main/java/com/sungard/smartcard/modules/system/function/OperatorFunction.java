package com.sungard.smartcard.modules.system.function;

import java.util.List;

import com.sungard.smartcard.AbstractFunction;
import com.sungard.smartcard.RetCode;
import com.sungard.smartcard.annotation.SmartCardFunction;
import com.sungard.smartcard.bccsvr.BccServerThread;
import com.sungard.smartcard.bccsvr.Function;
import com.sungard.smartcard.domain.Branch;
import com.sungard.smartcard.domain.Operator;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.modules.system.service.OperatorService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

/**
 * 操作员管理，包含操作员的增删改查
 *
 * @author HongYi.Wang
 * @version v1.00
 * @since 2012-02-23
 */
@SmartCardFunction(infotype = 3, funcnum = 10001102, name = "操作员维护")
@Component
public class OperatorFunction extends AbstractFunction {

    private static final Logger logger = LoggerFactory.getLogger(OperatorFunction.class);

    @Autowired
    private OperatorService operatorService;
	public void setOperatorService(OperatorService operatorService) {
		this.operatorService = operatorService;
	}

	@Override
	public void add(Function function, BccServerThread session)
			throws FunctionException {
		Operator or = super.getParameter(Operator.class, session);
		logger.info("----------------------------添加操作员--------------------------");
		operatorService.addOperator(or);
	}

	@Override
	public void delete(Function function, BccServerThread session)
			throws FunctionException {
		Operator or = super.getParameter(Operator.class, session);
		logger.info("----------------------------删除操作员--------------------------");
		operatorService.delOperator(or);
	}

	@Override
	public void query(Function function, BccServerThread session)
			throws FunctionException {
		Operator or = super.getParameter(Operator.class, session);
		logger.info("----------------------------查询操作员--------------------------");
		List<Operator> operators = operatorService.queryOperators(or);
		outPack(operators,Operator.class,session);
	}

	@Override
	public void update(Function function, BccServerThread session)
			throws FunctionException {
		Operator or = super.getParameter(Operator.class, session);
		logger.info("----------------------------添加操作员--------------------------");
		operatorService.modifyOperator(or);
	}
    
    
}
