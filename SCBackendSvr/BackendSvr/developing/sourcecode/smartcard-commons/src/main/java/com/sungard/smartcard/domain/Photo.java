package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_PHOTO的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Photo implements Serializable {

    /**
     * 客户号
     */
    private Integer custid;
    /**
     * 学工号
     */
    private String stuempno;
    /**
     * 照片
     */
    private Byte[] photo;
    /**
     * 小照片
     */
    private Byte[] minphoto;
    /**
     * 拍照日期
     */
    private String photodate;
    /**
     * 拍照时间
     */
    private String phototime;
    /**
     * 是否有卡
     */
    private String ifcard;
    /**
     * 制卡日期
     */
    private String makecarddate;
    /**
     * 制卡时间
     */
    private String makecardtime;
    /**
     * 更新时间
     */
    private String photoexacttime;

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

    public void setPhoto(Byte[] photo) {
        this.photo = photo;
    }

    public Byte[] getPhoto() {
        return this.photo;
    }

    public void setMinphoto(Byte[] minphoto) {
        this.minphoto = minphoto;
    }

    public Byte[] getMinphoto() {
        return this.minphoto;
    }

    public void setPhotodate(String photodate) {
        this.photodate = photodate;
    }

    public String getPhotodate() {
        return this.photodate;
    }

    public void setPhototime(String phototime) {
        this.phototime = phototime;
    }

    public String getPhototime() {
        return this.phototime;
    }

    public void setIfcard(String ifcard) {
        this.ifcard = ifcard;
    }

    public String getIfcard() {
        return this.ifcard;
    }

    public void setMakecarddate(String makecarddate) {
        this.makecarddate = makecarddate;
    }

    public String getMakecarddate() {
        return this.makecarddate;
    }

    public void setMakecardtime(String makecardtime) {
        this.makecardtime = makecardtime;
    }

    public String getMakecardtime() {
        return this.makecardtime;
    }

    public void setPhotoexacttime(String photoexacttime) {
        this.photoexacttime = photoexacttime;
    }

    public String getPhotoexacttime() {
        return this.photoexacttime;
    }
}