package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_CFGSPLIT的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Cfgsplit implements Serializable {

    /**
     * 交易类型
     */
    private Integer transtype;
    /**
     * 资金类型
     */
    private Integer fundtype;
    /**
     * 脱机标志1-脱机0-联机
     */
    private Integer offlineflag;
    /**
     * 卡交易标志
     */
    private Integer usecardflag;
    /**
     * 计算卡余额标志
     */
    private Integer calccardbal;
    /**
     * 借方标志
     */
    private String draccflag;
    /**
     * 借方科目
     */
    private String drsubjno;
    /**
     * 借方账号
     */
    private String draccno;
    /**
     * 贷方标志
     */
    private String craccflag;
    /**
     * 贷方科目
     */
    private String crsubjno;
    /**
     * 贷方账号
     */
    private String craccno;
    /**
     * 摘要
     */
    private String summary;

    public void setTranstype(Integer transtype) {
        this.transtype = transtype;
    }

    public Integer getTranstype() {
        return this.transtype;
    }

    public void setFundtype(Integer fundtype) {
        this.fundtype = fundtype;
    }

    public Integer getFundtype() {
        return this.fundtype;
    }

    public void setOfflineflag(Integer offlineflag) {
        this.offlineflag = offlineflag;
    }

    public Integer getOfflineflag() {
        return this.offlineflag;
    }

    public void setUsecardflag(Integer usecardflag) {
        this.usecardflag = usecardflag;
    }

    public Integer getUsecardflag() {
        return this.usecardflag;
    }

    public void setCalccardbal(Integer calccardbal) {
        this.calccardbal = calccardbal;
    }

    public Integer getCalccardbal() {
        return this.calccardbal;
    }

    public void setDraccflag(String draccflag) {
        this.draccflag = draccflag;
    }

    public String getDraccflag() {
        return this.draccflag;
    }

    public void setDrsubjno(String drsubjno) {
        this.drsubjno = drsubjno;
    }

    public String getDrsubjno() {
        return this.drsubjno;
    }

    public void setDraccno(String draccno) {
        this.draccno = draccno;
    }

    public String getDraccno() {
        return this.draccno;
    }

    public void setCraccflag(String craccflag) {
        this.craccflag = craccflag;
    }

    public String getCraccflag() {
        return this.craccflag;
    }

    public void setCrsubjno(String crsubjno) {
        this.crsubjno = crsubjno;
    }

    public String getCrsubjno() {
        return this.crsubjno;
    }

    public void setCraccno(String craccno) {
        this.craccno = craccno;
    }

    public String getCraccno() {
        return this.craccno;
    }

    public void setSummary(String summary) {
        this.summary = summary;
    }

    public String getSummary() {
        return this.summary;
    }
}