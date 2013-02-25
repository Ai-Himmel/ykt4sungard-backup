package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;


/**
 * T_SYSKEY的实体类
 * 系统键值表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Syskey implements Serializable {

    /**
     *
     */
    private String keycode;
    /**
     *
     */
    private String keyname;
    /**
     *
     */
    private Double keyval;
    /**
     *
     */
    private Integer maxval;
    /**
     *
     */
    private String keytype;

    public void setKeycode(String keycode) {
        this.keycode = keycode;
    }

    public String getKeycode() {
        return this.keycode;
    }

    public void setKeyname(String keyname) {
        this.keyname = keyname;
    }

    public String getKeyname() {
        return this.keyname;
    }

    public void setKeyval(Double keyval) {
        this.keyval = keyval;
    }

    public Double getKeyval() {
        return this.keyval;
    }

    public void setMaxval(Integer maxval) {
        this.maxval = maxval;
    }

    public Integer getMaxval() {
        return this.maxval;
    }

    public void setKeytype(String keytype) {
        this.keytype = keytype;
    }

    public String getKeytype() {
        return this.keytype;
    }
}