package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_RPTPOSLEDGER的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Rptposledger implements Serializable {

    /**
     * 记账日期
     */
    private String accdate;
    /**
     * 商户账号
     */
    private String accno;
    /**
     * 设备编号
     */
    private Integer deviceid;
    /**
     * 交易类型
     */
    private Integer transtype;
    /**
     * 摘要
     */
    private String summary;
    /**
     * 交易日期
     */
    private String transdate;
    /**
     * 交易次数
     */
    private Integer transcnt;
    /**
     * 借方发生额
     */
    private Double dramt;
    /**
     * 贷方发生额
     */
    private Double cramt;
    /**
     * 结存金额
     */
    private Double amount;

    public void setAccdate(String accdate) {
        this.accdate = accdate;
    }

    public String getAccdate() {
        return this.accdate;
    }

    public void setAccno(String accno) {
        this.accno = accno;
    }

    public String getAccno() {
        return this.accno;
    }

    public void setDeviceid(Integer deviceid) {
        this.deviceid = deviceid;
    }

    public Integer getDeviceid() {
        return this.deviceid;
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

    public void setTransdate(String transdate) {
        this.transdate = transdate;
    }

    public String getTransdate() {
        return this.transdate;
    }

    public void setTranscnt(Integer transcnt) {
        this.transcnt = transcnt;
    }

    public Integer getTranscnt() {
        return this.transcnt;
    }

    public void setDramt(Double dramt) {
        this.dramt = dramt;
    }

    public Double getDramt() {
        return this.dramt;
    }

    public void setCramt(Double cramt) {
        this.cramt = cramt;
    }

    public Double getCramt() {
        return this.cramt;
    }

    public void setAmount(Double amount) {
        this.amount = amount;
    }

    public Double getAmount() {
        return this.amount;
    }
}