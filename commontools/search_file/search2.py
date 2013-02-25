#! /usr/bin/env python
### search file script
# $Id: search2.py 22 2005-04-11 03:53:46Z cash $

import string,os,sys,re
import gc

re_test_string = re.compile(r'^\s*(FreeIDObjects)\([^\)]+\);',re.I)
re_region_comment_start = re.compile(r'\s*\{',re.I)
re_region_comment_end = re.compile(r'.*\}',re.I)

is_marching = True

def _search_file(basedir):
	if os.path.exists(basedir) :
		_recursive_search(basedir)
	else:
		print "Path not found!"
		sys.exit(1)

def _is_file_can_parse(file):
	if os.path.isdir(file) or os.path.islink(file):
		return False
	if file.rfind('.') > -1 :
		ext = file[file.rfind('.'):]
		return (string.lower(ext) == ".pas")
	else:
		return False

def _print_file_name(file_name):
	pass
	#print "File : %s " % (file_name)

def _get_pas_dfm_file_name(file_name):
	ext_pos = file_name.rfind('.')
	if ext_pos > -1 :
		file = file_name[:file_name.rfind('.')]
		file = file + ".dfm"
		return file
	return False

def _get_component_property_value(dfm_file,com_names,properties):
	try:
		dfm_handle = open(dfm_file,'r')
	except:
		return False
	
	for c,p in zip(com_names,properties):
		pass
	dfm_handle.close()
	
def _is_find_regexp_in_file(file):
	try:
		file_handle = open(file,'r')
	except:
		print "Error : cannot open file %s " % file
		return False
		
	file_content = []
	line = file_handle.readline()
	while line :
		line = line.strip(' \t')
		file_content.append(line)
		line = file_handle.readline()
	# find test value
	test_value = []
	x = 0
	found = False
	in_comment = False
	for line in file_content :
		x += 1
		# 
		if in_comment :
			m = re_region_comment_end.match(line)
			if m: 
				in_comment = False
			continue
		m = re_region_comment_start.match(line)
		if m :
			in_comment = True
			continue
			
		m = re_test_string.match(line)
		if m :
			found = True
			print "Find in file [%s] line [%04d] value[%s]" % (file,x,m.group(1))
			
	file_handle.close()
	file_content = []
	gc.collect()
	return found
	
def _recursive_search(basedir):
	global non_marching
	sub_files = os.listdir(basedir)
	for file_name in sub_files:
		real_path = os.path.join(basedir,file_name)
		if os.path.isdir(real_path) :
			_recursive_search(real_path)
		elif _is_file_can_parse(file_name):
			if _is_find_regexp_in_file(real_path):
				is_found = True
			else:
				is_found = False
			if is_marching and is_found:
				_print_file_name(real_path)
			elif (not is_marching) and (not is_found):
				_print_file_name(real_path)
				
		
if __name__ == "__main__":
	search_dir = "."
	if len(sys.argv) > 1 :
		search_dir = sys.argv[1]
	print "searching in [%s] ! waiting..." % search_dir
	_search_file(search_dir)