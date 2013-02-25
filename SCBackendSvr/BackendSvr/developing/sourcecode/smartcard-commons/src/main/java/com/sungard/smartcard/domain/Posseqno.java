package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_POSSEQNO的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Posseqno implements Serializable {

    /**
     * 设备ID
     */
    private Integer deviceid;
    /**
     * 设备流水号
     */
    private Integer devseqno;
    /**
     * 交易日期
     */
    private String transdate;

    public void setDeviceid(Integer deviceid) {
        this.deviceid = deviceid;
    }

    public Integer getDeviceid() {
        return this.deviceid;
    }

    public void setDevseqno(Integer devseqno) {
        this.devseqno = devseqno;
    }

    public Integer getDevseqno() {
        return this.devseqno;
    }

    public void setTransdate(String transdate) {
        this.transdate = transdate;
    }

    public String getTransdate() {
        return this.transdate;
    }
}