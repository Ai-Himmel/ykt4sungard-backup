package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_DOORGRPOPERRIGHT的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Doorgrpoperright implements Serializable {

    /**
     * 组号
     */
    private Integer groupid;
    /**
     * 操作员号
     */
    private String opercode;
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

    public void setOpercode(String opercode) {
        this.opercode = opercode;
    }

    public String getOpercode() {
        return this.opercode;
    }

    public void setUpdatetime(String updatetime) {
        this.updatetime = updatetime;
    }

    public String getUpdatetime() {
        return this.updatetime;
    }
}