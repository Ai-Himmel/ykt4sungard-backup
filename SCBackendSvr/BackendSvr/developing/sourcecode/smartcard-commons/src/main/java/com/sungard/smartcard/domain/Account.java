package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_ACCOUNT的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Account implements Serializable {

    /**
     * 账号
     */
    private String accno;
    /**
     * 帐户名称
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
     * 交易卡号
     */
    private Integer cardno;
    /**
     * 钱包号
     */
    private Integer purseno;
    /**
     * 单次消费限额
     */
    private Double singlemaxamt;
    /**
     * 日消费限额
     */
    private Double daycostmaxamt;
    /**
     * 日累计消费金额
     */
    private Double daycostamt;
    /**
     * 卡最大金额
     */
    private Double cardmaxbal;
    /**
     * 状态
     */
    private String status;
    /**
     * 押金
     */
    private Double foregift;
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
     * 代领补助金额
     */
    private Double subsidybal;
    /**
     * 补助批次号
     */
    private Integer subsidyno;
    /**
     * 卡余额
     */
    private Double cardbal;
    /**
     * 卡交易次数
     */
    private Integer cardcnt;
    /**
     * 卡充值次数
     */
    private Integer dpscnt;
    /**
     * 卡消费次数
     */
    private Integer paycnt;
    /**
     * 交易终端号
     */
    private Integer termid;
    /**
     * 交易时间
     */
    private String transtime;
    /**
     * 上次补助金额
     */
    private Double lastsubsidyamt;
    /**
     * 上次补助批次号
     */
    private Integer lastsubsidyno;
    /**
     * 上次卡余额
     */
    private Double lastcardbal;
    /**
     * 上次交易次数
     */
    private Integer lastcardcnt;
    /**
     * 上次卡充值次数
     */
    private Integer lastdpscnt;
    /**
     * 上次消费次数
     */
    private Integer lastpaycnt;
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

    public void setCardno(Integer cardno) {
        this.cardno = cardno;
    }

    public Integer getCardno() {
        return this.cardno;
    }

    public void setPurseno(Integer purseno) {
        this.purseno = purseno;
    }

    public Integer getPurseno() {
        return this.purseno;
    }

    public void setSinglemaxamt(Double singlemaxamt) {
        this.singlemaxamt = singlemaxamt;
    }

    public Double getSinglemaxamt() {
        return this.singlemaxamt;
    }

    public void setDaycostmaxamt(Double daycostmaxamt) {
        this.daycostmaxamt = daycostmaxamt;
    }

    public Double getDaycostmaxamt() {
        return this.daycostmaxamt;
    }

    public void setDaycostamt(Double daycostamt) {
        this.daycostamt = daycostamt;
    }

    public Double getDaycostamt() {
        return this.daycostamt;
    }

    public void setCardmaxbal(Double cardmaxbal) {
        this.cardmaxbal = cardmaxbal;
    }

    public Double getCardmaxbal() {
        return this.cardmaxbal;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getStatus() {
        return this.status;
    }

    public void setForegift(Double foregift) {
        this.foregift = foregift;
    }

    public Double getForegift() {
        return this.foregift;
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

    public void setSubsidybal(Double subsidybal) {
        this.subsidybal = subsidybal;
    }

    public Double getSubsidybal() {
        return this.subsidybal;
    }

    public void setSubsidyno(Integer subsidyno) {
        this.subsidyno = subsidyno;
    }

    public Integer getSubsidyno() {
        return this.subsidyno;
    }

    public void setCardbal(Double cardbal) {
        this.cardbal = cardbal;
    }

    public Double getCardbal() {
        return this.cardbal;
    }

    public void setCardcnt(Integer cardcnt) {
        this.cardcnt = cardcnt;
    }

    public Integer getCardcnt() {
        return this.cardcnt;
    }

    public void setDpscnt(Integer dpscnt) {
        this.dpscnt = dpscnt;
    }

    public Integer getDpscnt() {
        return this.dpscnt;
    }

    public void setPaycnt(Integer paycnt) {
        this.paycnt = paycnt;
    }

    public Integer getPaycnt() {
        return this.paycnt;
    }

    public void setTermid(Integer termid) {
        this.termid = termid;
    }

    public Integer getTermid() {
        return this.termid;
    }

    public void setTranstime(String transtime) {
        this.transtime = transtime;
    }

    public String getTranstime() {
        return this.transtime;
    }

    public void setLastsubsidyamt(Double lastsubsidyamt) {
        this.lastsubsidyamt = lastsubsidyamt;
    }

    public Double getLastsubsidyamt() {
        return this.lastsubsidyamt;
    }

    public void setLastsubsidyno(Integer lastsubsidyno) {
        this.lastsubsidyno = lastsubsidyno;
    }

    public Integer getLastsubsidyno() {
        return this.lastsubsidyno;
    }

    public void setLastcardbal(Double lastcardbal) {
        this.lastcardbal = lastcardbal;
    }

    public Double getLastcardbal() {
        return this.lastcardbal;
    }

    public void setLastcardcnt(Integer lastcardcnt) {
        this.lastcardcnt = lastcardcnt;
    }

    public Integer getLastcardcnt() {
        return this.lastcardcnt;
    }

    public void setLastdpscnt(Integer lastdpscnt) {
        this.lastdpscnt = lastdpscnt;
    }

    public Integer getLastdpscnt() {
        return this.lastdpscnt;
    }

    public void setLastpaycnt(Integer lastpaycnt) {
        this.lastpaycnt = lastpaycnt;
    }

    public Integer getLastpaycnt() {
        return this.lastpaycnt;
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
}