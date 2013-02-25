package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_PHOTOLIMIT的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Photolimit implements Serializable {

    /**
     * 操作员号
     */
    private String opercode;
    /**
     * 操作员名称
     */
    private String opername;
    /**
     * 操作员密码
     */
    private String operpwd;
    /**
     * 权限
     */
    private String operlimit;
    /**
     * 是否可用
     */
    private String enabled;
    /**
     * 生效日期
     */
    private String begindate;
    /**
     * 失效日期
     */
    private String enddate;
    /**
     * 备注
     */
    private String remark;

    public void setOpercode(String opercode) {
        this.opercode = opercode;
    }

    public String getOpercode() {
        return this.opercode;
    }

    public void setOpername(String opername) {
        this.opername = opername;
    }

    public String getOpername() {
        return this.opername;
    }

    public void setOperpwd(String operpwd) {
        this.operpwd = operpwd;
    }

    public String getOperpwd() {
        return this.operpwd;
    }

    public void setOperlimit(String operlimit) {
        this.operlimit = operlimit;
    }

    public String getOperlimit() {
        return this.operlimit;
    }

    public void setEnabled(String enabled) {
        this.enabled = enabled;
    }

    public String getEnabled() {
        return this.enabled;
    }

    public void setBegindate(String begindate) {
        this.begindate = begindate;
    }

    public String getBegindate() {
        return this.begindate;
    }

    public void setEnddate(String enddate) {
        this.enddate = enddate;
    }

    public String getEnddate() {
        return this.enddate;
    }

    public void setRemark(String remark) {
        this.remark = remark;
    }

    public String getRemark() {
        return this.remark;
    }
}