package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_PAYPARA的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Paypara implements Serializable {

    /**
     * 支付参数名称
     */
    private String paraname;
    /**
     * 支付代码
     */
    private Integer paycode;
    /**
     * 支付参数值
     */
    private String paraval;
    /**
     * 备注
     */
    private String remark;

    public void setParaname(String paraname) {
        this.paraname = paraname;
    }

    public String getParaname() {
        return this.paraname;
    }

    public void setPaycode(Integer paycode) {
        this.paycode = paycode;
    }

    public Integer getPaycode() {
        return this.paycode;
    }

    public void setParaval(String paraval) {
        this.paraval = paraval;
    }

    public String getParaval() {
        return this.paraval;
    }

    public void setRemark(String remark) {
        this.remark = remark;
    }

    public String getRemark() {
        return this.remark;
    }
}