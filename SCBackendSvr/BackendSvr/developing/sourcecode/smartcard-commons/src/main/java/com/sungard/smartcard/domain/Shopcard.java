package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_SHOPCARD的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Shopcard implements Serializable {

    /**
     * 卡号
     */
    private Integer cardno;
    /**
     * 商户号
     */
    private Integer shopid;
    /**
     * 显示卡号
     */
    private String showcardno;
    /**
     * 卡物理ID
     */
    private String cardphyid;
    /**
     * 卡密码
     */
    private String cardpwd;
    /**
     * 到期日期
     */
    private String expiredate;
    /**
     * 记录状态1-正常2-注销
     */
    private String status;
    /**
     * 1-挂失0-未挂失
     */
    private String lossflag;
    /**
     * 挂失日期
     */
    private String lossdate;
    /**
     * 开卡日期
     */
    private String opendate;
    /**
     * 注销日期
     */
    private String closedate;
    /**
     * 最后保存时间
     */
    private String lastsaved;

    public void setCardno(Integer cardno) {
        this.cardno = cardno;
    }

    public Integer getCardno() {
        return this.cardno;
    }

    public void setShopid(Integer shopid) {
        this.shopid = shopid;
    }

    public Integer getShopid() {
        return this.shopid;
    }

    public void setShowcardno(String showcardno) {
        this.showcardno = showcardno;
    }

    public String getShowcardno() {
        return this.showcardno;
    }

    public void setCardphyid(String cardphyid) {
        this.cardphyid = cardphyid;
    }

    public String getCardphyid() {
        return this.cardphyid;
    }

    public void setCardpwd(String cardpwd) {
        this.cardpwd = cardpwd;
    }

    public String getCardpwd() {
        return this.cardpwd;
    }

    public void setExpiredate(String expiredate) {
        this.expiredate = expiredate;
    }

    public String getExpiredate() {
        return this.expiredate;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getStatus() {
        return this.status;
    }

    public void setLossflag(String lossflag) {
        this.lossflag = lossflag;
    }

    public String getLossflag() {
        return this.lossflag;
    }

    public void setLossdate(String lossdate) {
        this.lossdate = lossdate;
    }

    public String getLossdate() {
        return this.lossdate;
    }

    public void setOpendate(String opendate) {
        this.opendate = opendate;
    }

    public String getOpendate() {
        return this.opendate;
    }

    public void setClosedate(String closedate) {
        this.closedate = closedate;
    }

    public String getClosedate() {
        return this.closedate;
    }

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }
}