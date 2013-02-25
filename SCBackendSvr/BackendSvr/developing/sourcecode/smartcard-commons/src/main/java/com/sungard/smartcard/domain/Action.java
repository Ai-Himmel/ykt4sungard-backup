package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_ACTION的实体类
 * 权限操作表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Action implements Serializable {

    /**
     * 操作名称
     */
    private String name;
    /**
     * 权限值
     */
    private Integer actionValue;
    /**
     * 备注
     */
    private String remark;

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return this.name;
    }

    public void setActionValue(Integer actionValue) {
        this.actionValue = actionValue;
    }

    public Integer getActionValue() {
        return this.actionValue;
    }

    public void setRemark(String remark) {
        this.remark = remark;
    }

    public String getRemark() {
        return this.remark;
    }
}