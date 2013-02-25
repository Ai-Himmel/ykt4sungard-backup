package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_AUTHCARD的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Authcard implements Serializable {

    /**
     * 交易卡号
     */
    private Integer cardno;
    /**
     * 卡物理ID
     */
    private String cardphyid;
    /**
     * 显示卡号
     */
    private String showcardno;
    /**
     * 授权卡权限
     */
    private Integer privilege;
    /**
     * 有效期
     */
    private String expiredate;
    /**
     * 记录状态
     */
    private String status;
    /**
     * 挂失状态
     */
    private String lossflag;
    /**
     * 挂失日期
     */
    private String lossdate;
    /**
     * 发卡日期
     */
    private String opendate;
    /**
     * 注销日期
     */
    private String closedate;

    public void setCardno(Integer cardno) {
        this.cardno = cardno;
    }

    public Integer getCardno() {
        return this.cardno;
    }

    public void setCardphyid(String cardphyid) {
        this.cardphyid = cardphyid;
    }

    public String getCardphyid() {
        return this.cardphyid;
    }

    public void setShowcardno(String showcardno) {
        this.showcardno = showcardno;
    }

    public String getShowcardno() {
        return this.showcardno;
    }

    public void setPrivilege(Integer privilege) {
        this.privilege = privilege;
    }

    public Integer getPrivilege() {
        return this.privilege;
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
}