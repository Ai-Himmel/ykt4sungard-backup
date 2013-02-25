package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_CFGSHOPFEE的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Cfgshopfee implements Serializable {

    /**
     * 商户号
     */
    private Integer shopid;
    /**
     * 卡收费类别
     */
    private Integer feetype;
    /**
     * 费率
     */
    private Long feerate;
    /**
     * 操作员号
     */
    private String opercode;
    /**
     * 最后保存时间
     */
    private String lastsaved;

    public void setShopid(Integer shopid) {
        this.shopid = shopid;
    }

    public Integer getShopid() {
        return this.shopid;
    }

    public void setFeetype(Integer feetype) {
        this.feetype = feetype;
    }

    public Integer getFeetype() {
        return this.feetype;
    }

    public void setFeerate(Long feerate) {
        this.feerate = feerate;
    }

    public Long getFeerate() {
        return this.feerate;
    }

    public void setOpercode(String opercode) {
        this.opercode = opercode;
    }

    public String getOpercode() {
        return this.opercode;
    }

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }
}