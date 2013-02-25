package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;
import com.sungard.smartcard.annotation.TransfersNodeIn;
import com.sungard.smartcard.annotation.TransfersNodeOut;
import com.sungard.smartcard.annotation.TransfersNodeType;

import java.io.Serializable;

/**
 * T_DEVICETMP的实体类
 * 设备临时表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Devicetmp implements Serializable {

    /**
     * 导入批次号
     */
    @TransfersNodeIn(value = TransfersNodeType.sphone, desc = "导入批次号")
    @TransfersNodeOut(value = TransfersNodeType.sphone, desc = "导入批次号")
    private String batchno;
    /**
     * 导入序列号
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol9, desc = "导入序列号")
    @TransfersNodeOut(value = TransfersNodeType.lvol9, desc = "导入序列号")
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
     * 区域代码
     */
    @TransfersNodeIn(value = TransfersNodeType.scust_type, desc = "区域代码")
    @TransfersNodeOut(value = TransfersNodeType.scust_type, desc = "区域代码")
    private String areacode;
    /**
     * 设备名称
     */
    @TransfersNodeIn(value = TransfersNodeType.semail, desc = "设备名称")
    @TransfersNodeOut(value = TransfersNodeType.semail, desc = "设备名称")
    private String devicename;
    /**
     * 设备物理ID★
     */
    @TransfersNodeIn(value = TransfersNodeType.scust_auth, desc = "设备物理ID")
    @TransfersNodeOut(value = TransfersNodeType.scust_auth, desc = "设备物理ID")
    private String devphyid;
    /**
     * 设备厂商代码
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol8, desc = "设备厂商代码")
    @TransfersNodeOut(value = TransfersNodeType.lvol8, desc = "设备厂商代码")
    private Integer devphytype;
    /**
     * 设备类型★
     */
    @TransfersNodeIn(value = TransfersNodeType.scust_limit, desc = "设备机型")
    @TransfersNodeOut(value = TransfersNodeType.scust_limit, desc = "设备机型")
    private String devtypecode;
    /**
     * 设备机号
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol4, desc = "设备机号")
    @TransfersNodeOut(value = TransfersNodeType.lvol4, desc = "设备机号")
    private Integer deviceno;
    /**
     * 上级设备ID
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol1, desc = "上级设备ID")
    @TransfersNodeOut(value = TransfersNodeType.lvol1, desc = "上级设备ID")
    private Integer fdeviceid;
    /**
     * 卡物理型号
     */
    @TransfersNodeIn(value = TransfersNodeType.sstatus1, desc = "卡片结构")
    @TransfersNodeOut(value = TransfersNodeType.sstatus1, desc = "卡片结构")
    private String cardphytype;
    /**
     * 通讯方式:1-串口2-MODEM3-TCPIP 9-级联
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol6, desc = "通讯方式")
    @TransfersNodeOut(value = TransfersNodeType.lvol6, desc = "通讯方式")
    private Integer commtype;
    /**
     * IP地址
     */
    @TransfersNodeIn(value = TransfersNodeType.scust_auth2, desc = "IP地址")
    @TransfersNodeOut(value = TransfersNodeType.scust_auth2, desc = "IP地址")
    private String ip;
    /**
     * 通讯端口号
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol7, desc = "通讯端口号")
    @TransfersNodeOut(value = TransfersNodeType.lvol7, desc = "通讯端口号")
    private Integer portno;
    /**
     * 服务器接口编号
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol3, desc = "服务器端口号")
    @TransfersNodeOut(value = TransfersNodeType.lvol3, desc = "服务器端口号")
    private Integer svrportno;
    /**
     * 端口总数
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol5, desc = "端口总数")
    @TransfersNodeOut(value = TransfersNodeType.lvol5, desc = "端口总数")
    private Integer svrportcnt;
    /**
     * 前置机系统ID（子系统ID）
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol2, desc = "子系统ID")
    @TransfersNodeOut(value = TransfersNodeType.lvol2, desc = "子系统ID")
    private Integer sysid;
    /**
     * 设备用途
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol0, desc = "设备用途")
    @TransfersNodeOut(value = TransfersNodeType.lvol0, desc = "设备用途")
    private Integer devusage;
    /**
     * 错误信息
     */
    @TransfersNodeOut(value = TransfersNodeType.vsvarstr0, desc = "错误信息")
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

    public void setAreacode(String areacode) {
        this.areacode = areacode;
    }

    public String getAreacode() {
        return this.areacode;
    }

    public void setDevicename(String devicename) {
        this.devicename = devicename;
    }

    public String getDevicename() {
        return this.devicename;
    }

    public void setDevphyid(String devphyid) {
        this.devphyid = devphyid;
    }

    public String getDevphyid() {
        return this.devphyid;
    }

    public void setDevphytype(Integer devphytype) {
        this.devphytype = devphytype;
    }

    public Integer getDevphytype() {
        return this.devphytype;
    }

    public void setDevtypecode(String devtypecode) {
        this.devtypecode = devtypecode;
    }

    public String getDevtypecode() {
        return this.devtypecode;
    }

    public void setDeviceno(Integer deviceno) {
        this.deviceno = deviceno;
    }

    public Integer getDeviceno() {
        return this.deviceno;
    }

    public void setFdeviceid(Integer fdeviceid) {
        this.fdeviceid = fdeviceid;
    }

    public Integer getFdeviceid() {
        return this.fdeviceid;
    }

    public void setCardphytype(String cardphytype) {
        this.cardphytype = cardphytype;
    }

    public String getCardphytype() {
        return this.cardphytype;
    }

    public void setCommtype(Integer commtype) {
        this.commtype = commtype;
    }

    public Integer getCommtype() {
        return this.commtype;
    }

    public void setIp(String ip) {
        this.ip = ip;
    }

    public String getIp() {
        return this.ip;
    }

    public void setPortno(Integer portno) {
        this.portno = portno;
    }

    public Integer getPortno() {
        return this.portno;
    }

    public void setSvrportno(Integer svrportno) {
        this.svrportno = svrportno;
    }

    public Integer getSvrportno() {
        return this.svrportno;
    }

    public void setSvrportcnt(Integer svrportcnt) {
        this.svrportcnt = svrportcnt;
    }

    public Integer getSvrportcnt() {
        return this.svrportcnt;
    }

    public void setSysid(Integer sysid) {
        this.sysid = sysid;
    }

    public Integer getSysid() {
        return this.sysid;
    }

    public void setDevusage(Integer devusage) {
        this.devusage = devusage;
    }

    public Integer getDevusage() {
        return this.devusage;
    }

    public void setErrmsg(String errmsg) {
        this.errmsg = errmsg;
    }

    public String getErrmsg() {
        return this.errmsg;
    }
}