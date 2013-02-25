package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_PSAMCARD的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Psamcard implements Serializable {

    /**
     * 卡号
     */
    private Integer cardno;
    /**
     * 卡类型
     */
    private Integer cardtype;
    /**
     * 卡版本号
     */
    private Integer cardver;
    /**
     * 终端编号
     */
    private String termno;
    /**
     * 状态
     */
    private Integer status;
    /**
     * 启用日期
     */
    private String startdate;
    /**
     * 过期日期
     */
    private String expiredate;
    /**
     * 密钥索引
     */
    private Integer keyindex;
    /**
     * 设备ID
     */
    private Integer deviceid;
    /**
     * 设备绑定日期
     */
    private String devjointime;
    /**
     * 发行方ID
     */
    private String publishid;
    /**
     * 用户ID
     */
    private String userid;
    /**
     * 注册日期
     */
    private String opendate;
    /**
     * 关闭日期
     */
    private String closedate;
    /**
     * 停用日期
     */
    private String disabledate;
    /**
     * 最后保存时间
     */
    private String lastsaved;

    public void setCardno(Integer cardno) {
        this.cardno = cardno;
    }

    public Integer getCardno() {
        return this.cardno;
    }

    public void setCardtype(Integer cardtype) {
        this.cardtype = cardtype;
    }

    public Integer getCardtype() {
        return this.cardtype;
    }

    public void setCardver(Integer cardver) {
        this.cardver = cardver;
    }

    public Integer getCardver() {
        return this.cardver;
    }

    public void setTermno(String termno) {
        this.termno = termno;
    }

    public String getTermno() {
        return this.termno;
    }

    public void setStatus(Integer status) {
        this.status = status;
    }

    public Integer getStatus() {
        return this.status;
    }

    public void setStartdate(String startdate) {
        this.startdate = startdate;
    }

    public String getStartdate() {
        return this.startdate;
    }

    public void setExpiredate(String expiredate) {
        this.expiredate = expiredate;
    }

    public String getExpiredate() {
        return this.expiredate;
    }

    public void setKeyindex(Integer keyindex) {
        this.keyindex = keyindex;
    }

    public Integer getKeyindex() {
        return this.keyindex;
    }

    public void setDeviceid(Integer deviceid) {
        this.deviceid = deviceid;
    }

    public Integer getDeviceid() {
        return this.deviceid;
    }

    public void setDevjointime(String devjointime) {
        this.devjointime = devjointime;
    }

    public String getDevjointime() {
        return this.devjointime;
    }

    public void setPublishid(String publishid) {
        this.publishid = publishid;
    }

    public String getPublishid() {
        return this.publishid;
    }

    public void setUserid(String userid) {
        this.userid = userid;
    }

    public String getUserid() {
        return this.userid;
    }

    public void setOpendate(String opendate) {
        this.opendate = opendate;
    }

    public String getOpendate() {
        return this.opendate;
    }

    public void setClosedate(String closedate) {
        this.closedate = closedate;
    }

    public String getClosedate() {
        return this.closedate;
    }

    public void setDisabledate(String disabledate) {
        this.disabledate = disabledate;
    }

    public String getDisabledate() {
        return this.disabledate;
    }

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }
}