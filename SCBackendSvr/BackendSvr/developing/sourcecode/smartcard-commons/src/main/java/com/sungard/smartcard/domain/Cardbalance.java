package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_CARDBALANCE的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Cardbalance implements Serializable {

    /**
     * 账号
     */
    private String accno;
    /**
     * 钱包类型
     */
    private Integer pursetype;
    /**
     * 交易卡号
     */
    private Integer cardno;
    /**
     * 原卡号
     */
    private Integer oldcardno;
    /**
     * 最后交易日期
     */
    private String transdate;
    /**
     * 最后交易时间
     */
    private String transtime;
    /**
     * 充值次数
     */
    private Integer dpscnt;
    /**
     * 消费次数
     */
    private Integer paycnt;
    /**
     * 账户余额
     */
    private Double balance;
    /**
     * 卡余额
     */
    private Double cardbal;
    /**
     * 累计充值金额
     */
    private Double accumdpsamt;

    public void setAccno(String accno) {
        this.accno = accno;
    }

    public String getAccno() {
        return this.accno;
    }

    public void setPursetype(Integer pursetype) {
        this.pursetype = pursetype;
    }

    public Integer getPursetype() {
        return this.pursetype;
    }

    public void setCardno(Integer cardno) {
        this.cardno = cardno;
    }

    public Integer getCardno() {
        return this.cardno;
    }

    public void setOldcardno(Integer oldcardno) {
        this.oldcardno = oldcardno;
    }

    public Integer getOldcardno() {
        return this.oldcardno;
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

    public void setDpscnt(Integer dpscnt) {
        this.dpscnt = dpscnt;
    }

    public Integer getDpscnt() {
        return this.dpscnt;
    }

    public void setPaycnt(Integer paycnt) {
        this.paycnt = paycnt;
    }

    public Integer getPaycnt() {
        return this.paycnt;
    }

    public void setBalance(Double balance) {
        this.balance = balance;
    }

    public Double getBalance() {
        return this.balance;
    }

    public void setCardbal(Double cardbal) {
        this.cardbal = cardbal;
    }

    public Double getCardbal() {
        return this.cardbal;
    }

    public void setAccumdpsamt(Double accumdpsamt) {
        this.accumdpsamt = accumdpsamt;
    }

    public Double getAccumdpsamt() {
        return this.accumdpsamt;
    }
}