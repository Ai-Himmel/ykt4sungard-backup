package com.sungard.smartcard.modules.device.function;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import com.sungard.smartcard.AbstractFunction;
import com.sungard.smartcard.RetCode;
import com.sungard.smartcard.annotation.SmartCardFunction;
import com.sungard.smartcard.annotation.TransfersNodeType;
import com.sungard.smartcard.bccsvr.BccServerThread;
import com.sungard.smartcard.bccsvr.Function;
import com.sungard.smartcard.domain.Devicetmp;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.modules.device.service.DeviceService;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

/**
 * 设备导入及审核
 * 
 * @author shijia.meng
 * @version v1.00
 * @since 2012-02-21
 */
@SmartCardFunction(infotype = 3, funcnum = 11002100, name = "设备导入")
@Component
public class DeviceImportFunction extends AbstractFunction {

	private static final Logger logger = LoggerFactory
			.getLogger(DeviceImportFunction.class);

	@Autowired
	private DeviceService deviceService;

	/**
	 * 导入设备信息
	 * 
	 * @param function .
	 * @param session .
	 * @throws FunctionException
	 */
	public void add(Function function, BccServerThread session)
			throws FunctionException {
		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmmss");
		String batchNo = session.GetStringFieldByName(0,
				TransfersNodeType.sphone.getName());// 导入批次号
		Integer seqNo = session.GetIntFieldByName2(0, TransfersNodeType.lvol9
				.getName());// 导入序列号
		String deviceName = session.GetStringFieldByName(0,
				TransfersNodeType.semail.getName());// 设备名称
		Integer devicePhyType = session.GetIntFieldByName2(0,
				TransfersNodeType.lvol8.getName());// 设备类型(设备厂商代码)
		String deviceType = session.GetStringFieldByName(0,
				TransfersNodeType.scust_limit.getName());// 设备机型
		Integer deviceUsage = session.GetIntFieldByName2(0,
				TransfersNodeType.lvol0.getName());// 设备用途
		String devicePhyId = session.GetStringFieldByName(0,
				TransfersNodeType.scust_auth.getName());// 设备物理id
		String deviceAreaCode = session.GetStringFieldByName(0,
				TransfersNodeType.scust_type.getName());// 所在区域id
		Integer fDeviceId = session.GetIntFieldByName2(0,
				TransfersNodeType.lvol1.getName());// 父设备id
		Integer sysId = session.GetIntFieldByName2(0, TransfersNodeType.lvol2
				.getName());// 子系统id
		Integer svPortNo = session.GetIntFieldByName2(0,
				TransfersNodeType.lvol3.getName());// 服务器端口号（服务器接口号）
		String cardPhyType = session.GetStringFieldByName(0,
				TransfersNodeType.sstatus1.getName());// 卡片结构
		String ip = session.GetStringFieldByName(0,
				TransfersNodeType.scust_auth2.getName());// ip地址
		Integer deviceNo = session.GetIntFieldByName2(0,
				TransfersNodeType.lvol4.getName());// 设备机号
		Integer svPortCnt = session.GetIntFieldByName2(0,
				TransfersNodeType.lvol5.getName());// 端口总数
		Integer commType = session.GetIntFieldByName2(0,
				TransfersNodeType.lvol6.getName());// 通讯方式
		Integer portNo = session.GetIntFieldByName2(0, TransfersNodeType.lvol7
				.getName());// 通讯端口号（服务器SOCKET端口号）
		// 错误码 1100110001 [{}]不存在 ；1100110002 [{}]已存在 ；1100110003 [{}]不能为空
		if (batchNo == null || (batchNo != null && batchNo.equals(""))) {
			batchNo = sdf.format(new Date());
		}
		if (batchNo.length() != 14) {
			throw new FunctionException(RetCode.LENGTH_NOT_14, "批次号");
		} else if (!isNotNull(deviceName)) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "设备名称");
		} else if (!isNotNullForInt(seqNo)) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "序列号");
		} else if (!isNotNull(devicePhyId)) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "设备物理ID");
		} else if (!isNotNull(ip)) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "设备IP");
		} else if (!isNotNull(String.valueOf(sysId))) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "子系统ID");
		} else if (!isNumeric(String.valueOf(seqNo))) {
			throw new FunctionException(RetCode.IS_NOT_NUMBERIC, "序列号");
		} else if (ip!=null&&!ip.equals("")&&!isIpCorrect(ip)) {
			throw new FunctionException(RetCode.IP_NO_CORRENT, "");
		} else if (!isNotExist("t_devicetmp", "deviceName", deviceName)) {
			throw new FunctionException(RetCode.IS_EXISTS, "设备名称");
		} else if (!isNotExist("t_devicetmp", "devicePhyId", devicePhyId)) {
			throw new FunctionException(RetCode.IS_EXISTS, "设备物理ID");
		} else if (!isNotExist("t_devicetmp", "ip", ip)) {
			throw new FunctionException(RetCode.IS_EXISTS, "设备IP");
		} else if (sysId!=null&&!isSysExist(sysId)) {
			throw new FunctionException(RetCode.IS_NOT_EXISTS, "子系统");
		} else if (devicePhyType!=null&&isNotExistForInt("t_phydevice", "phyType", devicePhyType)) {
			throw new FunctionException(RetCode.IS_NOT_EXISTS, "设备类型");
		} else if (deviceAreaCode!=null&&!deviceAreaCode.equals("")&&isNotExist("t_area", "areaCode", deviceAreaCode)) {
			throw new FunctionException(RetCode.IS_NOT_EXISTS, "区域代码");
		}
		Devicetmp device = new Devicetmp();
		device.setBatchno(batchNo);
		device.setSeqno(seqNo);
		device.setDevicename(deviceName);
		device.setDevtypecode(deviceType);
		device.setDevusage(deviceUsage);
		device.setDevphyid(devicePhyId);
		device.setAreacode(deviceAreaCode);
		device.setFdeviceid(fDeviceId);
		device.setSysid(sysId);
		device.setPortno(portNo);
		device.setIp(ip);
		device.setDeviceno(deviceNo);
		device.setSvrportcnt(svPortCnt);
		device.setCommtype(commType);
		device.setSvrportno(svPortNo);
		device.setDevphytype(devicePhyType);
		device.setCardphytype(cardPhyType);
		int affected = deviceService.saveDeviceTmp(device);
		logger.debug("[{} records was affected]", affected);
	}

	/**
	 * 根据批次号、序列号更新未审核设备信息
	 * 
	 * @param function .
	 * @param session .
	 * @throws FunctionException
	 */
	public void update(Function function, BccServerThread session)
			throws FunctionException {
		String batchNo = session.GetStringFieldByName(0,
				TransfersNodeType.sphone.getName());// 导入批次号
		Integer seqNo = session.GetIntFieldByName2(0, TransfersNodeType.lvol9
				.getName());// 导入序列号
		String deviceName = session.GetStringFieldByName(0,
				TransfersNodeType.semail.getName());// 设备名称
		Integer devicePhyType = session.GetIntFieldByName2(0,
				TransfersNodeType.lvol8.getName());// 设备类型(设备厂商代码)
		Integer deviceUsage = session.GetIntFieldByName2(0,
				TransfersNodeType.lvol0.getName());// 设备用途
		String devicePhyId = session.GetStringFieldByName(0,
				TransfersNodeType.scust_auth.getName());// 设备物理id
		String deviceAreaCode = session.GetStringFieldByName(0,
				TransfersNodeType.scust_type.getName());// 所在区域id
		Integer fDeviceId = session.GetIntFieldByName2(0,
				TransfersNodeType.lvol1.getName());// 父设备id
		Integer sysId = session.GetIntFieldByName2(0, TransfersNodeType.lvol2
				.getName());// 子系统id
		Integer svPortNo = session.GetIntFieldByName2(0,
				TransfersNodeType.lvol3.getName());// 服务器端口号（服务器接口号）
		String ip = session.GetStringFieldByName(0,
				TransfersNodeType.scust_auth2.getName());// ip地址
		Integer deviceNo = session.GetIntFieldByName2(0,
				TransfersNodeType.lvol4.getName());// 设备机号
		Integer svPortCnt = session.GetIntFieldByName2(0,
				TransfersNodeType.lvol5.getName());// 端口总数
		Integer commType = session.GetIntFieldByName2(0,
				TransfersNodeType.lvol6.getName());// 通讯方式
		Integer portNo = session.GetIntFieldByName2(0, TransfersNodeType.lvol7
				.getName());// 通讯端口号（服务器SOCKET端口号）
		String deviceType = session.GetStringFieldByName(0,
				TransfersNodeType.scust_limit.getName());// 设备机型
		String cardPhyType = session.GetStringFieldByName(0,
				TransfersNodeType.sstatus1.getName());// 卡片结构

		// 错误码 1100110001 [{}]不存在 ；1100110002 [{}]已存在 ；1100110003 [{}]不能为空
		if (!isNotNull(batchNo)) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "批次号");
		} else if (!isNotNullForInt(seqNo)) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "序列号");
		} else if (!isNotNull(deviceName)) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "设备名称");
		} else if (!isNotNull(devicePhyId)) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "设备物理ID");
		} else if (!isNotNull(ip)) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "设备IP");
		} else if (!isNotNull(String.valueOf(sysId))) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "子系统ID");
		} else if (isNotExist2(batchNo, seqNo)) {
			throw new FunctionException(RetCode.IS_NOT_EXISTS, "批次号和序列号");
		} else if (!isNotExistAndNotIncludeMine(batchNo, seqNo, "IP", ip)) {
			throw new FunctionException(RetCode.IS_EXISTS, "设备IP");
		} else if (!isNotExistAndNotIncludeMine(batchNo, seqNo, "DEVICENAME",
				deviceName)) {
			throw new FunctionException(RetCode.IS_EXISTS, "设备名称");
		} else if (!isNotExistAndNotIncludeMine(batchNo, seqNo, "DEVPHYID",
				devicePhyId)) {
			throw new FunctionException(RetCode.IS_EXISTS, "物理设备ID");
		} else if (ip!=null&&!ip.equals("")&&!isIpCorrect(ip)) {
			throw new FunctionException(RetCode.IP_NO_CORRENT, "");
		} else if (sysId!=null&&!isSysExist(sysId)) {
			throw new FunctionException(RetCode.IS_NOT_EXISTS, "子系统");
		} else if (devicePhyType!=null&&isNotExistForInt("t_phydevice", "phyType", devicePhyType)) {
			throw new FunctionException(RetCode.IS_NOT_EXISTS, "设备类型");
		} else if (deviceAreaCode!=null&&!deviceAreaCode.equals("")&&isNotExist("t_area", "areaCode", deviceAreaCode)) {
			throw new FunctionException(RetCode.IS_NOT_EXISTS, "区域代码");
		}
		Devicetmp device = new Devicetmp();
		device.setBatchno(batchNo);
		device.setSeqno(seqNo);
		device.setDevicename(deviceName);
		device.setDevtypecode(deviceType);
		device.setDevusage(deviceUsage);
		device.setDevphyid(devicePhyId);
		device.setAreacode(deviceAreaCode);
		device.setFdeviceid(fDeviceId);
		device.setSysid(sysId);
		device.setPortno(portNo);
		device.setIp(ip);
		device.setDeviceno(deviceNo);
		device.setSvrportcnt(svPortCnt);
		device.setCommtype(commType);
		device.setSvrportno(svPortNo);
		device.setDevphytype(devicePhyType);
		device.setCardphytype(cardPhyType);
		int affected = deviceService.updateDeviceTmp(device);
		logger.debug("[{} records was affected]", affected);

	}

	/**
	 * 根据批次号、流水号删除未审核设备信息
	 * 
	 * @param function .
	 * @param session .
	 * @throws FunctionException
	 */
	public void delete(Function function, BccServerThread session)
			throws FunctionException {
		String batchNo = session.GetStringFieldByName(0,
				TransfersNodeType.sphone.getName());// 导入批次号
		Integer seqNo = session.GetIntFieldByName2(0, TransfersNodeType.lvol9
				.getName());// 导入序列号
		if (!isNotNull(batchNo)) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "批次号");
		} else if (!isNotNullForInt(seqNo)) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "序列号");
		} else if (isNotExist2(batchNo, seqNo)) {
			throw new FunctionException(RetCode.IS_NOT_EXISTS, "批次号和序列号");
		}
		deviceService.deleteDeviceTmp(batchNo, seqNo);
		logger.debug("[record was deleted]");
	}

	/**
	 * 根据批次号删除未审核设备信息
	 * 
	 * @param function .
	 * @param session .
	 * @throws FunctionException
	 */
	public void deleteBatch(Function function, BccServerThread session)
			throws FunctionException {
		String batchNo = session.GetStringFieldByName(0,
				TransfersNodeType.sphone.getName());// 导入批次号

		if (!isNotNull(batchNo)) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "批次号");
		} else if (isNotExist("t_devicetmp", "batchNo", batchNo)) {
			throw new FunctionException(RetCode.IS_NOT_EXISTS, "批次号");
		}
		deviceService.deleteBatchDeviceTmp(batchNo);
		logger.debug("[record was deleted]");
	}

	/**
	 * 根据用户输入关键字查找未审核设备信息
	 * 
	 * @param function .
	 * @param session .
	 * @throws FunctionException
	 */
	public void query(Function function, BccServerThread session)
			throws FunctionException {
		Devicetmp param = super.getParameter(Devicetmp.class, session);
		super.outPack(deviceService.queryByParamDeviceTmp(param),
				Devicetmp.class, session);
	}

	public void other(Function function, BccServerThread session)
			throws FunctionException {
	}

	/**
	 * 根据批次号和序列号审核未审核设备
	 * 
	 * @param function .
	 * @param session .
	 * @throws FunctionException
	 */
	public void verify(Function function, BccServerThread session)
			throws FunctionException {
		String batchNo = session.GetStringFieldByName(0,
				TransfersNodeType.sphone.getName());// 导入批次号
		int seqNo = session.GetIntFieldByName(0, TransfersNodeType.lvol9
				.getName());// 导入序列号
		if (!isNotNull(batchNo)) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "批次号");
		} else if (!isNotNullForInt(seqNo)) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "序列号");
		} else if (isNotExist2(batchNo, seqNo)) {
			deviceService.updateDeviceTmpErrorMessage(batchNo, seqNo,
					"批次号和序列号不存在");
			throw new FunctionException(RetCode.IS_NOT_EXISTS, "批次号和序列号");
		} else if (isNotExist3(batchNo, seqNo, "FDEVICEID")) {
			deviceService.updateDeviceTmpErrorMessage(batchNo, seqNo,
					"父设备号在设备表中不存在");
			throw new FunctionException(RetCode.IS_NOT_EXISTS, "父设备号");
		} else if (!isNotExist3(batchNo, seqNo, "DEVICENAME")) {
			deviceService.updateDeviceTmpErrorMessage(batchNo, seqNo,
					"设备名称在设备表中已存在");
			throw new FunctionException(RetCode.IS_EXISTS, "设备名称");
		} else if (!isNotExist3(batchNo, seqNo, "DEVPHYID")) {
			deviceService.updateDeviceTmpErrorMessage(batchNo, seqNo,
					"设备物理ID在设备表中已存在");
			throw new FunctionException(RetCode.IS_EXISTS, "设备物理ID");
		} else if (!isNotExist3(batchNo, seqNo, "IP")) {
			deviceService.updateDeviceTmpErrorMessage(batchNo, seqNo,
					"设备IP在设备表中已存在");
			throw new FunctionException(RetCode.IS_EXISTS, "设备IP");
		} else if (!isSysExist2(batchNo, seqNo)) {
			deviceService.updateDeviceTmpErrorMessage(batchNo, seqNo,
					"子系统ID在系统中不存在");
			throw new FunctionException(RetCode.IS_NOT_EXISTS, "子系统ID");
		}
		deviceService.deviceTmpIntodevice(batchNo, seqNo);
		logger.debug("[record was inserted into]");

	}

	private boolean isNotExistAndNotIncludeMine(String batchNo, int seqNo,
			String key, String value) {
		int device = deviceService.isExistAndNotIncludeMineByDeviceTmp(batchNo,
				seqNo, key, value);
		if (device >= 1) {
			return false;
		} else if (device == 0) {
			return true;
		}
		return false;
	}

	private boolean isNotNull(String string) {
		if (string == null || (string != null && string.equals(""))) {
			return false;
		} else {
			return true;
		}
	}

	private boolean isNotNullForInt(Integer in) {
		if (in == null) {
			return false;
		} else {
			return true;
		}
	}

	private boolean isNotExist(String table, String key, String value) {
		int device = deviceService.isExist(table, key, value);
		if (device >= 1) {
			return false;
		} else if (device == 0) {
			return true;
		}
		return false;
	}

	private boolean isNotExistForInt(String table, String key, int value) {
		int device = deviceService.isExistForInt(table, key, value);
		if (device >= 1) {
			return false;
		} else if (device == 0) {
			return true;
		}
		return false;
	}

	private boolean isSysExist(int value) {
		int device = deviceService.isSysExist(value);
		if (device >= 1) {
			return true;
		} else if (device == 0) {
			return false;
		}
		return false;
	}

	// 获取流水号和序列号2个字段在临时表中子系统编号，并判断该编号在子系统表中是否存在
	private boolean isSysExist2(String branchNo, int seqNo) {
		int device = deviceService.isSysExist2(branchNo, seqNo);
		if (device >= 1) {
			return true;
		} else if (device == 0) {
			return false;
		}
		return false;
	}

	private boolean isCancelled(int deviceId) {
		int device = deviceService.isDeviceCancelled(deviceId);
		if (device >= 1) {
			return true;
		} else if (device == 0) {
			return false;
		}
		return false;
	}

	private boolean isIpCorrect(String ip) {// 正则表达式判断IP正确性
		Pattern p = Pattern
				.compile("^(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])$");
		Matcher m = p.matcher(ip);
		return m.matches();
	}

	public static boolean isNumeric(String s) {
		if ((s != null) && (s != ""))
			return s.matches("^[0-9]*$");
		else
			return false;
	}

	// 根据流水号和序列号2个字段在临时表中判断是否存在
	private boolean isNotExist2(String branchNo, int seqNo) {
		int device = deviceService.isExist2ByDeviceTmp(branchNo, seqNo);
		if (device >= 1) {
			return false;
		} else if (device == 0) {
			return true;
		}
		return false;
	}

	// 获取流水号和序列号2个字段在临时表中key字段的值是否在正式表中存在
	private boolean isNotExist3(String branchNo, int seqNo, String key) {
		int device = deviceService.isExist3ByDeviceTmp(branchNo, seqNo, key);
		if (device >= 1) {
			return false;
		} else if (device == 0) {
			return true;
		}
		return false;
	}

}
