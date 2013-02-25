package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_DOORWEEKTIME的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Doorweektime implements Serializable {

    /**
     * 星期ID
     */
    private Integer weekid;
    /**
     *
     */
    private String weekname;
    /**
     *
     */
    private Integer day1timegrpid;
    /**
     *
     */
    private Integer day2timegrpid;
    /**
     *
     */
    private Integer day3timegrpid;
    /**
     *
     */
    private Integer day4timegrpid;
    /**
     *
     */
    private Integer day5timegrpid;
    /**
     *
     */
    private Integer day6timegrpid;
    /**
     *
     */
    private Integer day7timegrpid;
    /**
     * 增删标志
     */
    private Integer adddelflag;
    /**
     * 下传状态
     */
    private Integer downstatus;
    /**
     *
     */
    private String updatetime;

    public void setWeekid(Integer weekid) {
        this.weekid = weekid;
    }

    public Integer getWeekid() {
        return this.weekid;
    }

    public void setWeekname(String weekname) {
        this.weekname = weekname;
    }

    public String getWeekname() {
        return this.weekname;
    }

    public void setDay1timegrpid(Integer day1timegrpid) {
        this.day1timegrpid = day1timegrpid;
    }

    public Integer getDay1timegrpid() {
        return this.day1timegrpid;
    }

    public void setDay2timegrpid(Integer day2timegrpid) {
        this.day2timegrpid = day2timegrpid;
    }

    public Integer getDay2timegrpid() {
        return this.day2timegrpid;
    }

    public void setDay3timegrpid(Integer day3timegrpid) {
        this.day3timegrpid = day3timegrpid;
    }

    public Integer getDay3timegrpid() {
        return this.day3timegrpid;
    }

    public void setDay4timegrpid(Integer day4timegrpid) {
        this.day4timegrpid = day4timegrpid;
    }

    public Integer getDay4timegrpid() {
        return this.day4timegrpid;
    }

    public void setDay5timegrpid(Integer day5timegrpid) {
        this.day5timegrpid = day5timegrpid;
    }

    public Integer getDay5timegrpid() {
        return this.day5timegrpid;
    }

    public void setDay6timegrpid(Integer day6timegrpid) {
        this.day6timegrpid = day6timegrpid;
    }

    public Integer getDay6timegrpid() {
        return this.day6timegrpid;
    }

    public void setDay7timegrpid(Integer day7timegrpid) {
        this.day7timegrpid = day7timegrpid;
    }

    public Integer getDay7timegrpid() {
        return this.day7timegrpid;
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