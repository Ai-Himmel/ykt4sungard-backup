package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_KEYS的实体类
 * CPU卡密钥表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class Keys implements Serializable {

    /**
     * 密钥ID
     */
    private Integer keyid;
    /**
     * 密钥值
     */
    private String keyval;
    /**
     * 备注
     */
    private String remark;

    public void setKeyid(Integer keyid) {
        this.keyid = keyid;
    }

    public Integer getKeyid() {
        return this.keyid;
    }

    public void setKeyval(String keyval) {
        this.keyval = keyval;
    }

    public String getKeyval() {
        return this.keyval;
    }

    public void setRemark(String remark) {
        this.remark = remark;
    }

    public String getRemark() {
        return this.remark;
    }
}