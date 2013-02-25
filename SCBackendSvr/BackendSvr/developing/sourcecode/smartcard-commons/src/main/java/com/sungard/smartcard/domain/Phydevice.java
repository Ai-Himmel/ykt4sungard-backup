package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_PHYDEVICE的实体类
 * 设备厂商类型表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Phydevice implements Serializable {

    /**
     *
     */
    private Integer phytype;
    /**
     *
     */
    private String dname;
    /**
     *
     */
    private String dtype;
    /**
     *
     */
    private String factory;
    /**
     *
     */
    private String remark;

    public void setPhytype(Integer phytype) {
        this.phytype = phytype;
    }

    public Integer getPhytype() {
        return this.phytype;
    }

    public void setDname(String dname) {
        this.dname = dname;
    }

    public String getDname() {
        return this.dname;
    }

    public void setDtype(String dtype) {
        this.dtype = dtype;
    }

    public String getDtype() {
        return this.dtype;
    }

    public void setFactory(String factory) {
        this.factory = factory;
    }

    public String getFactory() {
        return this.factory;
    }

    public void setRemark(String remark) {
        this.remark = remark;
    }

    public String getRemark() {
        return this.remark;
    }
}