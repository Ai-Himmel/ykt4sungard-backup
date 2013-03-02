package com.kingstargroup.conference.hibernate.form;

/**
 * TDictionary entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TDictionary extends AbstractTDictionary implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TDictionary() {
	}

	/** minimal constructor */
	public TDictionary(TDictionaryId id) {
		super(id);
	}

	/** full constructor */
	public TDictionary(TDictionaryId id, String dicttypename, String dictcaption) {
		super(id, dicttypename, dictcaption);
	}

}
