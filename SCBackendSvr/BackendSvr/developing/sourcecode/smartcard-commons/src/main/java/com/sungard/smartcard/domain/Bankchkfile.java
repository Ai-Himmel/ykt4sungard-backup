package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_BANKCHKFILE的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Bankchkfile implements Serializable {

    /**
     * 银行标识
     */
    private Integer bankid;
    /**
     * 银行日期
     */
    private Integer bankdate;
    /**
     * 银行对账文件名
     */
    private String bankchkfile;
    /**
     * 本地对账文件名
     */
    private String localchkfile;
    /**
     * 本地转换文件名
     */
    private String localcvtfile;
    /**
     * 'L‘ 本地 ’B'银行
     */
    private String filesource;
    /**
     * 核对状态:I导入'C'对账完成'R'处理完成
     */
    private String status;
    /**
     * 处理标志
     */
    private String resolved;
    /**
     * 备注
     */
    private String remark;
    /**
     * 银行记录条数
     */
    private Integer bankcnt;
    /**
     * 银行总金额
     */
    private Double bankamt;
    /**
     * 本地总数
     */
    private Integer localcnt;
    /**
     * 本地总金额
     */
    private Double localamt;
    /**
     * 记录创建时间
     */
    private String crttime;
    /**
     * 最后保存时间
     */
    private String updtime;

    public void setBankid(Integer bankid) {
        this.bankid = bankid;
    }

    public Integer getBankid() {
        return this.bankid;
    }

    public void setBankdate(Integer bankdate) {
        this.bankdate = bankdate;
    }

    public Integer getBankdate() {
        return this.bankdate;
    }

    public void setBankchkfile(String bankchkfile) {
        this.bankchkfile = bankchkfile;
    }

    public String getBankchkfile() {
        return this.bankchkfile;
    }

    public void setLocalchkfile(String localchkfile) {
        this.localchkfile = localchkfile;
    }

    public String getLocalchkfile() {
        return this.localchkfile;
    }

    public void setLocalcvtfile(String localcvtfile) {
        this.localcvtfile = localcvtfile;
    }

    public String getLocalcvtfile() {
        return this.localcvtfile;
    }

    public void setFilesource(String filesource) {
        this.filesource = filesource;
    }

    public String getFilesource() {
        return this.filesource;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getStatus() {
        return this.status;
    }

    public void setResolved(String resolved) {
        this.resolved = resolved;
    }

    public String getResolved() {
        return this.resolved;
    }

    public void setRemark(String remark) {
        this.remark = remark;
    }

    public String getRemark() {
        return this.remark;
    }

    public void setBankcnt(Integer bankcnt) {
        this.bankcnt = bankcnt;
    }

    public Integer getBankcnt() {
        return this.bankcnt;
    }

    public void setBankamt(Double bankamt) {
        this.bankamt = bankamt;
    }

    public Double getBankamt() {
        return this.bankamt;
    }

    public void setLocalcnt(Integer localcnt) {
        this.localcnt = localcnt;
    }

    public Integer getLocalcnt() {
        return this.localcnt;
    }

    public void setLocalamt(Double localamt) {
        this.localamt = localamt;
    }

    public Double getLocalamt() {
        return this.localamt;
    }

    public void setCrttime(String crttime) {
        this.crttime = crttime;
    }

    public String getCrttime() {
        return this.crttime;
    }

    public void setUpdtime(String updtime) {
        this.updtime = updtime;
    }

    public String getUpdtime() {
        return this.updtime;
    }
}