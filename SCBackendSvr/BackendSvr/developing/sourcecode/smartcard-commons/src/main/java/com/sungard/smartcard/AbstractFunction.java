package com.sungard.smartcard;

import com.sungard.smartcard.annotation.CrudType;
import com.sungard.smartcard.annotation.TransfersNodeType;
import com.sungard.smartcard.bccsvr.BccServerThread;
import com.sungard.smartcard.bccsvr.Function;
import com.sungard.smartcard.bccsvr.ServiceI;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.utils.drtp.TransfersNodeInfo;
import com.sungard.smartcard.utils.drtp.TransfersUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.slf4j.helpers.MessageFormatter;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 * 封装请求功能号的基本操作
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-17
 */
public abstract class AbstractFunction implements ServiceI {

    private static final Logger logger = LoggerFactory.getLogger(AbstractFunction.class);

    public <T> T getParameter(Class<T> paramType, BccServerThread session) {
        return TransfersUtils.getTransfersInObjects(paramType, session).get(0);
    }

    public <T> List<T> getParameters(Class<T> paramType, BccServerThread session) {
        return TransfersUtils.getTransfersInObjects(paramType, session);
    }

    public Map<String, Object> getParameters(BccServerThread session, String[] fieldNames) {
        Map<String, Object> parameters = new HashMap<String, Object>();
        for (String fieldName : fieldNames) {
            parameters.put(fieldName, session.GetFieldByName(0, fieldName));
        }
        return parameters;
    }

    public <T> void outPack(List<T> result, Class<T> entityClass, BccServerThread session) {
        TransfersUtils.TransfersAllRow(session, result, entityClass);
    }

    public <T> void outPack(T entity, BccServerThread session) {
        Set<TransfersNodeInfo> transOuts = TransfersUtils.getTransfersNodeInfosOut(entity.getClass());
        TransfersUtils.TransfersOneRow(session, entity, transOuts);
    }

    public void writeError(Function function, BccServerThread session, FunctionException e) {
        writeError(function, session, e.getCode(), e.getArgs());
    }

    public void writeError(Function function, BccServerThread session, int retCode, Object... args) {
        String errorMsg = AppContext.getRetMsg(retCode);
        String vsmess = MessageFormatter.arrayFormat(errorMsg, args).getMessage();
        session.SetStringFieldByName(TransfersNodeType.vsmess.getName(), vsmess);
        session.PutRow(retCode);
        logger.warn("[Function:{},retCode:{},vsmess:{}]", new Object[]{function.GetRequestType(), retCode, vsmess});
    }

    @Override
    public boolean doService(Function function, BccServerThread session) {
        logger.debug("[Function:{}] start...", function.GetRequestType());
        int retCode = RetCode.OK;
        try {
            //sstatus0是系统保留cpack字段，用于区分执行同一功能号中的不同方法
            String sstatus0 = session.GetStringFieldByName(0, TransfersNodeType.sstatus0.getName());
            switch (Enum.valueOf(CrudType.class, sstatus0)) {
                case A:
                    add(function, session);
                    break;
                case U:
                    update(function, session);
                    break;
                case D:
                    delete(function, session);
                    break;
                case Q:
                    query(function, session);
                    break;
                case DA:
                	deleteBatch(function, session);
                    break;
                case V:
                	verify(function, session);
                    break;
                case Other:
                    other(function, session);
                    break;
                default:
                    logger.warn("No action, [Function:{},sstatus0:{}]", function.GetRequestType(), sstatus0);
                    break;
            }
        } catch (FunctionException e) {
            logger.error(e.getMessage());
            retCode = e.getCode();
            writeError(function, session, e);
        } catch (Exception e) {
            logger.error(e.getMessage());
            retCode = RetCode.SYSTEM_EXCEPTION;
            writeError(function, session, retCode, e.getMessage());
        }
        session.DataDone(retCode);
        logger.debug("[Function:{}] end...", function.GetRequestType());
        return true;
    }

    public void add(Function function, BccServerThread session) throws FunctionException {
    }

    public void update(Function function, BccServerThread session) throws FunctionException {
    }

    public void delete(Function function, BccServerThread session) throws FunctionException {
    }

    public void query(Function function, BccServerThread session) throws FunctionException {
    }

    public void other(Function function, BccServerThread session) throws FunctionException {
    }

    public void deleteBatch(Function function, BccServerThread session) throws FunctionException {
    }
    public void verify(Function function, BccServerThread session) throws FunctionException {
    }
}
