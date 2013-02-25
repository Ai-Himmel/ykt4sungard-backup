package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_TRANSCODE的实体类
 * 交易码表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Transcode implements Serializable {

    /**
     * 交易码
     */
    private Integer transcode;
    /**
     * 交易名称
     */
    private String transname;
    /**
     * 是否记录操作员日志:0-不记录1-只记录成功流水2-只记录失败3-成功失败都记录
     */
    private Integer logflag;
    /**
     * 是否限制操作员:0不限制1-限制
     */
    private Integer limitflag;
    /**
     * 收费标志
     */
    private Integer feeflag;
    /**
     * 交易标志
     */
    private Integer transflag;
    /**
     * 禁用标志
     */
    private Integer disableflag;

    public void setTranscode(Integer transcode) {
        this.transcode = transcode;
    }

    public Integer getTranscode() {
        return this.transcode;
    }

    public void setTransname(String transname) {
        this.transname = transname;
    }

    public String getTransname() {
        return this.transname;
    }

    public void setLogflag(Integer logflag) {
        this.logflag = logflag;
    }

    public Integer getLogflag() {
        return this.logflag;
    }

    public void setLimitflag(Integer limitflag) {
        this.limitflag = limitflag;
    }

    public Integer getLimitflag() {
        return this.limitflag;
    }

    public void setFeeflag(Integer feeflag) {
        this.feeflag = feeflag;
    }

    public Integer getFeeflag() {
        return this.feeflag;
    }

    public void setTransflag(Integer transflag) {
        this.transflag = transflag;
    }

    public Integer getTransflag() {
        return this.transflag;
    }

    public void setDisableflag(Integer disableflag) {
        this.disableflag = disableflag;
    }

    public Integer getDisableflag() {
        return this.disableflag;
    }
}