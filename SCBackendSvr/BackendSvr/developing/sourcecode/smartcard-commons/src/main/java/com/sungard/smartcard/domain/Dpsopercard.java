package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_DPSOPERCARD的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-23
 */
@TransfersElement
public class Dpsopercard implements Serializable {

    /**
     * 操作员号
     */
    private String opercode;
    /**
     * 卡号
     */
    private Integer cardno;
    /**
     * 0-正常1-禁用
     */
    private Integer disableflag;
    /**
     * 绑定操作员
     */
    private String openoper;
    /**
     * 最后保存时间
     */
    private String lastsaved;

    public void setOpercode(String opercode) {
        this.opercode = opercode;
    }

    public String getOpercode() {
        return this.opercode;
    }

    public void setCardno(Integer cardno) {
        this.cardno = cardno;
    }

    public Integer getCardno() {
        return this.cardno;
    }

    public void setDisableflag(Integer disableflag) {
        this.disableflag = disableflag;
    }

    public Integer getDisableflag() {
        return this.disableflag;
    }

    public void setOpenoper(String openoper) {
        this.openoper = openoper;
    }

    public String getOpenoper() {
        return this.openoper;
    }

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }
}