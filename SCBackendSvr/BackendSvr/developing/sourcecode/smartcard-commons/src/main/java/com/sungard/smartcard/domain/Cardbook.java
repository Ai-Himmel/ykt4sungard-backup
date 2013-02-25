package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_CARDBOOK的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Cardbook implements Serializable {

    /**
     * 记录号
     */
    private Double showcardno;
    /**
     * 卡类型
     */
    private Integer cardtype;
    /**
     * 卡物理ID
     */
    private String cardphyid;
    /**
     * 操作员号
     */
    private String opercode;
    /**
     * 转交操作员
     */
    private String putopercode;
    /**
     * 领入批次号
     */
    private String batchno;
    /**
     * 领入日期
     */
    private String getdate;
    /**
     * 使用日期
     */
    private String usedate;
    /**
     * 回收日期
     */
    private String reclaimdate;
    /**
     * 使用状态
     */
    private Integer usestatus;

    public void setShowcardno(Double showcardno) {
        this.showcardno = showcardno;
    }

    public Double getShowcardno() {
        return this.showcardno;
    }

    public void setCardtype(Integer cardtype) {
        this.cardtype = cardtype;
    }

    public Integer getCardtype() {
        return this.cardtype;
    }

    public void setCardphyid(String cardphyid) {
        this.cardphyid = cardphyid;
    }

    public String getCardphyid() {
        return this.cardphyid;
    }

    public void setOpercode(String opercode) {
        this.opercode = opercode;
    }

    public String getOpercode() {
        return this.opercode;
    }

    public void setPutopercode(String putopercode) {
        this.putopercode = putopercode;
    }

    public String getPutopercode() {
        return this.putopercode;
    }

    public void setBatchno(String batchno) {
        this.batchno = batchno;
    }

    public String getBatchno() {
        return this.batchno;
    }

    public void setGetdate(String getdate) {
        this.getdate = getdate;
    }

    public String getGetdate() {
        return this.getdate;
    }

    public void setUsedate(String usedate) {
        this.usedate = usedate;
    }

    public String getUsedate() {
        return this.usedate;
    }

    public void setReclaimdate(String reclaimdate) {
        this.reclaimdate = reclaimdate;
    }

    public String getReclaimdate() {
        return this.reclaimdate;
    }

    public void setUsestatus(Integer usestatus) {
        this.usestatus = usestatus;
    }

    public Integer getUsestatus() {
        return this.usestatus;
    }
}