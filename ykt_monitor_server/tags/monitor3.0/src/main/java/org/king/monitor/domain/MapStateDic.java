package org.king.monitor.domain;

/**
 * MapStateDic entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class MapStateDic extends AbstractMapStateDic implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MapStateDic() {
	}

	/** full constructor */
	public MapStateDic(String stateid, String statename, String tagcode,
			long showcolor, long errornot, String errorcode) {
		super(stateid, statename, tagcode, showcolor, errornot, errorcode);
	}

}
