/**
 * 
 */
package com.kingstargroup.fdykt.dto;

import java.io.Serializable;

/**
 * @author jackey
 * 
 */
public class TTifSubsidyDTO implements Serializable {
	private Integer subsidyNo;
    private Integer custNo;
    private String batchNo;
    private Integer seqno;
    private String operCode;
    private Integer cardNo;
    private String summary;
    private String expireDate;
    private Integer billType;
    private String billNo;
    private double amount;
    private String subsidytype;
    private String txDate;
    private String txTime;
    private String getDate;
    private String getTime;
    private String status;
    private String brokerId;
    private String brokerName;
	public double getAmount() {
		return amount;
	}
	public void setAmount(double amount) {
		this.amount = amount;
	}
	public String getBatchNo() {
		return batchNo;
	}
	public void setBatchNo(String batchNo) {
		this.batchNo = batchNo;
	}
	public String getBillNo() {
		return billNo;
	}
	public void setBillNo(String billNo) {
		this.billNo = billNo;
	}
	public Integer getBillType() {
		return billType;
	}
	public void setBillType(Integer billType) {
		this.billType = billType;
	}
	public String getBrokerId() {
		return brokerId;
	}
	public void setBrokerId(String brokerId) {
		this.brokerId = brokerId;
	}
	public String getBrokerName() {
		return brokerName;
	}
	public void setBrokerName(String brokerName) {
		this.brokerName = brokerName;
	}
	public Integer getCardNo() {
		return cardNo;
	}
	public void setCardNo(Integer cardNo) {
		this.cardNo = cardNo;
	}
	public Integer getCustNo() {
		return custNo;
	}
	public void setCustNo(Integer custNo) {
		this.custNo = custNo;
	}
	public String getExpireDate() {
		return expireDate;
	}
	public void setExpireDate(String expireDate) {
		this.expireDate = expireDate;
	}
	public String getGetDate() {
		return getDate;
	}
	public void setGetDate(String getDate) {
		this.getDate = getDate;
	}
	public String getGetTime() {
		return getTime;
	}
	public void setGetTime(String getTime) {
		this.getTime = getTime;
	}
	public String getOperCode() {
		return operCode;
	}
	public void setOperCode(String operCode) {
		this.operCode = operCode;
	}
	public Integer getSeqno() {
		return seqno;
	}
	public void setSeqno(Integer seqno) {
		this.seqno = seqno;
	}
	public String getStatus() {
		return status;
	}
	public void setStatus(String status) {
		this.status = status;
	}

	public Integer getSubsidyNo() {
		return subsidyNo;
	}
	public void setSubsidyNo(Integer subsidyNo) {
		this.subsidyNo = subsidyNo;
	}
	public String getSubsidytype() {
		return subsidytype;
	}
	public void setSubsidytype(String subsidytype) {
		this.subsidytype = subsidytype;
	}
	public String getSummary() {
		return summary;
	}
	public void setSummary(String summary) {
		this.summary = summary;
	}
	public String getTxDate() {
		return txDate;
	}
	public void setTxDate(String txDate) {
		this.txDate = txDate;
	}
	public String getTxTime() {
		return txTime;
	}
	public void setTxTime(String txTime) {
		this.txTime = txTime;
	}
	

}
