package com.sungard.smartcard.modules.device.function;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

import com.sungard.smartcard.AbstractFunction;
import com.sungard.smartcard.RetCode;
import com.sungard.smartcard.annotation.SmartCardFunction;
import com.sungard.smartcard.annotation.TransfersNodeType;
import com.sungard.smartcard.bccsvr.BccServerThread;
import com.sungard.smartcard.bccsvr.Function;
import com.sungard.smartcard.domain.Device;
import com.sungard.smartcard.exception.FunctionException;
import com.sungard.smartcard.modules.device.service.DeviceService;
import com.sungard.smartcard.modules.device.service.impl.DeviceServiceImpl;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Component;

/**
 * 设备管理，包含操作员的增删改查
 * 
 * @author shijia.meng
 * @version v1.00
 * @since 2012-02-20
 */
@SmartCardFunction(infotype = 3, funcnum = 11001100, name = "设备管理")
@Component
public class DeviceManageFunction extends AbstractFunction {

	private static final Logger logger = LoggerFactory
			.getLogger(DeviceManageFunction.class);

	@Autowired
	@Qualifier("deviceServiceImpl")
	private DeviceService deviceService;

	/**
	 * 保存设备信息
	 * 
	 * @param function .
	 * @param session .
	 * @throws FunctionException
	 */
	public void add(Function function, BccServerThread session)
			throws FunctionException {
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
		String remark = session.GetStringFieldByName(0,
				TransfersNodeType.vsmess.getName());// 备注
		String cardPhyType = session.GetStringFieldByName(0,
				TransfersNodeType.sstatus1.getName());// 卡片结构

		// 错误码 1100110001 [{}]不存在 ；1100110002 [{}]已存在 ；1100110003 [{}]不能为空
		if (!isNotNull(deviceName)) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "设备名称");
		} else if (!isNotNull(devicePhyId)) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "设备物理ID");
		} else if (!isNotNull(ip)) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "设备IP");
		} else if (!isNotNull(String.valueOf(sysId))) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "子系统ID");
		} else if (!isNotExist("t_device", "deviceName", deviceName)) {
			throw new FunctionException(RetCode.IS_EXISTS, "设备名称");
		} else if (!isNotExist("t_device", "devicePhyId", devicePhyId)) {
			throw new FunctionException(RetCode.IS_EXISTS, "设备物理ID");
		} else if (!isNotExist("t_device", "ip", ip)) {
			throw new FunctionException(RetCode.IS_EXISTS, "设备IP");
		} else if (sysId!=null&&!isSysExist(sysId)) {
			throw new FunctionException(RetCode.IS_NOT_EXISTS, "子系统");
		} else if (devicePhyType!=null&&isNotExistForInt("t_phydevice", "phyType",
				devicePhyType)) {
			throw new FunctionException(RetCode.IS_NOT_EXISTS, "设备类型");
		} else if (deviceAreaCode!=null&&!deviceAreaCode.equals("")&&isNotExist("t_area", "areaCode", deviceAreaCode)) {
			throw new FunctionException(RetCode.IS_NOT_EXISTS, "区域代码");
		} else if (ip!=null&&!ip.equals("")&&!isIpCorrect(ip)) {
			throw new FunctionException(RetCode.IP_NO_CORRENT, "");
		}
		Device device = new Device();
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
		device.setRemark(remark);
		device.setSvrportno(svPortNo);
		device.setDevphytype(devicePhyType);
		device.setCardphytype(cardPhyType);
		device.setRunstatus(0);// 设置设备运行状态为未签到
		device.setStatus("1");// 设置设备状态为正常
		int affected = deviceService.saveDevice(device);
		logger.debug("[{} records was affected]", affected);
	}

	/**
	 * 根据deviceid更新设备信息
	 * 
	 * @param function .
	 * @param session .
	 * @throws FunctionException
	 */
	public void update(Function function, BccServerThread session)
			throws FunctionException {
		Integer deviceId = session.GetIntFieldByName2(0,
				TransfersNodeType.lvol9.getName());// 设备ID
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
				TransfersNodeType.scust_limit.getName());// 通讯端口号（服务器SOCKET端口号）
		String remark = session.GetStringFieldByName(0,
				TransfersNodeType.vsmess.getName());// 备注
		String cardPhyType = session.GetStringFieldByName(0,
				TransfersNodeType.sstatus1.getName());// 卡片结构

		// 错误码 1100110001 [{}]不存在 ；1100110002 [{}]已存在 ；1100110003 [{}]不能为空
		
		if (!isNotNull(deviceName)) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "设备名称");
		} else if (!isNotNullForInt(deviceId)) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "设备ID");
		} else if (!isNotNull(devicePhyId)) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "设备物理ID");
		} else if (!isNotNull(ip)) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "设备IP");
		} else if (!isNotNullForInt(sysId)) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "子系统ID");
		} else if (isNotExistForInt("t_device", "deviceid", deviceId)) {
			throw new FunctionException(RetCode.IS_NOT_EXISTS, "设备ID");
		} else if (isCancelled(deviceId)) {// 设备已经注销
			throw new FunctionException(RetCode.DEVICE_CANCELLED, "");
		} else if (!isNotExistAndNotIncludeMine(deviceId, "IP", ip)) {
			throw new FunctionException(RetCode.IS_EXISTS, "设备IP");
		} else if (!isNotExistAndNotIncludeMine(deviceId, "DEVPHYID",
				devicePhyId)) {
			throw new FunctionException(RetCode.IS_EXISTS, "设备物理ID");
		} else if (!isNotExistAndNotIncludeMine(deviceId, "DEVICENAME",
				deviceName)) {
			throw new FunctionException(RetCode.IS_EXISTS, "设备名称");
		} else if (sysId!=null&&!isSysExist(sysId)) {
			throw new FunctionException(RetCode.IS_NOT_EXISTS, "子系统");
		} else if (devicePhyType!=null&&isNotExistForInt("t_phydevice", "phyType",
				devicePhyType)) {
			throw new FunctionException(RetCode.IS_NOT_EXISTS, "设备类型");
		} else if (deviceAreaCode!=null&&!deviceAreaCode.equals("")&&isNotExist("t_area", "areaCode", deviceAreaCode)) {
			throw new FunctionException(RetCode.IS_NOT_EXISTS, "区域代码");
		} else if (ip!=null&&!ip.equals("")&&!isIpCorrect(ip)) {
			throw new FunctionException(RetCode.IP_NO_CORRENT, "");
		}
		Device device = new Device();
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
		device.setRemark(remark);
		device.setSvrportno(svPortNo);
		device.setDevphytype(devicePhyType);
		device.setCardphytype(cardPhyType);
		device.setDeviceid(deviceId);
		int affected = deviceService.updateDevice(device);
		logger.debug("[{} records was affected]", affected);

	}

	public void delete(Function function, BccServerThread session)
			throws FunctionException {
		Integer deviceId = session.GetIntFieldByName2(0,
				TransfersNodeType.lvol9.getName());// 设备ID
		 if (!isNotNullForInt(deviceId)) {
			throw new FunctionException(RetCode.IS_NOT_NULL, "设备ID");
		} else if (isNotExistForInt("t_device", "deviceid", deviceId)) {
			throw new FunctionException(RetCode.IS_NOT_EXISTS, "设备ID");
		} else if (false) {// 商户判断
			throw new FunctionException(RetCode.DEVICE_CONNECTWITH_SHOP, "");
		}
		deviceService.deleteDevice(deviceId);
		logger.debug("[{} was deleted]", deviceId);
	}

	/**
	 * 根据用户输入关键字查找设备信息
	 * 
	 * @param function .
	 * @param session .
	 * @throws FunctionException
	 */
	public void query(Function function, BccServerThread session)
			throws FunctionException {
		Device param = super.getParameter(Device.class, session);
		super.outPack(deviceService.queryByParam(param), Device.class, session);
	}

	public void other(Function function, BccServerThread session)
			throws FunctionException {
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

	private boolean isNotExistAndNotIncludeMine(int device1, String key,
			String value) {
		int device = deviceService.isExistAndNotIncludeMineByDevice(device1,
				key, value);
		if (device >= 1) {
			return false;
		} else if (device == 0) {
			return true;
		}
		return false;
	}

	private boolean isNotExistForInt(String table, String key, Integer value) {
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

}
