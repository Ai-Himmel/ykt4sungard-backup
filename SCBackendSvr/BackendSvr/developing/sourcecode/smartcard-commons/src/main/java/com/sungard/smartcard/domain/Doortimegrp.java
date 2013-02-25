package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_DOORTIMEGRP的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Doortimegrp implements Serializable {

    /**
     *
     */
    private Integer timegrpid;
    /**
     *
     */
    private String timegrpname;
    /**
     *
     */
    private Integer timeid1;
    /**
     *
     */
    private Integer timeid2;
    /**
     *
     */
    private Integer timeid3;
    /**
     *
     */
    private Integer timeid4;
    /**
     *
     */
    private Integer timeid5;
    /**
     *
     */
    private Integer timeid6;
    /**
     *
     */
    private Integer timeid7;
    /**
     *
     */
    private Integer timeid8;
    /**
     * 增删标志
     */
    private Integer adddelflag;
    /**
     * 下传状态
     */
    private Integer downstatus;
    /**
     * 更新时间
     */
    private String updatetime;

    public void setTimegrpid(Integer timegrpid) {
        this.timegrpid = timegrpid;
    }

    public Integer getTimegrpid() {
        return this.timegrpid;
    }

    public void setTimegrpname(String timegrpname) {
        this.timegrpname = timegrpname;
    }

    public String getTimegrpname() {
        return this.timegrpname;
    }

    public void setTimeid1(Integer timeid1) {
        this.timeid1 = timeid1;
    }

    public Integer getTimeid1() {
        return this.timeid1;
    }

    public void setTimeid2(Integer timeid2) {
        this.timeid2 = timeid2;
    }

    public Integer getTimeid2() {
        return this.timeid2;
    }

    public void setTimeid3(Integer timeid3) {
        this.timeid3 = timeid3;
    }

    public Integer getTimeid3() {
        return this.timeid3;
    }

    public void setTimeid4(Integer timeid4) {
        this.timeid4 = timeid4;
    }

    public Integer getTimeid4() {
        return this.timeid4;
    }

    public void setTimeid5(Integer timeid5) {
        this.timeid5 = timeid5;
    }

    public Integer getTimeid5() {
        return this.timeid5;
    }

    public void setTimeid6(Integer timeid6) {
        this.timeid6 = timeid6;
    }

    public Integer getTimeid6() {
        return this.timeid6;
    }

    public void setTimeid7(Integer timeid7) {
        this.timeid7 = timeid7;
    }

    public Integer getTimeid7() {
        return this.timeid7;
    }

    public void setTimeid8(Integer timeid8) {
        this.timeid8 = timeid8;
    }

    public Integer getTimeid8() {
        return this.timeid8;
    }

    public void setAdddelflag(Integer adddelflag) {
        this.adddelflag = adddelflag;
    }

    public Integer getAdddelflag() {
        return this.adddelflag;
    }

    public void setDownstatus(Integer downstatus) {
        this.downstatus = downstatus;
    }

    public Integer getDownstatus() {
        return this.downstatus;
    }

    public void setUpdatetime(String updatetime) {
        this.updatetime = updatetime;
    }

    public String getUpdatetime() {
        return this.updatetime;
    }
}