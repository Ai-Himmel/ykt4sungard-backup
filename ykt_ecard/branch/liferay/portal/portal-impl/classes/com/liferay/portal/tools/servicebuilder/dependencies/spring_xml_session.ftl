<bean id="${packagePath}.service.${entity.name}${sessionType}Service.impl" class="${packagePath}.service.impl.${entity.name}${sessionType}ServiceImpl" lazy-init="true" />
<bean id="${packagePath}.service.${entity.name}${sessionType}Service.transaction" class="org.springframework.transaction.interceptor.TransactionProxyFactoryBean" lazy-init="true">
	<property name="transactionManager">
		<ref bean="${entity.TXManager}" />
	</property>
	<property name="target">
		<ref bean="${packagePath}.service.${entity.name}${sessionType}Service.impl" />
	</property>
	<property name="transactionAttributes">
		<props>
			<#assign txRequiredList = entity.getTxRequiredList()>

			<#list txRequiredList as txRequired>
				<prop key="${txRequired}">PROPAGATION_REQUIRED,-com.liferay.portal.PortalException,-com.liferay.portal.SystemException</prop>
			</#list>

			<prop key="add*">PROPAGATION_REQUIRED,-com.liferay.portal.PortalException,-com.liferay.portal.SystemException</prop>
			<prop key="check*">PROPAGATION_REQUIRED,-com.liferay.portal.PortalException,-com.liferay.portal.SystemException</prop>
			<prop key="clear*">PROPAGATION_REQUIRED,-com.liferay.portal.PortalException,-com.liferay.portal.SystemException</prop>
			<prop key="delete*">PROPAGATION_REQUIRED,-com.liferay.portal.PortalException,-com.liferay.portal.SystemException</prop>
			<prop key="set*">PROPAGATION_REQUIRED,-com.liferay.portal.PortalException,-com.liferay.portal.SystemException</prop>
			<prop key="update*">PROPAGATION_REQUIRED,-com.liferay.portal.PortalException,-com.liferay.portal.SystemException</prop>
			<prop key="*">PROPAGATION_SUPPORTS,readOnly</prop>
		</props>
	</property>
</bean>
<bean id="${packagePath}.service.${entity.name}${sessionType}ServiceFactory" class="${packagePath}.service.${entity.name}${sessionType}ServiceFactory" lazy-init="true">
	<property name="service">
		<ref bean="${packagePath}.service.${entity.name}${sessionType}Service.transaction" />
	</property>
</bean>