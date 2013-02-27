package org.king.monitor.domain;

/**
 * MapSysDictionary entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class MapSysDictionary extends AbstractMapSysDictionary implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MapSysDictionary() {
	}

	/** minimal constructor */
	public MapSysDictionary(MapSysDictionaryId id) {
		super(id);
	}

	/** full constructor */
	public MapSysDictionary(MapSysDictionaryId id, String dictName,
			String dictCaption, String dictCode) {
		super(id, dictName, dictCaption, dictCode);
	}

}
