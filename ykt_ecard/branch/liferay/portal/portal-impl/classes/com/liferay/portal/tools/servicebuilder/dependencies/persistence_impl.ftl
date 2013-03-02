package ${packagePath}.service.persistence;

<#assign noSuchEntity = serviceBuilder.getNoSuchEntityException(entity)>

import ${packagePath}.${noSuchEntity}Exception;
import ${packagePath}.model.${entity.name};
import ${packagePath}.model.impl.${entity.name}Impl;
import ${packagePath}.model.impl.${entity.name}ModelImpl;
import ${basePersistencePackage}.BasePersistence;
import ${propsUtilPackage}.PropsUtil;
import ${springHibernatePackage}.FinderCache;
import ${springHibernatePackage}.HibernateUtil;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.dao.DynamicQuery;
import com.liferay.portal.kernel.dao.DynamicQueryInitializer;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.kernel.uuid.PortalUUIDUtil;
import com.liferay.portal.model.ModelListener;
import com.liferay.util.dao.hibernate.QueryPos;
import com.liferay.util.dao.hibernate.QueryUtil;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.Hibernate;
import org.hibernate.Query;
import org.hibernate.SQLQuery;
import org.hibernate.Session;
import org.springframework.dao.DataAccessException;
import org.springframework.jdbc.core.SqlParameter;
import org.springframework.jdbc.object.MappingSqlQuery;
import org.springframework.jdbc.object.SqlUpdate;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Types;
import java.util.Collections;
import java.util.Date;
import java.util.Iterator;
import java.util.List;

public class ${entity.name}PersistenceImpl extends BasePersistence implements ${entity.name}Persistence {

	public ${entity.name} create(${entity.PKClassName} ${entity.PKVarName}) {
		${entity.name} ${entity.varName} = new ${entity.name}Impl();

		${entity.varName}.setNew(true);
		${entity.varName}.setPrimaryKey(${entity.PKVarName});

		<#if entity.hasUuid()>
			String uuid = PortalUUIDUtil.generate();

			${entity.varName}.setUuid(uuid);
		</#if>

		return ${entity.varName};
	}

	public ${entity.name} remove(${entity.PKClassName} ${entity.PKVarName}) throws ${noSuchEntity}Exception, SystemException {
		Session session = null;

		try {
			session = openSession();

			${entity.name} ${entity.varName} = (${entity.name}) session.get(${entity.name}Impl.class,

			<#if entity.hasPrimitivePK()>
				new ${serviceBuilder.getPrimitiveObj("${entity.PKClassName}")}(
			</#if>

			${entity.PKVarName}

			<#if entity.hasPrimitivePK()>
				)
			</#if>

			);

			if (${entity.varName} == null) {
				if (_log.isWarnEnabled()) {
					_log.warn("No ${entity.name} exists with the primary key " + ${entity.PKVarName});
				}

				throw new ${noSuchEntity}Exception("No ${entity.name} exists with the primary key " + ${entity.PKVarName});
			}

			return remove(${entity.varName});
		}
		catch (${noSuchEntity}Exception nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public ${entity.name} remove(${entity.name} ${entity.varName}) throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(${entity.varName});
		}

		${entity.varName} = removeImpl(${entity.varName});

		if (listener != null) {
			listener.onAfterRemove(${entity.varName});
		}

		return ${entity.varName};
	}

	protected ${entity.name} removeImpl(${entity.name} ${entity.varName}) throws SystemException {
		<#list entity.columnList as column>
			<#if column.isCollection() && column.isMappingManyToMany()>
				<#assign tempEntity = serviceBuilder.getEntity(column.getEJBName())>

				try {
					clear${tempEntity.names}.clear(${entity.varName}.getPrimaryKey());
				}
				catch (Exception e) {
					throw HibernateUtil.processException(e);
				}
				finally {
					FinderCache.clearCache("${column.mappingTable}");
				}
			</#if>
		</#list>

		Session session = null;

		try {
			session = openSession();

			session.delete(${entity.varName});

			session.flush();

			return ${entity.varName};
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(${entity.name}.class.getName());
		}
	}

	public ${entity.name} update(${entity.name} ${entity.varName}) throws SystemException {
		return update(${entity.varName}, false);
	}

	public ${entity.name} update(${entity.name} ${entity.varName}, boolean merge) throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = ${entity.varName}.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(${entity.varName});
			}
			else {
				listener.onBeforeUpdate(${entity.varName});
			}
		}

		${entity.varName} = updateImpl(${entity.varName}, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(${entity.varName});
			}
			else {
				listener.onAfterUpdate(${entity.varName});
			}
		}

		return ${entity.varName};
	}

	public ${entity.name} updateImpl(${packagePath}.model.${entity.name} ${entity.varName}, boolean merge) throws SystemException {
		<#list entity.columnList as column>
			<#if column.isCollection() && column.isMappingManyToMany()>
				FinderCache.clearCache("${column.mappingTable}");
			</#if>
		</#list>

		<#if entity.hasUuid()>
			if (Validator.isNull(${entity.varName}.getUuid())) {
				String uuid = PortalUUIDUtil.generate();

				${entity.varName}.setUuid(uuid);
			}
		</#if>

		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(${entity.varName});
			}
			else {
				if (${entity.varName}.isNew()) {
					session.save(${entity.varName});
				}
			}

			session.flush();

			${entity.varName}.setNew(false);

			return ${entity.varName};
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(${entity.name}.class.getName());
		}
	}

	public ${entity.name} findByPrimaryKey(${entity.PKClassName} ${entity.PKVarName}) throws ${noSuchEntity}Exception, SystemException {
		${entity.name} ${entity.varName} = fetchByPrimaryKey(${entity.PKVarName});

		if (${entity.varName} == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No ${entity.name} exists with the primary key " + ${entity.PKVarName});
			}

			throw new ${noSuchEntity}Exception("No ${entity.name} exists with the primary key " + ${entity.PKVarName});
		}

		return ${entity.varName};
	}

	public ${entity.name} fetchByPrimaryKey(${entity.PKClassName} ${entity.PKVarName}) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (${entity.name}) session.get(${entity.name}Impl.class,

			<#if entity.hasPrimitivePK()>
				new ${serviceBuilder.getPrimitiveObj("${entity.PKClassName}")}(
			</#if>

			${entity.PKVarName}

			<#if entity.hasPrimitivePK()>
				)
			</#if>

			);
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	<#list entity.getFinderList() as finder>
		<#assign finderColsList = finder.getColumns()>

		<#if finder.isCollection()>
			public List findBy${finder.name}(

			<#list finderColsList as finderCol>
				${finderCol.type} ${finderCol.name}

				<#if finderCol_has_next>
					,
				</#if>
			</#list>

			) throws SystemException {
				boolean finderClassNameCacheEnabled = ${entity.name}ModelImpl.CACHE_ENABLED;
				String finderClassName = ${entity.name}.class.getName();
				String finderMethodName = "findBy${finder.name}";
				String[] finderParams = new String[] {
					<#list finderColsList as finderCol>
						${serviceBuilder.getPrimitiveObj("${finderCol.type}")}.class.getName()

						<#if finderCol_has_next>
							,
						</#if>
					</#list>
				};
				Object[] finderArgs = new Object[] {
					<#list finderColsList as finderCol>
						<#if finderCol.isPrimitiveType()>
							<#if finderCol.type == "boolean">
								Boolean.valueOf(
							<#else>
								new ${serviceBuilder.getPrimitiveObj("${finderCol.type}")}(
							</#if>
						</#if>

						${finderCol.name}

						<#if finderCol.isPrimitiveType()>
							)
						</#if>

						<#if finderCol_has_next>
							,
						</#if>
					</#list>
				};

				Object result = null;

				if (finderClassNameCacheEnabled) {
					result = FinderCache.getResult(finderClassName, finderMethodName, finderParams, finderArgs, getSessionFactory());
				}

				if (result == null) {
					Session session = null;

					try {
						session = openSession();

						StringMaker query = new StringMaker();

						query.append("FROM ${packagePath}.model.${entity.name} WHERE ");

						<#list finderColsList as finderCol>
							<#if !finderCol.isPrimitiveType()>
								if (${finderCol.name} == null) {
									<#if finderCol.comparator == "=">
										query.append("${finderCol.DBName} IS NULL");
									<#elseif finderCol.comparator == "<>" || finderCol.comparator = "!=">
										query.append("${finderCol.DBName} IS NOT NULL");
									<#else>
										query.append("${finderCol.DBName} ${finderCol.comparator} null");
									</#if>
								}
								else {
							</#if>

							<#if finderCol.type == "String" && !finderCol.isCaseSensitive()>
								query.append("lower(${finderCol.DBName}) ${finderCol.comparator} ?");
							<#else>
								query.append("${finderCol.DBName} ${finderCol.comparator} ?");
							</#if>

							<#if !finderCol.isPrimitiveType()>
								}
							</#if>

							<#if finderCol_has_next>
								query.append(" AND ");
							<#elseif finder.where?? && !validator.isNull(finder.getWhere())>
								query.append(" AND ${finder.where} ");
							<#else>
								query.append(" ");
							</#if>
						</#list>

						<#if entity.getOrder()??>
							query.append("ORDER BY ");

							<#assign orderList = entity.getOrder().getColumns()>

							<#list orderList as order>
								query.append("${order.DBName} <#if order.isOrderByAscending()>ASC<#else>DESC</#if><#if order_has_next>, </#if>");
							</#list>
						</#if>

						Query q = session.createQuery(query.toString());

						int queryPos = 0;

						<#list finderColsList as finderCol>
							<#if !finderCol.isPrimitiveType()>
								if (${finderCol.name} != null) {
							</#if>

							q.set${serviceBuilder.getPrimitiveObj("${finderCol.type}")}(queryPos++, ${finderCol.name}${serviceBuilder.getPrimitiveObjValue("${finderCol.type}")});

							<#if !finderCol.isPrimitiveType()>
								}
							</#if>
						</#list>

						List list = q.list();

						FinderCache.putResult(finderClassNameCacheEnabled, finderClassName, finderMethodName, finderParams, finderArgs, list);

						return list;
					}
					catch (Exception e) {
						throw HibernateUtil.processException(e);
					}
					finally {
						closeSession(session);
					}
				}
				else {
					return (List)result;
				}
			}

			public List findBy${finder.name}(

			<#list finderColsList as finderCol>
				${finderCol.type} ${finderCol.name},
			</#list>

			int begin, int end) throws SystemException {
				return findBy${finder.name}(

				<#list finderColsList as finderCol>
					${finderCol.name},
				</#list>

				begin, end, null);
			}

			public List findBy${finder.name}(

			<#list finderColsList as finderCol>
				${finderCol.type} ${finderCol.name},
			</#list>

			int begin, int end, OrderByComparator obc) throws SystemException {
				boolean finderClassNameCacheEnabled = ${entity.name}ModelImpl.CACHE_ENABLED;
				String finderClassName = ${entity.name}.class.getName();
				String finderMethodName = "findBy${finder.name}";
				String[] finderParams = new String[] {
					<#list finderColsList as finderCol>
						${serviceBuilder.getPrimitiveObj("${finderCol.type}")}.class.getName(),
					</#list>

					"java.lang.Integer", "java.lang.Integer", "com.liferay.portal.kernel.util.OrderByComparator"
				};
				Object[] finderArgs = new Object[] {
					<#list finderColsList as finderCol>
						<#if finderCol.isPrimitiveType()>
							<#if finderCol.type == "boolean">
								Boolean.valueOf(
							<#else>
								new ${serviceBuilder.getPrimitiveObj("${finderCol.type}")}(
							</#if>
						</#if>

						${finderCol.name}

						<#if finderCol.isPrimitiveType()>
							)
						</#if>

						,
					</#list>

					String.valueOf(begin), String.valueOf(end), String.valueOf(obc)
				};

				Object result = null;

				if (finderClassNameCacheEnabled) {
					result = FinderCache.getResult(finderClassName, finderMethodName, finderParams, finderArgs, getSessionFactory());
				}

				if (result == null) {
					Session session = null;

					try {
						session = openSession();

						StringMaker query = new StringMaker();

						query.append("FROM ${packagePath}.model.${entity.name} WHERE ");

						<#list finderColsList as finderCol>
							<#if !finderCol.isPrimitiveType()>
								if (${finderCol.name} == null) {
									<#if finderCol.comparator == "=">
										query.append("${finderCol.DBName} IS NULL");
									<#elseif finderCol.comparator == "<>" || finderCol.comparator = "!=">
										query.append("${finderCol.DBName} IS NOT NULL");
									<#else>
										query.append("${finderCol.DBName} ${finderCol.comparator} null");
									</#if>
								}
								else {
							</#if>

							<#if finderCol.type == "String" && !finderCol.isCaseSensitive()>
								query.append("lower(${finderCol.DBName}) ${finderCol.comparator} ?");
							<#else>
								query.append("${finderCol.DBName} ${finderCol.comparator} ?");
							</#if>

							<#if !finderCol.isPrimitiveType()>
								}
							</#if>

							<#if finderCol_has_next>
								query.append(" AND ");
							<#elseif finder.where?? && !validator.isNull(finder.getWhere())>
								query.append(" AND ${finder.where} ");
							<#else>
								query.append(" ");
							</#if>
						</#list>

						if (obc != null) {
							query.append("ORDER BY ");
							query.append(obc.getOrderBy());
						}

						<#if entity.getOrder()??>
							else {
								query.append("ORDER BY ");

								<#assign orderList = entity.getOrder().getColumns()>

								<#list orderList as order>
									query.append("${order.DBName} <#if order.isOrderByAscending()>ASC<#else>DESC</#if><#if order_has_next>, </#if>");
								</#list>
							}
						</#if>

						Query q = session.createQuery(query.toString());

						int queryPos = 0;

						<#list finderColsList as finderCol>
							<#if !finderCol.isPrimitiveType()>
								if (${finderCol.name} != null) {
							</#if>

							q.set${serviceBuilder.getPrimitiveObj("${finderCol.type}")}(queryPos++, ${finderCol.name}${serviceBuilder.getPrimitiveObjValue("${finderCol.type}")});

							<#if !finderCol.isPrimitiveType()>
								}
							</#if>
						</#list>

						List list = QueryUtil.list(q, getDialect(), begin, end);

						FinderCache.putResult(finderClassNameCacheEnabled, finderClassName, finderMethodName, finderParams, finderArgs, list);

						return list;
					}
					catch (Exception e) {
						throw HibernateUtil.processException(e);
					}
					finally {
						closeSession(session);
					}
				}
				else {
					return (List)result;
				}
			}

			public ${entity.name} findBy${finder.name}_First(

			<#list finderColsList as finderCol>
				${finderCol.type} ${finderCol.name},
			</#list>

			OrderByComparator obc) throws ${noSuchEntity}Exception, SystemException {
				List list = findBy${finder.name}(

				<#list finderColsList as finderCol>
					${finderCol.name},
				</#list>

				0, 1, obc);

				if (list.size() == 0) {
					StringMaker msg = new StringMaker();

					msg.append("No ${entity.name} exists with the key {");

					<#list finderColsList as finderCol>
						msg.append("${finderCol.name}=" + ${finderCol.name});

						<#if finderCol_has_next>
							msg.append(", ");
						<#else>
							msg.append(StringPool.CLOSE_CURLY_BRACE);
						</#if>
					</#list>

					throw new ${noSuchEntity}Exception(msg.toString());
				}
				else {
					return (${entity.name})list.get(0);
				}
			}

			public ${entity.name} findBy${finder.name}_Last(

			<#list finderColsList as finderCol>
				${finderCol.type} ${finderCol.name},
			</#list>

			OrderByComparator obc) throws ${noSuchEntity}Exception, SystemException {
				int count = countBy${finder.name}(

				<#list finderColsList as finderCol>
					${finderCol.name}

					<#if finderCol_has_next>
						,
					</#if>
				</#list>

				);

				List list = findBy${finder.name}(

				<#list finderColsList as finderCol>
					${finderCol.name},
				</#list>

				count - 1, count, obc);

				if (list.size() == 0) {
					StringMaker msg = new StringMaker();

					msg.append("No ${entity.name} exists with the key {");

					<#list finderColsList as finderCol>
						msg.append("${finderCol.name}=" + ${finderCol.name});

						<#if finderCol_has_next>
							msg.append(", ");
						<#else>
							msg.append(StringPool.CLOSE_CURLY_BRACE);
						</#if>
					</#list>

					throw new ${noSuchEntity}Exception(msg.toString());
				}
				else {
					return (${entity.name})list.get(0);
				}
			}

			public ${entity.name}[] findBy${finder.name}_PrevAndNext(${entity.PKClassName} ${entity.PKVarName},

			<#list finderColsList as finderCol>
				${finderCol.type} ${finderCol.name},
			</#list>

			OrderByComparator obc) throws ${noSuchEntity}Exception, SystemException {
				${entity.name} ${entity.varName} = findByPrimaryKey(${entity.PKVarName});

				int count = countBy${finder.name}(

				<#list finderColsList as finderCol>
					${finderCol.name}

					<#if finderCol_has_next>
						,
					</#if>
				</#list>

				);

				Session session = null;

				try {
					session = openSession();

					StringMaker query = new StringMaker();

					query.append("FROM ${packagePath}.model.${entity.name} WHERE ");

					<#list finderColsList as finderCol>
						<#if !finderCol.isPrimitiveType()>
							if (${finderCol.name} == null) {
								<#if finderCol.comparator == "=">
									query.append("${finderCol.DBName} IS NULL");
								<#elseif finderCol.comparator == "<>" || finderCol.comparator = "!=">
									query.append("${finderCol.DBName} IS NOT NULL");
								<#else>
									query.append("${finderCol.DBName} ${finderCol.comparator} null");
								</#if>
							}
							else {
						</#if>

						<#if finderCol.type == "String" && !finderCol.isCaseSensitive()>
							query.append("lower(${finderCol.DBName}) ${finderCol.comparator} ?");
						<#else>
							query.append("${finderCol.DBName} ${finderCol.comparator} ?");
						</#if>

						<#if !finderCol.isPrimitiveType()>
							}
						</#if>

						<#if finderCol_has_next>
							query.append(" AND ");
						<#elseif finder.where?? && !validator.isNull(finder.getWhere())>
							query.append(" AND ${finder.where} ");
						<#else>
							query.append(" ");
						</#if>
					</#list>

					if (obc != null) {
						query.append("ORDER BY ");
						query.append(obc.getOrderBy());
					}

					<#if entity.getOrder()??>
						else {
							query.append("ORDER BY ");

							<#assign orderList = entity.getOrder().getColumns()>

							<#list orderList as order>
								query.append("${order.DBName} <#if order.isOrderByAscending()>ASC<#else>DESC</#if><#if order_has_next>, </#if>");
							</#list>
						}
					</#if>

					Query q = session.createQuery(query.toString());

					int queryPos = 0;

					<#list finderColsList as finderCol>
						<#if !finderCol.isPrimitiveType()>
							if (${finderCol.name} != null) {
						</#if>

						q.set${serviceBuilder.getPrimitiveObj("${finderCol.type}")}(queryPos++, ${finderCol.name}${serviceBuilder.getPrimitiveObjValue("${finderCol.type}")});

						<#if !finderCol.isPrimitiveType()>
							}
						</#if>

					</#list>

					Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc, ${entity.varName});

					${entity.name}[] array = new ${entity.name}Impl[3];

					array[0] = (${entity.name}) objArray[0];
					array[1] = (${entity.name}) objArray[1];
					array[2] = (${entity.name}) objArray[2];

					return array;
				}
				catch (Exception e) {
					throw HibernateUtil.processException(e);
				}
				finally {
					closeSession(session);
				}
			}
		<#else>
			public ${entity.name} findBy${finder.name}(

			<#list finderColsList as finderCol>
				${finderCol.type} ${finderCol.name}

				<#if finderCol_has_next>
					,
				</#if>
			</#list>

			) throws ${noSuchEntity}Exception, SystemException {
				${entity.name} ${entity.varName} = fetchBy${finder.name}(

				<#list finderColsList as finderCol>
					${finderCol.name}

					<#if finderCol_has_next>
						,
					</#if>
				</#list>

				);

				if ( ${entity.varName} == null) {
					StringMaker msg = new StringMaker();

					msg.append("No ${entity.name} exists with the key {");

					<#list finderColsList as finderCol>
						msg.append("${finderCol.name}=" + ${finderCol.name});

						<#if finderCol_has_next>
							msg.append(", ");
						<#else>
							msg.append(StringPool.CLOSE_CURLY_BRACE);
						</#if>
					</#list>

					if (_log.isWarnEnabled()) {
						_log.warn(msg.toString());
					}

					throw new ${noSuchEntity}Exception(msg.toString());
				}

				return ${entity.varName};
			}

			public ${entity.name} fetchBy${finder.name}(

			<#list finderColsList as finderCol>
				${finderCol.type} ${finderCol.name}

				<#if finderCol_has_next>
					,
				</#if>
			</#list>

			) throws SystemException {
				boolean finderClassNameCacheEnabled = ${entity.name}ModelImpl.CACHE_ENABLED;
				String finderClassName = ${entity.name}.class.getName();
				String finderMethodName = "fetchBy${finder.name}";
				String[] finderParams = new String[] {
					<#list finderColsList as finderCol>
						${serviceBuilder.getPrimitiveObj("${finderCol.type}")}.class.getName()

						<#if finderCol_has_next>
							,
						</#if>
					</#list>
				};
				Object[] finderArgs = new Object[] {
					<#list finderColsList as finderCol>
						<#if finderCol.isPrimitiveType()>
							<#if finderCol.type == "boolean">
								Boolean.valueOf(
							<#else>
								new ${serviceBuilder.getPrimitiveObj("${finderCol.type}")}(
							</#if>
						</#if>

						${finderCol.name}

						<#if finderCol.isPrimitiveType()>
							)
						</#if>

						<#if finderCol_has_next>
							,
						</#if>
					</#list>
				};

				Object result = null;

				if (finderClassNameCacheEnabled) {
					result = FinderCache.getResult(finderClassName, finderMethodName, finderParams, finderArgs, getSessionFactory());
				}

				if (result == null) {
					Session session = null;

					try {
						session = openSession();

						StringMaker query = new StringMaker();

						query.append("FROM ${packagePath}.model.${entity.name} WHERE ");

						<#list finderColsList as finderCol>
							<#if !finderCol.isPrimitiveType()>
								if (${finderCol.name} == null) {
									<#if finderCol.comparator == "=">
										query.append("${finderCol.DBName} IS NULL");
									<#elseif finderCol.comparator == "<>" || finderCol.comparator = "!=">
										query.append("${finderCol.DBName} IS NOT NULL");
									<#else>
										query.append("${finderCol.DBName} ${finderCol.comparator} null");
									</#if>
								}
								else {
							</#if>

							<#if finderCol.type == "String" && !finderCol.isCaseSensitive()>
								query.append("lower(${finderCol.DBName}) ${finderCol.comparator} ?");
							<#else>
								query.append("${finderCol.DBName} ${finderCol.comparator} ?");
							</#if>

							<#if !finderCol.isPrimitiveType()>
								}
							</#if>

							<#if finderCol_has_next>
								query.append(" AND ");
							<#elseif finder.where?? && !validator.isNull(finder.getWhere())>
								query.append(" AND ${finder.where} ");
							<#else>
								query.append(" ");
							</#if>
						</#list>

						<#if entity.getOrder()??>
							query.append("ORDER BY ");

							<#assign orderList = entity.getOrder().getColumns()>

							<#list orderList as order>
								query.append("${order.DBName} <#if order.isOrderByAscending()>ASC<#else>DESC</#if><#if order_has_next>, </#if>");
							</#list>
						</#if>

						Query q = session.createQuery(query.toString());

						int queryPos = 0;

						<#list finderColsList as finderCol>
							<#if !finderCol.isPrimitiveType()>
								if (${finderCol.name} != null) {
							</#if>

							q.set${serviceBuilder.getPrimitiveObj("${finderCol.type}")}(queryPos++, ${finderCol.name}${serviceBuilder.getPrimitiveObjValue("${finderCol.type}")});

							<#if !finderCol.isPrimitiveType()>
								}
							</#if>
						</#list>

						List list = q.list();

						FinderCache.putResult(finderClassNameCacheEnabled, finderClassName, finderMethodName, finderParams, finderArgs, list);

						if (list.size() == 0) {
							return null;
						}
						else {
							return (${entity.name})list.get(0);
						}
					}
					catch (Exception e) {
						throw HibernateUtil.processException(e);
					}
					finally {
						closeSession(session);
					}
				}
				else {
					List list = (List)result;

					if (list.size() == 0) {
						return null;
					}
					else {
						return (${entity.name})list.get(0);
					}
				}
			}
		</#if>
	</#list>

	public List findWithDynamicQuery(DynamicQueryInitializer queryInitializer) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			DynamicQuery query = queryInitializer.initialize(session);

			return query.list();
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findWithDynamicQuery(DynamicQueryInitializer queryInitializer, int begin, int end) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			DynamicQuery query = queryInitializer.initialize(session);

			query.setLimit(begin, end);

			return query.list();
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findAll() throws SystemException {
		return findAll(QueryUtil.ALL_POS, QueryUtil.ALL_POS, null);
	}

	public List findAll(int begin, int end) throws SystemException {
		return findAll(begin, end, null);
	}

	public List findAll(int begin, int end, OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = ${entity.name}ModelImpl.CACHE_ENABLED;
		String finderClassName = ${entity.name}.class.getName();
		String finderMethodName = "findAll";
		String[] finderParams = new String[] {"java.lang.Integer", "java.lang.Integer", "com.liferay.portal.kernel.util.OrderByComparator"};
		Object[] finderArgs = new Object[] {String.valueOf(begin), String.valueOf(end), String.valueOf(obc)};

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName, finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			Session session = null;

			try {
				session = openSession();

				StringMaker query = new StringMaker();

				query.append("FROM ${packagePath}.model.${entity.name} ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				<#if entity.getOrder()??>
					else {
						query.append("ORDER BY ");

						<#assign orderList = entity.getOrder().getColumns()>

						<#list orderList as order>
							query.append("${order.DBName} <#if order.isOrderByAscending()>ASC<#else>DESC</#if><#if order_has_next>, </#if>");
						</#list>
					}
				</#if>

				Query q = session.createQuery(query.toString());

				List list = QueryUtil.list(q, getDialect(), begin, end);

				if (obc == null) {
					Collections.sort(list);
				}

				FinderCache.putResult(finderClassNameCacheEnabled, finderClassName, finderMethodName, finderParams, finderArgs, list);

				return list;
			}
			catch (Exception e) {
				throw HibernateUtil.processException(e);
			}
			finally {
				closeSession(session);
			}
		}
		else {
			return (List)result;
		}
	}

	<#list entity.getFinderList() as finder>
		<#assign finderColsList = finder.getColumns()>

		<#if finder.isCollection()>
			public void removeBy${finder.name}(

			<#list finderColsList as finderCol>
				${finderCol.type} ${finderCol.name}<#if finderCol_has_next>,</#if>
			</#list>

			) throws SystemException {
				Iterator itr = findBy${finder.name}(

				<#list finderColsList as finderCol>
					${finderCol.name}

					<#if finderCol_has_next>
						,
					</#if>
				</#list>

				).iterator();

				while (itr.hasNext()) {
					${entity.name} ${entity.varName} = (${entity.name})itr.next();

					remove(${entity.varName});
				}
			}
		<#else>
			public void removeBy${finder.name}(

			<#list finderColsList as finderCol>
				${finderCol.type} ${finderCol.name}

				<#if finderCol_has_next>
					,
				</#if>
			</#list>

			) throws ${noSuchEntity}Exception, SystemException {
				${entity.name} ${entity.varName} = findBy${finder.name}(

				<#list finderColsList as finderCol>
					${finderCol.name}

					<#if finderCol_has_next>
						,
					</#if>
				</#list>

				);

				remove(${entity.varName});
			}
		</#if>
	</#list>

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((${entity.name})itr.next());
		}
	}

	<#list entity.getFinderList() as finder>
		<#assign finderColsList = finder.getColumns()>

		public int countBy${finder.name}(

		<#list finderColsList as finderCol>
			${finderCol.type} ${finderCol.name}

			<#if finderCol_has_next>
				,
			</#if>
		</#list>

		) throws SystemException {
			boolean finderClassNameCacheEnabled = ${entity.name}ModelImpl.CACHE_ENABLED;
			String finderClassName = ${entity.name}.class.getName();
			String finderMethodName = "countBy${finder.name}";
			String[] finderParams = new String[] {
				<#list finderColsList as finderCol>
					${serviceBuilder.getPrimitiveObj("${finderCol.type}")}.class.getName()

					<#if finderCol_has_next>
						,
					</#if>
				</#list>
			};
			Object[] finderArgs = new Object[] {
				<#list finderColsList as finderCol>
					<#if finderCol.isPrimitiveType()>
						<#if finderCol.type == "boolean">
							Boolean.valueOf(
						<#else>
							new ${serviceBuilder.getPrimitiveObj("${finderCol.type}")}(
						</#if>
					</#if>

					${finderCol.name}

					<#if finderCol.isPrimitiveType()>
						)
					</#if>

					<#if finderCol_has_next>
						,
					</#if>
				</#list>
			};

			Object result = null;

			if (finderClassNameCacheEnabled) {
				result = FinderCache.getResult(finderClassName, finderMethodName, finderParams, finderArgs, getSessionFactory());
			}

			if (result == null) {
				Session session = null;

				try {
					session = openSession();

					StringMaker query = new StringMaker();

					query.append("SELECT COUNT(*) ");
					query.append("FROM ${packagePath}.model.${entity.name} WHERE ");

					<#list finderColsList as finderCol>
						<#if !finderCol.isPrimitiveType()>
							if (${finderCol.name} == null) {
								<#if finderCol.comparator == "=">
									query.append("${finderCol.DBName} IS NULL");
								<#elseif finderCol.comparator == "<>" || finderCol.comparator = "!=">
									query.append("${finderCol.DBName} IS NOT NULL");
								<#else>
									query.append("${finderCol.DBName} ${finderCol.comparator} null");
								</#if>
							}
							else {
						</#if>

						<#if finderCol.type == "String" && !finderCol.isCaseSensitive()>
							query.append("lower(${finderCol.DBName}) ${finderCol.comparator} ?");
						<#else>
							query.append("${finderCol.DBName} ${finderCol.comparator} ?");
						</#if>

						<#if !finderCol.isPrimitiveType()>
							}
						</#if>

						<#if finderCol_has_next>
							query.append(" AND ");
						<#elseif finder.where?? && !validator.isNull(finder.getWhere())>
							query.append(" AND ${finder.where} ");
						<#else>
							query.append(" ");
						</#if>
					</#list>

					Query q = session.createQuery(query.toString());

					int queryPos = 0;

					<#list finderColsList as finderCol>
						<#if !finderCol.isPrimitiveType()>
							if (${finderCol.name} != null) {
						</#if>

						q.set${serviceBuilder.getPrimitiveObj("${finderCol.type}")}(queryPos++, ${finderCol.name}${serviceBuilder.getPrimitiveObjValue("${finderCol.type}")});

						<#if !finderCol.isPrimitiveType()>
							}
						</#if>
					</#list>

					Long count = null;

					Iterator itr = q.list().iterator();

					if (itr.hasNext()) {
						count = (Long)itr.next();
					}

					if (count == null) {
						count = new Long(0);
					}

					FinderCache.putResult(finderClassNameCacheEnabled, finderClassName, finderMethodName, finderParams, finderArgs, count);

					return count.intValue();
				}
				catch (Exception e) {
					throw HibernateUtil.processException(e);
				}
				finally {
					closeSession(session);
				}
			}
			else {
				return ((Long)result).intValue();
			}
		}
	</#list>

	public int countAll() throws SystemException {
		boolean finderClassNameCacheEnabled = ${entity.name}ModelImpl.CACHE_ENABLED;
		String finderClassName = ${entity.name}.class.getName();
		String finderMethodName = "countAll";
		String[] finderParams = new String[] {};
		Object[] finderArgs = new Object[] {};

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName, finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			Session session = null;

			try {
				session = openSession();

				Query q = session.createQuery("SELECT COUNT(*) FROM ${packagePath}.model.${entity.name}");

				Long count = null;

				Iterator itr = q.list().iterator();

				if (itr.hasNext()) {
					count = (Long)itr.next();
				}

				if (count == null) {
					count = new Long(0);
				}

				FinderCache.putResult(finderClassNameCacheEnabled, finderClassName, finderMethodName, finderParams, finderArgs, count);

				return count.intValue();
			}
			catch (Exception e) {
				throw HibernateUtil.processException(e);
			}
			finally {
				closeSession(session);
			}
		}
		else {
			return ((Long)result).intValue();
		}
	}

	<#list entity.columnList as column>
		<#if column.isCollection() && (column.isMappingManyToMany() || column.isMappingOneToMany())>
			<#assign tempEntity = serviceBuilder.getEntity(column.getEJBName())>

			public List get${tempEntity.names}(${entity.PKClassName} pk) throws ${noSuchEntity}Exception, SystemException {
				return get${tempEntity.names}(pk, QueryUtil.ALL_POS, QueryUtil.ALL_POS);
			}

			public List get${tempEntity.names}(${entity.PKClassName} pk, int begin, int end) throws ${noSuchEntity}Exception, SystemException {
				return get${tempEntity.names}(pk, begin, end, null);
			}

			public List get${tempEntity.names}(${entity.PKClassName} pk, int begin, int end, OrderByComparator obc) throws ${noSuchEntity}Exception, SystemException {
				boolean finderClassNameCacheEnabled =
					<#if column.mappingTable??>
						${entity.name}ModelImpl.CACHE_ENABLED_${stringUtil.upperCase(column.mappingTable)}
					<#else>
						${tempEntity.packagePath}.model.impl.${tempEntity.name}ModelImpl.CACHE_ENABLED
					</#if>

					;
				String finderClassName =
					<#if column.mappingTable??>
						"${column.mappingTable}"
					<#else>
						${tempEntity.packagePath}.model.${tempEntity.name}.class.getName()
					</#if>

					;
				String finderMethodName = "get${tempEntity.names}";
				String[] finderParams = new String[] {
					<#if entity.hasPrimitivePK()>
						${serviceBuilder.getPrimitiveObj(entity.getPKClassName())}
					<#else>
						${entity.PKClassName}
					</#if>

					.class.getName(), "java.lang.Integer", "java.lang.Integer", "com.liferay.portal.kernel.util.OrderByComparator"
				};
				Object[] finderArgs = new Object[] {
					<#if entity.hasPrimitivePK()>
						<#if entity.PKClassName == "boolean">
							Boolean.valueOf(
						<#else>
							new ${serviceBuilder.getPrimitiveObj(entity.getPKClassName())}(
						</#if>
					</#if>

					pk

					<#if entity.hasPrimitivePK()>
						)
					</#if>

					, String.valueOf(begin), String.valueOf(end), String.valueOf(obc)
				};

				Object result = null;

				if (finderClassNameCacheEnabled) {
					result = FinderCache.getResult(finderClassName, finderMethodName, finderParams, finderArgs, getSessionFactory());
				}

				if (result == null) {
					Session session = null;

					try {
						session = HibernateUtil.openSession();

						StringMaker sm = new StringMaker();

						sm.append(_SQL_GET${tempEntity.names?upper_case});

						if (obc != null) {
							sm.append("ORDER BY ");
							sm.append(obc.getOrderBy());
						}

						<#if tempEntity.getOrder()??>
							else {
								sm.append("ORDER BY ");

								<#assign orderList = tempEntity.getOrder().getColumns()>

								<#list orderList as order>
									sm.append("${tempEntity.table}.${order.DBName} <#if order.isOrderByAscending()>ASC<#else>DESC</#if><#if order_has_next>, </#if>");
								</#list>
							}
						</#if>

						String sql = sm.toString();

						SQLQuery q = session.createSQLQuery(sql);

						q.addEntity("${tempEntity.table}", ${tempEntity.packagePath}.model.impl.${tempEntity.name}Impl.class);

						QueryPos qPos = QueryPos.getInstance(q);

						qPos.add(pk);

						List list = QueryUtil.list(q, getDialect(), begin, end);

						FinderCache.putResult(finderClassNameCacheEnabled, finderClassName, finderMethodName, finderParams, finderArgs, list);

						return list;
					}
					catch (Exception e) {
						throw new SystemException(e);
					}
					finally {
						closeSession(session);
					}
				}
				else {
					return (List)result;
				}
			}

			public int get${tempEntity.names}Size(${entity.PKClassName} pk) throws SystemException {
				boolean finderClassNameCacheEnabled =
					<#if column.mappingTable??>
						${entity.name}ModelImpl.CACHE_ENABLED_${stringUtil.upperCase(column.mappingTable)}
					<#else>
						${tempEntity.packagePath}.model.impl.${tempEntity.name}ModelImpl.CACHE_ENABLED
					</#if>

					;
				String finderClassName =
					<#if column.mappingTable??>
						"${column.mappingTable}"
					<#else>
						${tempEntity.packagePath}.model.${tempEntity.name}.class.getName()
					</#if>

					;
				String finderMethodName = "get${tempEntity.names}Size";
				String[] finderParams = new String[] {
					<#if entity.hasPrimitivePK()>
						${serviceBuilder.getPrimitiveObj(entity.getPKClassName())}
					<#else>
						${entity.PKClassName}
					</#if>

					.class.getName()
				};
				Object[] finderArgs = new Object[] {
					<#if entity.hasPrimitivePK()>
						<#if entity.PKClassName == "boolean">
							Boolean.valueOf(
						<#else>
							new ${serviceBuilder.getPrimitiveObj(entity.getPKClassName())}(
						</#if>
					</#if>

					pk

					<#if entity.hasPrimitivePK()>
						)
					</#if>
				};

				Object result = null;

				if (finderClassNameCacheEnabled) {
					result = FinderCache.getResult(finderClassName, finderMethodName, finderParams, finderArgs, getSessionFactory());
				}

				if (result == null) {
					Session session = null;

					try {
						session = openSession();

						SQLQuery q = session.createSQLQuery(_SQL_GET${tempEntity.names?upper_case}SIZE);

						q.addScalar(HibernateUtil.getCountColumnName(), Hibernate.LONG);

						QueryPos qPos = QueryPos.getInstance(q);

						qPos.add(pk);

						Long count = null;

						Iterator itr = q.list().iterator();

						if (itr.hasNext()) {
							count = (Long)itr.next();
						}

						if (count == null) {
							count = new Long(0);
						}

						FinderCache.putResult(finderClassNameCacheEnabled, finderClassName, finderMethodName, finderParams, finderArgs, count);

						return count.intValue();
					}
					catch (Exception e) {
						throw HibernateUtil.processException(e);
					}
					finally {
						closeSession(session);
					}
				}
				else {
					return ((Long)result).intValue();
				}
			}

			public boolean contains${tempEntity.name}(${entity.PKClassName} pk, ${tempEntity.PKClassName} ${tempEntity.varName}PK) throws SystemException {
				boolean finderClassNameCacheEnabled =
					<#if column.mappingTable??>
						${entity.name}ModelImpl.CACHE_ENABLED_${stringUtil.upperCase(column.mappingTable)}
					<#else>
						${tempEntity.packagePath}.model.impl.${tempEntity.name}ModelImpl.CACHE_ENABLED
					</#if>

					;
				String finderClassName =
					<#if column.mappingTable??>
						"${column.mappingTable}"
					<#else>
						${tempEntity.packagePath}.model.${tempEntity.name}.class.getName()
					</#if>

					;
				String finderMethodName = "contains${tempEntity.names}";
				String[] finderParams = new String[] {
					<#if entity.hasPrimitivePK()>
						${serviceBuilder.getPrimitiveObj(entity.getPKClassName())}
					<#else>
						${entity.PKClassName}
					</#if>

					.class.getName(),

					<#if tempEntity.hasPrimitivePK()>
						${serviceBuilder.getPrimitiveObj(tempEntity.getPKClassName())}
					<#else>
						${tempEntity.PKClassName}
					</#if>

					.class.getName()
				};
				Object[] finderArgs = new Object[] {
					<#if entity.hasPrimitivePK()>
						<#if entity.PKClassName == "boolean">
							Boolean.valueOf(
						<#else>
							new ${serviceBuilder.getPrimitiveObj(entity.getPKClassName())}(
						</#if>
					</#if>

					pk

					<#if entity.hasPrimitivePK()>
						)
					</#if>,

					<#if tempEntity.hasPrimitivePK()>
						<#if entity.PKClassName == "boolean">
							Boolean.valueOf(
						<#else>
							new ${serviceBuilder.getPrimitiveObj(tempEntity.getPKClassName())}(
						</#if>
					</#if>

					${tempEntity.varName}PK

					<#if tempEntity.hasPrimitivePK()>
						)
					</#if>
				};

				Object result = null;

				if (finderClassNameCacheEnabled) {
					result = FinderCache.getResult(finderClassName, finderMethodName, finderParams, finderArgs, getSessionFactory());
				}

				if (result == null) {
					try {
						Boolean value = Boolean.valueOf(contains${tempEntity.name}.contains(pk, ${tempEntity.varName}PK));

						FinderCache.putResult(finderClassNameCacheEnabled, finderClassName, finderMethodName, finderParams, finderArgs, value);

						return value.booleanValue();
					}
					catch (DataAccessException dae) {
						throw new SystemException(dae);
					}
				}
				else {
					return ((Boolean)result).booleanValue();
				}
			}

			public boolean contains${tempEntity.names}(${entity.PKClassName} pk) throws SystemException {
				if (get${tempEntity.names}Size(pk)> 0) {
					return true;
				}
				else {
					return false;
				}
			}

			<#if column.isMappingManyToMany()>
				<#assign noSuchTempEntity = serviceBuilder.getNoSuchEntityException(tempEntity)>

				public void add${tempEntity.name}(${entity.PKClassName} pk, ${tempEntity.PKClassName} ${tempEntity.varName}PK) throws ${noSuchEntity}Exception, ${tempEntity.packagePath}.${noSuchTempEntity}Exception, SystemException {
					try {
						add${tempEntity.name}.add(pk, ${tempEntity.varName}PK);
					}
					catch (DataAccessException dae) {
						throw new SystemException(dae);
					}
					finally {
						FinderCache.clearCache("${column.mappingTable}");
					}
				}

				public void add${tempEntity.name}(${entity.PKClassName} pk, ${tempEntity.packagePath}.model.${tempEntity.name} ${tempEntity.varName}) throws ${noSuchEntity}Exception, ${tempEntity.packagePath}.${noSuchTempEntity}Exception, SystemException {
					try {
						add${tempEntity.name}.add(pk, ${tempEntity.varName}.getPrimaryKey());
					}
					catch (DataAccessException dae) {
						throw new SystemException(dae);
					}
					finally {
						FinderCache.clearCache("${column.mappingTable}");
					}
				}

				public void add${tempEntity.names}(${entity.PKClassName} pk, ${tempEntity.PKClassName}[] ${tempEntity.varName}PKs) throws ${noSuchEntity}Exception, ${tempEntity.packagePath}.${noSuchTempEntity}Exception, SystemException {
					try {
						for (int i = 0; i < ${tempEntity.varName}PKs.length; i++) {
							add${tempEntity.name}.add(pk, ${tempEntity.varName}PKs[i]);
						}
					}
					catch (DataAccessException dae) {
						throw new SystemException(dae);
					}
					finally {
						FinderCache.clearCache("${column.mappingTable}");
					}
				}

				public void add${tempEntity.names}(${entity.PKClassName} pk, List ${tempEntity.varNames}) throws ${noSuchEntity}Exception, ${tempEntity.packagePath}.${noSuchTempEntity}Exception, SystemException {
					try {
						for (int i = 0; i < ${tempEntity.varNames}.size(); i++) {
							${tempEntity.packagePath}.model.${tempEntity.name} ${tempEntity.varName} = (${tempEntity.packagePath}.model.${tempEntity.name})${tempEntity.varNames}.get(i);

							add${tempEntity.name}.add(pk, ${tempEntity.varName}.getPrimaryKey());
						}
					}
					catch (DataAccessException dae) {
						throw new SystemException(dae);
					}
					finally {
						FinderCache.clearCache("${column.mappingTable}");
					}
				}

				public void clear${tempEntity.names}(${entity.PKClassName} pk) throws ${noSuchEntity}Exception, SystemException {
					try {
						clear${tempEntity.names}.clear(pk);
					}
					catch (DataAccessException dae) {
						throw new SystemException(dae);
					}
					finally {
						FinderCache.clearCache("${column.mappingTable}");
					}
				}

				public void remove${tempEntity.name}(${entity.PKClassName} pk, ${tempEntity.PKClassName} ${tempEntity.varName}PK) throws ${noSuchEntity}Exception, ${tempEntity.packagePath}.${noSuchTempEntity}Exception, SystemException {
					try {
						remove${tempEntity.name}.remove(pk, ${tempEntity.varName}PK);
					}
					catch (DataAccessException dae) {
						throw new SystemException(dae);
					}
					finally {
						FinderCache.clearCache("${column.mappingTable}");
					}
				}

				public void remove${tempEntity.name}(${entity.PKClassName} pk, ${tempEntity.packagePath}.model.${tempEntity.name} ${tempEntity.varName}) throws ${noSuchEntity}Exception, ${tempEntity.packagePath}.${noSuchTempEntity}Exception, SystemException {
					try {
						remove${tempEntity.name}.remove(pk, ${tempEntity.varName}.getPrimaryKey());
					}
					catch (DataAccessException dae) {
						throw new SystemException(dae);
					}
					finally {
						FinderCache.clearCache("${column.mappingTable}");
					}
				}

				public void remove${tempEntity.names}(${entity.PKClassName} pk, ${tempEntity.PKClassName}[] ${tempEntity.varName}PKs) throws ${noSuchEntity}Exception, ${tempEntity.packagePath}.${noSuchTempEntity}Exception, SystemException {
					try {
						for (int i = 0; i < ${tempEntity.varName}PKs.length; i++) {
							remove${tempEntity.name}.remove(pk, ${tempEntity.varName}PKs[i]);
						}
					}
					catch (DataAccessException dae) {
						throw new SystemException(dae);
					}
					finally {
						FinderCache.clearCache("${column.mappingTable}");
					}
				}

				public void remove${tempEntity.names}(${entity.PKClassName} pk, List ${tempEntity.varNames}) throws ${noSuchEntity}Exception, ${tempEntity.packagePath}.${noSuchTempEntity}Exception, SystemException {
					try {
						for (int i = 0; i < ${tempEntity.varNames}.size(); i++) {
							${tempEntity.packagePath}.model.${tempEntity.name} ${tempEntity.varName} = (${tempEntity.packagePath}.model.${tempEntity.name})${tempEntity.varNames}.get(i);

							remove${tempEntity.name}.remove(pk, ${tempEntity.varName}.getPrimaryKey());
						}
					}
					catch (DataAccessException dae) {
						throw new SystemException(dae);
					}
					finally {
						FinderCache.clearCache("${column.mappingTable}");
					}
				}

				public void set${tempEntity.names}(${entity.PKClassName} pk, ${tempEntity.PKClassName}[] ${tempEntity.varName}PKs) throws ${noSuchEntity}Exception, ${tempEntity.packagePath}.${noSuchTempEntity}Exception, SystemException {
					try {
						clear${tempEntity.names}.clear(pk);

						for (int i = 0; i < ${tempEntity.varName}PKs.length; i++) {
							add${tempEntity.name}.add(pk, ${tempEntity.varName}PKs[i]);
						}
					}
					catch (DataAccessException dae) {
						throw new SystemException(dae);
					}
					finally {
						FinderCache.clearCache("${column.mappingTable}");
					}
				}

				public void set${tempEntity.names}(${entity.PKClassName} pk, List ${tempEntity.varNames}) throws ${noSuchEntity}Exception, ${tempEntity.packagePath}.${noSuchTempEntity}Exception, SystemException {
					try {
						clear${tempEntity.names}.clear(pk);

						for (int i = 0; i < ${tempEntity.varNames}.size(); i++) {
							${tempEntity.packagePath}.model.${tempEntity.name} ${tempEntity.varName} = (${tempEntity.packagePath}.model.${tempEntity.name})${tempEntity.varNames}.get(i);

							add${tempEntity.name}.add(pk, ${tempEntity.varName}.getPrimaryKey());
						}
					}
					catch (DataAccessException dae) {
						throw new SystemException(dae);
					}
					finally {
						FinderCache.clearCache("${column.mappingTable}");
					}
				}
			</#if>
		</#if>
	</#list>

	protected void initDao() {
		<#list entity.columnList as column>
			<#if column.isCollection() && (column.isMappingManyToMany() || column.isMappingOneToMany())>
				<#assign tempEntity = serviceBuilder.getEntity(column.getEJBName())>

				contains${tempEntity.name} = new Contains${tempEntity.name}(this);

				<#if column.isMappingManyToMany()>
					add${tempEntity.name} = new Add${tempEntity.name}(this);
					clear${tempEntity.names} = new Clear${tempEntity.names}(this);
					remove${tempEntity.name} = new Remove${tempEntity.name}(this);
				</#if>
			</#if>
		</#list>
	}

	<#list entity.columnList as column>
		<#if column.isCollection() && (column.isMappingManyToMany() || column.isMappingOneToMany())>
			<#assign tempEntity = serviceBuilder.getEntity(column.getEJBName())>

			protected Contains${tempEntity.name} contains${tempEntity.name};

			<#if column.isMappingManyToMany()>
				protected Add${tempEntity.name} add${tempEntity.name};
				protected Clear${tempEntity.names} clear${tempEntity.names};
				protected Remove${tempEntity.name} remove${tempEntity.name};
			</#if>
		</#if>
	</#list>

	<#list entity.columnList as column>
		<#if column.isCollection() && (column.isMappingManyToMany() || column.isMappingOneToMany())>
			<#assign tempEntity = serviceBuilder.getEntity(column.getEJBName())>
			<#assign entitySqlType = serviceBuilder.getSqlType(packagePath + ".model." + entity.getName(), entity.getPKVarName(), entity.getPKClassName())>
			<#assign tempEntitySqlType = serviceBuilder.getSqlType(tempEntity.getPackagePath() + ".model." + entity.getName(), tempEntity.getPKVarName(), tempEntity.getPKClassName())>

			<#if entity.hasPrimitivePK()>
				<#assign pkVarNameWrapper = "new " + serviceBuilder.getPrimitiveObj(entity.getPKClassName()) + "("+ entity.getPKVarName() +")">
			<#else>
				<#assign pkVarNameWrapper = entity.getPKVarName()>
			</#if>

			<#if tempEntity.hasPrimitivePK()>
				<#assign tempEntityPkVarNameWrapper = "new " + serviceBuilder.getPrimitiveObj(tempEntity.getPKClassName()) + "("+ tempEntity.getPKVarName() +")">
			<#else>
				<#assign tempEntityPkVarNameWrapper = tempEntity.getPKVarName()>
			</#if>

			protected class Contains${tempEntity.name} extends MappingSqlQuery {

				protected Contains${tempEntity.name}(${entity.name}PersistenceImpl persistenceImpl) {
					super(persistenceImpl.getDataSource(), _SQL_CONTAINS${tempEntity.name?upper_case});

					declareParameter(new SqlParameter(Types.${entitySqlType}));
					declareParameter(new SqlParameter(Types.${tempEntitySqlType}));

					compile();
				}

				protected Object mapRow(ResultSet rs, int rowNumber) throws SQLException {
					return new Integer(rs.getInt("COUNT_VALUE"));
				}

				protected boolean contains(${entity.PKClassName} ${entity.PKVarName}, ${tempEntity.PKClassName} ${tempEntity.PKVarName}) {
					List results = execute(new Object[] {${pkVarNameWrapper}, ${tempEntityPkVarNameWrapper}});

					if (results.size()> 0) {
						Integer count = (Integer)results.get(0);

						if (count.intValue()> 0) {
							return true;
						}
					}

					return false;
				}

			}

			<#if column.isMappingManyToMany()>
				protected class Add${tempEntity.name} extends SqlUpdate {

					protected Add${tempEntity.name}(${entity.name}PersistenceImpl persistenceImpl) {
						super(persistenceImpl.getDataSource(), "INSERT INTO ${column.mappingTable} (${entity.PKVarName}, ${tempEntity.PKVarName}) VALUES (?, ?)");

						_persistenceImpl = persistenceImpl;

						declareParameter(new SqlParameter(Types.${entitySqlType}));
						declareParameter(new SqlParameter(Types.${tempEntitySqlType}));

						compile();
					}

					protected void add(${entity.PKClassName} ${entity.PKVarName}, ${tempEntity.PKClassName} ${tempEntity.PKVarName}) {
						if (!_persistenceImpl.contains${tempEntity.name}.contains(${entity.PKVarName}, ${tempEntity.PKVarName})) {
							update(new Object[] {${pkVarNameWrapper}, ${tempEntityPkVarNameWrapper}});
						}
					}

					private ${entity.name}PersistenceImpl _persistenceImpl;

				}

				protected class Clear${tempEntity.names} extends SqlUpdate {

					protected Clear${tempEntity.names}(${entity.name}PersistenceImpl persistenceImpl) {
						super(persistenceImpl.getDataSource(), "DELETE FROM ${column.mappingTable} WHERE ${entity.PKVarName} = ?");

						declareParameter(new SqlParameter(Types.${entitySqlType}));

						compile();
					}

					protected void clear(${entity.PKClassName} ${entity.PKVarName}) {
						update(new Object[] { ${pkVarNameWrapper} });
					}

				}

				protected class Remove${tempEntity.name} extends SqlUpdate {

					protected Remove${tempEntity.name}(${entity.name}PersistenceImpl persistenceImpl) {
						super(persistenceImpl.getDataSource(), "DELETE FROM ${column.mappingTable} WHERE ${entity.PKVarName} = ? AND ${tempEntity.PKVarName} = ?");

						declareParameter(new SqlParameter(Types.${entitySqlType}));
						declareParameter(new SqlParameter(Types.${tempEntitySqlType}));

						compile();
					}

					protected void remove(${entity.PKClassName} ${entity.PKVarName}, ${tempEntity.PKClassName} ${tempEntity.PKVarName}) {
						update(new Object[] {${pkVarNameWrapper}, ${tempEntityPkVarNameWrapper}});
					}

				}
			</#if>
		</#if>
	</#list>

	private static ModelListener _getListener() {
		if (Validator.isNotNull(_LISTENER)) {
			try {
				return (ModelListener)Class.forName(_LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e);
			}
		}

		return null;
	}

	<#list entity.columnList as column>
		<#if column.isCollection()>
			<#assign tempEntity = serviceBuilder.getEntity(column.getEJBName())>

			<#if column.isMappingManyToMany()>
				private static final String _SQL_GET${tempEntity.names?upper_case} = "SELECT {${tempEntity.table}.*} FROM ${tempEntity.table} INNER JOIN ${column.mappingTable} ON (${column.mappingTable}.${tempEntity.PKVarName} = ${tempEntity.table}.${tempEntity.PKVarName}) WHERE (${column.mappingTable}.${entity.PKVarName} = ?)";

				private static final String _SQL_GET${tempEntity.names?upper_case}SIZE = "SELECT COUNT(*) AS COUNT_VALUE FROM ${column.mappingTable} WHERE ${entity.PKVarName} = ?";

				private static final String _SQL_CONTAINS${tempEntity.name?upper_case} = "SELECT COUNT(*) AS COUNT_VALUE FROM ${column.mappingTable} WHERE ${entity.PKVarName} = ? AND ${tempEntity.PKVarName} = ?";
			<#elseif column.isMappingOneToMany()>
				private static final String _SQL_GET${tempEntity.names?upper_case} = "SELECT {${tempEntity.table}.*} FROM ${tempEntity.table} INNER JOIN ${entity.table} ON (${entity.table}.${entity.PKVarName} = ${tempEntity.table}.${entity.PKVarName}) WHERE (${entity.table}.${entity.PKVarName} = ?)";

				private static final String _SQL_GET${tempEntity.names?upper_case}SIZE = "SELECT COUNT(*) AS COUNT_VALUE FROM ${tempEntity.table} WHERE ${entity.PKVarName} = ?";

				private static final String _SQL_CONTAINS${tempEntity.name?upper_case} = "SELECT COUNT(*) AS COUNT_VALUE FROM ${tempEntity.table} WHERE ${entity.PKVarName} = ? AND ${tempEntity.PKVarName} = ?";
			</#if>
		</#if>
	</#list>

	private static final String _LISTENER = GetterUtil.getString(PropsUtil.get("value.object.listener.${packagePath}.model.${entity.name}"));

	private static Log _log = LogFactory.getLog(${entity.name}PersistenceImpl.class);

}