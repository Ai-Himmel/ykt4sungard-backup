package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_CUSTOMER的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Customer implements Serializable {

    /**
     * 客户号
     */
    private Integer custid;
    /**
     * 学工号
     */
    private String stuempno;
    /**
     * 客户类型
     */
    private Integer custtype;
    /**
     * 收费类别
     */
    private Integer feetype;
    /**
     * 状态1-正常2-注销
     */
    private String status;
    /**
     * 客户名称
     */
    private String custname;
    /**
     * 区域代码
     */
    private String areacode;
    /**
     * 部门代码
     */
    private String deptcode;
    /**
     * 部门全称
     */
    private String deptfullname;
    /**
     * 专业代码
     */
    private String specialtycode;
    /**
     * 班级代码
     */
    private String classcode;
    /**
     * 班级名称
     */
    private String classname;
    /**
     * 证件类型
     */
    private String idtype;
    /**
     * 证件号码
     */
    private String idno;
    /**
     * 性别
     */
    private String sex;
    /**
     * 国籍
     */
    private String country;
    /**
     * 民族
     */
    private String nation;
    /**
     * 电子信箱
     */
    private String email;
    /**
     * 电话
     */
    private String tel;
    /**
     * 手机
     */
    private String mobile;
    /**
     * 地址
     */
    private String addr;
    /**
     * 邮政编码
     */
    private String zipcode;
    /**
     * 客户属性
     */
    private String custattr;
    /**
     * 入校日期
     */
    private String indate;
    /**
     * 预计离校日期
     */
    private String outdate;
    /**
     * 注册日期,指的是客户信息添加进来的日期
     */
    private String opendate;
    /**
     * 注销日期
     */
    private String closedate;
    /**
     * 导入批次号
     */
    private String batchno;
    /**
     * 正式卡开通标志
     */
    private Integer openflag;
    /**
     * 拥有卡个数
     */
    private Integer holdcardcnt;
    /**
     * 使用标志
     */
    private String useflag;
    /**
     * 电子钱包开通标志
     */
    private String eaccflag;
    /**
     * 最后保存时间
     */
    private String lastsaved;

    public void setCustid(Integer custid) {
        this.custid = custid;
    }

    public Integer getCustid() {
        return this.custid;
    }

    public void setStuempno(String stuempno) {
        this.stuempno = stuempno;
    }

    public String getStuempno() {
        return this.stuempno;
    }

    public void setCusttype(Integer custtype) {
        this.custtype = custtype;
    }

    public Integer getCusttype() {
        return this.custtype;
    }

    public void setFeetype(Integer feetype) {
        this.feetype = feetype;
    }

    public Integer getFeetype() {
        return this.feetype;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getStatus() {
        return this.status;
    }

    public void setCustname(String custname) {
        this.custname = custname;
    }

    public String getCustname() {
        return this.custname;
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

    public void setDeptfullname(String deptfullname) {
        this.deptfullname = deptfullname;
    }

    public String getDeptfullname() {
        return this.deptfullname;
    }

    public void setSpecialtycode(String specialtycode) {
        this.specialtycode = specialtycode;
    }

    public String getSpecialtycode() {
        return this.specialtycode;
    }

    public void setClasscode(String classcode) {
        this.classcode = classcode;
    }

    public String getClasscode() {
        return this.classcode;
    }

    public void setClassname(String classname) {
        this.classname = classname;
    }

    public String getClassname() {
        return this.classname;
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

    public void setSex(String sex) {
        this.sex = sex;
    }

    public String getSex() {
        return this.sex;
    }

    public void setCountry(String country) {
        this.country = country;
    }

    public String getCountry() {
        return this.country;
    }

    public void setNation(String nation) {
        this.nation = nation;
    }

    public String getNation() {
        return this.nation;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getEmail() {
        return this.email;
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

    public void setCustattr(String custattr) {
        this.custattr = custattr;
    }

    public String getCustattr() {
        return this.custattr;
    }

    public void setIndate(String indate) {
        this.indate = indate;
    }

    public String getIndate() {
        return this.indate;
    }

    public void setOutdate(String outdate) {
        this.outdate = outdate;
    }

    public String getOutdate() {
        return this.outdate;
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

    public void setBatchno(String batchno) {
        this.batchno = batchno;
    }

    public String getBatchno() {
        return this.batchno;
    }

    public void setOpenflag(Integer openflag) {
        this.openflag = openflag;
    }

    public Integer getOpenflag() {
        return this.openflag;
    }

    public void setHoldcardcnt(Integer holdcardcnt) {
        this.holdcardcnt = holdcardcnt;
    }

    public Integer getHoldcardcnt() {
        return this.holdcardcnt;
    }

    public void setUseflag(String useflag) {
        this.useflag = useflag;
    }

    public String getUseflag() {
        return this.useflag;
    }

    public void setEaccflag(String eaccflag) {
        this.eaccflag = eaccflag;
    }

    public String getEaccflag() {
        return this.eaccflag;
    }

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }
}