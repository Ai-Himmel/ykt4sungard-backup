package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;
import com.sungard.smartcard.annotation.TransfersNodeOut;
import com.sungard.smartcard.annotation.TransfersNodeType;

import java.io.Serializable;

/**
 * T_FUNCTIONALITY的实体类
 * 系统功能
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Functionality implements Serializable {

    /**
     * ID
     */
    @TransfersNodeOut(value = TransfersNodeType.lvol0, desc = "系统功能ID")
    private Integer id;
    /**
     * 父功能ID
     */
    @TransfersNodeOut(value = TransfersNodeType.lvol1, desc = "系统功能父ID")
    private Integer pid;
    /**
     * 名称
     */
    @TransfersNodeOut(value = TransfersNodeType.sbankname, desc = "系统功能名")
    private String name;
    /**
     * 支持的授权操作值
     */
    @TransfersNodeOut(value = TransfersNodeType.lvol2, desc = "功能授权操作值")
    private Integer supportedAction;
    /**
     * 插件类型
     */
    @TransfersNodeOut(value = TransfersNodeType.sbankname2, desc = "插件类型")
    private String targetPlugin;
    /**
     * 级别
     */
    private Integer funcLevel;
    /**
     * 所属系统
     */
    private String app;
    /**
     * 备注
     */
    private String remark;

    public void setId(Integer id) {
        this.id = id;
    }

    public Integer getId() {
        return this.id;
    }

    public void setPid(Integer pid) {
        this.pid = pid;
    }

    public Integer getPid() {
        return this.pid;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return this.name;
    }

    public void setSupportedAction(Integer supportedAction) {
        this.supportedAction = supportedAction;
    }

    public Integer getSupportedAction() {
        return this.supportedAction;
    }

    public void setTargetPlugin(String targetPlugin) {
        this.targetPlugin = targetPlugin;
    }

    public String getTargetPlugin() {
        return this.targetPlugin;
    }

    public void setFuncLevel(Integer funcLevel) {
        this.funcLevel = funcLevel;
    }

    public Integer getFuncLevel() {
        return this.funcLevel;
    }

    public void setApp(String app) {
        this.app = app;
    }

    public String getApp() {
        return this.app;
    }

    public void setRemark(String remark) {
        this.remark = remark;
    }

    public String getRemark() {
        return this.remark;
    }
}