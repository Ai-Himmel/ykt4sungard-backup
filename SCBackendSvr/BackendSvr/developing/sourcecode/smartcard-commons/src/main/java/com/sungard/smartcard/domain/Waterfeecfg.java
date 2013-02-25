package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_WATERFEECFG的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Waterfeecfg implements Serializable {

    /**
     * 费率ID
     */
    private Integer feeid;
    /**
     * 费率名称
     */
    private String feename;
    /**
     * 钱包号
     */
    private Integer purseno;
    /**
     * 费率模式
     */
    private Integer feemode;
    /**
     * 卡权限类别数量
     */
    private Integer feetypecnt;

    public void setFeeid(Integer feeid) {
        this.feeid = feeid;
    }

    public Integer getFeeid() {
        return this.feeid;
    }

    public void setFeename(String feename) {
        this.feename = feename;
    }

    public String getFeename() {
        return this.feename;
    }

    public void setPurseno(Integer purseno) {
        this.purseno = purseno;
    }

    public Integer getPurseno() {
        return this.purseno;
    }

    public void setFeemode(Integer feemode) {
        this.feemode = feemode;
    }

    public Integer getFeemode() {
        return this.feemode;
    }

    public void setFeetypecnt(Integer feetypecnt) {
        this.feetypecnt = feetypecnt;
    }

    public Integer getFeetypecnt() {
        return this.feetypecnt;
    }
}