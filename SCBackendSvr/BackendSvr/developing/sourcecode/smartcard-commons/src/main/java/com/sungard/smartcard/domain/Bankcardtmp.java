package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_BANKCARDTMP的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Bankcardtmp implements Serializable {

    /**
     * 记录号
     */
    private Double recordno;
    /**
     * 终端号
     */
    private Integer termid;
    /**
     * 导入批次号
     */
    private String batchno;
    /**
     * 操作员号
     */
    private String opercode;
    /**
     * 客户号
     */
    private Integer custid;
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
     * 处理日期
     */
    private String transdate;
    /**
     * 1无效记录2待处理记录3处理失败4处理成功
     */
    private Integer status;
    /**
     * 备注
     */
    private String remark;

    public void setRecordno(Double recordno) {
        this.recordno = recordno;
    }

    public Double getRecordno() {
        return this.recordno;
    }

    public void setTermid(Integer termid) {
        this.termid = termid;
    }

    public Integer getTermid() {
        return this.termid;
    }

    public void setBatchno(String batchno) {
        this.batchno = batchno;
    }

    public String getBatchno() {
        return this.batchno;
    }

    public void setOpercode(String opercode) {
        this.opercode = opercode;
    }

    public String getOpercode() {
        return this.opercode;
    }

    public void setCustid(Integer custid) {
        this.custid = custid;
    }

    public Integer getCustid() {
        return this.custid;
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

    public void setTransdate(String transdate) {
        this.transdate = transdate;
    }

    public String getTransdate() {
        return this.transdate;
    }

    public void setStatus(Integer status) {
        this.status = status;
    }

    public Integer getStatus() {
        return this.status;
    }

    public void setRemark(String remark) {
        this.remark = remark;
    }

    public String getRemark() {
        return this.remark;
    }
}