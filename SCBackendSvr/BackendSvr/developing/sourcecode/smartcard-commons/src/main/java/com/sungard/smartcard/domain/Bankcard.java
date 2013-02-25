package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_BANKCARD的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Bankcard implements Serializable {

    /**
     * 客户号
     */
    private Integer custid;
    /**
     * 银行卡号
     */
    private String bankcardno;
    /**
     * 银行编号
     */
    private String bankcode;
    /**
     * 导入批次号
     */
    private String batchno;
    /**
     * 录入日期
     */
    private String createddate;
    /**
     * 关联日期
     */
    private String relatedate;
    /**
     * 最后保存时间
     */
    private String lastsaved;

    public void setCustid(Integer custid) {
        this.custid = custid;
    }

    public Integer getCustid() {
        return this.custid;
    }

    public void setBankcardno(String bankcardno) {
        this.bankcardno = bankcardno;
    }

    public String getBankcardno() {
        return this.bankcardno;
    }

    public void setBankcode(String bankcode) {
        this.bankcode = bankcode;
    }

    public String getBankcode() {
        return this.bankcode;
    }

    public void setBatchno(String batchno) {
        this.batchno = batchno;
    }

    public String getBatchno() {
        return this.batchno;
    }

    public void setCreateddate(String createddate) {
        this.createddate = createddate;
    }

    public String getCreateddate() {
        return this.createddate;
    }

    public void setRelatedate(String relatedate) {
        this.relatedate = relatedate;
    }

    public String getRelatedate() {
        return this.relatedate;
    }

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }
}