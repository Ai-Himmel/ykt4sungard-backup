package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_BANKCHKDATE的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class Bankchkdate implements Serializable {

    /**
     * 交易日期
     */
    private String chkdate;
    /**
     * 核对标志
     */
    private Integer chkflag;

    public void setChkdate(String chkdate) {
        this.chkdate = chkdate;
    }

    public String getChkdate() {
        return this.chkdate;
    }

    public void setChkflag(Integer chkflag) {
        this.chkflag = chkflag;
    }

    public Integer getChkflag() {
        return this.chkflag;
    }
}