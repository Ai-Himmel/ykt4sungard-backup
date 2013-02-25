package com.sungard.smartcard.dao.impl;

import com.sungard.smartcard.dao.CfgDao;
import com.sungard.smartcard.domain.Cfgver;
import com.sungard.smartcard.util.DateUtil;
import org.apache.commons.lang.StringUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.dao.EmptyResultDataAccessException;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;

/**
 * 系统参数版本号管理，系统在更新t_transcode，t_cfgfee，t_syspara时，需要更新系统参数版本号，并且重新加载系统参数
 *
 * @author Yiming.You
 * @version v1.00
 * @since 12-2-22
 */
@Repository
public class CfgDaoImpl implements CfgDao {

    private String CFGVER_QUERY = "select cfgverno from t_cfgver where cfgtype=1";
    private String CFGVER_INSERT = "insert into t_cfgver(cfgtype,cfgverno,opercode,lastsaved) values(?,?,?,?)";
    private String CFGVER_UPDATE = "update t_cfgver set cfgverno=cfgverno+1,opercode=? where cfgtype=1";

    @Autowired
    private JdbcTemplate jdbcTemplate;

    public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }

    @Override
    public int updateCfgver(String opercode) {
        return jdbcTemplate.update(CFGVER_UPDATE, opercode);
        //todo reload cfg
    }

    /**
     * 获得当前数据库中参数版本号
     *
     * @return -1 代表数据库中没有参数版本号记录
     */
    public int getCfgverno() {
        int cfgVerNo = -1;
        try {
            int i = jdbcTemplate.queryForInt(CFGVER_QUERY);
        } catch (EmptyResultDataAccessException e) {
            //没有参数版本配置记录
        }
        return cfgVerNo;
    }

    /**
     * 新增参数版本号
     *
     * @param cfgver 参数版本实体
     * @return 新增结果，保存成功时，返回值为1
     */
    public int addCfgver(Cfgver cfgver) {
        if (StringUtils.isBlank(cfgver.getLastsaved())) {
            cfgver.setLastsaved(DateUtil.getCurrentTime());
        }
        return jdbcTemplate.update(CFGVER_INSERT, cfgver.getCfgtype(), cfgver.getCfgverno(), cfgver.getOpercode(), cfgver.getLastsaved());
    }
}
