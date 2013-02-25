package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_EXCEPTDTL的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Exceptdtl implements Serializable {

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
     * 交易参考号
     */
    private Double refno;
    /**
     * 卡号
     */
    private Integer cardno;
    /**
     * 钱包号
     */
    private Integer purseno;
    /**
     * 卡充值次数
     */
    private Integer dpscnt;
    /**
     * 卡消费次数
     */
    private Integer paycnt;
    /**
     * 卡交易前余额
     */
    private Double cardbefbal;
    /**
     * 卡交易后余额
     */
    private Double cardaftbal;
    /**
     * 0-中途拔卡1写卡失败
     */
    private Integer failtype;
    /**
     * 0-未处理2失败3成功
     */
    private Integer status;
    /**
     * 备注
     */
    private String remark;
    /**
     * 最后保存时间
     */
    private String lastsaved;

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

    public void setRefno(Double refno) {
        this.refno = refno;
    }

    public Double getRefno() {
        return this.refno;
    }

    public void setCardno(Integer cardno) {
        this.cardno = cardno;
    }

    public Integer getCardno() {
        return this.cardno;
    }

    public void setPurseno(Integer purseno) {
        this.purseno = purseno;
    }

    public Integer getPurseno() {
        return this.purseno;
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

    public void setFailtype(Integer failtype) {
        this.failtype = failtype;
    }

    public Integer getFailtype() {
        return this.failtype;
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

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }
}