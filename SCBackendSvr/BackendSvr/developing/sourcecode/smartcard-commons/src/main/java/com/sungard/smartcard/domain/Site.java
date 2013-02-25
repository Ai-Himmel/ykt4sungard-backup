package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;
import com.sungard.smartcard.annotation.TransfersNodeIn;
import com.sungard.smartcard.annotation.TransfersNodeOut;
import com.sungard.smartcard.annotation.TransfersNodeType;

import java.io.Serializable;

/**
 * T_SITE的实体类
 * 站点表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Site implements Serializable {

    /**
     * 站点号
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol0, desc = "站点编号")
    @TransfersNodeOut(value = TransfersNodeType.lvol0, desc = "站点编号")
    private Integer siteno;
    /**
     * 站点名称
     */
    @TransfersNodeIn(value = TransfersNodeType.semail, desc = "站点名称，操作员号")
    @TransfersNodeOut(value = TransfersNodeType.semail, desc = "站点名称")
    private String sitename;
    /**
     * IP地址
     */
    @TransfersNodeIn(value = TransfersNodeType.sholder_ac_no, desc = "IP地址,操作员密码")
    @TransfersNodeOut(value = TransfersNodeType.sholder_ac_no, desc = "IP地址")
    private String ip;
    /**
     * 机器码
     */
    @TransfersNodeIn(value = TransfersNodeType.semail2, desc = "机器码,操作员原密码")
    @TransfersNodeOut(value = TransfersNodeType.semail2, desc = "机器码")
    private String machinecode;
    /**
     * 最后保存时间
     */
    private String lastsaved;
    /**
     * 备注
     */
    @TransfersNodeIn(value = TransfersNodeType.vsvarstr0, desc = "备注")
    @TransfersNodeOut(value = TransfersNodeType.vsvarstr0, desc = "备注")
    private String remark;

    public void setSiteno(Integer siteno) {
        this.siteno = siteno;
    }

    public Integer getSiteno() {
        return this.siteno;
    }

    public void setSitename(String sitename) {
        this.sitename = sitename;
    }

    public String getSitename() {
        return this.sitename;
    }

    public void setIp(String ip) {
        this.ip = ip;
    }

    public String getIp() {
        return this.ip;
    }

    public void setMachinecode(String machinecode) {
        this.machinecode = machinecode;
    }

    public String getMachinecode() {
        return this.machinecode;
    }

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }

    public void setRemark(String remark) {
        this.remark = remark;
    }

    public String getRemark() {
        return this.remark;
    }
}