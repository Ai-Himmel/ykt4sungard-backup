/*
 * BaseDaoSpringJdbc.java  v1.00  2011-12-13
 * Peoject	sungard-common-able
 * Copyright (c) 2011 Sungard.China.HE
 *
 * Filename	:	BaseDaoSpringJdbc.java  v1.00 2011-12-13
 * Project	: 	sungard-common-able
 * Copyight	:	Copyright (c) 2011 Sungard.China.HE
 */
package com.sungard.common.dao.jdbc;

import java.io.Serializable;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import javax.annotation.Resource;

import org.apache.commons.lang.reflect.FieldUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.dao.DataAccessException;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.RowMapper;
import org.springframework.jdbc.core.namedparam.BeanPropertySqlParameterSource;
import org.springframework.jdbc.core.namedparam.NamedParameterJdbcDaoSupport;
import org.springframework.jdbc.core.namedparam.SqlParameterSource;
import org.springframework.jdbc.core.simple.SimpleJdbcInsert;
import org.springframework.jdbc.support.KeyHolder;

import com.sungard.common.dao.BaseDaoable;
import com.sungard.common.page.PropertyFilter;
import com.sungard.common.page.PropertyFilter.MatchType;

/**
 * spring jdbc dao 实现.
 * 
 * @author <a href="mailto:jianggl88@gmail.com">蒋根亮</a>
 * @version v1.00
 * @since 1.00 2011-12-13
 * 
 */
public abstract class BaseDaoSpringJdbc<T, PK extends Serializable> extends NamedParameterJdbcDaoSupport implements
        BaseDaoable<T, PK> {

    private Logger logger = LoggerFactory.getLogger(getClass());

    // 查询条件结尾字串
    private static final String PARAM_COND_SUBFIX = "Cond";

    private Class<T> persistentClass;

    // private SimpleJdbcInsert insertActor;

    public BaseDaoSpringJdbc(final Class<T> persistentClass) {
        this.persistentClass = persistentClass;
    }

    @Override
    public T get(PK id) throws DataAccessException {
        RowMapper<T> rowMapper = new BeanPropertyRowMapper<T>(this.persistentClass);
        return getJdbcTemplate().queryForObject(getSelectByPkSql(), rowMapper, id);
    }

    @Override
    public List<T> getAll() {
        RowMapper<T> rowMapper = new BeanPropertyRowMapper<T>(this.persistentClass);
        return getJdbcTemplate().query(getSelectAllSql(), rowMapper);
    }

    @Override
    public void remove(PK id) {
        getJdbcTemplate().update(getDeleteByPkSql(), id);
    }

    @Override
    public T save(T object) {
        
        // 判断单主键还是复合主键的情况
        if (object!=null && generatedKeyNames()!=null) {
            if (generatedKeyNames().length == 1) {
                try {
                    Object pk =  FieldUtils.readField(FieldUtils.getField(object.getClass(), generatedKeyNames()[0], true), object);
                    if (pk!=null) {
//                        getNamedParameterJdbcTemplate().update(get, paramSource);
                    }
                } catch (IllegalAccessException e) {
                    e.printStackTrace();
                }
            }else{
                
            }
        }
        

        SimpleJdbcInsert simpleJdbcInsert = new SimpleJdbcInsert(getJdbcTemplate());
        simpleJdbcInsert.withTableName(getTableName()).setGeneratedKeyNames(generatedKeyNames());

        SqlParameterSource parameterSource = new BeanPropertySqlParameterSource(object);
        
        if (generatedKeyNames() != null && generatedKeyNames().length == 1) {
            Number number = simpleJdbcInsert.executeAndReturnKey(parameterSource);
            logger.debug("number====={}", number.longValue());
            try {
                // Field field =
                // FieldUtils.getDeclaredField(this.persistentClass, "id",
                // true);
                FieldUtils.writeField(FieldUtils.getField(object.getClass(), generatedKeyNames()[0], true), object,
                        number.longValue());
                // FieldUtils.writeField(object, generatedKeyNames()[0],
                // number.longValue());
            } catch (IllegalAccessException e) {
                e.printStackTrace();
            }
        } else {
            KeyHolder keyHolder = simpleJdbcInsert.executeAndReturnKeyHolder(parameterSource);
            Map<String, Object> map = keyHolder.getKeys();

            // MethodUtils.invokeMethod(object, methodName, arg);
            // FieldUtils.writeDeclaredField(object, generatedKeyNames()[0],
            // value);
            for (Iterator i = map.entrySet().iterator(); i.hasNext();) {
                Map.Entry entry = (Map.Entry) i.next();
                logger.debug(" ========= keyHolder key:{} value:{} ", entry.getKey(), entry.getValue());
            }
        }
        return object;
    }

    @Override
    public void saveOrUpdate(T object) {
        // TODO Auto-generated method stub
        // getJdbcTemplate().query
    }

    @Override
    public void update(T object) {

        // 组织更新语句
        StringBuilder sBuilder = new StringBuilder("update " + getTableName() + " set ");

        // 组织更新部分
        Map<String, Object> paramMap = new HashMap<String, Object>();
        List<PropertyFilter> list = getUpdatePrams();
        boolean flag = false;
        for (PropertyFilter prop : list) {
            if (prop.hasMultiProperties()) {

            } else {
                sBuilder.append(prop.getPropertyName() + " =:" + prop.getPropertyName() + ",");
                paramMap.put(prop.getPropertyName(), prop.getMatchValue());
            }
            flag = true;
        }
        if (flag) {
            sBuilder.delete(sBuilder.length() - 1, sBuilder.length());
        }

        // 组织条件部分
        List<PropertyFilter> conds = getUpdateConds();
        if (conds != null) {
            sBuilder.append(" where 1=1 ");
            for (PropertyFilter cond : conds) {
                String[] pams = paserWhereParams(cond.getMatchType());
                if (cond.hasMultiProperties()) {
                } else {
                    sBuilder.append(" and " + cond.getPropertyName() + pams[0] + cond.getPropertyName() + pams[1]);
                    paramMap.put(cond.getPropertyName() + PARAM_COND_SUBFIX, cond.getMatchValue());
                }
            }
        }

        logger.debug("--->>--update sql=[{}], --->>--paramMap=[{}]", sBuilder.toString(), paramMap);

        int count = getNamedParameterJdbcTemplate().update(sBuilder.toString(), paramMap);
        logger.debug("--->>--update row count ={}", count);

    }

    protected abstract String getTableName();

    public abstract String getSelectByPkSql();

    public abstract String getSelectAllSql();

    public abstract String getDeleteByPkSql();

    // 新增语句
    public abstract String getInsertSql();

    // 主键名列表
    protected abstract String[] generatedKeyNames();

    // ===========更新记录使用===================================
    /**
     * 更新参数列表<br/>
     * 
     * @return
     * @since v1.00
     * @see T
     */
    protected abstract List<PropertyFilter> getUpdatePrams();

    /**
     * 被更新记录条件列表<br/>
     * 
     * @return
     * @since v1.00
     * @see T
     */
    protected abstract List<PropertyFilter> getUpdateConds();

    /**
     * 组织查询条件.<br/>
     * 
     * @param MatchType
     *            m
     * @return String[]
     * @since v1.00
     * @see T
     */
    private String[] paserWhereParams(MatchType m) {

        String[] whparamStrings = new String[2];
        switch (m) {
        case EQ:
            whparamStrings[0] = " = :";
            whparamStrings[1] = PARAM_COND_SUBFIX;
            break;
        case LIKE:
            whparamStrings[0] = " like \'%:";
            whparamStrings[1] = PARAM_COND_SUBFIX + "%\'";
            break;
        default:
            whparamStrings[0] = " = :";
            whparamStrings[1] = PARAM_COND_SUBFIX;
            break;
        }

        return whparamStrings;
    }

    @Resource
    public void setJdbcTemplate1(JdbcTemplate jdbcTemplate) {
        super.setJdbcTemplate(jdbcTemplate);
    }

}
