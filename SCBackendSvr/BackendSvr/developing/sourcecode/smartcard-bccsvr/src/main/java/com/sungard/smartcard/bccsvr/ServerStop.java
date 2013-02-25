/*
 * ServerStop.java  v1.00  2011-12-19
 * Peoject	sungard-smartcard-bccsvr
 * Copyright (c) 2011 Sungard.China.HE
 *
 * Filename	:	ServerStop.java  v1.00 2011-12-19
 * Project	: 	sungard-smartcard-bccsvr
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.bccsvr;

import java.util.Date;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * 停止服务.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-19
 * 
 */
public class ServerStop {

    private static Logger logger = LoggerFactory.getLogger(ServerStop.class);

    public static void main(String[] args) {
//        logger.info("stop {}", BccServer.GetInstance());
        logger.info("-------servier stop begin {}", new Date());
//        BccServer.GetInstance().stopService();
        logger.info("-------servier stopted    {}", new Date());
    }

}
