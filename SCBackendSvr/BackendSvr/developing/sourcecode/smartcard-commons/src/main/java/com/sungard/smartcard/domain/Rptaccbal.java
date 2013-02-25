package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_RPTACCBAL的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Rptaccbal implements Serializable {

    /**
     * 记账日期
     */
    private String accdate;
    /**
     * 科目号
     */
    private String subjno;
    /**
     * 账号
     */
    private String accno;
    /**
     * 余额方向
     */
    private Integer balflag;
    /**
     * 余额
     */
    private Double balance;

    public void setAccdate(String accdate) {
        this.accdate = accdate;
    }

    public String getAccdate() {
        return this.accdate;
    }

    public void setSubjno(String subjno) {
        this.subjno = subjno;
    }

    public String getSubjno() {
        return this.subjno;
    }

    public void setAccno(String accno) {
        this.accno = accno;
    }

    public String getAccno() {
        return this.accno;
    }

    public void setBalflag(Integer balflag) {
        this.balflag = balflag;
    }

    public Integer getBalflag() {
        return this.balflag;
    }

    public void setBalance(Double balance) {
        this.balance = balance;
    }

    public Double getBalance() {
        return this.balance;
    }
}