package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_CARDBITMAP的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Cardbitmap implements Serializable {

    /**
     * 交易卡号
     */
    private Integer cardno;
    /**
     * 基准卡流水号
     */
    private Integer baseno;
    /**
     * 位图0
     */
    private String bitmap0;
    /**
     * 位图1
     */
    private String bitmap1;
    /**
     * 位图2
     */
    private String bitmap2;
    /**
     * 位图3
     */
    private String bitmap3;
    /**
     * 位图4
     */
    private String bitmap4;
    /**
     * 位图5
     */
    private String bitmap5;
    /**
     * 位图6
     */
    private String bitmap6;
    /**
     * 位图7
     */
    private String bitmap7;
    /**
     * 位图8
     */
    private String bitmap8;
    /**
     * 位图9
     */
    private String bitmap9;
    /**
     * 删除标志
     */
    private String delflag;

    public void setCardno(Integer cardno) {
        this.cardno = cardno;
    }

    public Integer getCardno() {
        return this.cardno;
    }

    public void setBaseno(Integer baseno) {
        this.baseno = baseno;
    }

    public Integer getBaseno() {
        return this.baseno;
    }

    public void setBitmap0(String bitmap0) {
        this.bitmap0 = bitmap0;
    }

    public String getBitmap0() {
        return this.bitmap0;
    }

    public void setBitmap1(String bitmap1) {
        this.bitmap1 = bitmap1;
    }

    public String getBitmap1() {
        return this.bitmap1;
    }

    public void setBitmap2(String bitmap2) {
        this.bitmap2 = bitmap2;
    }

    public String getBitmap2() {
        return this.bitmap2;
    }

    public void setBitmap3(String bitmap3) {
        this.bitmap3 = bitmap3;
    }

    public String getBitmap3() {
        return this.bitmap3;
    }

    public void setBitmap4(String bitmap4) {
        this.bitmap4 = bitmap4;
    }

    public String getBitmap4() {
        return this.bitmap4;
    }

    public void setBitmap5(String bitmap5) {
        this.bitmap5 = bitmap5;
    }

    public String getBitmap5() {
        return this.bitmap5;
    }

    public void setBitmap6(String bitmap6) {
        this.bitmap6 = bitmap6;
    }

    public String getBitmap6() {
        return this.bitmap6;
    }

    public void setBitmap7(String bitmap7) {
        this.bitmap7 = bitmap7;
    }

    public String getBitmap7() {
        return this.bitmap7;
    }

    public void setBitmap8(String bitmap8) {
        this.bitmap8 = bitmap8;
    }

    public String getBitmap8() {
        return this.bitmap8;
    }

    public void setBitmap9(String bitmap9) {
        this.bitmap9 = bitmap9;
    }

    public String getBitmap9() {
        return this.bitmap9;
    }

    public void setDelflag(String delflag) {
        this.delflag = delflag;
    }

    public String getDelflag() {
        return this.delflag;
    }
}