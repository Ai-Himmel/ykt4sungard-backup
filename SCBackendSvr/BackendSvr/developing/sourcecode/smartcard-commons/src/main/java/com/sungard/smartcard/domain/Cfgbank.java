package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_CFGBANK的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Cfgbank implements Serializable {

    /**
     * 银行代码
     */
    private String bankcode;
    /**
     * 银行名称
     */
    private String bankname;
    /**
     * 银行服务开始时间
     */
    private String bankstarttime;
    /**
     * 银行服务截止时间
     */
    private String bankendtime;
    /**
     * 银行IP
     */
    private String bankip;
    /**
     * 银行端口
     */
    private Integer bankport;
    /**
     * 银行端超时时间
     */
    private Integer banktimeout;
    /**
     * 前置机节点
     */
    private Integer bccdrtpno;
    /**
     * 前置机功能号
     */
    private Integer bccfuncno;
    /**
     * 前置机超时
     */
    private Integer bcctimeout;
    /**
     * QRYCARDFLAG
     */
    private Integer qrycardflag;

    public void setBankcode(String bankcode) {
        this.bankcode = bankcode;
    }

    public String getBankcode() {
        return this.bankcode;
    }

    public void setBankname(String bankname) {
        this.bankname = bankname;
    }

    public String getBankname() {
        return this.bankname;
    }

    public void setBankstarttime(String bankstarttime) {
        this.bankstarttime = bankstarttime;
    }

    public String getBankstarttime() {
        return this.bankstarttime;
    }

    public void setBankendtime(String bankendtime) {
        this.bankendtime = bankendtime;
    }

    public String getBankendtime() {
        return this.bankendtime;
    }

    public void setBankip(String bankip) {
        this.bankip = bankip;
    }

    public String getBankip() {
        return this.bankip;
    }

    public void setBankport(Integer bankport) {
        this.bankport = bankport;
    }

    public Integer getBankport() {
        return this.bankport;
    }

    public void setBanktimeout(Integer banktimeout) {
        this.banktimeout = banktimeout;
    }

    public Integer getBanktimeout() {
        return this.banktimeout;
    }

    public void setBccdrtpno(Integer bccdrtpno) {
        this.bccdrtpno = bccdrtpno;
    }

    public Integer getBccdrtpno() {
        return this.bccdrtpno;
    }

    public void setBccfuncno(Integer bccfuncno) {
        this.bccfuncno = bccfuncno;
    }

    public Integer getBccfuncno() {
        return this.bccfuncno;
    }

    public void setBcctimeout(Integer bcctimeout) {
        this.bcctimeout = bcctimeout;
    }

    public Integer getBcctimeout() {
        return this.bcctimeout;
    }

    public void setQrycardflag(Integer qrycardflag) {
        this.qrycardflag = qrycardflag;
    }

    public Integer getQrycardflag() {
        return this.qrycardflag;
    }
}