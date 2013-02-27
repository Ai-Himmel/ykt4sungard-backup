package org.king.monitor.domain;

public class MaxTimeResult extends AbstractResult {
	/** The value of the simple analysistime property. */
	private java.lang.String analysistime;

	public java.lang.String getAnalysistime() {
		return analysistime;
	}

	public void setAnalysistime(java.lang.String analysistime) {
		this.analysistime = analysistime;
	}

	/**
	 * 
	 */
	public MaxTimeResult() {
	}

	public MaxTimeResult(String analysistime) {
		this.analysistime = analysistime;
	}

}
