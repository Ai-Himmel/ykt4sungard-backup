package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_SHOPPOSTMP的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Shoppostmp implements Serializable {

    /**
     * 导入批次号
     */
    private String batchno;
    /**
     * 导入顺序号
     */
    private Integer seqno;
    /**
     * 导入日期
     */
    private String transdate;
    /**
     * 导入时间
     */
    private String transtime;
    /**
     * 导入操作员
     */
    private String opercode;
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
     * 截止时间
     */
    private String endtime;
    /**
     * 启用日期
     */
    private String startdate;
    /**
     * 停用日期
     */
    private String enddate;
    /**
     * 错误信息
     */
    private String errmsg;

    public void setBatchno(String batchno) {
        this.batchno = batchno;
    }

    public String getBatchno() {
        return this.batchno;
    }

    public void setSeqno(Integer seqno) {
        this.seqno = seqno;
    }

    public Integer getSeqno() {
        return this.seqno;
    }

    public void setTransdate(String transdate) {
        this.transdate = transdate;
    }

    public String getTransdate() {
        return this.transdate;
    }

    public void setTranstime(String transtime) {
        this.transtime = transtime;
    }

    public String getTranstime() {
        return this.transtime;
    }

    public void setOpercode(String opercode) {
        this.opercode = opercode;
    }

    public String getOpercode() {
        return this.opercode;
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

    public void setEndtime(String endtime) {
        this.endtime = endtime;
    }

    public String getEndtime() {
        return this.endtime;
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

    public void setErrmsg(String errmsg) {
        this.errmsg = errmsg;
    }

    public String getErrmsg() {
        return this.errmsg;
    }
}