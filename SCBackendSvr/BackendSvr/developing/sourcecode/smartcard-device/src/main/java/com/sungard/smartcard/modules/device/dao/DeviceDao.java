package com.sungard.smartcard.modules.device.dao;

import com.sungard.smartcard.domain.Device;
import com.sungard.smartcard.domain.Devicetmp;

import java.util.List;

/**
 * 充值操作员,充值操作员与卡绑定关系的基本数据库操作接口
 *
 * @author shijia.meng
 * @version v1.00
 * @since 12-2-20
 */
public interface DeviceDao {
    public int isExist(String table,String key,String value);
    public int isExistForInt(String table,String key,int value);
    public int isExistSys(int value);
    public int saveDevice(Device device);
    public int isDeviceCancelled(int deviceId);
    public int isExistDeviceAndNotIncludeMineByDevice(int device,String key,String value);
    public int updateDevice(Device device);
    public int updateDeviceTmp(Devicetmp device);
    public int updateDeviceStatus(int deviceId);
    public int deleteDeviceHeartBeat(int deviceId);
  //  public int isExistDeviceTmp(String key,String value);
	public int saveDeviceTmp(Devicetmp device);
	public int isExistDeviceAndNotIncludeMineByDeviceTmp(String batchNo,int seqNo,String key,String value);
	public int isExist2DeviceTmp(String branchNo,int seqNo);
	public int deleteDeviceTmp(String branchNo,int seqNo); 
	public int deleteBatchDeviceTmp(String branchNo); 
	public int updateDeviceTmpErrorMessage(String branchNo,int seqNo,String errorMessage); 
	public int isExist3DeviceTmp(String branchNo,int seqNo,String key);
	public int isExistSys2(String branchNo,int seqNo);
	public int deviceTmpIntodevice(String branchNo,int seqNo);
	public List<Device> findDeviceDao(Device device);
	public List<Devicetmp> findDeviceTmpDao(Devicetmp device);
	
}
