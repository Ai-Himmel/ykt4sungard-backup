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
	// �������κ�
	private String id;

	// �ͻ���
	private int custno;

	// ��������
	private String accur_date;

	// ����ʱ��
	private String accur_time;

	// ժҪ
	private String comment;

	// ��ֹ����
	private String deadline;

	// ��������λ��Ԫ��
	private float amount;

	// ״̬(1-δ��2-����)
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
