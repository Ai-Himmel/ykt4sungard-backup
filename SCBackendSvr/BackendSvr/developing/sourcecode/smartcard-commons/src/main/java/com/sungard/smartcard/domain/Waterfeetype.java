package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_WATERFEETYPE的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Waterfeetype implements Serializable {

    /**
     * 费率ID
     */
    private Integer feeid;
    /**
     * 收费类别
     */
    private Integer feetype;
    /**
     * 费率数量
     */
    private Integer feecnt;
    /**
     * 计费开始时间1
     */
    private Integer starttime1;
    /**
     * 计费时间1
     */
    private Integer feetime1;
    /**
     * 计费金额1
     */
    private Integer feeamt1;
    /**
     * 计费开始时间2
     */
    private Integer starttime2;
    /**
     * 计费时间2
     */
    private Integer feetime2;
    /**
     * 计费金额2
     */
    private Integer feeamt2;
    /**
     * 计费开始时间3
     */
    private Integer starttime3;
    /**
     * 计费时间3
     */
    private Integer feetime3;
    /**
     * 计费金额3
     */
    private Integer feeamt3;

    public void setFeeid(Integer feeid) {
        this.feeid = feeid;
    }

    public Integer getFeeid() {
        return this.feeid;
    }

    public void setFeetype(Integer feetype) {
        this.feetype = feetype;
    }

    public Integer getFeetype() {
        return this.feetype;
    }

    public void setFeecnt(Integer feecnt) {
        this.feecnt = feecnt;
    }

    public Integer getFeecnt() {
        return this.feecnt;
    }

    public void setStarttime1(Integer starttime1) {
        this.starttime1 = starttime1;
    }

    public Integer getStarttime1() {
        return this.starttime1;
    }

    public void setFeetime1(Integer feetime1) {
        this.feetime1 = feetime1;
    }

    public Integer getFeetime1() {
        return this.feetime1;
    }

    public void setFeeamt1(Integer feeamt1) {
        this.feeamt1 = feeamt1;
    }

    public Integer getFeeamt1() {
        return this.feeamt1;
    }

    public void setStarttime2(Integer starttime2) {
        this.starttime2 = starttime2;
    }

    public Integer getStarttime2() {
        return this.starttime2;
    }

    public void setFeetime2(Integer feetime2) {
        this.feetime2 = feetime2;
    }

    public Integer getFeetime2() {
        return this.feetime2;
    }

    public void setFeeamt2(Integer feeamt2) {
        this.feeamt2 = feeamt2;
    }

    public Integer getFeeamt2() {
        return this.feeamt2;
    }

    public void setStarttime3(Integer starttime3) {
        this.starttime3 = starttime3;
    }

    public Integer getStarttime3() {
        return this.starttime3;
    }

    public void setFeetime3(Integer feetime3) {
        this.feetime3 = feetime3;
    }

    public Integer getFeetime3() {
        return this.feetime3;
    }

    public void setFeeamt3(Integer feeamt3) {
        this.feeamt3 = feeamt3;
    }

    public Integer getFeeamt3() {
        return this.feeamt3;
    }
}