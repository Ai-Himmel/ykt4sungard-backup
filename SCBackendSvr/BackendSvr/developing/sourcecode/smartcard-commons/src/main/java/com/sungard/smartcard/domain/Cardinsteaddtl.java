package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_CARDINSTEADDTL的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Cardinsteaddtl implements Serializable {

    /**
     * 业务日期
     */
    private String accdate;
    /**
     * 终端编号
     */
    private Integer termid;
    /**
     * 终端流水号
     */
    private Integer termseqno;
    /**
     * 原卡号
     */
    private Integer cardno;
    /**
     * 原卡类型
     */
    private Integer oldcardtype;
    /**
     * 原卡物理ID
     */
    private String oldcardphyid;
    /**
     * 原显示卡号
     */
    private String oldshowcardno;
    /**
     * 原卡交易次数
     */
    private Integer oldcardcnt;
    /**
     * 原卡余额
     */
    private Double oldcardbal;
    /**
     * 原卡补助批次号
     */
    private Integer oldsubsidyno;
    /**
     * 新卡物理ID
     */
    private String cardphyid;
    /**
     * 新卡显示卡号
     */
    private String showcardno;
    /**
     * 冲正标志
     */
    private String revflag;
    /**
     * 状态
     */
    private String status;

    public void setAccdate(String accdate) {
        this.accdate = accdate;
    }

    public String getAccdate() {
        return this.accdate;
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

    public void setCardno(Integer cardno) {
        this.cardno = cardno;
    }

    public Integer getCardno() {
        return this.cardno;
    }

    public void setOldcardtype(Integer oldcardtype) {
        this.oldcardtype = oldcardtype;
    }

    public Integer getOldcardtype() {
        return this.oldcardtype;
    }

    public void setOldcardphyid(String oldcardphyid) {
        this.oldcardphyid = oldcardphyid;
    }

    public String getOldcardphyid() {
        return this.oldcardphyid;
    }

    public void setOldshowcardno(String oldshowcardno) {
        this.oldshowcardno = oldshowcardno;
    }

    public String getOldshowcardno() {
        return this.oldshowcardno;
    }

    public void setOldcardcnt(Integer oldcardcnt) {
        this.oldcardcnt = oldcardcnt;
    }

    public Integer getOldcardcnt() {
        return this.oldcardcnt;
    }

    public void setOldcardbal(Double oldcardbal) {
        this.oldcardbal = oldcardbal;
    }

    public Double getOldcardbal() {
        return this.oldcardbal;
    }

    public void setOldsubsidyno(Integer oldsubsidyno) {
        this.oldsubsidyno = oldsubsidyno;
    }

    public Integer getOldsubsidyno() {
        return this.oldsubsidyno;
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

    public void setRevflag(String revflag) {
        this.revflag = revflag;
    }

    public String getRevflag() {
        return this.revflag;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getStatus() {
        return this.status;
    }
}