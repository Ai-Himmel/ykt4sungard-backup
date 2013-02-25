package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_CFGPAYMENT的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Cfgpayment implements Serializable {

    /**
     * 客户的收费类别
     */
    private Integer paycode;
    /**
     * 交易类型
     */
    private String summary;
    /**
     * 是否启用
     */
    private Integer enabled;
    /**
     * 0-不联机1联机
     */
    private Integer onlinepay;
    /**
     * 1需要0不需要
     */
    private Integer paychkflag;
    /**
     * 0-输入1卡号2客户号3学号
     */
    private Integer payeeacctype;
    /**
     * 商户号
     */
    private Integer shopid;
    /**
     * BCC主功能号
     */
    private Integer bccfuncno;
    /**
     * BCCDRTP节点号
     */
    private Integer bccdrtpno;
    /**
     * 商户服务IP
     */
    private String ip;
    /**
     * 商户服务端口
     */
    private Integer port;
    /**
     * 商户超时时间(秒)
     */
    private Integer timeout;
    /**
     * 最后保存时间
     */
    private String lastsaved;

    public void setPaycode(Integer paycode) {
        this.paycode = paycode;
    }

    public Integer getPaycode() {
        return this.paycode;
    }

    public void setSummary(String summary) {
        this.summary = summary;
    }

    public String getSummary() {
        return this.summary;
    }

    public void setEnabled(Integer enabled) {
        this.enabled = enabled;
    }

    public Integer getEnabled() {
        return this.enabled;
    }

    public void setOnlinepay(Integer onlinepay) {
        this.onlinepay = onlinepay;
    }

    public Integer getOnlinepay() {
        return this.onlinepay;
    }

    public void setPaychkflag(Integer paychkflag) {
        this.paychkflag = paychkflag;
    }

    public Integer getPaychkflag() {
        return this.paychkflag;
    }

    public void setPayeeacctype(Integer payeeacctype) {
        this.payeeacctype = payeeacctype;
    }

    public Integer getPayeeacctype() {
        return this.payeeacctype;
    }

    public void setShopid(Integer shopid) {
        this.shopid = shopid;
    }

    public Integer getShopid() {
        return this.shopid;
    }

    public void setBccfuncno(Integer bccfuncno) {
        this.bccfuncno = bccfuncno;
    }

    public Integer getBccfuncno() {
        return this.bccfuncno;
    }

    public void setBccdrtpno(Integer bccdrtpno) {
        this.bccdrtpno = bccdrtpno;
    }

    public Integer getBccdrtpno() {
        return this.bccdrtpno;
    }

    public void setIp(String ip) {
        this.ip = ip;
    }

    public String getIp() {
        return this.ip;
    }

    public void setPort(Integer port) {
        this.port = port;
    }

    public Integer getPort() {
        return this.port;
    }

    public void setTimeout(Integer timeout) {
        this.timeout = timeout;
    }

    public Integer getTimeout() {
        return this.timeout;
    }

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }
}