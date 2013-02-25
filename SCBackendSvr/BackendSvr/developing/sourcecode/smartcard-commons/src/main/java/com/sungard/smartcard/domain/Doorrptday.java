package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_DOORRPTDAY的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Doorrptday implements Serializable {

    /**
     * 交易日期
     */
    private String transdate;
    /**
     * 设备编号
     */
    private Integer deviceid;
    /**
     * 总次数
     */
    private Integer totalcnt;
    /**
     *
     */
    private Integer validcnt;
    /**
     *
     */
    private Integer invalidcnt;

    public void setTransdate(String transdate) {
        this.transdate = transdate;
    }

    public String getTransdate() {
        return this.transdate;
    }

    public void setDeviceid(Integer deviceid) {
        this.deviceid = deviceid;
    }

    public Integer getDeviceid() {
        return this.deviceid;
    }

    public void setTotalcnt(Integer totalcnt) {
        this.totalcnt = totalcnt;
    }

    public Integer getTotalcnt() {
        return this.totalcnt;
    }

    public void setValidcnt(Integer validcnt) {
        this.validcnt = validcnt;
    }

    public Integer getValidcnt() {
        return this.validcnt;
    }

    public void setInvalidcnt(Integer invalidcnt) {
        this.invalidcnt = invalidcnt;
    }

    public Integer getInvalidcnt() {
        return this.invalidcnt;
    }
}