package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_MODIFYINFO的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Modifyinfo implements Serializable {

    /**
     * 客户号
     */
    private Integer custid;
    /**
     * 学工号
     */
    private String stuempno;
    /**
     * 录取通知号
     */
    private String enrollno;
    /**
     * 修改日期
     */
    private String modifydate;
    /**
     * 修改时间
     */
    private String modifytime;

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

    public void setEnrollno(String enrollno) {
        this.enrollno = enrollno;
    }

    public String getEnrollno() {
        return this.enrollno;
    }

    public void setModifydate(String modifydate) {
        this.modifydate = modifydate;
    }

    public String getModifydate() {
        return this.modifydate;
    }

    public void setModifytime(String modifytime) {
        this.modifytime = modifytime;
    }

    public String getModifytime() {
        return this.modifytime;
    }
}