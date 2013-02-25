package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_RPTOPERCARD的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Rptopercard implements Serializable {

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
     * 卡类型
     */
    private Integer cardtype;
    /**
     * 使用类型
     */
    private Integer usetype;
    /**
     * 摘要
     */
    private String summary;
    /**
     * 交易次数
     */
    private Integer transcnt;
    /**
     * 收入数量
     */
    private Integer incnt;
    /**
     * 支出数量
     */
    private Integer outcnt;
    /**
     * 库存数量
     */
    private Integer remaincnt;

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

    public void setCardtype(Integer cardtype) {
        this.cardtype = cardtype;
    }

    public Integer getCardtype() {
        return this.cardtype;
    }

    public void setUsetype(Integer usetype) {
        this.usetype = usetype;
    }

    public Integer getUsetype() {
        return this.usetype;
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

    public void setIncnt(Integer incnt) {
        this.incnt = incnt;
    }

    public Integer getIncnt() {
        return this.incnt;
    }

    public void setOutcnt(Integer outcnt) {
        this.outcnt = outcnt;
    }

    public Integer getOutcnt() {
        return this.outcnt;
    }

    public void setRemaincnt(Integer remaincnt) {
        this.remaincnt = remaincnt;
    }

    public Integer getRemaincnt() {
        return this.remaincnt;
    }
}