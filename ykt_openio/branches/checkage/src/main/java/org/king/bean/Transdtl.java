package org.king.bean;

import java.io.Serializable;

/**
 * .
 * User: Yiming.You
 * Date: 2011-4-28
 */
public class Transdtl implements Serializable {
    private String ecardId;

    private String requestTime;

    private String ecardNum;

    private String userName;

    private String fullName;

    private String amount;

    private String ecardMachineId;

    private String ecardIp;

    private String inpayamountId;

    private String replyTime;

    private String ackTime;

    /**
     * don't delete this constructor
     */
    public Transdtl() {
    }

    public String getEcardId() {
        return ecardId;
    }

    public void setEcardId(String ecardId) {
        this.ecardId = ecardId;
    }

    public String getRequestTime() {
        return requestTime;
    }

    public void setRequestTime(String requestTime) {
        this.requestTime = requestTime;
    }

    public String getEcardNum() {
        return ecardNum;
    }

    public void setEcardNum(String ecardNum) {
        this.ecardNum = ecardNum;
    }

    public String getUserName() {
        return userName;
    }

    public void setUserName(String userName) {
        this.userName = userName;
    }

    public String getFullName() {
        return fullName;
    }

    public void setFullName(String fullName) {
        this.fullName = fullName;
    }

    public String getAmount() {
        return amount;
    }

    public void setAmount(String amount) {
        this.amount = amount;
    }

    public String getEcardMachineId() {
        return ecardMachineId;
    }

    public void setEcardMachineId(String ecardMachineId) {
        this.ecardMachineId = ecardMachineId;
    }

    public String getEcardIp() {
        return ecardIp;
    }

    public void setEcardIp(String ecardIp) {
        this.ecardIp = ecardIp;
    }

    public String getInpayamountId() {
        return inpayamountId;
    }

    public void setInpayamountId(String inpayamountId) {
        this.inpayamountId = inpayamountId;
    }

    public String getReplyTime() {
        return replyTime;
    }

    public void setReplyTime(String replyTime) {
        this.replyTime = replyTime;
    }

    public String getAckTime() {
        return ackTime;
    }

    public void setAckTime(String ackTime) {
        this.ackTime = ackTime;
    }

    @Override
    public String toString() {
        return "Transdtl{" +
                "ecardId=" + ecardId +
                ", requestTime=" + requestTime +
                ", ecardNum=" + ecardNum +
                ", userName=" + userName +
                ", fullName=" + fullName +
                ", amount=" + amount +
                ", ecardMachineId=" + ecardMachineId +
                ", ecardIp=" + ecardIp + 
                ", inpayamountId=" + inpayamountId +
                ", replyTime=" + replyTime +
                ", ackTime=" + ackTime +
                '}';
    }
}
