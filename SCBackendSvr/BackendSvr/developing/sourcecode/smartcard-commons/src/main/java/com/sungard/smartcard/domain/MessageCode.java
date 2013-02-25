package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;

/**
 * T_MESSAGE_CODE的实体类
 * 返回消息码表
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-20
 */
@TransfersElement
public class MessageCode implements Serializable {

    /**
     * 消息码
     */
    private Integer retCode;
    /**
     * 消息
     */
    private String retMsg;

    public void setRetCode(Integer retCode) {
        this.retCode = retCode;
    }

    public Integer getRetCode() {
        return this.retCode;
    }

    public void setRetMsg(String retMsg) {
        this.retMsg = retMsg;
    }

    public String getRetMsg() {
        return this.retMsg;
    }

    @Override
    public String toString() {
        return "MessageCode{" +
                "retCode=" + retCode +
                ", retMsg='" + retMsg + '\'' +
                '}';
    }
}