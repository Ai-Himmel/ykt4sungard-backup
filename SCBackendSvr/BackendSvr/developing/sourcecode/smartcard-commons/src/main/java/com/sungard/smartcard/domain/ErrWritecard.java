package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_ERR_WRITECARD的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class ErrWritecard implements Serializable {

    /**
     *
     */
    private String accdate;
    /**
     *
     */
    private String acctime;
    /**
     *
     */
    private Integer termid;
    /**
     *
     */
    private Integer termseqno;
    /**
     *
     */
    private String transdate;
    /**
     *
     */
    private String transdate1;
    /**
     *
     */
    private String transtime;
    /**
     *
     */
    private String transtime1;
    /**
     *
     */
    private Integer transcode;
    /**
     *
     */
    private Integer transcode1;
    /**
     *
     */
    private Integer cardno;
    /**
     *
     */
    private Integer cardcnt;
    /**
     *
     */
    private Integer cardcnt1;
    /**
     *
     */
    private Double cardbefbal;
    /**
     *
     */
    private Double cardaftbal;
    /**
     *
     */
    private Double cardbefbal1;
    /**
     *
     */
    private Double cardaftbal1;
    /**
     *
     */
    private Double amount;
    /**
     *
     */
    private String devphyid;
    /**
     *
     */
    private Integer devseqno;
    /**
     *
     */
    private String status;
    /**
     *
     */
    private Integer errcode;
    /**
     *
     */
    private Double cardbal;
    /**
     *
     */
    private Double availbal;

    public void setAccdate(String accdate) {
        this.accdate = accdate;
    }

    public String getAccdate() {
        return this.accdate;
    }

    public void setAcctime(String acctime) {
        this.acctime = acctime;
    }

    public String getAcctime() {
        return this.acctime;
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

    public void setTransdate(String transdate) {
        this.transdate = transdate;
    }

    public String getTransdate() {
        return this.transdate;
    }

    public void setTransdate1(String transdate1) {
        this.transdate1 = transdate1;
    }

    public String getTransdate1() {
        return this.transdate1;
    }

    public void setTranstime(String transtime) {
        this.transtime = transtime;
    }

    public String getTranstime() {
        return this.transtime;
    }

    public void setTranstime1(String transtime1) {
        this.transtime1 = transtime1;
    }

    public String getTranstime1() {
        return this.transtime1;
    }

    public void setTranscode(Integer transcode) {
        this.transcode = transcode;
    }

    public Integer getTranscode() {
        return this.transcode;
    }

    public void setTranscode1(Integer transcode1) {
        this.transcode1 = transcode1;
    }

    public Integer getTranscode1() {
        return this.transcode1;
    }

    public void setCardno(Integer cardno) {
        this.cardno = cardno;
    }

    public Integer getCardno() {
        return this.cardno;
    }

    public void setCardcnt(Integer cardcnt) {
        this.cardcnt = cardcnt;
    }

    public Integer getCardcnt() {
        return this.cardcnt;
    }

    public void setCardcnt1(Integer cardcnt1) {
        this.cardcnt1 = cardcnt1;
    }

    public Integer getCardcnt1() {
        return this.cardcnt1;
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

    public void setCardbefbal1(Double cardbefbal1) {
        this.cardbefbal1 = cardbefbal1;
    }

    public Double getCardbefbal1() {
        return this.cardbefbal1;
    }

    public void setCardaftbal1(Double cardaftbal1) {
        this.cardaftbal1 = cardaftbal1;
    }

    public Double getCardaftbal1() {
        return this.cardaftbal1;
    }

    public void setAmount(Double amount) {
        this.amount = amount;
    }

    public Double getAmount() {
        return this.amount;
    }

    public void setDevphyid(String devphyid) {
        this.devphyid = devphyid;
    }

    public String getDevphyid() {
        return this.devphyid;
    }

    public void setDevseqno(Integer devseqno) {
        this.devseqno = devseqno;
    }

    public Integer getDevseqno() {
        return this.devseqno;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getStatus() {
        return this.status;
    }

    public void setErrcode(Integer errcode) {
        this.errcode = errcode;
    }

    public Integer getErrcode() {
        return this.errcode;
    }

    public void setCardbal(Double cardbal) {
        this.cardbal = cardbal;
    }

    public Double getCardbal() {
        return this.cardbal;
    }

    public void setAvailbal(Double availbal) {
        this.availbal = availbal;
    }

    public Double getAvailbal() {
        return this.availbal;
    }
}