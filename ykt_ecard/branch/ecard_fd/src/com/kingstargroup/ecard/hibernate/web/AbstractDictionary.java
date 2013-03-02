package com.kingstargroup.ecard.hibernate.web;

import java.io.Serializable;
import com.kingstargroup.ecard.hibernate.web.WebDictionaryKey;


public class AbstractDictionary extends 
		com.kingstargroup.ecard.common.BasicPersistence implements Serializable {
	/**
	 * The cached hash code value for this instance. Settting to 0 triggers
	 * re-calculation.
	 */
	private int hashValue = 0;

	/** The simple primary key value. */
	private WebDictionaryKey id;

	/** The value of the simple dictName property. */
	private java.lang.String dicName;

	/** The value of the simple dictCaption property. */
	private java.lang.String dicCaption;
	
	public AbstractDictionary(){
		
	}
	
	public AbstractDictionary(WebDictionaryKey id){
		this.id = id;
	}

	
	public java.lang.String getDicCaption() {
		return dicCaption;
	}

	public void setDicCaption(java.lang.String dicCaption) {
		this.dicCaption = dicCaption;
	}

	public java.lang.String getDicName() {
		return dicName;
	}

	public void setDicName(java.lang.String dicName) {
		this.dicName = dicName;
	}

	public int getHashValue() {
		return hashValue;
	}

	public void setHashValue(int hashValue) {
		this.hashValue = hashValue;
	}

	public WebDictionaryKey getId() {
		return id;
	}

	public void setId(WebDictionaryKey id) {
		this.id = id;
	}

}
