package com.sungard.smartcard.modules.system.service.impl;

import com.sungard.smartcard.domain.Dpsoper;
import com.sungard.smartcard.domain.Dpsopercard;
import com.sungard.smartcard.modules.system.dao.DpsoperDao;
import com.sungard.smartcard.modules.system.service.DpsoperService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.io.Serializable;
import java.util.List;

/**
 * 充值操作员，充值操作员与卡绑定关系的基本业务操作实现
 *
 * @author Yiming.You
 * @version v1.00
 * @since 12-2-20
 */
@Service
public class DpsoperServiceImpl implements DpsoperService {

    private static final Logger logger = LoggerFactory.getLogger(DpsoperServiceImpl.class);

    @Autowired
    private DpsoperDao dpsoperDao;

    public void setDpsoperDao(DpsoperDao dpsoperDao) {
        this.dpsoperDao = dpsoperDao;
    }

    /**
     * 查找所有的充值操作员与卡绑定关系
     *
     * @return 符合条件的充值操作员与卡绑定关系
     */
    @Override
    public List<Dpsoper> findAllDpsoper() {
        return dpsoperDao.findAllDpsoper();
    }

    /**
     * 根据Dpsopercard的属性查找数据库中是否已存在对应记录
     *
     * @param key   Dpsopercard的属性
     * @param value 属性对应的值
     * @return 返回1表示存在，0表示不存在
     */
    @Override
    public int isExistDpsopercard(String key, Serializable value) {
        return dpsoperDao.isExistDpsopercard(key, value);
    }

    @Override
    public int deleteDpsopercard(String opercode) {
        return dpsoperDao.deleteDpsopercard(opercode);
    }

    /**
     * 保存充值操作员与卡的绑定关系
     *
     * @param dpsopercard 充值操作员与卡绑定关系
     * @return .
     */
    @Override
    public int saveDpsopercard(Dpsopercard dpsopercard) {
        return dpsoperDao.saveDpsopercard(dpsopercard);
    }

    /**
     * 根据卡号查找操作员与卡绑定关系，一张卡只能与一个操作员绑定
     * @param cardno
     * @return
     */
    public Dpsopercard getDpsopercard(String opercode,int cardno){
        //
        return null;
    }
}
