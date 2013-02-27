package com.kingstargroup.form;

/**
 * AbstractMapAnalysisPoint entity provides the base persistence definition of
 * the MapAnalysisPoint entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractMapAnalysisPoint implements java.io.Serializable {

	// Fields

	private String analysisname;
	private String analysispoint;

	// Constructors

	/** default constructor */
	public AbstractMapAnalysisPoint() {
	}

	/** full constructor */
	public AbstractMapAnalysisPoint(String analysisname, String analysispoint) {
		this.analysisname = analysisname;
		this.analysispoint = analysispoint;
	}

	// Property accessors

	public String getAnalysisname() {
		return this.analysisname;
	}

	public void setAnalysisname(String analysisname) {
		this.analysisname = analysisname;
	}

	public String getAnalysispoint() {
		return this.analysispoint;
	}

	public void setAnalysispoint(String analysispoint) {
		this.analysispoint = analysispoint;
	}

}