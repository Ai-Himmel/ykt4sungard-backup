package com.sungard.ticketsys.model;

import java.io.Serializable;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;

@Entity
@Table(name = "T_TICK_BUSSER")
public class BusSer implements Serializable {

	private static final long serialVersionUID = 1L;
	private String serilNo;
	private String departTime;
	private String lineName;
	private String price;
	private String perferPrice;
	private Integer maxCount;
	
	@Id
	@Column(name = "SERIL_NO", unique = true, nullable = false)
	public String getSerilNo() {
		return serilNo;
	}
	public void setSerilNo(String serilNo) {
		this.serilNo = serilNo;
	}
	
	@Column(name = "DEPART_TIME")
	public String getDepartTime() {
		return departTime;
	}
	public void setDepartTime(String departTime) {
		this.departTime = departTime;
	}
	
	@Column(name = "lINE_NAME")
	public String getLineName() {
		return lineName;
	}
	public void setLineName(String lineName) {
		this.lineName = lineName;
	}
	
	@Column(name = "PRICE")
	public String getPrice() {
		return price;
	}
	public void setPrice(String price) {
		this.price = price;
	}
	
	@Column(name = "PERFER_PRICE")
	public String getPerferPrice() {
		return perferPrice;
	}
	public void setPerferPrice(String perferPrice) {
		this.perferPrice = perferPrice;
	}
	
	@Column(name = "MAX_COUNT")
	public Integer getMaxCount() {
		return maxCount;
	}
	public void setMaxCount(Integer maxCount) {
		this.maxCount = maxCount;
	}
	
	
	
}

