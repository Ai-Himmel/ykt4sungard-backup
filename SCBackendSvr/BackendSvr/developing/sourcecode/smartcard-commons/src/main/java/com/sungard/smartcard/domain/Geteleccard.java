package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_GETELECCARD的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Geteleccard implements Serializable {

    /**
     * 交易卡号
     */
    private Integer cardno;
    /**
     * 卡物理ID
     */
    private String cardphyid;
    /**
     * 设备ID
     */
    private Integer deviceid;
    /**
     * 0-管理卡-1-常开卡
     */
    private Integer usetype;
    /**
     * 1-增加2-删除
     */
    private Integer adddelflag;
    /**
     * 下载时间
     */
    private String downtime;

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

    public void setDeviceid(Integer deviceid) {
        this.deviceid = deviceid;
    }

    public Integer getDeviceid() {
        return this.deviceid;
    }

    public void setUsetype(Integer usetype) {
        this.usetype = usetype;
    }

    public Integer getUsetype() {
        return this.usetype;
    }

    public void setAdddelflag(Integer adddelflag) {
        this.adddelflag = adddelflag;
    }

    public Integer getAdddelflag() {
        return this.adddelflag;
    }

    public void setDowntime(String downtime) {
        this.downtime = downtime;
    }

    public String getDowntime() {
        return this.downtime;
    }
}