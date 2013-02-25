#! /usr/bin/env python
### search file script
# $Id: search.py 21 2005-04-11 02:48:49Z cash $

import string,os,sys,re
import gc

re_test_string = re.compile(r'(([^:]|^procedure)*)(:\s*)(TWVComboBox;)',re.I)
re_class_begin = re.compile(r'[^=]+\s{0,}=\s{0,}class\s{0,}\(\w{0,}\)',re.I)

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
	# dfm_file = _get_pas_dfm_file_name(file)
		
	global re_class_begin
	# print "searching file %s " % file
	file_content = []
	line = file_handle.readline()
	while line :
		line = line.strip(' \t')
		file_content.append(line)
		line = file_handle.readline()
	# find test value
	test_value = []
	in_declare = False
	for line in file_content :
		if not in_declare:
			m = re_class_begin.match(line)
			if m : 
				in_declare = True
				continue
		else:
			if line == "end;" :
				in_declare = False
			else:
				m = re_test_string.match(line)
				if m :
					test_value.append(m.group(1).strip(' \t'))
	
	if len(test_value) == 0:
		return False
	# find searching value
	for test_key in test_value :
		search_str = test_key+r'\.ItemsDataEntry\s*:=\s*\'\';'
		#print search_str
		try:
			search_reg = re.compile(re.escape(search_str),re.I)
		except Exception,ex:
			print "Build regexp error %s : [%s] " % (ex,search_str)
			continue
		x = 0
		for line in file_content:
			x += 1
			m = search_reg.match(line)
			if m :
				# print "line %s" % line
				break
		if x >= len(file_content):
			print "Not Found in file [%s] : [%s]" % (file,test_key)
	
	if len(test_value) > 0 :
		found = True
	else:
		found = False
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