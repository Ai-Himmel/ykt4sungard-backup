/*
 * OperatorDbutilsService.java  v1.00  2011-12-26
 * Peoject	smartcard-operator
 * Copyright (c) 2011 Sungard.China.HE
 *
 * Filename	:	OperatorDbutilsService.java  v1.00 2011-12-26
 * Project	: 	smartcard-operator
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.bccsvr.service;

import com.sungard.common.page.Paginator;
import com.sungard.modules.utils.db.dao.DBSessionDao;
import com.sungard.modules.utils.db.jdbc.dialect.Dialect;
import com.sungard.modules.utils.db.jdbc.dialect.OracleDialect;
import com.sungard.smartcard.annotation.SmartCardFunction;
import com.sungard.smartcard.bccsvr.BccServerThread;
import com.sungard.smartcard.bccsvr.Function;
import com.sungard.smartcard.bccsvr.ServiceI;
import com.sungard.smartcard.bccsvr.modules.operator.domain.OperatorQuery;
import com.sungard.smartcard.bccsvr.modules.operator.domain.Transdtl;
import com.sungard.smartcard.utils.drtp.TransfersNodeInfo;
import com.sungard.smartcard.utils.drtp.TransfersUtils;
import org.apache.commons.beanutils.MethodUtils;
import org.apache.commons.dbutils.QueryRunner;
import org.apache.commons.dbutils.ResultSetHandler;
import org.apache.commons.dbutils.handlers.BeanListHandler;
import org.apache.commons.dbutils.handlers.ScalarHandler;
import org.apache.commons.lang.StringUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.lang.reflect.InvocationTargetException;
import java.math.BigInteger;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;
import java.util.Set;

/**
 * dbutils 实现.
 *
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-26
 */
@SmartCardFunction(infotype = 3, funcnum = 90000106, name = "TransdtlService")
public class TransdtlService extends DBSessionDao implements ServiceI {

    private static final Logger logger = LoggerFactory.getLogger(TransdtlService.class);
    private static final String querySql = "select accdate, acctime, termid, termseqno, transdate, transtime, refno, transcode, custid, custname, stuempno, showcardno, cardno, purseno, transflag, cardcnt, cardbefbal, cardaftbal, amount, addamt, managefee, paytype, voucherno, opercode, sysid, devphyid, devseqno, exttype, extdata, coldate, coltime, offlineflag, revflag, status, errcode, remark from t_transdtl where accdate>'20101123'";

    @Override
    public boolean doService(Function func, BccServerThread session) {
        //获取传过来的查询参数
        List<OperatorQuery> listA = TransfersUtils.getTransfersInObjects(OperatorQuery.class, session);
        for (OperatorQuery queryObj : listA) {
            logger.info("查询参数 nameString={}", queryObj.nameString);
        }

        boolean flag = false;

        flag = query(session);

        if (!flag) {
            session.SetStringFieldByName("vsmess", "process unsuccessful!");
            session.PutRow(0);
        }
        session.DataDone(0);

        return flag;
    }

    /**
     * 查询，返回beanList.
     *
     * @param session .
     * @return boolean
     * @since v1.00
     */
    public boolean query(BccServerThread session) {

        long has = 0;
        long time = System.currentTimeMillis();

        try {
            boolean flag = true;

            // 获取传过来的查询参数
            List<OperatorQuery> listA = TransfersUtils.getTransfersInObjects(OperatorQuery.class, session);
            OperatorQuery operatorQuery = null;
            if (listA != null && listA.size() > 0) {
                operatorQuery = listA.get(0);
            }

            // int offset = operatorQuery.getOffset();// 起始行号
            // int pageno = operatorQuery.getPageno();// 起始页
            // int limit = operatorQuery.getPagesize();// 每页行数

            QueryRunner runner = new QueryRunner();

            // 查询总数
            String sql_count = "select count(*) from ";
            sql_count += StringUtils.substringAfter(querySql.toLowerCase(), "from");
            sql_count = StringUtils.substringBeforeLast(sql_count.toLowerCase(), "order by");
            // ResultSetHandler<Object> rshc = new ScalarHandler();// count
            ScalarHandler sh = new ScalarHandler() {
                @Override
                public Object handle(ResultSet rs) throws SQLException {
                    Object obj = super.handle(rs);
                    if (obj instanceof BigInteger)
                        return ((BigInteger) obj).longValue();
                    return obj;
                }
            };
            Number num = (Number) runner.query(getConnection(), sql_count, sh);
            int count = num.intValue();
            logger.info("coung:{}",count);

            Paginator paginator = new Paginator(operatorQuery.getPageno(), operatorQuery.getPagesize(), count);

            Dialect dialect = new OracleDialect();
            String sql_page = dialect.getLimitString(querySql, paginator.getOffset(), paginator.getPageSize());

            ResultSetHandler<List<Transdtl>> rsh = new BeanListHandler<Transdtl>(Transdtl.class);
            List<Transdtl> list = runner.query(getConnection(), sql_page, rsh);
            Set<TransfersNodeInfo> transOuts = TransfersUtils.getTransfersNodeInfosOut(Transdtl.class);
            for (Transdtl transdtl : list) {
                /*if (!TransfersUtils.TransfersOneRow(session, transdtl, transOuts)) {
                    logger.info("传输错误", transdtl);
                    flag = false;
                }*/
            }

            has = System.currentTimeMillis() - time;
            System.out.println("---------------------hasbeanlist execute time :" + has);
            System.out.println("---------------------hasbeanlist result size :" + list.size());

            return flag;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return true;
    }
}
