package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_DOORGRPMEMBER的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Doorgrpmember implements Serializable {

    /**
     * 组号
     */
    private Integer groupid;
    /**
     * 设备编号
     */
    private Integer deviceid;
    /**
     * 更新时间
     */
    private String updatetime;

    public void setGroupid(Integer groupid) {
        this.groupid = groupid;
    }

    public Integer getGroupid() {
        return this.groupid;
    }

    public void setDeviceid(Integer deviceid) {
        this.deviceid = deviceid;
    }

    public Integer getDeviceid() {
        return this.deviceid;
    }

    public void setUpdatetime(String updatetime) {
        this.updatetime = updatetime;
    }

    public String getUpdatetime() {
        return this.updatetime;
    }
}