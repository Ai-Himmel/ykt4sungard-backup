package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;
import com.sungard.smartcard.annotation.TransfersNodeIn;
import com.sungard.smartcard.annotation.TransfersNodeOut;
import com.sungard.smartcard.annotation.TransfersNodeType;

import java.io.Serializable;

/**
 * T_CFGFEE的实体类
 * 交易收费配置表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Cfgfee implements Serializable {

    /**
     * 客户的收费类别
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol5, desc = "客户的收费类别")
    @TransfersNodeOut(value = TransfersNodeType.lvol5, desc = "客户的收费类别")
    private Integer feetype;
    /**
     * 交易码
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol0, desc = "交易码")
    @TransfersNodeOut(value = TransfersNodeType.lvol0, desc = "交易码")
    private Integer transcode;
    /**
     * 卡类型
     */
    @TransfersNodeIn(value = TransfersNodeType.lsafe_level, desc = "卡类型")
    @TransfersNodeOut(value = TransfersNodeType.lsafe_level, desc = "卡类型")
    private Integer cardtype;
    /**
     * 交易类型
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol1, desc = "交易类型")
    @TransfersNodeOut(value = TransfersNodeType.lvol1, desc = "交易类型")
    private Integer transtype;
    /**
     * 费率类型:1固定值- 2-百分比3-以输入值作为收费金额
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol2, desc = "费率类型")
    @TransfersNodeOut(value = TransfersNodeType.lvol2, desc = "费率类型")
    private Integer ratetype;
    /**
     * 费率
     */
    @TransfersNodeIn(value = TransfersNodeType.damt0, desc = "费率")
    @TransfersNodeOut(value = TransfersNodeType.damt0, desc = "费率")
    private Double rateamt;
    /**
     * 备注
     */
    @TransfersNodeOut(value = TransfersNodeType.ssectypes, desc = "费率")
    private String remark;

    public void setFeetype(Integer feetype) {
        this.feetype = feetype;
    }

    public Integer getFeetype() {
        return this.feetype;
    }

    public void setTranscode(Integer transcode) {
        this.transcode = transcode;
    }

    public Integer getTranscode() {
        return this.transcode;
    }

    public void setCardtype(Integer cardtype) {
        this.cardtype = cardtype;
    }

    public Integer getCardtype() {
        return this.cardtype;
    }

    public void setTranstype(Integer transtype) {
        this.transtype = transtype;
    }

    public Integer getTranstype() {
        return this.transtype;
    }

    public void setRatetype(Integer ratetype) {
        this.ratetype = ratetype;
    }

    public Integer getRatetype() {
        return this.ratetype;
    }

    public void setRateamt(Double rateamt) {
        this.rateamt = rateamt;
    }

    public Double getRateamt() {
        return this.rateamt;
    }

    public void setRemark(String remark) {
        this.remark = remark;
    }

    public String getRemark() {
        return this.remark;
    }
}