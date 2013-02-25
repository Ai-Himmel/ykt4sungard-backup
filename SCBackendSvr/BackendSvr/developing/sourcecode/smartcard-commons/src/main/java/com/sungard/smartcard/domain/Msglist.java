package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;
import com.sungard.smartcard.annotation.TransfersNodeIn;
import com.sungard.smartcard.annotation.TransfersNodeOut;
import com.sungard.smartcard.annotation.TransfersNodeType;

import java.io.Serializable;

/**
 * T_MSGLIST的实体类
 * 消息队列表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Msglist implements Serializable {

    /**
     * 消息ID
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol0, desc = "消息ID")//4
    @TransfersNodeOut(value = TransfersNodeType.lvol0, desc = "消息ID")
    private Integer msgid;
    /**
     * 消息类型
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol1, desc = "消息类型")//4
    @TransfersNodeOut(value = TransfersNodeType.lvol1, desc = "消息类型")//4
    private Integer msgtype;
    /**
     * 消息级别
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol2, desc = "消息级别")//4
    @TransfersNodeOut(value = TransfersNodeType.lvol2, desc = "消息级别")
    private Integer msglevel;
    /**
     * 子系统编号
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol3, desc = "子系统编号")//4
    @TransfersNodeOut(value = TransfersNodeType.lvol3, desc = "子系统编号")
    private Integer sysid;
    /**
     * 设备编号
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol4, desc = "设备编号")//4
    @TransfersNodeOut(value = TransfersNodeType.lvol4, desc = "设备编号")
    private Integer deviceid;
    /**
     * 交易卡号
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol5, desc = "交易卡号")//4
    @TransfersNodeOut(value = TransfersNodeType.lvol5, desc = "交易卡号")//4
    private Integer cardno;
    /**
     * 交易日期 8
     */
    @TransfersNodeIn(value = TransfersNodeType.sdate0, desc = "交易日期")
    @TransfersNodeOut(value = TransfersNodeType.sdate0, desc = "交易日期")//9
    private String transdate;
    /**
     * 消息生成时间 30
     */
    @TransfersNodeOut(value = TransfersNodeType.sphone, desc = "消息生成时间")//31
    private String createdtime;
    /**
     * 消息开始处理时间30
     */
    @TransfersNodeIn(value = TransfersNodeType.sphone2, desc = "消息开始处理时间")
    @TransfersNodeOut(value = TransfersNodeType.sphone2, desc = "消息开始处理时间")//31
    private String starttime;
    /**
     * 消息处理完成时间30
     */
    @TransfersNodeIn(value = TransfersNodeType.sphone3, desc = "消息处理完成时间")
    @TransfersNodeOut(value = TransfersNodeType.sphone3, desc = "消息处理完成时间")//31
    private String endtime;
    /**
     * 消息请求内容1000
     */
    @TransfersNodeOut(value = TransfersNodeType.vsvarstr0, desc = "消息请求内容")//256
    private String reqdata;
    /**
     * 消息应答内容1000
     */
    @TransfersNodeOut(value = TransfersNodeType.vsvarstr1, desc = "消息应答内容")//256
    private String respdata;
    /**
     * 功能号
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol6, desc = "功能号")
    @TransfersNodeOut(value = TransfersNodeType.lvol6, desc = "功能号")//4
    private Integer funcno;
    /**
     * 父功能号
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol7, desc = "父功能号")
    @TransfersNodeOut(value = TransfersNodeType.lvol7, desc = "父功能号")//4
    private Integer pfuncno;
    /**
     * 最大发送次数
     */
    @TransfersNodeOut(value = TransfersNodeType.lvol8, desc = "最大发送次数")//4
    private Integer maxsendcnt;
    /**
     * 发送次数
     */
    @TransfersNodeOut(value = TransfersNodeType.lvol9, desc = "发送次数")//4
    private Integer sendcnt;
    /**
     * 接收次数
     */
    @TransfersNodeOut(value = TransfersNodeType.lvol10, desc = "接收次数")//4
    private Integer recvcnt;
    /**
     * 消息状态 number(1)
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol11, desc = "消息状态 ")//4
    @TransfersNodeOut(value = TransfersNodeType.lvol11, desc = "消息状态 ")
    private Integer status;
    /**
     * 序号
     */
    @TransfersNodeOut(value = TransfersNodeType.lvol12, desc = "序号 ")//4
    private Integer seqno;
    /**
     * 操作员号 8
     */
    @TransfersNodeIn(value = TransfersNodeType.scust_no, desc = "操作员号")//4
    @TransfersNodeOut(value = TransfersNodeType.scust_no, desc = "操作员号 ")//4
    private String opercode;
    /**
     * 错误码
     */
    @TransfersNodeIn(value = TransfersNodeType.lcert_code, desc = "错误码 ")//4
    @TransfersNodeOut(value = TransfersNodeType.lcert_code, desc = "错误码 ")
    private Integer errcode;
    /**
     * 错误消息 240
     */
    @TransfersNodeOut(value = TransfersNodeType.vsmess, desc = "错误消息 ")//4
    private String errmsg;
    /**
     * 删除标志char(1)
     */
    @TransfersNodeIn(value = TransfersNodeType.smarket_code2, desc = "删除标志 ")//2
    @TransfersNodeOut(value = TransfersNodeType.smarket_code2, desc = "删除标志 ")
    private String delflag;

    public void setMsgid(Integer msgid) {
        this.msgid = msgid;
    }

    public Integer getMsgid() {
        return this.msgid;
    }

    public void setMsgtype(Integer msgtype) {
        this.msgtype = msgtype;
    }

    public Integer getMsgtype() {
        return this.msgtype;
    }

    public void setMsglevel(Integer msglevel) {
        this.msglevel = msglevel;
    }

    public Integer getMsglevel() {
        return this.msglevel;
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

    public void setCardno(Integer cardno) {
        this.cardno = cardno;
    }

    public Integer getCardno() {
        return this.cardno;
    }

    public void setTransdate(String transdate) {
        this.transdate = transdate;
    }

    public String getTransdate() {
        return this.transdate;
    }

    public void setCreatedtime(String createdtime) {
        this.createdtime = createdtime;
    }

    public String getCreatedtime() {
        return this.createdtime;
    }

    public void setStarttime(String starttime) {
        this.starttime = starttime;
    }

    public String getStarttime() {
        return this.starttime;
    }

    public void setEndtime(String endtime) {
        this.endtime = endtime;
    }

    public String getEndtime() {
        return this.endtime;
    }

    public void setReqdata(String reqdata) {
        this.reqdata = reqdata;
    }

    public String getReqdata() {
        return this.reqdata;
    }

    public void setRespdata(String respdata) {
        this.respdata = respdata;
    }

    public String getRespdata() {
        return this.respdata;
    }

    public void setFuncno(Integer funcno) {
        this.funcno = funcno;
    }

    public Integer getFuncno() {
        return this.funcno;
    }

    public void setPfuncno(Integer pfuncno) {
        this.pfuncno = pfuncno;
    }

    public Integer getPfuncno() {
        return this.pfuncno;
    }

    public void setMaxsendcnt(Integer maxsendcnt) {
        this.maxsendcnt = maxsendcnt;
    }

    public Integer getMaxsendcnt() {
        return this.maxsendcnt;
    }

    public void setSendcnt(Integer sendcnt) {
        this.sendcnt = sendcnt;
    }

    public Integer getSendcnt() {
        return this.sendcnt;
    }

    public void setRecvcnt(Integer recvcnt) {
        this.recvcnt = recvcnt;
    }

    public Integer getRecvcnt() {
        return this.recvcnt;
    }

    public void setStatus(Integer status) {
        this.status = status;
    }

    public Integer getStatus() {
        return this.status;
    }

    public void setSeqno(Integer seqno) {
        this.seqno = seqno;
    }

    public Integer getSeqno() {
        return this.seqno;
    }

    public void setOpercode(String opercode) {
        this.opercode = opercode;
    }

    public String getOpercode() {
        return this.opercode;
    }

    public void setErrcode(Integer errcode) {
        this.errcode = errcode;
    }

    public Integer getErrcode() {
        return this.errcode;
    }

    public void setErrmsg(String errmsg) {
        this.errmsg = errmsg;
    }

    public String getErrmsg() {
        return this.errmsg;
    }

    public void setDelflag(String delflag) {
        this.delflag = delflag;
    }

    public String getDelflag() {
        return this.delflag;
    }
}