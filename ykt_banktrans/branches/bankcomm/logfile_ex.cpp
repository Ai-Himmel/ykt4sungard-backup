static bool do_sys_init()
{

	DWORD len = GetModuleFileName(NULL, g_module_path, sizeof(g_module_path) - 1);

	char *pos = strrchr(g_module_path, '\\');
	len = pos - g_module_path + 1;
	g_module_path[len] = '\0';
	char log_path[1204] = "";
	sprintf(log_path, "%slogs\\", g_module_path);
	DWORD ret = GetFileAttributes(log_path);
	if ( ret == INVALID_FILE_ATTRIBUTES )
	{
		if (!CreateDirectory(log_path, NULL))
			return false;
	}
	// ����־�ļ�
	if (g_logger.openlog(log_path))
		return false;
	g_logger.writelog("��ʼ���ɹ�");
	return true;
}