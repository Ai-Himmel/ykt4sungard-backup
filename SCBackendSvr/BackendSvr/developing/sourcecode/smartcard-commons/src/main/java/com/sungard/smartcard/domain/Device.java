package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;
import com.sungard.smartcard.annotation.TransfersNodeIn;
import com.sungard.smartcard.annotation.TransfersNodeOut;
import com.sungard.smartcard.annotation.TransfersNodeType;

import java.io.Serializable;

/**
 * T_DEVICE的实体类
 * 设备表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Device implements Serializable {

    /**
     * 终端编号也是设备编号
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol11, desc = "设备编号")
    @TransfersNodeOut(value = TransfersNodeType.lvol11, desc = "设备编号")
    private Integer deviceid;
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
     * 设备机号
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol4, desc = "设备机号")
    @TransfersNodeOut(value = TransfersNodeType.lvol4, desc = "设备机号")
    private Integer deviceno;
    /**
     * 设备厂商代码(设备类型)
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol8, desc = "设备厂商代码")
    @TransfersNodeOut(value = TransfersNodeType.lvol8, desc = "设备厂商代码")
    private Integer devphytype;
    /**
     * 设备类型★（设备机型）
     */
    @TransfersNodeIn(value = TransfersNodeType.scust_limit, desc = "设备机型")
    @TransfersNodeOut(value = TransfersNodeType.scust_limit, desc = "设备机型")
    private String devtypecode;
    /**
     * 设备版本号★
     */
    private String devverno;
    /**
     * 卡物理型号（卡片结构）
     */
    @TransfersNodeIn(value = TransfersNodeType.sstatus1, desc = "卡片结构")
    @TransfersNodeOut(value = TransfersNodeType.sstatus1, desc = "卡片结构")
    private String cardphytype;
    /**
     * 上级设备ID
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol1, desc = "上级设备ID")
    @TransfersNodeOut(value = TransfersNodeType.lvol1, desc = "上级设备ID")
    private Integer fdeviceid;
    /**
     * 运行状态
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol9, desc = "运行状态")
    @TransfersNodeOut(value = TransfersNodeType.lvol9, desc = "运行状态")
    private Integer runstatus;
    /**
     * 状态:1-正常2-注销
     */
    @TransfersNodeIn(value = TransfersNodeType.sstatus4, desc = "运行状态")
    @TransfersNodeOut(value = TransfersNodeType.sstatus4, desc = "运行状态")
    private String status;
    /**
     * 端口总数
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol5, desc = "端口总数")
    @TransfersNodeOut(value = TransfersNodeType.lvol5, desc = "端口总数")
    private Integer svrportcnt;
    /**
     * 服务器接口编号（服务器端口号）
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol3, desc = "服务器端口号")
    @TransfersNodeOut(value = TransfersNodeType.lvol3, desc = "服务器端口号")
    private Integer svrportno;
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
     * 服务器SOCKET端口号（通讯端口号）
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol7, desc = "通讯端口号")
    @TransfersNodeOut(value = TransfersNodeType.lvol7, desc = "通讯端口号")
    private Integer portno;
    /**
     * 波特率
     */
    private Integer baudrate;
    /**
     * 终端允许使用的卡收费类别
     */
    private String cardset;
    /**
     * 卡黑名单版本号
     */
    @TransfersNodeOut(value = TransfersNodeType.sserial4, desc = "卡黑名单版本号")
    private String cardverno;
    /**
     * 上次设备交易流水号
     */
    private Integer lastseqno;
    /**
     * 上次交易时间
     */
    private String lasttranstime;
    /**
     * 设备读卡的钱包号
     */
    private Integer purseno;
    /**
     * 最大充值限额，单位分
     */
    private Double maxamt;
    /**
     * 子系统ID
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol2, desc = "子系统ID")
    @TransfersNodeOut(value = TransfersNodeType.lvol2, desc = "子系统ID")
    private Integer sysid;
    /**
     * 区域代码
     */
    @TransfersNodeIn(value = TransfersNodeType.scust_type, desc = "区域代码")
    @TransfersNodeOut(value = TransfersNodeType.scust_type, desc = "区域代码")
    private String areacode;
    /**
     * 用于记录已经记录消息队列的名单版本
     */
    private String doorlstver;
    /**
     * 设备用途
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol0, desc = "设备用途")
    @TransfersNodeOut(value = TransfersNodeType.lvol0, desc = "设备用途")
    private Integer devusage;
    /**
     * 注册日期
     */
    private String opendate;
    /**
     * 注销日期
     */
    private String closedate;
    /**
     * 导入批次号
     */
    @TransfersNodeIn(value = TransfersNodeType.sphone, desc = "导入批次号")
    @TransfersNodeOut(value = TransfersNodeType.sphone, desc = "导入批次号")
    private String batchno;
    /**
     * 上次修改日期
     */
    private String lastsaved;
    /**
     * 备注
     */
    @TransfersNodeOut(value = TransfersNodeType.vsmess, desc = "备注")
    private String remark;

    public void setDeviceid(Integer deviceid) {
        this.deviceid = deviceid;
    }

    public Integer getDeviceid() {
        return this.deviceid;
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

    public void setDeviceno(Integer deviceno) {
        this.deviceno = deviceno;
    }

    public Integer getDeviceno() {
        return this.deviceno;
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

    public void setDevverno(String devverno) {
        this.devverno = devverno;
    }

    public String getDevverno() {
        return this.devverno;
    }

    public void setCardphytype(String cardphytype) {
        this.cardphytype = cardphytype;
    }

    public String getCardphytype() {
        return this.cardphytype;
    }

    public void setFdeviceid(Integer fdeviceid) {
        this.fdeviceid = fdeviceid;
    }

    public Integer getFdeviceid() {
        return this.fdeviceid;
    }

    public void setRunstatus(Integer runstatus) {
        this.runstatus = runstatus;
    }

    public Integer getRunstatus() {
        return this.runstatus;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getStatus() {
        return this.status;
    }

    public void setSvrportcnt(Integer svrportcnt) {
        this.svrportcnt = svrportcnt;
    }

    public Integer getSvrportcnt() {
        return this.svrportcnt;
    }

    public void setSvrportno(Integer svrportno) {
        this.svrportno = svrportno;
    }

    public Integer getSvrportno() {
        return this.svrportno;
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

    public void setBaudrate(Integer baudrate) {
        this.baudrate = baudrate;
    }

    public Integer getBaudrate() {
        return this.baudrate;
    }

    public void setCardset(String cardset) {
        this.cardset = cardset;
    }

    public String getCardset() {
        return this.cardset;
    }

    public void setCardverno(String cardverno) {
        this.cardverno = cardverno;
    }

    public String getCardverno() {
        return this.cardverno;
    }

    public void setLastseqno(Integer lastseqno) {
        this.lastseqno = lastseqno;
    }

    public Integer getLastseqno() {
        return this.lastseqno;
    }

    public void setLasttranstime(String lasttranstime) {
        this.lasttranstime = lasttranstime;
    }

    public String getLasttranstime() {
        return this.lasttranstime;
    }

    public void setPurseno(Integer purseno) {
        this.purseno = purseno;
    }

    public Integer getPurseno() {
        return this.purseno;
    }

    public void setMaxamt(Double maxamt) {
        this.maxamt = maxamt;
    }

    public Double getMaxamt() {
        return this.maxamt;
    }

    public void setSysid(Integer sysid) {
        this.sysid = sysid;
    }

    public Integer getSysid() {
        return this.sysid;
    }

    public void setAreacode(String areacode) {
        this.areacode = areacode;
    }

    public String getAreacode() {
        return this.areacode;
    }

    public void setDoorlstver(String doorlstver) {
        this.doorlstver = doorlstver;
    }

    public String getDoorlstver() {
        return this.doorlstver;
    }

    public void setDevusage(Integer devusage) {
        this.devusage = devusage;
    }

    public Integer getDevusage() {
        return this.devusage;
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

    public void setBatchno(String batchno) {
        this.batchno = batchno;
    }

    public String getBatchno() {
        return this.batchno;
    }

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }

    public void setRemark(String remark) {
        this.remark = remark;
    }

    public String getRemark() {
        return this.remark;
    }
}