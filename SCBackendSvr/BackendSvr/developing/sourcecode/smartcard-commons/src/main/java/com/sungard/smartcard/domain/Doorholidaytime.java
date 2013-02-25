package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_DOORHOLIDAYTIME的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Doorholidaytime implements Serializable {

    /**
     *
     */
    private Integer holidayid;
    /**
     *
     */
    private String holidaydate;
    /**
     * 时间组ID
     */
    private Integer timegrpid;
    /**
     * 增删标志
     */
    private Integer adddelflag;
    /**
     * 下传状态
     */
    private Integer downstatus;
    /**
     * 最后保存时间
     */
    private String updatetime;

    public void setHolidayid(Integer holidayid) {
        this.holidayid = holidayid;
    }

    public Integer getHolidayid() {
        return this.holidayid;
    }

    public void setHolidaydate(String holidaydate) {
        this.holidaydate = holidaydate;
    }

    public String getHolidaydate() {
        return this.holidaydate;
    }

    public void setTimegrpid(Integer timegrpid) {
        this.timegrpid = timegrpid;
    }

    public Integer getTimegrpid() {
        return this.timegrpid;
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