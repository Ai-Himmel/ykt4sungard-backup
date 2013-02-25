package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_SUBSYSPARA的实体类
 * 子系统参数表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Subsyspara implements Serializable {

    /**
     * 子系统ID
     */
    private Integer sysid;
    /**
     * 工作模式
     */
    private String workmode;
    /**
     * 心跳间隔
     */
    private Integer beatinterval;
    /**
     * 心跳次数限制
     */
    private Integer beatcntlimit;
    /**
     * 心跳发送功能号
     */
    private Integer reqbeatfuncno;
    /**
     * 请求设备信息功能号
     */
    private Integer reqdevfuncno;
    /**
     * 请求任务功能号
     */
    private Integer reqtaskfuncno;
    /**
     * 应答功能号
     */
    private Integer respfuncno;
    /**
     * 执行超时时间
     */
    private Integer exectimeout;
    /**
     * 采集间隔
     */
    private Integer colinterval;
    /**
     * 查询任务间隔
     */
    private Integer qryinterval;
    /**
     * 任务最大限制
     */
    private Integer taskmaxlimit;
    /**
     * 通讯平台节点号
     */
    private Integer bccdrtpno;
    /**
     * 通讯平台IP
     */
    private String bccdrtpip;
    /**
     * 通讯平台端口
     */
    private Integer bccdrtpport;
    /**
     * 主功能号
     */
    private Integer bccmainfuncno;
    /**
     * 轮询时间间隔（单位：毫秒）
     */
    private Integer bccinterval;

    public void setSysid(Integer sysid) {
        this.sysid = sysid;
    }

    public Integer getSysid() {
        return this.sysid;
    }

    public void setWorkmode(String workmode) {
        this.workmode = workmode;
    }

    public String getWorkmode() {
        return this.workmode;
    }

    public void setBeatinterval(Integer beatinterval) {
        this.beatinterval = beatinterval;
    }

    public Integer getBeatinterval() {
        return this.beatinterval;
    }

    public void setBeatcntlimit(Integer beatcntlimit) {
        this.beatcntlimit = beatcntlimit;
    }

    public Integer getBeatcntlimit() {
        return this.beatcntlimit;
    }

    public void setReqbeatfuncno(Integer reqbeatfuncno) {
        this.reqbeatfuncno = reqbeatfuncno;
    }

    public Integer getReqbeatfuncno() {
        return this.reqbeatfuncno;
    }

    public void setReqdevfuncno(Integer reqdevfuncno) {
        this.reqdevfuncno = reqdevfuncno;
    }

    public Integer getReqdevfuncno() {
        return this.reqdevfuncno;
    }

    public void setReqtaskfuncno(Integer reqtaskfuncno) {
        this.reqtaskfuncno = reqtaskfuncno;
    }

    public Integer getReqtaskfuncno() {
        return this.reqtaskfuncno;
    }

    public void setRespfuncno(Integer respfuncno) {
        this.respfuncno = respfuncno;
    }

    public Integer getRespfuncno() {
        return this.respfuncno;
    }

    public void setExectimeout(Integer exectimeout) {
        this.exectimeout = exectimeout;
    }

    public Integer getExectimeout() {
        return this.exectimeout;
    }

    public void setColinterval(Integer colinterval) {
        this.colinterval = colinterval;
    }

    public Integer getColinterval() {
        return this.colinterval;
    }

    public void setQryinterval(Integer qryinterval) {
        this.qryinterval = qryinterval;
    }

    public Integer getQryinterval() {
        return this.qryinterval;
    }

    public void setTaskmaxlimit(Integer taskmaxlimit) {
        this.taskmaxlimit = taskmaxlimit;
    }

    public Integer getTaskmaxlimit() {
        return this.taskmaxlimit;
    }

    public void setBccdrtpno(Integer bccdrtpno) {
        this.bccdrtpno = bccdrtpno;
    }

    public Integer getBccdrtpno() {
        return this.bccdrtpno;
    }

    public void setBccdrtpip(String bccdrtpip) {
        this.bccdrtpip = bccdrtpip;
    }

    public String getBccdrtpip() {
        return this.bccdrtpip;
    }

    public void setBccdrtpport(Integer bccdrtpport) {
        this.bccdrtpport = bccdrtpport;
    }

    public Integer getBccdrtpport() {
        return this.bccdrtpport;
    }

    public void setBccmainfuncno(Integer bccmainfuncno) {
        this.bccmainfuncno = bccmainfuncno;
    }

    public Integer getBccmainfuncno() {
        return this.bccmainfuncno;
    }

    public void setBccinterval(Integer bccinterval) {
        this.bccinterval = bccinterval;
    }

    public Integer getBccinterval() {
        return this.bccinterval;
    }
}