package com.sungard.smartcard.bccsvr.dao;

import org.apache.commons.dbutils.ResultSetHandler;

import java.sql.SQLException;
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
public interface JdbcOperations {
    /**
     * Query for an <code>int</code> passing in a SQL query
     *
     * @param sql  the SQL query to run.
     * @param args the map containing the arguments for the query
     * @return .
     * @throws SQLException
     */
    public int queryForInt(String sql, Map<String, Object> args) throws SQLException;

    /**
     * Query for an <code>int</code> passing in a SQL query
     * using the standard '?' placeholders for parameters
     * and a variable number of arguments.
     *
     * @param sql  the SQL query to run.
     * @param args the variable number of arguments for the query
     * @return .
     * @throws SQLException
     */
    public int queryForInt(String sql, Object... args) throws SQLException;

    /**
     * Query for an <code>long</code> passing in a SQL query
     *
     * @param sql  the SQL query to run.
     * @param args the map containing the arguments for the query
     * @return .
     * @throws SQLException
     */
    public long queryForLong(String sql, Map<String, ?> args) throws SQLException;

    /**
     * Query for an <code>long</code> passing in a SQL query
     * using the standard '?' placeholders for parameters
     * and a variable number of arguments.
     *
     * @param sql  the SQL query to run.
     * @param args the variable number of arguments for the query
     */
    public long queryForLong(String sql, Object... args) throws SQLException;

    /**
     * Query for an object of type <code>T</code> identified by the supplied @{@link Class}.
     *
     * @param sql          the SQL query to run
     * @param requiredType the required type of the return value
     * @param args         the map containing the arguments for the query
     * @return .
     * @throws SQLException
     */
    public <T> T queryForObject(String sql, Class<T> requiredType, Map<String, Object> args) throws SQLException;

    /**
     * Query for an object of type <code>T</code> identified by the supplied @{@link Class}.
     * Uses sql with the standard '?' placeholders for parameters
     *
     * @param sql          the SQL query to run
     * @param requiredType the required type of the return value
     * @param args         the variable number of arguments for the query
     * @return .
     * @throws SQLException
     */
    public <T> T queryForObject(String sql, Class<T> requiredType, Object... args) throws SQLException;

    /**
     * Execute the supplied query with the supplied arguments.
     * <p>Each element in the returned {@link List} is constructed as a {@link Map}
     *
     * @param sql  the SQL query to run
     * @param args the map containing the arguments for the query
     */
    public List<Map<String, Object>> queryForList(String sql, Map<String, Object> args) throws SQLException;

    /**
     * Execute the supplied query with the (optional) supplied arguments.
     * <p>Each element in the returned {@link List} is constructed as a @{@link Class}
     * Uses sql with the standard '?' placeholders for parameters
     *
     * @param sql          the SQL query to run
     * @param requiredType the required type of the return value
     * @param args         the variable number of arguments for the query
     */
    public <T> List<T> queryForList(String sql, Class<T> requiredType, Map<String, Object> args) throws SQLException;

    /**
     * Execute the supplied query with the (optional) supplied arguments.
     * <p>Each element in the returned {@link List} is constructed as a {@link Map}
     * Uses sql with the standard '?' placeholders for parameters
     *
     * @param sql  the SQL query to run
     * @param args the variable number of arguments for the query
     */
    public List<Map<String, Object>> queryForList(String sql, Object... args) throws SQLException;

    /**
     * Execute the supplied query with the (optional) supplied arguments.
     * <p>Each element in the returned {@link List} is constructed as a @{@link Class}
     * Uses sql with the standard '?' placeholders for parameters
     *
     * @param sql          the SQL query to run
     * @param requiredType the required type of the return value
     * @param args         the variable number of arguments for the query
     */
    public <T> List<T> queryForList(String sql, Class<T> requiredType, Object... args) throws SQLException;

    /**
     * Query for an object of type <code>T</code> identified by the supplied {@link Map}.
     * Uses sql with the standard '?' placeholders for parameters
     *
     * @param sql  the SQL query to run
     * @param args the variable number of arguments for the query
     * @return .
     * @throws SQLException
     */
    public Map<String, Object> queryForObject(String sql, Object... args) throws SQLException;

    /**
     * Query for an object of type <code>T</code> identified by the supplied {@link Map}.
     * Uses sql with the standard '?' placeholders for parameters
     *
     * @param sql  the SQL query to run
     * @param args the variable number of arguments for the query
     * @return .
     * @throws SQLException
     */
    public Map<String, Object> queryForObject(String sql, Map<String, Object> args) throws SQLException;

    public List<Object[]> queryForArrayList(String sql, Object... args) throws SQLException;

    public List<Object[]> queryForArrayList(String sql, Map<String, Object> args) throws SQLException;

    public Object[] queryForArray(String sql, Object... args) throws SQLException;

    public Object[] queryForArray(String sql, Map<String, Object> args) throws SQLException;

    public <T> T query(String sql, ResultSetHandler<T> rsh, Object... args) throws SQLException;

    public <T> T query(String sql, ResultSetHandler<T> rsh, Map<String, Object> args) throws SQLException;

    public Number query(String sql, Map<String, Object> args) throws SQLException;

    public Number query(String sql, Object... args) throws SQLException;

    /**
     * Execute the supplied SQL statement with (optional) supplied arguments.
     *
     * @param sql  the SQL statement to execute
     * @param args the map containing the arguments for the query
     * @return the numbers of rows affected by the update
     */
    public int update(String sql, Map<String, Object> args) throws SQLException;

    /**
     * Execute the supplied SQL statement with supplied arguments.
     * Uses sql with the standard '?' placeholders for parameters
     *
     * @param sql  the SQL statement to execute
     * @param args the variable number of arguments for the query
     * @return the numbers of rows affected by the update
     */
    public int update(String sql, Object... args) throws SQLException;

    /**
     * Executes a batch using the supplied SQL statement with the batch of supplied arguments.
     *
     * @param sql         the SQL statement to execute
     * @param batchValues the array of Maps containing the batch of arguments for the query
     * @return an array containing the numbers of rows affected by each update in the batch
     */
    public int[] batchUpdate(String sql, Map<String, ?>[] batchValues);

    /**
     * Execute a batch using the supplied SQL statement with the batch of supplied arguments.
     * Uses sql with the standard '?' placeholders for parameters
     *
     * @param sql       the SQL statement to execute
     * @param batchArgs the List of Object arrays containing the batch of arguments for the query
     * @return an array containing the numbers of rows affected by each update in the batch
     */
    public int[] batchUpdate(String sql, List<Object[]> batchArgs);
}
