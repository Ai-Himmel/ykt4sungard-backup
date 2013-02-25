package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_SUBJECT的实体类
 * 科目表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Subject implements Serializable {

    /**
     * 科目号
     */
    private String subjno;
    /**
     * 科目名称
     */
    private String subjname;
    /**
     * 科目类型
     */
    private Integer subjtype;
    /**
     * 科目余额方向
     */
    private Integer balflag;
    /**
     * 上级科目号
     */
    private String fsubjno;
    /**
     * 科目级别
     */
    private Integer subjlevel;
    /**
     * 末级标志
     */
    private String endflag;

    public void setSubjno(String subjno) {
        this.subjno = subjno;
    }

    public String getSubjno() {
        return this.subjno;
    }

    public void setSubjname(String subjname) {
        this.subjname = subjname;
    }

    public String getSubjname() {
        return this.subjname;
    }

    public void setSubjtype(Integer subjtype) {
        this.subjtype = subjtype;
    }

    public Integer getSubjtype() {
        return this.subjtype;
    }

    public void setBalflag(Integer balflag) {
        this.balflag = balflag;
    }

    public Integer getBalflag() {
        return this.balflag;
    }

    public void setFsubjno(String fsubjno) {
        this.fsubjno = fsubjno;
    }

    public String getFsubjno() {
        return this.fsubjno;
    }

    public void setSubjlevel(Integer subjlevel) {
        this.subjlevel = subjlevel;
    }

    public Integer getSubjlevel() {
        return this.subjlevel;
    }

    public void setEndflag(String endflag) {
        this.endflag = endflag;
    }

    public String getEndflag() {
        return this.endflag;
    }
}