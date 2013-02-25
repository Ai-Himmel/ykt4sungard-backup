package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;
import com.sungard.smartcard.annotation.TransfersNodeIn;
import com.sungard.smartcard.annotation.TransfersNodeOut;
import com.sungard.smartcard.annotation.TransfersNodeType;

import java.io.Serializable;

/**
 * T_DPSOPER的实体类
 * 充值操作员表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Dpsoper implements Serializable {

    /**
     * 操作员号
     */
    @TransfersNodeIn(value = TransfersNodeType.saddr, desc = "操作员编号")
    @TransfersNodeOut(value = TransfersNodeType.saddr, desc = "操作员编号")
    private String opercode;
    /**
     * 使用限制标志
     */
    private String devlimitflag;
    /**
     * 充值商户操作员标志
     */
    @TransfersNodeIn(value = TransfersNodeType.saddr2, desc = "充值商户操作员标志")
    private String shopoperflag;
    /**
     * 状态
     */
    private String status;
    /**
     * 开户日期
     */
    private String opendate;
    /**
     * 注销日期
     */
    private String closedate;
    /**
     * 最大充值金额
     */
    private Double maxdepositamt;
    /**
     * 总充值次数
     */
    private Integer depositcnt;
    /**
     * 总充值金额
     */
    private Double depositamt;
    /**
     * 最后充值日期
     */
    private String lasttransdate;
    /**
     * 最后充值设备物理ID
     */
    private String lastdevphyid;
    /**
     * 上次设备流水号
     */
    private Integer lastdevseqno;
    /**
     * 充值批次号
     */
    private Integer batchno;
    /**
     * 授权码
     */
    private Integer authcode;
    /**
     * 设备物理ID
     */
    private String devphyid;
    /**
     * 最后保存时间
     */
    private String lastsaved;

    public void setOpercode(String opercode) {
        this.opercode = opercode;
    }

    public String getOpercode() {
        return this.opercode;
    }

    public void setDevlimitflag(String devlimitflag) {
        this.devlimitflag = devlimitflag;
    }

    public String getDevlimitflag() {
        return this.devlimitflag;
    }

    public void setShopoperflag(String shopoperflag) {
        this.shopoperflag = shopoperflag;
    }

    public String getShopoperflag() {
        return this.shopoperflag;
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

    public void setMaxdepositamt(Double maxdepositamt) {
        this.maxdepositamt = maxdepositamt;
    }

    public Double getMaxdepositamt() {
        return this.maxdepositamt;
    }

    public void setDepositcnt(Integer depositcnt) {
        this.depositcnt = depositcnt;
    }

    public Integer getDepositcnt() {
        return this.depositcnt;
    }

    public void setDepositamt(Double depositamt) {
        this.depositamt = depositamt;
    }

    public Double getDepositamt() {
        return this.depositamt;
    }

    public void setLasttransdate(String lasttransdate) {
        this.lasttransdate = lasttransdate;
    }

    public String getLasttransdate() {
        return this.lasttransdate;
    }

    public void setLastdevphyid(String lastdevphyid) {
        this.lastdevphyid = lastdevphyid;
    }

    public String getLastdevphyid() {
        return this.lastdevphyid;
    }

    public void setLastdevseqno(Integer lastdevseqno) {
        this.lastdevseqno = lastdevseqno;
    }

    public Integer getLastdevseqno() {
        return this.lastdevseqno;
    }

    public void setBatchno(Integer batchno) {
        this.batchno = batchno;
    }

    public Integer getBatchno() {
        return this.batchno;
    }

    public void setAuthcode(Integer authcode) {
        this.authcode = authcode;
    }

    public Integer getAuthcode() {
        return this.authcode;
    }

    public void setDevphyid(String devphyid) {
        this.devphyid = devphyid;
    }

    public String getDevphyid() {
        return this.devphyid;
    }

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }
}