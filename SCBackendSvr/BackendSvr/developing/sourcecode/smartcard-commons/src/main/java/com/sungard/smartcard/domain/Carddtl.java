package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_CARDDTL的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Carddtl implements Serializable {

    /**
     * 业务日期
     */
    private String accdate;
    /**
     * 记账时间
     */
    private String acctime;
    /**
     * 终点编号
     */
    private Integer termid;
    /**
     * 终端流水号
     */
    private Integer termseqno;
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
     * 卡使用类型
     */
    private Integer usetype;
    /**
     * 摘要
     */
    private String summary;
    /**
     * 1-收入2-支出
     */
    private Integer inoutflag;
    /**
     * 交易数量
     */
    private Integer transcnt;
    /**
     * 物理卡号
     */
    private String cardphyid;
    /**
     * 显示卡号
     */
    private String showcardno;

    public void setAccdate(String accdate) {
        this.accdate = accdate;
    }

    public String getAccdate() {
        return this.accdate;
    }

    public void setAcctime(String acctime) {
        this.acctime = acctime;
    }

    public String getAcctime() {
        return this.acctime;
    }

    public void setTermid(Integer termid) {
        this.termid = termid;
    }

    public Integer getTermid() {
        return this.termid;
    }

    public void setTermseqno(Integer termseqno) {
        this.termseqno = termseqno;
    }

    public Integer getTermseqno() {
        return this.termseqno;
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

    public void setInoutflag(Integer inoutflag) {
        this.inoutflag = inoutflag;
    }

    public Integer getInoutflag() {
        return this.inoutflag;
    }

    public void setTranscnt(Integer transcnt) {
        this.transcnt = transcnt;
    }

    public Integer getTranscnt() {
        return this.transcnt;
    }

    public void setCardphyid(String cardphyid) {
        this.cardphyid = cardphyid;
    }

    public String getCardphyid() {
        return this.cardphyid;
    }

    public void setShowcardno(String showcardno) {
        this.showcardno = showcardno;
    }

    public String getShowcardno() {
        return this.showcardno;
    }
}