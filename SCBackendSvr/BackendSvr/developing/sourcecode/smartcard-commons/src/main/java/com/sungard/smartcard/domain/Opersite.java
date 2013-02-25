package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;
import com.sungard.smartcard.annotation.TransfersNodeIn;
import com.sungard.smartcard.annotation.TransfersNodeType;

import java.io.Serializable;

/**
 * T_OPERSITE的实体类
 * 操作员站点关系表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Opersite implements Serializable {

    /**
     * 操作员号
     */
    @TransfersNodeIn(value = TransfersNodeType.sdate0, desc = "操作员编号")
    private String opercode;
    /**
     * 站点号
     */
    @TransfersNodeIn(value = TransfersNodeType.lvol0, desc = "站点号")
    private Integer siteno;
    /**
     * 最后保存时间
     */
    private String lastsaved;

    public void setOpercode(String opercode) {
        this.opercode = opercode;
    }

    public String getOpercode() {
        return this.opercode;
    }

    public void setSiteno(Integer siteno) {
        this.siteno = siteno;
    }

    public Integer getSiteno() {
        return this.siteno;
    }

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }
}