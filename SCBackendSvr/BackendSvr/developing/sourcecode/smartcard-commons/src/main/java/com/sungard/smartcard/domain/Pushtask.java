package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_PUSHTASK的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Pushtask implements Serializable {

    /**
     * 任务号
     */
    private Integer taskid;
    /**
     * 任务序号
     */
    private Integer taskseq;
    /**
     *
     */
    private Integer funcno;
    /**
     *
     */
    private Integer funcgroup;
    /**
     *
     */
    private Integer sysid;
    /**
     * 设备编号
     */
    private Integer deviceid;
    /**
     *
     */
    private String addtime;
    /**
     *
     */
    private String begintime;
    /**
     *
     */
    private String invalidtime;
    /**
     *
     */
    private String exectime;
    /**
     *
     */
    private Integer execcnt;
    /**
     *
     */
    private Integer maxexec;
    /**
     *
     */
    private Integer nextinterval;
    /**
     *
     */
    private Integer status;
    /**
     *
     */
    private String flag;
    /**
     *
     */
    private Integer sendtype;
    /**
     *
     */
    private Integer routeid;
    /**
     *
     */
    private String contentstr;
    /**
     *
     */
    private String retcode;
    /**
     *
     */
    private String retmsg;

    public void setTaskid(Integer taskid) {
        this.taskid = taskid;
    }

    public Integer getTaskid() {
        return this.taskid;
    }

    public void setTaskseq(Integer taskseq) {
        this.taskseq = taskseq;
    }

    public Integer getTaskseq() {
        return this.taskseq;
    }

    public void setFuncno(Integer funcno) {
        this.funcno = funcno;
    }

    public Integer getFuncno() {
        return this.funcno;
    }

    public void setFuncgroup(Integer funcgroup) {
        this.funcgroup = funcgroup;
    }

    public Integer getFuncgroup() {
        return this.funcgroup;
    }

    public void setSysid(Integer sysid) {
        this.sysid = sysid;
    }

    public Integer getSysid() {
        return this.sysid;
    }

    public void setDeviceid(Integer deviceid) {
        this.deviceid = deviceid;
    }

    public Integer getDeviceid() {
        return this.deviceid;
    }

    public void setAddtime(String addtime) {
        this.addtime = addtime;
    }

    public String getAddtime() {
        return this.addtime;
    }

    public void setBegintime(String begintime) {
        this.begintime = begintime;
    }

    public String getBegintime() {
        return this.begintime;
    }

    public void setInvalidtime(String invalidtime) {
        this.invalidtime = invalidtime;
    }

    public String getInvalidtime() {
        return this.invalidtime;
    }

    public void setExectime(String exectime) {
        this.exectime = exectime;
    }

    public String getExectime() {
        return this.exectime;
    }

    public void setExeccnt(Integer execcnt) {
        this.execcnt = execcnt;
    }

    public Integer getExeccnt() {
        return this.execcnt;
    }

    public void setMaxexec(Integer maxexec) {
        this.maxexec = maxexec;
    }

    public Integer getMaxexec() {
        return this.maxexec;
    }

    public void setNextinterval(Integer nextinterval) {
        this.nextinterval = nextinterval;
    }

    public Integer getNextinterval() {
        return this.nextinterval;
    }

    public void setStatus(Integer status) {
        this.status = status;
    }

    public Integer getStatus() {
        return this.status;
    }

    public void setFlag(String flag) {
        this.flag = flag;
    }

    public String getFlag() {
        return this.flag;
    }

    public void setSendtype(Integer sendtype) {
        this.sendtype = sendtype;
    }

    public Integer getSendtype() {
        return this.sendtype;
    }

    public void setRouteid(Integer routeid) {
        this.routeid = routeid;
    }

    public Integer getRouteid() {
        return this.routeid;
    }

    public void setContentstr(String contentstr) {
        this.contentstr = contentstr;
    }

    public String getContentstr() {
        return this.contentstr;
    }

    public void setRetcode(String retcode) {
        this.retcode = retcode;
    }

    public String getRetcode() {
        return this.retcode;
    }

    public void setRetmsg(String retmsg) {
        this.retmsg = retmsg;
    }

    public String getRetmsg() {
        return this.retmsg;
    }
}