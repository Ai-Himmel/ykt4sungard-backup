package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_SEQNOCTL的实体类
 * 流水号控制表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Seqnoctl implements Serializable {

    /**
     * 终端编号
     */
    private Integer termid;
    /**
     * 终端流水号
     */
    private Integer termseqno;
    /**
     * 记账日期
     */
    private Integer accdate;

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

    public void setAccdate(Integer accdate) {
        this.accdate = accdate;
    }

    public Integer getAccdate() {
        return this.accdate;
    }
}