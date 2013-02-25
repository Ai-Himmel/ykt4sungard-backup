package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_RPTSYSSTAT的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Rptsysstat implements Serializable {

    /**
     * 结算日期
     */
    private String accdate;
    /**
     * 统计项目编号
     */
    private Integer itemid;
    /**
     * 统计项目名称
     */
    private String itemname;
    /**
     * 统计数据
     */
    private String itemval;

    public void setAccdate(String accdate) {
        this.accdate = accdate;
    }

    public String getAccdate() {
        return this.accdate;
    }

    public void setItemid(Integer itemid) {
        this.itemid = itemid;
    }

    public Integer getItemid() {
        return this.itemid;
    }

    public void setItemname(String itemname) {
        this.itemname = itemname;
    }

    public String getItemname() {
        return this.itemname;
    }

    public void setItemval(String itemval) {
        this.itemval = itemval;
    }

    public String getItemval() {
        return this.itemval;
    }
}