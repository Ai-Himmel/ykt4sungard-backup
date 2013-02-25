package com.sungard.smartcard.domain;

import com.sungard.smartcard.annotation.TransfersElement;

import java.io.Serializable;


/**
 * T_THIRDPAY_JJLINK的实体类
 *
 * @author Yiming.You
 * @version v1.00
 * @since 2012-02-27
 */
@TransfersElement
public class ThirdpayJjlink implements Serializable {

    /**
     * 一卡通充值流水号
     */
    private Double ecardId;
    /**
     * 充值请求发起的时间 YYYY-MM-DD HH:mm:ss
     */
    private String requestTime;
    /**
     * 一卡通号码
     */
    private String ecardNum;
    /**
     * 被充值用户id
     */
    private String username;
    /**
     * 被充值用户真实姓名
     */
    private String fullname;
    /**
     * 充值金额，单位：元
     */
    private Double amount;
    /**
     * 充值设备终端编号
     */
    private Integer ecardMachineId;
    /**
     * 一卡通服务器IP地址
     */
    private String ecardIp;
    /**
     * 充值记录号
     */
    private String inpayamountId;
    /**
     * 返回时间 YYYY-MM-DD HH:mm:ss
     */
    private String replyTime;
    /**
     * 确认时间 YYYY-MM-DD HH:mm:ss
     */
    private String ackTime;
    /**
     * 状态（1 请求充值,2 充值成功,3充值失败  4 请求数据不完整 5 对账补充值成功 6 对账补充值失败 7 对账成功）
     */
    private String status;
    /**
     * 最后更新时间
     */
    private String updateTime;
    /**
     * 对账次数
     */
    private Integer checkNum;

    public void setEcardId(Double ecardId) {
        this.ecardId = ecardId;
    }

    public Double getEcardId() {
        return this.ecardId;
    }

    public void setRequestTime(String requestTime) {
        this.requestTime = requestTime;
    }

    public String getRequestTime() {
        return this.requestTime;
    }

    public void setEcardNum(String ecardNum) {
        this.ecardNum = ecardNum;
    }

    public String getEcardNum() {
        return this.ecardNum;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getUsername() {
        return this.username;
    }

    public void setFullname(String fullname) {
        this.fullname = fullname;
    }

    public String getFullname() {
        return this.fullname;
    }

    public void setAmount(Double amount) {
        this.amount = amount;
    }

    public Double getAmount() {
        return this.amount;
    }

    public void setEcardMachineId(Integer ecardMachineId) {
        this.ecardMachineId = ecardMachineId;
    }

    public Integer getEcardMachineId() {
        return this.ecardMachineId;
    }

    public void setEcardIp(String ecardIp) {
        this.ecardIp = ecardIp;
    }

    public String getEcardIp() {
        return this.ecardIp;
    }

    public void setInpayamountId(String inpayamountId) {
        this.inpayamountId = inpayamountId;
    }

    public String getInpayamountId() {
        return this.inpayamountId;
    }

    public void setReplyTime(String replyTime) {
        this.replyTime = replyTime;
    }

    public String getReplyTime() {
        return this.replyTime;
    }

    public void setAckTime(String ackTime) {
        this.ackTime = ackTime;
    }

    public String getAckTime() {
        return this.ackTime;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getStatus() {
        return this.status;
    }

    public void setUpdateTime(String updateTime) {
        this.updateTime = updateTime;
    }

    public String getUpdateTime() {
        return this.updateTime;
    }

    public void setCheckNum(Integer checkNum) {
        this.checkNum = checkNum;
    }

    public Integer getCheckNum() {
        return this.checkNum;
    }
}