package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_POSDTL的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Posdtl implements Serializable {

    /**
     * 交易日期
     */
    private String transdate;
    /**
     * 交易时间
     */
    private String transtime;
    /**
     * 终端号
     */
    private Integer termid;
    /**
     * 设备物理ID
     */
    private String devphyid;
    /**
     * 设备流水号
     */
    private Integer devseqno;
    /**
     * 交易卡号
     */
    private Integer cardno;
    /**
     * 钱包号
     */
    private Integer purseno;
    /**
     * 卡交易次数
     */
    private Integer cardcnt;
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
     * 数据类型
     */
    private Integer datatype;
    /**
     * 交易码
     */
    private Integer transcode;
    /**
     * 商户卡号
     */
    private Integer shopid;
    /**
     * 补助批次号
     */
    private Integer subsidyno;
    /**
     * 导入批次号
     */
    private String batchno;
    /**
     * 子系统ID
     */
    private Integer sysid;
    /**
     * 采集日期
     */
    private String coldate;
    /**
     * 采集时间
     */
    private String coltime;
    /**
     * 记账日期
     */
    private String accdate;
    /**
     * 记账时间
     */
    private String acctime;
    /**
     * 终端流水号
     */
    private Integer termseqno;
    /**
     * 状态-1初始状态2-入账失败3-成功4-异常流水
     */
    private String status;
    /**
     * 错误码
     */
    private Integer errcode;
    /**
     * 错误信息
     */
    private String errmsg;
    /**
     * 删除标志
     */
    private String delflag;

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

    public void setTermid(Integer termid) {
        this.termid = termid;
    }

    public Integer getTermid() {
        return this.termid;
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

    public void setCardcnt(Integer cardcnt) {
        this.cardcnt = cardcnt;
    }

    public Integer getCardcnt() {
        return this.cardcnt;
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

    public void setDatatype(Integer datatype) {
        this.datatype = datatype;
    }

    public Integer getDatatype() {
        return this.datatype;
    }

    public void setTranscode(Integer transcode) {
        this.transcode = transcode;
    }

    public Integer getTranscode() {
        return this.transcode;
    }

    public void setShopid(Integer shopid) {
        this.shopid = shopid;
    }

    public Integer getShopid() {
        return this.shopid;
    }

    public void setSubsidyno(Integer subsidyno) {
        this.subsidyno = subsidyno;
    }

    public Integer getSubsidyno() {
        return this.subsidyno;
    }

    public void setBatchno(String batchno) {
        this.batchno = batchno;
    }

    public String getBatchno() {
        return this.batchno;
    }

    public void setSysid(Integer sysid) {
        this.sysid = sysid;
    }

    public Integer getSysid() {
        return this.sysid;
    }

    public void setColdate(String coldate) {
        this.coldate = coldate;
    }

    public String getColdate() {
        return this.coldate;
    }

    public void setColtime(String coltime) {
        this.coltime = coltime;
    }

    public String getColtime() {
        return this.coltime;
    }

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

    public void setErrcode(Integer errcode) {
        this.errcode = errcode;
    }

    public Integer getErrcode() {
        return this.errcode;
    }

    public void setErrmsg(String errmsg) {
        this.errmsg = errmsg;
    }

    public String getErrmsg() {
        return this.errmsg;
    }

    public void setDelflag(String delflag) {
        this.delflag = delflag;
    }

    public String getDelflag() {
        return this.delflag;
    }
}