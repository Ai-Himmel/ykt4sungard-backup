/*
 * OperatorMybatisService.java  v1.00  2011-12-30
 * Peoject	smartcard-operator
 * Copyright (c) 2011 Sungard.China.HE
 *
 * Filename	:	OperatorMybatisService.java  v1.00 2011-12-30
 * Project	: 	smartcard-operator
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.bccsvr.modules.operator.service;

import java.util.List;

import org.apache.commons.lang.StringUtils;
import org.apache.ibatis.session.SqlSession;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.sungard.modules.utils.db.orm.mybatis.SqlSessionHolder;
import com.sungard.smartcard.annotation.CrudType;
import com.sungard.smartcard.annotation.SmartCardFunction;
import com.sungard.smartcard.bccsvr.BccServerThread;
import com.sungard.smartcard.bccsvr.Function;
import com.sungard.smartcard.bccsvr.ServiceI;
import com.sungard.smartcard.bccsvr.modules.operator.dao.OperatorMapper;
import com.sungard.smartcard.bccsvr.modules.operator.domain.Operator;
import com.sungard.smartcard.bccsvr.modules.operator.domain.OperatorExample;
import com.sungard.smartcard.utils.drtp.TransfersUtils;

/**
 * mybatis service simple.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-30
 * 
 */
@SmartCardFunction(infotype = 3, funcnum = 90000106, name = "OperatorMybatisService")
public class OperatorMybatisService extends SqlSessionHolder implements ServiceI {

    private static final Logger logger = LoggerFactory.getLogger(OperatorMybatisService.class);

    private OperatorMapper operatorMapper;

    @Override
    public boolean doService(Function func, BccServerThread session) {
        logger.debug("OperatorJdbcService - start");

        // 获取传过来的查询参数
        List<Operator> listA = TransfersUtils.getTransfersInObjects(Operator.class, session);
        logger.info("查询参数={}", listA);

        boolean flag = false;

        
        long has = 0;
        long time = System.currentTimeMillis();
        
        
        String sstatus0 = "";// (String) session.GetFieldByName(0, "sstatus0");
        if (StringUtils.isBlank(sstatus0)) {
            sstatus0 = "Q";
        }
        switch (Enum.valueOf(CrudType.class, sstatus0)) {
        case A:
            break;
        case U:
            break;
        case D:
            break;
        case Q:
            flag = query(session);
            break;
        case Other:
            break;
        default:
            logger.debug("OperatorDbutilsService - 无处理应答");
            break;
        }

        if (!flag) {
            session.SetStringFieldByName("vsmess", "process successful!");
            session.PutRow(0);
        }
        session.DataDone(0);

        has = System.currentTimeMillis() - time;
        System.out.println("-------------------=========--hasmybatis execute time :" + has);
        
        return true;
    }

    public boolean query(BccServerThread session) {

        long has = 0;
        long time = System.currentTimeMillis();
        SqlSession sqlSession = getSqlSession();

        OperatorMapper operatorMapper = sqlSession.getMapper(OperatorMapper.class);
        OperatorExample operatorExample = new OperatorExample();
        operatorExample.createCriteria().andOpernameEqualTo("tc");
        List<Operator> list = operatorMapper.selectByExample(null);

        boolean flag = TransfersUtils.TransfersAllRow(session, list, Operator.class);

        has = System.currentTimeMillis() - time;
        System.out.println("---------------------hasmybatis execute time :" + has);

        return flag;

    }

    public OperatorMapper getOperatorMapper() {
        return operatorMapper;
    }

    public void setOperatorMapper(OperatorMapper operatorMapper) {
        this.operatorMapper = operatorMapper;
    }
}