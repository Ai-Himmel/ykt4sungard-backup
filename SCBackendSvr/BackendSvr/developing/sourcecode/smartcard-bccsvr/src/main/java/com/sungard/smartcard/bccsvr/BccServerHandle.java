/*
 * BccServerHandle.java  v1.00  2011-12-19
 * Peoject	sungard-smartcard-bccsvr
 * Copyright (c) 2011 Sungard.China.HE
 *
 * Filename	:	BccServerHandle.java  v1.00 2011-12-19
 * Project	: 	sungard-smartcard-bccsvr
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.smartcard.bccsvr;

import org.apache.commons.lang.StringUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.kingstar.bcc.bccsvr;

/**
 * 服务器服务数据区句柄资源.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-19
 * 
 */
public class BccServerHandle {

    private Logger logger = LoggerFactory.getLogger(BccServerHandle.class);
    /*
     * 内部本地方法类对象
     */
    private bccsvr bccsvr;

    private BccServer bccServer;

    /*
     * 该资源的生成句柄
     */
    private long handle = -1;

    private String XpackFile = "";

    public BccServerHandle() {
    }

    public BccServerHandle(BccServer bccServer) {
        this.bccServer = bccServer;
        this.bccsvr = this.bccServer.GetResource();
    }

    /**
     * 根据配置文件创建数据交换的数据区handle.<br/>
     * 
     * @return
     * @since v1.00
     * @see ServerServiceHandle#createHandle(String);
     */
    public long createHandle() {
        logger.debug("--->>> cpack.dat path ={}", XpackFile);
        
        return createHandle(XpackFile);
    }

    /**
     * 创建数据交换的数据区handle.<br/>
     * 
     * @param XpackFile
     * @return handle
     * @since v1.00
     * @see com.kingstar.bcc.bccsvr#NewXpackHandle(byte[]);
     */
    public long createHandle(String XpackFile) {
        if (StringUtils.isNotBlank(XpackFile)) {
            handle = getBccsvr().NewXpackHandle(XpackFile.getBytes());
        }
        if (handle == 0) {
            logger.error("--->>> createHandle error -----");
        }
        logger.debug("--->>> createHandle (long)handle = {}, this={} ", handle, this);
        return handle;
    }

    /**
     * 服务数据区句柄.<br/>
     * 
     * @return
     * @since v1.00
     */
    public long getHandle() {
        return handle;
    }

    public void setHandle(long handle) {
        this.handle = handle;
    }

    /**
     * 获取服务对象.<br/>
     * 
     * @return bccsvr
     * @since v1.00
     * @see com.kingstar.bcc.bccsvr;
     */
    public bccsvr getBccsvr() {
        return bccsvr;
    }

    // @Autowired
    public void setBccsvr(bccsvr bccsvr) {
        this.bccsvr = bccsvr;
    }

    public String getXpackFile() {
        return XpackFile;
    }

    public void setXpackFile(String xpackFile) {
        XpackFile = xpackFile;
    }
}
