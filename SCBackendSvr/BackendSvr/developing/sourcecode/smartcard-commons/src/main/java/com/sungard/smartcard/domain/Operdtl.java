package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_OPERDTL的实体类
 * 操作员交易流水表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Operdtl implements Serializable {

    /**
     * 记账日期
     */
    private String accdate;
    /**
     * 站点号
     */
    private Integer termid;
    /**
     * 站点流水号
     */
    private Integer termseqno;
    /**
     * 操作员号
     */
    private String opercode;
    /**
     * 交易日期
     */
    private String transdate;
    /**
     * 发生时间
     */
    private String transtime;
    /**
     * 交易码
     */
    private Integer transcode;
    /**
     * 审核操作员
     */
    private String chkoper;
    /**
     * 流水状态1-未处理2-失败3-成功4-冲正
     */
    private String status;
    /**
     * 交易信息
     */
    private String transinfo;
    /**
     * 请求数据
     */
    private String reqdata;

    public void setAccdate(String accdate) {
        this.accdate = accdate;
    }

    public String getAccdate() {
        return this.accdate;
    }

    public void setTermid(Integer termid) {
        this.termid = termid;
    }

    public Integer getTermid() {
        return this.termid;
    }

    public void setTermseqno(Integer termseqno) {
        this.termseqno = termseqno;
    }

    public Integer getTermseqno() {
        return this.termseqno;
    }

    public void setOpercode(String opercode) {
        this.opercode = opercode;
    }

    public String getOpercode() {
        return this.opercode;
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

    public void setTranscode(Integer transcode) {
        this.transcode = transcode;
    }

    public Integer getTranscode() {
        return this.transcode;
    }

    public void setChkoper(String chkoper) {
        this.chkoper = chkoper;
    }

    public String getChkoper() {
        return this.chkoper;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getStatus() {
        return this.status;
    }

    public void setTransinfo(String transinfo) {
        this.transinfo = transinfo;
    }

    public String getTransinfo() {
        return this.transinfo;
    }

    public void setReqdata(String reqdata) {
        this.reqdata = reqdata;
    }

    public String getReqdata() {
        return this.reqdata;
    }
}