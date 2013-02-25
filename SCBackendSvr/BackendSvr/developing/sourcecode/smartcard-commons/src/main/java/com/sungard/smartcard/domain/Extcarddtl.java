package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_EXTCARDDTL的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Extcarddtl implements Serializable {

    /**
     * 交易参考号
     */
    private Double refno;
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
     * 正为加钱负为减钱
     */
    private Integer cardno;
    /**
     * 补写金额
     */
    private Integer amount;
    /**
     * 处理日期
     */
    private String transdate;
    /**
     * 处理时间
     */
    private String transtime;
    /**
     * 1未补写2已补写3已下补助
     */
    private Integer status;
    /**
     * 补写原因
     */
    private String remark;

    public void setRefno(Double refno) {
        this.refno = refno;
    }

    public Double getRefno() {
        return this.refno;
    }

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

    public void setCardno(Integer cardno) {
        this.cardno = cardno;
    }

    public Integer getCardno() {
        return this.cardno;
    }

    public void setAmount(Integer amount) {
        this.amount = amount;
    }

    public Integer getAmount() {
        return this.amount;
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

    public void setStatus(Integer status) {
        this.status = status;
    }

    public Integer getStatus() {
        return this.status;
    }

    public void setRemark(String remark) {
        this.remark = remark;
    }

    public String getRemark() {
        return this.remark;
    }
}