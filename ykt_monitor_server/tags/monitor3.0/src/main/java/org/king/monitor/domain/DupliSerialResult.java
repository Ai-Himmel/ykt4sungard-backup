/**
 * 
 */
package org.king.monitor.domain;

/**<br>
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. <br>
 * File name: DupliSerialResult.java<br>
 * Description: <br>
 * Modify History����Change Log��:  <br>
 * �������ͣ��������޸ĵȣ�   ��������     ������    �������ݼ���<br>
 * ����  				 2005-11-2  ������    <br>
 * <p>
 *
 * @author      ������
 * @version     1.0
 * @since       1.0
 */
public class DupliSerialResult extends AbstractResult {


    /** The value of the SERIAL_NO component of this composite id. */
    private long serialNo;
    
    /** The value of the DEVICE_ID component of this composite id. */
    private java.lang.String deviceId;

    /** The value of the CARD_NO component of this composite id. */
    private long cardNo;
	
	/**
	 * @param no
	 * @param id
	 * @param no2
	 */
	public DupliSerialResult(long serialNo, String deviceId, long cardNo) {
		this.cardNo = cardNo;
		this.deviceId = deviceId;
		this.serialNo = serialNo;
	}

	public long getCardNo() {
		return cardNo;
	}

	public void setCardNo(long cardNo) {
		this.cardNo = cardNo;
	}

	public java.lang.String getDeviceId() {
		return deviceId;
	}

	public void setDeviceId(java.lang.String deviceId) {
		this.deviceId = deviceId;
	}

	public long getSerialNo() {
		return serialNo;
	}

	public void setSerialNo(long serialNo) {
		this.serialNo = serialNo;
	}


}
