package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_DOORTIME的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Doortime implements Serializable {

    /**
     *
     */
    private Integer timeid;
    /**
     *
     */
    private String timename;
    /**
     *
     */
    private String starttime;
    /**
     *
     */
    private String endtime;
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

    public void setTimeid(Integer timeid) {
        this.timeid = timeid;
    }

    public Integer getTimeid() {
        return this.timeid;
    }

    public void setTimename(String timename) {
        this.timename = timename;
    }

    public String getTimename() {
        return this.timename;
    }

    public void setStarttime(String starttime) {
        this.starttime = starttime;
    }

    public String getStarttime() {
        return this.starttime;
    }

    public void setEndtime(String endtime) {
        this.endtime = endtime;
    }

    public String getEndtime() {
        return this.endtime;
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