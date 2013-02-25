package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_DOORGROUP的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Doorgroup implements Serializable {

    /**
     * 组号
     */
    private Integer groupid;
    /**
     * 组名称
     */
    private String groupname;
    /**
     * 状态
     */
    private String status;
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

    public void setGroupname(String groupname) {
        this.groupname = groupname;
    }

    public String getGroupname() {
        return this.groupname;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getStatus() {
        return this.status;
    }

    public void setUpdatetime(String updatetime) {
        this.updatetime = updatetime;
    }

    public String getUpdatetime() {
        return this.updatetime;
    }
}