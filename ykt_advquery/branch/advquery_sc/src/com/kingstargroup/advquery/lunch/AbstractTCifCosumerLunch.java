package com.kingstargroup.advquery.lunch;


/**
 * AbstractTCifCosumerLunch entity provides the base persistence definition of
 * the TCifCosumerLunch entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractTCifCosumerLunch implements java.io.Serializable {

	// Fields
	private Integer cutId;
	private Integer cutType;
	private Integer cutState;
	private String cutName;
	private String stuempNo;
	private String sex;
	private String manId;
	private Integer cardId;
	private Integer state;
	private String phyId; 
	private Integer lunchType;
	
	public Integer getLunchType() {
		return lunchType;
	}
	public void setLunchType(Integer lunchType) {
		this.lunchType = lunchType;
	}
	public Integer getCutId() {
		return cutId;
	}
	public void setCutId(Integer cutId) {
		this.cutId = cutId;
	}
	public Integer getCutType() {
		return cutType;
	}
	public void setCutType(Integer cutType) {
		this.cutType = cutType;
	}
	public Integer getCutState() {
		return cutState;
	}
	public void setCutState(Integer cutState) {
		this.cutState = cutState;
	}
	public String getCutName() {
		return cutName;
	}
	public void setCutName(String cutName) {
		this.cutName = cutName;
	}
	public String getStuempNo() {
		return stuempNo;
	}
	public void setStuempNo(String stuempNo) {
		this.stuempNo = stuempNo;
	}
	public String getSex() {
		return sex;
	}
	public void setSex(String sex) {
		this.sex = sex;
	}
	public String getManId() {
		return manId;
	}
	public void setManId(String manId) {
		this.manId = manId;
	}
	public Integer getCardId() {
		return cardId;
	}
	public void setCardId(Integer cardId) {
		this.cardId = cardId;
	}
	public Integer getState() {
		return state;
	}
	public void setState(Integer state) {
		this.state = state;
	}
	public String getPhyId() {
		return phyId;
	}
	public void setPhyId(String phyId) {
		this.phyId = phyId;
	}

}