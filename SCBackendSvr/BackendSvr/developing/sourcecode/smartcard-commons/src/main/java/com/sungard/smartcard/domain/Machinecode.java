package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_MACHINECODE的实体类
 * 机器码表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Machinecode implements Serializable {

    /**
     * 机器码
     */
    private String machinecode;
    /**
     * IP地址
     */
    private String ip;
    /**
     * 最后保存时间
     */
    private String lastsaved;

    public void setMachinecode(String machinecode) {
        this.machinecode = machinecode;
    }

    public String getMachinecode() {
        return this.machinecode;
    }

    public void setIp(String ip) {
        this.ip = ip;
    }

    public String getIp() {
        return this.ip;
    }

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }
}