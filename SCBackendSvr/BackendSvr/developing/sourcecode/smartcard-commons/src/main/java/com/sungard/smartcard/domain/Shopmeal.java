package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_SHOPMEAL的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Shopmeal implements Serializable {

    /**
     * 商户号
     */
    private Integer shopid;
    /**
     * 商户账号
     */
    private String accno;
    /**
     * 早餐结束时间
     */
    private String endtime1;
    /**
     * 午餐结束时间
     */
    private String endtime2;
    /**
     * 晚餐结束时间
     */
    private String endtime3;
    /**
     * 夜餐结束时间
     */
    private String endtime4;
    /**
     * 操作员号
     */
    private String opercode;
    /**
     * 最后保存时间
     */
    private String lastsaved;

    public void setShopid(Integer shopid) {
        this.shopid = shopid;
    }

    public Integer getShopid() {
        return this.shopid;
    }

    public void setAccno(String accno) {
        this.accno = accno;
    }

    public String getAccno() {
        return this.accno;
    }

    public void setEndtime1(String endtime1) {
        this.endtime1 = endtime1;
    }

    public String getEndtime1() {
        return this.endtime1;
    }

    public void setEndtime2(String endtime2) {
        this.endtime2 = endtime2;
    }

    public String getEndtime2() {
        return this.endtime2;
    }

    public void setEndtime3(String endtime3) {
        this.endtime3 = endtime3;
    }

    public String getEndtime3() {
        return this.endtime3;
    }

    public void setEndtime4(String endtime4) {
        this.endtime4 = endtime4;
    }

    public String getEndtime4() {
        return this.endtime4;
    }

    public void setOpercode(String opercode) {
        this.opercode = opercode;
    }

    public String getOpercode() {
        return this.opercode;
    }

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }
}