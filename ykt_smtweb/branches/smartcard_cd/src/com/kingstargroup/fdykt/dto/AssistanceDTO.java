/**
 * 
 */
package com.kingstargroup.fdykt.dto;

import java.io.Serializable;

/**
 * @author jackey
 * 
 */
public class AssistanceDTO implements Serializable {
	// 补助批次号
	private String id;

	// 客户号
	private int custno;

	// 发生日期
	private String accur_date;

	// 发生时间
	private String accur_time;

	// 摘要
	private String comment;

	// 截止日期
	private String deadline;

	// 补助金额（单位：元）
	private float amount;

	// 状态(1-未领2-已领)
	private String status;

	public String getAccur_date() {
		return accur_date;
	}

	public void setAccur_date(String accur_date) {
		this.accur_date = accur_date;
	}

	public String getAccur_time() {
		return accur_time;
	}

	public void setAccur_time(String accur_time) {
		this.accur_time = accur_time;
	}

	public float getAmount() {
		return amount;
	}

	public void setAmount(float amount) {
		this.amount = amount;
	}

	public String getComment() {
		return comment;
	}

	public void setComment(String comment) {
		this.comment = comment;
	}

	public int getCustno() {
		return custno;
	}

	public void setCustno(int custno) {
		this.custno = custno;
	}

	public String getDeadline() {
		return deadline;
	}

	public void setDeadline(String deadline) {
		this.deadline = deadline;
	}

	public String getId() {
		return id;
	}

	public void setId(String id) {
		this.id = id;
	}

	public String getStatus() {
		return status;
	}

	public void setStatus(String status) {
		this.status = status;
	}

}
