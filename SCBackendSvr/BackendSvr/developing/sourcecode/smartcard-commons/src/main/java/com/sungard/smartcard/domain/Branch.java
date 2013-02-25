package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;
import com.sungard.smartcard.annotation.TransfersNodeIn;
import com.sungard.smartcard.annotation.TransfersNodeOut;
import com.sungard.smartcard.annotation.TransfersNodeType;

import java.io.Serializable;

/**
 * T_BRANCH的实体类
 * 网点表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Branch implements Serializable {

    /**
     * 网点号
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol12, desc = "网点号")
    @TransfersNodeOut(value = TransfersNodeType.lvol12, desc = "网点号")
    private Integer branchno;
    /**
     * 区域代码
     */
    @TransfersNodeIn(value = TransfersNodeType.scust_type, desc = "区域代码")
    @TransfersNodeOut(value = TransfersNodeType.scust_type, desc = "区域代码")
    private String areacode;
    /**
     * 网点名称
     */
    @TransfersNodeIn(value = TransfersNodeType.semail, desc = "网店名称")
    @TransfersNodeOut(value = TransfersNodeType.semail, desc = "网店名称")
    private String branchname;
    /**
     * 网点类型：1-管理中心2-充值点3-超市
     */
    @TransfersNodeIn(value = TransfersNodeType.smarket_code, desc = "网点类型")
    @TransfersNodeOut(value = TransfersNodeType.smarket_code, desc = "网点类型")
    private String branchtype;
    /**
     * 银行代码
     */
    @TransfersNodeIn(value = TransfersNodeType.smarket_code2, desc = "银行代码")
    @TransfersNodeOut(value = TransfersNodeType.smarket_code2, desc = "银行代码")
    private String bankcode;
    /**
     * 银行帐户
     */
    @TransfersNodeIn(value = TransfersNodeType.scust_auth, desc = "银行帐户")
    @TransfersNodeOut(value = TransfersNodeType.scust_auth, desc = "银行帐户")
    private String bankaccno;
    /**
     * 银行帐户名
     */
    @TransfersNodeIn(value = TransfersNodeType.semail2, desc = "银行帐户名")
    @TransfersNodeOut(value = TransfersNodeType.semail2, desc = "银行帐户名")
    private String bankaccname;
    /**
     * 联系人
     */
    @TransfersNodeIn(value = TransfersNodeType.scert_addr, desc = "联系人")
    @TransfersNodeOut(value = TransfersNodeType.scert_addr, desc = "联系人")
    private String contactman;
    /**
     * 电话
     */
    @TransfersNodeIn(value = TransfersNodeType.sphone, desc = "电话")
    @TransfersNodeOut(value = TransfersNodeType.sphone, desc = "电话")
    private String tel;
    /**
     * 手机
     */
    @TransfersNodeIn(value = TransfersNodeType.sphone2, desc = "手机")
    @TransfersNodeOut(value = TransfersNodeType.sphone2, desc = "手机")
    private String mobile;
    /**
     * 传真
     */
    @TransfersNodeIn(value = TransfersNodeType.sphone3, desc = "传真")
    @TransfersNodeOut(value = TransfersNodeType.sphone3, desc = "传真")
    private String fax;
    /**
     * 地址
     */
    @TransfersNodeIn(value = TransfersNodeType.vsvarstr0, desc = "地址")
    @TransfersNodeOut(value = TransfersNodeType.vsvarstr0, desc = "地址")
    private String addr;
    /**
     * 邮政编码
     */
    @TransfersNodeIn(value = TransfersNodeType.sdate0, desc = "邮政编码")
    @TransfersNodeOut(value = TransfersNodeType.sdate0, desc = "邮政编码")
    private String zipcode;
    /**
     * 状态
     */
    @TransfersNodeOut(value = TransfersNodeType.sstatus4, desc = "状态")
    private String status;
    /**
     * 注册日期
     */
    @TransfersNodeOut(value = TransfersNodeType.sbank_pwd, desc = "注册日期")
    private String opendate;
    /**
     * 注销日期
     */
    @TransfersNodeOut(value = TransfersNodeType.sbank_pwd2, desc = "注销日期")
    private String closedate;
    /**
     * 使用状态 0-未使用1-已使用
     */
    @TransfersNodeOut(value = TransfersNodeType.sstatus3, desc = "使用状态")
    private String useflag;
    /**
     * 保存时间
     */
    @TransfersNodeOut(value = TransfersNodeType.scust_limit, desc = "保存时间")
    private String lastsaved;

    public void setBranchno(Integer branchno) {
        this.branchno = branchno;
    }

    public Integer getBranchno() {
        return this.branchno;
    }

    public void setAreacode(String areacode) {
        this.areacode = areacode;
    }

    public String getAreacode() {
        return this.areacode;
    }

    public void setBranchname(String branchname) {
        this.branchname = branchname;
    }

    public String getBranchname() {
        return this.branchname;
    }

    public void setBranchtype(String branchtype) {
        this.branchtype = branchtype;
    }

    public String getBranchtype() {
        return this.branchtype;
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

    public void setContactman(String contactman) {
        this.contactman = contactman;
    }

    public String getContactman() {
        return this.contactman;
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

    public void setFax(String fax) {
        this.fax = fax;
    }

    public String getFax() {
        return this.fax;
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

    public void setStatus(String status) {
        this.status = status;
    }

    public String getStatus() {
        return this.status;
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

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }
}