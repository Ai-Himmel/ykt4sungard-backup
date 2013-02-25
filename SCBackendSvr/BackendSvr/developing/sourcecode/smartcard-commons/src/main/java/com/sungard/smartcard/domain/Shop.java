package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;


/**
 * T_SHOP的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Shop implements Serializable {

    /**
     * 商户号
     */
    private Integer shopid;
    /**
     * 上级商户号
     */
    private Integer fshopid;
    /**
     * 区域代码
     */
    private String areacode;
    /**
     * 部门代码
     */
    private String deptcode;
    /**
     * 商户名
     */
    private String shopname;
    /**
     * 商户类型1-收费商户2-充值商户
     */
    private Integer shoptype;
    /**
     * 是否独立核算：1-独立核算0-否
     */
    private String accflag;
    /**
     * 商户状态 1-正常2-销户
     */
    private String status;
    /**
     * 商户账号
     */
    private String accno;
    /**
     * 负责人
     */
    private String contactman;
    /**
     * 证件类型
     */
    private String idtype;
    /**
     * 证件号码
     */
    private String idno;
    /**
     * 电话
     */
    private String tel;
    /**
     * 手机
     */
    private String mobile;
    /**
     * 电子信箱
     */
    private String email;
    /**
     * 经营地址
     */
    private String businessaddr;
    /**
     * 联系地址
     */
    private String addr;
    /**
     * 邮政编码
     */
    private String zipcode;
    /**
     * 是否收搭伙费
     */
    private String boardfeeflag;
    /**
     * 佣金类型
     */
    private String rakeofftype;
    /**
     * 佣金费率
     */
    private Long rakeoffrate;
    /**
     * 存款折扣率
     */
    private Long depositagio;
    /**
     * 存款次数
     */
    private Integer depositcnt;
    /**
     * 存款总金额
     */
    private Double depositamt;
    /**
     * 折扣总金额
     */
    private Double discountamt;
    /**
     * 银行代码
     */
    private String bankcode;
    /**
     * 银行帐号
     */
    private String bankaccno;
    /**
     * 银行帐户名
     */
    private String bankaccname;
    /**
     * 开户日期
     */
    private String opendate;
    /**
     * 销户日期
     */
    private String closedate;
    /**
     * 使用标志
     */
    private String useflag;

    public void setShopid(Integer shopid) {
        this.shopid = shopid;
    }

    public Integer getShopid() {
        return this.shopid;
    }

    public void setFshopid(Integer fshopid) {
        this.fshopid = fshopid;
    }

    public Integer getFshopid() {
        return this.fshopid;
    }

    public void setAreacode(String areacode) {
        this.areacode = areacode;
    }

    public String getAreacode() {
        return this.areacode;
    }

    public void setDeptcode(String deptcode) {
        this.deptcode = deptcode;
    }

    public String getDeptcode() {
        return this.deptcode;
    }

    public void setShopname(String shopname) {
        this.shopname = shopname;
    }

    public String getShopname() {
        return this.shopname;
    }

    public void setShoptype(Integer shoptype) {
        this.shoptype = shoptype;
    }

    public Integer getShoptype() {
        return this.shoptype;
    }

    public void setAccflag(String accflag) {
        this.accflag = accflag;
    }

    public String getAccflag() {
        return this.accflag;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getStatus() {
        return this.status;
    }

    public void setAccno(String accno) {
        this.accno = accno;
    }

    public String getAccno() {
        return this.accno;
    }

    public void setContactman(String contactman) {
        this.contactman = contactman;
    }

    public String getContactman() {
        return this.contactman;
    }

    public void setIdtype(String idtype) {
        this.idtype = idtype;
    }

    public String getIdtype() {
        return this.idtype;
    }

    public void setIdno(String idno) {
        this.idno = idno;
    }

    public String getIdno() {
        return this.idno;
    }

    public void setTel(String tel) {
        this.tel = tel;
    }

    public String getTel() {
        return this.tel;
    }

    public void setMobile(String mobile) {
        this.mobile = mobile;
    }

    public String getMobile() {
        return this.mobile;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getEmail() {
        return this.email;
    }

    public void setBusinessaddr(String businessaddr) {
        this.businessaddr = businessaddr;
    }

    public String getBusinessaddr() {
        return this.businessaddr;
    }

    public void setAddr(String addr) {
        this.addr = addr;
    }

    public String getAddr() {
        return this.addr;
    }

    public void setZipcode(String zipcode) {
        this.zipcode = zipcode;
    }

    public String getZipcode() {
        return this.zipcode;
    }

    public void setBoardfeeflag(String boardfeeflag) {
        this.boardfeeflag = boardfeeflag;
    }

    public String getBoardfeeflag() {
        return this.boardfeeflag;
    }

    public void setRakeofftype(String rakeofftype) {
        this.rakeofftype = rakeofftype;
    }

    public String getRakeofftype() {
        return this.rakeofftype;
    }

    public void setRakeoffrate(Long rakeoffrate) {
        this.rakeoffrate = rakeoffrate;
    }

    public Long getRakeoffrate() {
        return this.rakeoffrate;
    }

    public void setDepositagio(Long depositagio) {
        this.depositagio = depositagio;
    }

    public Long getDepositagio() {
        return this.depositagio;
    }

    public void setDepositcnt(Integer depositcnt) {
        this.depositcnt = depositcnt;
    }

    public Integer getDepositcnt() {
        return this.depositcnt;
    }

    public void setDepositamt(Double depositamt) {
        this.depositamt = depositamt;
    }

    public Double getDepositamt() {
        return this.depositamt;
    }

    public void setDiscountamt(Double discountamt) {
        this.discountamt = discountamt;
    }

    public Double getDiscountamt() {
        return this.discountamt;
    }

    public void setBankcode(String bankcode) {
        this.bankcode = bankcode;
    }

    public String getBankcode() {
        return this.bankcode;
    }

    public void setBankaccno(String bankaccno) {
        this.bankaccno = bankaccno;
    }

    public String getBankaccno() {
        return this.bankaccno;
    }

    public void setBankaccname(String bankaccname) {
        this.bankaccname = bankaccname;
    }

    public String getBankaccname() {
        return this.bankaccname;
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

    public void setUseflag(String useflag) {
        this.useflag = useflag;
    }

    public String getUseflag() {
        return this.useflag;
    }
}