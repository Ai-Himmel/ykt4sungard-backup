package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;
import com.sungard.smartcard.annotation.TransfersNodeOut;
import com.sungard.smartcard.annotation.TransfersNodeType;

import java.io.Serializable;

/**
 * T_AREA的实体类
 * 区域表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Area implements Serializable {

    /**
     * 区域编号 3
     */

    @TransfersNodeOut(value = TransfersNodeType.sroom_no, desc = "区域编号")    //4
    private String areacode;
    /**
     * 区域名称 60
     */
    @TransfersNodeOut(value = TransfersNodeType.sbankname, desc = "区域名称")//81
    private String areaname;
    /**
     * 上级区域代码 3
     */
    @TransfersNodeOut(value = TransfersNodeType.sroom_no2, desc = "上级区域代码")//4
    private String fareacode;
    /**
     * 原区域代码 3
     */
    @TransfersNodeOut(value = TransfersNodeType.snation_code, desc = "原区域代码 ")//4
    private String oldareacode;
    /**
     * 区域级别  integer
     */
    @TransfersNodeOut(value = TransfersNodeType.lcert_code, desc = "区域级别")//int 4
    private Integer arealevel;
    /**
     * 地址 240
     */
    @TransfersNodeOut(value = TransfersNodeType.vsvarstr0, desc = "地址")//256
    private String addr;
    /**
     * 备注 240
     */
    @TransfersNodeOut(value = TransfersNodeType.vsvarstr1, desc = "备注")//256
    private String remark;


    public void setAreacode(String areacode) {
        this.areacode = areacode;
    }

    public String getAreacode() {
        return this.areacode;
    }

    public void setAreaname(String areaname) {
        this.areaname = areaname;
    }

    public String getAreaname() {
        return this.areaname;
    }

    public void setFareacode(String fareacode) {
        this.fareacode = fareacode;
    }

    public String getFareacode() {
        return this.fareacode;
    }

    public void setOldareacode(String oldareacode) {
        this.oldareacode = oldareacode;
    }

    public String getOldareacode() {
        return this.oldareacode;
    }

    public void setArealevel(Integer arealevel) {
        this.arealevel = arealevel;
    }

    public Integer getArealevel() {
        return this.arealevel;
    }

    public void setAddr(String addr) {
        this.addr = addr;
    }

    public String getAddr() {
        return this.addr;
    }

    public void setRemark(String remark) {
        this.remark = remark;
    }

    public String getRemark() {
        return this.remark;
    }
}