package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_BANKCHKDTL的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Bankchkdtl implements Serializable {

    /**
     * 银行ID
     */
    private Integer bankid;
    /**
     * 银行日期
     */
    private Integer bankdate;
    /**
     * 记录号
     */
    private Integer recordno;
    /**
     * 发生额
     */
    private Double amount;
    /**
     * 发生日期
     */
    private Integer transdate;
    /**
     * 对账结果:I-未对账E相同,存在 ,N不存在,D,不等
     */
    private String chkresult;
    /**
     * 对账
     */
    private String resolved;
    /**
     * 备注
     */
    private String remark;
    /**
     * 银行卡号
     */
    private String bankcardno;
    /**
     * 本地流水号
     */
    private String localsno;
    /**
     * 银行流水号
     */
    private String banksno;
    /**
     * 客户号
     */
    private Integer custid;
    /**
     * 学工号
     */
    private String stuempno;
    /**
     * 卡号
     */
    private Integer cardno;
    /**
     * 操作员
     */
    private String opercode;

    public void setBankid(Integer bankid) {
        this.bankid = bankid;
    }

    public Integer getBankid() {
        return this.bankid;
    }

    public void setBankdate(Integer bankdate) {
        this.bankdate = bankdate;
    }

    public Integer getBankdate() {
        return this.bankdate;
    }

    public void setRecordno(Integer recordno) {
        this.recordno = recordno;
    }

    public Integer getRecordno() {
        return this.recordno;
    }

    public void setAmount(Double amount) {
        this.amount = amount;
    }

    public Double getAmount() {
        return this.amount;
    }

    public void setTransdate(Integer transdate) {
        this.transdate = transdate;
    }

    public Integer getTransdate() {
        return this.transdate;
    }

    public void setChkresult(String chkresult) {
        this.chkresult = chkresult;
    }

    public String getChkresult() {
        return this.chkresult;
    }

    public void setResolved(String resolved) {
        this.resolved = resolved;
    }

    public String getResolved() {
        return this.resolved;
    }

    public void setRemark(String remark) {
        this.remark = remark;
    }

    public String getRemark() {
        return this.remark;
    }

    public void setBankcardno(String bankcardno) {
        this.bankcardno = bankcardno;
    }

    public String getBankcardno() {
        return this.bankcardno;
    }

    public void setLocalsno(String localsno) {
        this.localsno = localsno;
    }

    public String getLocalsno() {
        return this.localsno;
    }

    public void setBanksno(String banksno) {
        this.banksno = banksno;
    }

    public String getBanksno() {
        return this.banksno;
    }

    public void setCustid(Integer custid) {
        this.custid = custid;
    }

    public Integer getCustid() {
        return this.custid;
    }

    public void setStuempno(String stuempno) {
        this.stuempno = stuempno;
    }

    public String getStuempno() {
        return this.stuempno;
    }

    public void setCardno(Integer cardno) {
        this.cardno = cardno;
    }

    public Integer getCardno() {
        return this.cardno;
    }

    public void setOpercode(String opercode) {
        this.opercode = opercode;
    }

    public String getOpercode() {
        return this.opercode;
    }
}