package com.sungard.smartcard.modules.device.service.impl;

import java.util.ArrayList;
import java.util.List;

import com.sungard.smartcard.domain.Device;
import com.sungard.smartcard.domain.Devicetmp;
import com.sungard.smartcard.domain.Feetype;
import com.sungard.smartcard.domain.Operator;
import com.sungard.smartcard.modules.device.dao.DeviceDao;
import com.sungard.smartcard.modules.device.dao.impl.DeviceDaoImpl;
import com.sungard.smartcard.modules.device.service.DeviceService;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

/**
 * 设备管理业务处理实现
 * 
 * @author shijia.meng
 * @version v1.00
 * @since 2012-02-21
 */
@Service
public class DeviceServiceImpl implements DeviceService {

	@Autowired
	@Qualifier("deviceDaoImpl")
	private DeviceDao deviceDao;

	@Override
	public int isExist(String table,String key, String value) {
		int i = deviceDao.isExist(table,key, value);
		return i;
	}

	@Override
	public int isSysExist(int value) {
		int i = deviceDao.isExistSys(value);
		return i;
	}

	@Override
	@Transactional
	public int saveDevice(Device device) {
		return deviceDao.saveDevice(device);
	}

	@Override
	public int isExistForInt(String table,String key, int value) {
		int i = deviceDao.isExistForInt(table,key, value);
		return i;
	}

	@Override
	public int isDeviceCancelled(int deviceId) {
		int i = deviceDao.isDeviceCancelled(deviceId);
		return i;
	}

	@Override
	public int isExistAndNotIncludeMineByDevice(int device, String key,
			String value) {
		int i = deviceDao.isExistDeviceAndNotIncludeMineByDevice(device, key,
				value);
		return i;
	}

	@Override
	@Transactional
	public int updateDevice(Device device) {
		return deviceDao.updateDevice(device);
	}

	@Override
	@Transactional
	public int deleteDevice(int deviceId) {
		deviceDao.updateDeviceStatus(deviceId);
		deviceDao.deleteDeviceHeartBeat(deviceId);
		return 0;
	}


	@Override
	@Transactional
	public int saveDeviceTmp(Devicetmp device) {
		return deviceDao.saveDeviceTmp(device);
	}

	@Override
	public int isExistAndNotIncludeMineByDeviceTmp(String batchNo, int seqNo,
			String key, String value) {
		int i = deviceDao.isExistDeviceAndNotIncludeMineByDeviceTmp(batchNo,
				seqNo, key, value);
		return i;
	}

	@Override
	@Transactional
	public int updateDeviceTmp(Devicetmp device) {
		return deviceDao.updateDeviceTmp(device);
	}

	@Override
	public int isExist2ByDeviceTmp(String branchNo, int seqNo) {
		int i = deviceDao.isExist2DeviceTmp(branchNo, seqNo);
		return i;
	}

	@Override
	@Transactional
	public int deleteDeviceTmp(String branchNo, int seqNo) {
		return deviceDao.deleteDeviceTmp(branchNo, seqNo);
	}

	@Override
	@Transactional
	public int deleteBatchDeviceTmp(String branchNo) {
		return deviceDao.deleteBatchDeviceTmp(branchNo);
	}

	@Override
	@Transactional
	public int updateDeviceTmpErrorMessage(String branchNo, int seqNo,
			String errorMessage) {
		return deviceDao.updateDeviceTmpErrorMessage(branchNo, seqNo,
				errorMessage);
	}

	@Override
	public int isExist3ByDeviceTmp(String branchNo, int seqNo, String key) {
		int i = deviceDao.isExist3DeviceTmp(branchNo, seqNo, key);
		return i;
	}

	@Override
	public int isSysExist2(String branchNo, int seqNo) {
		int i = deviceDao.isExistSys2(branchNo, seqNo);
		return i;
	}

	@Override
	@Transactional
	public int deviceTmpIntodevice(String branchNo, int seqNo) {
		deviceDao.deviceTmpIntodevice(branchNo, seqNo);
		deviceDao.deleteDeviceTmp(branchNo, seqNo);
		return 0;
	}

	@Override
	public List<Device> queryByParam(Device device) {

		return deviceDao.findDeviceDao(device);
	}

	@Override
	public List<Devicetmp> queryByParamDeviceTmp(Devicetmp device) {
		return deviceDao.findDeviceTmpDao(device);
	}

}
