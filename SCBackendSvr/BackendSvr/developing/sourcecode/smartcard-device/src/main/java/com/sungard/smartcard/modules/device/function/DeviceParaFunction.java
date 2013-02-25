package com.sungard.smartcard.modules.device.function;

import com.sungard.smartcard.AbstractFunction;
import com.sungard.smartcard.annotation.SmartCardFunction;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * 设备参数控制，主要用于给设备下发任务，如开门，下传时钟等
 *
 * @author Yiming.You
 * @version v1.00
 * @since 12-2-24
 */
@SmartCardFunction(infotype = 3, funcnum = 11005100, name = "设备参数控制")
public class DeviceParaFunction extends AbstractFunction {
    private static final Logger logger = LoggerFactory.getLogger(DeviceParaFunction.class);


}
