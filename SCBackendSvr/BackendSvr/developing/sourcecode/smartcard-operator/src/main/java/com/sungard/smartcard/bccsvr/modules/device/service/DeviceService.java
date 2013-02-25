package com.sungard.smartcard.bccsvr.modules.device.service;

import com.sungard.smartcard.annotation.SmartCardFunction;
import com.sungard.smartcard.bccsvr.BccServerThread;
import com.sungard.smartcard.bccsvr.ErrorCode;
import com.sungard.smartcard.bccsvr.Function;
import com.sungard.smartcard.bccsvr.modules.device.dao.DeviceDao;
import com.sungard.smartcard.bccsvr.modules.device.domain.Device;
import com.sungard.smartcard.bccsvr.service.AbstractService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.sql.SQLException;
import java.util.List;

/**
 * @author Yiming.You
 * @version v1.00
 */
@SmartCardFunction(infotype = 3, funcnum = 300001, name = "DeviceService")
public class DeviceService extends AbstractService {

    private static final Logger logger = LoggerFactory.getLogger(DeviceService.class);

    //todo use annotation to initial device dao automatically, something like @autowaired(name="deviceDao")
    private DeviceDao deviceDao = new DeviceDao();

    public int add(Function function, BccServerThread session) {
        return ErrorCode.System.OK.getCode();
    }

    public int update(Function function, BccServerThread session) {
        int retCode = ErrorCode.System.OK.getCode();
        try {
            //get request parameter from cpack
            Device param = super.getParameter(Device.class, session);
            Device device = deviceDao.queryForObject("SELECT * FROM T_DEVICE WHERE DEVICEID=?", Device.class, param.getDeviceid());
            if (device == null) {
                return super.writeError(ErrorCode.Device.DEVICE_NOT_EXIST.getCode(), function, session, param.getDeviceid());
            }
            String sql = "UPDATE T_DEVICE SET DEVICENAME=? WHERE DEVICEID=?";
            int affected = deviceDao.update(sql, param.getDevicename(), param.getDeviceid());
            logger.debug("[{} records was affected]", affected);
        } catch (SQLException e) {
            retCode = ErrorCode.System.SYSTEM_EXCEPTION.getCode();
        }
        return retCode;
    }

    public int delete(Function function, BccServerThread session) {
        return ErrorCode.System.OK.getCode();
    }

    public int query(Function function, BccServerThread session) {
        int retCode = ErrorCode.System.OK.getCode();
        try {
            //get request parameter from cpack
            Device param = super.getParameter(Device.class, session);
            String sql = "SELECT * FROM T_DEVICE";
            List<Device> devices = deviceDao.queryForList(sql, Device.class);
            super.outPack(devices, Device.class, session);
        } catch (SQLException e) {
            retCode = ErrorCode.System.SYSTEM_EXCEPTION.getCode();
        }
        return retCode;
    }

    public int other(Function function, BccServerThread session) {
        return ErrorCode.System.OK.getCode();
    }
}
