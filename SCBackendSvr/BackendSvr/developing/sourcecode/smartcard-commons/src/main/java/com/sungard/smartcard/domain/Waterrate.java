package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;
import com.sungard.smartcard.annotation.TransfersNodeIn;
import com.sungard.smartcard.annotation.TransfersNodeOut;
import com.sungard.smartcard.annotation.TransfersNodeType;

import java.io.Serializable;

/**
 * T_WATERRATE的实体类
 * 脱机水价
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Waterrate implements Serializable {

    /**
     * 收费类别
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol0, desc = "收费类别")
    @TransfersNodeOut(value = TransfersNodeType.lvol0, desc = "收费类别")
    private Integer feetype;
    /**
     * 水价1
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol1, desc = "水价1")
    @TransfersNodeOut(value = TransfersNodeType.lvol1, desc = "水价1")
    private Integer rate1;
    /**
     * 水价2
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol2, desc = "水价2")
    @TransfersNodeOut(value = TransfersNodeType.lvol2, desc = "水价2")
    private Integer rate2;
    /**
     * 水价3
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol3, desc = "水价3")
    @TransfersNodeOut(value = TransfersNodeType.lvol3, desc = "水价3")
    private Integer rate3;
    /**
     * 保存时间
     */
    @TransfersNodeOut(value = TransfersNodeType.sholder_ac_no, desc = "保存时间(yyyyMMddhhmmss)")
    private String lastsaved;

    public void setFeetype(Integer feetype) {
        this.feetype = feetype;
    }

    public Integer getFeetype() {
        return this.feetype;
    }

    public void setRate1(Integer rate1) {
        this.rate1 = rate1;
    }

    public Integer getRate1() {
        return this.rate1;
    }

    public void setRate2(Integer rate2) {
        this.rate2 = rate2;
    }

    public Integer getRate2() {
        return this.rate2;
    }

    public void setRate3(Integer rate3) {
        this.rate3 = rate3;
    }

    public Integer getRate3() {
        return this.rate3;
    }

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }
}