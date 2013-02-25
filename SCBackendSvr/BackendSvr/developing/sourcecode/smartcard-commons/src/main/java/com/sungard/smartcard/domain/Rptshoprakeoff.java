package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_RPTSHOPRAKEOFF的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Rptshoprakeoff implements Serializable {

    /**
     * 业务日期
     */
    private String accdate;
    /**
     * 商户号
     */
    private Integer shopid;
    /**
     * 商户账号
     */
    private String accno;
    /**
     * 商户账户名
     */
    private String accname;
    /**
     * 佣金费率
     */
    private Long rakeoffrate;
    /**
     * 交易次数
     */
    private Integer transcnt;
    /**
     * 营业金额
     */
    private Double transamt;
    /**
     * 佣金金额
     */
    private Double rakeoffamt;
    /**
     * 结算金额
     */
    private Double amount;
    /**
     * 余额
     */
    private Double balance;
    /**
     * 人次
     */
    private Integer personcnt;

    public void setAccdate(String accdate) {
        this.accdate = accdate;
    }

    public String getAccdate() {
        return this.accdate;
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

    public void setRakeoffrate(Long rakeoffrate) {
        this.rakeoffrate = rakeoffrate;
    }

    public Long getRakeoffrate() {
        return this.rakeoffrate;
    }

    public void setTranscnt(Integer transcnt) {
        this.transcnt = transcnt;
    }

    public Integer getTranscnt() {
        return this.transcnt;
    }

    public void setTransamt(Double transamt) {
        this.transamt = transamt;
    }

    public Double getTransamt() {
        return this.transamt;
    }

    public void setRakeoffamt(Double rakeoffamt) {
        this.rakeoffamt = rakeoffamt;
    }

    public Double getRakeoffamt() {
        return this.rakeoffamt;
    }

    public void setAmount(Double amount) {
        this.amount = amount;
    }

    public Double getAmount() {
        return this.amount;
    }

    public void setBalance(Double balance) {
        this.balance = balance;
    }

    public Double getBalance() {
        return this.balance;
    }

    public void setPersoncnt(Integer personcnt) {
        this.personcnt = personcnt;
    }

    public Integer getPersoncnt() {
        return this.personcnt;
    }
}