package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_RPTOPERLEDGER的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Rptoperledger implements Serializable {

    /**
     * 业务日期
     */
    private String accdate;
    /**
     * 操作员号
     */
    private String opercode;
    /**
     * 科目号
     */
    private String subjno;
    /**
     * 账号
     */
    private String accno;
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
     * 借方发生额
     */
    private Double dramt;
    /**
     * 贷方发生额
     */
    private Double cramt;

    public void setAccdate(String accdate) {
        this.accdate = accdate;
    }

    public String getAccdate() {
        return this.accdate;
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

    public void setAccno(String accno) {
        this.accno = accno;
    }

    public String getAccno() {
        return this.accno;
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
}