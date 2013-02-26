package com.sungard.bean;

/**
 * 办证大厅收费记录
 * User: Yiming.You
 * Date: 2011-9-22
 */
public class Payrecord {
    private Integer cardno;
    private String stuempno;
    private String custname;
    private Double medicineFee;
    private Double dressingFee;
    private Double injectionFee;
    private Double vaccineFee;
    private Double otherFee;
    private Double totalFee;
    private String operator;
    private String transDate;
    private String transTime;
    private String refno;
    private String mac;
    private String transType;
    private String className;

    public Payrecord() {
    }

    public Integer getCardno() {
        return cardno;
    }

    public void setCardno(Integer cardno) {
        this.cardno = cardno;
    }

    public String getStuempno() {
        return stuempno;
    }

    public void setStuempno(String stuempno) {
        this.stuempno = stuempno;
    }

    public String getCustname() {
        return custname;
    }

    public void setCustname(String custname) {
        this.custname = custname;
    }

    public Double getMedicineFee() {
        return medicineFee;
    }

    public void setMedicineFee(Double medicineFee) {
        this.medicineFee = medicineFee;
    }

    public Double getDressingFee() {
        return dressingFee;
    }

    public void setDressingFee(Double dressingFee) {
        this.dressingFee = dressingFee;
    }

    public Double getInjectionFee() {
        return injectionFee;
    }

    public void setInjectionFee(Double injectionFee) {
        this.injectionFee = injectionFee;
    }

    public Double getVaccineFee() {
        return vaccineFee;
    }

    public void setVaccineFee(Double vaccineFee) {
        this.vaccineFee = vaccineFee;
    }

    public Double getOtherFee() {
        return otherFee;
    }

    public void setOtherFee(Double otherFee) {
        this.otherFee = otherFee;
    }

    public Double getTotalFee() {
        return totalFee;
    }

    public void setTotalFee(Double totalFee) {
        this.totalFee = totalFee;
    }

    public String getOperator() {
        return operator;
    }

    public void setOperator(String operator) {
        this.operator = operator;
    }

    public String getTransDate() {
        return transDate;
    }

    public void setTransDate(String transDate) {
        this.transDate = transDate;
    }

    public String getTransTime() {
        return transTime;
    }

    public void setTransTime(String transTime) {
        this.transTime = transTime;
    }

    public String getRefno() {
        return refno;
    }

    public void setRefno(String refno) {
        this.refno = refno;
    }

    public String getMac() {
        return mac;
    }

    public void setMac(String mac) {
        this.mac = mac;
    }

    public String getTransType() {
        return transType;
    }

    public void setTransType(String transType) {
        this.transType = transType;
    }

    public String getClassName() {
        return className;
    }

    public void setClassName(String className) {
        this.className = className;
    }
}
