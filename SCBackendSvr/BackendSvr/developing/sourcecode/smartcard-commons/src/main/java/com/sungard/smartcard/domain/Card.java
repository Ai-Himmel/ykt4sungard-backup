package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_CARD的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Card implements Serializable {

    /**
     * 卡号
     */
    private Integer cardno;
    /**
     * 卡账号
     */
    private String accno;
    /**
     * 卡类型
     */
    private Integer cardtype;
    /**
     * 卡物理类型
     */
    private Integer cardphytype;
    /**
     * 收费类型
     */
    private Integer feetype;
    /**
     * 客户号
     */
    private Integer custid;
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
     * 挂失生效时间
     */
    private String lossefttime;
    /**
     * 1-冻结0-未冻结
     */
    private String frozeflag;
    /**
     * 冻结日期
     */
    private String frozedate;
    /**
     * 1-坏卡0-不是坏卡
     */
    private String badflag;
    /**
     * 0-卡结构错误1-人为损坏2-质量问题
     */
    private String badtype;
    /**
     * 坏卡登记日期
     */
    private String baddate;
    /**
     * 锁定标志
     */
    private String lockflag;
    /**
     * 锁定日期
     */
    private String lockdate;
    /**
     * 开卡日期
     */
    private String opendate;
    /**
     * 注销日期
     */
    private String closedate;
    /**
     * 卡版本号
     */
    private String cardverno;
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

    public void setAccno(String accno) {
        this.accno = accno;
    }

    public String getAccno() {
        return this.accno;
    }

    public void setCardtype(Integer cardtype) {
        this.cardtype = cardtype;
    }

    public Integer getCardtype() {
        return this.cardtype;
    }

    public void setCardphytype(Integer cardphytype) {
        this.cardphytype = cardphytype;
    }

    public Integer getCardphytype() {
        return this.cardphytype;
    }

    public void setFeetype(Integer feetype) {
        this.feetype = feetype;
    }

    public Integer getFeetype() {
        return this.feetype;
    }

    public void setCustid(Integer custid) {
        this.custid = custid;
    }

    public Integer getCustid() {
        return this.custid;
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

    public void setLossefttime(String lossefttime) {
        this.lossefttime = lossefttime;
    }

    public String getLossefttime() {
        return this.lossefttime;
    }

    public void setFrozeflag(String frozeflag) {
        this.frozeflag = frozeflag;
    }

    public String getFrozeflag() {
        return this.frozeflag;
    }

    public void setFrozedate(String frozedate) {
        this.frozedate = frozedate;
    }

    public String getFrozedate() {
        return this.frozedate;
    }

    public void setBadflag(String badflag) {
        this.badflag = badflag;
    }

    public String getBadflag() {
        return this.badflag;
    }

    public void setBadtype(String badtype) {
        this.badtype = badtype;
    }

    public String getBadtype() {
        return this.badtype;
    }

    public void setBaddate(String baddate) {
        this.baddate = baddate;
    }

    public String getBaddate() {
        return this.baddate;
    }

    public void setLockflag(String lockflag) {
        this.lockflag = lockflag;
    }

    public String getLockflag() {
        return this.lockflag;
    }

    public void setLockdate(String lockdate) {
        this.lockdate = lockdate;
    }

    public String getLockdate() {
        return this.lockdate;
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

    public void setCardverno(String cardverno) {
        this.cardverno = cardverno;
    }

    public String getCardverno() {
        return this.cardverno;
    }

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }
}