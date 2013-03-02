<#list entities as entity>
	<#if entity.hasLocalService()>
		<#assign sessionType = "Local">

		<#include "spring_xml_session.ftl">
	</#if>
	<#if entity.hasRemoteService()>
		<#assign sessionType = "">

		<#include "spring_xml_session.ftl">
	</#if>

	<#if entity.hasColumns()>
		<bean id="${packagePath}.service.persistence.${entity.name}Persistence.impl" class="${entity.getPersistenceClass()}" lazy-init="true">
			<property name="dataSource">
				<ref bean="${entity.getDataSource()}" />
			</property>
			<property name="sessionFactory">
				<ref bean="${entity.getSessionFactory()}" />
			</property>
		</bean>
		<bean id="${packagePath}.service.persistence.${entity.name}Persistence.transaction" class="org.springframework.transaction.interceptor.TransactionProxyFactoryBean" lazy-init="true">
			<property name="transactionManager">
				<ref bean="liferayTransactionManager" />
			</property>
			<property name="target">
				<ref bean="${packagePath}.service.persistence.${entity.name}Persistence.impl" />
			</property>
			<property name="transactionAttributes">
				<props>
					<prop key="remove*">PROPAGATION_REQUIRED,-com.liferay.portal.PortalException,-com.liferay.portal.SystemException</prop>
					<prop key="set*">PROPAGATION_REQUIRED,-com.liferay.portal.PortalException,-com.liferay.portal.SystemException</prop>
					<prop key="update*">PROPAGATION_REQUIRED,-com.liferay.portal.PortalException,-com.liferay.portal.SystemException</prop>
					<prop key="*">PROPAGATION_SUPPORTS,readOnly</prop>
				</props>
			</property>
		</bean>
		<bean id="${packagePath}.service.persistence.${entity.name}Util" class="${packagePath}.service.persistence.${entity.name}Util" lazy-init="true">
			<property name="persistence">
				<ref bean="${packagePath}.service.persistence.${entity.name}Persistence.impl" />
			</property>
		</bean>
	</#if>

	<#if entity.hasFinderClass()>
		<bean id="${packagePath}.service.persistence.${entity.name}Finder.impl" class="${entity.finderClass}" lazy-init="true" />
		<bean id="${packagePath}.service.persistence.${entity.name}FinderUtil" class="${packagePath}.service.persistence.${entity.name}FinderUtil" lazy-init="true">
			<property name="finder">
				<ref bean="${packagePath}.service.persistence.${entity.name}Finder.impl" />
			</property>
		</bean>
	</#if>
</#list>