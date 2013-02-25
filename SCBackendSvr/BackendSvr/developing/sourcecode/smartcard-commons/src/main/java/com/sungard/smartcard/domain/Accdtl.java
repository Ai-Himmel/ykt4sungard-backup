package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_ACCDTL的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Accdtl implements Serializable {

    /**
     * 记账日期
     */
    private String accdate;
    /**
     * 记账时间
     */
    private String acctime;
    /**
     * 终端编号(站点号、设备ID)
     */
    private Integer termid;
    /**
     * 终端流水号
     */
    private Integer termseqno;
    /**
     * 子流水号
     */
    private Integer subseqno;
    /**
     * 交易日期,取系统日期
     */
    private String transdate;
    /**
     * 交易时间,取系统时间
     */
    private String transtime;
    /**
     * 凭证类型
     */
    private Integer paytype;
    /**
     * 凭证号(支票、经费本号码)
     */
    private String voucherno;
    /**
     * 交易码
     */
    private Integer transcode;
    /**
     * 交易类别
     */
    private Integer transtype;
    /**
     * 摘要
     */
    private String summary;
    /**
     * 科目号
     */
    private String subjno;
    /**
     * 账号
     */
    private String accno;
    /**
     * 帐户名
     */
    private String accname;
    /**
     * 借贷
     */
    private Integer dcflag;
    /**
     * 发生额
     */
    private Double amount;
    /**
     * 帐户余额
     */
    private Double balance;
    /**
     * 对方科目
     */
    private String oppsubjno;
    /**
     * 对方账号
     */
    private String oppaccno;
    /**
     * 对方帐户名
     */
    private String oppaccname;
    /**
     * 操作员号
     */
    private String opercode;
    /**
     * 备注
     */
    private String remark;

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

    public void setSubseqno(Integer subseqno) {
        this.subseqno = subseqno;
    }

    public Integer getSubseqno() {
        return this.subseqno;
    }

    public void setTransdate(String transdate) {
        this.transdate = transdate;
    }

    public String getTransdate() {
        return this.transdate;
    }

    public void setTranstime(String transtime) {
        this.transtime = transtime;
    }

    public String getTranstime() {
        return this.transtime;
    }

    public void setPaytype(Integer paytype) {
        this.paytype = paytype;
    }

    public Integer getPaytype() {
        return this.paytype;
    }

    public void setVoucherno(String voucherno) {
        this.voucherno = voucherno;
    }

    public String getVoucherno() {
        return this.voucherno;
    }

    public void setTranscode(Integer transcode) {
        this.transcode = transcode;
    }

    public Integer getTranscode() {
        return this.transcode;
    }

    public void setTranstype(Integer transtype) {
        this.transtype = transtype;
    }

    public Integer getTranstype() {
        return this.transtype;
    }

    public void setSummary(String summary) {
        this.summary = summary;
    }

    public String getSummary() {
        return this.summary;
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

    public void setAccname(String accname) {
        this.accname = accname;
    }

    public String getAccname() {
        return this.accname;
    }

    public void setDcflag(Integer dcflag) {
        this.dcflag = dcflag;
    }

    public Integer getDcflag() {
        return this.dcflag;
    }

    public void setAmount(Double amount) {
        this.amount = amount;
    }

    public Double getAmount() {
        return this.amount;
    }

    public void setBalance(Double balance) {
        this.balance = balance;
    }

    public Double getBalance() {
        return this.balance;
    }

    public void setOppsubjno(String oppsubjno) {
        this.oppsubjno = oppsubjno;
    }

    public String getOppsubjno() {
        return this.oppsubjno;
    }

    public void setOppaccno(String oppaccno) {
        this.oppaccno = oppaccno;
    }

    public String getOppaccno() {
        return this.oppaccno;
    }

    public void setOppaccname(String oppaccname) {
        this.oppaccname = oppaccname;
    }

    public String getOppaccname() {
        return this.oppaccname;
    }

    public void setOpercode(String opercode) {
        this.opercode = opercode;
    }

    public String getOpercode() {
        return this.opercode;
    }

    public void setRemark(String remark) {
        this.remark = remark;
    }

    public String getRemark() {
        return this.remark;
    }
}