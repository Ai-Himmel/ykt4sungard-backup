package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_SUBSYSTEM的实体类
 * 子系统表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Subsystem implements Serializable {

    /**
     * 子系统ID
     */
    private Integer sysid;
    /**
     * 子系统名称
     */
    private String sysname;
    /**
     * 子系统类别
     */
    private Integer systype;
    /**
     * 区域代码
     */
    private String areacode;
    /**
     *
     */
    private Integer serverid;
    /**
     *
     */
    private String macaddr;
    /**
     *
     */
    private String ip;
    /**
     *
     */
    private Integer port;
    /**
     * 卡版本号
     */
    private String cardverno;
    /**
     *
     */
    private String initkey;
    /**
     *
     */
    private String dynakey;
    /**
     *
     */
    private String synctime;
    /**
     * 运行状态
     */
    private Integer runstatus;
    /**
     *
     */
    private String status;
    /**
     * 注册日期
     */
    private String opendate;
    /**
     * 注销日期
     */
    private String closedate;
    /**
     * 备注
     */
    private String remark;

    public void setSysid(Integer sysid) {
        this.sysid = sysid;
    }

    public Integer getSysid() {
        return this.sysid;
    }

    public void setSysname(String sysname) {
        this.sysname = sysname;
    }

    public String getSysname() {
        return this.sysname;
    }

    public void setSystype(Integer systype) {
        this.systype = systype;
    }

    public Integer getSystype() {
        return this.systype;
    }

    public void setAreacode(String areacode) {
        this.areacode = areacode;
    }

    public String getAreacode() {
        return this.areacode;
    }

    public void setServerid(Integer serverid) {
        this.serverid = serverid;
    }

    public Integer getServerid() {
        return this.serverid;
    }

    public void setMacaddr(String macaddr) {
        this.macaddr = macaddr;
    }

    public String getMacaddr() {
        return this.macaddr;
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

    public void setCardverno(String cardverno) {
        this.cardverno = cardverno;
    }

    public String getCardverno() {
        return this.cardverno;
    }

    public void setInitkey(String initkey) {
        this.initkey = initkey;
    }

    public String getInitkey() {
        return this.initkey;
    }

    public void setDynakey(String dynakey) {
        this.dynakey = dynakey;
    }

    public String getDynakey() {
        return this.dynakey;
    }

    public void setSynctime(String synctime) {
        this.synctime = synctime;
    }

    public String getSynctime() {
        return this.synctime;
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

    public void setRemark(String remark) {
        this.remark = remark;
    }

    public String getRemark() {
        return this.remark;
    }
}