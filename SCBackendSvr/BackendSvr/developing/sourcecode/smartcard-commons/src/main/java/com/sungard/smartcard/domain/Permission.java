package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_PERMISSION的实体类
 * 功能角色关联表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Permission implements Serializable {

    /**
     * 系统功能ID
     */
    private Integer funcId;
    /**
     * 角色ID
     */
    private Integer roleId;
    /**
     * 功能授权操作值
     */
    private Integer authAction;

    public void setFuncId(Integer funcId) {
        this.funcId = funcId;
    }

    public Integer getFuncId() {
        return this.funcId;
    }

    public void setRoleId(Integer roleId) {
        this.roleId = roleId;
    }

    public Integer getRoleId() {
        return this.roleId;
    }

    public void setAuthAction(Integer authAction) {
        this.authAction = authAction;
    }

    public Integer getAuthAction() {
        return this.authAction;
    }
}