package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_SYSPARA的实体类
 * 系统参数表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Syspara implements Serializable {

    /**
     *
     */
    private Integer paraid;
    /**
     *
     */
    private String paraval;
    /**
     *
     */
    private String paraname;
    /**
     *
     */
    private String paraunit;
    /**
     *
     */
    private String displayflag;
    /**
     *
     */
    private String remark;
    /**
     *
     */
    private String lastsaved;

    public void setParaid(Integer paraid) {
        this.paraid = paraid;
    }

    public Integer getParaid() {
        return this.paraid;
    }

    public void setParaval(String paraval) {
        this.paraval = paraval;
    }

    public String getParaval() {
        return this.paraval;
    }

    public void setParaname(String paraname) {
        this.paraname = paraname;
    }

    public String getParaname() {
        return this.paraname;
    }

    public void setParaunit(String paraunit) {
        this.paraunit = paraunit;
    }

    public String getParaunit() {
        return this.paraunit;
    }

    public void setDisplayflag(String displayflag) {
        this.displayflag = displayflag;
    }

    public String getDisplayflag() {
        return this.displayflag;
    }

    public void setRemark(String remark) {
        this.remark = remark;
    }

    public String getRemark() {
        return this.remark;
    }

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }
}