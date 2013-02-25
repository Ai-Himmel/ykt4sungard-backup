package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;
import com.sungard.smartcard.annotation.TransfersNodeIn;
import com.sungard.smartcard.annotation.TransfersNodeOut;
import com.sungard.smartcard.annotation.TransfersNodeType;

import java.io.Serializable;

/**
 * T_OPERATOR的实体类
 * 操作员表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Operator implements Serializable {

    /**
     * 操作员代码
     */
    @TransfersNodeIn(value = TransfersNodeType.sdate0, desc = "操作员代码")
    @TransfersNodeOut(value = TransfersNodeType.sdate0, desc = "操作员代码")
    private String opercode;
    /**
     * 操作员类型:0-系统管理员 1-审核操作员 2-业务操作员 3-医疗系统操作员
     */
    @TransfersNodeIn(value = TransfersNodeType.sstatus1, desc = "操作员类型")
    @TransfersNodeOut(value = TransfersNodeType.sstatus1, desc = "操作员类型")
    private String opertype;
    /**
     * 所属网点号
     */
    @TransfersNodeIn(value = TransfersNodeType.lsafe_level, desc = "网点号")
    @TransfersNodeOut(value = TransfersNodeType.lsafe_level, desc = "网点号")
    private Integer branchno;
    /**
     * 操作员卡号
     */
    @TransfersNodeOut(value = TransfersNodeType.lsafe_level2, desc = "操作员卡号")
    private Integer cardno;
    /**
     * 操作员姓名
     */
    @TransfersNodeIn(value = TransfersNodeType.scert_addr, desc = "操作员姓名")
    @TransfersNodeOut(value = TransfersNodeType.scert_addr, desc = "操作员姓名")
    private String opername;
    /**
     * 电话
     */
    @TransfersNodeIn(value = TransfersNodeType.scust_limit, desc = "电话")
    @TransfersNodeOut(value = TransfersNodeType.scust_limit, desc = "电话")
    private String tel;
    /**
     * 手机
     */
    @TransfersNodeIn(value = TransfersNodeType.sphone3, desc = "手机")
    @TransfersNodeOut(value = TransfersNodeType.sphone3, desc = "手机")
    private String mobile;
    /**
     * 电子邮箱
     */
    @TransfersNodeIn(value = TransfersNodeType.semail, desc = "电子邮箱")
    @TransfersNodeOut(value = TransfersNodeType.semail, desc = "电子邮箱")
    private String email;
    /**
     * 地址
     */
    @TransfersNodeIn(value = TransfersNodeType.vsvarstr2, desc = "操作员操作员ip,地址")
    @TransfersNodeOut(value = TransfersNodeType.vsvarstr2, desc = "操作员操作员ip,地址")
    private String addr;
    /**
     * 邮政编码
     */
    @TransfersNodeIn(value = TransfersNodeType.sstation0, desc = "操作员mac地址,邮政编码")
    @TransfersNodeOut(value = TransfersNodeType.sstation0, desc = "操作员mac地址,邮政编码")
    private String zipcode;
    /**
     * 密码
     */
    @TransfersNodeIn(value = TransfersNodeType.scust_limit, desc = "操作员密码,密码")
    @TransfersNodeOut(value = TransfersNodeType.scust_limit, desc = "操作员密码,密码")
    private String operpwd;
    /**
     * 状态:0-锁定1-正常2-注销smarket_code2 char(2)
     */
    @TransfersNodeIn(value = TransfersNodeType.smarket_code2, desc = "状态")
    @TransfersNodeOut(value = TransfersNodeType.smarket_code2, desc = "状态")
    private String status;
    /**
     * 最后交易日期:充值操作员使用
     */
    private String lasttransdate;
    /**
     * 功能权限集
     */
    private String funcset;
    /**
     * 权限标志lvol7 int(4)
     */
    @TransfersNodeOut(value = TransfersNodeType.lvol7, desc = "权限标志")
    private Integer rightflag;
    /**
     * 是否有站点限制:0-无限制1-有限制smarket_code char(2)
     */
    @TransfersNodeOut(value = TransfersNodeType.smarket_code, desc = "是否有站点限制")
    private String sitelimit;
    /**
     * 登录标志:0-未登录1-已登录 smain_flag char(2)
     */
    @TransfersNodeOut(value = TransfersNodeType.smain_flag, desc = "登录标志")
    private String loginflag;
    /**
     * 登录站点号
     */
    @TransfersNodeIn(value = TransfersNodeType.lbank_acc_type2, desc = "角色id")
    @TransfersNodeOut(value = TransfersNodeType.lbank_acc_type2, desc = "登陆站点号")
    private Integer loginsiteno;
    /**
     * 登录时间
     */
    private String logintime;
    /**
     * 登出时间
     */
    private String logouttime;
    /**
     * 登录失败次数
     */
    private Integer failnumber;
    /**
     * 注册日期
     */
    private String opendate;
    /**
     * 注销日期
     */
    private String closedate;

    public void setOpercode(String opercode) {
        this.opercode = opercode;
    }

    public String getOpercode() {
        return this.opercode;
    }

    public void setOpertype(String opertype) {
        this.opertype = opertype;
    }

    public String getOpertype() {
        return this.opertype;
    }

    public void setBranchno(Integer branchno) {
        this.branchno = branchno;
    }

    public Integer getBranchno() {
        return this.branchno;
    }

    public void setCardno(Integer cardno) {
        this.cardno = cardno;
    }

    public Integer getCardno() {
        return this.cardno;
    }

    public void setOpername(String opername) {
        this.opername = opername;
    }

    public String getOpername() {
        return this.opername;
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

    public void setOperpwd(String operpwd) {
        this.operpwd = operpwd;
    }

    public String getOperpwd() {
        return this.operpwd;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getStatus() {
        return this.status;
    }

    public void setLasttransdate(String lasttransdate) {
        this.lasttransdate = lasttransdate;
    }

    public String getLasttransdate() {
        return this.lasttransdate;
    }

    public void setFuncset(String funcset) {
        this.funcset = funcset;
    }

    public String getFuncset() {
        return this.funcset;
    }

    public void setRightflag(Integer rightflag) {
        this.rightflag = rightflag;
    }

    public Integer getRightflag() {
        return this.rightflag;
    }

    public void setSitelimit(String sitelimit) {
        this.sitelimit = sitelimit;
    }

    public String getSitelimit() {
        return this.sitelimit;
    }

    public void setLoginflag(String loginflag) {
        this.loginflag = loginflag;
    }

    public String getLoginflag() {
        return this.loginflag;
    }

    public void setLoginsiteno(Integer loginsiteno) {
        this.loginsiteno = loginsiteno;
    }

    public Integer getLoginsiteno() {
        return this.loginsiteno;
    }

    public void setLogintime(String logintime) {
        this.logintime = logintime;
    }

    public String getLogintime() {
        return this.logintime;
    }

    public void setLogouttime(String logouttime) {
        this.logouttime = logouttime;
    }

    public String getLogouttime() {
        return this.logouttime;
    }

    public void setFailnumber(Integer failnumber) {
        this.failnumber = failnumber;
    }

    public Integer getFailnumber() {
        return this.failnumber;
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