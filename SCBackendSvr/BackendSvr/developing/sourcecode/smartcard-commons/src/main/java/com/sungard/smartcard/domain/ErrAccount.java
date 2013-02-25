package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_ERR_ACCOUNT的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class ErrAccount implements Serializable {

    /**
     *
     */
    private Integer cardno;
    /**
     *
     */
    private Integer totalnum;
    /**
     *
     */
    private String lostcntdetail;

    public void setCardno(Integer cardno) {
        this.cardno = cardno;
    }

    public Integer getCardno() {
        return this.cardno;
    }

    public void setTotalnum(Integer totalnum) {
        this.totalnum = totalnum;
    }

    public Integer getTotalnum() {
        return this.totalnum;
    }

    public void setLostcntdetail(String lostcntdetail) {
        this.lostcntdetail = lostcntdetail;
    }

    public String getLostcntdetail() {
        return this.lostcntdetail;
    }
}