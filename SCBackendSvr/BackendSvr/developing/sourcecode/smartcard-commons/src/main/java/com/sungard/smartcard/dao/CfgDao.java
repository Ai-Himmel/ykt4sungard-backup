package com.sungard.smartcard.dao;

import com.sungard.smartcard.domain.Cfgver;

/**
 * 系统关键参数版本号管理
 * 更新了系统参数T_SYSPARA，交易收费配置T_CFGFEE之后，要更新系统中的参数版本号
 *
 * @author Yiming.You
 * @version v1.00
 * @since 12-2-22
 */
public interface CfgDao {

    public int updateCfgver(String opercode);

    public int getCfgverno();

    public int addCfgver(Cfgver cfgver);
}
