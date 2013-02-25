package com.sungard.smartcard.bccsvr.dao;

import com.sungard.modules.utils.db.dao.DBSessionDao;
import com.sungard.smartcard.bccsvr.utils.NamedParameterUtils;
import org.apache.commons.dbutils.QueryRunner;
import org.apache.commons.dbutils.ResultSetHandler;
import org.apache.commons.dbutils.handlers.ArrayHandler;
import org.apache.commons.dbutils.handlers.ArrayListHandler;
import org.apache.commons.dbutils.handlers.BeanHandler;
import org.apache.commons.dbutils.handlers.BeanListHandler;
import org.apache.commons.dbutils.handlers.MapHandler;
import org.apache.commons.dbutils.handlers.MapListHandler;
import org.apache.commons.dbutils.handlers.ScalarHandler;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.sql.SQLException;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

/**
 * JDBC operations interface usable on Java 5 and above, exposing a
 * set of common JDBC operations, whose interface is simplified
 * through the use of varargs and autoboxing.
 *
 * @author Yiming.You
 * @version v1.00
 */
public class JdbcTemplate extends DBSessionDao implements JdbcOperations {

    private static final Logger logger = LoggerFactory.getLogger(JdbcTemplate.class);

    /**
     * Default maximum number of entries for this template's SQL cache: 256
     */
    public static final int DEFAULT_CACHE_LIMIT = 256;

    protected volatile int cacheLimit = DEFAULT_CACHE_LIMIT;

    //todo set fetch size
    protected volatile int fetchSize = 1000;

    /**
     * Cache of original SQL String to ParsedSql representation
     */
    protected final Map<String, ParsedSql> parsedSqlCache =
            new LinkedHashMap<String, ParsedSql>(DEFAULT_CACHE_LIMIT, 0.75f, true) {
                @Override
                protected boolean removeEldestEntry(Map.Entry<String, ParsedSql> eldest) {
                    return size() > getCacheLimit();
                }
            };

    @Override
    public int queryForInt(String sql, Map<String, Object> args) throws SQLException {
        return query(sql, args).intValue();
    }

    @Override
    public int queryForInt(String sql, Object... args) throws SQLException {
        return query(sql, args).intValue();
    }

    @Override
    public long queryForLong(String sql, Map<String, ?> args) throws SQLException {
        return query(sql, args).longValue();
    }

    @Override
    public long queryForLong(String sql, Object... args) throws SQLException {
        return query(sql, args).longValue();
    }

    public <T> List<T> queryForList(String sql, Class<T> elementType, Object... args) throws SQLException {
        return query(sql, new BeanListHandler<T>(elementType), args);
    }

    public <T> List<T> queryForList(String sql, Class<T> elementType, Map<String, Object> args) throws SQLException {
        return query(sql, new BeanListHandler<T>(elementType), args);
    }

    public List<Map<String, Object>> queryForList(String sql, Object... args) throws SQLException {
        return query(sql, new MapListHandler(), args);
    }

    public List<Map<String, Object>> queryForList(String sql, Map<String, Object> args) throws SQLException {
        return query(sql, new MapListHandler(), args);
    }

    public <T> T queryForObject(String sql, Class<T> elementType, Object... args) throws SQLException {
        return query(sql, new BeanHandler<T>(elementType), args);
    }

    public <T> T queryForObject(String sql, Class<T> elementType, Map<String, Object> args) throws SQLException {
        return query(sql, new BeanHandler<T>(elementType), args);
    }

    public Map<String, Object> queryForObject(String sql, Object... args) throws SQLException {
        return query(sql, new MapHandler(), args);
    }

    public Map<String, Object> queryForObject(String sql, Map<String, Object> args) throws SQLException {
        return query(sql, new MapHandler(), args);
    }

    public List<Object[]> queryForArrayList(String sql, Object... args) throws SQLException {
        return query(sql, new ArrayListHandler(), args);
    }

    public List<Object[]> queryForArrayList(String sql, Map<String, Object> args) throws SQLException {
        return query(sql, new ArrayListHandler(), args);
    }

    public Object[] queryForArray(String sql, Object... args) throws SQLException {
        return query(sql, new ArrayHandler(), args);
    }

    public Object[] queryForArray(String sql, Map<String, Object> args) throws SQLException {
        return query(sql, new ArrayHandler(), args);
    }

    public <T> T query(String sql, ResultSetHandler<T> rsh, Object... args) throws SQLException {
        logger.debug("Executing query SQL [{}]", sql);
        QueryRunner runner = new QueryRunner();
        return runner.query(getConnection(), sql, rsh, args);
    }

    public <T> T query(String sql, ResultSetHandler<T> rsh, Map<String, Object> args) throws SQLException {
        logger.debug("Executing named query SQL [{}]", sql);
        QueryRunner runner = new QueryRunner();
        ParsedSql parsedSql = getParsedSql(sql);
        String sqlToUse = NamedParameterUtils.substituteNamedParameters(parsedSql, args);
        Object[] valueArray = NamedParameterUtils.buildValueArray(parsedSql, args);
        return runner.query(getConnection(), sqlToUse, rsh, valueArray);
    }

    public Number query(String sql, Map<String, Object> args) throws SQLException {
        Object value = query(sql, new ScalarHandler(), args);
        if (value instanceof Number) {
            return (Number) value;
        } else {
            throw new SQLException("can't get a number with given sql");
        }
    }

    public Number query(String sql, Object... args) throws SQLException {
        Object value = query(sql, new ScalarHandler(), args);
        if (value instanceof Number) {
            return (Number) value;
        } else {
            throw new SQLException("can't get a number with given sql");
        }
    }

    @Override
    public int update(String sql, Map<String, Object> args) throws SQLException {
        logger.debug("Executing named update SQL [{}]", sql);
        QueryRunner runner = new QueryRunner();
        ParsedSql parsedSql = getParsedSql(sql);
        String sqlToUse = NamedParameterUtils.substituteNamedParameters(parsedSql, args);
        Object[] valueArray = NamedParameterUtils.buildValueArray(parsedSql, args);
        return runner.update(getConnection(), sqlToUse, valueArray);
    }

    @Override
    public int update(String sql, Object... args) throws SQLException {
        logger.debug("Executing update SQL [{}]", sql);
        QueryRunner runner = new QueryRunner();
        return runner.update(getConnection(), sql, args);
    }

    @Override
    public int[] batchUpdate(String sql, Map<String, ?>[] batchValues) {
        //todo
        return new int[0];
    }

    @Override
    public int[] batchUpdate(String sql, List<Object[]> batchArgs) {
        //todo
        return new int[0];
    }

    /**
     * Obtain a parsed representation of the given SQL statement.
     *
     * @param sql the original SQL
     * @return a representation of the parsed SQL statement
     */
    protected ParsedSql getParsedSql(String sql) {
        if (getCacheLimit() <= 0) {
            return NamedParameterUtils.parseSqlStatement(sql);
        }
        synchronized (this.parsedSqlCache) {
            ParsedSql parsedSql = this.parsedSqlCache.get(sql);
            if (parsedSql == null) {
                parsedSql = NamedParameterUtils.parseSqlStatement(sql);
                this.parsedSqlCache.put(sql, parsedSql);
            }
            return parsedSql;
        }
    }

    /**
     * Return the maximum number of entries for this template's SQL cache.
     */

    protected int getCacheLimit() {
        return this.cacheLimit;
    }
}
