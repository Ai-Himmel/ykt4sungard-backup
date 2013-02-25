package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;


/**
 * T_STATTERMTIME的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Stattermtime implements Serializable {

    /**
     * 结算日期
     */
    private Integer settledate;
    /**
     * 终端编号
     */
    private Integer termid;
    /**
     * 交易日期
     */
    private Integer transdate;
    /**
     * 时间ID
     */
    private Integer timeid;
    /**
     * 收费次数
     */
    private Integer feecnt;
    /**
     * 记次次数
     */
    private Integer freecnt;
    /**
     * 总次数
     */
    private Integer totalcnt;
    /**
     * 总金额
     */
    private Double totalamt;

    public void setSettledate(Integer settledate) {
        this.settledate = settledate;
    }

    public Integer getSettledate() {
        return this.settledate;
    }

    public void setTermid(Integer termid) {
        this.termid = termid;
    }

    public Integer getTermid() {
        return this.termid;
    }

    public void setTransdate(Integer transdate) {
        this.transdate = transdate;
    }

    public Integer getTransdate() {
        return this.transdate;
    }

    public void setTimeid(Integer timeid) {
        this.timeid = timeid;
    }

    public Integer getTimeid() {
        return this.timeid;
    }

    public void setFeecnt(Integer feecnt) {
        this.feecnt = feecnt;
    }

    public Integer getFeecnt() {
        return this.feecnt;
    }

    public void setFreecnt(Integer freecnt) {
        this.freecnt = freecnt;
    }

    public Integer getFreecnt() {
        return this.freecnt;
    }

    public void setTotalcnt(Integer totalcnt) {
        this.totalcnt = totalcnt;
    }

    public Integer getTotalcnt() {
        return this.totalcnt;
    }

    public void setTotalamt(Double totalamt) {
        this.totalamt = totalamt;
    }

    public Double getTotalamt() {
        return this.totalamt;
    }
}