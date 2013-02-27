package org.king.monitor.domain;


/**
 * TDictionaryId entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TDictionaryId extends AbstractTDictionaryId implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TDictionaryId() {
	}

	/** full constructor */
	public TDictionaryId(long dicttype, String dictval) {
		super(dicttype, dictval);
	}

}
