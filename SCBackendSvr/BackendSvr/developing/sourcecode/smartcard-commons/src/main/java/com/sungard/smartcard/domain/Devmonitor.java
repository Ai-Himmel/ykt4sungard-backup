package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_DEVMONITOR的实体类
 * 设备监控表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Devmonitor implements Serializable {

    /**
     * 终端编号也是设备编号
     */
    private Integer deviceid;
    /**
     *
     */
    private String optime;
    /**
     * 采集时间
     */
    private String coltime;
    /**
     *
     */
    private String devtime;
    /**
     * 心跳
     */
    private Integer beatstatus;
    /**
     * 卡版本号
     */
    private String cardverno;
    /**
     *
     */
    private Integer hardiskper;
    /**
     *
     */
    private Integer memoryper;
    /**
     *
     */
    private Integer cpuper;

    public void setDeviceid(Integer deviceid) {
        this.deviceid = deviceid;
    }

    public Integer getDeviceid() {
        return this.deviceid;
    }

    public void setOptime(String optime) {
        this.optime = optime;
    }

    public String getOptime() {
        return this.optime;
    }

    public void setColtime(String coltime) {
        this.coltime = coltime;
    }

    public String getColtime() {
        return this.coltime;
    }

    public void setDevtime(String devtime) {
        this.devtime = devtime;
    }

    public String getDevtime() {
        return this.devtime;
    }

    public void setBeatstatus(Integer beatstatus) {
        this.beatstatus = beatstatus;
    }

    public Integer getBeatstatus() {
        return this.beatstatus;
    }

    public void setCardverno(String cardverno) {
        this.cardverno = cardverno;
    }

    public String getCardverno() {
        return this.cardverno;
    }

    public void setHardiskper(Integer hardiskper) {
        this.hardiskper = hardiskper;
    }

    public Integer getHardiskper() {
        return this.hardiskper;
    }

    public void setMemoryper(Integer memoryper) {
        this.memoryper = memoryper;
    }

    public Integer getMemoryper() {
        return this.memoryper;
    }

    public void setCpuper(Integer cpuper) {
        this.cpuper = cpuper;
    }

    public Integer getCpuper() {
        return this.cpuper;
    }
}