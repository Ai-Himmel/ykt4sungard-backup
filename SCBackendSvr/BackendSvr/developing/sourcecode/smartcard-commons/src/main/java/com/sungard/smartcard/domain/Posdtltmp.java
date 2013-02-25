package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_POSDTLTMP的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Posdtltmp implements Serializable {

    /**
     * 交易日期
     */
    private String transdate;
    /**
     * 交易时间
     */
    private String transtime;
    /**
     * 设备物理ID
     */
    private String devphyid;
    /**
     * 设备流水号
     */
    private Integer devseqno;
    /**
     * 商户卡号
     */
    private Integer shopid;
    /**
     * 交易码
     */
    private Integer transcode;
    /**
     * 交易卡号
     */
    private Integer cardno;
    /**
     * 卡交易次数
     */
    private Integer cardcnt;
    /**
     * 钱包号
     */
    private Integer purseno;
    /**
     * 交易前卡余额
     */
    private Double cardbefbal;
    /**
     * 发生额-包含管理费
     */
    private Double amount;
    /**
     * 交易后卡余额
     */
    private Double cardaftbal;
    /**
     * 管理费
     */
    private Double managefee;
    /**
     * 交易标记
     */
    private Integer transmark;
    /**
     * 导入批次号
     */
    private String batchno;
    /**
     * 导入序号
     */
    private Integer seqno;
    /**
     * 录入日期
     */
    private String impdate;
    /**
     * 录入日期
     */
    private String imptime;
    /**
     * 录入操作员号
     */
    private String impoper;
    /**
     * 录入流水号
     */
    private Integer termseqno;
    /**
     * 流水状态:1-录入2-审核失败3-已审核
     */
    private String status;
    /**
     * 错误信息
     */
    private String errmsg;
    /**
     * 审核操作员号
     */
    private String chkoper;
    /**
     * 审核日期
     */
    private String chkdate;

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

    public void setDevphyid(String devphyid) {
        this.devphyid = devphyid;
    }

    public String getDevphyid() {
        return this.devphyid;
    }

    public void setDevseqno(Integer devseqno) {
        this.devseqno = devseqno;
    }

    public Integer getDevseqno() {
        return this.devseqno;
    }

    public void setShopid(Integer shopid) {
        this.shopid = shopid;
    }

    public Integer getShopid() {
        return this.shopid;
    }

    public void setTranscode(Integer transcode) {
        this.transcode = transcode;
    }

    public Integer getTranscode() {
        return this.transcode;
    }

    public void setCardno(Integer cardno) {
        this.cardno = cardno;
    }

    public Integer getCardno() {
        return this.cardno;
    }

    public void setCardcnt(Integer cardcnt) {
        this.cardcnt = cardcnt;
    }

    public Integer getCardcnt() {
        return this.cardcnt;
    }

    public void setPurseno(Integer purseno) {
        this.purseno = purseno;
    }

    public Integer getPurseno() {
        return this.purseno;
    }

    public void setCardbefbal(Double cardbefbal) {
        this.cardbefbal = cardbefbal;
    }

    public Double getCardbefbal() {
        return this.cardbefbal;
    }

    public void setAmount(Double amount) {
        this.amount = amount;
    }

    public Double getAmount() {
        return this.amount;
    }

    public void setCardaftbal(Double cardaftbal) {
        this.cardaftbal = cardaftbal;
    }

    public Double getCardaftbal() {
        return this.cardaftbal;
    }

    public void setManagefee(Double managefee) {
        this.managefee = managefee;
    }

    public Double getManagefee() {
        return this.managefee;
    }

    public void setTransmark(Integer transmark) {
        this.transmark = transmark;
    }

    public Integer getTransmark() {
        return this.transmark;
    }

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

    public void setImpoper(String impoper) {
        this.impoper = impoper;
    }

    public String getImpoper() {
        return this.impoper;
    }

    public void setTermseqno(Integer termseqno) {
        this.termseqno = termseqno;
    }

    public Integer getTermseqno() {
        return this.termseqno;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getStatus() {
        return this.status;
    }

    public void setErrmsg(String errmsg) {
        this.errmsg = errmsg;
    }

    public String getErrmsg() {
        return this.errmsg;
    }

    public void setChkoper(String chkoper) {
        this.chkoper = chkoper;
    }

    public String getChkoper() {
        return this.chkoper;
    }

    public void setChkdate(String chkdate) {
        this.chkdate = chkdate;
    }

    public String getChkdate() {
        return this.chkdate;
    }
}