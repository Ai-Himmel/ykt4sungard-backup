Liferay.Service.Portal = {
	servicePackage: "com.liferay.portal.service.http."
};

Liferay.Service.Portal.Address = {
	serviceClassName: Liferay.Service.Portal.servicePackage + "Address" + Liferay.Service.classNameSuffix,

	addAddress: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addAddress";

		return Liferay.Service.ajax(params, callback);
	},

	deleteAddress: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteAddress";

		return Liferay.Service.ajax(params, callback);
	},

	getAddress: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getAddress";

		return Liferay.Service.ajax(params, callback);
	},

	getAddresses: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getAddresses";

		return Liferay.Service.ajax(params, callback);
	},

	updateAddress: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateAddress";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Portal.ClassName = {
	serviceClassName: Liferay.Service.Portal.servicePackage + "ClassName" + Liferay.Service.classNameSuffix,

	getClassName: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getClassName";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Portal.Company = {
	serviceClassName: Liferay.Service.Portal.servicePackage + "Company" + Liferay.Service.classNameSuffix,

	addCompany: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addCompany";

		return Liferay.Service.ajax(params, callback);
	},

	updateCompany: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateCompany";

		return Liferay.Service.ajax(params, callback);
	},

	updateDisplay: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateDisplay";

		return Liferay.Service.ajax(params, callback);
	},

	updateSecurity: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateSecurity";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Portal.Country = {
	serviceClassName: Liferay.Service.Portal.servicePackage + "Country" + Liferay.Service.classNameSuffix,

	addCountry: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addCountry";

		return Liferay.Service.ajax(params, callback);
	},

	getCountries: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getCountries";

		return Liferay.Service.ajax(params, callback);
	},

	getCountry: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getCountry";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Portal.EmailAddress = {
	serviceClassName: Liferay.Service.Portal.servicePackage + "EmailAddress" + Liferay.Service.classNameSuffix,

	addEmailAddress: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addEmailAddress";

		return Liferay.Service.ajax(params, callback);
	},

	deleteEmailAddress: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteEmailAddress";

		return Liferay.Service.ajax(params, callback);
	},

	getEmailAddress: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getEmailAddress";

		return Liferay.Service.ajax(params, callback);
	},

	getEmailAddresses: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getEmailAddresses";

		return Liferay.Service.ajax(params, callback);
	},

	updateEmailAddress: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateEmailAddress";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Portal.Group = {
	serviceClassName: Liferay.Service.Portal.servicePackage + "Group" + Liferay.Service.classNameSuffix,

	addGroup: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addGroup";

		return Liferay.Service.ajax(params, callback);
	},

	addRoleGroups: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addRoleGroups";

		return Liferay.Service.ajax(params, callback);
	},

	deleteGroup: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteGroup";

		return Liferay.Service.ajax(params, callback);
	},

	getGroup: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getGroup";

		return Liferay.Service.ajax(params, callback);
	},

	getOrganizationsGroups: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getOrganizationsGroups";

		return Liferay.Service.ajax(params, callback);
	},

	getUserGroupsGroups: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getUserGroupsGroups";

		return Liferay.Service.ajax(params, callback);
	},

	hasUserGroup: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "hasUserGroup";

		return Liferay.Service.ajax(params, callback);
	},

	search: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "search";

		return Liferay.Service.ajax(params, callback);
	},

	searchCount: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "searchCount";

		return Liferay.Service.ajax(params, callback);
	},

	setRoleGroups: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "setRoleGroups";

		return Liferay.Service.ajax(params, callback);
	},

	unsetRoleGroups: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "unsetRoleGroups";

		return Liferay.Service.ajax(params, callback);
	},

	updateGroup: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateGroup";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Portal.Layout = {
	serviceClassName: Liferay.Service.Portal.servicePackage + "Layout" + Liferay.Service.classNameSuffix,

	addLayout: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addLayout";

		return Liferay.Service.ajax(params, callback);
	},

	deleteLayout: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteLayout";

		return Liferay.Service.ajax(params, callback);
	},

	getLayoutName: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getLayoutName";

		return Liferay.Service.ajax(params, callback);
	},

	getLayoutReferences: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getLayoutReferences";

		return Liferay.Service.ajax(params, callback);
	},

	setLayouts: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "setLayouts";

		return Liferay.Service.ajax(params, callback);
	},

	updateLayout: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateLayout";

		return Liferay.Service.ajax(params, callback);
	},

	updateLookAndFeel: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateLookAndFeel";

		return Liferay.Service.ajax(params, callback);
	},

	updateName: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateName";

		return Liferay.Service.ajax(params, callback);
	},

	updateParentLayoutId: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateParentLayoutId";

		return Liferay.Service.ajax(params, callback);
	},

	updatePriority: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updatePriority";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Portal.LayoutSet = {
	serviceClassName: Liferay.Service.Portal.servicePackage + "LayoutSet" + Liferay.Service.classNameSuffix,

	updateLookAndFeel: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateLookAndFeel";

		return Liferay.Service.ajax(params, callback);
	},

	updateVirtualHost: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateVirtualHost";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Portal.ListType = {
	serviceClassName: Liferay.Service.Portal.servicePackage + "ListType" + Liferay.Service.classNameSuffix,

	getListType: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getListType";

		return Liferay.Service.ajax(params, callback);
	},

	getListTypes: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getListTypes";

		return Liferay.Service.ajax(params, callback);
	},

	validate: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "validate";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Portal.MembershipRequest = {
	serviceClassName: Liferay.Service.Portal.servicePackage + "MembershipRequest" + Liferay.Service.classNameSuffix,

	addMembershipRequest: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addMembershipRequest";

		return Liferay.Service.ajax(params, callback);
	},

	deleteMembershipRequests: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteMembershipRequests";

		return Liferay.Service.ajax(params, callback);
	},

	getMembershipRequest: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getMembershipRequest";

		return Liferay.Service.ajax(params, callback);
	},

	updateStatus: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateStatus";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Portal.Organization = {
	serviceClassName: Liferay.Service.Portal.servicePackage + "Organization" + Liferay.Service.classNameSuffix,

	addGroupOrganizations: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addGroupOrganizations";

		return Liferay.Service.ajax(params, callback);
	},

	addPasswordPolicyOrganizations: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addPasswordPolicyOrganizations";

		return Liferay.Service.ajax(params, callback);
	},

	addOrganization: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addOrganization";

		return Liferay.Service.ajax(params, callback);
	},

	deleteOrganization: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteOrganization";

		return Liferay.Service.ajax(params, callback);
	},

	getOrganization: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getOrganization";

		return Liferay.Service.ajax(params, callback);
	},

	getOrganizationId: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getOrganizationId";

		return Liferay.Service.ajax(params, callback);
	},

	getUserOrganizations: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getUserOrganizations";

		return Liferay.Service.ajax(params, callback);
	},

	setGroupOrganizations: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "setGroupOrganizations";

		return Liferay.Service.ajax(params, callback);
	},

	unsetGroupOrganizations: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "unsetGroupOrganizations";

		return Liferay.Service.ajax(params, callback);
	},

	unsetPasswordPolicyOrganizations: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "unsetPasswordPolicyOrganizations";

		return Liferay.Service.ajax(params, callback);
	},

	updateOrganization: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateOrganization";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Portal.OrgLabor = {
	serviceClassName: Liferay.Service.Portal.servicePackage + "OrgLabor" + Liferay.Service.classNameSuffix,

	addOrgLabor: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addOrgLabor";

		return Liferay.Service.ajax(params, callback);
	},

	deleteOrgLabor: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteOrgLabor";

		return Liferay.Service.ajax(params, callback);
	},

	getOrgLabor: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getOrgLabor";

		return Liferay.Service.ajax(params, callback);
	},

	getOrgLabors: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getOrgLabors";

		return Liferay.Service.ajax(params, callback);
	},

	updateOrgLabor: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateOrgLabor";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Portal.PasswordPolicy = {
	serviceClassName: Liferay.Service.Portal.servicePackage + "PasswordPolicy" + Liferay.Service.classNameSuffix,

	addPasswordPolicy: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addPasswordPolicy";

		return Liferay.Service.ajax(params, callback);
	},

	deletePasswordPolicy: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deletePasswordPolicy";

		return Liferay.Service.ajax(params, callback);
	},

	updatePasswordPolicy: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updatePasswordPolicy";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Portal.Permission = {
	serviceClassName: Liferay.Service.Portal.servicePackage + "Permission" + Liferay.Service.classNameSuffix,

	checkPermission: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "checkPermission";

		return Liferay.Service.ajax(params, callback);
	},

	hasGroupPermission: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "hasGroupPermission";

		return Liferay.Service.ajax(params, callback);
	},

	hasUserPermission: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "hasUserPermission";

		return Liferay.Service.ajax(params, callback);
	},

	hasUserPermissions: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "hasUserPermissions";

		return Liferay.Service.ajax(params, callback);
	},

	setGroupPermissions: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "setGroupPermissions";

		return Liferay.Service.ajax(params, callback);
	},

	setOrgGroupPermissions: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "setOrgGroupPermissions";

		return Liferay.Service.ajax(params, callback);
	},

	setRolePermission: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "setRolePermission";

		return Liferay.Service.ajax(params, callback);
	},

	setRolePermissions: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "setRolePermissions";

		return Liferay.Service.ajax(params, callback);
	},

	setUserPermissions: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "setUserPermissions";

		return Liferay.Service.ajax(params, callback);
	},

	unsetRolePermission: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "unsetRolePermission";

		return Liferay.Service.ajax(params, callback);
	},

	unsetRolePermissions: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "unsetRolePermissions";

		return Liferay.Service.ajax(params, callback);
	},

	unsetUserPermissions: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "unsetUserPermissions";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Portal.Phone = {
	serviceClassName: Liferay.Service.Portal.servicePackage + "Phone" + Liferay.Service.classNameSuffix,

	addPhone: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addPhone";

		return Liferay.Service.ajax(params, callback);
	},

	deletePhone: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deletePhone";

		return Liferay.Service.ajax(params, callback);
	},

	getPhone: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getPhone";

		return Liferay.Service.ajax(params, callback);
	},

	getPhones: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getPhones";

		return Liferay.Service.ajax(params, callback);
	},

	updatePhone: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updatePhone";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Portal.Portal = {
	serviceClassName: Liferay.Service.Portal.servicePackage + "Portal" + Liferay.Service.classNameSuffix,

	test: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "test";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Portal.PluginSetting = {
	serviceClassName: Liferay.Service.Portal.servicePackage + "PluginSetting" + Liferay.Service.classNameSuffix,

	updatePluginSetting: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updatePluginSetting";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Portal.Portlet = {
	serviceClassName: Liferay.Service.Portal.servicePackage + "Portlet" + Liferay.Service.classNameSuffix,

	updatePortlet: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updatePortlet";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Portal.Region = {
	serviceClassName: Liferay.Service.Portal.servicePackage + "Region" + Liferay.Service.classNameSuffix,

	addRegion: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addRegion";

		return Liferay.Service.ajax(params, callback);
	},

	getRegions: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getRegions";

		return Liferay.Service.ajax(params, callback);
	},

	getRegion: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getRegion";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Portal.Resource = {
	serviceClassName: Liferay.Service.Portal.servicePackage + "Resource" + Liferay.Service.classNameSuffix,

	getResource: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getResource";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Portal.Role = {
	serviceClassName: Liferay.Service.Portal.servicePackage + "Role" + Liferay.Service.classNameSuffix,

	addRole: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addRole";

		return Liferay.Service.ajax(params, callback);
	},

	addUserRoles: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addUserRoles";

		return Liferay.Service.ajax(params, callback);
	},

	deleteRole: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteRole";

		return Liferay.Service.ajax(params, callback);
	},

	getGroupRole: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getGroupRole";

		return Liferay.Service.ajax(params, callback);
	},

	getGroupRoles: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getGroupRoles";

		return Liferay.Service.ajax(params, callback);
	},

	getRole: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getRole";

		return Liferay.Service.ajax(params, callback);
	},

	getUserGroupRoles: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getUserGroupRoles";

		return Liferay.Service.ajax(params, callback);
	},

	getUserRelatedRoles: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getUserRelatedRoles";

		return Liferay.Service.ajax(params, callback);
	},

	getUserRoles: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getUserRoles";

		return Liferay.Service.ajax(params, callback);
	},

	hasUserRole: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "hasUserRole";

		return Liferay.Service.ajax(params, callback);
	},

	hasUserRoles: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "hasUserRoles";

		return Liferay.Service.ajax(params, callback);
	},

	unsetUserRoles: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "unsetUserRoles";

		return Liferay.Service.ajax(params, callback);
	},

	updateRole: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateRole";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Portal.User = {
	serviceClassName: Liferay.Service.Portal.servicePackage + "User" + Liferay.Service.classNameSuffix,

	addGroupUsers: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addGroupUsers";

		return Liferay.Service.ajax(params, callback);
	},

	addOrganizationUsers: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addOrganizationUsers";

		return Liferay.Service.ajax(params, callback);
	},

	addPasswordPolicyUsers: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addPasswordPolicyUsers";

		return Liferay.Service.ajax(params, callback);
	},

	addRoleUsers: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addRoleUsers";

		return Liferay.Service.ajax(params, callback);
	},

	addUserGroupUsers: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addUserGroupUsers";

		return Liferay.Service.ajax(params, callback);
	},

	addUser: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addUser";

		return Liferay.Service.ajax(params, callback);
	},

	deleteRoleUser: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteRoleUser";

		return Liferay.Service.ajax(params, callback);
	},

	deleteUser: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteUser";

		return Liferay.Service.ajax(params, callback);
	},

	getDefaultUserId: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getDefaultUserId";

		return Liferay.Service.ajax(params, callback);
	},

	getGroupUsers: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getGroupUsers";

		return Liferay.Service.ajax(params, callback);
	},

	getRoleUsers: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getRoleUsers";

		return Liferay.Service.ajax(params, callback);
	},

	getUserByEmailAddress: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getUserByEmailAddress";

		return Liferay.Service.ajax(params, callback);
	},

	getUserById: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getUserById";

		return Liferay.Service.ajax(params, callback);
	},

	getUserByScreenName: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getUserByScreenName";

		return Liferay.Service.ajax(params, callback);
	},

	getUserIdByEmailAddress: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getUserIdByEmailAddress";

		return Liferay.Service.ajax(params, callback);
	},

	getUserIdByScreenName: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getUserIdByScreenName";

		return Liferay.Service.ajax(params, callback);
	},

	hasGroupUser: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "hasGroupUser";

		return Liferay.Service.ajax(params, callback);
	},

	hasRoleUser: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "hasRoleUser";

		return Liferay.Service.ajax(params, callback);
	},

	setRoleUsers: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "setRoleUsers";

		return Liferay.Service.ajax(params, callback);
	},

	setUserGroupUsers: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "setUserGroupUsers";

		return Liferay.Service.ajax(params, callback);
	},

	unsetGroupUsers: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "unsetGroupUsers";

		return Liferay.Service.ajax(params, callback);
	},

	unsetOrganizationUsers: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "unsetOrganizationUsers";

		return Liferay.Service.ajax(params, callback);
	},

	unsetPasswordPolicyUsers: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "unsetPasswordPolicyUsers";

		return Liferay.Service.ajax(params, callback);
	},

	unsetRoleUsers: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "unsetRoleUsers";

		return Liferay.Service.ajax(params, callback);
	},

	unsetUserGroupUsers: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "unsetUserGroupUsers";

		return Liferay.Service.ajax(params, callback);
	},

	updateActive: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateActive";

		return Liferay.Service.ajax(params, callback);
	},

	updateAgreedToTermsOfUse: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateAgreedToTermsOfUse";

		return Liferay.Service.ajax(params, callback);
	},

	updateLockout: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateLockout";

		return Liferay.Service.ajax(params, callback);
	},

	updateOrganizations: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateOrganizations";

		return Liferay.Service.ajax(params, callback);
	},

	updatePassword: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updatePassword";

		return Liferay.Service.ajax(params, callback);
	},

	updatePortrait: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updatePortrait";

		return Liferay.Service.ajax(params, callback);
	},

	updateUser: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateUser";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Portal.UserGroup = {
	serviceClassName: Liferay.Service.Portal.servicePackage + "UserGroup" + Liferay.Service.classNameSuffix,

	addGroupUserGroups: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addGroupUserGroups";

		return Liferay.Service.ajax(params, callback);
	},

	addUserGroup: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addUserGroup";

		return Liferay.Service.ajax(params, callback);
	},

	deleteUserGroup: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteUserGroup";

		return Liferay.Service.ajax(params, callback);
	},

	getUserGroup: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getUserGroup";

		return Liferay.Service.ajax(params, callback);
	},

	getUserUserGroups: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getUserUserGroups";

		return Liferay.Service.ajax(params, callback);
	},

	unsetGroupUserGroups: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "unsetGroupUserGroups";

		return Liferay.Service.ajax(params, callback);
	},

	updateUserGroup: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateUserGroup";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Portal.UserGroupRole = {
	serviceClassName: Liferay.Service.Portal.servicePackage + "UserGroupRole" + Liferay.Service.classNameSuffix,

	addUserGroupRoles: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addUserGroupRoles";

		return Liferay.Service.ajax(params, callback);
	},

	deleteUserGroupRoles: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteUserGroupRoles";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Portal.Website = {
	serviceClassName: Liferay.Service.Portal.servicePackage + "Website" + Liferay.Service.classNameSuffix,

	addWebsite: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addWebsite";

		return Liferay.Service.ajax(params, callback);
	},

	deleteWebsite: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteWebsite";

		return Liferay.Service.ajax(params, callback);
	},

	getWebsite: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getWebsite";

		return Liferay.Service.ajax(params, callback);
	},

	getWebsites: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getWebsites";

		return Liferay.Service.ajax(params, callback);
	},

	updateWebsite: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateWebsite";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Blogs = {
	servicePackage: "com.liferay.portlet.blogs.service.http."
};

Liferay.Service.Blogs.BlogsEntry = {
	serviceClassName: Liferay.Service.Blogs.servicePackage + "BlogsEntry" + Liferay.Service.classNameSuffix,

	deleteEntry: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteEntry";

		return Liferay.Service.ajax(params, callback);
	},

	getCompanyEntries: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getCompanyEntries";

		return Liferay.Service.ajax(params, callback);
	},

	getCompanyEntriesRSS: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getCompanyEntriesRSS";

		return Liferay.Service.ajax(params, callback);
	},

	getEntry: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getEntry";

		return Liferay.Service.ajax(params, callback);
	},

	getGroupEntries: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getGroupEntries";

		return Liferay.Service.ajax(params, callback);
	},

	getGroupEntriesRSS: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getGroupEntriesRSS";

		return Liferay.Service.ajax(params, callback);
	},

	getOrganizationEntries: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getOrganizationEntries";

		return Liferay.Service.ajax(params, callback);
	},

	getOrganizationEntriesRSS: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getOrganizationEntriesRSS";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Bookmarks = {
	servicePackage: "com.liferay.portlet.bookmarks.service.http."
};

Liferay.Service.Bookmarks.BookmarksEntry = {
	serviceClassName: Liferay.Service.Bookmarks.servicePackage + "BookmarksEntry" + Liferay.Service.classNameSuffix,

	addEntry: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addEntry";

		return Liferay.Service.ajax(params, callback);
	},

	deleteEntry: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteEntry";

		return Liferay.Service.ajax(params, callback);
	},

	getEntry: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getEntry";

		return Liferay.Service.ajax(params, callback);
	},

	openEntry: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "openEntry";

		return Liferay.Service.ajax(params, callback);
	},

	updateEntry: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateEntry";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Bookmarks.BookmarksFolder = {
	serviceClassName: Liferay.Service.Bookmarks.servicePackage + "BookmarksFolder" + Liferay.Service.classNameSuffix,

	addFolder: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addFolder";

		return Liferay.Service.ajax(params, callback);
	},

	deleteFolder: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteFolder";

		return Liferay.Service.ajax(params, callback);
	},

	getFolder: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getFolder";

		return Liferay.Service.ajax(params, callback);
	},

	updateFolder: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateFolder";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Cal = {
	servicePackage: "com.liferay.portlet.calendar.service.http."
};

Liferay.Service.Cal.CalEvent = {
	serviceClassName: Liferay.Service.Cal.servicePackage + "CalEvent" + Liferay.Service.classNameSuffix,

	addEvent: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addEvent";

		return Liferay.Service.ajax(params, callback);
	},

	deleteEvent: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteEvent";

		return Liferay.Service.ajax(params, callback);
	},

	getEvent: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getEvent";

		return Liferay.Service.ajax(params, callback);
	},

	updateEvent: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateEvent";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.DL = {
	servicePackage: "com.liferay.portlet.documentlibrary.service.http."
};

Liferay.Service.DL.DLFileEntry = {
	serviceClassName: Liferay.Service.DL.servicePackage + "DLFileEntry" + Liferay.Service.classNameSuffix,

	addFileEntry: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addFileEntry";

		return Liferay.Service.ajax(params, callback);
	},

	deleteFileEntry: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteFileEntry";

		return Liferay.Service.ajax(params, callback);
	},

	deleteFileEntryByTitle: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteFileEntryByTitle";

		return Liferay.Service.ajax(params, callback);
	},

	getFileEntry: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getFileEntry";

		return Liferay.Service.ajax(params, callback);
	},

	getFileEntryByTitle: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getFileEntryByTitle";

		return Liferay.Service.ajax(params, callback);
	},

	lockFileEntry: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "lockFileEntry";

		return Liferay.Service.ajax(params, callback);
	},

	unlockFileEntry: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "unlockFileEntry";

		return Liferay.Service.ajax(params, callback);
	},

	updateFileEntry: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateFileEntry";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.DL.DLFileShortcut = {
	serviceClassName: Liferay.Service.DL.servicePackage + "DLFileShortcut" + Liferay.Service.classNameSuffix,

	addFileShortcut: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addFileShortcut";

		return Liferay.Service.ajax(params, callback);
	},

	deleteFileShortcut: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteFileShortcut";

		return Liferay.Service.ajax(params, callback);
	},

	getFileShortcut: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getFileShortcut";

		return Liferay.Service.ajax(params, callback);
	},

	updateFileShortcut: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateFileShortcut";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.DL.DLFolder = {
	serviceClassName: Liferay.Service.DL.servicePackage + "DLFolder" + Liferay.Service.classNameSuffix,

	addFolder: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addFolder";

		return Liferay.Service.ajax(params, callback);
	},

	copyFolder: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "copyFolder";

		return Liferay.Service.ajax(params, callback);
	},

	deleteFolder: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteFolder";

		return Liferay.Service.ajax(params, callback);
	},

	getFolder: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getFolder";

		return Liferay.Service.ajax(params, callback);
	},

	getFolderId: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getFolderId";

		return Liferay.Service.ajax(params, callback);
	},

	reIndexSearch: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "reIndexSearch";

		return Liferay.Service.ajax(params, callback);
	},

	updateFolder: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateFolder";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.IG = {
	servicePackage: "com.liferay.portlet.imagegallery.service.http."
};

Liferay.Service.IG.IGFolder = {
	serviceClassName: Liferay.Service.IG.servicePackage + "IGFolder" + Liferay.Service.classNameSuffix,

	addFolder: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addFolder";

		return Liferay.Service.ajax(params, callback);
	},

	deleteFolder: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteFolder";

		return Liferay.Service.ajax(params, callback);
	},

	getFolder: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getFolder";

		return Liferay.Service.ajax(params, callback);
	},

	updateFolder: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateFolder";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.IG.IGImage = {
	serviceClassName: Liferay.Service.IG.servicePackage + "IGImage" + Liferay.Service.classNameSuffix,

	deleteImage: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteImage";

		return Liferay.Service.ajax(params, callback);
	},

	getImage: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getImage";

		return Liferay.Service.ajax(params, callback);
	},

	getImageByLargeImageId: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getImageByLargeImageId";

		return Liferay.Service.ajax(params, callback);
	},

	getImageBySmallImageId: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getImageBySmallImageId";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Journal = {
	servicePackage: "com.liferay.portlet.journal.service.http."
};

Liferay.Service.Journal.JournalArticle = {
	serviceClassName: Liferay.Service.Journal.servicePackage + "JournalArticle" + Liferay.Service.classNameSuffix,

	getArticle: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getArticle";

		return Liferay.Service.ajax(params, callback);
	},

	removeArticleLocale: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "removeArticleLocale";

		return Liferay.Service.ajax(params, callback);
	},

	updateContent: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateContent";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Journal.JournalFeed = {
	serviceClassName: Liferay.Service.Journal.servicePackage + "JournalFeed" + Liferay.Service.classNameSuffix,

	addFeed: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addFeed";

		return Liferay.Service.ajax(params, callback);
	},

	deleteFeed: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteFeed";

		return Liferay.Service.ajax(params, callback);
	},

	getFeed: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getFeed";

		return Liferay.Service.ajax(params, callback);
	},

	updateFeed: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateFeed";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Journal.JournalStructure = {
	serviceClassName: Liferay.Service.Journal.servicePackage + "JournalStructure" + Liferay.Service.classNameSuffix,

	addStructure: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addStructure";

		return Liferay.Service.ajax(params, callback);
	},

	deleteStructure: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteStructure";

		return Liferay.Service.ajax(params, callback);
	},

	getStructure: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getStructure";

		return Liferay.Service.ajax(params, callback);
	},

	updateStructure: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateStructure";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Journal.JournalTemplate = {
	serviceClassName: Liferay.Service.Journal.servicePackage + "JournalTemplate" + Liferay.Service.classNameSuffix,

	deleteTemplate: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteTemplate";

		return Liferay.Service.ajax(params, callback);
	},

	getTemplate: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getTemplate";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.MB = {
	servicePackage: "com.liferay.portlet.messageboards.service.http."
};

Liferay.Service.MB.MBBan = {
	serviceClassName: Liferay.Service.MB.servicePackage + "MBBan" + Liferay.Service.classNameSuffix,

	addBan: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addBan";

		return Liferay.Service.ajax(params, callback);
	},

	deleteBan: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteBan";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.MB.MBCategory = {
	serviceClassName: Liferay.Service.MB.servicePackage + "MBCategory" + Liferay.Service.classNameSuffix,

	addCategory: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addCategory";

		return Liferay.Service.ajax(params, callback);
	},

	deleteCategory: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteCategory";

		return Liferay.Service.ajax(params, callback);
	},

	getCategory: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getCategory";

		return Liferay.Service.ajax(params, callback);
	},

	getCategories: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getCategories";

		return Liferay.Service.ajax(params, callback);
	},

	getCategoriesCount: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getCategoriesCount";

		return Liferay.Service.ajax(params, callback);
	},

	subscribeCategory: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "subscribeCategory";

		return Liferay.Service.ajax(params, callback);
	},

	unsubscribeCategory: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "unsubscribeCategory";

		return Liferay.Service.ajax(params, callback);
	},

	updateCategory: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateCategory";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.MB.MBMessage = {
	serviceClassName: Liferay.Service.MB.servicePackage + "MBMessage" + Liferay.Service.classNameSuffix,

	addMessage: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addMessage";

		return Liferay.Service.ajax(params, callback);
	},

	deleteDiscussionMessage: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteDiscussionMessage";

		return Liferay.Service.ajax(params, callback);
	},

	deleteMessage: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteMessage";

		return Liferay.Service.ajax(params, callback);
	},

	getCategoryMessages: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getCategoryMessages";

		return Liferay.Service.ajax(params, callback);
	},

	getCategoryMessagesCount: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getCategoryMessagesCount";

		return Liferay.Service.ajax(params, callback);
	},

	getCategoryMessagesRSS: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getCategoryMessagesRSS";

		return Liferay.Service.ajax(params, callback);
	},

	getCompanyMessagesRSS: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getCompanyMessagesRSS";

		return Liferay.Service.ajax(params, callback);
	},

	getGroupMessagesRSS: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getGroupMessagesRSS";

		return Liferay.Service.ajax(params, callback);
	},

	getMessage: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getMessage";

		return Liferay.Service.ajax(params, callback);
	},

	getMessageDisplay: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getMessageDisplay";

		return Liferay.Service.ajax(params, callback);
	},

	getThreadMessagesRSS: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getThreadMessagesRSS";

		return Liferay.Service.ajax(params, callback);
	},

	subscribeMessage: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "subscribeMessage";

		return Liferay.Service.ajax(params, callback);
	},

	unsubscribeMessage: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "unsubscribeMessage";

		return Liferay.Service.ajax(params, callback);
	},

	updateDiscussionMessage: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateDiscussionMessage";

		return Liferay.Service.ajax(params, callback);
	},

	updateMessage: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateMessage";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.MB.MBThread = {
	serviceClassName: Liferay.Service.MB.servicePackage + "MBThread" + Liferay.Service.classNameSuffix,

	moveThread: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "moveThread";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Polls = {
	servicePackage: "com.liferay.portlet.polls.service.http."
};

Liferay.Service.Polls.PollsQuestion = {
	serviceClassName: Liferay.Service.Polls.servicePackage + "PollsQuestion" + Liferay.Service.classNameSuffix,

	addQuestion: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addQuestion";

		return Liferay.Service.ajax(params, callback);
	},

	deleteQuestion: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteQuestion";

		return Liferay.Service.ajax(params, callback);
	},

	getQuestion: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getQuestion";

		return Liferay.Service.ajax(params, callback);
	},

	updateQuestion: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateQuestion";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Polls.PollsVote = {
	serviceClassName: Liferay.Service.Polls.servicePackage + "PollsVote" + Liferay.Service.classNameSuffix,

	addVote: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addVote";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Ratings = {
	servicePackage: "com.liferay.portlet.ratings.service.http."
};

Liferay.Service.Ratings.RatingsEntry = {
	serviceClassName: Liferay.Service.Ratings.servicePackage + "RatingsEntry" + Liferay.Service.classNameSuffix,

	updateEntry: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateEntry";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Shopping = {
	servicePackage: "com.liferay.portlet.shopping.service.http."
};

Liferay.Service.Shopping.ShoppingCategory = {
	serviceClassName: Liferay.Service.Shopping.servicePackage + "ShoppingCategory" + Liferay.Service.classNameSuffix,

	addCategory: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addCategory";

		return Liferay.Service.ajax(params, callback);
	},

	deleteCategory: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteCategory";

		return Liferay.Service.ajax(params, callback);
	},

	getCategory: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getCategory";

		return Liferay.Service.ajax(params, callback);
	},

	updateCategory: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateCategory";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Shopping.ShoppingCoupon = {
	serviceClassName: Liferay.Service.Shopping.servicePackage + "ShoppingCoupon" + Liferay.Service.classNameSuffix,

	addCoupon: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addCoupon";

		return Liferay.Service.ajax(params, callback);
	},

	deleteCoupon: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteCoupon";

		return Liferay.Service.ajax(params, callback);
	},

	getCoupon: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getCoupon";

		return Liferay.Service.ajax(params, callback);
	},

	search: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "search";

		return Liferay.Service.ajax(params, callback);
	},

	updateCoupon: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateCoupon";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Shopping.ShoppingItem = {
	serviceClassName: Liferay.Service.Shopping.servicePackage + "ShoppingItem" + Liferay.Service.classNameSuffix,

	addBookItems: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addBookItems";

		return Liferay.Service.ajax(params, callback);
	},

	deleteItem: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteItem";

		return Liferay.Service.ajax(params, callback);
	},

	getItem: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getItem";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Shopping.ShoppingOrder = {
	serviceClassName: Liferay.Service.Shopping.servicePackage + "ShoppingOrder" + Liferay.Service.classNameSuffix,

	completeOrder: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "completeOrder";

		return Liferay.Service.ajax(params, callback);
	},

	deleteOrder: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteOrder";

		return Liferay.Service.ajax(params, callback);
	},

	getOrder: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getOrder";

		return Liferay.Service.ajax(params, callback);
	},

	sendEmail: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "sendEmail";

		return Liferay.Service.ajax(params, callback);
	},

	updateOrder: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateOrder";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.SC = {
	servicePackage: "com.liferay.portlet.softwarecatalog.service.http."
};

Liferay.Service.SC.SCLicense = {
	serviceClassName: Liferay.Service.SC.servicePackage + "SCLicense" + Liferay.Service.classNameSuffix,

	addLicense: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addLicense";

		return Liferay.Service.ajax(params, callback);
	},

	deleteLicense: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteLicense";

		return Liferay.Service.ajax(params, callback);
	},

	getLicense: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getLicense";

		return Liferay.Service.ajax(params, callback);
	},

	updateLicense: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateLicense";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.SC.SCFrameworkVersion = {
	serviceClassName: Liferay.Service.SC.servicePackage + "SCFrameworkVersion" + Liferay.Service.classNameSuffix,

	addFrameworkVersion: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addFrameworkVersion";

		return Liferay.Service.ajax(params, callback);
	},

	deleteFrameworkVersion: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteFrameworkVersion";

		return Liferay.Service.ajax(params, callback);
	},

	getFrameworkVersion: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getFrameworkVersion";

		return Liferay.Service.ajax(params, callback);
	},

	getFrameworkVersions: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getFrameworkVersions";

		return Liferay.Service.ajax(params, callback);
	},

	updateFrameworkVersion: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateFrameworkVersion";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.SC.SCProductEntry = {
	serviceClassName: Liferay.Service.SC.servicePackage + "SCProductEntry" + Liferay.Service.classNameSuffix,

	addProductEntry: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addProductEntry";

		return Liferay.Service.ajax(params, callback);
	},

	deleteProductEntry: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteProductEntry";

		return Liferay.Service.ajax(params, callback);
	},

	getProductEntry: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getProductEntry";

		return Liferay.Service.ajax(params, callback);
	},

	updateProductEntry: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateProductEntry";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.SC.SCProductVersion = {
	serviceClassName: Liferay.Service.SC.servicePackage + "SCProductVersion" + Liferay.Service.classNameSuffix,

	addProductVersion: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addProductVersion";

		return Liferay.Service.ajax(params, callback);
	},

	deleteProductVersion: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteProductVersion";

		return Liferay.Service.ajax(params, callback);
	},

	getProductVersion: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getProductVersion";

		return Liferay.Service.ajax(params, callback);
	},

	getProductVersions: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getProductVersions";

		return Liferay.Service.ajax(params, callback);
	},

	getProductVersionsCount: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getProductVersionsCount";

		return Liferay.Service.ajax(params, callback);
	},

	updateProductVersion: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateProductVersion";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Tags = {
	servicePackage: "com.liferay.portlet.tags.service.http."
};

Liferay.Service.Tags.TagsAsset = {
	serviceClassName: Liferay.Service.Tags.servicePackage + "TagsAsset" + Liferay.Service.classNameSuffix,

	deleteAsset: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteAsset";

		return Liferay.Service.ajax(params, callback);
	},

	getAsset: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getAsset";

		return Liferay.Service.ajax(params, callback);
	},

	getAssetsRSS: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getAssetsRSS";

		return Liferay.Service.ajax(params, callback);
	},

	getAssetTypes: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getAssetTypes";

		return Liferay.Service.ajax(params, callback);
	},

	getCompanyAssetDisplays: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getCompanyAssetDisplays";

		return Liferay.Service.ajax(params, callback);
	},

	getCompanyAssets: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getCompanyAssets";

		return Liferay.Service.ajax(params, callback);
	},

	getCompanyAssetsCount: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getCompanyAssetsCount";

		return Liferay.Service.ajax(params, callback);
	},

	getCompanyAssetsRSS: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getCompanyAssetsRSS";

		return Liferay.Service.ajax(params, callback);
	},

	incrementViewCounter: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "incrementViewCounter";

		return Liferay.Service.ajax(params, callback);
	},

	searchAssetDisplays: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "searchAssetDisplays";

		return Liferay.Service.ajax(params, callback);
	},

	searchAssetDisplaysCount: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "searchAssetDisplaysCount";

		return Liferay.Service.ajax(params, callback);
	},

	updateAsset: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateAsset";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Tags.TagsEntry = {
	serviceClassName: Liferay.Service.Tags.servicePackage + "TagsEntry" + Liferay.Service.classNameSuffix,

	addEntry: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addEntry";

		return Liferay.Service.ajax(params, callback);
	},

	deleteEntry: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteEntry";

		return Liferay.Service.ajax(params, callback);
	},

	getEntries: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getEntries";

		return Liferay.Service.ajax(params, callback);
	},

	search: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "search";

		return Liferay.Service.ajax(params, callback);
	},

	searchAutocomplete: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "searchAutocomplete";

		return Liferay.Service.ajax(params, callback);
	},

	searchCount: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "searchCount";

		return Liferay.Service.ajax(params, callback);
	},

	updateEntry: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateEntry";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Tags.TagsProperty = {
	serviceClassName: Liferay.Service.Tags.servicePackage + "TagsProperty" + Liferay.Service.classNameSuffix,

	addProperty: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addProperty";

		return Liferay.Service.ajax(params, callback);
	},

	deleteProperty: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteProperty";

		return Liferay.Service.ajax(params, callback);
	},

	getProperties: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getProperties";

		return Liferay.Service.ajax(params, callback);
	},

	getPropertyValues: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getPropertyValues";

		return Liferay.Service.ajax(params, callback);
	},

	updateProperty: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateProperty";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Wiki = {
	servicePackage: "com.liferay.portlet.wiki.service.http."
};

Liferay.Service.Wiki.WikiNode = {
	serviceClassName: Liferay.Service.Wiki.servicePackage + "WikiNode" + Liferay.Service.classNameSuffix,

	addNode: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addNode";

		return Liferay.Service.ajax(params, callback);
	},

	deleteNode: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deleteNode";

		return Liferay.Service.ajax(params, callback);
	},

	getNode: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getNode";

		return Liferay.Service.ajax(params, callback);
	},

	updateNode: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updateNode";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Wiki.WikiPage = {
	serviceClassName: Liferay.Service.Wiki.servicePackage + "WikiPage" + Liferay.Service.classNameSuffix,

	addPage: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addPage";

		return Liferay.Service.ajax(params, callback);
	},

	deletePage: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deletePage";

		return Liferay.Service.ajax(params, callback);
	},

	getPage: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getPage";

		return Liferay.Service.ajax(params, callback);
	},

	revertPage: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "revertPage";

		return Liferay.Service.ajax(params, callback);
	},

	updatePage: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "updatePage";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Workflow = {
	servicePackage: "com.liferay.portlet.workflow.service.http."
};

Liferay.Service.Workflow.WorkflowComponent = {
	serviceClassName: Liferay.Service.Workflow.servicePackage + "WorkflowComponent" + Liferay.Service.classNameSuffix,

	getCurrentTasks: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getCurrentTasks";

		return Liferay.Service.ajax(params, callback);
	},

	getCurrentTasksXml: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getCurrentTasksXml";

		return Liferay.Service.ajax(params, callback);
	},

	deploy: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "deploy";

		return Liferay.Service.ajax(params, callback);
	},

	getDefinition: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getDefinition";

		return Liferay.Service.ajax(params, callback);
	},

	getDefinitions: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getDefinitions";

		return Liferay.Service.ajax(params, callback);
	},

	getDefinitionsXml: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getDefinitionsXml";

		return Liferay.Service.ajax(params, callback);
	},

	getDefinitionsCount: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getDefinitionsCount";

		return Liferay.Service.ajax(params, callback);
	},

	getDefinitionsCountXml: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getDefinitionsCountXml";

		return Liferay.Service.ajax(params, callback);
	},

	getDefinitionXml: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getDefinitionXml";

		return Liferay.Service.ajax(params, callback);
	},

	getInstances: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getInstances";

		return Liferay.Service.ajax(params, callback);
	},

	getInstancesCount: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getInstancesCount";

		return Liferay.Service.ajax(params, callback);
	},

	getInstancesCountXml: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getInstancesCountXml";

		return Liferay.Service.ajax(params, callback);
	},

	getInstancesXml: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getInstancesXml";

		return Liferay.Service.ajax(params, callback);
	},

	getTask: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getTask";

		return Liferay.Service.ajax(params, callback);
	},

	getTaskXml: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getTaskXml";

		return Liferay.Service.ajax(params, callback);
	},

	getTaskFormElements: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getTaskFormElements";

		return Liferay.Service.ajax(params, callback);
	},

	getTaskFormElementsXml: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getTaskFormElementsXml";

		return Liferay.Service.ajax(params, callback);
	},

	getTaskTransitions: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getTaskTransitions";

		return Liferay.Service.ajax(params, callback);
	},

	getTaskTransitionsXml: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getTaskTransitionsXml";

		return Liferay.Service.ajax(params, callback);
	},

	getUserTasks: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getUserTasks";

		return Liferay.Service.ajax(params, callback);
	},

	getUserTasksCount: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getUserTasksCount";

		return Liferay.Service.ajax(params, callback);
	},

	getUserTasksCountXml: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getUserTasksCountXml";

		return Liferay.Service.ajax(params, callback);
	},

	getUserTasksXml: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getUserTasksXml";

		return Liferay.Service.ajax(params, callback);
	},

	signalInstance: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "signalInstance";

		return Liferay.Service.ajax(params, callback);
	},

	signalToken: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "signalToken";

		return Liferay.Service.ajax(params, callback);
	},

	startWorkflow: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "startWorkflow";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Workflow.WorkflowDefinition = {
	serviceClassName: Liferay.Service.Workflow.servicePackage + "WorkflowDefinition" + Liferay.Service.classNameSuffix,

	addDefinition: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addDefinition";

		return Liferay.Service.ajax(params, callback);
	},

	getDefinition: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "getDefinition";

		return Liferay.Service.ajax(params, callback);
	}
};

Liferay.Service.Workflow.WorkflowInstance = {
	serviceClassName: Liferay.Service.Workflow.servicePackage + "WorkflowInstance" + Liferay.Service.classNameSuffix,

	addInstance: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "addInstance";

		return Liferay.Service.ajax(params, callback);
	},

	signalInstance: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "signalInstance";

		return Liferay.Service.ajax(params, callback);
	},

	signalToken: function(params, callback) {
		params.serviceClassName = this.serviceClassName;
		params.serviceMethodName = "signalToken";

		return Liferay.Service.ajax(params, callback);
	}
};