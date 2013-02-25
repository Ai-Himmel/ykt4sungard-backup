package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_BANKCHKBILL的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Bankchkbill implements Serializable {

    /**
     * 交易日期
     */
    private String transdate;
    /**
     * 银行卡号
     */
    private String bankcardno;
    /**
     * 银行端流水号
     */
    private String banksn;
    /**
     * 交易卡号
     */
    private Integer cardno;
    /**
     * 本地流水号
     */
    private String localsn;
    /**
     * 交易码
     */
    private Integer transcode;
    /**
     * 摘要
     */
    private String summary;
    /**
     * 银行端交易金额
     */
    private Double bankamt;
    /**
     * 本地交易金额
     */
    private Double localamt;
    /**
     * 差额
     */
    private Double diffamt;
    /**
     * 0-未补帐1-已补帐
     */
    private String chkflag;

    public void setTransdate(String transdate) {
        this.transdate = transdate;
    }

    public String getTransdate() {
        return this.transdate;
    }

    public void setBankcardno(String bankcardno) {
        this.bankcardno = bankcardno;
    }

    public String getBankcardno() {
        return this.bankcardno;
    }

    public void setBanksn(String banksn) {
        this.banksn = banksn;
    }

    public String getBanksn() {
        return this.banksn;
    }

    public void setCardno(Integer cardno) {
        this.cardno = cardno;
    }

    public Integer getCardno() {
        return this.cardno;
    }

    public void setLocalsn(String localsn) {
        this.localsn = localsn;
    }

    public String getLocalsn() {
        return this.localsn;
    }

    public void setTranscode(Integer transcode) {
        this.transcode = transcode;
    }

    public Integer getTranscode() {
        return this.transcode;
    }

    public void setSummary(String summary) {
        this.summary = summary;
    }

    public String getSummary() {
        return this.summary;
    }

    public void setBankamt(Double bankamt) {
        this.bankamt = bankamt;
    }

    public Double getBankamt() {
        return this.bankamt;
    }

    public void setLocalamt(Double localamt) {
        this.localamt = localamt;
    }

    public Double getLocalamt() {
        return this.localamt;
    }

    public void setDiffamt(Double diffamt) {
        this.diffamt = diffamt;
    }

    public Double getDiffamt() {
        return this.diffamt;
    }

    public void setChkflag(String chkflag) {
        this.chkflag = chkflag;
    }

    public String getChkflag() {
        return this.chkflag;
    }
}