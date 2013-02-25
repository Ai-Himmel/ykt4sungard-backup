package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_CFGTRANS的实体类
 * 交易配置表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Cfgtrans implements Serializable {

    /**
     * 客户的收费类别
     */
    private Integer feetype;
    /**
     * 交易码
     */
    private Integer transcode;
    /**
     * 交易类型
     */
    private Integer transtype;
    /**
     * 费率类型:1定额- 2-百分比3-以输入金额为准
     */
    private Integer ratetype;
    /**
     * 费率
     */
    private Double rateamt;
    /**
     * 备注
     */
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