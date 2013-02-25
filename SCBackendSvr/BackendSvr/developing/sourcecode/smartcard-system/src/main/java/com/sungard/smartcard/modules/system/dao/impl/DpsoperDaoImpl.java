package com.sungard.smartcard.modules.system.dao.impl;

import com.sungard.smartcard.domain.Dpsoper;
import com.sungard.smartcard.domain.Dpsopercard;
import com.sungard.smartcard.modules.system.dao.DpsoperDao;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;

import java.io.Serializable;
import java.util.List;

/**
 * 充值操作员与卡绑定关系的基本数据库操作实现类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 12-2-20
 */
@Repository
public class DpsoperDaoImpl implements DpsoperDao {

    private static final Logger logger = LoggerFactory.getLogger(DpsoperDaoImpl.class);

    private static String DPSOPER_QUERY_ALL = "select opercode, devlimitflag, shopoperflag, status, opendate, closedate, maxdepositamt, depositcnt, depositamt, lasttransdate, lastdevphyid, lastdevseqno, batchno, authcode, devphyid, lastsaved from t_dpsoper";

    @Autowired
    private JdbcTemplate jdbcTemplate;

    public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }

    /**
     * 查找所有的充值操作员与卡绑定关系
     *
     * @return 所有充值操作员与卡绑定关系
     */
    @Override
    public List<Dpsoper> findAllDpsoper() {
        return jdbcTemplate.query(DPSOPER_QUERY_ALL, new BeanPropertyRowMapper(Dpsoper.class));
    }

    /**
     * 根据Dpsopercard的属性查找数据库中是否已存在对应记录
     *
     * @param key   Dpsopercard的属性
     * @param value 属性对应的值
     * @return 返回1表示存在，0表示不存在
     */
    public int isExistDpsopercard(String key, Serializable value) {
        String IS_EXIST_DPSOPERCARD = "select count(*) from t_dpsopercard where 1=1";
        if (key != null) {
            IS_EXIST_DPSOPERCARD += " and " + key + "=?";
            return jdbcTemplate.queryForInt(IS_EXIST_DPSOPERCARD, value);
        }
        return 0;
    }

    /**
     * 删除充值操作员与卡关联关系
     *
     * @param opercode 充值操作员编号
     * @return .
     */
    @Override
    public int deleteDpsopercard(String opercode) {
        String DPSOPERCARD_DELETE = "update t_dpsopercard set disableflag=1 where opercode=?";
        return jdbcTemplate.update(DPSOPERCARD_DELETE, opercode);
    }

    /**
     * 保存充值操作员与卡的绑定关系
     *
     * @param dpsopercard 充值操作员与卡绑定关系
     * @return .
     */
    @Override
    public int saveDpsopercard(Dpsopercard dpsopercard) {
        String DPSOPERCARD_INSERT = "insert into t_dpsopercard(opercode, cardno, disableflag, openoper, lastsaved) values(?,?,?,?,?)";
        return jdbcTemplate.update(DPSOPERCARD_INSERT, dpsopercard.getOpercode(), dpsopercard.getCardno(), dpsopercard.getDisableflag(), dpsopercard.getOpenoper(), dpsopercard.getLastsaved());
    }
}
