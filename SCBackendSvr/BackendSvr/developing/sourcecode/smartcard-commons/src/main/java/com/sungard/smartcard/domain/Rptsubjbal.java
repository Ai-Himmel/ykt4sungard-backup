package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_RPTSUBJBAL的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Rptsubjbal implements Serializable {

    /**
     * 结算日期
     */
    private String accdate;
    /**
     * 科目号
     */
    private String subjno;
    /**
     * 期初余额
     */
    private Double beginbal;
    /**
     * 期初余额方向
     */
    private Integer beginbalflag;
    /**
     * 借方发生额
     */
    private Double dramt;
    /**
     * 贷方发生额
     */
    private Double cramt;
    /**
     * 期末余额
     */
    private Double endbal;
    /**
     * 期末余额方向
     */
    private Integer endbalflag;

    public void setAccdate(String accdate) {
        this.accdate = accdate;
    }

    public String getAccdate() {
        return this.accdate;
    }

    public void setSubjno(String subjno) {
        this.subjno = subjno;
    }

    public String getSubjno() {
        return this.subjno;
    }

    public void setBeginbal(Double beginbal) {
        this.beginbal = beginbal;
    }

    public Double getBeginbal() {
        return this.beginbal;
    }

    public void setBeginbalflag(Integer beginbalflag) {
        this.beginbalflag = beginbalflag;
    }

    public Integer getBeginbalflag() {
        return this.beginbalflag;
    }

    public void setDramt(Double dramt) {
        this.dramt = dramt;
    }

    public Double getDramt() {
        return this.dramt;
    }

    public void setCramt(Double cramt) {
        this.cramt = cramt;
    }

    public Double getCramt() {
        return this.cramt;
    }

    public void setEndbal(Double endbal) {
        this.endbal = endbal;
    }

    public Double getEndbal() {
        return this.endbal;
    }

    public void setEndbalflag(Integer endbalflag) {
        this.endbalflag = endbalflag;
    }

    public Integer getEndbalflag() {
        return this.endbalflag;
    }
}