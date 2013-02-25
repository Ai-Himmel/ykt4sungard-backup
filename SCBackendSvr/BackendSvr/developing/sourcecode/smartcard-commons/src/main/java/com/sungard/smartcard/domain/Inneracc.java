package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_INNERACC的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Inneracc implements Serializable {

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
     * 昨日余额
     */
    private Double ydaybal;
    /**
     * 帐户余额
     */
    private Double balance;
    /**
     * 余额方向
     */
    private Integer balflag;
    /**
     * 上次交易日期
     */
    private String lasttransdate;
    /**
     * 上次清算日期
     */
    private String lastaccdate;

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

    public void setBalflag(Integer balflag) {
        this.balflag = balflag;
    }

    public Integer getBalflag() {
        return this.balflag;
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
}