package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_CFGVER的实体类
 * 配置版本表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Cfgver implements Serializable {

    /**
     * 配置类型
     */
    private Integer cfgtype;
    /**
     * 配置版本
     */
    private Integer cfgverno;
    /**
     * 操作员号
     */
    private String opercode;
    /**
     * 最后保存时间
     */
    private String lastsaved;

    public void setCfgtype(Integer cfgtype) {
        this.cfgtype = cfgtype;
    }

    public Integer getCfgtype() {
        return this.cfgtype;
    }

    public void setCfgverno(Integer cfgverno) {
        this.cfgverno = cfgverno;
    }

    public Integer getCfgverno() {
        return this.cfgverno;
    }

    public void setOpercode(String opercode) {
        this.opercode = opercode;
    }

    public String getOpercode() {
        return this.opercode;
    }

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }
}