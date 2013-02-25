package com.sungard.smartcard.modules.device.dao.impl;

import com.sungard.smartcard.domain.Device;
import com.sungard.smartcard.domain.Devicetmp;
import com.sungard.smartcard.modules.device.dao.DeviceDao;
import com.sungard.smartcard.modules.device.dao.DeviceParaDao;
import org.apache.commons.lang.StringUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;

import java.util.ArrayList;
import java.util.List;

/**
 * 设备参数管理的数据库操作实现
 *
 * @author Yiming.You
 * @version v1.00
 * @since 12-2-24
 */
@Repository
public class DeviceParaDaoImpl implements DeviceParaDao {

    @Autowired
    private JdbcTemplate jdbcTemplate;
}
