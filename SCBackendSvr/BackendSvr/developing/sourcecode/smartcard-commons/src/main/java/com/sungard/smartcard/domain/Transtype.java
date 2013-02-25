package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_TRANSTYPE的实体类
 * 交易类型表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Transtype implements Serializable {

    /**
     * 交易类别
     */
    private Integer transtype;
    /**
     * 交易名称
     */
    private String transname;
    /**
     * 显示标志1-显示0-不显示
     */
    private String displayflag;
    /**
     * 使用标志
     */
    private String useflag;

    public void setTranstype(Integer transtype) {
        this.transtype = transtype;
    }

    public Integer getTranstype() {
        return this.transtype;
    }

    public void setTransname(String transname) {
        this.transname = transname;
    }

    public String getTransname() {
        return this.transname;
    }

    public void setDisplayflag(String displayflag) {
        this.displayflag = displayflag;
    }

    public String getDisplayflag() {
        return this.displayflag;
    }

    public void setUseflag(String useflag) {
        this.useflag = useflag;
    }

    public String getUseflag() {
        return this.useflag;
    }
}