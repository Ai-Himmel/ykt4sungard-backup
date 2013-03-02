package com.kingstargroup.fdykt.dto;

import java.sql.Blob;

public class NewCardInfoDTO implements java.io.Serializable {

	private long custid;
	private String custname;
	private String stuempno;
	private String showcardno;
	private String oldcardphyid;
	private int status;
	private Blob minphoto;
	/**
	 * @return the custid
	 */
	public long getCustid() {
		return custid;
	}
	/**
	 * @param custid the custid to set
	 */
	public void setCustid(long custid) {
		this.custid = custid;
	}
	/**
	 * @return the custname
	 */
	public String getCustname() {
		return custname;
	}
	/**
	 * @param custname the custname to set
	 */
	public void setCustname(String custname) {
		this.custname = custname;
	}
	/**
	 * @return the stuempno
	 */
	public String getStuempno() {
		return stuempno;
	}
	/**
	 * @param stuempno the stuempno to set
	 */
	public void setStuempno(String stuempno) {
		this.stuempno = stuempno;
	}
	public String getOldcardphyid() {
		return oldcardphyid;
	}
	public void setOldcardphyid(String oldcardphyid) {
		this.oldcardphyid = oldcardphyid;
	}
	/**
	 * @return the showcardno
	 */
	public String getShowcardno() {
		return showcardno;
	}
	/**
	 * @param showcardno the showcardno to set
	 */
	public void setShowcardno(String showcardno) {
		this.showcardno = showcardno;
	}
	/**
	 * @return the minphoto
	 */
	public Blob getMinphoto() {
		return minphoto;
	}
	/**
	 * @param minphoto the minphoto to set
	 */
	public void setMinphoto(Blob minphoto) {
		this.minphoto = minphoto;
	}
	public int getStatus() {
		return status;
	}
	public void setStatus(int status) {
		this.status = status;
	}
	
	
	
}
