package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_FRONT的实体类
 * 前置机信息表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Front implements Serializable {

    /**
     * 前置机编号
     */
    private Integer frontid;
    /**
     * 前置机名称
     */
    private String frontname;
    /**
     * IP地址
     */
    private String ip;
    /**
     * DRTP端口
     */
    private Integer drtpport;
    /**
     * DRTP节点号
     */
    private Integer drtpnode;
    /**
     * BCC主功能号
     */
    private Integer bccmainfuncno;

    public void setFrontid(Integer frontid) {
        this.frontid = frontid;
    }

    public Integer getFrontid() {
        return this.frontid;
    }

    public void setFrontname(String frontname) {
        this.frontname = frontname;
    }

    public String getFrontname() {
        return this.frontname;
    }

    public void setIp(String ip) {
        this.ip = ip;
    }

    public String getIp() {
        return this.ip;
    }

    public void setDrtpport(Integer drtpport) {
        this.drtpport = drtpport;
    }

    public Integer getDrtpport() {
        return this.drtpport;
    }

    public void setDrtpnode(Integer drtpnode) {
        this.drtpnode = drtpnode;
    }

    public Integer getDrtpnode() {
        return this.drtpnode;
    }

    public void setBccmainfuncno(Integer bccmainfuncno) {
        this.bccmainfuncno = bccmainfuncno;
    }

    public Integer getBccmainfuncno() {
        return this.bccmainfuncno;
    }
}