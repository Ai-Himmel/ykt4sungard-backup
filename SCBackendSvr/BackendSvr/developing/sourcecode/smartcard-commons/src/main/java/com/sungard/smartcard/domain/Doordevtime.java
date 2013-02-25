package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_DOORDEVTIME的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Doordevtime implements Serializable {

    /**
     *
     */
    private Integer majordevid;
    /**
     *
     */
    private Integer minordevid;
    /**
     * 时间段ID
     */
    private Integer timeid;
    /**
     * 序号
     */
    private Integer seqno;
    /**
     * 增删标志
     */
    private Integer adddelflag;
    /**
     * 下传状态
     */
    private Integer downstatus;
    /**
     * 下传时间
     */
    private String downtime;
    /**
     *
     */
    private Integer refcnt;
    /**
     *
     */
    private String updatetime;

    public void setMajordevid(Integer majordevid) {
        this.majordevid = majordevid;
    }

    public Integer getMajordevid() {
        return this.majordevid;
    }

    public void setMinordevid(Integer minordevid) {
        this.minordevid = minordevid;
    }

    public Integer getMinordevid() {
        return this.minordevid;
    }

    public void setTimeid(Integer timeid) {
        this.timeid = timeid;
    }

    public Integer getTimeid() {
        return this.timeid;
    }

    public void setSeqno(Integer seqno) {
        this.seqno = seqno;
    }

    public Integer getSeqno() {
        return this.seqno;
    }

    public void setAdddelflag(Integer adddelflag) {
        this.adddelflag = adddelflag;
    }

    public Integer getAdddelflag() {
        return this.adddelflag;
    }

    public void setDownstatus(Integer downstatus) {
        this.downstatus = downstatus;
    }

    public Integer getDownstatus() {
        return this.downstatus;
    }

    public void setDowntime(String downtime) {
        this.downtime = downtime;
    }

    public String getDowntime() {
        return this.downtime;
    }

    public void setRefcnt(Integer refcnt) {
        this.refcnt = refcnt;
    }

    public Integer getRefcnt() {
        return this.refcnt;
    }

    public void setUpdatetime(String updatetime) {
        this.updatetime = updatetime;
    }

    public String getUpdatetime() {
        return this.updatetime;
    }
}