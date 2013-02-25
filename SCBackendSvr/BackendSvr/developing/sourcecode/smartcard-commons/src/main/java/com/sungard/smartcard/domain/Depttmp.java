package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_DEPTTMP的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Depttmp implements Serializable {

    /**
     * 部门代码
     */
    private String deptcode;
    /**
     * 区域代码
     */
    private String areacode;
    /**
     * 部门名称
     */
    private String deptname;
    /**
     * 部门英文名
     */
    private String deptename;
    /**
     * 部门全称
     */
    private String deptfullname;
    /**
     * 上级部门代码
     */
    private String fdeptcode;
    /**
     * 部门级别
     */
    private Integer deptlevel;
    /**
     * 最后保存日期
     */
    private String lastsaved;

    public void setDeptcode(String deptcode) {
        this.deptcode = deptcode;
    }

    public String getDeptcode() {
        return this.deptcode;
    }

    public void setAreacode(String areacode) {
        this.areacode = areacode;
    }

    public String getAreacode() {
        return this.areacode;
    }

    public void setDeptname(String deptname) {
        this.deptname = deptname;
    }

    public String getDeptname() {
        return this.deptname;
    }

    public void setDeptename(String deptename) {
        this.deptename = deptename;
    }

    public String getDeptename() {
        return this.deptename;
    }

    public void setDeptfullname(String deptfullname) {
        this.deptfullname = deptfullname;
    }

    public String getDeptfullname() {
        return this.deptfullname;
    }

    public void setFdeptcode(String fdeptcode) {
        this.fdeptcode = fdeptcode;
    }

    public String getFdeptcode() {
        return this.fdeptcode;
    }

    public void setDeptlevel(Integer deptlevel) {
        this.deptlevel = deptlevel;
    }

    public Integer getDeptlevel() {
        return this.deptlevel;
    }

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }
}