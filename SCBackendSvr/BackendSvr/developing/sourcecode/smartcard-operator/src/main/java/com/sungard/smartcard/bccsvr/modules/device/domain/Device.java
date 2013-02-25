package com.sungard.smartcard.bccsvr.modules.device.domain;

import com.sungard.smartcard.annotation.TransfersElement;
import com.sungard.smartcard.annotation.TransfersNodeAll;
import com.sungard.smartcard.annotation.TransfersNodeIn;
import com.sungard.smartcard.annotation.TransfersNodeOut;
import com.sungard.smartcard.annotation.TransfersNodeType;

import java.io.Serializable;
import java.math.BigDecimal;

/**
 * @author Yiming.You
 * @version v1.00
 */
@TransfersElement
public class Device implements Serializable {
    @TransfersNodeIn(value = TransfersNodeType.lvol0, desc = "")
    private Integer deviceid;

    @TransfersNodeIn(value = TransfersNodeType.saddr, desc = "")
    private String devicename;

    @TransfersNodeOut(value = TransfersNodeType.saddr2, desc = "")
    private String devphyid;

    @TransfersNodeOut(value = TransfersNodeType.lvol1, desc = "")
    private Integer deviceno;

    @TransfersNodeAll(value = TransfersNodeType.lvol10, desc = "")
    private Integer devphytype;

    @TransfersNodeAll(value = TransfersNodeType.sall_name, desc = "")
    private String devtypecode;

    @TransfersNodeAll(value = TransfersNodeType.sbank_acc, desc = "")
    private String devverno;

    @TransfersNodeAll(value = TransfersNodeType.sbank_acc2, desc = "")
    private String cardphytype;

    @TransfersNodeAll(value = TransfersNodeType.lvol11, desc = "")
    private Integer fdeviceid;

    @TransfersNodeAll(value = TransfersNodeType.lvol12, desc = "")
    private Integer runstatus;

    @TransfersNodeAll(value = TransfersNodeType.sbank_code, desc = "")
    private String status;

    @TransfersNodeAll(value = TransfersNodeType.lvol2, desc = "")
    private Integer svrportcnt;

    @TransfersNodeAll(value = TransfersNodeType.lvol3, desc = "")
    private Integer svrportno;

    @TransfersNodeAll(value = TransfersNodeType.lvol4, desc = "")
    private Integer commtype;

    @TransfersNodeAll(value = TransfersNodeType.sbank_code2, desc = "")
    private String ip;

    @TransfersNodeAll(value = TransfersNodeType.lvol5, desc = "")
    private Integer portno;

    @TransfersNodeAll(value = TransfersNodeType.lvol6, desc = "")
    private Integer baudrate;

    @TransfersNodeAll(value = TransfersNodeType.sbank_pwd, desc = "")
    private String cardset;

    @TransfersNodeAll(value = TransfersNodeType.sbank_pwd2, desc = "")
    private String cardverno;

    @TransfersNodeAll(value = TransfersNodeType.lvol7, desc = "")
    private Integer lastseqno;

    @TransfersNodeAll(value = TransfersNodeType.sbankname, desc = "")
    private String lasttranstime;

    @TransfersNodeAll(value = TransfersNodeType.lvol8, desc = "")
    private Integer purseno;

    @TransfersNodeAll(value = TransfersNodeType.damt0, desc = "")
    private BigDecimal maxamt;

    @TransfersNodeAll(value = TransfersNodeType.lvol9, desc = "")
    private Integer sysid;

    @TransfersNodeAll(value = TransfersNodeType.sbankname2, desc = "")
    private String areacode;

    @TransfersNodeAll(value = TransfersNodeType.sbranch_code0, desc = "")
    private String doorlstver;

    @TransfersNodeAll(value = TransfersNodeType.lbank_acc_type, desc = "")
    private Integer devusage;

    @TransfersNodeAll(value = TransfersNodeType.sbranch_code1, desc = "")
    private String opendate;

    @TransfersNodeAll(value = TransfersNodeType.sbranch_code2, desc = "")
    private String closedate;

    @TransfersNodeAll(value = TransfersNodeType.scard0, desc = "")
    private String batchno;

    @TransfersNodeAll(value = TransfersNodeType.sbank_code2, desc = "")
    private String lastsaved;

    @TransfersNodeAll(value = TransfersNodeType.sbranch_code0, desc = "")
    private String remark;

    public Integer getDeviceid() {
        return deviceid;
    }

    public void setDeviceid(Integer deviceid) {
        this.deviceid = deviceid;
    }

    public String getDevicename() {
        return devicename;
    }

    public void setDevicename(String devicename) {
        this.devicename = devicename == null ? null : devicename.trim();
    }

    public String getDevphyid() {
        return devphyid;
    }

    public void setDevphyid(String devphyid) {
        this.devphyid = devphyid == null ? null : devphyid.trim();
    }

    public Integer getDeviceno() {
        return deviceno;
    }

    public void setDeviceno(Integer deviceno) {
        this.deviceno = deviceno;
    }

    public Integer getDevphytype() {
        return devphytype;
    }

    public void setDevphytype(Integer devphytype) {
        this.devphytype = devphytype;
    }

    public String getDevtypecode() {
        return devtypecode;
    }

    public void setDevtypecode(String devtypecode) {
        this.devtypecode = devtypecode == null ? null : devtypecode.trim();
    }

    public String getDevverno() {
        return devverno;
    }

    public void setDevverno(String devverno) {
        this.devverno = devverno == null ? null : devverno.trim();
    }

    public String getCardphytype() {
        return cardphytype;
    }

    public void setCardphytype(String cardphytype) {
        this.cardphytype = cardphytype == null ? null : cardphytype.trim();
    }

    public Integer getFdeviceid() {
        return fdeviceid;
    }

    public void setFdeviceid(Integer fdeviceid) {
        this.fdeviceid = fdeviceid;
    }

    public Integer getRunstatus() {
        return runstatus;
    }

    public void setRunstatus(Integer runstatus) {
        this.runstatus = runstatus;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status == null ? null : status.trim();
    }

    public Integer getSvrportcnt() {
        return svrportcnt;
    }

    public void setSvrportcnt(Integer svrportcnt) {
        this.svrportcnt = svrportcnt;
    }

    public Integer getSvrportno() {
        return svrportno;
    }

    public void setSvrportno(Integer svrportno) {
        this.svrportno = svrportno;
    }

    public Integer getCommtype() {
        return commtype;
    }

    public void setCommtype(Integer commtype) {
        this.commtype = commtype;
    }

    public String getIp() {
        return ip;
    }

    public void setIp(String ip) {
        this.ip = ip == null ? null : ip.trim();
    }

    public Integer getPortno() {
        return portno;
    }

    public void setPortno(Integer portno) {
        this.portno = portno;
    }

    public Integer getBaudrate() {
        return baudrate;
    }

    public void setBaudrate(Integer baudrate) {
        this.baudrate = baudrate;
    }

    public String getCardset() {
        return cardset;
    }

    public void setCardset(String cardset) {
        this.cardset = cardset == null ? null : cardset.trim();
    }

    public String getCardverno() {
        return cardverno;
    }

    public void setCardverno(String cardverno) {
        this.cardverno = cardverno == null ? null : cardverno.trim();
    }

    public Integer getLastseqno() {
        return lastseqno;
    }

    public void setLastseqno(Integer lastseqno) {
        this.lastseqno = lastseqno;
    }

    public String getLasttranstime() {
        return lasttranstime;
    }

    public void setLasttranstime(String lasttranstime) {
        this.lasttranstime = lasttranstime == null ? null : lasttranstime.trim();
    }

    public Integer getPurseno() {
        return purseno;
    }

    public void setPurseno(Integer purseno) {
        this.purseno = purseno;
    }

    public BigDecimal getMaxamt() {
        return maxamt;
    }

    public void setMaxamt(BigDecimal maxamt) {
        this.maxamt = maxamt;
    }

    public Integer getSysid() {
        return sysid;
    }

    public void setSysid(Integer sysid) {
        this.sysid = sysid;
    }

    public String getAreacode() {
        return areacode;
    }

    public void setAreacode(String areacode) {
        this.areacode = areacode == null ? null : areacode.trim();
    }

    public String getDoorlstver() {
        return doorlstver;
    }

    public void setDoorlstver(String doorlstver) {
        this.doorlstver = doorlstver == null ? null : doorlstver.trim();
    }

    public Integer getDevusage() {
        return devusage;
    }

    public void setDevusage(Integer devusage) {
        this.devusage = devusage;
    }

    public String getOpendate() {
        return opendate;
    }

    public void setOpendate(String opendate) {
        this.opendate = opendate == null ? null : opendate.trim();
    }

    public String getClosedate() {
        return closedate;
    }

    public void setClosedate(String closedate) {
        this.closedate = closedate == null ? null : closedate.trim();
    }

    public String getBatchno() {
        return batchno;
    }

    public void setBatchno(String batchno) {
        this.batchno = batchno == null ? null : batchno.trim();
    }

    public String getLastsaved() {
        return lastsaved;
    }

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved == null ? null : lastsaved.trim();
    }

    public String getRemark() {
        return remark;
    }

    public void setRemark(String remark) {
        this.remark = remark == null ? null : remark.trim();
    }
}
