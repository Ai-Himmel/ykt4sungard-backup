package com.kingstargroup.ecard.hibernate.dictionary;

/**
 * AbstractTDictionary entity provides the base persistence definition of the
 * TDictionary entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTDictionary implements java.io.Serializable {

	// Fields

	private TDictionaryId id;
	private String dicttypename;
	private String dictcaption;

	// Constructors

	/** default constructor */
	public AbstractTDictionary() {
	}

	/** minimal constructor */
	public AbstractTDictionary(TDictionaryId id) {
		this.id = id;
	}

	/** full constructor */
	public AbstractTDictionary(TDictionaryId id, String dicttypename,
			String dictcaption) {
		this.id = id;
		this.dicttypename = dicttypename;
		this.dictcaption = dictcaption;
	}

	// Property accessors

	public TDictionaryId getId() {
		return this.id;
	}

	public void setId(TDictionaryId id) {
		this.id = id;
	}

	public String getDicttypename() {
		return this.dicttypename;
	}

	public void setDicttypename(String dicttypename) {
		this.dicttypename = dicttypename;
	}

	public String getDictcaption() {
		return this.dictcaption;
	}

	public void setDictcaption(String dictcaption) {
		this.dictcaption = dictcaption;
	}

}