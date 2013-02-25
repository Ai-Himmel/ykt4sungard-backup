package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_BANK的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Bank implements Serializable {

    /**
     * 银行ID
     */
    private Integer bankid;
    /**
     * 银行代码
     */
    private String bankcode;
    /**
     * 银行名称
     */
    private String bankname;
    /**
     * 是否启用
     */
    private Integer useflag;
    /**
     * 是否对账
     */
    private Integer chkacclag;
    /**
     * 服务开始时间
     */
    private String svrbegintime;
    /**
     * 服务截止时间
     */
    private String svrendtime;
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
     * 一卡通前置机ID
     */
    private Integer frontid;
    /**
     * 一卡通核对项
     */
    private String chktype;
    /**
     * 对账开始日期
     */
    private Integer chkbegindate;
    /**
     * 上次对账日期
     */
    private Integer lastchkdate;
    /**
     * 对账开始时间
     */
    private String chkbegintime;
    /**
     * 转换执行文件
     */
    private String cvtexecfile;
    /**
     * 对账执行文件
     */
    private String chkexecfile;
    /**
     * 对账不符自动处理
     */
    private Integer autoresolve;
    /**
     * 1:主动获取银行对账文件
     */
    private String getbankfile;

    public void setBankid(Integer bankid) {
        this.bankid = bankid;
    }

    public Integer getBankid() {
        return this.bankid;
    }

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

    public void setUseflag(Integer useflag) {
        this.useflag = useflag;
    }

    public Integer getUseflag() {
        return this.useflag;
    }

    public void setChkacclag(Integer chkacclag) {
        this.chkacclag = chkacclag;
    }

    public Integer getChkacclag() {
        return this.chkacclag;
    }

    public void setSvrbegintime(String svrbegintime) {
        this.svrbegintime = svrbegintime;
    }

    public String getSvrbegintime() {
        return this.svrbegintime;
    }

    public void setSvrendtime(String svrendtime) {
        this.svrendtime = svrendtime;
    }

    public String getSvrendtime() {
        return this.svrendtime;
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

    public void setFrontid(Integer frontid) {
        this.frontid = frontid;
    }

    public Integer getFrontid() {
        return this.frontid;
    }

    public void setChktype(String chktype) {
        this.chktype = chktype;
    }

    public String getChktype() {
        return this.chktype;
    }

    public void setChkbegindate(Integer chkbegindate) {
        this.chkbegindate = chkbegindate;
    }

    public Integer getChkbegindate() {
        return this.chkbegindate;
    }

    public void setLastchkdate(Integer lastchkdate) {
        this.lastchkdate = lastchkdate;
    }

    public Integer getLastchkdate() {
        return this.lastchkdate;
    }

    public void setChkbegintime(String chkbegintime) {
        this.chkbegintime = chkbegintime;
    }

    public String getChkbegintime() {
        return this.chkbegintime;
    }

    public void setCvtexecfile(String cvtexecfile) {
        this.cvtexecfile = cvtexecfile;
    }

    public String getCvtexecfile() {
        return this.cvtexecfile;
    }

    public void setChkexecfile(String chkexecfile) {
        this.chkexecfile = chkexecfile;
    }

    public String getChkexecfile() {
        return this.chkexecfile;
    }

    public void setAutoresolve(Integer autoresolve) {
        this.autoresolve = autoresolve;
    }

    public Integer getAutoresolve() {
        return this.autoresolve;
    }

    public void setGetbankfile(String getbankfile) {
        this.getbankfile = getbankfile;
    }

    public String getGetbankfile() {
        return this.getbankfile;
    }
}