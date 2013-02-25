package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_DOORHOLIDAY的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Doorholiday implements Serializable {

    /**
     * 节假日ID
     */
    private Integer holidayid;
    /**
     * 节假日名
     */
    private String holidayname;
    /**
     * 节假日天数
     */
    private Integer daycnt;
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

    public void setHolidayname(String holidayname) {
        this.holidayname = holidayname;
    }

    public String getHolidayname() {
        return this.holidayname;
    }

    public void setDaycnt(Integer daycnt) {
        this.daycnt = daycnt;
    }

    public Integer getDaycnt() {
        return this.daycnt;
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