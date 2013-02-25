package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_CUSTOMERTMP的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Customertmp implements Serializable {

    /**
     * 导入批次号或同步时间
     */
    private String batchno;
    /**
     * 导入序号
     */
    private Integer seqno;
    /**
     * 导入日期
     */
    private String transdate;
    /**
     * 导入操作员
     */
    private String opercode;
    /**
     * 学工号
     */
    private String stuempno;
    /**
     * 客户类型
     */
    private Integer custtype;
    /**
     * 客户类别名称
     */
    private String custtypename;
    /**
     * 收费类别
     */
    private Integer feetype;
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
     * 部门名称
     */
    private String deptname;
    /**
     * 专业代码
     */
    private String specialtycode;
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
     * 入校日期
     */
    private String indate;
    /**
     * 离校日期
     */
    private String outdate;
    /**
     * 更新标志
     */
    private Integer updflag;
    /**
     * 1-同步数据0-非同步数据
     */
    private Integer syncflag;
    /**
     * 0-未审核1-审核失败2审核通过
     */
    private Integer chkflag;
    /**
     * 错误信息
     */
    private String errmsg;

    public void setBatchno(String batchno) {
        this.batchno = batchno;
    }

    public String getBatchno() {
        return this.batchno;
    }

    public void setSeqno(Integer seqno) {
        this.seqno = seqno;
    }

    public Integer getSeqno() {
        return this.seqno;
    }

    public void setTransdate(String transdate) {
        this.transdate = transdate;
    }

    public String getTransdate() {
        return this.transdate;
    }

    public void setOpercode(String opercode) {
        this.opercode = opercode;
    }

    public String getOpercode() {
        return this.opercode;
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

    public void setCusttypename(String custtypename) {
        this.custtypename = custtypename;
    }

    public String getCusttypename() {
        return this.custtypename;
    }

    public void setFeetype(Integer feetype) {
        this.feetype = feetype;
    }

    public Integer getFeetype() {
        return this.feetype;
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

    public void setDeptname(String deptname) {
        this.deptname = deptname;
    }

    public String getDeptname() {
        return this.deptname;
    }

    public void setSpecialtycode(String specialtycode) {
        this.specialtycode = specialtycode;
    }

    public String getSpecialtycode() {
        return this.specialtycode;
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

    public void setUpdflag(Integer updflag) {
        this.updflag = updflag;
    }

    public Integer getUpdflag() {
        return this.updflag;
    }

    public void setSyncflag(Integer syncflag) {
        this.syncflag = syncflag;
    }

    public Integer getSyncflag() {
        return this.syncflag;
    }

    public void setChkflag(Integer chkflag) {
        this.chkflag = chkflag;
    }

    public Integer getChkflag() {
        return this.chkflag;
    }

    public void setErrmsg(String errmsg) {
        this.errmsg = errmsg;
    }

    public String getErrmsg() {
        return this.errmsg;
    }
}