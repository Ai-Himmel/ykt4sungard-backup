package com.sungard.smartcard.bccsvr.service;

import com.sungard.smartcard.annotation.CrudType;
import com.sungard.smartcard.annotation.TransfersNodeType;
import com.sungard.smartcard.bccsvr.BccServerThread;
import com.sungard.smartcard.bccsvr.ErrorCode;
import com.sungard.smartcard.bccsvr.Function;
import com.sungard.smartcard.bccsvr.ServiceI;
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
 * @author Yiming.You
 * @version v1.00
 */
public abstract class AbstractService implements ServiceI {

    private static final Logger logger = LoggerFactory.getLogger(AbstractService.class);

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

    public int writeError(int errorCode, Function function, BccServerThread session, Object... args) {
        //todo get error message from memory or database
        String errorMsg = "";
        String vsmess = MessageFormatter.arrayFormat(errorMsg, args).getMessage();
        session.SetStringFieldByName(TransfersNodeType.vsmess.getName(), vsmess);
        session.PutRow(errorCode);

        logger.warn("[Function:{},retCode:{},vsmess:{}]", new Object[]{function.GetRequestType(), errorCode, vsmess});
        return errorCode;
    }

    @Override
    public boolean doService(Function function, BccServerThread session) {
        logger.debug("[Function:{}] start...", function.GetRequestType());
        int retCode = ErrorCode.System.OK.getCode();
        try {
            //sstatus0 is a reserved system field, it's normally used to execute different methods
            String sstatus0 = session.GetStringFieldByName(0, TransfersNodeType.sstatus0.getName());
            switch (Enum.valueOf(CrudType.class, sstatus0)) {
                case A:
                    retCode = add(function, session);
                    break;
                case U:
                    retCode = update(function, session);
                    break;
                case D:
                    retCode = delete(function, session);
                    break;
                case Q:
                    retCode = query(function, session);
                    break;
                case Other:
                    retCode = other(function, session);
                    break;
                default:
                    logger.warn("No action, [Function:{},sstatus0:{}]", function.GetRequestType(), sstatus0);
                    break;
            }
        } catch (Exception e) {
            e.printStackTrace();
            //todo 1000 is used for unknown system error
            retCode = writeError(ErrorCode.System.SYSTEM_EXCEPTION.getCode(), function, session, e.getMessage());
        }
        session.DataDone(retCode);
        logger.debug("[Function:{}] end...", function.GetRequestType());
        return true;
    }

    public int add(Function function, BccServerThread session) {
        return ErrorCode.System.UNREALIZED_METHOD.getCode();
    }

    public int update(Function function, BccServerThread session) {
        return ErrorCode.System.UNREALIZED_METHOD.getCode();
    }

    public int delete(Function function, BccServerThread session) {
        return ErrorCode.System.UNREALIZED_METHOD.getCode();
    }

    public int query(Function function, BccServerThread session) {
        return ErrorCode.System.UNREALIZED_METHOD.getCode();
    }

    public int other(Function function, BccServerThread session) {
        return ErrorCode.System.UNREALIZED_METHOD.getCode();
    }
}
