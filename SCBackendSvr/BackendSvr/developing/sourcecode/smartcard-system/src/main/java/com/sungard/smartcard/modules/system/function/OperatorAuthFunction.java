package com.sungard.smartcard.modules.system.function;

import com.sungard.smartcard.AbstractFunction;
import com.sungard.smartcard.RetCode;
import com.sungard.smartcard.annotation.SmartCardFunction;
import com.sungard.smartcard.annotation.TransfersNodeType;
import com.sungard.smartcard.bccsvr.BccServerThread;
import com.sungard.smartcard.bccsvr.Function;
import com.sungard.smartcard.domain.Operator;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.modules.system.service.OperatorService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;

/**
 * 包括充值操作员赋权
 *
 * @author Yiming.You
 * @version v1.00
 * @since 12-2-20
 */
@SmartCardFunction(infotype = 3, funcnum = 10001103, name = "充值操作员维护")
public class OperatorAuthFunction extends AbstractFunction {
    private static final Logger logger = LoggerFactory.getLogger(OperatorAuthFunction.class);

    @Autowired
    @Qualifier("operatorServiceImpl")
    private OperatorService operatorService;

    /**
     * 充值操作员赋权
     *
     * @param function 请求功能
     * @param session  请求功能服务线程
     * @throws FunctionException
     */
    @Override
    public void other(Function function, BccServerThread session) throws FunctionException {
        //opercode:待授权操作员编号，authOpercode:执行当前授权操作的操作员编号，authOperpwd:执行当前授权操作的操作员密码
        String opercode = session.GetStringFieldByName(0, TransfersNodeType.semp.getName());
        String authOpercode = session.GetStringFieldByName(0, TransfersNodeType.vsvarstr0.getName());
        String authOperpwd = session.GetStringFieldByName(0, TransfersNodeType.scust_limit.getName());
        //只有特定的操作员才有权限对操作员进行充值授权
        if (!"bursar".equals(authOpercode)) {
            throw new FunctionException(RetCode.OPERATOR_NO_BURSARRIGHT, authOpercode);
        }
        Operator operator = operatorService.getOperator(authOpercode);
        if (operator == null) {
            throw new FunctionException(RetCode.OPERATOR_NOT_EXIST, authOpercode);
        }
        if (!operator.getOperpwd().equals(authOperpwd)) {
            throw new FunctionException(RetCode.OPERATOR_WRONG_PASSWORD, authOpercode);
        }
        operatorService.authOperator(opercode);
        logger.debug("充值操作员[]授权成功", opercode);
    }
}
