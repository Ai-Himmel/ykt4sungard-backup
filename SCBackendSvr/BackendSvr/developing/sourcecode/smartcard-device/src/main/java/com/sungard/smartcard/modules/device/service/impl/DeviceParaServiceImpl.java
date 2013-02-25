package com.sungard.smartcard.modules.device.service.impl;

import com.sungard.smartcard.domain.Device;
import com.sungard.smartcard.domain.Devicetmp;
import com.sungard.smartcard.modules.device.dao.DeviceDao;
import com.sungard.smartcard.modules.device.service.DeviceParaService;
import com.sungard.smartcard.modules.device.service.DeviceService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;

/**
 * 设备参数管理业务处理实现
 * 
 * @author Yiming.You
 * @version v1.00
 * @since 12-2-24
 */
@Service
public class DeviceParaServiceImpl implements DeviceParaService {

	@Autowired
	@Qualifier("deviceDaoImpl")
	private DeviceDao deviceDao;

}
