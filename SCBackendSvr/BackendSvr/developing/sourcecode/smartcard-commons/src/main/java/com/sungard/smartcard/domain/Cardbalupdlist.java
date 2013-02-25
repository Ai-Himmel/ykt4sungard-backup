package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_CARDBALUPDLIST的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Cardbalupdlist implements Serializable {

    /**
     * 批次号
     */
    private String batchno;
    /**
     * 下发序号
     */
    private Integer seqno;
    /**
     * 卡号
     */
    private Integer cardno;
    /**
     * 发生日期
     */
    private Integer transdate;
    /**
     * N-未处理P已下发S已领取F写卡失败I写卡中断C撤销
     */
    private String status;
    /**
     * 补写金额正为加钱负为减钱
     */
    private Double amount;
    /**
     * 摘要
     */
    private String summary;
    /**
     * 原交易代码
     */
    private Integer transcode;
    /**
     * 更新时间
     */
    private String lastupdtime;

    public void setBatchno(String batchno) {
        this.batchno = batchno;
    }

    public String getBatchno() {
        return this.batchno;
    }

    public void setSeqno(Integer seqno) {
        this.seqno = seqno;
    }

    public Integer getSeqno() {
        return this.seqno;
    }

    public void setCardno(Integer cardno) {
        this.cardno = cardno;
    }

    public Integer getCardno() {
        return this.cardno;
    }

    public void setTransdate(Integer transdate) {
        this.transdate = transdate;
    }

    public Integer getTransdate() {
        return this.transdate;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getStatus() {
        return this.status;
    }

    public void setAmount(Double amount) {
        this.amount = amount;
    }

    public Double getAmount() {
        return this.amount;
    }

    public void setSummary(String summary) {
        this.summary = summary;
    }

    public String getSummary() {
        return this.summary;
    }

    public void setTranscode(Integer transcode) {
        this.transcode = transcode;
    }

    public Integer getTranscode() {
        return this.transcode;
    }

    public void setLastupdtime(String lastupdtime) {
        this.lastupdtime = lastupdtime;
    }

    public String getLastupdtime() {
        return this.lastupdtime;
    }
}