package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_REFNO的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Refno implements Serializable {

    /**
     * 交易参考号
     */
    private Double refno;
    /**
     * MAC码
     */
    private String mac;
    /**
     * 状态
     */
    private Integer status;
    /**
     * 请求方参考号
     */
    private String reqrefno;
    /**
     * 记账日期
     */
    private String accdate;
    /**
     * 终端编号
     */
    private Integer termid;
    /**
     * 终端流水号
     */
    private Integer termseqno;
    /**
     * 最后保存时间
     */
    private String lastsaved;

    public void setRefno(Double refno) {
        this.refno = refno;
    }

    public Double getRefno() {
        return this.refno;
    }

    public void setMac(String mac) {
        this.mac = mac;
    }

    public String getMac() {
        return this.mac;
    }

    public void setStatus(Integer status) {
        this.status = status;
    }

    public Integer getStatus() {
        return this.status;
    }

    public void setReqrefno(String reqrefno) {
        this.reqrefno = reqrefno;
    }

    public String getReqrefno() {
        return this.reqrefno;
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

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }
}