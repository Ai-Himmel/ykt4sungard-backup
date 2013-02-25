package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_RPTOPERCASH的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Rptopercash implements Serializable {

    /**
     * 业务日期
     */
    private String accdate;
    /**
     * 网点号
     */
    private Integer branchno;
    /**
     * 操作员号
     */
    private String opercode;
    /**
     * 科目号
     */
    private String subjno;
    /**
     * 卡类型
     */
    private Integer transtype;
    /**
     * 摘要
     */
    private String summary;
    /**
     * 交易次数
     */
    private Integer transcnt;
    /**
     * 收入发生额
     */
    private Double inamt;
    /**
     * 支出发生额
     */
    private Double outamt;
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

    public void setBranchno(Integer branchno) {
        this.branchno = branchno;
    }

    public Integer getBranchno() {
        return this.branchno;
    }

    public void setOpercode(String opercode) {
        this.opercode = opercode;
    }

    public String getOpercode() {
        return this.opercode;
    }

    public void setSubjno(String subjno) {
        this.subjno = subjno;
    }

    public String getSubjno() {
        return this.subjno;
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

    public void setTranscnt(Integer transcnt) {
        this.transcnt = transcnt;
    }

    public Integer getTranscnt() {
        return this.transcnt;
    }

    public void setInamt(Double inamt) {
        this.inamt = inamt;
    }

    public Double getInamt() {
        return this.inamt;
    }

    public void setOutamt(Double outamt) {
        this.outamt = outamt;
    }

    public Double getOutamt() {
        return this.outamt;
    }

    public void setAmount(Double amount) {
        this.amount = amount;
    }

    public Double getAmount() {
        return this.amount;
    }
}