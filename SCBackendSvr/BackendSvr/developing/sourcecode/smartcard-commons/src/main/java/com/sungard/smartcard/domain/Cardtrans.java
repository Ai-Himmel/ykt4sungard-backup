package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_CARDTRANS的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Cardtrans implements Serializable {

    /**
     * 卡号
     */
    private Integer cardno;
    /**
     * 交易日期
     */
    private String transdate;
    /**
     * 交易时间
     */
    private String transtime;
    /**
     * 交易代码
     */
    private Integer transcode;
    /**
     * 交易终端
     */
    private Integer termid;
    /**
     * 终端流水号
     */
    private Integer termseqno;
    /**
     * 充值次数
     */
    private Integer dpscnt;
    /**
     * 消费次数
     */
    private Integer paycnt;
    /**
     * 交易金额
     */
    private Double amount;
    /**
     * 交易前余额
     */
    private Double cardbefbal;
    /**
     * 交易后余额
     */
    private Double cardaftbal;
    /**
     * 更新次数
     */
    private Integer updcnt;
    /**
     * 更新时间
     */
    private String updtime;

    public void setCardno(Integer cardno) {
        this.cardno = cardno;
    }

    public Integer getCardno() {
        return this.cardno;
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

    public void setTranscode(Integer transcode) {
        this.transcode = transcode;
    }

    public Integer getTranscode() {
        return this.transcode;
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

    public void setAmount(Double amount) {
        this.amount = amount;
    }

    public Double getAmount() {
        return this.amount;
    }

    public void setCardbefbal(Double cardbefbal) {
        this.cardbefbal = cardbefbal;
    }

    public Double getCardbefbal() {
        return this.cardbefbal;
    }

    public void setCardaftbal(Double cardaftbal) {
        this.cardaftbal = cardaftbal;
    }

    public Double getCardaftbal() {
        return this.cardaftbal;
    }

    public void setUpdcnt(Integer updcnt) {
        this.updcnt = updcnt;
    }

    public Integer getUpdcnt() {
        return this.updcnt;
    }

    public void setUpdtime(String updtime) {
        this.updtime = updtime;
    }

    public String getUpdtime() {
        return this.updtime;
    }
}