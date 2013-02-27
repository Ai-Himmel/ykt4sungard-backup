package org.king.monitor.domain;

/**
 * MapAnalysisPoint entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class MapAnalysisPoint extends AbstractMapAnalysisPoint implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MapAnalysisPoint() {
	}

	/** full constructor */
	public MapAnalysisPoint(String analysisname, String analysispoint) {
		super(analysisname, analysispoint);
	}

}
