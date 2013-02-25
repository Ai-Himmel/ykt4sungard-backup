package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;
import com.sungard.smartcard.annotation.TransfersNodeIn;
import com.sungard.smartcard.annotation.TransfersNodeOut;
import com.sungard.smartcard.annotation.TransfersNodeType;

import java.io.Serializable;

/**
 * T_CARDTYPERIGHT的实体类
 * 卡类型权限表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Cardtyperight implements Serializable {

    /**
     * 卡类型
     */
    @TransfersNodeIn(value = TransfersNodeType.lsafe_level, desc = "")
    @TransfersNodeOut(value = TransfersNodeType.lsafe_level, desc = "")
    private Integer cardtype;
    /**
     * 收费类别
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol5, desc = "")
    @TransfersNodeOut(value = TransfersNodeType.lvol5, desc = "")
    private Integer feetype;
    /**
     * 操作员号
     */
    @TransfersNodeIn(value = TransfersNodeType.semp_no, desc = "")
    @TransfersNodeOut(value = TransfersNodeType.semp_no, desc = "")
    private String opercode;
    /**
     * 最后保存时间
     */
    @TransfersNodeIn(value = TransfersNodeType.scust_limit2, desc = "")
    @TransfersNodeOut(value = TransfersNodeType.scust_limit2, desc = "")
    private String lastsaved;

    public void setCardtype(Integer cardtype) {
        this.cardtype = cardtype;
    }

    public Integer getCardtype() {
        return this.cardtype;
    }

    public void setFeetype(Integer feetype) {
        this.feetype = feetype;
    }

    public Integer getFeetype() {
        return this.feetype;
    }

    public void setOpercode(String opercode) {
        this.opercode = opercode;
    }

    public String getOpercode() {
        return this.opercode;
    }

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }
}