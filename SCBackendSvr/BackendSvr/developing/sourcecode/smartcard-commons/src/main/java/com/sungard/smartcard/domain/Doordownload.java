package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_DOORDOWNLOAD的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Doordownload implements Serializable {

    /**
     * 编号
     */
    private Integer id;
    /**
     * 名单版本号
     */
    private String cardverno;
    /**
     * 客户号
     */
    private Integer custid;
    /**
     *
     */
    private Integer ctrlid;
    /**
     *
     */
    private Integer sysid;
    /**
     * 交易卡号
     */
    private Integer cardno;
    /**
     * 卡物理ID
     */
    private String cardphyid;
    /**
     * 权限
     */
    private String rightbit;
    /**
     *
     */
    private Integer cardseqno;
    /**
     *
     */
    private Integer weekid;
    /**
     *
     */
    private Integer weekseqno;
    /**
     *
     */
    private Integer holidayid;
    /**
     *
     */
    private Integer holidayseqno;
    /**
     *
     */
    private String createtime;
    /**
     *
     */
    private String succtime;
    /**
     * 状态
     */
    private Integer status;
    /**
     * 增删标志
     */
    private Integer adddelflag;
    /**
     *
     */
    private Integer doorcount;

    public void setId(Integer id) {
        this.id = id;
    }

    public Integer getId() {
        return this.id;
    }

    public void setCardverno(String cardverno) {
        this.cardverno = cardverno;
    }

    public String getCardverno() {
        return this.cardverno;
    }

    public void setCustid(Integer custid) {
        this.custid = custid;
    }

    public Integer getCustid() {
        return this.custid;
    }

    public void setCtrlid(Integer ctrlid) {
        this.ctrlid = ctrlid;
    }

    public Integer getCtrlid() {
        return this.ctrlid;
    }

    public void setSysid(Integer sysid) {
        this.sysid = sysid;
    }

    public Integer getSysid() {
        return this.sysid;
    }

    public void setCardno(Integer cardno) {
        this.cardno = cardno;
    }

    public Integer getCardno() {
        return this.cardno;
    }

    public void setCardphyid(String cardphyid) {
        this.cardphyid = cardphyid;
    }

    public String getCardphyid() {
        return this.cardphyid;
    }

    public void setRightbit(String rightbit) {
        this.rightbit = rightbit;
    }

    public String getRightbit() {
        return this.rightbit;
    }

    public void setCardseqno(Integer cardseqno) {
        this.cardseqno = cardseqno;
    }

    public Integer getCardseqno() {
        return this.cardseqno;
    }

    public void setWeekid(Integer weekid) {
        this.weekid = weekid;
    }

    public Integer getWeekid() {
        return this.weekid;
    }

    public void setWeekseqno(Integer weekseqno) {
        this.weekseqno = weekseqno;
    }

    public Integer getWeekseqno() {
        return this.weekseqno;
    }

    public void setHolidayid(Integer holidayid) {
        this.holidayid = holidayid;
    }

    public Integer getHolidayid() {
        return this.holidayid;
    }

    public void setHolidayseqno(Integer holidayseqno) {
        this.holidayseqno = holidayseqno;
    }

    public Integer getHolidayseqno() {
        return this.holidayseqno;
    }

    public void setCreatetime(String createtime) {
        this.createtime = createtime;
    }

    public String getCreatetime() {
        return this.createtime;
    }

    public void setSucctime(String succtime) {
        this.succtime = succtime;
    }

    public String getSucctime() {
        return this.succtime;
    }

    public void setStatus(Integer status) {
        this.status = status;
    }

    public Integer getStatus() {
        return this.status;
    }

    public void setAdddelflag(Integer adddelflag) {
        this.adddelflag = adddelflag;
    }

    public Integer getAdddelflag() {
        return this.adddelflag;
    }

    public void setDoorcount(Integer doorcount) {
        this.doorcount = doorcount;
    }

    public Integer getDoorcount() {
        return this.doorcount;
    }
}