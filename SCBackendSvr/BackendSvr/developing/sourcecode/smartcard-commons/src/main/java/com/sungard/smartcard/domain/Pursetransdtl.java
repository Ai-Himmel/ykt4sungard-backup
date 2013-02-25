package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_PURSETRANSDTL的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Pursetransdtl implements Serializable {

    /**
     * 记账日期
     */
    private String accdate;
    /**
     * 记账时间
     */
    private String acctime;
    /**
     * 终端编号
     */
    private Integer termid;
    /**
     * 终端流水号
     */
    private Integer termseqno;
    /**
     * 钱包类型
     */
    private Integer pursetype;
    /**
     * 交易日期
     */
    private String transdate;
    /**
     * 交易时间
     */
    private String transtime;
    /**
     * 交易参考号
     */
    private Double refno;
    /**
     * 交易码
     */
    private Integer transcode;
    /**
     * 客户号
     */
    private Integer custid;
    /**
     * 客户名
     */
    private String custname;
    /**
     * 学工号
     */
    private String stuempno;
    /**
     * 显示卡号
     */
    private Double showcardno;
    /**
     * 卡号
     */
    private Integer cardno;
    /**
     * 1充值标志2消费次数
     */
    private Integer transflag;
    /**
     * 卡交易次数
     */
    private Integer cardcnt;
    /**
     * 交易前卡余额
     */
    private Double cardbefbal;
    /**
     * 交易后卡余额
     */
    private Double cardaftbal;
    /**
     * 发生额
     */
    private Double amount;
    /**
     * 操作员号
     */
    private String opercode;
    /**
     * 子系统编号
     */
    private Integer sysid;
    /**
     * 设备物理ID
     */
    private String devphyid;
    /**
     * 设备流水号
     */
    private Integer devseqno;
    /**
     * 采集日期
     */
    private String coldate;
    /**
     * 采集时间
     */
    private String coltime;
    /**
     * 记录状态1:未入账2-入账失败3-成功
     */
    private String status;
    /**
     * 错误码
     */
    private Integer errcode;
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

    public void setPursetype(Integer pursetype) {
        this.pursetype = pursetype;
    }

    public Integer getPursetype() {
        return this.pursetype;
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

    public void setRefno(Double refno) {
        this.refno = refno;
    }

    public Double getRefno() {
        return this.refno;
    }

    public void setTranscode(Integer transcode) {
        this.transcode = transcode;
    }

    public Integer getTranscode() {
        return this.transcode;
    }

    public void setCustid(Integer custid) {
        this.custid = custid;
    }

    public Integer getCustid() {
        return this.custid;
    }

    public void setCustname(String custname) {
        this.custname = custname;
    }

    public String getCustname() {
        return this.custname;
    }

    public void setStuempno(String stuempno) {
        this.stuempno = stuempno;
    }

    public String getStuempno() {
        return this.stuempno;
    }

    public void setShowcardno(Double showcardno) {
        this.showcardno = showcardno;
    }

    public Double getShowcardno() {
        return this.showcardno;
    }

    public void setCardno(Integer cardno) {
        this.cardno = cardno;
    }

    public Integer getCardno() {
        return this.cardno;
    }

    public void setTransflag(Integer transflag) {
        this.transflag = transflag;
    }

    public Integer getTransflag() {
        return this.transflag;
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

    public void setCardaftbal(Double cardaftbal) {
        this.cardaftbal = cardaftbal;
    }

    public Double getCardaftbal() {
        return this.cardaftbal;
    }

    public void setAmount(Double amount) {
        this.amount = amount;
    }

    public Double getAmount() {
        return this.amount;
    }

    public void setOpercode(String opercode) {
        this.opercode = opercode;
    }

    public String getOpercode() {
        return this.opercode;
    }

    public void setSysid(Integer sysid) {
        this.sysid = sysid;
    }

    public Integer getSysid() {
        return this.sysid;
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

    public void setRemark(String remark) {
        this.remark = remark;
    }

    public String getRemark() {
        return this.remark;
    }
}