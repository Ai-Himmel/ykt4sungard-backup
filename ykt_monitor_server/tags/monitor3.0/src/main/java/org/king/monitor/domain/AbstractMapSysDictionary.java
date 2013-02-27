package org.king.monitor.domain;

/**
 * AbstractMapSysDictionary entity provides the base persistence definition of
 * the MapSysDictionary entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractMapSysDictionary implements java.io.Serializable {

	// Fields

	private MapSysDictionaryId id;
	private String dictName;
	private String dictCaption;
	private String dictCode;

	// Constructors

	/** default constructor */
	public AbstractMapSysDictionary() {
	}

	/** minimal constructor */
	public AbstractMapSysDictionary(MapSysDictionaryId id) {
		this.id = id;
	}

	/** full constructor */
	public AbstractMapSysDictionary(MapSysDictionaryId id, String dictName,
			String dictCaption, String dictCode) {
		this.id = id;
		this.dictName = dictName;
		this.dictCaption = dictCaption;
		this.dictCode = dictCode;
	}

	// Property accessors

	public MapSysDictionaryId getId() {
		return this.id;
	}

	public void setId(MapSysDictionaryId id) {
		this.id = id;
	}

	public String getDictName() {
		return this.dictName;
	}

	public void setDictName(String dictName) {
		this.dictName = dictName;
	}

	public String getDictCaption() {
		return this.dictCaption;
	}

	public void setDictCaption(String dictCaption) {
		this.dictCaption = dictCaption;
	}

	public String getDictCode() {
		return this.dictCode;
	}

	public void setDictCode(String dictCode) {
		this.dictCode = dictCode;
	}

}