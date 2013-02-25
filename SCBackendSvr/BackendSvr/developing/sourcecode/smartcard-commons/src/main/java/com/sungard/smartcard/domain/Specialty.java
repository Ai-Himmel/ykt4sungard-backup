package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;
import com.sungard.smartcard.annotation.TransfersNodeIn;
import com.sungard.smartcard.annotation.TransfersNodeOut;
import com.sungard.smartcard.annotation.TransfersNodeType;

import java.io.Serializable;

/**
 * T_SPECIALTY的实体类
 * 专业表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Specialty implements Serializable {

    /**
     * 专业代码  30
     */
    @TransfersNodeIn(value = TransfersNodeType.scert_no, desc = "专业代码")//51
    @TransfersNodeOut(value = TransfersNodeType.scert_no, desc = "专业代码")
    private String specialtycode;


    /**
     * 专业名称 60
     */

    @TransfersNodeIn(value = TransfersNodeType.sall_name, desc = "专业名称")//81
    @TransfersNodeOut(value = TransfersNodeType.sall_name, desc = "专业名称")
    private String specialtyname;


    /**
     * 使用标志 0：未使用，1:使用
     * 长度 1
     */

    private String useflag;
    /**
     * 最后保存时间 30
     */
    @TransfersNodeOut(value = TransfersNodeType.scert_no2, desc = "最新保存时间")//51
    private String lastsaved;

    public void setSpecialtycode(String specialtycode) {
        this.specialtycode = specialtycode;
    }

    public String getSpecialtycode() {
        return this.specialtycode;
    }

    public void setSpecialtyname(String specialtyname) {
        this.specialtyname = specialtyname;
    }

    public String getSpecialtyname() {
        return this.specialtyname;
    }

    public void setUseflag(String useflag) {
        this.useflag = useflag;
    }

    public String getUseflag() {
        return this.useflag;
    }

    public void setLastsaved(String lastsaved) {
        this.lastsaved = lastsaved;
    }

    public String getLastsaved() {
        return this.lastsaved;
    }
}