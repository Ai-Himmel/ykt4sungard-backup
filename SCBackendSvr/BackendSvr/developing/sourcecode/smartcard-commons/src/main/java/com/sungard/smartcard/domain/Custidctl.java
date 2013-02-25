package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_CUSTIDCTL的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Custidctl implements Serializable {

    /**
     * 区域代码
     */
    private String areacode;
    /**
     * 客户起始号
     */
    private Integer startno;
    /**
     * 客户当前号
     */
    private Integer nextno;
    /**
     * 客户结束号
     */
    private Integer endno;
    /**
     * 最后保存时间
     */
    private String lastsaved;

    public void setAreacode(String areacode) {
        this.areacode = areacode;
    }

    public String getAreacode() {
        return this.areacode;
    }

    public void setStartno(Integer startno) {
        this.startno = startno;
    }

    public Integer getStartno() {
        return this.startno;
    }

    public void setNextno(Integer nextno) {
        this.nextno = nextno;
    }

    public Integer getNextno() {
        return this.nextno;
    }

    public void setEndno(Integer endno) {
        this.endno = endno;
    }

    public Integer getEndno() {
        return this.endno;
    }

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }
}