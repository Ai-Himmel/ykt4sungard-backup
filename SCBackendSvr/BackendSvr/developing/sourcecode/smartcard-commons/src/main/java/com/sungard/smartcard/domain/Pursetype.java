package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_PURSETYPE的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Pursetype implements Serializable {

    /**
     * 钱包类型
     */
    private Integer pursetype;
    /**
     * 钱包类型名
     */
    private String pursetypename;
    /**
     * 最大存款金额
     */
    private Double pursemaxbal;
    /**
     * 联机标志
     */
    private Integer onlineflag;
    /**
     * 商户号
     */
    private Integer shopid;
    /**
     * 退款余额标志
     */
    private Integer refundflag;
    /**
     * 主钱包标志
     */
    private Integer primaryflag;
    /**
     * 启用标志
     */
    private Integer enableflag;
    /**
     * 备注
     */
    private String remark;
    /**
     * 最后保存时间
     */
    private String lastsaved;

    public void setPursetype(Integer pursetype) {
        this.pursetype = pursetype;
    }

    public Integer getPursetype() {
        return this.pursetype;
    }

    public void setPursetypename(String pursetypename) {
        this.pursetypename = pursetypename;
    }

    public String getPursetypename() {
        return this.pursetypename;
    }

    public void setPursemaxbal(Double pursemaxbal) {
        this.pursemaxbal = pursemaxbal;
    }

    public Double getPursemaxbal() {
        return this.pursemaxbal;
    }

    public void setOnlineflag(Integer onlineflag) {
        this.onlineflag = onlineflag;
    }

    public Integer getOnlineflag() {
        return this.onlineflag;
    }

    public void setShopid(Integer shopid) {
        this.shopid = shopid;
    }

    public Integer getShopid() {
        return this.shopid;
    }

    public void setRefundflag(Integer refundflag) {
        this.refundflag = refundflag;
    }

    public Integer getRefundflag() {
        return this.refundflag;
    }

    public void setPrimaryflag(Integer primaryflag) {
        this.primaryflag = primaryflag;
    }

    public Integer getPrimaryflag() {
        return this.primaryflag;
    }

    public void setEnableflag(Integer enableflag) {
        this.enableflag = enableflag;
    }

    public Integer getEnableflag() {
        return this.enableflag;
    }

    public void setRemark(String remark) {
        this.remark = remark;
    }

    public String getRemark() {
        return this.remark;
    }

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }
}