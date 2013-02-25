package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_NETACC的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Netacc implements Serializable {

    /**
     * 账号
     */
    private String accno;
    /**
     * 帐户名
     */
    private String accname;
    /**
     * 科目号
     */
    private String subjno;
    /**
     * 帐户密码
     */
    private String accpwd;
    /**
     * 客户号
     */
    private Integer custid;
    /**
     * 止付标志
     */
    private Integer stoppayflag;
    /**
     * 状态
     */
    private String status;
    /**
     * 昨日余额
     */
    private Double ydaybal;
    /**
     * 帐户余额
     */
    private Double balance;
    /**
     * 可用余额
     */
    private Double availbal;
    /**
     * 冻结余额
     */
    private Double frozebal;
    /**
     * 上次交易日期
     */
    private String lasttransdate;
    /**
     * 上次清算日期
     */
    private String lastaccdate;
    /**
     * 开户日期
     */
    private String opendate;
    /**
     * 销户日期
     */
    private String closedate;
    /**
     * 支付密码
     */
    private String paypwd;
    /**
     * 登陆失败次数
     */
    private Integer failedcnt;
    /**
     * 最后登陆成功时间
     */
    private String lastlogintime;
    /**
     * 最后锁定时间
     */
    private String lastblocktime;
    /**
     * 最后解锁时间
     */
    private String lastunblocktime;

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

    public void setSubjno(String subjno) {
        this.subjno = subjno;
    }

    public String getSubjno() {
        return this.subjno;
    }

    public void setAccpwd(String accpwd) {
        this.accpwd = accpwd;
    }

    public String getAccpwd() {
        return this.accpwd;
    }

    public void setCustid(Integer custid) {
        this.custid = custid;
    }

    public Integer getCustid() {
        return this.custid;
    }

    public void setStoppayflag(Integer stoppayflag) {
        this.stoppayflag = stoppayflag;
    }

    public Integer getStoppayflag() {
        return this.stoppayflag;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getStatus() {
        return this.status;
    }

    public void setYdaybal(Double ydaybal) {
        this.ydaybal = ydaybal;
    }

    public Double getYdaybal() {
        return this.ydaybal;
    }

    public void setBalance(Double balance) {
        this.balance = balance;
    }

    public Double getBalance() {
        return this.balance;
    }

    public void setAvailbal(Double availbal) {
        this.availbal = availbal;
    }

    public Double getAvailbal() {
        return this.availbal;
    }

    public void setFrozebal(Double frozebal) {
        this.frozebal = frozebal;
    }

    public Double getFrozebal() {
        return this.frozebal;
    }

    public void setLasttransdate(String lasttransdate) {
        this.lasttransdate = lasttransdate;
    }

    public String getLasttransdate() {
        return this.lasttransdate;
    }

    public void setLastaccdate(String lastaccdate) {
        this.lastaccdate = lastaccdate;
    }

    public String getLastaccdate() {
        return this.lastaccdate;
    }

    public void setOpendate(String opendate) {
        this.opendate = opendate;
    }

    public String getOpendate() {
        return this.opendate;
    }

    public void setClosedate(String closedate) {
        this.closedate = closedate;
    }

    public String getClosedate() {
        return this.closedate;
    }

    public void setPaypwd(String paypwd) {
        this.paypwd = paypwd;
    }

    public String getPaypwd() {
        return this.paypwd;
    }

    public void setFailedcnt(Integer failedcnt) {
        this.failedcnt = failedcnt;
    }

    public Integer getFailedcnt() {
        return this.failedcnt;
    }

    public void setLastlogintime(String lastlogintime) {
        this.lastlogintime = lastlogintime;
    }

    public String getLastlogintime() {
        return this.lastlogintime;
    }

    public void setLastblocktime(String lastblocktime) {
        this.lastblocktime = lastblocktime;
    }

    public String getLastblocktime() {
        return this.lastblocktime;
    }

    public void setLastunblocktime(String lastunblocktime) {
        this.lastunblocktime = lastunblocktime;
    }

    public String getLastunblocktime() {
        return this.lastunblocktime;
    }
}