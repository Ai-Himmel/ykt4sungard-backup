package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_RPTSHOPMEAL的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Rptshopmeal implements Serializable {

    /**
     * 记账日期
     */
    private String accdate;
    /**
     * 商户账号
     */
    private String accno;
    /**
     * 早餐交易次数
     */
    private Integer transcnt1;
    /**
     * 早餐金额
     */
    private Double transamt1;
    /**
     * 午餐交易次数
     */
    private Integer transcnt2;
    /**
     * 午餐金额
     */
    private Double transamt2;
    /**
     * 晚餐交易次数
     */
    private Integer transcnt3;
    /**
     * 晚餐金额
     */
    private Double transamt3;
    /**
     * 夜餐交易次数
     */
    private Integer transcnt4;
    /**
     * 夜餐金额
     */
    private Double transamt4;

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

    public void setTranscnt1(Integer transcnt1) {
        this.transcnt1 = transcnt1;
    }

    public Integer getTranscnt1() {
        return this.transcnt1;
    }

    public void setTransamt1(Double transamt1) {
        this.transamt1 = transamt1;
    }

    public Double getTransamt1() {
        return this.transamt1;
    }

    public void setTranscnt2(Integer transcnt2) {
        this.transcnt2 = transcnt2;
    }

    public Integer getTranscnt2() {
        return this.transcnt2;
    }

    public void setTransamt2(Double transamt2) {
        this.transamt2 = transamt2;
    }

    public Double getTransamt2() {
        return this.transamt2;
    }

    public void setTranscnt3(Integer transcnt3) {
        this.transcnt3 = transcnt3;
    }

    public Integer getTranscnt3() {
        return this.transcnt3;
    }

    public void setTransamt3(Double transamt3) {
        this.transamt3 = transamt3;
    }

    public Double getTransamt3() {
        return this.transamt3;
    }

    public void setTranscnt4(Integer transcnt4) {
        this.transcnt4 = transcnt4;
    }

    public Integer getTranscnt4() {
        return this.transcnt4;
    }

    public void setTransamt4(Double transamt4) {
        this.transamt4 = transamt4;
    }

    public Double getTransamt4() {
        return this.transamt4;
    }
}