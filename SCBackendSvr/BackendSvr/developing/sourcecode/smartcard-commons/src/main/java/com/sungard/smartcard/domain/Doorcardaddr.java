package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_DOORCARDADDR的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Doorcardaddr implements Serializable {

    /**
     *
     */
    private Integer cardaddr;
    /**
     * 交易卡号
     */
    private Integer cardno;
    /**
     *
     */
    private String useflag;
    /**
     *
     */
    private Integer listid;
    /**
     *
     */
    private Integer ctrlid;
    /**
     * 增删标志
     */
    private Integer adddelflag;

    public void setCardaddr(Integer cardaddr) {
        this.cardaddr = cardaddr;
    }

    public Integer getCardaddr() {
        return this.cardaddr;
    }

    public void setCardno(Integer cardno) {
        this.cardno = cardno;
    }

    public Integer getCardno() {
        return this.cardno;
    }

    public void setUseflag(String useflag) {
        this.useflag = useflag;
    }

    public String getUseflag() {
        return this.useflag;
    }

    public void setListid(Integer listid) {
        this.listid = listid;
    }

    public Integer getListid() {
        return this.listid;
    }

    public void setCtrlid(Integer ctrlid) {
        this.ctrlid = ctrlid;
    }

    public Integer getCtrlid() {
        return this.ctrlid;
    }

    public void setAdddelflag(Integer adddelflag) {
        this.adddelflag = adddelflag;
    }

    public Integer getAdddelflag() {
        return this.adddelflag;
    }
}