package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_ERR_ACCOUNT_TMP的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class ErrAccountTmp implements Serializable {

    /**
     *
     */
    private Integer cardno;

    public void setCardno(Integer cardno) {
        this.cardno = cardno;
    }

    public Integer getCardno() {
        return this.cardno;
    }
}