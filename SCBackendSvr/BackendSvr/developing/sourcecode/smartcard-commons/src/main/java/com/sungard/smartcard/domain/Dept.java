package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;
import com.sungard.smartcard.annotation.TransfersNodeIn;
import com.sungard.smartcard.annotation.TransfersNodeOut;
import com.sungard.smartcard.annotation.TransfersNodeType;

import java.io.Serializable;

/**
 * T_DEPT的实体类
 * 部门表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Dept implements Serializable {

    /**
     * 部门代码 30
     */
    @TransfersNodeIn(value = TransfersNodeType.scust_limit, desc = "部门代码 ")
    @TransfersNodeOut(value = TransfersNodeType.scust_limit, desc = "部门代码 ")//33
    private String deptcode;
    /**
     * 区域代码 3
     */
    @TransfersNodeOut(value = TransfersNodeType.sroom_no, desc = "区域代码 ")//4
    private String areacode;
    /**
     * 部门名称 240
     */
    @TransfersNodeIn(value = TransfersNodeType.vsvarstr0, desc = "部门名称")
    @TransfersNodeOut(value = TransfersNodeType.vsvarstr0, desc = "部门名称")//256
    private String deptname;
    /**
     * 部门英文名 240
     */
    @TransfersNodeIn(value = TransfersNodeType.vsvarstr1, desc = "部门英文名")
    @TransfersNodeOut(value = TransfersNodeType.vsvarstr1, desc = "部门英文名")//256
    private String deptename;
    /**
     * 部门全称 1000
     */
    @TransfersNodeOut(value = TransfersNodeType.vsvarstr2, desc = "部门全称")//256
    private String deptfullname;
    /**
     * 上级部门代码  30
     */
    @TransfersNodeIn(value = TransfersNodeType.sbank_acc, desc = "上级部门代码")
    @TransfersNodeOut(value = TransfersNodeType.sbank_acc, desc = "上级部门代码")//41
    private String fdeptcode;
    /**
     * 部门级别 INTEGER
     */
    @TransfersNodeOut(value = TransfersNodeType.lserial0, desc = "部门级别")//int 4
    private Integer deptlevel;
    /**
     * 0部门1班级 NUMBER(1)
     */
    private Integer depttype;
    /**
     * 原部门代码 30
     */
    @TransfersNodeOut(value = TransfersNodeType.sbank_acc2, desc = "原部门代码")//41
    private String olddeptcode;
    /**
     * 使用标志:0-未使用1-已使用
     */
    private String useflag;
    /**
     * 最后保存日期 30
     */
    @TransfersNodeOut(value = TransfersNodeType.scert_no2, desc = "最新保存时间")//51
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

    public void setDepttype(Integer depttype) {
        this.depttype = depttype;
    }

    public Integer getDepttype() {
        return this.depttype;
    }

    public void setOlddeptcode(String olddeptcode) {
        this.olddeptcode = olddeptcode;
    }

    public String getOlddeptcode() {
        return this.olddeptcode;
    }

    public void setUseflag(String useflag) {
        this.useflag = useflag;
    }

    public String getUseflag() {
        return this.useflag;
    }

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }
}