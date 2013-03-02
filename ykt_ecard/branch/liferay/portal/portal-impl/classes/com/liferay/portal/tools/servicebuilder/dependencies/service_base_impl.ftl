package ${packagePath}.service.base;

import ${packagePath}.service.${entity.name}${sessionTypeName}Service;

<#if sessionTypeName == "">
	import ${principalBeanPackage}.PrincipalBean;
</#if>

<#if entity.hasColumns()>
	import ${packagePath}.model.${entity.name};
	import ${packagePath}.model.impl.${entity.name}Impl;
	import com.liferay.portal.SystemException;
	import com.liferay.portal.kernel.dao.DynamicQueryInitializer;
	import java.util.List;
</#if>

<#list referenceList as tempEntity>
	<#if entity.equals(tempEntity)>
		<#if sessionTypeName == "" && tempEntity.hasLocalService()>
			import ${tempEntity.packagePath}.service.${tempEntity.name}LocalService;
			import ${tempEntity.packagePath}.service.${tempEntity.name}LocalServiceFactory;
		</#if>
	<#else>
		<#if tempEntity.hasLocalService()>
			import ${tempEntity.packagePath}.service.${tempEntity.name}LocalService;
			import ${tempEntity.packagePath}.service.${tempEntity.name}LocalServiceFactory;
		</#if>
		<#if tempEntity.hasRemoteService()>
			import ${tempEntity.packagePath}.service.${tempEntity.name}Service;
			import ${tempEntity.packagePath}.service.${tempEntity.name}ServiceFactory;
		</#if>
	</#if>

	<#if tempEntity.hasColumns()>
		import ${tempEntity.packagePath}.service.persistence.${tempEntity.name}Persistence;
		import ${tempEntity.packagePath}.service.persistence.${tempEntity.name}Util;
	</#if>

	<#if tempEntity.hasFinderClass()>
		import ${tempEntity.packagePath}.service.persistence.${tempEntity.name}Finder;
		import ${tempEntity.packagePath}.service.persistence.${tempEntity.name}FinderUtil;
	</#if>
</#list>

import org.springframework.beans.factory.InitializingBean;

<#if sessionTypeName == "Local">
	public abstract class ${entity.name}LocalServiceBaseImpl implements ${entity.name}LocalService, InitializingBean {
<#else>
	public abstract class ${entity.name}ServiceBaseImpl extends PrincipalBean implements ${entity.name}Service, InitializingBean {
</#if>

<#if sessionTypeName == "Local" && entity.hasColumns()>
	public ${entity.name} add${entity.name}(${entity.name} model) throws SystemException {
		${entity.name} ${entity.varName} = new ${entity.name}Impl();

		${entity.varName}.setNew(true);

		<#list entity.regularColList as column>
			${entity.varName}.set${column.methodName}(model.get${column.methodName}());
		</#list>

		return ${entity.varName}Persistence.update(${entity.varName});
	}

	public List dynamicQuery(DynamicQueryInitializer queryInitializer) throws SystemException {
		return ${entity.varName}Persistence.findWithDynamicQuery(queryInitializer);
	}

	public List dynamicQuery(DynamicQueryInitializer queryInitializer, int begin, int end) throws SystemException {
		return ${entity.varName}Persistence.findWithDynamicQuery(queryInitializer, begin, end);
	}

	public ${entity.name} update${entity.name}(${entity.name} model) throws SystemException {
		${entity.name} ${entity.varName} = new ${entity.name}Impl();

		${entity.varName}.setNew(false);

		<#list entity.regularColList as column>
			${entity.varName}.set${column.methodName}(model.get${column.methodName}());
		</#list>

		return ${entity.varName}Persistence.update(${entity.varName});
	}
</#if>

<#list referenceList as tempEntity>
	<#if entity.equals(tempEntity)>
		<#if sessionTypeName == "" && tempEntity.hasLocalService()>
			public ${tempEntity.name}LocalService get${tempEntity.name}LocalService() {
				return ${tempEntity.varName}LocalService;
			}

			public void set${tempEntity.name}LocalService(${tempEntity.name}LocalService ${tempEntity.varName}LocalService) {
				this.${tempEntity.varName}LocalService = ${tempEntity.varName}LocalService;
			}
		</#if>
	<#else>
		<#if tempEntity.hasLocalService()>
			public ${tempEntity.name}LocalService get${tempEntity.name}LocalService() {
				return ${tempEntity.varName}LocalService;
			}

			public void set${tempEntity.name}LocalService(${tempEntity.name}LocalService ${tempEntity.varName}LocalService) {
				this.${tempEntity.varName}LocalService = ${tempEntity.varName}LocalService;
			}
		</#if>

		<#if tempEntity.hasRemoteService()>
			public ${tempEntity.name}Service get${tempEntity.name}Service() {
				return ${tempEntity.varName}Service;
			}

			public void set${tempEntity.name}Service(${tempEntity.name}Service ${tempEntity.varName}Service) {
				this.${tempEntity.varName}Service = ${tempEntity.varName}Service;
			}
		</#if>
	</#if>

	<#if tempEntity.hasColumns()>
		public ${tempEntity.name}Persistence get${tempEntity.name}Persistence() {
			return ${tempEntity.varName}Persistence;
		}

		public void set${tempEntity.name}Persistence(${tempEntity.name}Persistence ${tempEntity.varName}Persistence) {
			this.${tempEntity.varName}Persistence = ${tempEntity.varName}Persistence;
		}
	</#if>

	<#if tempEntity.hasFinderClass()>
		public ${tempEntity.name}Finder get${tempEntity.name}Finder() {
			return ${tempEntity.varName}Finder;
		}

		public void set${tempEntity.name}Finder(${tempEntity.name}Finder ${tempEntity.varName}Finder) {
			this.${tempEntity.varName}Finder = ${tempEntity.varName}Finder;
		}
	</#if>
</#list>

public void afterPropertiesSet() {
	<#list referenceList as tempEntity>
		<#if entity.equals(tempEntity)>
			<#if sessionTypeName == "" && tempEntity.hasLocalService()>
				if (${tempEntity.varName}LocalService == null) {
					${tempEntity.varName}LocalService = ${tempEntity.name}LocalServiceFactory.getImpl();
				}
			</#if>
		<#else>
			<#if tempEntity.hasLocalService()>
				if (${tempEntity.varName}LocalService == null) {
					${tempEntity.varName}LocalService = ${tempEntity.name}LocalServiceFactory.getImpl();
				}
			</#if>

			<#if tempEntity.hasRemoteService()>
				if (${tempEntity.varName}Service == null) {
					${tempEntity.varName}Service = ${tempEntity.name}ServiceFactory.getImpl();
				}
			</#if>
		</#if>

		<#if tempEntity.hasColumns()>
			if (${tempEntity.varName}Persistence == null) {
				${tempEntity.varName}Persistence = ${tempEntity.name}Util.getPersistence();
			}
		</#if>

		<#if tempEntity.hasFinderClass()>
			if (${tempEntity.varName}Finder == null) {
				${tempEntity.varName}Finder = ${tempEntity.name}FinderUtil.getFinder();
			}
		</#if>
	</#list>
}

<#list referenceList as tempEntity>
	<#if entity.equals(tempEntity)>
		<#if (sessionTypeName == "") && tempEntity.hasLocalService()>
			protected ${tempEntity.name}LocalService ${tempEntity.varName}LocalService;
		</#if>
	<#else>
		<#if tempEntity.hasLocalService()>
			protected ${tempEntity.name}LocalService ${tempEntity.varName}LocalService;
		</#if>

		<#if tempEntity.hasRemoteService()>
			protected ${tempEntity.name}Service ${tempEntity.varName}Service;
		</#if>
	</#if>

	<#if tempEntity.hasColumns()>
		protected ${tempEntity.name}Persistence ${tempEntity.varName}Persistence;
	</#if>

	<#if tempEntity.hasFinderClass()>
		protected ${tempEntity.name}Finder ${tempEntity.varName}Finder;
	</#if>
</#list>

}