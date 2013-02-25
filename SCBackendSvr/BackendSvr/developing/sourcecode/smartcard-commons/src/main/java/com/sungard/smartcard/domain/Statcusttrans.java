package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;


/**
 * T_STATCUSTTRANS的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Statcusttrans implements Serializable {

    /**
     * 结算日期
     */
    private Integer settledate;
    /**
     * 客户号
     */
    private Integer custid;
    /**
     * 交易日期
     */
    private Integer transdate;
    /**
     * 刷卡次数
     */
    private Integer transcnt;
    /**
     * 刷卡金额
     */
    private Double transamt;

    public void setSettledate(Integer settledate) {
        this.settledate = settledate;
    }

    public Integer getSettledate() {
        return this.settledate;
    }

    public void setCustid(Integer custid) {
        this.custid = custid;
    }

    public Integer getCustid() {
        return this.custid;
    }

    public void setTransdate(Integer transdate) {
        this.transdate = transdate;
    }

    public Integer getTransdate() {
        return this.transdate;
    }

    public void setTranscnt(Integer transcnt) {
        this.transcnt = transcnt;
    }

    public Integer getTranscnt() {
        return this.transcnt;
    }

    public void setTransamt(Double transamt) {
        this.transamt = transamt;
    }

    public Double getTransamt() {
        return this.transamt;
    }
}