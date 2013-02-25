package com.sungard.smartcard.modules.device.service;

import java.util.List;

import com.sungard.smartcard.domain.Device;
import com.sungard.smartcard.domain.Devicetmp;
import com.sungard.smartcard.domain.Feetype;
import com.sungard.smartcard.domain.Operator;

/**
 * 设备管理业务处理接口
 *
 * @author shijia.meng
 * @version v1.00
 * @since 2012-02-21
 */
public interface DeviceService {
	//根据key字段查找table表中value值的记录是否存在，用于校验业务
	public int isExist(String table,String key,String value);
	//根据key字段查找table表中value值的记录是否存在，用于校验业务
	public int isExistForInt(String table,String key,int value);
	
	//根据设备id查找设备是否已经注销
	public int isDeviceCancelled(int deviceId);
	
	//查找t_subsystem表中sysid字段的value值的记录是否存在，用于校验业务
	public int isSysExist(int value);
	
	//保存设备记录
	public int saveDevice(Device device);
	
	//保存设备临时记录
	public int saveDeviceTmp(Devicetmp device);
	
	//更新设备临时记录
	public int updateDeviceTmp(Devicetmp device);
	
	//更新设备记录
	public int updateDevice(Device device);
	//根据key字段查找device表中value值的记录是否存在(不包含自身设备记录)，用于校验业务
	public int isExistAndNotIncludeMineByDevice(int device,String key,String value);
	
	//根据key字段查找devicetmp表中value值的记录是否存在(不包含自身设备记录)，用于校验业务
	public int isExistAndNotIncludeMineByDeviceTmp(String batchNo,int seqNo,String key,String value);

	//删除设备记录
	public int deleteDevice(int deviceId);
	
	//根据流水号和序列号2个字段查找devicetmp表中的记录是否存在，用于校验业务
	public int isExist2ByDeviceTmp(String branchNo,int seqNo);
	
	//根据批次号和流水号删除设备临时表记录
	public int deleteDeviceTmp(String branchNo,int seqNo);
	
	//根据批次号删除设备临时表记录
	public int deleteBatchDeviceTmp(String branchNo);
	
	//根据批次号和序列号更新设备临时表记录中error字段信息
	public int updateDeviceTmpErrorMessage(String branchNo,int seqNo,String errorMessage);
	
	// 获取流水号和序列号2个字段在临时表中key字段的值是否在正式表中存在
	public int isExist3ByDeviceTmp(String branchNo,int seqNo,String key);
	
	// 获取流水号和序列号2个字段在临时表中子系统编号，并判断该编号在子系统表中是否存在
	public int isSysExist2(String branchNo,int seqNo);
	//获取该流水号和序列号的记录并将临时表的记录插入到正式表中
	public int deviceTmpIntodevice(String branchNo,int seqNo);
	
	public List<Device> queryByParam(Device device);
	
	public List<Devicetmp> queryByParamDeviceTmp(Devicetmp device); 
	
}
