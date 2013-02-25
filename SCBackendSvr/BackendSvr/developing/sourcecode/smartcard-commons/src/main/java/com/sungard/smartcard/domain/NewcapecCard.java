package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_NEWCAPEC_CARD的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class NewcapecCard implements Serializable {

    /**
     *
     */
    private String cardphyno;
    /**
     *
     */
    private Integer apptype;
    /**
     *
     */
    private Integer feetype;
    /**
     *
     */
    private Integer custtype;
    /**
     *
     */
    private Integer custid;
    /**
     *
     */
    private Integer idtype;
    /**
     *
     */
    private Integer dpscnt;
    /**
     *
     */
    private Integer transdate;
    /**
     *
     */
    private Integer daymaxamt;
    /**
     *
     */
    private Integer publishid;
    /**
     *
     */
    private Integer showcardno;
    /**
     *
     */
    private Integer subsidyno;
    /**
     *
     */
    private Integer cardstruct;
    /**
     *
     */
    private Integer schoolcode;

    public void setCardphyno(String cardphyno) {
        this.cardphyno = cardphyno;
    }

    public String getCardphyno() {
        return this.cardphyno;
    }

    public void setApptype(Integer apptype) {
        this.apptype = apptype;
    }

    public Integer getApptype() {
        return this.apptype;
    }

    public void setFeetype(Integer feetype) {
        this.feetype = feetype;
    }

    public Integer getFeetype() {
        return this.feetype;
    }

    public void setCusttype(Integer custtype) {
        this.custtype = custtype;
    }

    public Integer getCusttype() {
        return this.custtype;
    }

    public void setCustid(Integer custid) {
        this.custid = custid;
    }

    public Integer getCustid() {
        return this.custid;
    }

    public void setIdtype(Integer idtype) {
        this.idtype = idtype;
    }

    public Integer getIdtype() {
        return this.idtype;
    }

    public void setDpscnt(Integer dpscnt) {
        this.dpscnt = dpscnt;
    }

    public Integer getDpscnt() {
        return this.dpscnt;
    }

    public void setTransdate(Integer transdate) {
        this.transdate = transdate;
    }

    public Integer getTransdate() {
        return this.transdate;
    }

    public void setDaymaxamt(Integer daymaxamt) {
        this.daymaxamt = daymaxamt;
    }

    public Integer getDaymaxamt() {
        return this.daymaxamt;
    }

    public void setPublishid(Integer publishid) {
        this.publishid = publishid;
    }

    public Integer getPublishid() {
        return this.publishid;
    }

    public void setShowcardno(Integer showcardno) {
        this.showcardno = showcardno;
    }

    public Integer getShowcardno() {
        return this.showcardno;
    }

    public void setSubsidyno(Integer subsidyno) {
        this.subsidyno = subsidyno;
    }

    public Integer getSubsidyno() {
        return this.subsidyno;
    }

    public void setCardstruct(Integer cardstruct) {
        this.cardstruct = cardstruct;
    }

    public Integer getCardstruct() {
        return this.cardstruct;
    }

    public void setSchoolcode(Integer schoolcode) {
        this.schoolcode = schoolcode;
    }

    public Integer getSchoolcode() {
        return this.schoolcode;
    }
}