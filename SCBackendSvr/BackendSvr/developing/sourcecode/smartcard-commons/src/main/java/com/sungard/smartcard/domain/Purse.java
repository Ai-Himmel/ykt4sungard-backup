package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;
import com.sungard.smartcard.annotation.TransfersNodeIn;
import com.sungard.smartcard.annotation.TransfersNodeOut;
import com.sungard.smartcard.annotation.TransfersNodeType;

import java.io.Serializable;

/**
 * T_PURSE的实体类
 * 钱包表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Purse implements Serializable {

    /**
     * 钱包号
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol1, desc = "钱包号")
    @TransfersNodeOut(value = TransfersNodeType.lvol1, desc = "钱包号")
    private Integer purseno;
    /**
     * 钱包名
     */
    @TransfersNodeIn(value = TransfersNodeType.saddr, desc = "钱包名")
    @TransfersNodeOut(value = TransfersNodeType.saddr, desc = "钱包名")
    private String pursename;
    /**
     * 最大存款金额
     */
    @TransfersNodeIn(value = TransfersNodeType.damt1, desc = "最大存款金额")
    @TransfersNodeOut(value = TransfersNodeType.damt1, desc = "最大存款金额")
    private Integer cardmaxbal;
    /**
     * 使用标志0-未使用1-已使用
     */
    @TransfersNodeIn(value = TransfersNodeType.sstatus1, desc = "使用标志")
    @TransfersNodeOut(value = TransfersNodeType.sstatus1, desc = "使用标志")
    private String useflag;

    public void setPurseno(Integer purseno) {
        this.purseno = purseno;
    }

    public Integer getPurseno() {
        return this.purseno;
    }

    public void setPursename(String pursename) {
        this.pursename = pursename;
    }

    public String getPursename() {
        return this.pursename;
    }

    public Integer getCardmaxbal() {
        return cardmaxbal;
    }

    public void setCardmaxbal(Integer cardmaxbal) {
        this.cardmaxbal = cardmaxbal;
    }

    public void setUseflag(String useflag) {
        this.useflag = useflag;
    }

    public String getUseflag() {
        return this.useflag;
    }
}