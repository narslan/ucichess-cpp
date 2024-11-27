/*
	Error-checking support functions
	AUP2, Sec. 1.04.2

	Copyright 2003 by Marc J. Rochkind. All rights reserved.
	May be copied only for purposes and under conditions described
	on the Web page www.basepath.com/aup/copyright.htm.

	The Example Files are provided "as is," without any warranty;
	without even the implied warranty of merchantability or fitness
	for a particular purpose. The author and his publisher are not
	responsible for any damages, direct or incidental, resulting
	from the use or non-use of these Example Files.

	The Example Files may contain defects, and some contain deliberate
	coding mistakes that were included for educational reasons.
	You are responsible for determining if and how the Example Files
	are to be used.

*/
#pragma once

static struct ec_node {
  struct ec_node* ec_next;
  int ec_errno;
  char* ec_context;
} *ec_head, ec_node_emergency;
static char ec_s_emergency[100];

static void ec_push(const char* fcn, const char* file, int line, const char* str, int errno_arg) {
  auto node = ec_node();
  node.ec_errno = errno_arg;

  //fmt::print("{} {} {} {} {} {} {} {}", errno_arg, fcn, "{", file, ":", line, "}", str);
}

;
// namespace ucichess
