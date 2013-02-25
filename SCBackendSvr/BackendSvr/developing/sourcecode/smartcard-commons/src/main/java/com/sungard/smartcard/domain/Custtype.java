package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_CUSTTYPE的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Custtype implements Serializable {

    /**
     * 客户类型
     */
    private Integer custtype;
    /**
     * 客户类型名称
     */
    private String custtypename;
    /**
     * 默认收费类别
     */
    private Integer feetype;
    /**
     * 学校代码
     */
    private String areacode;
    /**
     * 原客户类别
     */
    private String oldcusttype;
    /**
     * 使用标志
     */
    private String useflag;

    public void setCusttype(Integer custtype) {
        this.custtype = custtype;
    }

    public Integer getCusttype() {
        return this.custtype;
    }

    public void setCusttypename(String custtypename) {
        this.custtypename = custtypename;
    }

    public String getCusttypename() {
        return this.custtypename;
    }

    public void setFeetype(Integer feetype) {
        this.feetype = feetype;
    }

    public Integer getFeetype() {
        return this.feetype;
    }

    public void setAreacode(String areacode) {
        this.areacode = areacode;
    }

    public String getAreacode() {
        return this.areacode;
    }

    public void setOldcusttype(String oldcusttype) {
        this.oldcusttype = oldcusttype;
    }

    public String getOldcusttype() {
        return this.oldcusttype;
    }

    public void setUseflag(String useflag) {
        this.useflag = useflag;
    }

    public String getUseflag() {
        return this.useflag;
    }
}