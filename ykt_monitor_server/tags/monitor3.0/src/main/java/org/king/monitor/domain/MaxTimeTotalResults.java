package org.king.monitor.domain;

public class MaxTimeTotalResults extends AbstractResult {
	/** The value of the simple analysistime property. */
	private java.lang.String MapDeviceTable;
	private java.lang.String MapServiceException;
	private java.lang.String MapSerialexceptTable;
	public java.lang.String getMapDeviceTable() {
		return MapDeviceTable;
	}
	public void setMapDeviceTable(java.lang.String mapDeviceTable) {
		MapDeviceTable = mapDeviceTable;
	}
	public java.lang.String getMapServiceException() {
		return MapServiceException;
	}
	public void setMapServiceException(java.lang.String mapServiceException) {
		MapServiceException = mapServiceException;
	}
	public java.lang.String getMapSerialexceptTable() {
		return MapSerialexceptTable;
	}
	public void setMapSerialexceptTable(java.lang.String mapSerialexceptTable) {
		MapSerialexceptTable = mapSerialexceptTable;
	}
	/**
	 * @param mapDeviceTable
	 * @param mapServiceException
	 * @param mapSerialexceptTable
	 */
	public MaxTimeTotalResults(String mapDeviceTable,
			String mapServiceException, String mapSerialexceptTable) {
		MapDeviceTable = mapDeviceTable;
		MapServiceException = mapServiceException;
		MapSerialexceptTable = mapSerialexceptTable;
	}


}
