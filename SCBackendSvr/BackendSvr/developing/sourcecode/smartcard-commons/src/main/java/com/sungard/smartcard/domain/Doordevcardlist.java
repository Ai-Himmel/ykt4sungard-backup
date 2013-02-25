package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_DOORDEVCARDLIST的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Doordevcardlist implements Serializable {

    /**
     * 设备编号
     */
    private Integer deviceid;
    /**
     * 客户号
     */
    private Integer custid;
    /**
     * 星期ID
     */
    private Integer weekid;
    /**
     * 节假日ID
     */
    private Integer holidayid;
    /**
     * 交易卡号
     */
    private Integer cardno;
    /**
     * 卡物理ID
     */
    private String cardphyid;
    /**
     * 名单版本号
     */
    private String cardverno;
    /**
     * 增删标志:1-增-2删
     */
    private Integer adddelflag;
    /**
     * 下传状态
     */
    private Integer downstatus;
    /**
     * 下传时间
     */
    private String downtime;
    /**
     * 更新时间
     */
    private String updatetime;

    public void setDeviceid(Integer deviceid) {
        this.deviceid = deviceid;
    }

    public Integer getDeviceid() {
        return this.deviceid;
    }

    public void setCustid(Integer custid) {
        this.custid = custid;
    }

    public Integer getCustid() {
        return this.custid;
    }

    public void setWeekid(Integer weekid) {
        this.weekid = weekid;
    }

    public Integer getWeekid() {
        return this.weekid;
    }

    public void setHolidayid(Integer holidayid) {
        this.holidayid = holidayid;
    }

    public Integer getHolidayid() {
        return this.holidayid;
    }

    public void setCardno(Integer cardno) {
        this.cardno = cardno;
    }

    public Integer getCardno() {
        return this.cardno;
    }

    public void setCardphyid(String cardphyid) {
        this.cardphyid = cardphyid;
    }

    public String getCardphyid() {
        return this.cardphyid;
    }

    public void setCardverno(String cardverno) {
        this.cardverno = cardverno;
    }

    public String getCardverno() {
        return this.cardverno;
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

    public void setDowntime(String downtime) {
        this.downtime = downtime;
    }

    public String getDowntime() {
        return this.downtime;
    }

    public void setUpdatetime(String updatetime) {
        this.updatetime = updatetime;
    }

    public String getUpdatetime() {
        return this.updatetime;
    }
}