package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_RPTSHOPBOARD的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Rptshopboard implements Serializable {

    /**
     * 记账日期
     */
    private String accdate;
    /**
     * 账号
     */
    private String accno;
    /**
     * 交易次数
     */
    private Integer transcnt;
    /**
     * 发生额
     */
    private Double transamt;

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