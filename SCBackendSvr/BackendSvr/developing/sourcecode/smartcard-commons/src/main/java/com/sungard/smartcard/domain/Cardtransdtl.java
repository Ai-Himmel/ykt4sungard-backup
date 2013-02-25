package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_CARDTRANSDTL的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Cardtransdtl implements Serializable {

    /**
     * 交易卡号
     */
    private Integer cardno;
    /**
     * 交易标志
     */
    private Integer transflag;
    /**
     * 卡交易次数
     */
    private Integer cardcnt;
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
    private String termno;
    /**
     * 终端流水号
     */
    private Integer termsno;
    /**
     * 交易前卡余额
     */
    private Double cardbefbal;
    /**
     * 发生额-包含管理费
     */
    private Double amount;
    /**
     * 补写金额
     */
    private Double addamt;
    /**
     * 管理费
     */
    private Double managefee;
    /**
     * 商户卡号
     */
    private Integer shopid;
    /**
     * 采集日期
     */
    private String coldate;
    /**
     * 采集时间
     */
    private String coltime;
    /**
     * 状态-1初始状态2-入账失败3-成功4-异常流水
     */
    private Integer status;
    /**
     * 备注
     */
    private String remark;

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

    public void setTermno(String termno) {
        this.termno = termno;
    }

    public String getTermno() {
        return this.termno;
    }

    public void setTermsno(Integer termsno) {
        this.termsno = termsno;
    }

    public Integer getTermsno() {
        return this.termsno;
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

    public void setAddamt(Double addamt) {
        this.addamt = addamt;
    }

    public Double getAddamt() {
        return this.addamt;
    }

    public void setManagefee(Double managefee) {
        this.managefee = managefee;
    }

    public Double getManagefee() {
        return this.managefee;
    }

    public void setShopid(Integer shopid) {
        this.shopid = shopid;
    }

    public Integer getShopid() {
        return this.shopid;
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

    public void setStatus(Integer status) {
        this.status = status;
    }

    public Integer getStatus() {
        return this.status;
    }

    public void setRemark(String remark) {
        this.remark = remark;
    }

    public String getRemark() {
        return this.remark;
    }
}