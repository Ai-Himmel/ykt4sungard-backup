package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_CFGRAKEOFF的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Cfgrakeoff implements Serializable {

    /**
     * 商户号
     */
    private Integer shopid;
    /**
     * 商户金额
     */
    private Double amount;
    /**
     * 折扣返回率
     */
    private Long agio;
    /**
     * 备注
     */
    private String remark;

    public void setShopid(Integer shopid) {
        this.shopid = shopid;
    }

    public Integer getShopid() {
        return this.shopid;
    }

    public void setAmount(Double amount) {
        this.amount = amount;
    }

    public Double getAmount() {
        return this.amount;
    }

    public void setAgio(Long agio) {
        this.agio = agio;
    }

    public Long getAgio() {
        return this.agio;
    }

    public void setRemark(String remark) {
        this.remark = remark;
    }

    public String getRemark() {
        return this.remark;
    }
}