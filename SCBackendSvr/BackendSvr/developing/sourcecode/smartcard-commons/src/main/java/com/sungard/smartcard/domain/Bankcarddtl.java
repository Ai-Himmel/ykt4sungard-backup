package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_BANKCARDDTL的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Bankcarddtl implements Serializable {

    /**
     * 交易参考号
     */
    private Double refno;
    /**
     * 发生日期
     */
    private String transdate;
    /**
     * 发生时间
     */
    private String transtime;
    /**
     * 终端号
     */
    private Integer termid;
    /**
     * 操作员号
     */
    private String opercode;
    /**
     * 导入批次号
     */
    private String batchno;
    /**
     * 客户号
     */
    private Integer custid;
    /**
     * 姓名
     */
    private String custname;
    /**
     * 学工号
     */
    private String stuempno;
    /**
     * 银行卡号
     */
    private String bankcardno;
    /**
     * 1- 签约2-解约3- 同步
     */
    private Integer optype;
    /**
     * 1-增加2-删除
     */
    private Integer adddelflag;
    /**
     * 错误码
     */
    private Integer errcode;
    /**
     * 备注
     */
    private String remark;

    public void setRefno(Double refno) {
        this.refno = refno;
    }

    public Double getRefno() {
        return this.refno;
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

    public void setTermid(Integer termid) {
        this.termid = termid;
    }

    public Integer getTermid() {
        return this.termid;
    }

    public void setOpercode(String opercode) {
        this.opercode = opercode;
    }

    public String getOpercode() {
        return this.opercode;
    }

    public void setBatchno(String batchno) {
        this.batchno = batchno;
    }

    public String getBatchno() {
        return this.batchno;
    }

    public void setCustid(Integer custid) {
        this.custid = custid;
    }

    public Integer getCustid() {
        return this.custid;
    }

    public void setCustname(String custname) {
        this.custname = custname;
    }

    public String getCustname() {
        return this.custname;
    }

    public void setStuempno(String stuempno) {
        this.stuempno = stuempno;
    }

    public String getStuempno() {
        return this.stuempno;
    }

    public void setBankcardno(String bankcardno) {
        this.bankcardno = bankcardno;
    }

    public String getBankcardno() {
        return this.bankcardno;
    }

    public void setOptype(Integer optype) {
        this.optype = optype;
    }

    public Integer getOptype() {
        return this.optype;
    }

    public void setAdddelflag(Integer adddelflag) {
        this.adddelflag = adddelflag;
    }

    public Integer getAdddelflag() {
        return this.adddelflag;
    }

    public void setErrcode(Integer errcode) {
        this.errcode = errcode;
    }

    public Integer getErrcode() {
        return this.errcode;
    }

    public void setRemark(String remark) {
        this.remark = remark;
    }

    public String getRemark() {
        return this.remark;
    }
}