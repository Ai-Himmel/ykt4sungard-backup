package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_CARDPHYTYPE的实体类
 * 卡物理类型表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Cardphytype implements Serializable {

    /**
     * 卡物理类型
     */
    private Integer cardphytype;
    /**
     * 卡类别名称
     */
    private String cardphytypename;
    /**
     * 是否启用
     */
    private String useflag;
    /**
     * 卡物理类型编码
     */
    private Integer cardphytypecode;

    public void setCardphytype(Integer cardphytype) {
        this.cardphytype = cardphytype;
    }

    public Integer getCardphytype() {
        return this.cardphytype;
    }

    public void setCardphytypename(String cardphytypename) {
        this.cardphytypename = cardphytypename;
    }

    public String getCardphytypename() {
        return this.cardphytypename;
    }

    public void setUseflag(String useflag) {
        this.useflag = useflag;
    }

    public String getUseflag() {
        return this.useflag;
    }

    public void setCardphytypecode(Integer cardphytypecode) {
        this.cardphytypecode = cardphytypecode;
    }

    public Integer getCardphytypecode() {
        return this.cardphytypecode;
    }
}