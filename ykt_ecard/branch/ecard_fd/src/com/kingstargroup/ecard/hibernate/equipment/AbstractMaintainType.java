package com.kingstargroup.ecard.hibernate.equipment;

import java.io.Serializable;

public class AbstractMaintainType extends com.kingstargroup.ecard.common.BasicPersistence implements Serializable {

	private String id;
	private Maintain maintainId;
	private String  dicValue;
	
	public AbstractMaintainType(){
		
	}
    public AbstractMaintainType(String id){
		this.id=id;
	}

	public String getDicValue() {
		return dicValue;
	}
	public void setDicValue(String dicValue) {
		this.dicValue = dicValue;
	}

	public String getId() {
		return id;
	}

	public void setId(String id) {
		this.id = id;
	}

	public Maintain getMaintainId() {
		return maintainId;
	}
	public void setMaintainId(Maintain maintainId) {
		this.maintainId = maintainId;
	}

}
