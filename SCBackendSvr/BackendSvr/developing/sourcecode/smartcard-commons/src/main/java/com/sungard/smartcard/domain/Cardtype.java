package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;
import com.sungard.smartcard.annotation.TransfersNodeIn;
import com.sungard.smartcard.annotation.TransfersNodeOut;
import com.sungard.smartcard.annotation.TransfersNodeType;

import java.io.Serializable;

/**
 * T_CARDTYPE的实体类
 * 卡类型表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Cardtype implements Serializable {

    /**
     * 卡类型
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol0, desc = "卡类型")
    @TransfersNodeOut(value = TransfersNodeType.lvol0, desc = "卡类型")
    private Integer cardtype;
    /**
     * 卡类别名称
     */
    @TransfersNodeIn(value = TransfersNodeType.sname, desc = "卡类别名称")
    @TransfersNodeOut(value = TransfersNodeType.sname, desc = "卡类别名称")
    private String cardtypename;
    /**
     * 卡物理类型
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol3, desc = "卡物理类型")
    @TransfersNodeOut(value = TransfersNodeType.lvol3, desc = "卡物理类型")
    private Integer cardphytype;
    /**
     * 1-匿名0-记名
     */
    @TransfersNodeIn(value = TransfersNodeType.smarket_code2, desc = "匿名")
    @TransfersNodeOut(value = TransfersNodeType.smarket_code2, desc = "匿名")
    private String anonymflag;
    /**
     * 默认收费类别
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol5, desc = "默认收费类别")
    @TransfersNodeOut(value = TransfersNodeType.lvol5, desc = "默认收费类别")
    private Integer feetype;
    /**
     * 卡成本费
     */
    @TransfersNodeIn(value = TransfersNodeType.damt2, desc = "卡成本费")
    @TransfersNodeOut(value = TransfersNodeType.damt2, desc = "卡成本费")
    private Double cardcostfee;
    /**
     * 能否重用:0-不能1-能
     */
    @TransfersNodeIn(value = TransfersNodeType.sstatus1, desc = "能否重用")
    @TransfersNodeOut(value = TransfersNodeType.sstatus1, desc = "能否重用")
    private String reuseable;
    /**
     * 能否补办:0-不能1-能
     */
    @TransfersNodeIn(value = TransfersNodeType.sstatus2, desc = "能否补办")
    @TransfersNodeOut(value = TransfersNodeType.sstatus2, desc = "能否补办")
    private String renewable;
    /**
     * 能否回收:0-不能1-能
     */
    @TransfersNodeIn(value = TransfersNodeType.sstatus4, desc = "能否回收")
    @TransfersNodeOut(value = TransfersNodeType.sstatus4, desc = "能否回收")
    private String recycleable;
    /**
     * 多钱包标志
     */
    @TransfersNodeIn(value = TransfersNodeType.smain_flag, desc = "多钱包标志")
    @TransfersNodeOut(value = TransfersNodeType.smain_flag, desc = "多钱包标志")
    private String multipurse;
    /**
     * 有效期是否固定天数
     */

    @TransfersNodeIn(value = TransfersNodeType.sstatus3, desc = "有效期是否固定天数")
    @TransfersNodeOut(value = TransfersNodeType.sstatus3, desc = "有效期是否固定天数")
    private String fixdayflag;
    /**
     * 有效天数
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol2, desc = "有效天数")
    @TransfersNodeOut(value = TransfersNodeType.lvol2, desc = "有效天数")
    private Integer fixdaycnt;
    /**
     * 使用标志:0-未使用1已使用
     */
    @TransfersNodeIn(value = TransfersNodeType.smarket_code, desc = "使用标志")
    @TransfersNodeOut(value = TransfersNodeType.smarket_code, desc = "使用标志")
    private String useflag;
    /**
     * 用途
     */
    @TransfersNodeIn(value = TransfersNodeType.vsvarstr0, desc = "用途")
    @TransfersNodeOut(value = TransfersNodeType.vsvarstr0, desc = "用途")
    private String purpose;

    public void setCardtype(Integer cardtype) {
        this.cardtype = cardtype;
    }

    public Integer getCardtype() {
        return this.cardtype;
    }

    public void setCardtypename(String cardtypename) {
        this.cardtypename = cardtypename;
    }

    public String getCardtypename() {
        return this.cardtypename;
    }

    public void setCardphytype(Integer cardphytype) {
        this.cardphytype = cardphytype;
    }

    public Integer getCardphytype() {
        return this.cardphytype;
    }

    public void setAnonymflag(String anonymflag) {
        this.anonymflag = anonymflag;
    }

    public String getAnonymflag() {
        return this.anonymflag;
    }

    public void setFeetype(Integer feetype) {
        this.feetype = feetype;
    }

    public Integer getFeetype() {
        return this.feetype;
    }

    public void setCardcostfee(Double cardcostfee) {
        this.cardcostfee = cardcostfee;
    }

    public Double getCardcostfee() {
        return this.cardcostfee;
    }

    public void setReuseable(String reuseable) {
        this.reuseable = reuseable;
    }

    public String getReuseable() {
        return this.reuseable;
    }

    public void setRenewable(String renewable) {
        this.renewable = renewable;
    }

    public String getRenewable() {
        return this.renewable;
    }

    public void setRecycleable(String recycleable) {
        this.recycleable = recycleable;
    }

    public String getRecycleable() {
        return this.recycleable;
    }

    public void setMultipurse(String multipurse) {
        this.multipurse = multipurse;
    }

    public String getMultipurse() {
        return this.multipurse;
    }

    public void setFixdayflag(String fixdayflag) {
        this.fixdayflag = fixdayflag;
    }

    public String getFixdayflag() {
        return this.fixdayflag;
    }

    public void setFixdaycnt(Integer fixdaycnt) {
        this.fixdaycnt = fixdaycnt;
    }

    public Integer getFixdaycnt() {
        return this.fixdaycnt;
    }

    public void setUseflag(String useflag) {
        this.useflag = useflag;
    }

    public String getUseflag() {
        return this.useflag;
    }

    public void setPurpose(String purpose) {
        this.purpose = purpose;
    }

    public String getPurpose() {
        return this.purpose;
    }
}