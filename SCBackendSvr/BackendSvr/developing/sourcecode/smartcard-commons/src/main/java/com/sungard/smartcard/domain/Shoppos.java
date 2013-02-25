package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_SHOPPOS的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Shoppos implements Serializable {

    /**
     * 记录编号
     */
    private Integer id;
    /**
     * 设备ID
     */
    private Integer deviceid;
    /**
     * 设备物理ID
     */
    private String devphyid;
    /**
     * 商户号
     */
    private Integer shopid;
    /**
     * 开始时间
     */
    private String starttime;
    /**
     * 截止时间
     */
    private String endtime;
    /**
     * 备注
     */
    private String remark;
    /**
     * 启用日期
     */
    private String startdate;
    /**
     * 停用日期
     */
    private String enddate;
    /**
     * 1-正常2-过期
     */
    private String status;
    /**
     * 操作员号
     */
    private String opercode;
    /**
     * 最好保存时间
     */
    private String lastsaved;

    public void setId(Integer id) {
        this.id = id;
    }

    public Integer getId() {
        return this.id;
    }

    public void setDeviceid(Integer deviceid) {
        this.deviceid = deviceid;
    }

    public Integer getDeviceid() {
        return this.deviceid;
    }

    public void setDevphyid(String devphyid) {
        this.devphyid = devphyid;
    }

    public String getDevphyid() {
        return this.devphyid;
    }

    public void setShopid(Integer shopid) {
        this.shopid = shopid;
    }

    public Integer getShopid() {
        return this.shopid;
    }

    public void setStarttime(String starttime) {
        this.starttime = starttime;
    }

    public String getStarttime() {
        return this.starttime;
    }

    public void setEndtime(String endtime) {
        this.endtime = endtime;
    }

    public String getEndtime() {
        return this.endtime;
    }

    public void setRemark(String remark) {
        this.remark = remark;
    }

    public String getRemark() {
        return this.remark;
    }

    public void setStartdate(String startdate) {
        this.startdate = startdate;
    }

    public String getStartdate() {
        return this.startdate;
    }

    public void setEnddate(String enddate) {
        this.enddate = enddate;
    }

    public String getEnddate() {
        return this.enddate;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getStatus() {
        return this.status;
    }

    public void setOpercode(String opercode) {
        this.opercode = opercode;
    }

    public String getOpercode() {
        return this.opercode;
    }

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }
}