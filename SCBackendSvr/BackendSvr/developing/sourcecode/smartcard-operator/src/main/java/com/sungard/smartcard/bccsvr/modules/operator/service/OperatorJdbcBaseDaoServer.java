/*
 * OperatorJdbcBaseDaoServer.java  v1.00  2012-1-6
 * Peoject	smartcard-operator
 * Copyright (c) 2012 Sungard.China.HE
 *
 * Filename	:	OperatorJdbcBaseDaoServer.java  v1.00 2012-1-6
 * Project	: 	smartcard-operator
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.bccsvr.modules.operator.service;

import java.util.List;
import java.util.Set;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.sungard.smartcard.annotation.SmartCardFunction;
import com.sungard.smartcard.bccsvr.BccServerThread;
import com.sungard.smartcard.bccsvr.Function;
import com.sungard.smartcard.bccsvr.ServiceI;
import com.sungard.smartcard.bccsvr.modules.operator.dao.OperatorJdbcBaseDao;
import com.sungard.smartcard.bccsvr.modules.operator.domain.Operator;
import com.sungard.smartcard.utils.drtp.TransfersNodeInfo;
import com.sungard.smartcard.utils.drtp.TransfersUtils;

/**
 * 含dao实现的服务.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2012-1-6
 * 
 */
@SmartCardFunction(infotype = 3, funcnum = 90000105, name = "OperatorJdbcBaseDaoServer")
public class OperatorJdbcBaseDaoServer implements ServiceI {

    private static final Logger logger = LoggerFactory.getLogger(OperatorJdbcBaseDaoServer.class);

    private ThreadLocal<OperatorJdbcBaseDao> threadLocal = new ThreadLocal<OperatorJdbcBaseDao>();
    private OperatorJdbcBaseDao operatorJdbcBaseDao;

    @Override
    public boolean doService(Function func, BccServerThread session) {

        boolean flag = false;

        flag = query(session);

        if (!flag) {
            session.ClearRow();
            session.SetStringFieldByName("vsmess", "process unsuccessful!");
            session.PutRow(0);
        }
        session.DataDone(0);

        return flag;
    }

    /**
     * 查询.
     * 
     * @param session
     * @return
     * @since v1.00
     */
    private boolean query(BccServerThread session) {

        List<Operator> list = getOperatorJdbcBaseDao().getAll();
        Set<TransfersNodeInfo> transOuts = TransfersUtils.getTransfersNodeInfosOut(Operator.class);
        for (Operator operator : list) {
            if (!TransfersUtils.TransfersOneRow(session, operator, transOuts)) {
                logger.info("传输错误", operator);
                return false;
            }
        }

        return true;
    }

    public OperatorJdbcBaseDao getOperatorJdbcBaseDao() {
        OperatorJdbcBaseDao dao = threadLocal.get();
        if (dao == null) {
            dao = new OperatorJdbcBaseDao();
            threadLocal.set(dao);
        }
        operatorJdbcBaseDao = dao;
        return dao;
    }

    public void setOperatorJdbcBaseDao(OperatorJdbcBaseDao operatorJdbcBaseDao) {
        this.operatorJdbcBaseDao = operatorJdbcBaseDao;
    }

}
