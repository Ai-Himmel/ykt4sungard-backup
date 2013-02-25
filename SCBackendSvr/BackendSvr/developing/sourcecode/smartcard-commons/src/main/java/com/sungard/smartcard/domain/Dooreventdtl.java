package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_DOOREVENTDTL的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Dooreventdtl implements Serializable {

    /**
     * 设备编号
     */
    private Integer deviceid;
    /**
     * 交易日期
     */
    private String transdate;
    /**
     * 交易时间
     */
    private String transtime;
    /**
     * 事件代码
     */
    private Integer eventcode;
    /**
     * 事件消息
     */
    private String eventmsg;
    /**
     * 子系统ID
     */
    private Integer sysid;
    /**
     * 采集日期
     */
    private String coldate;
    /**
     * 采集时间
     */
    private String coltime;

    public void setDeviceid(Integer deviceid) {
        this.deviceid = deviceid;
    }

    public Integer getDeviceid() {
        return this.deviceid;
    }

    public void setTransdate(String transdate) {
        this.transdate = transdate;
    }

    public String getTransdate() {
        return this.transdate;
    }

    public void setTranstime(String transtime) {
        this.transtime = transtime;
    }

    public String getTranstime() {
        return this.transtime;
    }

    public void setEventcode(Integer eventcode) {
        this.eventcode = eventcode;
    }

    public Integer getEventcode() {
        return this.eventcode;
    }

    public void setEventmsg(String eventmsg) {
        this.eventmsg = eventmsg;
    }

    public String getEventmsg() {
        return this.eventmsg;
    }

    public void setSysid(Integer sysid) {
        this.sysid = sysid;
    }

    public Integer getSysid() {
        return this.sysid;
    }

    public void setColdate(String coldate) {
        this.coldate = coldate;
    }

    public String getColdate() {
        return this.coldate;
    }

    public void setColtime(String coltime) {
        this.coltime = coltime;
    }

    public String getColtime() {
        return this.coltime;
    }
}