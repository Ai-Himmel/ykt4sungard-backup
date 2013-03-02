package ${packagePath}.model.impl;

<#if entity.hasCompoundPK()>
	import ${packagePath}.service.persistence.${entity.name}PK;
</#if>

import ${packagePath}.model.${entity.name};
import ${baseModelImplPackage}.BaseModelImpl;
import ${propsUtilPackage}.PropsUtil;
import com.liferay.portal.kernel.bean.ReadOnlyBeanHandler;
import com.liferay.portal.kernel.util.DateUtil;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.util.Html;
import java.io.Serializable;
import java.lang.reflect.Proxy;
import java.sql.Types;
import java.util.Date;

/**
 * <a href="${entity.name}ModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>${entity.name}</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see ${packagePath}.service.model.${entity.name}
 * @see ${packagePath}.service.model.${entity.name}Model
 * @see ${packagePath}.service.model.impl.${entity.name}Impl
 *
 */
public class ${entity.name}ModelImpl extends BaseModelImpl {

	public static final String TABLE_NAME = "${entity.table}";

	public static final Object[][] TABLE_COLUMNS = {
		<#list entity.getRegularColList() as column>
			<#assign sqlType = serviceBuilder.getSqlType(packagePath + ".model." + entity.getName(), column.getName(), column.getType())>

			{"${column.DBName}", new Integer(Types.${sqlType})}

			<#if column_has_next>
				,
			</#if>
		</#list>
	};

	public static final String TABLE_SQL_CREATE = "${serviceBuilder.getCreateTableSQL(entity)}";

	public static final String TABLE_SQL_DROP = "drop table ${entity.table}";

	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get("value.object.finder.cache.enabled.${packagePath}.model.${entity.name}"), true);

	<#list entity.columnList as column>
		<#if column.mappingTable??>
			public static final boolean CACHE_ENABLED_${stringUtil.upperCase(column.mappingTable)} =

			<#assign entityShortName = stringUtil.shorten(entity.name, 10, "")>

			<#if stringUtil.startsWith(column.mappingTable, entityShortName)>
				GetterUtil.getBoolean(PropsUtil.get("value.object.finder.cache.enabled.${column.mappingTable}"), true)
			<#else>
				<#assign tempEntity = serviceBuilder.getEntity(column.getEJBName())>

				${tempEntity.packagePath}.model.impl.${tempEntity.name}ModelImpl.CACHE_ENABLED_${stringUtil.upperCase(column.mappingTable)}
			</#if>

			;
		</#if>
	</#list>

	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get("lock.expiration.time.${packagePath}.model.${entity.name}"));

	public ${entity.name}ModelImpl() {
	}

	public ${entity.PKClassName} getPrimaryKey() {
		<#if entity.hasCompoundPK()>
			return new ${entity.PKClassName}(

			<#list entity.PKList as column>
				_${column.name}

				<#if column_has_next>
					,
				</#if>
			</#list>

			);
		<#else>
			return _${entity.PKList[0].name};
		</#if>
	}

	public void setPrimaryKey(${entity.PKClassName} pk) {
		<#if entity.hasCompoundPK()>
			<#list entity.PKList as column>
				set${column.methodName}(pk.${column.name});
			</#list>
		<#else>
			set${entity.PKList[0].methodName}(pk);
		</#if>
	}

	public Serializable getPrimaryKeyObj() {
		<#if entity.hasCompoundPK()>
			return new ${entity.PKClassName}(

			<#list entity.PKList as column>
				_${column.name}

				<#if column_has_next>
					,
				</#if>
			</#list>

			);
		<#else>
			return

			<#if entity.hasPrimitivePK()>
				new ${serviceBuilder.getPrimitiveObj("${entity.PKClassName}")} (
			</#if>

			_${entity.PKList[0].name}

			<#if entity.hasPrimitivePK()>
				)
			</#if>

			;
		</#if>
	}

	<#list entity.regularColList as column>
		public ${column.type} get${column.methodName}() {
			<#if column.type == "String" && column.isConvertNull()>
				return GetterUtil.getString(_${column.name});
			<#else>
				return _${column.name};
			</#if>
		}

		<#if column.type== "boolean">
			public ${column.type} is${column.methodName}() {
				return _${column.name};
			}
		</#if>

		public void set${column.methodName}(${column.type} ${column.name}) {
			<#if column.name == "uuid">
				if ((uuid != null) && (uuid != _uuid)) {
					_uuid = uuid;
				}
			<#else>
				if (

				<#if column.isPrimitiveType()>
					${column.name} != _${column.name}
				<#else>
					(${column.name} == null && _${column.name} != null) ||
					(${column.name} != null && _${column.name} == null) ||
					(${column.name} != null && _${column.name} != null && !${column.name}.equals(_${column.name}))
				</#if>

				) {
					_${column.name} = ${column.name};
				}
			</#if>
		}
	</#list>

	public ${entity.name} toEscapedModel() {
		if (isEscapedModel()) {
			return (${entity.name})this;
		}
		else {
			${entity.name} model = new ${entity.name}Impl();

			model.setEscapedModel(true);

			<#list entity.regularColList as column>
				model.set${column.methodName}(

				<#if column.EJBName??>
					(${column.EJBName})get${column.methodName}().clone()
				<#else>
					<#assign autoEscape = true>

					<#assign modelName = packagePath + ".model." + entity.name>

					<#if modelHintsUtil.getHints(modelName, column.name)??>
						<#assign hints = modelHintsUtil.getHints(modelName, column.name)>

						<#if hints.get("auto-escape")??>
							<#assign autoEscapeHintValue = hints.get("auto-escape")>

							<#if autoEscapeHintValue == "false">
								<#assign autoEscape = false>
							</#if>
						</#if>
					</#if>

					<#if autoEscape && (column.type == "String")>
						Html.escape(
					</#if>

					get${column.methodName}()

					<#if autoEscape && (column.type == "String")>
						)
					</#if>
				</#if>

				);
			</#list>

			model = (${entity.name})Proxy.newProxyInstance(${entity.name}.class.getClassLoader(), new Class[] {${entity.name}.class}, new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		 ${entity.name}Impl clone = new ${entity.name}Impl();

		<#list entity.regularColList as column>
			clone.set${column.methodName}(

			<#if column.EJBName??>
				(${column.EJBName})get${column.methodName}().clone()
			<#else>
				get${column.methodName}()
			</#if>

			);
		</#list>

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		${entity.name}Impl ${entity.varName} = (${entity.name}Impl)obj;

		<#if entity.isOrdered()>
			int value = 0;

			<#list entity.order.columns as column>
				<#if column.isPrimitiveType()>
					<#if column.type == "boolean">
						<#assign ltComparator = "==">
						<#assign gtComparator = "!=">
					<#else>
						<#assign ltComparator = "<">
						<#assign gtComparator = ">">
					</#if>

					if (get${column.methodName}() ${ltComparator} ${entity.varName}.get${column.methodName}()) {
						value = -1;
					}
					else if (get${column.methodName}() ${gtComparator} ${entity.varName}.get${column.methodName}()) {
						value = 1;
					}
					else {
						value = 0;
					}
				<#else>
					<#if column.type == "Date">
						value = DateUtil.compareTo(get${column.methodName}(), ${entity.varName}.get${column.methodName}());
					<#else>
						<#if column.isCaseSensitive()>
							value = get${column.methodName}().compareTo(${entity.varName}.get${column.methodName}());
						<#else>
							value = get${column.methodName}().toLowerCase().compareTo(${entity.varName}.get${column.methodName}().toLowerCase());
						</#if>
					</#if>
				</#if>

				<#if !column.isOrderByAscending()>
					value = value * -1;
				</#if>

				if (value != 0) {
					return value;
				}
			</#list>

			return 0;
		<#else>
			${entity.PKClassName} pk = ${entity.varName}.getPrimaryKey();

			<#if entity.hasPrimitivePK()>
				if (getPrimaryKey() < pk) {
					return -1;
				}
				else if (getPrimaryKey() > pk) {
					return 1;
				}
				else {
					return 0;
				}
			<#else>
				return getPrimaryKey().compareTo(pk);
			</#if>
		</#if>
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		${entity.name}Impl ${entity.varName} = null;

		try {
			${entity.varName} = (${entity.name}Impl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		${entity.PKClassName} pk = ${entity.varName}.getPrimaryKey();

		<#if entity.hasPrimitivePK()>
			if (getPrimaryKey() == pk) {
		<#else>
			if (getPrimaryKey().equals(pk)) {
		</#if>

			return true;
		}
		else{
			return false;
		}
	}

	public int hashCode() {
		<#if entity.hasPrimitivePK()>
			return (int)getPrimaryKey();
		<#else>
			return getPrimaryKey().hashCode();
		</#if>
	}

	<#list entity.regularColList as column>
		private ${column.type} _${column.name};
	</#list>

}