package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;
import com.sungard.smartcard.annotation.TransfersNodeIn;
import com.sungard.smartcard.annotation.TransfersNodeOut;
import com.sungard.smartcard.annotation.TransfersNodeType;

import java.io.Serializable;

/**
 * T_FEETYPE的实体类
 * 收费类别表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Feetype implements Serializable {

    /**
     * 收费类别
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol1, desc = "fasdf")
    @TransfersNodeOut(value = TransfersNodeType.lvol1, desc = "fasdf")
    private Integer feetype;
    /**
     * 收费名称
     */
    @TransfersNodeIn(value = TransfersNodeType.scusttypes, desc = "")
    @TransfersNodeOut(value = TransfersNodeType.scusttypes, desc = "")
    private String feename;
    /**
     * 是否收搭伙费:1-收0-不收
     */
    @TransfersNodeIn(value = TransfersNodeType.sname, desc = "")
    @TransfersNodeOut(value = TransfersNodeType.sname, desc = "")
    private String boardfeeflag;
    /**
     * 使用标志
     */
    private String useflag;
    /**
     * 备注
     */
    private String remark;
    /**
     * 预收搭伙费费率，如果收10%，则填写0.1
     */
    @TransfersNodeIn(value = TransfersNodeType.damt1, desc = "")
    @TransfersNodeOut(value = TransfersNodeType.damt1, desc = "")
    private Double boardfeerate;

    public void setFeetype(Integer feetype) {
        this.feetype = feetype;
    }

    public Integer getFeetype() {
        return this.feetype;
    }

    public void setFeename(String feename) {
        this.feename = feename;
    }

    public String getFeename() {
        return this.feename;
    }

    public void setBoardfeeflag(String boardfeeflag) {
        this.boardfeeflag = boardfeeflag;
    }

    public String getBoardfeeflag() {
        return this.boardfeeflag;
    }

    public void setUseflag(String useflag) {
        this.useflag = useflag;
    }

    public String getUseflag() {
        return this.useflag;
    }

    public void setRemark(String remark) {
        this.remark = remark;
    }

    public String getRemark() {
        return this.remark;
    }

    public void setBoardfeerate(Double boardfeerate) {
        this.boardfeerate = boardfeerate;
    }

    public Double getBoardfeerate() {
        return this.boardfeerate;
    }
}