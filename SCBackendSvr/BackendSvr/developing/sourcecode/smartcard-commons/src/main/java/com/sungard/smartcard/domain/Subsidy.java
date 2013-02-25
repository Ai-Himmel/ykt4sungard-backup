package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;


/**
 * T_SUBSIDY的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Subsidy implements Serializable {

    /**
     * 导入批次号
     */
    private String batchno;
    /**
     * 导入序号
     */
    private Integer seqno;
    /**
     * 学工号
     */
    private String stuempno;
    /**
     * 客户号
     */
    private Integer custid;
    /**
     * 补助批次号
     */
    private Integer subsidyno;
    /**
     * 交易卡号
     */
    private Integer cardno;
    /**
     * 摘要
     */
    private String summary;
    /**
     * 经办人姓名
     */
    private String brokername;
    /**
     * 经办人身份证号
     */
    private String brokeridno;
    /**
     * 支付方式:1-现金2-支票3-经费本
     */
    private Integer paytype;
    /**
     * 凭证号码
     */
    private String voucherno;
    /**
     * 发生额
     */
    private Double amount;
    /**
     * 补助类型
     */
    private String subsidytype;
    /**
     * 补助模式
     */
    private Integer subsidymode;
    /**
     * 交易日期
     */
    private String impdate;
    /**
     * 交易时间
     */
    private String imptime;
    /**
     * 下发日期
     */
    private String putdate;
    /**
     * 下发时间
     */
    private String puttime;
    /**
     * 领取日期
     */
    private String getdate;
    /**
     * 领取时间
     */
    private String gettime;
    /**
     * 状态:1-未下发2-已下发3-已领取-4-无效
     */
    private String status;
    /**
     * 审核标志
     */
    private Integer checkflag;
    /**
     * 错误信息
     */
    private String errmsg;
    /**
     * 操作员号
     */
    private String opercode;

    public void setBatchno(String batchno) {
        this.batchno = batchno;
    }

    public String getBatchno() {
        return this.batchno;
    }

    public void setSeqno(Integer seqno) {
        this.seqno = seqno;
    }

    public Integer getSeqno() {
        return this.seqno;
    }

    public void setStuempno(String stuempno) {
        this.stuempno = stuempno;
    }

    public String getStuempno() {
        return this.stuempno;
    }

    public void setCustid(Integer custid) {
        this.custid = custid;
    }

    public Integer getCustid() {
        return this.custid;
    }

    public void setSubsidyno(Integer subsidyno) {
        this.subsidyno = subsidyno;
    }

    public Integer getSubsidyno() {
        return this.subsidyno;
    }

    public void setCardno(Integer cardno) {
        this.cardno = cardno;
    }

    public Integer getCardno() {
        return this.cardno;
    }

    public void setSummary(String summary) {
        this.summary = summary;
    }

    public String getSummary() {
        return this.summary;
    }

    public void setBrokername(String brokername) {
        this.brokername = brokername;
    }

    public String getBrokername() {
        return this.brokername;
    }

    public void setBrokeridno(String brokeridno) {
        this.brokeridno = brokeridno;
    }

    public String getBrokeridno() {
        return this.brokeridno;
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

    public void setAmount(Double amount) {
        this.amount = amount;
    }

    public Double getAmount() {
        return this.amount;
    }

    public void setSubsidytype(String subsidytype) {
        this.subsidytype = subsidytype;
    }

    public String getSubsidytype() {
        return this.subsidytype;
    }

    public void setSubsidymode(Integer subsidymode) {
        this.subsidymode = subsidymode;
    }

    public Integer getSubsidymode() {
        return this.subsidymode;
    }

    public void setImpdate(String impdate) {
        this.impdate = impdate;
    }

    public String getImpdate() {
        return this.impdate;
    }

    public void setImptime(String imptime) {
        this.imptime = imptime;
    }

    public String getImptime() {
        return this.imptime;
    }

    public void setPutdate(String putdate) {
        this.putdate = putdate;
    }

    public String getPutdate() {
        return this.putdate;
    }

    public void setPuttime(String puttime) {
        this.puttime = puttime;
    }

    public String getPuttime() {
        return this.puttime;
    }

    public void setGetdate(String getdate) {
        this.getdate = getdate;
    }

    public String getGetdate() {
        return this.getdate;
    }

    public void setGettime(String gettime) {
        this.gettime = gettime;
    }

    public String getGettime() {
        return this.gettime;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getStatus() {
        return this.status;
    }

    public void setCheckflag(Integer checkflag) {
        this.checkflag = checkflag;
    }

    public Integer getCheckflag() {
        return this.checkflag;
    }

    public void setErrmsg(String errmsg) {
        this.errmsg = errmsg;
    }

    public String getErrmsg() {
        return this.errmsg;
    }

    public void setOpercode(String opercode) {
        this.opercode = opercode;
    }

    public String getOpercode() {
        return this.opercode;
    }
}