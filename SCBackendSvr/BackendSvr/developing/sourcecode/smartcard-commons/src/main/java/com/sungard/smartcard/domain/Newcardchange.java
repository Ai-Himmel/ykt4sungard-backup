package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_NEWCARDCHANGE的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Newcardchange implements Serializable {

    /**
     * 显示卡号
     */
    private String showcardno;
    /**
     * 学号
     */
    private String stuempno;
    /**
     * 卡有效期
     */
    private String expiredate;
    /**
     * 状态
     */
    private Integer status;
    /**
     * 批次号
     */
    private String batchno;
    /**
     * 顺序号
     */
    private Integer seqno;
    /**
     * 卡物理ID
     */
    private String cardphyid;
    /**
     * 旧卡物理ID
     */
    private String oldcardphyid;
    /**
     * 最后保存时间
     */
    private String lastsaved;

    public void setShowcardno(String showcardno) {
        this.showcardno = showcardno;
    }

    public String getShowcardno() {
        return this.showcardno;
    }

    public void setStuempno(String stuempno) {
        this.stuempno = stuempno;
    }

    public String getStuempno() {
        return this.stuempno;
    }

    public void setExpiredate(String expiredate) {
        this.expiredate = expiredate;
    }

    public String getExpiredate() {
        return this.expiredate;
    }

    public void setStatus(Integer status) {
        this.status = status;
    }

    public Integer getStatus() {
        return this.status;
    }

    public void setBatchno(String batchno) {
        this.batchno = batchno;
    }

    public String getBatchno() {
        return this.batchno;
    }

    public void setSeqno(Integer seqno) {
        this.seqno = seqno;
    }

    public Integer getSeqno() {
        return this.seqno;
    }

    public void setCardphyid(String cardphyid) {
        this.cardphyid = cardphyid;
    }

    public String getCardphyid() {
        return this.cardphyid;
    }

    public void setOldcardphyid(String oldcardphyid) {
        this.oldcardphyid = oldcardphyid;
    }

    public String getOldcardphyid() {
        return this.oldcardphyid;
    }

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }
}