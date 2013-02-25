package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_MEALTYPE的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Mealtype implements Serializable {

    /**
     * 餐次ID
     */
    private Integer mealtype;
    /**
     * 餐次名称
     */
    private String mealname;
    /**
     * 结束时间
     */
    private String endtime;
    /**
     * 更新时间
     */
    private String lastsaved;

    public void setMealtype(Integer mealtype) {
        this.mealtype = mealtype;
    }

    public Integer getMealtype() {
        return this.mealtype;
    }

    public void setMealname(String mealname) {
        this.mealname = mealname;
    }

    public String getMealname() {
        return this.mealname;
    }

    public void setEndtime(String endtime) {
        this.endtime = endtime;
    }

    public String getEndtime() {
        return this.endtime;
    }

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }
}