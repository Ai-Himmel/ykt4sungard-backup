package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_PAYMENTDTL的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Paymentdtl implements Serializable {

    /**
     * 记账日期
     */
    private String accdate;
    /**
     * 终端号
     */
    private Integer termid;
    /**
     * 终端流水号
     */
    private Integer termseqno;
    /**
     * 商户号
     */
    private Integer shopid;
    /**
     * 账号
     */
    private String accno;
    /**
     * 账户名
     */
    private String accname;
    /**
     * 交易日期
     */
    private String transdate;
    /**
     * 交易时间
     */
    private String transtime;
    /**
     * 金额
     */
    private Double amount;
    /**
     * 付款方银行账号
     */
    private String paybankaccno;
    /**
     * 付款方银行账户名
     */
    private String paybankaccname;
    /**
     * 收款方银行账号
     */
    private String payeebankaccno;
    /**
     * 收款方银行账户名
     */
    private String payeebankaccname;
    /**
     * 操作员号
     */
    private String opercode;

    public void setAccdate(String accdate) {
        this.accdate = accdate;
    }

    public String getAccdate() {
        return this.accdate;
    }

    public void setTermid(Integer termid) {
        this.termid = termid;
    }

    public Integer getTermid() {
        return this.termid;
    }

    public void setTermseqno(Integer termseqno) {
        this.termseqno = termseqno;
    }

    public Integer getTermseqno() {
        return this.termseqno;
    }

    public void setShopid(Integer shopid) {
        this.shopid = shopid;
    }

    public Integer getShopid() {
        return this.shopid;
    }

    public void setAccno(String accno) {
        this.accno = accno;
    }

    public String getAccno() {
        return this.accno;
    }

    public void setAccname(String accname) {
        this.accname = accname;
    }

    public String getAccname() {
        return this.accname;
    }

    public void setTransdate(String transdate) {
        this.transdate = transdate;
    }

    public String getTransdate() {
        return this.transdate;
    }

    public void setTranstime(String transtime) {
        this.transtime = transtime;
    }

    public String getTranstime() {
        return this.transtime;
    }

    public void setAmount(Double amount) {
        this.amount = amount;
    }

    public Double getAmount() {
        return this.amount;
    }

    public void setPaybankaccno(String paybankaccno) {
        this.paybankaccno = paybankaccno;
    }

    public String getPaybankaccno() {
        return this.paybankaccno;
    }

    public void setPaybankaccname(String paybankaccname) {
        this.paybankaccname = paybankaccname;
    }

    public String getPaybankaccname() {
        return this.paybankaccname;
    }

    public void setPayeebankaccno(String payeebankaccno) {
        this.payeebankaccno = payeebankaccno;
    }

    public String getPayeebankaccno() {
        return this.payeebankaccno;
    }

    public void setPayeebankaccname(String payeebankaccname) {
        this.payeebankaccname = payeebankaccname;
    }

    public String getPayeebankaccname() {
        return this.payeebankaccname;
    }

    public void setOpercode(String opercode) {
        this.opercode = opercode;
    }

    public String getOpercode() {
        return this.opercode;
    }
}