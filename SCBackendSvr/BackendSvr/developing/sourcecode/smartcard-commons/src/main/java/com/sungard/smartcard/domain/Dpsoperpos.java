package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_DPSOPERPOS的实体类
 * 充值操作员设备表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Dpsoperpos implements Serializable {

    /**
     * 操作员号
     */
    private String opercode;
    /**
     * 设备编号
     */
    private Integer deviceid;
    /**
     * 注册操作员
     */
    private String openoper;
    /**
     * 最后保存时间
     */
    private String lastsaved;

    public void setOpercode(String opercode) {
        this.opercode = opercode;
    }

    public String getOpercode() {
        return this.opercode;
    }

    public void setDeviceid(Integer deviceid) {
        this.deviceid = deviceid;
    }

    public Integer getDeviceid() {
        return this.deviceid;
    }

    public void setOpenoper(String openoper) {
        this.openoper = openoper;
    }

    public String getOpenoper() {
        return this.openoper;
    }

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }
}